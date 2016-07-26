/******************************************************************************
 *
 * Module Name: oseficlib - EFI specific CLibrary interfaces
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2016, Intel Corp.
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
        ACPI_MODULE_NAME    ("oseficlib")


/* Local definitions */

#define ACPI_EFI_PRINT_LENGTH   256


/* Local prototypes */

static int
AcpiEfiArgify (
    char                    *String,
    int                     *ArgcPtr,
    char                    ***ArgvPtr);

static int
AcpiEfiConvertArgcv (
    CHAR16                  *LoadOpt,
    UINT32                  LoadOptSize,
    int                     *ArgcPtr,
    char                    ***ArgvPtr,
    char                    **BufferPtr);

static CHAR16 *
AcpiEfiFlushFile (
    FILE                    *File,
    CHAR16                  *Begin,
    CHAR16                  *End,
    CHAR16                  *Pos,
    BOOLEAN                 FlushAll);


/* Local variables */

FILE                        *stdout = NULL;
FILE                        *stderr = NULL;
static ACPI_EFI_FILE_HANDLE AcpiGbl_EfiCurrentVolume = NULL;
ACPI_EFI_GUID               AcpiGbl_LoadedImageProtocol = ACPI_EFI_LOADED_IMAGE_PROTOCOL;
ACPI_EFI_GUID               AcpiGbl_TextInProtocol = ACPI_SIMPLE_TEXT_INPUT_PROTOCOL;
ACPI_EFI_GUID               AcpiGbl_TextOutProtocol = ACPI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
ACPI_EFI_GUID               AcpiGbl_FileSystemProtocol = ACPI_SIMPLE_FILE_SYSTEM_PROTOCOL;

int                         errno = 0;


/*******************************************************************************
 *
 * FUNCTION:    fopen
 *
 * PARAMETERS:  Path                - File path
 *              Modes               - File operation type
 *
 * RETURN:      File descriptor
 *
 * DESCRIPTION: Open a file for reading or/and writing.
 *
 ******************************************************************************/

