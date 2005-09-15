/*******************************************************************************
 *
 * Module Name: rscalc - Calculate stream and list lengths
 *              $Revision: 1.60 $
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

#define __RSCALC_C__

#include "acpi.h"
#include "acresrc.h"
#include "amlcode.h"
#include "amlresrc.h"
#include "acnamesp.h"

#define _COMPONENT          ACPI_RESOURCES
        ACPI_MODULE_NAME    ("rscalc")


/* 
 * Base sizes for external resource descriptors, indexed by internal type.
 * Includes size of the descriptor header (1 byte for small descriptors,
 * 3 bytes for large descriptors)
 */
static UINT8 AcpiGbl_StreamSizes [] = 
{
     4,         /* ACPI_RSTYPE_IRQ (Byte 3 is optional, but always created) */
     3,         /* ACPI_RSTYPE_DMA */
     2,         /* ACPI_RSTYPE_START_DPF (Byte 1 is optional, but always created) */
     1,         /* ACPI_RSTYPE_END_DPF */
     8,         /* ACPI_RSTYPE_IO */
     4,         /* ACPI_RSTYPE_FIXED_IO */
     1,         /* ACPI_RSTYPE_VENDOR */
     2,         /* ACPI_RSTYPE_END_TAG */
    12,         /* ACPI_RSTYPE_MEM24 */
    20,         /* ACPI_RSTYPE_MEM32 */
    12,         /* ACPI_RSTYPE_FIXED_MEM32 */
    16,         /* ACPI_RSTYPE_ADDRESS16 */
    26,         /* ACPI_RSTYPE_ADDRESS32 */
    46,         /* ACPI_RSTYPE_ADDRESS64 */
     9,         /* ACPI_RSTYPE_EXT_IRQ */
    15          /* ACPI_RSTYPE_GENERIC_REG */
};


/*
 * Base sizes of resource descriptors, both the actual AML stream length and
 * size of the internal struct representation.
 */
typedef struct acpi_resource_sizes
{
    UINT8                   MinimumStreamSize;
    UINT8                   MinimumStructSize;

} ACPI_RESOURCE_SIZES;

static ACPI_RESOURCE_SIZES      AcpiGbl_SmResourceSizes [] = 
{
     0,  0,                                                 /* 0x00, Reserved */
     0,  0,                                                 /* 0x01, Reserved */
     0,  0,                                                 /* 0x02, Reserved */
     0,  0,                                                 /* 0x03, Reserved */
     3,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_IRQ),          /* ACPI_RDESC_TYPE_IRQ_FORMAT */
     3,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_DMA),          /* ACPI_RDESC_TYPE_DMA_FORMAT */
     1,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_START_DPF),    /* ACPI_RDESC_TYPE_START_DEPENDENT */
     1,  ACPI_RESOURCE_LENGTH,                              /* ACPI_RDESC_TYPE_END_DEPENDENT */
     8,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_IO),           /* ACPI_RDESC_TYPE_IO_PORT */
     4,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_FIXED_IO),     /* ACPI_RDESC_TYPE_FIXED_IO_PORT */
     0,  0,                                                 /* 0x0A, Reserved */
     0,  0,                                                 /* 0x0B, Reserved */
     0,  0,                                                 /* 0x0C, Reserved */
     0,  0,                                                 /* 0x0D, Reserved */
     1,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_VENDOR),       /* ACPI_RDESC_TYPE_SMALL_VENDOR */
     2,  ACPI_RESOURCE_LENGTH,                              /* ACPI_RDESC_TYPE_END_TAG */
};

