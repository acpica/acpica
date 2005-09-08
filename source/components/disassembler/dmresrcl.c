/*******************************************************************************
 *
 * Module Name: dmresrcl.c - "Large" Resource Descriptor disassembly
 *              $Revision: 1.23 $
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


#include "acpi.h"
#include "acdisasm.h"


#ifdef ACPI_DISASSEMBLER

#define _COMPONENT          ACPI_CA_DEBUGGER
        ACPI_MODULE_NAME    ("dbresrcl")

/* Local prototypes */

static void
AcpiDmSpaceFlags (
        UINT8               Flags);

static void
AcpiDmIoFlags (
        UINT8               Flags);

static void
AcpiDmIoFlags2 (
        UINT8               SpecificFlags);

static void
AcpiDmMemoryFlags (
    UINT8                   Flags,
    UINT8                   SpecificFlags);

static void
AcpiDmMemoryFlags2 (
    UINT8                   SpecificFlags);


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmSpaceFlags
 *
 * PARAMETERS:  Flags               - Flag byte to be decoded
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode the flags specific to Space Address space descriptors
 *
 ******************************************************************************/

static void
AcpiDmSpaceFlags (
        UINT8               Flags)
{
    AcpiOsPrintf ("%s, %s, %s, %s,",
        AcpiGbl_ConsumeDecode [(Flags & 1)],
        AcpiGbl_DECDecode [(Flags & 0x2) >> 1],
        AcpiGbl_MinDecode [(Flags & 0x4) >> 2],
        AcpiGbl_MaxDecode [(Flags & 0x8) >> 3]);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmIoFlags
 *
 * PARAMETERS:  Flags               - Flag byte to be decoded
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode the flags specific to IO Address space descriptors
 *
 ******************************************************************************/

static void
AcpiDmIoFlags (
        UINT8               Flags)
{
    AcpiOsPrintf ("%s, %s, %s, %s,",
        AcpiGbl_ConsumeDecode [(Flags & 1)],
        AcpiGbl_MinDecode [(Flags & 0x4) >> 2],
        AcpiGbl_MaxDecode [(Flags & 0x8) >> 3],
        AcpiGbl_DECDecode [(Flags & 0x2) >> 1]);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmIoFlags2
 *
 * PARAMETERS:  SpecificFlags       - "Specific" flag byte to be decoded
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode the flags specific to IO Address space descriptors
 *
 ******************************************************************************/

static void
AcpiDmIoFlags2 (
        UINT8               SpecificFlags)
{
    AcpiOsPrintf (", %s",
        AcpiGbl_TTPDecode [(SpecificFlags & 0x10) >> 4]);

    /* TRS is only used if TTP is TypeTranslation */

    if (SpecificFlags & 0x10)
    {
        AcpiOsPrintf (", %s",
            AcpiGbl_TRSDecode [(SpecificFlags & 0x20) >> 5]);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmMemoryFlags
 *
 * PARAMETERS:  Flags               - Flag byte to be decoded
 *              SpecificFlags       - "Specific" flag byte to be decoded
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode flags specific to Memory Address Space descriptors
 *
 ******************************************************************************/

static void
AcpiDmMemoryFlags (
    UINT8                   Flags,
    UINT8                   SpecificFlags)
{
    AcpiOsPrintf ("%s, %s, %s, %s, %s, %s,",
        AcpiGbl_ConsumeDecode [(Flags & 1)],
        AcpiGbl_DECDecode [(Flags & 0x2) >> 1],
        AcpiGbl_MinDecode [(Flags & 0x4) >> 2],
        AcpiGbl_MaxDecode [(Flags & 0x8) >> 3],
        AcpiGbl_MEMDecode [(SpecificFlags & 0x6) >> 1],
        AcpiGbl_RWDecode [(SpecificFlags & 0x1)]);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmMemoryFlags2
 *
 * PARAMETERS:  SpecificFlags       - "Specific" flag byte to be decoded
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode flags specific to Memory Address Space descriptors
 *
 ******************************************************************************/

static void
AcpiDmMemoryFlags2 (
    UINT8                   SpecificFlags)
{
    AcpiOsPrintf (", %s, %s",
        AcpiGbl_MTPDecode [(SpecificFlags & 0x18) >> 3],
        AcpiGbl_TTPDecode [(SpecificFlags & 0x20) >> 5]);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmWordDescriptor
 *
 * PARAMETERS:  Resource            - Pointer to the resource descriptor
 *              Length              - Length of the descriptor in bytes
 *              Level               - Current source code indentation level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode a Word Address Space descriptor
 *
 ******************************************************************************/

void
AcpiDmWordDescriptor (
    ASL_RESOURCE_DESC       *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    if (Resource->Was.ResourceType >= 0xC0)
    {
        AcpiOsPrintf ("WordSpace (0x%2.2X, ", Resource->Was.ResourceType);
        AcpiDmSpaceFlags (Resource->Was.Flags);
        AcpiOsPrintf (" 0x%2.2X,", Resource->Was.SpecificFlags);
    }
    else
    {
        AcpiOsPrintf ("%s (",
            AcpiGbl_WordDecode [(Resource->Was.ResourceType & 3)]);

        AcpiDmIoFlags (Resource->Was.Flags);

        if ((Resource->Was.ResourceType & 0x3) == 1)
        {
            AcpiOsPrintf (" %s,",
                AcpiGbl_RNGDecode [(Resource->Was.SpecificFlags & 0x3)]);
        }
    }

    /* The WORD values */

    AcpiOsPrintf ("\n");
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%4.4X, // Address Space Granularity\n",
        (UINT32) Resource->Was.Granularity);
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%4.4X, // Address Range Minimum\n",
        (UINT32) Resource->Was.AddressMin);
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%4.4X, // Address Range Maximum\n",
        (UINT32) Resource->Was.AddressMax);
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%4.4X, // Address Translation Offset\n",
        (UINT32) Resource->Was.TranslationOffset);
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%4.4X",
        (UINT32) Resource->Was.AddressLength);

    /*
     * Optional fields:
     * If ResourceSourceIndex (byte) exists, ResourceSource (string) must also
     * (from ACPI specification)
     */
    if (Length > 14)
    {
        AcpiOsPrintf (", 0x%2.2X",
            (UINT32) Resource->Was.OptionalFields[0]);  /* Byte 13 */
        AcpiOsPrintf (", %s",
            &Resource->Was.OptionalFields[1]);          /* Bytes 14+ */
    }
    else
    {
        AcpiOsPrintf (",,,");
    }

    /* Type-specific flags */

    if (Resource->Was.ResourceType == ACPI_IO_RANGE)
    {
        AcpiOsPrintf ("\n");
        AcpiDmIndent (Level + 1);
        AcpiDmIoFlags2 (Resource->Was.SpecificFlags);
    }
    else if (Resource->Was.ResourceType == ACPI_MEMORY_RANGE)
    {
        AcpiOsPrintf ("\n");
        AcpiDmIndent (Level + 1);
        AcpiDmMemoryFlags2 (Resource->Was.SpecificFlags);
    }
    AcpiOsPrintf (")\n");
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDwordDescriptor
 *
 * PARAMETERS:  Resource            - Pointer to the resource descriptor
 *              Length              - Length of the descriptor in bytes
 *              Level               - Current source code indentation level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode a DWord Address Space descriptor
 *
 ******************************************************************************/

void
AcpiDmDwordDescriptor (
    ASL_RESOURCE_DESC       *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    if (Resource->Das.ResourceType >= 0xC0)
    {
        AcpiOsPrintf ("DWordSpace (0x%2.2X, ", Resource->Das.ResourceType);
        AcpiDmSpaceFlags (Resource->Das.Flags);
        AcpiOsPrintf (" 0x%2.2X,", Resource->Das.SpecificFlags);
    }
    else
    {
        AcpiOsPrintf ("D%s (",
            AcpiGbl_WordDecode [(Resource->Das.ResourceType & 3)]);

        if ((Resource->Das.ResourceType & 0x3) == 1)
        {
            AcpiDmIoFlags (Resource->Das.Flags);
            AcpiOsPrintf (" %s,",
                AcpiGbl_RNGDecode [(Resource->Das.SpecificFlags & 0x3)]);
        }
        else
        {
            AcpiDmMemoryFlags (Resource->Das.Flags, Resource->Das.SpecificFlags);
        }
    }

    /* The DWORD values */

    AcpiOsPrintf ("\n");
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X, // Address Space Granularity\n",
        Resource->Das.Granularity);
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X, // Address Range Minimum\n",
        Resource->Das.AddressMin);
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X, // Address Range Maximum\n",
        Resource->Das.AddressMax);
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X, // Address Translation Offset\n",
        Resource->Das.TranslationOffset);
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X",
        Resource->Das.AddressLength);

    /*
     * Optional fields:
     * If ResourceSourceIndex (byte) exists, ResourceSource (string) must also
     * (from ACPI specification)
     */
    if (Length > 24)
    {
        AcpiOsPrintf (", 0x%2.2X",
            Resource->Das.OptionalFields[0]);   /* Byte 23 */
        AcpiOsPrintf (", %s",
            &Resource->Das.OptionalFields[1]);  /* Bytes 24+ */
    }
    else
    {
        AcpiOsPrintf (",,,");
    }

    /* Type-specific flags */

    if (Resource->Das.ResourceType == ACPI_IO_RANGE)
    {
        AcpiOsPrintf ("\n");
        AcpiDmIndent (Level + 1);
        AcpiDmIoFlags2 (Resource->Das.SpecificFlags);
    }
    else if (Resource->Das.ResourceType == ACPI_MEMORY_RANGE)
    {
        AcpiOsPrintf ("\n");
        AcpiDmIndent (Level + 1);
        AcpiDmMemoryFlags2 (Resource->Das.SpecificFlags);
    }
    AcpiOsPrintf (")\n");
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmExtendedDescriptor
 *
 * PARAMETERS:  Resource            - Pointer to the resource descriptor
 *              Length              - Length of the descriptor in bytes
 *              Level               - Current source code indentation level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode a Extended Address Space descriptor
 *
 ******************************************************************************/

