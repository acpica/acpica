/******************************************************************************
 *
 * Module Name: dbstats - Generation and display of ACPI table statistics
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


#include "acpi.h"
#include "acdebug.h"
#include "amlcode.h"
#include "acparser.h"

#ifdef ENABLE_DEBUGGER

#define _COMPONENT          DEBUGGER
        MODULE_NAME         ("dbstats");

ARGUMENT_INFO               AcpiDbStatTypes [] =
{
    {"ALLOCATIONS"},
    {"OBJECTS"},
    {"MEMORY"},
    {"MISC"},
    {"TABLES"},
    {NULL}           /* Must be null terminated */
};

#define CMD_OBJECTS         0
#define CMD_ALLOCATIONS     1
#define CMD_MEMORY          2
#define CMD_MISC            3
#define CMD_TABLES          4

/*
 * Statistics
 */

UINT32                      NumNames = 0;
UINT32                      NumMethods = 0;
UINT32                      NumRegions = 0;
UINT32                      NumPackages = 0;
UINT32                      NumAliases = 0;
UINT32                      NumDevices = 0;
UINT32                      NumFieldDefs = 0;
UINT32                      NumThermalZones =  0;
UINT32                      NumNamedObjects = 0;
UINT32                      NumGrammarElements = 0;
UINT32                      NumMethodElements = 0;
UINT32                      NumMutexes = 0;
UINT32                      NumPowerResources = 0;
UINT32                      NumBankFields = 0;
UINT32                      NumIndexFields = 0;
UINT32                      NumEvents = 0;

UINT32                      SizeOfParseTree;
UINT32                      SizeOfMethodTrees;
UINT32                      SizeOfNameTableEntries;
UINT32                      SizeOfAcpiObjects;


/*****************************************************************************
 *
 * FUNCTION:    AcpiDbDisplayStatistics
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION:
 *
 ****************************************************************************/

