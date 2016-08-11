/******************************************************************************
 *
 * Module Name: aslsupport.l - Flex/lex scanner C support routines.
 *              NOTE: Included into aslcompile.l, not compiled by itself.
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

/* Configuration */

#define ASL_SPACES_PER_TAB      4

#define ASL_NORMAL_CHAR         0
#define ASL_ESCAPE_SEQUENCE     1
#define ASL_OCTAL_CONSTANT      2
#define ASL_HEX_CONSTANT        3


/* File node - used for "Include" operator file stack */

typedef struct asl_file_node
{
    FILE                    *File;
    UINT32                  CurrentLineNumber;
    YY_BUFFER_STATE         State;
    char                    *Filename;
    struct asl_file_node    *Next;

} ASL_FILE_NODE;

/* File stack for the "Include" operator (NOT #include operator) */

ASL_FILE_NODE               *Gbl_IncludeFileStack = NULL;


/* Definitions for comment state */

#define ASL_REGCOMMENT        1
#define ASL_INLINECOMMENT     2
#define ASL_OPENPARENCOMMENT  3
#define ASL_CLOSEPARENCOMMENT 4
#define ASL_OPENBRACECOMMENT  5
#define ASL_CLOSEBRACECOMMENT 6

/* Definitions for comment table entry */

#define ASL_NEWLINE    '\n'
#define ASL_OpenParen  '('
#define ASL_CLOSEPAREN ')'
#define ASL_COMMA      ','
#define ASL_OPENBRACE  '{'
#define ASL_CLOSEBRACE '}'
#define ASL_WHITESPACE ' '


/*******************************************************************************
 *
 * FUNCTION:    AslProcessCommentState
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
AslProcessCommentState (
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
            printf ("========================================================End Parsing paren/Brace node!\n");
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

/*    printf ("Comment type set to %d after processing the character %c\n", Gbl_CommentState.CommentType, input); */
    
}


/*******************************************************************************
 *
 * FUNCTION:    AslParserCleanup
 *
 * Used to delete the current buffer
 *
 ******************************************************************************/

void
AslParserCleanup (
    void)
{

    yy_delete_buffer (YY_CURRENT_BUFFER);
}


/*******************************************************************************
 *
 * FUNCTION:    AslDoLineDirective
 *
 * PARAMETERS:  None. Uses input() to access current source code line
 *
 * RETURN:      Updates global line number and filename
 *
 * DESCRIPTION: Handle #line directives emitted by the preprocessor.
 *
 * The #line directive is emitted by the preprocesser, and is used to
 * pass through line numbers from the original source code file to the
 * preprocessor output file (.i). This allows any compiler-generated
 * error messages to be displayed with the correct line number.
 *
 ******************************************************************************/

static void
AslDoLineDirective (
    void)
{
    int                     c;
    char                    *Token;
    UINT32                  LineNumber;
    char                    *Filename;
    UINT32                  i;

   Gbl_HasIncludeFiles = TRUE;

    /* Eat the entire line that contains the #line directive */

    Gbl_LineBufPtr = Gbl_CurrentLineBuffer;

    while ((c = input()) != '\n' && c != EOF)
    {
        *Gbl_LineBufPtr = c;
        Gbl_LineBufPtr++;
    }
    *Gbl_LineBufPtr = 0;

    /* First argument is the actual line number */

    Token = strtok (Gbl_CurrentLineBuffer, " ");
    if (!Token)
    {
        goto ResetAndExit;
    }

    /* First argument is the line number */

    LineNumber = (UINT32) UtDoConstant (Token);

    /* Emit the appropriate number of newlines */

    Gbl_CurrentColumn = 0;
    if (LineNumber > Gbl_CurrentLineNumber)
    {
        for (i = 0; i < (LineNumber - Gbl_CurrentLineNumber); i++)
        {
            FlWriteFile (ASL_FILE_SOURCE_OUTPUT, "\n", 1);
            Gbl_CurrentColumn++;
        }
    }

    FlSetLineNumber (LineNumber);

    /* Second argument is the optional filename (in double quotes) */

    Token = strtok (NULL, " \"");
    if (Token)
    {
        Filename = ACPI_ALLOCATE_ZEROED (strlen (Token) + 1);
        strcpy (Filename, Token);
        FlSetFilename (Filename);
    }

    /* Third argument is not supported at this time */

ResetAndExit:

    /* Reset globals for a new line */

    Gbl_CurrentLineOffset += Gbl_CurrentColumn;
    Gbl_CurrentColumn = 0;
    Gbl_LineBufPtr = Gbl_CurrentLineBuffer;
}


