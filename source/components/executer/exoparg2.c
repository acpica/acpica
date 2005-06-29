
/******************************************************************************
 * 
 * Module Name: iedyad - ACPI AML (p-code) execution for dyadic operators
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
 * 2.2. Intel grants,  of charge, to any person ("Licensee") obtaining a
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


#define __IEDYAD_C__

#include <acpi.h>
#include <parser.h>
#include <namesp.h>
#include <interp.h>
#include <events.h>
#include <amlcode.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("iedyad");


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic1
 *
 * PARAMETERS:  Opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 1 dyadic operator with numeric operands:
 *              NotifyOp
 *
 * ALLOCATION:  Deletes both operands
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecDyadic1 (
    UINT16                  Opcode,
    ACPI_OBJECT_INTERNAL    **Operands)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    ACPI_OBJECT_INTERNAL    *ValDesc = NULL;
    NAME_TABLE_ENTRY        *Entry;
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE_PTR ("AmlExecDyadic1", Operands);


    Status = AmlPrepOperands ("nl", Operands);

    if (Status != AE_OK)
    {
        /* Invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, Operands, 2);
        goto Cleanup;
    }

    DUMP_OPERANDS (Operands, IMODE_Execute, PsGetOpcodeName (Opcode), 2, "after AmlPrepOperands");

    /* Get the operands */

    ValDesc = Operands[0];
    ObjDesc = Operands[-1];


    /* Examine the opcode */

    switch (Opcode)
    {

    /* DefNotify   :=  NotifyOp    NotifyObject    NotifyValue */

    case AML_NotifyOp:

        /* The ObjDesc is actually an NTE */

        Entry = (NAME_TABLE_ENTRY *) ObjDesc;
        ObjDesc = NULL;

        /* Object must be a device or thermal zone */

        if (Entry && ValDesc)
        {
            switch (Entry->Type)
            {
            case ACPI_TYPE_Device:
            case ACPI_TYPE_Thermal:
            
                /* Requires that Device and ThermalZone be compatible mappings */

                /* Dispatch the notify to the appropriate handler */

                EvNotifyDispatch (Entry, ValDesc->Number.Value);
                break;

            default:
                DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic1/NotifyOp: unexpected notify object type %d\n",
                                ObjDesc->Common.Type));
                
                Status = AE_AML_OPERAND_TYPE;
            }
        }
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic1: Unknown dyadic opcode %02x\n", Opcode));
        Status = AE_AML_BAD_OPCODE;
    }


