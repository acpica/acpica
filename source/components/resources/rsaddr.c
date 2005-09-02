/*******************************************************************************
 *
 * Module Name: rsaddr - Address resource descriptors (16/32/64)
 *              $Revision: 1.43 $
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

#define __RSADDR_C__

#include "acpi.h"
#include "acresrc.h"

#define _COMPONENT          ACPI_RESOURCES
        ACPI_MODULE_NAME    ("rsaddr")

/* Local prototypes */

static void
AcpiRsDecodeGeneralFlags (
    ACPI_RESOURCE_DATA      *Resource,
    UINT8                   Flags);

static UINT8
AcpiRsEncodeGeneralFlags (
    ACPI_RESOURCE_DATA      *Resource);

static void
AcpiRsDecodeSpecificFlags (
    ACPI_RESOURCE_DATA      *Resource,
    UINT8                   Flags);

static UINT8
AcpiRsEncodeSpecificFlags (
    ACPI_RESOURCE_DATA      *Resource);


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsDecodeGeneralFlags
 *
 * PARAMETERS:  Resource            - Address resource data struct
 *              Flags               - Actual flag byte
 *
 * RETURN:      Decoded flag bits in resource struct
 *
 * DESCRIPTION: Decode a general flag byte to an address resource struct
 *
 ******************************************************************************/

