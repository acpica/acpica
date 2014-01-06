/******************************************************************************
 *
 * Module Name: tbinstal - ACPI table installation and removal
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2014, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights. You may have additional license terms from the party that provided
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
 * to or modifications of the Original Intel Code. No other license or right
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
 * and the following Disclaimer and Export Compliance provision. In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change. Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee. Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution. In
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
 * HERE. ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT, ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES. INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS. INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES. THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government. In the
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


#define __TBINSTAL_C__

#include "acpi.h"
#include "accommon.h"
#include "acnamesp.h"
#include "actables.h"


#define _COMPONENT          ACPI_TABLES
        ACPI_MODULE_NAME    ("tbinstal")


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbAcquireTable
 *
 * PARAMETERS:  TableDesc           - Table descriptor
 *              TablePtr            - Where table is returned
 *              TableLength         - Where table length is returned
 *              TableFlags          - Where table allocation flags are returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Acquire a table.  It can be used for tables not maintained in
 *              AcpiGbl_RootTableList.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbAcquireTable (
    ACPI_TABLE_DESC         *TableDesc,
    ACPI_TABLE_HEADER       **TablePtr,
    UINT32                  *TableLength,
    UINT8                   *TableFlags)
{
    ACPI_TABLE_HEADER       *Table = NULL;


    switch (TableDesc->Flags & ACPI_TABLE_ORIGIN_MASK)
    {
    case ACPI_TABLE_ORIGIN_MAPPED:

        Table = AcpiOsMapMemory (TableDesc->Address, TableDesc->Length);
        break;

    case ACPI_TABLE_ORIGIN_ALLOCATED:
    case ACPI_TABLE_ORIGIN_UNKNOWN:
    case ACPI_TABLE_ORIGIN_OVERRIDE:

        Table = ACPI_CAST_PTR (ACPI_TABLE_HEADER, TableDesc->Address);
        break;

    default:

        break;
    }

    /* Table is not valid yet */

    if (!Table)
    {
        return (AE_NO_MEMORY);
    }

    /* Fill the return values */

    *TablePtr = Table;
    *TableLength = TableDesc->Length;
    *TableFlags = TableDesc->Flags;

    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbReleaseTable
 *
 * PARAMETERS:  Table               - Pointer for the table
 *              TableLength         - Length for the table
 *              TableFlags          - Allocation flags for the table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Release a table.  The reversal of AcpiTbAcquireTable().
 *
 ******************************************************************************/

void
AcpiTbReleaseTable (
    ACPI_TABLE_HEADER       *Table,
    UINT32                  TableLength,
    UINT8                   TableFlags)
{
    switch (TableFlags & ACPI_TABLE_ORIGIN_MASK)
    {
    case ACPI_TABLE_ORIGIN_MAPPED:

        AcpiOsUnmapMemory (Table, TableLength);
        break;

    case ACPI_TABLE_ORIGIN_ALLOCATED:
    case ACPI_TABLE_ORIGIN_UNKNOWN:
    case ACPI_TABLE_ORIGIN_OVERRIDE:
    default:

        break;
    }
}


/******************************************************************************
 *
 * FUNCTION:    AcpiTbValidateTable
 *
 * PARAMETERS:  TableDesc           - Table descriptor
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to validate (ensure Pointer is valid)
 *              and verify the table.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiTbValidateTable (
    ACPI_TABLE_DESC         *TableDesc)
{
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE (TbValidateTable);


    /* Validate the table if necessary */

    if (!TableDesc->Pointer)
    {
        Status = AcpiTbAcquireTable (TableDesc, &TableDesc->Pointer,
                &TableDesc->Length, &TableDesc->Flags);
        if (ACPI_FAILURE (Status) || !TableDesc->Pointer)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }
    }

    /* Always calculate checksum, ignore bad checksum if requested */

    Status = AcpiTbVerifyChecksum (TableDesc->Pointer, TableDesc->Length);

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbInvalidateTable
 *
 * PARAMETERS:  TableDesc           - Table descriptor
 *
 * RETURN:      None
 *
 * DESCRIPTION: Invalidate one internal ACPI table, this is reversal of
 *              AcpiTbValidateTable().
 *
 ******************************************************************************/