void
AcpiDmExtendedDescriptor (
    ASL_RESOURCE_DESC       *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    if (Resource->Eas.ResourceType >= 0xC0)
    {
        AcpiOsPrintf ("ExtendedSpace (0x%2.2X, ", Resource->Eas.ResourceType);
        AcpiDmSpaceFlags (Resource->Eas.Flags);
        AcpiOsPrintf (" 0x%2.2X,", Resource->Eas.SpecificFlags);
    }
    else
    {
        if (Resource->Eas.ResourceType == ACPI_IO_RANGE)
        {
            AcpiOsPrintf ("ExtendedIO (");
            AcpiDmIoFlags (Resource->Eas.Flags);
            AcpiOsPrintf (" %s,",
                AcpiGbl_RNGDecode [(Resource->Eas.SpecificFlags & 0x3)]);
        }
        else
        {
            AcpiOsPrintf ("ExtendedMemory (");
            AcpiDmMemoryFlags (Resource->Eas.Flags, Resource->Eas.SpecificFlags);
        }
    }

    /* The QWORD values */

    AcpiOsPrintf ("\n");
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X%8.8X, // Address Space Granularity\n",
        ACPI_FORMAT_UINT64 (ACPI_GET_ADDRESS (Resource->Eas.Granularity)));

    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X%8.8X, // Address Range Minimum\n",
        ACPI_FORMAT_UINT64 (ACPI_GET_ADDRESS (Resource->Eas.AddressMin)));

    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X%8.8X, // Address Range Maximum\n",
        ACPI_FORMAT_UINT64 (ACPI_GET_ADDRESS (Resource->Eas.AddressMax)));

    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X%8.8X, // Address Translation Offset\n",
        ACPI_FORMAT_UINT64 (ACPI_GET_ADDRESS (Resource->Eas.TranslationOffset)));

    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X%8.8X, // Address Length\n",
        ACPI_FORMAT_UINT64 (ACPI_GET_ADDRESS (Resource->Eas.AddressLength)));

    /* Type-specific flags */

    AcpiDmIndent (Level + 1);
    if (Resource->Eas.ResourceType == ACPI_IO_RANGE)
    {
        AcpiOsPrintf ("0x%8.8X%8.8X, // Type Specific Attributes\n",
            ACPI_FORMAT_UINT64 (
                ACPI_GET_ADDRESS (Resource->Eas.TypeSpecificAttributes)));
        AcpiDmIndent (Level + 1);
        AcpiDmIoFlags2 (Resource->Eas.SpecificFlags);
        AcpiOsPrintf (")\n");
    }
    else if (Resource->Eas.ResourceType == ACPI_MEMORY_RANGE)
    {
        AcpiOsPrintf ("0x%8.8X%8.8X, // Type Specific Attributes\n",
            ACPI_FORMAT_UINT64 (
                ACPI_GET_ADDRESS (Resource->Eas.TypeSpecificAttributes)));
        AcpiDmIndent (Level + 1);
        AcpiDmMemoryFlags2 (Resource->Eas.SpecificFlags);
        AcpiOsPrintf (")\n");
    }
    else
    {
        AcpiOsPrintf ("0x%8.8X%8.8X) // Type Specific Attributes\n",
            ACPI_FORMAT_UINT64 (
                ACPI_GET_ADDRESS (Resource->Eas.TypeSpecificAttributes)));
    }

}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmQwordDescriptor
 *
 * PARAMETERS:  Resource            - Pointer to the resource descriptor
 *              Length              - Length of the descriptor in bytes
 *              Level               - Current source code indentation level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode a QWord Address Space descriptor
 *
 ******************************************************************************/

