/******************************************************************************
 *
 * Module Name: dmtable - Support for ACPI tables that contain no AML code
 *              $Revision: 1.2 $
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
        ACPI_MODULE_NAME    ("dmtable")

/* Local Prototypes */

static ACPI_DMTABLE_DATA *
AcpiDmMatchSignature (
    char                    *Signature);

static void
AcpiDmCheckAscii (
    UINT8                   *Target,
    UINT32                  Count);


/*******************************************************************************
 *
 * ACPI Table Data, indexed by signature.
 *
 * Simple tables have only a TableInfo structure, complex tables have a handler.
 * Table must be NULL terminated
 *
 ******************************************************************************/

ACPI_DMTABLE_DATA           AcpiDmTableData[] =
{
    {ACPI_SIG_MADT,     NULL,                       AcpiDmDumpMadt},
    {ACPI_SIG_BOOT,     AcpiDmTableInfoBoot,        NULL},
    {ACPI_SIG_DBGP,     AcpiDmTableInfoDbgp,        NULL},
    {ACPI_SIG_ECDT,     AcpiDmTableInfoEcdt,        NULL},
    {ACPI_SIG_FADT,     NULL,                       AcpiDmDumpFadt},
    {ACPI_SIG_HPET,     AcpiDmTableInfoHpet,        NULL},
    {ACPI_SIG_MCFG,     NULL,                       AcpiDmDumpMcfg},
    {ACPI_SIG_RSDP,     NULL,                       AcpiDmDumpRsdp},
    {ACPI_SIG_RSDT,     NULL,                       AcpiDmDumpRsdt},
    {ACPI_SIG_SBST,     AcpiDmTableInfoSbst,        NULL},
    {ACPI_SIG_SLIT,     NULL,                       AcpiDmDumpSlit},
    {ACPI_SIG_SPCR,     AcpiDmTableInfoSpcr,        NULL},
    {ACPI_SIG_SPMI,     AcpiDmTableInfoSpmi,        NULL},
    {ACPI_SIG_SRAT,     NULL,                       AcpiDmDumpSrat},
    {ACPI_SIG_TCPA,     AcpiDmTableInfoTcpa,        NULL},
    {ACPI_SIG_WDRT,     AcpiDmTableInfoWdrt,        NULL},
    {ACPI_SIG_XSDT,     NULL,                       AcpiDmDumpXsdt},
    {NULL,              NULL,                       NULL}
};


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmMatchSignature
 *
 * PARAMETERS:  Signature           - ACPI signature (4 chars) to match
 *
 * RETURN:      Pointer to a valid ACPI_DMTABLE_DATA. Null if no match found.
 *
 * DESCRIPTION: Find a match in the global table of supported ACPI tables
 *
 ******************************************************************************/

