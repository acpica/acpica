
/******************************************************************************
 * 
 * Module Name: ieprep - ACPI AML (p-code) execution - field prep utilities
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


#define __IEPREP_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>


#define _THIS_MODULE        "ieprep.c"
#define _COMPONENT          INTERPRETER




/*****************************************************************************
 * 
 * FUNCTION:    AmlPrepDefFieldValue
 *
 * PARAMETERS:  Region              - Region in which field is being defined
 *              FldFlg              - Access, LockRule, or UpdateRule.
 *                                    The format of a FieldFlag is described
 *                                    in the ACPI specification and in <aml.h>
 *              FldPos              - Field position
 *              FldLen              - Field length
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Construct an ACPI_OBJECT of type DefField and connect
 *              it to the nte whose handle is at ObjStack[ObjStackTop]
 *
 ****************************************************************************/

ACPI_STATUS
AmlPrepDefFieldValue (
    ACPI_HANDLE             Region, 
    UINT8                   FldFlg, 
    INT32                   FldPos, 
    INT32                   FldLen)
{
    ACPI_OBJECT             *ObjDesc = NULL;
    ACPI_STATUS             Status = AE_OK;
    INT32                   Type;


    FUNCTION_TRACE ("AmlPrepDefFieldValue");


    if (!Region)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepDefFieldValue: null Region\n"));
        Status = AE_AML_ERROR;
    }

    /* Region typecheck */

    else if (TYPE_Region != (Type = NsGetType (Region)))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepDefFieldValue: Needed Region, found %d %s\n",
                    Type, NsTypeNames[Type]));
        Status = AE_AML_ERROR;
    }

    else if (!(ObjDesc = AllocateObjectDesc ()))
    {   
        /* Unable to allocate new object descriptor    */

        Status = AE_NO_MEMORY;
    }


    if (AE_OK == Status)
    {   
        /* ObjDesc and Region valid */

        DUMP_STACK (MODE_Exec, "AmlPrepDefFieldValue", 2, "case DefField");


        ObjDesc->ValType = (UINT8) TYPE_DefField;
        if (TYPE_DefField != ObjDesc->Field.ValType)
        {
            /* 
             * The C implementation has done something which is technically legal
             * but unexpected:  the ValType field which was defined as a UINT8 did
             * not map to the same structure offset as the one which was defined
             * as a WORD_BIT -- see comments in the definition of the FieldUnit
             * variant of ACPI_OBJECT
             *
             * Log some evidence to facilitate porting the code.
             */
            ObjDesc->Field.ValType = 0x005a;
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlPrepDefFieldValue: **** Internal Failure %p %02x %02x %02x %02x\n",
                    ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                    ((UINT8 *) ObjDesc)[3]));
            OsdFree (ObjDesc);
            ObjDesc = NULL;
            Status = AE_AML_ERROR;
        }
    }

    if (AE_OK == Status)
    {   
        /* ObjDesc, Region, and ObjDesc->Field.ValType valid    */

        ObjDesc->Field.Access     = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
        ObjDesc->Field.LockRule   = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
        ObjDesc->Field.UpdateRule = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
        ObjDesc->Field.DatLen     = (UINT16) FldLen;

        /* TBD: - should use width of data register, not hardcoded 8 */

        DEBUG_PRINT (ACPI_INFO, ("AmlPrepDefFieldValue: hardcoded 8 **\n"));

        ObjDesc->Field.BitOffset  = (UINT16) FldPos % 8;
        ObjDesc->Field.Offset     = (UINT32) FldPos / 8;
        ObjDesc->Field.Container  = NsGetValue (Region);

        DEBUG_PRINT (ACPI_INFO, ("AmlPrepDefFieldValue: set nte %p (%4.4s) val = %p\n",
                        ObjStack[ObjStackTop], ObjStack[ObjStackTop], ObjDesc));

        DUMP_STACK_ENTRY (ObjDesc);
        DUMP_ENTRY (Region);
        DEBUG_PRINT (ACPI_INFO, ("\t%p \n", ObjDesc->Field.Container));

        if (ObjDesc->Field.Container)
        {
            DUMP_STACK_ENTRY (ObjDesc->Field.Container);
        }

        DEBUG_PRINT (ACPI_INFO,
                    ("============================================================\n"));

        /* 
         * Store the constructed descriptor (ObjDesc) into the nte whose
         * handle is on TOS, preserving the current type of that nte.
         */
        NsSetValue ((ACPI_HANDLE) ObjStack[ObjStackTop], ObjDesc,
                    (UINT8) NsGetType ((ACPI_HANDLE) ObjStack[ObjStackTop]));
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlPrepBankFieldValue
 *
 * PARAMETERS:  Region              - Region in which field is being defined
 *              BankReg             - Bank selection register
 *              BankVal             - Value to store in selection register
 *              FldFlg              - Access, LockRule, or UpdateRule
 *              FldPos              - Field position
 *              FldLen              - Field length
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Construct an ACPI_OBJECT of type BankField and connect
 *              it to the nte whose handle is at ObjStack[ObjStackTop]
 *
 ****************************************************************************/

ACPI_STATUS
AmlPrepBankFieldValue (
    ACPI_HANDLE             Region, 
    ACPI_HANDLE             BankReg, 
    UINT32                  BankVal,
    UINT8                   FldFlg, 
    INT32                   FldPos, 
    INT32                   FldLen)
{
    ACPI_OBJECT             *ObjDesc = NULL;
    ACPI_STATUS             Status = AE_OK;
    INT32                   Type;


    FUNCTION_TRACE ("AmlPrepBankFieldValue");


    if (!Region)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepBankFieldValue: null Region\n"));
        Status = AE_AML_ERROR;
    }
    else if (Region != (ACPI_HANDLE) (Type = NsGetType (Region)))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepBankFieldValue: Needed Region, found %d %s\n",
                        Type, NsTypeNames[Type]));
        Status = AE_AML_ERROR;
    }
    else if (!(ObjDesc = AllocateObjectDesc ()))
    {   
        /*  unable to allocate new object descriptor    */
        
        Status = AE_NO_MEMORY;
    }


    if (AE_OK == Status)
    {   
        /*  ObjDesc and Region valid    */

        DUMP_STACK (MODE_Exec, "AmlPrepBankFieldValue", 2, "case BankField");

        ObjDesc->ValType = (UINT8) TYPE_BankField;
        if (TYPE_BankField != ObjDesc->BankField.ValType)
        {
            /* See comments in AmlPrepDefFieldValue() re unexpected C behavior */

            ObjDesc->BankField.ValType = 0x005a;
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlPrepBankFieldValue: internal failure %p %02x %02x %02x %02x\n",
                    ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                    ((UINT8 *) ObjDesc)[3]));
            OsdFree (ObjDesc);

            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
        }
    }

    if (AE_OK == Status)
    {   
        /*  ObjDesc, Region, and ObjDesc->BankField.ValTyp valid    */

        ObjDesc->BankField.Access     = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
        ObjDesc->BankField.LockRule   = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
        ObjDesc->BankField.UpdateRule = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
        ObjDesc->BankField.DatLen     = (UINT16) FldLen;

        /* XXX - should use width of data register, not hardcoded 8 */

        DEBUG_PRINT (ACPI_INFO, (" ** AmlPrepBankFieldValue: hard 8 **\n"));

        ObjDesc->BankField.BitOffset  = (UINT16) FldPos % 8;
        ObjDesc->BankField.Offset     = (UINT32) FldPos / 8;
        ObjDesc->BankField.BankVal    = BankVal;
        ObjDesc->BankField.Container  = NsGetValue (Region);
        ObjDesc->BankField.BankSelect = NsGetValue (BankReg);


        DEBUG_PRINT (ACPI_INFO, ("AmlPrepBankFieldValue: set nte %p (%4.4s) val = %p\n",
                        ObjStack[ObjStackTop], ObjStack[ObjStackTop], ObjDesc));
        
        DUMP_STACK_ENTRY (ObjDesc);
        DUMP_ENTRY (Region);
        DUMP_ENTRY (BankReg);

        DEBUG_PRINT (ACPI_INFO,
                    ("============================================================\n"));

        /* 
         * Store the constructed descriptor (ObjDesc) into the nte whose
         * handle is on TOS, preserving the current type of that nte.
         */
        NsSetValue ((ACPI_HANDLE) ObjStack[ObjStackTop], ObjDesc,
                    (UINT8) NsGetType ((ACPI_HANDLE) ObjStack[ObjStackTop]));
    }


    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlPrepIndexFieldValue
 *
 * PARAMETERS:  IndexReg            - Index register
 *              DataReg             - Data register
 *              FldFlg              - Access, LockRule, or UpdateRule
 *              FldPos              - Field position
 *              FldLen              - Field length
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Construct an ACPI_OBJECT of type IndexField and connect
 *              it to the nte whose handle is at ObjStack[ObjStackTop]
 *
 ****************************************************************************/

