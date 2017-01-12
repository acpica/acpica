/******************************************************************************
 *
 * Module Name: aslcompiler.h - common include file for iASL
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2017, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights. You may have additional license terms from the party that provided
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
 * to or modifications of the Original Intel Code. No other license or right
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
 * and the following Disclaimer and Export Compliance provision. In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change. Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee. Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution. In
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
 * HERE. ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT, ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES. INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS. INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES. THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government. In the
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

#ifndef __ASLCOMPILER_H
#define __ASLCOMPILER_H

#include "acpi.h"
#include "accommon.h"
#include "amlresrc.h"
#include "acdebug.h"

/* Microsoft-specific */

#if (defined WIN32 || defined WIN64)

/* warn : used #pragma pack */
#pragma warning(disable:4103)

/* warn : named type definition in parentheses */
#pragma warning(disable:4115)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

/* Compiler headers */

#include "asldefine.h"
#include "asltypes.h"
#include "aslmessages.h"
#include "aslglobal.h"
#include "preprocess.h"


/*******************************************************************************
 *
 * Compiler prototypes
 *
 ******************************************************************************/

/*
 * Main ASL parser - generated from flex/bison, lex/yacc, etc.
 */
ACPI_PARSE_OBJECT *
AslDoError (
    void);

int
AslCompilerlex(
    void);

void
AslResetCurrentLineBuffer (
    void);

void
AslInsertLineBuffer (
    int                     SourceChar);

int
AslPopInputFileStack (
    void);

void
AslPushInputFileStack (
    FILE                    *InputFile,
    char                    *Filename);

void
AslParserCleanup (
    void);


/*
 * aslstartup - entered from main()
 */
void
AslInitializeGlobals (
    void);

typedef
ACPI_STATUS (*ASL_PATHNAME_CALLBACK) (
    char *);

ACPI_STATUS
AslDoOneFile (
    char                    *Filename);

ACPI_STATUS
AslCheckForErrorExit (
    void);


/*
 * aslcompile - compile mainline
 */
void
AslCompilerSignon (
    UINT32                  FileId);

void
AslCompilerFileHeader (
    UINT32                  FileId);

int
CmDoCompile (
    void);

void
CmDoOutputFiles (
    void);

void
CmCleanupAndExit (
    void);

void
CmDeleteCaches (
    void);


/*
 * aslascii - ascii support
 */
ACPI_STATUS
FlIsFileAsciiSource (
    char                    *Filename,
    BOOLEAN                 DisplayErrors);


/*
 * aslwalks - semantic analysis and parse tree walks
 */
ACPI_STATUS
AnOtherSemanticAnalysisWalkBegin (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

ACPI_STATUS
AnOtherSemanticAnalysisWalkEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

ACPI_STATUS
AnOperandTypecheckWalkEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

ACPI_STATUS
AnMethodTypingWalkEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);


/*
 * aslmethod - Control method analysis walk
 */
ACPI_STATUS
MtMethodAnalysisWalkBegin (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

ACPI_STATUS
MtMethodAnalysisWalkEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);


/*
 * aslbtypes - bitfield data types
 */
UINT32
AnMapObjTypeToBtype (
    ACPI_PARSE_OBJECT       *Op);

UINT32
AnMapArgTypeToBtype (
    UINT32                  ArgType);

UINT32
AnGetBtype (
    ACPI_PARSE_OBJECT       *Op);

void
AnFormatBtype (
    char                    *Buffer,
    UINT32                  Btype);


/*
 * aslanalyze - Support functions for parse tree walks
 */
void
AnCheckId (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_NAME               Type);

/* Values for Type argument above */

#define ASL_TYPE_HID        0
#define ASL_TYPE_CID        1

BOOLEAN
AnIsInternalMethod (
    ACPI_PARSE_OBJECT       *Op);

UINT32
AnGetInternalMethodReturnType (
    ACPI_PARSE_OBJECT       *Op);

BOOLEAN
AnLastStatementIsReturn (
    ACPI_PARSE_OBJECT       *Op);

