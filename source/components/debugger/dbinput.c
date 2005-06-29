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



#define COMMAND_PROMPT      '-'
#define EXECUTE_PROMPT      '%'

char                    *Version = "X003";
char                    LineBuf[80];
char                    ScopeBuf[40];
char                    DebugFilename[40];
char                    *Args[DB_MAX_ARGS];
char                    *Buffer;
char                    *Filename = NULL;
UINT32                  Gbl_MethodBreakpoint = 0;

int                     opt_tables      = FALSE;
int                     opt_disasm      = FALSE;
int                     opt_stats       = FALSE;
int                     opt_parse_jit   = FALSE;
int						opt_verbose     = TRUE;
   

/*
 * AML Debugger commands
 */

#define CMD_NOT_FOUND       0
#define CMD_NULL            1
#define CMD_ALLOCATIONS     2
#define CMD_ARGUMENTS       3
#define CMD_BREAKPOINT      4
#define CMD_CLOSE           5
#define CMD_DEBUG           6
#define CMD_DUMP            7
#define CMD_EXECUTE         8
#define CMD_EXIT            9
#define CMD_GO              10
#define CMD_HELP            11
#define CMD_HELP2           12
#define CMD_LEVEL           13
#define CMD_LIST            14
#define CMD_LOCALS          15
#define CMD_METHODS         16
#define CMD_NAMESPACE       17
#define CMD_NOTIFY          18
#define CMD_OBJECT          19
#define CMD_OPEN            20
#define CMD_PREFIX          21
#define CMD_QUIT            22
#define CMD_RESULTS         23
#define CMD_SET             24
#define CMD_STATS           25
#define CMD_STOP            26
#define CMD_TERMINATE       27
#define CMD_TREE            28

#define CMD_FIRST_VALID     2
#define CMD_NUM_COMMANDS    29


typedef struct CommandInfo
{
    char                    *Name;          /* Command Name */
    char                    MinArgs;        /* Minimum arguments required */

} COMMAND_INFO;

