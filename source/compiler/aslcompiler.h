
/******************************************************************************
 *
 * Module Name: aslcompiler.h - common include file
 *              $Revision: 1.12 $
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


#define CompilerId                              "ACPI Component Architecture ASL Compiler"
#define CompilerName                            "iasl"
#define Version                                 "X202"




typedef struct asl_method_info
{
    UINT8                   NumArguments;
    UINT8                   LocalInitialized[8];
    UINT32                  NumReturnNoValue;
    UINT32                  NumReturnWithValue;
    struct asl_method_info  *Next;

} ASL_METHOD_INFO;

typedef struct asl_analysis_walk_info
{
    ASL_METHOD_INFO         *MethodStack;

} ASL_ANALYSIS_WALK_INFO;



/*
 * Macros
 */
#define ASL_OFFSET_OF(s,m)          ((UINT32) &(((s *)0)->m))
#define ASL_RESDESC_OFFSET(m)       ASL_OFFSET_OF (ASL_RESOURCE_DESC, m)
#define ASL_GET_CHILD_NODE(a)       (a)->Child
#define ASL_GET_PEER_NODE(a)        (a)->Peer




#define ASL_PARSE_OPCODE_BASE       ACCESSAS        /* First Lex type */   


/* TBD: Is this a real opcode? */
#define AML_CONCAT_TPL_OP           (UINT16) 0x00FE


/* Internal opcodes */

#define AML_RAW_DATA_BYTE           (UINT16) 0xAA01
#define AML_RAW_DATA_WORD           (UINT16) 0xAA02
#define AML_RAW_DATA_DWORD          (UINT16) 0xAA04
#define AML_RAW_DATA_QWORD          (UINT16) 0xAA08
#define AML_RAW_DATA_BUFFER         (UINT16) 0xAA0B

#define AML_PACKAGE_LENGTH          (UINT16) 0xAA10

#define AML_UNASSIGNED_OPCODE       (UINT16) 0xEEEE
#define AML_DEFAULT_ARG_OP          (UINT16) 0xDDDD

#define NODE_VISITED                0x01
#define NODE_AML_PACKAGE            0x02
#define NODE_IS_TARGET              0x04
#define NODE_IS_RESOURCE_DESC       0x08
#define NODE_IS_RESOURCE_FIELD      0x10

#define ASL_WALK_VISIT_DOWNWARD     0x01
#define ASL_WALK_VISIT_UPWARD       0x02
#define ASL_WALK_VISIT_TWICE        0x03






#define OP_TABLE_ENTRY(a,b,c)        {b,a,c}

typedef struct asl_mapping_entry
{
    UINT32                  Value;
    UINT16                  AmlOpcode;
    UINT8                   Flags;

} ASL_MAPPING_ENTRY;

typedef union asl_node_value
{
    UINT64                  Integer;        /* Generic integer is largest integer */
    UINT64                  Integer64;
    UINT32                  Integer32;
    UINT16                  Integer16;
    UINT8                   Integer8;
    void                    *Pointer;
    char                    *String;

} ASL_NODE_VALUE;

typedef struct asl_parse_node
{
    struct asl_parse_node   *Parent;
    struct asl_parse_node   *Peer;
    struct asl_parse_node   *Child;
    ACPI_NAMESPACE_NODE     *NsNode;
    union asl_node_value    Value;
    char                    *ExternalName;
    char                    *Namepath;
    UINT32                  LineNumber;
    UINT16                  AmlOpcode;
    UINT16                  ParseOpcode;
    UINT32                  AmlLength;
    UINT32                  AmlSubtreeLength;
    UINT8                   AmlOpcodeLength;
    UINT8                   AmlPkgLenBytes;
    UINT8                   Flags;
    char                    ParseOpName[12];
    char                    AmlOpName[12];

} ASL_PARSE_NODE;


typedef struct asl_walk_info
{
    ASL_PARSE_NODE          **NodePtr;
    UINT32                  *LevelPtr;

} ASL_WALK_INFO;


typedef
void (*ASL_WALK_CALLBACK) (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context);



/*
 * Global variables.  Declared in aslmain.c only
 */