Cleanup:

    /* Always delete both operands */

    CmDeleteOperand (&Operands[0]);
    CmDeleteOperand (&Operands[-1]);
    

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic2R
 *
 * PARAMETERS:  Opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 dyadic operator with numeric operands and
 *              one or two result operands.
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecDyadic2R (
    UINT16                  Opcode,
    ACPI_OBJECT_INTERNAL    **Operands,
    ACPI_OBJECT_INTERNAL    **ReturnDesc)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *ObjDesc2;
    ACPI_OBJECT_INTERNAL    *ResDesc = NULL;
    ACPI_OBJECT_INTERNAL    *ResDesc2 = NULL;
    ACPI_OBJECT_INTERNAL    *RetDesc = NULL;
    ACPI_OBJECT_INTERNAL    *RetDesc2 = NULL;
    ACPI_STATUS             Status;
    UINT32                  Remainder;
    INT32                   NumOperands;
    char                    *NewBuf;


    FUNCTION_TRACE_PTR ("AmlExecDyadic2R", Operands);


    /* Examine the opcode */

    switch (Opcode)
    {

    /* DefConcat   :=  ConcatOp    Data1   Data2   Result  */

    case AML_ConcatOp:

        Status = AmlPrepOperands ("lss", Operands);
        NumOperands = 3;
        break;


    /* DefDivide   :=  DivideOp Dividend Divisor Remainder Quotient    */

    case AML_DivideOp:

        Status = AmlPrepOperands ("llnn", Operands);
        NumOperands = 4;
        break;


    /* DefX    :=  XOp Operand1    Operand2    Result  */

    default:

        Status = AmlPrepOperands ("lnn", Operands);
        NumOperands = 3;
        break;
    }


    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, Operands, NumOperands);
        goto Cleanup;
    }

    DUMP_OPERANDS (Operands, IMODE_Execute, PsGetOpcodeName (Opcode), NumOperands, "after AmlPrepOperands");


    /* Get all operand and result objects from the stack */

    if (AML_DivideOp == Opcode)
    {
        ResDesc2    = Operands[0];
        ResDesc     = Operands[-1];
        ObjDesc2    = Operands[-2];
        ObjDesc     = Operands[-3];
    }

    else
    {
        ResDesc     = Operands[0];
        ObjDesc2    = Operands[-1];
        ObjDesc     = Operands[-2];
    }


    /* Create an internal return object if necessary */

    switch (Opcode)
    {
    case AML_AddOp:
    case AML_BitAndOp:
    case AML_BitNandOp:
    case AML_BitOrOp:
    case AML_BitNorOp:
    case AML_BitXorOp:
    case AML_DivideOp:
    case AML_MultiplyOp:
    case AML_ShiftLeftOp:
    case AML_ShiftRightOp:
    case AML_SubtractOp:

        RetDesc = CmCreateInternalObject (ACPI_TYPE_Number);
        if (!RetDesc)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        break;
    }


    /* 
     * Execute the opcode 
     */

    switch (Opcode)
    {

    /* DefAdd  :=  AddOp   Operand1    Operand2    Result  */

    case AML_AddOp:

        RetDesc->Number.Value = ObjDesc->Number.Value + ObjDesc2->Number.Value;
        break;
 
        
    /* DefAnd  :=  AndOp   Operand1    Operand2    Result  */

    case AML_BitAndOp:

        RetDesc->Number.Value = ObjDesc->Number.Value & ObjDesc2->Number.Value;
        break;

        
    /* DefNAnd :=  NAndOp  Operand1    Operand2    Result  */

    case AML_BitNandOp:

        RetDesc->Number.Value = ~(ObjDesc->Number.Value & ObjDesc2->Number.Value);
        break;
   
       
    /* DefOr   :=  OrOp    Operand1    Operand2    Result  */
        
    case AML_BitOrOp:

        RetDesc->Number.Value = ObjDesc->Number.Value | ObjDesc2->Number.Value;
        break;

        
    /* DefNOr  :=  NOrOp   Operand1    Operand2    Result  */

    case AML_BitNorOp:

        RetDesc->Number.Value = ~(ObjDesc->Number.Value | ObjDesc2->Number.Value);
        break;

        
    /* DefXOr  :=  XOrOp   Operand1    Operand2    Result  */

    case AML_BitXorOp:

        RetDesc->Number.Value = ObjDesc->Number.Value ^ ObjDesc2->Number.Value;
        break;

        
    /* DefDivide   :=  DivideOp Dividend Divisor Remainder Quotient    */

    case AML_DivideOp:

        if ((UINT32) 0 == ObjDesc2->Number.Value)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2R/DivideOp: Divide by zero\n"));
            REPORT_ERROR ("AmlExecDyadic2R/DivideOp: Divide by zero");
            Status = AE_AML_DIVIDE_BY_ZERO;
            goto Cleanup;
        }

        RetDesc2 = CmCreateInternalObject (ACPI_TYPE_Number);
        if (!RetDesc2)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        Remainder               = ObjDesc->Number.Value % ObjDesc2->Number.Value;
        RetDesc->Number.Value   = ObjDesc->Number.Value / ObjDesc2->Number.Value;   /* Result (what we used to call the quotient) */
        RetDesc2->Number.Value  = Remainder;                                        /* Remainder */
        break;

        
    /* DefMultiply :=  MultiplyOp  Operand1    Operand2    Result  */

    case AML_MultiplyOp:

        RetDesc->Number.Value = ObjDesc->Number.Value * ObjDesc2->Number.Value;
        break;

        
    /* DefShiftLeft    :=  ShiftLeftOp Operand ShiftCount  Result  */

    case AML_ShiftLeftOp:

        RetDesc->Number.Value = ObjDesc->Number.Value << ObjDesc2->Number.Value;
        break;

        
    /* DefShiftRight   :=  ShiftRightOp    Operand ShiftCount  Result  */

    case AML_ShiftRightOp:

        RetDesc->Number.Value = ObjDesc->Number.Value >> ObjDesc2->Number.Value;
        break;

        
    /* DefSubtract :=  SubtractOp  Operand1    Operand2    Result  */

    case AML_SubtractOp:

        RetDesc->Number.Value = ObjDesc->Number.Value - ObjDesc2->Number.Value;
        break;


    /* DefConcat   :=  ConcatOp    Data1   Data2   Result  */

    case AML_ConcatOp:

        if (ObjDesc2->Common.Type != ObjDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2R/ConcatOp: operand type mismatch %d %d\n",
                            ObjDesc->Common.Type, ObjDesc2->Common.Type));
            Status = AE_AML_OPERAND_TYPE;
            goto Cleanup;
        }

        /* Both operands are now known to be the same */
        
        if (ACPI_TYPE_String == ObjDesc->Common.Type)
        {
            RetDesc = CmCreateInternalObject (ACPI_TYPE_String);
            if (!RetDesc)
            {
                Status = AE_NO_MEMORY;
                goto Cleanup;
            }

            /* Operand1 is string  */

            NewBuf = CmAllocate ((ACPI_SIZE) (ObjDesc->String.Length
                                                + ObjDesc2->String.Length + 1));
            if (!NewBuf)
            {
                REPORT_ERROR ("AmlExecDyadic2R/ConcatOp: String allocation failure");
                Status = AE_NO_MEMORY;
                goto Cleanup;
            }
            
            STRCPY (NewBuf, (char *) ObjDesc->String.Pointer);
            STRCPY (NewBuf + ObjDesc->String.Length, (char *) ObjDesc2->String.Pointer);
            
            /* Point the return object to the new string */
            
            RetDesc->String.Pointer = NewBuf;
            RetDesc->String.Length = ObjDesc->String.Length += ObjDesc2->String.Length;
        }
        
        else
        {
            /* Operand1 is not a string ==> must be a buffer */

            RetDesc = CmCreateInternalObject (ACPI_TYPE_Buffer);
            if (!RetDesc)
            {
                Status = AE_NO_MEMORY;
                goto Cleanup;
            }

            NewBuf = CmAllocate ((ACPI_SIZE) (ObjDesc->Buffer.Length
                                                + ObjDesc2->Buffer.Length));
            if (!NewBuf)
            {
                /* Only bail out if the buffer is small */
                
                /* TBD: what is the point of this code? */

                if (ObjDesc->Buffer.Length + ObjDesc2->Buffer.Length < 1024)
                {
                    REPORT_ERROR ("AmlExecDyadic2R/ConcatOp: Buffer allocation failure");
                    return_ACPI_STATUS (AE_NO_MEMORY);
                }

                DEBUG_PRINT (ACPI_ERROR, (
                            "AmlExecDyadic2R/ConcatOp: Buffer allocation failure %d\n",
                            ObjDesc->Buffer.Length + ObjDesc2->Buffer.Length));
                Status = AE_NO_MEMORY;
                goto Cleanup;
            }

            MEMCPY (NewBuf, ObjDesc->Buffer.Pointer, 
                            (ACPI_SIZE) ObjDesc->Buffer.Length);
            MEMCPY (NewBuf + ObjDesc->Buffer.Length, ObjDesc2->Buffer.Pointer,
                            (ACPI_SIZE) ObjDesc2->Buffer.Length);
            
            /*
             * Point the return object to the new buffer
             */
            
            RetDesc->Buffer.Pointer     = (UINT8 *) NewBuf;
            RetDesc->Buffer.Length      = ObjDesc->Buffer.Length + ObjDesc2->Buffer.Length;
        }
        break;


    default:

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2R: Unknown dyadic opcode %02x\n", Opcode));
        Status = AE_AML_BAD_OPCODE;
        goto Cleanup;
    }

    
    /*
     * Store the result of the operation (which is now in ObjDesc) into
     * the result descriptor, or the location pointed to by the result
     * descriptor (ResDesc).
     */

    if ((Status = AmlExecStore (RetDesc, ResDesc)) != AE_OK)
    {
        goto Cleanup;
    }
    
    if (AML_DivideOp == Opcode)
    {
        Status = AmlExecStore (RetDesc2, ResDesc2);

        /*
         * Since the remainder is not returned, check now if it should
         * be deleted (isn't being referenced)
         */
        if (RetDesc2->Common.ReferenceCount == 1)
        {
            CmDeleteInternalObject (RetDesc2);
        }
    }


    if (RetDesc->Common.ReferenceCount > 1)
    {
        DEBUG_PRINT (TRACE_EXEC, ("AmlExecDyadic2R: Return Obj %p has other refs, incrementing\n",
                        RetDesc));
        CmUpdateObjectReference (RetDesc, REF_INCREMENT);
    }


