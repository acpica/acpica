/******************************************************************************
 * 
 * Module Name: aemain - Main routine for the AcpiExec utility
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <acpi.h>
#include <acapi.h>
#include <amlcode.h>
#include <parser.h>
#include <tables.h>
#include <namesp.h>

#include "aecommon.h"


#define _COMPONENT          PARSER
        MODULE_NAME         ("aemain");


char                    *Version = "X002";
char                    LineBuf[80];
char                    CommandBuf[40];
char                    ArgBuf[40];
char                    ScopeBuf[40];
char                    DebugFilename[40];
FILE                    *DebugFile = NULL;
char                    *Buffer;
char                    *Filename = NULL;


int                     opt_tables = FALSE;
int                     opt_disasm = FALSE;
int                     opt_stats = FALSE;
   

/*
 * AcpiExec commands
 */

#define CMD_NULL        0
#define CMD_ALLOCATIONS 1
#define CMD_CLOSE       2
#define CMD_DEBUG       3
#define CMD_DUMP        4
#define CMD_EXECUTE     5
#define CMD_EXIT        6
#define CMD_HELP        7
#define CMD_HELP2       8
#define CMD_METHODS     9
#define CMD_NAMESPACE   10
#define CMD_OPEN        11
#define CMD_QUIT        12
#define CMD_SCOPE       13
#define CMD_NOT_FOUND   (-1)

#define NUM_COMMANDS    13

char                    *Commands[NUM_COMMANDS] = {
                            "ALLOCATIONS",
                            "CLOSE",
                            "DEBUG",
                            "DUMP",
                            "EXECUTE",
                            "EXIT",
                            "HELP",
                            "?",
                            "METHODS",
                            "NAMESPACE",
                            "OPEN",
                            "QUIT",
                            "SCOPE"};


/******************************************************************************
 * 
 * FUNCTION:    usage
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Print a usage message
 *
 *****************************************************************************/

void
usage (void)
{
    printf ("Usage: acpiexec [-dgs] [-l DebugLevel] [-o OutputFile] [AcpiTableFile]\n");
    printf ("Where:\n");
    printf ("    Input Options\n");
    printf ("        AcpiTableFile       Get ACPI tables from this file\n");
    printf ("    Output Options\n");
    printf ("    Miscellaneous Options\n");
    printf ("        -l DebugLevel       Specify debug output level\n");
}


/******************************************************************************
 * 
 * FUNCTION:    AeDisplayHelp
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Print a usage message
 *
 *****************************************************************************/

void
AeDisplayHelp (void)
{
    printf ("AcpiExec command line interpreter\n\n");
    printf ("Allocations                     Display memory allocation info\n");
    printf ("Close                           Close debug output file\n");
    printf ("Debug <DebugLevel>              Set level of debug output\n");
    printf ("Execute <Method Path>           Execute control method (full pathname)\n");
    printf ("Help                            This help screen\n");
    printf ("Methods [<lines per screen>]    Display list of loaded control methods\n");
    printf ("Open <Debug Filename>           Open a file for debug output\n");
    printf ("Quit                            Exit this command\n");
    printf ("Scope <Scope Path>              Set or Get current scope\n");
}


/******************************************************************************
 * 
 * FUNCTION:    GetLine
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Get the next command line from the user.  Gets entire line
 *              up to the next newline
 *
 *****************************************************************************/

void
GetLine (void)
{
    UINT32                  Temp;
    UINT32                  i;


    CommandBuf[0] = 0;
    ArgBuf[0] = 0;

    for (i = 0; ; i++)
    {
        Temp = getchar ();
        if (!Temp || Temp == '\n')
        {
            break;
        }

        LineBuf [i] = (char) Temp;
    }

    LineBuf [i] = 0;
    strupr (LineBuf);

    sscanf (LineBuf, "%s %s", CommandBuf, ArgBuf);
}


/******************************************************************************
 * 
 * FUNCTION:    AeMatchCommand
 *
 * PARAMETERS:  UserCommand             - User command line
 *
 * RETURN:      Index into command array, -1 if not found
 *
 * DESCRIPTION: Search command array for a command match
 *
 *****************************************************************************/

INT32
AeMatchCommand (
    char                    *UserCommand)
{
    UINT32                  i;


    if (UserCommand[0] == 0)
    {
        return 0;
    }

    for (i = 0; i < NUM_COMMANDS; i++)
    {
        if (strstr (Commands[i], UserCommand) == Commands[i])
        {
            return i + 1;
        }
    }

    /* Command not recognized */

    return -1;
}


