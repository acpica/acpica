/******************************************************************************
 *
 * Module Name: tbutils   - table utilities
 *              $Revision: 1.82 $
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

#define __TBXFACE_C__

#include "acpi.h"
#include "actables.h"

#define _COMPONENT          ACPI_TABLES
        ACPI_MODULE_NAME    ("tbutils")

/* Local prototypes */

static void
AcpiTbParseFadt (
    ACPI_NATIVE_UINT        TableIndex,
    UINT8                   Flags);

static void
AcpiTbConvertFadt (
    void);

static void
AcpiTbInstallTable (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT8                   Flags,
    char                    *Signature,
    ACPI_NATIVE_UINT        TableIndex);

static void inline
AcpiTbInitGenericAddress (
    ACPI_GENERIC_ADDRESS    *NewGasStruct,
    UINT8                   BitWidth,
    UINT64                  Address);


/* Table used for conversion of FADT to common format */

typedef struct acpi_fadt_conversion
{
    UINT8                   Target;
    UINT8                   Source;
    UINT8                   Length;

} ACPI_FADT_CONVERSION;

static ACPI_FADT_CONVERSION     FadtConversionTable[] =
{
    {ACPI_FADT_OFFSET (XPm1aEventBlock),    ACPI_FADT_OFFSET (Pm1aEventBlock),      ACPI_FADT_OFFSET (Pm1EventLength)},
    {ACPI_FADT_OFFSET (XPm1bEventBlock),    ACPI_FADT_OFFSET (Pm1bEventBlock),      ACPI_FADT_OFFSET (Pm1EventLength)},
    {ACPI_FADT_OFFSET (XPm1aControlBlock),  ACPI_FADT_OFFSET (Pm1aControlBlock),    ACPI_FADT_OFFSET (Pm1ControlLength)},
    {ACPI_FADT_OFFSET (XPm1bControlBlock),  ACPI_FADT_OFFSET (Pm1bControlBlock),    ACPI_FADT_OFFSET (Pm1ControlLength)},
    {ACPI_FADT_OFFSET (XPm2ControlBlock),   ACPI_FADT_OFFSET (Pm2ControlBlock),     ACPI_FADT_OFFSET (Pm2ControlLength)},
    {ACPI_FADT_OFFSET (XPmTimerBlock),      ACPI_FADT_OFFSET (PmTimerBlock),        ACPI_FADT_OFFSET (PmTimerLength)},
    {ACPI_FADT_OFFSET (XGpe0Block),         ACPI_FADT_OFFSET (Gpe0Block),           ACPI_FADT_OFFSET (Gpe0BlockLength)},
    {ACPI_FADT_OFFSET (XGpe1Block),         ACPI_FADT_OFFSET (Gpe1Block),           ACPI_FADT_OFFSET (Gpe1BlockLength)}
};

#define ACPI_FADT_CONVERSION_ENTRIES        (sizeof (FadtConversionTable) / sizeof (ACPI_FADT_CONVERSION))


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbPrintTableHeader
 *
 * PARAMETERS:  Address             - Table physical address
 *              Header              - Table header
 *
 * RETURN:      None
 *
 * DESCRIPTION: Print an ACPI table header. Special cases for FACS and RSDP.
 *
 ******************************************************************************/