void
AcpiDmQwordDescriptor (
    ASL_RESOURCE_DESC       *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    if (Resource->Qas.ResourceType >= 0xC0)
    {
        AcpiOsPrintf ("QWordSpace (0x%2.2X, ", Resource->Qas.ResourceType);
        AcpiDmSpaceFlags (Resource->Qas.Flags);
        AcpiOsPrintf (" 0x%2.2X,", Resource->Qas.SpecificFlags);
    }
    else
    {
        AcpiOsPrintf ("Q%s (",
            AcpiGbl_WordDecode [(Resource->Qas.ResourceType & 3)]);

        if ((Resource->Qas.ResourceType & 0x3) == 1)
        {
            AcpiDmIoFlags (Resource->Qas.Flags);
            AcpiOsPrintf (" %s,",
                AcpiGbl_RNGDecode [(Resource->Qas.SpecificFlags & 0x3)]);
        }
        else
        {
            AcpiDmMemoryFlags (Resource->Qas.Flags, Resource->Qas.SpecificFlags);
        }
    }

    /* The QWORD values */

    AcpiOsPrintf ("\n");
    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X%8.8X, // Address Space Granularity\n",
        ACPI_FORMAT_UINT64 (ACPI_GET_ADDRESS (Resource->Qas.Granularity)));

    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X%8.8X, // Address Range Minimum\n",
        ACPI_FORMAT_UINT64 (ACPI_GET_ADDRESS (Resource->Qas.AddressMin)));

    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X%8.8X, // Address Range Maximum\n",
        ACPI_FORMAT_UINT64 (ACPI_GET_ADDRESS (Resource->Qas.AddressMax)));

    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X%8.8X, // Address Translation Offset\n",
        ACPI_FORMAT_UINT64 (ACPI_GET_ADDRESS (Resource->Qas.TranslationOffset)));

    AcpiDmIndent (Level + 1);
    AcpiOsPrintf ("0x%8.8X%8.8X",
        ACPI_FORMAT_UINT64 (ACPI_GET_ADDRESS (Resource->Qas.AddressLength)));

    /*
     * Optional fields:
     * If ResourceSourceIndex (byte) exists, ResourceSource (string) must also
     * (from ACPI specification)
     */
    if (Length > 44)
    {
        AcpiOsPrintf (", 0x%2.2X",
            Resource->Qas.OptionalFields[0]);   /* Byte 43 */
        AcpiOsPrintf (", %s",
            &Resource->Qas.OptionalFields[1]);  /* Bytes 44+ */
    }
    else
    {
        AcpiOsPrintf (",,,");
    }

    /* Type-specific flags */

    if (Resource->Qas.ResourceType == ACPI_IO_RANGE)
    {
        AcpiOsPrintf ("\n");
        AcpiDmIndent (Level + 1);
        AcpiDmIoFlags2 (Resource->Qas.SpecificFlags);
    }
    else if (Resource->Qas.ResourceType == ACPI_MEMORY_RANGE)
    {
        AcpiOsPrintf ("\n");
        AcpiDmIndent (Level + 1);
        AcpiDmMemoryFlags2 (Resource->Qas.SpecificFlags);
    }
    AcpiOsPrintf (")\n");
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmMemory24Descriptor
 *
 * PARAMETERS:  Resource            - Pointer to the resource descriptor
 *              Length              - Length of the descriptor in bytes
 *              Level               - Current source code indentation level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode a Memory24 descriptor
 *
 ******************************************************************************/

