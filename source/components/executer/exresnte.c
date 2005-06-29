
/******************************************************************************
 * 
 * Module Name: iresnte - AML Interpreter object resolution
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

#define __IRESNTE_C__

#include <acpi.h>
#include <amlcode.h>
#include <parser.h>
#include <dispatch.h>
#include <interp.h>
#include <namesp.h>
#include <tables.h>
#include <events.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("iresnte");


/*****************************************************************************
 * 
 * FUNCTION:    AmlResolveEntryToValue
 *
 * PARAMETERS:  StackPtr        - Pointer to a location on a stack that contains
 *                                a ptr to an NTE
 *                                  
 * RETURN:      Status
 *
 * DESCRIPTION: Resolve a NAME_TABLE_ENTRY (nte, A.K.A. a "direct name pointer")
 *
 * Note: for some of the data types, the pointer attached to the NTE can be
 * either a pointer to an actual internal object or a pointer into the AML
 * stream itself.  These types are currently:
 *
 *      ACPI_TYPE_Number
 *      ACPI_TYPE_String
 *      ACPI_TYPE_Buffer
 *      ACPI_TYPE_Mutex
 *      ACPI_TYPE_Package
 *
 ****************************************************************************/

ACPI_STATUS
AmlResolveEntryToValue (
    NAME_TABLE_ENTRY        **StackPtr)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OBJECT_INTERNAL    *ValDesc = NULL;
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    NAME_TABLE_ENTRY        *StackEntry;
    UINT8                   *AmlPointer = NULL;
    ACPI_OBJECT_TYPE        EntryType;
    BOOLEAN                 Locked;
    BOOLEAN                 AttachedAmlPointer = FALSE;
    UINT8                   AmlOpcode = 0;
    UINT32                  TempVal;
    ACPI_OBJECT_TYPE        ObjectType;


    FUNCTION_TRACE ("AmlResolveEntryToValue");

    StackEntry = *StackPtr;


    /* 
     * The stack pointer is a "Direct name ptr", and points to a
     * a NAME_TABLE_ENTRY (nte).  Get the pointer that is attached to
     * the nte.
     */

    ValDesc     = NsGetAttachedObject ((ACPI_HANDLE) StackEntry);
    EntryType   = NsGetType ((ACPI_HANDLE) StackEntry);

    DEBUG_PRINT (TRACE_EXEC, ("AmlResolveEntryToValue: Entry=%p ValDesc=%p Type=%X\n", 
                    StackEntry, ValDesc, EntryType));


    /*
     * The ValDesc attached to the NTE can be either:
     * 1) An internal ACPI object 
     * 2) A pointer into the AML stream (into one of the ACPI system tables)
     */

    if (TbSystemTablePointer (ValDesc))
    {
        AttachedAmlPointer = TRUE;
        AmlOpcode = *((UINT8 *) ValDesc);
        AmlPointer = ((UINT8 *) ValDesc) + 1;

        DEBUG_PRINT (TRACE_EXEC, ("AmlResolveEntryToValue: Unparsed AML: %p Len=%X\n", 
                        AmlOpcode, AmlPointer));
    }


    /*
     * Action is based on the type of the NTE, which indicates the type
     * of the attached object or pointer
     */
    switch (EntryType)
    {

    case ACPI_TYPE_Package:

        /* 
         * ValDesc should point to either an ACPI_OBJECT_INTERNAL of
         * type Package, or an initialization in the AML stream.
         */
        if (!ValDesc)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Internal error - null ValDesc\n"));
            return_ACPI_STATUS (AE_AML_NO_OPERAND);
        }


        if (AttachedAmlPointer)
        {
#if defined  _RPARSER
            if (AML_PackageOp == AmlOpcode)
            {
                /* 
                 * The value pointer in the name table entry
                 * points to a package definition in the AML stream.
                 * Convert it to an object.
                 */

                if (AE_OK != (Status = PsxObjStackPush ()))             /* ObjStack */
                {
                    return_ACPI_STATUS (Status);
                }

                if (AE_OK == (Status = AmlPkgPushExec (AmlPointer, 0L)) &&          /* PkgStack */
                    AE_OK == (Status = AmlDoPkg (ACPI_TYPE_Package, IMODE_Execute)) &&
                    AE_OK == (Status = AmlPkgPopExec ()))                           /* PkgStack */
                {
                    NsAttachObject ((ACPI_HANDLE) StackEntry, PsxObjStackGetValue (0),
                                    (UINT8) ACPI_TYPE_Package);

                    /* Refresh local value pointer to reflect newly set value */
                
                    ValDesc = NsGetAttachedObject ((ACPI_HANDLE) StackEntry);
                    PsxObjStackPop (1);
                }
            
                else
                {
                    PsxObjStackPop (1);
                    return_ACPI_STATUS (Status);
                }
            }

            else
            {
                /* Aml Opcode is not a package op */

                DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Not a PackageOp opcode (%x)\n",
                                AmlOpcode));
                return_ACPI_STATUS (AE_AML_BAD_OPCODE);
            }
