
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


/* What are these ?? TBD */

extern INT32        OBJECT_DESCRIPTOR_PER_AMLPRIV;
extern INT32        OBJECT_DESCRIPTOR_IS_VOID;



/* Macros to allocate and deallocate structures */
/* GET RID OF THESE, confusing!! TBD!! */

#define  NEW(type)   ((type *)OsdCallocate (sizeof(type)))
#ifdef DELETE
#undef DELETE
#endif
#define  DELETE(ptr) OsdFree ((void *)(ptr)), (ptr) = 0

/* 
 * Macro to test for out-of-range subscript
 * No parens needed around aArray in expansion since the actual parameter
 * must be the name of a declared array and cannot be an expression.
 * Cast of iSubscript to int required by broken IC386 compiler.
 */

#define OUTRANGE(Subscript, Array) \
    (sizeof(Array[0]) == 0 || (int)(Subscript) < 0 \
     || (int)(Subscript) >= sizeof(Array)/sizeof(Array[0]))


/* Object Stack */

#ifdef __ISIDATA_C__
void            *ObjStack[AML_EXPR_MAX_NEST];  /* values are NsHandle or ObjHandle */
INT32           ObjStackTop = 0;

#else
extern void     *ObjStack[];  /* values are NsHandle or ObjHandle */
extern INT32    ObjStackTop;
#endif


#define PUSH_PKG_LENGTH         1
#define DO_NOT_PUSH_PKG_LENGTH  0


/* 
 * Method Stack, containing locals and args
 * per level, 0-7 are Local# and 8-14 are Arg#
 */

#define LCLBASE             0
#define NUMLCL              8
#define ARGBASE             (LCLBASE+NUMLCL)
#define NUMARG              7

extern OBJECT_DESCRIPTOR    *MethodStack[AML_METHOD_MAX_NEST][ARGBASE+NUMARG];
extern INT32                MethodStackTop;


/* |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
 * Functions which Load/Dump/Execute Interpreted Data
 * |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
 */

INT32
DoMatchOp (
    OpMode              iLE);

void
DoOpByte (
    INT32               nl, 
    UINT16              op, 
    OpMode              iLE);


/* |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
 * Functions which Load/Dump/Execute Names
 * |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
 */

char *
LastFQN (void);

void
AllocateNameString (
    INT32               PrefixCount,
    INT32               NSeg);

INT32
NcOK (
    INT32               c);

void
GenLabel (
    char                *Name);

/* |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
 * Functions which Load/Dump/Execute Atoms
 * |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
 */

/* |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
 * Functions which Load/Dump/Execute Expressions
 * |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
 */


INT32
DoOpCode (
    OpMode              iLE);

INT32
DoCode (
    OpMode              iLE);

UINT32 
AmlBufSeq (void);

INT32
DoPkg (
    NsType              Type, 
    OpMode              iLE);


INT32
DoDefinitionBlock (
    char                *name, 
    UINT8               *addr, 
    INT32               len,
    LogHandle           iLstHandle, 
    OSD_FILE            *fAsmF);

void
AmlMarkPackage (
    OBJECT_DESCRIPTOR   *pOD);

void
vAmlMarkObject (
    OBJECT_DESCRIPTOR   *pOD);

void
MarkObjectStack (
    INT32               *piCount);




/* P-code execution Prototypes */

INT32
GetMethodDepth (void);

INT32
GetRvalue (
    OBJECT_DESCRIPTOR   **StackPtr);

INT32
PrepDefFieldValue (
    NsHandle            Region, 
    UINT8               FldFlg, 
    INT32               FldPos, 
    INT32               FldLen);

INT32
PrepBankFieldValue (
    NsHandle            Region, 
    NsHandle            BankReg, 
    UINT32              BankVal,
    UINT8               FldFlg, 
    INT32               FldPos, 
    INT32               FldLen);

INT32
PrepIndexFieldValue(
    NsHandle            IndexReg, 
    NsHandle            DataReg,
    UINT8               FldFlg, 
    INT32               FldPos, 
    INT32               FldLen);

INT32
PrepStack (
    char                *Types);

void
AmlAppendOperandDiag(
    char                *Name, 
    INT32               Line, 
    UINT16              OpCode, 
    INT32               NOperands);

INT32
ExecStore (
    OBJECT_DESCRIPTOR   *op1, 
    OBJECT_DESCRIPTOR   *res);

INT32
ExecMonadic1 (
    UINT16              op);

INT32
ExecMonadic2R (
    UINT16              op);

INT32
ExecMonadic2 (
    UINT16              op);

INT32
ExecDyadic1 (
    UINT16              op);

INT32
ExecDyadic2R (
    UINT16              op);

INT32
ExecDyadic2S (
    UINT16              op);

INT32
ExecCreateField (
    UINT16              op);

INT32
ExecFatal (void);

INT32
ExecIndex (void);

INT32
ExecMatch (void);

INT32
ExecDyadic2 (
    UINT16              op);

INT32
AmlExec (
    INT32               Offset, 
    INT32               Len, 
    OBJECT_DESCRIPTOR   **Params);

