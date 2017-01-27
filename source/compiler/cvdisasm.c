/******************************************************************************
 *
 * Module Name: cvcompiler - ASL-/ASL+ converter functions
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

#include "aslcompiler.h"
#include "acparser.h"
#include "amlcode.h"
#include "acdebug.h"
#include "acconvert.h"


/*******************************************************************************
 *
 * FUNCTION:    CvPrintOneCommentList
 *
 * PARAMETERS:  CommentList
 *              Level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prints all commentss within a given list.
 *
 ******************************************************************************/

void
CvPrintOneCommentList (
    ACPI_COMMENT_LIST_NODE  *CommentList,
    UINT32                  Level)
{
    ACPI_COMMENT_LIST_NODE  *Temp = CommentList;
    ACPI_COMMENT_LIST_NODE  *Prev;


    while (Temp)
    {
        Prev = Temp;
        if (Temp->Comment)
        {
            AcpiDmIndent(Level);
            AcpiOsPrintf("%s\n", Temp->Comment);
            Temp->Comment = NULL;
        }
        Temp = Temp->Next;
        AcpiOsFree (Prev);
    }
    CommentList = NULL;
}


/*******************************************************************************
 *
 * FUNCTION:    CvPrintOneCommentType
 *
 * PARAMETERS:  Op
 *              CommentType
 *              EndStr - String to print after printing the comment
 *              Level  - indentation level for comment lists.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prints all comments of CommentType within the given Op and
 *              clears the printed comment from the Op.
 *
 ******************************************************************************/

