
/******************************************************************************
 * 
 * Module Name: tbutils - Table manipulation utilities
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

#define __TBUTILS_C__

#include <acpi.h>
#include <tables.h>


#define _THIS_MODULE        "tbutils.c"
#define _COMPONENT          TABLE_MANAGER




/*****************************************************************************
 * 
 * FUNCTION:    TbSystemTablePointer
 *
 * PARAMETERS:  *Where              - Pointer to be examined
 *
 * RETURN:      TRUE if Where is within the AML stream (in one of the ACPI
 *              system tables such as the DSDT or an SSDT.)
 *              FALSE otherwise
 *
 ****************************************************************************/

BOOLEAN
TbSystemTablePointer (
    void                    *Where)
{
    UINT32                  i;
    ACPI_TABLE_DESC         *TableDesc;
    ACPI_TABLE_HEADER       *Table;


    /* No function trace, called too often! */


    /* Ignore null pointer */

    if (!Where)
    {
        return (FALSE);
    }


    /* Check for a pointer within the DSDT */

    if (IS_IN_ACPI_TABLE (Where, Gbl_DSDT))
    {
        return (TRUE);
    }


    /* Check each of the loaded SSDTs (if any)*/

    TableDesc = &Gbl_AcpiTables[TABLE_SSDT];

    for (i = 0; i < Gbl_AcpiTables[TABLE_SSDT].Count; i++)
    {
        Table = TableDesc->Pointer;

        if (IS_IN_ACPI_TABLE (Where, Table))
        {
            return (TRUE);
        }

        TableDesc = TableDesc->Next;
    }


    /* TBD: Need to check the PSDTs? */


    return (FALSE);
}



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
 * FUNCTION:    TbVerifyTableChecksum
 *
 * PARAMETERS:  *TableHeader            - ACPI table to verify
 *
 * RETURN:      8 bit checksum of table
 *
 * DESCRIPTION: Does an 8 bit checksum of table and returns status.  A correct
 *              table should have a checksum of 0.
 *
 ******************************************************************************/

ACPI_STATUS
TbVerifyTableChecksum (
    void                    *TableHeader)
{
    UINT8                   CheckSum;
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("TbVerifyTableChecksum");


    /* Compute the checksum on the table */

    CheckSum = TbChecksum (TableHeader,
                        (ACPI_SIZE) ((ACPI_TABLE_HEADER *) TableHeader)->Length);

    /* Return the appropriate exception */

    if (CheckSum)
    {
        REPORT_ERROR ("Invalid ACPI table checksum");
        DEBUG_PRINT (ACPI_INFO, ("TbVerifyTableChecksum: Invalid checksum (%X)\n", CheckSum));

        Status = AE_BAD_CHECKSUM;
    }


    return_ACPI_STATUS (Status);
}


/******************************************************************************
 *
 * FUNCTION:    TbChecksum
 *
 * PARAMETERS:  Buffer              - Buffer to checksum
 *              Length              - Size of the buffer
 *
 * RETURNS      8 bit checksum of buffer
 *
 * DESCRIPTION: Computes an 8 bit checksum of the buffer(length) and returns it. 
 *
 ******************************************************************************/

UINT8
TbChecksum (
    void                    *Buffer, 
    UINT32                  Length)
{
    UINT8                   *limit;
    UINT8                   *rover;
    UINT8                   sum = 0;


    if (Buffer && Length)
    {   
        /*  Buffer and Length are valid   */
        
        limit = (UINT8 *) Buffer + Length;

        for (rover = Buffer; rover < limit; rover++)
        {
            sum += *rover;
        }
    }

    return sum;
}