void
AcpiTbPrintTableHeader (
    ACPI_PHYSICAL_ADDRESS   Address,
    ACPI_TABLE_HEADER       *Header)
{

    if (ACPI_COMPARE_NAME (Header->Signature, ACPI_SIG_FACS))
    {
        /* FACS only has signature and length fields of common table header */

        ACPI_INFO ((AE_INFO, "%4.4s @ 0x%p/0x%04X",
            Header->Signature, ACPI_CAST_PTR (void, Address), Header->Length));
    }
    else if (ACPI_COMPARE_NAME (Header->Signature, ACPI_SIG_RSDP))
    {
        /* RSDP has no common fields */

        ACPI_INFO ((AE_INFO, "RSDP @ 0x%p/0x%04X (v%3.3d %6.6s)",
            ACPI_CAST_PTR (void, Address),
            (((ACPI_TABLE_RSDP *) Header)->Revision > 0) ?
                    ((ACPI_TABLE_RSDP *) Header)->Length : 20,
            ((ACPI_TABLE_RSDP *) Header)->Revision,
            ((ACPI_TABLE_RSDP *) Header)->OemId));
    }
    else
    {
        /* Standard ACPI table with full common header */

        ACPI_INFO ((AE_INFO,
            "%4.4s @ 0x%p/0x%04X (v%3.3d %6.6s %8.8s 0x%08X %4.4s 0x%08X)",
            Header->Signature, ACPI_CAST_PTR (void, Address),
            Header->Length, Header->Revision, Header->OemId,
            Header->OemTableId, Header->OemRevision, Header->AslCompilerId,
            Header->AslCompilerRevision));
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbInitGenericAddress
 *
 * PARAMETERS:  NewGasStruct        - GAS struct to be initialized
 *              BitWidth            - Width of this register
 *              Address             - Address of the register
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize a GAS structure.
 *
 ******************************************************************************/

static void inline
AcpiTbInitGenericAddress (
    ACPI_GENERIC_ADDRESS    *NewGasStruct,
    UINT8                   BitWidth,
    UINT64                  Address)
{

    ACPI_MOVE_64_TO_64 (&NewGasStruct->Address, &Address);
    NewGasStruct->SpaceId = ACPI_ADR_SPACE_SYSTEM_IO;
    NewGasStruct->BitWidth = BitWidth;
    NewGasStruct->BitOffset = 0;
    NewGasStruct->AccessWidth = 0;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbValidateChecksum
 *
 * PARAMETERS:  Table               - ACPI table to verify
 *              Length              - Length of entire table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Verifies that the table checksums to zero. Optionally returns
 *              exception on bad checksum.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbVerifyChecksum (
    ACPI_TABLE_HEADER       *Table,
    UINT32                  Length)
{
    UINT8                   Checksum;


    /* Compute the checksum on the table */

    Checksum = AcpiTbChecksum (ACPI_CAST_PTR (UINT8, Table), Length);

    /* Checksum ok? (should be zero) */

    if (Checksum)
    {
        ACPI_WARNING ((AE_INFO,
            "Incorrect checksum in table [%4.4s] -  %2.2X, should be %2.2X",
            Table->Signature, Table->Checksum, (UINT8) (Table->Checksum - Checksum)));

#if (ACPI_CHECKSUM_ABORT)

        return (AE_BAD_CHECKSUM);
#endif
    }

    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbChecksum
 *
 * PARAMETERS:  Buffer          - Pointer to memory region to be checked
 *              Length          - Length of this memory region
 *
 * RETURN:      Checksum (UINT8)
 *
 * DESCRIPTION: Calculates circular checksum of memory region.
 *
 ******************************************************************************/

UINT8
AcpiTbChecksum (
    UINT8                   *Buffer,
    ACPI_NATIVE_UINT        Length)
{
    UINT8                   Sum = 0;
    UINT8                   *End = Buffer + Length;


    while (Buffer < End)
    {
        Sum = (UINT8) (Sum + *(Buffer++));
    }

    return Sum;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbConvertFadt
 *
 * PARAMETERS:  None, uses AcpiGbl_FADT
 *
 * RETURN:      None
 *
 * DESCRIPTION: Converts all versions of the FADT to a common internal format.
 *
 * NOTE:        AcpiGbl_FADT must be of size (ACPI_TABLE_FADT), and must contain
 *              a copy of the actual FADT.
 *
 * ACPICA will use the "X" fields of the FADT for all addresses.
 *
 * "X" fields are optional extensions to the original V1.0 fields. Even if
 * they are present in the structure, they can be optionally not used by
 * setting them to zero. Therefore, we must selectively expand V1.0 fields
 * if the corresponding X field is zero.
 *
 * For ACPI 1.0 FADTs, all address fields are expanded to the corresponding
 * "X" fields.
 *
 * For ACPI 2.0 FADTs, any "X" fields that are NULL are filled in by 
 * expanding the corresponding ACPI 1.0 field.
 *
 ******************************************************************************/

static void
AcpiTbConvertFadt (
    void)
{
    UINT8                       Pm1RegisterLength;
    ACPI_GENERIC_ADDRESS        *Target;
    ACPI_NATIVE_UINT            i;


    /* Expand the FACS and DSDT addresses as necessary */

    if (!AcpiGbl_FADT.XFacs)
    {
        AcpiGbl_FADT.XFacs = (UINT64) AcpiGbl_FADT.Facs;
    }

    if (!AcpiGbl_FADT.XDsdt)
    {
        AcpiGbl_FADT.XDsdt = (UINT64) AcpiGbl_FADT.Dsdt;
    }

    /*
     * Expand the V1.0 addresses to the "X" generic address structs,
     * as necessary.
     */
    for (i = 0; i < ACPI_FADT_CONVERSION_ENTRIES; i++)
    {
        Target = ACPI_ADD_PTR (
            ACPI_GENERIC_ADDRESS, &AcpiGbl_FADT, FadtConversionTable[i].Target);

        /* Expand only if the X target is null */

        if (!Target->Address)
        {
            AcpiTbInitGenericAddress (Target,
                *ACPI_ADD_PTR (UINT8, &AcpiGbl_FADT, FadtConversionTable[i].Length),
                *ACPI_ADD_PTR (UINT32, &AcpiGbl_FADT, FadtConversionTable[i].Source));
        }
    }

    /*
     * Calculate separate GAS structs for the PM1 Enable registers.
     * These addresses do not appear (directly) in the FADT, so it is 
     * useful to calculate them once, here.
     *
     * The PM event blocks are split into two register blocks, first is the
     * PM Status Register block, followed immediately by the PM Enable Register
     * block. Each is of length (Pm1EventLength/2)
     */
    Pm1RegisterLength = (UINT8) ACPI_DIV_2 (AcpiGbl_FADT.Pm1EventLength);

    /* PM1A is required */

    AcpiTbInitGenericAddress (&AcpiGbl_XPm1aEnable, Pm1RegisterLength,
        (AcpiGbl_FADT.XPm1aEventBlock.Address + Pm1RegisterLength));

    /* PM1B is optional; leave null if not present */

    if (AcpiGbl_FADT.XPm1bEventBlock.Address)
    {
        AcpiTbInitGenericAddress (&AcpiGbl_XPm1bEnable, Pm1RegisterLength,
            (AcpiGbl_FADT.XPm1bEventBlock.Address + Pm1RegisterLength));
    }

    /* Global FADT is the new common V2.0 FADT  */

    AcpiGbl_FADT.Header.Length = sizeof (ACPI_TABLE_FADT);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbInstallTable
 *
 * PARAMETERS:  Address                 - Physical address of DSDT or FACS
 *              Flags                   - Flags
 *              Signature               - Table signature, NULL if no need to
 *                                        match
 *              TableIndex              - Index into root table array
 *
 * RETURN:      None
 *
 * DESCRIPTION: Install an ACPI table into the global data structure.
 *
 ******************************************************************************/

static void
AcpiTbInstallTable (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT8                   Flags,
    char                    *Signature,
    ACPI_NATIVE_UINT        TableIndex)
{
    ACPI_TABLE_HEADER       *Table;


    if (!Address)
    {
        ACPI_ERROR ((AE_INFO, "Null physical address for ACPI table [%s]",
            Signature));
        return;
    }

    /* Map just the table header */

    Table = AcpiOsMapMemory (Address, sizeof (ACPI_TABLE_HEADER));
    if (!Table)
    {
        return;
    }

    /* If a particular signature is expected, signature must match */

    if (Signature && !ACPI_COMPARE_NAME (Table->Signature, Signature))
    {
        ACPI_ERROR ((AE_INFO, "Invalid signature 0x%X for ACPI table [%s]",
            *ACPI_CAST_PTR (UINT32, Table->Signature), Signature));
        goto UnmapAndExit;
    }

    /* Initialize the table entry */

    AcpiGbl_RootTableList.Tables[TableIndex].Address = Address;
    AcpiGbl_RootTableList.Tables[TableIndex].Length = Table->Length;
    AcpiGbl_RootTableList.Tables[TableIndex].Flags = Flags;

    ACPI_MOVE_32_TO_32 (
        &(AcpiGbl_RootTableList.Tables[TableIndex].Signature),
        Table->Signature);

    AcpiTbPrintTableHeader (Address, Table);

    if (TableIndex == ACPI_TABLE_INDEX_DSDT)
    {
        /* Global integer width is based upon revision of the DSDT */

        AcpiUtSetIntegerWidth (Table->Revision);
    }

UnmapAndExit:
    AcpiOsUnmapMemory (Table, sizeof (ACPI_TABLE_HEADER));
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbParseFadt
 *
 * PARAMETERS:  TableIndex          - Index for the FADT
 *              Flags               - Flags
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize the FADT, DSDT and FACS tables
 *              (FADT contains the addresses of the DSDT and FACS)
 *
 ******************************************************************************/

static void
AcpiTbParseFadt (
    ACPI_NATIVE_UINT        TableIndex,
    UINT8                   Flags)
{
    UINT32                  Length;
    ACPI_TABLE_HEADER       *Table;


    /*
     * Special case for the FADT because of multiple versions and the fact
     * that it contains pointers to both the DSDT and FACS tables.
     *
     * Get a local copy of the FADT and convert it to a common format
     * Map entire FADT, assumed to be smaller than one page.
     */
    Length = AcpiGbl_RootTableList.Tables[TableIndex].Length;

    Table = AcpiOsMapMemory (AcpiGbl_RootTableList.Tables[TableIndex].Address, Length);
    if (!Table)
    {
        return;
    }

    /*
     * Validate the FADT checksum before we copy the table. Ignore
     * checksum error as we want to try to get the DSDT and FACS.
     */
    (void) AcpiTbVerifyChecksum (Table, Length);

    /* Copy the entire FADT locally */

    ACPI_MEMSET (&AcpiGbl_FADT, sizeof (ACPI_TABLE_FADT), 0);

    ACPI_MEMCPY (&AcpiGbl_FADT, Table,
        ACPI_MIN (Length, sizeof (ACPI_TABLE_FADT)));
    AcpiOsUnmapMemory (Table, Length);

    /* Convert local FADT to the common internal format */

    AcpiTbConvertFadt ();

    /* Extract the DSDT and FACS tables from the FADT */

    AcpiTbInstallTable ((ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.XDsdt,
        Flags, ACPI_SIG_DSDT, ACPI_TABLE_INDEX_DSDT);

    AcpiTbInstallTable ((ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.XFacs,
        Flags, ACPI_SIG_FACS, ACPI_TABLE_INDEX_FACS);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbParseRootTable
 *
 * PARAMETERS:  Rsdp                    - Pointer to the RSDP
 *              Flags                   - Flags
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to parse the Root System Description
 *              Table (RSDT or XSDT)
 *
 * NOTE:        Tables are mapped (not copied) for efficiency. The FACS must
 *              be mapped and cannot be copied because it contains the actual
 *              memory location of the ACPI Global Lock.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbParseRootTable (
    ACPI_PHYSICAL_ADDRESS   RsdpAddress,
    UINT8                   Flags)
{
    ACPI_TABLE_RSDP         *Rsdp;
    ACPI_NATIVE_UINT        TableEntrySize;
    ACPI_NATIVE_UINT        i;
    UINT32                  TableCount;
    ACPI_TABLE_HEADER       *Table;
    ACPI_PHYSICAL_ADDRESS   Address;
    UINT32                  Length;
    UINT8                   *TableEntry;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (TbParseRootTable);


    /*
     * Map the entire RSDP and extract the address of the RSDT or XSDT
     */
    Rsdp = AcpiOsMapMemory (RsdpAddress, sizeof (ACPI_TABLE_RSDP));
    if (!Rsdp)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    AcpiTbPrintTableHeader (RsdpAddress, ACPI_CAST_PTR (ACPI_TABLE_HEADER, Rsdp));

    /* Differentiate between RSDT and XSDT root tables */

    if (Rsdp->Revision > 1 && Rsdp->XsdtPhysicalAddress)
    {
        /*
         * Root table is an XSDT (64-bit physical addresses). We must use the
         * XSDT if the revision is > 1 and the XSDT pointer is present, as per
         * the ACPI specification.
         */
        Address = (ACPI_PHYSICAL_ADDRESS) Rsdp->XsdtPhysicalAddress;
        TableEntrySize = sizeof (UINT64);
    }
    else
    {
        /* Root table is an RSDT (32-bit physical addresses) */

        Address = (ACPI_PHYSICAL_ADDRESS) Rsdp->RsdtPhysicalAddress;
        TableEntrySize = sizeof (UINT32);
    }

    /*
     * It is not possible to map more than one entry in some environments,
     * so unmap the RSDP here before mapping other tables
     */
    AcpiOsUnmapMemory (Rsdp, sizeof (ACPI_TABLE_RSDP));


    /* Map the RSDT/XSDT table header to get the full table length */

    Table = AcpiOsMapMemory (Address, sizeof (ACPI_TABLE_HEADER));
    if (!Table)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    AcpiTbPrintTableHeader (Address, Table);

    /* Get the length of the full table, verify length and map entire table */

    Length = Table->Length;
    AcpiOsUnmapMemory (Table, sizeof (ACPI_TABLE_HEADER));

    if (Length < sizeof (ACPI_TABLE_HEADER))
    {
        ACPI_ERROR ((AE_INFO, "Invalid length 0x%X in RSDT/XSDT", Length));
        return_ACPI_STATUS (AE_INVALID_TABLE_LENGTH);
    }

    Table = AcpiOsMapMemory (Address, Length);
    if (!Table)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Validate the root table checksum */

    Status = AcpiTbVerifyChecksum (Table, Length);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsUnmapMemory (Table, Length);
        return_ACPI_STATUS (Status);
    }

    /* Calculate the number of tables described in the root table */

    TableCount = (Table->Length - sizeof (ACPI_TABLE_HEADER)) / TableEntrySize;

    /*
     * First two entries in the table array are reserved for the DSDT and FACS,
     * which are not actually present in the RSDT/XSDT - they come from the FADT
     */
    TableEntry = ACPI_CAST_PTR (UINT8, Table) + sizeof (ACPI_TABLE_HEADER);
    AcpiGbl_RootTableList.Count = 2;

    /*
     * Initialize the root table array from the RSDT/XSDT
     */
    for (i = 0; i < TableCount; i++)
    {
        if (AcpiGbl_RootTableList.Count >= AcpiGbl_RootTableList.Size)
        {
            /* There is no more room in the root table array, attempt resize */

            Status = AcpiTbResizeRootTableList ();
            if (ACPI_FAILURE (Status))
            {
                ACPI_WARNING ((AE_INFO, "Truncating %u table entries!",
                    (unsigned) (AcpiGbl_RootTableList.Size - AcpiGbl_RootTableList.Count)));
                break;
            }
        }

        /*
         * Get the table physical address (32-bit for RSDT, 64-bit for XSDT)
         */
        if ((TableEntrySize == sizeof (UINT32)) ||
            (sizeof (ACPI_PHYSICAL_ADDRESS) == sizeof (UINT32)))
        {
            /*
             * 32-bit platform, RSDT: Move 32-bit to 32-bit
             * 32-bit platform, XSDT: Truncate 64-bit to 32-bit
             * 64-bit platform, RSDT: Expand 32-bit to 64-bit
             *
             * Note: Addresses are 32-bit aligned in both RSDT and XSDT
             */
            AcpiGbl_RootTableList.Tables[AcpiGbl_RootTableList.Count].Address =
                (ACPI_PHYSICAL_ADDRESS) (*ACPI_CAST_PTR (UINT32, TableEntry));
        }
        else
        {
            /*
             * 64-bit platform, XSDT: Move 64-bit to 64-bit
             *
             * Note: 64-bit addresses are only 32-bit aligned in the XSDT
             */
            ACPI_MOVE_64_TO_64 (
                &AcpiGbl_RootTableList.Tables[AcpiGbl_RootTableList.Count].Address,
                TableEntry);
        }

        TableEntry += TableEntrySize;
        AcpiGbl_RootTableList.Count++;
    }

    /*
     * It is not possible to map more than one entry in some environments,
     * so unmap the root table here before mapping other tables
     */
    AcpiOsUnmapMemory (Table, Length);

    /*
     * Complete the initialization of the root table array by examining
     * the header of each table
     */
    for (i = 2; i < AcpiGbl_RootTableList.Count; i++)
    {
        AcpiTbInstallTable (AcpiGbl_RootTableList.Tables[i].Address,
            Flags, NULL, i);

       /* Special case for FADT - get the DSDT and FACS */

        if (ACPI_COMPARE_NAME (
                &AcpiGbl_RootTableList.Tables[i].Signature, ACPI_SIG_FADT))
        {
            AcpiTbParseFadt (i, Flags);
        }
    }

    return_ACPI_STATUS (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiTbMap
 *
 * PARAMETERS:  Address             - Address to be mapped
 *              Length              - Length to be mapped
 *              Flags               - Logical or physical addressing mode
 *
 * RETURN:      Pointer to mapped region
 *
 * DESCRIPTION: Maps memory according to flag
 *
 *****************************************************************************/

void *
AcpiTbMap (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT32                  Length,
    UINT32                  Flags)
{

    if (Flags == ACPI_TABLE_ORIGIN_MAPPED)
    {
        return (AcpiOsMapMemory (Address, Length));
    }
    else
    {
        return (ACPI_CAST_PTR (void, Address));
    }
}


/******************************************************************************
 *
 * FUNCTION:    AcpiTbUnmap
 *
 * PARAMETERS:  Pointer             - To mapped region
 *              Length              - Length to be unmapped
 *              Flags               - Logical or physical addressing mode
 *
 * RETURN:      None
 *
 * DESCRIPTION: Unmaps memory according to flag
 *
 *****************************************************************************/

void
AcpiTbUnmap (
    void                    *Pointer,
    UINT32                  Length,
    UINT32                  Flags)
{

    if (Flags == ACPI_TABLE_ORIGIN_MAPPED)
    {
        AcpiOsUnmapMemory (Pointer, Length);
    }
}


