/******************************************************************************
 *
 * Module Name: amfldio - Aml Field I/O
 *              $Revision: 1.48 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, 2001, Intel Corp.
 * All rights reserved.
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


#define __AMFLDIO_C__

#include "acpi.h"
#include "acinterp.h"
#include "amlcode.h"
#include "acnamesp.h"
#include "achware.h"
#include "acevents.h"
#include "acdispat.h"


#define _COMPONENT          ACPI_EXECUTER
        MODULE_NAME         ("amfldio")


/*******************************************************************************
 *
 * FUNCTION:    AcpiAmlSetupField
 *
 * PARAMETERS:  *ObjDesc            - Field to be read or written
 *              *RgnDesc            - Region containing field
 *              FieldBitWidth       - Field Width in bits (8, 16, or 32)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Common processing for AcpiAmlExtractFromField and
 *              AcpiAmlInsertIntoField
 *
 ******************************************************************************/

ACPI_STATUS
AcpiAmlSetupField (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_OPERAND_OBJECT     *RgnDesc,
    UINT32                  FieldBitWidth)
{
    ACPI_STATUS             Status = AE_OK;
    UINT32                  FieldByteWidth;
    UINT32                  MinimumLength;


    FUNCTION_TRACE ("AmlSetupField");


    /* Parameter validation */

    if (!ObjDesc || !RgnDesc)
    {
        DEBUG_PRINT (ACPI_ERROR,
            ("AmlSetupField: Internal error - null handle\n"));
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }

    if (ACPI_TYPE_REGION != RgnDesc->Common.Type)
    {
        DEBUG_PRINT (ACPI_ERROR,
            ("AmlSetupField: Needed Region, found type %x %s\n",
            RgnDesc->Common.Type, AcpiCmGetTypeName (RgnDesc->Common.Type)));
        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    }


    /*
     * Init and validate Field width.   Possible values are 1, 2, 4, 8
     */

    FieldByteWidth = DIV_8 (FieldBitWidth);

    if ((FieldBitWidth != 8) &&
        (FieldBitWidth != 16) &&
        (FieldBitWidth != 32) &&
        (FieldBitWidth != 64))      /* ACPI 2.0 Qword support */
    {
        DEBUG_PRINT (ACPI_ERROR,
            ("AmlSetupField: Internal error - bad width %d\n", FieldBitWidth));
        return_ACPI_STATUS (AE_AML_OPERAND_VALUE);
    }


    /*
     * If the Region Address and Length have not been previously evaluated,
     * evaluate them and save the results.
     */
    if (!(RgnDesc->Region.Flags & AOPOBJ_DATA_VALID))
    {

        Status = AcpiDsGetRegionArguments (RgnDesc);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }


    if (RgnDesc->Region.Length <
       (ObjDesc->CommonField.ByteOffset & ~((UINT32) FieldByteWidth - 1)) +
            FieldByteWidth)
    {

        switch (ObjDesc->CommonField.Access)
        {
        case ACCESS_ANY_ACC:
        case ACCESS_BYTE_ACC:
        default:
            MinimumLength = 1;
            break;

        case ACCESS_WORD_ACC:
            MinimumLength = 2;
            break;

        case ACCESS_DWORD_ACC:
            MinimumLength = 4;
            break;

        case ACCESS_QWORD_ACC:
            MinimumLength = 8;
            break;
        }

        if (RgnDesc->Region.Length < MinimumLength)
        {
            DEBUG_PRINT (ACPI_ERROR,
                ("AmlSetupField:  Field access width (%d bytes) too large for region size (%X)\n",
                FieldByteWidth, RgnDesc->Region.Length));
        }

        /*
         * Offset rounded up to next multiple of field width
         * exceeds region length, indicate an error
         */
        DEBUG_PRINT (ACPI_ERROR,
            ("AmlSetupField:  Field length %d bits at region offset %X exceeds region size (%X bytes) field=%p region=%p\n",
            FieldBitWidth, ObjDesc->CommonField.ByteOffset, 
            RgnDesc->Region.Length, ObjDesc, RgnDesc));

        return_ACPI_STATUS (AE_AML_REGION_LIMIT);
    }

    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiAmlReadFieldDatum
 *
 * PARAMETERS:  *ObjDesc            - Field to be read
 *              *Value              - Where to store value
 *              FieldBitWidth       - Field Width in bits (8, 16, or 32)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve the value of the given field
 *
 ******************************************************************************/

ACPI_STATUS
AcpiAmlReadFieldDatum (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT32                  FieldByteOffset,
    UINT32                  FieldBitWidth,
    UINT32                  *Value)
{
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *RgnDesc;
    ACPI_PHYSICAL_ADDRESS   Address;
    UINT32                  LocalValue;
    UINT32                  FieldByteWidth;


    FUNCTION_TRACE_U32 ("AmlReadFieldDatum", FieldByteOffset);


    FieldByteWidth = DIV_8 (FieldBitWidth);
    if (!Value)
    {
        LocalValue = 0;
        Value = &LocalValue;    /*  support reads without saving value  */
    }


    /*
     * BufferFields - Read from a Buffer
     * Other Fields - Read from a Operation Region.
     */

    switch (ObjDesc->Common.Type)
    {
    case ACPI_TYPE_BUFFER_FIELD:

        /*
         * For BufferFields, we only need to copy the data from the
         * source buffer.  Length is the field width in bytes.
         */
        MEMCPY (Value, (ObjDesc->BufferField.BufferObj)->Buffer.Pointer
                        + ObjDesc->BufferField.ByteOffset + FieldByteOffset,
                        FieldByteWidth);
        Status = AE_OK;
        break;


    case INTERNAL_TYPE_REGION_FIELD:
    case INTERNAL_TYPE_BANK_FIELD:

        /*
         * For other fields, we need to go through an Operation Region
         * (Only types that will get here are RegionFields and BankFields)
         */

        RgnDesc = ObjDesc->CommonField.RegionObj;
        Status = AcpiAmlSetupField (ObjDesc, RgnDesc, FieldBitWidth);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }


        /*
         * Set offset to next multiple of field width,
         * add region base address and offset within the field
         */
        Address = RgnDesc->Region.Address +
                  (ObjDesc->CommonField.ByteOffset * FieldByteWidth) +
                  FieldByteOffset;

        DEBUG_PRINT (TRACE_BFIELD,
            ("AmlReadFieldDatum: Region %s(%X) at %08lx width %X\n",
            AcpiCmGetRegionName (RgnDesc->Region.SpaceId),
            RgnDesc->Region.SpaceId, Address,
            FieldBitWidth));


        /* Invoke the appropriate AddressSpace/OpRegion handler */

        Status = AcpiEvAddressSpaceDispatch (RgnDesc, ACPI_READ_ADR_SPACE,
                        Address, FieldBitWidth, Value);
        if (Status == AE_NOT_IMPLEMENTED)
        {
            DEBUG_PRINT (ACPI_ERROR,
                ("AmlReadFieldDatum: Region %s(%X) not implemented\n",
                AcpiCmGetRegionName (RgnDesc->Region.SpaceId),
                RgnDesc->Region.SpaceId));
        }

        else if (Status == AE_NOT_EXIST)
        {
            DEBUG_PRINT (ACPI_ERROR,
                ("AmlReadFieldDatum: Region %s(%X) has no handler\n",
                AcpiCmGetRegionName (RgnDesc->Region.SpaceId),
                RgnDesc->Region.SpaceId));
        }

        break;


    default:

        DEBUG_PRINT (ACPI_ERROR,
            ("AmlReadFieldDatum: %p, wrong source type - %s\n",
            ObjDesc, AcpiCmGetTypeName (ObjDesc->Common.Type)));
        Status = AE_AML_INTERNAL;
        break;
    }


    DEBUG_PRINT (TRACE_BFIELD,
        ("AmlExtractFromField: Returned value=%08lX \n", *Value));

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiAmlExtractFromField
 *
 * PARAMETERS:  *ObjDesc            - Field to be read
 *              *Value              - Where to store value
 *              FieldBitWidth       - Field Width in bits (8, 16, or 32)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve the value of the given field
 *
 ******************************************************************************/

ACPI_STATUS
AcpiAmlExtractFromField (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    void                    *Buffer,
    UINT32                  BufferLength,
    UINT32                  ByteLength,
    UINT32                  DatumLength,
    UINT32                  BitGranularity,
    UINT32                  ByteGranularity)
{
    ACPI_STATUS             Status;
    UINT32                  ThisFieldByteOffset;
    UINT32                  ThisFieldDatumOffset;
    UINT32                  PreviousRawDatum;
    UINT32                  ThisRawDatum = 0;
    UINT32                  ValidFieldBits;
    UINT32                  Mask;
    UINT32                  MergedDatum = 0;


    FUNCTION_TRACE ("AmlExtractFromField");

    /*
     * Clear the caller's buffer (the whole buffer length as given)
     * This is very important, especially in the cases where a byte is read,
     * but the buffer is really a UINT32 (4 bytes).
     */

    MEMSET (Buffer, 0, BufferLength);

    /* Read the first raw datum to prime the loop */

    ThisFieldByteOffset = 0;
    ThisFieldDatumOffset= 0;

    Status = AcpiAmlReadFieldDatum (ObjDesc, ThisFieldByteOffset,
                    BitGranularity, &PreviousRawDatum);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }

    /* We might actually be done if the request fits in one datum */

    if ((DatumLength == 1) &&
        ((ObjDesc->CommonField.BitOffset + ObjDesc->CommonField.BitLength) <=
            (UINT16) BitGranularity))
    {
        MergedDatum = PreviousRawDatum;
        MergedDatum = (MergedDatum >> ObjDesc->CommonField.BitOffset);

        ValidFieldBits = ObjDesc->CommonField.BitLength % BitGranularity;
        if (ValidFieldBits)
        {
            Mask = (((UINT32) 1 << ValidFieldBits) - (UINT32) 1);
            MergedDatum &= Mask;
        }


        /*
         * Place the MergedDatum into the proper format and return buffer
         * field
         */

        switch (ByteGranularity)
        {
        case 1:
            ((UINT8 *) Buffer) [ThisFieldDatumOffset] = (UINT8) MergedDatum;
            break;

        case 2:
            MOVE_UNALIGNED16_TO_16 (&(((UINT16 *) Buffer)[ThisFieldDatumOffset]), &MergedDatum);
            break;

        case 4:
            MOVE_UNALIGNED32_TO_32 (&(((UINT32 *) Buffer)[ThisFieldDatumOffset]), &MergedDatum);
            break;
        }

        ThisFieldByteOffset = 1;
        ThisFieldDatumOffset = 1;
    }

    else
    {
        /* We need to get more raw data to complete one or more field data */

        while (ThisFieldDatumOffset < DatumLength)
        {
            /*
             * If the field is aligned on a byte boundary, we don't want
             * to perform a final read, since this would potentially read
             * past the end of the region.
             *
             * TBD: [Investigate] It may make more sense to just split the aligned
             * and non-aligned cases since the aligned case is so very simple,
             */
            if ((ObjDesc->CommonField.BitOffset != 0) ||
                ((ObjDesc->CommonField.BitOffset == 0) &&
                (ThisFieldDatumOffset < (DatumLength -1))))
            {
                /*
                 * Get the next raw datum, it contains some or all bits
                 * of the current field datum
                 */

                Status = AcpiAmlReadFieldDatum (ObjDesc,
                                ThisFieldByteOffset + ByteGranularity,
                                BitGranularity, &ThisRawDatum);
                if (ACPI_FAILURE (Status))
                {
                    goto Cleanup;
                }

                /* Before merging the data, make sure the unused bits are clear */

                switch (ByteGranularity)
                {
                case 1:
                    ThisRawDatum &= 0x000000FF;
                    PreviousRawDatum &= 0x000000FF;
                    break;

                case 2:
                    ThisRawDatum &= 0x0000FFFF;
                    PreviousRawDatum &= 0x0000FFFF;
                    break;
                }
            }


            /*
             * Put together bits of the two raw data to make a complete
             * field datum
             */


            if (ObjDesc->CommonField.BitOffset != 0)
            {
                MergedDatum =
                    (PreviousRawDatum >> ObjDesc->CommonField.BitOffset) |
                    (ThisRawDatum << (BitGranularity - ObjDesc->CommonField.BitOffset));
            }

            else
            {
                MergedDatum = PreviousRawDatum;
            }

            /*
             * Prepare the merged datum for storing into the caller's
             *  buffer.  It is possible to have a 32-bit buffer
             *  (ByteGranularity == 4), but a ObjDesc->CommonField.BitLength
             *  of 8 or 16, meaning that the upper bytes of merged data
             *  are undesired.  This section fixes that.
             */
            switch (ObjDesc->CommonField.BitLength)
            {
            case 8:
                MergedDatum &= 0x000000FF;
                break;

            case 16:
                MergedDatum &= 0x0000FFFF;
                break;
            }

            /*
             * Now store the datum in the caller's buffer, according to
             * the data type
             */
            switch (ByteGranularity)
            {
            case 1:
                ((UINT8 *) Buffer) [ThisFieldDatumOffset] = (UINT8) MergedDatum;
                break;

            case 2:
                MOVE_UNALIGNED16_TO_16 (&(((UINT16 *) Buffer) [ThisFieldDatumOffset]), &MergedDatum);
                break;

            case 4:
                MOVE_UNALIGNED32_TO_32 (&(((UINT32 *) Buffer) [ThisFieldDatumOffset]), &MergedDatum);
                break;
            }

            /*
             * Save the most recent datum since it contains bits of
             * the *next* field datum
             */

            PreviousRawDatum = ThisRawDatum;

            ThisFieldByteOffset += ByteGranularity;
            ThisFieldDatumOffset++;

        }  /* while */
    }

Cleanup:

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiAmlWriteFieldDatum
 *
 * PARAMETERS:  *ObjDesc            - Field to be set
 *              Value               - Value to store
 *              FieldBitWidth       - Field Width in bits (8, 16, or 32)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store the value into the given field
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiAmlWriteFieldDatum (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT32                  FieldByteOffset,
    UINT32                  FieldBitWidth,
    UINT32                  Value)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OPERAND_OBJECT     *RgnDesc = NULL;
    ACPI_PHYSICAL_ADDRESS   Address;
    UINT32                  FieldByteWidth;


    FUNCTION_TRACE_U32 ("AmlWriteFieldDatum", FieldByteOffset);


    FieldByteWidth = DIV_8 (FieldBitWidth);

    /*
     * BufferFields - Read from a Buffer
     * Other Fields - Read from a Operation Region.
     */

    switch (ObjDesc->Common.Type)
    {
    case ACPI_TYPE_BUFFER_FIELD:

        /*
         * For BufferFields, we only need to copy the data to the
         * target buffer.  Length is the field width in bytes.
         */
        MEMCPY ((ObjDesc->BufferField.BufferObj)->Buffer.Pointer
                + ObjDesc->BufferField.ByteOffset + FieldByteOffset,
                &Value, FieldByteWidth);
        Status = AE_OK;
        break;


    case INTERNAL_TYPE_REGION_FIELD:
    case INTERNAL_TYPE_BANK_FIELD:

        /*
         * For other fields, we need to go through an Operation Region
         * (Only types that will get here are RegionFields and BankFields)
         */
        RgnDesc = ObjDesc->CommonField.RegionObj;
        Status = AcpiAmlSetupField (ObjDesc, RgnDesc, FieldBitWidth);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }


        /*
         * Set offset to next multiple of field width,
         *  add region base address and offset within the field
         */
        Address = RgnDesc->Region.Address +
                  (ObjDesc->CommonField.ByteOffset * FieldByteWidth) +
                  FieldByteOffset;

        DEBUG_PRINT (TRACE_BFIELD,
            ("AmlWriteFieldDatum: Store %lx in Region %s(%X) at %p width %X\n",
            Value, AcpiCmGetRegionName (RgnDesc->Region.SpaceId),
            RgnDesc->Region.SpaceId, Address,
            FieldBitWidth));

        /* Invoke the appropriate AddressSpace/OpRegion handler */

        Status = AcpiEvAddressSpaceDispatch (RgnDesc, ACPI_WRITE_ADR_SPACE,
                                            Address, FieldBitWidth, &Value);

        if (Status == AE_NOT_IMPLEMENTED)
        {
            DEBUG_PRINT (ACPI_ERROR,
                ("AmlWriteFieldDatum: **** Region type %s(%X) not implemented\n",
                AcpiCmGetRegionName (RgnDesc->Region.SpaceId),
                RgnDesc->Region.SpaceId));
        }

        else if (Status == AE_NOT_EXIST)
        {
            DEBUG_PRINT (ACPI_ERROR,
                ("AmlWriteFieldDatum: **** Region type %s(%X) does not have a handler\n",
                AcpiCmGetRegionName (RgnDesc->Region.SpaceId),
                RgnDesc->Region.SpaceId));
        }

        break;


    default:

        DEBUG_PRINT (ACPI_ERROR,
            ("AmlWriteFieldDatum: %p, wrong source type - %s\n",
            ObjDesc, AcpiCmGetTypeName (ObjDesc->Common.Type)));
        Status = AE_AML_INTERNAL;
        break;
    }


    DEBUG_PRINT (TRACE_BFIELD,
        ("AmlWriteFieldDatum: Value written=%08lX \n", Value));


    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiAmlWriteFieldDatumWithUpdateRule
 *
 * PARAMETERS:  *ObjDesc            - Field to be set
 *              Value               - Value to store
 *              FieldBitWidth       - Field Width in bits (8, 16, or 32)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Apply the field update rule to a field write
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiAmlWriteFieldDatumWithUpdateRule (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT32                  Mask,
    UINT32                  FieldValue,
    UINT32                  ThisFieldByteOffset,
    UINT32                  BitGranularity)
{
    ACPI_STATUS             Status = AE_OK;
    UINT32                  MergedValue;
    UINT32                  CurrentValue;


    /* Start with the new bits  */

    MergedValue = FieldValue;


    /* Decode the update rule */

    switch (ObjDesc->CommonField.UpdateRule)
    {

    case UPDATE_PRESERVE:

        /* Check if update rule needs to be applied (not if mask is all ones) */

        /* The left shift drops the bits we want to ignore. */
        if ((~Mask << (sizeof(Mask)*8 - BitGranularity)) != 0)
        {
            /*
             * Read the current contents of the byte/word/dword containing
             * the field, and merge with the new field value.
             */
            Status = AcpiAmlReadFieldDatum (ObjDesc, ThisFieldByteOffset,
                            BitGranularity, &CurrentValue);
            MergedValue |= (CurrentValue & ~Mask);
        }
        break;


    case UPDATE_WRITE_AS_ONES:

        /* Set positions outside the field to all ones */

        MergedValue |= ~Mask;
        break;


    case UPDATE_WRITE_AS_ZEROS:

        /* Set positions outside the field to all zeros */

        MergedValue &= Mask;
        break;


    default:
        DEBUG_PRINT (ACPI_ERROR,
            ("WriteFieldDatumWithUpdateRule: Unknown UpdateRule setting: %x\n",
            ObjDesc->CommonField.UpdateRule));
        Status = AE_AML_OPERAND_VALUE;
    }


    /* Write the merged value */

    if (ACPI_SUCCESS (Status))
    {
        Status = AcpiAmlWriteFieldDatum (ObjDesc, ThisFieldByteOffset,
                        BitGranularity, MergedValue);
    }

    return (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiAmlInsertIntoField
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
AcpiAmlInsertIntoField (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    void                    *Buffer,
    UINT32                  BufferLength,
    UINT32                  ByteLength,
    UINT32                  DatumLength,
    UINT32                  BitGranularity,
    UINT32                  ByteGranularity)
{
    ACPI_STATUS             Status;
    UINT32                  ThisFieldByteOffset;
    UINT32                  ThisFieldDatumOffset;
    UINT32                  Mask;
    UINT32                  MergedDatum;
    UINT32                  PreviousRawDatum;
    UINT32                  ThisRawDatum;
    UINT32                  FieldValue;
    UINT32                  ValidFieldBits;


    FUNCTION_TRACE ("AmlInsertIntoField");


    /*
     * Break the request into up to three parts:
     * non-aligned part at start, aligned part in middle, non-aligned part
     * at end --- Just like an I/O request ---
     */

    ThisFieldByteOffset = 0;
    ThisFieldDatumOffset= 0;

    /* Get a datum */

    switch (ByteGranularity)
    {
    case 1:
        PreviousRawDatum = ((UINT8 *) Buffer) [ThisFieldDatumOffset];
        break;

    case 2:
        MOVE_UNALIGNED16_TO_32 (&PreviousRawDatum,
                &(((UINT16 *) Buffer) [ThisFieldDatumOffset]));
        break;

    case 4:
        MOVE_UNALIGNED32_TO_32 (&PreviousRawDatum,
                &(((UINT32 *) Buffer) [ThisFieldDatumOffset]));
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR,
            ("AmlInsertIntoField: Invalid granularity: %x\n",
            ByteGranularity));
        Status = AE_AML_OPERAND_VALUE;
        goto Cleanup;
    }


    /*
     * Write a partial field datum if field does not begin on a datum boundary
     *
     * Construct Mask with 1 bits where the field is, 0 bits elsewhere
     *
     * 1) Bits above the field
     */

    Mask = (((UINT32)(-1)) << (UINT32) ObjDesc->CommonField.BitOffset);

    /* 2) Only the bottom 5 bits are valid for a shift operation. */

    if ((ObjDesc->CommonField.BitOffset + ObjDesc->CommonField.BitLength) < 32)
    {
        /* Bits above the field */

        Mask &= (~(((UINT32) (-1)) << ((UINT32) ObjDesc->CommonField.BitOffset +
                                       (UINT32) ObjDesc->CommonField.BitLength)));
    }

    /* 3) Shift and mask the value into the field position */

    FieldValue = (PreviousRawDatum << ObjDesc->CommonField.BitOffset) & Mask;

    Status = AcpiAmlWriteFieldDatumWithUpdateRule (ObjDesc, Mask, FieldValue,
                        ThisFieldByteOffset, BitGranularity);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }


    /* If the field fits within one datum, we are done. */

    if ((DatumLength == 1) &&
       ((ObjDesc->CommonField.BitOffset + ObjDesc->CommonField.BitLength) <=
            (UINT16) BitGranularity))
    {
        goto Cleanup;
    }

    /*
     * We don't need to worry about the update rule for these data, because
     * all of the bits are part of the field.
     *
     * Can't write the last datum, however, because it might contain bits that
     * are not part of the field -- the update rule must be applied.
     */

    while (ThisFieldDatumOffset < (DatumLength - 1))
    {
        ThisFieldDatumOffset++;

        /* Get the next raw datum, it contains bits of the current field datum... */

        switch (ByteGranularity)
        {
        case 1:
            ThisRawDatum = ((UINT8 *) Buffer) [ThisFieldDatumOffset];
            break;

        case 2:
            MOVE_UNALIGNED16_TO_32 (&ThisRawDatum,
                    &(((UINT16 *) Buffer) [ThisFieldDatumOffset]));
            break;

        case 4:
            MOVE_UNALIGNED32_TO_32 (&ThisRawDatum,
                    &(((UINT32 *) Buffer) [ThisFieldDatumOffset]));
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR,
                ("AmlInsertIntoField: Invalid Byte Granularity: %x\n",
                ByteGranularity));
            Status = AE_AML_OPERAND_VALUE;
            goto Cleanup;
        }

        /*
         * Put together bits of the two raw data to make a complete field
         * datum
         */

        if (ObjDesc->CommonField.BitOffset != 0)
        {
            MergedDatum = (PreviousRawDatum >>
                            (BitGranularity - ObjDesc->CommonField.BitOffset)) |
                          (ThisRawDatum << ObjDesc->CommonField.BitOffset);
        }

        else
        {
            MergedDatum = ThisRawDatum;
        }

        /* Now write the completed datum  */


        Status = AcpiAmlWriteFieldDatum (ObjDesc,
                        ThisFieldByteOffset + ByteGranularity,
                        BitGranularity, MergedDatum);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }


        /*
         * Save the most recent datum since it contains bits of
         * the *next* field datum
         */

        PreviousRawDatum = ThisRawDatum;

        ThisFieldByteOffset += ByteGranularity;

    }  /* while */


    /* Write a partial field datum if field does not end on a datum boundary */

    if ((ObjDesc->CommonField.BitLength + ObjDesc->CommonField.BitOffset) %
        BitGranularity)
    {
        switch (ByteGranularity)
        {
        case 1:
            ThisRawDatum = ((UINT8 *) Buffer) [ThisFieldDatumOffset];
            break;

        case 2:
            MOVE_UNALIGNED16_TO_32 (&ThisRawDatum,
                    &(((UINT16 *) Buffer) [ThisFieldDatumOffset]));
            break;

        case 4:
            MOVE_UNALIGNED32_TO_32 (&ThisRawDatum,
                    &(((UINT32 *) Buffer) [ThisFieldDatumOffset]));
            break;
        }

        /* Construct Mask with 1 bits where the field is, 0 bits elsewhere */

        ValidFieldBits = ((ObjDesc->CommonField.BitLength % BitGranularity) +
                            ObjDesc->CommonField.BitOffset);

        Mask = (((UINT32) 1 << ValidFieldBits) - (UINT32) 1);

        /* Shift and mask the value into the field position */

        FieldValue = (PreviousRawDatum >>
                        (BitGranularity - ObjDesc->CommonField.BitOffset)) & Mask;

        Status = AcpiAmlWriteFieldDatumWithUpdateRule (ObjDesc, Mask,
                        FieldValue, ThisFieldByteOffset + ByteGranularity,
                        BitGranularity);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }
    }


Cleanup:

    return_ACPI_STATUS (Status);
}


