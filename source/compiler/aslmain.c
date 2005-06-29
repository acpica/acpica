

#define _DECLARE_GLOBALS

#include <stdio.h>
#include "AslCompiler.h"


#define CompilerId      "ACPI Component Architecture ASL Compiler"
#define Version         "X201"

/*
char                        *OutputFilename;

FILE                        *AmlFile;
ACPI_TABLE_HEADER           TableHeader;
UINT32                      TableLength = 0;
UINT32                      InputLines = 0;
UINT32                      InputChars = 0;
UINT32                      TotalKeywords = 0;
UINT32                      TotalNamedObjects = 0;
UINT32                      TotalExecutableOpcodes = 0;
UINT32                      ErrorCount = 0;
UINT32                      WarningCount = 0;
*/

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

    if (AslCompilerdebug)
        vfprintf (stderr, Fmt, Args);

    va_end (Args);
    return 0;


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


void Usage (
    char                *ProgramName)
{
    printf ("Usage:   %s [-d] <InputFile>\n", ProgramName);
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


int
main (
    int                 argc, 
    char                **argv)
{
    UINT32              j;



    printf ("\n%s %s [%s]\n\n", CompilerId, Version, __DATE__);

    if (argc < 2)
    {
        Usage (argv[0]);
        return 0;
    }


    /* Get the command line options */

    while ((j = getopt (argc, argv, "d")) != EOF) switch (j)
    {
    case 'd':
        freopen ("debug.txt", "w+", stderr);
        AslCompilerdebug = -1;
        break;

    default:
        Usage (argv[0]);
        return -1;
    }


	AslCompilerin = fopen(argv[optind], "r");
    AslCompilerparse();
    CgGenerateOutput (argv[optind]);

    printf ("Compilation complete. %d Errors %d Warnings\n", ErrorCount, WarningCount);
    printf ("ASL Input: %d lines, %d bytes, %d keywords\n", 
                InputLines, InputChars, TotalKeywords);

    if (ErrorCount == 0)
    {
        printf ("AML Output: %s - %d bytes %d named objects %d executable opcodes\n\n", 
                    OutputFilename, TableLength, TotalNamedObjects, TotalExecutableOpcodes);
    }
    
    return 0;
}


