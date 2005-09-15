/*******************************************************************************
 *
 * Module Name: rsmisc - Miscellaneous resource descriptors
 *              $Revision: 1.31 $
 *
 ******************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2005, Intel Corp.
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

#define __RSMISC_C__

#include "acpi.h"
#include "acresrc.h"

#define _COMPONENT          ACPI_RESOURCES
        ACPI_MODULE_NAME    ("rsmisc")


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsGenericRegisterResource
 *
 * PARAMETERS:  ByteStreamBuffer        - Pointer to the resource input byte
 *                                        stream
 *              BytesConsumed           - Pointer to where the number of bytes
 *                                        consumed the ByteStreamBuffer is
 *                                        returned
 *              OutputBuffer            - Pointer to the return data buffer
 *              StructureSize           - Pointer to where the number of bytes
 *                                        in the return data struct is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Take the resource byte stream and fill out the appropriate
 *              structure pointed to by the OutputBuffer.  Return the
 *              number of bytes consumed from the byte stream.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsGenericRegisterResource (
    UINT8                   *ByteStreamBuffer,
    ACPI_SIZE               *BytesConsumed,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *StructureSize)
{
    UINT8                   *Buffer = ByteStreamBuffer;
    ACPI_RESOURCE           *OutputStruct = (void *) *OutputBuffer;
    UINT16                  Temp16;
    UINT8                   Temp8;
    ACPI_SIZE               StructSize = ACPI_SIZEOF_RESOURCE (
                                            ACPI_RESOURCE_GENERIC_REG);


    ACPI_FUNCTION_TRACE ("RsGenericRegisterResource");


    /* Byte 0 is the Descriptor Type */

    Buffer += 1;

    /* Get the Descriptor Length field (Bytes 1-2) */

    ACPI_MOVE_16_TO_16 (&Temp16, Buffer);
    Buffer += 2;

    /* Validate the descriptor length */

    if (Temp16 != 12)
    {
        return_ACPI_STATUS (AE_AML_BAD_RESOURCE_LENGTH);
    }

    /* The number of bytes consumed is fixed (12 + 3) */

    *BytesConsumed = 15;

    /* Fill out the structure */

    OutputStruct->Type = ACPI_RSTYPE_GENERIC_REG;

    /* Get SpaceId (Byte 3) */

    Temp8 = *Buffer;
    OutputStruct->Data.GenericReg.SpaceId = Temp8;
    Buffer += 1;

    /* Get RegisterBitWidth (Byte 4) */

    Temp8 = *Buffer;
    OutputStruct->Data.GenericReg.BitWidth = Temp8;
    Buffer += 1;

    /* Get RegisterBitOffset (Byte 5) */

    Temp8 = *Buffer;
    OutputStruct->Data.GenericReg.BitOffset = Temp8;
    Buffer += 1;

    /* Get AddressSize (Byte 6) */

    Temp8 = *Buffer;
    OutputStruct->Data.GenericReg.AddressSize = Temp8;
    Buffer += 1;

    /* Get RegisterAddress (Bytes 7-14) */

    ACPI_MOVE_64_TO_64 (&OutputStruct->Data.GenericReg.Address, Buffer);

    /* Set the Length parameter */

    OutputStruct->Length = (UINT32) StructSize;

    /* Return the final size of the structure */

    *StructureSize = StructSize;
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsGenericRegisterStream
 *
 * PARAMETERS:  Resource                - Pointer to the resource linked list
 *              OutputBuffer            - Pointer to the user's return buffer
 *              BytesConsumed           - Pointer to where the number of bytes
 *                                        used in the OutputBuffer is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Take the linked list resource structure and fills in the
 *              the appropriate bytes in a byte stream
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsGenericRegisterStream (
    ACPI_RESOURCE           *Resource,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *BytesConsumed)
{
    UINT8                   *Buffer = *OutputBuffer;
    UINT16                  Temp16;


    ACPI_FUNCTION_TRACE ("RsGenericRegisterStream");


    /* Set the Descriptor Type (Byte 0) */

    *Buffer = ACPI_RDESC_TYPE_GENERIC_REGISTER;
    Buffer += 1;

    /* Set the Descriptor Length (Bytes 1-2) */

    Temp16 = 12;
    ACPI_MOVE_16_TO_16 (Buffer, &Temp16);
    Buffer += 2;

    /* Set SpaceId (Byte 3) */

    *Buffer = (UINT8) Resource->Data.GenericReg.SpaceId;
    Buffer += 1;

    /* Set RegisterBitWidth (Byte 4) */

    *Buffer = (UINT8) Resource->Data.GenericReg.BitWidth;
    Buffer += 1;

    /* Set RegisterBitOffset (Byte 5) */

    *Buffer = (UINT8) Resource->Data.GenericReg.BitOffset;
    Buffer += 1;

    /* Set AddressSize (Byte 6) */

    *Buffer = (UINT8) Resource->Data.GenericReg.AddressSize;
    Buffer += 1;

    /* Set RegisterAddress (Bytes 7-14) */

    ACPI_MOVE_64_TO_64 (Buffer, &Resource->Data.GenericReg.Address);
    Buffer += 8;

    /* Return the number of bytes consumed in this operation */

    *BytesConsumed = ACPI_PTR_DIFF (Buffer, *OutputBuffer);
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsEndTagResource
 *
 * PARAMETERS:  ByteStreamBuffer        - Pointer to the resource input byte
 *                                        stream
 *              BytesConsumed           - Pointer to where the number of bytes
 *                                        consumed the ByteStreamBuffer is
 *                                        returned
 *              OutputBuffer            - Pointer to the return data buffer
 *              StructureSize           - Pointer to where the number of bytes
 *                                        in the return data struct is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Take the resource byte stream and fill out the appropriate
 *              structure pointed to by the OutputBuffer.  Return the
 *              number of bytes consumed from the byte stream.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsEndTagResource (
    UINT8                   *ByteStreamBuffer,
    ACPI_SIZE               *BytesConsumed,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *StructureSize)
{
    ACPI_RESOURCE           *OutputStruct = (void *) *OutputBuffer;
    ACPI_SIZE               StructSize = ACPI_RESOURCE_LENGTH;


    ACPI_FUNCTION_TRACE ("RsEndTagResource");


    /* The number of bytes consumed is static */

    *BytesConsumed = 2;

    /* Fill out the structure */

    OutputStruct->Type = ACPI_RSTYPE_END_TAG;

    /* Set the Length parameter */

    OutputStruct->Length = 0;

    /* Return the final size of the structure */

    *StructureSize = StructSize;
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsEndTagStream
 *
 * PARAMETERS:  Resource                - Pointer to the resource linked list
 *              OutputBuffer            - Pointer to the user's return buffer
 *              BytesConsumed           - Pointer to where the number of bytes
 *                                        used in the OutputBuffer is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Take the linked list resource structure and fills in the
 *              the appropriate bytes in a byte stream
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsEndTagStream (
    ACPI_RESOURCE           *Resource,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *BytesConsumed)
{
    UINT8                   *Buffer = *OutputBuffer;
    UINT8                   Temp8 = 0;


    ACPI_FUNCTION_TRACE ("RsEndTagStream");


    /* The Descriptor Type field is static */

    *Buffer = ACPI_RDESC_TYPE_END_TAG | 0x01;
    Buffer += 1;

    /*
     * Set the Checksum - zero means that the resource data is treated as if
     * the checksum operation succeeded (ACPI Spec 1.0b Section 6.4.2.8)
     */
    Temp8 = 0;

    *Buffer = Temp8;
    Buffer += 1;

    /* Return the number of bytes consumed in this operation */

    *BytesConsumed = ACPI_PTR_DIFF (Buffer, *OutputBuffer);
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsVendorResource
 *
 * PARAMETERS:  ByteStreamBuffer        - Pointer to the resource input byte
 *                                        stream
 *              BytesConsumed           - Pointer to where the number of bytes
 *                                        consumed the ByteStreamBuffer is
 *                                        returned
 *              OutputBuffer            - Pointer to the return data buffer
 *              StructureSize           - Pointer to where the number of bytes
 *                                        in the return data struct is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Take the resource byte stream and fill out the appropriate
 *              structure pointed to by the OutputBuffer.  Return the
 *              number of bytes consumed from the byte stream.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsVendorResource (
    UINT8                   *ByteStreamBuffer,
    ACPI_SIZE               *BytesConsumed,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *StructureSize)
{
    UINT8                   *Buffer = ByteStreamBuffer;
    ACPI_RESOURCE           *OutputStruct = (void *) *OutputBuffer;
    UINT16                  Temp16 = 0;
    UINT8                   Temp8 = 0;
    UINT8                   Index;
    ACPI_SIZE               StructSize = ACPI_SIZEOF_RESOURCE (
                                            ACPI_RESOURCE_VENDOR);


    ACPI_FUNCTION_TRACE ("RsVendorResource");


    /* Dereference the Descriptor to find if this is a large or small item. */

    Temp8 = *Buffer;

    if (Temp8 & ACPI_RDESC_TYPE_LARGE)
    {
        /* Large Item, point to the length field */

        Buffer += 1;

        /* Dereference */

        ACPI_MOVE_16_TO_16 (&Temp16, Buffer);

        /* Calculate bytes consumed */

        *BytesConsumed = (ACPI_SIZE) Temp16 + 3;

        /* Point to the first vendor byte */

        Buffer += 2;
    }
    else
    {
        /* Small Item, dereference the size */

        Temp16 = (UINT8)(*Buffer & 0x07);

        /* Calculate bytes consumed */

        *BytesConsumed = (ACPI_SIZE) Temp16 + 1;

        /* Point to the first vendor byte */

        Buffer += 1;
    }

    OutputStruct->Type = ACPI_RSTYPE_VENDOR;
    OutputStruct->Data.VendorSpecific.Length = Temp16;

    for (Index = 0; Index < Temp16; Index++)
    {
        OutputStruct->Data.VendorSpecific.Reserved[Index] = *Buffer;
        Buffer += 1;
    }

    /*
     * In order for the StructSize to fall on a 32-bit boundary,
     * calculate the length of the vendor string and expand the
     * StructSize to the next 32-bit boundary.
     */
    StructSize += ACPI_ROUND_UP_TO_32BITS (Temp16);

    /* Set the Length parameter */

    OutputStruct->Length = (UINT32) StructSize;

    /* Return the final size of the structure */

    *StructureSize = StructSize;
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsVendorStream
 *
 * PARAMETERS:  Resource                - Pointer to the resource linked list
 *              OutputBuffer            - Pointer to the user's return buffer
 *              BytesConsumed           - Pointer to where the number of bytes
 *                                        used in the OutputBuffer is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Take the linked list resource structure and fills in the
 *              the appropriate bytes in a byte stream
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsVendorStream (
    ACPI_RESOURCE           *Resource,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *BytesConsumed)
{
    UINT8                   *Buffer = *OutputBuffer;
    UINT16                  Temp16 = 0;
    UINT8                   Temp8 = 0;
    UINT8                   Index;


    ACPI_FUNCTION_TRACE ("RsVendorStream");


    /* Dereference the length to find if this is a large or small item. */

    if (Resource->Data.VendorSpecific.Length > 7)
    {
        /* Large Item, Set the descriptor field and length bytes */

        *Buffer = ACPI_RDESC_TYPE_LARGE_VENDOR;
        Buffer += 1;

        Temp16 = (UINT16) Resource->Data.VendorSpecific.Length;

        ACPI_MOVE_16_TO_16 (Buffer, &Temp16);
        Buffer += 2;
    }
    else
    {
        /* Small Item, Set the descriptor field */

        Temp8 = ACPI_RDESC_TYPE_SMALL_VENDOR;
        Temp8 |= (UINT8) Resource->Data.VendorSpecific.Length;

        *Buffer = Temp8;
        Buffer += 1;
    }

    /* Loop through all of the Vendor Specific fields */

    for (Index = 0; Index < Resource->Data.VendorSpecific.Length; Index++)
    {
        Temp8 = Resource->Data.VendorSpecific.Reserved[Index];

        *Buffer = Temp8;
        Buffer += 1;
    }

    /* Return the number of bytes consumed in this operation */

    *BytesConsumed = ACPI_PTR_DIFF (Buffer, *OutputBuffer);
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsStartDependFnsResource
 *
 * PARAMETERS:  ByteStreamBuffer        - Pointer to the resource input byte
 *                                        stream
 *              BytesConsumed           - Pointer to where the number of bytes
 *                                        consumed the ByteStreamBuffer is
 *                                        returned
 *              OutputBuffer            - Pointer to the return data buffer
 *              StructureSize           - Pointer to where the number of bytes
 *                                        in the return data struct is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Take the resource byte stream and fill out the appropriate
 *              structure pointed to by the OutputBuffer.  Return the
 *              number of bytes consumed from the byte stream.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsStartDependFnsResource (
    UINT8                   *ByteStreamBuffer,
    ACPI_SIZE               *BytesConsumed,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *StructureSize)
{
    UINT8                   *Buffer = ByteStreamBuffer;
    ACPI_RESOURCE           *OutputStruct = (void *) *OutputBuffer;
    UINT8                   Temp8 = 0;
    ACPI_SIZE               StructSize = ACPI_SIZEOF_RESOURCE (
                                ACPI_RESOURCE_START_DPF);


    ACPI_FUNCTION_TRACE ("RsStartDependFnsResource");


    /* The number of bytes consumed are found in the descriptor (Bits:0-1) */

    Temp8 = *Buffer;

    *BytesConsumed = (Temp8 & 0x01) + 1;

    OutputStruct->Type = ACPI_RSTYPE_START_DPF;

    /* Point to Byte 1 if it is used */

    if (2 == *BytesConsumed)
    {
        Buffer += 1;
        Temp8 = *Buffer;

        /* Check Compatibility priority */

        OutputStruct->Data.StartDpf.CompatibilityPriority = Temp8 & 0x03;

        if (3 == OutputStruct->Data.StartDpf.CompatibilityPriority)
        {
            return_ACPI_STATUS (AE_AML_BAD_RESOURCE_VALUE);
        }

        /* Check Performance/Robustness preference */

        OutputStruct->Data.StartDpf.PerformanceRobustness = (Temp8 >> 2) & 0x03;

        if (3 == OutputStruct->Data.StartDpf.PerformanceRobustness)
        {
            return_ACPI_STATUS (AE_AML_BAD_RESOURCE_VALUE);
        }
    }
    else
    {
        OutputStruct->Data.StartDpf.CompatibilityPriority =
            ACPI_ACCEPTABLE_CONFIGURATION;

        OutputStruct->Data.StartDpf.PerformanceRobustness =
            ACPI_ACCEPTABLE_CONFIGURATION;
    }

    /* Set the Length parameter */

    OutputStruct->Length = (UINT32) StructSize;

    /* Return the final size of the structure */

    *StructureSize = StructSize;
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsEndDependFnsResource
 *
 * PARAMETERS:  ByteStreamBuffer        - Pointer to the resource input byte
 *                                        stream
 *              BytesConsumed           - Pointer to where the number of bytes
 *                                        consumed the ByteStreamBuffer is
 *                                        returned
 *              OutputBuffer            - Pointer to the return data buffer
 *              StructureSize           - Pointer to where the number of bytes
 *                                        in the return data struct is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Take the resource byte stream and fill out the appropriate
 *              structure pointed to by the OutputBuffer.  Return the
 *              number of bytes consumed from the byte stream.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsEndDependFnsResource (
    UINT8                   *ByteStreamBuffer,
    ACPI_SIZE               *BytesConsumed,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *StructureSize)
{
    ACPI_RESOURCE           *OutputStruct = (void *) *OutputBuffer;
    ACPI_SIZE               StructSize = ACPI_RESOURCE_LENGTH;


    ACPI_FUNCTION_TRACE ("RsEndDependFnsResource");


    /* The number of bytes consumed is static */

    *BytesConsumed = 1;

    /*  Fill out the structure */

    OutputStruct->Type = ACPI_RSTYPE_END_DPF;

    /* Set the Length parameter */

    OutputStruct->Length = (UINT32) StructSize;

    /* Return the final size of the structure */

    *StructureSize = StructSize;
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsStartDependFnsStream
 *
 * PARAMETERS:  Resource                - Pointer to the resource linked list
 *              OutputBuffer            - Pointer to the user's return buffer
 *              BytesConsumed           - UINT32 pointer that is filled with
 *                                        the number of bytes of the
 *                                        OutputBuffer used
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Take the linked list resource structure and fills in the
 *              the appropriate bytes in a byte stream
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsStartDependFnsStream (
    ACPI_RESOURCE           *Resource,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *BytesConsumed)
{
    UINT8                   *Buffer = *OutputBuffer;
    UINT8                   Temp8 = 0;


    ACPI_FUNCTION_TRACE ("RsStartDependFnsStream");


    /*
     * The descriptor type field is set based upon whether a byte is needed
     * to contain Priority data.
     */
    if (ACPI_ACCEPTABLE_CONFIGURATION ==
            Resource->Data.StartDpf.CompatibilityPriority &&
        ACPI_ACCEPTABLE_CONFIGURATION ==
            Resource->Data.StartDpf.PerformanceRobustness)
    {
        *Buffer = ACPI_RDESC_TYPE_START_DEPENDENT;
    }
    else
    {
        *Buffer = ACPI_RDESC_TYPE_START_DEPENDENT | 0x01;
        Buffer += 1;

        /* Set the Priority Byte Definition */

        Temp8 = 0;
        Temp8 = (UINT8) ((Resource->Data.StartDpf.PerformanceRobustness &
                            0x03) << 2);
        Temp8 |= (Resource->Data.StartDpf.CompatibilityPriority &
                            0x03);
        *Buffer = Temp8;
    }

    Buffer += 1;

    /* Return the number of bytes consumed in this operation */

    *BytesConsumed = ACPI_PTR_DIFF (Buffer, *OutputBuffer);
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsEndDependFnsStream
 *
 * PARAMETERS:  Resource                - Pointer to the resource linked list
 *              OutputBuffer            - Pointer to the user's return buffer
 *              BytesConsumed           - Pointer to where the number of bytes
 *                                        used in the OutputBuffer is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Take the linked list resource structure and fills in the
 *              the appropriate bytes in a byte stream
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsEndDependFnsStream (
    ACPI_RESOURCE           *Resource,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *BytesConsumed)
{
    UINT8                   *Buffer = *OutputBuffer;


    ACPI_FUNCTION_TRACE ("RsEndDependFnsStream");


    /* The Descriptor Type field is static */

    *Buffer = ACPI_RDESC_TYPE_END_DEPENDENT;
    Buffer += 1;

    /* Return the number of bytes consumed in this operation */

    *BytesConsumed = ACPI_PTR_DIFF (Buffer, *OutputBuffer);
    return_ACPI_STATUS (AE_OK);
}

