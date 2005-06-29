
/******************************************************************************
 *
 * Module Name: aslfiles - file I/O suppoert
 *              $Revision: 1.15 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, 2001, Intel Corp.
 * All rights reserved.
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


#include "aslcompiler.h"

#define _COMPONENT          COMPILER
        MODULE_NAME         ("aslfiles")


/*******************************************************************************
 *
 * FUNCTION:    FlOpenLocalFile
 *
 * PARAMETERS:  LocalName           - Single filename (not a pathname)
 *              Mode                - Open mode for fopen
 *
 * RETURN:      File descriptor
 *
 * DESCRIPTION: Build a complete pathname for the input filename and open or
 *              create the file.
 *
 ******************************************************************************/

FILE *
FlOpenLocalFile (
    char                    *LocalName,
    char                    *Mode)
{

    strcpy (StringBuffer, Gbl_DirectoryPath);
    strcat (StringBuffer, LocalName);

    DbgPrint (ASL_PARSE_OUTPUT, "FlOpenLocalFile: %s\n", StringBuffer);
    return (fopen (StringBuffer, (const char *) Mode));

}


/*******************************************************************************
 *
 * FUNCTION:    FlOpenIncludeFile
 *
 * PARAMETERS:  Node        - Parse node for the INCLUDE ASL statement
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Open an include file and push it on the input file stack.
 *
 ******************************************************************************/

void
FlOpenIncludeFile (
    ASL_PARSE_NODE          *Node)
{
    FILE                    *IncFile;


    /* Node must be valid */

    if (!Node)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_INCLUDE_FILE_OPEN,
                    Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
                    Gbl_InputByteCount, Gbl_CurrentColumn, Gbl_InputFilename, " - Null parse node");
        return;
    }


    /*
     * Flush out the "include ()" statement on this line, start
     * the actual include file on the next line
     */
    ResetCurrentLineBuffer ();
    fprintf (Gbl_SourceOutputFile, "\n");
    Gbl_CurrentLineOffset++;

    /* Prepend the directory pathname and open the include file */

    DbgPrint (ASL_PARSE_OUTPUT, "\nOpen include file: path %s\n\n", Node->Value.String);
    IncFile = FlOpenLocalFile (Node->Value.String, "r");
    if (!IncFile)
    {
        AslError (ASL_ERROR, ASL_MSG_INCLUDE_FILE_OPEN, Node, Node->Value.String);
        return;
    }


    /* Push the include file on the open input file stack */

    AslPushInputFileStack (IncFile, Node->Value.String);
}


/*******************************************************************************
 *
 * FUNCTION:    FlGenerateFilename
 *
 * PARAMETERS:  InputFilename       - Original ASL source filename
 *              Suffix              - New extension.
 *
 * RETURN:      New filename containing the original base + the new suffix
 *
 * DESCRIPTION: Generate a new filename from the ASL source filename and a new
 *              extension.  Used to create the *.LST, *.TXT, etc. files.
 *
 ******************************************************************************/

char *
FlGenerateFilename (
    char                    *InputFilename,
    char                    *Suffix)
{
    char                    *Position;
    char                    *NewFilename;


    /* Copy the original filename to a new buffer */

    NewFilename = UtLocalCalloc (strlen (InputFilename) + strlen (Suffix));
    strcpy (NewFilename, InputFilename);

    /* Try to find the last dot in the filename */

    Position = strrchr (NewFilename, '.');
    if (Position)
    {
        /* Tack on the new suffix */
        Position++;
        *Position = 0;
        strcat (Position, Suffix);
    }

    else
    {
        /* No dot, add one and then the suffix */

        strcat (NewFilename, ".");
        strcat (NewFilename, Suffix);
    }

    return NewFilename;
}


/*******************************************************************************
 *
 * FUNCTION:    FlOpenInputFile
 *
 * PARAMETERS:  InputFilename       - The user-specified ASL source file to be
 *                                    compiled
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Open the specified input file, and save the directory path to
 *              the file so that include files and new files can be opened in
 *              the same directory.
 *
 ******************************************************************************/

ACPI_STATUS
FlOpenInputFile (
    char                    *InputFilename)
{
    char                    *Substring;


    /* Open the input ASL file, text mode */

    Gbl_AslInputFile = fopen (InputFilename, "r");
    AslCompilerin = Gbl_AslInputFile;
    if (!Gbl_AslInputFile)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_INPUT_FILE_OPEN, 0, 0, 0, 0, NULL, InputFilename);
        return (AE_ERROR);
    }


    /* Get the path to the input filename's directory */

    Gbl_DirectoryPath = strdup (InputFilename);
    Substring = strrchr (Gbl_DirectoryPath, '\\');
    if (!Substring)
    {
        Substring = strrchr (Gbl_DirectoryPath, '/');
        if (!Substring)
        {
            Substring = strrchr (Gbl_DirectoryPath, ':');
        }
    }

    if (!Substring)
    {
        Gbl_DirectoryPath[0] = 0;
    }

    else
    {
        *(Substring+1) = 0;
    }

    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    FlOpenAmlOutputFile
 *
 * PARAMETERS:  FilenamePrefix       - The user-specified ASL source file
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create the output filename (*.AML) and open the file.  The file
 *              is created in the same directory as the parent input file.
 *
 ******************************************************************************/

