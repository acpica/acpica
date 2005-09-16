/*******************************************************************************
 *
 * Module Name: rslist - Linked list utilities
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

#define __RSLIST_C__

#include "acpi.h"
#include "acresrc.h"

#define _COMPONENT          ACPI_RESOURCES
        ACPI_MODULE_NAME    ("rslist")


/* Dispatch table for convert-to-stream functions */

typedef
ACPI_STATUS (*ACPI_STREAM_HANDLER) (
    ACPI_RESOURCE           *Resource,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *BytesConsumed);

static ACPI_STREAM_HANDLER      AcpiGbl_StreamDispatch [] =
{
    AcpiRsIrqStream,                /* ACPI_RSTYPE_IRQ */
    AcpiRsDmaStream,                /* ACPI_RSTYPE_DMA */
    AcpiRsStartDependFnsStream,     /* ACPI_RSTYPE_START_DPF */
    AcpiRsEndDependFnsStream,       /* ACPI_RSTYPE_END_DPF */
    AcpiRsIoStream,                 /* ACPI_RSTYPE_IO */
    AcpiRsFixedIoStream,            /* ACPI_RSTYPE_FIXED_IO */
    AcpiRsVendorStream,             /* ACPI_RSTYPE_VENDOR */
    AcpiRsEndTagStream,             /* ACPI_RSTYPE_END_TAG */
    AcpiRsMemory24Stream,           /* ACPI_RSTYPE_MEM24 */
    AcpiRsMemory32RangeStream,      /* ACPI_RSTYPE_MEM32 */
    AcpiRsFixedMemory32Stream,      /* ACPI_RSTYPE_FIXED_MEM32 */
    AcpiRsAddress16Stream,          /* ACPI_RSTYPE_ADDRESS16 */
    AcpiRsAddress32Stream,          /* ACPI_RSTYPE_ADDRESS32 */
    AcpiRsAddress64Stream,          /* ACPI_RSTYPE_ADDRESS64 */
    AcpiRsExtendedIrqStream,        /* ACPI_RSTYPE_EXT_IRQ */
    AcpiRsGenericRegisterStream     /* ACPI_RSTYPE_GENERIC_REG */
};


/* Dispatch tables for convert-to-resource functions */

typedef
ACPI_STATUS (*ACPI_RESOURCE_HANDLER) (
    UINT8                   *ByteStreamBuffer,
    ACPI_SIZE               *BytesConsumed,
    UINT8                   **OutputBuffer,
    ACPI_SIZE               *StructureSize);

static ACPI_RESOURCE_HANDLER    AcpiGbl_SmResourceDispatch [] =
{
    NULL,                           /* 0x00, Reserved */
    NULL,                           /* 0x01, Reserved */
    NULL,                           /* 0x02, Reserved */
    NULL,                           /* 0x03, Reserved */
    AcpiRsIrqResource,              /* ACPI_RDESC_TYPE_IRQ_FORMAT */
    AcpiRsDmaResource,              /* ACPI_RDESC_TYPE_DMA_FORMAT */
    AcpiRsStartDependFnsResource,   /* ACPI_RDESC_TYPE_START_DEPENDENT */
    AcpiRsEndDependFnsResource,     /* ACPI_RDESC_TYPE_END_DEPENDENT */
    AcpiRsIoResource,               /* ACPI_RDESC_TYPE_IO_PORT */
    AcpiRsFixedIoResource,          /* ACPI_RDESC_TYPE_FIXED_IO_PORT */
    NULL,                           /* 0x0A, Reserved */
    NULL,                           /* 0x0B, Reserved */
    NULL,                           /* 0x0C, Reserved */
    NULL,                           /* 0x0D, Reserved */
    AcpiRsVendorResource,           /* ACPI_RDESC_TYPE_SMALL_VENDOR */
    AcpiRsEndTagResource            /* ACPI_RDESC_TYPE_END_TAG */
};

