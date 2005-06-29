/******************************************************************************
 * 
 * Module Name: iefield - ACPI AML (p-code) execution - field manipulation
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


#define __IEFIELD_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>
#include <hardware.h>
#include <events.h>


#define _THIS_MODULE        "iefield.c"
#define _COMPONENT          INTERPRETER


/*****************************************************************************
 * 
 * FUNCTION:    AmlSetupField
 *
 * PARAMETERS:  *ObjDesc            - Field to be read or written
 *              *RgnDesc            - Region containing field
 *              FieldBitWidth       - Field Width in bits (8, 16, or 32)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Common processing for AmlReadField and AmlWriteField
 *
 *  ACPI SPECIFICATION REFERENCES:
 *  16.2.4.3    Each of the Type1Opcodes is defined as specified in in-line
 *              comments below. For each one, use the following definitions.
 *  16.2.4.2    DefBitField     :=  BitFieldOp      SourceBuff  BitIndex    Destination
 *  16.2.4.2    DefByteField    :=  ByteFieldOp     SourceBuff  ByteIndex   Destination
 *  16.2.4.2    DefCreateField  :=  CreateFieldOp   SourceBuff  BitIndex    NumBits     NameString
 *  16.2.4.2    DefDWordField   :=  DWordFieldOp    SourceBuff  ByteIndex   Destination
 *  16.2.4.2    DefWordField    :=  WordFieldOp     SourceBuff  ByteIndex   Destination
 *  16.2.4.2    BitIndex        :=  TermArg=>Integer
 *  16.2.4.2    ByteIndex       :=  TermArg=>Integer
 *  16.2.4.2    Destination     :=  NameString
 *  16.2.4.2    NumBits         :=  TermArg=>Integer
 *  16.2.4.2    SourceBuff      :=  TermArg=>Buffer
 *
 ****************************************************************************/