ACPI_STATUS
AcpiDbDisplayStatistics (
    INT8                    *TypeArg)
{
    UINT32                  i;
    UINT32                  Type;


    if (!AcpiGbl_DSDT)
    {
        AcpiOsPrintf ("*** Warning:  There is no DSDT loaded\n");
    }

    if (!TypeArg)
    {
        AcpiOsPrintf ("Use subcommand OBJECTS, MEMORY, MISC, or TABLES\n");
        return AE_OK;
    }

    STRUPR (TypeArg);
    Type = AcpiDbMatchArgument (TypeArg, AcpiDbStatTypes);
    if (Type == (UINT32) -1)
    {
        AcpiOsPrintf ("Invalid or unsupported argument\n");
        return AE_OK;
    }


    switch (Type)
    {
#ifndef PARSER_ONLY
    case CMD_ALLOCATIONS:
        AcpiCmDumpAllocationInfo ();
        break;
#endif

    case CMD_TABLES:

        AcpiOsPrintf ("ACPI Table Information:\n\n");
        if (AcpiGbl_DSDT)
        {
            AcpiOsPrintf ("DSDT Length:................% 7ld (0x%X)\n", AcpiGbl_DSDT->Length, AcpiGbl_DSDT->Length);
        }
        break;

    case CMD_OBJECTS:

        AcpiOsPrintf ("\nObjects defined in the current namespace:\n\n");
        AcpiOsPrintf ("Names:......................% 7ld\n", NumNames);
        AcpiOsPrintf ("Events:.....................% 7ld\n", NumEvents);
        AcpiOsPrintf ("Devices:....................% 7ld\n", NumDevices);
        AcpiOsPrintf ("Aliases:....................% 7ld\n", NumAliases);
        AcpiOsPrintf ("Mutexes:....................% 7ld\n", NumMutexes);
        AcpiOsPrintf ("Packages:...................% 7ld\n", NumPackages);
        AcpiOsPrintf ("Bank Fields.................% 7ld\n", NumBankFields);
        AcpiOsPrintf ("Index Fields................% 7ld\n", NumIndexFields);
        AcpiOsPrintf ("Thermal Zones:..............% 7ld\n", NumThermalZones);
        AcpiOsPrintf ("Power Resources:............% 7ld\n", NumPowerResources);
        AcpiOsPrintf ("Control Methods:............% 7ld\n", NumMethods);
        AcpiOsPrintf ("Operation Regions:..........% 7ld\n", NumRegions);
        AcpiOsPrintf ("Field Definitions:..........% 7ld\n", NumFieldDefs);
        AcpiOsPrintf ("Total Named objects:........% 7ld\n", NumNamedObjects);

        AcpiOsPrintf ("\n");

        AcpiOsPrintf ("ASL/AML Grammar Usage:\n\n");
        AcpiOsPrintf ("Elements Inside Methods:....% 7ld\n", NumMethodElements);
        AcpiOsPrintf ("Elements Outside Methods:...% 7ld\n", NumGrammarElements - NumMethodElements);
        AcpiOsPrintf ("Total Grammar Elements:.....% 7ld\n", NumGrammarElements);
        break;

    case CMD_MEMORY:

        AcpiOsPrintf ("\nDynamic Memory Estimates:\n\n");
        AcpiOsPrintf ("Parse Tree without Methods:.% 7ld\n", SizeOfParseTree);
        AcpiOsPrintf ("Control Method Parse Trees:.% 7ld (If parsed simultaneously)\n", SizeOfMethodTrees);
        AcpiOsPrintf ("Named Object NTEs:..........% 7ld (%d objects)\n", SizeOfNameTableEntries, NumNamedObjects);
        AcpiOsPrintf ("Named Internal Objects......% 7ld\n", SizeOfAcpiObjects);
        AcpiOsPrintf ("State Cache size............% 7ld\n", AcpiGbl_GenericStateCacheDepth * sizeof (ACPI_GENERIC_STATE));
        AcpiOsPrintf ("Parse Cache size............% 7ld\n", AcpiGbl_ParseCacheDepth * sizeof (ACPI_GENERIC_OP));
        AcpiOsPrintf ("Object Cache size...........% 7ld\n", AcpiGbl_ObjectCacheDepth * sizeof (ACPI_OBJECT_INTERNAL));
        AcpiOsPrintf ("WalkState Cache size........% 7ld\n", AcpiGbl_WalkStateCacheDepth * sizeof (ACPI_WALK_STATE));

        AcpiOsPrintf ("\n");

        AcpiOsPrintf ("Cache Statistics:\n\n");
        AcpiOsPrintf ("State Cache requests........% 7ld\n", AcpiGbl_StateCacheRequests);
        AcpiOsPrintf ("State Cache hits............% 7ld\n", AcpiGbl_StateCacheHits);
        AcpiOsPrintf ("State Cache depth...........% 7ld (%d remaining entries)\n", AcpiGbl_GenericStateCacheDepth,
                                                            MAX_STATE_CACHE_DEPTH - AcpiGbl_GenericStateCacheDepth);
        AcpiOsPrintf ("Parse Cache requests........% 7ld\n", AcpiGbl_ParseCacheRequests);
        AcpiOsPrintf ("Parse Cache hits............% 7ld\n", AcpiGbl_ParseCacheHits);
        AcpiOsPrintf ("Parse Cache depth...........% 7ld (%d remaining entries)\n", AcpiGbl_ParseCacheDepth,
                                                            MAX_PARSE_CACHE_DEPTH - AcpiGbl_ParseCacheDepth);
        AcpiOsPrintf ("Object Cache requests.......% 7ld\n", AcpiGbl_ObjectCacheRequests);
        AcpiOsPrintf ("Object Cache hits...........% 7ld\n", AcpiGbl_ObjectCacheHits);
        AcpiOsPrintf ("Object Cache depth..........% 7ld (%d remaining entries)\n", AcpiGbl_ObjectCacheDepth,
                                                            MAX_OBJECT_CACHE_DEPTH - AcpiGbl_ObjectCacheDepth);
        AcpiOsPrintf ("WalkState Cache requests....% 7ld\n", AcpiGbl_WalkStateCacheRequests);
        AcpiOsPrintf ("WalkState Cache hits........% 7ld\n", AcpiGbl_WalkStateCacheHits);
        AcpiOsPrintf ("WalkState Cache depth.......% 7ld (%d remaining entries)\n", AcpiGbl_WalkStateCacheDepth,
                                                            MAX_WALK_CACHE_DEPTH - AcpiGbl_WalkStateCacheDepth);
        break;

    case CMD_MISC:

        AcpiOsPrintf ("\nMiscellaneous Statistics:\n\n");
        AcpiOsPrintf ("Calls to AcpiPsFind:..  ........% 7ld\n", AcpiGbl_PsFindCount);
        AcpiOsPrintf ("Calls to AcpiNsLookup:..........% 7ld\n", AcpiGbl_NsLookupCount);

        AcpiOsPrintf ("\n");

        AcpiOsPrintf ("Mutex usage:\n\n");
        for (i = 0; i < NUM_MTX; i++)
        {
            AcpiOsPrintf ("%-20s:       % 7ld\n", AcpiCmGetMutexName (i), AcpiGbl_AcpiMutexInfo[i].UseCount);
        }
        break;
    }

    AcpiOsPrintf ("\n");
    return AE_OK;
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiDbGenerateStatistics
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION:
 *
 ****************************************************************************/

void
AcpiDbGenerateStatistics (
    ACPI_GENERIC_OP         *Root,
    BOOLEAN                 IsMethod)
{
    ACPI_GENERIC_OP         *Op;


    Op = AcpiPsGetChild (Root);

    while (Op)
    {
        switch (Op->Opcode)
        {
        case AML_METHOD_OP:
            NumMethods++;
            break;

        case AML_NAME_OP:
            NumNames++;
            break;

        case AML_REGION_OP:
            NumRegions++;
            break;

        case AML_ALIAS_OP:
            NumAliases++;
            break;

        case AML_PACKAGE_OP:
            NumPackages++;
            break;

        case AML_DEVICE_OP:
            NumDevices++;
            break;

        case AML_THERMAL_ZONE_OP:
            NumThermalZones++;
            break;

        case AML_DEF_FIELD_OP:
            NumFieldDefs++;
            break;

        case AML_POWER_RES_OP:
            NumPowerResources++;
            break;

        case AML_MUTEX_OP:
            NumMutexes++;
            break;

        case AML_BANK_FIELD_OP:
            NumBankFields++;
            break;

        case AML_INDEX_FIELD_OP:
            NumIndexFields++;
            break;

        case AML_EVENT_OP:
            NumEvents++;
            break;
        }

        if (AcpiPsIsNamedOp (Op->Opcode))
        {
            NumNamedObjects++;
        }

        if (IsMethod)
        {
            NumMethodElements++;
        }

        NumGrammarElements++;
        Op = AcpiPsGetDepthNext (Root, Op);
    }


    SizeOfParseTree             = (NumGrammarElements - NumMethodElements) * (UINT32) sizeof (ACPI_GENERIC_OP);
    SizeOfMethodTrees           = NumMethodElements * (UINT32) sizeof (ACPI_GENERIC_OP);
    SizeOfNameTableEntries      = NumNamedObjects * (UINT32) sizeof (ACPI_NAMED_OBJECT);
    SizeOfAcpiObjects           = NumNamedObjects * (UINT32) sizeof (ACPI_OBJECT_INTERNAL);

}

#endif /* ENABLE_DEBUGGER  */
