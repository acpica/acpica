
/******************************************************************************
 * 
 * Module Name: cmglobal - Global variables for the ACPI subsystem
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

#define __CMGLOBAL_C__
#define DEFINE_ACPI_GLOBALS

#include "acpi.h"
#include "events.h"
#include "namesp.h"
#include "interp.h"


#define _COMPONENT          MISCELLANEOUS
        MODULE_NAME         ("cmglobal");



/******************************************************************************
 *
 * Static global variable initialization.
 *
 ******************************************************************************/

/* 
 * We want the debug switches statically initialized so they 
 * are already set when the debugger is entered.
 */

/* Debug switch - level and trace mask */

#ifdef ACPI_DEBUG
UINT32                      DebugLevel = DEBUG_DEFAULT;
#else
UINT32                      DebugLevel = NORMAL_DEFAULT;
#endif

/* Debug switch - layer (component) mask */

UINT32                      DebugLayer = ALL_COMPONENTS;
UINT32                      Acpi_GblNestingLevel = 0;


/* Debugger globals */

BOOLEAN                     Acpi_GblDbTerminateThreads = FALSE;
BOOLEAN                     Acpi_GblMethodExecuting = FALSE;

/* System flags */

UINT32                      Acpi_GblSystemFlags = 0;
UINT32                      Acpi_GblStartupFlags = 0;
BOOLEAN                     Acpi_GblShutdown = TRUE;        /* System starts unitialized! */



/******************************************************************************
 *
 * Namespace globals
 *
 ******************************************************************************/


/* 
 * Names built-in to the interpreter
 *
 * Initial values are currently supported only for types String and Number.
 * To avoid type punning, both are specified as strings in this table.
 */

PREDEFINED_NAMES            Acpi_GblPreDefinedNames[] = 
{
    {"_GPE",    INTERNAL_TYPE_DEF_ANY},
    {"_PR_",    INTERNAL_TYPE_DEF_ANY},
    {"_SB_",    INTERNAL_TYPE_DEF_ANY},
    {"_SI_",    INTERNAL_TYPE_DEF_ANY},
    {"_TZ_",    INTERNAL_TYPE_DEF_ANY},
    {"_REV",    ACPI_TYPE_NUMBER, "2"},
    {"_OS_",    ACPI_TYPE_STRING, ACPI_OS_NAME},
    {"_GL_",    ACPI_TYPE_MUTEX, "0"},

    /* Table terminator */

    {NULL,      ACPI_TYPE_ANY}
};


/* 
 * Properties of the ACPI Object Types, both internal and external.
 * 
 * Elements of AcpiNsProperties are bit significant
 * and the table is indexed by values of ACPI_OBJECT_TYPE
 */

UINT8                       Acpi_GblNsProperties[] = 
{
    NSP_NORMAL,                 /* 00 Any              */
    NSP_NORMAL,                 /* 01 Number           */
    NSP_NORMAL,                 /* 02 String           */
    NSP_NORMAL,                 /* 03 Buffer           */
    NSP_LOCAL,                  /* 04 Package          */
    NSP_NORMAL,                 /* 05 FieldUnit        */
    NSP_NEWSCOPE | NSP_LOCAL,   /* 06 Device           */
    NSP_LOCAL,                  /* 07 AcpiEvent            */
    NSP_NEWSCOPE | NSP_LOCAL,   /* 08 Method           */
    NSP_LOCAL,                  /* 09 Mutex            */
    NSP_LOCAL,                  /* 10 Region           */
    NSP_NEWSCOPE | NSP_LOCAL,   /* 11 Power            */
    NSP_NEWSCOPE | NSP_LOCAL,   /* 12 Processor        */
    NSP_NEWSCOPE | NSP_LOCAL,   /* 13 Thermal          */
    NSP_NORMAL,                 /* 14 BufferField      */
    NSP_NORMAL,                 /* 15 DdbHandle        */
    NSP_NORMAL,                 /* 16 reserved         */
    NSP_NORMAL,                 /* 17 reserved         */
    NSP_NORMAL,                 /* 18 reserved         */
    NSP_NORMAL,                 /* 19 reserved         */
    NSP_NORMAL,                 /* 20 reserved         */
    NSP_NORMAL,                 /* 21 reserved         */
    NSP_NORMAL,                 /* 22 reserved         */
    NSP_NORMAL,                 /* 23 reserved         */
    NSP_NORMAL,                 /* 24 reserved         */
    NSP_NORMAL,                 /* 25 DefField         */
    NSP_NORMAL,                 /* 26 BankField        */
    NSP_NORMAL,                 /* 27 IndexField       */
    NSP_NORMAL,                 /* 28 DefFieldDefn     */
    NSP_NORMAL,                 /* 29 BankFieldDefn    */
    NSP_NORMAL,                 /* 30 IndexFieldDefn   */
    NSP_NORMAL,                 /* 31 If               */
    NSP_NORMAL,                 /* 32 Else             */
    NSP_NORMAL,                 /* 33 While            */
    NSP_NEWSCOPE,               /* 34 Scope            */
    NSP_LOCAL,                  /* 35 DefAny           */
    NSP_NORMAL,                 /* 36 Reference           */
    NSP_NORMAL,                 /* 37 Alias            */
    NSP_NORMAL,                 /* 38 Notify           */
    NSP_NORMAL,                 /* 39 Address Handler  */
    NSP_NORMAL                  /* 40 Invalid          */
};


