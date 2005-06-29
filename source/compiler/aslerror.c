
#include <stdio.h>

#include "AslCompiler.h"
#include "acpi.h"


char                        *AslWarnings [] = {
    "Effective AML buffer length is zero",
    "Effective AML package length is zero",
};

char                        *AslErrors [] = {
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

void
AslWarning (
    UINT32                  WarningId)
{

    fprintf (stderr, "Warning %04.4d: %s\n", 
                WarningId + ASL_WARNING_PREFIX, AslWarnings[WarningId]);

    if (AslCompilerdebug)
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

    if (AslCompilerdebug)
    {
        printf ("Error %04.4d: %s\n", 
                    ErrorId + ASL_ERROR_PREFIX, AslErrors[ErrorId]);
    }

    ErrorCount++;
}

