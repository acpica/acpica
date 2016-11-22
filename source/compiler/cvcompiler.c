/******************************************************************************
 *
 * Module Name: cvcompiler - ASL-/ASL+ converter functions
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

#include "aslcompiler.h"
#include "acapps.h"
#include "aslcompiler.y.h"


/*******************************************************************************
 *
 * FUNCTION:    CvCommentNodeCalloc
 *
 * PARAMETERS:  Length              - Size of buffer requested
 *
 * RETURN:      Pointer to the buffer. Aborts on allocation failure
 *
 * DESCRIPTION: Allocate a string buffer. Bypass the local
 *              dynamic memory manager for performance reasons (This has a
 *              major impact on the speed of the compiler.)
 *
 ******************************************************************************/

struct acpi_comment_list_node*
CvCommentNodeCalloc (
    void)
{
   ACPI_COMMENT_LIST_NODE *NewCommentNode =
       (ACPI_COMMENT_LIST_NODE*) UtLocalCalloc (sizeof(ACPI_COMMENT_LIST_NODE));
   NewCommentNode->Next = 0;
   return NewCommentNode;
}


/*
 * Note: this function has been copied from dmwalk.c from the disassembler. 
 * figure out what I need and find a way to incorporate this function into common
 * as the development of the feature progresses.
 */
/*******************************************************************************
 *
 * FUNCTION:    CvParseOpBlockType 
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      BlockType - not a block, parens, braces, or even both.
 *
 * DESCRIPTION: Type of block for this op (parens or braces)
 *
 ******************************************************************************/

