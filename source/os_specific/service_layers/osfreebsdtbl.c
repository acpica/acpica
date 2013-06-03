/******************************************************************************
 *
 * Module Name: osfreebsdtbl - FreeBSD OSL for obtaining ACPI tables
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2013, Intel Corp.
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

#include "acpidump.h"

#include <kenv.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/sysctl.h>


#define _COMPONENT          ACPI_OS_SERVICES
        ACPI_MODULE_NAME    ("osfreebsdtbl")


/* Local prototypes */

static ACPI_STATUS
OslAddTablesToList (
    void);

static ACPI_STATUS
OslGetRsdp (
    void);

static ACPI_STATUS
OslMapTable (
    ACPI_SIZE               Address,
    char                    *Signature,
    ACPI_TABLE_HEADER       **Table);


#define SYSTEM_MEMORY       "/dev/mem"

#define SYSTEM_KENV         "hint.acpi.0.rsdp"
#define SYSTEM_SYSCTL       "machdep.acpi_root"

UINT8                   Gbl_TableListInitialized = FALSE;
UINT8                   Gbl_RsdpObtained = FALSE;
ACPI_TABLE_RSDP         Gbl_Rsdp;

/* List for obtained ACPI tables */

typedef struct          table_info
{
    struct table_info       *Next;
    UINT32                  Instance;
    char                    Signature[4];

} OSL_TABLE_INFO;

OSL_TABLE_INFO          *Gbl_TableListHead = NULL;