void
AnCheckMethodReturnValue (
    ACPI_PARSE_OBJECT       *Op,
    const ACPI_OPCODE_INFO  *OpInfo,
    ACPI_PARSE_OBJECT       *ArgOp,
    UINT32                  RequiredBtypes,
    UINT32                  ThisNodeBtype);

BOOLEAN
AnIsResultUsed (
    ACPI_PARSE_OBJECT       *Op);

void
ApCheckForGpeNameConflict (
    ACPI_PARSE_OBJECT       *Op);

void
ApCheckRegMethod (
    ACPI_PARSE_OBJECT       *Op);

BOOLEAN
ApFindNameInScope (
    char                    *Name,
    ACPI_PARSE_OBJECT       *Op);

BOOLEAN
ApFindNameInDeviceTree (
    char                    *Name,
    ACPI_PARSE_OBJECT       *Op);

/*
 * aslerror - error handling/reporting
 */
void
AslAbort (
    void);

void
AslError (
    UINT8                   Level,
    UINT16                  MessageId,
    ACPI_PARSE_OBJECT       *Op,
    char                    *ExtraMessage);

ACPI_STATUS
AslDisableException (
    char                    *MessageIdString);

BOOLEAN
AslIsExceptionDisabled (
    UINT8                   Level,
    UINT16                  MessageId);

void
AslCoreSubsystemError (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_STATUS             Status,
    char                    *ExtraMessage,
    BOOLEAN                 Abort);

int
AslCompilererror(
    const char              *s);

void
AslCommonError (
    UINT8                   Level,
    UINT16                  MessageId,
    UINT32                  CurrentLineNumber,
    UINT32                  LogicalLineNumber,
    UINT32                  LogicalByteOffset,
    UINT32                  Column,
    char                    *Filename,
    char                    *ExtraMessage);

void
AslCommonError2 (
    UINT8                   Level,
    UINT16                  MessageId,
    UINT32                  LineNumber,
    UINT32                  Column,
    char                    *SourceLine,
    char                    *Filename,
    char                    *ExtraMessage);

void
AePrintException (
    UINT32                  FileId,
    ASL_ERROR_MSG           *Enode,
    char                    *Header);

void
AePrintErrorLog (
    UINT32                  FileId);

void
AeClearErrorLog (
    void);


/*
 * asllisting - generate all "listing" type files
 */
void
LsDoListings (
    void);

void
LsWriteNodeToAsmListing (
    ACPI_PARSE_OBJECT       *Op);

void
LsWriteNode (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  FileId);

void
LsDumpParseTree (
    void);


/*
 * asllistsup - Listing file support utilities
 */
void
LsDumpAscii (
    UINT32                  FileId,
    UINT32                  Count,
    UINT8                   *Buffer);

void
LsDumpAsciiInComment (
    UINT32                  FileId,
    UINT32                  Count,
    UINT8                   *Buffer);

void
LsCheckException (
    UINT32                  LineNumber,
    UINT32                  FileId);

void
LsFlushListingBuffer (
    UINT32                  FileId);

void
LsWriteListingHexBytes (
    UINT8                   *Buffer,
    UINT32                  Length,
    UINT32                  FileId);

void
LsWriteSourceLines (
    UINT32                  ToLineNumber,
    UINT32                  ToLogicalLineNumber,
    UINT32                  FileId);

UINT32
LsWriteOneSourceLine (
    UINT32                  FileId);

void
LsPushNode (
    char                    *Filename);

ASL_LISTING_NODE *
LsPopNode (
    void);


/*
 * aslhex - generate all "hex" output files (C, ASM, ASL)
 */
void
HxDoHexOutput (
    void);


/*
 * aslfold - constant folding
 */
ACPI_STATUS
OpcAmlConstantWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);


/*
 * aslmessages - exception strings
 */
const char *
AeDecodeMessageId (
    UINT16                  MessageId);

const char *
AeDecodeExceptionLevel (
    UINT8                   Level);

UINT16
AeBuildFullExceptionCode (
    UINT8                   Level,
    UINT16                  MessageId);

/*
 * asloffset - generate C offset file for BIOS support
 */
ACPI_STATUS
LsAmlOffsetWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

void
LsDoOffsetTableHeader (
    UINT32                  FileId);

void
LsDoOffsetTableFooter (
    UINT32                  FileId);


