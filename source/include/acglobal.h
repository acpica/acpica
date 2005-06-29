
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
 * 2.1. Intel grants, free of charge, to any person ("Licensee") obtaining a 
 * copy of the source code appearing in this file ("Covered Code") a license 
 * under Intel's copyrights in the base code distributed originally by Intel 
 * ("Original Intel Code") to copy, make derivatives, distribute, use and 
 * display any portion of the Covered Code in any form; and
 *
 * 2.2. Intel grants Licensee a non-exclusive and non-transferable patent 
 * license (without the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell, 
 * offer to sell, and import the Covered Code and derivative works thereof 
 * solely to the minimum extent necessary to exercise the above copyright 
 * license, and in no event shall the patent license extend to any additions to
 * or modifications of the Original Intel Code.  No other license or right is 
 * granted directly or by implication, estoppel or otherwise;
 *
 * the above copyright and patent license is granted only if the following 
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of source code of any substantial portion of the Covered 
 * Code or modification must include the above Copyright Notice, the above 
 * License, this list of Conditions, and the following Disclaimer and Export 
 * Compliance provision.  In addition, Licensee must cause all Covered Code to 
 * which Licensee contributes to contain a file documenting the changes 
 * Licensee made to create that Covered Code and the date of any change.  
 * Licensee must include in that file the documentation of any changes made by
 * any predecessor Licensee.  Licensee must include a prominent statement that
 * the modification is derived, directly or indirectly, from Original Intel 
 * Code.
 *
 * 3.2. Redistribution in binary form of any substantial portion of the Covered 
 * Code or modification must reproduce the above Copyright Notice, and the 
 * following Disclaimer and Export Compliance provision in the documentation 
 * and/or other materials provided with the distribution.
 *
 * 3.3. Intel retains all right, title, and interest in and to the Original 
 * Intel Code.
 *
 * 3.4. Neither the name Intel nor any other trademark owned or controlled by 
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
 * event Licensee exports any such software from the United States or re-
 * exports any such software from a foreign destination, Licensee shall ensure
 * that the distribution and export/re-export of the software is in compliance 
 * with all laws, regulations, orders, or other restrictions of the U.S. Export 
 * Administration Regulations. Licensee agrees that neither it nor any of its 
 * subsidiaries will export/re-export any technical data, process, software, or 
 * service, directly or indirectly, to any country for which the United States 
 * government or any agency thereof requires an export license, other 
 * governmental approval, or letter of assurance, without first obtaining such
 * license, approval or letter.
 *
 *****************************************************************************/

#ifndef __GLOBALS_H__
#define __GLOBALS_H__



#ifdef DEFINE_ACPI_GLOBALS
#define ACPI_EXTERN
#ifndef __GNUC__
#pragma message ("ACPI_EXTERN variables defined in this module.")
#endif

#else
#define ACPI_EXTERN extern
#endif


/* Acpi table pointers */

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


/* Misc Globals */


ACPI_EXTERN BOOLEAN     GlobalLockSet;
ACPI_EXTERN INT32       Capabilities;
ACPI_EXTERN INT32       NameStringSize;
ACPI_EXTERN char        *NameString;    /* Runtime AML error message communication */

ACPI_EXTERN INT32       RestoreAcpiChipset;
ACPI_EXTERN UINT16      Pm1EnableRegisterSave;
ACPI_EXTERN UINT8       *Gpe0EnableRegisterSave;
ACPI_EXTERN UINT8       *Gpe1EnableRegisterSave;
ACPI_EXTERN INT32       OriginalMode;
ACPI_EXTERN INT32       EdgeLevelSave;
ACPI_EXTERN INT32       IrqEnableSave;
ACPI_EXTERN INT32       OriginalMode;
extern char             *ExceptionNames[];

/* File I/O globals */

ACPI_EXTERN char        *DsdtFile;
ACPI_EXTERN char        *OutputFile;
ACPI_EXTERN char        *InputFile;

ACPI_EXTERN INT32       AcpiLibInitStatus;
ACPI_EXTERN INT32       AcpiHook;           /* strong link that lives in acpilibv.c */

/* 
 * Namespace globals 
 */

ACPI_EXTERN INT32       NamedObjectErr;     /* Use to indicate if inc_error should be called */
ACPI_EXTERN nte         RootObjStruct;
ACPI_EXTERN nte         *RootObject;

/* Base of AML block, and pointer to current location in it */

ACPI_EXTERN UINT8       *PCodeBase;
ACPI_EXTERN UINT8       *PCode;

/* 
 * Length of AML block, and remaining length of current package.
 * PCodeBlockLen is used in IsInPCodeBlock()
 */
ACPI_EXTERN INT32       PCodeBlockLen;
ACPI_EXTERN INT32       PCodeLen;

/* 
 * Interpreter globals 
 */

ACPI_EXTERN UINT32      BufSeq;         /* Counts allocated Buffer descriptors */
ACPI_EXTERN INT32       SkipField;
ACPI_EXTERN INT32       LastPkgLen;
ACPI_EXTERN UINT8       LastFieldFlag;

/* 
 * global handle to the last method found
 * used during pass1 of load 
 */

ACPI_EXTERN NsHandle    LastMethod;


/* Procedure nesting level for debug output */

ACPI_EXTERN UINT32      NestingLevel;



/* These must not be ACPI_EXTERN since they need explicit initialization */

/* Runtime configuration of debug print levels */

extern UINT32           DebugLevel;
extern UINT32           DebugLayer;


/* Interpreter globals */

extern char             *FENames[];


/* Namespace globals */

#define NUM_NS_TYPES            37
#define NUM_PREDEFINED_NAMES    9

extern SCOPE_STACK              ScopeStack[];
extern SCOPE_STACK              *CurrentScope;
extern char                     BadType[];
extern char                     *NsTypeNames[NUM_NS_TYPES];
extern INT32                    NsProperties[NUM_NS_TYPES];
extern PREDEFINED_NAMES         PreDefinedNames [NUM_PREDEFINED_NAMES];


/* Interpreter globals */

extern INT32                    PkgStackLevel;
extern INT32                    PkgStack_Len[AML_PKG_MAX_NEST];
extern UINT8                    *PkgStack_Code[AML_PKG_MAX_NEST];
extern void                     *ObjStack[AML_EXPR_MAX_NEST];
extern INT32                    ObjStackTop;

/* 
 * Method Stack, containing locals and args
 * per level, 0-7 are Local# and 8-14 are Arg#
 */

#define LCLBASE                 0
#define NUMLCL                  8
#define ARGBASE                 (LCLBASE+NUMLCL)
#define NUMARG                  7


extern OBJECT_DESCRIPTOR        *MethodStack[AML_METHOD_MAX_NEST][ARGBASE+NUMARG];
extern INT32                    MethodStackTop;




#endif /* __GLOBALS_H__ */