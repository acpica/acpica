/******************************************************************************
 * 
 * Module Name: dbinput - user front-end to the AML debugger
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, Intel Corp.  All rights
 * reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.  
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee 
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.  
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
 * Intel shall be used in advertising or otherwise to promote the sale, use or
 * other dealings in products derived from or relating to the Covered Code
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED
 * HERE.  ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT,  ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES.  INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS.  INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE. 
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.  THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government.  In the
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/



#include <acpi.h>
#include <acapi.h>
#include <amlcode.h>
#include <parser.h>
#include <tables.h>
#include <namesp.h>
#include <interp.h>
#include <debugger.h>


#ifdef ACPI_DEBUG

#define _COMPONENT          DEBUGGER
        MODULE_NAME         ("dbinput");



char                    LineBuf[80];
char                    ParsedBuf[80];
char                    ScopeBuf[40];
char                    DebugFilename[40];
char                    *Args[DB_MAX_ARGS];
char                    *Buffer;
char                    *Filename = NULL;
UINT32                  Gbl_DbDebugLevel = 0x0FFFFFFF;
UINT32                  Gbl_DbConsoleDebugLevel = DEBUG_DEFAULT;
UINT32                  Gbl_MethodBreakpoint = 0;
BOOLEAN                 Gbl_MethodExecuting = FALSE;
BOOLEAN                 OutputToFile = FALSE;
UINT8                   Gbl_DbOutputFlags = DB_CONSOLE_OUTPUT;
BOOLEAN                 Gbl_DbTerminateThreads = FALSE;


BOOLEAN                 opt_tables      = FALSE;
BOOLEAN                 opt_disasm      = FALSE;
BOOLEAN                 opt_stats       = FALSE;
BOOLEAN                 opt_parse_jit   = FALSE;
BOOLEAN					opt_verbose     = TRUE;
   


/* This list of commands must match the string table below it */

enum AmlDebuggerCommands
{
    CMD_NOT_FOUND = 0,
    CMD_NULL,
    CMD_ALLOCATIONS,
    CMD_ARGS,
    CMD_ARGUMENTS,
    CMD_BREAKPOINT,
    CMD_CALL,
    CMD_CLOSE,
    CMD_DEBUG,
    CMD_DUMP,
    CMD_EVENT,
    CMD_EXECUTE,
    CMD_EXIT,
    CMD_FIND,
    CMD_GO,
    CMD_HELP,
    CMD_HELP2,
    CMD_HISTORY,
    CMD_HISTORY_EXE,
    CMD_HISTORY_LAST,
    CMD_INFORMATION,
    CMD_INTO,
    CMD_LEVEL,
    CMD_LIST,
    CMD_LOAD,
    CMD_LOCALS,
    CMD_METHODS,
    CMD_NAMESPACE,
    CMD_NOTIFY,
    CMD_OBJECT,
    CMD_OPEN,
    CMD_OWNER,
    CMD_PREFIX,
    CMD_QUIT,
    CMD_RESULTS,
    CMD_SET,
    CMD_STATS,
    CMD_STOP,
    CMD_TABLES,
    CMD_TERMINATE,
    CMD_TREE,
    CMD_UNLOAD 
};

#define CMD_FIRST_VALID     2


COMMAND_INFO                Commands[] = 
{
    "<NOT FOUND>",  0,
    "<NULL>",       0,
    "ALLOCATIONS",  0,
    "ARGS",         0,
    "ARGUMENTS",    0,
    "BREAKPOINT",   1,
    "CALL",         0,
    "CLOSE",        0,
    "DEBUG",        1,
    "DUMP",         1,
    "EVENT",        1,
    "EXECUTE",      1,
    "EXIT",         0,
    "FIND",         1,
    "GO",           0,
    "HELP",         0,
    "?",            0,
    "HISTORY",      0,
    "!",            1,
    "!!",           0,
    "INFORMATION",  0,
    "INTO",         0,
    "LEVEL",        0,
    "LIST",         0,
    "LOAD",         1,
    "LOCALS",       0,
    "METHODS",      0,
    "NAMESPACE",    0,
    "NOTIFY",       2,
    "OBJECT",       1,
    "OPEN",         1,
    "OWNER",        1,
    "PREFIX",       0,
    "QUIT",         0,
    "RESULTS",      0,
    "SET",          3,
    "STATS",        0,
    "STOP",         0,
    "TABLES",       0,
    "TERMINATE",    0,
    "TREE",         0,
    "UNLOAD",       0,
    NULL,           0
};




