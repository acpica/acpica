
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
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>

#include <parser.h>
#include <psopcode.h>

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


    OpInfo = PsGetOpcodeInfo (Op->Opcode);

    switch (OpInfo->Type)
    {
    case OPTYPE_CONTROL:

        Status = PsxExecBeginControlOp (WalkState, Op);
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
    ACPI_OBJECT_INTERNAL    **StartOfOperands;
    ACPI_OP_INFO            *OpInfo;


    FUNCTION_TRACE_PTR ("PsxExecEndOp", Op);


    Opcode = (UINT16) Op->Opcode;


    OpInfo = PsGetOpcodeInfo (Op->Opcode);
    if (!OpInfo)
    {
        DEBUG_PRINT (ACPI_ERROR, ("EndOp: Unknown opcode. Op=%X\n",
                        Op));

        return_ACPI_STATUS (AE_NOT_IMPLEMENTED);
    }

    Optype = OpInfo->Type;
    FirstArg = Op->Value.Arg;

    /* Decode the opcode */

    switch (Optype)
    {
    case OPTYPE_UNDEFINED:

        DEBUG_PRINT (ACPI_ERROR, ("EndOp: Undefined opcode type Op=%X\n",
                        Op));
        return_ACPI_STATUS (AE_NOT_IMPLEMENTED);
        break;


    case OPTYPE_BOGUS:
        DEBUG_PRINT (ACPI_ERROR, ("EndOp: Ignoring bogus opcode=%X type Op=%X\n",
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

        Status = PsxCreateOperands (FirstArg);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }


        switch (Optype)
        {

        case OPTYPE_MONADIC1:

            /* One operand, no result */

            Status = AmlExecMonadic1 (Opcode);
            break;


        case OPTYPE_MONADIC2:

            /* One operand, no result */

            Status = AmlExecMonadic2 (Opcode);
            break;


        case OPTYPE_MONADIC2R:

            /* One operand with result value */

            Status = AmlExecMonadic2R (Opcode);
            break;


        case OPTYPE_DYADIC1:

            /* Two operands, no result */

            Status = AmlExecDyadic1 (Opcode);
            break;


        case OPTYPE_DYADIC2:

            /* Two operands, no result */

            Status = AmlExecDyadic2 (Opcode);
            break;


        case OPTYPE_DYADIC2R:

            /* Two operands, one or two result values */

            Status = AmlExecDyadic2R (Opcode);

            /* Divide (only) returns two results */

            if (Op->Opcode == AML_DIVIDE)
            {
                /* Delete the REMAINDER object (leaving only the RESULT object) */

                AmlObjStackDeleteValue (STACK_TOP);
                AmlObjStackPop (1);
            }

            break;


        case OPTYPE_DYADIC2S:

            /* Synchronization operator, two operands */

            Status = AmlExecDyadic2S (Opcode);
            break;


        case OPTYPE_CREATE_FIELD:

            /* Three or four operands */

            Status = AmlExecCreateField (Opcode);
            break;


        case OPTYPE_FATAL:

            /* Three operands */

            Status = AmlExecFatal ();
            break;


        case OPTYPE_INDEX:

            /* Three operands */

            Status = AmlExecIndex ();
            break;


        case OPTYPE_MATCH:

            /* Six operands! */

            Status = AmlExecMatch ();
            break;
        }

        break;



    case OPTYPE_CONTROL:

        Status = PsxExecEndControlOp (WalkState, Op);
        break;

        break;


    case OPTYPE_METHOD_CALL: 

        DEBUG_PRINT (TRACE_PARSE, ("EndOp: Method invocation, Op=%X\n", Op));

        /*
         * (AML_METHODCALL) Op->Entry contains the method NTE
         */
        Entry =  Op->Entry;

        NextOp = FirstArg;          /* NextOp points to the op that holds the method name */
        NextOp = NextOp->Next;      /* NextOp points to first argument op */

        StartOfOperands = AmlObjStackGetPtr (STACK_TOP);

        Status = PsxCreateOperands (NextOp);
        if (ACPI_FAILURE (Status))
        {
            break;
        }

        /* Open new scope on the scope stack */

        NsPushMethodScope (Entry);

        /* Open new frame on method stack */
        /* Get arguments and push on method stack */


        /* Push new frame on Method stack */

        Status = AmlMthStackPush (StartOfOperands);
        if (ACPI_FAILURE (Status))
        {
            DEBUG_PRINT (ACPI_ERROR, ("EndOp: Could not push Method Stack\n"));

            /* TBD: do we need to pop the package stack here? */

            break;
        }


        /* Tell walk loop to preempt running method and execute this method */

        Status = AE_PENDING;
        break;


    case OPTYPE_RECONFIGURATION:

        DEBUG_PRINT (ACPI_ERROR, ("EndOp: Unimplemented reconfig opcode Op=%X\n",
                        Op));

        Status = AE_NOT_IMPLEMENTED;
        break;


    case OPTYPE_NAMED_OBJECT:

        switch (Op->Opcode)
        {
        case AML_OPREGION:

            DEBUG_PRINT (TRACE_EXEC, ("EndOp: Executing OpRegion Address/Length Op=%X\n",
                            Op));

            Status = PsxEvalRegionOperands (Op);


            break;


        case AML_METHOD:
            
            /* End of execution, nothing else to do */
            break;


        default:
            DEBUG_PRINT (TRACE_EXEC, ("EndOp: Unimplemented Named object, opcode= Op=%X\n",
                            Op->Opcode, Op));

            /* TBD: Nothing to do here at this time */

            Status = AE_OK;
            break;
        }

    default:

        break;
    }


    /*
     * Check if we just completed the evaluation of a conditional predicate 
     */

    if ((WalkState->ControlState) &&
        (WalkState->ControlState->Exec == CONTROL_PREDICATE_EXECUTING) &&
        (WalkState->ControlState->PredicateOp == Op))
    {
        DEBUG_PRINT (TRACE_EXEC, ("EndOp: Completed a predicate eval, opcode Op=%X\n",
                        Op));

        /* Completed the predicate, the result must be a number on the object stack */

        ObjDesc = AmlObjStackGetValue (STACK_TOP);
        if ((!ObjDesc) ||
            (ObjDesc->Common.Type != ACPI_TYPE_Number))
        {
            Status = AE_AML_ERROR;
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

        /* Delete the predicate object (we know that we don't need it anymore) and cleanup the stack */

        AmlObjStackDeleteValue (STACK_TOP);
        AmlObjStackPop (1);

        WalkState->ControlState->Exec = CONTROL_NORMAL;
    }


Cleanup:

    /* TBD: what to do with return value? */

    return_ACPI_STATUS (Status);

}



