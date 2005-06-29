/******************************************************************************
 *
 * Module Name: aemain - Main routine for the AcpiExec utility
 *              $Revision: 1.96 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2005, Intel Corp.
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

#include "aecommon.h"

#ifdef _DEBUG
#if ACPI_MACHINE_WIDTH != 16
#include <crtdbg.h>
#endif
#endif

#define _COMPONENT          PARSER
        ACPI_MODULE_NAME    ("aemain")


UINT8 AcpiGbl_BatchMode = FALSE;
char  *AcpiGbl_BatchMethodName;

#if ACPI_MACHINE_WIDTH == 16

ACPI_STATUS
AcpiGetIrqRoutingTable  (
    ACPI_HANDLE             DeviceHandle,
    ACPI_BUFFER             *RetBuffer)
{
    return AE_NOT_IMPLEMENTED;
}
#endif


/******************************************************************************
 *
 * FUNCTION:    AeGpeHandler
 *
 * DESCRIPTION: GPE handler for acpiexec
 *
 *****************************************************************************/

UINT32
AeGpeHandler (
    void                        *Context)
{


    AcpiOsPrintf ("Received a GPE at handler\n");
    return (0);
}


/******************************************************************************
 *
 * FUNCTION:    AfInstallGpeBlock
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Various GPE initialization
 *
 *****************************************************************************/

