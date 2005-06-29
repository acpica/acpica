
/******************************************************************************
 *
 * Module Name: asllisting - Listing file generation
 *              $Revision: 1.5 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, Intel Corp.  All rights
 * reserved.
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


#include "AslCompiler.h"
#include "AslCompiler.y.h"
#include "aslresource.h"
#include "amlcode.h"
#include "acparser.h"


UINT32                      HexColumn = 0;
UINT32                      AmlOffset = 0;
UINT32                      Gbl_CurrentLine = 0;
UINT8                       Gbl_AmlBuffer[16];
UINT8                       Gbl_HexBytesWereWritten = FALSE;


ASL_LISTING_NODE            *Gbl_ListingNode = NULL;


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
LsPushNode (
    char                    *Filename)
{
    ASL_LISTING_NODE        *Lnode;


    if (!Gbl_ListingFile)
    {
        return;
    }

    //fprintf (Gbl_SourceOutputFile, "\n");

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
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

ASL_LISTING_NODE *
LsPopNode (void)
{
    ASL_LISTING_NODE        *Lnode;


    /* Just grab the node at the head of the list */

    Lnode = Gbl_ListingNode;
    Gbl_ListingNode = Lnode->Next;

    free (Lnode);

    /* New "Current" node is the new head */

    return (Gbl_ListingNode);
}


 

/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
LsCheckException (
    UINT32                  LineNumber)
{

    if ((!AslGbl_NextError) || 
        (LineNumber < AslGbl_NextError->LogicalLineNumber ))
    {
        return;
    }
 
    fprintf (Gbl_ListingFile, "\n[****AslException****]\n");

    AePrintException (Gbl_ListingFile, AslGbl_NextError);
    fprintf (Gbl_ListingFile, "\n");

    AslGbl_NextError = AslGbl_NextError->Next;
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
LsFlushListingBuffer (void)
{
    UINT32                  i;
    UINT8                   BufChar;


    if (HexColumn == 0)
    {
        return;
    }

    /* Write the hex bytes */

    for (i = 0; i < HexColumn; i++)
    {
        fwrite (&hex[Gbl_AmlBuffer[i] >> 4], 1, 1, Gbl_ListingFile);
        fwrite (&hex[Gbl_AmlBuffer[i] & 0xF], 1, 1, Gbl_ListingFile);
        fprintf (Gbl_ListingFile, " ");
    }

    for (i = 0; i < ((16 - HexColumn) * 3); i++)
    {
        fprintf (Gbl_ListingFile, ".");
    }
    fprintf (Gbl_ListingFile, "    ");

    //fprintf (Gbl_ListingFile, "%*s    ", ((16 - HexColumn) * 3) + 1, "XX");


    /* Write the ASCII character associated with each of the bytes */

    for (i = 0; i < HexColumn; i++)
    {
        BufChar = Gbl_AmlBuffer[i];
        if ((BufChar > 0x1F && BufChar < 0x2E) ||
            (BufChar > 0x2F && BufChar < 0x61) ||
            (BufChar > 0x60 && BufChar < 0x7F))
        {
            fprintf (Gbl_ListingFile, "%c", BufChar);
        }
        else
        {
            fprintf (Gbl_ListingFile, ".");
        }
    }


    fprintf (Gbl_ListingFile, "\n");
    HexColumn = 0;
    Gbl_HexBytesWereWritten = TRUE;
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
LsWriteListingHexBytes (
    char                    *Buffer,
    UINT32                  Length)
{
    UINT32                  i;
    UINT8                   *CharBuffer = (UINT8 *) Buffer;


    if (!Gbl_ListingFlag)
    {
        return;
    }

    for (i = 0; i < Length; i++)
    {
        if (HexColumn == 0)
        {
            if (Gbl_HasIncludeFiles)
            {
                fprintf (Gbl_ListingFile, "%*s", 17, " ");
            }

            fprintf (Gbl_ListingFile, "%8.8X....", AmlOffset);
        }

        Gbl_AmlBuffer[HexColumn] = Buffer[i];

        HexColumn++;
        AmlOffset++;

        if (HexColumn >= 16)
        {
            LsFlushListingBuffer ();
        }
    }

}



/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
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
        sprintf (StringBuffer, "%s(%d)",
                    Gbl_ListingNode->Filename, Gbl_ListingNode->LineNumber);

        fprintf (Gbl_ListingFile, "%-20s", StringBuffer);
        fprintf (Gbl_ListingFile, "%5d....", Gbl_SourceLine);
    }
    else
    {
        fprintf (Gbl_ListingFile, "%8d....", Gbl_SourceLine);
    }

    while (fread (&FileByte, 1, 1, Gbl_SourceOutputFile))
    {
        fwrite (&FileByte, 1, 1, Gbl_ListingFile);
        DbgPrint ("%c", FileByte);

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

    return (0);
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
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
    AmlOffset = 0;

    /* Flush any remaining text in the source file */

    while (LsWriteOneSourceLine ())
    { ; }

}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
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
        if (Gbl_HexBytesWereWritten)
        {
            fprintf (Gbl_ListingFile, "\n");
            Gbl_HexBytesWereWritten = FALSE;
        }

        while ((Gbl_SourceLine < Gbl_CurrentLine) &&
                LsWriteOneSourceLine ())
        { ; }

        fprintf (Gbl_ListingFile, "\n");
    }
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
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

        case AML_INDEX_FIELD_OP:
        case AML_DEF_FIELD_OP:
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
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
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

    fseek (Gbl_OutputAmlFile, 0, SEEK_SET);

    j = 0;
    while (fread (&FileByte[j], 1, 1, Gbl_OutputAmlFile))
    {
        /*
         * Convert each AML byte to hex
         */

        UtConvertByteToHex (FileByte[j], Buffer);

        fwrite (Buffer, 4, 1, Gbl_HexFile);
        fprintf (Gbl_HexFile, ",");

        /* An occasional linefeed improves readability */

        j++;
        if (j >= HEX_CHARS_PER_LINE)
        {

            fprintf  (Gbl_HexFile, "  /*  ");

            /* Write the ASCII character associated with each of the bytes */

            for (j = 0; j < HEX_CHARS_PER_LINE; j++)
            {
                BufChar = FileByte[j];
                if ((BufChar > 0x1F && BufChar < 0x2E) ||
                    (BufChar > 0x2F && BufChar < 0x61) ||
                    (BufChar > 0x60 && BufChar < 0x7F))
                {
                    fprintf (Gbl_HexFile, "%c", BufChar);
                }
                else
                {
                    fprintf (Gbl_HexFile, ".");
                }
            }


            fprintf  (Gbl_HexFile, "  */\n");
            j = 0;
        }
    }

    fprintf  (Gbl_HexFile, "\n");
    fclose (Gbl_HexFile);
}