/*
 * aslopcodes - generate AML opcodes
 */
ACPI_STATUS
OpcAmlOpcodeWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

ACPI_STATUS
OpcAmlOpcodeUpdateWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

void
OpcGenerateAmlOpcode (
    ACPI_PARSE_OBJECT       *Op);

UINT32
OpcSetOptimalIntegerSize (
    ACPI_PARSE_OBJECT       *Op);

void
OpcGetIntegerWidth (
    ACPI_PARSE_OBJECT       *Op);


/*
 * asloperands - generate AML operands for the AML opcodes
 */
ACPI_PARSE_OBJECT  *
UtGetArg (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Argn);

void
OpnGenerateAmlOperands (
    ACPI_PARSE_OBJECT       *Op);

void
OpnDoPackage (
    ACPI_PARSE_OBJECT       *Op);


/*
 * aslopt - optmization
 */
void
OptOptimizeNamePath (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Flags,
    ACPI_WALK_STATE         *WalkState,
    char                    *AmlNameString,
    ACPI_NAMESPACE_NODE     *TargetNode);


/*
 * aslpld - ToPLD macro support
 */
void
OpcDoPld (
    ACPI_PARSE_OBJECT       *Op);


/*
 * aslprintf - Printf/Fprintf macros
 */
void
OpcDoPrintf (
    ACPI_PARSE_OBJECT       *Op);

void
OpcDoFprintf (
    ACPI_PARSE_OBJECT       *Op);


/*
 * aslprune - parse tree pruner
 */
void
AslPruneParseTree (
    UINT32                  PruneDepth,
    UINT32                  Type);


/*
 * aslcodegen - code generation
 */
void
CgGenerateAmlOutput (
    void);


/*
 * aslfile
 */
void
FlOpenFile (
    UINT32                  FileId,
    char                    *Filename,
    char                    *Mode);


/*
 * asllength - calculate/adjust AML package lengths
 */
ACPI_STATUS
LnPackageLengthWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

ACPI_STATUS
LnInitLengthsWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

void
CgGenerateAmlLengths (
    ACPI_PARSE_OBJECT       *Op);


/*
 * aslmap - opcode mappings and reserved method names
 */
ACPI_OBJECT_TYPE
AslMapNamedOpcodeToDataType (
    UINT16                  Opcode);


/*
 * aslpredef - ACPI predefined names support
 */
BOOLEAN
ApCheckForPredefinedMethod (
    ACPI_PARSE_OBJECT       *Op,
    ASL_METHOD_INFO         *MethodInfo);

void
ApCheckPredefinedReturnValue (
    ACPI_PARSE_OBJECT       *Op,
    ASL_METHOD_INFO         *MethodInfo);

UINT32
ApCheckForPredefinedName (
    ACPI_PARSE_OBJECT       *Op,
    char                    *Name);

void
ApCheckForPredefinedObject (
    ACPI_PARSE_OBJECT       *Op,
    char                    *Name);

ACPI_STATUS
ApCheckObjectType (
    const char              *PredefinedName,
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  ExpectedBtypes,
    UINT32                  PackageIndex);

void
ApDisplayReservedNames (
    void);


/*
 * aslprepkg - ACPI predefined names support for packages
 */
void
ApCheckPackage (
    ACPI_PARSE_OBJECT           *ParentOp,
    const ACPI_PREDEFINED_INFO  *Predefined);


/*
 * asltransform - parse tree transformations
 */
ACPI_STATUS
TrAmlTransformWalkBegin (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

ACPI_STATUS
TrAmlTransformWalkEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);


/*
 * asltree - parse tree support
 */
ACPI_STATUS
TrWalkParseTree (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Visitation,
    ASL_WALK_CALLBACK       DescendingCallback,
    ASL_WALK_CALLBACK       AscendingCallback,
    void                    *Context);

/*
 * aslexternal - External opcode support
 */
