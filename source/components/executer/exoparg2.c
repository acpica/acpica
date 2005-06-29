
/******************************************************************************
 * 
 * Module Name: iedyadic - ACPI AML (p-code) execution for dyadic operators
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
 * 2.1. Intel grants, free of charge, to any person ("Licensee") obtaining a 
 * copy of the source code appearing in this file ("Covered Code") a license 
 * under Intel's copyrights in the base code distributed originally by Intel 
 * ("Original Intel Code") to copy, make derivatives, distribute, use and 
 * display any portion of the Covered Code in any form; and
 *
 * 2.2. Intel grants Licensee a non-exclusive and non-transferable patent 
 * license (without the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell, 
 * offer to sell, and import the Covered Code and derivative works thereof 
 * solely to the minimum extent necessary to exercise the above copyright 
 * license, and in no event shall the patent license extend to any additions to
 * or modifications of the Original Intel Code.  No other license or right is 
 * granted directly or by implication, estoppel or otherwise;
 *
 * the above copyright and patent license is granted only if the following 
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of source code of any substantial portion of the Covered 
 * Code or modification must include the above Copyright Notice, the above 
 * License, this list of Conditions, and the following Disclaimer and Export 
 * Compliance provision.  In addition, Licensee must cause all Covered Code to 
 * which Licensee contributes to contain a file documenting the changes 
 * Licensee made to create that Covered Code and the date of any change.  
 * Licensee must include in that file the documentation of any changes made by
 * any predecessor Licensee.  Licensee must include a prominent statement that
 * the modification is derived, directly or indirectly, from Original Intel 
 * Code.
 *
 * 3.2. Redistribution in binary form of any substantial portion of the Covered 
 * Code or modification must reproduce the above Copyright Notice, and the 
 * following Disclaimer and Export Compliance provision in the documentation 
 * and/or other materials provided with the distribution.
 *
 * 3.3. Intel retains all right, title, and interest in and to the Original 
 * Intel Code.
 *
 * 3.4. Neither the name Intel nor any other trademark owned or controlled by 
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
 * event Licensee exports any such software from the United States or re-
 * exports any such software from a foreign destination, Licensee shall ensure
 * that the distribution and export/re-export of the software is in compliance 
 * with all laws, regulations, orders, or other restrictions of the U.S. Export 
 * Administration Regulations. Licensee agrees that neither it nor any of its 
 * subsidiaries will export/re-export any technical data, process, software, or 
 * service, directly or indirectly, to any country for which the United States 
 * government or any agency thereof requires an export license, other 
 * governmental approval, or letter of assurance, without first obtaining such
 * license, approval or letter.
 *
 *****************************************************************************/


#define __IEDYADIC_C__

#include <acpi.h>
#include <interpreter.h>
#include <events.h>
#include <amlcode.h>
#include <string.h>