/*******************************************************************************
 *
 * FUNCTION:    AslPopInputFileStack
 *
 * PARAMETERS:  None
 *
 * RETURN:      0 if a node was popped, -1 otherwise
 *
 * DESCRIPTION: Pop the top of the input file stack and point the parser to
 *              the saved parse buffer contained in the fnode. Also, set the
 *              global line counters to the saved values. This function is
 *              called when an include file reaches EOF.
 *
 ******************************************************************************/

int
AslPopInputFileStack (
    void)
{
    ASL_FILE_NODE           *Fnode;


    Gbl_PreviousIncludeFilename = Gbl_Files[ASL_FILE_INPUT].Filename;
    Fnode = Gbl_IncludeFileStack;
    DbgPrint (ASL_PARSE_OUTPUT,
        "\nPop InputFile Stack, Fnode %p\n", Fnode);

    DbgPrint (ASL_PARSE_OUTPUT,
        "Include: Closing \"%s\"\n\n", Gbl_Files[ASL_FILE_INPUT].Filename);

    if (!Fnode)
    {
        return (-1);
    }

    /* Close the current include file */

    fclose (yyin);

    /* Update the top-of-stack */

    Gbl_IncludeFileStack = Fnode->Next;

    /* Reset global line counter and filename */

    Gbl_Files[ASL_FILE_INPUT].Filename = Fnode->Filename;
    Gbl_CurrentLineNumber = Fnode->CurrentLineNumber;

    /* Point the parser to the popped file */

    yy_delete_buffer (YY_CURRENT_BUFFER);
    yy_switch_to_buffer (Fnode->State);

    /* All done with this node */

    ACPI_FREE (Fnode);
    return (0);
}


/*******************************************************************************
 *
 * FUNCTION:    AslPushInputFileStack
 *
 * PARAMETERS:  InputFile           - Open file pointer
 *              Filename            - Name of the file
 *
 * RETURN:      None
 *
 * DESCRIPTION: Push the InputFile onto the file stack, and point the parser
 *              to this file. Called when an include file is successfully
 *              opened.
 *
 ******************************************************************************/

void
AslPushInputFileStack (
    FILE                    *InputFile,
    char                    *Filename)
{
    ASL_FILE_NODE           *Fnode;
    YY_BUFFER_STATE         State;


    /* Save the current state in an Fnode */

    Fnode = UtLocalCalloc (sizeof (ASL_FILE_NODE));

    Fnode->File = yyin;
    Fnode->Next = Gbl_IncludeFileStack;
    Fnode->State = YY_CURRENT_BUFFER;
    Fnode->Filename = Gbl_Files[ASL_FILE_INPUT].Filename;
    Fnode->CurrentLineNumber = Gbl_CurrentLineNumber;

    /* Push it on the stack */

    Gbl_IncludeFileStack = Fnode;

    /* Point the parser to this file */

    State = yy_create_buffer (InputFile, YY_BUF_SIZE);
    yy_switch_to_buffer (State);

    DbgPrint (ASL_PARSE_OUTPUT,
        "\nPush InputFile Stack, returning %p\n\n", InputFile);

    /* Reset the global line count and filename */

    Gbl_Files[ASL_FILE_INPUT].Filename =
        UtStringCacheCalloc (strlen (Filename) + 1);

    strcpy (Gbl_Files[ASL_FILE_INPUT].Filename, Filename);

    Gbl_CurrentLineNumber = 1;
    yyin = InputFile;
}


/*******************************************************************************
 *
 * FUNCTION:    AslResetCurrentLineBuffer
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Reset the Line Buffer to zero, increment global line numbers.
 *
 ******************************************************************************/

void
AslResetCurrentLineBuffer (
    void)
{

    if (Gbl_Files[ASL_FILE_SOURCE_OUTPUT].Handle)
    {
        FlWriteFile (ASL_FILE_SOURCE_OUTPUT, Gbl_CurrentLineBuffer,
            Gbl_LineBufPtr - Gbl_CurrentLineBuffer);
    }

    Gbl_CurrentLineOffset += Gbl_CurrentColumn;
    Gbl_CurrentColumn = 0;

    Gbl_CurrentLineNumber++;
    Gbl_LogicalLineNumber++;
    Gbl_LineBufPtr = Gbl_CurrentLineBuffer;
}


