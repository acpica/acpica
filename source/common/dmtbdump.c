/******************************************************************************
 *
 * Module Name: dmtbdump - Dump ACPI data tables that contain no AML code
 *              $Revision: 1.1 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2006, Intel Corp.
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
#include "actables.h"

/* This module used for application-level code only */

#define _COMPONENT          ACPI_CA_DISASSEMBLER
        ACPI_MODULE_NAME    ("dmtbdump")


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDumpRsdp
 *
 * PARAMETERS:  Table               - An RSDP
 *
 * RETURN:      None
 *
 * DESCRIPTION: Format the contents of an RSDP
 *
 ******************************************************************************/

void
AcpiDmDumpRsdp (
    ACPI_TABLE_HEADER       *Table)
{

    AcpiDmDumpTable (sizeof (RSDP_DESCRIPTOR), 0, Table, AcpiDmTableInfoRsdp1);

    if (((RSDP_DESCRIPTOR *) Table)->Revision > 0)
    {
        AcpiDmDumpTable (sizeof (RSDP_DESCRIPTOR), 0, Table, AcpiDmTableInfoRsdp2);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDumpRsdt
 *
 * PARAMETERS:  Table               - An RSDT
 *
 * RETURN:      None
 *
 * DESCRIPTION: Format the contents of an RSDT
 *
 ******************************************************************************/

void
AcpiDmDumpRsdt (
    ACPI_TABLE_HEADER       *Table)
{
    UINT32                  *Array;
    UINT32                  TableCount;
    UINT32                  Offset;
    UINT32                  i;


    /* Point to start of table array */

    Array = ((RSDT_DESCRIPTOR *) Table)->TableOffsetEntry;
    Offset = sizeof (ACPI_TABLE_HEADER);

    /* RSDT uses 32-bit pointers */

    TableCount = (Table->Length - sizeof (ACPI_TABLE_HEADER)) / sizeof (UINT32);

    for (i = 0; i < TableCount; i++)
    {
        AcpiDmLineHeader2 (Offset, "ACPI Table", i);
        AcpiOsPrintf ("%8.8X\n", ACPI_GET32 (Array));
        Offset += sizeof (UINT32);
        Array++;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDumpXsdt
 *
 * PARAMETERS:  Table               - An XSDT
 *
 * RETURN:      None
 *
 * DESCRIPTION: Format the contents of an XSDT
 *
 ******************************************************************************/

void
AcpiDmDumpXsdt (
    ACPI_TABLE_HEADER       *Table)
{
    UINT64                  *Array; 
    UINT32                  TableCount;
    UINT32                  Offset;
    UINT32                  i;


    /* Point to start of table array */

    Array = ((XSDT_DESCRIPTOR *) Table)->TableOffsetEntry;
    Offset = sizeof (ACPI_TABLE_HEADER);

    /* XSDT uses 64-bit pointers */

    TableCount = (Table->Length - sizeof (ACPI_TABLE_HEADER)) / sizeof (UINT64);

    for (i = 0; i < TableCount; i++)
    {
        AcpiDmLineHeader2 (Offset, "ACPI Table", i);
        AcpiOsPrintf ("%8.8X%8.8X\n", ACPI_FORMAT_UINT64 (ACPI_GET64 (Array)));
        Offset += sizeof (UINT64);
        Array++;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDumpFadt
 *
 * PARAMETERS:  Table               - An FADT
 *
 * RETURN:      None
 *
 * DESCRIPTION: Format the contents of an FADT
 *
 ******************************************************************************/

void
AcpiDmDumpFadt (
    ACPI_TABLE_HEADER       *Table)
{

    /* Common ACPI 1.0 portion of FADT */

    AcpiDmDumpTable (Table->Length, 0, Table, AcpiDmTableInfoFadt1);

    /* Check for ACPI 2.0+ extended data */

    if (Table->Length > sizeof (FADT_DESCRIPTOR_REV1))
    {
        AcpiDmDumpTable (Table->Length, 0, Table, AcpiDmTableInfoFadt2);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDumpSrat
 *
 * PARAMETERS:  Table               - An SRAT
 *
 * RETURN:      None
 *
 * DESCRIPTION: Format the contents of an SRAT
 *
 ******************************************************************************/

void
AcpiDmDumpSrat (
    ACPI_TABLE_HEADER       *Table)
{
    UINT32                  Offset = sizeof (SYSTEM_RESOURCE_AFFINITY);
    STATIC_RESOURCE_ALLOC   *SubTable;


    SubTable = (STATIC_RESOURCE_ALLOC *) (((UINT8 *) Table) + Offset);
    while (Offset < Table->Length)
    {
        switch (SubTable->Type)
        {
        case SRAT_CPU_AFFINITY:
            AcpiDmDumpTable (Table->Length, Offset, SubTable, AcpiDmTableInfoSrat0);
            break;

        case SRAT_MEMORY_AFFINITY:
            AcpiDmDumpTable (Table->Length, Offset, SubTable, AcpiDmTableInfoSrat1);
            break;

        default:
            AcpiOsPrintf ("Unknown SRAT subtable type %X\n", SubTable->Type);
            return;
        }

        /* Point to next sub-table */

        AcpiOsPrintf ("\n");
        Offset += SubTable->Length;
        SubTable = (STATIC_RESOURCE_ALLOC *) (
            ((UINT8 *) SubTable) + SubTable->Length);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDumpSlit
 *
 * PARAMETERS:  Table               - An SLIT
 *
 * RETURN:      None
 *
 * DESCRIPTION: Format the contents of an SLIT
 *
 ******************************************************************************/

void
AcpiDmDumpSlit (
    ACPI_TABLE_HEADER       *Table)
{
    UINT32                  Offset = sizeof (SYSTEM_LOCALITY_INFO);
    UINT8                   *Row;
    UINT64                  Localities;
    UINT64                  i;
    UINT64                  j;


    AcpiDmDumpTable (Table->Length, 0, Table, AcpiDmTableInfoSlit);

    Localities = ((SYSTEM_LOCALITY_INFO *) Table)->LocalityCount;
    Row = (UINT8 *) ((SYSTEM_LOCALITY_INFO *) Table)->Entry;
    
    /* Display the Locality NxN Matrix */

    for (i = 0; i < Localities; i++)
    {
        /* Display one row of the matrix */

        AcpiDmLineHeader2 (Offset, "Locality", (UINT32) i);
        for  (j = 0; j < Localities; j++)
        {
            /* Check for beyond EOT */

            if (Offset >= Table->Length)
            {
                AcpiOsPrintf ("\n**** Not enough room in table for all localities\n");
                return;
            }

            AcpiOsPrintf ("%2.2X ", Row[j]);
            Offset++;

            /* Display up to 16 bytes per output row */

            if (j && (((j+1) % 16) == 0))
            {
                AcpiOsPrintf ("\n");
                AcpiDmLineHeader (Offset, "");
            }
        }

        /* Point to next row */

        AcpiOsPrintf ("\n");
        Row += Localities;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDumpMcfg
 *
 * PARAMETERS:  Table               - An MCFG Table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Format the contents of an MCFG table
 *
 ******************************************************************************/

void
AcpiDmDumpMcfg (
    ACPI_TABLE_HEADER       *Table)
{
    UINT32                  Offset = sizeof (ACPI_TABLE_MCFG);
    ACPI_MCFG_ALLOCATION    *SubTable;


    SubTable = (ACPI_MCFG_ALLOCATION *) (((UINT8 *) Table) + Offset);
    while (Offset < Table->Length)
    {
        if (Offset + sizeof (ACPI_MCFG_ALLOCATION) > Table->Length)
        {
            AcpiOsPrintf ("Warning: there are %d invalid trailing bytes\n",
                sizeof (ACPI_MCFG_ALLOCATION) - (Offset - Table->Length));
            return;
        }

        AcpiDmDumpTable (Table->Length, Offset, SubTable, AcpiDmTableInfoMcfg);

        /* Point to next sub-table */

        SubTable = (ACPI_MCFG_ALLOCATION *) (
            ((UINT8 *) SubTable) + sizeof (ACPI_MCFG_ALLOCATION));
        Offset += sizeof (ACPI_MCFG_ALLOCATION);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDumpMadt
 *
 * PARAMETERS:  Table               - An MADT
 *
 * RETURN:      None
 *
 * DESCRIPTION: Format the contents of an MADT. This table type consists
 *              of an open-ended number of subtables.
 *
 ******************************************************************************/

void
AcpiDmDumpMadt (
    ACPI_TABLE_HEADER       *Table)
{
    APIC_HEADER             *SubTable;
    UINT32                  Length = Table->Length;
    UINT32                  Offset = sizeof (MULTIPLE_APIC_TABLE);


    AcpiDmDumpTable (Length, 0, Table, AcpiDmTableInfoMadt);

    SubTable = (APIC_HEADER *) (((UINT8 *) Table) + Offset);
    while (Offset < Table->Length)
    {
        AcpiOsPrintf ("\n");
        AcpiDmDumpTable (Length, Offset, SubTable, AcpiDmTableInfoMadtHdr);

        switch (SubTable->Type)
        {
        case APIC_PROCESSOR:
            AcpiDmDumpTable (Length, Offset, SubTable, AcpiDmTableInfoMadt0);
            break;
        case APIC_IO:
            AcpiDmDumpTable (Length, Offset, SubTable, AcpiDmTableInfoMadt1);
            break;
        case APIC_XRUPT_OVERRIDE:
            AcpiDmDumpTable (Length, Offset, SubTable, AcpiDmTableInfoMadt2);
            break;
        case APIC_NMI:
            AcpiDmDumpTable (Length, Offset, SubTable, AcpiDmTableInfoMadt3);
            break;
        case APIC_LOCAL_NMI:
            AcpiDmDumpTable (Length, Offset, SubTable, AcpiDmTableInfoMadt4);
            break;
        case APIC_ADDRESS_OVERRIDE:
            AcpiDmDumpTable (Length, Offset, SubTable, AcpiDmTableInfoMadt5);
            break;
        case APIC_IO_SAPIC:
            AcpiDmDumpTable (Length, Offset, SubTable, AcpiDmTableInfoMadt6);
            break;
        case APIC_LOCAL_SAPIC:
            AcpiDmDumpTable (Length, Offset, SubTable, AcpiDmTableInfoMadt7);
            break;
        case APIC_XRUPT_SOURCE:
            AcpiDmDumpTable (Length, Offset, SubTable, AcpiDmTableInfoMadt8);
            break;

        default:
            AcpiOsPrintf ("Unknown APIC subtable type %X\n", SubTable->Type);
            return;
        }

        /* Point to next sub-table */

        Offset += SubTable->Length;
        SubTable = (APIC_HEADER *) (((UINT8 *) SubTable) + SubTable->Length);
    }
}