#ifdef _DECLARE_GLOBALS
#define EXTERN
#define INIT_GLOBAL(a,b)        a=b
#else
#define EXTERN                  extern
#define INIT_GLOBAL(a,b)        a
#endif

extern int                      optind;
extern char                     *optarg;
extern FILE                     *AslCompilerin;
extern int                      AslCompilerparse(void);
extern int                      AslCompilerdebug;
extern ASL_MAPPING_ENTRY        AslKeywordMapping[];
extern int                      yydebug;



/* Source code buffers and pointers for error reporting */

EXTERN int                      INIT_GLOBAL (Gbl_CurrentColumn, 0);
EXTERN int                      INIT_GLOBAL (Gbl_CurrentLineNumber, 1);
EXTERN char                     Gbl_CurrentLineBuffer[256];
EXTERN char                     INIT_GLOBAL (*Gbl_LineBufPtr, Gbl_CurrentLineBuffer);

/* Option flags */

EXTERN BOOLEAN                  INIT_GLOBAL (Gbl_DebugFlag, FALSE);
EXTERN BOOLEAN                  INIT_GLOBAL (Gbl_ListingFlag, FALSE);

/* Files */

EXTERN char                     INIT_GLOBAL (*Gbl_InputFilename, NULL);
EXTERN char                     INIT_GLOBAL (*Gbl_OutputFilename, NULL);
EXTERN char                     INIT_GLOBAL (*Gbl_ListingFilename, NULL);
EXTERN char                     INIT_GLOBAL (*Gbl_DebugFilename, NULL);
EXTERN FILE                     *Gbl_AslInputFile;
EXTERN FILE                     *Gbl_OutputAmlFile;
EXTERN FILE                     *Gbl_DebugFile;
EXTERN FILE                     *Gbl_ListingFile;

/* Statistics */

EXTERN UINT32                   INIT_GLOBAL (InputChars, 0);
EXTERN UINT32                   INIT_GLOBAL (TotalKeywords, 0);
EXTERN UINT32                   INIT_GLOBAL (TotalNamedObjects, 0);
EXTERN UINT32                   INIT_GLOBAL (TotalExecutableOpcodes, 0);
EXTERN UINT32                   INIT_GLOBAL (ErrorCount, 0);
EXTERN UINT32                   INIT_GLOBAL (WarningCount, 0);

/* Misc */


EXTERN ASL_PARSE_NODE           INIT_GLOBAL (*RootNode, NULL);
EXTERN ACPI_TABLE_HEADER        TableHeader;
EXTERN UINT32                   INIT_GLOBAL (Gbl_TableLength, 0);



#define ASL_ERROR_PREFIX        1000
#define ASL_WARNING_PREFIX      2000

typedef enum 
{
    ASL_WARNING_BUFFER_LENGTH = 0,
    ASL_WARNING_PACKAGE_LENGTH,
    ASL_WARNING_RETURN_TYPES,
    ASL_WARNING_NOT_FOUND,

} ASL_WARNING_IDS;

typedef enum 
{
    ASL_ERROR_MEMORY_ALLOCATION = 0,
    ASL_ERROR_INPUT_FILE_OPEN,
    ASL_ERROR_OUTPUT_FILENAME,
    ASL_ERROR_OUTPUT_FILE_OPEN,
    ASL_ERROR_LISTING_FILENAME,
    ASL_ERROR_LISTING_FILE_OPEN,
    ASL_ERROR_DEBUG_FILENAME,
    ASL_ERROR_DEBUG_FILE_OPEN,
    ASL_ERROR_ENCODING_LENGTH,
    ASL_ERROR_INVALID_PRIORITY,
    ASL_ERROR_INVALID_PERFORMANCE,
    ASL_ERROR_LOCAL_INIT,
    ASL_ERROR_ARG_INVALID,

} ASL_ERROR_IDS;


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


void
AslWarning (
    UINT32                  WarningId,
    UINT32                  LineNumber);

void
AslWarningMsg (
    UINT32                  WarningId,
    UINT32                  LineNumber,
    char                    *Message);

void
AslError (
    UINT32                  ErrorId,
    UINT32                  LineNumber);

void
AslErrorMsg (
    UINT32                  ErrorId,
    UINT32                  LineNumber,
    char                    *Message);

