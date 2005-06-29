
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
#include <dispatch.h>
#include <interp.h>
#include <amlcode.h>
#include <namesp.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("iemonad");





/*****************************************************************************
 * 
 * FUNCTION:    AmlGetObjectReference
 *
 * PARAMETERS:  ObjDesc         - Create a reference to this object
 *              RetDesc         - Where to store the reference
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Obtain and return a "reference" to the target object
 *              Common code for the RefOfOp and the CondRefOfOp.
 *
 ****************************************************************************/

ACPI_STATUS
AmlGetObjectReference (
    ACPI_OBJECT_INTERNAL    *ObjDesc,
    ACPI_OBJECT_INTERNAL    **RetDesc)
{
    ACPI_STATUS             Status = AE_OK;



    if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_ACPI_OBJ))
    {
        if (ObjDesc->Common.Type != INTERNAL_TYPE_Lvalue)
        {
            *RetDesc = NULL;
            Status = AE_TYPE;
            goto Cleanup;
        }

        /* 
         * Not a Name -- an indirect name pointer would have
         * been converted to a direct name pointer in AmlResolveOperands
         */
        switch (ObjDesc->Lvalue.OpCode)
        {
        case AML_LocalOp:

            *RetDesc = (void *) DsMthStackGetNte (MTH_TYPE_LOCAL, (ObjDesc->Lvalue.Offset));
            break;


        case AML_ArgOp:

            *RetDesc = (void *) DsMthStackGetNte (MTH_TYPE_ARG, (ObjDesc->Lvalue.Offset));
            break;


        default:

            DEBUG_PRINT (ACPI_ERROR, ("AmlGetObjectReference: (Internal) Unknown Lvalue subtype %02x\n",
                            ObjDesc->Lvalue.OpCode));
            *RetDesc = NULL;
            Status = AE_AML_INTERNAL;
            goto Cleanup;
        }

    }

    else if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))
    {
        /* Must be a named object;  Just return the NTE */

        *RetDesc = ObjDesc;
    }
    
    else
    {
        *RetDesc = NULL;
        Status = AE_TYPE;
    }


Cleanup:
 
    DEBUG_PRINT (TRACE_EXEC, ("AmlGetObjectReference: Obj=%p Ref=%p\n", ObjDesc, *RetDesc));
    return Status;
}


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
 ****************************************************************************/

ACPI_STATUS
AmlExecMonadic1 (
    UINT16                  Opcode,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE_PTR ("AmlExecMonadic1", WALK_OPERANDS);


    /* Resolve all operands */

    Status = AmlResolveOperands (Opcode, WALK_OPERANDS); 
    DUMP_OPERANDS (WALK_OPERANDS, IMODE_Execute, PsGetOpcodeName (Opcode), 1, "after AmlResolveOperands");

    /* Get all operands */

    Status |= DsObjStackPopObject (&ObjDesc, WalkState);
    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, WALK_OPERANDS, 1);
        goto Cleanup;
    }


    /* Examine the opcode */

    switch (Opcode)
    {

    /*  DefRelease  :=  ReleaseOp   MutexObject */

    case AML_ReleaseOp:

        Status = OsReleaseMutex (ObjDesc);
        break;


    /*  DefReset    :=  ResetOp     EventObject */

    case AML_ResetOp:

        Status = OsResetEvent (ObjDesc);
        break;


    /*  DefSignal   :=  SignalOp    EventObject */
    
    case AML_SignalOp:

        Status = OsSignalEvent (ObjDesc);
        break;


    /*  DefSleep    :=  SleepOp     MsecTime    */
    
    case AML_SleepOp:

        OsDoSuspend (ObjDesc->Number.Value);
        break;


    /*  DefStall    :=  StallOp     UsecTime    */
    
    case AML_StallOp:

        OsDoStall (ObjDesc->Number.Value);
        break;


    /*  Unknown opcode  */
    
    default:

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic1: Unknown monadic opcode %02x\n", Opcode));
        Status = AE_AML_BAD_OPCODE;
        break;
    
    } /* switch */



