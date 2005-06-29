
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

#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__


#include <acpitypes.h>
#include <acpiobj.h>


/* Interpreter constants */

#define AML_END_OF_BLOCK            -1
#define PUSH_PKG_LENGTH             1
#define DO_NOT_PUSH_PKG_LENGTH      0


#define STACK_TOP                   0
#define STACK_BOTTOM                (UINT32) -1


/* For AmlMthStackSetValue */

#define MTH_TYPE_LOCAL              0
#define MTH_TYPE_ARG                1



/*
 * iapi - External interpreter interfaces
 */

ACPI_STATUS
AmlLoadTable (
    ACPI_TABLE_TYPE         TableId);

ACPI_STATUS
AmlExecuteMethod (
    ACPI_OBJECT_INTERNAL    *MthDesc,
    ACPI_OBJECT_INTERNAL    **Params);


/*
 * iefield - ACPI AML (p-code) execution - field manipulation
 */


ACPI_STATUS
AmlReadField (
    ACPI_OBJECT_INTERNAL    *ObjDesc, 
    void                    *Buffer,
    UINT32                  BufferLength,
    UINT32                  ByteLength,
    UINT32                  DatumLength,
    UINT32                  BitGranularity,
    UINT32                  ByteGranularity);

ACPI_STATUS
AmlWriteField (
    ACPI_OBJECT_INTERNAL    *ObjDesc, 
    void                    *Buffer,
    UINT32                  BufferLength,
    UINT32                  ByteLength,
    UINT32                  DatumLength,
    UINT32                  BitGranularity,
    UINT32                  ByteGranularity);

ACPI_STATUS
AmlSetupField (
    ACPI_OBJECT_INTERNAL    *ObjDesc, 
    ACPI_OBJECT_INTERNAL    *RgnDesc, 
    INT32                   FieldBitWidth);

ACPI_STATUS
AmlReadFieldData (
    ACPI_OBJECT_INTERNAL    *ObjDesc, 
    UINT32                  FieldByteOffset,
    UINT32                  FieldBitWidth,
    UINT32                  *Value);

ACPI_STATUS
AmlAccessNamedField (
    INT32                   Mode, 
    ACPI_HANDLE             NamedField, 
    void                    *Buffer,
    UINT32                  Length);

ACPI_STATUS
AmlSetNamedFieldValue (
    ACPI_HANDLE             NamedField,
    void                    *Buffer,
    UINT32                  Length);

ACPI_STATUS
AmlGetNamedFieldValue (
    ACPI_HANDLE             NamedField, 
    void                    *Buffer,
    UINT32                  Length);


/*
 * ieopexec - ACPI AML (p-code) execution - specific opcodes
 */

ACPI_STATUS
AmlExecCreateField (
    UINT16                  Opcode);

ACPI_STATUS
AmlExecCreateMutex (
    OPERATING_MODE          InterpreterMode);

ACPI_STATUS
AmlExecCreateRegion (
    UINT8                   *AmlPtr,
    UINT32                  AmlLength,
    OPERATING_MODE          InterpreterMode);

ACPI_STATUS
AmlExecCreateEvent (
    void);

ACPI_STATUS
AmlExecCreateAlias (
    void);

ACPI_STATUS
AmlExecCreateMethod (
    UINT8                   *AmlPtr,
    UINT32                  AmlLength,
    UINT32                  MethodFlags,
    ACPI_HANDLE             Method);

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

ACPI_STATUS
AmlGetRvalue (
    ACPI_OBJECT_INTERNAL    **StackPtr);

BOOLEAN
AmlIsMethodValue (
    ACPI_OBJECT_INTERNAL    *ObjDesc);


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
    UINT32                  Type,
    UINT32                  Index);

ACPI_STATUS
AmlMthStackGetValue (
    UINT32                  Type,
    UINT32                  Index, 
    ACPI_OBJECT_INTERNAL    *ObjDesc);

ACPI_STATUS
AmlMthStackSetValue (
    UINT32                  Type,
    UINT32                  Index, 
    ACPI_OBJECT_INTERNAL    *ObjDesc, 
    ACPI_OBJECT_INTERNAL    *ObjDesc2);

ACPI_STATUS
AmlMthStackPop (
    void);

ACPI_STATUS
AmlMthStackPush (
    ACPI_OBJECT_INTERNAL    **Params);

ACPI_STATUS
AmlMthStackDeleteValue (
    UINT32                  Type,
    UINT32                  Index) ;

/*
 * ieostack - object stack utilities
 */

UINT32
AmlObjStackLevel (
     void);
void
AmlObjStackClearAll (
    void);

ACPI_STATUS
AmlPrepObjStack (
    char                    *Types);

