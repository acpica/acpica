/******************************************************************************
 * 
 * Module Name: dbcmds - debug commands and output routines
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
#include <parser.h>
#include <dispatch.h>
#include <amlcode.h>
#include <namesp.h>
#include <parser.h>
#include <events.h>
#include <interp.h>
#include <debugger.h>

#ifdef ACPI_DEBUG

#define _COMPONENT          DEBUGGER
        MODULE_NAME         ("dbcmds");



/* These object types map directly to the ACPI_TYPES */


ARGUMENT_INFO               DbObjectTypes [] = 
{
    "ANY",
    "NUMBERS",
    "STRINGS",
    "BUFFERS",
    "PACKAGES",
    "FIELDS",
    "DEVICES",
    "EVENTS",
    "METHODS",
    "MUTEXES",
    "REGIONS",
    "POWERRESOURCES",
    "PROCESSORS",
    "THERMALZONES",
    "BUFFERFIELDS",
    "DDBHANDLES",
    NULL            /* Must be null terminated */
};


typedef struct HistoryInfo
{
    char                    Command[80];
    UINT32                  CmdNum;

} HISTORY_INFO;


#define HI_NO_HISTORY       0
#define HI_RECORD_HISTORY   1

#define HISTORY_SIZE        8
HISTORY_INFO                HistoryBuffer[HISTORY_SIZE];
UINT32                      LoHistory = 0;
UINT32                      NumHistory = 0;
UINT32                      NextHistoryIndex = 0;
UINT32                      NextCmdNum = 1;



/******************************************************************************
 * 
 * FUNCTION:    DbAddToHistory
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Add a command line to the history buffer.
 *
 *****************************************************************************/

void
DbAddToHistory (
    char                    *CommandLine)
{


    STRCPY (HistoryBuffer[NextHistoryIndex].Command, CommandLine);
    HistoryBuffer[NextHistoryIndex].CmdNum = NextCmdNum;

    if ((NumHistory == HISTORY_SIZE) &&
        (NextHistoryIndex == LoHistory))
    {
        LoHistory++;
        if (LoHistory >= HISTORY_SIZE)
        {
            LoHistory = 0;
        }
    }

    NextHistoryIndex++;
    if (NextHistoryIndex >= HISTORY_SIZE)
    {
        NextHistoryIndex = 0;
    }


    NextCmdNum++;
    if (NumHistory < HISTORY_SIZE)
    {
        NumHistory++;
    }

}


/******************************************************************************
 * 
 * FUNCTION:    DbDisplayHistory
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display the contents of the history buffer
 *
 *****************************************************************************/

void
DbDisplayHistory (void)
{
    UINT32                  i;
    UINT32                  HistoryIndex;


    HistoryIndex = LoHistory;
    for (i = 0; i < NumHistory; i++)
    {
        OsdPrintf ("%d  %s\n", HistoryBuffer[HistoryIndex].CmdNum, &HistoryBuffer[HistoryIndex].Command);

        HistoryIndex++;
        if (HistoryIndex >= HISTORY_SIZE)
        {
            HistoryIndex = 0;
        }
    }
}


/******************************************************************************
 * 
 * FUNCTION:    DbGetFromHistory
 *
 * PARAMETERS:  CommandNumArg           - String containing the number of the
 *                                        command to be retrieved
 *
 * RETURN:      None
 *
 * DESCRIPTION: Get a command from the history buffer
 *
 *****************************************************************************/

char *
DbGetFromHistory (
    char                    *CommandNumArg)
{
    UINT32                  i;
    UINT32                  HistoryIndex;
    UINT32                  CmdNum;


    if (CommandNumArg == NULL)
    {
        CmdNum = NextCmdNum - 1;
    }

    else
    {
        CmdNum = STRTOUL (CommandNumArg, NULL, 0);
    }

    HistoryIndex = LoHistory;
    for (i = 0; i < NumHistory; i++)
    {
        if (HistoryBuffer[HistoryIndex].CmdNum == CmdNum)
        {
            return (HistoryBuffer[HistoryIndex].Command);
        }


        HistoryIndex++;
        if (HistoryIndex >= HISTORY_SIZE)
        {
            HistoryIndex = 0;
        }
    }

    OsdPrintf ("Invalid history number: %d\n", HistoryIndex);
    return NULL;
}
    

/******************************************************************************
 * 
 * FUNCTION:    DbMatchArgument
 *
 * PARAMETERS:  UserArgument             - User command line
 *
 * RETURN:      Index into command array, -1 if not found
 *
 * DESCRIPTION: Search command array for a command match
 *
 *****************************************************************************/