void
MarkMethodValues (
    INT32               *Count);

INT32
IsMethodValue (
    OBJECT_DESCRIPTOR   *pOD);


/* I/O Prototypes */
/* Prototypes */

void
ClearPkgStack (void);

void
SetPCodeInput (
    UINT8               *Base, 
    INT32               Len);

void
SetMethod (
    void                *Object);

INT32
AmlPrepExec (
    ptrdiff_t           Offset, 
    INT32               Len);

ACPI_OBJECT_HANDLE
PCodeHandle (void);

void
GetCurrentLoc (
    meth                *Method);

void
SetCurrentLoc (
    meth                *Method);

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

INT32
PushLen (
    INT32               len, 
    OpMode              LoadExecMode);

INT32
PushExecLen (
    INT32               len);

INT32
PushExec (
    UINT8               *Code, 
    INT32               Len);

INT32
PopLen (
    INT32               NoErrUnder, 
    OpMode              LoadExecMode);

INT32
PopExecLen (void);

INT32
PopExec (void);

INT32
PkgNested (void);

INT32
avail (
    size_t              n);

INT32
Peek (void);

INT32
GetPCodeByte (
    ptrdiff_t           Offset);

INT32
PeekOp (void);

size_t
ConsumeAMLStreamBytes (
    size_t              BytesToGet, 
    UINT8               *AmlBuffer);

void
ConsumeAMLPackage (
    OpMode              LoadExecMode);

void
DumpAMLBuffer (
    size_t              Length);


INT32
DumpStackEntry (
    OBJECT_DESCRIPTOR   *EntryDesc);

void
DumpStack (
    OpMode              LoadExecMode, 
    char                *pcIdent, 
    INT32               NumLevels, 
    char                *pcNote);
        
INT32
PushIfExec (
    OpMode              LoadExecMode);

INT32
IsInPCodeBlock (
    UINT8               *Where);

void
DeleteObject (
    OBJECT_DESCRIPTOR   **ppOD);


/* OS interfaces */


void
DoSuspend(
    UINT32              Time);

INT32
DoNotifyOp (
    OBJECT_DESCRIPTOR   *val, 
    OBJECT_DESCRIPTOR   *obj);

INT32
AcquireOpRqst(
    OBJECT_DESCRIPTOR   *Time, 
    OBJECT_DESCRIPTOR   *sOb);

INT32
WaitOpRqst(
    OBJECT_DESCRIPTOR   *Time, 
    OBJECT_DESCRIPTOR   *sOb);

INT32
ReleaseOpRqst(
    OBJECT_DESCRIPTOR   *sOb);

INT32
ResetOpRqst(
    OBJECT_DESCRIPTOR   *sOb);

INT32
SignalOpRqst(
    OBJECT_DESCRIPTOR   *sOb);

INT32
GetGlobalLock(void);

void
ReleaseGlobalLock(void);



INT32 
DoByteConst (
    OpMode              LoadExecMode, 
    INT32               LeadSpace);

INT32 
DoWordConst (
    OpMode              LoadExecMode, 
    INT32               LeadSpace);

INT32 
DoDWordConst (
    OpMode              LoadExecMode, 
    INT32               LeadSpace);

INT32 
DoName (
    NsType              DataType, 
    OpMode              LoadExecMode);


INT32 
DoPkgLength (
    INT32               DoPush, 
    OpMode              LoadExecMode);

INT32 
DoFieldFlag (
    OpMode              LoadExecMode);

INT32 
GetEncodedPkgLen (
    INT32               LastPkgLen);

INT32 
DoType2OpCode (
    OpMode              LoadExecMode);


INT32 
DoSuperName (
    OpMode              LoadExecMode, 
    NsType              Define);

INT32 
DoRefOpCode (
    OpMode              LoadExecMode);

INT32 
DoLiteral (
    OpMode              LoadExecMode);

char *
LastFullyQualifiedName (
    void);

INT32 
DoDataTerm (
    OpMode              LoadExecMode);

INT32 
DoType1OpCode (
    OpMode              LoadExecMode);

INT32
SetNamedFieldValue (
    NsHandle            NamedField, 
    UINT32              Value);

INT32
GetNamedFieldValue (
    NsHandle            NamedField, 
    UINT32              *Value);

INT32
SetMethodValue (
    INT32               Index, 
    OBJECT_DESCRIPTOR   *ObjDesc, 
    OBJECT_DESCRIPTOR   *ObjDesc2);

INT32
GetMethodValue (
    INT32               Index, 
    OBJECT_DESCRIPTOR   *ObjDesc);

NsType
GetMethodValTyp (
    INT32               Index);

void
AmlAppendBlockOwner (
    void                *Owner);

void 
ShowHexValue (
    INT32               ByteCount, 
    UINT8               *AmlPtr, 
    OpMode              LoadExecMode, 
    INT32               LeadSpace);

UINT8 *
ConsumeAMLByte (
    size_t              Bytes);



#endif /* __AML_H__ */
