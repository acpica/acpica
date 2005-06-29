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
#include <amlcode.h>
#include <namesp.h>
#include <parser.h>
#include <events.h>
#include <interp.h>
#include <debugger.h>


#ifdef ACPI_DEBUG

#define _COMPONENT          DEBUGGER
        MODULE_NAME         ("dbcmds");


extern int					opt_verbose;



/******************************************************************************
 * 
 * FUNCTION:    DbLocalNsLookup
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Lookup a name in the ACPI namespace
 *
 *****************************************************************************/

NAME_TABLE_ENTRY *
DbLocalNsLookup (
    char                    *Name)
{
    char                    *InternalPath;
    ACPI_STATUS             Status;
    NAME_TABLE_ENTRY        *Entry = NULL;


    /* Build an internal namestring */

    Status = NsInternalizeName (Name, &InternalPath);
    if (ACPI_FAILURE (Status))
    {
        OsdPrintf ("Invalid namestring: %s\n", Name);
        return NULL;
    }

    /* Lookup the name */

    Status = NsLookup (Gbl_CurrentScope->Scope, InternalPath, ACPI_TYPE_Any, IMODE_Execute, 
                                    NS_NO_UPSEARCH, &Entry);

    if (ACPI_FAILURE (Status))
    {
        OsdPrintf ("Could not locate name: %s %s\n", Name, Gbl_ExceptionNames[Status]);
    }


    CmFree (InternalPath);

    return Entry;
}


/******************************************************************************
 * 
 * FUNCTION:    DbDumpNamespace 
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Interface to NsDumpObjects
 *
 *****************************************************************************/

void
DbDumpNamespace (void)
{

    NsDumpObjects (ACPI_TYPE_Any, ACPI_UINT32_MAX, Gbl_RootObject);

}


/******************************************************************************
 * 
 * FUNCTION:    DbDecodeAndDisplayObject
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display a formatted ACPI object
 *
 *****************************************************************************/

void
DbDecodeAndDisplayObject (
    char                    *Param)
{
    UINT32                  Value;
    NAME_TABLE_ENTRY        *Entry;
    
    
    if (!Param)
    {
        return;
    }

    /* Differentiate between a number and a name */

    if ((Param[0] >= 0x30) && (Param[0] <= 0x39))
    {
        Value = STRTOUL (Param, NULL, 0);

        if (VALID_DESCRIPTOR_TYPE (((void *) Value), DESC_TYPE_NTE))
        {
            /* This is an NTE */

            CmDumpBuffer ((void *) Value, sizeof (NAME_TABLE_ENTRY), ACPI_UINT32_MAX);
            AmlDumpNameTableEntry ((void *) Value, 1);
        }

        else if (VALID_DESCRIPTOR_TYPE (((void *) Value), DESC_TYPE_ACPI_OBJ))
        {
            /* This is an ACPI OBJECT */

            CmDumpBuffer ((void *) Value, sizeof (ACPI_OBJECT_INTERNAL), ACPI_UINT32_MAX);
            AmlDumpObjectDescriptor ((void *) Value, 1);
        }

        else
        {
            /* Just dump some memory */

            CmDumpBuffer ((void *) Value, 64, ACPI_UINT32_MAX);
        }

        return;
    }
                    

    /* The parameter is a name string that must be resolved to an NTE */

    Entry = DbLocalNsLookup (Param);
    if (!Entry)
    {
        return;
    }

    /* Now dump the NTE */

    CmDumpBuffer ((void *) Entry, sizeof (NAME_TABLE_ENTRY), ACPI_UINT32_MAX);
    AmlDumpNameTableEntry (Entry, 1);


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
    char                    Type,
    UINT32                  Index,
    UINT32                  Value)
{
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


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

        PsxMthStackSetValue (MTH_TYPE_ARG, Index, ObjDesc);
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

        PsxMthStackSetValue (MTH_TYPE_LOCAL, Index, ObjDesc);
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
 * FUNCTION:    DbDisplayInternalObject
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Short display of an internal object
 *
 *****************************************************************************/

void 
DbDisplayInternalObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{
    UINT8                   Type;


    OsdPrintf ("Obj %p ", ObjDesc);

    if (!ObjDesc)
    {
        OsdPrintf ("<NullObj>\n");
        return;
    }

    else if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))
    {
        OsdPrintf ("<NameTableEntry> ");
    }

    else if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_ACPI_OBJ))
    {
        OsdPrintf ("<AcpiObj> ");
        Type = ObjDesc->Common.Type;
        if (Type > INTERNAL_TYPE_MAX)
        {
            OsdPrintf (" Type %x [Invalid Type]", Type);
            return;
        }

        OsdPrintf (" %12.12s ", Gbl_NsTypeNames[Type]);

        switch (ObjDesc->Common.Type)
        {
        case ACPI_TYPE_Number:
            OsdPrintf ("0x%X (%d)", ObjDesc->Number.Value, ObjDesc->Number.Value);
            break;

        case ACPI_TYPE_String:
            OsdPrintf ("\"%16s\"", ObjDesc->String.Pointer);
            break;

        }
    }

    else
    {
        OsdPrintf ("<Not a valid ACPI Object Descriptor> ");
    }

    OsdPrintf ("\n");
}



