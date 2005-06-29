
/******************************************************************************
 *
 * Module Name: asllisting - Listing file generation
 *              $Revision: 1.18 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, 2001, Intel Corp.
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
#include "aslcompiler.y.h"
#include "aslresource.h"
#include "amlcode.h"
#include "acparser.h"

#define _COMPONENT          ACPI_COMPILER
        MODULE_NAME         ("aslisting")


/*******************************************************************************
 *
 * FUNCTION:    LsPushNode
 *
 * PARAMETERS:  Filename        - Pointer to the include filename
 *
 * RETURN:      None
 *
 * DESCRIPTION: Push a listing node on the listing/include file stack.  This
 *              stack enables tracking of include files (infinitely nested)
 *              and resumption of the listing of the parent file when the
 *              include file is finished.
 *
 ******************************************************************************/

void
LsPushNode (
    char                    *Filename)
{
    ASL_LISTING_NODE        *Lnode;


    if (!Gbl_ListingFlag)
    {
        return;
    }


    /* Create a new node */

    Lnode = UtLocalCalloc (sizeof (ASL_LISTING_NODE));

    /* Initialize */

    Lnode->Filename = Filename;
    Lnode->LineNumber = 0;

    /* Link (push) */

    Lnode->Next = Gbl_ListingNode;
    Gbl_ListingNode = Lnode;
}


/*******************************************************************************
 *
 * FUNCTION:    LsPopNode
 *
 * PARAMETERS:  None
 *
 * RETURN:      List head after current head is popped off
 *
 * DESCRIPTION: Pop the current head of the list, free it, and return the
 *              next node on the stack (the new current node).
 *
 ******************************************************************************/

ASL_LISTING_NODE *
LsPopNode (void)
{
    ASL_LISTING_NODE        *Lnode;


    if (!Gbl_ListingFlag)
    {
        return Gbl_ListingNode;
    }

    /* Just grab the node at the head of the list */

    Lnode = Gbl_ListingNode;
    if ((!Lnode) ||
        (!Lnode->Next))
    {
        AslError (ASL_ERROR, ASL_MSG_INTERNAL, NULL, "Could not pop empty listing stack");
        return Gbl_ListingNode;
    }

    Gbl_ListingNode = Lnode->Next;

    AcpiCmFree (Lnode);

    /* New "Current" node is the new head */

    return (Gbl_ListingNode);
}


/*******************************************************************************
 *
 * FUNCTION:    LsCheckException
 *
 * PARAMETERS:  LineNumber          - Current logical (cumulative) line #
 *
 * RETURN:      None
 *
 * DESCRIPTION: Check if there is an exception for this line, and if there is,
 *              put it in the listing immediately.  Handles multiple errors
 *              per line.  Gbl_NextError points to the next error in the
 *              sorted (by line #) list of compile errors/warnings.
 *
 ******************************************************************************/

void
LsCheckException (
    UINT32                  LineNumber)
{


    if ((!Gbl_NextError) ||
        (LineNumber < Gbl_NextError->LogicalLineNumber ))
    {
        return;
    }

    /* Handle multiple errors per line */

    while (Gbl_NextError &&
          (LineNumber >= Gbl_NextError->LogicalLineNumber))
    {
        FlPrintFile (ASL_FILE_LISTING_OUTPUT, "\n[****AslException****]\n");

        AePrintException (ASL_FILE_LISTING_OUTPUT, Gbl_NextError);

        Gbl_NextError = Gbl_NextError->Next;
    }

    FlPrintFile (ASL_FILE_LISTING_OUTPUT, "\n");
}


/*******************************************************************************
 *
 * FUNCTION:    LsFlushListingBuffer
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Flush out the current contents of the 16-byte hex AML code
 *              buffer.  Usually called at the termination of a single line
 *              of source code or when the buffer is full.
 *
 ******************************************************************************/