INT32
DbMatchArgument (
    char                    *UserArgument,
    ARGUMENT_INFO           *Arguments)
{
    UINT32                  i;


    if (!UserArgument || UserArgument[0] == 0)
    {
        return -1;
    }

    for (i = 0; Arguments[i].Name; i++)
    {
        if (STRSTR (Arguments[i].Name, UserArgument) == Arguments[i].Name)
        {
            return i;
        }
    }

    /* Argument not recognized */

    return -1;
}


/******************************************************************************
 * 
 * FUNCTION:    DbSetMethodBreakpoint
 *
 * PARAMETERS:  Location            - AML offset of breakpoint
 *              Op                  - Current Op (from parse walk)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Set a breakpoint in a control method at the specified 
 *              AML offset
 *
 *****************************************************************************/

void
DbSetMethodBreakpoint (
    char                    *Location,
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op)
{
    UINT32                  Address;


    if (!Op)
    {
        OsdPrintf ("There is no method currently executing\n");
        return;
    }

    /* Get and verify the breakpoint address */

    Address = STRTOUL (Location, NULL, 16);
    if (Address <= Op->AmlOffset)
    {
        OsdPrintf ("Breakpoint 0x%X is beyond current address 0x%X\n", Address, Op->AmlOffset);
    }

    /* Just save the breakpoint in a global */

    Gbl_MethodBreakpoint = Address;
    Gbl_BreakpointWalk = WalkState;
    OsdPrintf ("Breakpoint set at AML offset 0x%X\n", Address);
}


/******************************************************************************
 * 
 * FUNCTION:    DbSetMethodCallBreakpoint
 *
 * PARAMETERS:  Location            - AML offset of breakpoint
 *              Op                  - Current Op (from parse walk)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Set a breakpoint in a control method at the specified 
 *              AML offset
 *
 *****************************************************************************/

void
DbSetMethodCallBreakpoint (
    ACPI_GENERIC_OP         *Op)
{


    if (!Op)
    {
        OsdPrintf ("There is no method currently executing\n");
        return;
    }


    Gbl_StepToNextCall = TRUE;
}



/******************************************************************************
 * 
 * FUNCTION:    DbDisassembleAml
 *
 * PARAMETERS:  Statements          - Number of statements to disassemble
 *              Op                  - Current Op (from parse walk)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Lookup a name in the ACPI namespace
 *
 *****************************************************************************/

void
DbDisassembleAml (
    char                    *Statements,
    ACPI_GENERIC_OP         *Op)
{
    UINT32                  NumStatements = 8;


    if (!Op)
    {
        OsdPrintf ("There is no method currently executing\n");
        return;
    }

    if (Statements)
    {
        NumStatements = STRTOUL (Statements, NULL, 0);
    }


    DbDisplayOp (Op, NumStatements);
}


/******************************************************************************
 * 
 * FUNCTION:    DbDumpNamespace 
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump entire namespace or a subtree
 *
 *****************************************************************************/

void
DbDumpNamespace (
    char                    *StartArg)
{
    ACPI_HANDLE             SubtreeEntry;



    /* No argument given, just start at the root and dump entire namespace */

    if (!StartArg)
    {
        SubtreeEntry = Gbl_RootObject;
    }

    /* Check if numeric argument, must be an NTE */

    else if ((StartArg[0] >= 0x30) && (StartArg[0] <= 0x39))
    {

        SubtreeEntry = (ACPI_HANDLE) STRTOUL (StartArg, NULL, 16);
        if (!OsdReadable (SubtreeEntry, sizeof (NAME_TABLE_ENTRY)))
        {
            OsdPrintf ("Address %p is invalid in this address space\n", SubtreeEntry);
            return;
        }
        if (!VALID_DESCRIPTOR_TYPE ((SubtreeEntry), DESC_TYPE_NTE))
        {
            OsdPrintf ("Address %p is not a valid NTE\n", SubtreeEntry);
            return;
        }
    }

    /* Alpha argument */

    else
    {
        /* The parameter is a name string that must be resolved to an NTE */

        SubtreeEntry = DbLocalNsLookup (StartArg);
        if (!SubtreeEntry)
        {
            return;
        }
    }


    DbSetOutputDestination (DB_DUPLICATE_OUTPUT);
    OsdPrintf ("ACPI Namespace (from %p subtree):\n", SubtreeEntry);

    /* Display the subtree */

    DbSetOutputDestination (DB_REDIRECTABLE_OUTPUT);
    NsDumpObjects (ACPI_TYPE_Any, ACPI_UINT32_MAX, SubtreeEntry);
    DbSetOutputDestination (DB_CONSOLE_OUTPUT);
}