void
CvPrintOneCommentType (
    ACPI_PARSE_OBJECT       *Op,
    UINT8                   CommentType,
    char*                   EndStr,
    UINT32                  Level)
{
    switch (CommentType)
    {
    case AML_REGCOMMENT:
        CvPrintOneCommentList (Op->Common.CommentList, Level);
        Op->Common.CommentList = NULL;
        break;

    case AML_INLINECOMMENT:
        if (Op->Common.InlineComment)
        {
            AcpiOsPrintf ("%s", Op->Common.InlineComment);
            Op->Common.InlineComment = NULL;
        }
        break;

    case AML_ENDNODECOMMENT:
        if (Op->Common.EndNodeComment)
        {
            AcpiOsPrintf ("%s", Op->Common.EndNodeComment);
            Op->Common.EndNodeComment = NULL;
        }
        break;

    case AML_NAMECOMMENT:
        if (Op->Common.NameComment)
        {
            AcpiOsPrintf ("%s", Op->Common.NameComment);
            Op->Common.NameComment = NULL;
        }
        break;

    case AML_CLOSE_BRACECOMMENT:
        if (Op->Common.CloseBraceComment)
        {
            AcpiOsPrintf ("%s", Op->Common.CloseBraceComment);
            Op->Common.CloseBraceComment = NULL;
        }
        break;

    case AML_ENDBLKCOMMENT:
        CvPrintOneCommentList (Op->Common.EndBlkComment, Level);
        Op->Common.EndBlkComment = NULL;
        break;

    default:
        break;
    }

    if (EndStr &&
        ((CommentType == AML_REGCOMMENT) || (CommentType == AML_INLINECOMMENT) ||
         (CommentType == AML_ENDNODECOMMENT) || (CommentType == AML_NAMECOMMENT) ||
         (CommentType == AML_CLOSE_BRACECOMMENT)))
    {
        AcpiOsPrintf ("%s", EndStr);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CvCloseBraceWriteComment 
 *
 * PARAMETERS:  Op
 *              Level
 *
 * RETURN:      none
 *
 * DESCRIPTION: Print a colse brace } and any open brace comments associated
 *              with this parse object.
 *
 ******************************************************************************/

void
CvCloseBraceWriteComment(
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level)
{
    ACPI_COMMENT_LIST_NODE  *CommentNode = Op->Common.EndBlkComment;

    if (!Gbl_CaptureComments)
    {
        AcpiOsPrintf ("}");
        return;
    }

    while (CommentNode)
    {
        AcpiDmIndent (1);
        AcpiOsPrintf("%s\n", CommentNode->Comment);
        CommentNode->Comment = NULL;
        CommentNode = CommentNode->Next;
        AcpiDmIndent (Level);
    }

    AcpiOsPrintf ("}");

    if (Op->Common.CloseBraceComment!=NULL)
    {
        AcpiOsPrintf (" %s", Op->Common.CloseBraceComment);
        Op->Common.CloseBraceComment=NULL;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CvCloseParenWriteComment 
 *
 * PARAMETERS:  Op
 *              Level
 *
 * RETURN:      none
 *
 * DESCRIPTION: Print a closing paren ) and any end node comments associated
 *              with this parse object.
 *
 ******************************************************************************/

void
CvCloseParenWriteComment(
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level)
{
    ACPI_COMMENT_LIST_NODE  *CommentNode = Op->Common.EndBlkComment;


    if (!Gbl_CaptureComments)
    {
        AcpiOsPrintf (")");
        return;
    }

    /*
     * If this op has a BLOCK_BRACE, then output the comment when the 
     * disassembler calls CvCloseBraceWriteComment 
     */
    if ((AcpiDmBlockType (Op) & (BLOCK_PAREN)) &&
	!(AcpiDmBlockType (Op) & (BLOCK_BRACE)))
    {
        while (CommentNode)
        {
            AcpiDmIndent (Level);
            AcpiOsPrintf("%s\n", CommentNode->Comment);
            CommentNode->Comment = NULL;
            CommentNode = CommentNode->Next;
            if (!CommentNode)
            {
                AcpiDmIndent (Level);
            }
        }
    }

    AcpiOsPrintf (")");

    if (Op->Common.EndNodeComment)
    {
        AcpiOsPrintf ("%s", Op->Common.EndNodeComment);
        Op->Common.EndNodeComment=NULL;
    }
    else if ((Op->Common.Parent->Common.AmlOpcode == AML_IF_OP) &&
	     Op->Common.Parent->Common.EndNodeComment)
    {
        AcpiOsPrintf ("%s", Op->Common.Parent->Common.EndNodeComment);
        Op->Common.Parent->Common.EndNodeComment = NULL;
    }
} 

/*******************************************************************************
 *
 * FUNCTION:    CvFileHasSwitched
 *
 * PARAMETERS:  Op
 *
 * RETURN:      BOOLEAN
 *
 * DESCRIPTION: Determine whether if a file has switched.
 *              TRUE - file has switched. 
 *              FALSE - file has not switched.
 *
 ******************************************************************************/

BOOLEAN
CvFileHasSwitched(
    ACPI_PARSE_OBJECT       *Op)
{
    if (Op->Common.PsFilename && AcpiGbl_CurrentFilename
        && strcmp(Op->Common.PsFilename, AcpiGbl_CurrentFilename))
    {
        return TRUE;
    }
    return FALSE;
}


/*******************************************************************************
 *
 * FUNCTION:    CvSwitchFiles
 *
 * PARAMETERS:  Level - indentation level
 *              Op
 *
 * RETURN:      None
 *
 * DESCRIPTION: Switch the outputfile. 
 *
 ******************************************************************************/

void
CvSwitchFiles(
    UINT32                  Level,
    ACPI_PARSE_OBJECT       *Op)
{
    char                    *Filename = Op->Common.PsFilename;
    ACPI_FILE_NODE          *FNode;

    CvDbgPrint ("Switching from %s to %s\n", AcpiGbl_CurrentFilename, Filename);    
    FNode = CvFilenameExists (Filename, AcpiGbl_FileTreeRoot);
    if (FNode)
    {
        if (!FNode->IncludeWritten)
        {
            CvDbgPrint ("Writing include for %s within %s\n", FNode->Filename, FNode->Parent->Filename);
            AcpiOsRedirectOutput (FNode->Parent->File);
            CvPrintOneCommentList (FNode->IncludeComment, Level);
            AcpiDmIndent (Level);
            AcpiOsPrintf ("Include (\"%s\")\n", FNode->Filename);
            CvDbgPrint ("emitted the following: Include (\"%s\")\n", FNode->Filename);
            FNode->IncludeWritten = TRUE;
        }

        /*
         * If the previous file is a descendant of the current file,
         * make sure that Include statements from the current file
         * to the previous have been emitted.
         */

        while (FNode && FNode->Parent && strcmp (FNode->Filename, AcpiGbl_CurrentFilename))
        {
            if (!FNode->IncludeWritten)
            {
                CvDbgPrint ("Writing include for %s within %s\n", FNode->Filename, FNode->Parent->Filename);
                AcpiOsRedirectOutput (FNode->Parent->File);
                CvPrintOneCommentList (FNode->IncludeComment, Level);
                AcpiDmIndent (Level);
                AcpiOsPrintf ("Include (\"%s\")\n", FNode->Filename);
                CvDbgPrint ("emitted the following in %s: Include (\"%s\")\n", FNode->Parent->Filename, FNode->Filename);
                FNode->IncludeWritten = TRUE;
            }
            FNode = FNode->Parent;
        }
    }

    /* Redirect output to the argument */

    FNode = CvFilenameExists (Filename, AcpiGbl_FileTreeRoot);
    AcpiOsRedirectOutput (FNode->File);
    AcpiGbl_CurrentFilename = FNode->Filename;
}