/*******************************************************************************
 *
 * FUNCTION:    AslInsertLineBuffer
 *
 * PARAMETERS:  SourceChar          - One char from the input ASL source file
 *
 * RETURN:      None
 *
 * DESCRIPTION: Put one character of the source file into the temp line buffer
 *
 ******************************************************************************/

void
AslInsertLineBuffer (
    int                     SourceChar)
{
    UINT32                  i;
    UINT32                  Count = 1;


    if (SourceChar == EOF)
    {
        return;
    }

    Gbl_InputByteCount++;

    /* Handle tabs. Convert to spaces */

    if (SourceChar == '\t')
    {
        SourceChar = ' ';
        Count = ASL_SPACES_PER_TAB -
                    (Gbl_CurrentColumn & (ASL_SPACES_PER_TAB-1));
    }

    for (i = 0; i < Count; i++)
    {
        Gbl_CurrentColumn++;

        /* Insert the character into the line buffer */

        *Gbl_LineBufPtr = (UINT8) SourceChar;
        Gbl_LineBufPtr++;

        if (Gbl_LineBufPtr >
            (Gbl_CurrentLineBuffer + (Gbl_LineBufferSize - 1)))
        {
#if 0
            /*
             * Warning if we have split a long source line.
             * <Probably overkill>
             */
            sprintf (MsgBuffer, "Max %u", Gbl_LineBufferSize);
            AslCommonError (ASL_WARNING, ASL_MSG_LONG_LINE,
                Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
                Gbl_CurrentLineOffset, Gbl_CurrentColumn,
                Gbl_Files[ASL_FILE_INPUT].Filename, MsgBuffer);
#endif

            AslResetCurrentLineBuffer ();
        }
        else if (SourceChar == '\n')
        {
            /* End of line */

            AslResetCurrentLineBuffer ();

        }

        AslProcessCommentState (SourceChar);
    }
}

/*******************************************************************************
 *
 * FUNCTION:    count
 *
 * PARAMETERS:  yytext              - Contains the matched keyword.
 *              Type                - Keyword/Character type:
 *                                      0 = anything except a keyword
 *                                      1 = pseudo-keywords
 *                                      2 = non-executable ASL keywords
 *                                      3 = executable ASL keywords
 *
 * RETURN:      None
 *
 * DESCRIPTION: Count keywords and put them into the line buffer
 *
 ******************************************************************************/

