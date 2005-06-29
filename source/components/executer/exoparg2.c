/******************************************************************************
 *
 * Module Name: exdyadic - ACPI AML execution for dyadic (2-operand) operators
 *              $Revision: 1.93 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, 2001, Intel Corp.
 * All rights reserved.
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


#define __EXDYADIC_C__

#include "acpi.h"
#include "acparser.h"
#include "acnamesp.h"
#include "acinterp.h"
#include "acevents.h"
#include "amlcode.h"
#include "acdispat.h"


#define _COMPONENT          ACPI_EXECUTER
        MODULE_NAME         ("exdyadic")


/*******************************************************************************
 *
 * FUNCTION:    AcpiExDoConcatenate
 *
 * PARAMETERS:  *ObjDesc            - Object to be converted.  Must be an
 *                                    Integer, Buffer, or String
 *              WalkState           - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Concatenate two objects OF THE SAME TYPE.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiExDoConcatenate (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_OPERAND_OBJECT     *ObjDesc2,
    ACPI_OPERAND_OBJECT     **ActualRetDesc,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    UINT32                  i;
    ACPI_INTEGER            ThisInteger;
    ACPI_OPERAND_OBJECT     *RetDesc;
    NATIVE_CHAR             *NewBuf;
    UINT32                  IntegerSize = sizeof (ACPI_INTEGER);


    FUNCTION_ENTRY ();


    /*
     * There are three cases to handle:
     * 1) Two Integers concatenated to produce a buffer
     * 2) Two Strings concatenated to produce a string
     * 3) Two Buffers concatenated to produce a buffer
     */
    switch (ObjDesc->Common.Type)
    {
    case ACPI_TYPE_INTEGER:

        /* Handle both ACPI 1.0 and ACPI 2.0 Integer widths */

        if (WalkState->MethodNode->Flags & ANOBJ_DATA_WIDTH_32)
        {
            /*
             * We are running a method that exists in a 32-bit ACPI table.
             * Truncate the value to 32 bits by zeroing out the upper
             * 32-bit field
             */
            IntegerSize = sizeof (UINT32);
        }

        /* Result of two integers is a buffer */

        RetDesc = AcpiUtCreateInternalObject (ACPI_TYPE_BUFFER);
        if (!RetDesc)
        {
            return (AE_NO_MEMORY);
        }

        /* Need enough space for two integers */

        RetDesc->Buffer.Length = IntegerSize * 2;
        NewBuf = ACPI_MEM_CALLOCATE (RetDesc->Buffer.Length);
        if (!NewBuf)
        {
            REPORT_ERROR
                (("ExDoConcatenate: Buffer allocation failure\n"));
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        RetDesc->Buffer.Pointer = (UINT8 *) NewBuf;

        /* Convert the first integer */

        ThisInteger = ObjDesc->Integer.Value;
        for (i = 0; i < IntegerSize; i++)
        {
            NewBuf[i] = (UINT8) ThisInteger;
            ThisInteger >>= 8;
        }

        /* Convert the second integer */

        ThisInteger = ObjDesc2->Integer.Value;
        for (; i < (IntegerSize * 2); i++)
        {
            NewBuf[i] = (UINT8) ThisInteger;
            ThisInteger >>= 8;
        }

        break;


    case ACPI_TYPE_STRING:

        RetDesc = AcpiUtCreateInternalObject (ACPI_TYPE_STRING);
        if (!RetDesc)
        {
            return (AE_NO_MEMORY);
        }

        /* Operand0 is string  */

        NewBuf = ACPI_MEM_ALLOCATE (ObjDesc->String.Length +
                                    ObjDesc2->String.Length + 1);
        if (!NewBuf)
        {
            REPORT_ERROR
                (("ExDoConcatenate: String allocation failure\n"));
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        STRCPY (NewBuf, ObjDesc->String.Pointer);
        STRCPY (NewBuf + ObjDesc->String.Length,
                        ObjDesc2->String.Pointer);

        /* Point the return object to the new string */

        RetDesc->String.Pointer = NewBuf;
        RetDesc->String.Length = ObjDesc->String.Length +=
                                 ObjDesc2->String.Length;
        break;


    case ACPI_TYPE_BUFFER:

        /* Operand0 is a buffer */

        RetDesc = AcpiUtCreateInternalObject (ACPI_TYPE_BUFFER);
        if (!RetDesc)
        {
            return (AE_NO_MEMORY);
        }

        NewBuf = ACPI_MEM_ALLOCATE (ObjDesc->Buffer.Length +
                                    ObjDesc2->Buffer.Length);
        if (!NewBuf)
        {
            REPORT_ERROR
                (("ExDoConcatenate: Buffer allocation failure\n"));
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        MEMCPY (NewBuf, ObjDesc->Buffer.Pointer,
                        ObjDesc->Buffer.Length);
        MEMCPY (NewBuf + ObjDesc->Buffer.Length, ObjDesc2->Buffer.Pointer,
                        ObjDesc2->Buffer.Length);

        /*
         * Point the return object to the new buffer
         */

        RetDesc->Buffer.Pointer     = (UINT8 *) NewBuf;
        RetDesc->Buffer.Length      = ObjDesc->Buffer.Length +
                                      ObjDesc2->Buffer.Length;
        break;


    default:
        Status = AE_AML_INTERNAL;
        RetDesc = NULL;
    }


    *ActualRetDesc = RetDesc;
    return (AE_OK);


Cleanup:

    AcpiUtRemoveReference (RetDesc);
    return (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiExOpcode_2A_0T_0R
 *
 * PARAMETERS:  WalkState           - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute opcode with two arguments, no target, and no return
 *              value.
 *
 * ALLOCATION:  Deletes both operands
 *
 ******************************************************************************/

ACPI_STATUS
AcpiExOpcode_2A_0T_0R (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OPERAND_OBJECT     **Operand = &WalkState->Operands[0];
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE_PTR ("ExOpcode_2A_0T_0R", WALK_OPERANDS);



    /* Examine the opcode */

    switch (WalkState->Opcode)
    {

    case AML_NOTIFY_OP:         /* Notify (NotifyObject, NotifyValue) */

        /* The first operand is a namespace node */

        Node = (ACPI_NAMESPACE_NODE *) Operand[0];
        Operand[0] = NULL;

        /* The node must refer to a device or thermal zone */

        if (Node && Operand[1])
        {
            switch (Node->Type)
            {
            case ACPI_TYPE_DEVICE:
            case ACPI_TYPE_THERMAL:

                /*
                 * Dispatch the notify to the appropriate handler
                 * NOTE: the request is queued for execution after this method
                 * completes.  The notify handlers are NOT invoked synchronously
                 * from this thread -- because handlers may in turn run other
                 * control methods.
                 */
                Status = AcpiEvQueueNotifyRequest (Node,
                                        (UINT32) Operand[1]->Integer.Value);
                break;

            default:
                ACPI_DEBUG_PRINT ((ACPI_DB_ERROR, "Unexpected notify object type %X\n",
                    Node->Type));

                Status = AE_AML_OPERAND_TYPE;
                break;
            }
        }
        break;

    default:

        REPORT_ERROR (("AcpiExOpcode_2A_0T_0R: Unknown dyadic opcode %X\n", WalkState->Opcode));
        Status = AE_AML_BAD_OPCODE;
    }


    /* Always delete both operands */

    AcpiUtRemoveReference (Operand[1]);
    AcpiUtRemoveReference (Operand[0]);


    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiExOpcode_2A_2T_1R
 *
 * PARAMETERS:  WalkState           - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a dyadic operator (2 operands) with 2 output targets
 *              and one implicit return value.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiExOpcode_2A_2T_1R (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OPERAND_OBJECT     **Operand = &WalkState->Operands[0];
    ACPI_OPERAND_OBJECT     *RetDesc1 = NULL;
    ACPI_OPERAND_OBJECT     *RetDesc2 = NULL;
    ACPI_STATUS             Status;


    FUNCTION_TRACE_STR ("ExOpcode_2A_2T_1R", AcpiPsGetOpcodeName (WalkState->Opcode));

    /*
     * Execute the opcode
     */
    switch (WalkState->Opcode)
    {
    case AML_DIVIDE_OP:             /* Divide (Dividend, Divisor, RemainderResult QuotientResult) */

        RetDesc1 = AcpiUtCreateInternalObject (ACPI_TYPE_INTEGER);
        if (!RetDesc1)
        {
            Status = AE_NO_MEMORY;
            break;
        }

        RetDesc2 = AcpiUtCreateInternalObject (ACPI_TYPE_INTEGER);
        if (!RetDesc2)
        {
            Status = AE_NO_MEMORY;
            break;
        }

        /* Quotient to RetDesc1, remainder to RetDesc2 */

        Status = AcpiUtDivide (&Operand[0]->Integer.Value, &Operand[1]->Integer.Value,
                               &RetDesc1->Integer.Value,   &RetDesc2->Integer.Value);
        break;


    default:

        REPORT_ERROR (("AcpiExOpcode_2A_2T_1R: Unknown opcode %X\n",
                WalkState->Opcode));
        Status = AE_AML_BAD_OPCODE;
        break;
    }


    /* 
     * Always delete the input operands 
     */
    AcpiUtRemoveReference (Operand[0]);
    AcpiUtRemoveReference (Operand[1]);


    if (ACPI_SUCCESS (Status))
    {
        /* Store the results to the target reference operands */

        Status = AcpiExStore (RetDesc2, Operand[2], WalkState);
        if (ACPI_FAILURE (Status))
        {
            goto ErrorExit;
        }

        Status = AcpiExStore (RetDesc1, Operand[3], WalkState);
        if (ACPI_FAILURE (Status))
        {
            goto ErrorExit;
        }

        /*
         * Since the remainder is not returned indirectly, remove a reference to
         * it. Only the quotient is returned indirectly.
         */
        AcpiUtRemoveReference (RetDesc2);
        WalkState->ResultObj = RetDesc1;

        return_ACPI_STATUS (Status);
    }


ErrorExit:

    /* On failure, delete the target reference operands */

    AcpiUtRemoveReference (Operand[2]);
    AcpiUtRemoveReference (Operand[3]);

    /* And delete the return objects */

    AcpiUtRemoveReference (RetDesc1);
    AcpiUtRemoveReference (RetDesc2);

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiExDoMathOp
 *
 * PARAMETERS:  Opcode              - AML opcode
 *              Operand0            - Integer operand #0
 *              Operand0            - Integer operand #1
 *
 * RETURN:      Integer result of the operation
 *
 * DESCRIPTION: Execute a math AML opcode. The purpose of having all of the
 *              math functions here is to prevent a lot of pointer dereferencing
 *              to obtain the operands.
 *
 ******************************************************************************/

ACPI_INTEGER
AcpiExDoMathOp (
    UINT16                  Opcode,
    ACPI_INTEGER            Operand0,
    ACPI_INTEGER            Operand1)
{


    switch (Opcode)
    {
    case AML_ADD_OP:                /* Add (Operand0, Operand1, Result) */

        return (Operand0 + Operand1);


    case AML_BIT_AND_OP:            /* And (Operand0, Operand1, Result) */

        return (Operand0 & Operand1);


    case AML_BIT_NAND_OP:           /* NAnd (Operand0, Operand1, Result) */

        return (~(Operand0 & Operand1));


    case AML_BIT_OR_OP:             /* Or (Operand0, Operand1, Result) */

        return (Operand0 | Operand1);


    case AML_BIT_NOR_OP:            /* NOr (Operand0, Operand1, Result) */

        return (~(Operand0 | Operand1));


    case AML_BIT_XOR_OP:            /* XOr (Operand0, Operand1, Result) */

        return (Operand0 ^ Operand1);


    case AML_MULTIPLY_OP:           /* Multiply (Operand0, Operand1, Result) */

        return (Operand0 * Operand1);


    case AML_SHIFT_LEFT_OP:         /* ShiftLeft (Operand, ShiftCount, Result) */

        return (Operand0 << Operand1);


    case AML_SHIFT_RIGHT_OP:        /* ShiftRight (Operand, ShiftCount, Result) */

        return (Operand0 >> Operand1);


    case AML_SUBTRACT_OP:           /* Subtract (Operand0, Operand1, Result) */

        return (Operand0 - Operand1);

    default:

        return (0);
    }
}



/*******************************************************************************
 *
 * FUNCTION:    AcpiExDoLogicalOp
 *
 * PARAMETERS:  Opcode              - AML opcode
 *              Operand0            - Integer operand #0
 *              Operand0            - Integer operand #1
 *
 * RETURN:      TRUE/FALSE result of the operation
 *
 * DESCRIPTION: Execute a logical AML opcode. The purpose of having all of the
 *              functions here is to prevent a lot of pointer dereferencing
 *              to obtain the operands and to simplify the generation of the
 *              logical value.
 *
 *              Note: cleanest machine code seems to be produced by the code
 *              below, rather than using statements of the form:
 *                  Result = (Operand0 == Operand1);
 *
 ******************************************************************************/

BOOLEAN
AcpiExDoLogicalOp (
    UINT16                  Opcode,
    ACPI_INTEGER            Operand0,
    ACPI_INTEGER            Operand1)
{


    switch (Opcode)
    {

    case AML_LAND_OP:               /* LAnd (Operand0, Operand1) */

        if (Operand0 && Operand1)
        {
            return (TRUE);
        }
        break;


    case AML_LEQUAL_OP:             /* LEqual (Operand0, Operand1) */

        if (Operand0 == Operand1)
        {
            return (TRUE);
        }
        break;


    case AML_LGREATER_OP:           /* LGreater (Operand0, Operand1) */

        if (Operand0 > Operand1)
        {
            return (TRUE);
        }
        break;


    case AML_LLESS_OP:              /* LLess (Operand0, Operand1) */

        if (Operand0 < Operand1)
        {
            return (TRUE);
        }
        break;


    case AML_LOR_OP:                 /* LOr (Operand0, Operand1) */

        if (Operand0 || Operand1)
        {
            return (TRUE);
        }
        break;
    }

    return (FALSE);
}



/*******************************************************************************
 *
 * FUNCTION:    AcpiExOpcode_2A_1T_1R
 *
 * PARAMETERS:  WalkState           - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute opcode with two arguments, one target, and a return
 *              value.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiExOpcode_2A_1T_1R (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OPERAND_OBJECT     **Operand = &WalkState->Operands[0];
    ACPI_OPERAND_OBJECT     *RetDesc    = NULL;
    ACPI_STATUS             Status      = AE_OK;


    FUNCTION_TRACE_U32 ("ExOpcode_2A_1T_1R", WalkState->Opcode);


    /*
     * Execute the opcode
     */
    switch (WalkState->Opcode)
    {
    case AML_ADD_OP:
    case AML_BIT_AND_OP:
    case AML_BIT_NAND_OP:
    case AML_BIT_OR_OP:
    case AML_BIT_NOR_OP:
    case AML_BIT_XOR_OP:
    case AML_MULTIPLY_OP:
    case AML_SHIFT_LEFT_OP:
    case AML_SHIFT_RIGHT_OP:
    case AML_SUBTRACT_OP:

        RetDesc = AcpiUtCreateInternalObject (ACPI_TYPE_INTEGER);
        if (!RetDesc)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        RetDesc->Integer.Value = AcpiExDoMathOp (WalkState->Opcode, 
                                                Operand[0]->Integer.Value, 
                                                Operand[1]->Integer.Value);
        break;


    case AML_MOD_OP:                /* Mod (Dividend, Divisor, RemainderResult (ACPI 2.0) */

        RetDesc = AcpiUtCreateInternalObject (ACPI_TYPE_INTEGER);
        if (!RetDesc)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        /* RetDesc will contain the remainder */

        Status = AcpiUtDivide (&Operand[0]->Integer.Value, &Operand[1]->Integer.Value,
                        NULL, &RetDesc->Integer.Value);

        break;


    case AML_CONCAT_OP:             /* Concatenate (Data1, Data2, Result) */

        /*
         * Convert the second operand if necessary.  The first operand
         * determines the type of the second operand, (See the Data Types
         * section of the ACPI specification.)  Both object types are
         * guaranteed to be either Integer/String/Buffer by the operand
         * resolution mechanism above.
         */
        switch (Operand[0]->Common.Type)
        {
        case ACPI_TYPE_INTEGER:
            Status = AcpiExConvertToInteger (Operand[1], &Operand[1], WalkState);
            break;

        case ACPI_TYPE_STRING:
            Status = AcpiExConvertToString (Operand[1], &Operand[1], 16, ACPI_UINT32_MAX, WalkState);
            break;

        case ACPI_TYPE_BUFFER:
            Status = AcpiExConvertToBuffer (Operand[1], &Operand[1], WalkState);
            break;

        default:
            Status = AE_AML_INTERNAL;
        }

        if (ACPI_SUCCESS (Status))
        {
            /*
             * Both operands are now known to be the same object type
             * (Both are Integer, String, or Buffer), and we can now perform the
             * concatenation.
             */
            Status = AcpiExDoConcatenate (Operand[0], Operand[1], &RetDesc, WalkState);
        }
        break;


    case AML_TO_STRING_OP:          /* ToString (Buffer, Length, Result) (ACPI 2.0) */

        Status = AcpiExConvertToString (Operand[0], &RetDesc, 16,
                        (UINT32) Operand[1]->Integer.Value, WalkState);
        break;


    case AML_CONCAT_RES_OP:         /* ConcatenateResTemplate (Buffer, Buffer, Result) (ACPI 2.0) */

        Status = AE_NOT_IMPLEMENTED;
        break;


    default:

        REPORT_ERROR (("AcpiExOpcode_2A_1T_1R: Unknown opcode %X\n",
                WalkState->Opcode));
        Status = AE_AML_BAD_OPCODE;
        break;
    }


    /* Always delete the operands */

    AcpiUtRemoveReference (Operand[0]);
    AcpiUtRemoveReference (Operand[1]);


    if (ACPI_SUCCESS (Status))
    {
        /*
         * Store the result of the operation (which is now in Operand[0]) into
         * the result descriptor, or the location pointed to by the result
         * descriptor (Operand[2]).
         */
        Status = AcpiExStore (RetDesc, Operand[2], WalkState);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }

        WalkState->ResultObj = RetDesc;
    }


Cleanup:

    /* Delete return object on error */

    if (ACPI_FAILURE (Status))
    {
        /* On failure, delete the result op */

        AcpiUtRemoveReference (Operand[2]);

        /* And delete the internal return object */

        AcpiUtRemoveReference (RetDesc);
    }

    /* Set the return object and exit */

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiExOpcode_2A_0T_1R
 *
 * PARAMETERS:  WalkState           - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute opcode with 2 arguments, no target, and a return value
 *
 ******************************************************************************/

ACPI_STATUS
AcpiExOpcode_2A_0T_1R (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OPERAND_OBJECT     **Operand = &WalkState->Operands[0];
    ACPI_OPERAND_OBJECT     *RetDesc = NULL;
    ACPI_STATUS             Status = AE_OK;
    BOOLEAN                 LogicalResult = FALSE;


    FUNCTION_TRACE_PTR ("ExOpcode_2A_0T_1R", WALK_OPERANDS);


    /* Create the internal return object */

    RetDesc = AcpiUtCreateInternalObject (ACPI_TYPE_INTEGER);
    if (!RetDesc)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    /*
     * Execute the Opcode
     */
    switch (WalkState->Opcode)
    {

    case AML_LAND_OP:               /* LAnd     (Operand0, Operand1) */
    case AML_LEQUAL_OP:             /* LEqual   (Operand0, Operand1) */
    case AML_LGREATER_OP:           /* LGreater (Operand0, Operand1) */
    case AML_LLESS_OP:              /* LLess    (Operand0, Operand1) */
    case AML_LOR_OP:                /* LOr      (Operand0, Operand1) */

        LogicalResult = AcpiExDoLogicalOp (WalkState->Opcode, 
                                            Operand[0]->Integer.Value,
                                            Operand[1]->Integer.Value);
        break;


    case AML_COPY_OP:               /* Copy (Source, Target) (ACPI 2.0) */

        Status = AE_NOT_IMPLEMENTED;
        goto Cleanup;
        break;


    case AML_ACQUIRE_OP:            /* Acquire (MutexObject, Timeout) */

        Status = AcpiExAcquireMutex (Operand[1], Operand[0], WalkState);
        if (Status == AE_TIME)
        {
            LogicalResult = TRUE;       /* TRUE = Acquire timed out */
            Status = AE_OK;
        }
        break;


    case AML_WAIT_OP:               /* Wait (EventObject, Timeout) */

        Status = AcpiExSystemWaitEvent (Operand[1], Operand[0]);
        if (Status == AE_TIME)
        {
            LogicalResult = TRUE;       /* TRUE, Wait timed out */
            Status = AE_OK;
        }
        break;


    default:

        REPORT_ERROR (("AcpiExOpcode_2A_0T_1R: Unknown dyadic opcode %X\n", WalkState->Opcode));
        Status = AE_AML_BAD_OPCODE;
        goto Cleanup;
        break;
    }


    /* 
     * Set return value to according to LogicalResult. logical TRUE (all ones)
     * Default is FALSE (zero) 
     */
    if (LogicalResult)
    {
        RetDesc->Integer.Value = ACPI_INTEGER_MAX;
    }


Cleanup:

    /* Always delete operands */

    AcpiUtRemoveReference (Operand[0]);
    AcpiUtRemoveReference (Operand[1]);


    /* Delete return object on error */

    if (ACPI_FAILURE (Status) &&
        (RetDesc))
    {
        AcpiUtRemoveReference (RetDesc);
        RetDesc = NULL;
    }


    /* Set the return object and exit */

    WalkState->ResultObj = RetDesc;
    return_ACPI_STATUS (Status);
}


