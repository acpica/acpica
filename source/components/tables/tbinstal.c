
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


#define _COMPONENT          TABLE_MANAGER
        MODULE_NAME         ("tbinstal");



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
 *              Install the table into the global data structs.
 *
 ******************************************************************************/

ACPI_STATUS
TbInstallTable (
    char                    *TablePtr,
    ACPI_TABLE_DESC         *TableInfo)
{
    ACPI_TABLE_TYPE         TableType;
    ACPI_TABLE_HEADER       *TableHeader;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("TbInstallTable");


    /* Check the table signature and make sure it is recognized */

    Status = TbRecognizeTable (TablePtr, TableInfo);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Table type is returned by RecognizeTable */

    TableType   = TableInfo->Type;
    TableHeader = TableInfo->Pointer;

    /* Lock tables while installing */

    CmAcquireMutex (MTX_TABLES);

    /* Install the table into the global data structure */

    Status = TbInitTableDescriptor (TableInfo->Type, TableInfo);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    DEBUG_PRINT (ACPI_INFO, ("%s located at %p\n", 
                                Gbl_AcpiTableData[TableType].Name, TableHeader));

    CmReleaseMutex (MTX_TABLES);

    /* Validate checksum for _most_ tables */

    if (TableType != TABLE_FACS)
    {
        /* But don't abort if the checksum is wrong */
        /* TBD: make this a configuration option? */

        TbVerifyTableChecksum (TableHeader);
    }


    return_ACPI_STATUS (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    TbRecognizeTable
 *
 * PARAMETERS:  TablePtr            - Input buffer pointer, optional
 *              TableInfo           - Return value from TbGetTable
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check a table signature for a match against known table types
 *
 ******************************************************************************/

ACPI_STATUS
TbRecognizeTable (
    char                    *TablePtr,
    ACPI_TABLE_DESC         *TableInfo)
{
    ACPI_TABLE_HEADER       *TableHeader;
    ACPI_STATUS             Status;
    ACPI_TABLE_TYPE         TableType = 0;
    UINT32                  i;

    
    FUNCTION_TRACE ("TbRecognizeTable");


    /* Ensure that we have a valid table pointer */

    TableHeader = (ACPI_TABLE_HEADER *) TableInfo->Pointer;
    if (!TableHeader)
    {   
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /* Search for a signature match among the known table types */

    Status = AE_BAD_SIGNATURE;
    for (i = 1; i < NUM_ACPI_TABLES; i++)       /* Start at one -> Skip RSDP */
    {
        if (!STRNCMP (TableHeader->Signature, Gbl_AcpiTableData[i].Signature, Gbl_AcpiTableData[i].SigLength))
        {
            /* Found a signature match, get the pertinent info from the TableData structure */

            TableType       = i;
            Status          = Gbl_AcpiTableData[i].Status;

            break;
        }
    }

    /* Return the table type and length via the info struct */

    TableInfo->Type = (UINT8) TableType;
    TableInfo->Length = TableHeader->Length;

    /*
     * Bad_Signature means that the table is bad or not one of the recognized tables
     */

    if (Status == AE_BAD_SIGNATURE)
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
    
        DUMP_BUFFER (TableHeader, 32);
    }


    /* 
     * An AE_SUPPORT means that the table was recognized, but is not supported
     */

    else if (Status == AE_SUPPORT)
    {
        DEBUG_PRINT (ACPI_INFO, ("Unsupported table %s (Type %d) was found and discarded\n",
                            Gbl_AcpiTableData[TableType].Name, TableType));
    }


    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    TbInitTableDescriptor
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
TbInitTableDescriptor (
    ACPI_TABLE_TYPE         TableType,
    ACPI_TABLE_DESC         *TableInfo)
{
    ACPI_TABLE_DESC         *ListHead;
    ACPI_TABLE_DESC         *TableDesc;


    FUNCTION_TRACE_U32 ("TbInitTableDescriptor", TableType);

    /*
     * Install the table into the global data structure 
     */
    
    ListHead    = &Gbl_AcpiTables[TableType];
    TableDesc   = ListHead;
   


    /*
     * Two major types of tables:  1) Only one instance is allowed.  This includes most
     * ACPI tables such as the DSDT.  2) Multiple instances of the table are allowed.  This
     * includes SSDT and PSDTs.
     */

    if (Gbl_AcpiTableData[TableType].Flags == ACPI_TABLE_SINGLE)
    {
        /*
         * Only one table allowed, just update the list head
         */

        if (ListHead->Pointer)
        {
            return_ACPI_STATUS (AE_EXIST);
        }

        TableDesc->Count = 1;
    }


    else 
    {
        /*
         * Multiple tables allowed for this table type, we must link
         * the new table in to the list of tables of this type.
         */

        if (ListHead->Pointer)
        {
            TableDesc = CmCallocate (sizeof (ACPI_TABLE_DESC));
            if (!TableDesc)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            ListHead->Count++;

            /* Update the original previous */

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

    TableDesc->Pointer              = TableInfo->Pointer;
    TableDesc->Length               = TableInfo->Length;
    TableDesc->Allocation           = TableInfo->Allocation;
    TableDesc->AmlPointer           = (UINT8 *) (TableDesc->Pointer + 1),
    TableDesc->AmlLength            = (UINT32) (TableDesc->Length - (UINT32) sizeof (ACPI_TABLE_HEADER));
    TableDesc->TableId              = Gbl_TbNextTableId;
    TableDesc->LoadedIntoNamespace  = FALSE;

    Gbl_TbNextTableId++;


    /* Set the appropriate global pointer (if there is one) to point to the newly installed table */

    if (Gbl_AcpiTableData[TableType].GlobalPtr)
    {
        *(Gbl_AcpiTableData[TableType].GlobalPtr) = TableInfo->Pointer;
    }


    return_ACPI_STATUS (AE_OK);
}