ACPI_STATUS
FlOpenAmlOutputFile (
    char                    *FilenamePrefix)
{


    /* Output filename usually comes from the ASL itself */

    if (!Gbl_OutputFilename)
    {
        /* Create the output AML filename */

        Gbl_OutputFilename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_AML_CODE);
        if (!Gbl_OutputFilename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_OUTPUT_FILENAME, 0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }
    }

    /* Open the output AML file in binary mode */

    Gbl_AmlOutputFile = fopen (Gbl_OutputFilename, "w+b");
    if (!Gbl_AmlOutputFile)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_OUTPUT_FILENAME, 0, 0, 0, 0, NULL, Gbl_OutputFilename);
        return (AE_ERROR);
    }

    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    FlOpenMiscOutputFiles
 *
 * PARAMETERS:  FilenamePrefix       - The user-specified ASL source file
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create and open the various output files needed, depending on
 *              the command line options
 *
 ******************************************************************************/

ACPI_STATUS
FlOpenMiscOutputFiles (
    char                    *FilenamePrefix)
{


    /* Create/Open a combined source output file if asked */

    Gbl_SourceOutputFilename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_SOURCE);
    if (!Gbl_SourceOutputFilename)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, 0, 0, NULL, NULL);
        return (AE_ERROR);
    }

    /* Open the debug file, text mode */

    Gbl_SourceOutputFile = fopen (Gbl_SourceOutputFilename, "w+");
    if (!Gbl_SourceOutputFile)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, 0, 0, NULL, Gbl_SourceOutputFilename);
        return (AE_ERROR);
    }


    /* Create/Open a listing output file if asked */

    if (Gbl_ListingFlag)
    {
        Gbl_ListingOutputFilename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_LISTING);
        if (!Gbl_ListingOutputFilename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the debug file, text mode */

        Gbl_ListingOutputFile = fopen (Gbl_ListingOutputFilename, "w+");
        if (!Gbl_ListingOutputFile)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, 0, 0, NULL, Gbl_ListingOutputFilename);
            return (AE_ERROR);
        }

        AslCompilerSignon (Gbl_ListingOutputFile);
        AslCompilerFileHeader (Gbl_ListingOutputFile);
    }


    /* Create/Open a hex output file if asked */

    if (Gbl_HexOutputFlag)
    {
        Gbl_HexOutputFilename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_HEX_DUMP);
        if (!Gbl_HexOutputFilename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the debug file, text mode */

        Gbl_HexOutputFile = fopen (Gbl_HexOutputFilename, "w+");
        if (!Gbl_HexOutputFile)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, 0, 0, NULL, Gbl_HexOutputFilename);
            return (AE_ERROR);
        }

        AslCompilerSignon (Gbl_HexOutputFile);
        AslCompilerFileHeader (Gbl_HexOutputFile);
    }


    /* Create a namespace output file if asked */

    if (Gbl_NsOutputFlag)
    {
        Gbl_NamespaceOutputFilename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_NAMESPACE);
        if (!Gbl_NamespaceOutputFilename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the debug file, text mode */

        Gbl_NamespaceOutputFile = fopen (Gbl_NamespaceOutputFilename, "w+");
        if (!Gbl_NamespaceOutputFile)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, 0, 0, NULL, Gbl_NamespaceOutputFilename);
            return (AE_ERROR);
        }

        AslCompilerSignon (Gbl_NamespaceOutputFile);
        AslCompilerFileHeader (Gbl_NamespaceOutputFile);
    }


    /* Create/Open a debug output file if asked */

    if (Gbl_DebugFlag)
    {
        Gbl_DebugOutputFilename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_DEBUG);
        if (!Gbl_DebugOutputFilename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_DEBUG_FILENAME, 0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the debug file, text mode */

        Gbl_DebugOutputFile = freopen (Gbl_DebugOutputFilename, "w+", stderr);
        if (!Gbl_DebugOutputFile)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_DEBUG_FILENAME, 0, 0, 0, 0, NULL, Gbl_DebugOutputFilename);
            return (AE_ERROR);
        }

        AslCompilerSignon (Gbl_DebugOutputFile);
        AslCompilerFileHeader (Gbl_DebugOutputFile);
    }


    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    FlCloseListingFile
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Close the listing file if the option was specified
 *
 ******************************************************************************/

void
FlCloseListingFile (void)
{

    if (!Gbl_ListingFlag)
    {
        return;
    }

    /* Flush any final AML in the buffer */

    LsFlushListingBuffer ();

    /* Print a summary of the compile exceptions */

    fprintf (Gbl_ListingOutputFile, "\n\nSummary of errors and warnings\n\n");
    AePrintErrorLog (Gbl_ListingOutputFile);
    fprintf (Gbl_ListingOutputFile, "\n\n");
    UtDisplaySummary (Gbl_ListingOutputFile);
    fprintf (Gbl_ListingOutputFile, "\n\n");

    /* Close the listing file */

    fclose (Gbl_ListingOutputFile);

    /*
     * TBD: SourceOutput should be .TMP, then rename if we want to keep it?
     */
    if (!Gbl_SourceOutputFlag)
    {
        fclose (Gbl_SourceOutputFile);
        unlink (Gbl_SourceOutputFilename);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    FlCloseSourceOutputFile
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Close the combined source file if the option was specified
 *
 ******************************************************************************/

void
FlCloseSourceOutputFile (void)
{

    fclose (Gbl_SourceOutputFile);
}


/*******************************************************************************
 *
 * FUNCTION:    FlCloseHexOutputFile
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Close the hex file if the option was specified
 *
 ******************************************************************************/

void
FlCloseHexOutputFile (void)
{
    if (!Gbl_HexOutputFlag)
    {
        return;
    }

    fclose (Gbl_HexOutputFile);
}