UINT32
CvParseOpBlockType (
    ACPI_PARSE_OBJECT       *Op)
{
    if (!Op)
    {
        return (BLOCK_NONE);
    }

    switch (Op->Asl.ParseOpcode)
    {
    /*from aslprimaries.y */

    case PARSEOP_VAR_PACKAGE:
    case PARSEOP_BANKFIELD:
    case PARSEOP_BUFFER:
    case PARSEOP_CASE:
    case PARSEOP_DEVICE:
    case PARSEOP_FIELD:
    case PARSEOP_FOR:
    case PARSEOP_FUNCTION:
    case PARSEOP_IF:
    case PARSEOP_ELSEIF:
    case PARSEOP_INDEXFIELD:
    case PARSEOP_METHOD:
    case PARSEOP_POWERRESOURCE:
    case PARSEOP_PROCESSOR:
    case PARSEOP_DATABUFFER:
    case PARSEOP_SCOPE:
    case PARSEOP_SWITCH:
    case PARSEOP_THERMALZONE:
    case PARSEOP_WHILE:

    /* from aslresources.y */

    case PARSEOP_RESOURCETEMPLATE: /* optional parens */
    case PARSEOP_VENDORLONG:
    case PARSEOP_VENDORSHORT:
    case PARSEOP_INTERRUPT:
    case PARSEOP_IRQNOFLAGS:
    case PARSEOP_IRQ:
    case PARSEOP_GPIO_INT:
    case PARSEOP_GPIO_IO:
    case PARSEOP_DMA:

    /*from aslrules.y */

    case PARSEOP_DEFINITION_BLOCK:
        return (BLOCK_PAREN | BLOCK_BRACE);

    default:

        return (BLOCK_NONE);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CvChangeFileExt
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: For -ca option: change a file extension of a given filename to
 *              the given file extension.
 *
 ******************************************************************************/

char*
CvChangeFileExt(
   char*       Filename,
   char*       FileExt)
{
    char                    *Position;
    char                    *DirectoryPosition;
    char                    *NewFilename;


    NewFilename = UtStringCacheCalloc (strlen (Filename)); 
    strcpy (NewFilename, Filename);
    DirectoryPosition = strrchr (NewFilename, '/');
    Position = strrchr (NewFilename, '.');

    if (Position && (Position > DirectoryPosition))
    {
        /* Tack on the new suffix */

        Position++;
        *Position = 0;
        strcat (Position, FileExt);
    }
    else
    {
        /* No dot, add one and then the suffix */

        strcat (NewFilename, ".");
        strcat (NewFilename, FileExt);
    }

    return (NewFilename);
}

/*******************************************************************************
 *
 * FUNCTION:    CvProcessCommentState
 *
 * PARAMETERS:  char
 *
 * RETURN:      None
 *
 * DESCRIPTION: For -q option. Take the given input. If this character is 
 *              defined as a comment table entry, then update the state
 *              accordingly.
 *
 ******************************************************************************/

void
CvProcessCommentState (
    char                    input)
{

    if (input == ' ')
    {
        Gbl_CommentState.SpacesBefore++;
    }
    else
    {
        Gbl_CommentState.SpacesBefore = 0;
    }

    switch (input)
    {
        case ASL_NEWLINE:

            Gbl_CommentState.CommentType = ASL_REGCOMMENT;
            break;

        case ASL_WHITESPACE: 

            break;

        case ASL_OpenParen:

            Gbl_CommentState.CommentType = ASL_OPENPARENCOMMENT;
            break;

        case ASL_CLOSEPAREN:

            Gbl_CommentState.CommentType = ASL_CLOSEPARENCOMMENT;
            break;

        case ASL_OPENBRACE:

            Gbl_CommentState.CommentType = ASL_REGCOMMENT;
            Gbl_CommentState.ParsingParenBraceNode = NULL;
            CvDbgPrint ("========================================================End Parsing paren/Brace node!\n");
            break;

        case ASL_CLOSEBRACE:
            
            Gbl_CommentState.CommentType = ASL_CLOSEBRACECOMMENT;
            break;

        case ASL_COMMA:

            Gbl_CommentState.CommentType = ASL_INLINECOMMENT;
            break;

        default:

            Gbl_CommentState.CommentType = ASL_INLINECOMMENT;
            break;

    }
}


/*******************************************************************************
 *
 * FUNCTION:    CvAddToCommentList
 *
 * PARAMETERS:  toAdd              - Contains the comment to be inserted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Count keywords and put them into the line buffer
 *
 ******************************************************************************/

void
CvAddToCommentList (
    char*                   ToAdd)
{
   if (Gbl_Comment_List_Head)
   {
       Gbl_Comment_List_Tail->Next = CvCommentNodeCalloc ();
       Gbl_Comment_List_Tail = Gbl_Comment_List_Tail->Next;
   }
   else 
   {
       Gbl_Comment_List_Head = CvCommentNodeCalloc ();
       Gbl_Comment_List_Tail = Gbl_Comment_List_Head;
   }

   Gbl_Comment_List_Tail->Comment = ToAdd;
   
   return;
}

/*******************************************************************************
 *
 * FUNCTION:    CvAppendInlineComment
 *
 * PARAMETERS:  InlineComment      - Append to the end of this string.
 *              toAdd              - Contains the comment to be inserted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Concatenate
 *
 ******************************************************************************/

char*
CvAppendInlineComment (
    char                    *InlineComment,
    char                    *ToAdd)
{
    //CvDbgPrint ("Appending to current inline comment.\n");

    char*  Str  = NULL;
    UINT32 Size = 0;
    if (InlineComment==NULL)
    {
        return ToAdd;
    }


    Size = strlen (InlineComment);

    if (ToAdd != NULL)
    {
        Size += strlen (ToAdd);
    }


    Str = UtStringCacheCalloc (Size+1);
    strcpy (Str, InlineComment);
    strcat (Str, ToAdd);
    Str[strlen (Str)] = 0; //null terminate

    return Str;
}


/*******************************************************************************
 *
 * FUNCTION:    CvPlaceComment
 *
 * PARAMETERS:  Int    Type
 *              char*  CommentString
 *
 * RETURN:      None
 *
 * DESCRIPTION: For -q option. Take the given input. If this character is 
 *              defined as a comment table entry, then update the state
 *              accordingly.
 *
 ******************************************************************************/

void
CvPlaceComment(
    UINT8                   Type,
    char                    *CommentString)
{
   
    CvDbgPrint ("Placing comment %s for type %d\n", CommentString, Type);
    switch (Type)
    {
        case ASL_REGCOMMENT:

            CvAddToCommentList (CommentString);
            break;

        case ASL_INLINECOMMENT:

            Gbl_CommentState.Latest_Parse_Node->Asl.InlineComment = 
                CvAppendInlineComment (Gbl_CommentState.Latest_Parse_Node->Asl.InlineComment,
                CommentString);
            break;

        case ASL_OPENPARENCOMMENT:

            Gbl_Inline_Comment_Buffer = 
                CvAppendInlineComment(Gbl_Inline_Comment_Buffer,
                CommentString);
            break;

        case ASL_CLOSEPARENCOMMENT:
           
            if (Gbl_CommentState.ParsingParenBraceNode !=NULL)
            {
                Gbl_CommentState.ParsingParenBraceNode->Asl.EndNodeComment = 
                    CvAppendInlineComment (Gbl_CommentState.ParsingParenBraceNode->Asl.EndNodeComment,
                    CommentString);
            }
            else
            {
                Gbl_CommentState.Latest_Parse_Node->Asl.EndNodeComment = 
                    CvAppendInlineComment (Gbl_CommentState.Latest_Parse_Node->Asl.EndNodeComment,
                    CommentString);
            }
            break;

        case ASL_CLOSEBRACECOMMENT:

            Gbl_CommentState.Latest_Parse_Node->Asl.CloseBraceComment = CommentString;
            break;

        default:

            break;

    }
}


