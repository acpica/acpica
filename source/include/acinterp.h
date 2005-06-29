
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


#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__


#define AML_END_OF_BLOCK    -1

#include <datatypes.h>
#include <acpiobj.h>


/*
 * CheckTrash macros
 * define _CHECK_TRASH to enable trash tracing
 */

/* TBD: obsolete?? */

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
    ACPI_HANDLE             NamedField, 
    UINT32                  Value);

ACPI_STATUS
AmlGetNamedFieldValue (
    ACPI_HANDLE             NamedField, 
    UINT32                  *Value);


/*
 * ieopexec - ACPI AML (p-code) execution - specific opcodes
 */

ACPI_STATUS
AmlExecCreateField (
    UINT16                  Opcode);

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
    ACPI_OBJECT             **StackPtr);

BOOLEAN
AmlIsMethodValue (
    ACPI_OBJECT             *ObjDesc);


/*
 * ieprep - ACPI AML (p-code) execution - prep utilities
 */

ACPI_STATUS
AmlPrepDefFieldValue (
    ACPI_HANDLE             Region, 
    UINT8                   FldFlg, 
    INT32                   FldPos, 
    INT32                   FldLen);

ACPI_STATUS
AmlPrepBankFieldValue (
    ACPI_HANDLE             Region, 
    ACPI_HANDLE             BankReg, 
    UINT32                  BankVal,
    UINT8                   FldFlg, 
    INT32                   FldPos, 
    INT32                   FldLen);

ACPI_STATUS
AmlPrepIndexFieldValue(
    ACPI_HANDLE             IndexReg, 
    ACPI_HANDLE             DataReg,
    UINT8                   FldFlg, 
    INT32                   FldPos, 
    INT32                   FldLen);


/*
 * iemstack - method stack utilities
 */

INT32
AmlMthStackLevel (
    void);

ACPI_OBJECT_TYPE
AmlMthStackGetType (
    INT32                   Index);

ACPI_STATUS
AmlMthStackGetValue (
    INT32                   Index, 
    ACPI_OBJECT             *ObjDesc);

ACPI_STATUS
AmlMthStackSetValue (
    INT32                   Index, 
    ACPI_OBJECT             *ObjDesc, 
    ACPI_OBJECT             *ObjDesc2);


/*
 * ieostack - object stack utilities
 */

UINT32
AmlObjStackLevel (
     void);
void
AmlClearObjStack (
    void);

ACPI_STATUS
AmlPrepObjStack (
    char                    *Types);

ACPI_STATUS
AmlObjPushIfExec (
    OPERATING_MODE          LoadExecMode);



/*
 * iepstack - package stack utilities
 */

UINT32
AmlPkgStackLevel (
     void);

void
AmlClearPkgStack (
    void);

