
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
#include <namespace.h>
#include <interpreter.h>
#include <events.h>
#include <amlcode.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("iedyad");


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic1
 *
 * PARAMETERS:  opcode              - The opcode to be executed
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
    UINT16                  opcode)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    ACPI_OBJECT_INTERNAL    *ValDesc = NULL;
    NAME_TABLE_ENTRY        *Entry;
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("AmlExecDyadic1");


    Status = AmlPrepObjStack ("nl");

    if (Status != AE_OK)
    {
        /* Invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
        return_ACPI_STATUS (Status);
    }

    AmlDumpObjStack (IMODE_Execute, Gbl_ShortOps[opcode], 2, "after AmlPrepObjStack");

    ValDesc = AmlObjStackGetValue (STACK_TOP);
    ObjDesc = AmlObjStackGetValue (1);


    /* Examine the opcode */

    switch (opcode)
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
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecDyadic1/NotifyOp: unexpected notify object type %d\n",
                        ObjDesc->Common.Type));
                
                Status = AE_AML_ERROR;
            }
        }
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic1: Unknown dyadic opcode %02x\n", opcode));
        Status = AE_AML_ERROR;
    }


    /* Delete the stack items */

    if (ValDesc)
    {
        CmDeleteInternalObject (ValDesc);
    }

    if (ObjDesc)
    {
        CmDeleteInternalObject (ObjDesc);
    }
    
    /* Clear the stack */

    AmlObjStackPop (1);
    AmlObjStackClearTop ();

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic2R
 *
 * PARAMETERS:  opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 dyadic operator with numeric operands and
 *              one or two result operands
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecDyadic2R (
    UINT16                  opcode)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    ACPI_OBJECT_INTERNAL    *ObjDesc2 = NULL;
    ACPI_OBJECT_INTERNAL    *ResDesc = NULL;
    ACPI_OBJECT_INTERNAL    *ResDesc2 = NULL;
    ACPI_STATUS             Status;
    UINT32                  remain;
    UINT32                  StackIndex;
    INT32                   NumOperands;
    char                    *NewBuf;


    FUNCTION_TRACE ("AmlExecDyadic2R");


    /* Examine the opcode */

    switch (opcode)
    {

    /* DefConcat   :=  ConcatOp    Data1   Data2   Result  */

    case AML_ConcatOp:

        Status = AmlPrepObjStack ("lss");
        NumOperands = 3;
        break;


    /* DefDivide   :=  DivideOp Dividend Divisor Remainder Quotient    */

    case AML_DivideOp:

        Status = AmlPrepObjStack ("llnn");
        NumOperands = 4;
        break;


    /* DefX    :=  XOp Operand1    Operand2    Result  */

    default:

        Status = AmlPrepObjStack ("lnn");
        NumOperands = 3;
        break;
    }


    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, NumOperands);
        goto Cleanup;
    }

    AmlDumpObjStack (IMODE_Execute, Gbl_ShortOps[opcode], NumOperands, "after AmlPrepObjStack");


    /* Get all operand and result objects from the stack */

    StackIndex = 0;
    if (AML_DivideOp == opcode)
    {
        ResDesc2 = AmlObjStackGetValue (StackIndex++);
    }

    ResDesc     = AmlObjStackGetValue (StackIndex++);
    ObjDesc2    = AmlObjStackGetValue (StackIndex++);
    ObjDesc     = AmlObjStackGetValue (StackIndex);


    /* 
     * Execute the opcode 
     */

    switch (opcode)
    {

    /* DefAdd  :=  AddOp   Operand1    Operand2    Result  */

    case AML_AddOp:
        ObjDesc->Number.Value += ObjDesc2->Number.Value;
        break;
 
        
    /* DefAnd  :=  AndOp   Operand1    Operand2    Result  */

    case AML_BitAndOp:
        ObjDesc->Number.Value &= ObjDesc2->Number.Value;
        break;

        
    /* DefNAnd :=  NAndOp  Operand1    Operand2    Result  */

    case AML_BitNandOp:
        ObjDesc->Number.Value = ~(ObjDesc->Number.Value & ObjDesc2->Number.Value);
        break;
   
       
    /* DefOr       :=  OrOp    Operand1    Operand2    Result  */
        
    case AML_BitOrOp:
        ObjDesc->Number.Value |= ObjDesc2->Number.Value;
        break;

        
    /* DefNOr  :=  NOrOp   Operand1    Operand2    Result  */

    case AML_BitNorOp:
        ObjDesc->Number.Value = ~(ObjDesc->Number.Value | ObjDesc2->Number.Value);
        break;

        
    /* DefXOr  :=  XOrOp   Operand1    Operand2    Result  */

    case AML_BitXorOp:
        ObjDesc->Number.Value ^= ObjDesc2->Number.Value;
        break;

        
    /* DefDivide   :=  DivideOp Dividend Divisor Remainder Quotient    */

    case AML_DivideOp:
        if ((UINT32) 0 == ObjDesc2->Number.Value)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2R/DivideOp: divide by zero\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        remain = ObjDesc->Number.Value % ObjDesc2->Number.Value;
        ObjDesc->Number.Value /= ObjDesc2->Number.Value;
        ObjDesc2->Number.Value = remain;
        break;

        
    /* DefMultiply :=  MultiplyOp  Operand1    Operand2    Result  */

    case AML_MultiplyOp:
        ObjDesc->Number.Value *= ObjDesc2->Number.Value;
        break;

        
    /* DefShiftLeft    :=  ShiftLeftOp Operand ShiftCount  Result  */

    case AML_ShiftLeftOp:
        ObjDesc->Number.Value <<= ObjDesc2->Number.Value;
        break;

        
    /* DefShiftRight   :=  ShiftRightOp    Operand ShiftCount  Result  */

    case AML_ShiftRightOp:
        ObjDesc->Number.Value >>= ObjDesc2->Number.Value;
        break;

        
    /* DefSubtract :=  SubtractOp  Operand1    Operand2    Result  */

    case AML_SubtractOp:
        ObjDesc->Number.Value -= ObjDesc2->Number.Value;
        break;


    /* DefConcat   :=  ConcatOp    Data1   Data2   Result  */

    case AML_ConcatOp:
        if (ObjDesc2->Common.Type != ObjDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecDyadic2R/ConcatOp: operand type mismatch %d %d\n",
                    ObjDesc->Common.Type, ObjDesc2->Common.Type));
            Status = AE_AML_ERROR;
            goto Cleanup;
        }

        /* Both operands are now known to be the same */
        
        if (ACPI_TYPE_String == ObjDesc->Common.Type)
        {
            /* Operand1 is string  */

            NewBuf = CmAllocate ((ACPI_SIZE) (ObjDesc->String.Length
                                                + ObjDesc2->String.Length + 1));
            if (!NewBuf)
            {
                REPORT_ERROR ("AmlExecDyadic2R/ConcatOp: String allocation failure");
                Status = AE_AML_ERROR;
                goto Cleanup;
            }
            
            STRCPY (NewBuf, (char *) ObjDesc->String.Pointer);
            STRCPY (NewBuf + ObjDesc->String.Length,
                     (char *) ObjDesc2->String.Pointer);
            
            /* Don't free old ObjDesc->String.Pointer; the operand still exists */
            
            ObjDesc->String.Pointer = (UINT8 *) NewBuf;
            ObjDesc->String.Length += ObjDesc2->String.Length;
        }
        
        else
        {
            /* Operand1 is not string ==> buffer   */

            NewBuf = CmAllocate ((ACPI_SIZE) (ObjDesc->Buffer.Length
                                                + ObjDesc2->Buffer.Length));
            if (!NewBuf)
            {
                /* Only bail out if the buffer is small */
                
                if (ObjDesc->Buffer.Length + ObjDesc2->Buffer.Length < 1024)
                {
                    REPORT_ERROR ("AmlExecDyadic2R/ConcatOp: Buffer allocation failure");
                    return_ACPI_STATUS (AE_AML_ERROR);
                }

                DEBUG_PRINT (ACPI_ERROR, (
                            "AmlExecDyadic2R/ConcatOp: Buffer allocation failure %d\n",
                            ObjDesc->Buffer.Length + ObjDesc2->Buffer.Length));
                Status = AE_AML_ERROR;
                goto Cleanup;
            }

            MEMCPY (NewBuf, ObjDesc->Buffer.Pointer, 
                            (ACPI_SIZE) ObjDesc->Buffer.Length);
            MEMCPY (NewBuf + ObjDesc->Buffer.Length, ObjDesc2->Buffer.Pointer,
                            (ACPI_SIZE) ObjDesc2->Buffer.Length);
            
            /*
             * Don't free old ObjDesc->Buffer.Pointer; the operand still exists 
             * Buffer.PtrRefCount remains the same! 
             */
            
            ObjDesc->Buffer.Pointer     = (UINT8 *) NewBuf;
            ObjDesc->Buffer.Length      += ObjDesc2->Buffer.Length;
        }
        break;


    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2R: Unknown dyadic opcode %02x\n", opcode));
        Status = AE_AML_ERROR;
        goto Cleanup;
    }

    
    /*
     * Store the result of the operation (which is now in ObjDesc) into
     * the result descriptor, or the location pointerd to by the result
     * descriptor (ResDesc).
     */

    if ((Status = AmlExecStore (ObjDesc, ResDesc)) != AE_OK)
    {
        goto Cleanup;
    }
    
    if (AML_DivideOp == opcode)
    {
        Status = AmlExecStore(ObjDesc2, ResDesc2);
    }