#else
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Unparsed Packages not supported!\n"));
            return_ACPI_STATUS (AE_NOT_IMPLEMENTED);
#endif
        }
        
        /* ValDesc is an internal object in all cases by the time we get here */

        if (!ValDesc || (ACPI_TYPE_Package != ValDesc->Common.Type))
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Internal error - Bad package value\n"));
            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }

        /* Return an additional reference to the object */

        ObjDesc = ValDesc;
        CmAddReference (ObjDesc);
        break;


    case ACPI_TYPE_Buffer:

        if (!ValDesc)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Internal error - null Buffer ValuePtr\n"));
            return_ACPI_STATUS (AE_AML_NO_OPERAND);
        }



       if (AttachedAmlPointer)
        {
#if defined _RPARSER
            if (AML_BufferOp == AmlOpcode)
            {
                /* 
                 * The value pointer in the name table entry
                 * points to a buffer definition in the AML stream.
                 * Convert it to an object.
                 */
                if (AE_OK != (Status = PsxObjStackPush ()))                /* ObjStack */
                {
                    return_ACPI_STATUS (Status);
                }

                if (AE_OK == (Status = AmlPkgPushExec (AmlPointer, 0L)) &&          /* PkgStack */
                    AE_OK == (Status = AmlDoPkg (ACPI_TYPE_Buffer, IMODE_Execute)) &&
                    AE_OK == (Status = AmlPkgPopExec ()))                           /* PkgStack */
                {
                    NsAttachObject ((ACPI_HANDLE) StackEntry, PsxObjStackGetValue (0),
                                    (UINT8) ACPI_TYPE_Buffer);
                
                    /* Refresh local value pointer to reflect newly set value */
                
                    ValDesc = NsGetAttachedObject ((ACPI_HANDLE) StackEntry);
                    PsxObjStackPop (1);
                }
            
                else
                {
                    PsxObjStackPop (1);
                    return_ACPI_STATUS (Status);
                }
            }

            else
            {
                /* Aml Opcode is not a buffer op */

                DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Not a BufferOp opcode (%x)\n",
                                AmlOpcode));
                return_ACPI_STATUS (AE_AML_BAD_OPCODE);
            }
#else
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Unparsed Buffers not supported!\n"));
            return_ACPI_STATUS (AE_NOT_IMPLEMENTED);