static ACPI_RESOURCE_HANDLER    AcpiGbl_LgResourceDispatch [] =
{
    NULL,                           /* 0x00, Reserved */
    AcpiRsMemory24Resource,         /* ACPI_RDESC_TYPE_MEMORY_24 */
    AcpiRsGenericRegisterResource,  /* ACPI_RDESC_TYPE_GENERIC_REGISTER */
    NULL,                           /* 0x03, Reserved */
    AcpiRsVendorResource,           /* ACPI_RDESC_TYPE_LARGE_VENDOR */
    AcpiRsMemory32RangeResource,    /* ACPI_RDESC_TYPE_MEMORY_32 */
    AcpiRsFixedMemory32Resource,    /* ACPI_RDESC_TYPE_FIXED_MEMORY_32 */
    AcpiRsAddress32Resource,        /* ACPI_RDESC_TYPE_DWORD_ADDRESS_SPACE */
    AcpiRsAddress16Resource,        /* ACPI_RDESC_TYPE_WORD_ADDRESS_SPACE */
    AcpiRsExtendedIrqResource,      /* ACPI_RDESC_TYPE_EXTENDED_XRUPT */
    AcpiRsAddress64Resource,        /* ACPI_RDESC_TYPE_QWORD_ADDRESS_SPACE */
    AcpiRsAddress64Resource         /* ACPI_RDESC_TYPE_EXTENDED_ADDRESS_SPACE */
};


/* Local prototypes */

static ACPI_RESOURCE_HANDLER
AcpiRsGetResourceHandler (
    UINT8                   ResourceType);


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsGetResourceType
 *
 * PARAMETERS:  ResourceType        - Byte 0 of a resource descriptor
 *
 * RETURN:      The Resource Type with no extraneous bits (except the large/
 *              small bit -- left alone)
 *
 * DESCRIPTION: Extract the Resource Type/Name from the first byte of
 *              a resource descriptor.
 *
 ******************************************************************************/

