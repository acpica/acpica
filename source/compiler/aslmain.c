
/******************************************************************************
 *
 * Module Name: aslmain - compiler main and utilities
 *              $Revision: 1.3 $
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



#define _DECLARE_GLOBALS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AslCompiler.h"


#define CompilerId      "ACPI Component Architecture ASL Compiler"
#define CompilerName    "iasl"
#define Version         "X202"




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

int
DbgPrint (
    char                    *Fmt,
    ...)
{
    va_list                 Args;


    va_start (Args, Fmt);

    if (Gbl_DebugFlag)
        vfprintf (stderr, Fmt, Args);

    va_end (Args);
    return 0;
}


/*******************************************************************************
 *
 * FUNCTION:    AslDisplaySummary
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display compilation statistics
 *
 ******************************************************************************/

void
AslDisplaySummary (
    void)
{


    printf ("Compilation complete. %d Errors %d Warnings\n", ErrorCount, WarningCount);
    printf ("ASL Input: %d lines, %d bytes, %d keywords\n", 
                Gbl_CurrentLineNumber, InputChars, TotalKeywords);

    if (ErrorCount == 0)
    {
        printf ("AML Output: %s - %d bytes %d named objects %d executable opcodes\n\n", 
                    Gbl_OutputFilename, TableLength, TotalNamedObjects, TotalExecutableOpcodes);
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

char *
AslGenerateFilename (
    char                    *InputFilename,
    char                    *Suffix)
{
    char                    *Position;
    char                    *NewFilename;


    NewFilename = calloc (strlen (InputFilename) + strlen (Suffix), 1);
    if (!NewFilename)
    {
        return NULL;
    }

    Position = strrchr (InputFilename, '.');
    if (Position)
    {
        *Position = 0;
    }

    strcpy (NewFilename, InputFilename);
    strcat (NewFilename, Suffix);


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
AslOpenAllFiles (
    char                    *InputFilename)
{


    /* Open the input ASL file, text mode */

	Gbl_AslInputFile = fopen (InputFilename, "r");
    AslCompilerin = Gbl_AslInputFile;
    if (!Gbl_AslInputFile)
    {
        AslError (ASL_ERROR_INPUT_FILE_OPEN);
        return (AE_ERROR);
    }


    /* Create the output AML filename */

    Gbl_OutputFilename = AslGenerateFilename (InputFilename, ".aml");
    if (!Gbl_OutputFilename)
    {
        AslError (ASL_ERROR_OUTPUT_FILENAME);
        return (AE_ERROR);
    }


    /* Open the output AML file in binary mode */

	Gbl_OutputAmlFile = fopen (Gbl_OutputFilename, "w+b");
    if (!Gbl_OutputAmlFile)
    {
        AslError (ASL_ERROR_OUTPUT_FILE_OPEN);
        return (AE_ERROR);
    }


    /* Create/Open a listing output file if asked */

    if (Gbl_ListingFlag)
    {
        Gbl_ListingFilename = AslGenerateFilename (InputFilename, ".lst");
        if (!Gbl_ListingFilename)
        {
            AslError (ASL_ERROR_LISTING_FILENAME);
            return (AE_ERROR);
        }

        /* Open the debug file, text mode */

	    Gbl_ListingFile = fopen (Gbl_ListingFilename, "w+");
        if (!Gbl_ListingFile)
        {
            AslError (ASL_ERROR_LISTING_FILE_OPEN);
            return (AE_ERROR);
        }
    }

    /* Create/Open a debug output file if asked */

    if (Gbl_DebugFlag)
    {
        Gbl_DebugFilename = AslGenerateFilename (InputFilename, ".txt");
        if (!Gbl_DebugFilename)
        {
            AslError (ASL_ERROR_DEBUG_FILENAME);
            return (AE_ERROR);
        }

        /* Open the debug file, text mode */

	    Gbl_DebugFile = freopen (Gbl_DebugFilename, "w+", stderr);
        if (!Gbl_DebugFile)
        {
            AslError (ASL_ERROR_DEBUG_FILE_OPEN);
            return (AE_ERROR);
        }
    }


    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    Usage 
 *
 * PARAMETERS:  None
 *  
 * RETURN:      None      
 *
 * DESCRIPTION: Display help message
 *
 ******************************************************************************/

void 
Usage (
    void)
{
    printf ("Usage:    %s [-dl] <InputFile>\n\n", CompilerName);
    printf ("Options:  -d               Create debug/trace output file (*.txt)\n");
    printf ("          -l               Create listing file (*.lst)\n");
    printf ("          -o <filename>    Specify output file (default is *.aml)\n");
}



/*******************************************************************************
 *
 * FUNCTION:    main    
 *
 * PARAMETERS:  Standard argc/argv
 *
 * RETURN:      Program termination code 
 *
 * DESCRIPTION: C main routine for the Asl Compiler
 *
 ******************************************************************************/


int
main (
    int                 argc, 
    char                **argv)
{
    UINT32              j;
    ACPI_STATUS         Status;



    printf ("\n%s [Version %s, %s]\n\n", CompilerId, Version, __DATE__);

    /* Minimum command line contains at least the input file */

    if (argc < 2)
    {
        Usage ();
        return 0;
    }


    /* Get the command line options */

    while ((j = getopt (argc, argv, "d")) != EOF) switch (j)
    {
    case 'd':
        Gbl_DebugFlag = TRUE;
        AslCompilerdebug = 1; /* same as yydebug */
        break;

    default:
        printf ("Unknown option %c\n", j);

        Usage ();
        return -1;
    }



    /* Next parameter must be the input filename */

    Gbl_InputFilename = argv[optind];
    Status = AslOpenAllFiles (Gbl_InputFilename);
    if (ACPI_FAILURE (Status))
    {
        return -1;
    }


    /* Build the parse tree */

    AslCompilerparse();
    
    
    /* Code generation - emit the AML */

    CgGenerateOutput ();


    AslDisplaySummary ();


    return 0;
}


