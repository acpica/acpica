
/******************************************************************************
 *
 * Module Name: aslcompiler.h - common include file
 *              $Revision: 1.39 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, Intel Corp.
 * All rights reserved.
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


#ifndef __ASLCOMPILER_H
#define __ASLCOMPILER_H

#pragma warning(disable:4103)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define ACPI_USE_SYSTEM_CLIBRARY
#define ACPI_DEBUG
#define ACPI_APPLICATION


#include "acpi.h"
#include "acdebug.h"
#include "asltypes.h"
#include "aslglobal.h"


/* TBD: Move to definition of NAMESPACE NODE */

#define ANOBJ_METHOD_NO_RETVAL          0x20
#define ANOBJ_METHOD_SOME_NO_RETVAL     0x40


/*
 * Compiler versions and names
 */

#define CompilerVersion             "X207"
#define CompilerCreatorRevision     0x00020206  /* Acpi 2.0, Version# */

#define CompilerId                  "Intel ACPI Component Architecture ASL Compiler"
#define CompilerCopyright           "Copyright (C) 2000 Intel Corporation"
#define CompilerCompliance          "ACPI 2.0"
#define CompilerName                "iasl"
#define CompilerCreatorId           "INTL"


/* Configuration constants */

#define ASL_MAX_ERROR_COUNT         200

/*
 * Macros
 */

#define ASL_OFFSET_OF(s,m)          ((UINT32) &(((s *)0)->m))
#define ASL_RESDESC_OFFSET(m)       ASL_OFFSET_OF (ASL_RESOURCE_DESC, m)
#define ASL_PTR_DIFF(a,b)           ((UINT8 *)(b) - (UINT8 *)(a))
#define ASL_PTR_ADD(a,b)            ((UINT8 *)(a) = ((UINT8 *)(a) + (b)))
#define ASL_GET_CHILD_NODE(a)       (a)->Child
#define ASL_GET_PEER_NODE(a)        (a)->Peer
#define OP_TABLE_ENTRY(a,b,c)       {b,a,c}


#define ASL_PARSE_OPCODE_BASE       ACCESSAS        /* First Lex type */


/* Internal AML opcodes */

#define AML_RAW_DATA_BYTE           (UINT16) 0xAA01 /* write one raw byte */
#define AML_RAW_DATA_WORD           (UINT16) 0xAA02 /* write 2 raw bytes */
#define AML_RAW_DATA_DWORD          (UINT16) 0xAA04 /* write 4 raw bytes */
#define AML_RAW_DATA_QWORD          (UINT16) 0xAA08 /* write 8 raw bytes */
#define AML_RAW_DATA_BUFFER         (UINT16) 0xAA0B /* raw buffer with length */
#define AML_RAW_DATA_CHAIN          (UINT16) 0xAA0C /* chain of raw buffers */
#define AML_PACKAGE_LENGTH          (UINT16) 0xAA10
#define AML_UNASSIGNED_OPCODE       (UINT16) 0xEEEE
#define AML_DEFAULT_ARG_OP          (UINT16) 0xDDDD


/* TBD: Is this a real opcode? */

#define AML_CONCAT_TPL_OP           (UINT16) 0x00FE


/*******************************************************************************
 *
 * Compiler prototypes
 *
 ******************************************************************************/


void
end_stmt (void);


/* parser */

int
AslCompilerparse( void);

ASL_PARSE_NODE *
AslDoError (void);

int
AslCompilererror(char* s);

int
AslCompilerlex();

char
*AslCompilertext;

/* aslmain */

void
AslCompilerSignon (
    FILE                    *Where);

void
AslCompilerFileHeader (
    FILE                    *Where);

void
AslDoSourceOutputFile (
    char                    *Buffer);

int
AslPopInputFileStack (void);

void
AslPushInputFileStack (
    FILE                    *InputFile,
    char                    *Filename);

int
AslCompilererror(char *s);

int
DbgPrint (
    char                    *Format,
    ...);

int
getopt (
    int                     argc,
    char                    **argv,
    char                    *opts);

void
ErrorContext (void);

/* aslcompile */

int
CmDoCompile (void);

void
CmCleanupAndExit (void);


/* aslerror */

void
AslError (
    UINT8                   Level,
    UINT8                   MessageId,
    ASL_PARSE_NODE          *Node,
    char                    *ExtraMessage);

ASL_ERROR_MSG *
AslCommonError (
    UINT8                   Level,
    UINT8                   MessageId,
    UINT32                  CurrentLineNumber,
    UINT32                  LogicalLineNumber,
    char                    *Filename,
    char                    *ExtraMessage);

void
AePrintException (
    FILE                    *Where,
    ASL_ERROR_MSG           *Enode);

void
AePrintErrorLog (
    FILE                    *Where);


/* asllisting */

void
LsWriteListingHexBytes (
    char                    *Buffer,
    UINT32                  Length);

void
LsWriteNodeToListing (
    ASL_PARSE_NODE          *Node);

void
LsFlushListingBuffer (void);

void
LsFinishSourceListing (void);

void
LsDoHexOutput (void);

void
LsPushNode (
    char                    *Filename);

ASL_LISTING_NODE *
LsPopNode (void);


/*
 * aslopcodes - generate AML opcodes
 */


void
OpcAmlOpcodeWalk (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context);

void
OpcGenerateAmlOpcode (
    ASL_PARSE_NODE          *Node);

UINT32
OpcSetOptimalIntegerSize (
    ASL_PARSE_NODE          *Node);


/*
 * asloperands - generate AML operands for the AML opcodes
 */