Cleanup:

    /* Always delete the operands */

    if (AML_DivideOp == Opcode)
    {
        CmDeleteOperand (&Operands[-2]);
        CmDeleteOperand (&Operands[-3]);

        /* On failure, delete the result ops */

        if (ACPI_FAILURE (Status))
        {
            CmDeleteOperand (&Operands[-1]);
            CmDeleteOperand (&Operands[0]);
        }
    }

    else
    {
        CmDeleteOperand (&Operands[-1]);
        CmDeleteOperand (&Operands[-2]);

        /* On failure, delete the result op */

        if (ACPI_FAILURE (Status))
        {
            CmDeleteOperand (&Operands[0]);
        }
    }

    /* Delete return object on error */

    if (ACPI_FAILURE (Status) &&
        (RetDesc))
    {
        CmDeleteInternalObject (RetDesc);
        RetDesc = NULL;
    }


    /* Set the return object and exit */

    *ReturnDesc = RetDesc;
    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic2S
 *
 * PARAMETERS:  Opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 dyadic synchronization operator
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecDyadic2S (
    UINT16                  Opcode,
    ACPI_OBJECT_INTERNAL    **Operands,
    ACPI_OBJECT_INTERNAL    **ReturnDesc)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *TimeDesc;
    ACPI_OBJECT_INTERNAL    *RetDesc = NULL;
    NAME_TABLE_ENTRY        *ThisEntry;
    ACPI_STATUS             Status;


    FUNCTION_TRACE_PTR ("AmlExecDyadic2S", Operands);


    Status = AmlPrepOperands ("nl", Operands);
    if (Status != AE_OK)
    {   
        /* Invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, Operands, 2);
        goto Cleanup;
    }


    /* Get the operands and validate them */

    DUMP_OPERANDS (Operands, IMODE_Execute, PsGetOpcodeName (Opcode), 2, "after AmlPrepOperands");

    TimeDesc    = Operands[0];
    ObjDesc     = Operands[-1];

    if (!TimeDesc || !ObjDesc)
    {
        Status = AE_AML_NO_OPERAND;
        goto Cleanup;
    }

    /* ObjDesc can be an NTE */

    if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))
    {
        ThisEntry = (NAME_TABLE_ENTRY *) ObjDesc;

        ObjDesc = NsGetAttachedObject ((ACPI_HANDLE) ThisEntry);
        if (!ObjDesc)
        {
            /* No object present, create a Mutex object */

            ObjDesc = CmCreateInternalObject (ACPI_TYPE_Mutex);
            if (!ObjDesc)
            {
                Status = AE_NO_MEMORY;
                goto Cleanup;
            }
            
            /* Initialize the new object and install it in the NTE */

            ObjDesc->Mutex.SyncLevel = 0;
            ObjDesc->Mutex.Semaphore = 0;
            ObjDesc->Mutex.LockCount = 0;
            ObjDesc->Mutex.ThreadId  = 0;

            NsAttachObject ((ACPI_HANDLE) ThisEntry, ObjDesc, ACPI_TYPE_Mutex);
        }
    }


    /* Create the internal return object */

    RetDesc = CmCreateInternalObject (ACPI_TYPE_Number);
    if (!RetDesc)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    
    /* Examine the opcode */

    switch (Opcode)
    {

    /* DefAcquire  :=  AcquireOp   MutexObject Timeout */

    case AML_AcquireOp:

        if (ACPI_TYPE_Mutex != ObjDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2S/AcquireOp: Needed Mutex, found %d\n",
                            ObjDesc->Common.Type));
            Status = AE_AML_OPERAND_TYPE;
            goto Cleanup;
        }

        Status = OsAcquireMutex (TimeDesc, ObjDesc);
        break;


    /* DefWait :=  WaitOp  EventObject Timeout */

    case AML_WaitOp:

        if (ACPI_TYPE_Event != ObjDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2S/WaitOp: Needed Event, found %d\n",
                            ObjDesc->Common.Type));
            Status = AE_AML_OPERAND_TYPE;
            goto Cleanup;
        }

        Status = OsWaitEvent (TimeDesc, ObjDesc);
        break;


    default:

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2S: Unknown dyadic synchronization opcode %02x\n",
                        Opcode));
        Status = AE_AML_BAD_OPCODE;
        goto Cleanup;
    }


    /* Return a boolean indicating if operation timed out (TRUE) or not (FALSE) */

    if (Status == AE_TIME)
    {
        RetDesc->Number.Value = (UINT32)(-1);   /* TRUE, operation timed out */
    }

    else
    {
        RetDesc->Number.Value = 0;              /* FALSE, operation did not time out */
    }



