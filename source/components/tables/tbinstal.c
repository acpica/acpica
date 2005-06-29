
/******************************************************************************
 * 
 * Module Name: tbinstal - ACPI table installation
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, Intel Corp.  All rights
 * reserved.
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


#define __TBINSTAL_C__

#include <acpi.h>
#include <hardware.h>
#include <tables.h>


#define _THIS_MODULE        "tbinstal.c"
#define _COMPONENT          TABLE_MANAGER



/******************************************************************************
 *
 * FUNCTION:    TbMapAcpiTable
 *
 * PARAMETERS:  PhysicalAddress         - Physical address of table to map
 *              *Size                   - Size of the table.  If zero, the size
 *                                        from the table header is used.  Actual
 *                                        size is returned here.
 *
 * RETURN:      Logical address of the mapped table.
 *
 * DESCRIPTION: Maps the physical address of table into a logical address
 *
 ******************************************************************************/

void *
TbMapAcpiTable (
    void                    *PhysicalAddress,
    UINT32                  *Size)
{
    ACPI_TABLE_HEADER       *Table;
    UINT32                  TableSize = *Size;



    /* If size is zero, look at the table header to get the actual size */

    if (!*Size)
    {
        /* Get the table header so we can extract the table length */

        Table = OsdMapMemory (PhysicalAddress, sizeof (ACPI_TABLE_HEADER));
        if (!Table)
        {
            return NULL;
        }

        /* Now we know how large to make the mapping (table + header) */

        TableSize = Table->Length;
        OsdUnMapMemory (Table, sizeof (ACPI_TABLE_HEADER));
    }


    /* Map the physical memory for the correct length */

    Table = OsdMapMemory (PhysicalAddress, TableSize);
    if (!Table)
    {
        return NULL;
    }

    DEBUG_PRINT (ACPI_INFO, ("Mapped memory for ACPI table, length=%d(0x%X) at %p\n",
                    TableSize, TableSize, Table));

    *Size = TableSize;
    return Table;
}



/******************************************************************************
 *
 * FUNCTION:    TbInstallTable
 *
 * PARAMETERS:  TablePtr            - Input buffer pointer, optional
 *              TableInfo           - Return value from TbGetTable
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load and validate all tables other than the RSDT.  The RSDT must
 *              already be loaded and validated.
 *
 ******************************************************************************/

