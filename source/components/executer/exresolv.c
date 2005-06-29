
/******************************************************************************
 * 
 * Module Name: ievalue - ACPI AML (p-code) execution - get value routines
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

#define __IEVALUE_C__

#include <acpi.h>
#include <amlcode.h>
#include <parser.h>
#include <interp.h>
#include <namesp.h>
#include <tables.h>
#include <events.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("ievalue");



/*****************************************************************************
 * 
 * FUNCTION:    AmlGetFieldUnitValue
 *
 * PARAMETERS:  *FieldDesc          - Pointer to a FieldUnit
 *              *ResultDesc         - Pointer to an empty descriptor
 *                                    which will become a Number
 *                                    containing the field's value.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve the value from a FieldUnit
 *
 ****************************************************************************/

ACPI_STATUS
AmlGetFieldUnitValue (
    ACPI_OBJECT_INTERNAL    *FieldDesc, 
    ACPI_OBJECT_INTERNAL    *ResultDesc)
{
    ACPI_STATUS             Status = AE_AML_ERROR;
    UINT32                  Mask;
    UINT8                   *Location = NULL;
    BOOLEAN                 Locked = FALSE;


    FUNCTION_TRACE ("AmlGetFieldUnitValue");


    if (!FieldDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: Internal error - null field pointer\n"));
    }

    else if (!FieldDesc->FieldUnit.Container)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: Internal error - null container pointer\n"));
    }

    else if (ACPI_TYPE_Buffer != FieldDesc->FieldUnit.Container->Common.Type)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: Internal error - container is not a Buffer\n"));
    }

    else if (FieldDesc->FieldUnit.Sequence
                != FieldDesc->FieldUnit.Container->Buffer.Sequence)
    {
        DEBUG_PRINT (ACPI_ERROR, (
                "AmlGetFieldUnitValue: Internal error - stale Buffer [%lx != %lx]\n",
                FieldDesc->FieldUnit.Sequence,
                FieldDesc->FieldUnit.Container->Buffer.Sequence));
    }

    else if (!ResultDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: Internal error - null result pointer\n"));
    }

    else 
    {
        /* Input parameters are valid */

        Status = AE_OK;

        /* Get the global lock if needed */

        Locked = AmlAcquireGlobalLock (FieldDesc->FieldUnit.LockRule);
    }

    if (AE_OK == Status)
    {   
        /* Input parameters valid and global lock possibly acquired */

        if (FieldDesc->FieldUnit.Length + FieldDesc->FieldUnit.BitOffset > 32)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: implementation limitation: Field exceeds UINT32\n"));
            Status = AE_AML_ERROR;
        }
    }

    if (AE_OK == Status)
    {   
        /* Field location is (base of buffer) + (byte offset) */
    
        Location = FieldDesc->FieldUnit.Container->Buffer.Pointer
                    + FieldDesc->FieldUnit.Offset;

        /* Construct Mask with as many 1 bits as the field width */
    
        Mask = ((UINT32) 1 << FieldDesc->FieldUnit.Length) - (UINT32) 1;

        ResultDesc->Number.Type = (UINT8) ACPI_TYPE_Number;

        /* Shift the word containing the field, and mask the value */
    
        ResultDesc->Number.Value
            = *(UINT32 *) Location >> FieldDesc->FieldUnit.BitOffset & Mask;

        DEBUG_PRINT (ACPI_INFO,
            ("** Read from buffer %p byte %ld bit %d width %d addr %p mask %08lx val %08lx\n",
            FieldDesc->FieldUnit.Container->Buffer.Pointer,
            FieldDesc->FieldUnit.Offset,
            FieldDesc->FieldUnit.BitOffset,
            FieldDesc->FieldUnit.Length,
            Location, Mask, ResultDesc->Number.Value));
    }

    /* Release global lock if we acquired it earlier */

    AmlReleaseGlobalLock (Locked);


    return_ACPI_STATUS (Status);
}




/*****************************************************************************
 * 
 * FUNCTION:    AmlGetRvalueFromObject
 *
 * PARAMETERS:  StackPtr        - Pointer to a stack location that contains a
 *                                ptr to an internal object.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve the value from an internal object.  The Lvalue type
 *              uses the associated AML opcode to determine the value.
 *
 ****************************************************************************/

