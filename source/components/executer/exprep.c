
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
#include <string.h>


#define _THIS_MODULE        "ieprep.c"
#define _COMPONENT          INTERPRETER

/* 
 * Method Stack, containing locals and args
 * per level, 0-7 are Local# and 8-14 are Arg#
 */

OBJECT_DESCRIPTOR *         MethodStack[AML_METHOD_MAX_NEST][ARGBASE+NUMARG];
INT32                       MethodStackTop = -1;


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", 'T', "GetMethodValTyp: internal error", "GetMethodValTyp: internal error"},
    {"0001", '1', "SetMethodValue: Descriptor Allocation Failure", "SetMethodValue: Descriptor Allocation Failure"},
    {"0002", '1', "PrepDefFieldValue: Descriptor Allocation Failure", "PrepDefFieldValue: Descriptor Allocation Failure"},
    {"0003", '1', "PrepBankFieldValue: Descriptor Allocation Failure", "PrepBankFieldValue: Descriptor Allocation Failure"},
    {"0004", '1', "PrepIndexFieldValue: Descriptor Allocation Failure", "PrepIndexFieldValue: Descriptor Allocation Failure"},
    {NULL, 'I', NULL, NULL}
};



/*****************************************************************************
 * 
 * FUNCTION:    GetMethodDepth
 *
 * RETURN:      The current value of MethodStackTop
 *
 ****************************************************************************/

INT32
GetMethodDepth (void)
{

    return MethodStackTop;
}


/*****************************************************************************
 * 
 * FUNCTION:    GetMethodValTyp
 *
 * PARAMETERS:  INT32 Index      index in MethodStack[MethodStackTop]
 *
 * RETURN:      Data type of selected Arg or Local
 *              Used only in ExecMonadic2()/TypeOp.
 *
 ****************************************************************************/

NsType
GetMethodValTyp (INT32 Index)
{
    FUNCTION_TRACE ("GetMethodValTyp");


    if (OUTRANGE (MethodStackTop, MethodStack) ||
        OUTRANGE (Index, MethodStack[MethodStackTop]))
    {
        /*  iMethodStackTop or iIndex invalid for current object stack  */

        REPORT_ERROR (&KDT[0]);
        return (NsType)-1;
    }

    if (!MethodStack[MethodStackTop][Index])
    {
        return TYPE_Any; /* Any == 0 => "uninitialized" -- see spec 15.2.3.5.2.28 */
    }

    return MethodStack[MethodStackTop][Index]->ValType;
}


/*****************************************************************************
 * 
 * FUNCTION:    GetMethodValue
 *
 * PARAMETERS:  INT32               Index       index in MethodStack[MethodStackTop]
 *              OBJECT_DESCRIPTOR   *ObjDesc    Descriptor into which selected Arg
 *                                              or Local value should be copied
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Retrieve value of selected Arg or Local
 *              Used only in GetRvalue().
 *
 ****************************************************************************/

