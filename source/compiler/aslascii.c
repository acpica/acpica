/******************************************************************************
 *
 * Module Name: aslascii - ASCII detection and support routines
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

#include "aslcompiler.h"
#include <acapps.h>

#define _COMPONENT          ACPI_COMPILER
        ACPI_MODULE_NAME    ("aslascii")


/* Local prototypes */

static void
FlConsumeAnsiComment (
    FILE                    *Handle,
    ASL_FILE_STATUS         *Status);

static void
FlConsumeNewComment (
    FILE                    *Handle,
    ASL_FILE_STATUS         *Status);


/*******************************************************************************
 *
 * FUNCTION:    FlCheckForAcpiTable
 *
 * PARAMETERS:  Handle              - Open input file
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Determine if a file seems to be a binary ACPI table, via the
 *              following checks on what would be the table header:
 *              0) File must be at least as long as an ACPI_TABLE_HEADER
 *              1) The header length field must match the file size
 *              2) Signature, OemId, OemTableId, AslCompilerId must be ASCII
 *
 ******************************************************************************/

ACPI_STATUS
FlCheckForAcpiTable (
    FILE                    *Handle)
{
    ACPI_TABLE_HEADER       Table;
    UINT32                  FileSize;
    size_t                  Actual;
    UINT32                  i;


    /* Read a potential table header */

    Actual = fread (&Table, 1, sizeof (ACPI_TABLE_HEADER), Handle);
    fseek (Handle, 0, SEEK_SET);

    if (Actual < sizeof (ACPI_TABLE_HEADER))
    {
        return (AE_ERROR);
    }

    /* Header length field must match the file size */

    FileSize = CmGetFileSize (Handle);
    if (Table.Length != FileSize)
    {
        return (AE_ERROR);
    }

    /*
     * These fields must be ASCII:
     * Signature, OemId, OemTableId, AslCompilerId.
     * We allow a NULL terminator in OemId and OemTableId.
     */
    for (i = 0; i < ACPI_NAME_SIZE; i++)
    {
        if (!ACPI_IS_ASCII ((UINT8) Table.Signature[i]))
        {
            return (AE_ERROR);
        }

        if (!ACPI_IS_ASCII ((UINT8) Table.AslCompilerId[i]))
        {
            return (AE_ERROR);
        }
    }

    for (i = 0; (i < ACPI_OEM_ID_SIZE) && (Table.OemId[i]); i++)
    {
        if (!ACPI_IS_ASCII ((UINT8) Table.OemId[i]))
        {
            return (AE_ERROR);
        }
    }

    for (i = 0; (i < ACPI_OEM_TABLE_ID_SIZE) && (Table.OemTableId[i]); i++)
    {
        if (!ACPI_IS_ASCII ((UINT8) Table.OemTableId[i]))
        {
            return (AE_ERROR);
        }
    }

    printf ("Binary file appears to be a valid ACPI table, disassembling\n");
    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    FlCheckForAscii
 *
 * PARAMETERS:  Handle              - Open input file
 *              Filename            - Input filename
 *              DisplayErrors       - TRUE if error messages desired
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Verify that the input file is entirely ASCII. Ignores characters
 *              within comments. Note: does not handle nested comments and does
 *              not handle comment delimiters within string literals. However,
 *              on the rare chance this happens and an invalid character is
 *              missed, the parser will catch the error by failing in some
 *              spectactular manner.
 *
 ******************************************************************************/

ACPI_STATUS
FlCheckForAscii (
    FILE                    *Handle,
    char                    *Filename,
    BOOLEAN                 DisplayErrors)
{
    UINT8                   Byte;
    ACPI_SIZE               BadBytes = 0;
    BOOLEAN                 OpeningComment = FALSE;
    ASL_FILE_STATUS         Status;


    Status.Line = 1;
    Status.Offset = 0;

    /* Read the entire file */

    while (fread (&Byte, 1, 1, Handle) == 1)
    {
        /* Ignore comment fields (allow non-ascii within) */

        if (OpeningComment)
        {
            /* Check for second comment open delimiter */

            if (Byte == '*')
            {
                FlConsumeAnsiComment (Handle, &Status);
            }

            if (Byte == '/')
            {
                FlConsumeNewComment (Handle, &Status);
            }

            /* Reset */

            OpeningComment = FALSE;
        }
        else if (Byte == '/')
        {
            OpeningComment = TRUE;
        }

        /* Check for an ASCII character */

        if (!ACPI_IS_ASCII (Byte))
        {
            if ((BadBytes < 10) && (DisplayErrors))
            {
                AcpiOsPrintf (
                    "Non-ASCII character [0x%2.2X] found in line %u, file offset 0x%.2X\n",
                    Byte, Status.Line, Status.Offset);
            }

            BadBytes++;
        }

        /* Update line counter */

        else if (Byte == 0x0A)
        {
            Status.Line++;
        }

        Status.Offset++;
    }

    /* Seek back to the beginning of the source file */

    fseek (Handle, 0, SEEK_SET);

    /* Were there any non-ASCII characters in the file? */

    if (BadBytes)
    {
        if (DisplayErrors)
        {
            AcpiOsPrintf (
                "%u non-ASCII characters found in input source text, could be a binary file\n",
                BadBytes);
            AslError (ASL_ERROR, ASL_MSG_NON_ASCII, NULL, Filename);
        }

        return (AE_BAD_CHARACTER);
    }

    /* File is OK (100% ASCII) */

    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    FlConsumeAnsiComment
 *
 * PARAMETERS:  Handle              - Open input file
 *              Status              - File current status struct
 *
 * RETURN:      Number of lines consumed
 *
 * DESCRIPTION: Step over a normal slash-star type comment
 *
 ******************************************************************************/

static void
FlConsumeAnsiComment (
    FILE                    *Handle,
    ASL_FILE_STATUS         *Status)
{
    UINT8                   Byte;
    BOOLEAN                 ClosingComment = FALSE;


    while (fread (&Byte, 1, 1, Handle) == 1)
    {
        /* Scan until comment close is found */

        if (ClosingComment)
        {
            if (Byte == '/')
            {
                return;
            }

            if (Byte != '*')
            {
                /* Reset */

                ClosingComment = FALSE;
            }
        }
        else if (Byte == '*')
        {
            ClosingComment = TRUE;
        }

        /* Maintain line count */

        if (Byte == 0x0A)
        {
            Status->Line++;
        }

        Status->Offset++;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    FlConsumeNewComment
 *
 * PARAMETERS:  Handle              - Open input file
 *              Status              - File current status struct
 *
 * RETURN:      Number of lines consumed
 *
 * DESCRIPTION: Step over a slash-slash type of comment
 *
 ******************************************************************************/

static void
FlConsumeNewComment (
    FILE                    *Handle,
    ASL_FILE_STATUS         *Status)
{
    UINT8                   Byte;


    while (fread (&Byte, 1, 1, Handle) == 1)
    {
        Status->Offset++;

        /* Comment ends at newline */

        if (Byte == 0x0A)
        {
            Status->Line++;
            return;
        }
    }
}