#endif
        }



        /* ValDesc is an internal object in all cases by the time we get here */

        if (!ValDesc || (ACPI_TYPE_Buffer != ValDesc->Common.Type))
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Bad buffer value\n"));
            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }
        
        /* Return an additional reference to the object */

        ObjDesc = ValDesc;
        CmAddReference (ObjDesc);

        DEBUG_PRINT (TRACE_BFIELD,
                    ("AmlResolveEntryToValue: New Buffer descriptor seq# %ld @ %p \n",
                    ObjDesc->Buffer.Sequence, ObjDesc));
        break;


    case ACPI_TYPE_String:
      
        if (AttachedAmlPointer)
        {
            /* Allocate a new string object */

            ObjDesc = CmCreateInternalObject (ACPI_TYPE_String);
            if (!ObjDesc)
            {   
                /* Descriptor allocation failure */

                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            /* Init the internal object */

            ObjDesc->String.Pointer = (char *) AmlPointer;
            ObjDesc->String.Length = STRLEN (AmlPointer);
        }

        else
        {
            if (ACPI_TYPE_String != ValDesc->Common.Type)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Internal error - Bad string value\n"));
                return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
            }

            /* Return an additional reference to the object */

            ObjDesc = ValDesc;
            CmAddReference (ObjDesc);
        }

        break;


    case ACPI_TYPE_Number:

        DEBUG_PRINT (TRACE_EXEC, ("AmlResolveEntryToValue: case Number \n"));

        if (!ValDesc)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Internal error - null Number ValuePtr\n"));
            return_ACPI_STATUS (AE_AML_NO_OPERAND);
        }

        
        /*
         * A ACPI_TYPE_Number can be either an object or an AML pointer
         */

        if (AttachedAmlPointer)
        {
            /* 
             * The attachment points into the AML stream, get the number from there.
             * The actual number is based upon the AML opcode
             * Note: WordOp and DWordOp will not work properly if the
             *       processor's endianness does not match the AML's.
             */

            switch (AmlOpcode)
            {

            case AML_ZeroOp:

                TempVal = 0;
                break;


            case AML_OneOp:

                TempVal = 1;
                break;


            case AML_OnesOp:

                TempVal = 0xFFFFFFFF;
                break;


            case AML_ByteOp:

                TempVal = (UINT32) ((UINT8 *) ValDesc)[1];
                break;


            case AML_WordOp:

                TempVal = (UINT32) *(UINT16 *)&((UINT8 *) ValDesc)[1];
                break;


            case AML_DWordOp:

                TempVal = *(UINT32 *)&((UINT8 *) ValDesc)[1];
                break;


            default:

                DEBUG_PRINT (ACPI_ERROR, ("AmlResolveToValue/Number: Internal error - expected AML number, found %02x\n",
                                AmlOpcode));

                return_ACPI_STATUS (AE_AML_BAD_OPCODE);

            } /* switch */

            
            /* Create and initialize a new object */

            ObjDesc = CmCreateInternalObject (ACPI_TYPE_Number);
            if (!ObjDesc)
            {   
                /* Descriptor allocation failure  */
                
                return_ACPI_STATUS (AE_NO_MEMORY);
            }
            
            ObjDesc->Number.Value = TempVal;
        }
        
        else
        {
            /* The NTE has an attached internal object, make sure it's a number */

            if (ACPI_TYPE_Number != ValDesc->Common.Type)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlResolveToValue/Number: Attached obj %p not a Number, type 0x%X\n", ValDesc, ValDesc->Common.Type));
                return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
            }

            /* Return an additional reference to the object */

            ObjDesc = ValDesc;
            CmAddReference (ObjDesc);
        }

        break;


    case INTERNAL_TYPE_DefField:

        /*
         * TBD: Is this the correct solution?
         *
         * This section was extended to convert to generic buffer if 
         *  the return length is greater than 32 bits, but still allows
         *  for returning a type Number for smaller values because the
         *  caller can then apply arithmetic operators on those fields.
         *
         * XXX - Implementation limitation: Fields are implemented as type
         * XXX - Number, but they really are supposed to be type Buffer.
         * XXX - The two are interchangeable only for lengths <= 32 bits.
         */
        if(ValDesc->Field.Length > 32)
        {
            ObjectType = ACPI_TYPE_Buffer;
        }
        else
        {
            ObjectType = ACPI_TYPE_Number;
        }
            
        /*
         * Create the destination buffer object and the buffer space.
         */
        ObjDesc = CmCreateInternalObject (ObjectType);
        if (!ObjDesc)
        {   
            /* Descriptor allocation failure  */
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        /*
         * Fill in the object specific details
         */
        if (ACPI_TYPE_Buffer == ObjectType)
        {
            ObjDesc->Buffer.Pointer = CmCallocate(ValDesc->Field.Length);
            if (!ObjDesc->Buffer.Pointer)
            {   
                CmRemoveReference(ObjDesc);
                /* Buffer allocation failure  */
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            ObjDesc->Buffer.Length = ValDesc->Field.Length;
                
            Status = AmlGetNamedFieldValue ((ACPI_HANDLE) StackEntry, ObjDesc->Buffer.Pointer, ObjDesc->Buffer.Length);

            if (AE_OK != Status)
            {
                return_ACPI_STATUS (Status);
            }
        }
        else
        {
            Status = AmlGetNamedFieldValue ((ACPI_HANDLE) StackEntry, &TempVal, sizeof (TempVal));

            if (AE_OK != Status)
            {
                return_ACPI_STATUS (Status);
            }

            ObjDesc->Number.Value = TempVal;
        }


        DEBUG_PRINT (TRACE_EXEC, ("AmlResolveEntryToValue: at DefField Entry=%p ValDesc=%p Type=%X\n", 
                        StackEntry, ValDesc, EntryType));
        break;


    case INTERNAL_TYPE_BankField:

        if (!ValDesc)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Internal error - null BankField ValuePtr\n"));
            return_ACPI_STATUS (AE_AML_NO_OPERAND);
        }

        if (AttachedAmlPointer)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Internal error - BankField cannot be an Aml ptr\n"));
            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }

        if (INTERNAL_TYPE_BankField != ValDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlResolveToValue/BankField:Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                    &(((NAME_TABLE_ENTRY *) (*StackPtr))->Name), INTERNAL_TYPE_BankField, ValDesc->Common.Type, ValDesc));
            
            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }


        /* Get the global lock if needed */

        ObjDesc = (ACPI_OBJECT_INTERNAL *) *StackPtr;
        Locked = AmlAcquireGlobalLock (ObjDesc->FieldUnit.LockRule);
        {

            /* Set Index value to select proper Data register */
            /* perform the update */
        
            Status = AmlSetNamedFieldValue (ValDesc->BankField.BankSelect,
                                            &ValDesc->BankField.Value, sizeof (ValDesc->BankField.Value));
        }
        AmlReleaseGlobalLock (Locked);


        if (AE_OK != Status)
        {
            return_ACPI_STATUS (Status);
        }
        
        /* Read Data value */
        
        Status = AmlGetNamedFieldValue ((ACPI_HANDLE) ValDesc->BankField.Container, &TempVal, sizeof (TempVal));
        if (AE_OK != Status)
        {
            return_ACPI_STATUS (Status);
        }

        ObjDesc = CmCreateInternalObject (ACPI_TYPE_Number);
        if (!ObjDesc)
        {
            /* Descriptor allocation failure  */

            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        ObjDesc->Number.Value = TempVal;
        break;


    case INTERNAL_TYPE_IndexField:

        if (!ValDesc)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Internal error - null IndexField ValuePtr\n"));
            return_ACPI_STATUS (AE_AML_NO_OPERAND);
        }

        if (AttachedAmlPointer)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Internal error - IndexField cannot be an Aml ptr\n"));
            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }

        if (INTERNAL_TYPE_IndexField != ValDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlResolveToValue/IndexField: Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                    &(((NAME_TABLE_ENTRY *) (*StackPtr))->Name), INTERNAL_TYPE_IndexField, ValDesc->Common.Type, ValDesc));
            
            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }


        /* Set Index value to select proper Data register */
        /* Get the global lock if needed */

        ObjDesc = (ACPI_OBJECT_INTERNAL *) *StackPtr;
        Locked = AmlAcquireGlobalLock (ObjDesc->FieldUnit.LockRule);
        {
            /* Perform the update */
          
            Status = AmlSetNamedFieldValue (ValDesc->IndexField.Index,
                                            &ValDesc->IndexField.Value, sizeof (ValDesc->IndexField.Value));
        }
        AmlReleaseGlobalLock (Locked);

        if (AE_OK != Status)
        {
            return_ACPI_STATUS (Status);
        }

        /* Read Data value */
        
        Status = AmlGetNamedFieldValue (ValDesc->IndexField.Data, &TempVal, sizeof (TempVal));
        if (AE_OK != Status)
        {
            return_ACPI_STATUS (Status);
        }

        ObjDesc = CmCreateInternalObject (ACPI_TYPE_Number);
        if (!ObjDesc)
        {
            /* Descriptor allocation failure  */

            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        ObjDesc->Number.Value = TempVal;
        break;


    case ACPI_TYPE_FieldUnit:

        if (!ValDesc)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Internal error - null FieldUnit ValuePtr\n"));
            return_ACPI_STATUS (AE_AML_NO_OPERAND);
        }

        if (AttachedAmlPointer)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Internal error - FieldUnit cannot be an Aml ptr\n"));
            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }

        if (ValDesc->Common.Type != (UINT8) EntryType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlResolveToValue/FieldUnit: Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                      &(((NAME_TABLE_ENTRY *) (*StackPtr))->Name), EntryType,
                      ValDesc->Common.Type, ValDesc));
            
            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
            break;
        }

        ObjDesc = CmCreateInternalObject (ACPI_TYPE_Any);
        if (!ObjDesc)
        {
            /* Descriptor allocation failure  */

            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        if ((Status = AmlGetFieldUnitValue (ValDesc, ObjDesc)) != AE_OK)
        {
            CmRemoveReference (ObjDesc);
            return_ACPI_STATUS (Status);
        }

        break;



    /* 
     * For these objects, just return the object attached to the NTE
     */
    
    case ACPI_TYPE_Mutex:
    case ACPI_TYPE_Method:
    case ACPI_TYPE_Power:
    case ACPI_TYPE_Processor:
    case ACPI_TYPE_Thermal:
    case ACPI_TYPE_Event:
    case ACPI_TYPE_Region: 


        /* There must be an object attached to this NTE */

        if (!ValDesc)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: NTE %p has no attached object\n",
                            StackEntry));
        
            return_ACPI_STATUS (AE_AML_INTERNAL);
        }

        /* Return an additional reference to the object */

        ObjDesc = ValDesc;
        CmAddReference (ObjDesc);
        break;


    /* Devices rarely have an attached object, return the NTE */

    case ACPI_TYPE_Device:


    /* Method locals and arguments have a pseudo-NTE, just return it */

    case INTERNAL_TYPE_MethodArgument:
    case INTERNAL_TYPE_MethodLocalVar:

        return_ACPI_STATUS (AE_OK);
        break;


    /* TYPE_Any is untyped, and thus there is no object associated with it */

    case ACPI_TYPE_Any:

        DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Untyped entry %p - has no Rvalue\n",
                        StackEntry));
        
        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);  /* Cannot be AE_TYPE */


    /* Default case is for unknown types */

    default:

        DEBUG_PRINT (ACPI_ERROR, ("AmlResolveEntryToValue: Entry %p - Unknown object type %d\n",
                        StackEntry, EntryType));
        
        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    
    } /* switch (EntryType) */




    /* Put the object descriptor on the stack */

    *StackPtr = (void *) ObjDesc;

    return_ACPI_STATUS (Status);
}



