
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

#include <acpi.h>
#include <events.h>
#include <namesp.h>
#include <interp.h>


#define _COMPONENT          MISCELLANEOUS
        MODULE_NAME         ("cmglobal");



/******************************************************************************
 *
 * Static global variable initialization.
 *
 ******************************************************************************/

UINT32                        Gbl_AcpiCaVersion = ACPI_CA_VERSION;

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
UINT32                      Gbl_NestingLevel = 0;


/* System flags */

UINT32                      Gbl_SystemFlags = 0;
UINT32                      Gbl_StartupFlags = 0;
BOOLEAN						Gbl_Shutdown = TRUE;		/* System starts unitialized! */



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

PREDEFINED_NAMES            Gbl_PreDefinedNames[] = 
{
    {"_GPE",    INTERNAL_TYPE_DefAny},
    {"_PR_",    INTERNAL_TYPE_DefAny},
    {"_SB_",    INTERNAL_TYPE_DefAny},
    {"_SI_",    INTERNAL_TYPE_DefAny},
    {"_TZ_",    INTERNAL_TYPE_DefAny},
    {"_REV",    ACPI_TYPE_Number, "2"},
    {"_OS_",    ACPI_TYPE_String, ACPI_OS_NAME},
    {"_GL_",    ACPI_TYPE_Mutex, "0"},

    /* Table terminator */

    {NULL,      ACPI_TYPE_Any}
};


/* 
 * Properties of the ACPI Object Types, both internal and external.
 * 
 * Elements of NsProperties are bit significant
 * and the table is indexed by values of ACPI_OBJECT_TYPE
 */