INT32
GetMethodValue (INT32 Index, OBJECT_DESCRIPTOR *ObjDesc)
{
    INT32           Excep = S_ERROR;


    FUNCTION_TRACE ("GetMethodValue");


    if (!ObjDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("GetMethodValue: NULL object descriptor pointer\n"));
    }
    
    else
    {   
        /* ObjDesc is valid */

        if (OUTRANGE (MethodStackTop, MethodStack) ||
            OUTRANGE (Index, MethodStack[MethodStackTop]))
        {
            /* MethodStackTop or Index invalid for current object stack */

            DEBUG_PRINT (ACPI_ERROR, ("GetMethodValue: Bad method stack index [%d][%d]\n",
                            MethodStackTop, Index));
        }

        else if (!MethodStack[MethodStackTop][Index])
        {
            /* Index points to uninitialized object stack value */

            if ((ARGBASE <= Index) && (Index < (ARGBASE + NUMARG)))
            {
                DEBUG_PRINT (ACPI_ERROR, ("GetMethodValue: Uninitialized Arg%d\n",
                        Index - ARGBASE));
            }
            else if ((LCLBASE <= Index) && (Index < (LCLBASE + NUMLCL)))
            {
                DEBUG_PRINT (ACPI_ERROR, ("GetMethodValue: Uninitialized Local%d\n",
                                Index - LCLBASE));
            }
            else
            {
                DEBUG_PRINT (ACPI_ERROR, ("GetMethodValue: Uninitialized method value %d\n",
                                Index));
            }

#ifdef HACK
            DEBUG_PRINT (ACPI_WARN, (" ** GetMethodValue: ret uninit as 4 **\n"));
            ObjDesc->Number.ValType = (UINT8) Number;
            ObjDesc->Number.Number = 0x4;
            Excep = S_SUCCESS;
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

            Excep = S_SUCCESS;
        }
    }

    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    SetMethodValue
 *
 * PARAMETERS:  INT32               Index       Index in MethodStack[MethodStackTop]
 *              OBJECT_DESCRIPTOR * ObjDesc     Value to be stored
 *                                              May be NULL -- see Description.
 *              OBJECT_DESCRIPTOR * ObjDesc2    Spare descriptor into which *ObjDesc
 *                                              can be copied, or NULL if one must
 *                                              be allocated for the purpose.  If
 *                                              provided, this descriptor will be
 *                                              consumed (either used for the new
 *                                              value or deleted).
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store a value in an Arg or Local.
 *              To undefine an entry, pass ObjDesc as NULL; the old descriptor
 *              will be deleted.
 *
 * ALLOCATION:
 *  Reference     Size                    Pool    Owner       Description
 *  MethodStack   s(OBJECT_DESCRIPTOR)    bu      amlexec     Object
 *
 ****************************************************************************/