void
AfInstallGpeBlock (
    void)
{
    ACPI_STATUS                 Status;
    ACPI_HANDLE                 Handle;
    ACPI_HANDLE                 Handle2 = NULL;
    ACPI_HANDLE                 Handle3 = NULL;
    ACPI_GENERIC_ADDRESS        BlockAddress;


    Status = AcpiGetHandle (NULL, "\\_GPE", &Handle);
    if (ACPI_FAILURE (Status))
    {
        return;
    }

    BlockAddress.AddressSpaceId = 0;
#if ACPI_MACHINE_WIDTH != 16
    ACPI_STORE_ADDRESS (BlockAddress.Address, 0x8000000076540000);
#else
    ACPI_STORE_ADDRESS (BlockAddress.Address, 0x76540000);
#endif

//    Status = AcpiInstallGpeBlock (Handle, &BlockAddress, 4, 8);

    /* Above should fail, ignore */

    Status = AcpiGetHandle (NULL, "\\GPE2", &Handle2);
    if (ACPI_SUCCESS (Status))
    {
        Status = AcpiInstallGpeBlock (Handle2, &BlockAddress, 8, 8);

        AcpiInstallGpeHandler (Handle2, 8, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
        AcpiSetGpeType (Handle2, 8, ACPI_GPE_TYPE_WAKE);
        AcpiEnableGpe (Handle2, 8, 0);
    }

    Status = AcpiGetHandle (NULL, "\\GPE3", &Handle3);
    if (ACPI_SUCCESS (Status))
    {
        Status = AcpiInstallGpeBlock (Handle3, &BlockAddress, 8, 11);
    }

//    Status = AcpiRemoveGpeBlock (Handle);
//    Status = AcpiRemoveGpeBlock (Handle2);
//    Status = AcpiRemoveGpeBlock (Handle3);

}


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
    printf ("Usage: acpiexec [-?dgis] [-x DebugLevel] [-o OutputFile] [-b [Method]] [AcpiTableFile]\n");
    printf ("Where:\n");
    printf ("    Input Options\n");
    printf ("        AcpiTableFile       Get ACPI tables from this file\n");
    printf ("    Output Options\n");
    printf ("    Miscellaneous Options\n");
    printf ("        -?                  Display this message\n");
    printf ("        -b [Method]         Batch mode method execution\n");
    printf ("        -i                  Do not run STA/INI methods\n");
    printf ("        -s                  Enable Interpreter Slack Mode\n");
    printf ("        -x DebugLevel       Specify debug output level\n");
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

int ACPI_SYSTEM_XFACE
main (
    int                     argc,
    char                    **argv)
{
    int                     j;
    ACPI_STATUS             Status;
    UINT32                  InitFlags;
    ACPI_BUFFER             ReturnBuf;
    ACPI_TABLE_HEADER       *Table;
    char                    Buffer[32];


#ifdef _DEBUG
#if ACPI_MACHINE_WIDTH != 16
    _CrtSetDbgFlag (_CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF |
                    _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
#endif
#endif

    signal (SIGINT, AeCtrlCHandler);

    /* Init globals */

    AcpiDbgLevel = ACPI_NORMAL_DEFAULT;
    AcpiDbgLayer = 0xFFFFFFFF;

    /* Init ACPI and start debugger thread */

    AcpiInitializeSubsystem ();
    AcpiGbl_GlobalLockPresent = TRUE;

    printf ("\nIntel ACPI Component Architecture\nAML Execution/Debug Utility");

#if ACPI_MACHINE_WIDTH == 16
    printf (" (16-bit)");
#endif

    printf (" version %8.8X", ((UINT32) ACPI_CA_VERSION));
    printf (" [%s]\n\n",  __DATE__);

    /* Get the command line options */

    while ((j = AcpiGetopt (argc, argv, "?b^dgio:svx:")) != EOF) switch(j)
    {
    case 'b':
        AcpiGbl_BatchMode = TRUE;
        switch (AcpiGbl_Optarg[0])
        {
        case '^':
            AcpiGbl_BatchMethodName = "MAIN";
            break;
        default:
            AcpiGbl_BatchMethodName = AcpiGbl_Optarg;
            break;
        }
        break;

    case 'd':
        AcpiGbl_DbOpt_disasm = TRUE;
        AcpiGbl_DbOpt_stats = TRUE;
        break;

    case 'g':
        AcpiGbl_DbOpt_tables = TRUE;
        AcpiGbl_DbFilename = NULL;
        break;

    case 'i':
        AcpiGbl_DbOpt_ini_methods = FALSE;
        break;

    case 'x':
        AcpiDbgLevel = strtoul (AcpiGbl_Optarg, NULL, 0);
        AcpiGbl_DbConsoleDebugLevel = AcpiDbgLevel;
        printf ("Debug Level: %lX\n", AcpiDbgLevel);
        break;

    case 'o':
        printf ("O option is not implemented\n");
        break;

    case 's':
        AcpiGbl_EnableInterpreterSlack = TRUE;
        printf ("Enabling AML Interpreter slack mode\n");
        break;

    case 'v':
        AcpiDbgLevel |= ACPI_LV_INIT_NAMES;
        break;

    case '?':
    default:
        usage();
        return -1;
    }


    InitFlags = (ACPI_NO_HANDLER_INIT | ACPI_NO_ACPI_ENABLE);
    if (!AcpiGbl_DbOpt_ini_methods)
    {
        InitFlags |= (ACPI_NO_DEVICE_INIT | ACPI_NO_OBJECT_INIT);
    }

    /* Standalone filename is the only argument */

    if (argv[AcpiGbl_Optind])
    {
        AcpiGbl_DbOpt_tables = TRUE;
        AcpiGbl_DbFilename = argv[AcpiGbl_Optind];

        Status = AcpiDbReadTableFromFile (AcpiGbl_DbFilename, &Table);
        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not get input table, %s\n", AcpiFormatException (Status));
            goto enterloop;
        }

        AeBuildLocalTables (Table);
        Status = AeInstallTables ();
        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not load ACPI tables, %s\n", AcpiFormatException (Status));
            goto enterloop;
        }

        Status = AeInstallHandlers ();
        if (ACPI_FAILURE (Status))
        {
            goto enterloop;
        }

        /*
         * TBD:
         * Need a way to call this after the "LOAD" command
         */
        Status = AcpiEnableSubsystem (InitFlags);
        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not EnableSubsystem, %s\n", AcpiFormatException (Status));
            goto enterloop;
        }

        Status = AcpiInitializeObjects (InitFlags);
        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not InitializeObjects, %s\n", AcpiFormatException (Status));
            goto enterloop;
        }


        ReturnBuf.Length = 32;
        ReturnBuf.Pointer = Buffer;
        AcpiGetName (AcpiGbl_RootNode, ACPI_FULL_PATHNAME, &ReturnBuf);
        AcpiEnableEvent (ACPI_EVENT_GLOBAL, 0);

        AcpiInstallGpeHandler (NULL, 0, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
        AcpiSetGpeType (NULL, 0, ACPI_GPE_TYPE_WAKE_RUN);
        AcpiEnableGpe (NULL, 0, ACPI_NOT_ISR);
        AcpiRemoveGpeHandler (NULL, 0, AeGpeHandler);

        AcpiInstallGpeHandler (NULL, 0, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
        AcpiSetGpeType (NULL, 0, ACPI_GPE_TYPE_WAKE_RUN);
        AcpiEnableGpe (NULL, 0, ACPI_NOT_ISR);

        AcpiInstallGpeHandler (NULL, 1, ACPI_GPE_EDGE_TRIGGERED, AeGpeHandler, NULL);
        AcpiSetGpeType (NULL, 1, ACPI_GPE_TYPE_RUNTIME);
        AcpiEnableGpe (NULL, 1, ACPI_NOT_ISR);

        AcpiInstallGpeHandler (NULL, 2, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
        AcpiSetGpeType (NULL, 2, ACPI_GPE_TYPE_WAKE);
        AcpiEnableGpe (NULL, 2, ACPI_NOT_ISR);

        AcpiInstallGpeHandler (NULL, 3, ACPI_GPE_EDGE_TRIGGERED, AeGpeHandler, NULL);
        AcpiSetGpeType (NULL, 3, ACPI_GPE_TYPE_WAKE_RUN);

        AcpiInstallGpeHandler (NULL, 4, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
        AcpiSetGpeType (NULL, 4, ACPI_GPE_TYPE_RUNTIME);

        AcpiInstallGpeHandler (NULL, 5, ACPI_GPE_EDGE_TRIGGERED, AeGpeHandler, NULL);
        AcpiSetGpeType (NULL, 5, ACPI_GPE_TYPE_WAKE);

        AcpiInstallGpeHandler (NULL, 0x19, ACPI_GPE_LEVEL_TRIGGERED, AeGpeHandler, NULL);
        AcpiSetGpeType (NULL, 0x19, ACPI_GPE_TYPE_WAKE_RUN);
        AcpiEnableGpe (NULL, 0x19, ACPI_NOT_ISR);


        AfInstallGpeBlock ();
    }

#if ACPI_MACHINE_WIDTH == 16
    else
    {
#include "16bit.h"

        Status = AfFindTable (DSDT_SIG, NULL, NULL);
        if (ACPI_FAILURE (Status))
        {
            goto enterloop;
        }


        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not load ACPI tables, %s\n", AcpiFormatException (Status));
            goto enterloop;
        }


        Status = AcpiNsLoadNamespace ();
        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not load ACPI namespace, %s\n", AcpiFormatException (Status));
            goto enterloop;
        }


        Status = AeInstallHandlers ();
        if (ACPI_FAILURE (Status))
        {
            goto enterloop;
        }
        /* TBD:
         * Need a way to call this after the "LOAD" command
         */
        Status = AcpiEnableSubsystem (InitFlags);
        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not EnableSubsystem, %s\n", AcpiFormatException (Status));
            goto enterloop;
        }

        Status = AcpiInitializeObjects (InitFlags);
        if (ACPI_FAILURE (Status))
        {
            printf ("**** Could not InitializeObjects, %s\n", AcpiFormatException (Status));
            goto enterloop;
        }

     }
#endif

enterloop:

    if (AcpiGbl_BatchMode)
    {
        AcpiDbExecute (AcpiGbl_BatchMethodName, NULL, EX_NO_SINGLE_STEP);
    }
    else
    {
        /* Enter the debugger command loop */

        AcpiDbUserCommands (ACPI_DEBUGGER_COMMAND_PROMPT, NULL);
    }

    return 0;
}
