
/******************************************************************************
 * 
 * Name: interpreter.h - Interpreter subcomponent prototypes and defines
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


#ifndef __AML_H__
#define __AML_H__


#define AML_END_OF_BLOCK    -1

#include <datatypes.h>
#include <acpiobj.h>            /* For NsType data type only !! */


/*
 * CheckTrash macros
 * define _CHECK_TRASH to enable trash tracing
 */

#ifndef _CHECK_TRASH

/* Usual case: discard calls to these functions */

#define CheckTrash(a)
#define CheckTrashA(a,b,c,d,e,f,g,h)

#else 

extern void CheckTrash(char *Where);
extern void CheckTrashA(char *Where,
                unsigned long *pulP, unsigned long ulC1, unsigned long ulC2,
                int *piP, int iC1, int iC2, void *nNt);
#endif


/* 
 * Macro to test for out-of-range subscript
 * No parens needed around Array in expansion since the actual parameter
 * must be the name of a declared array and cannot be an expression.
 */

#define OUTRANGE(Subscript, Array) \
    (sizeof(Array[0]) == 0 ||\
    (UINT32)(Subscript) >= (sizeof(Array)/sizeof(Array[0])))


#define PUSH_PKG_LENGTH         1
#define DO_NOT_PUSH_PKG_LENGTH  0




/*
 * iefield - ACPI AML (p-code) execution - field manipulation
 */


ACPI_STATUS
AmlSetNamedFieldValue (
    NsHandle            NamedField, 
    UINT32              Value);

ACPI_STATUS
AmlGetNamedFieldValue (
    NsHandle            NamedField, 
    UINT32              *Value);


/*
 * ieopexec - ACPI AML (p-code) execution - specific opcodes
 */

ACPI_STATUS
AmlExecCreateField (
    UINT16              op);

ACPI_STATUS
AmlExecFatal (
    void);

ACPI_STATUS
AmlExecIndex (
    void);

ACPI_STATUS
AmlExecMatch (
    void);


/*
 * ievalue - ACPI AML (p-code) execution - get value functions
 */

INT32
AmlGetRvalue (
    OBJECT_DESCRIPTOR   **StackPtr);

BOOLEAN
AmlIsMethodValue (
    OBJECT_DESCRIPTOR   *pOD);


/*
 * ieprep - ACPI AML (p-code) execution - prep utilities
 */

INT32
AmlGetMethodDepth (
    void);

NsType
AmlGetMethodType (
    INT32               Index);

ACPI_STATUS
AmlGetMethodValue (
    INT32               Index, 
    OBJECT_DESCRIPTOR   *ObjDesc);

ACPI_STATUS
AmlSetMethodValue (
    INT32               Index, 
    OBJECT_DESCRIPTOR   *ObjDesc, 
    OBJECT_DESCRIPTOR   *ObjDesc2);

ACPI_STATUS
AmlPrepDefFieldValue (
    NsHandle            Region, 
    UINT8               FldFlg, 
    INT32               FldPos, 
    INT32               FldLen);

ACPI_STATUS
AmlPrepBankFieldValue (
    NsHandle            Region, 
    NsHandle            BankReg, 
    UINT32              BankVal,
    UINT8               FldFlg, 
    INT32               FldPos, 
    INT32               FldLen);

ACPI_STATUS
AmlPrepIndexFieldValue(
    NsHandle            IndexReg, 
    NsHandle            DataReg,
    UINT8               FldFlg, 
    INT32               FldPos, 
    INT32               FldLen);

ACPI_STATUS
AmlPrepStack (
    char                *Types);


/*
 * iesystem - Interface to OS services
 */

UINT16 
OsThreadId (
    void);

ACPI_STATUS
OsDoNotifyOp (
    OBJECT_DESCRIPTOR   *val, 
    OBJECT_DESCRIPTOR   *obj);

void
OsDoSuspend(
    UINT32              Time);

ACPI_STATUS
OsAcquireOpRqst(
    OBJECT_DESCRIPTOR   *Time, 
    OBJECT_DESCRIPTOR   *sOb);

ACPI_STATUS
OsReleaseOpRqst(
    OBJECT_DESCRIPTOR   *sOb);