Cleanup:

    /*
     * Don't delete ObjDesc because it will remain on the stack.
     * Deleting ObjDesc2 is valid for DivideOp since we preserved
     * the remainder on the stack
     */
    
    CmDeleteInternalObject (ObjDesc2);
    AmlObjStackPop (NumOperands - 1);
    
    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic2S
 *
 * PARAMETERS:  opcode              - The opcode to be executed
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
    UINT16                  opcode)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    ACPI_OBJECT_INTERNAL    *TimeDesc = NULL;
    ACPI_OBJECT_INTERNAL    *ResDesc = NULL;
    NAME_TABLE_ENTRY        *ThisEntry;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecDyadic2S");


    Status = AmlPrepObjStack ("nl");
    if (Status != AE_OK)
    {   
        /* Invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
        return_ACPI_STATUS (Status);
    }


    /* Get the operands and validate them */

    AmlDumpObjStack (IMODE_Execute, Gbl_LongOps[opcode & 0x00ff], 2, "after AmlPrepObjStack");

    TimeDesc = AmlObjStackGetValue (STACK_TOP);
    ObjDesc = AmlObjStackGetValue (1);

    if (!TimeDesc || !ObjDesc)
    {
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    /* ObjDesc can be an NTE */

    if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))
    {
        ThisEntry = (NAME_TABLE_ENTRY *) ObjDesc;
        if (!ThisEntry->Object)
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

            ThisEntry->Object = ObjDesc;
            ThisEntry->Type = ACPI_TYPE_Mutex;
        }

        /* Extract the valid object */

        ObjDesc = ThisEntry->Object;
    }


    /* Examine the opcode */

    switch (opcode)
    {

    /* DefAcquire  :=  AcquireOp   MutexObject Timeout */

    case AML_AcquireOp:

        if (ACPI_TYPE_Mutex != ObjDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecDyadic2S/AcquireOp: Needed Mutex, found %d\n",
                    ResDesc->Common.Type));
            Status = AE_AML_ERROR;
        }
        else
        {
            Status = OsAcquireOpRqst (TimeDesc, ObjDesc);
        }



    /* DefWait :=  WaitOp  EventObject Timeout */

    case AML_WaitOp:

        if (ACPI_TYPE_Event != ObjDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecDyadic2S/WaitOp: Needed Event, found %d\n",
                    ResDesc->Common.Type));
            Status = AE_AML_ERROR;
        }
        else
        {
            Status = OsWaitOpRqst (TimeDesc, ObjDesc);
        }


    default:

        DEBUG_PRINT (ACPI_ERROR, (
                "AmlExecDyadic2S: Unknown dyadic synchronization opcode %02x\n",
                opcode));
        Status = AE_AML_ERROR;
    }