ACPI_STATUS
AmlGetRvalueFromObject (
    ACPI_OBJECT_INTERNAL    **StackPtr)
{
    ACPI_OBJECT_INTERNAL    *StackDesc;
    ACPI_STATUS             Status = AE_OK;
    ACPI_HANDLE             TempHandle = NULL;
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    UINT32				    MvIndex = 0;
    UINT16                  Opcode;


    FUNCTION_TRACE ("AmlGetRvalueFromObject");


    StackDesc = *StackPtr;

    /* This is an ACPI_OBJECT_INTERNAL */

    switch (StackDesc->Common.Type)
    {

    case INTERNAL_TYPE_Lvalue:

        Opcode = StackDesc->Lvalue.OpCode;

        switch (Opcode)
        {

        case AML_NameOp:
        
            /* 
             * Convert indirect name ptr to a direct name ptr.
             * Then, AmlGetRvalueFromEntry can be used to get the value
             */
        
            TempHandle = StackDesc->Lvalue.Object;
            CmDeleteInternalObject (StackDesc);

            /* Put direct name pointer onto stack and exit */

            (*StackPtr) = TempHandle;
            Status = AE_OK;
            break;


        case AML_LocalOp:

            MvIndex = StackDesc->Lvalue.Offset;

            DEBUG_PRINT (ACPI_INFO, ("AmlGetRvalueFromObject: [Local%d] before MthStackGetValue %p %p %08lx \n",
                            MvIndex, StackPtr, StackDesc, *(UINT32 *) StackDesc));

            CmDeleteInternalObject (StackDesc);     /* Delete the Lvalue */
            Status = PsxMthStackGetValue (MTH_TYPE_LOCAL, MvIndex, StackPtr);
            StackDesc = *StackPtr;

            DEBUG_PRINT (ACPI_INFO, ("AmlGetRvalueFromObject: [Local%d] after MSGV Status=%s %p %p %08lx \n",
                            MvIndex, CmFormatException (Status), StackPtr, StackDesc,
                            *(UINT32 *) StackDesc));
        
            if (ACPI_TYPE_Number == StackDesc->Common.Type)
            {
                /* Value is a Number */
            
                DEBUG_PRINT (ACPI_INFO, ("AmlGetRvalueFromObject: [Local%d] value is [0x%X] \n", 
                                            MvIndex, StackDesc->Number.Value));
            }

            break;


        case AML_ArgOp:

            MvIndex = StackDesc->Lvalue.Offset;

            DEBUG_PRINT (TRACE_EXEC, ("AmlGetRvalueFromObject: [Arg%d] before PsxMthStackGetValue %p %p %08lx \n",
                            MvIndex, StackPtr, StackDesc, *(UINT32 *) StackDesc));

            CmDeleteInternalObject (StackDesc);     /* Delete the Lvalue */
            Status = PsxMthStackGetValue (MTH_TYPE_ARG, MvIndex, StackPtr);
            StackDesc = *StackPtr;
   
            DEBUG_PRINT (TRACE_EXEC, ("AmlGetRvalueFromObject: [Arg%d] MSGV returned %s %p %p %08lx \n",
                            MvIndex, CmFormatException (Status), StackPtr, StackDesc,
                            *(UINT32 *) StackDesc));

            if (ACPI_TYPE_Number == StackDesc->Common.Type)
            {
                /* Value is a Number */
            
                DEBUG_PRINT (ACPI_INFO, ("AmlGetRvalueFromObject: [Arg%d] value is [0x%X] \n", 
                                            MvIndex, StackDesc->Number.Value));
            }

            break;


        case AML_ZeroOp:

            StackDesc->Common.Type = (UINT8) ACPI_TYPE_Number;
            StackDesc->Number.Value = 0;
            Status = AE_OK;
            break;


        case AML_OneOp:

            StackDesc->Common.Type = (UINT8) ACPI_TYPE_Number;
            StackDesc->Number.Value = 1;
            Status = AE_OK;
            break;


        case AML_OnesOp:

            StackDesc->Common.Type = (UINT8) ACPI_TYPE_Number;
            StackDesc->Number.Value = 0xFFFFFFFF;
            Status = AE_OK;
            break;


        case AML_IndexOp:

            ObjDesc = StackDesc->Lvalue.Object;
            if (ObjDesc)
            {
                /*
                 * Valid obj descriptor, copy pointer to return value
                 */
                *StackPtr = ObjDesc;
                Status = AE_OK;
            }

            else
            {
                /* Invalid obj descriptor */

                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromObject: Null IndexOp value ptr\n"));
                Status = AE_AML_ERROR;
            }

            break;


        default:

            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromObject: Unknown Lvalue subtype %02x\n",
                            Opcode));
            Status = AE_AML_ERROR;

        }   /* switch (Opcode) */


        if (AE_OK != Status)
        {
            return_ACPI_STATUS (Status);
        }

        break; /* case INTERNAL_TYPE_Lvalue */


    case ACPI_TYPE_FieldUnit:

        ObjDesc = CmCreateInternalObject (ACPI_TYPE_Any);
        if (!ObjDesc)
        {   
            /* Descriptor allocation failure  */
        
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        if ((Status = AmlGetFieldUnitValue (StackDesc, ObjDesc)) != AE_OK)
        {
            CmDeleteInternalObject (ObjDesc);
            ObjDesc = NULL;
        }
    
        *StackPtr = (void *) ObjDesc;
        return_ACPI_STATUS (Status);


    case INTERNAL_TYPE_BankField:

        ObjDesc = CmCreateInternalObject (ACPI_TYPE_Any);
        if (!ObjDesc)
        {   
            /* Descriptor allocation failure */
        
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        if ((Status = AmlGetFieldUnitValue (StackDesc, ObjDesc)) != AE_OK)
        {
            CmDeleteInternalObject (ObjDesc);
            ObjDesc = NULL;
        }

        *StackPtr = (void *) ObjDesc;
        return_ACPI_STATUS (Status);
        break;


    /* TBD: - may need to handle IndexField, and DefField someday */

    default:

        break;

    }   /* switch (StackDesc->Common.Type) */


    return_ACPI_STATUS (Status);
}



