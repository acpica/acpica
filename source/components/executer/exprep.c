
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
#include <interp.h>
#include <amlcode.h>
#include <namesp.h>
#include <parser.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("ieprep");


/*****************************************************************************
 * 
 * FUNCTION:    AmlResolveOperands
 *
 * PARAMETERS:  Opcode              Opcode being interpreted
 *              StackPtr            Top of operand stack
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert stack entries to required types
 *
 *      Each nibble in ArgTypes represents one required operand
 *      and indicates the required Type:
 *
 *      The corresponding stack entry will be converted to the
 *      required type if possible, else return an exception
 *
 ****************************************************************************/

ACPI_STATUS
AmlResolveOperands (
    UINT16                  Opcode,
    ACPI_OBJECT_INTERNAL    **StackPtr)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_STATUS             Status = AE_OK;
    UINT8                   ObjectType;
    ACPI_HANDLE             TempHandle;
    UINT32                  ArgTypes;
    ACPI_OP_INFO            *OpInfo;
    UINT32                  ThisArgType;


    FUNCTION_TRACE_U32 ("AmlResolveOperands", Opcode);


    OpInfo = PsGetOpcodeInfo (Opcode);
    if (!OpInfo)
    {
        return_ACPI_STATUS (AE_AML_BAD_OPCODE)
    }


    ArgTypes = OpInfo->RuntimeArgs;
    if (ArgTypes == ARGI_INVALID_OPCODE)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlResolveOperands: Internal error - %X is not a runtime opcode\n", Opcode));
        Status = AE_AML_INTERNAL;
        goto Cleanup;
    }

    DEBUG_PRINT (TRACE_EXEC, ("AmlResolveOperands: Opcode %X OperandTypes=%X \n", Opcode, ArgTypes));


   /* 
     * Normal exit is with *Types == '\0' at end of string.
     * Function will return an exception from within the loop upon
     * finding an entry which is not, and cannot be converted
     * to, the required type; if stack underflows; or upon
     * finding a NULL stack entry (which "should never happen").
     */

    while (GET_CURRENT_ARG_TYPE (ArgTypes))
    {
        if (!StackPtr || !*StackPtr)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveOperands: Internal error - null stack entry at %X\n", StackPtr));
            Status = AE_AML_INTERNAL;
            goto Cleanup;
        }

        /* Extract useful items */

        ObjDesc = *StackPtr;

        /* Decode the descriptor type */

        if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))
        {
            /* NTE */

            ObjectType = ((NAME_TABLE_ENTRY *) ObjDesc)->Type;
        }

        else if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_ACPI_OBJ))
        {
            /* ACPI internal object */

            ObjectType = ObjDesc->Common.Type;

            /* Check for bad ACPI_OBJECT_TYPE */

            if (!AmlValidateObjectType (ObjectType))
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlResolveOperands: Bad operand object type [0x%x]\n", ObjectType));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
        
            if (ObjectType == (UINT8) INTERNAL_TYPE_Reference)
            {
                /*
                 * Decode the Reference 
                 */

                OpInfo = PsGetOpcodeInfo (Opcode);
                if (!OpInfo)
                {
                    return_ACPI_STATUS (AE_AML_BAD_OPCODE)
                }


                switch (ObjDesc->Reference.OpCode)
                {
                case AML_ZeroOp:
                case AML_OneOp:
                case AML_OnesOp:
                case AML_DebugOp:
                case AML_NameOp:
                case AML_IndexOp:
                case AML_ArgOp:
                case AML_LocalOp:

                    DEBUG_PRINT (ACPI_INFO, ("Reference Opcode: %s\n", OpInfo->Name));
                    break;
            
                default:
                    DEBUG_PRINT (ACPI_INFO, ("Reference Opcode: Unknown [%02x]\n", ObjDesc->Reference.OpCode));

                    Status = AE_AML_OPERAND_TYPE;
                    goto Cleanup;
                    break;
                }
            }
        
        }
        
        else
        {
            /* Invalid descriptor */

            DEBUG_PRINT (ACPI_ERROR, ("Bad descriptor type 0x%X in Obj %p\n", ObjDesc->Common.DataType, ObjDesc));

            Status = AE_AML_OPERAND_TYPE;
            goto Cleanup;
        }


        /*
         * Decode a character from the type string
         */

        ThisArgType = GET_CURRENT_ARG_TYPE (ArgTypes);
        INCREMENT_ARG_LIST (ArgTypes);


        switch (ThisArgType)
        {

        case ARGI_REFERENCE:   /* Reference */
        case ARGI_TARGETREF:

            /* Need an operand of type INTERNAL_TYPE_Reference */

            if (VALID_DESCRIPTOR_TYPE (ObjDesc, DESC_TYPE_NTE))             /* direct name ptr OK as-is */
            {
                break;
            }

            if (INTERNAL_TYPE_Reference != ObjectType)
            {
                DEBUG_PRINT (ACPI_INFO, ("AmlResolveOperands: Needed Reference, found %s Obj=%p\n",
                                CmGetTypeName (ObjectType), *StackPtr));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }

            if (AML_NameOp == ObjDesc->Reference.OpCode)
            {
                /* Convert an indirect name ptr to direct name ptr and put it on the stack */
                
                TempHandle = ObjDesc->Reference.Object;
                CmRemoveReference (ObjDesc);
                (*StackPtr) = TempHandle;
            }
            break;


        case ARGI_NUMBER:   /* Number */

            /* Need an operand of type ACPI_TYPE_Number */

            if ((Status = AmlResolveToValue (StackPtr)) != AE_OK)
            {
                goto Cleanup;
            }

            if (ACPI_TYPE_Number != (*StackPtr)->Common.Type)
            {
                DEBUG_PRINT (ACPI_INFO, ("AmlResolveOperands: Needed Number, found %s Obj=%p\n",
                                CmGetTypeName (ObjectType), *StackPtr));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
            break;


        case ARGI_STRING:

            /* Need an operand of type ACPI_TYPE_String or ACPI_TYPE_Buffer */

            if ((Status = AmlResolveToValue (StackPtr)) != AE_OK)
            {
                goto Cleanup;
            }

            if ((ACPI_TYPE_String != (*StackPtr)->Common.Type) &&
                (ACPI_TYPE_Buffer != (*StackPtr)->Common.Type))
            {
                DEBUG_PRINT (ACPI_INFO, ("AmlResolveOperands: Needed String or Buffer, found %s Obj=%p\n",
                                CmGetTypeName (ObjectType), *StackPtr));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
            break;


        case ARGI_BUFFER:

            /* Need an operand of type ACPI_TYPE_Buffer */

            if ((Status = AmlResolveToValue(StackPtr)) != AE_OK)
            {
                goto Cleanup;
            }

            if (ACPI_TYPE_Buffer != (*StackPtr)->Common.Type)
            {
                DEBUG_PRINT (ACPI_INFO, ("AmlResolveOperands: Needed Buffer, found %s Obj=%p\n",
                                CmGetTypeName (ObjectType), *StackPtr));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
            break;


        case ARGI_MUTEX:

            /* Need an operand of type ACPI_TYPE_Mutex */

            if ((Status = AmlResolveToValue(StackPtr)) != AE_OK)
            {
                goto Cleanup;
            }

            if (ACPI_TYPE_Mutex != (*StackPtr)->Common.Type)
            {
                DEBUG_PRINT (ACPI_INFO, ("AmlResolveOperands: Needed Mutex, found %s Obj=%p\n",
                                CmGetTypeName (ObjectType), *StackPtr));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
            break;


        case ARGI_EVENT:

            /* Need an operand of type ACPI_TYPE_Event */

            if ((Status = AmlResolveToValue(StackPtr)) != AE_OK)
            {
                goto Cleanup;
            }

            if (ACPI_TYPE_Event != (*StackPtr)->Common.Type)
            {
                DEBUG_PRINT (ACPI_INFO, ("AmlResolveOperands: Needed Event, found %s Obj=%p\n",
                                CmGetTypeName (ObjectType), *StackPtr));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
            break;


        case ARGI_REGION:

            /* Need an operand of type ACPI_TYPE_Region */

            if ((Status = AmlResolveToValue(StackPtr)) != AE_OK)
            {
                goto Cleanup;
            }

            if (ACPI_TYPE_Region != (*StackPtr)->Common.Type)
            {
                DEBUG_PRINT (ACPI_INFO, ("AmlResolveOperands: Needed Region, found %s Obj=%p\n",
                                CmGetTypeName (ObjectType), *StackPtr));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
            break;


         case ARGI_IF:   /* If */

            /* Need an operand of type INTERNAL_TYPE_If */

            if (INTERNAL_TYPE_If != (*StackPtr)->Common.Type)
            {
                DEBUG_PRINT (ACPI_INFO, ("AmlResolveOperands: Needed If, found %s Obj=%p\n",
                                CmGetTypeName (ObjectType), *StackPtr));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
            break;


        case ARGI_PACKAGE:   /* Package */

            /* Need an operand of type ACPI_TYPE_Package */

            if ((Status = AmlResolveToValue (StackPtr)) != AE_OK)
            {
                goto Cleanup;
            }

            if (ACPI_TYPE_Package != (*StackPtr)->Common.Type)
            {
                DEBUG_PRINT (ACPI_INFO, ("AmlResolveOperands: Needed Package, found %s Obj=%p\n",
                                CmGetTypeName (ObjectType), *StackPtr));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
            break;


        case ARGI_ANYTYPE:

            /*
             * TBD: how to handle this case:
             *      Store (RefOf (NAME), Local0))
             */

            if ((Status = AmlResolveToValue (StackPtr)) != AE_OK)
            {
                goto Cleanup;
            }

            /* All types OK, so we don't perform any typechecks */

            break;


        case ARGI_DATAOBJECT:


            if ((Status = AmlResolveToValue (StackPtr)) != AE_OK)
            {
                goto Cleanup;
            }

            /* Need a buffer, string, or package */

            if (((*StackPtr)->Common.Type != ACPI_TYPE_Buffer) &&
                ((*StackPtr)->Common.Type != ACPI_TYPE_String) &&
                ((*StackPtr)->Common.Type != ACPI_TYPE_Package))
            {
                DEBUG_PRINT (ACPI_INFO, ("AmlResolveOperands: Needed Buf/Str/Pkg, found %s Obj=%p\n",
                                CmGetTypeName (ObjectType), *StackPtr));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
            break;


        case ARGI_COMPLEXOBJ:

            if ((Status = AmlResolveToValue (StackPtr)) != AE_OK)
            {
                goto Cleanup;
            }

            /* Need a buffer or package */

            if (((*StackPtr)->Common.Type != ACPI_TYPE_Buffer) &&
                ((*StackPtr)->Common.Type != ACPI_TYPE_Package))
            {
                DEBUG_PRINT (ACPI_INFO, ("AmlResolveOperands: Needed Package, Buf/Pkg %s Obj=%p\n",
                                CmGetTypeName (ObjectType), *StackPtr));
                Status = AE_AML_OPERAND_TYPE;
                goto Cleanup;
            }
            break;


        /* Unknown abbreviation passed in */

        default:
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveOperands: Internal error - Unknown arg type %X\n",
                        ThisArgType));
            Status = AE_BAD_PARAMETER;
            goto Cleanup;

        }   /* switch (*Types++) */


        /* 
         * If more operands needed, decrement StackPtr to point
         * to next operand on stack (after checking for underflow).
         */
        if (GET_CURRENT_ARG_TYPE (ArgTypes))
        {
            StackPtr--;
        }

    }   /* while (*Types) */


Cleanup:

  return_ACPI_STATUS (Status);
}



/*****************************************************************************
 * 
 * FUNCTION:    AmlDecodeFieldAccessType
 *
 * PARAMETERS:  Access          - Encoded field access bits
 *
 * RETURN:      Field granularity (8, 16, or 32)
 *
 * DESCRIPTION: Decode the AccessType bits of a field definition.
 *
 ****************************************************************************/

UINT32
AmlDecodeFieldAccessType (
    UINT32                  Access)
{
 
    switch (Access)
    {
    case ACCESS_AnyAcc:
        return 8;
        break;

    case ACCESS_ByteAcc:
        return 8;
        break;

    case ACCESS_WordAcc:
        return 16;
        break;

    case ACCESS_DWordAcc:
        return 32;
        break;

    default:
        /* Invalid field access type */

        DEBUG_PRINT (ACPI_ERROR, ("AmlDecodeFieldAccessType: Unknown field access type %x\n",
                        Access));
        return 0;
    }
}



/*****************************************************************************
 * 
 * FUNCTION:    AmlPrepCommonFieldObjec
 *
 * PARAMETERS:  ObjDesc             - The field object
 *              FieldFlags          - Access, LockRule, or UpdateRule.
 *                                    The format of a FieldFlag is described
 *                                    in the ACPI specification and in <aml.h>
 *              FieldPosition       - Field position
 *              FieldLength         - Field length
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize the areas of the field object that are common
 *              to the various types of fields.
 *
 ****************************************************************************/

ACPI_STATUS
AmlPrepCommonFieldObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc,
    UINT8                   FieldFlags, 
    UINT8                   FieldAttribute,
    UINT32                  FieldPosition, 
    UINT32                  FieldLength)
{
    UINT32                  Granularity;


    FUNCTION_TRACE ("AmlPrepCommonFieldObject");


    /*
     * Note: the structure being initialized is the
     * ACPI_COMMON_FIELD_INFO;  Therefore, we can just use the Field union to
     * access this common area.  No structure fields outside of the common area
     * are initialized by this procedure.
     */

    /* Decode the FieldFlags */

    ObjDesc->Field.Access           = (UINT8) ((FieldFlags & ACCESS_TYPE_MASK) >> ACCESS_TYPE_SHIFT);
    ObjDesc->Field.LockRule         = (UINT8) ((FieldFlags & LOCK_RULE_MASK) >> LOCK_RULE_SHIFT);
    ObjDesc->Field.UpdateRule       = (UINT8) ((FieldFlags & UPDATE_RULE_MASK) >> UPDATE_RULE_SHIFT);

    /* Other misc fields */

    ObjDesc->Field.Length           = (UINT16) FieldLength;
    ObjDesc->Field.AccessAttribute  = FieldAttribute;

    /* Decode the access type so we can compute offsets */

    Granularity = AmlDecodeFieldAccessType (ObjDesc->Field.Access);
    if (!Granularity)
    {
        return_ACPI_STATUS (AE_AML_OPERAND_VALUE);
    }

    /* Access granularity based fields */

    ObjDesc->Field.Granularity      = (UINT8) Granularity;
    ObjDesc->Field.BitOffset        = (UINT8) (FieldPosition % Granularity);
    ObjDesc->Field.Offset           = (UINT32) FieldPosition / Granularity;


    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlPrepDefFieldValue
 *
 * PARAMETERS:  ThisEntry           - Owning NTE
 *              Region              - Region in which field is being defined
 *              FieldFlags          - Access, LockRule, or UpdateRule.
 *                                    The format of a FieldFlag is described
 *                                    in the ACPI specification and in <aml.h>
 *              FieldPosition       - Field position
 *              FieldLength         - Field length
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Construct an ACPI_OBJECT_INTERNAL of type DefField and 
 *              connect it to the parent NTE.
 *
 ****************************************************************************/

ACPI_STATUS
AmlPrepDefFieldValue (
    NAME_TABLE_ENTRY        *ThisEntry,
    ACPI_HANDLE             Region, 
    UINT8                   FieldFlags,
    UINT8                   FieldAttribute,
    UINT32                  FieldPosition, 
    UINT32                  FieldLength)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    INT32                   Type;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlPrepDefFieldValue");


    /* Parameter validation */

    if (!Region)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepDefFieldValue: null Region\n"));
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }

    Type = NsGetType (Region);
    if (Type != ACPI_TYPE_Region)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepDefFieldValue: Needed Region, found %d %s\n",
                        Type, CmGetTypeName (Type)));
        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    }

    /* Allocate a new object */

    ObjDesc = CmCreateInternalObject (INTERNAL_TYPE_DefField);
    if (!ObjDesc)
    {   
        return_ACPI_STATUS (AE_NO_MEMORY);
    }


    /* ObjDesc and Region valid */

    DUMP_OPERANDS ((ACPI_OBJECT_INTERNAL **) &ThisEntry, IMODE_Execute, "AmlPrepDefFieldValue", 1, "case DefField");
    DUMP_OPERANDS ((ACPI_OBJECT_INTERNAL **) &Region, IMODE_Execute, "AmlPrepDefFieldValue", 1, "case DefField");

    /* Initialize areas of the object that are common to all fields */

    Status = AmlPrepCommonFieldObject (ObjDesc, FieldFlags, FieldAttribute, FieldPosition, FieldLength);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Initialize areas of the object that are specific to this field type */

    ObjDesc->Field.Container = NsGetAttachedObject (Region);

    /* An additional reference for the container */

    CmUpdateObjectReference (ObjDesc->Field.Container, REF_INCREMENT);


    /* Debug info */

    DEBUG_PRINT (ACPI_INFO, ("AmlPrepDefFieldValue: bitoff=%X off=%X gran=%X\n",
                    ObjDesc->Field.BitOffset, ObjDesc->Field.Offset, ObjDesc->Field.Granularity));

    DEBUG_PRINT (ACPI_INFO, ("AmlPrepDefFieldValue: set nte %p (%4.4s) val = %p\n",
                    ThisEntry, &(ThisEntry->Name), ObjDesc));

    DUMP_STACK_ENTRY (ObjDesc);
    DUMP_ENTRY (Region, ACPI_INFO);
    DEBUG_PRINT (ACPI_INFO, ("\t%p \n", ObjDesc->Field.Container));
    if (ObjDesc->Field.Container)
    {
        DUMP_STACK_ENTRY (ObjDesc->Field.Container);
    }
    DEBUG_PRINT (ACPI_INFO, ("============================================================\n"));

    /* 
     * Store the constructed descriptor (ObjDesc) into the nte whose
     * handle is on TOS, preserving the current type of that nte.
     */
    Status = NsAttachObject ((ACPI_HANDLE) ThisEntry, ObjDesc,
                                (UINT8) NsGetType ((ACPI_HANDLE) ThisEntry));

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlPrepBankFieldValue
 *
 * PARAMETERS:  ThisEntry           - Owning NTE
 *              Region              - Region in which field is being defined
 *              BankReg             - Bank selection register
 *              BankVal             - Value to store in selection register
 *              FieldFlags          - Access, LockRule, or UpdateRule
 *              FieldPosition       - Field position
 *              FieldLength         - Field length
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Construct an ACPI_OBJECT_INTERNAL of type BankField and 
 *              connect it to the parent NTE.
 *
 ****************************************************************************/

ACPI_STATUS
AmlPrepBankFieldValue (
    NAME_TABLE_ENTRY        *ThisEntry,
    ACPI_HANDLE             Region, 
    ACPI_HANDLE             BankReg, 
    UINT32                  BankVal,
    UINT8                   FieldFlags, 
    UINT8                   FieldAttribute,
    UINT32                  FieldPosition, 
    UINT32                  FieldLength)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    INT32                   Type;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlPrepBankFieldValue");


    /* Parameter validation */

    if (!Region)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepBankFieldValue: null Region\n"));
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }

    Type = NsGetType (Region);
    if (Type != ACPI_TYPE_Region)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepBankFieldValue: Needed Region, found %d %s\n",
                        Type, CmGetTypeName (Type)));
        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    }

    /* Allocate a new object */

    ObjDesc = CmCreateInternalObject (INTERNAL_TYPE_BankField);
    if (!ObjDesc)
    {   
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /*  ObjDesc and Region valid    */

    DUMP_OPERANDS ((ACPI_OBJECT_INTERNAL **) &ThisEntry, IMODE_Execute, "AmlPrepBankFieldValue", 1, "case BankField");
    DUMP_OPERANDS ((ACPI_OBJECT_INTERNAL **) &Region, IMODE_Execute, "AmlPrepBankFieldValue", 1, "case BankField");

    /* Initialize areas of the object that are common to all fields */

    Status = AmlPrepCommonFieldObject (ObjDesc, FieldFlags, FieldAttribute, FieldPosition, FieldLength);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Initialize areas of the object that are specific to this field type */

    ObjDesc->BankField.Value        = BankVal;
    ObjDesc->BankField.Container    = NsGetAttachedObject (Region);
    ObjDesc->BankField.BankSelect   = NsGetAttachedObject (BankReg);

    /* An additional reference for the container and bank select */
    /* TBD: is "BankSelect" ever a real internal object?? */

    CmUpdateObjectReference (ObjDesc->BankField.Container, REF_INCREMENT);
    CmUpdateObjectReference (ObjDesc->BankField.BankSelect, REF_INCREMENT);

    /* Debug info */

    DEBUG_PRINT (ACPI_INFO, ("AmlPrepBankFieldValue: bitoff=%X off=%X gran=%X\n",
                    ObjDesc->BankField.BitOffset, ObjDesc->BankField.Offset, ObjDesc->Field.Granularity));

    DEBUG_PRINT (ACPI_INFO, ("AmlPrepBankFieldValue: set nte %p (%4.4s) val = %p\n",
                    ThisEntry, &(ThisEntry->Name), ObjDesc));
    
    DUMP_STACK_ENTRY (ObjDesc);
    DUMP_ENTRY (Region, ACPI_INFO);
    DUMP_ENTRY (BankReg, ACPI_INFO);
    DEBUG_PRINT (ACPI_INFO, ("============================================================\n"));

    /* 
     * Store the constructed descriptor (ObjDesc) into the nte whose
     * handle is on TOS, preserving the current type of that nte.
     */
    Status = NsAttachObject ((ACPI_HANDLE) ThisEntry, ObjDesc,
                                (UINT8) NsGetType ((ACPI_HANDLE) ThisEntry));

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlPrepIndexFieldValue
 *
 * PARAMETERS:  ThisEntry           - Owning NTE
 *              IndexReg            - Index register
 *              DataReg             - Data register
 *              FieldFlags          - Access, LockRule, or UpdateRule
 *              FieldPosition       - Field position
 *              FieldLength         - Field length
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Construct an ACPI_OBJECT_INTERNAL of type IndexField and 
 *              connect it to the parent NTE.
 *
 ****************************************************************************/

ACPI_STATUS
AmlPrepIndexFieldValue (
    NAME_TABLE_ENTRY        *ThisEntry,
    ACPI_HANDLE             IndexReg, 
    ACPI_HANDLE             DataReg,
    UINT8                   FieldFlags, 
    UINT8                   FieldAttribute,
    UINT32                  FieldPosition, 
    UINT32                  FieldLength)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlPrepIndexFieldValue");


    /* Parameter validation */

    if (!IndexReg || !DataReg)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlPrepIndexFieldValue: null handle\n"));
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }

    /* Allocate a new object descriptor */

    ObjDesc = CmCreateInternalObject (INTERNAL_TYPE_IndexField);
    if (!ObjDesc)
    {   
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Initialize areas of the object that are common to all fields */

    Status = AmlPrepCommonFieldObject (ObjDesc, FieldFlags, FieldAttribute, FieldPosition, FieldLength);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Initialize areas of the object that are specific to this field type */

    ObjDesc->IndexField.Value       = (UINT32) (FieldPosition / ObjDesc->Field.Granularity);
    ObjDesc->IndexField.Index       = IndexReg;
    ObjDesc->IndexField.Data        = DataReg;

    /* Debug info */

    DEBUG_PRINT (ACPI_INFO, ("AmlPrepIndexFieldValue: bitoff=%X off=%X gran=%X\n",
                    ObjDesc->IndexField.BitOffset, ObjDesc->IndexField.Offset, ObjDesc->Field.Granularity));

    DEBUG_PRINT (ACPI_INFO, ("AmlPrepIndexFieldValue: set nte %p (%4.4s) val = %p\n",
                    ThisEntry, &(ThisEntry->Name), ObjDesc));

    DUMP_STACK_ENTRY (ObjDesc);
    DUMP_ENTRY (IndexReg, ACPI_INFO);
    DUMP_ENTRY (DataReg, ACPI_INFO);
    DEBUG_PRINT (ACPI_INFO, ("============================================================\n"));

    /* 
     * Store the constructed descriptor (ObjDesc) into the nte whose
     * handle is on TOS, preserving the current type of that nte.
     */
    Status = NsAttachObject ((ACPI_HANDLE) ThisEntry, ObjDesc,
                                (UINT8) NsGetType ((ACPI_HANDLE) ThisEntry));

    return_ACPI_STATUS (Status);
}

