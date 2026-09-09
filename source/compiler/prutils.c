/******************************************************************************
 *
 * Module Name: prutils - Preprocessor utilities
 *
 *****************************************************************************/

/******************************************************************************
 *
 * Copyright (c) 1999 - 2026, Intel Corp.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 *
 *****************************************************************************/

#include "aslcompiler.h"

#define _COMPONENT          ASL_PREPROCESSOR
        ACPI_MODULE_NAME    ("prutils")


/******************************************************************************
 *
 * FUNCTION:    PrGetNextToken
 *
 * PARAMETERS:  Buffer              - Current line buffer
 *              MatchString         - String with valid token delimiters
 *              Next                - Set to next possible token in buffer
 *
 * RETURN:      Next token (null-terminated). Modifies the input line.
 *              Remainder of line is stored in *Next.
 *
 * DESCRIPTION: Local implementation of strtok() with local storage for the
 *              next pointer. Not only thread-safe, but allows multiple
 *              parsing of substrings such as expressions.
 *
 *****************************************************************************/

char *
PrGetNextToken (
    char                    *Buffer,
    char                    *MatchString,
    char                    **Next)
{
    char                    *TokenStart;


    if (!Buffer)
    {
        /* Use Next if it is valid */

        Buffer = *Next;
        if (!(*Next))
        {
            return (NULL);
        }
    }

    /* Skip any leading delimiters */

    while (*Buffer)
    {
        if (strchr (MatchString, *Buffer))
        {
            Buffer++;
        }
        else
        {
            break;
        }
    }

    /* Anything left on the line? */

    if (!(*Buffer))
    {
        *Next = NULL;
        return (NULL);
    }

    TokenStart = Buffer;

    /* Find the end of this token */

    while (*Buffer)
    {
        if (strchr (MatchString, *Buffer))
        {
            *Buffer = 0;
            *Next = Buffer+1;
            if (!**Next)
            {
                *Next = NULL;
            }

            return (TokenStart);
        }

        Buffer++;
    }

    *Next = NULL;
    return (TokenStart);
}


/*******************************************************************************
 *
 * FUNCTION:    PrError
 *
 * PARAMETERS:  Level               - Seriousness (Warning/error, etc.)
 *              MessageId           - Index into global message buffer
 *              Column              - Column in current line
 *
 * RETURN:      None
 *
 * DESCRIPTION: Preprocessor error reporting. Front end to AslCommonError2
 *
 ******************************************************************************/

void
PrError (
    UINT8                   Level,
    UINT16                  MessageId,
    UINT32                  Column)
{
#if 0
    AcpiOsPrintf ("%s (%u) : %s", AslGbl_Files[ASL_FILE_INPUT].Filename,
        AslGbl_CurrentLineNumber, AslGbl_CurrentLineBuffer);
#endif


    if (Column > 120)
    {
        Column = 0;
    }

    /* TBD: Need Logical line number? */

    AslCommonError2 (Level, MessageId,
        AslGbl_CurrentLineNumber, Column,
        AslGbl_CurrentLineBuffer,
        AslGbl_Files[ASL_FILE_INPUT].Filename, "Preprocessor");

    AslGbl_PreprocessorError = TRUE;
}


/*******************************************************************************
 *
 * FUNCTION:    PrReplaceResizeSubstring
 *
 * PARAMETERS:  Args                - Struct containing name, offset & usecount
 *              Diff1               - Difference in lengths when new < old
 *              Diff2               - Difference in lengths when new > old
 *              i                   - The curr. no. of iteration of replacement
 *              Token               - Substring that replaces Args->Name
 *              Stringize           - TRUE if the argument is stringized
 *
 * RETURN:      None
 *
 * DESCRIPTION: Advanced substring replacement in a string using resized buffer.
 *
 ******************************************************************************/