static void
AcpiRsDecodeGeneralFlags (
    ACPI_RESOURCE_DATA      *Resource,
    UINT8                   Flags)
{
    ACPI_FUNCTION_ENTRY ();


    /* Producer / Consumer - flag bit[0] */

    Resource->Address.ProducerConsumer = (UINT32) (Flags & 0x01);

    /* Decode (_DEC) - flag bit[1] */

    Resource->Address.Decode = (UINT32) ((Flags >> 1) & 0x01);

    /* Min Address Fixed (_MIF) - flag bit[2] */

    Resource->Address.MinAddressFixed = (UINT32) ((Flags >> 2) & 0x01);

    /* Max Address Fixed (_MAF) - flag bit[3] */

    Resource->Address.MaxAddressFixed = (UINT32) ((Flags >> 3) & 0x01);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsEncodeGeneralFlags
 *
 * PARAMETERS:  Resource            - Address resource data struct
 *
 * RETURN:      Encoded general flag byte
 *
 * DESCRIPTION: Construct a general flag byte from an address resource struct
 *
 ******************************************************************************/

static UINT8
AcpiRsEncodeGeneralFlags (
    ACPI_RESOURCE_DATA      *Resource)
{
    UINT8                   Flags;


    ACPI_FUNCTION_ENTRY ();


    /* Producer / Consumer - flag bit[0] */

    Flags = (UINT8) (Resource->Address.ProducerConsumer & 0x01);

    /* Decode (_DEC) - flag bit[1] */

    Flags |= (UINT8) ((Resource->Address.Decode & 0x01) << 1);

    /* Min Address Fixed (_MIF) - flag bit[2] */

    Flags |= (UINT8) ((Resource->Address.MinAddressFixed & 0x01) << 2);

    /* Max Address Fixed (_MAF) - flag bit[3] */

    Flags |= (UINT8) ((Resource->Address.MaxAddressFixed & 0x01) << 3);

    return (Flags);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsDecodeSpecificFlags
 *
 * PARAMETERS:  Resource            - Address resource data struct
 *              Flags               - Actual flag byte
 *
 * RETURN:      Decoded flag bits in attribute struct
 *
 * DESCRIPTION: Decode a type-specific flag byte to an attribute struct.
 *              Type-specific flags are only defined for the Memory and IO
 *              resource types.
 *
 ******************************************************************************/

static void
AcpiRsDecodeSpecificFlags (
    ACPI_RESOURCE_DATA      *Resource,
    UINT8                   Flags)
{
    ACPI_FUNCTION_ENTRY ();


    if (Resource->Address.ResourceType == ACPI_MEMORY_RANGE)
    {
        /* Write Status (_RW) - flag bit[0] */

        Resource->Address.Attribute.Memory.ReadWriteAttribute =
            (UINT16) (Flags & 0x01);

        /* Memory Attributes (_MEM) - flag bits[2:1] */

        Resource->Address.Attribute.Memory.CacheAttribute =
            (UINT16) ((Flags >> 1) & 0x03);
    }
    else if (Resource->Address.ResourceType == ACPI_IO_RANGE)
    {
        /* Ranges (_RNG) - flag bits[1:0] */

        Resource->Address.Attribute.Io.RangeAttribute =
            (UINT16) (Flags & 0x03);

        /* Translations (_TTP and _TRS) - flag bits[5:4] */

        Resource->Address.Attribute.Io.TranslationAttribute =
            (UINT16) ((Flags >> 4) & 0x03);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsEncodeSpecificFlags
 *
 * PARAMETERS:  Resource            - Address resource data struct
 *
 * RETURN:      Encoded type-specific flag byte
 *
 * DESCRIPTION: Construct a type-specific flag byte from an attribute struct.
 *              Type-specific flags are only defined for the Memory and IO
 *              resource types.
 *
 ******************************************************************************/

static UINT8
AcpiRsEncodeSpecificFlags (
    ACPI_RESOURCE_DATA      *Resource)
{
    UINT8                   Flags = 0;


    ACPI_FUNCTION_ENTRY ();


    if (Resource->Address.ResourceType == ACPI_MEMORY_RANGE)
    {
        /* Write Status (_RW) - flag bit[0] */

        Flags = (UINT8)
            (Resource->Address.Attribute.Memory.ReadWriteAttribute & 0x01);

        /* Memory Attributes (_MEM) - flag bits[2:1] */

        Flags |= (UINT8)
            ((Resource->Address.Attribute.Memory.CacheAttribute & 0x03) << 1);
    }
    else if (Resource->Address.ResourceType == ACPI_IO_RANGE)
    {
        /* Ranges (_RNG) - flag bits[1:0] */

        Flags = (UINT8)
            (Resource->Address.Attribute.Io.RangeAttribute & 0x03);

        /* Translations (_TTP and _TRS) - flag bits[5:4] */

        Flags |= (UINT8)
            ((Resource->Address.Attribute.Io.TranslationAttribute & 0x03) << 4);
    }

    return (Flags);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsAddress16Resource
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
AcpiRsAddress16Resource (
    UINT8                   *ByteStreamBuffer,
    ACPI_SIZE               *BytesConsumed,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *StructureSize)
{
    UINT32                  Index;
    UINT16                  Temp16;
    UINT8                   Temp8;
    UINT8                   *TempPtr;
    UINT8                   *Buffer = ByteStreamBuffer;
    ACPI_RESOURCE           *OutputStruct = (void *) *OutputBuffer;
    ACPI_SIZE               StructSize = ACPI_SIZEOF_RESOURCE (
                                            ACPI_RESOURCE_ADDRESS16);


    ACPI_FUNCTION_TRACE ("RsAddress16Resource");


    /* Get the Descriptor Length field */

    Buffer += 1;
    ACPI_MOVE_16_TO_16 (&Temp16, Buffer);

    /* Validate minimum descriptor length */

    if (Temp16 < 13)
    {
        return_ACPI_STATUS (AE_AML_BAD_RESOURCE_LENGTH);
    }

    *BytesConsumed = Temp16 + 3;
    OutputStruct->Id = ACPI_RSTYPE_ADDRESS16;

    /* Get the Resource Type (Byte3) */

    Buffer += 2;
    Temp8 = *Buffer;

    /* Values 0-2 and 0xC0-0xFF are valid */

    if ((Temp8 > 2) && (Temp8 < 0xC0))
    {
        return_ACPI_STATUS (AE_AML_INVALID_RESOURCE_TYPE);
    }

    OutputStruct->Data.Address16.ResourceType = Temp8;

    /* Get the General Flags (Byte4) */

    Buffer += 1;
    AcpiRsDecodeGeneralFlags (&OutputStruct->Data, *Buffer);

    /* Get the Type Specific Flags (Byte5) */

    Buffer += 1;
    AcpiRsDecodeSpecificFlags (&OutputStruct->Data, *Buffer);

    /* Get Granularity (Bytes 6-7) */

    Buffer += 1;
    ACPI_MOVE_16_TO_32 (&OutputStruct->Data.Address16.Granularity, Buffer);

    /* Get MinAddressRange (Bytes 8-9) */

    Buffer += 2;
    ACPI_MOVE_16_TO_32 (&OutputStruct->Data.Address16.MinAddressRange, Buffer);

    /* Get MaxAddressRange (Bytes 10-11) */

    Buffer += 2;
    ACPI_MOVE_16_TO_32 (&OutputStruct->Data.Address16.MaxAddressRange, Buffer);

    /* Get AddressTranslationOffset (Bytes 12-13) */

    Buffer += 2;
    ACPI_MOVE_16_TO_32 (&OutputStruct->Data.Address16.AddressTranslationOffset,
        Buffer);

    /* Get AddressLength (Bytes 14-15) */

    Buffer += 2;
    ACPI_MOVE_16_TO_32 (&OutputStruct->Data.Address16.AddressLength, Buffer);

    /* Resource Source Index (if present) */

    Buffer += 2;

    /*
     * This will leave us pointing to the Resource Source Index
     * If it is present, then save it off and calculate the
     * pointer to where the null terminated string goes:
     * Each Interrupt takes 32-bits + the 5 bytes of the
     * stream that are default.
     *
     * Note: Some resource descriptors will have an additional null, so
     * we add 1 to the length.
     */
    if (*BytesConsumed > (16 + 1))
    {
        /* Dereference the Index */

        OutputStruct->Data.Address16.ResourceSource.Index = (UINT32) *Buffer;

        /* Point to the String */

        Buffer += 1;

        /* Point the String pointer to the end of this structure */

        OutputStruct->Data.Address16.ResourceSource.StringPtr =
                (char *)((UINT8 * )OutputStruct + StructSize);

        TempPtr = (UINT8 *)
            OutputStruct->Data.Address16.ResourceSource.StringPtr;

        /* Copy the ResourceSource string into the buffer */

        Index = 0;
        while (*Buffer)
        {
            *TempPtr = *Buffer;

            TempPtr++;
            Buffer++;
            Index++;
        }

        /* Add the terminating null and set the string length */

        *TempPtr = 0;
        OutputStruct->Data.Address16.ResourceSource.StringLength = Index + 1;

        /*
         * In order for the StructSize to fall on a 32-bit boundary,
         * calculate the length of the string and expand the
         * StructSize to the next 32-bit boundary.
         */
        Temp8 = (UINT8) (Index + 1);
        StructSize += ACPI_ROUND_UP_TO_32BITS (Temp8);
    }
    else
    {
        OutputStruct->Data.Address16.ResourceSource.Index = 0;
        OutputStruct->Data.Address16.ResourceSource.StringLength = 0;
        OutputStruct->Data.Address16.ResourceSource.StringPtr = NULL;
    }

    /* Set the Length parameter */

    OutputStruct->Length = (UINT32) StructSize;

    /* Return the final size of the structure */

    *StructureSize = StructSize;
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsAddress16Stream
 *
 * PARAMETERS:  LinkedList              - Pointer to the resource linked list
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
AcpiRsAddress16Stream (
    ACPI_RESOURCE           *LinkedList,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *BytesConsumed)
{
    UINT8                   *Buffer = *OutputBuffer;
    UINT8                   *LengthField;
    ACPI_SIZE               ActualBytes;


    ACPI_FUNCTION_TRACE ("RsAddress16Stream");


    /* Set the Descriptor Type field */

    *Buffer = ACPI_RDESC_TYPE_WORD_ADDRESS_SPACE;
    Buffer += 1;

    /* Save a pointer to the Length field - to be filled in later */

    LengthField = Buffer;
    Buffer += 2;

    /* Set the Resource Type (Memory, Io, BusNumber) */

    *Buffer = (UINT8) (LinkedList->Data.Address16.ResourceType & 0x03);
    Buffer += 1;

    /* Set the general flags */

    *Buffer = AcpiRsEncodeGeneralFlags (&LinkedList->Data);
    Buffer += 1;

    /* Set the type specific flags */

    *Buffer = AcpiRsEncodeSpecificFlags (&LinkedList->Data);
    Buffer += 1;

    /* Set the address space granularity */

    ACPI_MOVE_32_TO_16 (Buffer, &LinkedList->Data.Address16.Granularity);
    Buffer += 2;

    /* Set the address range minimum */

    ACPI_MOVE_32_TO_16 (Buffer, &LinkedList->Data.Address16.MinAddressRange);
    Buffer += 2;

    /* Set the address range maximum */

    ACPI_MOVE_32_TO_16 (Buffer, &LinkedList->Data.Address16.MaxAddressRange);
    Buffer += 2;

    /* Set the address translation offset */

    ACPI_MOVE_32_TO_16 (Buffer,
        &LinkedList->Data.Address16.AddressTranslationOffset);
    Buffer += 2;

    /* Set the address length */

    ACPI_MOVE_32_TO_16 (Buffer, &LinkedList->Data.Address16.AddressLength);
    Buffer += 2;

    /* Resource Source Index and Resource Source are optional */

    if (LinkedList->Data.Address16.ResourceSource.StringLength)
    {
        *Buffer = (UINT8) LinkedList->Data.Address16.ResourceSource.Index;
        Buffer += 1;

        /* Copy the ResourceSource string */

        ACPI_STRCPY ((char *) Buffer,
                LinkedList->Data.Address16.ResourceSource.StringPtr);

        /*
         * Buffer needs to be set to the length of the string + one for the
         * terminating null
         */
        Buffer += (ACPI_SIZE)(ACPI_STRLEN (
                    LinkedList->Data.Address16.ResourceSource.StringPtr) + 1);
    }

    /* Return the number of bytes consumed in this operation */

    ActualBytes = ACPI_PTR_DIFF (Buffer, *OutputBuffer);
    *BytesConsumed = ActualBytes;

    /*
     * Set the length field to the number of bytes consumed
     * minus the header size (3 bytes)
     */
    ActualBytes -= 3;
    ACPI_MOVE_SIZE_TO_16 (LengthField, &ActualBytes);
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsAddress32Resource
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
AcpiRsAddress32Resource (
    UINT8                   *ByteStreamBuffer,
    ACPI_SIZE               *BytesConsumed,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *StructureSize)
{
    UINT16                  Temp16;
    UINT8                   Temp8;
    UINT8                   *TempPtr;
    UINT32                  Index;
    UINT8                   *Buffer = ByteStreamBuffer;
    ACPI_RESOURCE           *OutputStruct= (void *) *OutputBuffer;
    ACPI_SIZE               StructSize = ACPI_SIZEOF_RESOURCE (
                                            ACPI_RESOURCE_ADDRESS32);


    ACPI_FUNCTION_TRACE ("RsAddress32Resource");


    /* Get the Descriptor Length field */

    Buffer += 1;
    ACPI_MOVE_16_TO_16 (&Temp16, Buffer);

    /* Validate minimum descriptor length */

    if (Temp16 < 23)
    {
        return_ACPI_STATUS (AE_AML_BAD_RESOURCE_LENGTH);
    }

    *BytesConsumed = Temp16 + 3;
    OutputStruct->Id = ACPI_RSTYPE_ADDRESS32;

    /* Get the Resource Type (Byte3) */

    Buffer += 2;
    Temp8 = *Buffer;

    /* Values 0-2 and 0xC0-0xFF are valid */

    if ((Temp8 > 2) && (Temp8 < 0xC0))
    {
        return_ACPI_STATUS (AE_AML_INVALID_RESOURCE_TYPE);
    }

    OutputStruct->Data.Address32.ResourceType = Temp8;

    /* Get the General Flags (Byte4) */

    Buffer += 1;
    AcpiRsDecodeGeneralFlags (&OutputStruct->Data, *Buffer);

    /* Get the Type Specific Flags (Byte5) */

    Buffer += 1;
    AcpiRsDecodeSpecificFlags (&OutputStruct->Data, *Buffer);

    /* Get Granularity (Bytes 6-9) */

    Buffer += 1;
    ACPI_MOVE_32_TO_32 (&OutputStruct->Data.Address32.Granularity, Buffer);

    /* Get MinAddressRange (Bytes 10-13) */

    Buffer += 4;
    ACPI_MOVE_32_TO_32 (&OutputStruct->Data.Address32.MinAddressRange, Buffer);

    /* Get MaxAddressRange (Bytes 14-17) */

    Buffer += 4;
    ACPI_MOVE_32_TO_32 (&OutputStruct->Data.Address32.MaxAddressRange, Buffer);

    /* Get AddressTranslationOffset (Bytes 18-21) */

    Buffer += 4;
    ACPI_MOVE_32_TO_32 (&OutputStruct->Data.Address32.AddressTranslationOffset,
        Buffer);

    /* Get AddressLength (Bytes 22-25) */

    Buffer += 4;
    ACPI_MOVE_32_TO_32 (&OutputStruct->Data.Address32.AddressLength, Buffer);

    /* Resource Source Index (if present) */

    Buffer += 4;

    /*
     * This will leave us pointing to the Resource Source Index
     * If it is present, then save it off and calculate the
     * pointer to where the null terminated string goes:
     *
     * Note: Some resource descriptors will have an additional null, so
     * we add 1 to the length.
     */
    if (*BytesConsumed > (26 + 1))
    {
        /* Dereference the Index */

        OutputStruct->Data.Address32.ResourceSource.Index = (UINT32) *Buffer;

        /* Point to the String */

        Buffer += 1;

        /* Point the String pointer to the end of this structure */

        OutputStruct->Data.Address32.ResourceSource.StringPtr =
                (char *)((UINT8 *)OutputStruct + StructSize);

        TempPtr = (UINT8 *)
            OutputStruct->Data.Address32.ResourceSource.StringPtr;

        /* Copy the ResourceSource string into the buffer */

        Index = 0;
        while (*Buffer)
        {
            *TempPtr = *Buffer;

            TempPtr++;
            Buffer++;
            Index++;
        }

        /* Add the terminating null and set the string length */

        *TempPtr = 0;
        OutputStruct->Data.Address32.ResourceSource.StringLength = Index + 1;

        /*
         * In order for the StructSize to fall on a 32-bit boundary,
         * calculate the length of the string and expand the
         * StructSize to the next 32-bit boundary.
         */
        Temp8 = (UINT8) (Index + 1);
        StructSize += ACPI_ROUND_UP_TO_32BITS (Temp8);
    }
    else
    {
        OutputStruct->Data.Address32.ResourceSource.Index = 0;
        OutputStruct->Data.Address32.ResourceSource.StringLength = 0;
        OutputStruct->Data.Address32.ResourceSource.StringPtr = NULL;
    }

    /* Set the Length parameter */

    OutputStruct->Length = (UINT32) StructSize;

    /* Return the final size of the structure */

    *StructureSize = StructSize;
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsAddress32Stream
 *
 * PARAMETERS:  LinkedList              - Pointer to the resource linked list
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
AcpiRsAddress32Stream (
    ACPI_RESOURCE           *LinkedList,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *BytesConsumed)
{
    UINT8                   *Buffer;
    UINT16                  *LengthField;


    ACPI_FUNCTION_TRACE ("RsAddress32Stream");


    Buffer = *OutputBuffer;

    /* Set the Descriptor Type field */

    *Buffer = ACPI_RDESC_TYPE_DWORD_ADDRESS_SPACE;
    Buffer += 1;

    /* Save a pointer to the Length field - to be filled in later */

    LengthField = ACPI_CAST_PTR (UINT16, Buffer);
    Buffer += 2;

    /* Set the Resource Type (Memory, Io, BusNumber) */

    *Buffer = (UINT8) (LinkedList->Data.Address32.ResourceType & 0x03);
    Buffer += 1;

    /* Set the general flags */

    *Buffer = AcpiRsEncodeGeneralFlags (&LinkedList->Data);
    Buffer += 1;

    /* Set the type specific flags */

    *Buffer = AcpiRsEncodeSpecificFlags (&LinkedList->Data);
    Buffer += 1;

    /* Set the address space granularity */

    ACPI_MOVE_32_TO_32 (Buffer, &LinkedList->Data.Address32.Granularity);
    Buffer += 4;

    /* Set the address range minimum */

    ACPI_MOVE_32_TO_32 (Buffer, &LinkedList->Data.Address32.MinAddressRange);
    Buffer += 4;

    /* Set the address range maximum */

    ACPI_MOVE_32_TO_32 (Buffer, &LinkedList->Data.Address32.MaxAddressRange);
    Buffer += 4;

    /* Set the address translation offset */

    ACPI_MOVE_32_TO_32 (Buffer,
        &LinkedList->Data.Address32.AddressTranslationOffset);
    Buffer += 4;

    /* Set the address length */

    ACPI_MOVE_32_TO_32 (Buffer, &LinkedList->Data.Address32.AddressLength);
    Buffer += 4;

    /* Resource Source Index and Resource Source are optional */

    if (LinkedList->Data.Address32.ResourceSource.StringLength)
    {
        *Buffer = (UINT8) LinkedList->Data.Address32.ResourceSource.Index;
        Buffer += 1;

        /* Copy the ResourceSource string */

        ACPI_STRCPY ((char *) Buffer,
            LinkedList->Data.Address32.ResourceSource.StringPtr);

        /*
         * Buffer needs to be set to the length of the string + one for the
         *  terminating null
         */
        Buffer += (ACPI_SIZE)(ACPI_STRLEN (
                    LinkedList->Data.Address32.ResourceSource.StringPtr) + 1);
    }

    /* Return the number of bytes consumed in this operation */

    *BytesConsumed = ACPI_PTR_DIFF (Buffer, *OutputBuffer);

    /*
     * Set the length field to the number of bytes consumed
     * minus the header size (3 bytes)
     */
    *LengthField = (UINT16) (*BytesConsumed - 3);
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsAddress64Resource
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
AcpiRsAddress64Resource (
    UINT8                   *ByteStreamBuffer,
    ACPI_SIZE               *BytesConsumed,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *StructureSize)
{
    UINT16                  Temp16;
    UINT8                   Temp8;
    UINT8                   ResourceType;
    UINT8                   *TempPtr;
    UINT32                  Index;
    UINT8                   *Buffer = ByteStreamBuffer;
    ACPI_RESOURCE           *OutputStruct = (void *) *OutputBuffer;
    ACPI_SIZE               StructSize = ACPI_SIZEOF_RESOURCE (
                                            ACPI_RESOURCE_ADDRESS64);


    ACPI_FUNCTION_TRACE ("RsAddress64Resource");


    /* Get the Descriptor Type */

    ResourceType = *Buffer;

    /* Get the Descriptor Length field */

    Buffer += 1;
    ACPI_MOVE_16_TO_16 (&Temp16, Buffer);

    /* Validate minimum descriptor length */

    if (Temp16 < 43)
    {
        return_ACPI_STATUS (AE_AML_BAD_RESOURCE_LENGTH);
    }

    *BytesConsumed = Temp16 + 3;
    OutputStruct->Id = ACPI_RSTYPE_ADDRESS64;

    /* Get the Resource Type (Byte3) */

    Buffer += 2;
    Temp8 = *Buffer;

    /* Values 0-2 and 0xC0-0xFF are valid */

    if ((Temp8 > 2) && (Temp8 < 0xC0))
    {
        return_ACPI_STATUS (AE_AML_INVALID_RESOURCE_TYPE);
    }

    OutputStruct->Data.Address64.ResourceType = Temp8;

    /* Get the General Flags (Byte4) */

    Buffer += 1;
    AcpiRsDecodeGeneralFlags (&OutputStruct->Data, *Buffer);

    /* Get the Type Specific Flags (Byte5) */

    Buffer += 1;
    AcpiRsDecodeSpecificFlags (&OutputStruct->Data, *Buffer);

    if (ResourceType == ACPI_RDESC_TYPE_EXTENDED_ADDRESS_SPACE)
    {
        /* Move past RevisionId and Reserved byte */

        Buffer += 2;
    }

    /* Get Granularity (Bytes 6-13) or (Bytes 8-15) */

    Buffer += 1;
    ACPI_MOVE_64_TO_64 (&OutputStruct->Data.Address64.Granularity, Buffer);

    /* Get MinAddressRange (Bytes 14-21) or (Bytes 16-23) */

    Buffer += 8;
    ACPI_MOVE_64_TO_64 (&OutputStruct->Data.Address64.MinAddressRange, Buffer);

    /* Get MaxAddressRange (Bytes 22-29) or (Bytes 24-31) */

    Buffer += 8;
    ACPI_MOVE_64_TO_64 (&OutputStruct->Data.Address64.MaxAddressRange, Buffer);

    /* Get AddressTranslationOffset (Bytes 30-37) or (Bytes 32-39) */

    Buffer += 8;
    ACPI_MOVE_64_TO_64 (&OutputStruct->Data.Address64.AddressTranslationOffset,
        Buffer);

    /* Get AddressLength (Bytes 38-45) or (Bytes 40-47) */

    Buffer += 8;
    ACPI_MOVE_64_TO_64 (&OutputStruct->Data.Address64.AddressLength, Buffer);

    OutputStruct->Data.Address64.ResourceSource.Index = 0;
    OutputStruct->Data.Address64.ResourceSource.StringLength = 0;
    OutputStruct->Data.Address64.ResourceSource.StringPtr = NULL;

    if (ResourceType == ACPI_RDESC_TYPE_EXTENDED_ADDRESS_SPACE)
    {
        /* Get TypeSpecificAttribute (Bytes 48-55) */

        Buffer += 8;
        ACPI_MOVE_64_TO_64 (
            &OutputStruct->Data.Address64.TypeSpecificAttributes,
            Buffer);
    }
    else
    {
        OutputStruct->Data.Address64.TypeSpecificAttributes = 0;

        /* Resource Source Index (if present) */

        Buffer += 8;

        /*
         * This will leave us pointing to the Resource Source Index
         * If it is present, then save it off and calculate the
         * pointer to where the null terminated string goes:
         * Each Interrupt takes 32-bits + the 5 bytes of the
         * stream that are default.
         *
         * Note: Some resource descriptors will have an additional null, so
         * we add 1 to the length.
         */
        if (*BytesConsumed > (46 + 1))
        {
            /* Dereference the Index */

            OutputStruct->Data.Address64.ResourceSource.Index = (UINT32) *Buffer;

            /* Point to the String */

            Buffer += 1;

            /* Point the String pointer to the end of this structure */

            OutputStruct->Data.Address64.ResourceSource.StringPtr =
                    (char *)((UINT8 *)OutputStruct + StructSize);

            TempPtr = (UINT8 *)
                OutputStruct->Data.Address64.ResourceSource.StringPtr;

            /* Copy the ResourceSource string into the buffer */

            Index = 0;
            while (*Buffer)
            {
                *TempPtr = *Buffer;

                TempPtr++;
                Buffer++;
                Index++;
            }

            /*
             * Add the terminating null and set the string length
             */
            *TempPtr = 0;
            OutputStruct->Data.Address64.ResourceSource.StringLength =
                Index + 1;

            /*
             * In order for the StructSize to fall on a 32-bit boundary,
             * calculate the length of the string and expand the
             * StructSize to the next 32-bit boundary.
             */
            Temp8 = (UINT8) (Index + 1);
            StructSize += ACPI_ROUND_UP_TO_32BITS (Temp8);
        }
    }

    /* Set the Length parameter */

    OutputStruct->Length = (UINT32) StructSize;

    /* Return the final size of the structure */

    *StructureSize = StructSize;
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsAddress64Stream
 *
 * PARAMETERS:  LinkedList              - Pointer to the resource linked list
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
AcpiRsAddress64Stream (
    ACPI_RESOURCE           *LinkedList,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *BytesConsumed)
{
    UINT8                   *Buffer;
    UINT16                  *LengthField;


    ACPI_FUNCTION_TRACE ("RsAddress64Stream");


    Buffer = *OutputBuffer;

    /* Set the Descriptor Type field */

    *Buffer = ACPI_RDESC_TYPE_QWORD_ADDRESS_SPACE;
    Buffer += 1;

    /* Save a pointer to the Length field - to be filled in later */

    LengthField = ACPI_CAST_PTR (UINT16, Buffer);
    Buffer += 2;

    /* Set the Resource Type (Memory, Io, BusNumber) */

    *Buffer = (UINT8) (LinkedList->Data.Address64.ResourceType & 0x03);
    Buffer += 1;

    /* Set the general flags */

    *Buffer = AcpiRsEncodeGeneralFlags (&LinkedList->Data);
    Buffer += 1;

    /* Set the type specific flags */

    *Buffer = AcpiRsEncodeSpecificFlags (&LinkedList->Data);
    Buffer += 1;

    /* Set the address space granularity */

    ACPI_MOVE_64_TO_64 (Buffer, &LinkedList->Data.Address64.Granularity);
    Buffer += 8;

    /* Set the address range minimum */

    ACPI_MOVE_64_TO_64 (Buffer, &LinkedList->Data.Address64.MinAddressRange);
    Buffer += 8;

    /* Set the address range maximum */

    ACPI_MOVE_64_TO_64 (Buffer, &LinkedList->Data.Address64.MaxAddressRange);
    Buffer += 8;

    /* Set the address translation offset */

    ACPI_MOVE_64_TO_64 (Buffer,
        &LinkedList->Data.Address64.AddressTranslationOffset);
    Buffer += 8;

    /* Set the address length */

    ACPI_MOVE_64_TO_64 (Buffer, &LinkedList->Data.Address64.AddressLength);
    Buffer += 8;

    /* Resource Source Index and Resource Source are optional */

    if (LinkedList->Data.Address64.ResourceSource.StringLength)
    {
        *Buffer = (UINT8) LinkedList->Data.Address64.ResourceSource.Index;
        Buffer += 1;

        /* Copy the ResourceSource string */

        ACPI_STRCPY ((char *) Buffer,
            LinkedList->Data.Address64.ResourceSource.StringPtr);

        /*
         * Buffer needs to be set to the length of the string + one for the
         * terminating null
         */
        Buffer += (ACPI_SIZE)(ACPI_STRLEN (
                    LinkedList->Data.Address64.ResourceSource.StringPtr) + 1);
    }

    /* Return the number of bytes consumed in this operation */

    *BytesConsumed = ACPI_PTR_DIFF (Buffer, *OutputBuffer);

    /*
     * Set the length field to the number of bytes consumed
     * minus the header size (3 bytes)
     */
    *LengthField = (UINT16) (*BytesConsumed - 3);
    return_ACPI_STATUS (AE_OK);
}

