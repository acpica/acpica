

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