/******************************************************************************
 * 
 * FUNCTION:    AeExecuter
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Command line execution for AcpiExec utility.  Commands are
 *              matched and dispatched here.
 *
 *****************************************************************************/

void
AeExecuter (void)
{
    UINT32                  Temp;
    INT32                   CommandIndex;
    ACPI_STATUS             Status;


    AcpiInitialize (NULL);

    /* Always have to get the tables! */

    Status = AdGetTables (Filename);   
    if (ACPI_FAILURE (Status))
    {
        printf ("Could not get ACPI tables (Exception %s)\n", Gbl_ExceptionNames[Status]);
        goto Cleanup;
    }

    /* Always parse the tables, only option is what to display */

    Status = AdParseTables ();
    if (ACPI_FAILURE (Status))
    {
        printf ("Could not parse ACPI tables (Exception %s)\n", Gbl_ExceptionNames[Status]);
        goto Cleanup;
    }

    Status = AeInstallHandlers ();

/*
    Status = AcpiLoadNamespace ();
    if (ACPI_FAILURE (Status))
    {
        printf ("Could not load the namespace (Exception %s)\n", Gbl_ExceptionNames[Status]);
        goto Cleanup;
    }

*/
    setvbuf (stdin, NULL, _IONBF, 0);
    ScopeBuf [0] = '\\';
    ScopeBuf [1] =  0;

    for (; ;)
    {
        printf ("- ");
        GetLine ();
        CommandIndex = AeMatchCommand (CommandBuf);

        switch (CommandIndex)
        {
        case CMD_NULL:
            break;

        case CMD_ALLOCATIONS:
            CmDumpAllocationInfo ();
            break;

        case CMD_OPEN:
            DebugLevel = 0x0FFFFFFF;
            AeOpenDebugFile (ArgBuf);
            break;

        case CMD_CLOSE:
            AeCloseDebugFile ();
            break;

        case CMD_DEBUG:
            DebugLevel = strtoul (ArgBuf, NULL, 0);
            printf ("Debug Level: %0lX\n", DebugLevel);
            break;

        case CMD_DUMP:
            AeDumpBuffer (strtoul (ArgBuf, NULL, 0));
            break;

        case CMD_EXECUTE:
            if (DebugFile && !DebugLevel)
            {
                printf ("Debug output is not enabled!\n");
            }
            AeExecute (ArgBuf);
            break;

        case CMD_HELP:
        case CMD_HELP2:
            AeDisplayHelp ();
            break;

        case CMD_METHODS:
            Temp = strtoul (ArgBuf, NULL, 0);
            AeDisplayAllMethods (Temp);
            break;

        case CMD_NAMESPACE:
            AeDumpNamespace ();
            break;

        case CMD_SCOPE:
            AeSetScope (ArgBuf);
            break;

        case CMD_EXIT:
        case CMD_QUIT:
            if (!DebugFile)
            {
                DebugLevel = DEBUG_DEFAULT;
            }
            AcpiTerminate ();
            AeCloseDebugFile ();
            return;

        case CMD_NOT_FOUND:
            printf ("Unknown Command\n");
        }
    }


Cleanup:
    if (DsdtPtr)
        free (DsdtPtr);


}


/******************************************************************************
 * 
 * FUNCTION:    main
 *
 * PARAMETERS:  argc, argv
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Main routine for AcpiDump utility
 *
 *****************************************************************************/

int
main (
    int                     argc, 
    char                    **argv)
{      
    int                     j;


    /* Init globals */

    Buffer = malloc (BUFFER_SIZE);
    DebugLevel = DEBUG_DEFAULT;    
    DebugLayer = 0xFFFFFFFF;


    printf ("ACPI AML Execution Utility version %s\n", Version);
    if (argc < 2)
    {
        usage ();
        return 0;
    }

    /* Get the command line options */

    while ((j = getopt (argc, argv, "dgl:o:s")) != EOF) switch(j) 
    {
    case 'd':
        opt_disasm = TRUE;
        opt_stats = TRUE;
        break;

    case 'g':
        opt_tables = TRUE;
        Filename = NULL;
        break;
    
    case 'l':
        DebugLevel = strtoul (optarg, NULL, 0);
        printf ("Debug Level: %lX\n", DebugLevel);
        break;

    case 'o':
        printf ("O option is not implemented\n");
        break;

    case 's':
        opt_stats = TRUE;
        break;

    default:    
        usage();
        return -1;
    }                      
    
    /* Standalone filename is the only argument */

    if (argv[optind])
    {
        opt_tables = TRUE;
        Filename = argv[optind];
    }


    AeExecuter ();

    return 0;
}
