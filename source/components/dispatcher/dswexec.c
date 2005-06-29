
/******************************************************************************
 * 
 * Module Name: psxexec - Parser/Interpreter interface, method execution 
 *                        callbacks;  Dispatch to interpreter.
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

#define __PSXEXEC_C__

#include <acpi.h>
#include <amlcode.h>
#include <parser.h>
#include <interp.h>
#include <namesp.h>
#include <debugger.h>


#define _COMPONENT          PARSER
        MODULE_NAME         ("psxexec");




/*****************************************************************************
 *
 * FUNCTION:    PsxExecBeginOp
 *
 * PARAMETERS:  WalkState       - Current state of the parse tree walk
 *              Op              - Op that has been just been reached in the
 *                                walk;  Arguments have not been evaluated yet.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Descending callback used during the execution of control
 *              methods.  This is where most operators and operands are 
 *              dispatched to the interpreter.
 *
 ****************************************************************************/

ACPI_STATUS
PsxExecBeginOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op)
{
    ACPI_OP_INFO            *OpInfo;
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE_PTR ("PsxExecBeginOp", Op);


    if (Op == WalkState->Origin)
    {
        return_ACPI_STATUS (AE_OK);
    }
    
    /*
     * If the previous opcode was a conditional, this opcode
     * must be the beginning of the associated predicate.
     * Save this knowledge in the current scope descriptor
     */

    if ((WalkState->ControlState) &&
        (WalkState->ControlState->Exec == CONTROL_CONDITIONAL_EXECUTING))
    {
        DEBUG_PRINT (TRACE_EXEC, ("BeginOp: Exec predicate Op=%X State=%X\n",
                        Op, WalkState));

        WalkState->ControlState->Exec           = CONTROL_PREDICATE_EXECUTING;
        WalkState->ControlState->PredicateOp    = Op;         /* Save start of predicate */
    }

/*
    if (Op->Opcode != AML_MethodOp)
    {
        return_ACPI_STATUS (AE_OK);
    }
    
*/

    OpInfo = PsGetOpcodeInfo (Op->Opcode);

    switch (OpInfo->Flags & OP_INFO_TYPE)
    {
    case OPTYPE_CONTROL:

        Status = PsxExecBeginControlOp (WalkState, Op);
        break;

    case OPTYPE_NAMED_OBJECT:

        if (WalkState->Origin->Opcode == AML_MethodOp)
        {
            /*
             * Found a named object declaration during method execution;  we must enter
             * this object into the namespace.
             *
             * TBD: make this a temporary namespace object
             */

            Status = PsxLoad2BeginOp (WalkState, Op);
        }
        break;

    default:
        break;
    }

    /* Nothing to do here during method execution */

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    PsxExecEndOp
 *
 * PARAMETERS:  WalkState       - Current state of the parse tree walk
 *              Op              - Op that has been just been completed in the
 *                                walk;  Arguments have now been evaluated.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Ascending callback used during the execution of control
 *              methods.  The only thing we really need to do here is to 
 *              notice the beginning of IF, ELSE, and WHILE blocks.
 *
 ****************************************************************************/

ACPI_STATUS
PsxExecEndOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op)
{
    ACPI_STATUS             Status = AE_OK;
    UINT16                  Opcode;
    UINT8                   Optype;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_GENERIC_OP         *NextOp;
    NAME_TABLE_ENTRY        *Entry;
    ACPI_GENERIC_OP         *FirstArg;
    ACPI_OBJECT_INTERNAL    *ResultObj = NULL;
    ACPI_OP_INFO            *OpInfo;
    UINT32                  OperandIndex;


    FUNCTION_TRACE_PTR ("PsxExecEndOp", Op);


    Opcode = (UINT16) Op->Opcode;


    OpInfo = PsGetOpcodeInfo (Op->Opcode);
    if (!OpInfo)
    {
        DEBUG_PRINT (ACPI_ERROR, ("ExecEndOp: Unknown opcode. Op=%X\n",
                        Op));

        return_ACPI_STATUS (AE_NOT_IMPLEMENTED);
    }

    Optype = (UINT8) (OpInfo->Flags & OP_INFO_TYPE);
    FirstArg = Op->Value.Arg;

    /* Init the walk state */

    WalkState->NumOperands = 0;
    WalkState->ReturnDesc = NULL;


    /* Call debugger for single step support (DEBUG build only) */

    DEBUG_EXEC (Status = DbSingleStep (WalkState, Op, Optype));
    DEBUG_EXEC (if (Status != AE_OK) {return_ACPI_STATUS (Status);});


    /* Decode the opcode */

    switch (Optype)
    {
    case OPTYPE_UNDEFINED:

        DEBUG_PRINT (ACPI_ERROR, ("ExecEndOp: Undefined opcode type Op=%X\n",
                        Op));
        return_ACPI_STATUS (AE_NOT_IMPLEMENTED);
        break;


    case OPTYPE_BOGUS:
        DEBUG_PRINT (TRACE_PARSE, ("ExecEndOp: Internal opcode=%X type Op=%X\n",
                        Opcode, Op));
        break;

    case OPTYPE_CONSTANT:           /* argument type only */
    case OPTYPE_LITERAL:            /* argument type only */
    case OPTYPE_DATA_TERM:          /* argument type only */
    case OPTYPE_LOCAL_VARIABLE:     /* argument type only */
    case OPTYPE_METHOD_ARGUMENT:    /* argument type only */
        break;


    /* most operators with arguments */

    case OPTYPE_MONADIC1:
    case OPTYPE_DYADIC1:
    case OPTYPE_MONADIC2:
    case OPTYPE_MONADIC2R:
    case OPTYPE_DYADIC2:
    case OPTYPE_DYADIC2R:
    case OPTYPE_DYADIC2S:
    case OPTYPE_INDEX:
    case OPTYPE_MATCH:
    case OPTYPE_CREATE_FIELD:
    case OPTYPE_FATAL:

        Status = PsxCreateOperands (WalkState, FirstArg);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }

        OperandIndex = WalkState->NumOperands - 1;

        switch (Optype)
        {

        case OPTYPE_MONADIC1:

            /* 1 Operand, 0 ExternalResult, 0 InternalResult */

            Status = AmlExecMonadic1 (Opcode, &WalkState->Operands [OperandIndex]);
            break;


        case OPTYPE_MONADIC2:

            /* 1 Operand, 0 ExternalResult, 1 InternalResult */

            Status = AmlExecMonadic2 (Opcode, &WalkState->Operands [OperandIndex], &ResultObj);
            if (ACPI_SUCCESS (Status))
            {
                PsxResultStackPush (ResultObj, WalkState);
            }

            break;


        case OPTYPE_MONADIC2R:

            /* 1 Operand, 1 ExternalResult, 1 InternalResult */

            Status = AmlExecMonadic2R (Opcode, &WalkState->Operands [OperandIndex], &ResultObj);
            if (ACPI_SUCCESS (Status))
            {
                PsxResultStackPush (ResultObj, WalkState);
            }

            break;


        case OPTYPE_DYADIC1:

            /* 2 Operands, 0 ExternalResult, 0 InternalResult */

            Status = AmlExecDyadic1 (Opcode, &WalkState->Operands [OperandIndex]);

            break;


        case OPTYPE_DYADIC2:

            /* 2 Operands, 0 ExternalResult, 1 InternalResult */

            Status = AmlExecDyadic2 (Opcode, &WalkState->Operands [OperandIndex], &ResultObj);
            if (ACPI_SUCCESS (Status))
            {
                PsxResultStackPush (ResultObj, WalkState);
            }

            break;


        case OPTYPE_DYADIC2R:

            /* 2 Operands, 1 or 2 ExternalResults, 1 InternalResult */

            Status = AmlExecDyadic2R (Opcode, &WalkState->Operands [OperandIndex], &ResultObj);
            if (ACPI_SUCCESS (Status))
            {
                PsxResultStackPush (ResultObj, WalkState);
            }

            break;


        case OPTYPE_DYADIC2S:   /* Synchronization Operator */

            /* 2 Operands, 0 ExternalResult, 1 InternalResult */

            Status = AmlExecDyadic2S (Opcode, &WalkState->Operands [OperandIndex], &ResultObj);
            if (ACPI_SUCCESS (Status))
            {
                PsxResultStackPush (ResultObj, WalkState);
            }

            break;


        case OPTYPE_CREATE_FIELD:

            /* 3 or 4 Operands, 0 ExternalResult, 0 InternalResult */

            Status = AmlExecCreateField (Opcode, &WalkState->Operands [OperandIndex]);

            break;


        case OPTYPE_FATAL:

            /* 3 Operands, 0 ExternalResult, 0 InternalResult */

            Status = AmlExecFatal (&WalkState->Operands [OperandIndex]);
            break;


        case OPTYPE_INDEX:  /* Type 2 opcode with 3 operands */

            /* 3 Operands, 1 ExternalResult, 1 InternalResult */

            Status = AmlExecIndex (&WalkState->Operands [OperandIndex], &ResultObj);
            if (ACPI_SUCCESS (Status))
            {
                PsxResultStackPush (ResultObj, WalkState);
            }

            break;


        case OPTYPE_MATCH:  /* Type 2 opcode with 6 operands */

            /* 6 Operands, 0 ExternalResult, 1 InternalResult */

            Status = AmlExecMatch (&WalkState->Operands [OperandIndex], &ResultObj);
            PsxResultStackPush (ResultObj, WalkState);

            break;
        }

        break;



    case OPTYPE_CONTROL:    /* Type 1 opcode, IF/ELSE/WHILE/NOOP */

        /* 1 Operand, 0 ExternalResult, 0 InternalResult */

        Status = PsxExecEndControlOp (WalkState, Op);

        break;


    case OPTYPE_METHOD_CALL: 

        DEBUG_PRINT (TRACE_PARSE, ("ExecEndOp: Method invocation, Op=%X\n", Op));

        /*
         * (AML_METHODCALL) Op->Value->Arg->NameTableEntry contains the method NTE pointer
         */
        NextOp = FirstArg;          /* NextOp points to the op that holds the method name */
        Entry = NextOp->NameTableEntry;

        NextOp = NextOp->Next;      /* NextOp points to first argument op */


        /*
         * Get the method's arguments and put them on the operand stack
         */

        Status = PsxCreateOperands (WalkState, NextOp);
        if (ACPI_FAILURE (Status))
        {
            break;
        }

        /*
         * Since the operands will be passed to another control method, we must
         * resolve all local references here (Local variables, arguments to *this* method, etc.)
         */

        Status = PsxResolveOperands (WalkState);
        if (ACPI_FAILURE (Status))
        {
            break;
        }

        /* Open new scope on the scope stack */
/*
        Status = NsScopeStackPushEntry (Entry);
        if (ACPI_FAILURE (Status))
        {
            DEBUG_PRINT (ACPI_ERROR, ("ExecEndOp: Could not push Scope Stack\n"));
            break;
        }
*/

        /* Tell the walk loop to preempt this running method and execute the new method */

        Status = AE_PENDING;

        /* Return now; we don't want to disturb anything, especially the operand count! */

        return_ACPI_STATUS (Status);
        break;


    case OPTYPE_RECONFIGURATION:

        DEBUG_PRINT (ACPI_ERROR, ("ExecEndOp: Unimplemented reconfig opcode=%X Op=%X\n",
                        Op->Opcode, Op));

        Status = AE_NOT_IMPLEMENTED;
        break;


    case OPTYPE_NAMED_OBJECT:


        if ((WalkState->Origin->Opcode == AML_MethodOp) &&
            (WalkState->Origin != Op))
        {
            PsxLoad2EndOp (WalkState, Op);
        }

        switch (Op->Opcode)
        {
        case AML_RegionOp:

            DEBUG_PRINT (TRACE_EXEC, ("ExecEndOp: Executing OpRegion Address/Length Op=%X\n",
                            Op));

            Status = PsxEvalRegionOperands (WalkState, Op);


            break;


        case AML_MethodOp:
            
            /* End of execution, nothing else to do */

            break;


        case AML_AliasOp:

            /* Alias creation was already handled by call to psxload above */

            break;


        default:
            /* TBD: Nothing to do here at this time */

            Status = AE_OK;
            break;
        }
        
        break;

    default:

        DEBUG_PRINT (ACPI_ERROR, ("ExecEndOp: Unimplemented opcode, type=%X Opcode=%X Op=%X\n",
                        Optype, Op->Opcode, Op));

        Status = AE_NOT_IMPLEMENTED;
        break;
    }



    /*
     * Check if we just completed the evaluation of a conditional predicate 
     */

    if ((WalkState->ControlState) &&
        (WalkState->ControlState->Exec == CONTROL_PREDICATE_EXECUTING) &&
        (WalkState->ControlState->PredicateOp == Op))
    {
        /* Completed the predicate, the result must be a number */

        WalkState->ControlState->Exec = 0;

/* TBD: REDO now that we have the resultobj mechanism */

        if (ResultObj)
        {
            Status = PsxResultStackPop (&ObjDesc, WalkState);
            if (ACPI_FAILURE (Status))
            {
                goto Cleanup;
            }
        }

        else
        {
            Status = PsxCreateOperand (WalkState, Op);
            if (ACPI_FAILURE (Status))
            {
                goto Cleanup;
            }

            Status = AmlGetRvalue (&WalkState->Operands [0]);
            if (ACPI_FAILURE (Status))
            {
                goto Cleanup;
            }

            ObjDesc = WalkState->Operands [0];
        }

        if (!ObjDesc)
        {
            DEBUG_PRINT (ACPI_ERROR, ("ExecEndOp: No predicate ObjDesc=%X State=%X\n",
                            ObjDesc, WalkState));

            Status = AE_AML_NO_OPERAND;
            goto Cleanup;
        }

        if (ObjDesc->Common.Type != ACPI_TYPE_Number)
        {
            DEBUG_PRINT (ACPI_ERROR, ("ExecEndOp: Bad predicate ObjDesc=%X State=%X\n",
                            ObjDesc, WalkState));

            Status = AE_AML_OPERAND_TYPE;
            goto Cleanup;
        }
        /* Save the result of the predicate evaluation on the control stack */

        if (ObjDesc->Number.Value)
        {
            WalkState->ControlState->Predicate = TRUE;
        }
        else
        {
            /* Predicate is FALSE, we will just toss the rest of the package */

            WalkState->ControlState->Predicate = FALSE;
            Status = AE_FALSE;
        }

        DEBUG_PRINT (TRACE_EXEC, ("ExecEndOp: Completed a predicate eval=%X Op=%X\n",
                        WalkState->ControlState->Predicate, Op));

         /* Break to debugger to display result */

        DEBUG_EXEC (DbDisplayResultObject (ObjDesc));

        /* Delete the predicate result object (we know that we don't need it anymore) and cleanup the stack */

        CmDeleteInternalObject (ObjDesc);
        ResultObj = NULL;

        PsxObjStackPop (1, WalkState);

        WalkState->ControlState->Exec = CONTROL_NORMAL;
    }


Cleanup:

    if (ResultObj)
    {
        /* Break to debugger to display result */

        DEBUG_EXEC (DbDisplayResultObject (ResultObj));

        /* Delete the result op IFF:
         * Parent will not use the result -- such as any non-nested type2 op in a method (parent will be method)
         */
        PsxDeleteResultIfNotUsed (Op, ResultObj, WalkState);
    }

    /* Always clear the object stack */

    WalkState->NumOperands = 0; /* TBD Clear stack of return value, but don't delete it */
    
    return_ACPI_STATUS (Status);
}



