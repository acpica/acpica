/******************************************************************************
 *
 * Module Name: tbfadt   - FADT table utilities
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

#define __TBFADT_C__

#include "acpi.h"
#include "actables.h"

#define _COMPONENT          ACPI_TABLES
        ACPI_MODULE_NAME    ("tbfadt")

/* Local prototypes */

static void inline
AcpiTbInitGenericAddress (
    ACPI_GENERIC_ADDRESS    *NewGasStruct,
    UINT8                   BitWidth,
    UINT64                  Address);

static void
AcpiTbFadtRegisterError (
    char                    *RegisterName,
    UINT32                  Value);

static void
AcpiTbConvertFadt (
    void);

static void
AcpiTbValidateFadt (
    void);


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

void
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

    ACPI_MEMSET (&AcpiGbl_FADT, 0, sizeof (ACPI_TABLE_FADT));

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

    /* Validate important FADT values */

    AcpiTbValidateFadt ();
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
     * Expand the 32-bit V1.0 addresses to the 64-bit "X" generic address
     * structures as necessary.
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
                (UINT64) *ACPI_ADD_PTR (UINT32, &AcpiGbl_FADT, FadtConversionTable[i].Source));
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


/******************************************************************************
 *
 * FUNCTION:    AcpiTbValidateFadt
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Validate various ACPI registers in the FADT
 *
 ******************************************************************************/

static void
AcpiTbValidateFadt (
    void)
{

    /* These length fields have a minimum value */

    if (AcpiGbl_FADT.Pm1EventLength < 4)
    {
        AcpiTbFadtRegisterError ("Pm1EventLength",
            (UINT32) AcpiGbl_FADT.Pm1EventLength);
    }

    if (AcpiGbl_FADT.PmTimerLength < 4)
    {
        AcpiTbFadtRegisterError ("PmTimerLength",
            (UINT32) AcpiGbl_FADT.PmTimerLength);
    }

    /* These length and address fields must be non-zero */

    if (!AcpiGbl_FADT.Pm1ControlLength)
    {
        AcpiTbFadtRegisterError ("Pm1ControlLength", 0);
    }

    if (!ACPI_VALID_ADDRESS (AcpiGbl_FADT.XPm1aEventBlock.Address))
    {
        AcpiTbFadtRegisterError ("XPm1aEventBlock.Address", 0);
    }

    if (!ACPI_VALID_ADDRESS (AcpiGbl_FADT.XPm1aControlBlock.Address))
    {
        AcpiTbFadtRegisterError ("XPm1aControlBlock.Address", 0);
    }

    if (!ACPI_VALID_ADDRESS (AcpiGbl_FADT.XPmTimerBlock.Address))
    {
        AcpiTbFadtRegisterError ("XPmTimerBlock.Address", 0);
    }

    /* If PM2 block is present, must have non-zero length */

    if ((ACPI_VALID_ADDRESS (AcpiGbl_FADT.XPm2ControlBlock.Address) &&
        !AcpiGbl_FADT.Pm2ControlLength))
    {
        AcpiTbFadtRegisterError ("Pm2ControlLength",
            (UINT32) AcpiGbl_FADT.Pm2ControlLength);
    }

    /* Length of any valid GPE blocks must be a multiple of 2 */

    if (ACPI_VALID_ADDRESS (AcpiGbl_FADT.XGpe0Block.Address) &&
        (AcpiGbl_FADT.Gpe0BlockLength & 1))
    {
        AcpiTbFadtRegisterError ("Gpe0BlockLength",
            (UINT32) AcpiGbl_FADT.Gpe0BlockLength);
    }

    if (ACPI_VALID_ADDRESS (AcpiGbl_FADT.XGpe1Block.Address) &&
        (AcpiGbl_FADT.Gpe1BlockLength & 1))
    {
        AcpiTbFadtRegisterError ("Gpe1BlockLength",
            (UINT32) AcpiGbl_FADT.Gpe1BlockLength);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbFadtRegisterError
 *
 * PARAMETERS:  RegisterName            - Pointer to string identifying register
 *              Value                   - Actual register contents value
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display FADT warning message
 *
 ******************************************************************************/

static void
AcpiTbFadtRegisterError (
    char                    *RegisterName,
    UINT32                  Value)
{

    ACPI_WARNING ((AE_INFO, "Invalid FADT value \"%s\" = %X",
        RegisterName, Value));
}






