/******************************************************************************
 *
 * Module Name: osefixf - EFI OSL interfaces
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2017, Intel Corp.
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

#include "acpi.h"
#include "accommon.h"
#include "acapps.h"

#define _COMPONENT          ACPI_OS_SERVICES
        ACPI_MODULE_NAME    ("osefixf")


/* Local prototypes */

static BOOLEAN
AcpiEfiCompareGuid (
    ACPI_EFI_GUID           *Guid1,
    ACPI_EFI_GUID           *Guid2);

static ACPI_PHYSICAL_ADDRESS
AcpiEfiGetRsdpViaGuid (
    ACPI_EFI_GUID           *Guid);

static ACPI_EFI_PCI_IO *
AcpiEfiGetPciDev (
    ACPI_PCI_ID             *PciId);


/******************************************************************************
 *
 * FUNCTION:    AcpiEfiGetRsdpViaGuid
 *
 * PARAMETERS:  Guid1               - GUID to compare
 *              Guid2               - GUID to compare
 *
 * RETURN:      TRUE if Guid1 == Guid2
 *
 * DESCRIPTION: Compares two GUIDs
 *
 *****************************************************************************/

static BOOLEAN
AcpiEfiCompareGuid (
    ACPI_EFI_GUID           *Guid1,
    ACPI_EFI_GUID           *Guid2)
{
    INT32                   *g1;
    INT32                   *g2;
    INT32                   r;


    g1 = (INT32 *) Guid1;
    g2 = (INT32 *) Guid2;

    r  = g1[0] - g2[0];
    r |= g1[1] - g2[1];
    r |= g1[2] - g2[2];
    r |= g1[3] - g2[3];

    return (r ? FALSE : TRUE);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiEfiGetRsdpViaGuid
 *
 * PARAMETERS:  None
 *
 * RETURN:      RSDP address if found
 *
 * DESCRIPTION: Find RSDP address via EFI using specified GUID.
 *
 *****************************************************************************/

static ACPI_PHYSICAL_ADDRESS
AcpiEfiGetRsdpViaGuid (
    ACPI_EFI_GUID           *Guid)
{
    ACPI_PHYSICAL_ADDRESS   Address = 0;
    int                     i;


    for (i = 0; i < ST->NumberOfTableEntries; i++)
    {
        if (AcpiEfiCompareGuid (&ST->ConfigurationTable[i].VendorGuid, Guid))
        {
            Address = ACPI_PTR_TO_PHYSADDR (
                ST->ConfigurationTable[i].VendorTable);
            break;
        }
    }

    return (Address);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsGetRootPointer
 *
 * PARAMETERS:  None
 *
 * RETURN:      RSDP physical address
 *
 * DESCRIPTION: Gets the ACPI root pointer (RSDP)
 *
 *****************************************************************************/

ACPI_PHYSICAL_ADDRESS
AcpiOsGetRootPointer (
    void)
{
    ACPI_PHYSICAL_ADDRESS   Address;
    ACPI_EFI_GUID           Guid10 = ACPI_TABLE_GUID;
    ACPI_EFI_GUID           Guid20 = ACPI_20_TABLE_GUID;


    Address = AcpiEfiGetRsdpViaGuid (&Guid20);
    if (!Address)
    {
        Address = AcpiEfiGetRsdpViaGuid (&Guid10);
    }

    return (Address);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsMapMemory
 *
 * PARAMETERS:  where               - Physical address of memory to be mapped
 *              length              - How much memory to map
 *
 * RETURN:      Pointer to mapped memory. Null on error.
 *
 * DESCRIPTION: Map physical memory into caller's address space
 *
 *****************************************************************************/

void *
AcpiOsMapMemory (
    ACPI_PHYSICAL_ADDRESS   where,
    ACPI_SIZE               length)
{

    return (ACPI_TO_POINTER ((ACPI_SIZE) where));
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsUnmapMemory
 *
 * PARAMETERS:  where               - Logical address of memory to be unmapped
 *              length              - How much memory to unmap
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete a previously created mapping. Where and Length must
 *              correspond to a previous mapping exactly.
 *
 *****************************************************************************/

void
AcpiOsUnmapMemory (
    void                    *where,
    ACPI_SIZE               length)
{

    return;
}


/******************************************************************************
 *
 * FUNCTION:    Spinlock interfaces
 *
 * DESCRIPTION: No-op on single threaded BIOS
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsCreateLock (
    ACPI_SPINLOCK           *OutHandle)
{
    return (AE_OK);
}

void
AcpiOsDeleteLock (
    ACPI_SPINLOCK           Handle)
{
}

ACPI_CPU_FLAGS
AcpiOsAcquireLock (
    ACPI_SPINLOCK           Handle)
{
    return (0);
}

void
AcpiOsReleaseLock (
    ACPI_SPINLOCK           Handle,
    ACPI_CPU_FLAGS          Flags)
{
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsAllocate
 *
 * PARAMETERS:  Size                - Amount to allocate, in bytes
 *
 * RETURN:      Pointer to the new allocation. Null on error.
 *
 * DESCRIPTION: Allocate memory. Algorithm is dependent on the OS.
 *
 *****************************************************************************/

void *
AcpiOsAllocate (
    ACPI_SIZE               Size)
{
    ACPI_EFI_STATUS         EfiStatus;
    void                    *Mem;


    EfiStatus = uefi_call_wrapper (BS->AllocatePool, 3,
        AcpiEfiLoaderData, Size, &Mem);
    if (ACPI_EFI_ERROR (EfiStatus))
    {
        fprintf (stderr,
            "EFI_BOOT_SERVICES->AllocatePool(EfiLoaderData) failure.\n");
        return (NULL);
    }

    return (Mem);
}


#ifdef USE_NATIVE_ALLOCATE_ZEROED
/******************************************************************************
 *
 * FUNCTION:    AcpiOsAllocateZeroed
 *
 * PARAMETERS:  Size                - Amount to allocate, in bytes
 *
 * RETURN:      Pointer to the new allocation. Null on error.
 *
 * DESCRIPTION: Allocate and zero memory. Algorithm is dependent on the OS.
 *
 *****************************************************************************/

void *
AcpiOsAllocateZeroed (
    ACPI_SIZE               Size)
{
    void                    *Mem;


    Mem = AcpiOsAllocate (Size);
    if (Mem)
    {
        memset (Mem, 0, Size);
    }

    return (Mem);
}
#endif


/******************************************************************************
 *
 * FUNCTION:    AcpiOsFree
 *
 * PARAMETERS:  Mem                 - Pointer to previously allocated memory
 *
 * RETURN:      None
 *
 * DESCRIPTION: Free memory allocated via AcpiOsAllocate
 *
 *****************************************************************************/

void
AcpiOsFree (
    void                    *Mem)
{

    uefi_call_wrapper (BS->FreePool, 1, Mem);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsPrintf
 *
 * PARAMETERS:  Format, ...         - Standard printf format
 *
 * RETURN:      None
 *
 * DESCRIPTION: Formatted output.
 *
 *****************************************************************************/

void ACPI_INTERNAL_VAR_XFACE
AcpiOsPrintf (
    const char              *Format,
    ...)
{
    va_list                 Args;


    va_start (Args, Format);
    AcpiOsVprintf (Format, Args);
    va_end (Args);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsVprintf
 *
 * PARAMETERS:  Format              - Standard printf format
 *              Args                - Argument list
 *
 * RETURN:      None
 *
 * DESCRIPTION: Formatted output with arguments list pointer.
 *
 *****************************************************************************/

void
AcpiOsVprintf (
    const char              *Format,
    va_list                 Args)
{

    (void) vfprintf (ACPI_FILE_OUT, Format, Args);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsInitialize
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize this module.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsInitialize (
    void)
{

    return (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadPciConfiguration
 *
 * PARAMETERS:  PciId               - Seg/Bus/Dev
 *              PciRegister         - Device Register
 *              Value               - Buffer where value is placed
 *              Width               - Number of bits
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read data from PCI configuration space
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsReadPciConfiguration (
    ACPI_PCI_ID             *PciId,
    UINT32                  PciRegister,
    UINT64                  *Value64,
    UINT32                  Width)
{
    ACPI_EFI_PCI_IO         *PciIo;
    ACPI_EFI_STATUS         EfiStatus;
    UINT8                   Value8;
    UINT16                  Value16;
    UINT32                  Value32;


    *Value64 = 0;
    PciIo = AcpiEfiGetPciDev (PciId);
    if (PciIo == NULL)
    {
        return (AE_NOT_FOUND);
    }

    switch (Width)
    {
    case 8:
        EfiStatus = uefi_call_wrapper (PciIo->Pci.Read, 5, PciIo,
            AcpiEfiPciIoWidthUint8, PciRegister, 1, (VOID *) &Value8);
        *Value64 = Value8;
        break;

    case 16:
        EfiStatus = uefi_call_wrapper (PciIo->Pci.Read, 5, PciIo,
            AcpiEfiPciIoWidthUint16, PciRegister, 1, (VOID *) &Value16);
        *Value64 = Value16;
        break;

    case 32:
        EfiStatus = uefi_call_wrapper (PciIo->Pci.Read, 5, PciIo,
            AcpiEfiPciIoWidthUint32, PciRegister, 1, (VOID *) &Value32);
        *Value64 = Value32;
        break;

    case 64:
        EfiStatus = uefi_call_wrapper (PciIo->Pci.Read, 5, PciIo,
            AcpiEfiPciIoWidthUint64, PciRegister, 1, (VOID *) Value64);
        break;

    default:
        return (AE_BAD_PARAMETER);
    }

    return (ACPI_EFI_ERROR (EfiStatus)) ? (AE_ERROR) : (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWritePciConfiguration
 *
 * PARAMETERS:  PciId               - Seg/Bus/Dev
 *              PciRegister         - Device Register
 *              Value               - Value to be written
 *              Width               - Number of bits
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Write data to PCI configuration space
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsWritePciConfiguration (
    ACPI_PCI_ID             *PciId,
    UINT32                  PciRegister,
    UINT64                  Value64,
    UINT32                  Width)
{
    ACPI_EFI_PCI_IO         *PciIo;
    ACPI_EFI_STATUS         EfiStatus;
    UINT8                   Value8;
    UINT16                  Value16;
    UINT32                  Value32;


    PciIo = AcpiEfiGetPciDev (PciId);
    if (PciIo == NULL)
    {
        return (AE_NOT_FOUND);
    }

    switch (Width)
    {
    case 8:
        Value8 = (UINT8) Value64;
        EfiStatus = uefi_call_wrapper (PciIo->Pci.Write, 5, PciIo,
            AcpiEfiPciIoWidthUint8, PciRegister, 1, (VOID *) &Value8);
        break;

    case 16:
        Value16 = (UINT16) Value64;
        EfiStatus = uefi_call_wrapper (PciIo->Pci.Write, 5, PciIo,
            AcpiEfiPciIoWidthUint16, PciRegister, 1, (VOID *) &Value16);
        break;

    case 32:
        Value32 = (UINT32) Value64;
        EfiStatus = uefi_call_wrapper (PciIo->Pci.Write, 5, PciIo,
            AcpiEfiPciIoWidthUint32, PciRegister, 1, (VOID *) &Value32);
        break;

    case 64:
        EfiStatus = uefi_call_wrapper (PciIo->Pci.Write, 5, PciIo,
            AcpiEfiPciIoWidthUint64, PciRegister, 1, (VOID *) &Value64);
        break;

    default:
        return (AE_BAD_PARAMETER);
    }

    return (ACPI_EFI_ERROR (EfiStatus)) ? (AE_ERROR) : (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    AcpiEfiGetPciDev
 *
 * PARAMETERS:  PciId               - Seg/Bus/Dev
 *
 * RETURN:      ACPI_EFI_PCI_IO that matches PciId. Null on error.
 *
 * DESCRIPTION: Find ACPI_EFI_PCI_IO for the given PciId.
 *
 *****************************************************************************/

static ACPI_EFI_PCI_IO *
AcpiEfiGetPciDev (
    ACPI_PCI_ID             *PciId)
{
    ACPI_EFI_STATUS         EfiStatus;
    UINTN                   i;
    UINTN                   HandlesCount = 0;
    ACPI_EFI_HANDLE         *Handles = NULL;
    ACPI_EFI_GUID           EfiPciIoProtocol = ACPI_EFI_PCI_IO_PROTOCOL;
    ACPI_EFI_PCI_IO         *PciIoProtocol = NULL;
    UINTN                   Bus;
    UINTN                   Device;
    UINTN                   Function;
    UINTN                   Segment;


    EfiStatus = uefi_call_wrapper (BS->LocateHandleBuffer, 5, AcpiEfiByProtocol,
        &EfiPciIoProtocol, NULL, &HandlesCount, &Handles);
    if (ACPI_EFI_ERROR (EfiStatus))
    {
        return (NULL);
    }

    for (i = 0; i < HandlesCount; i++)
    {
        EfiStatus = uefi_call_wrapper (BS->HandleProtocol, 3, Handles[i],
            &EfiPciIoProtocol, (VOID **) &PciIoProtocol);
        if (!ACPI_EFI_ERROR (EfiStatus))
        {
            EfiStatus = uefi_call_wrapper (PciIoProtocol->GetLocation, 5,
                PciIoProtocol, &Segment, &Bus, &Device, &Function);
            if (!ACPI_EFI_ERROR (EfiStatus) &&
                Bus == PciId->Bus &&
                Device == PciId->Device &&
                Function == PciId->Function &&
                Segment == PciId->Segment)
            {
                uefi_call_wrapper (BS->FreePool, 1, Handles);
                return (PciIoProtocol);
            }
        }
    }

    uefi_call_wrapper (BS->FreePool, 1, Handles);
    return (NULL);
}