ACPI_STATUS
OsSignalOpRqst(
    OBJECT_DESCRIPTOR   *sOb);

ACPI_STATUS
OsWaitOpRqst(
    OBJECT_DESCRIPTOR   *Time, 
    OBJECT_DESCRIPTOR   *sOb);

ACPI_STATUS
OsResetOpRqst(
    OBJECT_DESCRIPTOR   *sOb);

ACPI_STATUS
OsGetGlobalLock(
    void);

void
OsReleaseGlobalLock(
    void);


/*
 * iexecute - ACPI AML (p-code) execution
 */

ACPI_STATUS
AmlExecuteMethod (
    INT32               Offset, 
    INT32               Len, 
    OBJECT_DESCRIPTOR   **Params);

ACPI_STATUS
AmlExecStore (
    OBJECT_DESCRIPTOR   *op1, 
    OBJECT_DESCRIPTOR   *res);


/*
 * iemonadic - ACPI AML (p-code) execution, monadic operators
 */

ACPI_STATUS
AmlExecMonadic1 (
    UINT16              op);

ACPI_STATUS
AmlExecMonadic2R (
    UINT16              op);

ACPI_STATUS
AmlExecMonadic2 (
    UINT16              op);


/*
 * iedyadic - ACPI AML (p-code) execution, dyadic operators
 */

ACPI_STATUS
AmlExecDyadic1 (
    UINT16              op);

ACPI_STATUS
AmlExecDyadic2R (
    UINT16              op);

ACPI_STATUS
AmlExecDyadic2S (
    UINT16              op);

ACPI_STATUS
AmlExecDyadic2 (
    UINT16              op);


/*
 * isatoms - interpreter/scanner atom load/execute
 */

ACPI_STATUS 
AmlDoSuperName (
    OpMode              LoadExecMode, 
    NsType              Define);

ACPI_STATUS
AmlDoLiteral (
    OpMode              LoadExecMode);

/*
 * iscode - Scanner AML code manipulation routines
 */

INT32
AmlAvail (
    size_t              n);

INT32
AmlPeek (
    void);

INT32
AmlGetPCodeByte (
    ptrdiff_t           Offset);

INT32
AmlPeekOp (
    void);

UINT8 *
AmlConsumeBytes (
    size_t              Bytes);

size_t
AmlConsumeStreamBytes (
    size_t              BytesToGet, 
    UINT8               *AmlBuffer);

void
AmlConsumePackage (
    OpMode              LoadExecMode);

INT32
AmlIsInPCodeBlock (
    UINT8               *Where);

void
AmlSetPCodeInput (
    UINT8               *Base, 
    INT32               Len);

ACPI_STATUS
AmlSetMethod (
    void                *Object);

ACPI_STATUS
AmlPrepExec (
    ptrdiff_t           Offset, 
    INT32               Len);

ACPI_OBJECT_HANDLE
AmlGetPCodeHandle (
    void);

void
AmlGetCurrentLocation (
    meth                *Method);

void
AmlSetCurrentLocation (
    meth                *Method);


/*
 * isdump - Scanner debug output routines
 */

void
AmlDumpBuffer (
    size_t              Length);


ACPI_STATUS
AmlDumpStackEntry (
    OBJECT_DESCRIPTOR   *EntryDesc);

void
AmlDumpStack (
    OpMode              LoadExecMode, 
    char                *pcIdent, 
    INT32               NumLevels, 
    char                *pcNote);

void
AmlDumpObjectDescriptor (
	OBJECT_DESCRIPTOR   *Obj);


/*
 * isdoexp - interpreter/scanner expression load/execute
 */

ACPI_STATUS
AmlDoDataTerm (
    OpMode              LoadExecMode);

ACPI_STATUS
AmlDoCode (
    OpMode              iLE);

ACPI_STATUS
AmlDoDefinitionBlock (
    char                *name, 
    UINT8               *addr, 
    INT32               len);

ACPI_STATUS
AmlDoFieldElement (
    NsType              DataType, 
    OpMode              LoadExecMode);


/*
 * isdopkg - interpreter/scanner AML package load/execute
 */

ACPI_STATUS
AmlDoPkg (
    NsType              Type, 
    OpMode              iLE);


/*
 * isdoname - interpreter/scanner named object load/execute
 */