Cleanup:

    /* Delete TimeOut object descriptor before removing it from object stack   */

    CmDeleteInternalObject (TimeDesc);

    /* Remove TimeOut parameter from object stack  */

    AmlObjStackPop (1);
    
    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic2
 *
 * PARAMETERS:  opcode              - The opcode to be executed
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
    UINT16                  opcode)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *ObjDesc2;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecDyadic2");


    Status = AmlPrepObjStack ("nn");

    if (Status != AE_OK)
    {
        /* Invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
        return_ACPI_STATUS (Status);
    }

    AmlDumpObjStack (IMODE_Execute, Gbl_ShortOps[opcode], 2, "after AmlPrepObjStack");

    ObjDesc2 = AmlObjStackGetValue (STACK_TOP);
    ObjDesc = AmlObjStackGetValue (1);


    /*
     * Execute the opcode
     */

    switch (opcode)
    {

    /* DefLAnd :=  LAndOp  Operand1    Operand2    */

    case AML_LAndOp:
        if (ObjDesc->Number.Value && ObjDesc2->Number.Value)
        {
            Status = AE_PENDING;
        }
        break;


    /* DefLEqual   :=  LEqualOp    Operand1    Operand2    */

    case AML_LEqualOp:
        if (ObjDesc->Number.Value == ObjDesc2->Number.Value)
        {
            Status = AE_PENDING;
        }
        break;


    /* DefLGreater :=  LGreaterOp  Operand1    Operand2    */

    case AML_LGreaterOp:
        if (ObjDesc->Number.Value > ObjDesc2->Number.Value)
        {
            Status = AE_PENDING;
        }
        break;


    /* DefLLess    :=  LLessOp Operand1    Operand2    */

    case AML_LLessOp:
        if (ObjDesc->Number.Value < ObjDesc2->Number.Value)
        {
            Status = AE_PENDING;
        }
        break;


    /* DefLOr  :=  LOrOp   Operand1    Operand2    */

    case AML_LOrOp:
        if (ObjDesc->Number.Value || ObjDesc2->Number.Value)
        {
            Status = AE_PENDING;
        }
        break;
    
    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2: Unknown dyadic opcode %02x\n", opcode));
        return_ACPI_STATUS (AE_AML_ERROR);
    }


    /* ObjDesc->Type == Number was assured by AmlPrepObjStack("nn") call */
    
    if (Status == AE_PENDING)
    {
        ObjDesc->Number.Value = 0xffffffff;
    }
    else
    {
        ObjDesc->Number.Value = 0;
    }


    /* Free operand2 object and remove it from the stack */

    CmDeleteInternalObject (ObjDesc2);
    AmlObjStackPop (1);
 
    /* Always return AE_OK here (AE_PENDING was handled above!) */

    return_ACPI_STATUS (AE_OK);
}


