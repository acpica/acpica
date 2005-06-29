/******************************************************************************
 *
 * Module Name: iefread - read from a field
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


#define __IEFREAD_C__

#include "acpi.h"
#include "interp.h"
#include "amlcode.h"
#include "namesp.h"
#include "hardware.h"
#include "events.h"


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("iefread");


/*****************************************************************************
 *
 * FUNCTION:    AcpiAmlReadFieldData
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
AcpiAmlReadFieldData (
    ACPI_OBJECT_INTERNAL    *ObjDesc,
    UINT32                  FieldByteOffset,
    UINT32                  FieldBitWidth,
    UINT32                  *Value)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    *RgnDesc = NULL;
    UINT32                  Address;
    UINT32                  LocalValue = 0;
    INT32                   FieldByteWidth;


    FUNCTION_TRACE ("AmlReadFieldData");


    /* ObjDesc is validated by callers */

    if (ObjDesc)
    {
        RgnDesc = ObjDesc->Field.Container;
    }


    FieldByteWidth = DIV_8 (FieldBitWidth);
    Status = AcpiAmlSetupField (ObjDesc, RgnDesc, FieldBitWidth);
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
     * field width, add region base address and offset within the field
     */

    Address = RgnDesc->Region.Address +
              (ObjDesc->Field.Offset & ~((UINT32) FieldByteWidth - 1)) +
              FieldByteOffset;

    if (RgnDesc->Region.SpaceId >= NUM_REGION_TYPES)
    {
        DEBUG_PRINT (TRACE_OPREGION,
                    ("AmlReadFieldData: **** Unknown OpRegion SpaceID %d at %08lx width %d\n",
                    RgnDesc->Region.SpaceId, Address, FieldBitWidth));
    }

    else
    {
        DEBUG_PRINT (TRACE_OPREGION,
                    ("AmlReadFieldData: OpRegion %s at %08lx width %d\n",
                    Acpi_GblRegionTypes[RgnDesc->Region.SpaceId], Address, FieldBitWidth));
    }


    /* Invoke the appropriate AddressSpace/OpRegion handler */

    Status = AcpiEvAddressSpaceDispatch (RgnDesc, ADDRESS_SPACE_READ,
                                        Address, FieldBitWidth, Value);

    if (Status == AE_NOT_IMPLEMENTED)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlReadFieldData: **** OpRegion type %s not implemented\n",
                Acpi_GblRegionTypes[RgnDesc->Region.SpaceId]));
    }

    else if (Status == AE_EXIST)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlReadFieldData: **** Unknown OpRegion SpaceID %d\n",
                RgnDesc->Region.SpaceId));
    }

    DEBUG_PRINT (TRACE_OPREGION, ("AmlReadField: Returned value=%08lx \n", *Value));

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiAmlReadField
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
AcpiAmlReadField (
    ACPI_OBJECT_INTERNAL    *ObjDesc,
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
    UINT32                  ThisRawDatum;
    UINT32                  ValidFieldBits;
    UINT32                  Mask;
    UINT32                  MergedDatum = 0;



    FUNCTION_TRACE ("AmlReadField");

    /*
     * Clear the caller's buffer (the whole buffer length as given)
     * This is very important, especially in the cases where a byte is read,
     * but the buffer is really a UINT32 (4 bytes).
     */

    MEMSET (Buffer, 0, BufferLength);

    /* Read the first raw datum to prime the loop */

    ThisFieldByteOffset = 0;
    ThisFieldDatumOffset= 0;

    Status = AcpiAmlReadFieldData (ObjDesc, ThisFieldByteOffset, BitGranularity, &PreviousRawDatum);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }

    /* We might actually be done if the request fits in one datum */

    if ((DatumLength == 1) && ((ObjDesc->Field.BitOffset + ObjDesc->FieldUnit.Length) <= (UINT16) BitGranularity))
    {
        MergedDatum = PreviousRawDatum;

        MergedDatum = (MergedDatum >> ObjDesc->Field.BitOffset);

        ValidFieldBits = ObjDesc->FieldUnit.Length % BitGranularity;
        if (ValidFieldBits)
        {
            Mask = (((UINT32) 1 << ValidFieldBits) - (UINT32) 1);
            MergedDatum &= Mask;
        }


        /* Place the MergedDatum into the proper format and return buffer field */
        switch (ByteGranularity)
        {
        case 1:
            ((UINT8 *) Buffer) [ThisFieldDatumOffset] = (UINT8) MergedDatum;
            break;

        case 2:
            STORE16TO16 (&(((UINT16 *) Buffer) [ThisFieldDatumOffset]), &MergedDatum);
            break;

        case 4:
            STORE32TO32 (&(((UINT32 *) Buffer) [ThisFieldDatumOffset]), &MergedDatum);
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
            /* Get the next raw datum, it contains bits of the current field datum... */

            Status = AcpiAmlReadFieldData (ObjDesc, ThisFieldByteOffset + ByteGranularity,
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

            /* Put together bits of the two raw data to make a complete field datum */

            if (ObjDesc->Field.BitOffset != 0)
            {
                MergedDatum = (PreviousRawDatum >> ObjDesc->Field.BitOffset) |
                                (ThisRawDatum << (BitGranularity - ObjDesc->Field.BitOffset));
            }

            else
            {
                MergedDatum = PreviousRawDatum;
            }

            /* Now store the datum in the caller's buffer, according to the data type */

            switch (ByteGranularity)
            {
            case 1:
                ((UINT8 *) Buffer) [ThisFieldDatumOffset] = (UINT8) MergedDatum;
                break;

            case 2:
                STORE16TO16 (&(((UINT16 *) Buffer) [ThisFieldDatumOffset]), &MergedDatum);
                break;

            case 4:
                STORE32TO32 (&(((UINT32 *) Buffer) [ThisFieldDatumOffset]), &MergedDatum);
                break;
            }


            /* Save the most recent datum since it contains bits of the *next* field datum */

            PreviousRawDatum = ThisRawDatum;

            ThisFieldByteOffset += ByteGranularity;
            ThisFieldDatumOffset++;

        }  /* while */
    }

Cleanup:

    return_ACPI_STATUS (Status);
}






