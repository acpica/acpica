
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
#include <namespace.h>
#include <interpreter.h>


#define _THIS_MODULE        "cmglobal.c"
#define _COMPONENT          MISCELLANEOUS



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
UINT32                      Gbl_NestingLevel = 0;


/* System flags */

UINT32                      Gbl_SystemFlags = 0;
UINT32                      Gbl_StartupFlags = 0;

/* 
 * Human-readable decode of exception codes, mostly for debugging
 * These need to match the corresponding defines
 * Note that AE_PENDING is not an error, but indicates
 * that other alternatives should be checked.
 */
char                        *Gbl_ExceptionNames[] = 
{ 
    "AE_OK",
    "AE_PENDING",
    "AE_AML_ERROR",
    "AE_RETURN_VALUE",
    "AE_ERROR",
    "AE_NO_ACPI_TABLES",
    "AE_NO_NAMESPACE",
    "AE_NO_MEMORY",
    "AE_BAD_SIGNATURE",
    "AE_BAD_HEADER",
    "AE_BAD_CHECKSUM",
    "AE_BAD_PARAMETER",
    "AE_BAD_CHARACTER",
    "AE_BAD_PATHNAME",
    "AE_BAD_DATA",
    "AE_NOT_FOUND",
    "AE_NOT_EXIST",
    "AE_EXIST",
    "AE_TYPE",
    "AE_NULL_ENTRY",
    "AE_BUFFER_OVERFLOW",
    "AE_STACK_OVERFLOW",
    "AE_STACK_UNDERFLOW",
    "AE_NOT_IMPLEMENTED",
    "AE_VERSION_MISMATCH",
    "AE_SUPPORT",
    "AE_SHARE",
    "AE_LIMIT",
    "AE_TIME",
    "AE_UNKNOWN_STATUS"
};


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
    {"_GPE",    TYPE_DefAny},
    {"_PR_",    TYPE_DefAny},
    {"_SB_",    TYPE_DefAny},
    {"_SI_",    TYPE_DefAny},
    {"_TZ_",    TYPE_DefAny},
    {"_REV",    TYPE_Number, "2"},
    {"_OS_",    TYPE_String, "Intel AML interpreter"},
    {"_GL_",    TYPE_Mutex, "0"},

    /* Table terminator */

    {NULL,      TYPE_Any}
};


/* 
 * Elements of NsProperties are bit significant
 * and should be one-to-one with values of NsType in acpinmsp.h
 */

INT32                       Gbl_NsProperties[] =    /* properties of types */
{
    0,                      /* Any              */
    0,                      /* Number           */
    0,                      /* String           */
    0,                      /* Buffer           */
    LOCAL,                  /* Package          */
    0,                      /* FieldUnit        */
    NEWSCOPE | LOCAL,       /* Device           */
    LOCAL,                  /* Event            */
    NEWSCOPE | LOCAL,       /* Method           */
    LOCAL,                  /* Mutex            */
    LOCAL,                  /* Region           */
    NEWSCOPE | LOCAL,       /* Power            */
    NEWSCOPE | LOCAL,       /* Processor        */
    NEWSCOPE | LOCAL,       /* Thermal          */
    0,                      /* Alias            */
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0,
    0,                      /* DefField         */
    0,                      /* BankField        */
    0,                      /* IndexField       */
    0,                      /* DefFieldDefn     */
    0,                      /* BankFieldDefn    */
    0,                      /* IndexFieldDefn   */
    0,                      /* If               */
    0,                      /* Else             */
    0,                      /* While            */
    NEWSCOPE,               /* Scope            */
    LOCAL,                  /* DefAny           */
    0,                      /* Lvalue           */
    0                       /* Invalid          */
};

char                        Gbl_BadType[] = "ERROR: Unused type value";


/* 
 * Elements of NsTypeNames should be
 * one-to-one with values of NsType in acpinmsp.h

 */

/* 
 * The type Any is used as a "don't care" when searching; when stored in a
 * table it really means that we have thus far seen no evidence to indicate
 * what type is actually going to be stored for this entry.
 */

char                        *Gbl_NsTypeNames[] =  /* printable names of types */
{
    "Unknown",
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
    "Alias",
     Gbl_BadType, 
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
    "BankField",
    "IndexField",
    "DefFieldDefn",
    "BankFieldDefn",
    "IndexFieldDefn",
    "If",
    "Else",
    "While",
    "Scope",
    "DefAny",
    "Lvalue",
    "Invalid"
};


/******************************************************************************
 *
 * Table globals
 *
 ******************************************************************************/


ACPI_TABLE_DESC             Gbl_AcpiTables[NUM_ACPI_TABLES];


UINT8                       Gbl_AcpiTableFlags[NUM_ACPI_TABLES] =
{
    ACPI_TABLE_SINGLE,      /* RSDP */
    ACPI_TABLE_SINGLE,      /* APIC */
    ACPI_TABLE_SINGLE,      /* DSDT */
    ACPI_TABLE_SINGLE,      /* FACP */
    ACPI_TABLE_SINGLE,      /* FACS */
    ACPI_TABLE_MULTIPLE,    /* PSDT */
    ACPI_TABLE_SINGLE,      /* RSDT */
    ACPI_TABLE_MULTIPLE,    /* SSDT */
    ACPI_TABLE_SINGLE       /* SBST */
};

char                        *Gbl_AcpiTableNames[] = 
{
    "RSDP",
    APIC_SIG,
    DSDT_SIG,
    FACP_SIG,
    FACS_SIG,
    PSDT_SIG,
    RSDT_SIG,
    SSDT_SIG,
    SBST_SIG
};



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
CmInitGlobals (void)
{
    UINT32                  i;

    FUNCTION_TRACE ("CmInitGlobals");

    
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


    /* Global "typed" ACPI table pointers */

    Gbl_RSDP                    = NULL;
    Gbl_RSDT                    = NULL;
    Gbl_FACS                    = NULL;
    Gbl_FACP                    = NULL;
    Gbl_APIC                    = NULL;
    Gbl_DSDT                    = NULL;
    Gbl_SBST                    = NULL;


    /* Miscellaneous variables */
    
    Gbl_SystemFlags             = 0;
    Gbl_StartupFlags            = 0;
    Gbl_GlobalLockSet           = FALSE;
    Gbl_RsdpOriginalLocation    = 0;
    
    /* Stack pointers */

    Gbl_MethodStackTop          = -1;
    Gbl_PkgStackLevel           = 0;
    Gbl_ObjStackTop             = 0;

    /* Interpreter */

    Gbl_BufSeq                  = 0;
    Gbl_NamedObjectErr          = FALSE;

    /* Hardware oriented */

    Gbl_Gpe0EnableRegisterSave  = NULL;
    Gbl_Gpe1EnableRegisterSave  = NULL;
    Gbl_OriginalMode            = SYS_MODE_UNKNOWN;   /*  original ACPI/legacy mode   */
    Gbl_GpeRegisters            = NULL;
    Gbl_GpeInfo                 = NULL;

    /* Namespace */

    Gbl_RootObject              = &Gbl_RootObjStruct;

    Gbl_RootObject->Name        = NS_ROOT;
    Gbl_RootObject->Scope       = NULL;
    Gbl_RootObject->ParentScope = NULL;
    Gbl_RootObject->ParentEntry = NULL;
    Gbl_RootObject->NextEntry   = NULL;
    Gbl_RootObject->PrevEntry   = NULL;
    Gbl_RootObject->Type        = TYPE_Any;
    Gbl_RootObject->Object      = NULL;

    return_VOID;
}   