Cleanup:

    /* Delete params */

    CmDeleteOperand (&Operands[0]);
    CmDeleteOperand (&Operands[-1]);

    /* Delete return object on error */

    if (ACPI_FAILURE (Status) &&
        (RetDesc))
    {
        CmDeleteInternalObject (RetDesc);
        RetDesc = NULL;
    }


    /* Set the return object and exit */

    *ReturnDesc = RetDesc;
    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic2
 *
 * PARAMETERS:  Opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 dyadic operator with numeric operands and
 *              no result operands
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *              containing result value
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecDyadic2 (
    UINT16                  Opcode,
    ACPI_OBJECT_INTERNAL    **Operands,
    ACPI_OBJECT_INTERNAL    **ReturnDesc)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *ObjDesc2;
    ACPI_OBJECT_INTERNAL    *RetDesc = NULL;
    ACPI_STATUS             Status;
    BOOLEAN                 Lboolean;


    FUNCTION_TRACE_PTR ("AmlExecDyadic2", Operands);


    Status = AmlPrepOperands ("nn", Operands);
    if (Status != AE_OK)
    {
        /* Invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, Operands, 2);
        goto Cleanup;
    }

    DUMP_OPERANDS (Operands, IMODE_Execute, PsGetOpcodeName (Opcode), 2, "after AmlPrepOperands");

    ObjDesc2    = Operands[0];
    ObjDesc     = Operands[-1];


    /* Create the internal return object */

    RetDesc = CmCreateInternalObject (ACPI_TYPE_Number);
    if (!RetDesc)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    /*
     * Execute the Opcode
     */

    switch (Opcode)
    {

    /* DefLAnd :=  LAndOp  Operand1    Operand2    */

    case AML_LAndOp:
        
        Lboolean = (BOOLEAN) (ObjDesc->Number.Value && ObjDesc2->Number.Value);
        break;


    /* DefLEqual   :=  LEqualOp    Operand1    Operand2    */

    case AML_LEqualOp:

        Lboolean = (BOOLEAN) (ObjDesc->Number.Value == ObjDesc2->Number.Value);
        break;


    /* DefLGreater :=  LGreaterOp  Operand1    Operand2    */

    case AML_LGreaterOp:

        Lboolean = (BOOLEAN) (ObjDesc->Number.Value > ObjDesc2->Number.Value);
        break;


    /* DefLLess    :=  LLessOp Operand1    Operand2    */

    case AML_LLessOp:

        Lboolean = (BOOLEAN) (ObjDesc->Number.Value < ObjDesc2->Number.Value);
        break;


    /* DefLOr  :=  LOrOp   Operand1    Operand2    */

    case AML_LOrOp:

        Lboolean = (BOOLEAN) (ObjDesc->Number.Value || ObjDesc2->Number.Value);
        break;
    

    default:

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2: Unknown dyadic opcode %02x\n", Opcode));
        Status = AE_AML_BAD_OPCODE;
        goto Cleanup;
        break;
    }


    /* Set return value to logical TRUE (all ones) or FALSE (zero) */  
    
    if (Lboolean)
    {
        RetDesc->Number.Value = 0xffffffff;
    }
    else
    {
        RetDesc->Number.Value = 0;
    }


Cleanup:

    /* Always delete operands */

    CmDeleteOperand (&Operands[0]);
    CmDeleteOperand (&Operands[-1]);

 
    /* Delete return object on error */

    if (ACPI_FAILURE (Status) &&
        (RetDesc))
    {
        CmDeleteInternalObject (RetDesc);
        RetDesc = NULL;
    }


    /* Set the return object and exit */

    *ReturnDesc = RetDesc;
    return_ACPI_STATUS (Status);
}


