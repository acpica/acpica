/******************************************************************************
 *
 * Module Name: aslcodegen - AML code generation
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
#include "aslcompiler.y.h"
#include "amlcode.h"
#include "acapps.h"

#define _COMPONENT          ACPI_COMPILER
        ACPI_MODULE_NAME    ("aslcodegen")

/* Local prototypes */

static ACPI_STATUS
CgAmlWriteWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context);

static void
CgLocalWriteAmlData (
    ACPI_PARSE_OBJECT       *Op,
    void                    *Buffer,
    UINT32                  Length);

static void
CgWriteAmlOpcode (
    ACPI_PARSE_OBJECT       *Op);

static void
CgWriteTableHeader (
    ACPI_PARSE_OBJECT       *Op);

static void
CgCloseTable (
    void);

static void
CgWriteNode (
    ACPI_PARSE_OBJECT       *Op);

char*
CgChangeFileExt(
   char*                    Filename,
   char*                    FileExt);


/*******************************************************************************
 *
 * FUNCTION:    CgGenerateAmlOutput
 *
 * PARAMETERS:  None.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Generate AML code. Currently generates the listing file
 *              simultaneously.
 *
 ******************************************************************************/

void
CgGenerateAmlOutput (
    void)
{

    /* Generate the AML output file */

    FlSeekFile (ASL_FILE_SOURCE_OUTPUT, 0);
    Gbl_SourceLine = 0;
    Gbl_NextError = Gbl_ErrorLog;

    TrWalkParseTree (Gbl_ParseTreeRoot, ASL_WALK_VISIT_DOWNWARD,
        CgAmlWriteWalk, NULL, NULL);

    DbgPrint (ASL_TREE_OUTPUT, ASL_PARSE_TREE_HEADER2);
    CgCloseTable ();
}


/*******************************************************************************
 *
 * FUNCTION:    CgAmlWriteWalk
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Parse tree walk to generate the AML code.
 *
 ******************************************************************************/

static ACPI_STATUS
CgAmlWriteWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{

    /* Generate the AML for this node */

    CgWriteNode (Op);

    if (!Gbl_DebugFlag)
    {
        return (AE_OK);
    }

    /* Print header at level 0. Alignment assumes 32-bit pointers */

    if (!Level)
    {
        DbgPrint (ASL_TREE_OUTPUT,
            "\nFinal parse tree used for AML output:\n");
        DbgPrint (ASL_TREE_OUTPUT, ASL_PARSE_TREE_HEADER2);
    }

    /* Dump ParseOp name and possible value */

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_NAMESEG:
    case PARSEOP_NAMESTRING:
    case PARSEOP_METHODCALL:
    case PARSEOP_STRING_LITERAL:

        UtDumpStringOp (Op, Level);
        break;

    default:

        UtDumpBasicOp (Op, Level);
        break;
    }

    DbgPrint (ASL_TREE_OUTPUT, ASL_PARSE_TREE_DEBUG2,
        /* 1  */ (UINT32) Op->Asl.Value.Integer,
        /* 2  */ Op->Asl.ParseOpcode,
        /* 3  */ Op->Asl.AmlOpcode,
        /* 4  */ Op->Asl.AmlOpcodeLength,
        /* 5  */ Op->Asl.AmlPkgLenBytes,
        /* 6  */ Op->Asl.AmlLength,
        /* 7  */ Op->Asl.AmlSubtreeLength,
        /* 8  */ Op->Asl.Parent ? Op->Asl.Parent->Asl.AmlSubtreeLength : 0,
        /* 9  */ Op,
        /* 10 */ Op->Asl.Parent,
        /* 11 */ Op->Asl.Child,
        /* 12 */ Op->Asl.Next,
        /* 13 */ Op->Asl.CompileFlags,
        /* 14 */ Op->Asl.AcpiBtype,
        /* 15 */ Op->Asl.FinalAmlLength,
        /* 16 */ Op->Asl.Column,
        /* 17 */ Op->Asl.LineNumber,
        /* 18 */ Op->Asl.EndLine,
        /* 19 */ Op->Asl.LogicalLineNumber,
        /* 20 */ Op->Asl.EndLogicalLine);

    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    CgLocalWriteAmlData
 *
 * PARAMETERS:  Op              - Current parse op
 *              Buffer          - Buffer to write
 *              Length          - Size of data in buffer
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write a buffer of AML data to the AML output file.
 *
 ******************************************************************************/