Cleanup:

    /* Always delete the operand */

    CmDeleteInternalObject (ObjDesc);

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
    ACPI_WALK_STATE         *WalkState,
    ACPI_OBJECT_INTERNAL    **ReturnDesc)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *ResDesc;
    ACPI_OBJECT_INTERNAL    *RetDesc = NULL;
    ACPI_OBJECT_INTERNAL    *RetDesc2 = NULL;
    UINT32                  ResVal;
    ACPI_STATUS             Status;
    UINT32                  ReferenceCount;
    INT32                   d0;
    INT32                   d1;
    INT32                   d2;
    INT32                   d3;


    FUNCTION_TRACE_PTR ("AmlExecMonadic2R", WALK_OPERANDS);


    /* Resolve all operands */

    Status = AmlResolveOperands (Opcode, WALK_OPERANDS);
    DUMP_OPERANDS (WALK_OPERANDS, IMODE_Execute, PsGetOpcodeName (Opcode), 2, "after AmlResolveOperands");

    /* Get all operands */

    Status |= DsObjStackPopObject (&ResDesc, WalkState);
    Status |= DsObjStackPopObject (&ObjDesc, WalkState);
    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, WALK_OPERANDS, 2);
        goto Cleanup;
    }


    /* Create a return object of type NUMBER for most opcodes */

    switch (Opcode)
    {
    case AML_BitNotOp:
    case AML_FindSetLeftBitOp:
    case AML_FindSetRightBitOp:
    case AML_FromBCDOp:
    case AML_ToBCDOp:
    case AML_CondRefOfOp:

        RetDesc = CmCreateInternalObject (ACPI_TYPE_Number);
        if (!RetDesc)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        break;
    }


    switch (Opcode)
    {
    /*  DefNot  :=  NotOp   Operand Result  */
    
    case AML_BitNotOp:

        RetDesc->Number.Value = ~ObjDesc->Number.Value;
        break;


    /*  DefFindSetLeftBit   :=  FindSetLeftBitOp    Operand Result  */

    case AML_FindSetLeftBitOp:

        RetDesc->Number.Value = ObjDesc->Number.Value;
        for (ResVal = 0; RetDesc->Number.Value && ResVal < 33; ++ResVal)
        {
            RetDesc->Number.Value >>= 1;
        }

        RetDesc->Number.Value = ResVal;
        break;


    /*  DefFindSetRightBit  :=  FindSetRightBitOp   Operand Result  */

    case AML_FindSetRightBitOp:

        RetDesc->Number.Value = ObjDesc->Number.Value;
        for (ResVal = 0; RetDesc->Number.Value && ResVal < 33; ++ResVal)
        {
            RetDesc->Number.Value <<= 1;
        }

        RetDesc->Number.Value = ResVal == 0 ? 0 : 33 - ResVal;
        break;


    /*  DefFromBDC  :=  FromBCDOp   BCDValue    Result  */

    case AML_FromBCDOp:

        d0 = (INT32) (ObjDesc->Number.Value & 15);
        d1 = (INT32) (ObjDesc->Number.Value >> 4 & 15);
        d2 = (INT32) (ObjDesc->Number.Value >> 8 & 15);
        d3 = (INT32) (ObjDesc->Number.Value >> 12 & 15);
        
        if (d0 > 9 || d1 > 9 || d2 > 9 || d3 > 9)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2R/FromBCDOp: BCD digit too large %d %d %d %d\n",
                            d3, d2, d1, d0));
            Status = AE_AML_NUMERIC_OVERFLOW;
            goto Cleanup;
        }
        
        RetDesc->Number.Value = d0 + d1 * 10 + d2 * 100 + d3 * 1000;
        break;


    /*  DefToBDC    :=  ToBCDOp Operand Result  */
    
    case AML_ToBCDOp:


        if (ObjDesc->Number.Value > 9999)
        {
            DEBUG_PRINT (ACPI_ERROR, ("ExecMonadic2R/ToBCDOp: BCD overflow: %d\n",
                            ObjDesc->Number.Value));
            Status = AE_AML_NUMERIC_OVERFLOW;
            goto Cleanup;
        }
        
        RetDesc->Number.Value
            = ObjDesc->Number.Value % 10
            + (ObjDesc->Number.Value / 10 % 10 << 4)
            + (ObjDesc->Number.Value / 100 % 10 << 8)
            + (ObjDesc->Number.Value / 1000 % 10 << 12);
        
        break;


    /*  DefCondRefOf        :=  CondRefOfOp         SourceObject    Result  */

    case AML_CondRefOfOp:

        /*
         * This op is a little strange because the internal return value is different 
         * than the return value stored in the result descriptor (There are really 
         * two return values)
         */

        if ((NAME_TABLE_ENTRY *) ObjDesc == Gbl_RootObject)
        {
            /* This means that the object does not exist in the namespace, return FALSE */

            RetDesc->Number.Value = 0;

            /* Must delete the result descriptor since there is no reference being returned */

            CmDeleteInternalObject (ResDesc);
            goto Cleanup;
        }

        /* Get the object reference and store it */

        Status = AmlGetObjectReference (ObjDesc, &RetDesc2);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }

        Status = AmlExecStore (RetDesc2, ResDesc);
        if (RetDesc2->Common.ReferenceCount > 1)
        {
            DEBUG_PRINT (TRACE_EXEC, ("AmlExecMonadic2R: Return Obj %p has other refs, incrementing\n",
                            RetDesc2));
            CmUpdateObjectReference (RetDesc2, REF_INCREMENT);
        }

        /* The object exists in the namespace, return TRUE */

        RetDesc->Number.Value = (UINT32) -1;
        goto Cleanup;
        break;


    case AML_StoreOp:

        /*
         * A store operand is typically a number, string, buffer or lvalue
         * TBD: What about a store to a package?
         */

        /* 
         * Do the store, and be careful about deleting the source object,
         * since the object itself may have been stored.
         */
        
        ReferenceCount = ObjDesc->Common.ReferenceCount;
        Status = AmlExecStore (ObjDesc, ResDesc);
        if (ObjDesc->Common.ReferenceCount > ReferenceCount)
        {
            DEBUG_PRINT (TRACE_EXEC, ("AmlExecMonadic2R: Operand %p was physically stored, not deleting\n",
                            ObjDesc));
            CmUpdateObjectReference (ObjDesc, REF_INCREMENT);
        }
        
        *ReturnDesc = ObjDesc;
        ObjDesc = NULL;
        return_ACPI_STATUS (Status);

        break;


    case AML_DebugOp:
    
        /* Lvalue, returning an Lvalue */

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2R: DebugOp should never get here!\n"));
        return_ACPI_STATUS (AE_OK);
        break;


    /*
     * These are obsolete opcodes 
     */

    /*  DefShiftLeftBit     :=  ShiftLeftBitOp      Source          BitNum  */
    /*  DefShiftRightBit    :=  ShiftRightBitOp     Source          BitNum  */

    case AML_ShiftLeftBitOp:
    case AML_ShiftRightBitOp:
        
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2R: %s unimplemented\n", 
                        PsGetOpcodeName (Opcode)));
        Status = AE_SUPPORT;
        goto Cleanup;
        break;


    default:

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2R: internal error: Unknown monadic opcode %02x\n",
                        Opcode));
        Status = AE_AML_BAD_OPCODE;
        goto Cleanup;
    }
    

    Status = AmlExecStore (RetDesc, ResDesc);

    if (RetDesc->Common.ReferenceCount > 1)
    {
        DEBUG_PRINT (TRACE_EXEC, ("AmlExecMonadic2R: Return Obj %p has other refs, incrementing\n",
                        RetDesc));
        CmUpdateObjectReference (RetDesc, REF_INCREMENT);
    }



