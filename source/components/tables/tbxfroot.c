
/******************************************************************************
 *
 * Module Name: tbtable - ACPI tables: FACP, FACS, and RSDP utilities
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

#define __TBTABLE_C__

#include "acpi.h"
#include "achware.h"
#include "actables.h"


#define _COMPONENT          TABLE_MANAGER
        MODULE_NAME         ("tbtable");


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbGetTableRsdt
 *
 * PARAMETERS:  NumberOfTables      - Where the table count is placed
 *              TablePtr            - Input buffer pointer, optional
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load and validate the RSDP (ptr) and RSDT (table)
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbGetTableRsdt (
    UINT32                  *NumberOfTables)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_TABLE_DESC         TableInfo;


    FUNCTION_TRACE ("TbGetTableRsdt");


    /* Get the RSDP */

    Status = AcpiTbFindRsdp (&TableInfo);
    if (ACPI_FAILURE (Status))
    {
        REPORT_WARNING ("RSDP structure not found");
        return_ACPI_STATUS (AE_NO_ACPI_TABLES);
    }

    /* Save the table pointers and allocation info */

    Status = AcpiTbInitTableDescriptor (ACPI_TABLE_RSDP, &TableInfo);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    AcpiGbl_RSDP = (ROOT_SYSTEM_DESCRIPTOR_POINTER *) TableInfo.Pointer;


    /*
     * RSDP structure was found;  Now get the RSDT
     */

    DEBUG_PRINT (ACPI_INFO,
        ("RSDP located at %p, RSDT physical=%p \n",
        AcpiGbl_RSDP, AcpiGbl_RSDP->RsdtPhysicalAddress));

    Status = AcpiTbGetTable ((void *) AcpiGbl_RSDP->RsdtPhysicalAddress, NULL,
                            &TableInfo);
    if (ACPI_FAILURE (Status))
    {
        DEBUG_PRINT (ACPI_ERROR,
            ("GetRsdt: Could not get the RSDT, %s\n",
            AcpiCmFormatException (Status)));

        if (Status == AE_BAD_SIGNATURE)
        {
            /* Invalid RSDT signature */

            REPORT_ERROR ("Invalid signature where RSDP indicates RSDT should be located");

            DUMP_BUFFER (AcpiGbl_RSDP, 20);

            DEBUG_PRINT_RAW (ACPI_ERROR,
                ("RSDP points to RSDT at %lXh, but RSDT signature is invalid\n",
                (void *) AcpiGbl_RSDP->RsdtPhysicalAddress));
        }
    }


    /* Always delete the RSDP mapping */

    AcpiTbDeleteAcpiTable (ACPI_TABLE_RSDP);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Save the table pointers and allocation info */

    Status = AcpiTbInitTableDescriptor (ACPI_TABLE_RSDT, &TableInfo);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    AcpiGbl_RSDT = (ROOT_SYSTEM_DESCRIPTION_TABLE *) TableInfo.Pointer;


    /* Valid RSDT signature, verify the checksum */

    DEBUG_PRINT (ACPI_INFO, ("RSDT located at %p\n", AcpiGbl_RSDT));

    Status = AcpiTbVerifyTableChecksum ((ACPI_TABLE_HEADER *) AcpiGbl_RSDT);

    /*
     * Determine the number of tables pointed to by the RSDT.
     * This is defined by the ACPI Specification to be the number of
     * pointers contained within the RSDT.  The size of the pointers
     * is architecture-dependent.
     */

    *NumberOfTables = ((AcpiGbl_RSDT->header.Length -
                        sizeof (ACPI_TABLE_HEADER)) / sizeof (void *));


    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbScanMemoryForRsdp
 *
 * PARAMETERS:  StartAddress        - Starting pointer for search
 *              Length              - Maximum length to search
 *
 * RETURN:      Pointer to the RSDP if found, otherwise NULL.
 *
 * DESCRIPTION: Search a block of memory for the RSDP signature
 *
 ******************************************************************************/

