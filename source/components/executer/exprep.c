
/******************************************************************************
 * 
 * Module Name: ieprep - ACPI AML (p-code) execution - prep utilities
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


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", 'T', "AmlGetMethodType: internal error", "AmlGetMethodType: internal error"},
    {"0001", '1', "AmlSetMethodValue: Descriptor Allocation Failure", "AmlSetMethodValue: Descriptor Allocation Failure"},
    {"0002", '1', "AmlPrepDefFieldValue: Descriptor Allocation Failure", "AmlPrepDefFieldValue: Descriptor Allocation Failure"},
    {"0003", '1', "AmlPrepBankFieldValue: Descriptor Allocation Failure", "AmlPrepBankFieldValue: Descriptor Allocation Failure"},
    {"0004", '1', "AmlPrepIndexFieldValue: Descriptor Allocation Failure", "AmlPrepIndexFieldValue: Descriptor Allocation Failure"},
    {NULL, 'I', NULL, NULL}
};



/*****************************************************************************
 * 
 * FUNCTION:    AmlGetMethodDepth
 *
 * PARAMETERS:  None.
 *
 * RETURN:      The current value of MethodStackTop
 *
 ****************************************************************************/

INT32
AmlGetMethodDepth (void)
{

    return MethodStackTop;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlGetMethodType
 *
 * PARAMETERS:  Index               - Index in MethodStack[MethodStackTop]
 *
 * RETURN:      Data type of selected Arg or Local
 *              Used only in ExecMonadic2()/TypeOp.
 *
 ****************************************************************************/

ACPI_OBJECT_TYPE
AmlGetMethodType (
    INT32                   Index)
{
    FUNCTION_TRACE ("AmlGetMethodType");


    if (OUTRANGE (MethodStackTop, MethodStack) ||
        OUTRANGE (Index, MethodStack[MethodStackTop]))
    {
        /* MethodStackTop or Index invalid for current object stack  */

        REPORT_ERROR (&KDT[0]);
        FUNCTION_EXIT;
        return (ACPI_OBJECT_TYPE) -1;
    }

    if (!MethodStack[MethodStackTop][Index])
    {
        FUNCTION_EXIT;
        return TYPE_Any; /* Any == 0 => "uninitialized" -- see spec 15.2.3.5.2.28 */
    }

    FUNCTION_EXIT;
    return MethodStack[MethodStackTop][Index]->ValType;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlGetMethodValue
 *
 * PARAMETERS:  Index               - Index in MethodStack[MethodStackTop]
 *              *ObjDesc            - Descriptor into which selected Arg
 *                                    or Local value should be copied
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve value of selected Arg or Local
 *              Used only in AmlGetRvalue().
 *
 ****************************************************************************/

ACPI_STATUS
AmlGetMethodValue (
    INT32                   Index, 
    ACPI_OBJECT             *ObjDesc)
{
    ACPI_STATUS             Status = AE_AML_ERROR;


    FUNCTION_TRACE ("AmlGetMethodValue");


    if (!ObjDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetMethodValue: NULL object descriptor pointer\n"));
    }
    
    else
    {   
        /* ObjDesc is valid */

        if (OUTRANGE (MethodStackTop, MethodStack) ||
            OUTRANGE (Index, MethodStack[MethodStackTop]))
        {
            /* MethodStackTop or Index invalid for current object stack */

            DEBUG_PRINT (ACPI_ERROR, ("AmlGetMethodValue: Bad method stack index [%d][%d]\n",
                            MethodStackTop, Index));
        }

        else if (!MethodStack[MethodStackTop][Index])
        {
            /* Index points to uninitialized object stack value */

            if ((ARGBASE <= Index) && (Index < (ARGBASE + NUMARG)))
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetMethodValue: Uninitialized Arg%d\n",
                        Index - ARGBASE));
            }
            else if ((LCLBASE <= Index) && (Index < (LCLBASE + NUMLCL)))
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetMethodValue: Uninitialized Local%d\n",
                                Index - LCLBASE));
            }
            else
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetMethodValue: Uninitialized method value %d\n",
                                Index));
            }

#ifdef HACK
            DEBUG_PRINT (ACPI_WARN, (" ** AmlGetMethodValue: ret uninit as 4 **\n"));
            ObjDesc->Number.ValType = (UINT8) Number;
            ObjDesc->Number.Number = 0x4;
            Status = AE_OK;