INT32
SetMethodValue (INT32 Index, OBJECT_DESCRIPTOR *ObjDesc, OBJECT_DESCRIPTOR *ObjDesc2)
{
    FUNCTION_TRACE ("SetMethodValue");


    DEBUG_PRINT (TRACE_EXEC, ("SetMethodValue: Index=%d, ObjDesc=%p, ObjDesc2=%p\n",
                    Index, ObjDesc, ObjDesc2));

    if (OUTRANGE (MethodStackTop, MethodStack) ||
        OUTRANGE (Index, MethodStack[MethodStackTop]))
    {
        /* MethodStackTop or Index invalid for current object stack */

        DEBUG_PRINT (ACPI_ERROR, ("SetMethodValue: Bad method stack index [%d][%d]\n",
                        MethodStackTop, Index));
        return S_ERROR;
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

                return S_ERROR;
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

            DELETE (ObjDesc2);
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

            DELETE (MethodStack[MethodStackTop][Index]);

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

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    PrepDefFieldValue
 *
 * PARAMETERS:  NsHandle    Region     Region in which field is being defined
 *              UINT8       FldFlg     Access, LockRule, UpdateRule
 *                                     The format of a FieldFlag is described
 *                                     in the ACPI specification and in <aml.h>
 *              INT32       FldPos     field position
 *              INT32       FldLen     field length
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Construct an OBJECT_DESCRIPTOR of type DefField and connect
 *              it to the nte whose handle is at ObjStack[ObjStackTop]
 *
 * ALLOCATION:
 *  Reference   Size                    Pool    Owner       Description
 *  nte.ValDesc s(OBJECT_DESCRIPTOR)    bu      amlexec     Field descriptor
 *
 ****************************************************************************/

INT32
PrepDefFieldValue (NsHandle Region, UINT8 FldFlg, INT32 FldPos, INT32 FldLen)
{
    OBJECT_DESCRIPTOR   *ObjDesc = NULL;
    INT32               Excep = S_SUCCESS;
    INT32               Type;


    FUNCTION_TRACE ("PrepDefFieldValue");


    if (!Region)
    {
        DEBUG_PRINT (ACPI_ERROR, ("PrepDefFieldValue: null Region\n"));
        Excep = S_ERROR;
    }

    else if (Region != (NsHandle)(Type = NsGetType (Region)))
    {
        DEBUG_PRINT (ACPI_ERROR, ("PrepDefFieldValue: Needed Region, found %d %s\n",
                    Type, NsTypeNames[Type]));
        Excep = S_ERROR;
    }

    else if (!(ObjDesc = AllocateObjectDesc (&KDT[3])))
    {   
        /*  unable to allocate new object descriptor    */

        Excep = S_ERROR;
    }


    if (S_SUCCESS == Excep)
    {   
        /* ObjDesc and Region valid */

        DUMP_STACK (MODE_Exec, "PrepDefFieldValue", 2, "case DefField");


        ObjDesc->ValType = (UINT8) TYPE_DefField;
        if (TYPE_DefField != ObjDesc->Field.ValType)
        {
            /* 
             * The C implementation has done something which is technically legal
             * but unexpected:  the ValType field which was defined as a UINT8 did
             * not map to the same structure offset as the one which was defined
             * as a WORD_BIT -- see comments in the definition of the FieldUnit
             * variant of OBJECT_DESCRIPTOR in amlpriv.h.
             *
             * Log some evidence to facilitate porting the code.
             */
            ObjDesc->Field.ValType = 0x005a;
            DEBUG_PRINT (ACPI_ERROR, (
                    "PrepDefFieldValue: internal failure %p %02x %02x %02x %02x\n",
                    ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                    ((UINT8 *) ObjDesc)[3]));
            DELETE (ObjDesc);
            Excep = S_ERROR;
        }
    }

    if (S_SUCCESS == Excep)
    {   
        /* ObjDesc, Region, and ObjDesc->Field.ValType valid    */

        ObjDesc->Field.Access     = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
        ObjDesc->Field.LockRule   = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
        ObjDesc->Field.UpdateRule = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
        ObjDesc->Field.DatLen     = (UINT16) FldLen;

        /* XXX - should use width of data register, not hardcoded 8 */

        DEBUG_PRINT (ACPI_INFO, (" ** PrepDefFieldValue: hard 8 **\n"));

        ObjDesc->Field.BitOffset  = (UINT16) FldPos % 8;
        ObjDesc->Field.Offset     = (UINT32) FldPos / 8;
        ObjDesc->Field.Container  = NsGetValue (Region);


        DEBUG_PRINT (ACPI_INFO, ("PrepDefFieldValue: set nte %p (%4.4s) val = %p\n",
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
        NsSetValue ((NsHandle) ObjStack[ObjStackTop], ObjDesc,
                    (UINT8) NsGetType ((NsHandle) ObjStack[ObjStackTop]));
    }

    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    PrepBankFieldValue
 *
 * PARAMETERS:  NsHandle    Region     Region in which field is being defined
 *              NsHandle    BankReg    Bank selection register
 *              UINT32      BankVal    Value to store in selection register
 *              UINT8       FldFlg     Access, LockRule, UpdateRule
 *              INT32       FldPos     field position
 *              INT32       FldLen     field length
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Construct an OBJECT_DESCRIPTOR of type BankField and connect
 *              it to the nte whose handle is at ObjStack[ObjStackTop]
 *
 * ALLOCATION:
 *  Reference   Size                    Pool    Owner       Description
 *  nte.ValDesc s(OBJECT_DESCRIPTOR)    bu      amlexec     Field descriptor
 *
 ****************************************************************************/

INT32
PrepBankFieldValue (NsHandle Region, NsHandle BankReg, UINT32 BankVal,
                        UINT8 FldFlg, INT32 FldPos, INT32 FldLen)
{
    OBJECT_DESCRIPTOR   *ObjDesc = NULL;
    INT32               Excep = S_SUCCESS;
    INT32               Type;


    FUNCTION_TRACE ("PrepBankFieldValue");


    if (!Region)
    {
        DEBUG_PRINT (ACPI_ERROR, ("PrepBankFieldValue: null Region\n"));
        Excep = S_ERROR;
    }
    else if (Region != (NsHandle) (Type = NsGetType (Region)))
    {
        DEBUG_PRINT (ACPI_ERROR, ("PrepBankFieldValue: Needed Region, found %d %s\n",
                        Type, NsTypeNames[Type]));
        Excep = S_ERROR;
    }
    else if (!(ObjDesc = AllocateObjectDesc (&KDT[3])))
    {   
        /*  unable to allocate new object descriptor    */
        
        Excep = S_ERROR;
    }


    if (S_SUCCESS == Excep)
    {   
        /*  ObjDesc and Region valid    */

        DUMP_STACK (MODE_Exec, "PrepBankFieldValue", 2, "case BankField");

        ObjDesc->ValType = (UINT8) TYPE_BankField;
        if (TYPE_BankField != ObjDesc->BankField.ValType)
        {
            /* See comments in PrepDefFieldValue() re unexpected C behavior */

            ObjDesc->BankField.ValType = 0x005a;
            DEBUG_PRINT (ACPI_ERROR, (
                    "PrepBankFieldValue: internal failure %p %02x %02x %02x %02x\n",
                    ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                    ((UINT8 *) ObjDesc)[3]));
            DELETE (ObjDesc);
            return S_ERROR;
        }
    }

    if (S_SUCCESS == Excep)
    {   
        /*  ObjDesc, Region, and ObjDesc->BankField.ValTyp valid    */

        ObjDesc->BankField.Access     = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
        ObjDesc->BankField.LockRule   = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
        ObjDesc->BankField.UpdateRule = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
        ObjDesc->BankField.DatLen     = (UINT16) FldLen;

        /* XXX - should use width of data register, not hardcoded 8 */

        DEBUG_PRINT (ACPI_INFO, (" ** PrepBankFieldValue: hard 8 **\n"));

        ObjDesc->BankField.BitOffset  = (UINT16) FldPos % 8;
        ObjDesc->BankField.Offset     = (UINT32) FldPos / 8;
        ObjDesc->BankField.BankVal    = BankVal;
        ObjDesc->BankField.Container  = NsGetValue (Region);
        ObjDesc->BankField.BankSelect = NsGetValue (BankReg);


        DEBUG_PRINT (ACPI_INFO, ("PrepBankFieldValue: set nte %p (%4.4s) val = %p\n",
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
        NsSetValue ((NsHandle) ObjStack[ObjStackTop], ObjDesc,
                    (UINT8) NsGetType ((NsHandle) ObjStack[ObjStackTop]));
    }


    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    PrepIndexFieldValue
 *
 * PARAMETERS:  NsHandle    IndexReg   Index register
 *              NsHandle    DataReg    Data register
 *              UINT8       FldFlg     Access, LockRule, UpdateRule
 *              INT32       FldPos     field position
 *              INT32       FldLen     field length
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Construct an OBJECT_DESCRIPTOR of type IndexField and connect
 *              it to the nte whose handle is at ObjStack[ObjStackTop]
 *
 * ALLOCATION:
 *  Reference   Size                    Pool    Owner       Description
 *  nte.ValDesc s(OBJECT_DESCRIPTOR)    bu      amlexec     Field descriptor
 *
 ****************************************************************************/

INT32
PrepIndexFieldValue (NsHandle IndexReg, NsHandle DataReg,
                        UINT8 FldFlg, INT32 FldPos, INT32 FldLen)
{
    OBJECT_DESCRIPTOR   *ObjDesc = NULL;
    INT32               Excep = S_SUCCESS;


    FUNCTION_TRACE ("PrepIndexFieldValue");


    if (!IndexReg || !DataReg)
    {
        DEBUG_PRINT (ACPI_ERROR, ("PrepIndexFieldValue: null handle\n"));
        Excep = S_ERROR;
    }

    else if (!(ObjDesc = AllocateObjectDesc (&KDT[4])))
    {   
        /*  unable to allocate new object descriptor    */

        Excep = S_ERROR;
    }

    if (S_SUCCESS == Excep)
    {   
        /* ObjDesc, IndexRegion, and DataReg valid  */

        ObjDesc->ValType = (UINT8) TYPE_IndexField;
        if (TYPE_IndexField != ObjDesc->IndexField.ValType)
        {
            /* See comments in PrepDefFieldValue() re unexpected C behavior */
        
            ObjDesc->IndexField.ValType = 0x005a;
            DEBUG_PRINT (ACPI_ERROR, (
                    "PrepIndexFieldValue: internal failure %p %02x %02x %02x %02x\n",
                    ObjDesc, ((UINT8 *) ObjDesc)[0], ((UINT8 *) ObjDesc)[1], ((UINT8 *) ObjDesc)[2],
                    ((UINT8 *) ObjDesc)[3]));
            DELETE (ObjDesc);
            return S_ERROR;
        }
    }


    if (S_SUCCESS == Excep)
    {   
        /*  ObjDesc, IndexRegion, and DataReg, and ObjDesc->IndexField.ValTyp valid */
    
        ObjDesc->IndexField.Access        = (FldFlg & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT;
        ObjDesc->IndexField.LockRule      = (FldFlg & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT;
        ObjDesc->IndexField.UpdateRule    = (FldFlg & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT;
        ObjDesc->IndexField.DatLen        = (UINT16) FldLen;

        /* XXX - should use width of data register, not hardcoded 8 */

        DEBUG_PRINT (ACPI_INFO, (" ** PrepIndexFieldValue: hard 8 **\n"));

        ObjDesc->IndexField.BitOffset = (UINT16) FldPos % 8;
        ObjDesc->IndexField.IndexVal  = (UINT32) FldPos / 8;
        ObjDesc->IndexField.Index     = IndexReg;
        ObjDesc->IndexField.Data      = DataReg;

        DEBUG_PRINT (ACPI_INFO, ("PrepIndexFieldValue: set nte %p (%4.4s) val = %p\n",
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
        NsSetValue ((NsHandle) ObjStack[ObjStackTop], ObjDesc,
                    (UINT8) NsGetType ((NsHandle) ObjStack[ObjStackTop]));
    }

    return Excep;
}

/*****************************************************************************
 * 
 * FUNCTION:    PrepStack
 *
 * PARAMETERS:  char *Types       String showing operand types needed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Convert stack entries to required types
 *
 *      Each character in Types represents one required operand
 *      and indicates the required ValType:
 *          l => Lvalue, also accepts an entry which is an NsHandle
 *                  instead of an (OBJECT_DESCRIPTOR *))
 *          n => Number
 *          s => String or Buffer
 *          b => Buffer
 *          i => If
 *          p => Package
 *      The corresponding stack entry will be converted to the
 *      required type if possible, else return S_ERROR.
 *
 ****************************************************************************/

INT32
PrepStack (char *Types)
{
    OBJECT_DESCRIPTOR **    StackPtr = (OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop];
    INT32                   Excep;


    FUNCTION_TRACE ("PrepStack");


    /* 
     * Ensure room on stack for GetRvalue() to operate
     * without clobbering top existing entry.
     */

    Excep = PushIfExec (MODE_Exec);
    if (S_SUCCESS != Excep)
    {
        return Excep;
    }

    /* 
     * Normal exit is with *Types == '\0' at end of string.
     * Function will return S_ERROR from within the loop upon
     * finding an entry which is not, and cannot be converted
     * to, the required type; if stack underflows; or upon
     * finding a NULL stack entry (which "should never happen").
     */

    while (*Types)
    {
        UINT8       bTypeFound;
        char        TypeFound[30];
        char        *TypeFoundPtr;


        if (!StackPtr || !*StackPtr)
        {
            DEBUG_PRINT (ACPI_ERROR, ("PrepStack:internal error: null stack entry\n"));
            ObjStackTop--;
            return S_ERROR;
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
            if (IsNsHandle (*StackPtr))             /* direct name ptr OK as-is */
            {
                break;
            }

            if (TYPE_Lvalue != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, ("PrepStack: Needed Lvalue, found %s\n",
                            TypeFoundPtr));
                ObjStackTop--;
                return S_ERROR;
            }

            if (AML_NameOp == (*StackPtr)->Lvalue.OpCode)
            {
                /* Convert indirect name ptr to direct name ptr */
                
                NsHandle TempHandle = (*StackPtr)->Lvalue.Ref;
                DELETE (*StackPtr);
                (*StackPtr) = TempHandle;
            }
            break;

        case 'n':                                   /* need Number */
            Excep = GetRvalue (StackPtr);

            DEBUG_PRINT (TRACE_EXEC,
                          ("PrepStack:n: GetRvalue returned %s\n", RV[Excep]));

            if (S_SUCCESS != Excep)
            {
                ObjStackTop--;
                return Excep;
            }

            if (TYPE_Number != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, ("PrepStack: Needed Number, found %s\n",
                            TypeFoundPtr));
                ObjStackTop--;
                return S_ERROR;
            }
            break;

        case 's':                                   /* need String (or Buffer) */
            if ((Excep = GetRvalue (StackPtr)) != S_SUCCESS)
            {
                ObjStackTop--;
                return Excep;
            }

            DEBUG_PRINT (TRACE_EXEC, ("GetRvalue returned S_SUCCESS\n"));

            if (TYPE_String != (*StackPtr)->ValType &&
                TYPE_Buffer != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "PrepStack: Needed String or Buffer, found %s\n",
                        TypeFoundPtr));
                ObjStackTop--;
                return S_ERROR;
            }
            break;

        case 'b':                                   /* need Buffer */
            if ((Excep = GetRvalue(StackPtr)) != S_SUCCESS)
            {
                ObjStackTop--;
                return Excep;
            }

            DEBUG_PRINT (TRACE_EXEC, ("GetRvalue returned S_SUCCESS\n"));

            if (TYPE_Buffer != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, ("PrepStack: Needed Buffer, found %s\n",
                            TypeFoundPtr));
                ObjStackTop--;
                return S_ERROR;
            }
            break;

        case 'i':                                   /* need If */
            if (TYPE_If != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, ("PrepStack: Needed If, found %s\n",
                        TypeFoundPtr));
                ObjStackTop--;
                return S_ERROR;
            }
            break;

        case 'p':                                   /* need Package */
            if ((Excep = GetRvalue (StackPtr)) != S_SUCCESS)
            {
                ObjStackTop--;
                return Excep;
            }

            DEBUG_PRINT (TRACE_EXEC, ("GetRvalue returned S_SUCCESS\n"));

            if (TYPE_Package != (*StackPtr)->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, ("PrepStack: Needed Package, found %s\n",
                            TypeFoundPtr));
                ObjStackTop--;
                return S_ERROR;
            }
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR, (
                    "PrepStack:internal error Unknown type flag %02x\n",
                    *--Types));
            ObjStackTop--;
            return S_ERROR;

        }   /* switch (*Types++) */


        /* 
         * If more operands needed, decrement StackPtr to point
         * to next operand on stack (after checking for underflow).
         */
        if (*Types)
        {
            /* Don't try to decrement below bottom of stack */
            
            if ((OBJECT_DESCRIPTOR **) &ObjStack[0] == StackPtr)
            {
                DEBUG_PRINT (ACPI_ERROR, ("PrepStack: not enough operands\n"));
                ObjStackTop--;
                return S_ERROR;
            }

            StackPtr--;
        }

    }   /* while (*Types) */

    ObjStackTop--;
    return S_SUCCESS;
}




