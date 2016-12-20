#include "acpi.h"
#include "accommon.h"
#include "acapps.h"


#define LINE_SIZE           256
static char                 LineBuffer[LINE_SIZE];

/******************************************************************************
 *
 * FUNCTION:    main
 *
 * PARAMETERS:  argc/argv           - Standard argc/argv
 *
 * RETURN:      Status
 *
 * DESCRIPTION: C main function for acpidump utility
 *
 ******************************************************************************/

#ifndef _GNU_EFI
int ACPI_SYSTEM_XFACE
main (
    int                     argc,
    char                    *argv[])
#else
int ACPI_SYSTEM_XFACE
acpi_main (
    int                     argc,
    char                    *argv[])
#endif
{
    ACPI_FILE               File;
    BOOLEAN                 DoCloseFile = FALSE;
    char                    *Result;


    AcpiOsInitialize ();

    printf ("argc=%d\n", argc);

    if (argc > 1)
    {
        File = fopen (argv[1], "r");
        if (!File)
        {
            printf ("Failed to open %s.\n", argv[1]);
            return (-1);
        }
        DoCloseFile = TRUE;
    }
    else
    {
        File = stdin;
    }

    while (1)
    {
        Result = fgets (LineBuffer, LINE_SIZE, File);
        if (!Result)
        {
            printf ("Failed to read %s.\n", argv[1]);
            fclose (File);
            return (-2);
        }

        printf ("%s", LineBuffer);

        if (strncmp (Result, "exit", 4) == 0)
        {
            break;
        }
    }


    if (DoCloseFile)
    {
        fclose (File);
    }
    return (0);
}