static void
CgLocalWriteAmlData (
    ACPI_PARSE_OBJECT       *Op,
    void                    *Buffer,
    UINT32                  Length)
{

    /* Write the raw data to the AML file */

    FlWriteFile (ASL_FILE_AML_OUTPUT, Buffer, Length);

    /* Update the final AML length for this node (used for listings) */

    if (Op)
    {
        Op->Asl.FinalAmlLength += Length;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CgWriteAmlDefBlockComment
 *
 * PARAMETERS:  Op              - Current parse op
 *
 * RETURN:      None
 *
 * DESCRIPTION: For -ca: write all comments for a particular definition block.
 *              For definition blocks, the comments need to come after the 
 *              definition block header. The regular comments above the 
 *              definition block would be categorized as 
 *              STD_DEFBLK_COMMENT and comments after the closing brace
 *              is categorized as END_DEFBLK_COMMENT.
 *
 ******************************************************************************/

static void
CgWriteAmlDefBlockComment(
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   CommentOpcode;
    UINT8                   CommentOption = FILENAME_COMMENT;
    ACPI_COMMENT_LIST_NODE  *Current;
    char                    *NewFilename; 
    char                    *Position;
    char                    *DirectoryPosition;


    if (Op->Asl.ParseOpcode != PARSEOP_DEFINITION_BLOCK)
    {
        return;
    }

    CommentOpcode = (UINT8)AML_COMMENT_OP;
    Current = Op->Asl.CommentList;

    printf ("Printing comments for a definition block..\n");
    
    /* first, print the file name comment after changing .asl to .dsl */

    NewFilename = UtStringCacheCalloc (strlen (Op->Asl.Filename)); 
    strcpy (NewFilename, Op->Asl.Filename);
    DirectoryPosition = strrchr (NewFilename, '/');
    Position = strrchr (NewFilename, '.');

    if (Position && (Position > DirectoryPosition))
    {
        /* Tack on the new suffix */

        Position++;
        *Position = 0;
        strcat (Position, FILE_SUFFIX_DISASSEMBLY);
    }
    else
    {
        /* No dot, add one and then the suffix */

        strcat (NewFilename, ".");
        strcat (NewFilename, FILE_SUFFIX_DISASSEMBLY);
    }
    
    CgLocalWriteAmlData (Op, &CommentOpcode, 1);
    CgLocalWriteAmlData (Op, &CommentOption, 1);

    /* +1 is what emits the 0x00 at the end of this opcode. */

    CgLocalWriteAmlData (Op, NewFilename, strlen (NewFilename) + 1); 

    CommentOption = STD_DEFBLK_COMMENT;
    while (Current)
    {
        CgLocalWriteAmlData (Op, &CommentOpcode, 1);
        CgLocalWriteAmlData (Op, &CommentOption, 1);

        /* +1 is what emits the 0x00 at the end of this opcode. */

        CgLocalWriteAmlData (Op, Current->Comment, strlen (Current->Comment) + 1); 
        printf ("Printing comment: %s\n", Current->Comment);
        Current = Current->Next;
    }
    Op->Asl.CommentList = NULL;
        
    /* print any Inline comments associated with this node */

    if (Op->Asl.CloseBraceComment)
    {
        CommentOption = END_DEFBLK_COMMENT;
        CgLocalWriteAmlData (Op, &CommentOpcode, 1);
        CgLocalWriteAmlData (Op, &CommentOption, 1);

        /* +1 is what emits the 0x00 at the end of this opcode. */

        CgLocalWriteAmlData (Op, Op->Asl.CloseBraceComment, strlen (Op->Asl.CloseBraceComment) + 1); 
        Op->Asl.CloseBraceComment = NULL;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CgChangeFileExt
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
CgChangeFileExt(
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
 * FUNCTION:    CgWriteAmlComment
 *
 * PARAMETERS:  Op              - Current parse op
 *
 * RETURN:      None
 *
 * DESCRIPTION: For -ca: write all comments pertaining to the current parse op
 *
 ******************************************************************************/

static void
CgWriteAmlComment(
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   CommentOpcode;
    ACPI_COMMENT_LIST_NODE  *Current;
    UINT8                   CommentOption;
    char                    *NewFilename;
    char                    *ParentFilename;

    if (Op->Asl.ParseOpcode == PARSEOP_DEFINITION_BLOCK)
    {
        return;
    }

    CommentOpcode = (UINT8)AML_COMMENT_OP;
    Current = Op->Asl.CommentList;

    /* Print out the filename comment if needed */
    if (Op->Asl.FileChanged)
    {

        /* first, print the file name comment after changing .asl to .dsl */

        NewFilename = CgChangeFileExt(Op->Asl.Filename, FILE_SUFFIX_DISASSEMBLY);

        printf ("Writing file comment, \"%s\" for %s\n", NewFilename, Op->Asl.ParseOpName);
    
        CommentOption = FILENAME_COMMENT;
        CgLocalWriteAmlData (Op, &CommentOpcode, 1);
        CgLocalWriteAmlData (Op, &CommentOption, 1);
        CgLocalWriteAmlData (Op, NewFilename, strlen (NewFilename) + 1); 

        if (Op->Asl.ParentFilename && strcmp (Op->Asl.ParentFilename, Op->Asl.Filename))
        { 
            ParentFilename = CgChangeFileExt(Op->Asl.ParentFilename, FILE_SUFFIX_DISASSEMBLY);
            CommentOption = PARENTFILENAME_COMMENT;
            CgLocalWriteAmlData (Op, &CommentOpcode, 1);
            CgLocalWriteAmlData (Op, &CommentOption, 1);
            CgLocalWriteAmlData (Op, ParentFilename, strlen (ParentFilename) + 1); 
        }
       
 
        /* prevent multiple writes of the same comment */

        Op->Asl.FileChanged = FALSE;
    }

    /*
     * Regular comments are stored in a list of comments within an Op.
     * If there is a such list in this node, print out the comment
     * as byte code.
     */
    //printf ("Printing comments for the following opcode: %s.\n", Op->Asl.ParseOpName);
    while (Current)
    {
        CommentOption = STANDARD_COMMENT;
        CgLocalWriteAmlData (Op, &CommentOpcode, 1);
        CgLocalWriteAmlData (Op, &CommentOption, 1);

        /* +1 is what emits the 0x00 at the end of this opcode. */

        CgLocalWriteAmlData (Op, Current->Comment, strlen (Current->Comment) + 1); 
        printf ("Printing comment: %s\n", Current->Comment);
        Current = Current->Next;
    }

    Op->Asl.CommentList = NULL;
        
    /* print any Inline comments associated with this node */

    if (Op->Asl.InlineComment)
    {
        CommentOption = INLINE_COMMENT;
        CgLocalWriteAmlData (Op, &CommentOpcode, 1);
        CgLocalWriteAmlData (Op, &CommentOption, 1);
        // +1 is what emits the 0x00 at the end of this opcode.
        CgLocalWriteAmlData (Op, Op->Asl.InlineComment, strlen (Op->Asl.InlineComment) + 1); 
        Op->Asl.InlineComment = NULL;
    }

    if (Op->Asl.EndNodeComment)
    {
        CommentOption = ENDNODE_COMMENT;
        CgLocalWriteAmlData (Op, &CommentOpcode, 1);
        CgLocalWriteAmlData (Op, &CommentOption, 1);
        // +1 is what emits the 0x00 at the end of this opcode.
        CgLocalWriteAmlData (Op, Op->Asl.EndNodeComment, strlen (Op->Asl.EndNodeComment) + 1); 
        Op->Asl.EndNodeComment = NULL;
    }

    if (Op->Asl.OpenBraceComment)
    {
        CommentOption = OPENBRACE_COMMENT;
        CgLocalWriteAmlData (Op, &CommentOpcode, 1);
        CgLocalWriteAmlData (Op, &CommentOption, 1);
        // +1 is what emits the 0x00 at the end of this opcode.
        CgLocalWriteAmlData (Op, Op->Asl.OpenBraceComment, strlen (Op->Asl.OpenBraceComment) + 1); 
        Op->Asl.OpenBraceComment = NULL;
    }

    if (Op->Asl.CloseBraceComment)
    {
        CommentOption = CLOSEBRACE_COMMENT;
        CgLocalWriteAmlData (Op, &CommentOpcode, 1);
        CgLocalWriteAmlData (Op, &CommentOption, 1);
        // +1 is what emits the 0x00 at the end of this opcode.
        CgLocalWriteAmlData (Op, Op->Asl.CloseBraceComment, strlen (Op->Asl.CloseBraceComment) + 1); 
        Op->Asl.CloseBraceComment = NULL;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CgWriteAmlOpcode
 *
 * PARAMETERS:  Op            - Parse node with an AML opcode
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Write the AML opcode corresponding to a parse node.
 *
 ******************************************************************************/

static void
CgWriteAmlOpcode (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   PkgLenFirstByte;
    UINT32                  i;
    union {
        UINT16                  Opcode;
        UINT8                   OpcodeBytes[2];
    } Aml;
    union {
        UINT32                  Len;
        UINT8                   LenBytes[4];
    } PkgLen;


    /* We expect some DEFAULT_ARGs, just ignore them */

    if (Op->Asl.ParseOpcode == PARSEOP_DEFAULT_ARG)
    {
        return;
    }

    /*
     * Before printing the bytecode, generate comment byte codes 
     * associated with this node.
     */
    if (Gbl_CaptureComments)
    {
        CgWriteAmlComment(Op);
    }

    switch (Op->Asl.AmlOpcode)
    {
    case AML_UNASSIGNED_OPCODE:

        /* These opcodes should not get here */

        printf ("Found a node with an unassigned AML opcode\n");
        FlPrintFile (ASL_FILE_STDERR,
            "Found a node with an unassigned AML opcode\n");
        return;

    case AML_INT_RESERVEDFIELD_OP:

        /* Special opcodes for within a field definition */

        Aml.Opcode = AML_FIELD_OFFSET_OP;
        break;

    case AML_INT_ACCESSFIELD_OP:

        Aml.Opcode = AML_FIELD_ACCESS_OP;
        break;

    case AML_INT_CONNECTION_OP:

        Aml.Opcode = AML_FIELD_CONNECTION_OP;
        break;

    default:

        Aml.Opcode = Op->Asl.AmlOpcode;
        break;
    }


    switch (Aml.Opcode)
    {
    case AML_PACKAGE_LENGTH:

        /* Value is the length to be encoded (Used in field definitions) */

        PkgLen.Len = (UINT32) Op->Asl.Value.Integer;
        break;

    default:

        /* Check for two-byte opcode */

        if (Aml.Opcode > 0x00FF)
        {
            /* Write the high byte first */

            CgLocalWriteAmlData (Op, &Aml.OpcodeBytes[1], 1);
        }

        CgLocalWriteAmlData (Op, &Aml.OpcodeBytes[0], 1);

        /* Subtreelength doesn't include length of package length bytes */

        PkgLen.Len = Op->Asl.AmlSubtreeLength + Op->Asl.AmlPkgLenBytes;
        break;
    }

    /* Does this opcode have an associated "PackageLength" field? */

    if (Op->Asl.CompileFlags & NODE_AML_PACKAGE)
    {
        if (Op->Asl.AmlPkgLenBytes == 1)
        {
            /* Simplest case -- no bytes to follow, just write the count */

            CgLocalWriteAmlData (Op, &PkgLen.LenBytes[0], 1);
        }
        else if (Op->Asl.AmlPkgLenBytes != 0)
        {
            /*
             * Encode the "bytes to follow" in the first byte, top two bits.
             * The low-order nybble of the length is in the bottom 4 bits
             */
            PkgLenFirstByte = (UINT8)
                (((UINT32) (Op->Asl.AmlPkgLenBytes - 1) << 6) |
                (PkgLen.LenBytes[0] & 0x0F));

            CgLocalWriteAmlData (Op, &PkgLenFirstByte, 1);

            /*
             * Shift the length over by the 4 bits we just stuffed
             * in the first byte
             */
            PkgLen.Len >>= 4;

            /*
             * Now we can write the remaining bytes -
             * either 1, 2, or 3 bytes
             */
            for (i = 0; i < (UINT32) (Op->Asl.AmlPkgLenBytes - 1); i++)
            {
                CgLocalWriteAmlData (Op, &PkgLen.LenBytes[i], 1);
            }
        }
    }

    switch (Aml.Opcode)
    {
    case AML_BYTE_OP:

        CgLocalWriteAmlData (Op, &Op->Asl.Value.Integer, 1);
        break;

    case AML_WORD_OP:

        CgLocalWriteAmlData (Op, &Op->Asl.Value.Integer, 2);
       break;

    case AML_DWORD_OP:

        CgLocalWriteAmlData (Op, &Op->Asl.Value.Integer, 4);
        break;

    case AML_QWORD_OP:

        CgLocalWriteAmlData (Op, &Op->Asl.Value.Integer, 8);
        break;

    case AML_STRING_OP:

        CgLocalWriteAmlData (Op, Op->Asl.Value.String, Op->Asl.AmlLength);
        break;

    default:

        /* All data opcodes must appear above */

        break;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CgWriteTableHeader
 *
 * PARAMETERS:  Op        - The DEFINITIONBLOCK node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write a table header corresponding to the DEFINITIONBLOCK
 *
 ******************************************************************************/

static void
CgWriteTableHeader (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Child;
    UINT32                  CommentLength;
    ACPI_COMMENT_LIST_NODE  *Current;


    /* AML filename */

    Child = Op->Asl.Child;

    /* Signature */

    Child = Child->Asl.Next;
    strncpy (TableHeader.Signature, Child->Asl.Value.String, 4);

    /* Revision */

    Child = Child->Asl.Next;
    TableHeader.Revision = (UINT8) Child->Asl.Value.Integer;

    /* Command-line Revision override */

    if (Gbl_RevisionOverride)
    {
        TableHeader.Revision = Gbl_RevisionOverride;
    }

    /* OEMID */

    Child = Child->Asl.Next;
    strncpy (TableHeader.OemId, Child->Asl.Value.String, 6);

    /* OEM TableID */

    Child = Child->Asl.Next;
    strncpy (TableHeader.OemTableId, Child->Asl.Value.String, 8);

    /* OEM Revision */

    Child = Child->Asl.Next;
    TableHeader.OemRevision = (UINT32) Child->Asl.Value.Integer;

    /* Compiler ID */

    ACPI_MOVE_NAME (TableHeader.AslCompilerId, ASL_CREATOR_ID);

    /* Compiler version */

    TableHeader.AslCompilerRevision = ACPI_CA_VERSION;

    /* Table length. Checksum zero for now, will rewrite later */

    TableHeader.Length = sizeof (ACPI_TABLE_HEADER) +
        Op->Asl.AmlSubtreeLength;

    /* Calculate the comment lengths for this definition block */

    if (Gbl_CaptureComments)
    {
        printf ("====================Calculating comment lengths for %s====================\n",  Op->Asl.ParseOpName);
        TableHeader.Length += strlen (Gbl_ParseTreeRoot->Asl.Filename) + 3;
        if (Op->Asl.CommentList!=NULL)
        {
            Current = Op->Asl.CommentList; 
            while (Current)
            {
                CommentLength = strlen (Current->Comment)+3;
                printf ("Length of standard comment +3 (including space for 0xA9 0x01 and 0x00): %d\n", CommentLength);
                printf ("**********Comment string: %s\n\n", Current->Comment);
                TableHeader.Length += CommentLength;
                Current = Current->Next;
            }
        }

        if (Op->Asl.CloseBraceComment!=NULL)
        {
            CommentLength = strlen (Op->Asl.CloseBraceComment)+3;
            printf ("Length of inline comment +3 (including space for 0xA9 0x02 and 0x00): %d\n", CommentLength);
            printf ("**********Comment string: %s\n\n", Op->Asl.CloseBraceComment);
            TableHeader.Length += CommentLength;
        }
    }

    TableHeader.Checksum = 0;

    Op->Asl.FinalAmlOffset = ftell (Gbl_Files[ASL_FILE_AML_OUTPUT].Handle);

    /* Write entire header and clear the table header global */

    CgLocalWriteAmlData (Op, &TableHeader, sizeof (ACPI_TABLE_HEADER));
    memset (&TableHeader, 0, sizeof (ACPI_TABLE_HEADER));
}


/*******************************************************************************
 *
 * FUNCTION:    CgUpdateHeader
 *
 * PARAMETERS:  Op                  - Op for the Definition Block
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Complete the ACPI table by calculating the checksum and
 *              re-writing the header for the input definition block
 *
 ******************************************************************************/

static void
CgUpdateHeader (
    ACPI_PARSE_OBJECT       *Op)
{
    signed char             Sum;
    UINT32                  i;
    UINT32                  Length;
    UINT8                   FileByte;
    UINT8                   Checksum;


    /* Calculate the checksum over the entire definition block */

    Sum = 0;
    Length = sizeof (ACPI_TABLE_HEADER) + Op->Asl.AmlSubtreeLength;
    FlSeekFile (ASL_FILE_AML_OUTPUT, Op->Asl.FinalAmlOffset);
    for (i = 0; i < Length; i++)
    {
        if (FlReadFile (ASL_FILE_AML_OUTPUT, &FileByte, 1) != AE_OK)
        {
            printf ("EOF while reading checksum bytes\n");
            return;
        }

        Sum = (signed char) (Sum + FileByte);
    }

    Checksum = (UINT8) (0 - Sum);

    /* Re-write the the checksum byte */

    FlSeekFile (ASL_FILE_AML_OUTPUT, Op->Asl.FinalAmlOffset +
        ACPI_OFFSET (ACPI_TABLE_HEADER, Checksum));

    FlWriteFile (ASL_FILE_AML_OUTPUT, &Checksum, 1);
}


/*******************************************************************************
 *
 * FUNCTION:    CgCloseTable
 *
 * PARAMETERS:  None.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Complete the ACPI table by calculating the checksum and
 *              re-writing each table header. This allows support for
 *              multiple definition blocks in a single source file.
 *
 ******************************************************************************/

static void
CgCloseTable (
    void)
{
    ACPI_PARSE_OBJECT   *Op;


    /* Process all definition blocks */

    Op = Gbl_ParseTreeRoot->Asl.Child;
    while (Op)
    {
        CgUpdateHeader (Op);
        Op = Op->Asl.Next;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    CgWriteNode
 *
 * PARAMETERS:  Op            - Parse node to write.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Write the AML that corresponds to a parse node.
 *
 ******************************************************************************/

static void
CgWriteNode (
    ACPI_PARSE_OBJECT       *Op)
{
    ASL_RESOURCE_NODE       *Rnode;


    /* Write all comments here. */
    if (Gbl_CaptureComments)
    {
        CgWriteAmlComment(Op);
    }

    /* Always check for DEFAULT_ARG and other "Noop" nodes */
    /* TBD: this may not be the best place for this check */

    if ((Op->Asl.ParseOpcode == PARSEOP_DEFAULT_ARG)  ||
        (Op->Asl.ParseOpcode == PARSEOP_INCLUDE)      ||
        (Op->Asl.ParseOpcode == PARSEOP_INCLUDE_END))
    {
        return;
    }

    if ((Op->Asl.ParseOpcode == PARSEOP_EXTERNAL) &&
        Gbl_DoExternals == FALSE)
    {
        return;
    }

    Op->Asl.FinalAmlLength = 0;

    switch (Op->Asl.AmlOpcode)
    {
    case AML_RAW_DATA_BYTE:
    case AML_RAW_DATA_WORD:
    case AML_RAW_DATA_DWORD:
    case AML_RAW_DATA_QWORD:

        CgLocalWriteAmlData (Op, &Op->Asl.Value.Integer, Op->Asl.AmlLength);
        return;


    case AML_RAW_DATA_BUFFER:

        CgLocalWriteAmlData (Op, Op->Asl.Value.Buffer, Op->Asl.AmlLength);
        return;


    case AML_RAW_DATA_CHAIN:

        Rnode = ACPI_CAST_PTR (ASL_RESOURCE_NODE, Op->Asl.Value.Buffer);
        while (Rnode)
        {
            CgLocalWriteAmlData (Op, Rnode->Buffer, Rnode->BufferLength);
            Rnode = Rnode->Next;
        }
        return;

    default:

        /* Internal data opcodes must all appear above */

        break;
    }

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_DEFAULT_ARG:

        break;

    case PARSEOP_DEFINITION_BLOCK:

        CgWriteTableHeader (Op);
        if (Gbl_CaptureComments)
        {
            CgWriteAmlDefBlockComment (Op);
        }
        break;

    case PARSEOP_NAMESEG:
    case PARSEOP_NAMESTRING:
    case PARSEOP_METHODCALL:

        CgLocalWriteAmlData (Op, Op->Asl.Value.String, Op->Asl.AmlLength);
        break;

    default:

        CgWriteAmlOpcode (Op);
        break;
    }
}