static ACPI_RESOURCE_SIZES    AcpiGbl_LgResourceSizes [] = 
{   
     0,  0,                                                 /* 0x00, Reserved */
    12,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_MEM24),        /* ACPI_RDESC_TYPE_MEMORY_24 */
    15,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_GENERIC_REG),  /* ACPI_RDESC_TYPE_GENERIC_REGISTER */
     0,  0,                                                 /* 0x03, Reserved */
     3,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_VENDOR),       /* ACPI_RDESC_TYPE_LARGE_VENDOR */
    20,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_MEM32),        /* ACPI_RDESC_TYPE_MEMORY_32 */
    12,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_FIXED_MEM32),  /* ACPI_RDESC_TYPE_FIXED_MEMORY_32 */
    26,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_ADDRESS32),    /* ACPI_RDESC_TYPE_DWORD_ADDRESS_SPACE */
    16,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_ADDRESS16),    /* ACPI_RDESC_TYPE_WORD_ADDRESS_SPACE */
     9,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_EXT_IRQ),      /* ACPI_RDESC_TYPE_EXTENDED_XRUPT */
    46,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_ADDRESS64),    /* ACPI_RDESC_TYPE_QWORD_ADDRESS_SPACE */
    56,  ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_ADDRESS64),    /* ACPI_RDESC_TYPE_EXTENDED_ADDRESS_SPACE */
};


/* Local prototypes */

static UINT8
AcpiRsCountSetBits (
    UINT16                  BitField);

static ACPI_RESOURCE_SIZES *
AcpiRsGetResourceSizes (
    UINT8                   ResourceType);

static UINT16
AcpiRsGetResourceLength (
    UINT8                   *Resource);

static ACPI_SIZE
AcpiRsStructOptionLength (
    ACPI_RESOURCE_SOURCE    *ResourceSource);

static UINT32
AcpiRsStreamOptionLength (
    UINT32                  ResourceLength,
    UINT32                  MinimumTotalLength);


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsCountSetBits
 *
 * PARAMETERS:  BitField        - Field in which to count bits
 *
 * RETURN:      Number of bits set within the field
 *
 * DESCRIPTION: Count the number of bits set in a resource field. Used for 
 *              (Short descriptor) interrupt and DMA lists.
 *
 ******************************************************************************/