/*****************************************************************************
 * 
 * FUNCTION:    AmlGetRvalueFromEntry
 *
 * PARAMETERS:  StackPtr        - Pointer to a location on a stack that contains
 *                                a ptr to an NTE
 *                                  
 * RETURN:      Status
 *
 * DESCRIPTION: Create an Rvalue from a NAME_TABLE_ENTRY (nte, A.K.A. a "direct
 *              name pointer")
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
AmlGetRvalueFromEntry (
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


    FUNCTION_TRACE ("AmlGetRvalueFromEntry");

    StackEntry = *StackPtr;


    /* 
     * The stack pointer is a "Direct name ptr", and points to a
     * a NAME_TABLE_ENTRY (nte).  Get the pointer that is attached to
     * the nte.
     */

    ValDesc     = NsGetAttachedObject ((ACPI_HANDLE) StackEntry);
    EntryType   = NsGetType ((ACPI_HANDLE) StackEntry);

    DEBUG_PRINT (TRACE_EXEC, ("AmlGetRvalueFromEntry: Entry=%p ValDesc=%p Type=%X\n", 
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

        DEBUG_PRINT (TRACE_EXEC, ("AmlGetRvalueFromEntry: Unparsed AML: %p Len=%X\n", 
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
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Internal error - null ValDesc\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
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

                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Not a PackageOp opcode (%x)\n",
                                AmlOpcode));
                return_ACPI_STATUS (AE_AML_ERROR);
            }
#else
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Unparsed Packages not supported!\n"));
            return_ACPI_STATUS (AE_NOT_IMPLEMENTED);
#endif
        }
        
        /* ValDesc is an internal object in all cases by the time we get here */

        if (!ValDesc || (ACPI_TYPE_Package != ValDesc->Common.Type))
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Internal error - Bad package value\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        /* Return an additional reference to the object */

        ObjDesc = ValDesc;
        CmUpdateObjectReference (ObjDesc, REF_INCREMENT);
        break;


    case ACPI_TYPE_Buffer:

        if (!ValDesc)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Internal error - null Buffer ValuePtr\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
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

                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Not a BufferOp opcode (%x)\n",
                                AmlOpcode));
                return_ACPI_STATUS (AE_AML_ERROR);
            }