ACPI_STATUS
AmlSetupField (
    ACPI_OBJECT_INTERNAL    *ObjDesc, 
    ACPI_OBJECT_INTERNAL    *RgnDesc, 
    INT32                   FieldBitWidth)
{
    ACPI_OBJECT_INTERNAL    *ObjValDesc = NULL;
    ACPI_STATUS             Status = AE_OK;
    INT32                   FieldByteWidth;


    FUNCTION_TRACE ("AmlSetupField");

BREAKPOINT3;
    if (!ObjDesc || !RgnDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlSetupField: Internal error - null handle\n"));
        Status = AE_AML_ERROR;
    }

    else if (ACPI_TYPE_Region != RgnDesc->Common.Type)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlSetupField: Needed Region, found %d %s\n",
                        RgnDesc->Common.Type, Gbl_NsTypeNames[RgnDesc->Common.Type]));
        Status = AE_AML_ERROR;
    }

    if (AE_OK == Status)
    {   
        /* ObjDesc, RgnDesc, and RgnDesc->Common.Type valid */
        
        FieldByteWidth = FieldBitWidth / 8;     /*  possible values are 1, 2, 4 */

        if ((FieldBitWidth != 8) && 
            (FieldBitWidth != 16) && 
            (FieldBitWidth != 32))
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlSetupField: Internal error - bad width %d\n", FieldBitWidth));
            Status = AE_AML_ERROR;
        }
    }


    if (AE_OK == Status)
    {   
        /* 
         * If the address and length have not been previously evaluated,
         * evaluate them and save the results.
         */
        if (0 == RgnDesc->Region.DataValid)
        {
            /* 
             * Address and length have not been previously evaluated
             * save PCode and PCodeLen on package stack
             */

            Status = AmlPkgPushExecLength (0L);

            if (AE_OK == Status)
            {   
                /*
                 * PCode and PCodeLen preserved on package stack
                 * Point to Address opcode in AML stream
                 */

                if (!RgnDesc->Region.AddressLocation)
                {
                    REPORT_ERROR ("AmlSetupField: Region Method subobject does not exist");
                    return_ACPI_STATUS (AE_EXIST);
                }

                AmlSetCurrentLocation (RgnDesc->Region.AddressLocation);

                /* Evaluate the Address opcode */

                if ((Status = AmlDoOpCode (IMODE_Execute)) == AE_OK && 
                    (Status = AmlGetRvalue (AmlObjStackGetTopPtr ())) == AE_OK)
                {
                    /* Pull the address off the stack */

                    ObjValDesc = AmlObjStackRemoveValue (STACK_TOP);


                    if (!ObjValDesc ||
                        ObjValDesc->Common.Type != (UINT8) ACPI_TYPE_Number)
                    {
                        DEBUG_PRINT (ACPI_ERROR, ("AmlSetupField: Malformed Region/Address "
                                    "ObjValDesc = %p, ObjValDesc->Common.Type = %02Xh, Number = %02Xh\n",
                                    ObjValDesc, ObjValDesc->Common.Type, (UINT8) ACPI_TYPE_Number));

                        Status = AE_AML_ERROR;
                    }

                    else
                    {
                        RgnDesc->Region.Address = ObjValDesc->Number.Value;
                    }

                    /* Free ObjValDesc, it was allocated by AmlDoOpcode */

                    CmDeleteInternalObject (ObjValDesc);
                }

                if (AE_OK == Status)
                {   
                    /* Evaluate the Length opcode */

                    if ((Status = AmlDoOpCode (IMODE_Execute)) == AE_OK &&
                        (Status = AmlGetRvalue (AmlObjStackGetTopPtr ())) == AE_OK)
                    {
                        /* Pull the length off the stack */

                        ObjValDesc = AmlObjStackRemoveValue (STACK_TOP);

                        if (!ObjValDesc ||
                            ObjValDesc->Common.Type != (UINT8) ACPI_TYPE_Number)
                        {

                            DEBUG_PRINT (ACPI_ERROR, ("AmlSetupField: Malformed Region/Length \n"));
                            Status = AE_AML_ERROR;
                        }

                        else
                        {
                            /* Region Length valid */

                            RgnDesc->Region.Length = ObjValDesc->Number.Value;

                            /* 
                             * Remember that both Address and Length
                             * have been successfully evaluated and saved.
                             */
                            RgnDesc->Region.DataValid = 1;
                        }

                        /* Free ObjValDesc, it was allocated by AmlDoOpcode */

                        CmDeleteInternalObject (ObjValDesc);
                    }
                }
            }

            if (AE_OK == Status)
            {
                /*  restore PCode and PCodeLen  */

                Status = AmlPkgPopExec ();
            }
        }
    }

    if (AE_OK == Status)
    {
        /* 
         * If (offset rounded up to next multiple of field width)
         * exceeds region length, indicate an error.
         */

        if (RgnDesc->Region.Length <
           (ObjDesc->Field.Offset & ~((UINT32) FieldByteWidth - 1)) + FieldByteWidth)
        {
            /*  
             * Offset rounded up to next multiple of field width
             * exceeds region length, indicate an error
             */

            DEBUG_PRINT (ACPI_ERROR,
                    ("AmlSetupField: Operation at %08lx width %d bits exceeds region bound %08lx\n",
                    ObjDesc->Field.Offset, FieldBitWidth, RgnDesc->Region.Length));

            DUMP_STACK_ENTRY (RgnDesc);
            DUMP_STACK_ENTRY (ObjDesc);

            Status = AE_AML_ERROR;
        }
    }

    return_ACPI_STATUS (Status);
}



/*****************************************************************************
 * 
 * FUNCTION:    AmlReadField
 *
 * PARAMETERS:  *ObjDesc            - Field to be read
 *              *Value              - Where to store value
 *              FieldBitWidth       - Field Width in bits (8, 16, or 32)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve the value of the given field
 *
 ****************************************************************************/

