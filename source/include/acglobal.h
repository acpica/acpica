
/******************************************************************************
 * 
 * Name: globals.h - Declarations for global variables
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
 * license (without the right to sublicense), under only those claims of Intel
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

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "config.h"
#include "acpitables.h"

/*
 * Ensure that the globals are actually defined only once
 */
#ifdef DEFINE_ACPI_GLOBALS
#define ACPI_EXTERN
#else
#define ACPI_EXTERN extern
#endif



/*****************************************************************************
 * 
 * ACPI Table globals 
 *
 ****************************************************************************/

ACPI_EXTERN ROOT_SYSTEM_DESCRIPTOR_POINTER      * RSDP;
ACPI_EXTERN ROOT_SYSTEM_DESCRIPTION_TABLE       * RSDT;
ACPI_EXTERN FIRMWARE_ACPI_CONTROL_STRUCTURE     * FACS;
ACPI_EXTERN FIXED_ACPI_DESCRIPTION_TABLE        * FACP;
ACPI_EXTERN APIC_TABLE                          * MAPIC;
ACPI_EXTERN ACPI_TABLE_HEADER                   * DSDT;
ACPI_EXTERN ACPI_TABLE_HEADER                   * PSDT;

/* 
 * TBD - There may be multiple SSDTs so a single pointer is not sufficient 
 * to tag them all.  An array or linked list of SSDT pointers will be
 * necessary. 
 */
ACPI_EXTERN ACPI_TABLE_HEADER                   * SSDT;
ACPI_EXTERN ACPI_TABLE_HEADER                   * SBDT;


extern      ACPI_TABLE_INFO     AcpiTables[NUM_ACPI_TABLES];

/*****************************************************************************
 * 
 * Miscellaneous globals 
 *
 ****************************************************************************/

ACPI_EXTERN BOOLEAN             GlobalLockSet;
extern      UINT32              SystemFlags;
extern      UINT32              StartupFlags;

ACPI_EXTERN INT32               RestoreAcpiChipset;
ACPI_EXTERN UINT16              Pm1EnableRegisterSave;
ACPI_EXTERN UINT8               *Gpe0EnableRegisterSave;
ACPI_EXTERN UINT8               *Gpe1EnableRegisterSave;
ACPI_EXTERN INT32               OriginalMode;
ACPI_EXTERN INT32               EdgeLevelSave;
ACPI_EXTERN INT32               IrqEnableSave;
extern char                     *ExceptionNames[];

ACPI_EXTERN UINT32              RsdpOriginalLocation; 

/* Procedure nesting level for debug output */

extern UINT32                   NestingLevel;

/* Runtime configuration of debug print levels */

extern UINT32                   DebugLevel;
extern UINT32                   DebugLayer;



/*****************************************************************************
 * 
 * Namespace globals 
 *
 ****************************************************************************/

#define NUM_NS_TYPES            37
#define NUM_PREDEFINED_NAMES    9

extern SCOPE_STACK              ScopeStack[];
extern SCOPE_STACK              *CurrentScope;
extern char                     BadType[];
extern char                     *NsTypeNames[NUM_NS_TYPES];
extern INT32                    NsProperties[NUM_NS_TYPES];
extern PREDEFINED_NAMES         PreDefinedNames [NUM_PREDEFINED_NAMES];


ACPI_EXTERN INT32               NamedObjectErr;     /* indicate if inc_error should be called */
ACPI_EXTERN NAME_TABLE_ENTRY    RootObjStruct;
ACPI_EXTERN NAME_TABLE_ENTRY    *RootObject;



/*****************************************************************************
 * 
 * Interpreter globals 
 *
 ****************************************************************************/

/* Package stack */

extern INT32                    PkgStackLevel;
extern INT32                    PkgStack_Len[AML_PKG_MAX_NEST];
extern UINT8                    *PkgStack_Code[AML_PKG_MAX_NEST];

/* Object stack */

extern void                     *ObjStack[AML_EXPR_MAX_NEST];
extern INT32                    ObjStackTop;

/* Method stack - contains arguments and locals */
/* TBD: Split into parallel arg stack and local stack */

extern ACPI_OBJECT_INTERNAL     *MethodStack[AML_METHOD_MAX_NEST][MTH_ENTRY_SIZE];
extern INT32                    MethodStackTop;

/* Base of AML block, and pointer to current location in it */

ACPI_EXTERN UINT8               *PCodeBase;
ACPI_EXTERN UINT8               *PCode;

/* 
 * Length of AML block, and remaining length of current package.
 * PCodeBlockLen is used in IsInPCodeBlock()
 */
ACPI_EXTERN INT32               PCodeBlockLen;
ACPI_EXTERN INT32               PCodeLen;

ACPI_EXTERN UINT32              BufSeq;             /* Counts allocated Buffer descriptors */
ACPI_EXTERN INT32               SkipField;
ACPI_EXTERN INT32               LastPkgLen;
ACPI_EXTERN UINT8               LastFieldFlag;
extern char                     *FENames[];

/* 
 * Handle to the last method found
 * used during pass1 of load 
 */
ACPI_EXTERN ACPI_HANDLE         LastMethod;




/*****************************************************************************
 * 
 * Event globals 
 *
 ****************************************************************************/

extern UINT32                   EventCount[NUM_FIXED_EVENTS];   
extern FIXED_EVENT_HANDLER      FixedEventHandlers[NUM_FIXED_EVENTS];

ACPI_EXTERN ACPI_HANDLE         GpeObjHandle;
ACPI_EXTERN UINT32              SciHandle;
ACPI_EXTERN UINT32              GpeRegisterCount;
ACPI_EXTERN GPE_REGISTERS       *GpeRegisters;
ACPI_EXTERN GPE_LEVEL_INFO      *GpeInfo;



#endif /* __GLOBALS_H__ */