Cleanup:
    /* Always delete the operand object */

    CmDeleteInternalObject (ObjDesc);

    /* Delete return object(s) on error */

    if (ACPI_FAILURE (Status))
    {
        CmDeleteInternalObject (ResDesc);     /* Result descriptor */
        if (RetDesc)
        {
            CmDeleteInternalObject (RetDesc);
            RetDesc = NULL;
        }
    }

    /* Set the return object and exit */

    *ReturnDesc = RetDesc;
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
    ACPI_WALK_STATE         *WalkState,
    ACPI_OBJECT_INTERNAL    **ReturnDesc)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *TmpDesc;
    ACPI_OBJECT_INTERNAL    *RetDesc = NULL;
    ACPI_STATUS             Status;
    UINT32                  Type;
    UINT32                  Value;


    FUNCTION_TRACE_PTR ("AmlExecMonadic2", WALK_OPERANDS);


    /* Resolve all operands */

    Status = AmlResolveOperands (Opcode, WALK_OPERANDS);
    DUMP_OPERANDS (WALK_OPERANDS, IMODE_Execute, PsGetOpcodeName (Opcode), 1, "after AmlResolveOperands");

    /* Get all operands */

    Status |= DsObjStackPopObject (&ObjDesc, WalkState);
    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, WALK_OPERANDS, 1);
        goto Cleanup;
    }



    /* Get the operand and decode the opcode */


    switch (Opcode)
    {

    /*  DefLNot :=  LNotOp  Operand */

    case AML_LNotOp:

        RetDesc = CmCreateInternalObject (ACPI_TYPE_Number);
        if (!RetDesc)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        RetDesc->Number.Value = !ObjDesc->Number.Value;
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
           RetDesc = ObjDesc;
       }

       else
       {
            /* 
             * Duplicate the Lvalue in a new object so that we can resolve it
             * without destroying the original Lvalue object
             */
        
            RetDesc = CmCreateInternalObject (INTERNAL_TYPE_Lvalue);
            if (!RetDesc)
            {
              Status = AE_NO_MEMORY;
               goto Cleanup;
            }

            RetDesc->Lvalue.OpCode = ObjDesc->Lvalue.OpCode;
            RetDesc->Lvalue.Offset = ObjDesc->Lvalue.Offset;
            RetDesc->Lvalue.Object = ObjDesc->Lvalue.Object;
        }
        

        /* 
         * Convert the RetDesc Lvalue to a Number
         * (This deletes the original RetDesc)
         */
    
        Status = AmlResolveOperands (AML_LNotOp, &RetDesc);
        if (Status != AE_OK)
        {
            AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, WALK_OPERANDS, 1);
            goto Cleanup;
        }

        /* Do the actual increment or decrement */
    
        if (AML_IncrementOp == Opcode)
        {
            RetDesc->Number.Value++;
        }
        else
        {
            RetDesc->Number.Value--;
        }

        /* Store the result back in the original descriptor */

        Status = AmlExecStore (RetDesc, ObjDesc);

        /* Objdesc was just deleted (because it is an Lvalue) */

        ObjDesc = NULL;

        break;


    /*  DefObjectType   :=  ObjectTypeOp    SourceObject    */

    case AML_TypeOp:
        
        if (INTERNAL_TYPE_Lvalue == ObjDesc->Common.Type)
        {
            /* 
             * Not a Name -- an indirect name pointer would have
             * been converted to a direct name pointer in AmlResolveOperands
             */
            switch (ObjDesc->Lvalue.OpCode)
            {
            case AML_ZeroOp: 
            case AML_OneOp: 
            case AML_OnesOp:
                
                /* Constants are of type Number */
                
                Type = ACPI_TYPE_Number;
                break;


            case AML_DebugOp:
                
                /* Per 1.0b spec, Debug object is of type DebugObject */
                
                Type = ACPI_TYPE_DebugObject;
                break;


            case AML_IndexOp:

                /* Get the type of this reference (index into another object) */

                Type = ObjDesc->Lvalue.TargetType;
                break;


            case AML_LocalOp:

                Type = DsMthStackGetType (MTH_TYPE_LOCAL, (ObjDesc->Lvalue.Offset));
                break;


            case AML_ArgOp:

                Type = DsMthStackGetType (MTH_TYPE_ARG, (ObjDesc->Lvalue.Offset));
                break;


            default:

                DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2/TypeOp:internal error: Unknown Lvalue subtype %02x\n",
                                ObjDesc->Lvalue.OpCode));
                Status = AE_AML_INTERNAL;
                goto Cleanup;
            }
        }
        
        else
        {
            /* 
             * Since we passed AmlResolveOperands("l") and it's not an Lvalue,
             * it must be a direct name pointer. 
             */
            Type = NsGetType ((ACPI_HANDLE) ObjDesc);
        }

        /*  Allocate a descriptor to hold the type. */

        RetDesc = CmCreateInternalObject (ACPI_TYPE_Number);
        if (!RetDesc)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }
        
        RetDesc->Number.Value = Type;
        break;


    /*  DefSizeOf   :=  SizeOfOp    SourceObject    */

    case AML_SizeOfOp:

        if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))
        {
            ObjDesc = NsGetAttachedObject (ObjDesc);
        }

        if (!ObjDesc)
        {
            Value = 0;
        }

        else
        {
            switch (ObjDesc->Common.Type)
            {

            case ACPI_TYPE_Buffer:

                Value = ObjDesc->Buffer.Length;
                break;


            case ACPI_TYPE_String:

                Value = ObjDesc->String.Length;
                break;


            case ACPI_TYPE_Package:

                Value = ObjDesc->Package.Count;
                break;


            default:

                DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2: Not Buf/Str/Pkg - found type 0x%X\n", 
                                ObjDesc->Common.Type));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
        }

        /* 
         * Now that we have the size of the object, create a result
         * object to hold the value
         */

        RetDesc = CmCreateInternalObject (ACPI_TYPE_Number);
        if (!RetDesc)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        RetDesc->Number.Value = Value;
        break;


    /*  DefRefOf    :=  RefOfOp     SourceObject    */

    case AML_RefOfOp:

        Status = AmlGetObjectReference (ObjDesc, &RetDesc);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }
        break;


    /*  DefDerefOf  :=  DerefOfOp   ObjReference    */

    case AML_DerefOfOp:


        /* Check for a method local or argument */

        if (!VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))
        {
            /* Must dereference the local/arg reference first */

            switch (ObjDesc->Lvalue.OpCode)
            {
                /* Set ObjDesc to the value of the local/arg */

            case AML_LocalOp:

                DsMthStackGetValue (MTH_TYPE_LOCAL, (ObjDesc->Lvalue.Offset), &ObjDesc);
                break;


            case AML_ArgOp:

                DsMthStackGetValue (MTH_TYPE_ARG, (ObjDesc->Lvalue.Offset), &ObjDesc);
                break;
            }
        }


        if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))
        {
            /* Extract the actual object from the NTE (This is the dereference) */

            RetDesc = ((NAME_TABLE_ENTRY *) ObjDesc)->Object;
        }

        else
        {   /* This must be a reference object produced by the Index ASL operation */
            /* Must be an lvalue, make sure opcode is correct */

            if ((ObjDesc->Lvalue.OpCode != AML_IndexOp) &&
                (ObjDesc->Lvalue.OpCode != AML_RefOfOp))
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2: DerefOf, invalid obj ref %p\n", ObjDesc));

                Status = AE_TYPE;
                goto Cleanup;
            }


            switch (ObjDesc->Lvalue.OpCode)
            {
            case AML_IndexOp:

                if (ObjDesc->Lvalue.TargetType == ACPI_TYPE_Buffer)
                {
                    RetDesc = CmCreateInternalObject (ACPI_TYPE_Number);
                    if (!RetDesc)
                    {
                        Status = AE_NO_MEMORY;
                        goto Cleanup;
                    }

                    TmpDesc = ObjDesc->Lvalue.Object;
                    RetDesc->Number.Value = TmpDesc->Buffer.Pointer[ObjDesc->Lvalue.Offset];

                    /* TBD: (see below) Don't add an additional ref! */
                }
                else if (ObjDesc->Lvalue.TargetType == ACPI_TYPE_Package)
                {
                    RetDesc = *(ObjDesc->Lvalue.Where);
                }
                
                else
                {
                    DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2: DerefOf, Unknown TargetType %X in obj %p\n", 
                                    ObjDesc->Lvalue.TargetType, ObjDesc));
                    Status = AE_AML_OPERAND_TYPE;
                    goto Cleanup;
                }

                break;


            case AML_RefOfOp:
           
                RetDesc = ObjDesc->Lvalue.Object;
                break;
            }
        }


        /* TBD: ??? Return an additional reference to the object */

        /* CmUpdateObjectReference (RetDesc, REF_INCREMENT); */

        break;
        

    default:

        DEBUG_PRINT (ACPI_ERROR, ( "AmlExecMonadic2: Internal error, unknown monadic opcode %02x\n",
                        Opcode));
        Status = AE_AML_BAD_OPCODE;
        goto Cleanup;
    }



Cleanup:

    if (ObjDesc)
    {
        CmDeleteInternalObject (ObjDesc);
    }

    /* Delete return object on error */

    if (ACPI_FAILURE (Status) &&
        (RetDesc))
    {
        CmDeleteInternalObject (RetDesc);
        RetDesc = NULL;
    }

    *ReturnDesc = RetDesc;
    return_ACPI_STATUS (Status);
}
 