/******************************************************************************
 *
 * Table globals
 *
 ******************************************************************************/


ACPI_TABLE_DESC             Acpi_GblAcpiTables[NUM_ACPI_TABLES];


ACPI_TABLE_SUPPORT          Acpi_GblAcpiTableData[NUM_ACPI_TABLES] =
{
                 /* Name,   Signature,  Signature size,    How many allowed?,   Supported?  Global typed pointer */

    /* RSDP 0 */ {"RSDP",   RSDP_SIG, sizeof (RSDP_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      NULL},
    /* APIC 1 */ {APIC_SIG, APIC_SIG, sizeof (APIC_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      (void **) &Acpi_GblAPIC},
    /* DSDT 2 */ {DSDT_SIG, DSDT_SIG, sizeof (DSDT_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      (void **) &Acpi_GblDSDT},
    /* FACP 3 */ {FACP_SIG, FACP_SIG, sizeof (FACP_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      (void **) &Acpi_GblFACP},
    /* FACS 4 */ {FACS_SIG, FACS_SIG, sizeof (FACS_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      (void **) &Acpi_GblFACS},
    /* PSDT 5 */ {PSDT_SIG, PSDT_SIG, sizeof (PSDT_SIG)-1, ACPI_TABLE_MULTIPLE, AE_OK,      NULL},
    /* RSDT 6 */ {RSDT_SIG, RSDT_SIG, sizeof (RSDT_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      NULL},
    /* SSDT 7 */ {SSDT_SIG, SSDT_SIG, sizeof (SSDT_SIG)-1, ACPI_TABLE_MULTIPLE, AE_OK,      NULL},
    /* SBST 8 */ {SBST_SIG, SBST_SIG, sizeof (SBST_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      (void **) &Acpi_GblSBST},
    /* BOOT 9 */ {BOOT_SIG, BOOT_SIG, sizeof (BOOT_SIG)-1, ACPI_TABLE_SINGLE,   AE_SUPPORT, NULL}
};

ACPI_INIT_DATA Acpi_GblAcpiInitData;



/******************************************************************************
 *
 * Strings and procedures used for debug only
 *
 ******************************************************************************/

#ifdef ACPI_DEBUG

char                        *MsgAcpiErrorBreak = "*** Break on ACPI_ERROR ***\n";


/*****************************************************************************
 * 
 * FUNCTION:    AcpiCmGetMutexName
 *
 * PARAMETERS:  None.
 *
 * RETURN:      Status
 * 
 * DESCRIPTION: Translate a mutex ID into a name string (Debug only)
 *
 ****************************************************************************/

char *
AcpiCmGetMutexName (
    UINT32                  MutexId)
{

    if (MutexId > MAX_MTX)
    {
        return ("Invalid Mutex ID");
    }

    return (Acpi_GblMutexNames[MutexId]);
}


/* 
 * Elements of Acpi_GblNsTypeNames below must match
 * one-to-one with values of ACPI_OBJECT_TYPE
 *
 * The type ACPI_TYPE_ANY (Untyped) is used as a "don't care" when searching; when 
 * stored in a table it really means that we have thus far seen no evidence to 
 * indicatewhat type is actually going to be stored for this entry.
 */

static char                 Acpi_GblBadType[] = "UNDEFINED";
#define TYPE_NAME_LENGTH    9                       /* Maximum length of each string */

static char                 *Acpi_GblNsTypeNames[] =    /* printable names of ACPI types */
{
    "Untyped",
    "Number",
    "String",
    "Buffer",
    "Package",
    "FieldUnit",
    "Device",
    "Event",
    "Method",
    "Mutex",
    "Region",
    "Power",
    "Processor",
    "Thermal",
    "BufferFld",
    "DdbHandle", 
     Acpi_GblBadType, 
     Acpi_GblBadType, 
     Acpi_GblBadType, 
     Acpi_GblBadType,
     Acpi_GblBadType, 
     Acpi_GblBadType, 
     Acpi_GblBadType, 
     Acpi_GblBadType, 
     Acpi_GblBadType,
    "DefField",
    "BnkField",
    "IdxField",
    "DefFldDfn",
    "BnkFldDfn",
    "IdxFldDfn",
    "If",
    "Else",
    "While",
    "Scope",
    "DefAny",
    "Reference",
    "Alias",
    "Notify", 
    "AddrHndlr", 
    "Invalid"
};



/*****************************************************************************
 * 
 * FUNCTION:    AcpiCmGetTypeName
 *
 * PARAMETERS:  None.
 *
 * RETURN:      Status
 * 
 * DESCRIPTION: Translate a Type ID into a name string (Debug only)
 *
 ****************************************************************************/

char *
AcpiCmGetTypeName (
    UINT32                  Type)
{

    if (Type > INTERNAL_TYPE_INVALID)
    {
        return (Acpi_GblBadType);
    }

    return (Acpi_GblNsTypeNames[Type]);
}

#endif



/*****************************************************************************
 * 
 * FUNCTION:    AcpiCmValidObjectType
 *
 * PARAMETERS:  None.
 *
 * RETURN:      TRUE if valid object type
 * 
 * DESCRIPTION: Validate an object type
 *
 ****************************************************************************/

BOOLEAN
AcpiCmValidObjectType (
    UINT32                  Type)
{
    
    if (Type > ACPI_TYPE_MAX)
    {
        if ((Type < INTERNAL_TYPE_BEGIN) ||
            (Type > INTERNAL_TYPE_MAX))
        {
            return FALSE;
        }
    }

    return TRUE;
}



/*****************************************************************************
 * 
 * FUNCTION:    AcpiCmFormatException
 *
 * PARAMETERS:  Status              - Acpi status to be formatted
 *
 * RETURN:      Formatted status string
 *
 * DESCRIPTION: Convert an ACPI exception to a string
 *
 ****************************************************************************/

char *
AcpiCmFormatException (
    ACPI_STATUS             Status)
{

    if (Status > ACPI_MAX_STATUS)
    {
        return "UNKNOWN_STATUS";
    }

    return (Acpi_GblExceptionNames [Status]);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiCmAllocateOwnerId
 *
 * PARAMETERS:  IdType          - Type of ID (method or table)
 *
 * DESCRIPTION: Allocate a table or method owner id
 *
 ***************************************************************************/

ACPI_OWNER_ID
AcpiCmAllocateOwnerId (
    UINT32                  IdType)
{
    ACPI_OWNER_ID           OwnerId = 0xFFFF;


    FUNCTION_TRACE ("CmAllocateOwnerId");


    AcpiCmAcquireMutex (MTX_CACHES);

    switch (IdType)
    {
    case OWNER_TYPE_TABLE:

        OwnerId = Acpi_GblNextTableOwnerId;
        Acpi_GblNextTableOwnerId++;

        if (Acpi_GblNextTableOwnerId == FIRST_METHOD_ID)
        {
            Acpi_GblNextTableOwnerId = FIRST_TABLE_ID;
        }
        break;


    case OWNER_TYPE_METHOD:

        OwnerId = Acpi_GblNextMethodOwnerId;
        Acpi_GblNextMethodOwnerId++;

        if (Acpi_GblNextMethodOwnerId == FIRST_TABLE_ID)
        {
            Acpi_GblNextMethodOwnerId = FIRST_METHOD_ID;
        }
        break;
    }


    AcpiCmReleaseMutex (MTX_CACHES);

    return_VALUE (OwnerId);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiCmInitGlobals
 *
 * PARAMETERS:  none
 *
 * DESCRIPTION: Init library globals.  All globals that require specific
 *              initialization should be initialized here!
 *
 ***************************************************************************/

void 
AcpiCmInitGlobals (ACPI_INIT_DATA *InitData)
{
    UINT32                  i;

    FUNCTION_TRACE ("CmInitGlobals");


    if (InitData)
    {
        MEMCPY (&Acpi_GblAcpiInitData, InitData, sizeof (ACPI_INIT_DATA));
    } 

    else 
    {
        MEMSET (&Acpi_GblAcpiInitData, 0, sizeof (ACPI_INIT_DATA));
    }

    /* ACPI table structure */

    for (i = 0; i < ACPI_TABLE_MAX; i++)
    {
        Acpi_GblAcpiTables[i].Prev          = &Acpi_GblAcpiTables[i];
        Acpi_GblAcpiTables[i].Next          = &Acpi_GblAcpiTables[i];
        Acpi_GblAcpiTables[i].Pointer       = NULL;
        Acpi_GblAcpiTables[i].Length        = 0;
        Acpi_GblAcpiTables[i].Allocation    = ACPI_MEM_NOT_ALLOCATED;
        Acpi_GblAcpiTables[i].Count         = 0;
    }
      

    /* Address Space handler array */

    for (i = 0; i < ACPI_MAX_ADDRESS_SPACE; i++)
    {
        Acpi_GblAddressSpaces[i].Handler    = NULL;
        Acpi_GblAddressSpaces[i].Context    = NULL;
    }

    /* Mutex locked flags */

    for (i = 0; i < NUM_MTX; i++)
    {
        Acpi_GblAcpiMutexInfo[i].Mutex      = NULL;
        Acpi_GblAcpiMutexInfo[i].Locked     = FALSE;
        Acpi_GblAcpiMutexInfo[i].UseCount   = 0;
    }

    /* Global notify handlers */

    Acpi_GblSysNotify.Handler       = NULL;
    Acpi_GblDrvNotify.Handler       = NULL;

    /* Global "typed" ACPI table pointers */

    Acpi_GblRSDP                    = NULL;
    Acpi_GblRSDT                    = NULL;
    Acpi_GblFACS                    = NULL;
    Acpi_GblFACP                    = NULL;
    Acpi_GblAPIC                    = NULL;
    Acpi_GblDSDT                    = NULL;
    Acpi_GblSBST                    = NULL;


    /* Global Lock support */

    Acpi_GblGlobalLockAcquired      = FALSE;
    Acpi_GblGlobalLockThreadCount   = 0;

    /* Miscellaneous variables */

    Acpi_GblSystemFlags             = 0;
    Acpi_GblStartupFlags            = 0;
    Acpi_GblGlobalLockSet           = FALSE;
    Acpi_GblRsdpOriginalLocation    = 0;
    Acpi_GblWhenToParseMethods      = METHOD_PARSE_CONFIGURATION;
    Acpi_GblCmSingleStep            = FALSE;
    Acpi_GblDbTerminateThreads      = FALSE;
    Acpi_GblShutdown                = FALSE;
    Acpi_GblNsLookupCount           = 0;
    Acpi_GblPsFindCount             = 0;
    Acpi_GblAcpiHardwarePresent     = TRUE;
    Acpi_GblNextTableOwnerId        = FIRST_TABLE_ID;
    Acpi_GblNextMethodOwnerId       = FIRST_METHOD_ID;
    Acpi_GblDebuggerConfiguration   = DEBUGGER_THREADING;

    /* Cache of small "state" objects */

    Acpi_GblGenericStateCache       = NULL;
    Acpi_GblGenericStateCacheDepth  = 0;
    Acpi_GblStateCacheRequests      = 0;
    Acpi_GblStateCacheHits          = 0;

    Acpi_GblParseCache              = NULL;
    Acpi_GblParseCacheDepth         = 0;
    Acpi_GblParseCacheRequests      = 0;
    Acpi_GblParseCacheHits          = 0;

    Acpi_GblObjectCache             = NULL;
    Acpi_GblObjectCacheDepth        = 0;
    Acpi_GblObjectCacheRequests     = 0;
    Acpi_GblObjectCacheHits         = 0;

    Acpi_GblWalkStateCache          = NULL;
    Acpi_GblWalkStateCacheDepth     = 0;
    Acpi_GblWalkStateCacheRequests  = 0;
    Acpi_GblWalkStateCacheHits      = 0;

    /* Interpreter */

    Acpi_GblBufSeq                  = 0;
    Acpi_GblNamedObjectErr          = FALSE;

    /* Parser */

    Acpi_GblParsedNamespaceRoot     = NULL;

    /* Hardware oriented */

    Acpi_GblGpe0EnableRegisterSave  = NULL;
    Acpi_GblGpe1EnableRegisterSave  = NULL;
    Acpi_GblOriginalMode            = SYS_MODE_UNKNOWN;   /*  original ACPI/legacy mode   */
    Acpi_GblGpeRegisters            = NULL;
    Acpi_GblGpeInfo                 = NULL;

    /* Namespace */

    Acpi_GblRootObject              = &Acpi_GblRootObjStruct;

    Acpi_GblRootObject->Name        = ACPI_ROOT_NAME;
    Acpi_GblRootObject->DataType    = DESC_TYPE_NTE;
    Acpi_GblRootObject->Type        = ACPI_TYPE_ANY;
    Acpi_GblRootObject->Fill1       = 0;
    Acpi_GblRootObject->Scope       = NULL;
    Acpi_GblRootObject->ParentEntry = NULL;
    Acpi_GblRootObject->NextEntry   = NULL;
    Acpi_GblRootObject->PrevEntry   = NULL;
    Acpi_GblRootObject->Object      = NULL;
    
    /* Memory allocation metrics - compiled out in non-debug mode. */

    INITIALIZE_ALLOCATION_METRICS();

    return_VOID;
}   


