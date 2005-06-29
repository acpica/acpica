
/******************************************************************************
 * 
 * Module Name: iemonadic - ACPI AML (p-code) execution for monadic operators
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


#define __IEMONADIC_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>


#define _THIS_MODULE        "iemonadic.c"
#define _COMPONENT          INTERPRETER



/*****************************************************************************
 * 
 * FUNCTION:    AmlExecMonadic1
 *
 * PARAMETERS:  opcode              - The opcode to be executed
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
    UINT16                  opcode)
{
    ACPI_OBJECT             *ObjDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecMonadic1");


    if (AML_SleepOp == opcode || AML_StallOp == opcode)
    {
        Status = AmlPrepStack ("n");                 /* operand should be a Number */
    }
    else
    {
        Status = AmlPrepStack ("l");                 /* operand should be an Lvalue */
    }

    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 1);
        FUNCTION_STATUS_EXIT (Status);
        return Status;
    }


    AmlDumpStack (MODE_Exec, LongOps[opcode & 0x00ff], 1, "after AmlPrepStack");

    ObjDesc = (ACPI_OBJECT *) ObjStack[ObjStackTop];

    switch (opcode)
    {

    /*  DefRelease  :=  ReleaseOp   MutexObject */

    case AML_ReleaseOp:
        if (TYPE_Mutex != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic1/ReleaseOp: Needed Mutex, found %d\n",
                    ObjDesc->ValType));
            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
        }

        Status = OsReleaseOpRqst (ObjDesc);
        FUNCTION_STATUS_EXIT (Status);
        return Status;


    /*  DefReset        :=  ResetOp     EventObject */

    case AML_ResetOp:
        if (TYPE_Event != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic1/ResetOp: Needed Event, found %d\n", ObjDesc->ValType));
            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
        }

        Status = OsResetOpRqst (ObjDesc);
        FUNCTION_STATUS_EXIT (Status);
        return Status;


    /*  DefSignal   :=  SignalOp        EventObject */
    
    case AML_SignalOp:
        if (TYPE_Event != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic1/SignalOp: Needed Event, found %d\n", ObjDesc->ValType));
            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
        }

        Status = OsSignalOpRqst (ObjDesc);
        FUNCTION_STATUS_EXIT (Status);
        return Status;


    /*  DefSleep    :=  SleepOp MsecTime    */
    
    case AML_SleepOp:
        OsDoSuspend (ObjDesc->Number.Number);
        break;


    /*  DefStall    :=  StallOp UsecTime    */
    
    case AML_StallOp:
        OsdSleepUsec (ObjDesc->Number.Number);
        break;


    /*  unknown opcode  */
    
    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic1: Unknown monadic opcode %02x\n", opcode));
        FUNCTION_STATUS_EXIT (AE_AML_ERROR);
        return AE_AML_ERROR;
    
    } /* switch */


    OsdFree (ObjDesc);
    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecMonadic2R
 *
 * PARAMETERS:  opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 monadic operator with numeric operand and
 *              result operand on operand stack
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecMonadic2R (
    UINT16                  opcode)
{
    ACPI_OBJECT             *ObjDesc;
    ACPI_OBJECT             *ResDesc;
    UINT32                  ResVal;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecMonadic2R");


    Status = AmlPrepStack ("ln");

    if (Status != AE_OK)
    {
        /* Invalid parameters on object stack   */
        /* This was added since it is allowable to return a buffer so */
        /* ln is a local and a number and that will fail.  lb is a local */
        /* and a buffer which will pass.  */
        
        Status = AmlPrepStack ("lb");

        if (Status != AE_OK)
        {
            AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
            FUNCTION_STATUS_EXIT (Status);
            return Status;
        }
    }

    AmlDumpStack (MODE_Exec, ShortOps[opcode], 2, "after AmlPrepStack");

    ResDesc = (ACPI_OBJECT *) ObjStack[ObjStackTop];
    ObjDesc = (ACPI_OBJECT *) ObjStack[ObjStackTop - 1];

    switch (opcode)
    {
        INT32           d0, d1, d2, d3;


    /*  DefNot  :=  NotOp   Operand Result  */
    
    case AML_BitNotOp:
        ObjDesc->Number.Number = ~ObjDesc->Number.Number;
        break;


    /*  DefFindSetLeftBit   :=  FindSetLeftBitOp    Operand Result  */

    case AML_FindSetLeftBitOp:
        for (ResVal = 0; ObjDesc->Number.Number && ResVal < 33; ++ResVal)
        {
            ObjDesc->Number.Number >>= 1;
        }

        ObjDesc->Number.Number = ResVal;
        break;


    /*  DefFindSetRightBit  :=  FindSetRightBitOp   Operand Result  */

    case AML_FindSetRightBitOp:
        for (ResVal = 0; ObjDesc->Number.Number && ResVal < 33; ++ResVal)
        {
            ObjDesc->Number.Number <<= 1;
        }

        ObjDesc->Number.Number = ResVal == 0 ? 0 : 33 - ResVal;
        break;


    /*  DefFromBDC  :=  FromBCDOp   BCDValue    Result  */

    case AML_FromBCDOp:
        d0 = (INT32) (ObjDesc->Number.Number & 15);
        d1 = (INT32) (ObjDesc->Number.Number >> 4 & 15);
        d2 = (INT32) (ObjDesc->Number.Number >> 8 & 15);
        d3 = (INT32) (ObjDesc->Number.Number >> 12 & 15);
        
        if (d0 > 9 || d1 > 9 || d2 > 9 || d3 > 9)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic2R/FromBCDOp: improper BCD digit %d %d %d %d\n",
                    d3, d2, d1, d0));
            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
        }
        
        ObjDesc->Number.Number = d0 + d1 * 10 + d2 * 100 + d3 * 1000;
        break;


    /*  DefToBDC    :=  ToBCDOp Operand Result  */
    
    case AML_ToBCDOp:
        if (ObjDesc->Number.Number > 9999)
        {
            DEBUG_PRINT (ACPI_ERROR, ("iExecMonadic2R/ToBCDOp: BCD overflow: %d\n",
                    ObjDesc->Number.Number));
            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
        }
        
        ObjDesc->Number.Number
            = ObjDesc->Number.Number % 10
            + (ObjDesc->Number.Number / 10 % 10 << 4)
            + (ObjDesc->Number.Number / 100 % 10 << 8)
            + (ObjDesc->Number.Number / 1000 % 10 << 12);
        
        break;


    /*  DefShiftLeftBit     :=  ShiftLeftBitOp      Source          BitNum  */
    /*  DefShiftRightBit    :=  ShiftRightBitOp     Source          BitNum  */
    /*  DefCondRefOf        :=  CondRefOfOp         SourceObject    Result  */

    case AML_ShiftLeftBitOp:
    case AML_ShiftRightBitOp:
    case AML_CondRefOfOp:
        
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2R: %s unimplemented\n",
                (opcode > ACPI_UCHAR_MAX) ? LongOps[opcode & 0x00ff] : ShortOps[opcode]));
        FUNCTION_STATUS_EXIT (AE_AML_ERROR);
        return AE_AML_ERROR;

    case AML_StoreOp:
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2R: internal error: Unknown monadic opcode %02x\n",
                    opcode));
        FUNCTION_STATUS_EXIT (AE_AML_ERROR);
        return AE_AML_ERROR;
    }
    
    Status = AmlExecStore (ObjDesc, ResDesc);
    ObjStackTop--;

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecMonadic2
 *
 * PARAMETERS:  opcode              - The opcode to be executed
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
    UINT16                  opcode)
{
    ACPI_OBJECT             *ObjDesc;
    ACPI_OBJECT             *ResDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecMonadic2");


    if (AML_LNotOp == opcode)
    {
        Status = AmlPrepStack ("n");
    }
    else
    {
        Status = AmlPrepStack ("l");
    }

    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 1);
        FUNCTION_STATUS_EXIT (Status);
        return Status;
    }

    AmlDumpStack (MODE_Exec, ShortOps[opcode], 1, "after AmlPrepStack");

    ObjDesc = (ACPI_OBJECT *) ObjStack[ObjStackTop];


    switch (opcode)
    {

    /*  DefLNot :=  LNotOp  Operand */

    case AML_LNotOp:
        ObjDesc->Number.Number = (!ObjDesc->Number.Number) - (UINT32) 1;
        break;


    /*  DefDecrement    :=  DecrementOp Target  */
    /*  DefIncrement    :=  IncrementOp Target  */

    case AML_DecrementOp:
    case AML_IncrementOp:

        if ((Status = AmlPushIfExec (MODE_Exec)) != AE_OK)
        {
            REPORT_ERROR ("AmlExecMonadic2/IncDec: stack overflow");
            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
        }

        /* duplicate the Lvalue on TOS */
        
        ResDesc = AllocateObjectDesc ();
        if (ResDesc)
        {
            memcpy ((void *) ResDesc, (void *) ObjDesc, sizeof (*ObjDesc));
            
            /* push went into unused space, so no need to DeleteObject() */
            
            ObjStack[ObjStackTop] = (void *) ResDesc;
        }
        
        else
        {
            FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
            return AE_NO_MEMORY;
        }

        /* Convert the top copy to a Number */
        
        Status = AmlPrepStack ("n");
        if (Status != AE_OK)
        {
            AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 1);
            FUNCTION_STATUS_EXIT (Status);
            return Status;
        }

        /* get the Number in ObjDesc and the Lvalue in ResDesc */
        
        ObjDesc = (ACPI_OBJECT *) ObjStack[ObjStackTop];
        ResDesc = (ACPI_OBJECT *) ObjStack[ObjStackTop - 1];

        /* do the ++ or -- */
        
        if (AML_IncrementOp == opcode)
        {
            ObjDesc->Number.Number++;
        }
        else
        {
            ObjDesc->Number.Number--;
        }

        /* store result */
        
        LocalDeleteObject ((ACPI_OBJECT **) &ObjStack[ObjStackTop - 1]);
        ObjStack[ObjStackTop - 1] = (void *) ObjDesc;
        
        Status = AmlExecStore (ObjDesc, ResDesc);
        ObjStackTop--;

        FUNCTION_STATUS_EXIT (Status);
        return Status;



    /*  DefObjectType   :=  ObjectTypeOp    SourceObject    */

    case AML_TypeOp:
        
        /* This case uses Status to hold the type encoding */
        
        if (TYPE_Lvalue == ObjDesc->ValType)
        {
            /* 
             * Not a Name -- an indirect name pointer would have
             * been converted to a direct name pointer in AmlPrepStack
             */
            switch (ObjDesc->Lvalue.OpCode)
            {
            case AML_ZeroOp: case AML_OneOp: case AML_OnesOp:
                
                /* Constants are of type Number */
                
                Status = (INT32) TYPE_Number;
                break;

            case Debug1:
                
                /* Per spec, Debug object is of type Region */
                
                Status = (INT32) TYPE_Region;
                break;

            case AML_IndexOp:
                DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2/TypeOp: determining type of Index result is not implemented\n"));
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;

            case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
            case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:
                Status = (INT32) AmlGetMethodType (LCLBASE + ObjDesc->Lvalue.OpCode - AML_Local0);
                break;

            case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
            case AML_Arg4: case AML_Arg5: case AML_Arg6:
                Status = (INT32) AmlGetMethodType (ARGBASE + ObjDesc->Lvalue.OpCode - AML_Arg0);
                break;

            default:
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecMonadic2/TypeOp:internal error: Unknown Lvalue subtype %02x\n",
                        ObjDesc->Lvalue.OpCode));
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }
        }
        
        else
        {
            /* 
             * Since we passed AmlPrepStack("l") and it's not an Lvalue,
             * it must be a direct name pointer.  Allocate a descriptor
             * to hold the type.
             */
            Status = (INT32) NsGetType ((ACPI_HANDLE) ObjDesc);

            ObjDesc = AllocateObjectDesc ();
            if (!ObjDesc)
            {
                FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                return AE_NO_MEMORY;
            }

            /* 
             * Replace (ACPI_HANDLE) on TOS with descriptor containing result.
             * No need to LocalDeleteObject() first since TOS is an ACPI_HANDLE.
             */

            ObjStack[ObjStackTop] = (void *) ObjDesc;
        }
        
        ObjDesc->ValType = (UINT8) TYPE_Number;
        ObjDesc->Number.Number = (UINT32) Status;
        break;


    /*  DefSizeOf   :=  SizeOfOp    SourceObject    */

    case AML_SizeOfOp:
        switch (ObjDesc->ValType)
        {
        case TYPE_Buffer:
            ObjDesc->Number.Number = ObjDesc->Buffer.BufLen;
            ObjDesc->ValType = (UINT8) TYPE_Number;
            break;

        case TYPE_String:
            ObjDesc->Number.Number = ObjDesc->String.StrLen;
            ObjDesc->ValType = (UINT8) TYPE_Number;
            break;

        case TYPE_Package:
            ObjDesc->Number.Number = ObjDesc->Package.PkgCount;
            ObjDesc->ValType = (UINT8) TYPE_Number;
            break;

        default:
           DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic2: Needed aggregate, found %d\n", ObjDesc->ValType));
            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
        }
        break;


    /*  DefRefOf    :=  RefOfOp     SourceObject    */
    /*  DefDerefOf  :=  DerefOfOp   ObjReference    */

    case AML_RefOfOp:
    case AML_DerefOfOp:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2: %s unimplemented\n",
                (opcode > ACPI_UCHAR_MAX) ? LongOps[opcode & 0x00ff] : ShortOps[opcode]));
        ObjStackTop++;  /*  dummy return value  */

        FUNCTION_STATUS_EXIT (AE_AML_ERROR);
        return AE_AML_ERROR;

    default:
        DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic2:internal error: Unknown monadic opcode %02x\n",
                    opcode));
        
        FUNCTION_STATUS_EXIT (AE_AML_ERROR);
        return AE_AML_ERROR;
    }

    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
}


