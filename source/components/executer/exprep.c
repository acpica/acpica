
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
 * DESCRIPTION: Construct an ACPI_OBJECT_INTERNAL of type DefField and connect
 *              it to the nte whose handle is at the object stack top.
 *
 ****************************************************************************/

ACPI_STATUS
AmlPrepDefFieldValue (
    ACPI_HANDLE             Region, 
    UINT8                   FldFlg, 
    INT32                   FldPos, 
    INT32                   FldLen)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    INT32                   Type;


    FUNCTION_TRACE ("AmlPrepDefFieldValue");


    if (!Region)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepDefFieldValue: null Region\n"));
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    /* Region typecheck */

    if (TYPE_Region != (Type = NsGetType (Region)))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepDefFieldValue: Needed Region, found %d %s\n",
                    Type, NsTypeNames[Type]));
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    /* Allocate a new object */

    ObjDesc = CmCreateInternalObject (TYPE_DefField);
    if (!ObjDesc)
    {   
        /* Unable to allocate new object descriptor    */

        return_ACPI_STATUS (AE_NO_MEMORY);
    }


    /* ObjDesc and Region valid */

    DUMP_STACK (IMODE_Execute, "AmlPrepDefFieldValue", 2, "case DefField");

    if (TYPE_DefField != ObjDesc->Field.Type)
    {
        /* 
         * The C implementation has done something which is technically legal
         * but unexpected:  the Type field which was defined as a UINT8 did
         * not map to the same structure offset as the one which was defined
         * as a WORD_BIT -- see comments in the definition of the FieldUnit
         * variant of ACPI_OBJECT_INTERNAL
         *
         * Log some evidence to facilitate porting the code.
         */
        ObjDesc->Field.Type = 0x005a;
        DEBUG_PRINT (ACPI_ERROR, (
                "AmlPrepDefFieldValue: **** Internal Failure %p %02x %02x %02x %02x\n",
                ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                ((UINT8 *) ObjDesc)[3]));

        CmDeleteInternalObject (ObjDesc);
        ObjDesc = NULL;
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    /* ObjDesc, Region, and ObjDesc->Field.Type valid    */

    ObjDesc->Field.Access     = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
    ObjDesc->Field.LockRule   = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
    ObjDesc->Field.UpdateRule = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
    ObjDesc->Field.Length     = (UINT16) FldLen;

    /* TBD: - should use width of data register, not hardcoded 8 */

    DEBUG_PRINT (ACPI_INFO, ("AmlPrepDefFieldValue: hardcoded 8 **\n"));

    ObjDesc->Field.BitOffset  = (UINT16) FldPos % 8;
    ObjDesc->Field.Offset     = (UINT32) FldPos / 8;
    ObjDesc->Field.Container  = NsGetAttachedObject (Region);

    /* An additional reference for the container */

    CmUpdateObjectReference (ObjDesc->Field.Container, REF_INCREMENT);


    /* Debug output only */

    DEBUG_PRINT (ACPI_INFO, ("AmlPrepDefFieldValue: set nte %p (%4.4s) val = %p\n",
                    AmlObjStackGetValue (0), AmlObjStackGetValue (0), ObjDesc));

    DUMP_STACK_ENTRY (ObjDesc);
    DUMP_ENTRY (Region, ACPI_INFO);
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
    NsAttachObject ((ACPI_HANDLE) AmlObjStackGetValue (0), ObjDesc,
                (UINT8) NsGetType ((ACPI_HANDLE) AmlObjStackGetValue (0)));

    return_ACPI_STATUS (AE_OK);
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
 * DESCRIPTION: Construct an ACPI_OBJECT_INTERNAL of type BankField and connect
 *              it to the nte whose handle is at the object stack top
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
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    INT32                   Type;


    FUNCTION_TRACE ("AmlPrepBankFieldValue");


    if (!Region)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepBankFieldValue: null Region\n"));
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    if (Region != (ACPI_HANDLE) (Type = NsGetType (Region)))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepBankFieldValue: Needed Region, found %d %s\n",
                        Type, NsTypeNames[Type]));
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    /* Allocate a new object */

    ObjDesc = CmCreateInternalObject (TYPE_BankField);
    if (!ObjDesc)
    {   
        /* Unable to allocate new object descriptor    */
        
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /*  ObjDesc and Region valid    */

    DUMP_STACK (IMODE_Execute, "AmlPrepBankFieldValue", 2, "case BankField");

    if (TYPE_BankField != ObjDesc->BankField.Type)
    {
        /* See comments in AmlPrepDefFieldValue() re: unexpected C behavior */

        ObjDesc->BankField.Type = 0x005a;
        DEBUG_PRINT (ACPI_ERROR, (
                "AmlPrepBankFieldValue: internal failure %p %02x %02x %02x %02x\n",
                ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                ((UINT8 *) ObjDesc)[3]));

        CmDeleteInternalObject (ObjDesc);

        return_ACPI_STATUS (AE_AML_ERROR);
    }

    /*  ObjDesc, Region, and ObjDesc->BankField.ValTyp valid    */

    ObjDesc->BankField.Access     = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
    ObjDesc->BankField.LockRule   = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
    ObjDesc->BankField.UpdateRule = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
    ObjDesc->BankField.Length     = (UINT16) FldLen;

    /* XXX - should use width of data register, not hardcoded 8 */

    DEBUG_PRINT (ACPI_INFO, (" ** AmlPrepBankFieldValue: hard 8 **\n"));

    ObjDesc->BankField.BitOffset  = (UINT16) FldPos % 8;
    ObjDesc->BankField.Offset     = (UINT32) FldPos / 8;
    ObjDesc->BankField.Value      = BankVal;
    ObjDesc->BankField.Container  = NsGetAttachedObject (Region);
    ObjDesc->BankField.BankSelect = NsGetAttachedObject (BankReg);

    /* An additional reference for the container and bank select */
    /* TBD: is "BankSelect" ever a real internal object?? */

    CmUpdateObjectReference (ObjDesc->BankField.Container, REF_INCREMENT);
    CmUpdateObjectReference (ObjDesc->BankField.BankSelect, REF_INCREMENT);


    DEBUG_PRINT (ACPI_INFO, ("AmlPrepBankFieldValue: set nte %p (%4.4s) val = %p\n",
                    AmlObjStackGetValue (0), AmlObjStackGetValue (0), ObjDesc));
    
    DUMP_STACK_ENTRY (ObjDesc);
    DUMP_ENTRY (Region, ACPI_INFO);
    DUMP_ENTRY (BankReg, ACPI_INFO);

    DEBUG_PRINT (ACPI_INFO,
                ("============================================================\n"));

    /* 
     * Store the constructed descriptor (ObjDesc) into the nte whose
     * handle is on TOS, preserving the current type of that nte.
     */
    NsAttachObject ((ACPI_HANDLE) AmlObjStackGetValue (0), ObjDesc,
                (UINT8) NsGetType ((ACPI_HANDLE) AmlObjStackGetValue (0)));


    return_ACPI_STATUS (AE_OK);
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
 * DESCRIPTION: Construct an ACPI_OBJECT_INTERNAL of type IndexField and connect
 *              it to the nte whose handle is at the object stack top
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
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;


    FUNCTION_TRACE ("AmlPrepIndexFieldValue");


    if (!IndexReg || !DataReg)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepIndexFieldValue: null handle\n"));
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    /* Allocate a new object descriptor */

    ObjDesc = CmCreateInternalObject (TYPE_IndexField);
    if (!ObjDesc)
    {   
        /* Unable to allocate new object descriptor    */
        
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* ObjDesc, IndexRegion, and DataReg valid  */

    if (TYPE_IndexField != ObjDesc->IndexField.Type)
    {
        /* See comments in AmlPrepDefFieldValue() re unexpected C behavior */
    
        ObjDesc->IndexField.Type = 0x005a;
        DEBUG_PRINT (ACPI_ERROR, (
                "AmlPrepIndexFieldValue: internal failure %p %02x %02x %02x %02x\n",
                ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                ((UINT8 *) ObjDesc)[3]));

        CmDeleteInternalObject (ObjDesc);
        return_ACPI_STATUS (AE_AML_ERROR);
    }


    /*  ObjDesc, IndexRegion, and DataReg, and ObjDesc->IndexField.ValTyp valid */

    ObjDesc->IndexField.Access        = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
    ObjDesc->IndexField.LockRule      = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
    ObjDesc->IndexField.UpdateRule    = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
    ObjDesc->IndexField.Length        = (UINT16) FldLen;

    /* XXX - should use width of data register, not hardcoded 8 */

    DEBUG_PRINT (ACPI_INFO, (" ** AmlPrepIndexFieldValue: hard 8 **\n"));

    ObjDesc->IndexField.BitOffset = (UINT16) FldPos % 8;
    ObjDesc->IndexField.Value     = (UINT32) FldPos / 8;
    ObjDesc->IndexField.Index     = IndexReg;
    ObjDesc->IndexField.Data      = DataReg;

    DEBUG_PRINT (ACPI_INFO, ("AmlPrepIndexFieldValue: set nte %p (%4.4s) val = %p\n",
                    AmlObjStackGetValue (0), AmlObjStackGetValue (0), ObjDesc));

    DUMP_STACK_ENTRY (ObjDesc);
    DUMP_ENTRY (IndexReg, ACPI_INFO);
    DUMP_ENTRY (DataReg, ACPI_INFO);

    DEBUG_PRINT (ACPI_INFO,
                ("============================================================\n"));

    /* 
     * Store the constructed descriptor (ObjDesc) into the nte whose
     * handle is on TOS, preserving the current type of that nte.
     */
    NsAttachObject ((ACPI_HANDLE) AmlObjStackGetValue (0), ObjDesc,
                    (UINT8) NsGetType ((ACPI_HANDLE) AmlObjStackGetValue (0)));

    return_ACPI_STATUS (AE_OK);
}