/******************************************************************************
 * 
 * FUNCTION:    DbDisplayLocals
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display all locals for a control method
 *
 *****************************************************************************/

void
DbDisplayLocals (void)
{
    UINT32                  i;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    NAME_TABLE_ENTRY        *Entry;



    WalkState = PsGetCurrentWalkState (Gbl_CurrentWalkList);
    if (!WalkState)
    {
        OsdPrintf ("There is no method currently executing\n");
        return;
    }

    ObjDesc = WalkState->MethodDesc;
    Entry = WalkState->Origin->ResultObj;


    OsdPrintf ("Local Variables for method [%4.4s]:\n", &Entry->Name);

    for (i = 0; i < MTH_NUM_LOCALS; i++)
    {
        ObjDesc = WalkState->LocalVariables[i].Object;
        OsdPrintf ("Local%d: ", i);
        DbDisplayInternalObject (ObjDesc);
    }
}



/******************************************************************************
 * 
 * FUNCTION:    DbDisplayArguments
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display all arguments for a control method
 *
 *****************************************************************************/

void
DbDisplayArguments (void)
{  
    UINT32                  i;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    UINT32                  NumArgs;
    UINT32                  Concurrency;
    NAME_TABLE_ENTRY        *Entry;


    WalkState = PsGetCurrentWalkState (Gbl_CurrentWalkList);
    if (!WalkState)
    {
        OsdPrintf ("There is no method currently executing\n");
        return;
    }

    ObjDesc = WalkState->MethodDesc;
    Entry = WalkState->Origin->ResultObj;

    NumArgs = ObjDesc->Method.ParamCount;
    Concurrency = ObjDesc->Method.Concurrency;

    OsdPrintf ("Method [%4.4s] has %d arguments, max concurrency = %d\n", &Entry->Name, NumArgs, Concurrency);

    for (i = 0; i < NumArgs; i++)
    {
        ObjDesc = WalkState->Arguments[i].Object;
        OsdPrintf ("Arg%d: ", i);
        DbDisplayInternalObject (ObjDesc);
    }
}



/******************************************************************************
 * 
 * FUNCTION:    DbDisplayResults 
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display current contents of a method result stack
 *
 *****************************************************************************/

void
DbDisplayResults (void)
{
    UINT32                  i;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    UINT32                  NumResults;
    NAME_TABLE_ENTRY        *Entry;


    WalkState = PsGetCurrentWalkState (Gbl_CurrentWalkList);
    if (!WalkState)
    {
        OsdPrintf ("There is no method currently executing\n");
        return;
    }

    ObjDesc = WalkState->MethodDesc;
    Entry = WalkState->Origin->ResultObj;
    NumResults = WalkState->NumResults - WalkState->CurrentResult;

    OsdPrintf ("Method [%4.4s] has %d stacked result objects\n", &Entry->Name, NumResults);

    for (i = WalkState->CurrentResult; i < WalkState->NumResults; i++)
    {
        ObjDesc = WalkState->Results[i];
        OsdPrintf ("Result%d: ", i);
        DbDisplayInternalObject (ObjDesc);
    }
}



/******************************************************************************
 * 
 * FUNCTION:    DbDisplayCallingTree
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display current calling tree of nested control methods
 *
 *****************************************************************************/