void
LsFlushListingBuffer (void)
{
    UINT32                  i;
    UINT8                   BufChar;


    if (Gbl_CurrentHexColumn == 0)
    {
        return;
    }

    /* Write the hex bytes */

    for (i = 0; i < Gbl_CurrentHexColumn; i++)
    {
        FlWriteFile (ASL_FILE_LISTING_OUTPUT, &hex[Gbl_AmlBuffer[i] >> 4], 1);
        FlWriteFile (ASL_FILE_LISTING_OUTPUT, &hex[Gbl_AmlBuffer[i] & 0xF], 1);
        FlWriteFile (ASL_FILE_LISTING_OUTPUT, " ", 1);
    }

    for (i = 0; i < ((16 - Gbl_CurrentHexColumn) * 3); i++)
    {
        FlWriteFile (ASL_FILE_LISTING_OUTPUT, ".", 1);
    }

    FlWriteFile (ASL_FILE_LISTING_OUTPUT, "    ", 4);


    /* Write the ASCII character associated with each of the bytes */

    for (i = 0; i < Gbl_CurrentHexColumn; i++)
    {
        BufChar = Gbl_AmlBuffer[i];
        if ((BufChar > 0x1F && BufChar < 0x2E) ||
            (BufChar > 0x2F && BufChar < 0x61) ||
            (BufChar > 0x60 && BufChar < 0x7F))
        {
            FlPrintFile (ASL_FILE_LISTING_OUTPUT,"%c", BufChar);
        }
        else
        {
            FlWriteFile (ASL_FILE_LISTING_OUTPUT, ".", 1);
        }
    }


    FlPrintFile (ASL_FILE_LISTING_OUTPUT, "\n");
    Gbl_CurrentHexColumn = 0;
    Gbl_HexBytesWereWritten = TRUE;
}


/*******************************************************************************
 *
 * FUNCTION:    LsWriteListingHexBytes
 *
 * PARAMETERS:  Buffer          - AML code buffer
 *              Length          - Number of AML bytes to write
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write the contents of the AML buffer to the listing file via
 *              the listing buffer.  The listing buffer is flushed every 16
 *              AML bytes.
 *
 ******************************************************************************/

void
LsWriteListingHexBytes (
    char                    *Buffer,
    UINT32                  Length)
{
    UINT32                  i;
    UINT8                   *CharBuffer = (UINT8 *) Buffer;


    /* Are we in listing mode? */

    if (!Gbl_ListingFlag)
    {
        return;
    }

    /* Transfer all requested bytes */

    for (i = 0; i < Length; i++)
    {
        /* Print line header when buffer is empty */

        if (Gbl_CurrentHexColumn == 0)
        {
            if (Gbl_HasIncludeFiles)
            {
                FlPrintFile (ASL_FILE_LISTING_OUTPUT, "%*s", 10, " ");
            }

            FlPrintFile (ASL_FILE_LISTING_OUTPUT, "%8.8X....", Gbl_CurrentAmlOffset);
        }

        /* Transfer AML byte and update counts */

        Gbl_AmlBuffer[Gbl_CurrentHexColumn] = Buffer[i];

        Gbl_CurrentHexColumn++;
        Gbl_CurrentAmlOffset++;

        /* Flush buffer when it is full */

        if (Gbl_CurrentHexColumn >= 16)
        {
            LsFlushListingBuffer ();
        }
    }

}


/*******************************************************************************
 *
 * FUNCTION:    LsWriteOneSourceLine
 *
 * PARAMETERS:  None
 *
 * RETURN:      FALSE on EOF (input source file), TRUE otherwise
 *
 * DESCRIPTION: Read one line from the input source file and echo it to the
 *              listing file, prefixed with the line number, and if the source
 *              file contains include files, prefixed with the current filename
 *
 ******************************************************************************/