UINT8                       Gbl_NsProperties[] = 
{
    NSP_NORMAL,                 /* 00 Any              */
    NSP_NORMAL,                 /* 01 Number           */
    NSP_NORMAL,                 /* 02 String           */
    NSP_NORMAL,                 /* 03 Buffer           */
    NSP_LOCAL,                  /* 04 Package          */
    NSP_NORMAL,                 /* 05 FieldUnit        */
    NSP_NEWSCOPE | NSP_LOCAL,   /* 06 Device           */
    NSP_LOCAL,                  /* 07 Event            */
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


ACPI_TABLE_DESC             Gbl_AcpiTables[NUM_ACPI_TABLES];


ACPI_TABLE_SUPPORT          Gbl_AcpiTableData[NUM_ACPI_TABLES] =
{
                 /* Name,   Signature,  Signature size,    How many allowed?,   Supported?  Global typed pointer */

    /* RSDP 0 */ {"RSDP",   RSDP_SIG, sizeof (RSDP_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      NULL},
    /* APIC 1 */ {APIC_SIG, APIC_SIG, sizeof (APIC_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      (void **) &Gbl_APIC},
    /* DSDT 2 */ {DSDT_SIG, DSDT_SIG, sizeof (DSDT_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      (void **) &Gbl_DSDT},
    /* FACP 3 */ {FACP_SIG, FACP_SIG, sizeof (FACP_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      (void **) &Gbl_FACP},
    /* FACS 4 */ {FACS_SIG, FACS_SIG, sizeof (FACS_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      (void **) &Gbl_FACS},
    /* PSDT 5 */ {PSDT_SIG, PSDT_SIG, sizeof (PSDT_SIG)-1, ACPI_TABLE_MULTIPLE, AE_OK,      NULL},
    /* RSDT 6 */ {RSDT_SIG, RSDT_SIG, sizeof (RSDT_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      NULL},
    /* SSDT 7 */ {SSDT_SIG, SSDT_SIG, sizeof (SSDT_SIG)-1, ACPI_TABLE_MULTIPLE, AE_OK,      NULL},
    /* SBST 8 */ {SBST_SIG, SBST_SIG, sizeof (SBST_SIG)-1, ACPI_TABLE_SINGLE,   AE_OK,      (void **) &Gbl_SBST},
    /* BOOT 9 */ {BOOT_SIG, BOOT_SIG, sizeof (BOOT_SIG)-1, ACPI_TABLE_SINGLE,   AE_SUPPORT, NULL}
};

ACPI_INIT_DATA Gbl_AcpiInitData;



/******************************************************************************
 *
 * Strings and procedures used for debug only
 *
 ******************************************************************************/

#ifdef ACPI_DEBUG

char                        *MsgAcpiErrorBreak = "*** Break on ACPI_ERROR ***\n";


/* Names for the mutexes used in the subsystem */

static char                 *Gbl_MutexNames[] =
{
    "MTX_Memory",
    "MTX_Tables",
    "MTX_Dispatcher",
    "MTX_Interpreter",
    "MTX_Execute",
    "MTX_Namespace",
    "MTX_Events",
    "MTX_OpRegions",
    "MTX_DebugCommand",
    "MTX_Debugger"
};


/*****************************************************************************
 * 
 * FUNCTION:    CmGetMutexName
 *
 * PARAMETERS:  None.
 *
 * RETURN:      Status
 * 
 * DESCRIPTION: Translate a mutex ID into a name string (Debug only)
 *
 ****************************************************************************/

char *
CmGetMutexName (
    UINT32                  MutexId)
{

    if (MutexId > MAX_MTX)
    {
        return ("Invalid Mutex ID");
    }

    return (Gbl_MutexNames[MutexId]);
}


/* 
 * Elements of Gbl_NsTypeNames below must match
 * one-to-one with values of ACPI_OBJECT_TYPE
 *
 * The type ACPI_TYPE_Any (Untyped) is used as a "don't care" when searching; when 
 * stored in a table it really means that we have thus far seen no evidence to 
 * indicatewhat type is actually going to be stored for this entry.
 */

static char                 Gbl_BadType[] = "UNDEFINED";
#define TYPE_NAME_LENGTH    9                       /* Maximum length of each string */

static char                 *Gbl_NsTypeNames[] =    /* printable names of ACPI types */
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
     Gbl_BadType, 
     Gbl_BadType, 
     Gbl_BadType, 
     Gbl_BadType,
     Gbl_BadType, 
     Gbl_BadType, 
     Gbl_BadType, 
     Gbl_BadType, 
     Gbl_BadType,
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
 * FUNCTION:    CmGetTypeName
 *
 * PARAMETERS:  None.
 *
 * RETURN:      Status
 * 
 * DESCRIPTION: Translate a Type ID into a name string (Debug only)
 *
 ****************************************************************************/

char *
CmGetTypeName (
    UINT32                  Type)
{

    if (Type > INTERNAL_TYPE_Invalid)
    {
        return (Gbl_BadType);
    }

    return (Gbl_NsTypeNames[Type]);
}

#endif



/*****************************************************************************
 * 
 * FUNCTION:    CmValidObjectType
 *
 * PARAMETERS:  None.
 *
 * RETURN:      TRUE if valid object type
 * 
 * DESCRIPTION: Validate an object type
 *
 ****************************************************************************/

BOOLEAN
CmValidObjectType (
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
 * FUNCTION:    CmFormatException
 *
 * PARAMETERS:  Status              - Acpi status to be formatted
 *
 * RETURN:      Formatted status string
 *
 * DESCRIPTION: Convert an ACPI exception to a string
 *
 ****************************************************************************/

char *
CmFormatException (
    ACPI_STATUS             Status)
{

    if (Status > ACPI_MAX_STATUS)
    {
        return "UNKNOWN_STATUS";
    }

    return (Gbl_ExceptionNames [Status]);
}



/****************************************************************************
 *
 * FUNCTION:    CmInitGlobals
 *
 * PARAMETERS:  none
 *
 * DESCRIPTION: Init library globals.  All globals that require specific
 *              initialization should be initialized here!
 *
 ***************************************************************************/

void 
CmInitGlobals (ACPI_INIT_DATA *InitData)
{
    UINT32                  i;

    FUNCTION_TRACE ("CmInitGlobals");


    if (InitData)
    {
        MEMCPY (&Gbl_AcpiInitData, InitData, sizeof (ACPI_INIT_DATA));
    } 

    else 
    {
        MEMSET (&Gbl_AcpiInitData, 0, sizeof (ACPI_INIT_DATA));
    }

    /* ACPI table structure */

    for (i = 0; i < ACPI_TABLE_MAX; i++)
    {
        Gbl_AcpiTables[i].Prev          = &Gbl_AcpiTables[i];
        Gbl_AcpiTables[i].Next          = &Gbl_AcpiTables[i];
        Gbl_AcpiTables[i].Pointer       = NULL;
        Gbl_AcpiTables[i].Length        = 0;
        Gbl_AcpiTables[i].Allocation    = ACPI_MEM_NOT_ALLOCATED;
        Gbl_AcpiTables[i].Count         = 0;
    }
      

    /* Address Space handler array */

    for (i = 0; i < ACPI_MAX_ADDRESS_SPACE; i++)
    {
        Gbl_AddressSpaces[i].Handler    = NULL;
        Gbl_AddressSpaces[i].Context    = NULL;
    }

    /* Mutex locked flags */

    for (i = 0; i < NUM_MTX; i++)
    {
        Gbl_AcpiMutexInfo[i].Mutex      = NULL;
        Gbl_AcpiMutexInfo[i].Locked     = FALSE;
        Gbl_AcpiMutexInfo[i].UseCount   = 0;
    }

    /* Global notify handlers */

    Gbl_SysNotify.Handler       = NULL;
    Gbl_DrvNotify.Handler       = NULL;

    /* Global "typed" ACPI table pointers */

    Gbl_RSDP                    = NULL;
    Gbl_RSDT                    = NULL;
    Gbl_FACS                    = NULL;
    Gbl_FACP                    = NULL;
    Gbl_APIC                    = NULL;
    Gbl_DSDT                    = NULL;
    Gbl_SBST                    = NULL;


    /* Global Lock support */

    Gbl_GlobalLockAcquired      = FALSE;
    Gbl_GlobalLockThreadCount   = 0;

    /* Miscellaneous variables */

    Gbl_SystemFlags             = 0;
    Gbl_StartupFlags            = 0;
    Gbl_GlobalLockSet           = FALSE;
    Gbl_RsdpOriginalLocation    = 0;
    Gbl_WhenToParseMethods      = METHOD_PARSE_AT_INIT;
    Gbl_CmSingleStep            = FALSE;
    Gbl_DbTerminateThreads      = FALSE;
    Gbl_Shutdown                = FALSE;
    Gbl_NsLookupCount           = 0;
    Gbl_PsFindCount             = 0;
    Gbl_AcpiHardwarePresent     = TRUE;
    Gbl_TbNextTableId           = 1;

    /* Interpreter */

    Gbl_BufSeq                  = 0;
    Gbl_NamedObjectErr          = FALSE;

    /* Parser */

    Gbl_ParsedNamespaceRoot     = NULL;

    /* Hardware oriented */

    Gbl_Gpe0EnableRegisterSave  = NULL;
    Gbl_Gpe1EnableRegisterSave  = NULL;
    Gbl_OriginalMode            = SYS_MODE_UNKNOWN;   /*  original ACPI/legacy mode   */
    Gbl_GpeRegisters            = NULL;
    Gbl_GpeInfo                 = NULL;

    /* Namespace */

    Gbl_RootObject              = &Gbl_RootObjStruct;

    Gbl_RootObject->DataType    = DESC_TYPE_NTE;
    Gbl_RootObject->Type        = ACPI_TYPE_Any;
    Gbl_RootObject->Fill1       = 0;
    Gbl_RootObject->Name        = * (UINT32 *) NS_ROOT;
    Gbl_RootObject->Scope       = NULL;
    Gbl_RootObject->ParentEntry = NULL;
    Gbl_RootObject->NextEntry   = NULL;
    Gbl_RootObject->PrevEntry   = NULL;
    Gbl_RootObject->Object      = NULL;
    
    /* Memory allocation metrics - compiled out in non-debug mode. */

    INITIALIZE_ALLOCATION_METRICS();

    return_VOID;
}   