/******************************************************************************
 * 
 * FUNCTION:    DbDisplayHelp
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Print a usage message
 *
 *****************************************************************************/

void
DbDisplayHelp (void)
{
    OsdPrintf ("\nAML Debugger Commands\n\n");
    OsdPrintf ("Allocations                         Display memory allocation info\n");
    OsdPrintf ("Debug <Namepath> [Arguments]        Single Step a control method\n");
    OsdPrintf ("Dump <Address>|<Namepath>\n");
    OsdPrintf ("     [Byte|Word|Dword|Qword]        Display ACPI objects or memory\n");
    OsdPrintf ("Event <F|G> <Value>                 Generate Event (Fixed/GPE)\n");
    OsdPrintf ("Execute <Namepath> [Arguments]      Execute control method\n");
    OsdPrintf ("Find <Name>   (? is wildcard)       Find ACPI name(s) with wildcards\n");
    OsdPrintf ("Help                                This help screen\n");
    OsdPrintf ("History                             Display command history buffer\n");
    OsdPrintf ("Level [<DebugLevel>] [console]      Get/Set debug level for file or console\n");
    OsdPrintf ("Method                              Display list of loaded control methods\n");
    OsdPrintf ("Namespace [<Addr>|<Path>] [Depth]   Display loaded namespace tree/subtree\n");
    OsdPrintf ("Notify <NamePath> <Value>           Send a notification\n");
    OsdPrintf ("Objects <ObjectType>                Display all objects of the given type\n");
    OsdPrintf ("Owner <OwnerId> [Depth]             Display loaded namespace by object owner\n");
    OsdPrintf ("Prefix [<NamePath>]                 Set or Get current execution prefix\n");
    OsdPrintf ("Quit or Exit                        Exit this command\n");
    OsdPrintf ("Stats                               Display namespace and memory statistics\n");
    OsdPrintf ("Tables                              Display info about loaded ACPI tables\n");
    OsdPrintf ("Terminate                           Delete namespace and all internal objects\n");
    OsdPrintf ("Unload                              Unload an ACPI table\n");
    OsdPrintf ("! <CommandNumber>                   Execute command from history buffer\n");
    OsdPrintf ("!!                                  Execute last command again\n");

    OsdPrintf ("\nControl Method Execution Commands\n\n");
    OsdPrintf ("Arguments (or Args)                 Display method arguments\n");
    OsdPrintf ("Breakpoint <AmlOffset>              Set an AML execution breakpoint\n");
    OsdPrintf ("Call                                Run to next control method invocation\n");
    OsdPrintf ("Go                                  Allow method to run to completion\n");
    OsdPrintf ("Information                         Display info about the current method\n");
    OsdPrintf ("Into                                Step into (not over) a method call\n");
    OsdPrintf ("List [# of Aml Opcodes]             Display method ASL statements\n");
    OsdPrintf ("Locals                              Display method local variables\n");
    OsdPrintf ("Results                             Display method result stack\n");
    OsdPrintf ("Set <A|L> <#> <Value>               Set method data (Arguments/Locals)\n");
    OsdPrintf ("Stop                                Terminate control method\n");
    OsdPrintf ("Tree                                Display control method calling tree\n");
    OsdPrintf ("<Enter>                             Single step next AML opcode (over calls)\n");

    OsdPrintf ("\nFile I/O Commands\n\n");
    OsdPrintf ("Close                               Close debug output file\n");
    OsdPrintf ("Open <Output Filename>              Open a file for debug output\n");
    OsdPrintf ("Load <Input Filename>               Load ACPI table from a file\n");
}