#endif /* HACK */

        }

        else
        {
            /* Index points to initialized object stack value   */

            memcpy ((void *) ObjDesc,
                     (void *) MethodStack[MethodStackTop][Index],
                     sizeof (*ObjDesc));

            if (TYPE_Buffer == ObjDesc->ValType)
            {
                /* Assign a new sequence number to track buffer usage */
            
                ObjDesc->Buffer.Sequence = AmlBufSeq ();
            }

            Status = AE_OK;
        }
    }

    FUNCTION_EXIT;
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlSetMethodValue
 *
 * PARAMETERS:  Index               - Index in MethodStack[MethodStackTop]
 *              *ObjDesc            - Value to be stored
 *                                    May be NULL -- see Description.
 *              *ObjDesc2           - Spare descriptor into which *ObjDesc
 *                                    can be copied, or NULL if one must
 *                                    be allocated for the purpose.  If
 *                                    provided, this descriptor will be
 *                                    consumed (either used for the new
 *                                    value or deleted).
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store a value in an Arg or Local.
 *              To undefine an entry, pass ObjDesc as NULL; the old descriptor
 *              will be deleted.
 *
 ****************************************************************************/

ACPI_STATUS
AmlSetMethodValue (
    INT32                   Index, 
    ACPI_OBJECT             *ObjDesc, 
    ACPI_OBJECT             *ObjDesc2)
{
    FUNCTION_TRACE ("AmlSetMethodValue");


    DEBUG_PRINT (TRACE_EXEC, ("AmlSetMethodValue: Index=%d, ObjDesc=%p, ObjDesc2=%p\n",
                    Index, ObjDesc, ObjDesc2));

    if (OUTRANGE (MethodStackTop, MethodStack) ||
        OUTRANGE (Index, MethodStack[MethodStackTop]))
    {
        /* MethodStackTop or Index invalid for current object stack */

        DEBUG_PRINT (ACPI_ERROR, ("AmlSetMethodValue: Bad method stack index [%d][%d]\n",
                        MethodStackTop, Index));
        FUNCTION_EXIT;
        return AE_AML_ERROR;
    }

    if (!MethodStack[MethodStackTop][Index])
    {
        /* Local or Arg is currently undefined in object stack */

        if (!ObjDesc2 && ObjDesc)
        {
            /* 
             * No descriptor was provided in ObjDesc2, and the currently-undefined
             * Local or Arg is to be defined.  Allocate a descriptor.
             */
            MethodStack[MethodStackTop][Index] = AllocateObjectDesc (&KDT[1]);
            if (!MethodStack[MethodStackTop][Index])
            {
                /*  allocation failure  */

                FUNCTION_EXIT;
                return AE_NO_MEMORY;
            }
        }

        else
        {
            /* 
             * A descriptor was provided in ObjDesc2; use it for the Arg/Local
             * new value (or delete it later if the new value is NULL).
             * We also come here if no descriptor was supplied and the
             * undefined Local or Arg is to remain undefined; in that case
             * the assignment is a no-op.
             */
            MethodStack[MethodStackTop][Index] = ObjDesc2;
        }
    }
 
    else
    {
        /* 
         * Arg or Local is currently defined, so that descriptor will be
         * reused for the new value.  Delete the spare descriptor if supplied.
         */
        if (ObjDesc2)
        {
            /* XXX - see XXX comment below re possible storage leak */

            OsdFree (ObjDesc2);
            ObjDesc = NULL;
        }
    }

    if (!ObjDesc)
    {
        /* 
         * Undefine the Arg or Local by setting its descriptor pointer to NULL.
         * If it is currently defined, delete the old descriptor first.
         */
        if (MethodStack[MethodStackTop][Index])
        {
            /* object descriptor currently defined, delete the old descriptor   */

            if (TYPE_Buffer == MethodStack[MethodStackTop][Index]->ValType)
            {
                /* 
                 * Ensure the about-to-be-deleted Buffer's sequence number
                 * will no longer match any FieldUnits defined within it,
                 * by inverting its most-significant bit.
                 */
                MethodStack[MethodStackTop][Index]->Buffer.Sequence
                                                                ^= 0x80000000UL;
            }

            OsdFree (MethodStack[MethodStackTop][Index]);
            MethodStack[MethodStackTop][Index] = NULL;

            /*  TBD:    Should also delete any unshared storage pointed to by this
             *          descriptor, but lacking a convenient way to determine
             *          whether the storage is shared or not we'll let Garbage
             *          Collection handle it.
             */
        }

        MethodStack[MethodStackTop][Index] = ObjDesc;
    }

    else
    {
        /* 
         * Copy the ObjStack descriptor (*ObjDesc) into the descriptor for the
         * Arg or Local.
         */
        /*
         * TBD:     possible storage leak: if the old descriptor happens to be
         *          for an aggregate (Buffer, String, Package, etc.), it points
         *          to other storage which may or may not be shared; if unshared
         *          it should be freed here. (Good Luck figuring out whether it
         *          is shared or not.)
         */
        memcpy ((void *) MethodStack[MethodStackTop][Index],
                 (void *) ObjDesc, sizeof (*ObjDesc));

        if (TYPE_Buffer == ObjDesc->ValType)
        {
            /* Assign a new sequence number to track buffers */

            MethodStack[MethodStackTop][Index]->Buffer.Sequence
                        = AmlBufSeq ();
        }
    }

    FUNCTION_EXIT;
    return AE_OK;
}


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

    else if (Region != (ACPI_HANDLE)(Type = NsGetType (Region)))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepDefFieldValue: Needed Region, found %d %s\n",
                    Type, NsTypeNames[Type]));
        Status = AE_AML_ERROR;
    }

    else if (!(ObjDesc = AllocateObjectDesc (&KDT[3])))
    {   
        /*  unable to allocate new object descriptor    */

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
             * variant of ACPI_OBJECT in amlpriv.h.
             *
             * Log some evidence to facilitate porting the code.
             */
            ObjDesc->Field.ValType = 0x005a;
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlPrepDefFieldValue: internal failure %p %02x %02x %02x %02x\n",
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

        /* XXX - should use width of data register, not hardcoded 8 */

        DEBUG_PRINT (ACPI_INFO, (" ** AmlPrepDefFieldValue: hard 8 **\n"));

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

    FUNCTION_EXIT;
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
    else if (!(ObjDesc = AllocateObjectDesc (&KDT[3])))
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

            FUNCTION_EXIT;
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


    FUNCTION_EXIT;
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

    else if (!(ObjDesc = AllocateObjectDesc (&KDT[4])))
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
            FUNCTION_EXIT;
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

    FUNCTION_EXIT;
    return Status;
}

