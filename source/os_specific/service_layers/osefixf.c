/******************************************************************************
 *
 * Module Name: osefixf - EFI OSL interfaces
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2015, Intel Corp.
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


/* Local definitions */

#define ACPI_EFI_PRINT_LENGTH   256

#define ACPI_EFI_KEY_ESC        0x0000
#define ACPI_EFI_KEY_BACKSPACE  0x0008
#define ACPI_EFI_KEY_ENTER      0x000D
#define ACPI_EFI_KEY_CTRL_C     0x0003

#define ACPI_EFI_ASCII_NULL     0x00
#define ACPI_EFI_ASCII_DEL      0x7F
#define ACPI_EFI_ASCII_ESC      0x1B
#define ACPI_EFI_ASCII_CR       '\r'
#define ACPI_EFI_ASCII_NL       '\n'


/* Local prototypes */

static ACPI_STATUS
AcpiEfiArgify (
    char                    *String,
    int                     *ArgcPtr,
    char                    ***ArgvPtr);

static BOOLEAN
AcpiEfiCompareGuid (
    EFI_GUID                *Guid1,
    EFI_GUID                *Guid2);

static ACPI_STATUS
AcpiEfiConvertArgcv (
    CHAR16                  *LoadOpt,
    UINT32                  LoadOptSize,
    int                     *ArgcPtr,
    char                    ***ArgvPtr,
    char                    **BufferPtr);

static ACPI_STATUS
AcpiEfiGetFileInfo (
    ACPI_FILE               File,
    EFI_FILE_INFO           **InfoPtr);

static ACPI_PHYSICAL_ADDRESS
AcpiEfiGetRsdpViaGuid (
    EFI_GUID                *Guid);

static CHAR16 *
AcpiEfiFlushFile (
    ACPI_FILE               File,
    CHAR16                  *Begin,
    CHAR16                  *End,
    CHAR16                  *Pos,
    BOOLEAN                 FlushAll);


/* Local variables */

