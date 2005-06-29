
/******************************************************************************
 * 
 * Module Name: dsmethod - Parser/Interpreter interface - control method parsing
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

#define __DSMETHOD_C__

#include <acpi.h>
#include <parser.h>
#include <amlcode.h>
#include <dispatch.h>
#include <interp.h>
#include <namesp.h>
#include <tables.h>
#include <debugger.h>


#define _COMPONENT          DISPATCHER
        MODULE_NAME         ("dsmeth0d");



/*******************************************************************************
 *
 * FUNCTION:    DsParseMethod
 *
 * PARAMETERS:  ObjHandle       - NTE of the method
 *              Level           - Current nesting level
 *              Context         - Points to a method counter
 *              ReturnValue     - Not used
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Call the parser and parse the AML that is
 *              associated with the method.
 *
 ******************************************************************************/

ACPI_STATUS
DsParseMethod (
    ACPI_HANDLE             ObjHandle)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_GENERIC_OP         *Op;
    NAME_TABLE_ENTRY        *Entry;
    ACPI_OWNER_ID           OwnerId;


    FUNCTION_TRACE_PTR ("DsParseMethod", ObjHandle);


    /* Parameter Validation */

    if (!ObjHandle)
    {
        return_ACPI_STATUS (AE_NULL_ENTRY);
    }

    DEBUG_PRINT (ACPI_INFO, ("DsParseMethod: **** Parsing [%4.4s] **** Nte=%p\n", 
                    &((NAME_TABLE_ENTRY *)ObjHandle)->Name, ObjHandle));


    /* Extract the method object from the method NTE */

    Entry = (NAME_TABLE_ENTRY *) ObjHandle;
    ObjDesc = Entry->Object;
    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_NULL_OBJECT);
    }

     /* Create a mutex for the method if there is a concurrency limit */

    if ((ObjDesc->Method.Concurrency != INFINITE_CONCURRENCY) &&
        (!ObjDesc->Method.Semaphore))
    {
        Status = OsdCreateSemaphore (ObjDesc->Method.Concurrency, &ObjDesc->Method.Semaphore);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    /* Allocate a new parser op to be the root of the parsed method tree */

    Op = PsAllocOp (AML_MethodOp);
    if (!Op)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Init new op with the method name and pointer back to the NTE */

    PsSetName (Op, Entry->Name);
    Op->NameTableEntry = Entry;


    /* Parse the method, creating a parse tree */

    Status = PsParseAml (Op, ObjDesc->Method.Pcode, ObjDesc->Method.PcodeLength);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    /* Get a new OwnerId for objects created by this method */

    OwnerId = CmAllocateOwnerId (OWNER_TYPE_METHOD);

	/*
	 * Make a first pass walk to add newly declared items to the namespace.
	 * (The first pass only adds the names, it does not evaluate them)
	 * The second pass occurs during the actual execution of the method
	 * so that operands are evaluated dynamically.
	 */

    PsWalkParsedAml (Op->Value.Arg, Op, ObjDesc, Entry->Scope, NULL, NULL,
                        OwnerId, DsLoad1BeginOp, DsLoad1EndOp);

    /* Install the parsed tree in the method object */

    ObjDesc->Method.ParserOp = Op;
    ObjDesc->Method.OwningId = OwnerId;

    DEBUG_EXEC (DbGenerateStatistics (Op, 1));

    DEBUG_PRINT (ACPI_INFO, ("DsParseMethod: **** [%4.4s] Parsed **** Nte=%p Op=%p\n", 
                    &((NAME_TABLE_ENTRY *)ObjHandle)->Name, ObjHandle, Op));

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    DsCallControlMethod
 *
 * PARAMETERS:  WalkState           - Current state of the walk
 *              Op                  - Current Op to be walked
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Transfer execution to a called control method
 *
 ******************************************************************************/

ACPI_STATUS
DsCallControlMethod (
    ACPI_WALK_LIST          *WalkList,
    ACPI_WALK_STATE         *ThisWalkState,
    ACPI_GENERIC_OP         *Op)
{
    ACPI_STATUS             Status;
    ACPI_DEFERRED_OP        *Method;
    NAME_TABLE_ENTRY        *MethodNte;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_WALK_STATE         *NextWalkState;
    UINT32                  NumArgs;
    UINT32                  i;


    FUNCTION_TRACE_PTR ("DsCallControlMethod", ThisWalkState);

    DEBUG_PRINT (TRACE_DISPATCH, ("DsCall, execute method %p, currentstate=%p\n", 
                        ThisWalkState->PrevOp, ThisWalkState));
    BREAKPOINT3;


    /* TBD: Move this code to the ParseAml procedure? */

    /*
     * PrevOp points to the METHOD_CALL Op.
     * Get the NTE entry (in the METHOD_CALL->NAME Op) and the corresponding METHOD Op
     */

    MethodNte   = (ThisWalkState->PrevOp->Value.Arg)->NameTableEntry;
    ObjDesc     = NsGetAttachedObject (MethodNte);
    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_NULL_OBJECT);
    }

    /*
     * If the method isn't parsed yet (no parse tree), we must parse it.
     */
    if (!ObjDesc->Method.ParserOp)
    {
        DEBUG_PRINT (TRACE_DISPATCH, ("DsCall, parsing control method\n"));

        Status = DsParseMethod (MethodNte);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    /* Get the parse tree and parameter count */

    Method      = ObjDesc->Method.ParserOp;
    NumArgs     = ObjDesc->Method.ParamCount;

    /* Save the (current) Op for when this walk is restarted */

    ThisWalkState->MethodCallOp = ThisWalkState->PrevOp;
    ThisWalkState->PrevOp       = Op;

    /* Create a new state for the preempting walk */

    NextWalkState = DsCreateWalkState ((ACPI_GENERIC_OP *) Method, ObjDesc, WalkList);
    if (!NextWalkState)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }


    /* Open a new scope */

    Status = DsScopeStackPush (MethodNte->Scope, ACPI_TYPE_Method, NextWalkState);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    /* TBD: Do the operands always start at index 0? */

    /* 
     * Initialize the arguments for the method.  The resolved arguments were put 
     * on the previous walk state's operand stack
     */

    Status = DsMethodDataInitArgs (&ThisWalkState->Operands[0], ThisWalkState->NumOperands);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Delete the operands on the previous walkstate operand stack (they were copied to new objects) */

    for (i = 0; i < NumArgs; i++)
    {
        CmRemoveReference (ThisWalkState->Operands [i]);
    }

    /* Clear the operand stack */

    ThisWalkState->NumOperands = 0;

    /* The next op will be the beginning of the method */

    NextWalkState->NextOp = (ACPI_GENERIC_OP *) Method;

    /* 
     * If there is a concurrency limit on this method, we need to obtain a unit
     * from the method semaphore.  This releases the interpreter if we block
     */

    if (ObjDesc->Method.Semaphore)
    {
        Status = OsLocalWaitSemaphore (ObjDesc->Method.Semaphore, WAIT_FOREVER);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

 
    DEBUG_PRINT (TRACE_DISPATCH, ("DsCall, starting nested execution, newstate=%p\n", NextWalkState));
    BREAKPOINT3;

    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    DsRestartControlMethod
 *
 * PARAMETERS:  WalkState           - State of the method when it was preempted
 *              Op                  - Pointer to new current op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Restart a method that was preempted
 *
 ******************************************************************************/

ACPI_STATUS
DsRestartControlMethod (
    ACPI_WALK_STATE         *WalkState,
    ACPI_OBJECT_INTERNAL    *ReturnDesc)
{
    ACPI_STATUS             Status;


    FUNCTION_TRACE_PTR ("DsRestartControlMethod", WalkState);


    if (ReturnDesc)
    {
        /* Get the return value (if any) from the previous method.  NULL if no return value */

        Status = DsResultStackPush (ReturnDesc, WalkState);
        if (ACPI_FAILURE (Status))
        {
            CmRemoveReference (ReturnDesc);
            return_ACPI_STATUS (Status);
        }

        /* Delete the return value if it will not be used by the calling method */

        DsDeleteResultIfNotUsed (WalkState->MethodCallOp, ReturnDesc, WalkState);
    }

    DEBUG_PRINT (TRACE_DISPATCH, ("DsRestart: Method=%p Return=%p State=%p\n", 
                        WalkState->MethodCallOp, ReturnDesc, WalkState));


    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    DsTerminateControlMethod
 *
 * PARAMETERS:  WalkState           - State of the method
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Terminate a control method.  Delete everything that the method
 *              created, delete all locals and arguments, and delete the parse
 *              tree if requested.
 *
 ******************************************************************************/

ACPI_STATUS
DsTerminateControlMethod (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_GENERIC_OP         *Op;
    NAME_TABLE_ENTRY        *MethodEntry;


    FUNCTION_TRACE_PTR ("DsTerminateControlMethod", WalkState);


    /* The method object should be stored in the walk state */

    ObjDesc = WalkState->MethodDesc;
    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_OK);
    }

    /* The root of the method parse tree should be stored in the method object */

    Op = ObjDesc->Method.ParserOp;
    if (!Op)
    {
        return_ACPI_STATUS (AE_OK);
    }

    /* The method NTE is stored in the method Op */

    MethodEntry = Op->NameTableEntry;


    /*
     * Delete any namespace entries created immediately underneath the method
     */
    CmReleaseMutex (MTX_NAMESPACE);
    if (MethodEntry->Scope)
    {
        NsDeleteNamespaceSubtree (MethodEntry);
    }

    /* 
     * Delete any namespace entries created anywhere else within the namespace 
     */

    NsDeleteNamespaceByOwner (WalkState->MethodDesc->Method.OwningId);
    CmAcquireMutex (MTX_NAMESPACE);


    /* Signal completion of the execution of this method if necessary */

    if (WalkState->MethodDesc->Method.Semaphore)
    {
        Status = OsdSignalSemaphore (WalkState->MethodDesc->Method.Semaphore, 1);
    }

    /* Delete all arguments and locals */

    DsMethodDataDeleteAll (WalkState);
    
    /* 
     * Delete the method's parse tree if asked to 
     */
    if (Gbl_WhenToParseMethods & METHOD_DELETE_AT_COMPLETION)
    {
        PsDeleteParseTree (WalkState->MethodDesc->Method.ParserOp);
        WalkState->MethodDesc->Method.ParserOp = NULL;
    }


    return_ACPI_STATUS (AE_OK);
}