ACPI_STATUS
AmlReadField (
    ACPI_OBJECT_INTERNAL    *ObjDesc, 
    UINT32                  *Value, 
    INT32                   FieldBitWidth)
{
    ACPI_OBJECT_INTERNAL    *RgnDesc = NULL;
    ACPI_STATUS             Status;
    UINT32                  Address;
    UINT32                  LocalValue = 0;
    INT32                   FieldByteWidth;
    

    FUNCTION_TRACE ("AmlReadField");


    /* ObjDesc is validated by callers */

    if (ObjDesc)
    {
        RgnDesc = ObjDesc->Field.Container;
    }


    FieldByteWidth = FieldBitWidth / 8;
    Status = AmlSetupField (ObjDesc, RgnDesc, FieldBitWidth);
    if (AE_OK != Status)
    {
        return_ACPI_STATUS (Status);
    }

    /* SetupField validated RgnDesc and FieldBitWidth  */

    if (!Value)
    {
        Value = &LocalValue;    /*  support reads without saving value  */
    }


    /* 
     * Round offset down to next multiple of
     * field width, and add region base address.
     */

    Address = RgnDesc->Region.Address
            + (ObjDesc->Field.Offset & ~((UINT32) FieldByteWidth - 1));

    if (RgnDesc->Region.SpaceId >= NUM_REGION_TYPES)
    {
        DEBUG_PRINT (TRACE_OPREGION,
                    ("AmlReadField: **** Read from unknown OpRegion SpaceID %d at %08lx width %d ** \n",
                    RgnDesc->Region.SpaceId, Address, FieldBitWidth));
    }

    else
    {
        DEBUG_PRINT (TRACE_OPREGION,
                    ("AmlReadField: Read from OpRegion %s at %08lx width %d\n",
                    Gbl_RegionTypes[RgnDesc->Region.SpaceId], Address, FieldBitWidth));
    }


    /* Invoke the appropriate AddressSpace/OpRegion handler */

    Status = EvAddressSpaceDispatch (RgnDesc, ADDRESS_SPACE_READ, 
                                        Address, FieldBitWidth, Value);

    if (Status == AE_NOT_IMPLEMENTED)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlReadField: **** OpRegion type %s not implemented\n",
                Gbl_RegionTypes[RgnDesc->Region.SpaceId]));
    }

    else if (Status == AE_EXIST)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlReadField: **** Unknown OpRegion SpaceID %d\n",
                RgnDesc->Region.SpaceId));
    }

    DEBUG_PRINT (TRACE_OPREGION, ("AmlReadField: Returned value=%08lx \n", *Value));

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlWriteField
 *
 * PARAMETERS:  *ObjDesc            - Field to be set
 *              Value               - Value to store
 *              FieldBitWidth       - Field Width in bits (8, 16, or 32)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store the value into the given field
 *
 ****************************************************************************/

ACPI_STATUS
AmlWriteField (
    ACPI_OBJECT_INTERNAL    *ObjDesc, 
    UINT32                  Value, 
    INT32                   FieldBitWidth)
{
    ACPI_OBJECT_INTERNAL    *RgnDesc = NULL;
    ACPI_STATUS             Status = AE_OK;
    UINT32                  Address;
    INT32                   FieldByteWidth;


    FUNCTION_TRACE ("AmlWriteField");


    /* ObjDesc is validated by callers */

    if (ObjDesc)
    {
        RgnDesc = ObjDesc->Field.Container;
    }

    FieldByteWidth = FieldBitWidth / 8;
    Status = AmlSetupField (ObjDesc, RgnDesc, FieldBitWidth);
    if (AE_OK != Status)
    {
        return_ACPI_STATUS (Status);
    }

    Address = RgnDesc->Region.Address
                + (ObjDesc->Field.Offset & ~((UINT32) FieldByteWidth - 1));

    if (RgnDesc->Region.SpaceId >= NUM_REGION_TYPES)
    {
        DEBUG_PRINT (TRACE_OPREGION,
                ("AmlWriteField: **** Store %lx in unknown OpRegion SpaceID %d at %08lx width %d ** \n",
                Value, RgnDesc->Region.SpaceId, Address, FieldBitWidth));
    }
    else
    {
        DEBUG_PRINT (TRACE_OPREGION,
                ("AmlWriteField: Store %lx in OpRegion %s at %08lx width %d\n",
                Value, Gbl_RegionTypes[RgnDesc->Region.SpaceId], Address, FieldBitWidth));
    }

    /* Invoke the appropriate AddressSpace/OpRegion handler */

    Status = EvAddressSpaceDispatch (RgnDesc, ADDRESS_SPACE_WRITE, 
                                        Address, FieldBitWidth, &Value);

    if (Status == AE_NOT_IMPLEMENTED)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlWriteField: **** OpRegion type %s not implemented\n",
                        Gbl_RegionTypes[RgnDesc->Region.SpaceId]));
    }

    else if (Status == AE_EXIST)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlWriteField: **** Unknown OpRegion SpaceID %d\n",
                        RgnDesc->Region.SpaceId));
    }

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlAccessNamedField
 *
 * PARAMETERS:  Mode                - ACPI_READ or ACPI_WRITE
 *              NamedField          - Handle for field to be accessed
 *              *Value              - Value to be read or written
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read or write a named field
 *
 ****************************************************************************/