void
DbDisplayCallingTree (void)
{
    UINT32                  i;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    NAME_TABLE_ENTRY        *Entry;


    WalkState = PsGetCurrentWalkState (Gbl_CurrentWalkList);
    if (!WalkState)
    {
        OsdPrintf ("There is no method currently executing\n");
        return;
    }

    ObjDesc = WalkState->MethodDesc;
    Entry = WalkState->Origin->ResultObj;

    OsdPrintf ("Current Control Method Call Tree\n");

    for (i = 0; WalkState; i++)
    {
        ObjDesc = WalkState->MethodDesc;
        Entry = WalkState->Origin->ResultObj;

        OsdPrintf ("    [%4.4s]\n", &Entry->Name);

        WalkState = WalkState->Next;
    }
}



/******************************************************************************
 * 
 * FUNCTION:    DbDisplayResultObject
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display the result of an AML opcode
 *
 *****************************************************************************/

void
DbDisplayResultObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{

    /* TBD:
     * We don't always want to display the result.
     * For now, only display if single stepping
     * however, this output is very useful in other contexts also
     */

    if (!Gbl_CmSingleStep)
    {
        return;
    }

    OsdPrintf ("Result: ");
    DbDisplayInternalObject (ObjDesc);
    OsdPrintf ("\n");
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
DbWalkMethods (
    ACPI_HANDLE                 ObjHandle,
    UINT32                      NestingLevel,
    void                        *Context,
    void                        **ReturnValue)
{
    UINT32                      NumArgs;
    ACPI_OBJECT_INTERNAL        *ObjDesc;
    UINT32                      BufSize;
    char                        buffer[64];


    ObjDesc = ((NAME_TABLE_ENTRY *)ObjHandle)->Object;
    NumArgs = ObjDesc->Method.ParamCount;

    NsHandleToPathname (ObjHandle, &BufSize, buffer);

    /* Skip past the junk at the start of the path */

    OsdPrintf ("%32s", &buffer[6]);
    OsdPrintf ("  #args = %d\n", NumArgs);

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
DbDisplayAllMethods (
    UINT32                      DisplayCount)
{

    if (DisplayCount == 0)
        DisplayCount = ACPI_UINT32_MAX;

    OsdPrintf ("Control Methods defined in this namespace: \n");

    AcpiWalkNamespace (ACPI_TYPE_Method, ACPI_ROOT_OBJECT, ACPI_UINT32_MAX,
        DbWalkMethods, NULL, NULL);

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
    UINT32                  Flags)
{
    ACPI_STATUS             Status;
    ACPI_BUFFER             ReturnObj;
    ACPI_OBJECT_LIST        ParamObjects;
    UINT32                  PreviousAllocations;
    UINT32                  PreviousSize;
    UINT32                  Allocations;
    UINT32                  Size;
    char                    LocalBuf[64];


//    ACPI_OBJECT             Obj [4];

    if (Flags & EX_SINGLE_STEP)
    {
        Gbl_CmSingleStep = TRUE;
    }

    /* Memory allocation tracking */

    PreviousAllocations = Gbl_CurrentAllocCount;
    PreviousSize = Gbl_CurrentAllocSize;

    ParamObjects.Count = 0;

    /* Prepare for a return object of arbitrary size */

    ReturnObj.Pointer = Buffer;
    ReturnObj.Length = BUFFER_SIZE;

    /* Catenate the current scope to the supplied name */

    STRCPY (LocalBuf, ScopeBuf);
    STRCAT (LocalBuf, Name);

    OsdPrintf ("Executing %s\n", LocalBuf);
    if (OutputToFile)
    {
        OsdPrintf ("\nExecuting %s\n\n", LocalBuf);
    }

    /* Do the actual execution */

    Status = AcpiEvaluateObject (NULL, LocalBuf, NULL, &ReturnObj);

    Gbl_CmSingleStep = FALSE;

    /* Memory allocatoin tracking */

    Allocations = Gbl_CurrentAllocCount - PreviousAllocations;
    Size = Gbl_CurrentAllocSize - PreviousSize;

    if (Allocations > 0)
    {
        OsdPrintf ("Outstanding: %ld allocations of total size %ld after execution\n",
            Allocations, Size);
    }


    if (ACPI_FAILURE (Status))
    {
        OsdPrintf ("Execution of %s failed with status %s\n", LocalBuf, Gbl_ExceptionNames[Status]);
        OsdPrintf ("Execution of %s failed with status %s\n", LocalBuf, Gbl_ExceptionNames[Status]);
        return;
    }

    /* Display a return object, if any */

    DbDumpObject (LocalBuf, &ReturnObj);
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

    if (Name[0] == 0)
    {
        OsdPrintf ("Current scope: %s\n", ScopeBuf);
        return;
    }

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

#endif  /* ACPI_DEBUG */