UINT32
CgSetOptimalIntegerSize (
    ASL_PARSE_NODE          *Node);

void
CgGenerateAmlLengths (
    ASL_PARSE_NODE          *Node);

void
CgGenerateAmlOpcode (
    ASL_PARSE_NODE          *Node);


ACPI_STATUS
CgOpenOutputFile (
    char                    *InputFilename);


void
CgAmlOpcodeWalk (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context);

void
CgAmlPackageLengthWalk (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context);

void
CgAmlWriteWalk (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context);


void
CgGenerateAmlOperands (
    ASL_PARSE_NODE          *Node);


void
CgGenerateOutput(
    void);

void
CgCloseTable (void);


void
CgWriteNode (
    ASL_PARSE_NODE          *Node);


void
CgDoResourceTemplate (
    ASL_PARSE_NODE          *Node);


void
TgWalkParseTree (
    UINT32                  Visitation,
    ASL_WALK_CALLBACK       DescendingCallback,
    ASL_WALK_CALLBACK       AscendingCallback,
    void                    *Context);


char *
TgAddNode (
    void                    *Thing);

ASL_PARSE_NODE *
_TgUpdateNode (
    UINT32                  ParseOpcode,
    ASL_PARSE_NODE          *Node);

char *
TgCreateNode (
    UINT32                  ParseOpcode,
    UINT32                  NumChildren,
    ...);

char *
TgCreateLeafNode (  
    UINT32                  ParseOpcode,
    void                    *Value);

void
TgWalkTree (void);


#define TgLinkPeerNode(a,b)      (char *)_TgLinkPeerNode ((ASL_PARSE_NODE *)(a),(ASL_PARSE_NODE *)(b))
#define TgLinkChildNode(a,b)     (char *)_TgLinkChildNode ((ASL_PARSE_NODE *)(a),(ASL_PARSE_NODE *)(b))
#define TgUpdateNode(a,b)        (char *)_TgUpdateNode (a,(ASL_PARSE_NODE *)(b))
#define TgSetNodeFlags(a,b)      (char *)_TgSetNodeFlags ((ASL_PARSE_NODE *)(a),(b))

ASL_PARSE_NODE *
_TgLinkPeerNode (
    ASL_PARSE_NODE          *Node1,
    ASL_PARSE_NODE          *Node2);

ASL_PARSE_NODE *
_TgLinkChildNode (
    ASL_PARSE_NODE          *Node1,
    ASL_PARSE_NODE          *Node2);

ASL_PARSE_NODE *
_TgSetNodeFlags (
    ASL_PARSE_NODE          *Node,
    UINT32                  Flags);

/* Analyze */

void
AnSemanticAnalysisWalkBegin (
    ASL_PARSE_NODE              *Node,
    UINT32                      Level,
    void                        *Context);

void
AnSemanticAnalysisWalkEnd (
    ASL_PARSE_NODE              *Node,
    UINT32                      Level,
    void                        *Context);

/* Load */

ACPI_STATUS
LdNamespace1Begin (
    ASL_PARSE_NODE              *PsNode,
    UINT32                      Level,
    void                        *Context);

ACPI_STATUS
LdNamespace1End (
    ASL_PARSE_NODE              *PsNode,
    UINT32                      Level,
    void                        *Context);

/* Lookup */

ACPI_STATUS
LkNamespaceLocateBegin (
    ASL_PARSE_NODE              *PsNode,
    UINT32                      Level,
    void                        *Context);

ACPI_STATUS
LkNamespaceLocateEnd (
    ASL_PARSE_NODE              *PsNode,
    UINT32                      Level,
    void                        *Context);

/* Utils */

void *
UtLocalCalloc (
    UINT32                  Size);


void *
UtLocalRealloc (
    void                    *Previous,
    UINT32                  Size);


void
UtPrintFormattedName (
    UINT16                  ParseOpcode,
    UINT32                  Level);

ACPI_STATUS
UtOpenAllFiles (
    char                    *InputFilename);

void
UtDisplaySummary (
    void);


UINT8
UtHexCharToValue (
    int                     hc);


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


/* Find */

void
LnAdjustLengthToRoot (
    ASL_PARSE_NODE          *PsNode,
    UINT32                  LengthDelta);


#endif