static void
count (
    int                 Type)
{
    int                 i;


    switch (Type)
    {
    case 2:

        TotalKeywords++;
        TotalNamedObjects++;
        break;

    case 3:

        TotalKeywords++;
        TotalExecutableOpcodes++;
        break;

    default:

        break;
    }

    for (i = 0; (yytext[i] != 0) && (yytext[i] != EOF); i++)
    {
        AslInsertLineBuffer (yytext[i]);
        *Gbl_LineBufPtr = 0;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AddToCommentList
 *
 * PARAMETERS:  toAdd              - Contains the comment to be inserted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Count keywords and put them into the line buffer
 *
 ******************************************************************************/

static void
AddToCommentList (
    char*                   ToAdd)
{
   if (Gbl_Comment_List_Head)
   {
       Gbl_Comment_List_Tail->Next = UtCommentNodeCalloc ();
       Gbl_Comment_List_Tail = Gbl_Comment_List_Tail->Next;
   }
   else 
   {
       Gbl_Comment_List_Head = UtCommentNodeCalloc ();
       Gbl_Comment_List_Tail = Gbl_Comment_List_Head;
   }

   Gbl_Comment_List_Tail->Comment = ToAdd;
   
   return;
}

/*******************************************************************************
 *
 * FUNCTION:    AppendInlineComment
 *
 * PARAMETERS:  InlineComment      - Append to the end of this string.
 *              toAdd              - Contains the comment to be inserted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Concatenate
 *
 ******************************************************************************/

static char*
AppendInlineComment (
    char                    *InlineComment,
    char                    *ToAdd)
{
    printf ("Appending to current inline comment.\n");

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
 * FUNCTION:    AslPlaceComment
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
AslPlaceComment(
    UINT8                   Type,
    char                    *CommentString)
{
   
    printf ("Placing comment %s for type %d\n", CommentString, Type);
    switch (Type)
    {
        case ASL_REGCOMMENT:

            AddToCommentList (CommentString);
            break;

        case ASL_INLINECOMMENT:

            Gbl_CommentState.Latest_Parse_Node->Asl.InlineComment = 
                AppendInlineComment (Gbl_CommentState.Latest_Parse_Node->Asl.InlineComment,
                CommentString);
            break;

        case ASL_OPENPARENCOMMENT:

            Gbl_Inline_Comment_Buffer = 
                AppendInlineComment(Gbl_Inline_Comment_Buffer,
                CommentString);
            break;

        case ASL_CLOSEPARENCOMMENT:
           
            if (Gbl_CommentState.ParsingParenBraceNode !=NULL)
            {
                Gbl_CommentState.ParsingParenBraceNode->Asl.EndNodeComment = 
                    AppendInlineComment (Gbl_CommentState.ParsingParenBraceNode->Asl.EndNodeComment,
                    CommentString);
            }
            else
            {
                Gbl_CommentState.Latest_Parse_Node->Asl.EndNodeComment = 
                    AppendInlineComment (Gbl_CommentState.Latest_Parse_Node->Asl.EndNodeComment,
                    CommentString);
            }
            break;

        case ASL_OPENBRACECOMMENT:

            Gbl_CommentState.ParsingParenBraceNode->Asl.OpenBraceComment = CommentString;
            break;

        case ASL_CLOSEBRACECOMMENT:

            Gbl_CommentState.Latest_Parse_Node->Asl.CloseBraceComment = CommentString;
            break;

        default:

            break;

    }
}

/*******************************************************************************
 *
 * FUNCTION:    AslDoComment
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Process a standard comment.
 *
 ******************************************************************************/

static BOOLEAN
AslDoComment (
    void)
{

    char                    *LineToken;
    char                    *FinalLineToken;
    int                     i;
    BOOLEAN                 CharStart;
    int                     c;
    int                     c1 = 0;
    char                    *StringBuffer = MsgBuffer;
    char                    *EndBuffer = MsgBuffer + ASL_MSG_BUFFER_SIZE;
    char                    *CommentString;
    char                    *FinalCommentString;
    ASL_COMMENT_STATE       CurrentState = Gbl_CommentState; //for reference


    printf ("Multi-line comment\n");

    AslInsertLineBuffer ('/');
    *StringBuffer = '/';
    ++StringBuffer;
    AslInsertLineBuffer ('*');
    *StringBuffer = '*';
    ++StringBuffer;
 
loop:

    /* Eat chars until end-of-comment */

    while (((c = input ()) != '*') && (c != EOF))
    {
        AslInsertLineBuffer (c);
        *StringBuffer = c;
        ++StringBuffer;
        c1 = c;
    }

    if (c == EOF)
    {
        goto EarlyEOF;
    }

    /*
     * Check for nested comment -- can help catch cases where a previous
     * comment was accidently left unterminated
     */
    if ((c1 == '/') && (c == '*'))
    {
        AslCommonError (ASL_WARNING, ASL_MSG_NESTED_COMMENT,
            Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
            Gbl_InputByteCount, Gbl_CurrentColumn,
            Gbl_Files[ASL_FILE_INPUT].Filename, NULL);
    }

    /* Comment is closed only if the NEXT character is a slash */

    AslInsertLineBuffer (c);
    *StringBuffer = c;
    ++StringBuffer;

    if (((c1 = input ()) != '/') && (c1 != EOF))
    {
        unput (c1);
        goto loop;
    }

    if (c1 == EOF)
    {
        goto EarlyEOF;
    }
    if (StringBuffer > EndBuffer)
    { 
        goto BufferOverflow;
    }

    AslInsertLineBuffer (c1);
    *StringBuffer = c1;
    ++StringBuffer;

    *StringBuffer = 0; //null terminate this string

    if (Gbl_CaptureComments)
    {
        CommentString = UtStringCacheCalloc (strlen (MsgBuffer) + 1);
        strcpy (CommentString, MsgBuffer);

         printf ("CommentString: %s\n", CommentString);

        /* 
         * Determine whether if this comment spans multiple lines.
         * If so, break apart the comment by line so that it can be 
         * properly indented.
         */
        if (strchr (CommentString, '\n') != NULL)
        {
            /* 
             * Get the first token out. The for loop pads subsequent lines
             * for comments similar to the style of this comment. 
             */
            LineToken = strtok (CommentString, "\n");

            FinalLineToken = UtStringCacheCalloc (strlen (LineToken) + 1);
            strcpy (FinalLineToken, LineToken);
            
            AddToCommentList (LineToken);

            LineToken = strtok (NULL, "\n");
            while (LineToken != NULL)
            {
                /* 
                 * It is assumed that each line has some sort of indentation.
                 * This means that we need to find the first character that is not
                 * a white space within each line. 
                 */
                    
                CharStart = FALSE;
                for (i = 0; i < strlen (LineToken) + 1 && !CharStart; i++)
                {
                    if (LineToken[i] != ' ' && LineToken[i] != '\t')
                    {
                        CharStart = TRUE;
                        LineToken += i-1;
                        LineToken [0] = ' '; //Pad for Formatting.
                    }
                }

                FinalLineToken = UtStringCacheCalloc (strlen (LineToken) + 1);
                strcat (FinalLineToken, LineToken);
                AddToCommentList (FinalLineToken);
                LineToken = strtok (NULL,"\n");
            }
        }

        /* 
         * If this only spans a single line, check to see whether if this comment
         * appears on the same line as a line of code. If does, retain it's
         * position for stylistic reasons. If it doesn't, add it to the comment
         * List so that it can be associated with the next node that's created. 
         */
        else             
        {
           /* 
            * if this is not a regular comment, pad with extra spaces that appeared 
            * in the original source input to retain the original spacing.
            */

            FinalCommentString = UtStringCacheCalloc (strlen (CommentString) + CurrentState.SpacesBefore + 1);
            for (i=0; (CurrentState.CommentType != ASL_REGCOMMENT) && 
                (i < CurrentState.SpacesBefore); ++i)
            {
                 FinalCommentString[i] = ' ';
            }
            strcat (FinalCommentString, CommentString);
            AslPlaceComment (CurrentState.CommentType, FinalCommentString);    
        }
    }

    return (TRUE);


EarlyEOF:

    /*
     * Premature End-Of-File
     */
    AslCommonError (ASL_ERROR, ASL_MSG_EARLY_EOF,
        Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
        Gbl_CurrentLineOffset, Gbl_CurrentColumn,
        Gbl_Files[ASL_FILE_INPUT].Filename, NULL);
    return (FALSE);


BufferOverflow:

    /* Comment was too long */

    AslCommonError (ASL_ERROR, ASL_MSG_STRING_LENGTH,
        Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
        Gbl_CurrentLineOffset, Gbl_CurrentColumn,
        Gbl_Files[ASL_FILE_INPUT].Filename, "Max length 4096");
    return (FALSE);

}


/*******************************************************************************
 *
 * FUNCTION:    AslDoCommentType2
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Process a new "//" comment. Inline comments will be converted
 *              to "/ *" standard comments.
 *
 ******************************************************************************/

static BOOLEAN
AslDoCommentType2 (
    void)
{
    int                     c;
    int                     i;
    char                    *StringBuffer = MsgBuffer;
    char                    *EndBuffer = MsgBuffer + ASL_MSG_BUFFER_SIZE;
    char                    *CommentString;
    char                    *FinalCommentString;
    ASL_COMMENT_STATE       CurrentState = Gbl_CommentState; //for reference

    printf("Single-line comment\n");

    AslInsertLineBuffer ('/');
    *StringBuffer = '/';
    ++StringBuffer;
    AslInsertLineBuffer ('/');
    *StringBuffer = '/';
    ++StringBuffer;

    while (((c = input ()) != '\n') && (c != EOF))
    {
        AslInsertLineBuffer (c);
        *StringBuffer = c;
        ++StringBuffer;
    }

    if (c == EOF)
    {
        /* End of file is OK, change to newline. Let parser detect EOF later */

        c = '\n';
    }

    if (StringBuffer > EndBuffer)
    {
        goto BufferOverflow;       
    }
 
    // Since AslInsertLineBuffer (c) will clear the global flag, capture it here.

    AslInsertLineBuffer (c);
    *StringBuffer = 0; //null terminate this string
 
    if (Gbl_CaptureComments)
    {

        CommentString = UtStringCacheCalloc (strlen (MsgBuffer) + 1);
        strcpy (CommentString, MsgBuffer);

        /* If this comment lies on the same line as the latest parse node,
         * assign it to that node's CommentAfter field. Saving in this field
         * will allow us to support comments that come after code on the same
         * line as the code itself. For example, 
         * Name(A,"") //comment 
         *
         * will be retained rather than transformed into 
         *
         * Name(A,"") 
         * //comment 
         * 
         * For this case, we only need to add one comment since
         *
         * Name(A,"") //comment1 //comment2 ... more comments here.
         *
         * would be lexically analyzed as a single comment.
         *
         */
        /* Create a new string with the approperiate spaces. Since we need
         * to account for the proper spacing, the actual comment,
         * extra 2 spaces so that this comment can be converted to the "/ *"
         * style and the null terminator, the string would look something like
         * 
         * [ (spaces) (comment)  ( * /) ('\0') ]
         *
         */

        FinalCommentString = UtStringCacheCalloc (CurrentState.SpacesBefore + strlen (CommentString) + 3 + 1);

        for (i=0; (CurrentState.CommentType!=1) && (i<CurrentState.SpacesBefore); ++i)
        {
            FinalCommentString[i] = ' ';
        }
        strcat(FinalCommentString, CommentString);

        // convert to a "/ *" style comment. disable this????
//        strcat (FinalCommentString, " */");
//        FinalCommentString [SpaceCount + 1] = '*';

        FinalCommentString [CurrentState.SpacesBefore + strlen (CommentString) + 3] = 0;
        if (FinalCommentString[strlen (FinalCommentString) - 1] == 0x0D)
        {
            FinalCommentString[strlen(FinalCommentString)-1] = 0;  
        }
        AslPlaceComment(CurrentState.CommentType, FinalCommentString);    

    }

    return (TRUE);


BufferOverflow:

    /* Comment was too long */

    AslCommonError (ASL_ERROR, ASL_MSG_STRING_LENGTH,
        Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
        Gbl_CurrentLineOffset, Gbl_CurrentColumn,
        Gbl_Files[ASL_FILE_INPUT].Filename, "Max length 4096");
    return (FALSE);

}


/*******************************************************************************
 *
 * FUNCTION:    AslDoStringLiteral
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Process a string literal (surrounded by quotes)
 *
 ******************************************************************************/

static char
AslDoStringLiteral (
    void)
{
    char                *StringBuffer = MsgBuffer;
    char                *EndBuffer = MsgBuffer + ASL_MSG_BUFFER_SIZE;
    char                *CleanString;
    int                 StringChar;
    UINT32              State = ASL_NORMAL_CHAR;
    UINT32              i = 0;
    UINT8               Digit;
    char                ConvertBuffer[4];

    /*
     * Eat chars until end-of-literal.
     * NOTE:  Put back the original surrounding quotes into the
     * source line buffer.
     */
    AslInsertLineBuffer ('\"');
    while ((StringChar = input()) != EOF)
    {
        AslInsertLineBuffer (StringChar);

DoCharacter:
        switch (State)
        {
        case ASL_NORMAL_CHAR:

            switch (StringChar)
            {
            case '\\':
                /*
                 * Special handling for backslash-escape sequence. We will
                 * toss the backslash and translate the escape char(s).
                 */
                State = ASL_ESCAPE_SEQUENCE;
                continue;

            case '\"':

                /* String terminator */

                goto CompletedString;

            default:

                break;
            }
            break;


        case ASL_ESCAPE_SEQUENCE:

            State = ASL_NORMAL_CHAR;
            switch (StringChar)
            {
            case 'a':

                StringChar = 0x07;      /* BELL */
                break;

            case 'b':

                StringChar = 0x08;      /* BACKSPACE */
                break;

            case 'f':

                StringChar = 0x0C;      /* FORMFEED */
                break;

            case 'n':

                StringChar = 0x0A;      /* LINEFEED */
                break;

            case 'r':

                StringChar = 0x0D;      /* CARRIAGE RETURN*/
                break;

            case 't':

                StringChar = 0x09;      /* HORIZONTAL TAB */
                break;

            case 'v':

                StringChar = 0x0B;      /* VERTICAL TAB */
                break;

            case 'x':

                State = ASL_HEX_CONSTANT;
                i = 0;
                continue;

            case '\'':                  /* Single Quote */
            case '\"':                  /* Double Quote */
            case '\\':                  /* Backslash */

                break;

            default:

                /* Check for an octal digit (0-7) */

                if (ACPI_IS_OCTAL_DIGIT (StringChar))
                {
                    State = ASL_OCTAL_CONSTANT;
                    ConvertBuffer[0] = StringChar;
                    i = 1;
                    continue;
                }

                /* Unknown escape sequence issue warning, but use the character */

                AslCommonError (ASL_WARNING, ASL_MSG_INVALID_ESCAPE,
                    Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
                    Gbl_CurrentLineOffset, Gbl_CurrentColumn,
                    Gbl_Files[ASL_FILE_INPUT].Filename, NULL);
                break;
            }
            break;


        case ASL_OCTAL_CONSTANT:

            /* Up to three octal digits allowed */

            if (!ACPI_IS_OCTAL_DIGIT (StringChar) ||
                (i > 2))
            {
                /*
                 * Reached end of the constant. Convert the assembled ASCII
                 * string and resume processing of the next character
                 */
                ConvertBuffer[i] = 0;
                Digit = (UINT8) strtoul (ConvertBuffer, NULL, 8);

                /* Check for NULL or non-ascii character (ignore if so) */

                if ((Digit == 0) || (Digit > ACPI_ASCII_MAX))
                {
                    AslCommonError (ASL_WARNING, ASL_MSG_INVALID_STRING,
                        Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
                        Gbl_CurrentLineOffset, Gbl_CurrentColumn,
                        Gbl_Files[ASL_FILE_INPUT].Filename, NULL);
                }
                else
                {
                    *StringBuffer = (char) Digit;
                    StringBuffer++;
                    if (StringBuffer >= EndBuffer)
                    {
                        goto BufferOverflow;
                    }
                }

                State = ASL_NORMAL_CHAR;
                goto DoCharacter;
                break;
            }

            /* Append another digit of the constant */

            ConvertBuffer[i] = StringChar;
            i++;
            continue;

        case ASL_HEX_CONSTANT:

            /* Up to two hex digits allowed */

            if (!isxdigit (StringChar) ||
                (i > 1))
            {
                /*
                 * Reached end of the constant. Convert the assembled ASCII
                 * string and resume processing of the next character
                 */
                ConvertBuffer[i] = 0;
                Digit = (UINT8) strtoul (ConvertBuffer, NULL, 16);

                /* Check for NULL or non-ascii character (ignore if so) */

                if ((Digit == 0) || (Digit > ACPI_ASCII_MAX))
                {
                    AslCommonError (ASL_WARNING, ASL_MSG_INVALID_STRING,
                        Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
                        Gbl_CurrentLineOffset, Gbl_CurrentColumn,
                        Gbl_Files[ASL_FILE_INPUT].Filename, NULL);
                }
                else
                {
                    *StringBuffer = (char) Digit;
                    StringBuffer++;
                    if (StringBuffer >= EndBuffer)
                    {
                        goto BufferOverflow;
                    }
                }

                State = ASL_NORMAL_CHAR;
                goto DoCharacter;
                break;
            }

            /* Append another digit of the constant */

            ConvertBuffer[i] = StringChar;
            i++;
            continue;

        default:

            break;
        }

        /* Save the finished character */

        *StringBuffer = StringChar;
        StringBuffer++;
        if (StringBuffer >= EndBuffer)
        {
            goto BufferOverflow;
        }
    }

    /*
     * Premature End-Of-File
     */
    AslCommonError (ASL_ERROR, ASL_MSG_EARLY_EOF,
        Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
        Gbl_CurrentLineOffset, Gbl_CurrentColumn,
        Gbl_Files[ASL_FILE_INPUT].Filename, NULL);
    return (FALSE);


CompletedString:
    /*
     * Null terminate the input string and copy string to a new buffer
     */
    *StringBuffer = 0;

    CleanString = UtStringCacheCalloc (strlen (MsgBuffer) + 1);
    if (!CleanString)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_MEMORY_ALLOCATION,
            Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
            Gbl_CurrentLineOffset, Gbl_CurrentColumn,
            Gbl_Files[ASL_FILE_INPUT].Filename, NULL);
        return (FALSE);
    }

    strcpy (CleanString, MsgBuffer);
    AslCompilerlval.s = CleanString;
    return (TRUE);


BufferOverflow:

    /* Literal was too long */

    AslCommonError (ASL_ERROR, ASL_MSG_STRING_LENGTH,
        Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
        Gbl_CurrentLineOffset, Gbl_CurrentColumn,
        Gbl_Files[ASL_FILE_INPUT].Filename, "Max length 4096");
    return (FALSE);
}