/******************************************************************************
 * 
 * FUNCTION:    DbSendNotify 
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Send an ACPI notificationn
 *
 *****************************************************************************/

void
DbSendNotify (
    char                    *Name,
    UINT32                  Value)
{
    NAME_TABLE_ENTRY        *Entry;



    /* Translate name to an NTE */

    Entry = DbLocalNsLookup (Name);
    if (!Entry)
    {
        return;
    }

    /* Decode NTE type */

    switch (Entry->Type)
    {
    case ACPI_TYPE_Device:
    case ACPI_TYPE_Thermal:
            
         /* Send the notify */

        EvNotifyDispatch (Entry, Value);
        break;

    default:
        OsdPrintf ("Named object is not a device or a thermal object\n");
        break;
    }

}


/******************************************************************************
 * 
 * FUNCTION:    DbSetMethodData
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Set control method local or argument
 *
 *****************************************************************************/

void
DbSetMethodData (
    char                    *TypeArg,
    char                    *IndexArg,
    char                    *ValueArg)
{
    char                    Type;
    UINT32                  Index;
    UINT32                  Value;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    Type = TypeArg[0];
    if ((Type != 'L') &&
        (Type != 'A'))
    {
        OsdPrintf ("Invalid SET operand: %s\n", TypeArg);
        return;
    }

    Index = STRTOUL (IndexArg, NULL, 16);
    Value = STRTOUL (ValueArg, NULL, 16);

    WalkState = PsGetCurrentWalkState (Gbl_CurrentWalkList);
    if (!WalkState)
    {
        OsdPrintf ("There is no method currently executing\n");
        return;
    }



    ObjDesc = CmCreateInternalObject (ACPI_TYPE_Number);
    if (!ObjDesc)
    {
        OsdPrintf ("Could not create an internal object\n");
        return;
    }

    ObjDesc->Number.Value = Value;

    switch (Type)
    {
    case 'A':
        
        /* Set a method argument */

        if (Index > MTH_NUM_ARGS)
        {
            OsdPrintf ("Arg%d - Invalid argument name\n", Index);
            return;
        }

        DsMthStackSetValue (MTH_TYPE_ARG, Index, ObjDesc);
        ObjDesc = WalkState->Arguments[Index].Object;
        OsdPrintf ("Arg%d: ", Index);
        DbDisplayInternalObject (ObjDesc);
        break;

    case 'L':

        /* Set a method local */

        if (Index > MTH_NUM_LOCALS)
        {
            OsdPrintf ("Local%d - Invalid local variable name\n", Index);
            return;
        }

        DsMthStackSetValue (MTH_TYPE_LOCAL, Index, ObjDesc);
        ObjDesc = WalkState->LocalVariables[Index].Object;
        OsdPrintf ("Local%d: ", Index);
        DbDisplayInternalObject (ObjDesc);
        break;

    default:
        break;
    }
}



/******************************************************************************
 * 
 * FUNCTION:    DbWalkMethods
 *
 * PARAMETERS:  Callback from WalkNamespace
 *
 * RETURN:      None
 *
 * DESCRIPTION: Called for a single method found in the namespace
 *
 *****************************************************************************/

ACPI_STATUS
DbWalkForSpecificObjects (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_STATUS             Status;
    UINT32                  BufSize;
    char                    buffer[64];


    ObjDesc = ((NAME_TABLE_ENTRY *)ObjHandle)->Object;

    /* Get the full pathname to this method */

    Status = NsHandleToPathname (ObjHandle, &BufSize, buffer);

    if (ACPI_FAILURE (Status))
    {
        OsdPrintf ("Could Not get pathname for object %p\n", ObjHandle);
        return AE_OK;
    }

    OsdPrintf ("%32s", buffer);

    if (ObjDesc)
    {
        switch (ObjDesc->Common.Type)
        {
        case ACPI_TYPE_Method:
            OsdPrintf ("  #Args %d  Concurrency %d", ObjDesc->Method.ParamCount, ObjDesc->Method.Concurrency);
            break;

        case ACPI_TYPE_Number:
            OsdPrintf ("  Value 0x%X", ObjDesc->Number.Value);
            break;
    
        case ACPI_TYPE_String:
            OsdPrintf ("  \"%s\"", ObjDesc->String.Pointer);
            break;

        case ACPI_TYPE_Region:
            OsdPrintf ("  SpaceId %d Address %X Length %X", ObjDesc->Region.SpaceId, ObjDesc->Region.Address, ObjDesc->Region.Length);
            break;

        case ACPI_TYPE_Package:
            OsdPrintf ("  #Elements %d", ObjDesc->Package.Count);
            break;

        case ACPI_TYPE_Buffer:
            OsdPrintf ("  Length %d", ObjDesc->Buffer.Length);
            break;
        }
    }

    OsdPrintf ("\n");
    return AE_OK;
}