UINT32
LsWriteOneSourceLine (void)
{
    UINT8               FileByte;


    Gbl_SourceLine++;
    Gbl_ListingNode->LineNumber++;

    if (Gbl_HasIncludeFiles)
    {
        /*
         * This file contains "include" statements, print the current
         * filename and line number within the current file
         */

        FlPrintFile (ASL_FILE_LISTING_OUTPUT, "%12s %5d....",
                    Gbl_ListingNode->Filename, Gbl_ListingNode->LineNumber);
    }
    else
    {
        /* No include files, just print the line number */

        FlPrintFile (ASL_FILE_LISTING_OUTPUT, "%8d....", Gbl_SourceLine);
    }


    /* Read one line (up to a newline or EOF) */

    while (FlReadFile (ASL_FILE_SOURCE_OUTPUT, &FileByte, 1) == AE_OK)
    {
        FlWriteFile (ASL_FILE_LISTING_OUTPUT, &FileByte, 1);
        DbgPrint (ASL_PARSE_OUTPUT, "%c", FileByte);

        if (FileByte == '\n')
        {
            /*
             * Check if an error occurred on this source line during the compile.
             * If so, we print the error message after the source line.
             */
            LsCheckException (Gbl_SourceLine);
            return (1);
        }
    }

    /* EOF on the input file was reached */

    return (0);
}


/*******************************************************************************
 *
 * FUNCTION:    LsFinishSourceListing
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Cleanup routine for the listing file.  Flush the hex AML
 *              listing buffer, and flush out any remaining lines in the
 *              source input file.
 *
 ******************************************************************************/

void
LsFinishSourceListing (void)
{
    UINT32              Actual = 1;


    if (!Gbl_ListingFlag)
    {
        return;
    }

    LsFlushListingBuffer ();
    Gbl_CurrentAmlOffset = 0;

    /* Flush any remaining text in the source file */

    while (LsWriteOneSourceLine ())
    { ; }

}


/*******************************************************************************
 *
 * FUNCTION:    LsWriteSourceLines
 *
 * PARAMETERS:  ToLineNumber
 *              ToLogicalLineNumber
 *
 * RETURN:      None
 *
 * DESCRIPTION: Read then write source lines to the listing file until we have
 *              reached the specified logical (cumulative) line number.  This
 *              automatically echos out comment blocks and other non-AML
 *              generating text until we get to the actual AML-generating line
 *              of ASL code specified by the logical line number.
 *
 ******************************************************************************/

void
LsWriteSourceLines (
    UINT32              ToLineNumber,
    UINT32              ToLogicalLineNumber)
{

    Gbl_CurrentLine = ToLogicalLineNumber;

    /* Flush any hex bytes remaining from the last opcode */

    LsFlushListingBuffer ();

    /*
     * Read lines and write them as long as we are not caught up
     */
    if (Gbl_SourceLine < Gbl_CurrentLine)
    {
        /*
         * If we just completed writing some AML hex bytes, output a linefeed
         * to add some whitespace for readability.
         */

        if (Gbl_HexBytesWereWritten)
        {
            FlPrintFile (ASL_FILE_LISTING_OUTPUT, "\n");
            Gbl_HexBytesWereWritten = FALSE;
        }

        /*
         * Write one line at a time until we have reached the target line #
         */
        while ((Gbl_SourceLine < Gbl_CurrentLine) &&
                LsWriteOneSourceLine ())
        { ; }


        FlPrintFile (ASL_FILE_LISTING_OUTPUT, "\n");
    }
}


/*******************************************************************************
 *
 * FUNCTION:    LsWriteNodeToListing
 *
 * PARAMETERS:  Node            - Parse node to write to the listing file.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Write "a node" to the listing file.  This means to
 *              1) Write out all of the source text associated with the node
 *              2) Write out all of the AML bytes associated with the node
 *              3) Write any compiler exceptions associated with the node
 *
 ******************************************************************************/

