
/******************************************************************************
 *
 * Module Name: abcompare - compare AML files
 *              $Revision: 1.7 $
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

#include "acpibin.h"
#include <stdlib.h>


FILE                *File1;
FILE                *File2;
ACPI_TABLE_HEADER   Header1;
ACPI_TABLE_HEADER   Header2;


/******************************************************************************
 *
 * FUNCTION:    AbValidateHeader
 *
 * DESCRIPTION: Check for valid ACPI table header
 *
 ******************************************************************************/

BOOLEAN
AbValidateHeader (
    ACPI_TABLE_HEADER       *Header)
{

    if (!AcpiCmValidAcpiName (* (UINT32 *) &Header->Signature))
    {
        printf ("Header signature is invalid\n");
        return FALSE;
    }

    return TRUE;
}


/******************************************************************************
 *
 * FUNCTION:    AbCompareAmlFiles
 *
 * DESCRIPTION: Compare two AML files
 *
 ******************************************************************************/

int
AbCompareAmlFiles (
    char                    *File1Path,
    char                    *File2Path)
{
    UINT32                  Actual1;
    UINT32                  Actual2;
    UINT32                  Offset;
    UINT8                   Char1;
    UINT8                   Char2;
    UINT8                   Mismatches = 0;


    File1 = fopen (File1Path, "rb");
    if (!File1)
    {
        printf ("Could not open file %s\n", File1Path);
        return -1;
    }


    File2 = fopen (File2Path, "rb");
    if (!File2)
    {
        printf ("Could not open file %s\n", File2Path);
        return -1;
    }


    /* Read the ACPI header from each file */

    Actual1 = fread (&Header1, 1, sizeof (ACPI_TABLE_HEADER), File1);
    if (Actual1 < sizeof (ACPI_TABLE_HEADER))
    {
        printf ("File %s does not contain an ACPI table header\n", File1Path);
        return -1;
    }

    Actual2 = fread (&Header2, 1, sizeof (ACPI_TABLE_HEADER), File2);
    if (Actual2 < sizeof (ACPI_TABLE_HEADER))
    {
        printf ("File %s does not contain an ACPI table header\n", File2Path);
        return -1;
    }

    if ((!AbValidateHeader (&Header1)) ||
        (!AbValidateHeader (&Header2)))
    {
        return -1;
    }

    /* Table signatures must match */

    if ((UINT32) Header1.Signature != (UINT32) Header1.Signature)
    {
        printf ("Table signatures do not match\n");
        return -1;
    }


    if (!Gbl_TerseMode)
    {
        /* Display header information */

        printf ("Signature         : %8.4s  %8.4s\n",    Header1.Signature, Header2.Signature);
        printf ("Length            : %8.8X  %8.8X\n",    Header1.Length, Header2.Length);
        printf ("Revision          : % 8.2X  % 8.2X\n",  Header1.Revision, Header2.Revision);
        printf ("Checksum          : % 8.2X  % 8.2X\n",  Header1.Checksum, Header2.Checksum);
        printf ("OEM ID            : %8.6s  %8.6s\n",    Header1.OemId, Header2.OemId);
        printf ("OEM Table ID      : %8.8s  %8.8s\n",    Header1.OemTableId, Header2.OemTableId);
        printf ("OEM Revision      : %8.8X  %8.8X\n",    Header1.OemRevision, Header2.OemRevision);
        printf ("ASL Compiler ID   : %8.4s  %8.4s\n",    Header1.AslCompilerId, Header2.AslCompilerId);
        printf ("Compiler Revision : %8.8X  %8.8X\n",    Header1.AslCompilerRevision, Header2.AslCompilerRevision);
        printf ("\n");
    }

    /* Do the byte-by-byte compare */

    Actual1 = fread (&Char1, 1, 1, File1);
    Actual2 = fread (&Char2, 1, 1, File2);
    Offset = sizeof (ACPI_TABLE_HEADER);

    while (Actual1 && Actual2)
    {
        if (Char1 != Char2)
        {
            printf ("Error - Byte mismatch at offset %8.8X: 0x%2.2X 0x%2.2X\n", Offset, Char1, Char2);
            Mismatches++;
            if (Mismatches > 10)
            {
                printf ("10 Mismatches: Too many mismatches\n");
                return 0;
            }
        }

        Offset++;
        Actual1 = fread (&Char1, 1, 1, File1);
        Actual2 = fread (&Char2, 1, 1, File2);

    }


    if (Actual1)
    {
        printf ("Error - file %s is longer than file %s\n", File1Path, File2Path);
        Mismatches++;
    }
    else if (Actual2)
    {
        printf ("Error - file %s is shorter than file %s\n", File1Path, File2Path);
        Mismatches++;
    }
    else if (!Mismatches)
    {
        printf ("Files compare exactly after header\n");
    }

    printf ("%d Mismatches found\n", Mismatches);
    return 0;
}