/******************************************************************************
 * 
 * FUNCTION:    DbDisplayAllMethods
 *
 * PARAMETERS:  Root            - Root of the parse tree
 *
 * RETURN:      None
 *
 * DESCRIPTION: Need to wait until second pass to parse the control methods
 *
 *****************************************************************************/

ACPI_STATUS
DbDisplayObjects (
    char                    *ObjTypeArg,
    char                    *DisplayCountArg)
{
    UINT32                  DisplayCount;
    UINT32                  Type;

    
    Type = DbMatchArgument (ObjTypeArg, DbObjectTypes);
    if (Type == (UINT32) -1)
    {
        OsdPrintf ("Invalid or unsupported argument\n");
        return AE_OK;
    }


    if (DisplayCountArg)
    {
        DisplayCount = STRTOUL (DisplayCountArg, NULL, 0);
    }
    
    else
    {
        DisplayCount = ACPI_UINT32_MAX;
    }

    DbSetOutputDestination (DB_DUPLICATE_OUTPUT);
    OsdPrintf ("Objects of type [%s] defined in the current ACPI Namespace: \n", CmGetTypeName (Type));

    DbSetOutputDestination (DB_REDIRECTABLE_OUTPUT);

    AcpiWalkNamespace (Type, ACPI_ROOT_OBJECT, ACPI_UINT32_MAX,
                        DbWalkForSpecificObjects, (void *) Type, NULL);

    DbSetOutputDestination (DB_CONSOLE_OUTPUT);
    return AE_OK;
}



/******************************************************************************
 * 
 * FUNCTION:    DbWalkAndMatchName
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: 
 *
 *****************************************************************************/

ACPI_STATUS
DbWalkAndMatchName (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_STATUS             Status;
    char                    *RequestedName = (char *) Context;
    UINT32                  i;
    UINT32                  BufSize;
    char                    Buffer[96];


    ObjDesc = ((NAME_TABLE_ENTRY *)ObjHandle)->Object;


    /* Check for a name match */

    for (i = 0; i < 4; i++)
    {
        /* Wildcard support */

        if ((RequestedName[i] != '?') &&
            (RequestedName[i] != ((char *)(&((NAME_TABLE_ENTRY *)ObjHandle)->Name))[i]))
        {
            /* No match, just exit */

            return AE_OK;
        }
    }


    /* Get the full pathname to this object */

    BufSize = sizeof (Buffer);

    Status = NsHandleToPathname (ObjHandle, &BufSize, Buffer);
    if (ACPI_FAILURE (Status))
    {
        OsdPrintf ("Could Not get pathname for object %p\n", ObjHandle);
    }

    else
    {
        OsdPrintf ("%32s (0x%p) - %s\n", Buffer, ObjHandle, CmGetTypeName (((NAME_TABLE_ENTRY *)ObjHandle)->Type));
    }

    return AE_OK;
}


/******************************************************************************
 * 
 * FUNCTION:    DbWalkAndMatchName
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: 
 *
 *****************************************************************************/

ACPI_STATUS
DbFindNameInNamespace (
    char                    *NameArg)
{
    
    if (STRLEN (NameArg) > 4)
    {
        OsdPrintf ("Name must be no longer than 4 characters\n");
        return (AE_OK);
    }

    AcpiWalkNamespace (ACPI_TYPE_Any, ACPI_ROOT_OBJECT, ACPI_UINT32_MAX,
        DbWalkAndMatchName, NameArg, NULL);

    DbSetOutputDestination (DB_CONSOLE_OUTPUT);
    return AE_OK;
}


/******************************************************************************
 * 
 * FUNCTION:    DbExecute
 *
 * PARAMETERS:  Name                - Name of method to execute
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a control method.  Name is relative to the current
 *              scope.
 *
 *****************************************************************************/

