/******************************************************************************
 * 
 * Module Name: parser.h - AML Parser subcomponent prototypes and defines
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


#ifndef _PARSER_H_
#define _PARSER_H_




#define OP_HAS_RETURN_VALUE         1

/* variable # arguments */

#define ACPI_VAR_ARGS               (~0UL)

/* maximum virtual address */

#define ACPI_MAX_AML                ((UINT8 *)(~0UL))

/* mask argument count from method declaration */

#define ACPI_METHOD_ARG_MASK        (0x7)

/* For PsxMthStackSetValue */

#define MTH_TYPE_LOCAL              0
#define MTH_TYPE_ARG                1




/* psapi - Parser external interfaces */

ACPI_STATUS
PsxLoadTable (
    UINT8                   *PcodeAddr, 
    INT32                   PcodeLength);

ACPI_STATUS
PsxExecute (
    ACPI_OBJECT_INTERNAL    *MthDesc,
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    **ReturnObjDesc);

ACPI_STATUS
PsxGetRegionData (
    ACPI_OBJECT_INTERNAL    *RgnDesc);


#ifndef _RPARSER

/* Common interfaces */

ACPI_STATUS
PsxObjStackPush (
    void                    *Object,
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
PsxObjStackPop (
    UINT32                  PopCount,
    ACPI_WALK_STATE         *WalkState);

void *
PsxObjStackGetValue (
    UINT32                  Index,
    ACPI_WALK_STATE         *WalkState);



/******************************************************************************
 * 
 * Parser to Interpreter interface layer
 *
 *****************************************************************************/


/* psxctrl - Parser/Interpreter interface, control stack routines */

ACPI_CTRL_STATE *
PsCreateControlState (void);

void
PsPushControlState (
    ACPI_CTRL_STATE         *ControlState,
    ACPI_WALK_STATE         *WalkState);

ACPI_CTRL_STATE *
PsPopControlState (
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS 
PsxExecBeginControlOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS 
PsxExecEndControlOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);


/* psxexec - Parser/Interpreter interface, method execution callbacks */

ACPI_STATUS
PsxExecBeginOp (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
PsxExecEndOp (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op);


/* psxfield - Parser/Interpreter interface for AML fields */


ACPI_STATUS
PsxCreateField (
    ACPI_GENERIC_OP         *Op,
    ACPI_HANDLE             Region);

ACPI_STATUS
PsxCreateBankField (
    ACPI_GENERIC_OP         *Op,
    ACPI_HANDLE             Region);

ACPI_STATUS
PsxCreateIndexField (
    ACPI_GENERIC_OP         *Op,
    ACPI_HANDLE             Region);


/* psxload - Parser/Interpreter interface, namespace load callbacks */

ACPI_STATUS
PsxLoadBeginMethodOp (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
PsxLoadBeginOp (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
PsxLoadEndOp (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op);


/* psxmargs - method stack utilities */


ACPI_STATUS
PsxMthStackDeleteArgs (
    ACPI_WALK_STATE         *WalkState);

BOOLEAN
PsxIsMethodValue (
    ACPI_OBJECT_INTERNAL    *ObjDesc);

INT32
PsxMthStackLevel (
    void);

ACPI_OBJECT_TYPE
PsxMthStackGetType (
    UINT32                  Type,
    UINT32                  Index);

ACPI_STATUS
PsxMthStackGetValue (
    UINT32                  Type,
    UINT32                  Index, 
    ACPI_OBJECT_INTERNAL    **ObjDesc);

ACPI_STATUS
PsxMthStackSetValue (
    UINT32                  Type,
    UINT32                  Index, 
    ACPI_OBJECT_INTERNAL    *ObjDesc); 

ACPI_STATUS
PsxMthStackPop (
    void);

ACPI_STATUS
PsxMthStackPush (
    ACPI_OBJECT_INTERNAL    **Params);

ACPI_STATUS
PsxMthStackDeleteValue (
    UINT32                  Type,
    UINT32                  Index);

ACPI_STATUS
PsxMthStackInitArgs (
    ACPI_OBJECT_INTERNAL    **Params,
    UINT32                  ParamCount);

NAME_TABLE_ENTRY *
PsxMthStackGetNte (
    UINT32                  Type,
    UINT32                  Index);

ACPI_STATUS
PsxMthStackInit (
    ACPI_WALK_STATE         *WalkState);


/* psxmethod - Parser/Interpreter interface - control method parsing */

ACPI_STATUS
PsxParseMethod (
    ACPI_HANDLE             ObjHandle);

ACPI_STATUS
PsxCallControlMethod (
    ACPI_WALK_LIST          *WalkList,
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
PsxRestartControlMethod (
    ACPI_WALK_STATE         *WalkState,
    ACPI_OBJECT_INTERNAL    *ReturnDesc);


/* psxobj - Parser/Interpreter interface - object initialization and conversion */

ACPI_STATUS
PsxInitOneObject (
    ACPI_HANDLE             ObjHandle, 
    UINT32                  Level, 
    void                    *Context,
    void                    **ReturnValue);

ACPI_STATUS
PsxInitializeObjects (
    void);

ACPI_STATUS
PsxBuildInternalPackageObj (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *op,
    ACPI_OBJECT_INTERNAL    **ObjDesc);

ACPI_STATUS
PsxBuildInternalObject (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *op,
    ACPI_OBJECT_INTERNAL    **ObjDescPtr);

ACPI_STATUS
PsxInitObjectFromOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op,
    UINT32                  Opcode,
    ACPI_OBJECT_INTERNAL    *ObjDesc);

ACPI_STATUS
PsxCreateNamedObject (
    ACPI_WALK_STATE         *WalkState,
    NAME_TABLE_ENTRY        *Entry,
    ACPI_GENERIC_OP         *Op);


/* psxregn - Parser/Interpreter interface - Op Region parsing */

ACPI_STATUS
PsxEvalRegionOperands (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op);

ACPI_STATUS
PsxInitializeRegion (
    ACPI_HANDLE             ObjHandle);

    
/* psxutils - Parser/Interpreter interface utility routines */

void
PsxDeleteResultIfNotUsed (
    ACPI_GENERIC_OP         *Op,
    ACPI_OBJECT_INTERNAL    *ResultObj,
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
PsxCreateOperand (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Arg);

ACPI_STATUS
PsxCreateOperands (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *FirstArg);

ACPI_STATUS
PsxResolveOperands (
    ACPI_WALK_STATE         *WalkState);

ACPI_OBJECT_TYPE
PsxMapOpcodeToDataType (
    UINT32                  Opcode,
    UINT32                  *OutFlags);

ACPI_OBJECT_TYPE 
PsxMapNamedOpcodeToDataType (
    UINT32                  Opcode);




/******************************************************************************
 * 
 * Parser interfaces
 *
 *****************************************************************************/



/* psargs - Parse AML opcode arguments */

UINT8 *
PsGetNextPackageEnd (
    ACPI_PARSE_STATE        *ParserState);

UINT8 *
PsGetNextNamestring (
    ACPI_PARSE_STATE        *ParserState);

void
PsGetNextSimpleArg (
    ACPI_PARSE_STATE        *ParserState,
    INT32                   ArgType,        /* type of argument */
    ACPI_GENERIC_OP         *Arg);           /* (OUT) argument data */

void
PsGetNextNamepath (
    ACPI_PARSE_STATE        *ParserState,
    ACPI_GENERIC_OP         *Arg,
    UINT32                  *ArgCount,
    BOOLEAN                 MethodCall);

ACPI_GENERIC_OP *
PsGetNextField (
    ACPI_PARSE_STATE        *ParserState);

ACPI_GENERIC_OP *
PsGetNextArg (
    ACPI_PARSE_STATE        *ParserState, 
    INT32                   ArgType, 
    UINT32                  *ArgCount);


/* psopcode - AML Opcode information */

ACPI_OP_INFO *
PsGetOpcodeInfo (
    INT32                   Opcode);

char *
PsGetOpcodeName (
    INT32                   Opcode);


/* psparse - top level parsing routines */

void
PsDeleteParseTree (
    ACPI_GENERIC_OP         *root);

ACPI_STATUS
PsParseLoop (
    ACPI_PARSE_STATE        *ParserState);


ACPI_STATUS
PsParseAml (
    ACPI_GENERIC_OP         *StartScope,
    UINT8                   *Aml, 
    INT32                   AmlSize);

ACPI_STATUS
PsParseTable (
    UINT8                   *aml, 
    INT32                   amlSize,
    INTERPRETER_CALLBACK    DescendingCallback,
    INTERPRETER_CALLBACK    AscendingCallback,
    ACPI_GENERIC_OP         **RootObject);

INT32
PsPeekOpcode (
    ACPI_PARSE_STATE        *state);



/* psscope - Scope stack management routines */


ACPI_STATUS
PsInitScope (
    ACPI_PARSE_STATE        *ParserState,
    ACPI_GENERIC_OP         *Root);

ACPI_GENERIC_OP *
PsGetParentScope (
    ACPI_PARSE_STATE        *state);

BOOLEAN
PsHasCompletedScope (
    ACPI_PARSE_STATE        *ParserState);

ACPI_STATUS
PsPushScope (
    ACPI_PARSE_STATE        *ParserState,
    ACPI_GENERIC_OP         *Op, 
    char                    *NextArg,
    UINT32                  ArgCount);

void
PsPopScope (
    ACPI_PARSE_STATE        *ParserState,
    ACPI_GENERIC_OP         **Op,
    char                    **NextArg);

void
PsCleanupScope (
    ACPI_PARSE_STATE        *state);


/* pstree - parse tree manipulation routines */

void 
PsAppendArg(
    ACPI_GENERIC_OP         *op, 
    ACPI_GENERIC_OP         *arg);

ACPI_GENERIC_OP*
PsFind (
    ACPI_GENERIC_OP         *Scope, 
    UINT8                   *Path,
    UINT32                  Opcode,
    UINT32                  Create);

ACPI_GENERIC_OP *
PsGetArg(
    ACPI_GENERIC_OP         *op, 
    UINT32                   argn);

ACPI_GENERIC_OP *
PsGetChild (
    ACPI_GENERIC_OP         *op);

ACPI_GENERIC_OP *
PsGetDepthNext (
    ACPI_GENERIC_OP         *Origin, 
    ACPI_GENERIC_OP         *Op);



/* pswalk - parse tree walk routines */

ACPI_STATUS
PsWalkParsedAml (
    ACPI_GENERIC_OP         *StartOp,
    ACPI_GENERIC_OP         *EndOp,
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    **CallerReturnDesc,
    INTERPRETER_CALLBACK    DescendingCallback,
    INTERPRETER_CALLBACK    AscendingCallback);

ACPI_STATUS
PsGetNextWalkOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op,
    INTERPRETER_CALLBACK    AscendingCallback);

ACPI_WALK_STATE *
PsGetCurrentWalkState (
    ACPI_WALK_LIST          *WalkList);


/* pswstate - parser WALK_STATE management routines */

ACPI_WALK_STATE *
PsCreateWalkState (
    ACPI_GENERIC_OP         *Origin,
    ACPI_WALK_LIST          *WalkList);

ACPI_STATUS
PsxObjStackDeleteAll (
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
PsxObjStackPopAndDelete (
    UINT32                  PopCount,
    ACPI_WALK_STATE         *WalkState);

void
PsDeleteWalkState (
    ACPI_WALK_STATE         *WalkState);

ACPI_WALK_STATE *
PsPopWalkState (
    ACPI_WALK_LIST          *WalkList);

ACPI_STATUS
PsxResultStackPop (
    ACPI_OBJECT_INTERNAL    **Object,
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
PsxResultStackPush (
    void                    *Object,
    ACPI_WALK_STATE         *WalkState);

ACPI_STATUS
PsxResultStackClear (
    ACPI_WALK_STATE         *WalkState);


/* psutils - parser utilities */

void
PsInitOp (
    ACPI_GENERIC_OP         *op,
    UINT32                  opcode);

ACPI_GENERIC_OP * 
PsAllocOp (
    UINT32                  opcode);

BOOLEAN
PsIsLeadingChar (
    INT32                   c);

BOOLEAN
PsIsPrefixChar (
    INT32                   c);

BOOLEAN
PsIsNamedOp (
    UINT32                  opcode);

BOOLEAN
PsIsNamedObjectOp (
    UINT32                  opcode);

BOOLEAN
PsIsDeferredOp (
    UINT32                  opcode);

BOOLEAN
PsIsBytelistOp(
    UINT32                  opcode);

BOOLEAN
PsIsFieldOp(
    UINT32                  opcode);

ACPI_NAMED_OP*
PsToNamedOp(
    ACPI_GENERIC_OP         *op);

ACPI_DEFERRED_OP *
PsToDeferredOp (
    ACPI_GENERIC_OP         *Op);

ACPI_BYTELIST_OP*
PsToBytelistOp(
    ACPI_GENERIC_OP         *op);

UINT32
PsGetName(
    ACPI_GENERIC_OP         *op);

void
PsSetName(
    ACPI_GENERIC_OP         *op, 
    UINT32                  name);


/* psdump - display parser tree */

INT32
PsSprintPath (
    char                    *BufferStart,
    UINT32                  BufferSize,
    ACPI_GENERIC_OP         *Op);

INT32
PsSprintOp (
    char                    *BufferStart, 
    UINT32                  BufferSize, 
    ACPI_GENERIC_OP         *Op);

void 
PsShow (
    ACPI_GENERIC_OP         *op);






#else

/******************************************************************************
 * 
 * Original Recursive parser
 * TBD: Remove when the parser is obsoleted
 *
 *****************************************************************************/


INT32
PsxMthStackLevel (
    void);

BOOLEAN
PsxIsMethodValue (
    ACPI_OBJECT_INTERNAL    *ObjDesc);

char *
PsGetOpcodeName (
    INT32                   Opcode);

ACPI_OBJECT_TYPE
PsxMthStackGetType (
    UINT32                  Type,
    UINT32                  Index);

ACPI_STATUS
PsxMthStackGetValue (
    UINT32                  Type,
    UINT32                  Index, 
    ACPI_OBJECT_INTERNAL    **DestDesc);

ACPI_STATUS
PsxMthStackSetValue (
    UINT32                  Type,
    UINT32                  Index, 
    ACPI_OBJECT_INTERNAL    *SrcDesc, 
    ACPI_OBJECT_INTERNAL    *DestDesc);

ACPI_STATUS
PsxMthStackPush (
    ACPI_OBJECT_INTERNAL    **Params);

ACPI_STATUS
PsxMthStackPop (
    void);

NAME_TABLE_ENTRY *
PsxMthStackGetNte (
    UINT32                  Type,
    UINT32                  Index);


/*
 * idoatoms - interpreter/scanner atom load/execute
 */

ACPI_STATUS 
AmlDoSuperName (
    OPERATING_MODE          LoadExecMode, 
    ACPI_OBJECT_TYPE        Define);

ACPI_STATUS
AmlDoLiteral (
    OPERATING_MODE          LoadExecMode);


/*
 * idoexpr - interpreter/scanner expression load/execute
 */

ACPI_STATUS
AmlDoCodeBlock (
    OPERATING_MODE          InterpreterMode);

ACPI_STATUS
AmlDoDataTerm (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoCode (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
PsxLoadTable (
    UINT8                   *Address, 
    INT32                   Length);
    
ACPI_STATUS
AmlDoFieldElement (
    ACPI_OBJECT_TYPE        DataType, 
    FIELD_INFO              *FieldInfo,
    OPERATING_MODE          LoadExecMode);


/*
 * isdopkg - interpreter/scanner AML package load/execute
 */

ACPI_STATUS
AmlDoPkg (
    ACPI_OBJECT_TYPE        Type, 
    OPERATING_MODE          LoadExecMode);


/*
 * idopkobj - typed package routines for misc types
 */

ACPI_STATUS
AmlDoPackagePkg (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoDevicePkg (
    ACPI_OBJECT_TYPE        DataType, 
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoPowerPkg (
    ACPI_OBJECT_TYPE        DataType, 
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoProcessorPkg (
    ACPI_OBJECT_TYPE        DataType, 
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoMethodPkg (
    ACPI_OBJECT_TYPE        DataType, 
    UINT32                  PkgLength,
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoBufferPkg (
    OPERATING_MODE          LoadExecMode);


/*
 * idopkfld - typed package routines for field types
 */

ACPI_STATUS
AmlDoDefFieldPkg (
    ACPI_OBJECT_TYPE        DataType, 
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoBankFieldPkg (
    ACPI_OBJECT_TYPE        DataType, 
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoIndexFieldPkg (
    ACPI_OBJECT_TYPE        DataType, 
    OPERATING_MODE          LoadExecMode);


/*
 * idopkctl - typed package routines for control types
 */

ACPI_STATUS
AmlDoWhilePkg (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoIfPkg (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoElsePkg (
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
    FIELD_INFO              *FieldInfo,
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
AmlDoMatchOp (
    OPERATING_MODE          LoadExecMode);

void
AmlDoOpByte (
    UINT16                  Opcode, 
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

ACPI_STATUS
AmlDoPkgLength (
    INT32                   DoPush, 
    UINT32                  *ReturnLength,
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
 * ixface - parser/interpreter interface
 */

ACPI_STATUS
PsExecMonadic1 (
    UINT16                  Opcode);

ACPI_STATUS
PsExecMonadic2 (
    UINT16                  Opcode);

ACPI_STATUS
PsExecMonadic2R (
    UINT16                  Opcode);

ACPI_STATUS
PsExecDyadic1 (
    UINT16                  Opcode);

ACPI_STATUS
PsExecDyadic2 (
    UINT16                  Opcode);

ACPI_STATUS
PsExecDyadic2R (
    UINT16                  Opcode);

ACPI_STATUS
PsExecDyadic2S (
    UINT16                  Opcode);

ACPI_STATUS
PsExecCreateField (
    UINT16                  Opcode);

ACPI_STATUS
PsExecFatal (
    void);

ACPI_STATUS
PsExecIndex (
    void);

ACPI_STATUS
PsExecMatch (
    void);

ACPI_STATUS
PsExecCreateMutex (
    OPERATING_MODE          InterpreterMode);

ACPI_STATUS
PsExecCreateEvent (
    void);

ACPI_STATUS
PsExecCreateAlias (
    void);


/*
 * ieostack - object stack utilities
 */

UINT32
PsxObjStackLevel (
     void);
void
PsxObjStackClearAll (
    void);

ACPI_STATUS
PsxObjStackPushIfExec (
    OPERATING_MODE          LoadExecMode);

ACPI_STATUS
PsxObjStackPush (
    void);

void *
PsxObjStackPopValue (
    void);

ACPI_STATUS
PsxObjStackPop (
    UINT32                  StackEntries);

ACPI_OBJECT_INTERNAL **
PsxObjStackGetPtr (
    UINT32                  OffsetFromStackTop);

void *
PsxObjStackGetValue (
    UINT32                  OffsetFromStackTop);

void
PsxObjStackSetValue (
    UINT32                  OffsetFromStackTop,
    void                    *StackEntry);

void *
PsxObjStackRemoveValue (
    UINT32                  OffsetFromStackTop);

void
PsxObjStackDeleteValue (
    UINT32                  OffsetFromStackTop);

ACPI_STATUS
PsxObjStackClearUntil (
    ACPI_OBJECT_TYPE        Type);


ACPI_OBJECT_INTERNAL **
PsxObjStackGetTopPtr (
    void);

void
PsxObjStackClearTop (
    void);



#endif



#endif /* _PARSER_H_ */