ACPI_STATUS
AmlPkgPushLength (
    INT32                   Length, 
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlPkgPushExecLength (
    INT32                   Length);

ACPI_STATUS
AmlPkgPushExec (
    UINT8                   *Code, 
    INT32                   Len);

ACPI_STATUS
AmlPkgPopLength (
    INT32                   NoErrUnder, 
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlPkgPopExecLength (
    void);

ACPI_STATUS
AmlPkgPopExec (
    void);


/*
 * iesystem - Interface to OS services
 */

UINT16 
OsThreadId (
    void);

ACPI_STATUS
OsDoNotifyOp (
    ACPI_OBJECT             *Value, 
    ACPI_OBJECT             *ObjDesc);

void
OsDoSuspend(
    UINT32                  Time);

ACPI_STATUS
OsAcquireOpRqst(
    ACPI_OBJECT             *Time, 
    ACPI_OBJECT             *ObjDesc);

ACPI_STATUS
OsReleaseOpRqst(
    ACPI_OBJECT             *ObjDesc);

ACPI_STATUS
OsSignalOpRqst(
    ACPI_OBJECT             *ObjDesc);

ACPI_STATUS
OsWaitOpRqst(
    ACPI_OBJECT             *Time, 
    ACPI_OBJECT             *ObjDesc);

ACPI_STATUS
OsResetOpRqst(
    ACPI_OBJECT             *ObjDesc);

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
    INT32                   Offset, 
    INT32                   Len, 
    ACPI_OBJECT             **Params);

ACPI_STATUS
AmlExecStore (
    ACPI_OBJECT             *op1, 
    ACPI_OBJECT             *res);


/*
 * iemonadic - ACPI AML (p-code) execution, monadic operators
 */

ACPI_STATUS
AmlExecMonadic1 (
    UINT16                  Opcode);

ACPI_STATUS
AmlExecMonadic2R (
    UINT16                  Opcode);

ACPI_STATUS
AmlExecMonadic2 (
    UINT16                  Opcode);


/*
 * iedyadic - ACPI AML (p-code) execution, dyadic operators
 */

ACPI_STATUS
AmlExecDyadic1 (
    UINT16                  Opcode);

ACPI_STATUS
AmlExecDyadic2R (
    UINT16                  Opcode);
        
ACPI_STATUS
AmlExecDyadic2S (
    UINT16                  Opcode);

ACPI_STATUS
AmlExecDyadic2 (
    UINT16                  Opcode);


/*
 * isatoms - interpreter/scanner atom load/execute
 */

ACPI_STATUS 
AmlDoSuperName (
    OPERATING_MODE          LoadExecMode, 
    ACPI_OBJECT_TYPE        Define);

ACPI_STATUS
AmlDoLiteral (
    OPERATING_MODE          LoadExecMode);

/*
 * iscode - Scanner AML code manipulation routines
 */

INT32
AmlAvail (
    ACPI_SIZE               n);

INT32
AmlPeek (
    void);

INT32
AmlGetPCodeByte (
    ACPI_PTRDIFF            Offset);

INT32
AmlPeekOp (
    void);

UINT8 *
AmlConsumeBytes (
    ACPI_SIZE               Bytes);

ACPI_SIZE
AmlConsumeStreamBytes (
    ACPI_SIZE               BytesToGet, 
    UINT8                   *AmlBuffer);

void
AmlConsumePackage (
    OPERATING_MODE          LoadExecMode);

INT32
AmlIsInPCodeBlock (
    UINT8                   *Where);

void
AmlSetPCodeInput (
    UINT8                   *Base, 
    INT32                   Len);

ACPI_STATUS
AmlSetMethod (
    void                    *Object);

ACPI_STATUS
AmlPrepExec (
    ACPI_PTRDIFF            Offset, 
    INT32                   Len);

ACPI_OBJECT_HANDLE
AmlGetPCodeHandle (
    void);

void
AmlGetCurrentLocation (
    METHOD_INFO             *Method);

void
AmlSetCurrentLocation (
    METHOD_INFO             *Method);


/*
 * isdump - Scanner debug output routines
 */

void
AmlDumpBuffer (
    ACPI_SIZE               Length);


ACPI_STATUS
AmlDumpObjStackEntry (
    ACPI_OBJECT             *EntryDesc);

void
AmlDumpObjStack (
    OPERATING_MODE          LoadExecMode, 
    char                    *pcIdent, 
    INT32                   NumLevels, 
    char                    *pcNote);

void
AmlDumpObjectDescriptor (
	ACPI_OBJECT             *ObjDesc);


/*
 * isdoexp - interpreter/scanner expression load/execute
 */

ACPI_STATUS
AmlDoDataTerm (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoCode (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoDefinitionBlock (
    char                    *name, 
    UINT8                   *addr, 
    INT32                   Length);
    
ACPI_STATUS
AmlDoFieldElement (
    ACPI_OBJECT_TYPE        DataType, 
    OPERATING_MODE          LoadExecMode);


/*
 * isdopkg - interpreter/scanner AML package load/execute
 */

ACPI_STATUS
AmlDoPkg (
    ACPI_OBJECT_TYPE        Type, 
    OPERATING_MODE          LoadExecMode);


/*
 * isdoname - interpreter/scanner named object load/execute
 */

ACPI_STATUS
AmlDoNameSpaceModifier (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoNamedObject (
    OPERATING_MODE          LoadExecMode);


/*
 * isidata - interpreter/scanner interpreted data load/execute
 */

ACPI_STATUS 
AmlDoFieldFlag (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoMatchOp (
    OPERATING_MODE          LoadExecMode);

void
AmlDoOpByte (
    INT32                   nl, 
    UINT16                  Opcode, 
    OPERATING_MODE          LoadExecMode);


/*
 * isnames - interpreter/scanner name load/execute
 */

char *
AmlAllocateNameString (
    INT32                   PrefixCount,
    INT32                   NSeg);

INT32
AmlGoodChar (
    INT32                   c);

ACPI_STATUS
AmlDoSeg (
    char                    *NameString,
    OPERATING_MODE          LoadExecMode);

INT32 
AmlDecodePackageLength (
    INT32                   LastPkgLen);

ACPI_STATUS
AmlDoName (
    ACPI_OBJECT_TYPE        DataType, 
    OPERATING_MODE          LoadExecMode);


/*
 * isdoop - interpreter/scanner expression(opcode) load/execute
 */

ACPI_STATUS
AmlDoOpCode (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoRefOpCode (
    OPERATING_MODE          LoadExecMode);


/*
 * isdoopt1 - interpreter/scanner expression(opcode) load/execute
 */

ACPI_STATUS
AmlDoType1OpCode (
    OPERATING_MODE          LoadExecMode);


/*
 * isdoopt2 - interpreter/scanner expression(opcode) load/execute
 */

ACPI_STATUS 
AmlDoType2OpCode (
    OPERATING_MODE          LoadExecMode);
    

/*
 * isrdata - interpreter/scanner raw data load/execute
 */

void 
AmlShowHexValue (
    INT32                   ByteCount, 
    UINT8                   *AmlPtr, 
    OPERATING_MODE          LoadExecMode, 
    INT32                   LeadSpace);

ACPI_STATUS
AmlDoPkgLength (
    INT32                   DoPush, 
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoByteConst (
    OPERATING_MODE          LoadExecMode, 
    INT32                   LeadSpace);

ACPI_STATUS
AmlDoWordConst (
    OPERATING_MODE          LoadExecMode, 
    INT32                   LeadSpace);

ACPI_STATUS
AmlDoDWordConst (
    OPERATING_MODE          LoadExecMode, 
    INT32                   LeadSpace);


/*
 * isutils - interpreter/scanner utilities
 */

BOOLEAN
AmlAcquireGlobalLock (
    UINT16                  Rule);

ACPI_STATUS
AmlReleaseGlobalLock (
    BOOLEAN                 Locked);

void
AmlAppendOperandDiag(
    char                    *Name, 
    INT32                   Line, 
    UINT16                  OpCode, 
    INT32                   NOperands);

UINT32 
AmlBufSeq (
    void);

INT32
AmlDigitsNeeded (
    INT32                   Value, 
    INT32                   Base);


#endif /* __INTERPRETER_H__ */