ACPI_STATUS
AmlDoNameSpaceModifier (
    OpMode              LoadExecMode);

ACPI_STATUS
AmlDoNamedObject (
    OpMode              LoadExecMode);


/*
 * isidata - interpreter/scanner interpreted data load/execute
 */

ACPI_STATUS 
AmlDoFieldFlag (
    OpMode              LoadExecMode);

ACPI_STATUS
AmlDoMatchOp (
    OpMode              iLE);

void
AmlDoOpByte (
    INT32               nl, 
    UINT16              op, 
    OpMode              iLE);


/*
 * isnames - interpreter/scanner name load/execute
 */

void
AmlAllocateNameString (
    INT32               PrefixCount,
    INT32               NSeg);

INT32
AmlGoodChar (
    INT32               c);

INT32 
AmlDecodePackageLength (
    INT32               LastPkgLen);

ACPI_STATUS
AmlDoName (
    NsType              DataType, 
    OpMode              LoadExecMode);


/*
 * isdoop - interpreter/scanner expression(opcode) load/execute
 */

ACPI_STATUS
AmlDoOpCode (
    OpMode              iLE);

ACPI_STATUS
AmlDoRefOpCode (
    OpMode              LoadExecMode);


/*
 * isdoopt1 - interpreter/scanner expression(opcode) load/execute
 */

ACPI_STATUS
AmlDoType1OpCode (
    OpMode              LoadExecMode);


/*
 * isdoopt2 - interpreter/scanner expression(opcode) load/execute
 */

ACPI_STATUS 
AmlDoType2OpCode (
    OpMode              LoadExecMode);


/*
 * isrdata - interpreter/scanner raw data load/execute
 */

void 
AmlShowHexValue (
    INT32               ByteCount, 
    UINT8               *AmlPtr, 
    OpMode              LoadExecMode, 
    INT32               LeadSpace);

ACPI_STATUS
AmlDoPkgLength (
    INT32               DoPush, 
    OpMode              LoadExecMode);

ACPI_STATUS
AmlDoByteConst (
    OpMode              LoadExecMode, 
    INT32               LeadSpace);

ACPI_STATUS
AmlDoWordConst (
    OpMode              LoadExecMode, 
    INT32               LeadSpace);

ACPI_STATUS
AmlDoDWordConst (
    OpMode              LoadExecMode, 
    INT32               LeadSpace);


/*
 * isstack - Scanner stack routines
 */

void
AmlClearPkgStack (
    void);

ACPI_STATUS
AmlPushLength (
    INT32               len, 
    OpMode              LoadExecMode);

ACPI_STATUS
AmlPushExecLength (
    INT32               len);

ACPI_STATUS
AmlPushExec (
    UINT8               *Code, 
    INT32               Len);

ACPI_STATUS
AmlPopLength (
    INT32               NoErrUnder, 
    OpMode              LoadExecMode);

ACPI_STATUS
AmlPopExecLength (
    void);

ACPI_STATUS
AmlPopExec (
    void);

ACPI_STATUS
AmlPushIfExec (
    OpMode              LoadExecMode);

INT32
AmlPackageNested (
     void);


/*
 * isutils - interpreter/scanner utilities
 */

BOOLEAN
AmlAcquireGlobalLock (
    UINT16              Rule);

ACPI_STATUS
AmlReleaseGlobalLock (
    BOOLEAN             Locked);

void
AmlAppendBlockOwner (
    void                *Owner);

void
AmlAppendOperandDiag(
    char                *Name, 
    INT32               Line, 
    UINT16              OpCode, 
    INT32               NOperands);

UINT32 
AmlBufSeq (
    void);

INT32
DigitsNeeded (
    INT32               val, 
    INT32               base);

void
LineSet (
    INT32               n, 
    OpMode              LoadExecMode);

void
Indent (
    INT32               n);


/* More PLUMBER stuff (in isutils) TBD: what is this? */

void
AmlMarkPackage (
    OBJECT_DESCRIPTOR   *pOD);

void
vAmlMarkObject (
    OBJECT_DESCRIPTOR   *pOD);

void
MarkObjectStack (
    INT32               *piCount);


void
MarkMethodValues (
    INT32               *Count);



#endif