void
OpnGenerateAmlOperands (
    ASL_PARSE_NODE          *Node);


/*
 * aslresource - resource template generation
 */

void
RsDoResourceTemplate (
    ASL_PARSE_NODE          *Node);


void
CgGenerateAmlOutput (void);
void
CgGenerateAmlLengths (
    ASL_PARSE_NODE          *Node);

ACPI_STATUS
CgOpenOutputFile (
    char                    *InputFilename);


/* asllength */

void
LnPackageLengthWalk (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context);

void
LnInitLengthsWalk (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context);


void
CgAmlWriteWalk (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context);


void
CgGenerateOutput(
    void);

void
CgCloseTable (void);


void
CgWriteNode (
    ASL_PARSE_NODE          *Node);


/*
 * asltree - parse tree support
 */

void
TrWalkParseTree (
    UINT32                  Visitation,
    ASL_WALK_CALLBACK       DescendingCallback,
    ASL_WALK_CALLBACK       AscendingCallback,
    void                    *Context);

/* Values for "Visitation" parameter above */

#define ASL_WALK_VISIT_DOWNWARD     0x01
#define ASL_WALK_VISIT_UPWARD       0x02
#define ASL_WALK_VISIT_TWICE        0x03


char *
TrAddNode (
    void                    *Thing);

ASL_PARSE_NODE *
TrUpdateNode (
    UINT32                  ParseOpcode,
    ASL_PARSE_NODE          *Node);

ASL_PARSE_NODE *
TrCreateNode (
    UINT32                  ParseOpcode,
    UINT32                  NumChildren,
    ...);

ASL_PARSE_NODE *
TrCreateLeafNode (
    UINT32                  ParseOpcode);

ASL_PARSE_NODE *
TrCreateValuedLeafNode (
    UINT32                  ParseOpcode,
    ACPI_INTEGER            Value);

ASL_PARSE_NODE *
TrLinkChildren (
    ASL_PARSE_NODE          *Node,
    UINT32                  NumChildren,
    ...);

void
TrSetEndLineNumber (
    ASL_PARSE_NODE          *Node);

void
TrWalkTree (void);

ASL_PARSE_NODE *
TrLinkPeerNode (
    ASL_PARSE_NODE          *Node1,
    ASL_PARSE_NODE          *Node2);

ASL_PARSE_NODE *
TrLinkChildNode (
    ASL_PARSE_NODE          *Node1,
    ASL_PARSE_NODE          *Node2);

ASL_PARSE_NODE *
TrSetNodeFlags (
    ASL_PARSE_NODE          *Node,
    UINT32                  Flags);

ASL_PARSE_NODE *
TrLinkPeerNodes (
    UINT32                  NumPeers,
    ...);


/* Analyze */

void
AnSemanticAnalysisWalkBegin (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context);

void
AnSemanticAnalysisWalkEnd (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context);

/*
 * aslfiles - File I/O support
 */

void
FlOpenIncludeFile (
    ASL_PARSE_NODE          *Node);

ACPI_STATUS
FlOpenInputFile (
    char                    *InputFilename);

ACPI_STATUS
FlOpenAmlOutputFile (
    char                    *InputFilename);

ACPI_STATUS
FlOpenMiscOutputFiles (
    char                    *InputFilename);

void
FlCloseListingFile (void);

void
FlCloseSourceOutputFile (void);

void
FlCloseHexOutputFile (void);


/* Load */

ACPI_STATUS
LdLoadNamespace (void);


ACPI_STATUS
LdNamespace1Begin (
    ASL_PARSE_NODE          *PsNode,
    UINT32                  Level,
    void                    *Context);

ACPI_STATUS
LdNamespace1End (
    ASL_PARSE_NODE          *PsNode,
    UINT32                  Level,
    void                    *Context);


/* Lookup */

ACPI_STATUS
LkCrossReferenceNamespace (void);

ACPI_STATUS
LkNamespaceLocateBegin (
    ASL_PARSE_NODE          *PsNode,
    UINT32                  Level,
    void                    *Context);

ACPI_STATUS
LkNamespaceLocateEnd (
    ASL_PARSE_NODE          *PsNode,
    UINT32                  Level,
    void                    *Context);

ACPI_STATUS
LsDisplayNamespace (void);


/* Utils */

void *
UtLocalCalloc (
    UINT32                  Size);

void
UtPrintFormattedName (
    UINT16                  ParseOpcode,
    UINT32                  Level);

void
UtDisplaySummary (
    FILE                    *Where);

UINT8
UtHexCharToValue (
    int                     hc);

void
UtConvertByteToHex (
    UINT8                   RawByte,
    UINT8                   *Buffer);

char *
UtGetOpName (
    UINT32                  ParseOpcode);

ASL_PARSE_NODE  *
UtGetArg (
    ASL_PARSE_NODE          *Op,
    UINT32                  Argn);

void
UtAttachNamepathToOwner (
    ASL_PARSE_NODE          *Node,
    ASL_PARSE_NODE          *NameNode);

ASL_PARSE_NODE *
UtCheckIntegerRange (
    ASL_PARSE_NODE          *Node,
    UINT32                  LowValue,
    UINT32                  HighValue);

ACPI_INTEGER
UtStrtoul64 (
    NATIVE_CHAR             *String,
    NATIVE_CHAR             **Terminator,
    UINT32                  Base);


/* Find */

void
LnAdjustLengthToRoot (
    ASL_PARSE_NODE          *PsNode,
    UINT32                  LengthDelta);


#endif /*  __ASLCOMPILER_H */