ACPI_STATUS
ExAmlExternalWalkBegin (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

ACPI_STATUS
ExAmlExternalWalkEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

void
ExDoExternal (
    ACPI_PARSE_OBJECT       *Op);

/* Values for "Visitation" parameter above */

#define ASL_WALK_VISIT_DOWNWARD     0x01
#define ASL_WALK_VISIT_UPWARD       0x02
#define ASL_WALK_VISIT_TWICE        (ASL_WALK_VISIT_DOWNWARD | ASL_WALK_VISIT_UPWARD)


void
TrSetParent (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_PARSE_OBJECT       *ParentOp);

ACPI_PARSE_OBJECT *
TrAllocateNode (
    UINT32                  ParseOpcode);

void
TrPrintNodeCompileFlags (
    UINT32                  Flags);

void
TrReleaseNode (
    ACPI_PARSE_OBJECT       *Op);

ACPI_PARSE_OBJECT *
TrUpdateNode (
    UINT32                  ParseOpcode,
    ACPI_PARSE_OBJECT       *Op);

ACPI_PARSE_OBJECT *
TrCreateNode (
    UINT32                  ParseOpcode,
    UINT32                  NumChildren,
    ...);

ACPI_PARSE_OBJECT *
TrCreateLeafNode (
    UINT32                  ParseOpcode);

ACPI_PARSE_OBJECT *
TrCreateNullTarget (
    void);

ACPI_PARSE_OBJECT *
TrCreateAssignmentNode (
    ACPI_PARSE_OBJECT       *Target,
    ACPI_PARSE_OBJECT       *Source);

ACPI_PARSE_OBJECT *
TrCreateTargetOperand (
    ACPI_PARSE_OBJECT       *OriginalOp,
    ACPI_PARSE_OBJECT       *ParentOp);

ACPI_PARSE_OBJECT *
TrCreateValuedLeafNode (
    UINT32                  ParseOpcode,
    UINT64                  Value);

ACPI_PARSE_OBJECT *
TrCreateConstantLeafNode (
    UINT32                  ParseOpcode);

ACPI_PARSE_OBJECT *
TrLinkChildren (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  NumChildren,
    ...);

void
TrSetEndLineNumber (
    ACPI_PARSE_OBJECT       *Op);

void
TrSetCurrentFilename (
    ACPI_PARSE_OBJECT       *Op);

void
TrWalkTree (
    void);

ACPI_PARSE_OBJECT *
TrLinkPeerNode (
    ACPI_PARSE_OBJECT       *Op1,
    ACPI_PARSE_OBJECT       *Op2);

ACPI_PARSE_OBJECT *
TrLinkChildNode (
    ACPI_PARSE_OBJECT       *Op1,
    ACPI_PARSE_OBJECT       *Op2);

ACPI_PARSE_OBJECT *
TrSetNodeFlags (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Flags);

ACPI_PARSE_OBJECT *
TrSetNodeAmlLength (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Length);

ACPI_PARSE_OBJECT *
TrLinkPeerNodes (
    UINT32                  NumPeers,
    ...);


/*
 * aslfiles - File I/O support
 */
void
FlAddIncludeDirectory (
    char                    *Dir);

char *
FlMergePathnames (
    char                    *PrefixDir,
    char                    *FilePathname);

void
FlOpenIncludeFile (
    ACPI_PARSE_OBJECT       *Op);

void
FlFileError (
    UINT32                  FileId,
    UINT8                   ErrorId);

UINT32
FlGetFileSize (
    UINT32                  FileId);

ACPI_STATUS
FlReadFile (
    UINT32                  FileId,
    void                    *Buffer,
    UINT32                  Length);

void
FlWriteFile (
    UINT32                  FileId,
    void                    *Buffer,
    UINT32                  Length);

void
FlSeekFile (
    UINT32                  FileId,
    long                    Offset);

void
FlCloseFile (
    UINT32                  FileId);

void
FlPrintFile (
    UINT32                  FileId,
    char                    *Format,
    ...);

void
FlDeleteFile (
    UINT32                  FileId);

void
FlSetLineNumber (
    UINT32                  LineNumber);

void
FlSetFilename (
    char                    *Filename);

ACPI_STATUS
FlOpenInputFile (
    char                    *InputFilename);

ACPI_STATUS
FlOpenAmlOutputFile (
    char                    *InputFilename);

ACPI_STATUS
FlOpenMiscOutputFiles (
    char                    *InputFilename);

/*
 * aslhwmap - hardware map summary
 */
void
MpEmitMappingInfo (
    void);


/*
 * asload - load namespace in prep for cross reference
 */
ACPI_STATUS
LdLoadNamespace (
    ACPI_PARSE_OBJECT       *RootOp);


/*
 * asllookup - namespace lookup functions
 */
void
LkFindUnreferencedObjects (
    void);

/*
 * aslhelp - help screens
 */
void
Usage (
    void);

void
AslFilenameHelp (
    void);

void
AslDisassemblyHelp (
    void);


/*
 * aslnamesp - namespace output file generation
 */
ACPI_STATUS
NsDisplayNamespace (
    void);

void
NsSetupNamespaceListing (
    void                    *Handle);

/*
 * asloptions - command line processing
 */
int
AslCommandLine (
    int                     argc,
    char                    **argv);

/*
 * aslxref - namespace cross reference
 */
ACPI_STATUS
XfCrossReferenceNamespace (
    void);


/*
 * aslxrefout
 */
void
OtPrintHeaders (
    char                    *Message);

void
OtCreateXrefFile (
    void);

void
OtXrefWalkPart1 (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    ASL_METHOD_INFO         *MethodInfo);


/*
 * aslutils - common compiler utilites
 */
void
DbgPrint (
    UINT32                  Type,
    char                    *Format,
    ...);

/* Type values for above */

#define ASL_DEBUG_OUTPUT    0
#define ASL_PARSE_OUTPUT    1
#define ASL_TREE_OUTPUT     2

UINT8
UtIsBigEndianMachine (
    void);

BOOLEAN
UtQueryForOverwrite (
    char                    *Pathname);

void
UtDumpStringOp (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level);

void
UtDumpIntegerOp (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    UINT32                  IntegerLength);

void
UtDumpBasicOp (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level);

void
UtDisplaySupportedTables (
    void);

void
UtDisplayConstantOpcodes (
    void);

UINT8
UtBeginEvent (
    char                    *Name);

void
UtEndEvent (
    UINT8                   Event);

void *
UtLocalCalloc (
    UINT32                  Size);

void
UtDisplaySummary (
    UINT32                  FileId);

void
UtConvertByteToHex (
    UINT8                   RawByte,
    UINT8                   *Buffer);

void
UtConvertByteToAsmHex (
    UINT8                   RawByte,
    UINT8                   *Buffer);

char *
UtGetOpName (
    UINT32                  ParseOpcode);

void
UtSetParseOpName (
    ACPI_PARSE_OBJECT       *Op);

char *
UtStringCacheCalloc (
    UINT32                  Length);

void
UtExpandLineBuffers (
    void);

void
UtFreeLineBuffers (
    void);

ACPI_STATUS
UtInternalizeName (
    char                    *ExternalName,
    char                    **ConvertedName);

void
UtAttachNamepathToOwner (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_PARSE_OBJECT       *NameNode);

ACPI_PARSE_OBJECT *
UtCheckIntegerRange (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  LowValue,
    UINT32                  HighValue);

UINT64
UtDoConstant (
    char                    *String);


/*
 * asluuid - UUID support
 */
ACPI_STATUS
AuValidateUuid (
    char                    *InString);

ACPI_STATUS
AuConvertUuidToString (
    char                    *UuIdBuffer,
    char                    *OutString);

/*
 * aslresource - Resource template generation utilities
 */
void
RsSmallAddressCheck (
    UINT8                   Type,
    UINT32                  Minimum,
    UINT32                  Maximum,
    UINT32                  Length,
    UINT32                  Alignment,
    ACPI_PARSE_OBJECT       *MinOp,
    ACPI_PARSE_OBJECT       *MaxOp,
    ACPI_PARSE_OBJECT       *LengthOp,
    ACPI_PARSE_OBJECT       *AlignOp,
    ACPI_PARSE_OBJECT       *Op);

void
RsLargeAddressCheck (
    UINT64                  Minimum,
    UINT64                  Maximum,
    UINT64                  Length,
    UINT64                  Granularity,
    UINT8                   Flags,
    ACPI_PARSE_OBJECT       *MinOp,
    ACPI_PARSE_OBJECT       *MaxOp,
    ACPI_PARSE_OBJECT       *LengthOp,
    ACPI_PARSE_OBJECT       *GranOp,
    ACPI_PARSE_OBJECT       *Op);

UINT16
RsGetStringDataLength (
    ACPI_PARSE_OBJECT       *InitializerOp);

ASL_RESOURCE_NODE *
RsAllocateResourceNode (
    UINT32                  Size);

void
RsCreateResourceField (
    ACPI_PARSE_OBJECT       *Op,
    char                    *Name,
    UINT32                  ByteOffset,
    UINT32                  BitOffset,
    UINT32                  BitLength);

void
RsSetFlagBits (
    UINT8                   *Flags,
    ACPI_PARSE_OBJECT       *Op,
    UINT8                   Position,
    UINT8                   DefaultBit);

void
RsSetFlagBits16 (
    UINT16                  *Flags,
    ACPI_PARSE_OBJECT       *Op,
    UINT8                   Position,
    UINT8                   DefaultBit);

ACPI_PARSE_OBJECT *
RsCompleteNodeAndGetNext (
    ACPI_PARSE_OBJECT       *Op);

void
RsCheckListForDuplicates (
    ACPI_PARSE_OBJECT       *Op);

ASL_RESOURCE_NODE *
RsDoOneResourceDescriptor (
    ASL_RESOURCE_INFO       *Info,
    UINT8                   *State);

/* Values for State above */

#define ACPI_RSTATE_NORMAL              0
#define ACPI_RSTATE_START_DEPENDENT     1
#define ACPI_RSTATE_DEPENDENT_LIST      2

UINT32
RsLinkDescriptorChain (
    ASL_RESOURCE_NODE       **PreviousRnode,
    ASL_RESOURCE_NODE       *Rnode);

void
RsDoResourceTemplate (
    ACPI_PARSE_OBJECT       *Op);


/*
 * aslrestype1 - Miscellaneous Small descriptors
 */
ASL_RESOURCE_NODE *
RsDoEndTagDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoEndDependentDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoMemory24Descriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoMemory32Descriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoMemory32FixedDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoStartDependentDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoStartDependentNoPriDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoVendorSmallDescriptor (
    ASL_RESOURCE_INFO       *Info);


/*
 * aslrestype1i - I/O-related Small descriptors
 */
ASL_RESOURCE_NODE *
RsDoDmaDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoFixedDmaDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoFixedIoDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoIoDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoIrqDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoIrqNoFlagsDescriptor (
    ASL_RESOURCE_INFO       *Info);


/*
 * aslrestype2 - Large resource descriptors
 */
ASL_RESOURCE_NODE *
RsDoInterruptDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoVendorLargeDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoGeneralRegisterDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoGpioIntDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoGpioIoDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoI2cSerialBusDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoSpiSerialBusDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoUartSerialBusDescriptor (
    ASL_RESOURCE_INFO       *Info);

/*
 * aslrestype2d - DWord address descriptors
 */
ASL_RESOURCE_NODE *
RsDoDwordIoDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoDwordMemoryDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoDwordSpaceDescriptor (
    ASL_RESOURCE_INFO       *Info);


/*
 * aslrestype2e - Extended address descriptors
 */
ASL_RESOURCE_NODE *
RsDoExtendedIoDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoExtendedMemoryDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoExtendedSpaceDescriptor (
    ASL_RESOURCE_INFO       *Info);


/*
 * aslrestype2q - QWord address descriptors
 */
ASL_RESOURCE_NODE *
RsDoQwordIoDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoQwordMemoryDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoQwordSpaceDescriptor (
    ASL_RESOURCE_INFO       *Info);


/*
 * aslrestype2w - Word address descriptors
 */
ASL_RESOURCE_NODE *
RsDoWordIoDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoWordSpaceDescriptor (
    ASL_RESOURCE_INFO       *Info);

ASL_RESOURCE_NODE *
RsDoWordBusNumberDescriptor (
    ASL_RESOURCE_INFO       *Info);


/*
 * Entry to data table compiler subsystem
 */
ACPI_STATUS
DtDoCompile(
    void);

ACPI_STATUS
DtCreateTemplates (
    char                    **argv);

#endif /*  __ASLCOMPILER_H */
