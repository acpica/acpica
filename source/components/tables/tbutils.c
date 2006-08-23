/******************************************************************************
 *
 * Module Name: tbutils   - table utilities
 *              $Revision: 1.80 $
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
    ACPI_TABLE_FADT         *Fadt,
    UINT8                   Flags);

static void inline
AcpiTbInitGenericAddress (
    ACPI_GENERIC_ADDRESS    *NewGasStruct,
    UINT8                   BitWidth,
    ACPI_PHYSICAL_ADDRESS   Address);


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbPrintTableHeader
 *
 * PARAMETERS:  Address             - Table physical address
 *              Header              - Table header
 *
 * RETURN:      None
 *
 * DESCRIPTION: Print an ACPI table header
 *
 ******************************************************************************/

void
AcpiTbPrintTableHeader (
    ACPI_PHYSICAL_ADDRESS   Address,
    ACPI_TABLE_HEADER       *Header)
{

    ACPI_INFO ((AE_INFO,
        "%4.4s @ 0x%p Length 0x%04X (v%3.3d %6.6s %8.8s 0x%08X %4.4s 0x%08X)",
        Header->Signature, ACPI_CAST_PTR (void, Address),
        Header->Length, Header->Revision, Header->OemId,
        Header->OemTableId, Header->OemRevision, Header->AslCompilerId,
        Header->AslCompilerRevision));
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
    ACPI_PHYSICAL_ADDRESS   Address)
{

    ACPI_STORE_ADDRESS (NewGasStruct->Address, Address);
    NewGasStruct->SpaceId = ACPI_ADR_SPACE_SYSTEM_IO;
    NewGasStruct->BitWidth = BitWidth;
    NewGasStruct->BitOffset = 0;
    NewGasStruct->AccessWidth = 0;
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
 * PARAMETERS:  Fadt                - FADT table to be converted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Converts a BIOS supplied ACPI 1.0 FADT to a local
 *              ACPI 2.0 FADT. If the BIOS supplied a 2.0 FADT then it is simply
 *              copied to the local FADT.  The ACPI CA software uses this
 *              local FADT. Thus a significant amount of special #ifdef
 *              type codeing is saved.
 *
 ******************************************************************************/

void
AcpiTbConvertFadt (
    ACPI_TABLE_FADT         *Fadt)
{

    /*
     * Convert table pointers to 64-bit fields
     */
    if (!AcpiGbl_FADT.XFacs)
    {
        AcpiGbl_FADT.XFacs = (UINT64) AcpiGbl_FADT.Facs;
    }

    if (!AcpiGbl_FADT.XDsdt)
    {
        AcpiGbl_FADT.XDsdt = (UINT64) AcpiGbl_FADT.Dsdt;
    }

    /*
     * Convert the V1.0 block addresses to V2.0 GAS structures
     */
    AcpiTbInitGenericAddress (&AcpiGbl_FADT.XPm1aEventBlock,
        AcpiGbl_FADT.Pm1EventLength,
        (ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.Pm1aEventBlock);
    AcpiTbInitGenericAddress (&AcpiGbl_FADT.XPm1bEventBlock,
        AcpiGbl_FADT.Pm1EventLength,
        (ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.Pm1bEventBlock);
    AcpiTbInitGenericAddress (&AcpiGbl_FADT.XPm1aControlBlock,
        AcpiGbl_FADT.Pm1ControlLength,
        (ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.Pm1aControlBlock);
    AcpiTbInitGenericAddress (&AcpiGbl_FADT.XPm1bControlBlock,
        AcpiGbl_FADT.Pm1ControlLength,
        (ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.Pm1bControlBlock);
    AcpiTbInitGenericAddress (&AcpiGbl_FADT.XPm2ControlBlock,
        AcpiGbl_FADT.Pm2ControlLength,
        (ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.Pm2ControlBlock);
    AcpiTbInitGenericAddress (&AcpiGbl_FADT.XPmTimerBlock,
        AcpiGbl_FADT.PmTimerLength,
        (ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.PmTimerBlock);
    AcpiTbInitGenericAddress (&AcpiGbl_FADT.XGpe0Block, 0,
        (ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.Gpe0Block);
    AcpiTbInitGenericAddress (&AcpiGbl_FADT.XGpe1Block, 0,
        (ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.Gpe1Block);

    /*
     * Create separate GAS structs for the PM1 Enable registers
     */
    AcpiTbInitGenericAddress (&AcpiGbl_XPm1aEnable,
        (UINT8) ACPI_DIV_2 (AcpiGbl_FADT.Pm1EventLength),
        (ACPI_PHYSICAL_ADDRESS)
        (ACPI_GET_ADDRESS
            (AcpiGbl_FADT.XPm1aEventBlock.Address) +
            ACPI_DIV_2 (AcpiGbl_FADT.Pm1EventLength)));

    /*
     * PM1B is optional; leave null if not present
     */
    if (ACPI_GET_ADDRESS (AcpiGbl_FADT.XPm1bEventBlock.Address))
    {
        AcpiTbInitGenericAddress (&AcpiGbl_XPm1bEnable,
            (UINT8) ACPI_DIV_2 (AcpiGbl_FADT.Pm1EventLength),
            (ACPI_PHYSICAL_ADDRESS)
                (ACPI_GET_ADDRESS (AcpiGbl_FADT.XPm1bEventBlock.Address) +
                    ACPI_DIV_2 (AcpiGbl_FADT.Pm1EventLength)));
    }

    /* Global FADT is the new common V2.0 FADT  */

    AcpiGbl_FADT.Header.Length = sizeof (ACPI_TABLE_FADT);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbParseFadt
 *
 * PARAMETERS:  Fadt                - Pointer to FADT table
 *              Flags               - Flags
 *
 * RETURN:      none
 *
 * DESCRIPTION: This function is called to initialise the FADT, DSDT and FACS
 *              tables (FADT contains the addresses of the DSDT and FACS)
 *
 ******************************************************************************/

static void
AcpiTbParseFadt (
    ACPI_TABLE_FADT         *Fadt,
    UINT8                   Flags)
{
    ACPI_PHYSICAL_ADDRESS   DsdtAddress = (ACPI_PHYSICAL_ADDRESS) Fadt->XDsdt;
    ACPI_PHYSICAL_ADDRESS   FacsAddress = (ACPI_PHYSICAL_ADDRESS) Fadt->XFacs;
    ACPI_TABLE_HEADER       *Table;


    if (!DsdtAddress)
    {
        goto NoDsdt;
    }

    Table = AcpiOsMapMemory (DsdtAddress, sizeof (ACPI_TABLE_HEADER));
    if (!Table)
    {
        goto NoDsdt;
    }

    /* Initialize the DSDT table */

    ACPI_MOVE_32_TO_32 (
        &(AcpiGbl_RootTableList.Tables[ACPI_TABLE_INDEX_DSDT].Signature),
        ACPI_SIG_DSDT);

    AcpiGbl_RootTableList.Tables[ACPI_TABLE_INDEX_DSDT].Address = DsdtAddress;
    AcpiGbl_RootTableList.Tables[ACPI_TABLE_INDEX_DSDT].Length = Table->Length;
    AcpiGbl_RootTableList.Tables[ACPI_TABLE_INDEX_DSDT].Flags = Flags;

    AcpiTbPrintTableHeader (DsdtAddress, Table);

    /* Global integer width is based upon revision of the DSDT */

    AcpiUtSetIntegerWidth (Table->Revision);
    AcpiOsUnmapMemory (Table, sizeof (ACPI_TABLE_HEADER));

NoDsdt:
    if (!FacsAddress)
    {
        return;
    }

    Table = AcpiOsMapMemory (FacsAddress, sizeof (ACPI_TABLE_HEADER));
    if (!Table)
    {
        return;
    }

    /* Initialize the FACS table */

    ACPI_MOVE_32_TO_32 (
        &(AcpiGbl_RootTableList.Tables[ACPI_TABLE_INDEX_FACS].Signature),
        ACPI_SIG_FACS);

    AcpiGbl_RootTableList.Tables[ACPI_TABLE_INDEX_FACS].Address = FacsAddress;
    AcpiGbl_RootTableList.Tables[ACPI_TABLE_INDEX_FACS].Length = Table->Length;
    AcpiGbl_RootTableList.Tables[ACPI_TABLE_INDEX_FACS].Flags = Flags;

    ACPI_INFO ((AE_INFO, "%4.4s @ 0x%p",
        Table->Signature, ACPI_CAST_PTR (void, FacsAddress)));

    AcpiOsUnmapMemory (Table, sizeof (ACPI_TABLE_HEADER));
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
    ACPI_TABLE_RSDP         *Rsdp,
    UINT8                   Flags)
{
    ACPI_TABLE_HEADER       *Table;
    ACPI_PHYSICAL_ADDRESS   Address;
    UINT32                  Length;
    UINT8                   *TableEntry;
    ACPI_NATIVE_UINT        i;
    ACPI_NATIVE_UINT        PointerSize;
    UINT32                  TableCount;
    UINT8                   Checksum;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (TbParseRootTable);


    /* Differentiate between RSDT and XSDT root tables */

    if (Rsdp->Revision > 1 && Rsdp->XsdtPhysicalAddress)
    {
        /*
         * Root table is an XSDT (64-bit physical addresses). We must use the
         * XSDT if the revision is > 1 and the XSDT pointer is present, as per
         * the ACPI specification.
         */
        Address = (ACPI_NATIVE_UINT) Rsdp->XsdtPhysicalAddress;
        PointerSize = sizeof (UINT64);
    }
    else
    {
        /* Root table is an RSDT (32-bit physical addresses) */

        Address = (ACPI_NATIVE_UINT) Rsdp->RsdtPhysicalAddress;
        PointerSize = sizeof (UINT32);
    }

    /* Map the table header to get the full table length */

    Table = AcpiOsMapMemory (Address, sizeof (ACPI_TABLE_HEADER));
    if (!Table)
    {
        return (AE_NO_MEMORY);
    }

    /* Get the length of the full table, verify length and map entire table */

    Length = Table->Length;
    AcpiOsUnmapMemory (Table, sizeof (ACPI_TABLE_HEADER));

    if (Length < sizeof (ACPI_TABLE_HEADER))
    {
        ACPI_ERROR ((AE_INFO, "Invalid length 0x%X in RSDT/XSDT", Length));
        return (AE_INVALID_TABLE_LENGTH);
    }

    Table = AcpiOsMapMemory (Address, Length);
    if (!Table)
    {
        return (AE_NO_MEMORY);
    }

    /* Validate the root table checksum */

    Checksum = AcpiTbChecksum (ACPI_CAST_PTR (UINT8, Table), Length);
#if (ACPI_CHECKSUM_ABORT)

    if (Checksum)
    {
        AcpiOsUnmapMemory(Table, Length);
        return (AE_BAD_CHECKSUM);
    }
#endif

    AcpiTbPrintTableHeader (Address, Table);

    /* Calculate the number of tables described in the root table */

    TableCount = (Table->Length - sizeof (ACPI_TABLE_HEADER)) / PointerSize;

    /* Setup loop */

    TableEntry = ACPI_CAST_PTR (UINT8, Table) + sizeof (ACPI_TABLE_HEADER);
    AcpiGbl_RootTableList.Count = 2;

    /*
     * Initialize the ACPI table entries
     * First two entries in the table array are reserved for the DSDT and FACS
     */
    for (i = 0; i < TableCount; ++i, TableEntry += PointerSize)
    {
        /* Ensure there is room for another table entry */

        if (AcpiGbl_RootTableList.Count >= AcpiGbl_RootTableList.Size)
        {
            Status = AcpiTbResizeRootTableList ();
            if (ACPI_FAILURE (Status))
            {
                ACPI_WARNING ((AE_INFO, "Truncating %u table entries!",
                    (unsigned) (AcpiGbl_RootTableList.Size - AcpiGbl_RootTableList.Count)));
                break;
            }
        }

        /* Get the physical address (32-bit for RSDT, 64-bit for XSDT) */

        if (PointerSize == sizeof (UINT32))
        {
            AcpiGbl_RootTableList.Tables[AcpiGbl_RootTableList.Count].Address =
                (ACPI_PHYSICAL_ADDRESS) (*ACPI_CAST_PTR (UINT32, TableEntry));
        }
        else
        {
            AcpiGbl_RootTableList.Tables[AcpiGbl_RootTableList.Count].Address =
                (ACPI_PHYSICAL_ADDRESS) (*ACPI_CAST_PTR (UINT64, TableEntry));
        }

        AcpiGbl_RootTableList.Count++;
    }

    /*
     * It is not possible to map more than one entry in some environments,
     * so unmap the root table here before mapping other tables
     */
    AcpiOsUnmapMemory (Table, Length);

    /* Initialize all tables other than the DSDT and FACS */

    for (i = 2; i < AcpiGbl_RootTableList.Count; i++)
    {
        Address = AcpiGbl_RootTableList.Tables[i].Address;
        Length = sizeof (ACPI_TABLE_HEADER);

        Table = AcpiOsMapMemory (Address, Length);
        if (!Table)
        {
            continue;
        }

        AcpiGbl_RootTableList.Tables[i].Length = Table->Length;
        AcpiGbl_RootTableList.Tables[i].Flags = Flags;

        ACPI_MOVE_32_TO_32 (&(AcpiGbl_RootTableList.Tables[i].Signature),
            Table->Signature);

        AcpiTbPrintTableHeader (Address, Table);

        /*
         * Special case for the FADT because of multiple versions -
         * get a local copy and convert to common format
         */
        if (ACPI_COMPARE_NAME (Table->Signature, ACPI_SIG_FADT))
        {
            AcpiOsUnmapMemory (Table, Length);
            Length = Table->Length;

            Table = AcpiOsMapMemory (Address, Length);
            if (!Table)
            {
                continue;
            }

            /* Copy the entire FADT locally */

            ACPI_MEMCPY (&AcpiGbl_FADT, Table,
                ACPI_MIN (Table->Length, sizeof (ACPI_TABLE_FADT)));

            /* Small table means old revision, convert to new */

            if (Table->Length < sizeof (ACPI_TABLE_FADT))
            {
                AcpiTbConvertFadt (ACPI_CAST_PTR (ACPI_TABLE_FADT, Table));
            }

            /* Unmap original FADT */

            AcpiOsUnmapMemory (Table, Length);
            AcpiTbParseFadt (&AcpiGbl_FADT, Flags);
        }
        else
        {
            AcpiOsUnmapMemory (Table, Length);
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


