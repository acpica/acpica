
/******************************************************************************
 *
 * Module Name: aslfiles - file I/O suppoert
 *              $Revision: 1.4 $
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


#include "AslCompiler.h"


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

FILE *
FlOpenLocalFile (
    char                    *LocalName,
    char                    *Mode)
{
    
    strcpy (StringBuffer, Gbl_DirectoryPath);
    strcat (StringBuffer, LocalName);

    DbgPrint ("FlOpenLocalFile: %s\n", StringBuffer);
    return (fopen (StringBuffer, (const char *) Mode));

}

/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
FlOpenIncludeFile (
    ASL_PARSE_NODE          *Node)
{
    FILE                    *IncFile;

    if (!Node)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_INCLUDE_FILE_OPEN,
                    Gbl_CurrentLineNumber, Gbl_LogicalLineNumber, " - Null parse node");
        return;
    }


    if (Gbl_SourceOutputFlag || Gbl_ListingFlag)
    {
          fprintf (Gbl_SourceOutputFile, "\n");
          Gbl_LogicalLineNumber++;
    }

    DbgPrint ("\nOpen include file: path %s\n\n", Node->Value.String);
    IncFile = FlOpenLocalFile (Node->Value.String, "r");
    if (!IncFile)
    {
        AslError (ASL_ERROR, ASL_MSG_INCLUDE_FILE_OPEN, Node, Node->Value.String);
        return;
    }


    AslPushInputFileStack (IncFile, Node->Value.String);
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

char *
FlGenerateFilename (
    char                    *InputFilename,
    char                    *Suffix)
{
    char                    *Position;
    char                    *NewFilename;


    NewFilename = UtLocalCalloc (strlen (InputFilename) + strlen (Suffix));
    strcpy (NewFilename, InputFilename);

    Position = strrchr (NewFilename, '.');
    if (Position)
    {
        *Position = 0;
        strcat (Position, Suffix);
    }

    else
    {
        strcat (NewFilename, Suffix);
    }

    return NewFilename;
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
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
        AslCommonError (ASL_ERROR, ASL_MSG_INPUT_FILE_OPEN, 0, 0, InputFilename);
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
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

ACPI_STATUS
FlOpenAmlOutputFile (
    char                    *InputFilename)
{


    /* Output filename usually comes from the ASL itself */

    if (!Gbl_OutputFilename)
    {
        /* Create the output AML filename */

        Gbl_OutputFilename = FlGenerateFilename (InputFilename, ".aml");
        if (!Gbl_OutputFilename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_OUTPUT_FILENAME, 0, 0, NULL);
            return (AE_ERROR);
        }
    }

    /* Open the output AML file in binary mode */

	Gbl_OutputAmlFile = fopen (Gbl_OutputFilename, "w+b");
    if (!Gbl_OutputAmlFile)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_OUTPUT_FILENAME, 0, 0, Gbl_OutputFilename);
        return (AE_ERROR);
    }

    return (AE_OK);
}



/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

ACPI_STATUS
FlOpenMiscOutputFiles (
    char                    *InputFilename)
{

    /* Create/Open a combined source output file if asked */

    if (Gbl_SourceOutputFlag || Gbl_ListingFlag)
    {
        Gbl_SourceOutputFilename = FlGenerateFilename (InputFilename, ".src");
        if (!Gbl_SourceOutputFilename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, NULL);
            return (AE_ERROR);
        }

        /* Open the debug file, text mode */

	    Gbl_SourceOutputFile = fopen (Gbl_SourceOutputFilename, "w+");
        if (!Gbl_SourceOutputFile)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, Gbl_SourceOutputFilename);
            return (AE_ERROR);
        }

    }

    /* Create/Open a listing output file if asked */

    if (Gbl_ListingFlag)
    {
        Gbl_ListingFilename = FlGenerateFilename (InputFilename, ".lst");
        if (!Gbl_ListingFilename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, NULL);
            return (AE_ERROR);
        }

        /* Open the debug file, text mode */

	    Gbl_ListingFile = fopen (Gbl_ListingFilename, "w+");
        if (!Gbl_ListingFile)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, Gbl_ListingFilename);
            return (AE_ERROR);
        }

        AslCompilerSignon (Gbl_ListingFile);
        AslCompilerFileHeader (Gbl_ListingFile);
    }


    /* Create/Open a hex output file if asked */

    if (Gbl_HexOutputFlag)
    {
        Gbl_HexFilename = FlGenerateFilename (InputFilename, ".hex");
        if (!Gbl_HexFilename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, NULL);
            return (AE_ERROR);
        }

        /* Open the debug file, text mode */

	    Gbl_HexFile = fopen (Gbl_HexFilename, "w+");
        if (!Gbl_HexFile)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, Gbl_HexFilename);
            return (AE_ERROR);
        }

        AslCompilerSignon (Gbl_HexFile);
        AslCompilerFileHeader (Gbl_HexFile);
    }


    /* Create a namespace output file if asked */

    if (Gbl_NsOutputFlag)
    {
        Gbl_NsFilename = FlGenerateFilename (InputFilename, ".nsp");
        if (!Gbl_NsFilename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, NULL);
            return (AE_ERROR);
        }

        /* Open the debug file, text mode */

	    Gbl_NsFile = fopen (Gbl_NsFilename, "w+");
        if (!Gbl_NsFile)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME, 0, 0, Gbl_NsFilename);
            return (AE_ERROR);
        }

        AslCompilerSignon (Gbl_NsFile);
        AslCompilerFileHeader (Gbl_NsFile);
    }


    /* Create/Open a debug output file if asked */

    if (Gbl_DebugFlag)
    {
        Gbl_DebugFilename = FlGenerateFilename (InputFilename, ".txt");
        if (!Gbl_DebugFilename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_DEBUG_FILENAME, 0, 0, NULL);
            return (AE_ERROR);
        }

        /* Open the debug file, text mode */

	    Gbl_DebugFile = freopen (Gbl_DebugFilename, "w+", stderr);
        if (!Gbl_DebugFile)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_DEBUG_FILENAME, 0, 0, Gbl_DebugFilename);
            return (AE_ERROR);
        }

        AslCompilerSignon (Gbl_DebugFile);
        AslCompilerFileHeader (Gbl_DebugFile);
    }


    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
FlCloseListingFile (void)
{

    if (!Gbl_ListingFlag)
    {
        return;
    }

    LsFlushListingBuffer ();

    fprintf (Gbl_ListingFile, "\n\nSummary of errors and warnings\n\n");
    AePrintErrorLog (Gbl_ListingFile);
    fprintf (Gbl_ListingFile, "\n\n");

    fclose (Gbl_ListingFile);
    
    if (!Gbl_SourceOutputFlag)
    {
        fclose (Gbl_SourceOutputFile);
        unlink (Gbl_SourceOutputFilename);
    }

}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
FlCloseSourceOutputFile (void)
{

    if (!Gbl_SourceOutputFlag)
    {
        return;
    }

    fclose (Gbl_SourceOutputFile);
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
FlCloseHexOutputFile (void)
{
    if (!Gbl_HexOutputFlag)
    {
        return;
    }

    fclose (Gbl_HexFile);
}