UINT8
AcpiRsGetResourceType (
    UINT8                   ResourceType)
{
    ACPI_FUNCTION_ENTRY ();


    /* Determine if this is a small or large resource */

    if (ResourceType & ACPI_RDESC_TYPE_LARGE)
    {
        /* Large Resource Type -- bits 6:0 contain the name */

        return (ResourceType);
    }
    else
    {
        /* Small Resource Type -- bits 6:3 contain the name */

        return ((UINT8) (ResourceType & ACPI_RDESC_SMALL_MASK));
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsGetResourceHandler
 *
 * PARAMETERS:  ResourceType        - Byte 0 of a resource descriptor
 *
 * RETURN:      Pointer to the resource conversion handler
 *
 * DESCRIPTION: Extract the Resource Type/Name from the first byte of
 *              a resource descriptor.
 *
 ******************************************************************************/

static ACPI_RESOURCE_HANDLER
AcpiRsGetResourceHandler (
    UINT8                   ResourceType)
{
    ACPI_FUNCTION_ENTRY ();


    /* Determine if this is a small or large resource */

    if (ResourceType & ACPI_RDESC_TYPE_LARGE)
    {
        /* Large Resource Type -- bits 6:0 contain the name */

        if (ResourceType > ACPI_RDESC_LARGE_MAX)
        {
            return (NULL);
        }

        return (AcpiGbl_LgResourceDispatch [
                    (ResourceType & ACPI_RDESC_LARGE_MASK)]);
    }
    else
    {
        /* Small Resource Type -- bits 6:3 contain the name */

        return (AcpiGbl_SmResourceDispatch [
                    ((ResourceType & ACPI_RDESC_SMALL_MASK) >> 3)]);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsByteStreamToList
 *
 * PARAMETERS:  ByteStreamBuffer        - Pointer to the resource byte stream
 *              ByteStreamBufferLength  - Length of ByteStreamBuffer
 *              OutputBuffer            - Pointer to the buffer that will
 *                                        contain the output structures
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Takes the resource byte stream and parses it, creating a
 *              linked list of resources in the caller's output buffer
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsByteStreamToList (
    UINT8                   *ByteStreamBuffer,
    UINT32                  ByteStreamBufferLength,
    UINT8                   *OutputBuffer)
{
    UINT8                   *Buffer = OutputBuffer;
    ACPI_STATUS             Status;
    ACPI_SIZE               BytesParsed = 0;
    ACPI_SIZE               BytesConsumed = 0;
    ACPI_SIZE               StructureSize = 0;
    ACPI_RESOURCE           *Resource;
    ACPI_RESOURCE_HANDLER   Handler;


    ACPI_FUNCTION_TRACE ("RsByteStreamToList");


    /* Loop until end-of-buffer or an EndTag is found */

    while (BytesParsed < ByteStreamBufferLength)
    {
        /* Get the handler associated with this Descriptor Type */

        Handler = AcpiRsGetResourceHandler (*ByteStreamBuffer);
        if (Handler)
        {
            /* Convert a byte stream resource to local resource struct */

            Status = Handler (ByteStreamBuffer, &BytesConsumed,
                        &Buffer, &StructureSize);
        }
        else
        {
            /* Invalid resource type */

            Status = AE_AML_INVALID_RESOURCE_TYPE;
        }

        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        /* Set the aligned length of the new resource descriptor */

        Resource = ACPI_CAST_PTR (ACPI_RESOURCE, Buffer);
        Resource->Length = (UINT32) ACPI_ALIGN_RESOURCE_SIZE (Resource->Length);

        /* Normal exit on completion of an EndTag resource descriptor */

        if (AcpiRsGetResourceType (*ByteStreamBuffer) == ACPI_RDESC_TYPE_END_TAG)
        {
            return_ACPI_STATUS (AE_OK);
        }

        /* Update counter and point to the next input resource */

        BytesParsed += BytesConsumed;
        ByteStreamBuffer += BytesConsumed;

        /* Point to the next structure in the output buffer */

        Buffer += ACPI_ALIGN_RESOURCE_SIZE (StructureSize);
    }

    /* Completed buffer, but did not find an EndTag resource descriptor */

    return_ACPI_STATUS (AE_AML_NO_RESOURCE_END_TAG);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiRsListToByteStream
 *
 * PARAMETERS:  Resource                - Pointer to the resource linked list
 *              ByteSteamSizeNeeded     - Calculated size of the byte stream
 *                                        needed from calling
 *                                        AcpiRsGetByteStreamLength()
 *                                        The size of the OutputBuffer is
 *                                        guaranteed to be >=
 *                                        ByteStreamSizeNeeded
 *              OutputBuffer            - Pointer to the buffer that will
 *                                        contain the byte stream
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Takes the resource linked list and parses it, creating a
 *              byte stream of resources in the caller's output buffer
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRsListToByteStream (
    ACPI_RESOURCE           *Resource,
    ACPI_SIZE               ByteStreamSizeNeeded,
    UINT8                   *OutputBuffer)
{
    UINT8                   *Buffer = OutputBuffer;
    ACPI_SIZE               BytesConsumed = 0;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE ("RsListToByteStream");


    /* Convert each resource descriptor in the list */

    while (1)
    {
        /* Validate Type before dispatch */

        if (Resource->Type > ACPI_RSTYPE_MAX)
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_ERROR,
                "Invalid descriptor type (%X) in resource list\n",
                Resource->Type));
            return_ACPI_STATUS (AE_BAD_DATA);
        }

        /* Perform the conversion, per resource type */

        Status = AcpiGbl_StreamDispatch[Resource->Type] (Resource,
                    &Buffer, &BytesConsumed);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        /* Check for end-of-list */

        if (Resource->Type == ACPI_RSTYPE_END_TAG)
        {
            /* An End Tag indicates the end of the Resource Template */

            return_ACPI_STATUS (AE_OK);
        }

        /* Set the Buffer to point to the next (output) resource descriptor */

        Buffer += BytesConsumed;

        /* Point to the next input resource object */

        Resource = ACPI_PTR_ADD (ACPI_RESOURCE,
                        Resource, Resource->Length);
    }
}