/*****************************************************************************
 * 
 * FUNCTION:    AmlPrepStack
 *
 * PARAMETERS:  *Types              - String showing operand types needed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert stack entries to required types
 *
 *      Each character in Types represents one required operand
 *      and indicates the required ValType:
 *          l => Lvalue, also accepts an entry which is an ACPI_HANDLE
 *                  instead of an (ACPI_OBJECT *))
 *          n => Number
 *          s => String or Buffer
 *          b => Buffer
 *          i => If
 *          p => Package
 *      The corresponding stack entry will be converted to the
 *      required type if possible, else return AE_AML_ERROR.
 *
 ****************************************************************************/

ACPI_STATUS
AmlPrepStack (
    char                    *Types)
{
    ACPI_OBJECT             **StackPtr = (ACPI_OBJECT **) &ObjStack[ObjStackTop];
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlPrepStack");


    /* 
     * Ensure room on stack for AmlGetRvalue() to operate
     * without clobbering top existing entry.
     */

    Status = AmlPushIfExec (MODE_Exec);
    if (AE_OK != Status)
    {
        FUNCTION_EXIT;
        return Status;
    }

    /* 
     * Normal exit is with *Types == '\0' at end of string.
     * Function will return AE_AML_ERROR from within the loop upon
     * finding an entry which is not, and cannot be converted
     * to, the required type; if stack underflows; or upon
     * finding a NULL stack entry (which "should never happen").
     */

    while (*Types)
    {
        UINT8       bTypeFound;
        char        TypeFound[30];
        char        *TypeFoundPtr = NULL;


        if (!StackPtr || !*StackPtr)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlPrepStack:internal error: null stack entry\n"));
            ObjStackTop--;
            FUNCTION_EXIT;
            return AE_AML_ERROR;
        }

        bTypeFound = (*StackPtr)->ValType;
        if (bTypeFound > (UINT8) TYPE_Lvalue || 
            BadType == NsTypeNames[bTypeFound])
        {
            sprintf (TypeFound, "type encoding %d", bTypeFound);
            TypeFoundPtr = TypeFound;
        }
        
        else if ((UINT8) TYPE_Lvalue == bTypeFound)
        {
            strcpy (TypeFound, "Lvalue ");
            switch ((*StackPtr)->Lvalue.OpCode)
            {
            case AML_ZeroOp:
                strcat (TypeFound, "Zero");
                break;
            
            case AML_OneOp:
                strcat (TypeFound, "One");
                break;
            
            case AML_OnesOp:
                strcat (TypeFound, "Ones");
                break;
            
            case Debug1:
                strcat (TypeFound, "Debug");
                break;
            
            case AML_NameOp:
                sprintf (&TypeFound[7], "Name");
                break;
           
            case AML_IndexOp:
                sprintf (&TypeFound[7], "Index %p",
                            (*StackPtr)->Lvalue.Ref);
                break;
            
            case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
            case AML_Arg4: case AML_Arg5: case AML_Arg6:
                sprintf (&TypeFound[7], "Arg%d",
                            (*StackPtr)->Lvalue.OpCode - AML_Arg0);
                break;
            
            case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
            case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:
                sprintf (&TypeFound[7], "Local%d",
                            (*StackPtr)->Lvalue.OpCode - AML_Local0);
                break;
            
            default:
                sprintf (&TypeFound[7], "??? %02x",
                            (*StackPtr)->Lvalue.OpCode);
                break;
            }
        }
        
        else
        {
            TypeFoundPtr = NsTypeNames[bTypeFound];
        }


        switch (*Types++)
        {
        case 'l':                                   /* need Lvalue */
            if (IS_NS_HANDLE (*StackPtr))             /* direct name ptr OK as-is */
            {
                break;
            }

            if (TYPE_Lvalue != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlPrepStack: Needed Lvalue, found %s\n",
                            TypeFoundPtr));
                ObjStackTop--;
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            if (AML_NameOp == (*StackPtr)->Lvalue.OpCode)
            {
                /* Convert indirect name ptr to direct name ptr */
                
                ACPI_HANDLE TempHandle = (*StackPtr)->Lvalue.Ref;
                OsdFree (*StackPtr);
                (*StackPtr) = TempHandle;
            }
            break;

        case 'n':                                   /* need Number */
            Status = AmlGetRvalue (StackPtr);

            DEBUG_PRINT (TRACE_EXEC,
                          ("AmlPrepStack:n: AmlGetRvalue returned %s\n", ExceptionNames[Status]));

            if (AE_OK != Status)
            {
                ObjStackTop--;
                FUNCTION_EXIT;
                return Status;
            }

            if (TYPE_Number != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlPrepStack: Needed Number, found %s\n",
                            TypeFoundPtr));
                ObjStackTop--;
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }
            break;

        case 's':                                   /* need String (or Buffer) */
            if ((Status = AmlGetRvalue (StackPtr)) != AE_OK)
            {
                ObjStackTop--;
                FUNCTION_EXIT;
                return Status;
            }

            DEBUG_PRINT (TRACE_EXEC, ("AmlGetRvalue returned AE_OK\n"));

            if (TYPE_String != (*StackPtr)->ValType &&
                TYPE_Buffer != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlPrepStack: Needed String or Buffer, found %s\n",
                        TypeFoundPtr));
                ObjStackTop--;
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }
            break;

        case 'b':                                   /* need Buffer */
            if ((Status = AmlGetRvalue(StackPtr)) != AE_OK)
            {
                ObjStackTop--;
                FUNCTION_EXIT;
                return Status;
            }

            DEBUG_PRINT (TRACE_EXEC, ("AmlGetRvalue returned AE_OK\n"));

            if (TYPE_Buffer != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlPrepStack: Needed Buffer, found %s\n",
                            TypeFoundPtr));
                ObjStackTop--;
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }
            break;

        case 'i':                                   /* need If */
            if (TYPE_If != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlPrepStack: Needed If, found %s\n",
                        TypeFoundPtr));
                ObjStackTop--;
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }
            break;

        case 'p':                                   /* need Package */
            if ((Status = AmlGetRvalue (StackPtr)) != AE_OK)
            {
                ObjStackTop--;
                FUNCTION_EXIT;
                return Status;
            }

            DEBUG_PRINT (TRACE_EXEC, ("AmlGetRvalue returned AE_OK\n"));

            if (TYPE_Package != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlPrepStack: Needed Package, found %s\n",
                            TypeFoundPtr));
                ObjStackTop--;
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlPrepStack:internal error Unknown type flag %02x\n",
                    *--Types));
            ObjStackTop--;
            FUNCTION_EXIT;
            return AE_AML_ERROR;

        }   /* switch (*Types++) */


        /* 
         * If more operands needed, decrement StackPtr to point
         * to next operand on stack (after checking for underflow).
         */
        if (*Types)
        {
            /* Don't try to decrement below bottom of stack */
            
            if ((ACPI_OBJECT **) &ObjStack[0] == StackPtr)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlPrepStack: not enough operands\n"));
                ObjStackTop--;
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            StackPtr--;
        }

    }   /* while (*Types) */

    ObjStackTop--;
    FUNCTION_EXIT;
    return AE_OK;
}