FILE *
fopen (
    const char              *Path,
    const char              *Modes)
{
    ACPI_EFI_STATUS         EfiStatus = ACPI_EFI_SUCCESS;
    UINT64                  OpenModes;
    ACPI_EFI_FILE_HANDLE    EfiFile = NULL;
    CHAR16                  *Path16 = NULL;
    CHAR16                  *Pos16;
    const char              *Pos;
    INTN                    Count, i;
    BOOLEAN                 IsAppend = FALSE;
    FILE                    *File = NULL;


    if (!Path)
    {
        errno = EINVAL;
        return (NULL);
    }

    /*
     * Convert modes, EFI says the only 2 read/write modes are read-only,
     * read+write. Thus set default mode as read-only.
     */
    OpenModes = ACPI_EFI_FILE_MODE_READ;
    switch (*Modes++)
    {
    case 'r':

        break;

    case 'w':

        OpenModes |= (ACPI_EFI_FILE_MODE_WRITE | ACPI_EFI_FILE_MODE_CREATE);
        break;

    case 'a':

        OpenModes |= (ACPI_EFI_FILE_MODE_WRITE | ACPI_EFI_FILE_MODE_CREATE);
        IsAppend = TRUE;
        break;

    default:

        errno = EINVAL;
        return (NULL);
    }

    for (; *Modes; Modes++)
    {
        switch (*Modes)
        {
        case '+':

            OpenModes |= (ACPI_EFI_FILE_MODE_WRITE | ACPI_EFI_FILE_MODE_CREATE);
            break;

        case 'b':
        case 't':

            break;

        case 'f':
        default:

            break;
        }
    }

    /* Allocate path buffer */

    Count = strlen (Path);
    Path16 = ACPI_ALLOCATE_ZEROED ((Count + 1) * sizeof (CHAR16));
    if (!Path16)
    {
        EfiStatus = ACPI_EFI_BAD_BUFFER_SIZE;
        errno = ENOMEM;
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
    if (ACPI_EFI_ERROR (EfiStatus))
    {
        fprintf (stderr, "EFI_FILE_HANDLE->Open() failure.\n");
        errno = ENOENT;
        goto ErrorExit;
    }

    File = (FILE *) EfiFile;
    if (IsAppend)
    {
        fseek (File, 0, SEEK_END);
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
 * FUNCTION:    fclose
 *
 * PARAMETERS:  File                - File descriptor
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Close a file.
 *
 ******************************************************************************/

void
fclose (
    FILE                    *File)
{
    ACPI_EFI_FILE_HANDLE    EfiFile;


    if (File == stdout || File == stderr)
    {
        return;
    }
    EfiFile = (ACPI_EFI_FILE_HANDLE) File;
    (void) uefi_call_wrapper (AcpiGbl_EfiCurrentVolume->Close, 1, EfiFile);

    return;
}


/*******************************************************************************
 *
 * FUNCTION:    fread
 *
 * PARAMETERS:  Buffer              - Data buffer
 *              Size                - Data block size
 *              Count               - Number of data blocks
 *              File                - File descriptor
 *
 * RETURN:      Size of successfully read buffer
 *
 * DESCRIPTION: Read from a file.
 *
 ******************************************************************************/

int
fread (
    void                    *Buffer,
    ACPI_SIZE               Size,
    ACPI_SIZE               Count,
    FILE                    *File)
{
    int                     Length = -1;
    ACPI_EFI_FILE_HANDLE    EfiFile;
    UINTN                   ReadSize;
    ACPI_EFI_STATUS         EfiStatus;


    if (File == stdout || File == stderr)
    {
    }
    else
    {
        EfiFile = (ACPI_EFI_FILE_HANDLE) File;
        if (!EfiFile)
        {
            errno = EINVAL;
            goto ErrorExit;
        }
        ReadSize = Size * Count;

        EfiStatus = uefi_call_wrapper (AcpiGbl_EfiCurrentVolume->Read, 3,
            EfiFile, &ReadSize, Buffer);
        if (ACPI_EFI_ERROR (EfiStatus))
        {
            fprintf (stderr, "EFI_FILE_HANDLE->Read() failure.\n");
            errno = EIO;
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
    FILE                    *File,
    CHAR16                  *Begin,
    CHAR16                  *End,
    CHAR16                  *Pos,
    BOOLEAN                 FlushAll)
{

    if (FlushAll || Pos >= (End - 1))
    {
        *Pos = 0;
        uefi_call_wrapper (File->OutputString, 2, File, Begin);
        Pos = Begin;
    }

    return (Pos);
}


/*******************************************************************************
 *
 * FUNCTION:    fwrite
 *
 * PARAMETERS:  Buffer              - Data buffer
 *              Size                - Data block size
 *              Count               - Number of data blocks
 *              File                - File descriptor
 *
 * RETURN:      Size of successfully written buffer
 *
 * DESCRIPTION: Write to a file.
 *
 ******************************************************************************/

int
fwrite (
    void                    *Buffer,
    ACPI_SIZE               Size,
    ACPI_SIZE               Count,
    FILE                    *File)
{
    int                     Length = -1;
    CHAR16                  String[ACPI_EFI_PRINT_LENGTH];
    const char              *Ascii;
    CHAR16                  *End;
    CHAR16                  *Pos;
    int                     i, j;
    ACPI_EFI_FILE_HANDLE    EfiFile;
    UINTN                   WriteSize;
    ACPI_EFI_STATUS         EfiStatus;


    if (File == stdout || File == stderr)
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
        EfiFile = (ACPI_EFI_FILE_HANDLE) File;
        if (!EfiFile)
        {
            errno = EINVAL;
            goto ErrorExit;
        }
        WriteSize = Size * Count;

        EfiStatus = uefi_call_wrapper (AcpiGbl_EfiCurrentVolume->Write, 3,
            EfiFile, &WriteSize, Buffer);
        if (ACPI_EFI_ERROR (EfiStatus))
        {
            fprintf (stderr, "EFI_FILE_HANDLE->Write() failure.\n");
            errno = EIO;
            goto ErrorExit;
        }
        Length = WriteSize;
    }

ErrorExit:

    return (Length);
}


/*******************************************************************************
 *
 * FUNCTION:    ftell
 *
 * PARAMETERS:  File                - File descriptor
 *
 * RETURN:      Size of current position
 *
 * DESCRIPTION: Get current file offset.
 *
 ******************************************************************************/

long
ftell (
    FILE                    *File)
{
    long                    Offset = -1;


    return (Offset);
}


/*******************************************************************************
 *
 * FUNCTION:    fseek
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

int
fseek (
    FILE                    *File,
    long                    Offset,
    int                     From)
{

    return (-1);
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
 * RETURN:      Clibraray error code
 *              -EINVAL: invalid parameter
 *              EAGAIN: try again
 *
 * DESCRIPTION: Convert EFI arguments into C arguments.
 *
 *****************************************************************************/

static int
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
	errno = EINVAL;
        return (-EINVAL);
    }

    CopyBuffer = String;

    while (*String != '\0')
    {
        while (isspace (*String))
        {
            *String++ = '\0';
        }
        Arg = CopyBuffer;
        while (*String != '\0')
        {
            if (isspace (*String) &&
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

    if (MaxArgc < Argc)
    {
        errno = EAGAIN;
        return (-ENOMEM);
    }
    return (0);
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
 * RETURN:      Clibrary error code
 *
 * DESCRIPTION: Convert EFI arguments into C arguments.
 *
 *****************************************************************************/

static int
AcpiEfiConvertArgcv (
    CHAR16                  *LoadOptions,
    UINT32                  LoadOptionsSize,
    int                     *ArgcPtr,
    char                    ***ArgvPtr,
    char                    **BufferPtr)
{
    int                     Error = 0;
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
        errno = ENOMEM;
        Error = -ENOMEM;
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
            errno = ENOMEM;
            Error = -ENOMEM;
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
    Error = AcpiEfiArgify (Buffer, &Argc, &Argv);
    if (Error && errno == EAGAIN)
    {
        goto TryAgain;
    }

ErrorExit:

    if (Error)
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
    return (Error);
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

ACPI_EFI_STATUS
efi_main (
    ACPI_EFI_HANDLE         Image,
    ACPI_EFI_SYSTEM_TABLE   *SystemTab)
{
    ACPI_EFI_LOADED_IMAGE   *Info;
    ACPI_EFI_STATUS         EfiStatus = ACPI_EFI_SUCCESS;
    int                     Error;
    int                     argc;
    char                    **argv = NULL;
    char                    *OptBuffer = NULL;
    ACPI_EFI_FILE_IO_INTERFACE *Volume = NULL;


    /* Initialize global variables */

    ST = SystemTab;
    BS = SystemTab->BootServices;
    stdout = SystemTab->ConOut;
    stderr = SystemTab->ConOut;

    /* Retrieve image information */

    EfiStatus = uefi_call_wrapper (BS->HandleProtocol, 3,
        Image, &AcpiGbl_LoadedImageProtocol, ACPI_CAST_PTR (VOID, &Info));
    if (ACPI_EFI_ERROR (EfiStatus))
    {
        fprintf (stderr,
            "EFI_BOOT_SERVICES->HandleProtocol(LoadedImageProtocol) failure.\n");
        return (EfiStatus);
    }

    EfiStatus = uefi_call_wrapper (BS->HandleProtocol, 3,
        Info->DeviceHandle, &AcpiGbl_FileSystemProtocol, (void **) &Volume);
    if (ACPI_EFI_ERROR (EfiStatus))
    {
        fprintf (stderr,
            "EFI_BOOT_SERVICES->HandleProtocol(FileSystemProtocol) failure.\n");
        return (EfiStatus);
    }
    EfiStatus = uefi_call_wrapper (Volume->OpenVolume, 2,
        Volume, &AcpiGbl_EfiCurrentVolume);
    if (ACPI_EFI_ERROR (EfiStatus))
    {
        fprintf (stderr, "EFI_FILE_IO_INTERFACE->OpenVolume() failure.\n");
        return (EfiStatus);
    }

    Error = AcpiEfiConvertArgcv (Info->LoadOptions,
        Info->LoadOptionsSize, &argc, &argv, &OptBuffer);
    if (Error)
    {
        EfiStatus = ACPI_EFI_DEVICE_ERROR;
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

#ifdef _EDK2_EFI
struct _ACPI_EFI_SYSTEM_TABLE        *ST;
struct _ACPI_EFI_BOOT_SERVICES       *BS;
struct _ACPI_EFI_RUNTIME_SERVICES    *RT;

EFI_STATUS
EFIAPI
UefiMain (
    EFI_HANDLE              Image,
    EFI_SYSTEM_TABLE        *SystemTab)
{
    EFI_STATUS              EfiStatus;


    EfiStatus = (EFI_STATUS) efi_main (
        (ACPI_EFI_HANDLE) Image, (ACPI_EFI_SYSTEM_TABLE *) SystemTab);
    return (EfiStatus);
}
#endif