struct stat              Gbl_StatBuf;


/******************************************************************************
 *
 * FUNCTION:    AsGetFile
 *
 * DESCRIPTION: Open a file and read it entirely into a an allocated buffer
 *
 ******************************************************************************/

char *
AbGetFile (
    char                    *Filename,
    UINT32                  *FileSize)
{

    int                     FileHandle;
    UINT32                  Size;
    char                    *Buffer = NULL;


    /* Binary mode leaves CR/LF pairs */

    FileHandle = open (Filename, O_BINARY | O_RDONLY);
    if (!FileHandle)
    {
        printf ("Could not open %s\n", Filename);
        return NULL;
    }

    if (fstat (FileHandle, &Gbl_StatBuf))
    {
        printf ("Could not get file status for %s\n", Filename);
        goto ErrorExit;
    }

    /*
     * Create a buffer for the entire file
     * Add 10% extra to accomodate string replacements
     */

    Size = Gbl_StatBuf.st_size;
    Buffer = calloc (Size + (Size / 10), 1);
    if (!Buffer)
    {
        printf ("Could not allocate buffer of size %d\n", Size + (Size / 10));
        goto ErrorExit;
    }

    /* Read the entire file */

    Size = read (FileHandle, Buffer, Size);
    if (Size == -1)
    {
        printf ("Could not read the input file %s\n", Filename);
        free (Buffer);
        Buffer = NULL;
        goto ErrorExit;
    }

    *FileSize = Size;

ErrorExit:
    close (FileHandle);

    return (Buffer);
}


int
AbDumpAmlFile (
    char                    *File1Path)
{
    char                    *FileBuffer;
    UINT32                  FileSize;


    FileBuffer = AbGetFile (File1Path, &FileSize);
    printf ("File %s contains 0x%X bytes\n\n", File1Path, FileSize);


    if (!AbValidateHeader ((ACPI_TABLE_HEADER *) FileBuffer))
    {
        return -1;
    }


    AcpiDbgLevel = ACPI_UINT32_MAX;
    AcpiCmDumpBuffer (FileBuffer, FileSize, DB_BYTE_DISPLAY, ACPI_UINT32_MAX);

    return 0;
}

#define DB_CONSOLE_OUTPUT       0x02

FILE                        *DebugFile = NULL;
UINT8                       AcpiGbl_DbOutputFlags = DB_CONSOLE_OUTPUT ;


void *
_CmCallocate (
    UINT32                  Size,
    UINT32                  Component,
    NATIVE_CHAR             *Module,
    UINT32                  Line)
{

    return NULL;
}

void
_CmFree (
    void                    *Address,
    UINT32                  Component,
    NATIVE_CHAR             *Module,
    UINT32                  Line)
{
    return;
}


void *
AcpiCmMemset (
    void                    *Dest,
    UINT32                  Value,
    NATIVE_UINT             Count)
{
    return (Dest);
}