static ACPI_DMTABLE_DATA *
AcpiDmMatchSignature (
    char                    *Signature)
{
    ACPI_DMTABLE_DATA       *TableData;


    for (TableData = AcpiDmTableData; TableData->Signature; TableData++)
    {
        if (ACPI_COMPARE_NAME (Signature, TableData->Signature))
        {
            return (TableData);
        }
    }

    return (NULL);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDumpDataTable
 *
 * PARAMETERS:  Table               - An ACPI table
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Format the contents of an ACPI data table (any table other
 *              than an SSDT or DSDT that does not contain executable AML code)
 *
 ******************************************************************************/

void
AcpiDmDumpDataTable (
    ACPI_TABLE_HEADER       *Table)
{
    ACPI_DMTABLE_DATA       *TableData;


    /* Ignore tables that contain AML */

    if (AcpiUtIsAmlTable (Table))
    {
        return;
    }

    /*
     * Handle tables that don't use the common ACPI table header structure.
     * Currently, these are the FACS and RSDP.
     */
    if (ACPI_COMPARE_NAME (Table->Signature, "FACS"))
    {
        AcpiDmDumpTable (Table->Length, 0, Table, AcpiDmTableInfoFacs);
        return;
    }
    else if (ACPI_COMPARE_NAME (Table->Signature, "RSD "))
    {
        AcpiDmDumpRsdp (Table);
        return;
    }

    /*
     * Any other tables must use the common ACPI table header, dump it now
     */
    AcpiDmDumpTable (Table->Length, 0, Table, AcpiDmTableInfoHeader);
    AcpiOsPrintf ("\n");

    /* Match signature and dispatch appropriately */

    TableData = AcpiDmMatchSignature (Table->Signature);
    if (!TableData)
    {
        AcpiOsPrintf ("\n**** Unsupported ACPI table type [%4.4s]\n\n", Table->Signature);

        /* TBD: We might want to dump the contents of the unknown table here */
    }
    else if (TableData->TableHandler)
    {
        /* Complex table, has a handler */

        TableData->TableHandler (Table);
    }
    else if (TableData->TableInfo)
    {
        /* Simple table, just walk the info table */

        AcpiDmDumpTable (Table->Length, 0, Table, TableData->TableInfo);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmLineHeader
 *
 * PARAMETERS:  Offset              - Current byte offset, from table start
 *              Name                - Name of this field
 *
 * RETURN:      None
 *
 * DESCRIPTION: Utility routines for formatting output lines. Displays the
 *              current table offset in hex and decimal, and the table field
 *              name.
 *
 ******************************************************************************/

void
AcpiDmLineHeader (
    UINT32                  Offset,
    char                    *Name)
{
    AcpiOsPrintf ("[%3.3Xh %3.3d] %28s : ", Offset, Offset, Name);
}

void
AcpiDmLineHeader2 (
    UINT32                  Offset,
    char                    *Name,
    UINT32                  Value)
{
    AcpiOsPrintf ("[%3.3Xh %3.3d] %23s % 4d : ", Offset, Offset, Name, Value);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDumpTable
 *
 * PARAMETERS:  TableLength         - Length of the entire ACPI table
 *              TableOffset         - Starting offset within the table for this
 *                                    sub-descriptor
 *              Table               - The ACPI table
 *              Info                - Info table for this ACPI table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display ACPI table contents by walking the Info table.
 *
 ******************************************************************************/

void
AcpiDmDumpTable (
    UINT32                  TableLength,
    UINT32                  TableOffset,
    void                    *Table,
    ACPI_DMTABLE_INFO       *Info)
{
    UINT8                   *Target;
    char                    *Subname;
    UINT32                  CurrentOffset;
    UINT8                   Temp8;


    if (!Info)
    {
        AcpiOsPrintf ("Display not implemented\n");
        return;
    }

    /* Walk entire Info table; Null name terminates */

    for (; Info->Name; Info++)
    {
        Target = ACPI_ADD_PTR (UINT8, Table, Info->Offset);
        CurrentOffset = TableOffset + Info->Offset;

        /* Check for beyond EOT */

        if (CurrentOffset >= TableLength)
        {
            return;
        }

        /* Start a new line and decode the opcode */

        AcpiDmLineHeader (CurrentOffset, Info->Name);

        switch (Info->Opcode)
        {
        /* Single-bit Flag fields. Note: Opcode is bit position */

        case ACPI_DMT_FLAG0:
        case ACPI_DMT_FLAG1:
        case ACPI_DMT_FLAG2:
        case ACPI_DMT_FLAG3:
        case ACPI_DMT_FLAG4:
        case ACPI_DMT_FLAG5:
        case ACPI_DMT_FLAG6:
        case ACPI_DMT_FLAG7:

            AcpiOsPrintf ("%1.1X\n", ((*Target) >> Info->Opcode) & 0x01);
            break;

        /* 2-bit Flag fields */

        case ACPI_DMT_FLAGS0:

            AcpiOsPrintf ("%1.1X\n", (*Target) & 0x03);
            break;

        case ACPI_DMT_FLAGS2:

            AcpiOsPrintf ("%1.1X\n", ((*Target) >> 2) & 0x03);
            break;

        /* Standard Data Types */

        case ACPI_DMT_UINT8:

            AcpiOsPrintf ("%2.2X\n", *Target);
            break;

        case ACPI_DMT_UINT16:

            AcpiOsPrintf ("%4.4X\n", ACPI_GET16 (Target));
            break;

        case ACPI_DMT_UINT24:

            AcpiOsPrintf ("%2.2X%2.2X%2.2X\n",
                *Target, *(Target + 1), *(Target + 2));
            break;

        case ACPI_DMT_UINT32:

            AcpiOsPrintf ("%8.8X\n", ACPI_GET32 (Target));
            break;

        case ACPI_DMT_UINT64:

            AcpiOsPrintf ("%8.8X%8.8X\n",
                ACPI_FORMAT_UINT64 (ACPI_GET64 (Target)));
            break;

        case ACPI_DMT_STRING:

            AcpiOsPrintf ("%s\n", (char *) Target);
            break;

        /* Fixed length ASCII name fields */

        case ACPI_DMT_NAME4:

            AcpiDmCheckAscii (Target, 4);
            AcpiOsPrintf ("%4.4s\n", Target);
            break;

        case ACPI_DMT_NAME6:

            AcpiDmCheckAscii (Target, 6);
            AcpiOsPrintf ("%6.6s\n", Target);
            break;

        case ACPI_DMT_NAME8:

            AcpiDmCheckAscii (Target, 8);
            AcpiOsPrintf ("%8.8s\n", Target);
            break;

        /* Special Data Types */

        case ACPI_DMT_CHKSUM:

            /* Checksum, validate and compute new one if necessary */

            AcpiOsPrintf ("%2.2X", *Target);
            Temp8 = AcpiTbGenerateChecksum (Table,
                        ((ACPI_TABLE_HEADER *)Table)->Length);
            if (Temp8)
            {
                ((ACPI_TABLE_HEADER *)Table)->Checksum = 0;
                Temp8 = (UINT8) (0 - AcpiTbGenerateChecksum (Table,
                            ((ACPI_TABLE_HEADER *)Table)->Length));

                AcpiOsPrintf ("       /* Incorrect checksum, should be %2.2X */",
                    Temp8);
            }
            AcpiOsPrintf ("\n");
            break;

        case ACPI_DMT_SPACEID:

            /* Address Space ID */
            /* TBD: probably can use the global lookup table on these */

            AcpiOsPrintf ("%2.2X ", *Target);
            switch (*Target)
            {
            case ACPI_ADR_SPACE_SYSTEM_MEMORY:
                AcpiOsPrintf ("(System Memory)\n");
                break;
            case ACPI_ADR_SPACE_SYSTEM_IO:
                AcpiOsPrintf ("(System I/O)\n");
                break;
            default:
                AcpiOsPrintf ("\n");
                break;
            }
            break;

        case ACPI_DMT_GAS:

            /* Generic Address Structure */

            AcpiOsPrintf ("<Generic Address Structure>\n");
            AcpiDmDumpTable (((ACPI_TABLE_HEADER *)Table)->Length,
                CurrentOffset, Target, AcpiDmTableInfoGas);
            break;

        case ACPI_DMT_APIC:

            /* MADT subtable types */

            switch (*Target)
            {
            case APIC_PROCESSOR:
                Subname = "Processor Local APIC";
                break;
            case APIC_IO:
                Subname = "I/O APIC";
                break;
            case APIC_XRUPT_OVERRIDE:
                Subname = "Interrupt Source Override";
                break;
            case APIC_NMI:
                Subname = "NMI Source";
                break;
            case APIC_LOCAL_NMI:
                Subname = "Local APIC NMI";
                break;
            case APIC_ADDRESS_OVERRIDE:
                Subname = "Local APIC Address Override";
                break;
            case APIC_IO_SAPIC:
                Subname = "I/O SAPIC";
                break;
            case APIC_LOCAL_SAPIC:
                Subname = "Local SAPIC";
                break;
            case APIC_XRUPT_SOURCE:
                Subname = "Platform Interrupt Sources";
                break;
            default:
                Subname = "Unknown SubTable Type";
                break;
            }
            AcpiOsPrintf ("%2.2X <%s>\n", *Target, Subname);
            break;

        case ACPI_DMT_SRAT:

            /* SRAT subtable types */

            switch (*Target)
            {
            case SRAT_CPU_AFFINITY:
                Subname = "Processor Local APIC/SAPIC Affinity";
                break;
            case SRAT_MEMORY_AFFINITY:
                Subname = "Memory Affinity";
                break;
            default:
                Subname = "Unknown SubTable Type";
                break;
            }
            AcpiOsPrintf ("%2.2X <%s>\n", *Target, Subname);
            break;

        case ACPI_DMT_EXIT:
            return;

        default:
            AcpiOsPrintf ("**** Invalid table opcode [%X] ****\n", Info->Opcode);
            return;
        }
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmCheckAscii
 *
 * PARAMETERS:  Name                - Ascii string
 *              Count               - Number of characters to check
 *
 * RETURN:      None
 *
 * DESCRIPTION: Ensure that the requested number of characters are printable
 *              Ascii characters. Sets non-printable and null chars to <space>.
 *
 ******************************************************************************/

static void
AcpiDmCheckAscii (
    UINT8                   *Name,
    UINT32                  Count)
{
    UINT32                  i;


    for (i = 0; i < Count; i++)
    {
        if (!Name[i] || !isprint (Name[i]))
        {
            Name[i] = ' ';
        }
    }
}
