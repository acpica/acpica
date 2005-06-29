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
#include "debugger.h"
#include "amlcode.h"
#include "parser.h"

#ifdef ACPI_DEBUG

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
UINT32                      SizeOfNTEs;
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
    char                    *TypeArg)
{
    UINT32                  i;
    UINT32                  Type;


    if (!AcpiGbl_DSDT)
    {
        AcpiOsdPrintf ("*** Warning:  There is no DSDT loaded\n");
    }

    if (!TypeArg)
    {
        AcpiOsdPrintf ("Use subcommand OBJECTS, MEMORY, MISC, or TABLES\n");
        return AE_OK;
    }

    STRUPR (TypeArg);
    Type = AcpiDbMatchArgument (TypeArg, AcpiDbStatTypes);
    if (Type == (UINT32) -1)
    {
        AcpiOsdPrintf ("Invalid or unsupported argument\n");
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

        AcpiOsdPrintf ("ACPI Table Information:\n\n");
        if (AcpiGbl_DSDT)
        {
            AcpiOsdPrintf ("DSDT Length:................% 7ld (0x%X)\n", AcpiGbl_DSDT->Length, AcpiGbl_DSDT->Length);
        }
        break;

    case CMD_OBJECTS:

        AcpiOsdPrintf ("\nObjects defined in the current namespace:\n\n");
        AcpiOsdPrintf ("Names:......................% 7ld\n", NumNames);
        AcpiOsdPrintf ("Events:.....................% 7ld\n", NumEvents);
        AcpiOsdPrintf ("Devices:....................% 7ld\n", NumDevices);
        AcpiOsdPrintf ("Aliases:....................% 7ld\n", NumAliases);
        AcpiOsdPrintf ("Mutexes:....................% 7ld\n", NumMutexes);
        AcpiOsdPrintf ("Packages:...................% 7ld\n", NumPackages);
        AcpiOsdPrintf ("Bank Fields.................% 7ld\n", NumBankFields);
        AcpiOsdPrintf ("Index Fields................% 7ld\n", NumIndexFields);
        AcpiOsdPrintf ("Thermal Zones:..............% 7ld\n", NumThermalZones);
        AcpiOsdPrintf ("Power Resources:............% 7ld\n", NumPowerResources);
        AcpiOsdPrintf ("Control Methods:............% 7ld\n", NumMethods);
        AcpiOsdPrintf ("Operation Regions:..........% 7ld\n", NumRegions);
        AcpiOsdPrintf ("Field Definitions:..........% 7ld\n", NumFieldDefs);
        AcpiOsdPrintf ("Total Named objects:........% 7ld\n", NumNamedObjects);

        AcpiOsdPrintf ("\n");

        AcpiOsdPrintf ("ASL/AML Grammar Usage:\n\n");
        AcpiOsdPrintf ("Elements Inside Methods:....% 7ld\n", NumMethodElements);
        AcpiOsdPrintf ("Elements Outside Methods:...% 7ld\n", NumGrammarElements - NumMethodElements);
        AcpiOsdPrintf ("Total Grammar Elements:.....% 7ld\n", NumGrammarElements);
        break;

    case CMD_MEMORY:

        AcpiOsdPrintf ("\nDynamic Memory Estimates:\n\n");
        AcpiOsdPrintf ("Parse Tree without Methods:.% 7ld\n", SizeOfParseTree);
        AcpiOsdPrintf ("Control Method Parse Trees:.% 7ld (If parsed simultaneously)\n", SizeOfMethodTrees);
        AcpiOsdPrintf ("Named Object NTEs:..........% 7ld (%d objects)\n", SizeOfNTEs, NumNamedObjects);
        AcpiOsdPrintf ("Named Internal Objects......% 7ld\n", SizeOfAcpiObjects);
        AcpiOsdPrintf ("State Cache size............% 7ld\n", AcpiGbl_GenericStateCacheDepth * sizeof (ACPI_GENERIC_STATE));
        AcpiOsdPrintf ("Parse Cache size............% 7ld\n", AcpiGbl_ParseCacheDepth * sizeof (ACPI_GENERIC_OP));
        AcpiOsdPrintf ("Object Cache size...........% 7ld\n", AcpiGbl_ObjectCacheDepth * sizeof (ACPI_OBJECT_INTERNAL));
        AcpiOsdPrintf ("WalkState Cache size........% 7ld\n", AcpiGbl_WalkStateCacheDepth * sizeof (ACPI_WALK_STATE));

        AcpiOsdPrintf ("\n");

        AcpiOsdPrintf ("Cache Statistics:\n\n");
        AcpiOsdPrintf ("State Cache requests........% 7ld\n", AcpiGbl_StateCacheRequests);
        AcpiOsdPrintf ("State Cache hits............% 7ld\n", AcpiGbl_StateCacheHits);
        AcpiOsdPrintf ("State Cache depth...........% 7ld\n", AcpiGbl_GenericStateCacheDepth);
        AcpiOsdPrintf ("Parse Cache requests........% 7ld\n", AcpiGbl_ParseCacheRequests);
        AcpiOsdPrintf ("Parse Cache hits............% 7ld\n", AcpiGbl_ParseCacheHits);
        AcpiOsdPrintf ("Parse Cache depth...........% 7ld\n", AcpiGbl_ParseCacheDepth);
        AcpiOsdPrintf ("Object Cache requests.......% 7ld\n", AcpiGbl_ObjectCacheRequests);
        AcpiOsdPrintf ("Object Cache hits...........% 7ld\n", AcpiGbl_ObjectCacheHits);
        AcpiOsdPrintf ("Object Cache depth..........% 7ld\n", AcpiGbl_ObjectCacheDepth);
        AcpiOsdPrintf ("WalkState Cache requests....% 7ld\n", AcpiGbl_WalkStateCacheRequests);
        AcpiOsdPrintf ("WalkState Cache hits........% 7ld\n", AcpiGbl_WalkStateCacheHits);
        AcpiOsdPrintf ("WalkState Cache depth.......% 7ld\n", AcpiGbl_WalkStateCacheDepth);
        break;

    case CMD_MISC:

        AcpiOsdPrintf ("\nMiscellaneous Statistics:\n\n");
        AcpiOsdPrintf ("Calls to AcpiPsFind:..  ........% 7ld\n", AcpiGbl_PsFindCount);
        AcpiOsdPrintf ("Calls to AcpiNsLookup:..........% 7ld\n", AcpiGbl_NsLookupCount);

        AcpiOsdPrintf ("\n");

        AcpiOsdPrintf ("Mutex usage:\n\n");
        for (i = 0; i < NUM_MTX; i++)
        {
            AcpiOsdPrintf ("%-20s:       % 7ld\n", AcpiCmGetMutexName (i), AcpiGbl_AcpiMutexInfo[i].UseCount);
        }
        break;
    }

    AcpiOsdPrintf ("\n");
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



    SizeOfParseTree     = (NumGrammarElements - NumMethodElements) * (UINT32) sizeof (ACPI_GENERIC_OP);
    SizeOfMethodTrees   = NumMethodElements * (UINT32) sizeof (ACPI_GENERIC_OP);
    SizeOfNTEs          = NumNamedObjects * (UINT32) sizeof (NAME_TABLE_ENTRY);
    SizeOfAcpiObjects   = NumNamedObjects * (UINT32) sizeof (ACPI_OBJECT_INTERNAL);

}

#endif /* ACPI_DEBUG  */