void
LsWriteNodeToListing (
    ASL_PARSE_NODE          *Node)
{
    ACPI_OPCODE_INFO        *OpInfo;
    UINT8                   Optype;


    if (!Gbl_ListingFlag)
    {
        return;
    }


    /* These cases do not have a corresponding AML opcode */

    switch (Node->ParseOpcode)
    {
    case DEFINITIONBLOCK:
        LsWriteSourceLines (Node->EndLine, Node->EndLogicalLine);
        return;

    case METHODCALL:
        LsWriteSourceLines (Node->LineNumber, Node->LogicalLineNumber);
        return;

    case INCLUDE:
        /*
         * Flush everything up to and including the include source line
         */
        LsWriteSourceLines (Node->LineNumber, Node->LogicalLineNumber);

        /*
         * Create a new listing node and push it
         */

        LsPushNode (Node->Child->Value.String);
        return;

    case INCLUDE_END:
        /*
         * Flush out the rest of the include file
         */
        LsWriteSourceLines (Node->LineNumber, Node->LogicalLineNumber);

        /*
         * Pop off this listing node and go back to the parent file
         */
        LsPopNode ();
        return;
    }


    /*
     * Otherwise, we look at the AML opcode because we can
     * switch on the opcode type, getting an entire class
     * at once
     */

    OpInfo = AcpiPsGetOpcodeInfo (Node->AmlOpcode);
    Optype = (UINT8) ACPI_GET_OP_CLASS (OpInfo);

    switch (Optype)
    {
    case OPTYPE_BOGUS:
    case OPTYPE_CONSTANT:           /* argument type only */
    case OPTYPE_LITERAL:            /* argument type only */
    case OPTYPE_DATA_TERM:          /* argument type only */
    case OPTYPE_LOCAL_VARIABLE:     /* argument type only */
    case OPTYPE_METHOD_ARGUMENT:    /* argument type only */

        break;


    case OPTYPE_NAMED_OBJECT:

        switch (Node->AmlOpcode)
        {

        /* For fields, we want to dump all the AML after the entire definition */

        case AML_FIELD_OP:
        case AML_INDEX_FIELD_OP:
        case AML_BANK_FIELD_OP:
        case AML_NAME_OP:

            LsWriteSourceLines (Node->EndLine, Node->EndLogicalLine);
            break;

        default:
            LsWriteSourceLines (Node->LineNumber, Node->LogicalLineNumber);
            break;
        }
        break;

    case OPTYPE_UNDEFINED:
    default:

        LsWriteSourceLines (Node->LineNumber, Node->LogicalLineNumber);
        break;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    LsDoHexOutput
 *
 * PARAMETERS:  None
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Create the hex output file.  This is the same data as the AML
 *              output file, but formatted into hex/ascii bytes suitable for
 *              inclusion into a C source file.
 *
 ******************************************************************************/

#define HEX_CHARS_PER_LINE 16

void
LsDoHexOutput (void)
{
    UINT32                  j;
    UINT8                   BufChar;
    UINT8                   FileByte[HEX_CHARS_PER_LINE];
    UINT8                   Buffer[4];


    if (!Gbl_HexOutputFlag)
    {
        return;
    }


    /* Start at the beginning of the AML file */

    FlSeekFile (ASL_FILE_AML_OUTPUT, 0);

    /* Process all AML bytes in the AML file */

    j = 0;
    while (FlReadFile (ASL_FILE_AML_OUTPUT, &FileByte[j], 1) == AE_OK)
    {
        /*
         * Convert each AML byte to hex
         */

        UtConvertByteToHex (FileByte[j], Buffer);

        FlWriteFile (ASL_FILE_HEX_OUTPUT, Buffer, 4);
        FlPrintFile (ASL_FILE_HEX_OUTPUT, ",");

        /* An occasional linefeed improves readability */

        j++;
        if (j >= HEX_CHARS_PER_LINE)
        {

            FlPrintFile (ASL_FILE_HEX_OUTPUT, "  /*  ");

            /* Write the ASCII character associated with each of the bytes */

            for (j = 0; j < HEX_CHARS_PER_LINE; j++)
            {
                BufChar = FileByte[j];
                if ((BufChar > 0x1F && BufChar < 0x2E) ||
                    (BufChar > 0x2F && BufChar < 0x61) ||
                    (BufChar > 0x60 && BufChar < 0x7F))
                {
                    FlPrintFile (ASL_FILE_HEX_OUTPUT, "%c", BufChar);
                }
                else
                {
                    FlPrintFile (ASL_FILE_HEX_OUTPUT, ".");
                }
            }


            FlPrintFile (ASL_FILE_HEX_OUTPUT, "  */\n");
            j = 0;
        }
    }

    FlPrintFile (ASL_FILE_HEX_OUTPUT, "\n");
    FlCloseFile (ASL_FILE_HEX_OUTPUT);
}


