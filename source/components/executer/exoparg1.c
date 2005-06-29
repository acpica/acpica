
/******************************************************************************
 * 
 * Module Name: iemonad - ACPI AML (p-code) execution for monadic operators
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

#define __IEMONAD_C__

#include <acpi.h>
#include <parser.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("iemonad");



/*****************************************************************************
 * 
 * FUNCTION:    AmlExecMonadic1
 *
 * PARAMETERS:  Opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 1 monadic operator with numeric operand on 
 *              object stack
 *
 * ALLOCATION:  Deletes the operand
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecMonadic1 (
    UINT16                  Opcode,
    ACPI_OBJECT_INTERNAL    **Operands)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE_PTR ("AmlExecMonadic1", Operands);


    if (AML_SleepOp == Opcode || AML_StallOp == Opcode)
    {
        Status = AmlPrepOperands ("n", Operands);                 /* Operand should be a Number */
    }

    else
    {
        Status = AmlPrepOperands ("l", Operands);                 /* Operand should be an Lvalue */
    }

    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, Operands, 1);
        return_ACPI_STATUS (Status);
    }


    /* Get the operand from the stack */

    DUMP_OPERANDS (Operands, IMODE_Execute, PsGetOpcodeName (Opcode), 1, "after AmlPrepOperands");
    ObjDesc = Operands[0];
    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    /* ObjDesc can be an NTE - extract the object from the NTE */

    if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))
    {
        if (!(ObjDesc = NsGetAttachedObject ((ACPI_HANDLE) ObjDesc)));
        {
            /* No object, just exit */

            return_ACPI_STATUS (AE_OK);
        }
    }


    /* Examine the opcode */

    switch (Opcode)
    {

    /*  DefRelease  :=  ReleaseOp   MutexObject */

    case AML_ReleaseOp:

        if (ACPI_TYPE_Mutex != ObjDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic1/ReleaseOp: Needed Mutex, found %d\n",
                    ObjDesc->Common.Type));
           return_ACPI_STATUS (AE_AML_ERROR);
        }

        Status = OsReleaseOpRqst (ObjDesc);
        return_ACPI_STATUS (Status);


    /*  DefReset    :=  ResetOp     EventObject */

    case AML_ResetOp:

        if (ACPI_TYPE_Event != ObjDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic1/ResetOp: Needed Event, found %d\n", ObjDesc->Common.Type));
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        Status = OsResetOpRqst (ObjDesc);
        return_ACPI_STATUS (Status);


    /*  DefSignal   :=  SignalOp    EventObject */
    
    case AML_SignalOp:

        if (ACPI_TYPE_Event != ObjDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic1/SignalOp: Needed Event, found %d\n", ObjDesc->Common.Type));
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        Status = OsSignalOpRqst (ObjDesc);
        return_ACPI_STATUS (Status);


    /*  DefSleep    :=  SleepOp MsecTime    */
    
    case AML_SleepOp:

        OsDoSuspend (ObjDesc->Number.Value);
        break;


    /*  DefStall    :=  StallOp UsecTime    */
    
    case AML_StallOp:

        OsdSleepUsec (ObjDesc->Number.Value);
        break;


    /*  Unknown opcode  */
    
    default:

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic1: Unknown monadic opcode %02x\n", Opcode));
        return_ACPI_STATUS (AE_AML_ERROR);
    
    } /* switch */


    /* 
     * Delete the operand (If NTE, it won't be deleted)
     */

    CmDeleteOperand (&Operands[0]);

    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecMonadic2R
 *
 * PARAMETERS:  Opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 monadic operator with numeric operand and
 *              result operand on operand stack
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecMonadic2R (
    UINT16                  Opcode,
    ACPI_OBJECT_INTERNAL    **Operands,
    ACPI_OBJECT_INTERNAL    **ReturnDesc)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *ResDesc;
    UINT32                  ResVal;
    ACPI_STATUS             Status;
    INT32                   d0, d1, d2, d3;



    FUNCTION_TRACE_PTR ("AmlExecMonadic2R", Operands);

    /*
     * We will try several different combinations of operands
     *
     * 1) Try Lvalue returning a Number
     */

    Status = AmlPrepOperands ("ln", Operands);
    if (Status == AE_TYPE)
    {
        /* Try Lvalue, returning a string or buffer */

        Status = AmlPrepOperands ("ls", Operands);
    }

    if (Status == AE_TYPE)
    {
        /* Try Lvalue, returning an Lvalue (caused by storing into a DebugOp */

        Status = AmlPrepOperands ("ll", Operands);
    }

    if (Status == AE_TYPE)
    {
        /* Try Package, returning a Number (Local0 = _PRT package) */

        Status = AmlPrepOperands ("pn", Operands);
    }

    /* If everything failed above, exit */

    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, Operands, 2);
        return_ACPI_STATUS (Status);
    }


    /*
     * Stack was prepped successfully
     */

    DUMP_OPERANDS (Operands, IMODE_Execute, PsGetOpcodeName (Opcode), 2, "after AmlPrepOperands");

    ResDesc = Operands[0];
    ObjDesc = Operands[-1];

    switch (Opcode)
    {
    /*  DefNot  :=  NotOp   Operand Result  */
    
    case AML_BitNotOp:

        ObjDesc->Number.Value = ~ObjDesc->Number.Value;
        break;


    /*  DefFindSetLeftBit   :=  FindSetLeftBitOp    Operand Result  */

    case AML_FindSetLeftBitOp:

        for (ResVal = 0; ObjDesc->Number.Value && ResVal < 33; ++ResVal)
        {
            ObjDesc->Number.Value >>= 1;
        }

        ObjDesc->Number.Value = ResVal;
        break;


    /*  DefFindSetRightBit  :=  FindSetRightBitOp   Operand Result  */

    case AML_FindSetRightBitOp:

        for (ResVal = 0; ObjDesc->Number.Value && ResVal < 33; ++ResVal)
        {
            ObjDesc->Number.Value <<= 1;
        }

        ObjDesc->Number.Value = ResVal == 0 ? 0 : 33 - ResVal;
        break;


    /*  DefFromBDC  :=  FromBCDOp   BCDValue    Result  */

    case AML_FromBCDOp:

        d0 = (INT32) (ObjDesc->Number.Value & 15);
        d1 = (INT32) (ObjDesc->Number.Value >> 4 & 15);
        d2 = (INT32) (ObjDesc->Number.Value >> 8 & 15);
        d3 = (INT32) (ObjDesc->Number.Value >> 12 & 15);
        
        if (d0 > 9 || d1 > 9 || d2 > 9 || d3 > 9)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic2R/FromBCDOp: improper BCD digit %d %d %d %d\n",
                    d3, d2, d1, d0));
            return_ACPI_STATUS (AE_AML_ERROR);
        }
        
        ObjDesc->Number.Value = d0 + d1 * 10 + d2 * 100 + d3 * 1000;
        break;


    /*  DefToBDC    :=  ToBCDOp Operand Result  */
    
    case AML_ToBCDOp:


        if (ObjDesc->Number.Value > 9999)
        {
            DEBUG_PRINT (ACPI_ERROR, ("iExecMonadic2R/ToBCDOp: BCD overflow: %d\n",
                    ObjDesc->Number.Value));
            return_ACPI_STATUS (AE_AML_ERROR);
        }
        
        ObjDesc->Number.Value
            = ObjDesc->Number.Value % 10
            + (ObjDesc->Number.Value / 10 % 10 << 4)
            + (ObjDesc->Number.Value / 100 % 10 << 8)
            + (ObjDesc->Number.Value / 1000 % 10 << 12);
        
        break;


    /*  DefShiftLeftBit     :=  ShiftLeftBitOp      Source          BitNum  */
    /*  DefShiftRightBit    :=  ShiftRightBitOp     Source          BitNum  */
    /*  DefCondRefOf        :=  CondRefOfOp         SourceObject    Result  */

    case AML_ShiftLeftBitOp:
    case AML_ShiftRightBitOp:
    case AML_CondRefOfOp:
        
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2R: %s unimplemented\n", PsGetOpcodeName (Opcode)));
        return_ACPI_STATUS (AE_AML_ERROR);


    case AML_StoreOp:

        break;


    default:

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2R: internal error: Unknown monadic opcode %02x\n",
                    Opcode));
        return_ACPI_STATUS (AE_AML_ERROR);
    }
    
    Status = AmlExecStore (ObjDesc, ResDesc);

    *ReturnDesc = ObjDesc;

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecMonadic2
 *
 * PARAMETERS:  Opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 monadic operator with numeric operand:
 *              DerefOfOp, RefOfOp, SizeOfOp, TypeOp, IncrementOp,
 *              DecrementOp, LNotOp,
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecMonadic2 (
    UINT16                  Opcode,
    ACPI_OBJECT_INTERNAL    **Operands,
    ACPI_OBJECT_INTERNAL    **ReturnDesc)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *TempDesc;
    ACPI_STATUS             Status;
    UINT32                  Type;


    FUNCTION_TRACE_PTR ("AmlExecMonadic2", Operands);


    if (AML_LNotOp == Opcode)
    {
        Status = AmlPrepOperands ("n", Operands);
    }
    else
    {
        Status = AmlPrepOperands ("l", Operands);
    }

    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, Operands, 1);
        return_ACPI_STATUS (Status);
    }

    DUMP_OPERANDS (Operands, IMODE_Execute, PsGetOpcodeName (Opcode), 1, "after AmlPrepOperands");


    /* Get the operand and decode the opcode */

    ObjDesc = Operands[0];

    switch (Opcode)
    {

    /*  DefLNot :=  LNotOp  Operand */

    case AML_LNotOp:

        ObjDesc->Number.Value = !ObjDesc->Number.Value;
        break;


    /*  DefDecrement    :=  DecrementOp Target  */
    /*  DefIncrement    :=  IncrementOp Target  */

    case AML_DecrementOp:
    case AML_IncrementOp:

        /* 
         * Since we are expecting an Lvalue on the top of the stack, it
         * can be either an NTE or an internal object.
         *
         * TBD: This may be the prototype code for all cases where an Lvalue
         * is expected!! 10/99
         */

        if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))
        {
            TempDesc = ObjDesc;
        }

        else
        {
            /* Duplicate the Lvalue in a TempDesc */
        
            TempDesc = CmCreateInternalObject (ObjDesc->Common.Type);
            if (!TempDesc)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            Status = CmCopyInternalObject (ObjDesc, TempDesc);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }
        }
        
        /* Convert the TempDesc Lvalue to a Number */
        
        Status = AmlPrepOperands ("n", &TempDesc);
        if (Status != AE_OK)
        {
            AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, Operands, 1);
            return_ACPI_STATUS (Status);
        }

        /* Do the actual increment or decrement */
        
        if (AML_IncrementOp == Opcode)
        {
            TempDesc->Number.Value++;
        }
        else
        {
            TempDesc->Number.Value--;
        }

        /* Store the result back in the original descriptor */

        Status = AmlExecStore (TempDesc, ObjDesc);

        /* 
         * Delete the temporary descriptor 
         * Don't delete ObjDesc because it holds the result
         */

        CmDeleteInternalObject (TempDesc);  

        *ReturnDesc = ObjDesc;
        return_ACPI_STATUS (Status);



    /*  DefObjectType   :=  ObjectTypeOp    SourceObject    */

    case AML_TypeOp:
        
        if (INTERNAL_TYPE_Lvalue == ObjDesc->Common.Type)
        {
            /* 
             * Not a Name -- an indirect name pointer would have
             * been converted to a direct name pointer in AmlPrepOperands
             */
            switch (ObjDesc->Lvalue.OpCode)
            {
            case AML_ZeroOp: case AML_OneOp: case AML_OnesOp:
                
                /* Constants are of type Number */
                
                Type = ACPI_TYPE_Number;
                break;


            case Debug1:
                
                /* Per spec, Debug object is of type Region */
                
                Type = ACPI_TYPE_Region;
                break;


            case AML_IndexOp:

                DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2/TypeOp: determining type of Index result is not implemented\n"));
                return_ACPI_STATUS (AE_AML_ERROR);


            case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
            case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:

                Type = PsxMthStackGetType (MTH_TYPE_LOCAL, (ObjDesc->Lvalue.OpCode - AML_Local0));
                break;


            case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
            case AML_Arg4: case AML_Arg5: case AML_Arg6:

                Type = PsxMthStackGetType (MTH_TYPE_ARG, (ObjDesc->Lvalue.OpCode - AML_Arg0));
                break;


            default:

                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecMonadic2/TypeOp:internal error: Unknown Lvalue subtype %02x\n",
                        ObjDesc->Lvalue.OpCode));
                return_ACPI_STATUS (AE_AML_ERROR);
            }
        }
        
        else
        {
            /* 
             * Since we passed AmlPrepOperands("l") and it's not an Lvalue,
             * it must be a direct name pointer.  Allocate a descriptor
             * to hold the type.
             */
            Type = NsGetType ((ACPI_HANDLE) ObjDesc);

            ObjDesc = CmCreateInternalObject (ACPI_TYPE_Number);
            if (!ObjDesc)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            /* 
             * Replace (ACPI_HANDLE) on TOS with descriptor containing result.
             * No need to CmDeleteInternalObject() first since TOS is an ACPI_HANDLE.
             */

            Operands[0] = ObjDesc;
        }
        

        /* TBD: reuse of ObjDesc, fix */

        ObjDesc->Common.Type = (UINT8) ACPI_TYPE_Number;
        ObjDesc->Number.Value = Type;

        break;


    /*  DefSizeOf   :=  SizeOfOp    SourceObject    */

    case AML_SizeOfOp:

        switch (ObjDesc->Common.Type)
        {

        case ACPI_TYPE_Buffer:

            ObjDesc->Number.Value = ObjDesc->Buffer.Length;
            ObjDesc->Common.Type = (UINT8) ACPI_TYPE_Number;
            break;


        case ACPI_TYPE_String:

            ObjDesc->Number.Value = ObjDesc->String.Length;
            ObjDesc->Common.Type = (UINT8) ACPI_TYPE_Number;
            break;


        case ACPI_TYPE_Package:

            ObjDesc->Number.Value = ObjDesc->Package.Count;
            ObjDesc->Common.Type = (UINT8) ACPI_TYPE_Number;
            break;


        default:

            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic2: Needed aggregate, found %d\n", ObjDesc->Common.Type));
            return_ACPI_STATUS (AE_AML_ERROR);

        }
        break;


    /*  DefRefOf    :=  RefOfOp     SourceObject    */

    case AML_RefOfOp:

        if (INTERNAL_TYPE_Lvalue == ObjDesc->Common.Type)
        {
            /* 
             * Not a Name -- an indirect name pointer would have
             * been converted to a direct name pointer in AmlPrepOperands
             */
            switch (ObjDesc->Lvalue.OpCode)
            {
            case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
            case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:

                ObjDesc = (void *) PsxMthStackGetNte (MTH_TYPE_LOCAL, (ObjDesc->Lvalue.OpCode - AML_Local0));
                break;


            case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
            case AML_Arg4: case AML_Arg5: case AML_Arg6:

                ObjDesc = (void *) PsxMthStackGetNte (MTH_TYPE_ARG, (ObjDesc->Lvalue.OpCode - AML_Arg0));
                break;


            default:

                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecMonadic2/RefOp:internal error: Unknown Lvalue subtype %02x\n",
                        ObjDesc->Lvalue.OpCode));
                return_ACPI_STATUS (AE_AML_ERROR);
            }
        }
        
        else
        {
            /* Get the NTE (look it up?) */

            ObjDesc = NULL;
            return_ACPI_STATUS (AE_NOT_IMPLEMENTED);
        }

        CmDeleteOperand (&Operands[0]);
        Operands[0] = ObjDesc;

        DEBUG_PRINT (TRACE_EXEC, ("AmlExecMonadic2: RefOf returns %p\n",
                    ObjDesc));

        /* Just return the object descriptor as the reference! */

        break;


    /*  DefDerefOf  :=  DerefOfOp   ObjReference    */

    case AML_DerefOfOp:

        if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))
        {
            /* Extract the actual object from the NTE (This is the dereference) */

            ObjDesc = ((NAME_TABLE_ENTRY *) ObjDesc)->Object;

            /* No need to delete object on stack, it is an NTE */

            Operands[0] = ObjDesc;  /* Return the object */
        }

        else
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2: DerefOf, invalid obj ref %p\n", ObjDesc));

            return_ACPI_STATUS (AE_NOT_IMPLEMENTED);
        }

        break;
        

    default:

        DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic2: Internal error, unknown monadic opcode %02x\n",
                    Opcode));
        
        return_ACPI_STATUS (AE_AML_ERROR);
    }


    /* Internal return value is at the top of the object stack */

    *ReturnDesc = ObjDesc;
    return_ACPI_STATUS (AE_OK);
}
 
