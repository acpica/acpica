/******************************************************************************
 *
 * Module Name: psparse - Parser top level AML parse routines
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

/*
 * Parse the AML and build an operation tree as most interpreters,
 * like Perl, do. Parsing is done by hand rather than with a YACC
 * generated parser to tightly constrain stack and dynamic memory
 * usage. At the same time, parsing is kept flexible and the code
 * fairly compact by parsing based on a list of AML opcode
 * templates in AmlOpInfo[]
 */

#include "acpi.h"
#include "accommon.h"
#include "acparser.h"
#include "acdispat.h"
#include "amlcode.h"
#include "acinterp.h"

#define _COMPONENT          ACPI_PARSER
        ACPI_MODULE_NAME    ("psparse")


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsGetOpcodeSize
 *
 * PARAMETERS:  Opcode          - An AML opcode
 *
 * RETURN:      Size of the opcode, in bytes (1 or 2)
 *
 * DESCRIPTION: Get the size of the current opcode.
 *
 ******************************************************************************/

UINT32
AcpiPsGetOpcodeSize (
    UINT32                  Opcode)
{

    /* Extended (2-byte) opcode if > 255 */

    if (Opcode > 0x00FF)
    {
        return (2);
    }

    /* Otherwise, just a single byte opcode */

    return (1);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsCommentExists
 *
 * PARAMETERS:  toCheck              - check if this address appears in the list
 *
 * RETURN:      BOOLEAN
 *
 * DESCRIPTION: look at the pointer address and check if this appears in the 
 *              list of all addresses. If it exitsts in the list, return TRUE
 *              if it exists, add to the list and return FALSE.
 *
 ******************************************************************************/

BOOLEAN
AcpiPsCommentExists (
    UINT8                    *ToCheck)
{
    ACPI_COMMENT_ADDR_NODE   *Current = AcpiGbl_CommentAddrListHead;
    UINT8                    Option;


    if (!ToCheck)
    {
        return (FALSE);
    }
    Option   = *(ToCheck + 1);

    /* FILENAME_COMMENT and PARENTFILENAME_COMMENT will not be treated as comments */

    if ((Option == FILENAME_COMMENT) || (Option == PARENTFILENAME_COMMENT))
    {
       return (FALSE); 
    }

    if (!Current)
    {
        AcpiGbl_CommentAddrListHead = 
            AcpiOsAcquireObject (AcpiGbl_RegCommentCache);
        AcpiGbl_CommentAddrListHead->Addr = ToCheck;
        AcpiGbl_CommentAddrListHead->Next = NULL;
        return (FALSE);
    }
    else
    {
        printf ("========== Traversing address list now ==========\n");
        while (Current)
        {
            if (Current->Addr != ToCheck)
            {
                printf ("Address in list: %p\n", Current->Addr);
                Current = Current->Next;
            }
            else
            {
                printf ("========== Found addr, ending traversal =====================\n");
                return (TRUE);
            }
        }
        printf ("========== Ending traversal adding address =====================\n");

        /* 
         * If the execution gets to this point, it means that this address
         * does not exists in the list. Add this address to the 
         * beginning of the list.
         */
        Current = AcpiGbl_CommentAddrListHead;
        AcpiGbl_CommentAddrListHead = 
            AcpiOsAcquireObject (AcpiGbl_RegCommentCache);
        AcpiGbl_CommentAddrListHead->Addr = ToCheck;
        AcpiGbl_CommentAddrListHead->Next = Current;
        return (FALSE);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsFilenameExists
 *
 * PARAMETERS:  Filename
 *
 * RETURN:      Status
 *
 * DESCRIPTION: for -ca option: look for the given filename in the stack.
 *              Returns TRUE if it exists, returns FALSE if it doesn't.
 *
 ******************************************************************************/

ACPI_FILE_NODE*
AcpiPsFilenameExists(
    char                    *Filename,
    ACPI_FILE_NODE           *Head)
{
    ACPI_FILE_NODE          *Current = Head;


    while (Current)
    {
        if (!strcmp (Current->Filename, Filename))
        {
            return (Current);
        }
        Current = Current->Next;
    }
    return (NULL);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsAddToFileTree
 *
 * PARAMETERS:  char* Filename
 *
 * RETURN:      void
 *
 * DESCRIPTION: Add this filename to the AcpiGbl_FileTree if it does not exist.
 *
 ******************************************************************************/

void
AcpiPsAddToFileTree (
    char                    *Filename)
{
    ACPI_FILE_NODE          *Temp;


    if (!AcpiPsFilenameExists (Filename, AcpiGbl_FileTreeRoot))
    {
        Temp = AcpiGbl_FileTreeRoot;
        AcpiGbl_FileTreeRoot = AcpiOsAcquireObject (AcpiGbl_FileCache);
        AcpiGbl_FileTreeRoot->Parent = NULL;
        AcpiGbl_FileTreeRoot->Next = Temp;
        strcpy(AcpiGbl_FileTreeRoot->Filename, Filename);
    }

    Temp = AcpiGbl_FileTreeRoot;
    printf ("File tree entries so far:\n");
    while (Temp)
    {
        printf ("    %s\n", Temp->Filename);
        Temp = Temp->Next;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsSetFileParent
 *
 * PARAMETERS:  char* ChildFile, char* ParentFile
 *
 * RETURN:      void
 *
 * DESCRIPTION: point the child's parent pointer to the node that corresponds
 *              with parent's node.
 *
 ******************************************************************************/

void
AcpiPsSetFileParent (
    char                    *ChildFile,
    char                    *ParentFile)
{
    ACPI_FILE_NODE          *Child;
    ACPI_FILE_NODE          *Parent;


    printf ("Setting file parent within file dependency tree.\n");
    Child  = AcpiPsFilenameExists (ChildFile, AcpiGbl_FileTreeRoot); 
    Parent = AcpiPsFilenameExists (ParentFile, AcpiGbl_FileTreeRoot);
    if (Child && Parent)
    {
        Child->Parent = Parent;
        return;
    }
    else
    {
        printf ("Child and/or parent does not exist.\n");
        return;
    } 
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsCaptureJustComments
 *
 * PARAMETERS:  ParserState         - A parser state object
 *
 * RETURN:      void
 *
 * DESCRIPTION: look at the aml that the parser state is pointing to,
 *              capture any AML_COMMENT_OP and it's arguments and increment the
 *              aml pointer past the comment. This is used in the -q option.
 *
 ******************************************************************************/

void
AcpiPsCaptureJustComments (
    ACPI_PARSE_STATE        *ParserState)
{
    UINT8                   *Aml;
    UINT16                  Opcode;
    UINT32                  Length = 0;
    UINT8                   CommentOption;
    char                    *Debug;
    ACPI_COMMENT_LIST_NODE  *CommentNode;
    BOOLEAN                 StdDefBlockFlag = FALSE;


    Aml = ParserState->Aml;
    Opcode = (UINT16) ACPI_GET8 (Aml);
    printf("CaptureComments Opcode: 0x%x\n", Opcode);
    if (Opcode != AML_COMMENT_OP)
    {
       return;
    }


    while (Opcode == AML_COMMENT_OP)
    {                  
        printf("comment aml address: %p\n", Aml);

        if (AcpiPsCommentExists(Aml))
        {
            printf("Avoiding capturing an existing comment.\n");
        }
        else
        {
            CommentOption = *(Aml+1);

            /*increment past the comment option and point the approperiate char pointers.*/

            ParserState->Aml += 2; 

            /* found a comment. Now, set pointers to these comments. */

            switch (CommentOption)
            {
                case STD_DEFBLK_COMMENT:

                    StdDefBlockFlag = TRUE;

                case STANDARD_COMMENT:

                    printf("found regular comment.\n");

                    /* add to a linked list of nodes. This list will be taken by the parse node created next. */
                
                    CommentNode = AcpiOsAcquireObject (AcpiGbl_RegCommentCache);
                
                    CommentNode->Comment = ACPI_CAST_PTR (char, ParserState->Aml);
                    CommentNode->Next    = NULL;
                     
                    if (AcpiGbl_RegCommentListHead==NULL)
                    {
                        AcpiGbl_RegCommentListHead 
                         = AcpiGbl_RegCommentListTail 
                         = CommentNode;
                    }
                    else
                    {
                        AcpiGbl_RegCommentListTail->Next = CommentNode;
                        AcpiGbl_RegCommentListTail = AcpiGbl_RegCommentListTail->Next;
                    }
                    break;

                case INLINE_COMMENT:

                    printf ("found inline comment.\n");
                    Debug = AcpiGbl_CurrentInlineComment;          
                    AcpiGbl_CurrentInlineComment = ACPI_CAST_PTR (char, ParserState->Aml);
                    if (Debug!=NULL)
                    {
                        printf ("CAUTION: switching %s with %s for inline comments!\n", Debug, AcpiGbl_CurrentInlineComment);
                    }
                    break;

                case ENDNODE_COMMENT:

                    printf ("found EndNode comment.\n");
                    Debug = AcpiGbl_CurrentEndNodeComment;
                    AcpiGbl_CurrentEndNodeComment = ACPI_CAST_PTR (char, ParserState->Aml);
                    if (Debug!=NULL)
                    {
                        printf ("CAUTION: switching %s with %s for inline comments\n", Debug, AcpiGbl_CurrentEndNodeComment);
                    }
                    break;

                case OPENBRACE_COMMENT:

                    printf("found open brace comment.\n");
                    Debug = AcpiGbl_CurrentOpenBraceComment;
                    AcpiGbl_CurrentOpenBraceComment = ACPI_CAST_PTR (char, ParserState->Aml);
                    if (Debug!=NULL)
                    {
                        printf("CAUTION: switching %s with %s for inline comments\n", Debug, AcpiGbl_CurrentOpenBraceComment);
                    }
                    break;

                case CLOSEBRACE_COMMENT:

                    printf("found close brace comment.\n");
                    Debug = AcpiGbl_CurrentCloseBraceComment;
                    AcpiGbl_CurrentCloseBraceComment = ACPI_CAST_PTR (char, ParserState->Aml);
                    if (Debug!=NULL)
                    {
                        printf("CAUTION: switching %s with %s for inline comments\n", Debug, AcpiGbl_CurrentCloseBraceComment);
                    }
                    break;        

                case END_DEFBLK_COMMENT:

                    printf("Found comment that belongs after the } for a definition block.\n");
                     
                    Debug = AcpiGbl_CurrentScope->Common.CloseBraceComment;
                    AcpiGbl_CurrentScope->Common.CloseBraceComment = ACPI_CAST_PTR (char, ParserState->Aml);
                    
                    if (Debug!=NULL)
                    {
                        printf("CAUTION: switching %s with %s for inline comments\n", Debug, AcpiGbl_CurrentCloseBraceComment);
                    }
                    break;        

                case FILENAME_COMMENT:

                    printf ("Found a filename.");
                    AcpiGbl_CurrentFilename = ACPI_CAST_PTR (char, ParserState->Aml);
                    printf ("Setting the Current filename to %s\n", AcpiGbl_CurrentFilename);
                    AcpiPsAddToFileTree (AcpiGbl_CurrentFilename);

                    /* 
                     * Since PARENTFILENAME_COMMENT may come after FILENAME_COMMENT, 
                     * we need to reset the AcpiGbl_CurrentParentFilename to itself in case 
                     * PARENTFILENAME_COMMENT does not exist.
                     */
                    AcpiGbl_CurrentParentFilename = AcpiGbl_CurrentFilename;
                    break;

                case PARENTFILENAME_COMMENT:

                    printf ("Found a parent filename.");
                    AcpiGbl_CurrentParentFilename = ACPI_CAST_PTR (char, ParserState->Aml);
                    printf ("Setting the Current parent filename to %s\n", AcpiGbl_CurrentParentFilename);

                    /* add the parent filename just in case it doesn't exist before connecting. */

                    AcpiPsAddToFileTree (AcpiGbl_CurrentParentFilename);
                    AcpiPsSetFileParent (AcpiGbl_CurrentFilename, AcpiGbl_CurrentParentFilename);
                    break;

                default:

                    break;

            } /* end switch statement */

	} /* end else */

        /* determine the length and move forward that amount */
        Length = 0;
        while (ParserState->Aml[Length])
        {
            Length++;
        }

        ParserState->Aml += Length + 1;


        /* Peek at the next Opcode. */

        Aml = ParserState->Aml;
        Opcode = (UINT16) ACPI_GET8 (Aml);

        printf ("Summary after capture:          \n"
            "Current end node comment:        %s\n"
            "Current inline node comment:     %s\n" 
            "Current open brace node comment: %s\n" 
            "Current close node comment:      %s\n", 
            AcpiGbl_CurrentEndNodeComment,
            AcpiGbl_CurrentInlineComment,
            AcpiGbl_CurrentOpenBraceComment,
            AcpiGbl_CurrentCloseBraceComment);
    } // End while
 
    printf ("\n");

    if (StdDefBlockFlag)
    {
        /* 
         * Give all of its comments to the current scope, which is known as
         * the definition block, since STD_DEFBLK_COMMENT only appears after
         * definition block headers.
         */
        AcpiGbl_CurrentScope->Common.CommentList = AcpiGbl_RegCommentListHead;
        AcpiGbl_RegCommentListHead = NULL;
        AcpiGbl_RegCommentListTail = NULL;
    }
    printf ("Ending capture...\n");
    
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsCaptureComments
 *
 * PARAMETERS:  ParserState         - A parser state object
 *
 * RETURN:      void
 *
 * DESCRIPTION: look at the aml that the parser state is pointing to,
 *              capture any AML_COMMENT_OP and it's arguments and increment the
 *              aml pointer past the comment. This is used in the -q option.
 *
 ******************************************************************************/

void
AcpiPsCaptureComments (
    ACPI_WALK_STATE         *WalkState)
{
    UINT8                   *Aml;
    UINT16                  Opcode;
    const ACPI_OPCODE_INFO  *OpInfo;

    /* Before parsing, check to see that comments that come directly after 
     * deferred opcodes aren't being processed.
     */

    Aml = WalkState->ParserState.Aml;
    Opcode = (UINT16) ACPI_GET8 (Aml);
    OpInfo = AcpiPsGetOpcodeInfo (Opcode);

    if (!(OpInfo->Flags & AML_DEFER) || ((OpInfo->Flags & AML_DEFER)&&(WalkState->PassNumber != ACPI_IMODE_LOAD_PASS1)))
    {
        AcpiPsCaptureJustComments(&WalkState->ParserState);
        WalkState->Aml = WalkState->ParserState.Aml; //Is this needed? What will this do?
    }
    
}

/*******************************************************************************
 *
 * FUNCTION:    AcpiPsPeekOpcode
 *
 * PARAMETERS:  ParserState         - A parser state object
 *
 * RETURN:      Next AML opcode
 *
 * DESCRIPTION: Get next AML opcode (without incrementing AML pointer)
 *
 ******************************************************************************/

UINT16
AcpiPsPeekOpcode (
    ACPI_PARSE_STATE        *ParserState)
{
    UINT8                   *Aml;
    UINT16                  Opcode;


    Aml = ParserState->Aml;
    Opcode = (UINT16) ACPI_GET8 (Aml);

    if (Opcode == AML_EXTENDED_OP_PREFIX)
    {
        /* Extended opcode, get the second opcode byte */

        Aml++;
        Opcode = (UINT16) ((Opcode << 8) | ACPI_GET8 (Aml));
    }

    return (Opcode);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsCompleteThisOp
 *
 * PARAMETERS:  WalkState       - Current State
 *              Op              - Op to complete
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perform any cleanup at the completion of an Op.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiPsCompleteThisOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Prev;
    ACPI_PARSE_OBJECT       *Next;
    const ACPI_OPCODE_INFO  *ParentInfo;
    ACPI_PARSE_OBJECT       *ReplacementOp = NULL;
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE_PTR (PsCompleteThisOp, Op);


    /* Check for null Op, can happen if AML code is corrupt */

    if (!Op)
    {
        return_ACPI_STATUS (AE_OK);  /* OK for now */
    }

    AcpiExStopTraceOpcode (Op, WalkState);

    /* Delete this op and the subtree below it if asked to */

    if (((WalkState->ParseFlags & ACPI_PARSE_TREE_MASK) != ACPI_PARSE_DELETE_TREE) ||
         (WalkState->OpInfo->Class == AML_CLASS_ARGUMENT))
    {
        return_ACPI_STATUS (AE_OK);
    }

    /* Make sure that we only delete this subtree */

    if (Op->Common.Parent)
    {
        Prev = Op->Common.Parent->Common.Value.Arg;
        if (!Prev)
        {
            /* Nothing more to do */

            goto Cleanup;
        }

        /*
         * Check if we need to replace the operator and its subtree
         * with a return value op (placeholder op)
         */
        ParentInfo = AcpiPsGetOpcodeInfo (Op->Common.Parent->Common.AmlOpcode);

        switch (ParentInfo->Class)
        {
        case AML_CLASS_CONTROL:

            break;

        case AML_CLASS_CREATE:
            /*
             * These opcodes contain TermArg operands. The current
             * op must be replaced by a placeholder return op
             */
            ReplacementOp = AcpiPsAllocOp (
                AML_INT_RETURN_VALUE_OP, Op->Common.Aml);
            if (!ReplacementOp)
            {
                Status = AE_NO_MEMORY;
            }
            break;

        case AML_CLASS_NAMED_OBJECT:
            /*
             * These opcodes contain TermArg operands. The current
             * op must be replaced by a placeholder return op
             */
            if ((Op->Common.Parent->Common.AmlOpcode == AML_REGION_OP)       ||
                (Op->Common.Parent->Common.AmlOpcode == AML_DATA_REGION_OP)  ||
                (Op->Common.Parent->Common.AmlOpcode == AML_BUFFER_OP)       ||
                (Op->Common.Parent->Common.AmlOpcode == AML_PACKAGE_OP)      ||
                (Op->Common.Parent->Common.AmlOpcode == AML_BANK_FIELD_OP)   ||
                (Op->Common.Parent->Common.AmlOpcode == AML_VAR_PACKAGE_OP))
            {
                ReplacementOp = AcpiPsAllocOp (
                    AML_INT_RETURN_VALUE_OP, Op->Common.Aml);
                if (!ReplacementOp)
                {
                    Status = AE_NO_MEMORY;
                }
            }
            else if ((Op->Common.Parent->Common.AmlOpcode == AML_NAME_OP) &&
                     (WalkState->PassNumber <= ACPI_IMODE_LOAD_PASS2))
            {
                if ((Op->Common.AmlOpcode == AML_BUFFER_OP) ||
                    (Op->Common.AmlOpcode == AML_PACKAGE_OP) ||
                    (Op->Common.AmlOpcode == AML_VAR_PACKAGE_OP))
                {
                    ReplacementOp = AcpiPsAllocOp (Op->Common.AmlOpcode,
                        Op->Common.Aml);
                    if (!ReplacementOp)
                    {
                        Status = AE_NO_MEMORY;
                    }
                    else
                    {
                        ReplacementOp->Named.Data = Op->Named.Data;
                        ReplacementOp->Named.Length = Op->Named.Length;
                    }
                }
            }
            break;

        default:

            ReplacementOp = AcpiPsAllocOp (
                AML_INT_RETURN_VALUE_OP, Op->Common.Aml);
            if (!ReplacementOp)
            {
                Status = AE_NO_MEMORY;
            }
        }

        /* We must unlink this op from the parent tree */

        if (Prev == Op)
        {
            /* This op is the first in the list */

            if (ReplacementOp)
            {
                ReplacementOp->Common.Parent = Op->Common.Parent;
                ReplacementOp->Common.Value.Arg = NULL;
                ReplacementOp->Common.Node = Op->Common.Node;
                Op->Common.Parent->Common.Value.Arg = ReplacementOp;
                ReplacementOp->Common.Next = Op->Common.Next;
            }
            else
            {
                Op->Common.Parent->Common.Value.Arg = Op->Common.Next;
            }
        }

        /* Search the parent list */

        else while (Prev)
        {
            /* Traverse all siblings in the parent's argument list */

            Next = Prev->Common.Next;
            if (Next == Op)
            {
                if (ReplacementOp)
                {
                    ReplacementOp->Common.Parent = Op->Common.Parent;
                    ReplacementOp->Common.Value.Arg = NULL;
                    ReplacementOp->Common.Node = Op->Common.Node;
                    Prev->Common.Next = ReplacementOp;
                    ReplacementOp->Common.Next = Op->Common.Next;
                    Next = NULL;
                }
                else
                {
                    Prev->Common.Next = Op->Common.Next;
                    Next = NULL;
                }
            }
            Prev = Next;
        }
    }


Cleanup:

    /* Now we can actually delete the subtree rooted at Op */

    AcpiPsDeleteParseTree (Op);
    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsNextParseState
 *
 * PARAMETERS:  WalkState           - Current state
 *              Op                  - Current parse op
 *              CallbackStatus      - Status from previous operation
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Update the parser state based upon the return exception from
 *              the parser callback.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiPsNextParseState (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       *Op,
    ACPI_STATUS             CallbackStatus)
{
    ACPI_PARSE_STATE        *ParserState = &WalkState->ParserState;
    ACPI_STATUS             Status = AE_CTRL_PENDING;


    ACPI_FUNCTION_TRACE_PTR (PsNextParseState, Op);


    switch (CallbackStatus)
    {
    case AE_CTRL_TERMINATE:
        /*
         * A control method was terminated via a RETURN statement.
         * The walk of this method is complete.
         */
        ParserState->Aml = ParserState->AmlEnd;
        Status = AE_CTRL_TERMINATE;
        break;

    case AE_CTRL_BREAK:

        ParserState->Aml = WalkState->AmlLastWhile;
        WalkState->ControlState->Common.Value = FALSE;
        Status = AE_CTRL_BREAK;
        break;

    case AE_CTRL_CONTINUE:

        ParserState->Aml = WalkState->AmlLastWhile;
        Status = AE_CTRL_CONTINUE;
        break;

    case AE_CTRL_PENDING:

        ParserState->Aml = WalkState->AmlLastWhile;
        break;

#if 0
    case AE_CTRL_SKIP:

        ParserState->Aml = ParserState->Scope->ParseScope.PkgEnd;
        Status = AE_OK;
        break;
#endif

    case AE_CTRL_TRUE:
        /*
         * Predicate of an IF was true, and we are at the matching ELSE.
         * Just close out this package
         */
        ParserState->Aml = AcpiPsGetNextPackageEnd (ParserState);
        Status = AE_CTRL_PENDING;
        break;

    case AE_CTRL_FALSE:
        /*
         * Either an IF/WHILE Predicate was false or we encountered a BREAK
         * opcode. In both cases, we do not execute the rest of the
         * package;  We simply close out the parent (finishing the walk of
         * this branch of the tree) and continue execution at the parent
         * level.
         */
        ParserState->Aml = ParserState->Scope->ParseScope.PkgEnd;

        /* In the case of a BREAK, just force a predicate (if any) to FALSE */

        WalkState->ControlState->Common.Value = FALSE;
        Status = AE_CTRL_END;
        break;

    case AE_CTRL_TRANSFER:

        /* A method call (invocation) -- transfer control */

        Status = AE_CTRL_TRANSFER;
        WalkState->PrevOp = Op;
        WalkState->MethodCallOp = Op;
        WalkState->MethodCallNode = (Op->Common.Value.Arg)->Common.Node;

        /* Will return value (if any) be used by the caller? */

        WalkState->ReturnUsed = AcpiDsIsResultUsed (Op, WalkState);
        break;

    default:

        Status = CallbackStatus;
        if ((CallbackStatus & AE_CODE_MASK) == AE_CODE_CONTROL)
        {
            Status = AE_OK;
        }
        break;
    }

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsParseAml
 *
 * PARAMETERS:  WalkState       - Current state
 *
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Parse raw AML and return a tree of ops
 *
 ******************************************************************************/

ACPI_STATUS
AcpiPsParseAml (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_THREAD_STATE       *Thread;
    ACPI_THREAD_STATE       *PrevWalkList = AcpiGbl_CurrentWalkList;
    ACPI_WALK_STATE         *PreviousWalkState;


    ACPI_FUNCTION_TRACE (PsParseAml);

    ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
        "Entered with WalkState=%p Aml=%p size=%X\n",
        WalkState, WalkState->ParserState.Aml,
        WalkState->ParserState.AmlSize));

    if (!WalkState->ParserState.Aml)
    {
        return_ACPI_STATUS (AE_NULL_OBJECT);
    }

    /* Create and initialize a new thread state */

    Thread = AcpiUtCreateThreadState ();
    if (!Thread)
    {
        if (WalkState->MethodDesc)
        {
            /* Executing a control method - additional cleanup */

            AcpiDsTerminateControlMethod (WalkState->MethodDesc, WalkState);
        }

        AcpiDsDeleteWalkState (WalkState);
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    WalkState->Thread = Thread;

    /*
     * If executing a method, the starting SyncLevel is this method's
     * SyncLevel
     */
    if (WalkState->MethodDesc)
    {
        WalkState->Thread->CurrentSyncLevel =
            WalkState->MethodDesc->Method.SyncLevel;
    }

    AcpiDsPushWalkState (WalkState, Thread);

    /*
     * This global allows the AML debugger to get a handle to the currently
     * executing control method.
     */
    AcpiGbl_CurrentWalkList = Thread;

    /*
     * Execute the walk loop as long as there is a valid Walk State. This
     * handles nested control method invocations without recursion.
     */
    ACPI_DEBUG_PRINT ((ACPI_DB_PARSE, "State=%p\n", WalkState));

    Status = AE_OK;
    while (WalkState)
    {
        if (ACPI_SUCCESS (Status))
        {
            /*
             * The ParseLoop executes AML until the method terminates
             * or calls another method.
             */
            Status = AcpiPsParseLoop (WalkState);
        }

        ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
            "Completed one call to walk loop, %s State=%p\n",
            AcpiFormatException (Status), WalkState));

        if (Status == AE_CTRL_TRANSFER)
        {
            /*
             * A method call was detected.
             * Transfer control to the called control method
             */
            Status = AcpiDsCallControlMethod (Thread, WalkState, NULL);
            if (ACPI_FAILURE (Status))
            {
                Status = AcpiDsMethodError (Status, WalkState);
            }

            /*
             * If the transfer to the new method method call worked
             *, a new walk state was created -- get it
             */
            WalkState = AcpiDsGetCurrentWalkState (Thread);
            continue;
        }
        else if (Status == AE_CTRL_TERMINATE)
        {
            Status = AE_OK;
        }
        else if ((Status != AE_OK) && (WalkState->MethodDesc))
        {
            /* Either the method parse or actual execution failed */

            ACPI_ERROR_METHOD ("Method parse/execution failed",
                WalkState->MethodNode, NULL, Status);

            /* Check for possible multi-thread reentrancy problem */

            if ((Status == AE_ALREADY_EXISTS) &&
                (!(WalkState->MethodDesc->Method.InfoFlags &
                    ACPI_METHOD_SERIALIZED)))
            {
                /*
                 * Method is not serialized and tried to create an object
                 * twice. The probable cause is that the method cannot
                 * handle reentrancy. Mark as "pending serialized" now, and
                 * then mark "serialized" when the last thread exits.
                 */
                WalkState->MethodDesc->Method.InfoFlags |=
                    ACPI_METHOD_SERIALIZED_PENDING;
            }
        }

        /* We are done with this walk, move on to the parent if any */

        WalkState = AcpiDsPopWalkState (Thread);

        /* Reset the current scope to the beginning of scope stack */

        AcpiDsScopeStackClear (WalkState);

        /*
         * If we just returned from the execution of a control method or if we
         * encountered an error during the method parse phase, there's lots of
         * cleanup to do
         */
        if (((WalkState->ParseFlags & ACPI_PARSE_MODE_MASK) ==
            ACPI_PARSE_EXECUTE) ||
            (ACPI_FAILURE (Status)))
        {
            AcpiDsTerminateControlMethod (WalkState->MethodDesc, WalkState);
        }

        /* Delete this walk state and all linked control states */

        AcpiPsCleanupScope (&WalkState->ParserState);
        PreviousWalkState = WalkState;

        ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
            "ReturnValue=%p, ImplicitValue=%p State=%p\n",
            WalkState->ReturnDesc, WalkState->ImplicitReturnObj, WalkState));

        /* Check if we have restarted a preempted walk */

        WalkState = AcpiDsGetCurrentWalkState (Thread);
        if (WalkState)
        {
            if (ACPI_SUCCESS (Status))
            {
                /*
                 * There is another walk state, restart it.
                 * If the method return value is not used by the parent,
                 * The object is deleted
                 */
                if (!PreviousWalkState->ReturnDesc)
                {
                    /*
                     * In slack mode execution, if there is no return value
                     * we should implicitly return zero (0) as a default value.
                     */
                    if (AcpiGbl_EnableInterpreterSlack &&
                        !PreviousWalkState->ImplicitReturnObj)
                    {
                        PreviousWalkState->ImplicitReturnObj =
                            AcpiUtCreateIntegerObject ((UINT64) 0);
                        if (!PreviousWalkState->ImplicitReturnObj)
                        {
                            return_ACPI_STATUS (AE_NO_MEMORY);
                        }
                    }

                    /* Restart the calling control method */

                    Status = AcpiDsRestartControlMethod (WalkState,
                        PreviousWalkState->ImplicitReturnObj);
                }
                else
                {
                    /*
                     * We have a valid return value, delete any implicit
                     * return value.
                     */
                    AcpiDsClearImplicitReturn (PreviousWalkState);

                    Status = AcpiDsRestartControlMethod (WalkState,
                        PreviousWalkState->ReturnDesc);
                }
                if (ACPI_SUCCESS (Status))
                {
                    WalkState->WalkType |= ACPI_WALK_METHOD_RESTART;
                }
            }
            else
            {
                /* On error, delete any return object or implicit return */

                AcpiUtRemoveReference (PreviousWalkState->ReturnDesc);
                AcpiDsClearImplicitReturn (PreviousWalkState);
            }
        }

        /*
         * Just completed a 1st-level method, save the final internal return
         * value (if any)
         */
        else if (PreviousWalkState->CallerReturnDesc)
        {
            if (PreviousWalkState->ImplicitReturnObj)
            {
                *(PreviousWalkState->CallerReturnDesc) =
                    PreviousWalkState->ImplicitReturnObj;
            }
            else
            {
                 /* NULL if no return value */

                *(PreviousWalkState->CallerReturnDesc) =
                    PreviousWalkState->ReturnDesc;
            }
        }
        else
        {
            if (PreviousWalkState->ReturnDesc)
            {
                /* Caller doesn't want it, must delete it */

                AcpiUtRemoveReference (PreviousWalkState->ReturnDesc);
            }
            if (PreviousWalkState->ImplicitReturnObj)
            {
                /* Caller doesn't want it, must delete it */

                AcpiUtRemoveReference (PreviousWalkState->ImplicitReturnObj);
            }
        }

        AcpiDsDeleteWalkState (PreviousWalkState);
    }

    /* Normal exit */

    AcpiExReleaseAllMutexes (Thread);
    AcpiUtDeleteGenericState (ACPI_CAST_PTR (ACPI_GENERIC_STATE, Thread));
    AcpiGbl_CurrentWalkList = PrevWalkList;
    return_ACPI_STATUS (Status);
}