#define _THIS_MODULE        "iedyadic.c"
#define _COMPONENT          INTERPRETER


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", '1', "AmlExecDyadic2R: Descriptor Allocation Failure", "AmlExecDyadic2R: Descriptor Allocation Failure"},
    {"0001", '1', "AmlExecDyadic2R/ConcatOp: String allocation failure", "AmlExecDyadic2R/ConcatOp: String allocation failure"},
    {"0002", '1', "AmlExecDyadic2R/ConcatOp: Buffer allocation failure", "AmlExecDyadic2R/ConcatOp: Buffer allocation failure"},
    {NULL, 'I', NULL, NULL}
};



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
AmlExecDyadic1 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc = NULL;
    OBJECT_DESCRIPTOR       *ValDesc = NULL;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecDyadic1");


    Status = AmlPrepStack ("nl");

    if (Status != AE_OK)
    {
        /* Invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
        FUNCTION_EXIT;
        return Status;
    }

    AmlDumpStack (MODE_Exec, ShortOps[opcode], 2, "after AmlPrepStack");

    ValDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    switch (opcode)
    {


    /*  DefNotify   :=  NotifyOp    NotifyObject    NotifyValue */

    case AML_NotifyOp:

        /* Object must be a device or thermal zone */

        if (ObjDesc && ValDesc)
        {
            switch (ObjDesc->ValType)
            {
            case TYPE_Device:
            case TYPE_Thermal:
            
                /* Requires that Device and ThermalZone be compatible mappings */

                /* Dispatch the notify to the appropriate handler */

                EvNotifyDispatch (ObjDesc->Device.Device, ValDesc->Number.Number);
                break;

            default:
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecDyadic1/NotifyOp: unexpected notify object type %d\n",
                        ObjDesc->ValType));
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }
        }
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic1: Unknown dyadic opcode %02x\n", opcode));
        FUNCTION_EXIT;
        return AE_AML_ERROR;
    }

    if (ValDesc)
    {
        OsdFree (ValDesc);
    }

    if (ObjDesc)
    {
        OsdFree (ObjDesc);
    }
    
    ObjStack[--ObjStackTop] = NULL;

    FUNCTION_EXIT;
    return AE_OK;
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
AmlExecDyadic2R (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc = NULL;
    OBJECT_DESCRIPTOR       *ObjDesc2 = NULL;
    OBJECT_DESCRIPTOR       *ResDesc = NULL;
    OBJECT_DESCRIPTOR       *ResDesc2 = NULL;
    ACPI_STATUS             Status;
    UINT32                  remain;
    INT32                   NumOperands;


    FUNCTION_TRACE ("AmlExecDyadic2R");


    switch (opcode)
    {


    /*  DefConcat   :=  ConcatOp    Data1   Data2   Result  */

    case AML_ConcatOp:
        Status = AmlPrepStack ("lss");
        NumOperands = 3;
        break;


    /*  DefDivide   :=  DivideOp Dividend Divisor Remainder Quotient    */

    case AML_DivideOp:
        Status = AmlPrepStack ("llnn");
        NumOperands = 4;
        break;


    /*  DefX    :=  XOp Operand1    Operand2    Result  */

    default:
        Status = AmlPrepStack ("lnn");
        NumOperands = 3;
        break;
    }

    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, NumOperands);
        FUNCTION_EXIT;
        return Status;
    }

    AmlDumpStack (MODE_Exec, ShortOps[opcode], NumOperands, "after AmlPrepStack");

    if (AML_DivideOp == opcode)
    {
        ResDesc2 = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];
    }

    ResDesc     = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];
    ObjDesc2    = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];
    ObjDesc     = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjStackTop += NumOperands - 1;

    switch (opcode)
    {


    /*  DefAdd  :=  AddOp   Operand1    Operand2    Result  */

    case AML_AddOp:
        ObjDesc->Number.Number += ObjDesc2->Number.Number;
        break;
 
        
    /*  DefAnd  :=  AndOp   Operand1    Operand2    Result  */

    case AML_BitAndOp:
        ObjDesc->Number.Number &= ObjDesc2->Number.Number;
        break;

        
    /*  DefNAnd :=  NAndOp  Operand1    Operand2    Result  */

    case AML_BitNandOp:
        ObjDesc->Number.Number = ~(ObjDesc->Number.Number & ObjDesc2->Number.Number);
        break;
   
       
    /*  DefOr       :=  OrOp    Operand1    Operand2    Result  */
        
    case AML_BitOrOp:
        ObjDesc->Number.Number |= ObjDesc2->Number.Number;
        break;

        
    /*  DefNOr  :=  NOrOp   Operand1    Operand2    Result  */

    case AML_BitNorOp:
        ObjDesc->Number.Number = ~(ObjDesc->Number.Number | ObjDesc2->Number.Number);
        break;

        
    /*  DefXOr  :=  XOrOp   Operand1    Operand2    Result  */

    case AML_BitXorOp:
        ObjDesc->Number.Number ^= ObjDesc2->Number.Number;
        break;

        
    /*  DefDivide   :=  DivideOp Dividend Divisor Remainder Quotient    */

    case AML_DivideOp:
        if ((UINT32) 0 == ObjDesc2->Number.Number)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2R/DivideOp: divide by zero\n"));
            FUNCTION_EXIT;
            return AE_AML_ERROR;
        }

        remain = ObjDesc->Number.Number % ObjDesc2->Number.Number;
        ObjDesc->Number.Number /= ObjDesc2->Number.Number;
        ObjDesc2->Number.Number = remain;
        break;

        
    /*  DefMultiply :=  MultiplyOp  Operand1    Operand2    Result  */

    case AML_MultiplyOp:
        ObjDesc->Number.Number *= ObjDesc2->Number.Number;
        break;

        
    /*  DefShiftLeft    :=  ShiftLeftOp Operand ShiftCount  Result  */

    case AML_ShiftLeftOp:
        ObjDesc->Number.Number <<= ObjDesc2->Number.Number;
        break;

        
    /*  DefShiftRight   :=  ShiftRightOp    Operand ShiftCount  Result  */

    case AML_ShiftRightOp:
        ObjDesc->Number.Number >>= ObjDesc2->Number.Number;
        break;

        
    /*  DefSubtract :=  SubtractOp  Operand1    Operand2    Result  */

    case AML_SubtractOp:
        ObjDesc->Number.Number -= ObjDesc2->Number.Number;
        break;


    /*  DefConcat   :=  ConcatOp    Data1   Data2   Result  */

    case AML_ConcatOp:
        if (ObjDesc2->ValType != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecDyadic2R/ConcatOp: operand type mismatch %d %d\n",
                    ObjDesc->ValType, ObjDesc2->ValType));
            FUNCTION_EXIT;
            return AE_AML_ERROR;
        }

        /* Both operands are now known to be the same */
        
        if (TYPE_String == ObjDesc->ValType)
        {
            /*  Operand1 is string  */

            char *NewBuf = OsdAllocate ((size_t) (ObjDesc->String.StrLen
                                                + ObjDesc2->String.StrLen + 1));
            if (!NewBuf)
            {
                REPORT_ERROR (&KDT[1]);
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }
            
            strcpy (NewBuf, (char *) ObjDesc->String.String);
            strcpy (NewBuf + ObjDesc->String.StrLen,
                     (char *) ObjDesc2->String.String);
            
            /* Don't free old ObjDesc->String.String; the operand still exists */
            
            ObjDesc->String.String = (UINT8 *) NewBuf;
            ObjDesc->String.StrLen += ObjDesc2->String.StrLen;
        }
        
        else
        {
            /*  Operand1 is not string ==> buffer   */

            char *NewBuf = OsdAllocate ((size_t) (ObjDesc->Buffer.BufLen
                                                + ObjDesc2->Buffer.BufLen));
            if (!NewBuf)
            {
                /* Only bail out if the buffer is small */
                
                if (ObjDesc->Buffer.BufLen + ObjDesc2->Buffer.BufLen < 1024)
                {
                    REPORT_ERROR (&KDT[0]);
                    FUNCTION_EXIT;
                    return AE_AML_ERROR;
                }

                DEBUG_PRINT (ACPI_ERROR, (
                            "AmlExecDyadic2R/ConcatOp: Buffer allocation failure %d\n",
                            ObjDesc->Buffer.BufLen + ObjDesc2->Buffer.BufLen));
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            memcpy (NewBuf, ObjDesc->Buffer.Buffer, (size_t) ObjDesc->Buffer.BufLen);
            memcpy (NewBuf + ObjDesc->Buffer.BufLen, ObjDesc2->Buffer.Buffer,
                    (size_t) ObjDesc2->Buffer.BufLen);
            
            /* Don't free old ObjDesc->Buffer.Buffer; the operand still exists */
            
            ObjDesc->Buffer.Buffer = (UINT8 *) NewBuf;
            ObjDesc->Buffer.BufLen += ObjDesc2->Buffer.BufLen;
        }
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2R: Unknown dyadic opcode %02x\n", opcode));
        FUNCTION_EXIT;
        return AE_AML_ERROR;
    }
    
    if ((Status = AmlExecStore (ObjDesc, ResDesc)) != AE_OK)
    {
        ObjStackTop -= NumOperands - 1;
        FUNCTION_EXIT;
        return Status;
    }
    
    if (AML_DivideOp == opcode)
    {
        Status = AmlExecStore(ObjDesc2, ResDesc2);
    }

    /* Don't delete ObjDesc because it remains on the stack */
    /* deleting psObjDescOperand2 is valid for DivideOp since we preserved
     * remainder on stack
     */
    
    OsdFree (ObjDesc2);
    ObjStackTop -= NumOperands - 1;
    
    FUNCTION_EXIT;
    return Status;
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
AmlExecDyadic2S (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc = NULL;
    OBJECT_DESCRIPTOR       *TimeDesc = NULL;
    OBJECT_DESCRIPTOR       *ResDesc = NULL;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecDyadic2S");


    Status = AmlPrepStack ("nl");

    if (Status != AE_OK)
    {   
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
    }

    else
    {
        AmlDumpStack (MODE_Exec, LongOps[opcode & 0x00ff], 2, "after AmlPrepStack");

        TimeDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
        ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

        switch (opcode)
        {


        /*  DefAcquire  :=  AcquireOp   MutexObject Timeout */

        case AML_AcquireOp:
            if (TYPE_Mutex != ObjDesc->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecDyadic2S/AcquireOp: Needed Mutex, found %d\n",
                        ResDesc->ValType));
                Status = AE_AML_ERROR;
            }
            else
            {
                Status = OsAcquireOpRqst (TimeDesc, ObjDesc);
            }



        /*  DefWait :=  WaitOp  EventObject Timeout */

        case AML_WaitOp:
            if (TYPE_Event != ObjDesc->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecDyadic2S/WaitOp: Needed Event, found %d\n",
                        ResDesc->ValType));
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

        /*  delete TimeOut object descriptor before removing it from object stack   */
    
        OsdFree (TimeDesc);

        /*  remove TimeOut parameter from object stack  */

        ObjStackTop--;
    
    }

    FUNCTION_EXIT;
    return Status;
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
AmlExecDyadic2 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ObjDesc2;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecDyadic2");


    Status = AmlPrepStack ("nn");

    if (Status != AE_OK)
    {
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
        FUNCTION_EXIT;
        return Status;
    }

    AmlDumpStack (MODE_Exec, ShortOps[opcode], 2, "after AmlPrepStack");

    ObjDesc2 = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    Status = AE_OK;      /* Make sure AE_OK */
    switch (opcode)
    {


    /*  DefLAnd :=  LAndOp  Operand1    Operand2    */

    case AML_LAndOp:
        if (ObjDesc->Number.Number && ObjDesc2->Number.Number)
        {
            Status = AE_PENDING;
        }
        break;


    /*  DefLEqual   :=  LEqualOp    Operand1    Operand2    */

    case AML_LEqualOp:
        if (ObjDesc->Number.Number == ObjDesc2->Number.Number)
        {
            Status = AE_PENDING;
        }
        break;


    /*  DefLGreater :=  LGreaterOp  Operand1    Operand2    */

    case AML_LGreaterOp:
        if (ObjDesc->Number.Number > ObjDesc2->Number.Number)
        {
            Status = AE_PENDING;
        }
        break;


    /*  DefLLess    :=  LLessOp Operand1    Operand2    */

    case AML_LLessOp:
        if (ObjDesc->Number.Number < ObjDesc2->Number.Number)
        {
            Status = AE_PENDING;
        }
        break;


    /*  DefLOr  :=  LOrOp   Operand1    Operand2    */

    case AML_LOrOp:
        if (ObjDesc->Number.Number || ObjDesc2->Number.Number)
        {
            Status = AE_PENDING;
        }
        break;
    
    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2: Unknown dyadic opcode %02x\n", opcode));
        FUNCTION_EXIT;
        return AE_AML_ERROR;
    }

    /* ObjDesc->ValType == Number was assured by AmlPrepStack("nn") call */
    
    if (Status == AE_PENDING)
    {
        ObjDesc->Number.Number = 0xffffffff;
    }
    else
    {
        ObjDesc->Number.Number = 0;
    }

    OsdFree (ObjDesc2);
    ObjStackTop--;
    
    FUNCTION_EXIT;
    return AE_OK;
}


