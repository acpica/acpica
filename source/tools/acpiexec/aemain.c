/******************************************************************************
 *
 * Module Name: aemain - Main routine for the AcpiExec utility
 *              $Revision: 1.31 $
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acpi.h"
#include "amlcode.h"
#include "acparser.h"
#include "actables.h"
#include "acnamesp.h"
#include "acinterp.h"
#include "acdebug.h"

#include "aecommon.h"


#define _COMPONENT          PARSER
        MODULE_NAME         ("aemain")


/*
 * We need a local FADT so that the hardware subcomponent will function,
 * even though the underlying OSD HW access functions don't do
 * anything.
 */

FADT_DESCRIPTOR             LocalFADT;
ACPI_COMMON_FACS            LocalFACS;


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
    printf ("Usage: acpiexec [-?dgis] [-l DebugLevel] [-o OutputFile] [AcpiTableFile]\n");
    printf ("Where:\n");
    printf ("    Input Options\n");
    printf ("        AcpiTableFile       Get ACPI tables from this file\n");
    printf ("    Output Options\n");
    printf ("    Miscellaneous Options\n");
    printf ("        -?                  Display this message\n");
    printf ("        -i                  Do not run INI methods\n");
    printf ("        -l DebugLevel       Specify debug output level\n");
    printf ("        -v                  Verbose init output\n");
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
    ACPI_STATUS             Status;
    UINT32                  InitFlags;


    /* Init globals */

    Buffer = malloc (BUFFER_SIZE);
    AcpiDbgLevel = NORMAL_DEFAULT | TRACE_TABLES;
    AcpiDbgLayer = 0xFFFFFFFF;


    printf ("ACPI AML Execution/Debug Utility ");

#ifdef _IA16
    printf ("16-bit ");
#else
    printf ("32-bit ");
#endif

    printf ("version [%s]\n", __DATE__);

    /* Get the command line options */

    while ((j = getopt (argc, argv, "?dgijl:o:sv")) != EOF) switch(j)
    {
    case 'd':
        opt_disasm = TRUE;
        opt_stats = TRUE;
        break;

    case 'g':
        opt_tables = TRUE;
        Filename = NULL;
        break;

    case 'i':
        opt_ini_methods = FALSE;
        break;

    case 'j':
        opt_parse_jit = TRUE;
        break;

    case 'l':
        AcpiDbgLevel = strtoul (optarg, NULL, 0);
        printf ("Debug Level: %lX\n", AcpiDbgLevel);
        break;

    case 'o':
        printf ("O option is not implemented\n");
        break;

    case 's':
        opt_stats = TRUE;
        break;

    case 'v':
        AcpiDbgLevel |= TRACE_INIT;
        break;

    case '?':
    default:
        usage();
        return -1;
    }


    /* Init ACPI and start debugger thread */

    AcpiInitializeSubsystem ();


    InitFlags = (ACPI_NO_HARDWARE_INIT | ACPI_NO_ACPI_ENABLE | ACPI_NO_EVENT_INIT);

    if (!opt_ini_methods)
    {
        InitFlags |= (ACPI_NO_DEVICE_INIT | ACPI_NO_OBJECT_INIT);
    }

    /* Standalone filename is the only argument */

    if (argv[optind])
    {
        opt_tables = TRUE;
        Filename = argv[optind];


        Status = AcpiDbLoadAcpiTable (Filename);
        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not load input table, %s\n", AcpiCmFormatException (Status));
            goto enterloop;
        }


        /* Need a fake FADT so that the hardware component is happy */

        ACPI_STORE_ADDRESS (LocalFADT.XGpe0Blk.Address, 0x70);
        ACPI_STORE_ADDRESS (LocalFADT.XPm1aEvtBlk.Address, 0x80);
        ACPI_STORE_ADDRESS (LocalFADT.XPm1aCntBlk.Address, 0x90);
        ACPI_STORE_ADDRESS (LocalFADT.XPmTmrBlk.Address, 0xA0);

        LocalFADT.Gpe0BlkLen    = 8;
        LocalFADT.Pm1EvtLen     = 4;
        LocalFADT.Pm1CntLen     = 4;
        LocalFADT.PmTmLen       = 8;

        AcpiGbl_FADT = &LocalFADT;
        AcpiGbl_FACS = &LocalFACS;


        /* TBD:
         * Need a way to call this after the "LOAD" command
         */
        AeInstallHandlers ();

        Status = AcpiEnableSubsystem (InitFlags);
        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not EnableSubsystem, %s\n", AcpiCmFormatException (Status));
            goto enterloop;
        }

    }

#ifdef _IA16
    else
    {
#include "16bit.h"

        Status = AfFindDsdt (NULL, NULL);
        if (ACPI_FAILURE (Status))
        {
            goto enterloop;
        }


        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not load ACPI tables, %s\n", AcpiCmFormatException (Status));
            goto enterloop;
        }


        Status = AcpiNsLoadNamespace ();
        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not load ACPI namespace, %s\n", AcpiCmFormatException (Status));
            goto enterloop;
        }

        /* TBD:
         * Need a way to call this after the "LOAD" command
         */
        AeInstallHandlers ();

        Status = AcpiEnableSubsystem (InitFlags);
        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not EnableSubsystem, %s\n", AcpiCmFormatException (Status));
            goto enterloop;
        }
     }
#endif

enterloop:

    /* Enter the debugger command loop */

    AcpiDbUserCommands (DB_COMMAND_PROMPT, NULL);

    return 0;
}