static EFI_FILE_HANDLE      AcpiGbl_EfiCurrentVolume = NULL;


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
    EFI_GUID                *Guid1,
    EFI_GUID                *Guid2)
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
    EFI_GUID                *Guid)
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
    EFI_GUID                Guid10 = ACPI_TABLE_GUID;
    EFI_GUID                Guid20 = ACPI_20_TABLE_GUID;


    Address = AcpiEfiGetRsdpViaGuid (&Guid20);
    if (!Address)
    {
        Address = AcpiEfiGetRsdpViaGuid (&Guid10);
    }

    return (Address);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsPredefinedOverride
 *
 * PARAMETERS:  InitVal             - Initial value of the predefined object
 *              NewVal              - The new value for the object
 *
 * RETURN:      Status, pointer to value. Null pointer returned if not
 *              overriding.
 *
 * DESCRIPTION: Allow the OS to override predefined names
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsPredefinedOverride (
    const ACPI_PREDEFINED_NAMES *InitVal,
    ACPI_STRING                 *NewVal)
{

    if (!InitVal || !NewVal)
    {
        return (AE_BAD_PARAMETER);
    }

    *NewVal = NULL;
    return (AE_OK);
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
 * FUNCTION:    Single threaded stub interfaces
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

ACPI_STATUS
AcpiOsCreateSemaphore (
    UINT32              MaxUnits,
    UINT32              InitialUnits,
    ACPI_HANDLE         *OutHandle)
{
    *OutHandle = (ACPI_HANDLE) 1;
    return (AE_OK);
}

ACPI_STATUS
AcpiOsDeleteSemaphore (
    ACPI_HANDLE         Handle)
{
    return (AE_OK);
}

ACPI_STATUS
AcpiOsWaitSemaphore (
    ACPI_HANDLE         Handle,
    UINT32              Units,
    UINT16              Timeout)
{
    return (AE_OK);
}

ACPI_STATUS
AcpiOsSignalSemaphore (
    ACPI_HANDLE         Handle,
    UINT32              Units)
{
    return (AE_OK);
}

ACPI_THREAD_ID
AcpiOsGetThreadId (
    void)
{
    return (1);
}

ACPI_STATUS
AcpiOsExecute (
    ACPI_EXECUTE_TYPE       Type,
    ACPI_OSD_EXEC_CALLBACK  Function,
    void                    *Context)
{
    return (AE_OK);
}

void
AcpiOsWaitEventsComplete (
    void)
{
    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsInstallInterruptHandler
 *
 * PARAMETERS:  InterruptNumber     - Level handler should respond to.
 *              ServiceRoutine      - Address of the ACPI interrupt handler
 *              Context             - Where status is returned
 *
 * RETURN:      Handle to the newly installed handler.
 *
 * DESCRIPTION: Install an interrupt handler. Used to install the ACPI
 *              OS-independent handler.
 *
 *****************************************************************************/

UINT32
AcpiOsInstallInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine,
    void                    *Context)
{

    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsRemoveInterruptHandler
 *
 * PARAMETERS:  InterruptNumber     - Level handler should respond to.
 *              ServiceRoutine      - Address of the ACPI interrupt handler
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Uninstalls an interrupt handler.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsRemoveInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine)
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
    UINT64                  *Value,
    UINT32                  Width)
{

    *Value = 0;
    return (AE_OK);
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
    UINT64                  Value,
    UINT32                  Width)
{

    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadPort
 *
 * PARAMETERS:  Address             - Address of I/O port/register to read
 *              Value               - Where value is placed
 *              Width               - Number of bits
 *
 * RETURN:      Value read from port
 *
 * DESCRIPTION: Read data from an I/O port or register
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsReadPort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  *Value,
    UINT32                  Width)
{

    switch (Width)
    {
    case 8:

        *Value = 0xFF;
        break;

    case 16:

        *Value = 0xFFFF;
        break;

    case 32:

        *Value = 0xFFFFFFFF;
        break;

    default:

        return (AE_BAD_PARAMETER);
    }

    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWritePort
 *
 * PARAMETERS:  Address             - Address of I/O port/register to write
 *              Value               - Value to write
 *              Width               - Number of bits
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write data to an I/O port or register
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsWritePort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  Value,
    UINT32                  Width)
{

    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadMemory
 *
 * PARAMETERS:  Address             - Physical Memory Address to read
 *              Value               - Where value is placed
 *              Width               - Number of bits (8,16,32, or 64)
 *
 * RETURN:      Value read from physical memory address. Always returned
 *              as a 64-bit integer, regardless of the read width.
 *
 * DESCRIPTION: Read data from a physical memory address
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsReadMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  *Value,
    UINT32                  Width)
{

    switch (Width)
    {
    case 8:
    case 16:
    case 32:
    case 64:

        *Value = 0;
        break;

    default:

        return (AE_BAD_PARAMETER);
    }
    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWriteMemory
 *
 * PARAMETERS:  Address             - Physical Memory Address to write
 *              Value               - Value to write
 *              Width               - Number of bits (8,16,32, or 64)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write data to a physical memory address
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsWriteMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  Value,
    UINT32                  Width)
{

    return (AE_OK);
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
    EFI_STATUS              EfiStatus;
    void                    *Mem;


    EfiStatus = uefi_call_wrapper (BS->AllocatePool, 3,
        EfiLoaderData, Size, &Mem);
    if (EFI_ERROR (EfiStatus))
    {
        AcpiLogError ("EFI_BOOT_SERVICES->AllocatePool(EfiLoaderData) failure.\n");
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
        ACPI_MEMSET (Mem, 0, Size);
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


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsOpenFile
 *
 * PARAMETERS:  Path                - File path
 *              Modes               - File operation type
 *
 * RETURN:      File descriptor
 *
 * DESCRIPTION: Open a file for reading (ACPI_FILE_READING) or/and writing
 *              (ACPI_FILE_WRITING).
 *
 ******************************************************************************/

ACPI_FILE
AcpiOsOpenFile (
    const char              *Path,
    UINT8                   Modes)
{
    EFI_STATUS              EfiStatus = EFI_SUCCESS;
    UINT64                  OpenModes;
    EFI_FILE_HANDLE         EfiFile = NULL;
    CHAR16                  *Path16 = NULL;
    CHAR16                  *Pos16;
    const char              *Pos;
    INTN                    Count, i;
    ACPI_FILE               File = NULL;


    if (!Path)
    {
        return (NULL);
    }

    /* Convert modes */

    OpenModes = EFI_FILE_MODE_READ;
    if (Modes & ACPI_FILE_WRITING)
    {
        OpenModes |= (EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE);
    }

    /* Allocate path buffer */

    Count = ACPI_STRLEN (Path);
    Path16 = ACPI_ALLOCATE_ZEROED ((Count + 1) * sizeof (CHAR16));
    if (!Path16)
    {
        EfiStatus = EFI_BAD_BUFFER_SIZE;
        goto ErrorExit;
    }
    Pos = Path;
    Pos16 = Path16;
    while (*Pos == '/' || *Pos == '\\')
    {
        Pos++;
        Count--;
    }
    for (i = 0; i < Count; i++)
    {
        if (*Pos == '/')
        {
            *Pos16++ = '\\';
            Pos++;
        }
        else
        {
            *Pos16++ = *Pos++;
        }
    }
    *Pos16 = '\0';

    EfiStatus = uefi_call_wrapper (AcpiGbl_EfiCurrentVolume->Open, 5,
        AcpiGbl_EfiCurrentVolume, &EfiFile, Path16, OpenModes, 0);
    if (EFI_ERROR (EfiStatus))
    {
        AcpiLogError ("EFI_FILE_HANDLE->Open() failure.\n");
        goto ErrorExit;
    }
    File = (ACPI_FILE) EfiFile;
    if (Modes & ACPI_FILE_APPENDING)
    {
        AcpiOsSetFileOffset (File, 0, ACPI_FILE_END);
    }

ErrorExit:

    if (Path16)
    {
        ACPI_FREE (Path16);
    }

    return (File);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsCloseFile
 *
 * PARAMETERS:  File                - File descriptor
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Close a file.
 *
 ******************************************************************************/

void
AcpiOsCloseFile (
    ACPI_FILE               File)
{
    EFI_FILE_HANDLE         EfiFile;


    if (File == ACPI_FILE_IN || File == ACPI_FILE_OUT ||
        File == ACPI_FILE_ERR)
    {
        return;
    }
    EfiFile = (EFI_FILE_HANDLE) File;
    (void) uefi_call_wrapper (AcpiGbl_EfiCurrentVolume->Close, 1, EfiFile);

    return;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsGetFileCharacter
 *
 * PARAMETERS:  File                - File descriptor
 *
 * RETURN:      The character read or EOF on the end of the file or error
 *
 * DESCRIPTION: Read a character from the file.
 *
 ******************************************************************************/

int
AcpiOsGetFileCharacter (
    ACPI_FILE               File)
{
    UINT8                   Byte;
    int                     Length;


    Length = AcpiOsReadFile (File, ACPI_CAST_PTR (void, &Byte), 1, 1);
    if (Length == 0)
    {
        Length = EOF;
    }
    else if (Length == 1)
    {
        Length = (int) Byte;
    }

    return (Length);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsPutFileCharacter
 *
 * PARAMETERS:  File                - File descriptor
 *              c                   - Character byte
 *
 * RETURN:      The character written or EOF on the end of the file or error
 *
 * DESCRIPTION: Write a character to the file.
 *
 ******************************************************************************/

int
AcpiOsPutFileCharacter (
    ACPI_FILE               File,
    char                    c)
{
    UINT8                   Byte = (UINT8) c;
    int                     Length;


    Length = AcpiOsWriteFile (File, ACPI_CAST_PTR (void, &Byte), 1, 1);
    if (Length == 0)
    {
        Length = EOF;
    }
    else if (Length == 1)
    {
        Length = (int) Byte;
    }

    return (Length);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsGetFileString
 *
 * PARAMETERS:  File                - File descriptor
 *
 * RETURN:      The string read
 *
 * DESCRIPTION: Read a string from the file.
 *
 ******************************************************************************/

char *
AcpiOsGetFileString (
    char                    *s,
    ACPI_SIZE               Size,
    ACPI_FILE               File)
{
    ACPI_SIZE               ReadBytes = 0;
    int                     Ret;


    if (Size <= 1)
    {
        AcpiLogError ("Invalid AcpiOsGetFileString() buffer size: %u.\n",
                (UINT32) Size);
        return (NULL);
    }
    while (ReadBytes < (Size - 1))
    {
        Ret = AcpiOsGetFileCharacter (File);
        if (Ret == EOF)
        {
            if (ReadBytes == 0)
            {
                return (NULL);
            }
            break;
        }
        else if (Ret < 0)
        {
            return (NULL);
        }
        else if (Ret == '\n')
        {
            s[ReadBytes++] = (char) Ret;
            break;
        }
        else
        {
            s[ReadBytes++] = (char) Ret;
        }
    }

    s[ReadBytes] = '\0';
    return (s);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsReadFile
 *
 * PARAMETERS:  File                - File descriptor
 *              Buffer              - Data buffer
 *              Size                - Data block size
 *              Count               - Number of data blocks
 *
 * RETURN:      Size of successfully read buffer
 *
 * DESCRIPTION: Read from a file.
 *
 ******************************************************************************/

int
AcpiOsReadFile (
    ACPI_FILE               File,
    void                    *Buffer,
    ACPI_SIZE               Size,
    ACPI_SIZE               Count)
{
    int                     Length = -EINVAL;
    EFI_FILE_HANDLE         EfiFile;
    SIMPLE_INPUT_INTERFACE  *In;
    UINTN                   ReadSize;
    EFI_STATUS              EfiStatus;
    EFI_INPUT_KEY           Key;
    ACPI_SIZE               Pos = 0;


    if (!Buffer)
    {
        goto ErrorExit;
    }

    ReadSize = Size * Count;

    if (File == ACPI_FILE_OUT || File == ACPI_FILE_ERR)
    {
        /* Do not support read operations on output console */
    }
    else if (File == ACPI_FILE_IN)
    {
        In = ACPI_CAST_PTR (SIMPLE_INPUT_INTERFACE, File);

        while (Pos < ReadSize)
        {
WaitKey:
            EfiStatus = uefi_call_wrapper (In->ReadKeyStroke, 2, In, &Key);
            if (EFI_ERROR (EfiStatus))
            {
                if (EfiStatus == EFI_NOT_READY)
                {
                    goto WaitKey;
                }
                AcpiLogError ("SIMPLE_INPUT_INTERFACE->ReadKeyStroke() failure.\n");
                goto ErrorExit;
            }

            switch (Key.UnicodeChar)
            {
            case ACPI_EFI_KEY_CTRL_C:

                break;

            case ACPI_EFI_KEY_ENTER:

                *(ACPI_ADD_PTR (UINT8, Buffer, Pos)) = (UINT8) ACPI_EFI_ASCII_CR;
                if (Pos < ReadSize - 1)
                {
                    /* Drop CR in case we don't have sufficient buffer */

                    Pos++;
                }
                *(ACPI_ADD_PTR (UINT8, Buffer, Pos)) = (UINT8) ACPI_EFI_ASCII_NL;
                Pos++;
                break;

            case ACPI_EFI_KEY_BACKSPACE:

                *(ACPI_ADD_PTR (UINT8, Buffer, Pos)) = (UINT8) ACPI_EFI_ASCII_DEL;
                Pos++;
                break;

            case ACPI_EFI_KEY_ESC:

                *(ACPI_ADD_PTR (UINT8, Buffer, Pos)) = (UINT8) ACPI_EFI_ASCII_ESC;
                Pos++;
                break;

            default:

                *(ACPI_ADD_PTR (UINT8, Buffer, Pos)) = (UINT8) Key.UnicodeChar;
                Pos++;
                break;
            }
        }
        Length = Pos;
    }
    else
    {
        EfiFile = (EFI_FILE_HANDLE) File;
        if (!EfiFile)
        {
            goto ErrorExit;
        }

        EfiStatus = uefi_call_wrapper (AcpiGbl_EfiCurrentVolume->Read, 3,
            EfiFile, &ReadSize, Buffer);
        if (EFI_ERROR (EfiStatus))
        {
            AcpiLogError ("EFI_FILE_HANDLE->Read() failure.\n");
            goto ErrorExit;
        }
        Length = ReadSize;
    }

ErrorExit:

    return (Length);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEfiFlushFile
 *
 * PARAMETERS:  File                - File descriptor
 *              Begin               - String with boundary
 *              End                 - Boundary of the string
 *              Pos                 - Current position
 *              FlushAll            - Whether checking boundary before flushing
 *
 * RETURN:      Updated position
 *
 * DESCRIPTION: Flush cached buffer to the file.
 *
 ******************************************************************************/

static CHAR16 *
AcpiEfiFlushFile (
    ACPI_FILE               File,
    CHAR16                  *Begin,
    CHAR16                  *End,
    CHAR16                  *Pos,
    BOOLEAN                 FlushAll)
{
    SIMPLE_TEXT_OUTPUT_INTERFACE *Out;


    if (File == ACPI_FILE_OUT || File == ACPI_FILE_ERR)
    {
        Out = ACPI_CAST_PTR (SIMPLE_TEXT_OUTPUT_INTERFACE, File);

        if (FlushAll || Pos >= (End - 1))
        {
            *Pos = 0;
            uefi_call_wrapper (Out->OutputString, 2, Out, Begin);
            Pos = Begin;
        }
    }

    return (Pos);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsWriteFile
 *
 * PARAMETERS:  File                - File descriptor
 *              Buffer              - Data buffer
 *              Size                - Data block size
 *              Count               - Number of data blocks
 *
 * RETURN:      Size of successfully written buffer
 *
 * DESCRIPTION: Write to a file.
 *
 ******************************************************************************/

int
AcpiOsWriteFile (
    ACPI_FILE               File,
    void                    *Buffer,
    ACPI_SIZE               Size,
    ACPI_SIZE               Count)
{
    int                     Length = -EINVAL;
    CHAR16                  String[ACPI_EFI_PRINT_LENGTH];
    const char              *Ascii;
    CHAR16                  *End;
    CHAR16                  *Pos;
    int                     i, j;
    EFI_FILE_HANDLE         EfiFile;
    UINTN                   WriteSize;
    EFI_STATUS              EfiStatus;


    if (File == ACPI_FILE_IN)
    {
        /* Do not support write operations on input console */
    }
    else if (File == ACPI_FILE_OUT || File == ACPI_FILE_ERR)
    {
        Pos = String;
        End = String + ACPI_EFI_PRINT_LENGTH - 1;
        Ascii = ACPI_CAST_PTR (const char, Buffer);
        Length = 0;

        for (j = 0; j < Count; j++)
        {
            for (i = 0; i < Size; i++)
            {
                if (*Ascii == '\n')
                {
                    *Pos++ = '\r';
                    Pos = AcpiEfiFlushFile (File, String,
                            End, Pos, FALSE);
                }
                *Pos++ = *Ascii++;
                Length++;
                Pos = AcpiEfiFlushFile (File, String,
                        End, Pos, FALSE);
            }
        }
        Pos = AcpiEfiFlushFile (File, String, End, Pos, TRUE);
    }
    else
    {
        EfiFile = (EFI_FILE_HANDLE) File;
        if (!EfiFile)
        {
            goto ErrorExit;
        }
        WriteSize = Size * Count;

        EfiStatus = uefi_call_wrapper (AcpiGbl_EfiCurrentVolume->Write, 3,
            EfiFile, &WriteSize, Buffer);
        if (EFI_ERROR (EfiStatus))
        {
            AcpiLogError ("EFI_FILE_HANDLE->Write() failure.\n");
            goto ErrorExit;
        }
        Length = WriteSize;
    }

ErrorExit:

    return (Length);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEfiGetFileInfo
 *
 * PARAMETERS:  File                - File descriptor
 *              InfoPtr             - Pointer to contain file information
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get file information.
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiEfiGetFileInfo (
    ACPI_FILE               File,
    EFI_FILE_INFO           **InfoPtr)
{
    EFI_STATUS              EfiStatus = EFI_BUFFER_TOO_SMALL;
    EFI_FILE_INFO           *Buffer = NULL;
    UINTN                   BufferSize = SIZE_OF_EFI_FILE_INFO + 200;
    EFI_FILE_HANDLE         EfiFile;


    if (!InfoPtr)
    {
        return (AE_BAD_PARAMETER);
    }

    while (EfiStatus == EFI_BUFFER_TOO_SMALL)
    {
        EfiFile = ACPI_CAST_PTR (EFI_FILE, File);
        Buffer = AcpiOsAllocate (BufferSize);
        if (!Buffer)
        {
            return (AE_NO_MEMORY);
        }
        EfiStatus = uefi_call_wrapper (EfiFile->GetInfo, 4, EfiFile,
            &GenericFileInfo, &BufferSize, Buffer);
        if (EFI_ERROR (EfiStatus))
        {
            AcpiOsFree (Buffer);
            if (EfiStatus != EFI_BUFFER_TOO_SMALL)
            {
                return (AE_ERROR);
            }
        }
    }

    *InfoPtr = Buffer;
    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsGetFileOffset
 *
 * PARAMETERS:  File                - File descriptor
 *
 * RETURN:      current position
 *
 * DESCRIPTION: Get current file offset.
 *
 ******************************************************************************/

long
AcpiOsGetFileOffset (
    ACPI_FILE               File)
{
    long                    Offset = -1;
    UINT64                  Current;
    EFI_STATUS              EfiStatus;
    EFI_FILE_HANDLE         EfiFile;


    if (File == ACPI_FILE_IN || File == ACPI_FILE_OUT ||
        File == ACPI_FILE_ERR)
    {
        Offset = 0;
    }
    else
    {
        EfiFile = ACPI_CAST_PTR (EFI_FILE, File);

        EfiStatus = uefi_call_wrapper (EfiFile->GetPosition, 2,
            EfiFile, &Current);
        if (EFI_ERROR (EfiStatus))
        {
            goto ErrorExit;
        }
        else
        {
            Offset = (long) Current;
        }
    }

ErrorExit:
    return (Offset);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsSetFileOffset
 *
 * PARAMETERS:  File                - File descriptor
 *              Offset              - File offset
 *              From                - From begin/end of file
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Set current file offset.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiOsSetFileOffset (
    ACPI_FILE               File,
    long                    Offset,
    UINT8                   From)
{
    EFI_FILE_INFO           *Info;
    ACPI_STATUS             Status;
    ACPI_SIZE               Size;
    UINT64                  Current;
    EFI_STATUS              EfiStatus;
    EFI_FILE_HANDLE         EfiFile;


    if (File == ACPI_FILE_IN || File == ACPI_FILE_OUT ||
        File == ACPI_FILE_ERR)
    {
        return (AE_OK);
    }
    else
    {
        EfiFile = ACPI_CAST_PTR (EFI_FILE, File);
        Status = AcpiEfiGetFileInfo (File, &Info);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }
        Size = Info->FileSize;
        AcpiOsFree (Info);

        if (From == ACPI_FILE_CURRENT_POSITION)
        {
            EfiStatus = uefi_call_wrapper (EfiFile->GetPosition, 2,
                EfiFile, &Current);
            if (EFI_ERROR (EfiStatus))
            {
                return (AE_LIMIT);
            }
            Current += Offset;
        }
        else if (From == ACPI_FILE_END)
        {
            Current = Size - Offset;
        }
        else
        {
            Current = Offset;
        }

        EfiStatus = uefi_call_wrapper (EfiFile->SetPosition, 2,
            EfiFile, Current);
        if (EFI_ERROR (EfiStatus))
        {
            return (AE_LIMIT);
        }
    }

    return (AE_OK);
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

    (void) ACPI_VFPRINTF (ACPI_FILE_OUT, Format, Args);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsInitialize, AcpiOsTerminate
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize/terminate this module.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsInitialize (
    void)
{

    return (AE_OK);
}

ACPI_STATUS
AcpiOsTerminate (
    void)
{

    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsSignal
 *
 * PARAMETERS:  Function            - ACPI A signal function code
 *              Info                - Pointer to function-dependent structure
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Miscellaneous functions. Example implementation only.
 *
 *****************************************************************************/

ACPI_STATUS
AcpiOsSignal (
    UINT32                  Function,
    void                    *Info)
{

    switch (Function)
    {
    case ACPI_SIGNAL_FATAL:

        break;

    case ACPI_SIGNAL_BREAKPOINT:

        break;

    default:

        break;
    }

    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsReadable
 *
 * PARAMETERS:  Pointer             - Area to be verified
 *              Length              - Size of area
 *
 * RETURN:      TRUE if readable for entire length
 *
 * DESCRIPTION: Verify that a pointer is valid for reading
 *
 *****************************************************************************/

BOOLEAN
AcpiOsReadable (
    void                    *Pointer,
    ACPI_SIZE               Length)
{

    return (TRUE);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiOsWritable
 *
 * PARAMETERS:  Pointer             - Area to be verified
 *              Length              - Size of area
 *
 * RETURN:      TRUE if writable for entire length
 *
 * DESCRIPTION: Verify that a pointer is valid for writing
 *
 *****************************************************************************/

BOOLEAN
AcpiOsWritable (
    void                    *Pointer,
    ACPI_SIZE               Length)
{

    return (TRUE);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiEfiArgify
 *
 * PARAMETERS:  String              - Pointer to command line argument strings
 *                                    which are seperated with spaces
 *              ArgcPtr             - Return number of the arguments
 *              ArgvPtr             - Return vector of the arguments
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert EFI arguments into C arguments.
 *
 *****************************************************************************/

static ACPI_STATUS
AcpiEfiArgify (
    char                    *String,
    int                     *ArgcPtr,
    char                    ***ArgvPtr)
{
    char                    *CopyBuffer;
    int                     MaxArgc = *ArgcPtr;
    int                     Argc = 0;
    char                    **Argv = *ArgvPtr;
    char                    *Arg;
    BOOLEAN                 IsSingleQuote = FALSE;
    BOOLEAN                 IsDoubleQuote = FALSE;
    BOOLEAN                 IsEscape = FALSE;


    if (String == NULL)
    {
        return (AE_BAD_PARAMETER);
    }

    CopyBuffer = String;

    while (*String != '\0')
    {
        while (ACPI_IS_SPACE (*String))
        {
            *String++ = '\0';
        }
        Arg = CopyBuffer;
        while (*String != '\0')
        {
            if (ACPI_IS_SPACE (*String) &&
                !IsSingleQuote && !IsDoubleQuote && !IsEscape)
            {
                *Arg++ = '\0';
                String++;
                break;
            }
            if (IsEscape)
            {
                IsEscape = FALSE;
                *Arg++ = *String;
            }
            else if (*String == '\\')
            {
                IsEscape = TRUE;
            }
            else if (IsSingleQuote)
            {
                if (*String == '\'')
                {
                    IsSingleQuote = FALSE;
                    *Arg++ = '\0';
                }
                else
                {
                    *Arg++ = *String;
                }
            }
            else if (IsDoubleQuote)
            {
                if (*String == '"')
                {
                    IsDoubleQuote = FALSE;
                    *Arg = '\0';
                }
                else
                {
                    *Arg++ = *String;
                }
            }
            else
            {
                if (*String == '\'')
                {
                    IsSingleQuote = TRUE;
                }
                else if (*String == '"')
                {
                    IsDoubleQuote = TRUE;
                }
                else
                {
                    *Arg++ = *String;
                }
            }
            String++;
        }
        if (Argv && Argc < MaxArgc)
        {
            Argv[Argc] = CopyBuffer;
        }
        Argc++;
        CopyBuffer = Arg;
    }
    if (Argv && Argc < MaxArgc)
    {
        Argv[Argc] = NULL;
    }

    *ArgcPtr = Argc;
    *ArgvPtr = Argv;

    return ((MaxArgc < Argc) ? AE_NO_MEMORY : AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiEfiConvertArgcv
 *
 * PARAMETERS:  LoadOptions         - Pointer to the EFI options buffer, which
 *                                    is NULL terminated
 *              LoadOptionsSize     - Size of the EFI options buffer
 *              ArgcPtr             - Return number of the arguments
 *              ArgvPtr             - Return vector of the arguments
 *              BufferPtr           - Buffer to contain the argument strings
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert EFI arguments into C arguments.
 *
 *****************************************************************************/

static ACPI_STATUS
AcpiEfiConvertArgcv (
    CHAR16                  *LoadOptions,
    UINT32                  LoadOptionsSize,
    int                     *ArgcPtr,
    char                    ***ArgvPtr,
    char                    **BufferPtr)
{
    ACPI_STATUS             Status = AE_OK;
    UINT32                  Count = LoadOptionsSize / sizeof (CHAR16);
    UINT32                  i;
    CHAR16                  *From;
    char                    *To;
    int                     Argc = 0;
    char                    **Argv = NULL;
    char                    *Buffer;


    /* Prepare a buffer to contain the argument strings */

    Buffer = ACPI_ALLOCATE_ZEROED (Count);
    if (!Buffer)
    {
        Status = AE_NO_MEMORY;
        goto ErrorExit;
    }

TryAgain:

    /* Extend the argument vector */

    if (Argv)
    {
        ACPI_FREE (Argv);
        Argv = NULL;
    }
    if (Argc > 0)
    {
        Argv = ACPI_ALLOCATE_ZEROED (sizeof (char *) * (Argc + 1));
        if (!Argv)
        {
            Status = AE_NO_MEMORY;
            goto ErrorExit;
        }
    }

    /*
     * Note: As AcpiEfiArgify() will modify the content of the buffer, so
     *       we need to restore it each time before invoking
     *       AcpiEfiArgify().
     */
    From = LoadOptions;
    To = ACPI_CAST_PTR (char, Buffer);
    for (i = 0; i < Count; i++)
    {
        *To++ = (char) *From++;
    }

    /*
     * The "Buffer" will contain NULL terminated strings after invoking
     * AcpiEfiArgify(). The number of the strings are saved in Argc and the
     * pointers of the strings are saved in Argv.
     */
    Status = AcpiEfiArgify (Buffer, &Argc, &Argv);
    if (ACPI_FAILURE (Status))
    {
        if (Status == AE_NO_MEMORY)
        {
            goto TryAgain;
        }
    }

ErrorExit:

    if (ACPI_FAILURE (Status))
    {
        ACPI_FREE (Buffer);
        ACPI_FREE (Argv);
    }
    else
    {
        *ArgcPtr = Argc;
        *ArgvPtr = Argv;
        *BufferPtr = Buffer;
    }
    return (Status);
}


/******************************************************************************
 *
 * FUNCTION:    efi_main
 *
 * PARAMETERS:  Image               - EFI image handle
 *              SystemTab           - EFI system table
 *
 * RETURN:      EFI Status
 *
 * DESCRIPTION: Entry point of EFI executable
 *
 *****************************************************************************/

EFI_STATUS
efi_main (
    EFI_HANDLE              Image,
    EFI_SYSTEM_TABLE        *SystemTab)
{
    EFI_LOADED_IMAGE        *Info;
    EFI_STATUS              EfiStatus = EFI_SUCCESS;
    ACPI_STATUS             Status;
    int                     argc;
    char                    **argv = NULL;
    char                    *OptBuffer = NULL;
    EFI_FILE_IO_INTERFACE   *Volume = NULL;


    /* Initialize EFI library */

    InitializeLib (Image, SystemTab);

    /* Disable the platform watchdog timer if we go interactive */

    uefi_call_wrapper(BS->SetWatchdogTimer, 4, 0, 0x0, 0, NULL);

    /* Retrieve image information */

    EfiStatus = uefi_call_wrapper (BS->HandleProtocol, 3,
        Image, &LoadedImageProtocol, ACPI_CAST_PTR (VOID, &Info));
    if (EFI_ERROR (EfiStatus))
    {
        AcpiLogError ("EFI_BOOT_SERVICES->HandleProtocol(LoadedImageProtocol) failure.\n");
        return (EfiStatus);
    }
    EfiStatus = uefi_call_wrapper (BS->HandleProtocol, 3,
        Info->DeviceHandle, &FileSystemProtocol, (void **) &Volume);
    if (EFI_ERROR (EfiStatus))
    {
        AcpiLogError ("EFI_BOOT_SERVICES->HandleProtocol(FileSystemProtocol) failure.\n");
        return (EfiStatus);
    }
    EfiStatus = uefi_call_wrapper (Volume->OpenVolume, 2,
        Volume, &AcpiGbl_EfiCurrentVolume);
    if (EFI_ERROR (EfiStatus))
    {
        AcpiLogError ("EFI_FILE_IO_INTERFACE->OpenVolume() failure.\n");
        return (EfiStatus);
    }

    Status = AcpiEfiConvertArgcv (Info->LoadOptions,
        Info->LoadOptionsSize, &argc, &argv, &OptBuffer);
    if (ACPI_FAILURE (Status))
    {
        EfiStatus = EFI_DEVICE_ERROR;
        goto ErrorAlloc;
    }

    acpi_main (argc, argv);

ErrorAlloc:

    if (argv)
    {
        ACPI_FREE (argv);
    }
    if (OptBuffer)
    {
        ACPI_FREE (OptBuffer);
    }

    return (EfiStatus);
}
