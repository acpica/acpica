
#include <stdio.h>

#include "AslCompiler.h"
#include "acpi.h"


char                        *AslWarnings [] = {
    "Effective AML buffer length is zero",
    "Effective AML package length is zero",
};

char                        *AslErrors [] = {
    "Could not open input file",
    "Could not create output filename",
    "Could not open output AML file",
    "Could not create listing filename",
    "Could not open listing file",
    "Could not create debug filename",
    "Could not open debug file",
    "Package length too long to encode",
};




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


/*
 * Report an error situation discovered in a production
 *
 */
int
AslCompilererror(char *s)
{



	fprintf (stdout, "%5d: ", Gbl_CurrentLineNumber);
    fprintf (stdout, "%s\n", Gbl_CurrentLineBuffer);
	fprintf (stdout, "\n%*s", Gbl_CurrentColumn + 7, "^");
    fprintf (stdout, "%s\n\n", s);

    if (Gbl_DebugFlag)
        printf ("Syntax Error - %s ", s);

    ErrorCount++;
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

void
AslWarning (
    UINT32                  WarningId)
{

    fprintf (stderr, "Warning %04.4d: %s\n", 
                WarningId + ASL_WARNING_PREFIX, AslWarnings[WarningId]);

    if (Gbl_DebugFlag)
    {
        printf ("Warning %04.4d: %s\n", 
                    WarningId + ASL_WARNING_PREFIX, AslWarnings[WarningId]);
    }
    
    WarningCount++;
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
AslError (
    UINT32                  ErrorId)
{

    fprintf (stderr, "Error %04.4d: %s\n", 
                ErrorId + ASL_ERROR_PREFIX, AslErrors[ErrorId]);

    if (Gbl_DebugFlag)
    {
        printf ("Error %04.4d: %s\n", 
                    ErrorId + ASL_ERROR_PREFIX, AslErrors[ErrorId]);
    }

    ErrorCount++;
}