ACPI_STATUS
AmlObjStackPushIfExec (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlObjStackPush (
    void);

void *
AmlObjStackPopValue (
    void);

ACPI_STATUS
AmlObjStackPop (
    UINT32                  StackEntries);

ACPI_OBJECT_INTERNAL **
AmlObjStackGetPtr (
    UINT32                  OffsetFromStackTop);

void *
AmlObjStackGetValue (
    UINT32                  OffsetFromStackTop);

void
AmlObjStackSetValue (
    UINT32                  OffsetFromStackTop,
    void                    *StackEntry);

void *
AmlObjStackRemoveValue (
    UINT32                  OffsetFromStackTop);

void
AmlObjStackDeleteValue (
    UINT32                  OffsetFromStackTop);

ACPI_STATUS
AmlObjStackClearUntil (
    ACPI_OBJECT_TYPE        Type);


ACPI_OBJECT_INTERNAL **
AmlObjStackGetTopPtr (
    void);

void
AmlObjStackClearTop (
    void);



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
    UINT32                  Length, 
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlPkgPushExecLength (
    UINT32                  Length);

ACPI_STATUS
AmlPkgPushExec (
    UINT8                   *Code, 
    UINT32                  Len);

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
    ACPI_OBJECT_INTERNAL    *Value, 
    ACPI_OBJECT_INTERNAL    *ObjDesc);

void
OsDoSuspend(
    UINT32                  Time);

ACPI_STATUS
OsAcquireOpRqst(
    ACPI_OBJECT_INTERNAL    *Time, 
    ACPI_OBJECT_INTERNAL    *ObjDesc);

ACPI_STATUS
OsReleaseOpRqst(
    ACPI_OBJECT_INTERNAL    *ObjDesc);

ACPI_STATUS
OsSignalOpRqst(
    ACPI_OBJECT_INTERNAL    *ObjDesc);

ACPI_STATUS
OsWaitOpRqst(
    ACPI_OBJECT_INTERNAL    *Time, 
    ACPI_OBJECT_INTERNAL    *ObjDesc);

ACPI_STATUS
OsResetOpRqst(
    ACPI_OBJECT_INTERNAL    *ObjDesc);

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
AmlExecStore (
    ACPI_OBJECT_INTERNAL    *op1, 
    ACPI_OBJECT_INTERNAL    *res);

ACPI_STATUS
PsxExecute (
    ACPI_OBJECT_INTERNAL    *MthDesc,
    ACPI_OBJECT_INTERNAL    **Params);



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
    UINT8                   *Pcode);

UINT16
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

void
AmlSetPCodeInput (
    UINT8                   *Base, 
    UINT32                  Length);

ACPI_STATUS
AmlSetMethod (
    void                    *Object);

ACPI_STATUS
AmlPrepExec (
    UINT8                   *Pcode, 
    UINT32                  PcodeLength);

ACPI_HANDLE
AmlGetPCodeHandle (
    void);

void
AmlGetCurrentLocation (
    ACPI_OBJECT_INTERNAL    *MethodDesc);

void
AmlSetCurrentLocation (
    ACPI_OBJECT_INTERNAL    *MethodDesc);


/*
 * isdump - Scanner debug output routines
 */

void 
AmlShowHexValue (
    INT32                   ByteCount, 
    UINT8                   *AmlPtr, 
    OPERATING_MODE          LoadExecMode, 
    INT32                   LeadSpace);

void
AmlDumpBuffer (
    ACPI_SIZE               Length);


ACPI_STATUS
AmlDumpObjStackEntry (
    ACPI_OBJECT_INTERNAL    *EntryDesc);

void
_AmlDumpObjStack (
    OPERATING_MODE          LoadExecMode, 
    char                    *Ident, 
    INT32                   NumLevels, 
    char                    *Note,
    char                    *ModuleName, 
    INT32                   LineNumber);

void
AmlDumpObjectDescriptor (
	ACPI_OBJECT_INTERNAL    *ObjDesc);


#define AmlDumpObjStack(a,b,c,d)    _AmlDumpObjStack(a,b,c,d,_THIS_MODULE,__LINE__)



/*
 * isnames - interpreter/scanner name load/execute
 */

char *
AmlAllocateNameString (
    INT32                   PrefixCount,
    INT32                   NSeg);

INT32
AmlGoodChar (
    INT32                   Character);

BOOLEAN 
AmlGoodName (
    UINT32                  Name);

ACPI_STATUS
AmlExecNameSegment (
    UINT8                   **InAmlAddress,
    char                    *NameString);

ACPI_STATUS
AmlGetNameString (
    ACPI_OBJECT_TYPE        DataType, 
    UINT8                   *InAmlAddress,
    char                    **OutNameString,
    UINT32                  *OutNameLength)  ; 

INT32 
AmlDecodePackageLength (
    INT32                   LastPkgLen);


ACPI_STATUS
AmlDoName (
    ACPI_OBJECT_TYPE        DataType, 
    OPERATING_MODE          LoadExecMode);



/*
 * isutils - interpreter/scanner utilities
 */

BOOLEAN
AmlAcquireGlobalLock (
    UINT32                  Rule);

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

ACPI_STATUS
AmlEisaIdToString (
    UINT32                  NumericId,
    char                    *OutString);


/*
 * ieregion - default OpRegion handlers
 */

ACPI_STATUS
AmlSystemMemorySpaceHandler (
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value,
    void                    *Context);

ACPI_STATUS
AmlSystemIoSpaceHandler (
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value,
    void                    *Context);

ACPI_STATUS
AmlPciConfigSpaceHandler (
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value,
    void                    *Context);

ACPI_STATUS
AmlEmbeddedControllerSpaceHandler (
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value,
    void                    *Context);

ACPI_STATUS
AmlSmBusSpaceHandler (
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value,
    void                    *Context);




#endif /* __INTERPRETER_H__ */
