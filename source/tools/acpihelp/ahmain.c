/******************************************************************************
 *
 * Module Name: ahmain - Main module for the acpi help utility
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2017, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights. You may have additional license terms from the party that provided
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
 * to or modifications of the Original Intel Code. No other license or right
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
 * and the following Disclaimer and Export Compliance provision. In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change. Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee. Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution. In
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
 * HERE. ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT, ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES. INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS. INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES. THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government. In the
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

#define DEFINE_AHELP_GLOBALS
#include "acpihelp.h"


/* Local prototypes */

static void
AhDisplayUsage (
    void);

#define AH_UTILITY_NAME             "ACPI Help Utility"
#define AH_SUPPORTED_OPTIONS        "adeghikmopstuv"


#if defined ACPI_OPTION
#undef ACPI_OPTION
#endif

#define ACPI_OPTION(Name, Description) \
    AcpiOsPrintf ("  %-24s%s\n", Name, Description);


/******************************************************************************
 *
 * FUNCTION:    AhDisplayUsage
 *
 * DESCRIPTION: Usage message
 *
 ******************************************************************************/

static void
AhDisplayUsage (
    void)
{

    ACPI_USAGE_HEADER ("acpihelp <options> [Name/Prefix | HexValue]");
    ACPI_OPTION ("-h",                      "Display help");
    ACPI_OPTION ("-v",                      "Display version information");

    ACPI_USAGE_TEXT ("\nAML Names and Encodings (ACPI Machine Language):\n");
    ACPI_OPTION ("-a [Name/Prefix | *]",    "Display both ASL operator and AML opcode name(s)");
    ACPI_OPTION ("-g [Name/Prefix | *]",    "Display AML grammar elements(s)");
    ACPI_OPTION ("-m [Name/Prefix | *]",    "Display AML opcode name(s)");

    ACPI_USAGE_TEXT ("\nACPI Values:\n");
    ACPI_OPTION ("-e [HexValue]",           "Decode ACPICA exception code");
    ACPI_OPTION ("-o [HexValue]",           "Decode hex AML opcode");

    ACPI_USAGE_TEXT ("\nASL Names and Symbols (ACPI Source Language):\n");
    ACPI_OPTION ("-k [Name/Prefix | *]",    "Display ASL non-operator keyword(s)");
    ACPI_OPTION ("-p [Name/Prefix | *]",    "Display ASL predefined method name(s)");
    ACPI_OPTION ("-s [Name/Prefix | *]",    "Display ASL operator name(s)");

    ACPI_USAGE_TEXT ("\nOther miscellaneous ACPI Names:\n");
    ACPI_OPTION ("-i [Name/Prefix | *]",    "Display ACPI/PNP Hardware ID(s)");
    ACPI_OPTION ("-d",                      "Display iASL Preprocessor directives");
    ACPI_OPTION ("-t",                      "Display supported ACPI tables");
    ACPI_OPTION ("-u",                      "Display ACPI-related UUIDs");

    ACPI_USAGE_TEXT ("\nName/Prefix or HexValue not specified means \"Display All\"\n");
    ACPI_USAGE_TEXT ("\nDefault search with valid Name/Prefix and no options:\n");
    ACPI_USAGE_TEXT ("    Find ASL/AML operator names - if NamePrefix does not start with underscore\n");
    ACPI_USAGE_TEXT ("    Find ASL predefined method names - if NamePrefix starts with underscore\n");
}


/******************************************************************************
 *
 * FUNCTION:    main
 *
 * DESCRIPTION: C main function for AcpiHelp utility.
 *
 ******************************************************************************/

int ACPI_SYSTEM_XFACE
main (
    int                     argc,
    char                    *argv[])
{
    char                    *Name;
    UINT32                  DecodeType;
    int                     j;


    AcpiOsInitialize ();
    ACPI_DEBUG_INITIALIZE (); /* For debug version only */
    printf (ACPI_COMMON_SIGNON (AH_UTILITY_NAME));
    DecodeType = AH_DECODE_DEFAULT;

    if (argc < 2)
    {
        AhDisplayUsage ();
        return (0);
    }

    /* Command line options */

    while ((j = AcpiGetopt (argc, argv, AH_SUPPORTED_OPTIONS)) != ACPI_OPT_END) switch (j)
    {
    case 'a':

        DecodeType = AH_DECODE_ASL_AML;
        break;

    case 'd':

        DecodeType = AH_DISPLAY_DIRECTIVES;
        break;

    case 'e':

        DecodeType = AH_DECODE_EXCEPTION;
        break;

    case 'g':

        DecodeType = AH_DECODE_AML_TYPE;
        break;

    case 'i':

        DecodeType = AH_DISPLAY_DEVICE_IDS;
        break;

    case 'k':

        DecodeType = AH_DECODE_ASL_KEYWORD;
        break;

    case 'm':

        DecodeType = AH_DECODE_AML;
        break;

    case 'o':

        DecodeType = AH_DECODE_AML_OPCODE;
        break;

    case 'p':

        DecodeType = AH_DECODE_PREDEFINED_NAME;
        break;

    case 's':

        DecodeType = AH_DECODE_ASL;
        break;

    case 't':

        DecodeType = AH_DISPLAY_TABLES;
        break;

    case 'u':

        DecodeType = AH_DISPLAY_UUIDS;
        break;

    case 'v': /* -v: (Version): signon already emitted, just exit */

        return (0);

    case 'h':
    default:

        AhDisplayUsage ();
        return (-1);
    }

    /* Missing (null) name means "display all" */

    Name = argv[AcpiGbl_Optind];

    switch (DecodeType)
    {
    case AH_DECODE_ASL_AML:

        AhFindAslAndAmlOperators (Name);
        break;

    case AH_DECODE_AML:

        AhFindAmlOpcode (Name);
        break;

    case AH_DECODE_AML_OPCODE:

        AhDecodeAmlOpcode (Name);
        break;

    case AH_DECODE_AML_TYPE:

        AhFindAmlTypes (Name);
        break;

    case AH_DECODE_PREDEFINED_NAME:

        AhFindPredefinedNames (Name);
        break;

    case AH_DECODE_ASL:

        AhFindAslOperators (Name);
        break;

    case AH_DECODE_ASL_KEYWORD:

        AhFindAslKeywords (Name);
        break;

    case AH_DISPLAY_DEVICE_IDS:

        AhDisplayDeviceIds (Name);
        break;

    case AH_DECODE_EXCEPTION:

        AhDecodeException (Name);
        break;

    case AH_DISPLAY_UUIDS:

        AhDisplayUuids ();
        break;

    case AH_DISPLAY_TABLES:

        AhDisplayTables ();
        break;

    case AH_DISPLAY_DIRECTIVES:

        AhDisplayDirectives ();
        break;

   default:

        if (!Name)
        {
            AhFindAslOperators (Name);
            break;
        }

        if (*Name == '_')
        {
            AhFindPredefinedNames (Name);
        }
        else
        {
            AhFindAslAndAmlOperators (Name);
        }
        break;
    }

    return (0);
}