void
PrReplaceResizeSubstring(
    PR_MACRO_ARG            *Args,
    UINT32                  Diff1,
    UINT32                  Diff2,
    UINT32                  i,
    char                    *Token,
    BOOLEAN                 Stringize)
{
    UINT32                  b, PrevOffset;
    char                    *temp;
    char                    *NewBuffer;
    char                    CheckChar;
    const char              *MacroSeparators = PR_MACRO_SEPARATORS;
    /* For argument boundary checking, treat # as a separator too (for token pasting) */
    char                    ArgSeparatorsStr[256];
    const char              *ArgSeparators;
    char                    *SearchName = NULL;
    char                    *QuotedToken = NULL;
    UINT32                  SearchLength;
    ACPI_SIZE               CurrentLength;
    ACPI_SIZE               RequiredLength;
    ACPI_SIZE               ReplaceLength;
    BOOLEAN                 ValidBoundary;
    char                    BeforeChar;
    char                    AfterChar;

    /* Create ArgSeparators string by concatenating MacroSeparators with "#" */
    strcpy (ArgSeparatorsStr, MacroSeparators);
    strcat (ArgSeparatorsStr, "#");
    ArgSeparators = ArgSeparatorsStr;

    CurrentLength = strlen (AslGbl_MacroTokenBuffer);
    ReplaceLength = Stringize ? (strlen (Token) + 2) : strlen (Token);
    RequiredLength = CurrentLength + 1;

    if (ReplaceLength > strlen (Args->Name))
    {
        RequiredLength += (ReplaceLength - strlen (Args->Name));
    }

    NewBuffer = (char *) realloc (
        AslGbl_MacroTokenReplaceBuffer, RequiredLength);
    
    if (!NewBuffer)
    {
        PrError (ASL_ERROR, ASL_MSG_INVALID_INVOCATION, 0);
        return;
    }
    
    AslGbl_MacroTokenReplaceBuffer = NewBuffer;

    if (Stringize)
    {
        UINT32                  k;
        const char              *Src;

        SearchLength = strlen (Args->Name) + 1;
        SearchName = UtLocalCalloc (SearchLength + 1);
        SearchName[0] = '#';
        strcpy (&SearchName[1], Args->Name);

        /* Allocate space for escaped content plus surrounding quotes */
        QuotedToken = UtLocalCalloc ((2 * strlen (Token)) + 3);
        
        /* Build stringized token with proper escaping */
        QuotedToken[0] = '"';
        k = 1;
        for (Src = Token; *Src; Src++)
        {
            if (*Src == '\\' || *Src == '"')
            {
                QuotedToken[k++] = '\\';
            }
            QuotedToken[k++] = *Src;
        }
        QuotedToken[k++] = '"';
        QuotedToken[k] = '\0';

        PrevOffset = Args->Offset[i];
        temp = strstr (AslGbl_MacroTokenBuffer, SearchName);
        if (temp == NULL)
        {
            goto StringizeExit;
        }

ResetStringize:
        temp = strstr (temp, SearchName);
        if (temp == NULL)
        {
            goto StringizeExit;
        }

        Args->Offset[i] = strlen (AslGbl_MacroTokenBuffer) -
            strlen (temp);
        
        /* Validate token boundaries using ArgSeparators (includes #) */
        CheckChar = AslGbl_MacroTokenBuffer[(Args->Offset[i] + SearchLength)];
        ValidBoundary = (strchr (ArgSeparators,
                (unsigned char) CheckChar) || CheckChar == '\0');
        
        /* If not at start of buffer, also check preceding character */
        if (Args->Offset[i] != 0)
        {
            ValidBoundary = ValidBoundary &&
                (strchr (ArgSeparators,
                    (unsigned char) AslGbl_MacroTokenBuffer[(Args->Offset[i] - 1)]));
        }
        
        if (!ValidBoundary)
        {
            temp += SearchLength;
            goto ResetStringize;
        }

        PrReplaceData (
            &AslGbl_MacroTokenBuffer[Args->Offset[i]],
            SearchLength, QuotedToken, strlen (QuotedToken));

        Args->Offset[i] = PrevOffset;

StringizeExit:
        ACPI_FREE (SearchName);
        ACPI_FREE (QuotedToken);
        return;
    }

    /*
     * When the replacement argument (during invocation) length
     * < replaced parameter (in the macro function definition
     * and its expansion) length
     */
    if (Diff1 != 0)
    {
        /*
         * We save the offset value to reset it after replacing each
         * instance of each arg and setting the offset value to
         * the start of the arg to be replaced since it changes
         * with each iteration when arg length != token length
         */
        PrevOffset = Args->Offset[i];
        temp = strstr (AslGbl_MacroTokenBuffer, Args->Name);
        if (temp == NULL)
        {
            return;
        }

ResetHere1:
        temp = strstr (temp, Args->Name);
        if (temp == NULL)
        {
            return;
        }
        Args->Offset[i] = strlen (AslGbl_MacroTokenBuffer) -
            strlen (temp);
        
        /* Check token boundaries for all cases, including offset == 0 */
        if (Args->Offset[i] == 0)
        {
            /* At start of buffer: only need to check after token */
            AfterChar = AslGbl_MacroTokenBuffer[strlen (Args->Name)];
            ValidBoundary = (!AfterChar || strchr (ArgSeparators, (unsigned char) AfterChar));
        }
        else
        {
            /* Check both before and after token */
            BeforeChar = AslGbl_MacroTokenBuffer[(Args->Offset[i] - 1)];
            AfterChar = AslGbl_MacroTokenBuffer[(Args->Offset[i] + strlen (Args->Name))];
            ValidBoundary = (strchr (ArgSeparators, (unsigned char) BeforeChar)) &&
                (!AfterChar || strchr (ArgSeparators, (unsigned char) AfterChar));
        }
        
        if (!ValidBoundary)
        {
            temp += strlen (Args->Name);
            goto ResetHere1;
        }

        /*
         * For now, we simply set the extra char positions (generated
         * due to longer name replaced by shorter name) to whitespace
         * chars so it will be ignored during compilation
         */
        b = strlen (Token) + Args->Offset[i];
        memset (&AslGbl_MacroTokenBuffer[b], ' ', Diff1);

# if 0

    /* Work in progress as of 03/08/2023 - experimental 'if' block
     * to test code for removing extra whitespaces from the macro
     * replacement when replacement arg < replaced param
     */
        char Buff[8192];
        /* char* Replace; */
        /* Replace = Buff; */

        for (j = 0; j < strlen (AslGbl_MacroTokenBuffer); j++)
        {
            Buff[j] = AslGbl_MacroTokenBuffer[j];
        }
        Buff[strlen (AslGbl_MacroTokenBuffer)] = '\0';
        /* fprintf(stderr, "Buff: %s\n", Buff); */

        UINT32 len = strlen (Buff);

        for (j = 0; j < len; j++)
        {
            if (Buff[0] == ' ')
            {
                for (j = 0; j < (len - 1); j++)
                {
                    Buff[j] = Buff[j + 1];
                }
                Buff[j] = '\0';
                len--;
                j = -1;
                continue;
            }

            if (Buff[j] == ' ' && Buff[j + 1] == ' ')
            {
                for (k = 0; k < (len - 1); k++)
                {
                    Buff[j] = Buff[j + 1];
                }
                Buff[j] = '\0';
                len--;
                j--;
            }
        }
        /* fprintf(stderr, "Buff: %s\n", Buff); */

        for (k = 0; k < strlen (Buff); k++)
        {
            AslGbl_MacroTokenBuffer[k] = Buff[k];
        }
#endif

        PrReplaceData (
            &AslGbl_MacroTokenBuffer[Args->Offset[i]],
            strlen (Args->Name), Token, strlen (Token));

        temp = NULL;
        Args->Offset[i] = PrevOffset;
    }

    /*
     * When the replacement argument (during invocation) length
     * > replaced parameter (in the macro function definition
     * and its expansion) length
     */
    else if (Diff2 != 0)
    {
        /* Doing the same thing with offset value as for prev case */

        PrevOffset = Args->Offset[i];
        temp = strstr (AslGbl_MacroTokenBuffer, Args->Name);
        if (temp == NULL)
        {
            return;
        }

ResetHere2:
        temp = strstr (temp, Args->Name);
        if (temp == NULL)
        {
            return;
        }
        Args->Offset[i] = strlen (AslGbl_MacroTokenBuffer) -
            strlen (temp);
        
        /* Check token boundaries for all cases, including offset == 0 */
        if (Args->Offset[i] == 0)
        {
            /* At start of buffer: only need to check after token */
            AfterChar = AslGbl_MacroTokenBuffer[strlen (Args->Name)];
            ValidBoundary = (!AfterChar || strchr (ArgSeparators, (unsigned char) AfterChar));
        }
        else
        {
            /* Check both before and after token */
            BeforeChar = AslGbl_MacroTokenBuffer[(Args->Offset[i] - 1)];
            AfterChar = AslGbl_MacroTokenBuffer[(Args->Offset[i] + strlen (Args->Name))];
            ValidBoundary = (strchr (ArgSeparators, (unsigned char) BeforeChar)) &&
                (!AfterChar || strchr (ArgSeparators, (unsigned char) AfterChar));
        }
        
        if (!ValidBoundary)
        {
            temp+= strlen (Args->Name);
            goto ResetHere2;
        }

        /*
         * We will need to allocate some extra space in our buffer to
         * accommodate the increase in the replacement string length
         * over the shorter outgoing arg string and do the replacement
         * at the correct offset value which is resetted every iteration
         */
        memcpy (AslGbl_MacroTokenReplaceBuffer, AslGbl_MacroTokenBuffer,
            Args->Offset[i]);
        AslGbl_MacroTokenReplaceBuffer[Args->Offset[i]] = '\0';
        strcat (AslGbl_MacroTokenReplaceBuffer, Token);
        strcat (AslGbl_MacroTokenReplaceBuffer, (AslGbl_MacroTokenBuffer +
            (Args->Offset[i] + strlen (Args->Name))));

        strcpy (AslGbl_MacroTokenBuffer, AslGbl_MacroTokenReplaceBuffer);

        temp = NULL;
        Args->Offset[i] = PrevOffset;
    }

    /*
     * When the replacement argument (during invocation) length =
     * replaced parameter (in the macro function definition and
     * its expansion) length
     */
    else
    {

        /*
         * We still need to reset the offset for each iteration even when
         * arg and param lengths are same since any macro func invocation
         * could use various cases for each separate arg-param pair
         */
        PrevOffset = Args->Offset[i];
        temp = strstr (AslGbl_MacroTokenBuffer, Args->Name);
        if (temp == NULL)
        {
            return;
        }

ResetHere3:
        temp = strstr (temp, Args->Name);
        if (temp == NULL)
        {
            return;
        }
        Args->Offset[i] = strlen (AslGbl_MacroTokenBuffer) -
            strlen (temp);
        
        /* Check token boundaries for all cases, including offset == 0 */
        if (Args->Offset[i] == 0)
        {
            /* At start of buffer: only need to check after token */
            AfterChar = AslGbl_MacroTokenBuffer[strlen (Args->Name)];
            ValidBoundary = (!AfterChar || strchr (ArgSeparators, (unsigned char) AfterChar));
        }
        else
        {
            /* Check both before and after token */
            BeforeChar = AslGbl_MacroTokenBuffer[(Args->Offset[i] - 1)];
            AfterChar = AslGbl_MacroTokenBuffer[(Args->Offset[i] + strlen (Args->Name))];
            ValidBoundary = (strchr (ArgSeparators, (unsigned char) BeforeChar)) &&
                (!AfterChar || strchr (ArgSeparators, (unsigned char) AfterChar));
        }
        
        if (!ValidBoundary)
        {
            temp += strlen (Args->Name);
            goto ResetHere3;
        }

        PrReplaceData (
            &AslGbl_MacroTokenBuffer[Args->Offset[i]],
            strlen (Args->Name), Token, strlen (Token));
        temp = NULL;
        Args->Offset[i] = PrevOffset;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    PrReplaceData
 *
 * PARAMETERS:  Buffer              - Original(target) buffer pointer
 *              LengthToRemove      - Length to be removed from target buffer
 *              BufferToAdd         - Data to be inserted into target buffer
 *              LengthToAdd         - Length of BufferToAdd
 *
 * RETURN:      Pointer to where the buffer is replaced with data
 *
 * DESCRIPTION: Generic buffer data replacement.
 *
 ******************************************************************************/

char *
PrReplaceData (
    char                    *Buffer,
    UINT32                  LengthToRemove,
    char                    *BufferToAdd,
    UINT32                  LengthToAdd)
{
    UINT32                  BufferLength;


    /* Buffer is a string, so the length must include the terminating zero */

    BufferLength = strlen (Buffer) + 1;

    if (LengthToRemove != LengthToAdd)
    {
        /*
         * Move some of the existing data
         * 1) If adding more bytes than removing, make room for the new data
         * 2) if removing more bytes than adding, delete the extra space
         */
        if (LengthToRemove > 0)
        {
            memmove ((Buffer + LengthToAdd), (Buffer + LengthToRemove),
                (BufferLength - LengthToRemove));
        }
    }


    /* Now we can move in the new data */

    if (LengthToAdd > 0)
    {
        memmove (Buffer, BufferToAdd, LengthToAdd);
    }
    return (Buffer + LengthToAdd);
}


/*******************************************************************************
 *
 * FUNCTION:    PrResolveTokenPasting
 *
 * DESCRIPTION: Resolve simple token pasting by removing ## and adjacent
 *              whitespace in the expanded macro buffer.
 *
 ******************************************************************************/

void
PrResolveTokenPasting (
    void)
{
    char                    *Ptr;
    char                    *Start;
    char                    *End;
    BOOLEAN                 InString = FALSE;


    Ptr = AslGbl_MacroTokenBuffer;
    while (*Ptr)
    {
        /* Track entry/exit from quoted strings */
        if (*Ptr == '"')
        {
            InString = (BOOLEAN) !InString;
            Ptr++;
            continue;
        }

        /* Skip over string contents */
        if (InString)
        {
            /* Handle escaped quotes and backslashes */
            if (*Ptr == '\\' && Ptr[1])
            {
                Ptr += 2;
            }
            else
            {
                Ptr++;
            }
            continue;
        }

        /* Look for ## token pasting operator outside strings */
        if (*Ptr == '#' && Ptr[1] == '#')
        {
            Start = Ptr;
            while ((Start > AslGbl_MacroTokenBuffer) &&
                isspace ((unsigned char) Start[-1]))
            {
                Start--;
            }

            End = Ptr + 2;
            while (*End && isspace ((unsigned char) *End))
            {
                End++;
            }

            PrReplaceData (Start, (UINT32) (End - Start), "", 0);
            /* Don't increment Ptr; the replacement shifted buffer */
        }
        else
        {
            Ptr++;
        }
    }
}


/*******************************************************************************
 *
 * FUNCTION:    PrOpenIncludeFile
 *
 * PARAMETERS:  Filename            - Filename or pathname for include file
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Open an include file and push it on the input file stack.
 *
 ******************************************************************************/

FILE *
PrOpenIncludeFile (
    char                    *Filename,
    char                    *OpenMode,
    char                    **FullPathname)
{
    FILE                    *IncludeFile;
    ASL_INCLUDE_DIR         *NextDir;


    /* Start the actual include file on the next line */

    AslGbl_CurrentLineOffset++;

    /* Attempt to open the include file */
    /* If the file specifies an absolute path, just open it */

    if ((Filename[0] == '/')  ||
        (Filename[0] == '\\') ||
        (Filename[1] == ':'))
    {
        IncludeFile = PrOpenIncludeWithPrefix (
            "", Filename, OpenMode, FullPathname);
        if (!IncludeFile)
        {
            goto ErrorExit;
        }
        return (IncludeFile);
    }

    /*
     * The include filename is not an absolute path.
     *
     * First, search for the file within the "local" directory -- meaning
     * the same directory that contains the source file.
     *
     * Construct the file pathname from the global directory name.
     */
    IncludeFile = PrOpenIncludeWithPrefix (
        AslGbl_DirectoryPath, Filename, OpenMode, FullPathname);
    if (IncludeFile)
    {
        return (IncludeFile);
    }

    /*
     * Second, search for the file within the (possibly multiple)
     * directories specified by the -I option on the command line.
     */
    NextDir = AslGbl_IncludeDirList;
    while (NextDir)
    {
        IncludeFile = PrOpenIncludeWithPrefix (
            NextDir->Dir, Filename, OpenMode, FullPathname);
        if (IncludeFile)
        {
            return (IncludeFile);
        }

        NextDir = NextDir->Next;
    }

    /* We could not open the include file after trying very hard */

ErrorExit:
    sprintf (AslGbl_MainTokenBuffer, "%s, %s", Filename, strerror (errno));
    PrError (ASL_ERROR, ASL_MSG_INCLUDE_FILE_OPEN, 0);
    return (NULL);
}


/*******************************************************************************
 *
 * FUNCTION:    FlOpenIncludeWithPrefix
 *
 * PARAMETERS:  PrefixDir       - Prefix directory pathname. Can be a zero
 *                                length string.
 *              Filename        - The include filename from the source ASL.
 *
 * RETURN:      Valid file descriptor if successful. Null otherwise.
 *
 * DESCRIPTION: Open an include file and push it on the input file stack.
 *
 ******************************************************************************/

FILE *
PrOpenIncludeWithPrefix (
    char                    *PrefixDir,
    char                    *Filename,
    char                    *OpenMode,
    char                    **FullPathname)
{
    FILE                    *IncludeFile;
    char                    *Pathname;


    /* Build the full pathname to the file */

    Pathname = FlMergePathnames (PrefixDir, Filename);

    DbgPrint (ASL_PARSE_OUTPUT, PR_PREFIX_ID
        "Include: Opening file - \"%s\"\n",
        AslGbl_CurrentLineNumber, Pathname);

    /* Attempt to open the file, push if successful */

    IncludeFile = fopen (Pathname, OpenMode);
    if (!IncludeFile)
    {
        return (NULL);
    }

    /* Push the include file on the open input file stack */

    PrPushInputFileStack (IncludeFile, Pathname);
    *FullPathname = Pathname;
    return (IncludeFile);
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
PrPushInputFileStack (
    FILE                    *InputFile,
    char                    *Filename)
{
    PR_FILE_NODE            *Fnode;


    AslGbl_HasIncludeFiles = TRUE;

    /* Save the current state in an Fnode */

    Fnode = UtLocalCalloc (sizeof (PR_FILE_NODE));

    Fnode->File = AslGbl_Files[ASL_FILE_INPUT].Handle;
    Fnode->Next = AslGbl_InputFileList;
    Fnode->Filename = AslGbl_Files[ASL_FILE_INPUT].Filename;
    Fnode->CurrentLineNumber = AslGbl_CurrentLineNumber;

    /* Push it on the stack */

    AslGbl_InputFileList = Fnode;

    DbgPrint (ASL_PARSE_OUTPUT, PR_PREFIX_ID
        "Push InputFile Stack: handle %p\n\n",
        AslGbl_CurrentLineNumber, InputFile);

    /* Reset the global line count and filename */

    AslGbl_Files[ASL_FILE_INPUT].Filename =
        UtLocalCacheCalloc (strlen (Filename) + 1);
    strcpy (AslGbl_Files[ASL_FILE_INPUT].Filename, Filename);

    AslGbl_Files[ASL_FILE_INPUT].Handle = InputFile;
    AslGbl_CurrentLineNumber = 1;

    /* Emit a new #line directive for the include file */

    FlPrintFile (ASL_FILE_PREPROCESSOR, "#line %u \"%s\"\n", 1, Filename);
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

BOOLEAN
PrPopInputFileStack (
    void)
{
    PR_FILE_NODE            *Fnode;


    Fnode = AslGbl_InputFileList;
    DbgPrint (ASL_PARSE_OUTPUT, "\n" PR_PREFIX_ID
        "Pop InputFile Stack, Fnode %p\n\n",
        AslGbl_CurrentLineNumber, Fnode);

    if (!Fnode)
    {
        return (FALSE);
    }

    /* Close the current include file */

    fclose (AslGbl_Files[ASL_FILE_INPUT].Handle);

    /* Update the top-of-stack */

    AslGbl_InputFileList = Fnode->Next;

    /* Reset global line counter and filename */

    AslGbl_Files[ASL_FILE_INPUT].Filename = Fnode->Filename;
    AslGbl_Files[ASL_FILE_INPUT].Handle = Fnode->File;
    AslGbl_CurrentLineNumber = Fnode->CurrentLineNumber;

    /* Emit a new #line directive after the include file */

    FlPrintFile (ASL_FILE_PREPROCESSOR, "#line %u \"%s\"\n",
        AslGbl_CurrentLineNumber, Fnode->Filename);

    /* All done with this node */

    ACPI_FREE (Fnode);
    return (TRUE);
}