void
AcpiTbInvalidateTable (
    ACPI_TABLE_DESC         *TableDesc)
{

    ACPI_FUNCTION_TRACE (TbInvalidateTable);


    /* Table must be validated */

    if (!TableDesc->Pointer)
    {
        return_VOID;
    }

    AcpiTbReleaseTable (TableDesc->Pointer, TableDesc->Length,
                TableDesc->Flags);
    TableDesc->Pointer = NULL;

    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbAddTable
 *
 * PARAMETERS:  TableDesc           - Table descriptor
 *              TableIndex          - Where the table index is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to add an ACPI table. It is used to
 *              dynamically load tables via the Load and LoadTable AML
 *              operators.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbAddTable (
    ACPI_TABLE_DESC         *TableDesc,
    UINT32                  *TableIndex)
{
    UINT32                  i;
    ACPI_STATUS             Status = AE_OK;
    ACPI_TABLE_HEADER       *FinalTable;


    ACPI_FUNCTION_TRACE (TbAddTable);


    if (!TableDesc->Pointer)
    {
        Status = AcpiTbValidateTable (TableDesc);
        if (ACPI_FAILURE (Status) || !TableDesc->Pointer)
        {
            return_ACPI_STATUS (Status);
        }
    }

    /*
     * Validate the incoming table signature.
     *
     * 1) Originally, we checked the table signature for "SSDT" or "PSDT".
     * 2) We added support for OEMx tables, signature "OEM".
     * 3) Valid tables were encountered with a null signature, so we just
     *    gave up on validating the signature, (05/2008).
     * 4) We encountered non-AML tables such as the MADT, which caused
     *    interpreter errors and kernel faults. So now, we once again allow
     *    only "SSDT", "OEMx", and now, also a null signature. (05/2011).
     */
    if ((TableDesc->Pointer->Signature[0] != 0x00) &&
       (!ACPI_COMPARE_NAME (TableDesc->Pointer->Signature, ACPI_SIG_SSDT)) &&
       (ACPI_STRNCMP (TableDesc->Pointer->Signature, "OEM", 3)))
    {
        ACPI_BIOS_ERROR ((AE_INFO,
            "Table has invalid signature [%4.4s] (0x%8.8X), "
            "must be SSDT or OEMx",
            AcpiUtValidAcpiName (TableDesc->Pointer->Signature) ?
                TableDesc->Pointer->Signature : "????",
            *(UINT32 *) TableDesc->Pointer->Signature));

        return_ACPI_STATUS (AE_BAD_SIGNATURE);
    }

    (void) AcpiUtAcquireMutex (ACPI_MTX_TABLES);

    /* Check if table is already registered */

    for (i = 0; i < AcpiGbl_RootTableList.CurrentTableCount; ++i)
    {
        if (!AcpiGbl_RootTableList.Tables[i].Pointer)
        {
            Status = AcpiTbValidateTable (&AcpiGbl_RootTableList.Tables[i]);
            if (ACPI_FAILURE (Status) ||
                !AcpiGbl_RootTableList.Tables[i].Pointer)
            {
                continue;
            }
        }

        /*
         * Check for a table match on the entire table length,
         * not just the header.
         */
        if (TableDesc->Length != AcpiGbl_RootTableList.Tables[i].Length)
        {
            continue;
        }

        if (ACPI_MEMCMP (TableDesc->Pointer,
                AcpiGbl_RootTableList.Tables[i].Pointer,
                AcpiGbl_RootTableList.Tables[i].Length))
        {
            continue;
        }

        /*
         * Note: the current mechanism does not unregister a table if it is
         * dynamically unloaded. The related namespace entries are deleted,
         * but the table remains in the root table list.
         *
         * The assumption here is that the number of different tables that
         * will be loaded is actually small, and there is minimal overhead
         * in just keeping the table in case it is needed again.
         *
         * If this assumption changes in the future (perhaps on large
         * machines with many table load/unload operations), tables will
         * need to be unregistered when they are unloaded, and slots in the
         * root table list should be reused when empty.
         */
        *TableIndex = i;

        if (AcpiGbl_RootTableList.Tables[i].Flags & ACPI_TABLE_IS_LOADED)
        {
            /* Table is still loaded, this is an error */

            Status = AE_ALREADY_EXISTS;
            goto Release;
        }
        else
        {
            /* Table was unloaded, allow it to be reloaded */

            AcpiTbUninstallTable (TableDesc);
            TableDesc->Pointer = AcpiGbl_RootTableList.Tables[i].Pointer;
            TableDesc->Address = AcpiGbl_RootTableList.Tables[i].Address;
            Status = AE_OK;
            goto PrintHeader;
        }
    }

    /*
     * ACPI Table Override:
     * Allow the host to override dynamically loaded tables.
     * NOTE: the table is fully mapped at this point, and the mapping will
     * be deleted by AcpiTbOverrideTable if the table is actually overridden.
     */
    FinalTable = AcpiTbOverrideTable (TableDesc->Pointer, TableDesc);
    if (FinalTable)
    {
        /* Ensure table descriptor is in "VALIDATED" state */

        TableDesc->Pointer = FinalTable;
    }

    /* Add the table to the global root table list */

    Status = AcpiTbStoreTable (TableDesc->Address, TableDesc->Pointer,
                TableDesc->Length, TableDesc->Flags, TableIndex);
    if (ACPI_FAILURE (Status))
    {
        goto Release;
    }

PrintHeader:
    AcpiTbPrintTableHeader (TableDesc->Address, TableDesc->Pointer);

Release:
    (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);
    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbOverrideTable
 *
 * PARAMETERS:  TableHeader         - Header for the original table
 *              TableDesc           - Table descriptor initialized for the
 *                                    original table. May or may not be mapped.
 *
 * RETURN:      Pointer to the entire new table. NULL if table not overridden.
 *              If overridden, installs the new table within the input table
 *              descriptor.
 *
 * DESCRIPTION: Attempt table override by calling the OSL override functions.
 *              Note: If the table is overridden, then the entire new table
 *              is acquired and returned by this function.
 *              After invocation, the table descriptor is in a state that is
 *              "INSTALLED" but not "VALIDATED", thus the "Pointer" member is
 *              kept NULL.
 *
 ******************************************************************************/

ACPI_TABLE_HEADER *
AcpiTbOverrideTable (
    ACPI_TABLE_HEADER       *TableHeader,
    ACPI_TABLE_DESC         *TableDesc)
{
    ACPI_STATUS             Status;
    ACPI_TABLE_HEADER       *NewTable;
    UINT32                  NewTableLength;
    UINT8                   NewFlags;
    char                    *OverrideType;
    ACPI_TABLE_DESC         NewTableDesc;


    ACPI_MEMSET (&NewTableDesc, 0, sizeof (ACPI_TABLE_DESC));

    /* (1) Attempt logical override (returns a logical address) */

    Status = AcpiOsTableOverride (TableHeader, &NewTableDesc.Pointer);
    if (ACPI_SUCCESS (Status) && NewTableDesc.Pointer)
    {
        NewTableDesc.Address = ACPI_PTR_TO_PHYSADDR (NewTableDesc.Pointer);
        NewTableDesc.Length = NewTableDesc.Pointer->Length;
        NewTableDesc.Flags = ACPI_TABLE_ORIGIN_OVERRIDE;
        OverrideType = "Logical";
        goto FinishOverride;
    }

    /* (2) Attempt physical override (returns a physical address) */

    Status = AcpiOsPhysicalTableOverride (TableHeader,
        &NewTableDesc.Address, &NewTableDesc.Length);
    if (ACPI_SUCCESS (Status) && NewTableDesc.Address && NewTableDesc.Length)
    {
        OverrideType = "Physical";
        NewTableDesc.Flags = ACPI_TABLE_ORIGIN_MAPPED;
        goto FinishOverride;
    }

    return (NULL); /* There was no override */


FinishOverride:

    /*
     * Acquire the entire new table to indicate overridden.
     * Note that this is required by the callers of this function.
     */
    Status = AcpiTbAcquireTable (&NewTableDesc, &NewTable,
            &NewTableLength, &NewFlags);
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, AE_NO_MEMORY,
            "%4.4s " ACPI_PRINTF_UINT
            " Attempted table override failed",
            TableHeader->Signature,
            ACPI_FORMAT_TO_UINT (TableDesc->Address)));
        return (NULL);
    }

    ACPI_INFO ((AE_INFO, "%4.4s " ACPI_PRINTF_UINT
        " %s table override, new table: " ACPI_PRINTF_UINT,
        TableHeader->Signature,
        ACPI_FORMAT_TO_UINT (TableDesc->Address),
        OverrideType, ACPI_FORMAT_TO_UINT (NewTableDesc.Address)));

    /* We can now uninstall the original table (if fully mapped) */

    AcpiTbUninstallTable (TableDesc);

    /* Install the new table */

    TableDesc->Address = NewTableDesc.Address;
    TableDesc->Length = NewTableDesc.Length;
    TableDesc->Flags = NewTableDesc.Flags;

    return (NewTable);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbResizeRootTableList
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Expand the size of global table array
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbResizeRootTableList (
    void)
{
    ACPI_TABLE_DESC         *Tables;
    UINT32                  TableCount;


    ACPI_FUNCTION_TRACE (TbResizeRootTableList);


    /* AllowResize flag is a parameter to AcpiInitializeTables */

    if (!(AcpiGbl_RootTableList.Flags & ACPI_ROOT_ALLOW_RESIZE))
    {
        ACPI_ERROR ((AE_INFO, "Resize of Root Table Array is not allowed"));
        return_ACPI_STATUS (AE_SUPPORT);
    }

    /* Increase the Table Array size */

    if (AcpiGbl_RootTableList.Flags & ACPI_ROOT_ORIGIN_ALLOCATED)
    {
        TableCount = AcpiGbl_RootTableList.MaxTableCount;
    }
    else
    {
        TableCount = AcpiGbl_RootTableList.CurrentTableCount;
    }

    Tables = ACPI_ALLOCATE_ZEROED (
        ((ACPI_SIZE) TableCount + ACPI_ROOT_TABLE_SIZE_INCREMENT) *
        sizeof (ACPI_TABLE_DESC));
    if (!Tables)
    {
        ACPI_ERROR ((AE_INFO, "Could not allocate new root table array"));
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Copy and free the previous table array */

    if (AcpiGbl_RootTableList.Tables)
    {
        ACPI_MEMCPY (Tables, AcpiGbl_RootTableList.Tables,
            (ACPI_SIZE) TableCount * sizeof (ACPI_TABLE_DESC));

        if (AcpiGbl_RootTableList.Flags & ACPI_ROOT_ORIGIN_ALLOCATED)
        {
            ACPI_FREE (AcpiGbl_RootTableList.Tables);
        }
    }

    AcpiGbl_RootTableList.Tables = Tables;
    AcpiGbl_RootTableList.MaxTableCount =
        TableCount + ACPI_ROOT_TABLE_SIZE_INCREMENT;
    AcpiGbl_RootTableList.Flags |= ACPI_ROOT_ORIGIN_ALLOCATED;

    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbStoreTable
 *
 * PARAMETERS:  Address             - Table address
 *              Table               - Table header
 *              Length              - Table length
 *              Flags               - flags
 *
 * RETURN:      Status and table index.
 *
 * DESCRIPTION: Add an ACPI table to the global table list
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbStoreTable (
    ACPI_PHYSICAL_ADDRESS   Address,
    ACPI_TABLE_HEADER       *Table,
    UINT32                  Length,
    UINT8                   Flags,
    UINT32                  *TableIndex)
{
    ACPI_STATUS             Status;
    ACPI_TABLE_DESC         *NewTable;


    /* Ensure that there is room for the table in the Root Table List */

    if (AcpiGbl_RootTableList.CurrentTableCount >=
        AcpiGbl_RootTableList.MaxTableCount)
    {
        Status = AcpiTbResizeRootTableList();
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }
    }

    NewTable = &AcpiGbl_RootTableList.Tables[AcpiGbl_RootTableList.CurrentTableCount];

    /* Initialize added table */

    NewTable->Address = Address;
    NewTable->Pointer = Table;
    NewTable->Length = Length;
    NewTable->OwnerId = 0;
    NewTable->Flags = Flags;

    ACPI_MOVE_32_TO_32 (&NewTable->Signature, Table->Signature);

    *TableIndex = AcpiGbl_RootTableList.CurrentTableCount;
    AcpiGbl_RootTableList.CurrentTableCount++;
    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbUninstallTable
 *
 * PARAMETERS:  TableDesc           - Table descriptor
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete one internal ACPI table
 *
 ******************************************************************************/

void
AcpiTbUninstallTable (
    ACPI_TABLE_DESC         *TableDesc)
{

    ACPI_FUNCTION_TRACE (TbUninstallTable);


    /* Table must be installed */

    if (!TableDesc->Address)
    {
        return_VOID;
    }

    AcpiTbInvalidateTable (TableDesc);

    if ((TableDesc->Flags & ACPI_TABLE_ORIGIN_MASK) ==
        ACPI_TABLE_ORIGIN_ALLOCATED)
    {
        ACPI_FREE (ACPI_CAST_PTR (void, TableDesc->Address));
    }

    TableDesc->Address = ACPI_PTR_TO_PHYSADDR (NULL);

    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbTerminate
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete all internal ACPI tables
 *
 ******************************************************************************/

void
AcpiTbTerminate (
    void)
{
    UINT32                  i;


    ACPI_FUNCTION_TRACE (TbTerminate);


    (void) AcpiUtAcquireMutex (ACPI_MTX_TABLES);

    /* Delete the individual tables */

    for (i = 0; i < AcpiGbl_RootTableList.CurrentTableCount; i++)
    {
        AcpiTbUninstallTable (&AcpiGbl_RootTableList.Tables[i]);
    }

    /*
     * Delete the root table array if allocated locally. Array cannot be
     * mapped, so we don't need to check for that flag.
     */
    if (AcpiGbl_RootTableList.Flags & ACPI_ROOT_ORIGIN_ALLOCATED)
    {
        ACPI_FREE (AcpiGbl_RootTableList.Tables);
    }

    AcpiGbl_RootTableList.Tables = NULL;
    AcpiGbl_RootTableList.Flags = 0;
    AcpiGbl_RootTableList.CurrentTableCount = 0;

    ACPI_DEBUG_PRINT ((ACPI_DB_INFO, "ACPI Tables freed\n"));
    (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);

    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbDeleteNamespaceByOwner
 *
 * PARAMETERS:  TableIndex          - Table index
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Delete all namespace objects created when this table was loaded.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbDeleteNamespaceByOwner (
    UINT32                  TableIndex)
{
    ACPI_OWNER_ID           OwnerId;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (TbDeleteNamespaceByOwner);


    Status = AcpiUtAcquireMutex (ACPI_MTX_TABLES);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    if (TableIndex >= AcpiGbl_RootTableList.CurrentTableCount)
    {
        /* The table index does not exist */

        (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    /* Get the owner ID for this table, used to delete namespace nodes */

    OwnerId = AcpiGbl_RootTableList.Tables[TableIndex].OwnerId;
    (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);

    /*
     * Need to acquire the namespace writer lock to prevent interference
     * with any concurrent namespace walks. The interpreter must be
     * released during the deletion since the acquisition of the deletion
     * lock may block, and also since the execution of a namespace walk
     * must be allowed to use the interpreter.
     */
    (void) AcpiUtReleaseMutex (ACPI_MTX_INTERPRETER);
    Status = AcpiUtAcquireWriteLock (&AcpiGbl_NamespaceRwLock);

    AcpiNsDeleteNamespaceByOwner (OwnerId);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    AcpiUtReleaseWriteLock (&AcpiGbl_NamespaceRwLock);

    Status = AcpiUtAcquireMutex (ACPI_MTX_INTERPRETER);
    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbAllocateOwnerId
 *
 * PARAMETERS:  TableIndex          - Table index
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Allocates OwnerId in TableDesc
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbAllocateOwnerId (
    UINT32                  TableIndex)
{
    ACPI_STATUS             Status = AE_BAD_PARAMETER;


    ACPI_FUNCTION_TRACE (TbAllocateOwnerId);


    (void) AcpiUtAcquireMutex (ACPI_MTX_TABLES);
    if (TableIndex < AcpiGbl_RootTableList.CurrentTableCount)
    {
        Status = AcpiUtAllocateOwnerId
                    (&(AcpiGbl_RootTableList.Tables[TableIndex].OwnerId));
    }

    (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);
    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbReleaseOwnerId
 *
 * PARAMETERS:  TableIndex          - Table index
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Releases OwnerId in TableDesc
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbReleaseOwnerId (
    UINT32                  TableIndex)
{
    ACPI_STATUS             Status = AE_BAD_PARAMETER;


    ACPI_FUNCTION_TRACE (TbReleaseOwnerId);


    (void) AcpiUtAcquireMutex (ACPI_MTX_TABLES);
    if (TableIndex < AcpiGbl_RootTableList.CurrentTableCount)
    {
        AcpiUtReleaseOwnerId (
            &(AcpiGbl_RootTableList.Tables[TableIndex].OwnerId));
        Status = AE_OK;
    }

    (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);
    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbGetOwnerId
 *
 * PARAMETERS:  TableIndex          - Table index
 *              OwnerId             - Where the table OwnerId is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: returns OwnerId for the ACPI table
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbGetOwnerId (
    UINT32                  TableIndex,
    ACPI_OWNER_ID           *OwnerId)
{
    ACPI_STATUS             Status = AE_BAD_PARAMETER;


    ACPI_FUNCTION_TRACE (TbGetOwnerId);


    (void) AcpiUtAcquireMutex (ACPI_MTX_TABLES);
    if (TableIndex < AcpiGbl_RootTableList.CurrentTableCount)
    {
        *OwnerId = AcpiGbl_RootTableList.Tables[TableIndex].OwnerId;
        Status = AE_OK;
    }

    (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);
    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbIsTableLoaded
 *
 * PARAMETERS:  TableIndex          - Table index
 *
 * RETURN:      Table Loaded Flag
 *
 ******************************************************************************/

BOOLEAN
AcpiTbIsTableLoaded (
    UINT32                  TableIndex)
{
    BOOLEAN                 IsLoaded = FALSE;


    (void) AcpiUtAcquireMutex (ACPI_MTX_TABLES);
    if (TableIndex < AcpiGbl_RootTableList.CurrentTableCount)
    {
        IsLoaded = (BOOLEAN)
            (AcpiGbl_RootTableList.Tables[TableIndex].Flags &
            ACPI_TABLE_IS_LOADED);
    }

    (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);
    return (IsLoaded);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbSetTableLoadedFlag
 *
 * PARAMETERS:  TableIndex          - Table index
 *              IsLoaded            - TRUE if table is loaded, FALSE otherwise
 *
 * RETURN:      None
 *
 * DESCRIPTION: Sets the table loaded flag to either TRUE or FALSE.
 *
 ******************************************************************************/

void
AcpiTbSetTableLoadedFlag (
    UINT32                  TableIndex,
    BOOLEAN                 IsLoaded)
{

    (void) AcpiUtAcquireMutex (ACPI_MTX_TABLES);
    if (TableIndex < AcpiGbl_RootTableList.CurrentTableCount)
    {
        if (IsLoaded)
        {
            AcpiGbl_RootTableList.Tables[TableIndex].Flags |=
                ACPI_TABLE_IS_LOADED;
        }
        else
        {
            AcpiGbl_RootTableList.Tables[TableIndex].Flags &=
                ~ACPI_TABLE_IS_LOADED;
        }
    }

    (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);
}