void
DbExecute (
    char                    *Name,
    char                    **Args,
    UINT32                  Flags)
{
    ACPI_STATUS             Status;
    ACPI_BUFFER             ReturnObj;
    ACPI_OBJECT_LIST        ParamObjects;
    ACPI_OBJECT             Params[MTH_NUM_ARGS];
    UINT32                  PreviousAllocations;
    UINT32                  PreviousSize;
    UINT32                  Allocations;
    UINT32                  Size;
    UINT32                  i;
    char                    LocalBuf[64];


    if (OutputToFile && !DebugLevel)
    {
        OsdPrintf ("Warning: debug output is not enabled!\n");
    }

    /* Memory allocation tracking */

    PreviousAllocations = Gbl_CurrentAllocCount;
    PreviousSize = Gbl_CurrentAllocSize;

    if (Args[0])
    {
        for (i = 0; Args[i] && i < MTH_NUM_ARGS; i++)
        {
            Params[i].Type              = ACPI_TYPE_Number;
            Params[i].Number.Value      = STRTOUL (Args[i], NULL, 16);
        }

        ParamObjects.Pointer        = Params;
        ParamObjects.Count          = i;
    }

    else
    {
        /* Setup default parameters */

        Params[0].Type              = ACPI_TYPE_Number;
        Params[0].Number.Value      = 0x01020304;

        Params[1].Type              = ACPI_TYPE_String;
        Params[1].String.Length     = 12;
        Params[1].String.Pointer    = "AML Debugger";

        ParamObjects.Pointer        = Params;
        ParamObjects.Count          = 2;
    }

    /* Prepare for a return object of arbitrary size */

    ReturnObj.Pointer           = Buffer;
    ReturnObj.Length            = BUFFER_SIZE;

    /* Catenate the current scope to the supplied name */

    LocalBuf[0] = 0;
    if ((Name[0] != '\\') &&
        (Name[0] != '/'))
    {
        STRCAT (LocalBuf, ScopeBuf);
    }
    STRCAT (LocalBuf, Name);
    DbPrepNamestring (LocalBuf);

    DbSetOutputDestination (DB_DUPLICATE_OUTPUT);
    OsdPrintf ("Executing %s\n", LocalBuf);

    if (Flags & EX_SINGLE_STEP)
    {
        Gbl_CmSingleStep = TRUE;
        DbSetOutputDestination (DB_CONSOLE_OUTPUT);
    }

    else
    {
        /* No single step, allow redirection to a file */

        DbSetOutputDestination (DB_REDIRECTABLE_OUTPUT);
    }


    /* Do the actual method execution */

    Status = AcpiEvaluateObject (NULL, LocalBuf, &ParamObjects, &ReturnObj);

    Gbl_CmSingleStep = FALSE;
    Gbl_MethodExecuting = FALSE;

    /* Memory allocation tracking */

    Allocations = Gbl_CurrentAllocCount - PreviousAllocations;
    Size = Gbl_CurrentAllocSize - PreviousSize;

    DbSetOutputDestination (DB_DUPLICATE_OUTPUT);

    if (Allocations > 0)
    {
        OsdPrintf ("Outstanding: %ld allocations of total size %ld after execution\n",
                        Allocations, Size);
    }


    if (ACPI_FAILURE (Status))
    {
        OsdPrintf ("Execution of %s failed with status %s\n", LocalBuf, CmFormatException (Status));
    }

    else
    {
        /* Display a return object, if any */

        if (ReturnObj.Length)
        {
            OsdPrintf ("Execution of %s returned object %p\n", LocalBuf, ReturnObj.Pointer);
            DbDumpObject (ReturnObj.Pointer, 1);
        }
    }

    DbSetOutputDestination (DB_CONSOLE_OUTPUT);
}


/******************************************************************************
 * 
 * FUNCTION:    DbSetScope
 *
 * PARAMETERS:  Name                - New scope path
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Set the "current scope" as maintained by this utility.  
 *              The scope is used as a prefix to ACPI paths.
 *
 *****************************************************************************/

void
DbSetScope (
    char                    *Name)
{

    if (!Name || Name[0] == 0)
    {
        OsdPrintf ("Current scope: %s\n", ScopeBuf);
        return;
    }

    DbPrepNamestring (Name);

    /* TBD: Validate scope here */

    if (Name[0] == '\\')
    {
        STRCPY (ScopeBuf, Name);
        STRCAT (ScopeBuf, "\\");
    }

    else
    {
        STRCAT (ScopeBuf, Name);
        STRCAT (ScopeBuf, "\\");
    }
  
    OsdPrintf ("New scope: %s\n", ScopeBuf);
}

#endif
