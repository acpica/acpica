/******************************************************************************
 *
 * Module Name: cvparser - Converter functions that are called from the AML
 *                         parser.
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

#include "acpi.h"
#include "accommon.h"
#include "acparser.h"
#include "acdispat.h"
#include "amlcode.h"
#include "acinterp.h"
#include "acdisasm.h"
#include "acconvert.h"


/* local prototypes */

static BOOLEAN
CvCommentExists (
    UINT8                   *ToCheck);


/*******************************************************************************
 *
 * FUNCTION:    CvInitFileTree
 *
 * PARAMETERS:  Op
 *
 * RETURN:      none
 *
 * DESCRIPTION: Initialize the file dependency tree by looking at the AML.
 *
 ******************************************************************************/

void
CvInitFileTree (
    ACPI_TABLE_HEADER       *Table,
    UINT8                   *AmlStart,
    UINT32                  AmlLength)
{
    UINT8                   *TreeAml;
    UINT8                   *FileEnd;
    char                    *Filename = NULL;
    char                    *PreviousFilename = NULL;
    char                    *ParentFilename = NULL;
    char                    *ChildFilename = NULL;
    UINT8                   fnameLength;
    char                    *temp;



    /* 
     * The following is for the -ca option. This is the initialization of 
     * the file dependency tree.
     */
    if (Gbl_CaptureComments)
    {
        /* This is expected to work only for a single defintion block. */

        CvDbgPrint ("AmlLength: %x\n", AmlLength);
        CvDbgPrint ("AmlStart:  %p\n", AmlStart);
        CvDbgPrint ("AmlEnd?:   %p\n", AmlStart+AmlLength);
    
        AcpiGbl_FileTreeRoot = AcpiOsAcquireObject (AcpiGbl_FileCache);
        AcpiGbl_FileTreeRoot->FileStart = (char*)(AmlStart);
        AcpiGbl_FileTreeRoot->FileEnd = (char*)(AmlStart + Table->Length);
        AcpiGbl_FileTreeRoot->Next = NULL;
        AcpiGbl_FileTreeRoot->Parent = NULL;
        AcpiGbl_FileTreeRoot->Filename = (char*)(AmlStart+2);

        /* Set this file to the current open file */

        AcpiGbl_FileTreeRoot->File = AcpiGbl_OutputFile; 
    
        /* 
         * Set this to true because we dont need to output
         * an include statement for the topmost file 
         */
        AcpiGbl_FileTreeRoot->IncludeWritten = TRUE;
        Filename = NULL;    
        AcpiGbl_CurrentFilename = (char*)(AmlStart+2);
        AcpiGbl_RootFilename    = (char*)(AmlStart+2);
  

        TreeAml = AmlStart;
        FileEnd = AmlStart +AmlLength;

        while (TreeAml <= FileEnd)
        {
            if (*TreeAml == 0xA9 && *(TreeAml+1) == 0x08)
            {
                CvDbgPrint ("A9 and a 08 file\n");
                PreviousFilename = Filename;
                Filename = (char*) (TreeAml+2);

                /*
                 * Make sure that this filename contains a .dsl extension.
                 * If it doesn't contain it, then it must be 0xA9 and 0x08 then it
                 * must be some raw data that doesn't outline a filename.
                 */
                fnameLength = strlen(Filename);
                temp = Filename + fnameLength - 3;
                if (!strcmp(temp, "dsl"))
                {
                    ADDTOFILETREE (Filename, PreviousFilename);
                    ChildFilename = Filename;
                }
            }
            else if (*TreeAml == 0xA9 && *(TreeAml+1) == 0x09)
            {
                CvDbgPrint ("A9 and a 09 file\n");
                fnameLength = strlen(Filename);
                temp = Filename + fnameLength - 3;
                if (!strcmp(temp, "dsl"))
                {
                	ParentFilename = (char*)(TreeAml+2);
                        SETFILEPARENT (ChildFilename, ParentFilename);
		}
            }
            ++TreeAml;
        }
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CvClearOpComments
 *
 * PARAMETERS:  Op
 *
 * RETURN:      none
 *
 * DESCRIPTION: Clear all converter-related fields of the given Op.
 *
 ******************************************************************************/

void
CvClearOpComments (
    ACPI_PARSE_OBJECT       *Op)
{
    Op->Common.InlineComment     = NULL;
    Op->Common.EndNodeComment    = NULL;
    Op->Common.NameComment       = NULL;
    Op->Common.CommentList       = NULL;
    Op->Common.EndBlkComment     = NULL;
    Op->Common.CloseBraceComment = NULL;
    Op->Common.IncComment        = NULL;
    Op->Common.PsFilename        = NULL;
    Op->Common.PsParentFilename  = NULL;
}


/*******************************************************************************
 *
 * FUNCTION:    CvCommentExists
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

static BOOLEAN
CvCommentExists (
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
        //CvDbgPrint ("========== Traversing address list now ==========\n");
        while (Current)
        {
            if (Current->Addr != ToCheck)
            {
//                CvDbgPrint ("Address in list: %p\n", Current->Addr);
                Current = Current->Next;
            }
            else
            {
                //CvDbgPrint ("========== Found addr, ending traversal =====================\n");
                return (TRUE);
            }
        }
        //CvDbgPrint ("========== Ending traversal adding address =====================\n");

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
 * FUNCTION:    CvFilenameExists
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
CvFilenameExists(
    char                    *Filename,
    ACPI_FILE_NODE          *Head)
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
 * FUNCTION:    CvFileAddressLookup
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
CvFileAddressLookup(
    char                    *Address,
    ACPI_FILE_NODE          *Head)
{
    ACPI_FILE_NODE          *Current = Head;


    while (Current)
    {
        if (Address >= Current->FileStart && (Address < Current->FileEnd || !Current->FileEnd))
        {
            return (Current);
        }
        Current = Current->Next;
    }

    return (NULL);
}


/*******************************************************************************
 *
 * FUNCTION:    CvFileLabelNode
 *
 * PARAMETERS:  Op
 *
 * RETURN:      None
 *
 * DESCRIPTION: for -ca option: Takes a given parse op, looks up its 
 *              Op->Common.Aml field within the file tree and fills in
 *              approperiate file information from a matching node within the
 *              tree.
 *
 ******************************************************************************/

void
CvFileLabelNode(
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_FILE_NODE          *Temp;

    
    if (!Op)
    {
        return;
    }

    Temp = CvFileAddressLookup ((char*)Op->Common.Aml, AcpiGbl_FileTreeRoot);
    if (Temp)
    {
        Op->Common.PsFilename = Temp->Filename;
        if (Temp->Parent)
        {
            Op->Common.PsParentFilename = Temp->Parent->Filename;
        }
        else 
        {
            Op->Common.PsParentFilename = Temp->Filename;
        }
    }

    return;
}


/*******************************************************************************
 *
 * FUNCTION:    CvAddToFileTree
 *
 * PARAMETERS:  char* Filename
 *
 * RETURN:      void
 *
 * DESCRIPTION: Add this filename to the AcpiGbl_FileTree if it does not exist.
 *
 ******************************************************************************/

void
CvAddToFileTree (
    char                    *Filename,
    char                    *PreviousFilename)
{
    ACPI_FILE_NODE          *Temp;


    if (!strcmp(Filename, AcpiGbl_RootFilename) && PreviousFilename)
    {
        Temp = CvFilenameExists (PreviousFilename, AcpiGbl_FileTreeRoot);
        if (Temp)
        {
            Temp->FileEnd = Filename;
        }
    }
    else if (!strcmp(Filename, AcpiGbl_RootFilename) && !PreviousFilename)
    {
        return;
    }
    Temp = CvFilenameExists (Filename, AcpiGbl_FileTreeRoot);
    if (Temp && PreviousFilename)
    {
        /* 
         * Update the end of the previous file and all of their parents' ending
         * Addresses. This is done to ensure that parent file ranges extend to
         * the end of their childrens' files.
         */
        Temp = CvFilenameExists (PreviousFilename, AcpiGbl_FileTreeRoot);
        if (Temp && Temp->FileEnd < Filename)
        {
            Temp->FileEnd = Filename; 
            Temp = Temp->Parent;
            while (Temp) 
            {
                if (Temp->FileEnd < Filename)
                {
                    Temp->FileEnd = Filename;
                    //CvDbgPrint ("Setting file end to %p\n", Temp->FileEnd);
                }
                Temp = Temp->Parent;
            }
        }
    }
    else
    {
        Temp = AcpiGbl_FileTreeRoot;
        AcpiGbl_FileTreeRoot = AcpiOsAcquireObject (AcpiGbl_FileCache);
        AcpiGbl_FileTreeRoot->Next = Temp;
        AcpiGbl_FileTreeRoot->Parent = NULL;
        AcpiGbl_FileTreeRoot->Filename = Filename;
        AcpiGbl_FileTreeRoot->FileStart = Filename;
        AcpiGbl_FileTreeRoot->IncludeWritten = FALSE;
        AcpiGbl_FileTreeRoot->File = fopen(Filename, "w+");
    }

    /* Print for debugging */

    Temp = AcpiGbl_FileTreeRoot;
    //CvDbgPrint ("File tree entries so far:\n");
    while (Temp)
    {
        //CvDbgPrint ("    %s\t%p - %p\n", Temp->Filename, Temp->FileStart, Temp->FileEnd);
        Temp = Temp->Next;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CvSetFileParent
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
CvSetFileParent (
    char                    *ChildFile,
    char                    *ParentFile)
{
    ACPI_FILE_NODE          *Child;
    ACPI_FILE_NODE          *Parent;
    ACPI_FILE_NODE          *Temp;


    //CvDbgPrint ("Setting file parent within file dependency tree.\n");
    Child  = CvFilenameExists (ChildFile, AcpiGbl_FileTreeRoot); 
    Parent = CvFilenameExists (ParentFile, AcpiGbl_FileTreeRoot);
    if (Child && Parent)
    {
        Child->Parent = Parent;

        while (Child->Parent)
        {
            if (Child->Parent->FileEnd < Child->FileStart)
            {
                Child->Parent->FileEnd = Child->FileStart;
            }
            Child = Child->Parent;
        }
    }
    else
    {
        //CvDbgPrint ("Child and/or parent does not exist.\n");
    } 

    Temp = AcpiGbl_FileTreeRoot;
    //CvDbgPrint ("File tree relations so far | child filename, parent filename\n");
    while (Temp)
    {
        //CvDbgPrint ("                             %s -> ", Temp->Filename);
        if (Temp->Parent)
        {
            //CvDbgPrint ("%s\n",Temp->Parent->Filename);
        }
        else
        {
            //CvDbgPrint ("none\n");
        }
        
        Temp = Temp->Next;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CvCaptureListComments
 *
 * PARAMETERS:  ParserState         - A parser state object
 *
 * RETURN:      void
 *
 * DESCRIPTION:  
 *
 ******************************************************************************/

void
CvCaptureListComments (
    ACPI_PARSE_STATE        *ParserState,
    ACPI_COMMENT_LIST_NODE  *ListHead,
    ACPI_COMMENT_LIST_NODE  *ListTail)
{
    ACPI_COMMENT_LIST_NODE  *CommentNode;

    CommentNode = AcpiOsAcquireObject (AcpiGbl_RegCommentCache);
    CommentNode->Comment = ACPI_CAST_PTR (char, ParserState->Aml);
    CommentNode->Next    = NULL;

    if (ListHead==NULL)
    {
        ListHead = CommentNode;
        ListTail = CommentNode;
    }
    else
    {
        ListTail->Next = CommentNode;
        ListTail = ListTail->Next;
    }
}
  

/*******************************************************************************
 *
 * FUNCTION:    CvCaptureJustComments
 *
 * PARAMETERS:  ParserState         - A parser state object
 *
 * RETURN:      void
 *
 * DESCRIPTION: look at the aml that the parser state is pointing to,
 *              capture any AML_COMMENT_OP and it's arguments and increment the
 *              aml pointer past the comment. This is used in the -q option.
 *              Comments are transferred to parse nodes through
 *              CvTransferComments as well as AcpiPsBuildNamedOp ().
 *
 ******************************************************************************/

void
CvCaptureJustComments (
    ACPI_PARSE_STATE        *ParserState)
{
    UINT8                   *Aml;
    UINT16                  Opcode;
    UINT32                  Length = 0;
    UINT8                   CommentOption;
    char                    *Debug;
    BOOLEAN                 StdDefBlockFlag = FALSE;
    ACPI_COMMENT_LIST_NODE  *CommentNode;


    if (!Gbl_CaptureComments)
    {
        return;
    }
    Aml = ParserState->Aml;
    Opcode = (UINT16) ACPI_GET8 (Aml);
    CommentOption = (UINT16) ACPI_GET8 (Aml+1);
    //CvDbgPrint ("CaptureComments Opcode: 0x%x\n", Opcode);
    if (Opcode != AML_COMMENT_OP || ((Opcode == AML_COMMENT_OP) && ((CommentOption < 0x1) || (CommentOption > 0xb))))
    {
       return;
    }


    while (Opcode == AML_COMMENT_OP)
    {                  
        //CvDbgPrint ("comment aml address: %p\n", Aml);

        if (CvCommentExists(Aml))
        {
            //CvDbgPrint ("Avoiding capturing an existing comment.\n");
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

                    /* add to a linked list of nodes. This list will be taken by the parse node created next. */

                    CommentNode = AcpiOsAcquireObject (AcpiGbl_RegCommentCache);
                    CommentNode->Comment = ACPI_CAST_PTR (char, ParserState->Aml);
                    CommentNode->Next    = NULL;

                    if (AcpiGbl_DefBlkCommentListHead==NULL)
                    {
                        AcpiGbl_DefBlkCommentListHead = CommentNode;
                        AcpiGbl_DefBlkCommentListTail = CommentNode;
                    }
                    else
                    {
                        AcpiGbl_DefBlkCommentListTail->Next = CommentNode;
                        AcpiGbl_DefBlkCommentListTail = AcpiGbl_DefBlkCommentListTail->Next;
                    }
                    break;

                case STANDARD_COMMENT:

                    //CvDbgPrint ("found regular comment.\n");

                    /* add to a linked list of nodes. This list will be taken by the parse node created next. */

                    CommentNode = AcpiOsAcquireObject (AcpiGbl_RegCommentCache);
                    CommentNode->Comment = ACPI_CAST_PTR (char, ParserState->Aml);
                    CommentNode->Next    = NULL;

                    if (AcpiGbl_RegCommentListHead==NULL)
                    {
                        AcpiGbl_RegCommentListHead = CommentNode;
                        AcpiGbl_RegCommentListTail = CommentNode;
                    }
                    else
                    {
                        AcpiGbl_RegCommentListTail->Next = CommentNode;
                        AcpiGbl_RegCommentListTail = AcpiGbl_RegCommentListTail->Next;
                    }
                    break;

                case ENDBLK_COMMENT:

                    //CvDbgPrint ("found endblk comment.\n");

                    /* add to a linked list of nodes. This will be taken by the next created parse node. */
                    CommentNode = AcpiOsAcquireObject (AcpiGbl_RegCommentCache);
                    CommentNode->Comment = ACPI_CAST_PTR (char, ParserState->Aml);
                    CommentNode->Next    = NULL;

                    if (AcpiGbl_EndBlkCommentListHead==NULL)
                    {
                        AcpiGbl_EndBlkCommentListHead = CommentNode;
                        AcpiGbl_EndBlkCommentListTail = CommentNode;
                    }
                    else
                    {
                        AcpiGbl_EndBlkCommentListTail->Next = CommentNode;
                        AcpiGbl_EndBlkCommentListTail = AcpiGbl_EndBlkCommentListTail->Next;
                    }
                    break;

                case INLINE_COMMENT:

                    //CvDbgPrint ("found inline comment.\n");
                    Debug = AcpiGbl_CurrentInlineComment;          
                    AcpiGbl_CurrentInlineComment = ACPI_CAST_PTR (char, ParserState->Aml);
                    if (Debug!=NULL)
                    {
                        //CvDbgPrint ("CAUTION: switching %s with %s for inline comments!\n", Debug, AcpiGbl_CurrentInlineComment);
                    }
                    break;

                case ENDNODE_COMMENT:

                    //CvDbgPrint ("found EndNode comment.\n");
                    Debug = AcpiGbl_CurrentEndNodeComment;
                    AcpiGbl_CurrentEndNodeComment = ACPI_CAST_PTR (char, ParserState->Aml);
                    if (Debug!=NULL)
                    {
                        //CvDbgPrint ("CAUTION: switching %s with %s for inline comments\n", Debug, AcpiGbl_CurrentEndNodeComment);
                    }
                    break;

                case CLOSEBRACE_COMMENT:

                    //CvDbgPrint ("found close brace comment.\n");
                    Debug = AcpiGbl_CurrentCloseBraceComment;
                    AcpiGbl_CurrentCloseBraceComment = ACPI_CAST_PTR (char, ParserState->Aml);
                    if (Debug!=NULL)
                    {
                        //CvDbgPrint ("CAUTION: switching %s with %s for inline comments\n", Debug, AcpiGbl_CurrentCloseBraceComment);
                    }
                    break;        

                case END_DEFBLK_COMMENT:

                    //CvDbgPrint ("Found comment that belongs after the } for a definition block.\n");
                     
                    Debug = AcpiGbl_CurrentScope->Common.CloseBraceComment;
                    AcpiGbl_CurrentScope->Common.CloseBraceComment = ACPI_CAST_PTR (char, ParserState->Aml);
                    
                    if (Debug!=NULL)
                    {
                        //CvDbgPrint ("CAUTION: switching %s with %s for inline comments\n", Debug, AcpiGbl_CurrentCloseBraceComment);
                    }
                    break;        

                case FILENAME_COMMENT:
                    
                    //CvDbgPrint ("Found a filename: %s", ACPI_CAST_PTR (char, ParserState->Aml));
                    break;

                case PARENTFILENAME_COMMENT:
                    //CvDbgPrint ("Found a parent filename.");
                    break;

                case INCLUDE_COMMENT:
                    printf ("Found a include comment.");

                    /* add to a linked list of nodes. This list will be taken by the parse node created next. */

                    CommentNode = AcpiOsAcquireObject (AcpiGbl_RegCommentCache);
                    CommentNode->Comment = ACPI_CAST_PTR (char, ParserState->Aml);
                    CommentNode->Next    = NULL;

                    if (AcpiGbl_IncCommentListHead==NULL)
                    {
                        AcpiGbl_IncCommentListHead = CommentNode;
                        AcpiGbl_IncCommentListTail = CommentNode;
                    }
                    else
                    {
                        AcpiGbl_IncCommentListTail->Next = CommentNode;
                        AcpiGbl_IncCommentListTail = AcpiGbl_IncCommentListTail->Next;
                    }
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

        /*CvDbgPrint ("Summary after capture:          \n"
            "Current end node comment:        %s\n"
            "Current inline node comment:     %s\n" 
            "Current open brace node comment: %s\n" 
            "Current close node comment:      %s\n", 
            AcpiGbl_CurrentEndNodeComment,
            AcpiGbl_CurrentInlineComment,
            AcpiGbl_CurrentOpenBraceComment,
            AcpiGbl_CurrentCloseBraceComment);*/
    } // End while
 
    //CvDbgPrint ("\n");

    if (StdDefBlockFlag)
    {
        /* 
         * Give all of its comments to the current scope, which is known as
         * the definition block, since STD_DEFBLK_COMMENT only appears after
         * definition block headers.
         */
        AcpiGbl_CurrentScope->Common.CommentList = AcpiGbl_DefBlkCommentListHead;
        AcpiGbl_DefBlkCommentListHead = NULL;
        AcpiGbl_DefBlkCommentListTail = NULL;
    }
    //CvDbgPrint ("Ending capture...\n");
    
}


/*******************************************************************************
 *
 * FUNCTION:    CvCaptureComments
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
CvCaptureComments (
    ACPI_WALK_STATE         *WalkState)
{
    UINT8                   *Aml;
    UINT16                  Opcode;
    const ACPI_OPCODE_INFO  *OpInfo;


    if (!Gbl_CaptureComments)
    {
        return;
    }

    /* 
     *Before parsing, check to see that comments that come directly after 
     * deferred opcodes aren't being processed.
     */
    Aml = WalkState->ParserState.Aml;
    Opcode = (UINT16) ACPI_GET8 (Aml);
    OpInfo = AcpiPsGetOpcodeInfo (Opcode);
    if (!(OpInfo->Flags & AML_DEFER) || ((OpInfo->Flags & AML_DEFER)&&(WalkState->PassNumber != ACPI_IMODE_LOAD_PASS1)))
    {
        CvCaptureJustComments(&WalkState->ParserState);
        WalkState->Aml = WalkState->ParserState.Aml; //Is this needed? What will this do?
    }
    
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsTransferComments
 *
 * PARAMETERS:  WalkState           - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Parse AML (pointed to by the current parser state) and return
 *              a tree of ops.
 *
 ******************************************************************************/

void
CvTransferComments (
    ACPI_PARSE_OBJECT       *Op) 
{
    //CvDbgPrint ("Transferring all captured global comments to the folowing opcode: %x\n", Op->Common.AmlOpcode);
    if (AcpiGbl_CurrentInlineComment)
    { 
        Op->Common.InlineComment = AcpiGbl_CurrentInlineComment;
        //CvDbgPrint ("Op->Common.InlineComment: %s\n", Op->Common.InlineComment);
        AcpiGbl_CurrentInlineComment = NULL;
    }

    if (AcpiGbl_CurrentEndNodeComment != NULL)
    { 
        Op->Common.EndNodeComment = AcpiGbl_CurrentEndNodeComment;
        //CvDbgPrint ("Op->Common.EndNodeComment: %s\n", Op->Common.EndNodeComment);
        AcpiGbl_CurrentEndNodeComment = NULL;
    }

    if (AcpiGbl_CurrentCloseBraceComment != NULL)
    {
        Op->Common.CloseBraceComment = AcpiGbl_CurrentCloseBraceComment;
        //CvDbgPrint ("Op->Common.CloseBraceComment: %s\n", Op->Common.CloseBraceComment);
        AcpiGbl_CurrentCloseBraceComment = NULL;
    }

    if (AcpiGbl_RegCommentListHead != NULL)
    { 
        Op->Common.CommentList = AcpiGbl_RegCommentListHead;
        //CvDbgPrint ("Op->Common.CommentList head: %s\n", Op->Common.CommentList->Comment);
        AcpiGbl_RegCommentListHead = NULL;
        AcpiGbl_RegCommentListTail = NULL;
    }

    if (AcpiGbl_EndBlkCommentListHead != NULL)
    {
        Op->Common.EndBlkComment = AcpiGbl_EndBlkCommentListHead;
        //CvDbgPrint ("Op->Common.CommentList head: %s\n", Op->Common.EndBlkComment->Comment);
        AcpiGbl_EndBlkCommentListHead = NULL;
        AcpiGbl_EndBlkCommentListTail = NULL;
    }

    if (AcpiGbl_IncCommentListHead != NULL)
    {
        Op->Common.IncComment = AcpiGbl_IncCommentListHead;
        printf ("Op->Common.IncComment head: %s\n", Op->Common.IncComment->Comment);
        AcpiGbl_IncCommentListHead = NULL;
        AcpiGbl_IncCommentListTail = NULL;
    }


    //CvDbgPrint("\n");
}