#else
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Unparsed Buffers not supported!\n"));
            return_ACPI_STATUS (AE_NOT_IMPLEMENTED);
#endif
        }



        /* ValDesc is an internal object in all cases by the time we get here */

        if (!ValDesc || (ACPI_TYPE_Buffer != ValDesc->Common.Type))
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Bad buffer value\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
        }
        
        /* Return an additional reference to the object */

        ObjDesc = ValDesc;
        CmUpdateObjectReference (ObjDesc, REF_INCREMENT);

        DEBUG_PRINT (TRACE_BFIELD,
                    ("AmlGetRvalueFromEntry: New Buffer descriptor seq# %ld @ %p \n",
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
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Internal error - Bad string value\n"));
                return_ACPI_STATUS (AE_AML_ERROR);
            }

            /* Return an additional reference to the object */

            ObjDesc = ValDesc;
            CmUpdateObjectReference (ObjDesc, REF_INCREMENT);
        }

        break;


    case ACPI_TYPE_Number:

        DEBUG_PRINT (TRACE_EXEC, ("AmlGetRvalueFromEntry: case Number \n"));

        if (!ValDesc)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Internal error - null Number ValuePtr\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
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

                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlGetRvalue/Number: Internal error - expected AML number, found %02x\n",
                        AmlOpcode));

                return_ACPI_STATUS (AE_AML_ERROR);

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
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue/Number: Internal error - not a Number\n"));
                return_ACPI_STATUS (AE_AML_ERROR);
            }

            /* Return an additional reference to the object */

            ObjDesc = ValDesc;
            CmUpdateObjectReference (ObjDesc, REF_INCREMENT);
        }

        break;


    case INTERNAL_TYPE_DefField:

        /*
         * TBD: Convert to generic buffer
         *
         * XXX - Implementation limitation: Fields are implemented as type
         * XXX - Number, but they really are supposed to be type Buffer.
         * XXX - The two are interchangeable only for lengths <= 32 bits.
         */
        Status = AmlGetNamedFieldValue ((ACPI_HANDLE) StackEntry, &TempVal, sizeof (TempVal));
        if (AE_OK != Status)
        {
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        ObjDesc = CmCreateInternalObject (ACPI_TYPE_Number);
        if (!ObjDesc)
        {   
            /* Descriptor allocation failure  */
            
            return_ACPI_STATUS (AE_NO_MEMORY);
        }


        DEBUG_PRINT (TRACE_EXEC, ("AmlGetRvalueFromEntry: at DefField Entry=%p ValDesc=%p Type=%X\n", 
                        StackEntry, ValDesc, EntryType));

        ObjDesc->Number.Value = TempVal;
        break;


    case INTERNAL_TYPE_BankField:

        if (!ValDesc)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Internal error - null BankField ValuePtr\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        if (AttachedAmlPointer)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Internal error - BankField cannot be an Aml ptr\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        if (INTERNAL_TYPE_BankField != ValDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlGetRvalue/BankField:Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                    &(((NAME_TABLE_ENTRY *) (*StackPtr))->Name), INTERNAL_TYPE_BankField, ValDesc->Common.Type, ValDesc));
            
            return_ACPI_STATUS (AE_AML_ERROR);
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
            return_ACPI_STATUS (AE_AML_ERROR);
        }
        
        /* Read Data value */
        
        Status = AmlGetNamedFieldValue ((ACPI_HANDLE) ValDesc->BankField.Container, &TempVal, sizeof (TempVal));
        if (AE_OK != Status)
        {
            return_ACPI_STATUS (AE_AML_ERROR);
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
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Internal error - null IndexField ValuePtr\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        if (AttachedAmlPointer)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Internal error - IndexField cannot be an Aml ptr\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        if (INTERNAL_TYPE_IndexField != ValDesc->Common.Type)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlGetRvalue/IndexField: Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                    &(((NAME_TABLE_ENTRY *) (*StackPtr))->Name), INTERNAL_TYPE_IndexField, ValDesc->Common.Type, ValDesc));
            
            return_ACPI_STATUS (AE_AML_ERROR);
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
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        /* Read Data value */
        
        Status = AmlGetNamedFieldValue (ValDesc->IndexField.Data, &TempVal, sizeof (TempVal));
        if (AE_OK != Status)
        {
            return_ACPI_STATUS (AE_AML_ERROR);
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
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Internal error - null FieldUnit ValuePtr\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        if (AttachedAmlPointer)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Internal error - FieldUnit cannot be an Aml ptr\n"));
            return_ACPI_STATUS (AE_AML_ERROR);
        }

        if (ValDesc->Common.Type != (UINT8) EntryType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlGetRvalue/FieldUnit: Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                      &(((NAME_TABLE_ENTRY *) (*StackPtr))->Name), EntryType,
                      ValDesc->Common.Type, ValDesc));
            
            return_ACPI_STATUS (AE_AML_ERROR);
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
            CmDeleteInternalObject (ObjDesc);
            return_ACPI_STATUS (Status);
        }

        break;



    /* 
     * Cases which just return the name as the rvalue
     * 
     * TBD: The first group used to be in the unimplemented list, but
     * perhaps it makes more sense to just return the name in these cases
     */
    
    case ACPI_TYPE_Mutex:
    case ACPI_TYPE_Method:
    case ACPI_TYPE_Power:
    case ACPI_TYPE_Processor:
    case ACPI_TYPE_Thermal:
    case ACPI_TYPE_Event:
    case ACPI_TYPE_Region: 

    case ACPI_TYPE_Device:

    /* Method locals and arguments have a pseudo-NTE, just return it */

    case INTERNAL_TYPE_MethodArgument:
    case INTERNAL_TYPE_MethodLocalVar:

        return_ACPI_STATUS (AE_OK);
        break;


    /* TYPE_Any is untyped, and thus there is no object associated with it */

    case ACPI_TYPE_Any:

        DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Untyped entry %p - has no Rvalue\n",
                        StackEntry));
        
        return_ACPI_STATUS (AE_AML_ERROR);  /* Cannot be AE_TYPE */


    /* Default case is for unknown types */

    default:

        DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalueFromEntry: Entry %p - Unknown object type %d\n",
                        StackEntry, EntryType));
        
        return_ACPI_STATUS (AE_AML_ERROR);
    
    } /* switch (EntryType) */




    /* Put the object descriptor on the stack */

    *StackPtr = (void *) ObjDesc;

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlGetRvalue
 *
 * PARAMETERS:  **StackPtr          - Points to entry on ObjStack, which can 
 *                                    be either an (ACPI_OBJECT_INTERNAL *)
 *                                    or an ACPI_HANDLE.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert Lvalue entries on ObjStack to Rvalues
 *
 ****************************************************************************/

