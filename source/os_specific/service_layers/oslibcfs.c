/******************************************************************************
 *
 * Module Name: oslibcfs - C library OSL for file I/O
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
#include <stdio.h>
#include <stdarg.h>

#define _COMPONENT          ACPI_OS_SERVICES
        ACPI_MODULE_NAME    ("oslibcfs")


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsOpenFile
 *
 * PARAMETERS:  Path                - File path
 *              Modes               - File operation type
 *
 * RETURN:      File descriptor.
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
    ACPI_FILE               File;
    UINT32                  i = 0;
    char                    ModesStr[5];


    if (Modes & ACPI_FILE_READING)
    {
        ModesStr[i++] = 'r';
    }
    if (Modes & ACPI_FILE_WRITING)
    {
        ModesStr[i++] = 'w';
    }
    if (Modes & ACPI_FILE_BINARY)
    {
        ModesStr[i++] = 'b';
    }
    else if (Modes & ACPI_FILE_TEXT)
    {
        ModesStr[i++] = 't';
    }
    if (Modes & ACPI_FILE_APPENDING)
    {
        ModesStr[i++] = '+';
    }

    ModesStr[i++] = '\0';

    File = fopen (Path, ModesStr);
    if (!File)
    {
        perror ("Could not open file");
    }

    return (File);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsCloseFile
 *
 * PARAMETERS:  File                - An open file descriptor
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Close a file opened via AcpiOsOpenFile.
 *
 ******************************************************************************/

void
AcpiOsCloseFile (
    ACPI_FILE               File)
{
    fclose (File);
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
    int                     Ret;


    Ret = fgetc (File);
    if (Ret < 0 && ferror (File))
    {
        perror ("Error reading file");
    }

    return (Ret);
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
    const char              c)
{
    int                     Ret;


    Ret = fputc (c, File);
    if (Ret < 0 && ferror (File))
    {
        perror ("Error writing file");
    }

    return (Ret);
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
    char                    *Ret;


    Ret = fgets (s, Size, File);
    if (Ret == NULL && ferror (File))
    {
        perror ("Error reading file");
    }

    return (Ret);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsReadFile
 *
 * PARAMETERS:  File                - An open file descriptor
 *              Buffer              - Data buffer
 *              Size                - Data block size
 *              Count               - Number of data blocks
 *
 * RETURN:      Number of bytes actually read.
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
    int                     Length;


    Length = fread (Buffer, Size, Count, File);
    if (Length < 0)
    {
        perror ("Error reading file");
    }

    return (Length);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsWriteFile
 *
 * PARAMETERS:  File                - An open file descriptor
 *              Buffer              - Data buffer
 *              Size                - Data block size
 *              Count               - Number of data blocks
 *
 * RETURN:      Number of bytes actually written.
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
    int                     Length;


    Length = fwrite (Buffer, Size, Count, File);
    if (Length < 0)
    {
        perror ("Error writing file");
    }

    return (Length);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsGetFileOffset
 *
 * PARAMETERS:  File                - An open file descriptor
 *
 * RETURN:      Current file pointer position.
 *
 * DESCRIPTION: Get current file offset.
 *
 ******************************************************************************/

long
AcpiOsGetFileOffset (
    ACPI_FILE               File)
{
    long                    Offset;


    Offset = ftell (File);
    return (Offset);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiOsSetFileOffset
 *
 * PARAMETERS:  File                - An open file descriptor
 *              Offset              - New file offset
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
    int                     Ret = 0;


    if (From == ACPI_FILE_BEGIN)
    {
        Ret = fseek (File, Offset, SEEK_SET);
    }
    if (From == ACPI_FILE_END)
    {
        Ret = fseek (File, Offset, SEEK_END);
    }

    if (Ret < 0)
    {
        return (AE_ERROR);
    }
    else
    {
        return (AE_OK);
    }
}