char *
AcpiTbScanMemoryForRsdp (
    char                    *StartAddress,
    UINT32                  Length)
{
    UINT32                  Offset;
    char                    *MemRover;


    /* Search from given start addr for the requested length  */

    for (Offset = 0, MemRover = StartAddress;
         Offset < Length;
         Offset += RSDP_SCAN_STEP, MemRover += RSDP_SCAN_STEP)
    {

        /* The signature and checksum must both be correct */

        if (STRNCMP (MemRover, RSDP_SIG, sizeof (RSDP_SIG)-1) == 0 &&
            AcpiTbChecksum (MemRover,
                sizeof (ROOT_SYSTEM_DESCRIPTOR_POINTER)) == 0)
        {
            /* If so, we have found the RSDP */

            return MemRover;
        }
    }

    /* Searched entire block, no RSDP was found */

    return NULL;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbFindRsdp
 *
 * PARAMETERS:  *BufferPtr              - If == NULL, read data from buffer
 *                                        rather than searching memory
 *              *TableInfo              - Where the table info is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Search lower 1Mbyte of memory for the root system descriptor
 *              pointer structure.  If it is found, set *RSDP to point to it.
 *
 *              NOTE: The RSDP must be either in the first 1K of the Extended
 *              BIOS Data Area or between E0000 and FFFFF (ACPI 1.0 section
 *              5.2.2; assertion #421).
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbFindRsdp (
    ACPI_TABLE_DESC         *TableInfo)
{
    char                    *TablePtr;
    char                    *MemRover;
    ACPI_STATUS             Status = AE_OK;

    FUNCTION_TRACE ("TbFindRsdp");

    if (AcpiGbl_AcpiInitData.RSDP_PhysicalAddress)
    {
        /*
         *  RSDP address was supplied as part of the initialization data
         */

        Status = AcpiOsMapMemory(AcpiGbl_AcpiInitData.RSDP_PhysicalAddress,
                                sizeof (ROOT_SYSTEM_DESCRIPTOR_POINTER),
                                (void **)&TablePtr);

        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        if (!TablePtr)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        /*
         *  The signature and checksum must both be correct
         */

        if (STRNCMP (TablePtr, RSDP_SIG, sizeof (RSDP_SIG)-1) != 0)
        {
            /* Nope, BAD Signature */

            return_ACPI_STATUS (AE_BAD_SIGNATURE);
        }

        /* The signature and checksum must both be correct */

        if (AcpiTbChecksum (TablePtr,
                sizeof (ROOT_SYSTEM_DESCRIPTOR_POINTER)) != 0)
        {
            /* Nope, BAD Checksum */

            return_ACPI_STATUS (AE_BAD_CHECKSUM);
        }

        /* RSDP supplied is OK */
        /* If so, we have found the RSDP */

        TableInfo->Pointer      = (ACPI_TABLE_HEADER *) TablePtr;
        TableInfo->Length       = sizeof (ROOT_SYSTEM_DESCRIPTOR_POINTER);
        TableInfo->Allocation   = ACPI_MEM_MAPPED;
        TableInfo->BasePointer  = TablePtr;

        return_ACPI_STATUS (AE_OK);
    }

    /*
     * Search memory for RSDP.  First map low physical memory.
     */

    Status = AcpiOsMapMemory (LO_RSDP_WINDOW_BASE, LO_RSDP_WINDOW_SIZE,
                                (void **)&TablePtr);

    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /*
     * 1) Search EBDA (low memory) paragraphs
     */

    if (NULL != (MemRover = AcpiTbScanMemoryForRsdp (TablePtr,
                                                        LO_RSDP_WINDOW_SIZE)))
    {
        /* Found it, return pointer and don't delete the mapping */

        TableInfo->Pointer      = (ACPI_TABLE_HEADER *) MemRover;
        TableInfo->Length       = LO_RSDP_WINDOW_SIZE;
        TableInfo->Allocation   = ACPI_MEM_MAPPED;
        TableInfo->BasePointer  = TablePtr;

        return_ACPI_STATUS (AE_OK);
    }

    /* This mapping is no longer needed */

    AcpiOsUnmapMemory (TablePtr, LO_RSDP_WINDOW_SIZE);


    /*
     * 2) Search upper memory: 16-byte boundaries in E0000h-F0000h
     */

    Status = AcpiOsMapMemory (HI_RSDP_WINDOW_BASE, HI_RSDP_WINDOW_SIZE,
                                (void **)&TablePtr);

    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    if (NULL != (MemRover = AcpiTbScanMemoryForRsdp (TablePtr,
                                                        HI_RSDP_WINDOW_SIZE)))
    {
        /* Found it, return pointer and don't delete the mapping */

        TableInfo->Pointer      = (ACPI_TABLE_HEADER *) MemRover;
        TableInfo->Length       = HI_RSDP_WINDOW_SIZE;
        TableInfo->Allocation   = ACPI_MEM_MAPPED;
        TableInfo->BasePointer  = TablePtr;

        return_ACPI_STATUS (AE_OK);
    }

    /* This mapping is no longer needed */

    AcpiOsUnmapMemory (TablePtr, HI_RSDP_WINDOW_SIZE);


    /* RSDP signature was not found */

    return_ACPI_STATUS (AE_NOT_FOUND);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiTbGetTableFacs
 *
 * PARAMETERS:  *BufferPtr              - If == NULL, read data from buffer
 *                                        rather than searching memory
 *              *TableInfo              - Where the table info is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Returns a pointer to the FACS as defined in FACP.  This
 *              function assumes the global variable FACP has been
 *              correctly initialized.  The value of FACP->FirmwareCtrl
 *              into a far pointer which is returned.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiTbGetTableFacs (
    char                    *BufferPtr,
    ACPI_TABLE_DESC         *TableInfo)
{
    void                    *TablePtr = NULL;
    UINT32                  Size;
    UINT8                   Allocation;
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("TbGetTableFacs");


    /* Must have a valid FACP pointer */

    if (!AcpiGbl_FACP)
    {
        return_ACPI_STATUS (AE_NO_ACPI_TABLES);
    }

    Size = sizeof (FIRMWARE_ACPI_CONTROL_STRUCTURE);
    if (BufferPtr)
    {
        /*
         * Getting table from a file -- allocate a buffer and
         * read the table.
         */
        TablePtr = AcpiCmAllocate (Size);
        if(!TablePtr)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        MEMCPY (TablePtr, BufferPtr, Size);

        /* Save allocation type */

        Allocation = ACPI_MEM_ALLOCATED;
    }

    else
    {
        /* Just map the physical memory to our address space */

        Status = AcpiTbMapAcpiTable ((void *) AcpiGbl_FACP->FirmwareCtrl,
                                        &Size, &TablePtr);
        if (ACPI_FAILURE(Status))
        {
            return_ACPI_STATUS (Status);
        }

        /* Save allocation type */

        Allocation = ACPI_MEM_MAPPED;
    }


    /* Return values */

    TableInfo->Pointer      = TablePtr;
    TableInfo->Length       = Size;
    TableInfo->Allocation   = Allocation;
    TableInfo->BasePointer  = TablePtr;

    return_ACPI_STATUS (Status);
}