static UINT8
AcpiRsCountSetBits (
    UINT16                  BitField)
{
    UINT8                   BitsSet;


    ACPI_FUNCTION_ENTRY ();


    for (BitsSet = 0; BitField; BitsSet++)
    {
        /* Zero the least significant bit that is set */

        BitField &= (BitField - 1);
    }

    return (BitsSet);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsGetResourceSizes
 *
 * PARAMETERS:  ResourceType        - Byte 0 of a resource descriptor
 *
 * RETURN:      Pointer to the resource conversion handler
 *
 * DESCRIPTION: Extract the Resource Type/Name from the first byte of
 *              a resource descriptor.
 *
 ******************************************************************************/

static ACPI_RESOURCE_SIZES *
AcpiRsGetResourceSizes (
    UINT8                   ResourceType)
{
    ACPI_RESOURCE_SIZES     *SizeInfo;


    ACPI_FUNCTION_ENTRY ();


    /* Determine if this is a small or large resource */

    if (ResourceType & ACPI_RDESC_TYPE_LARGE)
    {
        /* Large Resource Type -- bits 6:0 contain the name */

        if (ResourceType > ACPI_RDESC_LARGE_MAX)
        {
            return (NULL);
        }

        SizeInfo = &AcpiGbl_LgResourceSizes [
                    (ResourceType & ACPI_RDESC_LARGE_MASK)];
    }
    else
    {
        /* Small Resource Type -- bits 6:3 contain the name */

        SizeInfo = &AcpiGbl_SmResourceSizes [
                    ((ResourceType & ACPI_RDESC_SMALL_MASK) >> 3)];
    }

    /* Zero entry indicates an invalid resource type */

    if (!SizeInfo->MinimumStreamSize)
    {
        return (NULL);
    }

    return (SizeInfo);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsGetResourceLength
 *
 * PARAMETERS:  Resource        - Pointer to the resource descriptor
 *
 * RETURN:      Byte length of the (AML byte stream) descriptor. By definition,
 *              this does not include the size of the descriptor header and the
 *              length field itself.
 *
 * DESCRIPTION: Extract the length of a resource descriptor.
 *
 ******************************************************************************/

static UINT16
AcpiRsGetResourceLength (
    UINT8                   *Resource)
{
    UINT16                  ResourceLength;


    ACPI_FUNCTION_ENTRY ();


    /* Determine if this is a small or large resource */

    if (*Resource & ACPI_RDESC_TYPE_LARGE)
    {
        /* Large Resource type -- length is in bytes 1-2 */

        ACPI_MOVE_16_TO_16 (&ResourceLength, (Resource + 1));

    }
    else
    {
        /* Small Resource Type -- bits 2:0 of byte 0 contain the length */

        ResourceLength = (UINT16) (*Resource & ACPI_RDESC_SMALL_LENGTH_MASK);
    }

    return (ResourceLength);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsStructOptionLength
 *
 * PARAMETERS:  ResourceSource  - Pointer to optional descriptor field
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Common code to handle optional ResourceSourceIndex and 
 *              ResourceSource fields in some Large descriptors. Used during
 *              list-to-stream conversion
 *
 ******************************************************************************/

static ACPI_SIZE
AcpiRsStructOptionLength (
    ACPI_RESOURCE_SOURCE    *ResourceSource)
{
    ACPI_FUNCTION_ENTRY ();


    /*
     * If the ResourceSource string is valid, return the size of the string
     * (StringLength includes the NULL terminator) plus the size of the 
     * ResourceSourceIndex (1).
     */
    if (ResourceSource->StringPtr)
    {
        return ((ACPI_SIZE) ResourceSource->StringLength + 1);
    }

    return (0);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsStreamOptionLength
 *
 * PARAMETERS:  ResourceLength      - Length from the resource header
 *              MinimumTotalLength  - Minimum length of this resource, before
 *                                    any optional fields. Includes header size
 *                                        
 * RETURN:      Length of optional string (0 if no string present)
 *
 * DESCRIPTION: Common code to handle optional ResourceSourceIndex and 
 *              ResourceSource fields in some Large descriptors. Used during
 *              stream-to-list conversion
 *
 ******************************************************************************/

static UINT32
AcpiRsStreamOptionLength (
    UINT32                  ResourceLength,
    UINT32                  MinimumTotalLength)
{
    UINT32                  StringLength = 0;
    UINT32                  MinimumResourceLength;


    ACPI_FUNCTION_ENTRY ();


    /*
     * The ResourceSourceIndex and ResourceSource are optional elements of some
     * Large-type resource descriptors.
     */

    /* Compute minimum size of the data part of the resource descriptor */

    MinimumResourceLength = MinimumTotalLength - sizeof (ASL_LARGE_HEADER);

    /*
     * If the length of the actual resource descriptor is greater than the ACPI
     * spec-defined minimum length, it means that a ResourceSourceIndex exists 
     * and is followed by a (required) null terminated string. The string length
     * (including the null terminator) is the resource length minus the minimum
     * length, minus one byte for the ResourceSourceIndex itself.
     */
    if (ResourceLength > MinimumResourceLength)
    {
        /* Compute the length of the optional string */

        StringLength = ResourceLength - MinimumResourceLength - 1;
    }

    /* Round up length to 32 bits for internal structure alignment */

    return (ACPI_ROUND_UP_TO_32BITS (StringLength));
}



/*******************************************************************************
 *
 * FUNCTION:    AcpiRsGetByteStreamLength
 *
 * PARAMETERS:  LinkedList          - Pointer to the resource linked list
 *              SizeNeeded          - Where the required size is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Takes a linked list of internal resource descriptors and
 *              calculates the size buffer needed to hold the corresponding
 *              external resource byte stream.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsGetByteStreamLength (
    ACPI_RESOURCE           *LinkedList,
    ACPI_SIZE               *SizeNeeded)
{
    ACPI_SIZE               ByteStreamSizeNeeded = 0;
    ACPI_SIZE               SegmentSize;


    ACPI_FUNCTION_TRACE ("RsGetByteStreamLength");


    /* Traverse entire list of internal resource descriptors */

    while (LinkedList)
    {
        /* Validate the descriptor type */

        if (LinkedList->Id > ACPI_RSTYPE_MAX)
        {
            return_ACPI_STATUS (AE_AML_INVALID_RESOURCE_TYPE);
        }

        /* Get the base size of the (external stream) resource descriptor */

        SegmentSize = AcpiGbl_StreamSizes [LinkedList->Id];

        /*
         * Augment the base size for descriptors with optional and/or
         * variable-length fields
         */
        switch (LinkedList->Id)
        {
        case ACPI_RSTYPE_VENDOR:
            /*
             * Vendor Defined Resource:
             * For a Vendor Specific resource, if the Length is between 1 and 7
             * it will be created as a Small Resource data type, otherwise it
             * is a Large Resource data type.
             */
            if (LinkedList->Data.VendorSpecific.Length > 7)
            {
                /* Base size of a Large resource descriptor */

                SegmentSize = 3;
            }

            /* Add the size of the vendor-specific data */

            SegmentSize += LinkedList->Data.VendorSpecific.Length;
            break;


        case ACPI_RSTYPE_END_TAG:
            /*
             * End Tag:
             * We are done -- return the accumulated total size.
             */
            *SizeNeeded = ByteStreamSizeNeeded + SegmentSize;

            /* Normal exit */

            return_ACPI_STATUS (AE_OK);


        case ACPI_RSTYPE_ADDRESS16:
            /*
             * 16-Bit Address Resource:
             * Add the size of the optional ResourceSource info
             */
            SegmentSize += AcpiRsStructOptionLength (
                            &LinkedList->Data.Address16.ResourceSource);
            break;


        case ACPI_RSTYPE_ADDRESS32:
            /*
             * 32-Bit Address Resource:
             * Add the size of the optional ResourceSource info
             */
            SegmentSize += AcpiRsStructOptionLength (
                            &LinkedList->Data.Address32.ResourceSource);
            break;


        case ACPI_RSTYPE_ADDRESS64:
            /*
             * 64-Bit Address Resource:
             * Add the size of the optional ResourceSource info
             */
            SegmentSize += AcpiRsStructOptionLength (
                            &LinkedList->Data.Address64.ResourceSource);
            break;


        case ACPI_RSTYPE_EXT_IRQ:
            /*
             * Extended IRQ Resource:
             * Add the size of each additional optional interrupt beyond the 
             * required 1 (4 bytes for each UINT32 interrupt number)
             */
            SegmentSize += (((ACPI_SIZE)
                LinkedList->Data.ExtendedIrq.NumberOfInterrupts - 1) * 4);

            /* Add the size of the optional ResourceSource info */

            SegmentSize += AcpiRsStructOptionLength (
                            &LinkedList->Data.ExtendedIrq.ResourceSource);
            break;


        default:
            break;
        }

        /* Update the total */

        ByteStreamSizeNeeded += SegmentSize;

        /* Point to the next object */

        LinkedList = ACPI_PTR_ADD (ACPI_RESOURCE,
                        LinkedList, LinkedList->Length);
    }

    /* Did not find an END_TAG descriptor */

    return_ACPI_STATUS (AE_AML_INVALID_RESOURCE_TYPE);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsGetListLength
 *
 * PARAMETERS:  ByteStreamBuffer        - Pointer to the resource byte stream
 *              ByteStreamBufferLength  - Size of ByteStreamBuffer
 *              SizeNeeded              - Where the size needed is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Takes an external resource byte stream and calculates the size
 *              buffer needed to hold the corresponding internal resource
 *              descriptor linked list.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsGetListLength (
    UINT8                   *ByteStreamBuffer,
    UINT32                  ByteStreamBufferLength,
    ACPI_SIZE               *SizeNeeded)
{
    UINT8                   *Buffer;
    ACPI_RESOURCE_SIZES     *ResourceInfo;
    UINT32                  BufferSize = 0;
    UINT32                  BytesParsed = 0;
    UINT8                   ResourceType;
    UINT16                  Temp16;
    UINT16                  ResourceLength;
    UINT16                  HeaderLength;
    UINT32                  ExtraStructBytes;


    ACPI_FUNCTION_TRACE ("RsGetListLength");


    while (BytesParsed < ByteStreamBufferLength)
    {
        /* The next byte in the stream is the resource descriptor type */

        ResourceType = AcpiRsGetResourceType (*ByteStreamBuffer);

        /* Get the base stream size and structure sizes for the descriptor */

        ResourceInfo = AcpiRsGetResourceSizes (ResourceType);
        if (!ResourceInfo)
        {
            return_ACPI_STATUS (AE_AML_INVALID_RESOURCE_TYPE);
        }

        /* Get the Length field from the input resource descriptor */

        ResourceLength = AcpiRsGetResourceLength (ByteStreamBuffer);

        /* Augment the size for descriptors with optional fields */

        ExtraStructBytes = 0;

        if (!(ResourceType & ACPI_RDESC_TYPE_LARGE))
        {
            /*
             * Small resource descriptors
             */
            HeaderLength = 1;
            Buffer = ByteStreamBuffer + HeaderLength;

            switch (ResourceType)
            {
            case ACPI_RDESC_TYPE_IRQ_FORMAT:
                /*
                 * IRQ Resource:
                 * Get the number of bits set in the IRQ word
                 */
                ACPI_MOVE_16_TO_16 (&Temp16, Buffer);

                ExtraStructBytes = (AcpiRsCountSetBits (Temp16) * 
                                        sizeof (UINT32));
                break;


            case ACPI_RDESC_TYPE_DMA_FORMAT:
                /*
                 * DMA Resource:
                 * Get the number of bits set in the DMA channels byte
                 */
                ExtraStructBytes = (AcpiRsCountSetBits ((UINT16) *Buffer) * 
                                        sizeof (UINT32));
                break;


            case ACPI_RDESC_TYPE_SMALL_VENDOR:
                /*
                 * Vendor Specific Resource:
                 * Ensure a 32-bit boundary for the structure
                 */
                ExtraStructBytes = ACPI_ROUND_UP_TO_32BITS (ResourceLength);
                break;


            case ACPI_RDESC_TYPE_END_TAG:
                /*
                 * End Tag:
                 * Terminate the loop now
                 */
                ByteStreamBufferLength = BytesParsed;
                break;


            default:
                break;
            }
        }
        else
        {
            /*
             * Large resource descriptors
             */
            HeaderLength = sizeof (ASL_LARGE_HEADER);
            Buffer = ByteStreamBuffer + HeaderLength;

            switch (ResourceType)
            {
            case ACPI_RDESC_TYPE_LARGE_VENDOR:
                /*
                 * Vendor Defined Resource:
                 * Add vendor data and ensure a 32-bit boundary for the structure
                 */
                ExtraStructBytes = ACPI_ROUND_UP_TO_32BITS (ResourceLength);
                break;


            case ACPI_RDESC_TYPE_DWORD_ADDRESS_SPACE:
            case ACPI_RDESC_TYPE_WORD_ADDRESS_SPACE:
               /*
                 * 32-Bit or 16-bit Address Resource:
                 * Add the size of any optional data (ResourceSource)
                 */
                ExtraStructBytes = AcpiRsStreamOptionLength (ResourceLength, 
                                        ResourceInfo->MinimumStreamSize);
                break;


            case ACPI_RDESC_TYPE_EXTENDED_XRUPT:
                /*
                 * Extended IRQ:
                 * Point past the InterruptVectorFlags to get the
                 * InterruptTableLength.
                 */
                Buffer++;

                /*
                 * Add 4 bytes for each additional interrupt. Note: at least one 
                 * interrupt is required and is included in the minimum
                 * descriptor size
                 */
                ExtraStructBytes = ((*Buffer - 1) * sizeof (UINT32));

                /* Add the size of any optional data (ResourceSource) */

                ExtraStructBytes += AcpiRsStreamOptionLength (
                                        ResourceLength - ExtraStructBytes, 
                                        ResourceInfo->MinimumStreamSize);
                break;


            case ACPI_RDESC_TYPE_QWORD_ADDRESS_SPACE:
                /*
                 * 64-Bit Address Resource:
                 * Add the size of any optional data (ResourceSource)
                 * Ensure a 64-bit boundary for the structure
                 */
                ExtraStructBytes = ACPI_ROUND_UP_TO_64BITS (
                    AcpiRsStreamOptionLength (ResourceLength, 
                                        ResourceInfo->MinimumStreamSize));
                break;


            default:
                break;
            }
        }

        /* Update the required buffer size for the internal descriptor structs */

        Temp16 = (UINT16) (ResourceInfo->MinimumStructSize +  ExtraStructBytes);
        BufferSize += (UINT32) ACPI_ALIGN_RESOURCE_SIZE (Temp16);

        /*
         * Update byte count and point to the next resource within the stream
         * using the size of the header plus the length contained in the header
         */
        Temp16 = (UINT16) (HeaderLength + ResourceLength);
        BytesParsed += Temp16;
        ByteStreamBuffer += Temp16;
    }

    /* This is the data the caller needs */

    *SizeNeeded = BufferSize;
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsGetPciRoutingTableLength
 *
 * PARAMETERS:  PackageObject           - Pointer to the package object
 *              BufferSizeNeeded        - UINT32 pointer of the size buffer
 *                                        needed to properly return the
 *                                        parsed data
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Given a package representing a PCI routing table, this
 *              calculates the size of the corresponding linked list of
 *              descriptions.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsGetPciRoutingTableLength (
    ACPI_OPERAND_OBJECT     *PackageObject,
    ACPI_SIZE               *BufferSizeNeeded)
{
    UINT32                  NumberOfElements;
    ACPI_SIZE               TempSizeNeeded = 0;
    ACPI_OPERAND_OBJECT     **TopObjectList;
    UINT32                  Index;
    ACPI_OPERAND_OBJECT     *PackageElement;
    ACPI_OPERAND_OBJECT     **SubObjectList;
    BOOLEAN                 NameFound;
    UINT32                  TableIndex;


    ACPI_FUNCTION_TRACE ("RsGetPciRoutingTableLength");


    NumberOfElements = PackageObject->Package.Count;

    /*
     * Calculate the size of the return buffer.
     * The base size is the number of elements * the sizes of the
     * structures.  Additional space for the strings is added below.
     * The minus one is to subtract the size of the UINT8 Source[1]
     * member because it is added below.
     *
     * But each PRT_ENTRY structure has a pointer to a string and
     * the size of that string must be found.
     */
    TopObjectList = PackageObject->Package.Elements;

    for (Index = 0; Index < NumberOfElements; Index++)
    {
        /* Dereference the sub-package */

        PackageElement = *TopObjectList;

        /*
         * The SubObjectList will now point to an array of the
         * four IRQ elements: Address, Pin, Source and SourceIndex
         */
        SubObjectList = PackageElement->Package.Elements;

        /* Scan the IrqTableElements for the Source Name String */

        NameFound = FALSE;

        for (TableIndex = 0; TableIndex < 4 && !NameFound; TableIndex++)
        {
            if ((ACPI_TYPE_STRING ==
                    ACPI_GET_OBJECT_TYPE (*SubObjectList)) ||

                ((ACPI_TYPE_LOCAL_REFERENCE ==
                    ACPI_GET_OBJECT_TYPE (*SubObjectList)) &&

                    ((*SubObjectList)->Reference.Opcode ==
                        AML_INT_NAMEPATH_OP)))
            {
                NameFound = TRUE;
            }
            else
            {
                /* Look at the next element */

                SubObjectList++;
            }
        }

        TempSizeNeeded += (sizeof (ACPI_PCI_ROUTING_TABLE) - 4);

        /* Was a String type found? */

        if (NameFound)
        {
            if (ACPI_GET_OBJECT_TYPE (*SubObjectList) == ACPI_TYPE_STRING)
            {
                /*
                 * The length String.Length field does not include the
                 * terminating NULL, add 1
                 */
                TempSizeNeeded += ((ACPI_SIZE)
                    (*SubObjectList)->String.Length + 1);
            }
            else
            {
                TempSizeNeeded += AcpiNsGetPathnameLength (
                                    (*SubObjectList)->Reference.Node);
            }
        }
        else
        {
            /*
             * If no name was found, then this is a NULL, which is
             * translated as a UINT32 zero.
             */
            TempSizeNeeded += sizeof (UINT32);
        }

        /* Round up the size since each element must be aligned */

        TempSizeNeeded = ACPI_ROUND_UP_TO_64BITS (TempSizeNeeded);

        /* Point to the next ACPI_OPERAND_OBJECT */

        TopObjectList++;
    }

    /*
     * Adding an extra element to the end of the list, essentially a
     * NULL terminator
     */
    *BufferSizeNeeded = TempSizeNeeded + sizeof (ACPI_PCI_ROUTING_TABLE);
    return_ACPI_STATUS (AE_OK);
}