void
AcpiDmMemory24Descriptor (
    ASL_RESOURCE_DESC       *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    AcpiOsPrintf ("Memory24 (%s, 0x%4.4X, 0x%4.4X, 0x%4.4X, 0x%4.4X)\n",
        AcpiGbl_RWDecode [Resource->M24.Information & 1],
        (UINT32) Resource->M24.AddressMin,
        (UINT32) Resource->M24.AddressMax,
        (UINT32) Resource->M24.Alignment,
        (UINT32) Resource->M24.RangeLength);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmMemory32Descriptor
 *
 * PARAMETERS:  Resource            - Pointer to the resource descriptor
 *              Length              - Length of the descriptor in bytes
 *              Level               - Current source code indentation level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode a Memory32 descriptor
 *
 ******************************************************************************/

void
AcpiDmMemory32Descriptor (
    ASL_RESOURCE_DESC       *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    AcpiOsPrintf ("Memory32 (%s, 0x%8.8X, 0x%8.8X, 0x%8.8X, 0x%8.8X)\n",
        AcpiGbl_RWDecode [Resource->M32.Information & 1],
        Resource->M32.AddressMin,
        Resource->M32.AddressMax,
        Resource->M32.Alignment,
        Resource->M32.RangeLength);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmFixedMemory32Descriptor
 *
 * PARAMETERS:  Resource            - Pointer to the resource descriptor
 *              Length              - Length of the descriptor in bytes
 *              Level               - Current source code indentation level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode a Fixed Memory32 descriptor
 *
 ******************************************************************************/

void
AcpiDmFixedMemory32Descriptor (
    ASL_RESOURCE_DESC       *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    AcpiOsPrintf ("Memory32Fixed (%s, 0x%8.8X, 0x%8.8X)\n",
        AcpiGbl_RWDecode [Resource->F32.Information & 1],
        Resource->F32.BaseAddress,
        Resource->F32.RangeLength);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmGenericRegisterDescriptor
 *
 * PARAMETERS:  Resource            - Pointer to the resource descriptor
 *              Length              - Length of the descriptor in bytes
 *              Level               - Current source code indentation level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode a Generic Register descriptor
 *
 ******************************************************************************/

void
AcpiDmGenericRegisterDescriptor (
    ASL_RESOURCE_DESC       *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    AcpiOsPrintf ("Register (");

    AcpiDmAddressSpace (Resource->Grg.AddressSpaceId);

    AcpiOsPrintf ("0x%2.2X, 0x%2.2X, 0x%8.8X%8.8X)\n",
        (UINT32) Resource->Grg.BitWidth,
        (UINT32) Resource->Grg.BitOffset,
        ACPI_FORMAT_UINT64 (ACPI_GET_ADDRESS (Resource->Grg.Address)));
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmInterruptDescriptor
 *
 * PARAMETERS:  Resource            - Pointer to the resource descriptor
 *              Length              - Length of the descriptor in bytes
 *              Level               - Current source code indentation level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode a extended Interrupt descriptor
 *
 ******************************************************************************/

void
AcpiDmInterruptDescriptor (
    ASL_RESOURCE_DESC       *Resource,
    UINT32                  Length,
    UINT32                  Level)
{
    UINT32                  i;
    UINT8                   *Rover;


    AcpiDmIndent (Level);
    AcpiOsPrintf ("Interrupt (%s, %s, %s, %s",
        AcpiGbl_ConsumeDecode [(Resource->Exx.Flags & 1)],
        AcpiGbl_HEDecode [(Resource->Exx.Flags >> 1) & 1],
        AcpiGbl_LLDecode [(Resource->Exx.Flags >> 2) & 1],
        AcpiGbl_SHRDecode [(Resource->Exx.Flags >> 3) & 1]);

    /*
     * Optional fields:
     * If ResourceSourceIndex (byte) exists, ResourceSource (string) must also
     * (from ACPI specification)
     */
    if (Resource->Exx.Length > (UINT16) (4 * Resource->Exx.TableLength) + 3)
    {
        /* Get a pointer past the interrupt values */

        Rover = ((UINT8 *) Resource) + ((4 * Resource->Exx.TableLength) + 5);

        /* Resource Index */
        /* Resource Source */

        AcpiOsPrintf (", 0x%X, \"%s\"", (UINT32) Rover[0], (char *) &Rover[1]);
    }

    AcpiOsPrintf (")\n");
    AcpiDmIndent (Level);
    AcpiOsPrintf ("{\n");
    for (i = 0; i < Resource->Exx.TableLength; i++)
    {
        AcpiDmIndent (Level + 1);
        AcpiOsPrintf ("0x%8.8X,\n", (UINT32) Resource->Exx.InterruptNumber[i]);
    }

    AcpiDmIndent (Level);
    AcpiOsPrintf ("}\n");
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmVendorLargeDescriptor
 *
 * PARAMETERS:  Resource            - Pointer to the resource descriptor
 *              Length              - Length of the descriptor in bytes
 *              Level               - Current source code indentation level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decode a Vendor Large descriptor
 *
 ******************************************************************************/

void
AcpiDmVendorLargeDescriptor (
    ASL_RESOURCE_DESC       *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    AcpiOsPrintf ("VendorLong ()\n");
    AcpiDmIndent (Level);

    AcpiOsPrintf ("{\n");

    AcpiDmDisasmByteList (Level + 1, (UINT8 *) Resource->Lgv.VendorDefined, Length);
    AcpiDmIndent (Level);
    AcpiOsPrintf ("}\n");
}

#endif

