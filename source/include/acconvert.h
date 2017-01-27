/******************************************************************************
 *
 * Module Name: acapps - common include for ACPI applications/tools
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2016, Intel Corp.
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

#ifndef _ACCONVERT
#define _ACCONVERT

/* Definitions for comment state */

#define ASL_REGCOMMENT        1
#define ASL_INLINECOMMENT     2
#define ASL_OPENPARENCOMMENT  3
#define ASL_CLOSE_PARENCOMMENT 4
#define ASL_CLOSE_BRACECOMMENT 5

/* Definitions for comment table entry */

#define ASL_NEWLINE    '\n'
#define ASL_OpenParen  '('
#define ASL_CLOSE_PAREN ')'
#define ASL_COMMA      ','
#define ASL_OPENBRACE  '{'
#define ASL_CLOSE_BRACE '}'
#define ASL_WHITESPACE ' '


/* Definitions for comment print function*/

#define AML_REGCOMMENT        1
#define AML_INLINECOMMENT     2
#define AML_ENDNODECOMMENT    3
#define AML_NAMECOMMENT       4
#define AML_CLOSE_BRACECOMMENT 5
#define AML_ENDBLKCOMMENT     6
#define AML_INCLUDECOMMENT    7


#ifdef ACPI_ASL_COMPILER
/*
 * cvcompiler
 */
void
CvProcessComment (
    ASL_COMMENT_STATE       CurrentState,
    char                    *StringBuffer,
    int                     c1);

void
CvProcessCommentType2 (
    ASL_COMMENT_STATE       CurrentState,
    char                    *StringBuffer);

UINT32
CvCalculateCommentLengths(
   ACPI_PARSE_OBJECT        *Op);

char*
CvChangeFileExt (
   char*                    Filename,
   char*                    FileExt);

void
CvProcessCommentState (
    char                    input);

char*
CvAppendInlineComment (
    char                    *InlineComment,
    char                    *ToAdd);

void
CvAddToCommentList (
    char*                   ToAdd);

void
CvPlaceComment (
    UINT8                   Type,
    char                    *CommentString);

UINT32
CvParseOpBlockType (
    ACPI_PARSE_OBJECT       *Op);

ACPI_COMMENT_LIST_NODE*
CvCommentNodeCalloc (
    void);

void
CgWriteAmlDefBlockComment (
    ACPI_PARSE_OBJECT       *Op);

void
CgWriteOneAmlComment (
    ACPI_PARSE_OBJECT       *Op,
    char*                   CommentToPrint,
    UINT8                   InputOption);

void
CgWriteAmlComment (
    ACPI_PARSE_OBJECT       *Op);


/*
 * cvparser
 */
void
CvInitFileTree (
    ACPI_TABLE_HEADER       *Table,
    UINT8                   *AmlStart,
    UINT32                  AmlLength);

void
CvClearOpComments (
    ACPI_PARSE_OBJECT       *Op);

ACPI_FILE_NODE*
CvFilenameExists (
    char                    *Filename,
    ACPI_FILE_NODE           *Head);

ACPI_FILE_NODE*
CvFileAddressLookup (
    char                    *Address,
    ACPI_FILE_NODE          *Head);

void
CvFileLabelNode (
    ACPI_PARSE_OBJECT       *Op);

void
CvAddToFileTree (
    char                    *Filename,
    char                    *PreviousFilename);

void
CvSetFileParent (
    char                    *ChildFile,
    char                    *ParentFile);

void
CvCaptureListComments (
    ACPI_PARSE_STATE        *ParserState,
    ACPI_COMMENT_LIST_NODE  *ListHead,
    ACPI_COMMENT_LIST_NODE  *ListTail);

void
CvCaptureJustComments (
    ACPI_PARSE_STATE        *ParserState);

void
CvCaptureComments (
    ACPI_WALK_STATE         *WalkState);

void
CvTransferComments (
    ACPI_PARSE_OBJECT       *Op);

/*
 * cvdisasm
 */
void
CvSwitchFiles (
    UINT32                  level,
    ACPI_PARSE_OBJECT       *op);

BOOLEAN
CvFileHasSwitched (
    ACPI_PARSE_OBJECT       *Op);


void
CvCloseParenWriteComment (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level);

void
CvCloseBraceWriteComment (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level);

void
CvPrintOneCommentList (
    ACPI_COMMENT_LIST_NODE  *CommentList,
    UINT32                  Level);

void
CvPrintOneCommentType (
    ACPI_PARSE_OBJECT       *Op,
    UINT8                   CommentType,
    char*                   EndStr,
    UINT32                  Level);


#endif

#endif /* _ACCONVERT */