/******************************************************************************
 * 
 * FUNCTION:    DbGetNextToken
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Command line parsing
 *
 *****************************************************************************/

char *
DbGetNextToken (
    char                    *String,
    char                    **Next)
{
    char                    *Start;

    /* At end of buffer? */

    if (!String || !(*String))
    {
        return NULL;
    }


    /* Get rid of any spaces at the beginning */

    if (*String == ' ')
    {
        while (*String && (*String == ' '))
        {
            String++;
        }

        if (!(*String))
        {
            return NULL;
        }
    }

    Start = String;

    /* Find end of token */

    while (*String && (*String != ' '))
    {
        String++;
    }


    if (!(*String))
    {
        *Next = NULL;
    }

    else
    {
        *String = 0;
        *Next = String + 1;
    }

    return Start;
}


/******************************************************************************
 * 
 * FUNCTION:    DbGetLine
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Get the next command line from the user.  Gets entire line
 *              up to the next newline
 *
 *****************************************************************************/

INT32
DbGetLine (
    char                    *InputBuffer)
{
    UINT32                  i;
    INT32                   Count;
    char                    *Next;
    char                    *This;



    STRCPY (ParsedBuf, InputBuffer);
    STRUPR (ParsedBuf);

    This = ParsedBuf;
    for (i = 0; i < DB_MAX_ARGS; i++)
    {
        Args[i] = DbGetNextToken (This, &Next);
        if (!Args[i])
        {
            break;
        }

        This = Next;
    }

  
    /* Uppercase the actual command */

    if (Args[0])
    {
        STRUPR (Args[0]);
    }

    Count = i;
    if (Count)
        Count--;  /* Number of args only */

    return Count;
}


/******************************************************************************
 * 
 * FUNCTION:    DbMatchCommand
 *
 * PARAMETERS:  UserCommand             - User command line
 *
 * RETURN:      Index into command array, -1 if not found
 *
 * DESCRIPTION: Search command array for a command match
 *
 *****************************************************************************/

INT32
DbMatchCommand (
    char                    *UserCommand)
{
    UINT32                  i;


    if (!UserCommand || UserCommand[0] == 0)
    {
        return CMD_NULL;
    }

    for (i = CMD_FIRST_VALID; Commands[i].Name; i++)
    {
        if (STRSTR (Commands[i].Name, UserCommand) == Commands[i].Name)
        {
            return i;
        }
    }

    /* Command not recognized */

    return CMD_NOT_FOUND;
}


/******************************************************************************
 * 
 * FUNCTION:    DbCommandDispatch
 *
 * PARAMETERS:  
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Command dispatcher.  Called from two places:
 *
 *****************************************************************************/