ACPI_STATUS
AmlGetRvalue (
    ACPI_OBJECT_INTERNAL    **StackPtr)
{
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE_PTR ("AmlGetRvalue", StackPtr);


    if (!StackPtr || !*StackPtr)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: Internal error - null pointer\n"));
        return_ACPI_STATUS (AE_AML_ERROR);
    }


    /* 
     * The entity pointed to by the StackPtr can be either
     * 1) A valid ACPI_OBJECT_INTERNAL, or
     * 2) A NAME_TABLE_ENTRY (nte)
     */

    if (VALID_DESCRIPTOR_TYPE (*StackPtr, DESC_TYPE_ACPI_OBJ))       
    {

        Status = AmlGetRvalueFromObject (StackPtr);
    }

    /* 
     * Object on the stack may have changed if AmlGetRvalueFromObject() was called
     * (i.e., we can't use an _else_ here.)
     */

    if (VALID_DESCRIPTOR_TYPE (*StackPtr, DESC_TYPE_NTE))       
    {
        Status = AmlGetRvalueFromEntry ((NAME_TABLE_ENTRY **) StackPtr);
    }


    DEBUG_PRINT (ACPI_INFO, ("AmlGetRvalue: Returning resolved object %p\n", *StackPtr));

    return_ACPI_STATUS (Status);
}
    