ACPI_STATUS
AmlAccessNamedField (
    INT32                   Mode, 
    ACPI_HANDLE             NamedField, 
    UINT32                  *Value)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    ACPI_STATUS             Status = AE_OK;
    char                    *Type = NULL;
    UINT32                  Granularity = 0;
    UINT32                  MaxW = 0;
    UINT32                  Mask = 0;
    UINT32                  dValue = 0;
    UINT32                  OldVal = 0;
    BOOLEAN                 Locked = FALSE;



    FUNCTION_TRACE ("AmlAccessNamedField");

    ObjDesc = NsGetAttachedObject (NamedField);
    if (!ObjDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlAccessNamedField: Internal error - null value pointer\n"));
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    if (INTERNAL_TYPE_DefField != NsGetType (NamedField))
    {
        DEBUG_PRINT (ACPI_ERROR, (
                  "AmlAccessNamedField: Name %4.4s type %d is not a defined field\n",
                  &(((NAME_TABLE_ENTRY *) NamedField)->Name), NsGetType (NamedField)));
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    /* ObjDesc valid and NamedField is a defined field  */

    DEBUG_PRINT (ACPI_INFO,
                ("AmlAccessNamedField: DefField type and ValPtr OK in nte \n"));
    DUMP_ENTRY (NamedField, ACPI_INFO);

    DEBUG_PRINT (ACPI_INFO, ("AmlAccessNamedField: ObjDesc=%p, ObjDesc->Common.Type=%d\n",
                ObjDesc, ObjDesc->Common.Type));
    DEBUG_PRINT (ACPI_INFO, ("AmlAccessNamedField: DatLen=%d, BitOffset=%d\n",
                ObjDesc->FieldUnit.Length, ObjDesc->FieldUnit.BitOffset));

    if (INTERNAL_TYPE_DefField != ObjDesc->Common.Type)
    {
        DEBUG_PRINT (ACPI_ERROR, (
                "AmlAccessNamedField: Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                &(((NAME_TABLE_ENTRY *) NamedField)->Name), NsGetType (NamedField), ObjDesc->Common.Type, ObjDesc));
        return_ACPI_STATUS (AE_AML_ERROR);
    }


    switch (ObjDesc->Field.Access)
    {
    case ACCESS_AnyAcc:
        Granularity     = 8;
        MaxW            = 32;
        Type            = "UINT32";
        break;

    case ACCESS_ByteAcc:
        Granularity     = 8;
        MaxW            = 8;
        Type            = "UINT8";
        break;

    case ACCESS_WordAcc:
        Granularity     = 16;
        MaxW            = 16;
        Type            = "UINT16";
        break;

    case ACCESS_DWordAcc:
        Granularity     = 32;
        MaxW            = 32;
        Type            = "UINT32";
        break;

    default:
        /* Invalid field access type */

        DEBUG_PRINT (ACPI_ERROR, (
                    "AmlAccessNamedField: Unknown field access type %d\n",
                    ObjDesc->Field.Access));
        return_ACPI_STATUS (AE_AML_ERROR);
    }


    /* Field has valid access type */

    if ((UINT32) (ObjDesc->FieldUnit.Length + ObjDesc->FieldUnit.BitOffset) > MaxW)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlAccessNamedField: Field exceeds %s\n", Type));
        return_ACPI_STATUS (AE_AML_ERROR);
    }


    /* Get the global lock if needed */

    Locked = AmlAcquireGlobalLock (ObjDesc->FieldUnit.LockRule);


    /* 
     * As long as MaxW/2 is wide enough for the data and MaxW > Granularity,
     * divide MaxW by 2.
     */
    while (Granularity < MaxW && 
           ObjDesc->FieldUnit.Length + ObjDesc->FieldUnit.BitOffset
                <= (UINT16) MaxW / 2)
    {
        MaxW /= 2;
    }

    if (ACPI_WRITE == Mode)
    {
        /* Write access */
        /* Construct Mask with 1 bits where the field is, 0 bits elsewhere */

        Mask = (((UINT32) 1 << ObjDesc->FieldUnit.Length) - (UINT32) 1)
                            << ObjDesc->Field.BitOffset;
        
        if (Value)
        {
            /* Shift and mask the value into the field position */

            dValue = (*Value << ObjDesc->Field.BitOffset) & Mask;
        }


        if (ObjDesc->FieldUnit.Length % Granularity || 
            ObjDesc->FieldUnit.BitOffset)
        {
            /* Write does not fill an integral number of naturally aligned units */

            switch (ObjDesc->Field.UpdateRule)
            {
            case UPDATE_Preserve:

                /* 
                 * Read the current contents of the byte/word/dword containing
                 * the field, and merge with the new field value.
                 */
                Status = AmlReadField (ObjDesc, &OldVal, MaxW);
                dValue |= OldVal & ~Mask;
                break;

            case UPDATE_WriteAsOnes:

                /* Set positions outside the field to 1's */

                dValue |= ~Mask;
                break;

            case UPDATE_WriteAsZeros:

                /* 
                 * Positions outside the field are already 0
                 * due to "& Mask" above
                 */
                break;

            default:
                DEBUG_PRINT (ACPI_ERROR, (
                            "AmlAccessNamedField: Unknown UpdateRule setting %d\n",
                            ObjDesc->Field.UpdateRule));
                Status = AE_AML_ERROR;
            }
        }


        if (AE_OK == Status)
        {

            DEBUG_PRINT (ACPI_INFO, ("AmlAccessNamedField: Calling AmlWriteField\n"));

            /* Perform the update */

            Status = AmlWriteField (ObjDesc, dValue, MaxW);
        }
    }

    else
    {
        /* ACPI_READ access */

        Status = AmlReadField (ObjDesc, Value, MaxW);

        if ((AE_OK == Status) &&
             Value)
        {
            *Value >>= ObjDesc->Field.BitOffset;
            *Value &= (((UINT32) 1 << ObjDesc->FieldUnit.Length) - (UINT32) 1);
        }
    }

    /* Release global lock if we acquired it earlier */

    AmlReleaseGlobalLock (Locked);

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlSetNamedFieldValue
 *
 * PARAMETERS:  NamedField          - Handle for field to be set
 *              Value               - Value to be stored in field
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store the given value into the field
 *
 ****************************************************************************/

ACPI_STATUS
AmlSetNamedFieldValue (
    ACPI_HANDLE             NamedField, 
    UINT32                  Value)
{
    ACPI_STATUS             Status = AE_AML_ERROR;


    FUNCTION_TRACE ("AmlSetNamedFieldValue");


    if (!NamedField)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlSetNamedFieldValue: Internal error - null handle\n"));
    }

    else
    {
        Status = AmlAccessNamedField (ACPI_WRITE, NamedField, &Value);
    }

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlGetNamedFieldValue
 *
 * PARAMETERS:  NamedField          - Handle for field to be read
 *              *Value              - Where to store value read froom field
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve the value of the given field
 *
 ****************************************************************************/

ACPI_STATUS

AmlGetNamedFieldValue (
    ACPI_HANDLE             NamedField, 
    UINT32                  *Value)
{
    ACPI_STATUS             Status = AE_AML_ERROR;


    FUNCTION_TRACE ("AmlGetNamedFieldValue");


    if (!NamedField)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetNamedFieldValue: Internal error - null handle\n"));
    }

    else if (!Value)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetNamedFieldValue: Internal error - null pointer\n"));
    }

    else
    {
        Status = AmlAccessNamedField (ACPI_READ, NamedField, Value);
    }

    return_ACPI_STATUS (Status);
}
  
