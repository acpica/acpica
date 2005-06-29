/******************************************************************************
 *
 * Module Name: dsopcode - Dispatcher Op Region support and handling of
 *                         "control" opcodes
 *              $Revision: 1.16 $
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

#define __DSOPCODE_C__

#include "acpi.h"
#include "acparser.h"
#include "amlcode.h"
#include "acdispat.h"
#include "acinterp.h"
#include "acnamesp.h"
#include "acevents.h"
#include "actables.h"

#define _COMPONENT          DISPATCHER
        MODULE_NAME         ("dsopcode")


/*****************************************************************************
 *
 * FUNCTION:    AcpiDsGetRegionArguments
 *
 * PARAMETERS:  RgnDesc         - A valid region object
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Get region address and length.  This implements the late
 *              evaluation of these region attributes.
 *
 ****************************************************************************/

ACPI_STATUS
AcpiDsGetRegionArguments (
    ACPI_OPERAND_OBJECT     *RgnDesc)
{
    ACPI_OPERAND_OBJECT     *MethodDesc;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_PARSE_OBJECT       *Op;
    ACPI_PARSE_OBJECT       *RegionOp;
    ACPI_STATUS             Status;
    ACPI_TABLE_DESC         *TableDesc;


    FUNCTION_TRACE_PTR ("DsGetRegionArguments", RgnDesc);


    if (RgnDesc->Region.RegionFlags & REGION_AGRUMENT_DATA_VALID)
    {
        return_ACPI_STATUS (AE_OK);
    }


    MethodDesc = RgnDesc->Region.Method;
    Node = RgnDesc->Region.Node;


    /*
     * Allocate a new parser op to be the root of the parsed
     * OpRegion tree
     */

    Op = AcpiPsAllocOp (AML_SCOPE_OP);
    if (!Op)
    {
        return (AE_NO_MEMORY);
    }

    /* Save the Node for use in AcpiPsParseAml */

    Op->Node = AcpiNsGetParentObject (Node);

    /* Get a handle to the parent ACPI table */

    Status = AcpiTbHandleToObject (Node->OwnerId, &TableDesc);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Parse the entire OpRegion declaration, creating a parse tree */

    Status = AcpiPsParseAml (Op, MethodDesc->Method.Pcode,
                                MethodDesc->Method.PcodeLength, 0,
                                NULL, NULL, NULL, AcpiDsLoad1BeginOp, AcpiDsLoad1EndOp);

    if (ACPI_FAILURE (Status))
    {
        AcpiPsDeleteParseTree (Op);
        return_ACPI_STATUS (Status);
    }


    /* Get and init the actual RegionOp created above */

/*    RegionOp = Op->Value.Arg;
    Op->Node = Node;*/


    RegionOp = Op->Value.Arg;
    RegionOp->Node = Node;
    AcpiPsDeleteParseTree (Op);

    /* AcpiEvaluate the address and length arguments for the OpRegion */

    Op = AcpiPsAllocOp (AML_SCOPE_OP);
    if (!Op)
    {
        return (AE_NO_MEMORY);
    }

    Op->Node = AcpiNsGetParentObject (Node);

    Status = AcpiPsParseAml (Op, MethodDesc->Method.Pcode,
                                MethodDesc->Method.PcodeLength,
                                ACPI_PARSE_EXECUTE | ACPI_PARSE_DELETE_TREE,
                                NULL /*MethodDesc*/, NULL, NULL,
                                AcpiDsExecBeginOp, AcpiDsExecEndOp);
/*
    AcpiPsWalkParsedAml (RegionOp, RegionOp, NULL, NULL, NULL,
                            NULL, TableDesc->TableId,
                            AcpiDsExecBeginOp, AcpiDsExecEndOp);
*/
    /* All done with the parse tree, delete it */

    AcpiPsDeleteParseTree (Op);

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiDsInitializeRegion
 *
 * PARAMETERS:  Op              - A valid region Op object
 *
 * RETURN:      Status
 *
 * DESCRIPTION:
 *
 ****************************************************************************/

ACPI_STATUS
AcpiDsInitializeRegion (
    ACPI_HANDLE             ObjHandle)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_STATUS             Status;


    ObjDesc = AcpiNsGetAttachedObject (ObjHandle);

    /* Namespace is NOT locked */

    Status = AcpiEvInitializeRegion (ObjDesc, FALSE);

    return (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiDsEvalRegionOperands
 *
 * PARAMETERS:  Op              - A valid region Op object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get region address and length
 *              Called from AcpiDsExecEndOp during OpRegion parse tree walk
 *
 ****************************************************************************/

ACPI_STATUS
AcpiDsEvalRegionOperands (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_OPERAND_OBJECT     *RegionDesc;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_PARSE_OBJECT       *NextOp;


    FUNCTION_TRACE_PTR ("DsEvalRegionOperands", Op);


    /*
     * This is where we evaluate the address and length fields of the OpRegion declaration
     */

    Node =  Op->Node;

    /* NextOp points to the op that holds the SpaceID */
    NextOp = Op->Value.Arg;

    /* NextOp points to address op */
    NextOp = NextOp->Next;

    /* AcpiEvaluate/create the address and length operands */

    Status = AcpiDsCreateOperands (WalkState, NextOp);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    RegionDesc = AcpiNsGetAttachedObject (Node);
    if (!RegionDesc)
    {
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    /* Get the length and save it */

    /* Top of stack */
    ObjDesc = WalkState->Operands[WalkState->NumOperands - 1];

    RegionDesc->Region.Length = ObjDesc->Number.Value;
    AcpiCmRemoveReference (ObjDesc);

    /* Get the address and save it */

    /* Top of stack - 1 */
    ObjDesc = WalkState->Operands[WalkState->NumOperands - 2];

    RegionDesc->Region.Address = ObjDesc->Number.Value;
    AcpiCmRemoveReference (ObjDesc);


    DEBUG_PRINT (TRACE_EXEC,
        ("DsEvalRegionOperands: RgnObj %p Addr %X Len %X\n",
        RegionDesc, RegionDesc->Region.Address, RegionDesc->Region.Length));

    /* Now the address and length are valid for this opregion */

    RegionDesc->Region.RegionFlags |= REGION_AGRUMENT_DATA_VALID;

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDsExecBeginControlOp
 *
 * PARAMETERS:  WalkList        - The list that owns the walk stack
 *              Op              - The control Op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handles all control ops encountered during control method
 *              execution.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiDsExecBeginControlOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_GENERIC_STATE      *ControlState;


    DEBUG_PRINT (TRACE_DISPATCH,
        ("BeginControlOp: Op=%p Opcode=%2.2X State=%p\n", Op,
        Op->Opcode, WalkState));

    switch (Op->Opcode)
    {
    case AML_IF_OP:
    case AML_WHILE_OP:

        /*
         * IF/WHILE: Create a new control state to manage these
         * constructs. We need to manage these as a stack, in order
         * to handle nesting.
         */

        ControlState = AcpiCmCreateControlState ();
        if (!ControlState)
        {
            Status = AE_NO_MEMORY;
            break;
        }

        AcpiCmPushGenericState (&WalkState->ControlState, ControlState);

        /*
         * Save a pointer to the predicate for multiple executions
         * of a loop
         */
        WalkState->ControlState->Control.AmlPredicateStart =
                    WalkState->ParserState->Aml - 1;
                    /*AcpiPsPkgLengthEncodingSize (GET8 (WalkState->ParserState->Aml));*/
        break;


    case AML_ELSE_OP:

        /* Predicate is in the state object */
        /* If predicate is true, the IF was executed, ignore ELSE part */

        if (WalkState->LastPredicate)
        {
            Status = AE_CTRL_TRUE;
        }

        break;


    case AML_RETURN_OP:

        break;


    default:
        break;
    }

    return (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDsExecEndControlOp
 *
 * PARAMETERS:  WalkList        - The list that owns the walk stack
 *              Op              - The control Op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handles all control ops encountered during control method
 *              execution.
 *
 *
 ******************************************************************************/

ACPI_STATUS
AcpiDsExecEndControlOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_GENERIC_STATE      *ControlState;


    switch (Op->Opcode)
    {
    case AML_IF_OP:

        DEBUG_PRINT (TRACE_DISPATCH,
            ("EndControlOp: [IF_OP] Op=%p\n", Op));

        /*
         * Save the result of the predicate in case there is an
         * ELSE to come
         */

        WalkState->LastPredicate =
                (BOOLEAN) WalkState->ControlState->Common.Value;

        /*
         * Pop the control state that was created at the start
         * of the IF and free it
         */

        ControlState =
                AcpiCmPopGenericState (&WalkState->ControlState);

        AcpiCmDeleteGenericState (ControlState);

        break;


    case AML_ELSE_OP:

        break;


    case AML_WHILE_OP:

        DEBUG_PRINT (TRACE_DISPATCH,
            ("EndControlOp: [WHILE_OP] Op=%p\n", Op));

        if (WalkState->ControlState->Common.Value)
        {
            /* Predicate was true, go back and evaluate it again! */

            Status = AE_CTRL_PENDING;
        }

/*        else
        {*/
            DEBUG_PRINT (TRACE_DISPATCH,
                ("EndControlOp: [WHILE_OP] termination! Op=%p\n", Op));

            /* Pop this control state and free it */

            ControlState =
                    AcpiCmPopGenericState (&WalkState->ControlState);

            WalkState->AmlLastWhile = ControlState->Control.AmlPredicateStart;
            AcpiCmDeleteGenericState (ControlState);
/*        }*/

        break;


    case AML_RETURN_OP:

        DEBUG_PRINT (TRACE_DISPATCH,
            ("EndControlOp: [RETURN_OP] Op=%p Arg=%p\n",Op, Op->Value.Arg));


        /*
         * One optional operand -- the return value
         * It can be either an immediate operand or a result that
         * has been bubbled up the tree
         */
        if (Op->Value.Arg)
        {
            /* Return statement has an immediate operand */

            Status = AcpiDsCreateOperands (WalkState, Op->Value.Arg);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }

            /*
             * If value being returned is a Reference (such as
             * an arg or local), resolve it now because it may
             * cease to exist at the end of the method.
             */

            Status = AcpiAmlResolveToValue (&WalkState->Operands [0], WalkState);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }

            /*
             * Get the return value and save as the last result
             * value.  This is the only place where WalkState->ReturnDesc
             * is set to anything other than zero!
             */

            WalkState->ReturnDesc = WalkState->Operands[0];
        }

        else if (WalkState->NumResults > 0)
        {
            /*
             * The return value has come from a previous calculation.
             *
             * If value being returned is a Reference (such as
             * an arg or local), resolve it now because it may
             * cease to exist at the end of the method.
             */

            Status = AcpiAmlResolveToValue (&WalkState->Results [0], WalkState);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }

            WalkState->ReturnDesc = WalkState->Results [0];
        }

        else
        {
            /* No return operand */

            if (WalkState->NumOperands)
            {
                AcpiCmRemoveReference (WalkState->Operands [0]);
            }

            WalkState->Operands [0]     = NULL;
            WalkState->NumOperands      = 0;
            WalkState->ReturnDesc       = NULL;
        }


        DEBUG_PRINT (TRACE_DISPATCH,
            ("EndControlOp: Completed RETURN_OP State=%p, RetVal=%p\n",
            WalkState, WalkState->ReturnDesc));

        /* End the control method execution right now */
        Status = AE_CTRL_TERMINATE;
        break;


    case AML_NOOP_OP:

        /* Just do nothing! */
        break;


    case AML_BREAK_POINT_OP:

        /* Call up to the OS dependent layer to handle this */

        AcpiOsBreakpoint (NULL);

        /* If it returns, we are done! */

        break;


    case AML_BREAK_OP:

        DEBUG_PRINT (ACPI_INFO,
            ("EndControlOp: Break to end of current package, Op=%p\n", Op));

        /*
         * As per the ACPI specification:
         *      "The break operation causes the current package
         *          execution to complete"
         *      "Break -- Stop executing the current code package
         *          at this point"
         *
         * Returning AE_FALSE here will cause termination of
         * the current package, and execution will continue one
         * level up, starting with the completion of the parent Op.
         */

        Status = AE_CTRL_FALSE;
        break;


    default:

        DEBUG_PRINT (ACPI_ERROR,
            ("EndControlOp: Unknown control opcode=%X Op=%p\n",
            Op->Opcode, Op));

        Status = AE_AML_BAD_OPCODE;
        break;
    }


    return (Status);
}