/******************************************************************************
 *
 * FUNCTION:    AcpiOsGetTableByAddress
 *
 * PARAMETERS:  Address         - Physical address of the ACPI table
 *              Table           - Where a pointer to the table is returned
 *
 * RETURN:      Status; Table buffer is returned if AE_OK.
 *              AE_NOT_FOUND: A valid table was not found at the address
 *
 * DESCRIPTION: Get an ACPI table via a physical memory address.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsGetTableByAddress (
    ACPI_PHYSICAL_ADDRESS   Address,
    ACPI_TABLE_HEADER       **Table)
{
    ACPI_TABLE_HEADER       *MappedTable;
    ACPI_TABLE_HEADER       *LocalTable;
    ACPI_STATUS             Status;


    if (Address < ACPI_HI_RSDP_WINDOW_BASE)
    {
        fprintf (stderr, "Invalid table address: 0x%8.8X%8.8X\n",
            ACPI_FORMAT_UINT64 (Address));
        return (AE_BAD_ADDRESS);
    }

    /* Get the table and validate it */

    Status = OslMapTable (Address, NULL, &MappedTable);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* Copy table to local buffer */

    LocalTable = calloc (1, MappedTable->Length);
    if (!LocalTable)
    {
        return (AE_NO_MEMORY);
    }

    ACPI_MEMCPY (LocalTable, MappedTable, MappedTable->Length);
    AcpiOsUnmapMemory (MappedTable, MappedTable->Length);

    *Table = LocalTable;
    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsGetTableByName
 *
 * PARAMETERS:  Signature       - ACPI Signature for desired table. Must be
 *                                a null terminated 4-character string.
 *              Instance        - For SSDTs (0...n)
 *              Table           - Where a pointer to the table is returned
 *              Address         - Where the table physical address is returned
 *
 * RETURN:      Status; Table buffer and physical address returned if AE_OK.
 *
 * RETURN:      Status; Table buffer and physical address returned if AE_OK.
 *              AE_LIMIT: Instance is beyond valid limit
 *              AE_NOT_FOUND: A table with the signature was not found
 *
 * NOTE:        Assumes the input signature is uppercase.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsGetTableByName (
    char                    *Signature,
    UINT32                  Instance,
    ACPI_TABLE_HEADER       **Table,
    ACPI_PHYSICAL_ADDRESS   *Address)
{
    ACPI_TABLE_HEADER       *LocalTable = NULL;
    ACPI_TABLE_HEADER       *MappedTable;
    ACPI_TABLE_FADT         *Fadt;
    UINT8                   NumberOfTables;
    UINT8                   Revision;
    UINT8                   *TableData;
    UINT8                   ItemSize;
    UINT32                  CurrentInstance = 0;
    ACPI_PHYSICAL_ADDRESS   TableAddress = 0;
    ACPI_STATUS             Status;
    UINT32                  i;


    /* Instance is only valid for SSDTs */

    if (Instance && !ACPI_COMPARE_NAME (Signature, ACPI_SIG_SSDT))
    {
        return (AE_LIMIT);
    }

    Status = OslGetRsdp ();
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* Requests for RSDT/XSDT are special cases */

    if (ACPI_COMPARE_NAME (Signature, ACPI_SIG_XSDT))
    {
        if ((Gbl_Rsdp.Revision <= 1) ||
            (!Gbl_Rsdp.XsdtPhysicalAddress))
        {
            return (AE_NOT_FOUND);
        }
    }
    else if (ACPI_COMPARE_NAME (Signature, ACPI_SIG_RSDT))
    {
        if (!Gbl_Rsdp.RsdtPhysicalAddress)
        {
            return (AE_NOT_FOUND);
        }
    }

    /* Map RSDT or XSDT based on RSDP version */

    if (Gbl_Rsdp.Revision)
    {
        Status = OslMapTable (Gbl_Rsdp.XsdtPhysicalAddress,
            ACPI_SIG_XSDT, &MappedTable);
        Revision = 2;
        ItemSize = sizeof (UINT64);
    }
    else /* No XSDT, use RSDT */
    {
        Status = OslMapTable (Gbl_Rsdp.RsdtPhysicalAddress,
            ACPI_SIG_RSDT, &MappedTable);
        Revision = 0;
        ItemSize = sizeof (UINT32);
    }

    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* Copy RSDT/XSDT to local buffer */

    LocalTable = calloc (1, MappedTable->Length);
    if (!LocalTable)
    {
        AcpiOsUnmapMemory (MappedTable, MappedTable->Length);
        return (AE_NO_MEMORY);
    }

    ACPI_MEMCPY (LocalTable, MappedTable, MappedTable->Length);
    AcpiOsUnmapMemory (MappedTable, MappedTable->Length);

    /* If RSDT/XSDT requested, we are done */

    if (ACPI_COMPARE_NAME (Signature, ACPI_SIG_RSDT) ||
        ACPI_COMPARE_NAME (Signature, ACPI_SIG_XSDT))
    {
        if (Revision)
        {
            *Address = Gbl_Rsdp.XsdtPhysicalAddress;
        }
        else
        {
            *Address = Gbl_Rsdp.RsdtPhysicalAddress;
        }

        *Table = LocalTable;
        return (AE_OK);
    }

    TableData = ACPI_CAST8 (LocalTable) + sizeof (*LocalTable);

    /* DSDT and FACS address must be extracted from the FADT */

    if (ACPI_COMPARE_NAME (Signature, ACPI_SIG_DSDT) ||
        ACPI_COMPARE_NAME (Signature, ACPI_SIG_FACS))
    {
        /* Get the FADT */

        if (Revision)
        {
            TableAddress = ACPI_GET64 (TableData);
        }
        else
        {
            TableAddress = ACPI_GET32 (TableData);
        }

        if (!TableAddress)
        {
            fprintf (stderr, "No FADT in memory!\n");
            return (AE_NOT_FOUND);
        }

        Status = OslMapTable (TableAddress, NULL,
            ACPI_CAST_PTR (ACPI_TABLE_HEADER *, &Fadt));
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        if (!Fadt)
        {
            fprintf (stderr, "No FADT in memory!\n");
            return (AE_NOT_FOUND);
        }

        /* Get the appropriate address, either 32-bit or 64-bit */

        TableAddress = 0;
        if (ACPI_COMPARE_NAME (Signature, ACPI_SIG_DSDT))
        {
            if ((Fadt->Header.Length >= 148) && Fadt->XDsdt)
            {
                TableAddress = (ACPI_PHYSICAL_ADDRESS) Fadt->XDsdt;
            }
            else if ((Fadt->Header.Length >= 44) && Fadt->Dsdt)
            {
                TableAddress = (ACPI_PHYSICAL_ADDRESS) Fadt->Dsdt;
            }
        }
        else
        {
            if ((Fadt->Header.Length >= 140) && Fadt->XFacs)
            {
                TableAddress = (ACPI_PHYSICAL_ADDRESS) Fadt->XFacs;
            }
            else if ((Fadt->Header.Length >= 40) && Fadt->Facs)
            {
                TableAddress = (ACPI_PHYSICAL_ADDRESS) Fadt->Facs;
            }
        }

        AcpiOsUnmapMemory (Fadt, Fadt->Header.Length);
        if (!TableAddress)
        {
            fprintf (stderr, "No %s in FADT!\n", Signature);
            return (AE_NOT_FOUND);
        }

        /* Now we can finally get the requested table (DSDT or FACS) */

        Status = OslMapTable (TableAddress, Signature, &MappedTable);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }
    }
    else
    {
        /* Case for a normal ACPI table */

        NumberOfTables =
            (LocalTable->Length - sizeof (*LocalTable)) / ItemSize;

        /* Search RSDT/XSDT for the requested table */

        for (i = 0; i < NumberOfTables; i++, TableData += ItemSize)
        {
            if (Revision)
            {
                TableAddress =
                    (ACPI_PHYSICAL_ADDRESS) (*ACPI_CAST64 (TableData));
            }
            else
            {
                TableAddress =
                    (ACPI_PHYSICAL_ADDRESS) (*ACPI_CAST32 (TableData));
            }

            if (!TableAddress)
            {
                continue;
            }

            Status = OslMapTable (TableAddress, NULL, &MappedTable);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }

            if (!MappedTable)
            {
                continue;
            }

            /* Does this table the match the requested signature? */

            if (!ACPI_COMPARE_NAME (MappedTable->Signature, Signature))
            {
                AcpiOsUnmapMemory (MappedTable, MappedTable->Length);
                MappedTable = NULL;
                continue;
            }

            /* Match table instance (for SSDTs) */

            if (CurrentInstance != Instance)
            {
                AcpiOsUnmapMemory (MappedTable, MappedTable->Length);
                MappedTable = NULL;
                CurrentInstance++;
                continue;
            }

            break;
        }
    }

    /* Copy table to local buffer */

    LocalTable = calloc (1, MappedTable->Length);
    if (!LocalTable)
    {
        return (AE_NO_MEMORY);
    }

    ACPI_MEMCPY (LocalTable, MappedTable, MappedTable->Length);
    AcpiOsUnmapMemory (MappedTable, MappedTable->Length);
    *Address = TableAddress;

    *Table = LocalTable;
    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsGetTableByIndex
 *
 * PARAMETERS:  Index           - Which table to get
 *              Table           - Where a pointer to the table is returned
 *              Address         - Where the table physical address is returned
 *
 * RETURN:      Status; Table buffer and physical address returned if AE_OK.
 *              AE_LIMIT: Index is beyond valid limit
 *
 * DESCRIPTION: Get an ACPI table via an index value (0 through n). Returns
 *              AE_LIMIT when an invalid index is reached. Index is not
 *              necessarily an index into the RSDT/XSDT.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsGetTableByIndex (
    UINT32                  Index,
    ACPI_TABLE_HEADER       **Table,
    ACPI_PHYSICAL_ADDRESS   *Address)
{
    ACPI_STATUS             Status;
    OSL_TABLE_INFO          *Pointer;
    UINT32                  i;


    /* Initialize the table list if necessary */

    if (!Gbl_TableListInitialized)
    {
        Gbl_TableListHead = calloc (1, sizeof (*Gbl_TableListHead));

        /* List head records the length of the list */

        Gbl_TableListHead->Instance = 0;

        Status = OslAddTablesToList ();
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        Gbl_TableListInitialized = TRUE;
    }

    if (Index >= Gbl_TableListHead->Instance)
    {
        return (AE_LIMIT);
    }

    /* Point to the table list entry specified by the Index argument */

    Pointer = Gbl_TableListHead;
    for (i = 0; i <= Index; i++)
    {
        Pointer = Pointer->Next;
    }

    Status = AcpiOsGetTableByName (Pointer->Signature,
        Pointer->Instance, Table, Address);
    return (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsMapMemory
 *
 * PARAMETERS:  Where               - Physical address of memory to be mapped
 *              Length              - How much memory to mapped
 *
 * RETURN:      Pointer to mapped memory. Null on error.
 *
 * DESCRIPTION: Map physical memory into caller's address space.
 *
 *****************************************************************************/

void *
AcpiOsMapMemory (
    ACPI_PHYSICAL_ADDRESS   Where,
    ACPI_SIZE               Length)
{
    ACPI_PHYSICAL_ADDRESS   Offset;
    UINT8                   *MappedMemory;
    int                     fd;


    fd = open (SYSTEM_MEMORY, O_RDONLY);
    if (fd < 0)
    {
        fprintf (stderr, "Cannot open /dev/mem\n");
        return (NULL);
    }

    /* Align the offset to use mmap */

    Offset = Where % PAGE_SIZE;

    /* Map the table header to get the length of the full table */

    MappedMemory = mmap (NULL, Length + Offset, PROT_READ, MAP_SHARED,
        fd, Where - Offset);
    close (fd);
    if (MappedMemory == MAP_FAILED)
    {
        return (NULL);
    }

    return (ACPI_CAST8 (MappedMemory + Offset));
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsUnmapMemory
 *
 * PARAMETERS:  Where               - Logical address of memory to be unmapped
 *              Length              - How much memory to unmap
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete a previously created mapping. Where and Length must
 *              correspond to a previous mapping exactly.
 *
 *****************************************************************************/

void
AcpiOsUnmapMemory (
    void                    *Where,
    ACPI_SIZE               Length)
{
    ACPI_PHYSICAL_ADDRESS   Offset;


    Offset = (ACPI_PHYSICAL_ADDRESS) Where % PAGE_SIZE;
    munmap ((UINT8 *) Where - Offset, Length + Offset);
}


/******************************************************************************
 *
 * FUNCTION:    OslAddTablesToList
 *      
 * PARAMETERS:  None
 *
 * RETURN:      Status; Table list is initiated if AE_OK.
 *
 * DESCRIPTION: Add ACPI tables to the table list.
 *
 *****************************************************************************/
  
static ACPI_STATUS
OslAddTablesToList (
    void)
{
    ACPI_PHYSICAL_ADDRESS   Address;
    OSL_TABLE_INFO          *Info;
    OSL_TABLE_INFO          *Pointer;
    ACPI_TABLE_HEADER       *Table;
    ACPI_TABLE_HEADER       *MappedTable;
    UINT8                   *TableData;
    UINT8                   ItemSize;
    UINT8                   Revision = 0;
    UINT8                   NumberOfSsdt = 0;
    UINT8                   NumberOfTables;
    ACPI_STATUS             Status;
    int                     i;

    Status = OslGetRsdp ();
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    if ((Gbl_Rsdp.Revision <= 1) || (!Gbl_Rsdp.XsdtPhysicalAddress))
    {
        Status = OslMapTable (Gbl_Rsdp.RsdtPhysicalAddress,
            ACPI_SIG_RSDT, &MappedTable);
        ItemSize = sizeof (UINT32);
    }
    else
    {
        Status = OslMapTable (Gbl_Rsdp.XsdtPhysicalAddress,
            ACPI_SIG_XSDT, &MappedTable);
        Revision = 2;
        ItemSize = sizeof (UINT64);
    }
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    Pointer = Gbl_TableListHead;

    /* Add mandatory tables first */

    for (i = 0; i < 3; i++)
    {
        Info = calloc (1, sizeof (*Info));

        switch (i) {
        case 0:

            ACPI_MEMCPY (Info->Signature,
                Revision ? ACPI_SIG_XSDT : ACPI_SIG_RSDT, ACPI_NAME_SIZE);
            break;

        case 1:

            ACPI_MEMCPY (Info->Signature, ACPI_SIG_FACS, ACPI_NAME_SIZE);
            break;

        default:

            ACPI_MEMCPY (Info->Signature, ACPI_SIG_DSDT, ACPI_NAME_SIZE);

        }

        Pointer->Next = Info;
        Pointer = Info;
        Gbl_TableListHead->Instance++;
    }

    /* Add normal tables from RSDT/XSDT */

    TableData = ACPI_CAST8 (MappedTable) + sizeof (*MappedTable);
    NumberOfTables = (MappedTable->Length - sizeof (*MappedTable)) / ItemSize;
    for (i = 0; i < NumberOfTables; i++, TableData += ItemSize)
    {
        Address = Revision ? ACPI_GET64 (TableData) : ACPI_GET32 (TableData);

        Table = AcpiOsMapMemory (Address, sizeof (*Table));
        if (!Table)
        {
            return (AE_NO_MEMORY);
        }

        Info = calloc (1, sizeof (*Info));
        if (!Info)
        {
            AcpiOsUnmapMemory (Table, sizeof (*Table));
            return (AE_NO_MEMORY);
        }

        ACPI_MEMCPY (Info->Signature, Table->Signature, ACPI_NAME_SIZE);

        if (ACPI_COMPARE_NAME (Info->Signature, ACPI_SIG_SSDT))
        {
            Info->Instance = NumberOfSsdt;
            NumberOfSsdt++;
        }

        AcpiOsUnmapMemory (Table, sizeof (*Table));

        Pointer->Next = Info;
        Pointer = Info;
        Gbl_TableListHead->Instance++;
    }

    AcpiOsUnmapMemory (MappedTable, MappedTable->Length);

    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    OslGetRsdp
 *      
 * PARAMETERS:  None
 *
 * RETURN:      Status; RSDP returned if AE_OK.
 *
 * DESCRIPTION: Find RSDP from loader, kernel, or memory.
 *
 *****************************************************************************/
  
static ACPI_STATUS
OslGetRsdp (
    void)
{
    ACPI_PHYSICAL_ADDRESS   RsdpBase;
    ACPI_SIZE               RsdpSize;
    UINT8                   *RsdpAddress;
    UINT8                   *Table;
    char                    Buffer[32];
    u_long                  Address = 0;
    size_t                  Length = sizeof (Address);

    /* Get RSDP from memory on first invocation of this function */

    if (Gbl_RsdpObtained)
    {
        return (AE_OK);
    }

    /* Attempt to use kenv or sysctl to find RSD PTR record. */

    if (kenv (KENV_GET, SYSTEM_KENV, Buffer, sizeof (Buffer)) > 0)
    {
        Address = strtoul (Buffer, NULL, 0);
    }
    if (!Address)
    {
        if (sysctlbyname (SYSTEM_SYSCTL, &Address, &Length, NULL, 0) != 0)
        {
            Address = 0;
        }
    }
    if (Address)
    {
        RsdpBase = Address;
        RsdpSize = sizeof (Gbl_Rsdp);
    }
    else
    {
        RsdpBase = ACPI_HI_RSDP_WINDOW_BASE;
        RsdpSize = ACPI_HI_RSDP_WINDOW_SIZE;
    }

    RsdpAddress = AcpiOsMapMemory (RsdpBase, RsdpSize);
    if (!RsdpAddress)
    {
        return (AE_NOT_FOUND);
    }

    Table = AcpiTbScanMemoryForRsdp (RsdpAddress, RsdpSize);
    if (!Table)
    {
        AcpiOsUnmapMemory (RsdpAddress, RsdpSize);
        return (AE_NOT_FOUND);
    }

    ACPI_MEMCPY (&Gbl_Rsdp, Table, sizeof (Gbl_Rsdp));
    Gbl_RsdpObtained = TRUE;
    AcpiOsUnmapMemory (RsdpAddress, RsdpSize);

    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    OslMapTable
 *
 * PARAMETERS:  Address             - Address of the table in memory
 *              Signature           - Optional ACPI Signature for desired table.
 *                                    Null terminated 4-character string.
 *              Table               - Where a pointer to the mapped table is
 *                                    returned
 *
 * RETURN:      Status; Mapped table is returned if AE_OK.
 *
 * DESCRIPTION: Map entire ACPI table into caller's address space. Also
 *              validates the table and checksum.
 *
 *****************************************************************************/

static ACPI_STATUS
OslMapTable (
    ACPI_SIZE               Address,
    char                    *Signature,
    ACPI_TABLE_HEADER       **Table)
{
    ACPI_TABLE_HEADER       *LocalTable;
    UINT32                  Length;


    /* Start by mapping just the header */

    LocalTable = AcpiOsMapMemory (Address, sizeof (*LocalTable));
    if (!LocalTable)
    {
        fprintf (stderr, "Could not map table header at 0x%8.8X%8.8X\n",
            ACPI_FORMAT_UINT64 (Address));
        return (AE_BAD_ADDRESS);
    }

    /* Check if table is valid */

    if (!ApIsValidHeader (LocalTable))
    {
        return (AE_BAD_HEADER);
    }

    /* If specified, signature must match */

    if (Signature &&
        !ACPI_COMPARE_NAME (Signature, LocalTable->Signature))
    {
        return (AE_NOT_EXIST);
    }

    /* Map the entire table */

    Length = LocalTable->Length;

    AcpiOsUnmapMemory (LocalTable, sizeof (ACPI_TABLE_HEADER));
    LocalTable = AcpiOsMapMemory (Address, Length);
    if (!LocalTable)
    {
        fprintf (stderr, "Could not map table at 0x%8.8X%8.8X\n",
            ACPI_FORMAT_UINT64 (Address));
        return (AE_NO_MEMORY);
    }

    *Table = LocalTable;
    return (AE_OK);
}