ACPI_STATUS
TbInstallTable (
    char                    *TablePtr,
    ACPI_TABLE_DESC         *TableInfo)
{
    ACPI_TABLE_HEADER       *TableHeader = NULL;
    ACPI_STATUS             Status = AE_OK;
    ACPI_TABLE_TYPE         TableType;
    void                    **TableGlobalPtr;


    FUNCTION_TRACE ("TbInstallTable");


    /* Ensure that we have a valid table pointer */

    TableHeader = (ACPI_TABLE_HEADER *) TableInfo->Pointer;
    if (!TableHeader)
    {   
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /* 
     * Determine the table type from the 4-character signature 
     */

    if (!STRNCMP (TableHeader->Signature, FACP_SIG, 4))
    {
        TableType       = TABLE_FACP;
        TableGlobalPtr  = (void **) &Gbl_FACP;
    }

    else if (!STRNCMP (TableHeader->Signature, FACS_SIG, 4))
    {
        TableType       = TABLE_FACS;
        TableGlobalPtr  = (void **) &Gbl_FACS;
    }

    else if (!STRNCMP (TableHeader->Signature, DSDT_SIG, 4))
    {
        TableType       = TABLE_DSDT;
        TableGlobalPtr  = (void **) &Gbl_DSDT;
    }
    
    else if (!STRNCMP (TableHeader->Signature, APIC_SIG, 4))
    {
        /* APIC table */

        TableType       = TABLE_APIC;
        TableGlobalPtr  = (void **) &Gbl_APIC;
    }

    else if (!STRNCMP (TableHeader->Signature, PSDT_SIG, 4))
    {
        /* PSDT table [Supports multiple tables] */

        TableType       = TABLE_PSDT;
        TableGlobalPtr  = NULL;
    }

    else if (!STRNCMP (TableHeader->Signature, SSDT_SIG, 4))
    {
        /* SSDT table [Supports multiple tables] */

        TableType       = TABLE_SSDT;
        TableGlobalPtr  = NULL;
    }


    else if (!STRNCMP (TableHeader->Signature, SBST_SIG, 4))
    {
        /* SBST table */

        TableType       = TABLE_SBST;
        TableGlobalPtr  = (void **) &Gbl_SBST;
    }

    else if (!STRNCMP (TableHeader->Signature, BOOT_SIG, 4))
    {
        /* 
         * BOOT table
         * Although this is a known table, there is nothing we need to do with it
         */

        return_ACPI_STATUS (AE_BAD_SIGNATURE);
    }

    else
    {
        /* Unknown table */

        DEBUG_PRINT (ACPI_ERROR, ("Unknown table at %x in RSDT with signature '%4.4s'\n",
                                TableHeader, TableHeader->Signature));
        REPORT_ERROR ("Unknown table in the RSDT");

        TbVerifyTableChecksum (TableHeader);
    
        /* 
         * TBD: - need to be able to handle multiple unknown tables.  Error should be
         * displayed when table is displayed,  Displaying it here for now 
         */
    
        DUMP_BUFFER (TableHeader, 32, 0);

        return_ACPI_STATUS (AE_BAD_SIGNATURE);
    }


    /* 
     * Common table installation code 
     */


    /* Save the table pointers and allocation info */

    Status = TbInstallAcpiTable (TableType, TableInfo);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    if (TableGlobalPtr)
    {
        *TableGlobalPtr = TableHeader;
    }

    DEBUG_PRINT (ACPI_INFO, ("%s located at %p\n", 
                                Gbl_AcpiTableNames[TableType], TableHeader));

    /* Validate checksum for _most_ tables */

    if (TableType != TABLE_FACS)
    {
        TbVerifyTableChecksum (TableHeader);
    }


    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    TbInstallAcpiTable
 *
 * PARAMETERS:  TableType           - The type of the table
 *              TableInfo           - A table info struct
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Install a table into the global data structs.
 *
 ***************************************************************************/

ACPI_STATUS
TbInstallAcpiTable (
    ACPI_TABLE_TYPE         TableType,
    ACPI_TABLE_DESC         *TableInfo)
{
    ACPI_TABLE_DESC         *ListHead;
    ACPI_TABLE_DESC         *TableDesc;


    FUNCTION_TRACE ("TbInstallAcpiTable");


    ListHead    = &Gbl_AcpiTables[TableType];
    TableDesc   = ListHead;
   
    if (Gbl_AcpiTableFlags[TableType] == ACPI_TABLE_SINGLE)
    {
        if (ListHead->Pointer)
        {
            TbFreeAcpiTable (ListHead);
        }

        TableDesc->Count = 1;
    }


    else 
    {
        if (ListHead->Pointer)
        {
            TableDesc = CmCallocate (sizeof (ACPI_TABLE_DESC));
            if (!TableDesc)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            ListHead->Count++;

            /* Update original previous */

            ListHead->Prev->Next = TableDesc;

            /* Update new entry */

            TableDesc->Prev = ListHead->Prev;
            TableDesc->Next = (ACPI_TABLE_DESC *) ListHead;

            /* Update list head */

            ListHead->Prev = TableDesc;
        }

        else
        {
            TableDesc->Count = 1;
        }
    }


    /* Common initialization of the table descriptor */

    TableDesc->Pointer      = TableInfo->Pointer;
    TableDesc->Length       = TableInfo->Length;
    TableDesc->Allocation   = TableInfo->Allocation;


    return_ACPI_STATUS (AE_OK);
}


