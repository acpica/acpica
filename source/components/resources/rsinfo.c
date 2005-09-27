/*******************************************************************************
 *
 * Module Name: rsinfo - Dispatch and Info tables
 *              $Revision: 1.1 $
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

#define __RSINFO_C__

#include "acpi.h"
#include "acresrc.h"

#define _COMPONENT          ACPI_RESOURCES
        ACPI_MODULE_NAME    ("rsinfo")

/*
 * Resource dispatch and information tables. Any new resource types (either
 * Large or Small) must be reflected in each of these tables, so they are here
 * in one place.
 *
 * The tables for Large descriptors are indexed by bits 6:0 of the AML
 * descriptor type byte. The tables for Small descriptors are indexed by
 * bits 6:3 of the descriptor byte. The tables for internal resource
 * descriptors are indexed by the ACPI_RESOURCE_TYPE field.
 */


/* Macros used in the tables below */

#define ACPI_LARGE_RESOURCE_LENGTHS(r) \
    sizeof(AML_RESOURCE_##r) - sizeof(AML_RESOURCE_LARGE_HEADER),\
    ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_##r)

#define ACPI_SMALL_RESOURCE_LENGTHS(r) \
    sizeof(AML_RESOURCE_##r) - sizeof(AML_RESOURCE_SMALL_HEADER),\
    ACPI_SIZEOF_RESOURCE (ACPI_RESOURCE_##r)

/* Small descriptors with no associated data (header only) */

#define ACPI_SMALL_RESOURCE_LENGTHS2(r) \
    sizeof(AML_RESOURCE_##r) - sizeof(AML_RESOURCE_SMALL_HEADER),\
    ACPI_RESOURCE_LENGTH

/* Redirect large/small Vendor resources to common internal format */

#define ACPI_RESOURCE_VENDOR_SMALL  ACPI_RESOURCE_VENDOR
#define ACPI_RESOURCE_VENDOR_LARGE  ACPI_RESOURCE_VENDOR


/* Dispatch table for convert-resource-to-AML (Set Resource) functions */

ACPI_SET_RESOURCE_HANDLER           AcpiGbl_SetResourceDispatch [] =
{
    AcpiRsSetIrqResource,           /* ACPI_RESOURCE_TYPE_IRQ */
    AcpiRsSetDmaResource,           /* ACPI_RESOURCE_TYPE_DMA */
    AcpiRsSetStartDpfResource,      /* ACPI_RESOURCE_TYPE_START_DEPENDENT */
    AcpiRsSetEndDpfResource,        /* ACPI_RESOURCE_TYPE_END_DEPENDENT */
    AcpiRsSetIoResource,            /* ACPI_RESOURCE_TYPE_IO */
    AcpiRsSetFixedIoResource,       /* ACPI_RESOURCE_TYPE_FIXED_IO */
    AcpiRsSetVendorResource,        /* ACPI_RESOURCE_TYPE_VENDOR */
    AcpiRsSetEndTagResource,        /* ACPI_RESOURCE_TYPE_END_TAG */
    AcpiRsSetMemory24Resource,      /* ACPI_RESOURCE_TYPE_MEMORY24 */
    AcpiRsSetMemory32Resource,      /* ACPI_RESOURCE_TYPE_MEMORY32 */
    AcpiRsSetFixedMemory32Resource, /* ACPI_RESOURCE_TYPE_FIXED_MEMORY32 */
    AcpiRsSetAddress16Resource,     /* ACPI_RESOURCE_TYPE_ADDRESS16 */
    AcpiRsSetAddress32Resource,     /* ACPI_RESOURCE_TYPE_ADDRESS32 */
    AcpiRsSetAddress64Resource,     /* ACPI_RESOURCE_TYPE_ADDRESS64 */
    AcpiRsSetExtAddress64Resource,  /* ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64 */
    AcpiRsSetExtIrqResource,        /* ACPI_RESOURCE_TYPE_EXTENDED_IRQ */
    AcpiRsSetGenericRegResource     /* ACPI_RESOURCE_TYPE_GENERIC_REGISTER */
};


/* Dispatch tables for convert-AML-to-resource (Get Resource) functions */

ACPI_GET_RESOURCE_HANDLER           AcpiGbl_SmGetResourceDispatch [] =
{
    NULL,                           /* 0x00, Reserved */
    NULL,                           /* 0x01, Reserved */
    NULL,                           /* 0x02, Reserved */
    NULL,                           /* 0x03, Reserved */
    AcpiRsGetIrqResource,           /* 0x04, ACPI_RESOURCE_NAME_IRQ */
    AcpiRsGetDmaResource,           /* 0x05, ACPI_RESOURCE_NAME_DMA */
    AcpiRsGetStartDpfResource,      /* 0x06, ACPI_RESOURCE_NAME_START_DEPENDENT */
    AcpiRsGetEndDpfResource,        /* 0x07, ACPI_RESOURCE_NAME_END_DEPENDENT */
    AcpiRsGetIoResource,            /* 0x08, ACPI_RESOURCE_NAME_IO */
    AcpiRsGetFixedIoResource,       /* 0x09, ACPI_RESOURCE_NAME_FIXED_IO */
    NULL,                           /* 0x0A, Reserved */
    NULL,                           /* 0x0B, Reserved */
    NULL,                           /* 0x0C, Reserved */
    NULL,                           /* 0x0D, Reserved */
    AcpiRsGetVendorResource,        /* 0x0E, ACPI_RESOURCE_NAME_VENDOR_SMALL */
    AcpiRsGetEndTagResource         /* 0x0F, ACPI_RESOURCE_NAME_END_TAG */
};

ACPI_GET_RESOURCE_HANDLER           AcpiGbl_LgGetResourceDispatch[] =
{
    NULL,                           /* 0x00, Reserved */
    AcpiRsGetMemory24Resource,      /* 0x01, ACPI_RESOURCE_NAME_MEMORY24 */
    AcpiRsGetGenericRegResource,    /* 0x02, ACPI_RESOURCE_NAME_GENERIC_REGISTER */
    NULL,                           /* 0x03, Reserved */
    AcpiRsGetVendorResource,        /* 0x04, ACPI_RESOURCE_NAME_VENDOR_LARGE */
    AcpiRsGetMemory32Resource,      /* 0x05, ACPI_RESOURCE_NAME_MEMORY32 */
    AcpiRsGetFixedMemory32Resource, /* 0x06, ACPI_RESOURCE_NAME_FIXED_MEMORY32 */
    AcpiRsGetAddress32Resource,     /* 0x07, ACPI_RESOURCE_NAME_ADDRESS32 */
    AcpiRsGetAddress16Resource,     /* 0x08, ACPI_RESOURCE_NAME_ADDRESS16 */
    AcpiRsGetExtIrqResource,        /* 0x09, ACPI_RESOURCE_NAME_EXTENDED_IRQ */
    AcpiRsGetAddress64Resource,     /* 0x0A, ACPI_RESOURCE_NAME_ADDRESS64 */
    AcpiRsGetExtAddress64Resource   /* 0x0B, ACPI_RESOURCE_NAME_EXTENDED_ADDRESS64 */
};


#if defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)

/* Dispatch table for resource dump functions */

ACPI_DUMP_RESOURCE_HANDLER          AcpiGbl_DumpResourceDispatch [] =
{
    AcpiRsDumpIrq,                  /* ACPI_RESOURCE_TYPE_IRQ */
    AcpiRsDumpDma,                  /* ACPI_RESOURCE_TYPE_DMA */
    AcpiRsDumpStartDependFns,       /* ACPI_RESOURCE_TYPE_START_DEPENDENT */
    AcpiRsDumpEndDependFns,         /* ACPI_RESOURCE_TYPE_END_DEPENDENT */
    AcpiRsDumpIo,                   /* ACPI_RESOURCE_TYPE_IO */
    AcpiRsDumpFixedIo,              /* ACPI_RESOURCE_TYPE_FIXED_IO */
    AcpiRsDumpVendorSpecific,       /* ACPI_RESOURCE_TYPE_VENDOR */
    AcpiRsDumpEndTag,               /* ACPI_RESOURCE_TYPE_END_TAG */
    AcpiRsDumpMemory24,             /* ACPI_RESOURCE_TYPE_MEMORY24 */
    AcpiRsDumpMemory32,             /* ACPI_RESOURCE_TYPE_MEMORY32 */
    AcpiRsDumpFixedMemory32,        /* ACPI_RESOURCE_TYPE_FIXED_MEMORY32 */
    AcpiRsDumpAddress16,            /* ACPI_RESOURCE_TYPE_ADDRESS16 */
    AcpiRsDumpAddress32,            /* ACPI_RESOURCE_TYPE_ADDRESS32 */
    AcpiRsDumpAddress64,            /* ACPI_RESOURCE_TYPE_ADDRESS64 */
    AcpiRsDumpExtAddress64,         /* ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64 */
    AcpiRsDumpExtendedIrq,          /* ACPI_RESOURCE_TYPE_EXTENDED_IRQ */
    AcpiRsDumpGenericReg            /* ACPI_RESOURCE_TYPE_GENERIC_REGISTER */
};
#endif

/*
 * Base sizes for external AML resource descriptors, indexed by internal type.
 * Includes size of the descriptor header (1 byte for small descriptors,
 * 3 bytes for large descriptors)
 */
UINT8                               AcpiGbl_AmlResourceSizes [] =
{
    sizeof (AML_RESOURCE_IRQ),              /* ACPI_RESOURCE_TYPE_IRQ (Byte 3 is optional, but always created) */
    sizeof (AML_RESOURCE_DMA),              /* ACPI_RESOURCE_TYPE_DMA */
    sizeof (AML_RESOURCE_START_DEPENDENT),  /* ACPI_RESOURCE_TYPE_START_DEPENDENT (Byte 1 is optional, but always created) */
    sizeof (AML_RESOURCE_END_DEPENDENT),    /* ACPI_RESOURCE_TYPE_END_DEPENDENT */
    sizeof (AML_RESOURCE_IO),               /* ACPI_RESOURCE_TYPE_IO */
    sizeof (AML_RESOURCE_FIXED_IO),         /* ACPI_RESOURCE_TYPE_FIXED_IO */
    sizeof (AML_RESOURCE_VENDOR_SMALL),     /* ACPI_RESOURCE_TYPE_VENDOR */
    sizeof (AML_RESOURCE_END_TAG),          /* ACPI_RESOURCE_TYPE_END_TAG */
    sizeof (AML_RESOURCE_MEMORY24),         /* ACPI_RESOURCE_TYPE_MEMORY24 */
    sizeof (AML_RESOURCE_MEMORY32),         /* ACPI_RESOURCE_TYPE_MEMORY32 */
    sizeof (AML_RESOURCE_FIXED_MEMORY32),   /* ACPI_RESOURCE_TYPE_FIXED_MEMORY32 */
    sizeof (AML_RESOURCE_ADDRESS16),        /* ACPI_RESOURCE_TYPE_ADDRESS16 */
    sizeof (AML_RESOURCE_ADDRESS32),        /* ACPI_RESOURCE_TYPE_ADDRESS32 */
    sizeof (AML_RESOURCE_ADDRESS64),        /* ACPI_RESOURCE_TYPE_ADDRESS64 */
    sizeof (AML_RESOURCE_EXTENDED_ADDRESS64),/*ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64 */
    sizeof (AML_RESOURCE_EXTENDED_IRQ),     /* ACPI_RESOURCE_TYPE_EXTENDED_IRQ */
    sizeof (AML_RESOURCE_GENERIC_REGISTER)  /* ACPI_RESOURCE_TYPE_GENERIC_REGISTER */
};


/*
 * Base sizes of resource descriptors, both the actual AML stream length and
 * size of the internal struct representation.
 */
ACPI_RESOURCE_INFO                  AcpiGbl_SmResourceInfo [] =
{
    {0, 0, 0},                                             /* 0x00, Reserved */
    {0, 0, 0},                                             /* 0x01, Reserved */
    {0, 0, 0},                                             /* 0x02, Reserved */
    {0, 0, 0},                                             /* 0x03, Reserved */
    {2, ACPI_SMALL_RESOURCE_LENGTHS (IRQ)},                /* 0x04, ACPI_RESOURCE_NAME_IRQ */
    {0, ACPI_SMALL_RESOURCE_LENGTHS (DMA)},                /* 0x05, ACPI_RESOURCE_NAME_DMA */
    {2, ACPI_SMALL_RESOURCE_LENGTHS (START_DEPENDENT)},    /* 0x06, ACPI_RESOURCE_NAME_START_DEPENDENT */
    {0, ACPI_SMALL_RESOURCE_LENGTHS2 (END_DEPENDENT)},     /* 0x07, ACPI_RESOURCE_NAME_END_DEPENDENT */
    {0, ACPI_SMALL_RESOURCE_LENGTHS (IO)},                 /* 0x08, ACPI_RESOURCE_NAME_IO */
    {0, ACPI_SMALL_RESOURCE_LENGTHS (FIXED_IO)},           /* 0x09, ACPI_RESOURCE_NAME_FIXED_IO */
    {0, 0, 0},                                             /* 0x0A, Reserved */
    {0, 0, 0},                                             /* 0x0B, Reserved */
    {0, 0, 0},                                             /* 0x0C, Reserved */
    {0, 0, 0},                                             /* 0x0D, Reserved */
    {1, ACPI_SMALL_RESOURCE_LENGTHS (VENDOR_SMALL)},       /* 0x0E, ACPI_RESOURCE_NAME_VENDOR_SMALL */
    {0, ACPI_SMALL_RESOURCE_LENGTHS2 (END_TAG)}            /* 0x0F, ACPI_RESOURCE_NAME_END_TAG */
};

ACPI_RESOURCE_INFO                  AcpiGbl_LgResourceInfo [] =
{
    {0, 0, 0},                                             /* 0x00, Reserved */
    {0, ACPI_LARGE_RESOURCE_LENGTHS (MEMORY24)},           /* 0x01, ACPI_RESOURCE_NAME_MEMORY24 */
    {0, ACPI_LARGE_RESOURCE_LENGTHS (GENERIC_REGISTER)},   /* 0x02, ACPI_RESOURCE_NAME_GENERIC_REGISTER */
    {0, 0, 0},                                             /* 0x03, Reserved */
    {1, ACPI_LARGE_RESOURCE_LENGTHS (VENDOR_LARGE)},       /* 0x04, ACPI_RESOURCE_NAME_VENDOR_LARGE */
    {0, ACPI_LARGE_RESOURCE_LENGTHS (MEMORY32)},           /* 0x05, ACPI_RESOURCE_NAME_MEMORY32 */
    {0, ACPI_LARGE_RESOURCE_LENGTHS (FIXED_MEMORY32)},     /* 0x06, ACPI_RESOURCE_NAME_FIXED_MEMORY32 */
    {1, ACPI_LARGE_RESOURCE_LENGTHS (ADDRESS32)},          /* 0x07, ACPI_RESOURCE_NAME_ADDRESS32 */
    {1, ACPI_LARGE_RESOURCE_LENGTHS (ADDRESS16)},          /* 0x08, ACPI_RESOURCE_NAME_ADDRESS16 */
    {1, ACPI_LARGE_RESOURCE_LENGTHS (EXTENDED_IRQ)},       /* 0x09, ACPI_RESOURCE_NAME_EXTENDED_IRQ */
    {1, ACPI_LARGE_RESOURCE_LENGTHS (ADDRESS64)},          /* 0x0A, ACPI_RESOURCE_NAME_ADDRESS64 */
    {0, ACPI_LARGE_RESOURCE_LENGTHS (EXTENDED_ADDRESS64)}  /* 0x0B, ACPI_RESOURCE_NAME_EXTENDED_ADDRESS64 */
};