ACPI_STATUS
DbCommandDispatch (
    char                    *InputBuffer,
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op)
{
    UINT32                  Temp;
    INT32                   CommandIndex;
    INT32                   ParamCount;
    char                    *CommandLine;
    ACPI_STATUS             Status = AE_CTRL_TRUE;


    /* If AcpiTerminate has been called, terminate this thread */

    if (Gbl_DbTerminateThreads)
    {
        return (AE_CTRL_TERMINATE);
    }
   
    ParamCount = DbGetLine (InputBuffer);
    CommandIndex = DbMatchCommand (Args[0]);
    Temp = 0;

    /* Verify that we have the minimum number of params */

    if (ParamCount < Commands[CommandIndex].MinArgs)
    {
        OsdPrintf ("%d parameters entered, [%s] requires %d parameters\n", 
                        ParamCount, Commands[CommandIndex].Name, Commands[CommandIndex].MinArgs);
        return (AE_CTRL_TRUE);
    }

    /* Decode and dispatch the command */

    switch (CommandIndex)
    {
    case CMD_NULL:
        if (Op)
        {
            return (AE_OK);
        }
        break;

    case CMD_ALLOCATIONS:
        CmDumpAllocationInfo ();
        break;

    case CMD_ARGS:
    case CMD_ARGUMENTS:
        DbDisplayArguments ();
        break;

    case CMD_BREAKPOINT:
        DbSetMethodBreakpoint (Args[1], WalkState, Op);
        break;

    case CMD_CALL:
        DbSetMethodCallBreakpoint (Op);
        Status = AE_OK;
        break;

    case CMD_CLOSE:
        DbCloseDebugFile ();
        break;

    case CMD_DEBUG:
        DbExecute (Args[1], &Args[2], EX_SINGLE_STEP);
        break;

    case CMD_DUMP:
        DbDecodeAndDisplayObject (Args[1], Args[2]);
        break;

    case CMD_EVENT:
        OsdPrintf ("Event command not implemented\n");
        break;

    case CMD_EXECUTE:
        DbExecute (Args[1], &Args[2], EX_NO_SINGLE_STEP);
        break;

    case CMD_FIND:
        DbFindNameInNamespace (Args[1]);
        break;

    case CMD_GO:
        Gbl_CmSingleStep = FALSE;
        return (AE_OK);

    case CMD_HELP:
    case CMD_HELP2:
        DbDisplayHelp ();
        break;

    case CMD_HISTORY:
        DbDisplayHistory ();
        break;

    case CMD_HISTORY_EXE:
        CommandLine = DbGetFromHistory (Args[1]);
        if (!CommandLine)
        {
            return AE_CTRL_TRUE;
        }

        Status = DbCommandDispatch (CommandLine, WalkState, Op);
        if (Status == AE_OK)
            Status = AE_CTRL_TRUE;
        return Status;
        break;

    case CMD_HISTORY_LAST:
        CommandLine = DbGetFromHistory (NULL);
        if (!CommandLine)
        {
            return AE_CTRL_TRUE;
        }

        Status = DbCommandDispatch (CommandLine, WalkState, Op);
        if (Status == AE_OK)
            Status = AE_CTRL_TRUE;
        return Status;

    case CMD_INFORMATION:
        DbDisplayMethodInfo (Op);
        break;

    case CMD_INTO:
        if (Op)
        {
            Gbl_CmSingleStep = TRUE;             
            Gbl_MethodBreakpoint = 0;
            return AE_OK;
        }
        break;

    case CMD_LEVEL:
        if (ParamCount == 0)
        {
            OsdPrintf ("Current debug level for file output is:    %8.8lX\n", Gbl_DbDebugLevel);
            OsdPrintf ("Current debug level for console output is: %8.8lX\n", Gbl_DbConsoleDebugLevel);
        }
        else if (ParamCount == 2)
        {
            Temp = Gbl_DbConsoleDebugLevel;
            Gbl_DbConsoleDebugLevel = STRTOUL (Args[1], NULL, 16);
            OsdPrintf ("Debug Level for console output was %8.8lX, now %8.8lX\n", Temp, Gbl_DbConsoleDebugLevel);
        }
        else
        {
            Temp = Gbl_DbDebugLevel;
            Gbl_DbDebugLevel = STRTOUL (Args[1], NULL, 16);
            OsdPrintf ("Debug Level for file output was %8.8lX, now %8.8lX\n", Temp, Gbl_DbDebugLevel);
        }
        break;

    case CMD_LIST:
        DbDisassembleAml (Args[1], Op);
        break;

    case CMD_LOAD:
        DbLoadAcpiTable (Args[1]);
        break;

    case CMD_LOCALS:
        DbDisplayLocals ();
        break;
    
    case CMD_METHODS:
        DbDisplayObjects ("METHOD", Args[1]);
        break;

    case CMD_NAMESPACE:
        DbDumpNamespace (Args[1], Args[2]);
        break;

    case CMD_NOTIFY:
        Temp = STRTOUL (Args[2], NULL, 0);
        DbSendNotify (Args[1], Temp);
        break;

    case CMD_OBJECT:
        DbDisplayObjects (Args[1], Args[2]);
        break;

    case CMD_OPEN:
        DbOpenDebugFile (Args[1]);
        break;

    case CMD_OWNER:
        DbDumpNamespaceByOwner (Args[1], Args[2]);
        break;

    case CMD_PREFIX:
        DbSetScope (Args[1]);
        break;

    case CMD_RESULTS:
        DbDisplayResults ();
        break;
 
    case CMD_SET:
        DbSetMethodData (Args[1], Args[2], Args[3]);
        break;

    case CMD_STATS:
        DbDisplayStatistics ();
        break;

    case CMD_STOP:
        return (AE_AML_ERROR);
        break;

    case CMD_TABLES:
        DbDisplayTableInfo (Args[1]);
        break;

    case CMD_TERMINATE:
        DbSetOutputDestination (DB_REDIRECTABLE_OUTPUT);
        CmSubsystemShutdown ();

        /* TBD: Need some way to re-initialize without re-creating the semaphores! */

//        AcpiInitialize (NULL);
        break;

    case CMD_TREE:
        DbDisplayCallingTree ();
        break;

    case CMD_UNLOAD:
        DbUnloadAcpiTable (Args[1], Args[2]);
        break;

    case CMD_EXIT:
    case CMD_QUIT:
        if (Op)
        {
            return (AE_AML_ERROR);
        }

        if (!OutputToFile)
        {
            DebugLevel = DEBUG_DEFAULT;
        }

        /* Shutdown */

//        CmSubsystemShutdown ();
        DbCloseDebugFile ();

        Gbl_DbTerminateThreads = TRUE;

        return (AE_CTRL_TERMINATE);

    case CMD_NOT_FOUND:
        OsdPrintf ("Unknown Command\n");
        return (AE_CTRL_TRUE);
    }


    /* Add all commands that come here to the history buffer */

    DbAddToHistory (InputBuffer);
    return Status;
}