ACPI_STATUS
AmlPrepIndexFieldValue (
    ACPI_HANDLE             IndexReg, 
    ACPI_HANDLE             DataReg,
    UINT8                   FldFlg, 
    INT32                   FldPos, 
    INT32                   FldLen)
{
    ACPI_OBJECT             *ObjDesc = NULL;
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("AmlPrepIndexFieldValue");


    if (!IndexReg || !DataReg)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepIndexFieldValue: null handle\n"));
        Status = AE_AML_ERROR;
    }

    else if (!(ObjDesc = AllocateObjectDesc ()))
    {   
        /*  unable to allocate new object descriptor    */

        Status = AE_NO_MEMORY;
    }

    if (AE_OK == Status)
    {   
        /* ObjDesc, IndexRegion, and DataReg valid  */

        ObjDesc->ValType = (UINT8) TYPE_IndexField;
        if (TYPE_IndexField != ObjDesc->IndexField.ValType)
        {
            /* See comments in AmlPrepDefFieldValue() re unexpected C behavior */
        
            ObjDesc->IndexField.ValType = 0x005a;
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlPrepIndexFieldValue: internal failure %p %02x %02x %02x %02x\n",
                    ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                    ((UINT8 *) ObjDesc)[3]));
            OsdFree (ObjDesc);
            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
        }
    }


    if (AE_OK == Status)
    {   
        /*  ObjDesc, IndexRegion, and DataReg, and ObjDesc->IndexField.ValTyp valid */
    
        ObjDesc->IndexField.Access        = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
        ObjDesc->IndexField.LockRule      = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
        ObjDesc->IndexField.UpdateRule    = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
        ObjDesc->IndexField.DatLen        = (UINT16) FldLen;

        /* XXX - should use width of data register, not hardcoded 8 */

        DEBUG_PRINT (ACPI_INFO, (" ** AmlPrepIndexFieldValue: hard 8 **\n"));

        ObjDesc->IndexField.BitOffset = (UINT16) FldPos % 8;
        ObjDesc->IndexField.IndexVal  = (UINT32) FldPos / 8;
        ObjDesc->IndexField.Index     = IndexReg;
        ObjDesc->IndexField.Data      = DataReg;

        DEBUG_PRINT (ACPI_INFO, ("AmlPrepIndexFieldValue: set nte %p (%4.4s) val = %p\n",
                        ObjStack[ObjStackTop], ObjStack[ObjStackTop], ObjDesc));

        DUMP_STACK_ENTRY (ObjDesc);
        DUMP_ENTRY (IndexReg);
        DUMP_ENTRY (DataReg);

        DEBUG_PRINT (ACPI_INFO,
                    ("============================================================\n"));

        /* 
         * Store the constructed descriptor (ObjDesc) into the nte whose
         * handle is on TOS, preserving the current type of that nte.
         */
        NsSetValue ((ACPI_HANDLE) ObjStack[ObjStackTop], ObjDesc,
                    (UINT8) NsGetType ((ACPI_HANDLE) ObjStack[ObjStackTop]));
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}

