
/******************************************************************************
 *
 * Module Name: aslerror - Error handling and statistics
 *              $Revision: 1.60 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2002, Intel Corp.
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


#include "aslcompiler.h"

#define _COMPONENT          ACPI_COMPILER
        MODULE_NAME         ("aslerror")


char                        *AslMessages [] = {
    NULL,
    "Memory allocation failure",
    "Could not open input file",
    "Could not create output filename",
    "Could not open output AML file",
    "Could not create listing filename",
    "Could not open listing file",
    "Could not create debug filename",
    "Could not open debug file",
    "Could not open include file",
    "Package length too long to encode",
    "Invalid priority value",
    "Invalid performance/robustness value",
    "Method local variable is not initialized",
    "Method argument is not initialized",
    "Unsupported feature",
    "Use of reserved word",
    "Effective AML buffer length is zero",
    "Effective AML package length is zero",
    "Mixed return types in method",
    "Object not found or not accessible from scope",
    "Object not accessible from this scope",
    "Object does not exist",
    "Nested comment found",
    "Reserved method has too many arguments",
    "Reserved method has too few arguments",
    "Reserved method must return a value",
    "Too many arguments",
    "Too few arguments",
    "Called method returns no value",
    "Called method may not always return a value",
    "Internal compiler error",
    "Invalid backwards offset",
    "Unknown reserved name",
    "Name already exists in scope",
    "Invalid type",
    "Multiple types",
    "",
    "Not a control method, cannot invoke",
    "Splitting long input line",
    "Recursive method call",
    "Not a parameter, used as local only",
    "Could not open file",
    "Could not read file",
    "Could not write file",
    "Could not seek file",
    "Could not close file",
    "Access width is greater than region size",
    "Host Operation Region requires ByteAcc access",
    "Host Operation Region requires BufferAcc access",
    "Field unit extends beyond region limit",
    "Resource field name cannot be used as a target",
    "Invalid Byte Offset, Bit Offset required",
    "Invalid Bit Offset, Byte Offset required",
    "Opcode is not implemented in compiler AML code generator",
    "No enclosing While statement",
    "Invalid Escape Sequence",
    "Null (0) escape sequence terminates string"
};


char                        *AslErrorLevel [] = {
    "Error  ",
    "Warning",
    "Remark ",
};

#define ASL_ERROR_LEVEL_LENGTH          7


/*******************************************************************************
 *
 * FUNCTION:    AeAddToErrorLog
 *
 * PARAMETERS:  Enode       - An error node to add to the log
 *
 * RETURN:      None
 *
 * DESCRIPTION: Add a new error node to the error log.  The error log is
 *              ordered by the "logical" line number (cumulative line number
 *              including all include files.)
 *
 ******************************************************************************/