/******************************************************************************
 * 
 * FUNCTION:    DbExecuteThread
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Debugger execute thread.  Waits for a command line, then
 *              simply dispatches it.
 *
 *****************************************************************************/

void
DbExecuteThread (
    void                    *Context)
{
    ACPI_STATUS             Status = AE_OK;


    while (Status != AE_CTRL_TERMINATE)
    {
        Gbl_MethodExecuting = FALSE;
        Gbl_StepToNextCall = FALSE;

        CmAcquireMutex (MTX_DEBUGGER);
        Status = DbCommandDispatch (LineBuf, NULL, NULL);
        CmReleaseMutex (MTX_DEBUG_COMMAND);
    }
}



/******************************************************************************
 * 
 * FUNCTION:    DbUserCommands
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Command line execution for the AML debugger.  Commands are
 *              matched and dispatched here.
 *
 *****************************************************************************/

ACPI_STATUS
DbUserCommands (
    char                    Prompt,
    ACPI_GENERIC_OP         *Op)
{
    ACPI_STATUS             Status = AE_OK;

    /* TBD: NEed a separate command line buffer for step mode */

    while (!Gbl_DbTerminateThreads)
    {
        /* Force output to console until a command is entered */

        DbSetOutputDestination (DB_CONSOLE_OUTPUT);

        /* Different prompt if method is executing */

        if (!Gbl_MethodExecuting)
        {
            OsdPrintf ("%1c ", DB_COMMAND_PROMPT);
        }
        else
        {
            OsdPrintf ("%1c ", DB_EXECUTE_PROMPT);
        }

        /* Get the user input line */

        OsdGetLine (LineBuf);

        /* Signal the debug thread that we have a command to execute */

        CmReleaseMutex (MTX_DEBUGGER);
        CmAcquireMutex (MTX_DEBUG_COMMAND);
    }


    /* 
     * Only this thread (the original thread) should actually terminate the subsystem,
     * because all the semaphores are deleted during termination
     */
    AcpiTerminate ();

    return Status;
}



#endif  /* ACPI_DEBUG */