COMMAND_INFO            Commands[CMD_NUM_COMMANDS] = {
                            "<NOT FOUND>",  0,
                            "<NULL>",       0,
                            "ALLOCATIONS",  0,
                            "ARGUMENTS",    0,
                            "BREAKPOINT",   1,
                            "CLOSE",        0,
                            "DEBUG",        1,
                            "DUMP",         1,
                            "EXECUTE",      1,
                            "EXIT",         0,
                            "GO",           0,
                            "HELP",         0,
                            "?",            0,
                            "LEVEL",        1,
                            "LIST",         0,
                            "LOCALS",       0,
                            "METHODS",      0,
                            "NAMESPACE",    0,
                            "NOTIFY",       2,
                            "OBJECT",       1,
                            "OPEN",         1,
                            "PREFIX",       1,
                            "QUIT",         0,
                            "RESULTS",      0,
                            "SET",          3,
                            "STATS",        0,
                            "STOP",         0,
                            "TERMINATE",    0,
                            "TREE",         0};



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
    OsdPrintf ("\nACPI/AML Debugger Commands\n\n");
    OsdPrintf ("Allocations                     Display memory allocation info\n");
    OsdPrintf ("Close                           Close debug output file\n");
    OsdPrintf ("Debug <Method Path>             Single Step a control method\n");
    OsdPrintf ("Dump <Address>|<NamePath>       Display ACPI objects or memory\n");
    OsdPrintf ("Execute <Method Path>           Execute control method (full pathname)\n");
    OsdPrintf ("Help                            This help screen\n");
    OsdPrintf ("Level <DebugLevel>              Set level of debug output\n");
    OsdPrintf ("Methods [<lines per screen>]    Display list of loaded control methods\n");
    OsdPrintf ("Notify <NamePath> <Value>       Send a notification\n");
    OsdPrintf ("Object <Address>                Display formatted ACPI object\n");
    OsdPrintf ("Open <Debug Filename>           Open a file for debug output\n");
    OsdPrintf ("Prefix [<NamePath>]             Set or Get current execution prefix\n");
    OsdPrintf ("Quit or Exit                    Exit this command\n");
    OsdPrintf ("Stats                           Display namespace and memory statistics\n");
    OsdPrintf ("Terminate                       Delete namespace and all internal objects\n");

    OsdPrintf ("\nACPI/AML Control Method Execution Commands\n\n");
    OsdPrintf ("Arguments                       Display method arguments\n");
    OsdPrintf ("Breakpoint <AmlOffset>          Set an AML execution breakpoint\n");
    OsdPrintf ("Go                              Allow method to run to completion\n");
    OsdPrintf ("List [# of Aml Opcodes]         Display method ASL statements\n");
    OsdPrintf ("Locals                          Display method local variables\n");
    OsdPrintf ("Results                         Display method result stack\n");
    OsdPrintf ("Set <A|L> <#> <Value>           Set method Arguments and Locals\n");
    OsdPrintf ("Stop                            Terminate control method\n");
    OsdPrintf ("Tree                            Display control method calling tree\n");
    OsdPrintf ("<Enter>                         Single step next AML opcode\n");
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

    *String = 0;
    *Next = String + 1;

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
DbGetLine (void)
{
    UINT32                  i;
    INT32                   Count;
    char                    *Next;
    char                    *This;



    OsdGetLine (LineBuf);
    STRUPR (LineBuf);

    This = LineBuf;
    for (i = 0; i < DB_MAX_ARGS; i++)
    {
        Args[i] = DbGetNextToken (This, &Next);
        if (!Args[i])
        {
            break;
        }

        This = Next;
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

    for (i = CMD_FIRST_VALID; i < CMD_NUM_COMMANDS; i++)
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
 * FUNCTION:    DbExecuter
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
DbExecuter (
    char                    Prompt,
    ACPI_GENERIC_OP         *Op)
{
    UINT32                  Temp;
    UINT32                  Temp2;
    UINT32                  Temp3;
    INT32                   CommandIndex;
    INT32                   ParamCount;


    /* TBD: NEed a separate command line buffer for step mode */

    while (1)
    {
        OsdPrintf ("%1c ", Prompt);
        ParamCount = DbGetLine ();
        CommandIndex = DbMatchCommand (Args[0]);
        Temp = 0;

        /* Verify that we have the minimum number of params */

        if (ParamCount < Commands[CommandIndex].MinArgs)
        {
            OsdPrintf ("%d parameters entered, [%s] requires %d parameters\n", 
                            ParamCount, Commands[CommandIndex].Name, Commands[CommandIndex].MinArgs);
            continue;
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

        case CMD_ARGUMENTS:
            DbDisplayArguments ();
            break;

        case CMD_BREAKPOINT:
            DbSetMethodBreakpoint (Args[1], Op);
            break;

        case CMD_CLOSE:
            DbCloseDebugFile ();
            break;

        case CMD_DEBUG:
            if (OutputToFile && !DebugLevel)
            {
                OsdPrintf ("Debug output is not enabled!\n");
            }
            DbExecute (Args[1], EX_SINGLE_STEP);
            break;

        case CMD_DUMP:
            DbDecodeAndDisplayObject (Args[1]);
            break;

        case CMD_EXECUTE:
            if (OutputToFile && !DebugLevel)
            {
                OsdPrintf ("Debug output is not enabled!\n");
            }
            DbExecute (Args[1], EX_NO_SINGLE_STEP);
            break;

        case CMD_GO:
            Gbl_CmSingleStep = FALSE;
            return (AE_OK);

        case CMD_HELP:
        case CMD_HELP2:
            DbDisplayHelp ();
            break;

        case CMD_LEVEL:
            DebugLevel = STRTOUL (Args[1], NULL, 0);
            OsdPrintf ("Debug Level: %0lX\n", DebugLevel);
            break;

        case CMD_LIST:
            DbDisassembleAml (Args[1], Op);
            break;

        case CMD_LOCALS:
            DbDisplayLocals ();
            break;
        
        case CMD_METHODS:
            if (ParamCount > 0)
            {
                Temp = STRTOUL (Args[1], NULL, 0);
            }
            DbDisplayAllMethods (Temp);
            break;

        case CMD_NAMESPACE:
            DbDumpNamespace ();
            break;

        case CMD_NOTIFY:
            if (ParamCount < 2)
            {
                OsdPrintf ("Requires 2 parameters\n");
                break;
            }
            Temp = STRTOUL (Args[2], NULL, 0);
            DbSendNotify (Args[1], Temp);
            break;

        case CMD_OBJECT:
            Temp = STRTOUL (Args[1], NULL, 0);
            DbDisplayInternalObject ((ACPI_OBJECT_INTERNAL *) Temp);
            break;

        case CMD_OPEN:
            if (DebugLevel == DEBUG_DEFAULT)
            {
                DebugLevel = 0x0FFFFEFF;
            }
            
            DbOpenDebugFile (Args[1]);
            break;

        case CMD_PREFIX:
            DbSetScope (Args[1]);
            break;

        case CMD_RESULTS:
            DbDisplayResults ();
            break;
     
        case CMD_SET:
            if ((Args[1][0] != 'L') &&
                (Args[1][0] != 'A'))
            {
                OsdPrintf ("Invalid SET operand: %s\n", Args[1]);
                break;
            }

            Temp2 = STRTOUL (Args[2], NULL, 0);
            Temp3 = STRTOUL (Args[3], NULL, 0);

            DbSetMethodData (Args[1][0], Temp2, Temp3);
            break;

        case CMD_STATS:
            DbDisplayStatistics ();
            break;

        case CMD_STOP:
            return (AE_AML_ERROR);
            break;

        case CMD_TERMINATE:
            AcpiTerminate ();
            break;

        case CMD_TREE:
            DbDisplayCallingTree ();
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
            AcpiTerminate ();
//            DbCloseDebugFile ();
            return (AE_OK);

        case CMD_NOT_FOUND:
            OsdPrintf ("Unknown Command\n");
        }
    }
}



/******************************************************************************
 * 
 * FUNCTION:    DbSingleStep  
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Called just before execution of an AML opcode.
 *
 *****************************************************************************/

ACPI_STATUS
DbSingleStep (
    ACPI_GENERIC_OP         *Op,
    UINT8                   OpType)
{
    ACPI_GENERIC_OP         *Next;
    ACPI_STATUS             Status;


    /* Is there a breakpoint set? */

    if (Gbl_MethodBreakpoint)
    {
        /* Check if the breakpoint has been reached or passed */

        if (Gbl_MethodBreakpoint <= Op->AmlOffset)
        {
            /* Hit the breakpoint, resume single step, reset breakpoint */

            OsdPrintf ("***Break*** at AML offset 0x%X\n", Op->AmlOffset);
            Gbl_CmSingleStep = TRUE;
            Gbl_MethodBreakpoint = 0;
        }
    }

    /* If we are not single stepping, just continue executing the method */

    if (!Gbl_CmSingleStep)
    {
        return (AE_OK);
    }


    /* 
     * Check if this is an opcode that we are interested in --
     * namely, opcodes that have arguments
     */
    switch (OpType)
    {
    case OPTYPE_UNDEFINED:
    case OPTYPE_CONSTANT:           /* argument type only */
    case OPTYPE_LITERAL:            /* argument type only */
    case OPTYPE_DATA_TERM:          /* argument type only */
    case OPTYPE_LOCAL_VARIABLE:     /* argument type only */
    case OPTYPE_METHOD_ARGUMENT:    /* argument type only */
        return (AE_OK);
        break;

    case OPTYPE_NAMED_OBJECT:
        switch (Op->Opcode)
        {

        case AML_MethodOp:
            return (AE_OK);
            break;
        }
    }

    /* Display this op (and only this op) */

    Next = Op->Next;
    Op->Next = NULL;
    DbDisplayOp (Op, ACPI_UINT32_MAX);
    Op->Next = Next;


    /* Go into the command loop and await next user command */

    Status = DbExecuter (EXECUTE_PROMPT, Op);

    /* User commands complete, continue execution of the interrupted method */

    return Status;
}

/******************************************************************************
 * 
 * FUNCTION:    DbInitialize
 *
 * PARAMETERS:  
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Init and start debugger
 *
 *****************************************************************************/

int
DbInitialize (void)
{      


    /* Init globals */

    Buffer = OsdAllocate (BUFFER_SIZE);

//    setvbuf (stdin, NULL, _IONBF, 0);
    ScopeBuf [0] = '\\';
    ScopeBuf [1] =  0;



	if (!opt_verbose)
	{
		INDENT_STRING = "    ";
        opt_disasm = TRUE;
        opt_stats = FALSE;
	}

    DbExecuter (COMMAND_PROMPT, NULL);

    return 0;
}


#endif  /* ACPI_DEBUG */