void
AeAddToErrorLog (
    ASL_ERROR_MSG           *Enode)
{
    ASL_ERROR_MSG           *Next;
    ASL_ERROR_MSG           *Prev;


    if (!Gbl_ErrorLog)
    {
        Gbl_ErrorLog = Enode;
        return;
    }

    /* List is sorted according to line number */

    if (!Gbl_ErrorLog)
    {
        Gbl_ErrorLog = Enode;
        return;
    }

    /* Walk error list until we find a line number greater than ours */

    Prev = NULL;
    Next = Gbl_ErrorLog;

    while ((Next) &&
           (Next->LogicalLineNumber <= Enode->LogicalLineNumber))
    {
        Prev = Next;
        Next = Next->Next;
    }

    /* Found our place in the list */

    Enode->Next = Next;

    if (Prev)
    {
        Prev->Next = Enode;
    }
    else
    {
        Gbl_ErrorLog = Enode;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AePrintException
 *
 * PARAMETERS:  Where       - Where to send the message
 *              Enode       - Error node to print
 *
 * RETURN:      None
 *
 * DESCRIPTION: Print the contents of an error node.
 *
 * NOTE:        We don't use the FlxxxFile I/O functions here because on error
 *              they abort the compiler and call this function!  Since we
 *              are reporting errors here, we ignore most output errors and
 *              just try to get out as much as we can.
 *
 ******************************************************************************/

void
AePrintException (
    UINT32                  FileId,
    ASL_ERROR_MSG           *Enode)
{
    UINT8                   SourceByte;
    UINT32                  Actual;
    UINT32                  MsgLength;
    char                    *MainMessage;
    char                    *ExtraMessage;
    UINT32                  SourceColumn;
    UINT32                  ErrorColumn;
    FILE                    *OutputFile;
    FILE                    *SourceFile;


    OutputFile = Gbl_Files[FileId].Handle;
    SourceFile = Gbl_Files[ASL_FILE_SOURCE_OUTPUT].Handle;


    /* Print filename and line number if present and valid */

    if (Enode->Filename)
    {
        fprintf (OutputFile, "%6s", Enode->Filename);

        if (Enode->LineNumber)
        {
            fprintf (OutputFile, "%6u: ", Enode->LineNumber);

            /*
             * Seek to the offset in the combined source file, read the source
             * line, and write it to the output.
             */
            fseek (SourceFile, Enode->LogicalByteOffset, SEEK_SET);

            Actual = fread (&SourceByte, 1, 1, SourceFile);
            while (Actual && SourceByte && (SourceByte != '\n'))
            {
                fwrite (&SourceByte, 1, 1, OutputFile);
                Actual = fread (&SourceByte, 1, 1, SourceFile);
            }

            fprintf (OutputFile, "\n");
        }
    }

    /* NULL message ID, just print the raw message */

    if (Enode->MessageId == 0)
    {
        fprintf (OutputFile, "%s\n", Enode->Message);
    }
    else
    {
        /* Decode the message ID */

        fprintf (OutputFile, "%s %4.4d -",
                    AslErrorLevel[Enode->Level],
                    Enode->MessageId + ((Enode->Level+1) * 1000));

        MainMessage = AslMessages[Enode->MessageId];
        ExtraMessage = Enode->Message;

        if (Enode->LineNumber)
        {
            MsgLength = strlen (MainMessage);
            if (MsgLength == 0)
            {
                MainMessage = Enode->Message;

                MsgLength = strlen (MainMessage);
                ExtraMessage = NULL;
            }

            SourceColumn = Enode->Column + Enode->FilenameLength + 6 + 2;
            ErrorColumn = ASL_ERROR_LEVEL_LENGTH + 5 + 2 + 1;

            if (SourceColumn < 80)
            {
                if ((MsgLength + ErrorColumn) < (SourceColumn - 1))
                {
                    fprintf (OutputFile, "%*s%s",
                        (int) ((SourceColumn - 1) - ErrorColumn),
                        MainMessage, " ^ ");
                }
                else
                {
                    fprintf (OutputFile, "%*s %s",
                        (int) ((SourceColumn - ErrorColumn) + 1), "^",
                        MainMessage);
                }
            }
            else
            {
                fprintf (OutputFile, " ^ %s   %s\n\n",
                            MainMessage,
                            ExtraMessage);
            }

            /* Print the extra info message if present */

            if (ExtraMessage)
            {
                fprintf (OutputFile, " (%s)", ExtraMessage);
            }
            fprintf (OutputFile, "\n\n");
        }
        else
        {
            fprintf (OutputFile, " %s %s\n\n",
                        MainMessage,
                        ExtraMessage);
        }
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AePrintErrorLog
 *
 * PARAMETERS:  FileId           - Where to output the error log
 *
 * RETURN:      None
 *
 * DESCRIPTION: Print the entire contents of the error log
 *
 ******************************************************************************/

void
AePrintErrorLog (
    UINT32                  FileId)
{
    ASL_ERROR_MSG           *Enode = Gbl_ErrorLog;


    while (Enode)
    {
        AePrintException (FileId, Enode);
        Enode = Enode->Next;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AslCommonError
 *
 * PARAMETERS:  Level               - Seriousness (Warning/error, etc.)
 *              MessageId           - Index into global message buffer
 *              CurrentLineNumber   - Actual file line number
 *              LogicalLineNumber   - Cumulative line number
 *              LogicalByteOffset   - Byte offset in source file
 *              Column              - Column in current line
 *              Filename            - source filename
 *              ExtraMessage        - additional error message
 *
 * RETURN:      New error node for this error
 *
 * DESCRIPTION: Create a new error node and add it to the error log
 *
 ******************************************************************************/

ASL_ERROR_MSG *
AslCommonError (
    UINT8                   Level,
    UINT8                   MessageId,
    UINT32                  CurrentLineNumber,
    UINT32                  LogicalLineNumber,
    UINT32                  LogicalByteOffset,
    UINT32                  Column,
    char                    *Filename,
    char                    *ExtraMessage)
{
    UINT32                  MessageSize;
    char                    *MessageBuffer = NULL;
    ASL_ERROR_MSG           *Enode;


    Enode = UtLocalCalloc (sizeof (ASL_ERROR_MSG));

    if (ExtraMessage)
    {
        /* Allocate a buffer for the message and a new error node */

        MessageSize   = strlen (ExtraMessage) + 1;
        MessageBuffer = UtLocalCalloc (MessageSize);

        /* Keep a copy of the extra message */

        STRCPY (MessageBuffer, ExtraMessage);
    }

    /*
     * Initialize the error node
     */
    if (Filename)
    {
        Enode->Filename       = Filename;
        Enode->FilenameLength = strlen (Filename);
        if (Enode->FilenameLength < 6)
        {
            Enode->FilenameLength = 6;
        }
    }

    Enode->MessageId            = MessageId;
    Enode->Level                = Level;
    Enode->LineNumber           = CurrentLineNumber;
    Enode->LogicalLineNumber    = LogicalLineNumber;
    Enode->LogicalByteOffset    = LogicalByteOffset;
    Enode->Column               = Column;
    Enode->Message              = MessageBuffer;

    /* Add the new node to the error node list */

    AeAddToErrorLog (Enode);

    if (Gbl_DebugFlag)
    {
        /* stderr is a file, send error to it immediately */

        AePrintException (ASL_FILE_STDERR, Enode);
    }

    Gbl_ExceptionCount[Level]++;
    if (Gbl_ExceptionCount[ASL_ERROR] > ASL_MAX_ERROR_COUNT)
    {

        AePrintErrorLog (ASL_FILE_STDOUT);
        if (Gbl_DebugFlag)
        {
            /* Print error summary to the debug file */

            AePrintErrorLog (ASL_FILE_STDERR);
        }
        printf ("\nMaximum error count (%d) exceeded.\n", ASL_MAX_ERROR_COUNT);
        CmCleanupAndExit ();
    }

    return Enode;
}


/*******************************************************************************
 *
 * FUNCTION:    AslError
 *
 * PARAMETERS:  Level               - Seriousness (Warning/error, etc.)
 *              MessageId           - Index into global message buffer
 *              Node                - Parse node where error happened
 *              ExtraMessage        - additional error message
 *
 * RETURN:      None
 *
 * DESCRIPTION: Main error reporting routine for the ASL compiler (all code
 *              except the parser.)
 *
 ******************************************************************************/

void
AslError (
    UINT8                   Level,
    UINT8                   MessageId,
    ASL_PARSE_NODE          *Node,
    char                    *ExtraMessage)
{

    if (Node)
    {
        AslCommonError (Level, MessageId, Node->LineNumber,
                        Node->LogicalLineNumber,
                        Node->LogicalByteOffset,
                        Node->Column,
                        Node->Filename, ExtraMessage);
    }
    else
    {
        AslCommonError (Level, MessageId, 0,
                        0, 0, 0, NULL, ExtraMessage);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AslCompilererror
 *
 * PARAMETERS:  CompilerMessage
 *
 * RETURN:      Status?
 *
 * DESCRIPTION: Report an error situation discovered in a production
 *               NOTE: don't change the name of this function.
 *
 ******************************************************************************/

int
AslCompilererror (
    char                    *CompilerMessage)
{


    AslCommonError (ASL_ERROR, ASL_MSG_SYNTAX, Gbl_CurrentLineNumber,
                    Gbl_LogicalLineNumber, Gbl_CurrentLineOffset,
                    Gbl_CurrentColumn, Gbl_Files[ASL_FILE_INPUT].Filename,
                    CompilerMessage /*MsgBuffer*/);

    return 0;
}


