
/******************************************************************************
 *
 * Module Name: aslopcode - AML opcode generation
 *              $Revision: 1.33 $
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
#include "aslcompiler.y.h"
#include "amlcode.h"

#include "acnamesp.h"

#define _COMPONENT          ACPI_COMPILER
        MODULE_NAME         ("aslopcodes")


/*******************************************************************************
 *
 * FUNCTION:    OpcAmlOpcodeWalk
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      None
 *
 * DESCRIPTION: Parse tree walk to generate both the AML opcodes and the AML
 *              operands.
 *
 ******************************************************************************/

ACPI_STATUS
OpcAmlOpcodeWalk (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context)
{

    TotalParseNodes++;

    OpcGenerateAmlOpcode (Node);
    OpnGenerateAmlOperands (Node);

    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    OpcSetOptimalIntegerSize
 *
 * PARAMETERS:  Node        - A parse tree node
 *
 * RETURN:      Integer width, in bytes.  Also sets the node AML opcode to the
 *              optimal integer AML prefix opcode.
 *
 * DESCRIPTION: Determine the optimal AML encoding of an integer.  All leading
 *              zeros can be truncated to squeeze the integer into the
 *              minimal number of AML bytes.
 *
 ******************************************************************************/

UINT32
OpcSetOptimalIntegerSize (
    ASL_PARSE_NODE          *Node)
{


    if (Node->Value.Integer <= ACPI_UINT8_MAX)
    {
        Node->AmlOpcode = AML_BYTE_OP;
        return 1;
    }
    else if (Node->Value.Integer <= ACPI_UINT16_MAX)
    {
        Node->AmlOpcode = AML_WORD_OP;
        return 2;
    }
    else if (Node->Value.Integer <= ACPI_UINT32_MAX)
    {
        Node->AmlOpcode = AML_DWORD_OP;
        return 4;
    }
    else
    {
        Node->AmlOpcode = AML_QWORD_OP;
        return 8;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    OpcDoAccessAs
 *
 * PARAMETERS:  Node        - Parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Implement the ACCESS_AS ASL keyword.
 *
 ******************************************************************************/

void
OpcDoAccessAs (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;


    Node->AmlOpcodeLength = 1;
    Next = Node->Child;

    /* First child is the access type */

    Next->AmlOpcode = AML_RAW_DATA_BYTE;
    Next->ParseOpcode = RAW_DATA;

    /* Second child is the optional access attribute */

    Next = Next->Peer;
    if (Next->ParseOpcode == DEFAULT_ARG)
    {
        Next->Value.Integer = 0;
    }
    Next->AmlOpcode = AML_RAW_DATA_BYTE;
    Next->ParseOpcode = RAW_DATA;
}


/*******************************************************************************
 *
 * FUNCTION:    OpcDoUnicode
 *
 * PARAMETERS:  Node        - Parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Implement the UNICODE ASL "macro".  Convert the input string
 *              to a unicode buffer.
 *
 ******************************************************************************/

void
OpcDoUnicode (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      Length;
    UINT32                      Count;
    UINT32                      i;
    char                        *AsciiString;
    UINT16                      *UnicodeString;
    ASL_PARSE_NODE              *BufferLengthNode;


    /* Opcode and package length first */
    /* Buffer Length is next, followed by the initializer list */

    BufferLengthNode = Node->Child;
    InitializerNode = BufferLengthNode->Peer;

    AsciiString = InitializerNode->Value.String;

    Count = strlen (AsciiString);
    Length = (Count * 2)  + sizeof (UINT16);
    UnicodeString = UtLocalCalloc (Length);

    for (i = 0; i < Count; i++)
    {
        UnicodeString[i] = AsciiString[i];
    }

    ACPI_MEM_FREE (AsciiString);

    /*
     * Just set the buffer size node to be the buffer length, regardless
     * of whether it was previously an integer or a default_arg placeholder
     */
    BufferLengthNode->ParseOpcode   = INTEGER;
    BufferLengthNode->AmlOpcode     = AML_DWORD_OP;
    BufferLengthNode->Value.Integer = Length;

    OpcSetOptimalIntegerSize (BufferLengthNode);

    InitializerNode->Value.Pointer  = UnicodeString;
    InitializerNode->AmlOpcode      = AML_RAW_DATA_BUFFER;
    InitializerNode->AmlLength      = Length;
    InitializerNode->ParseOpcode    = RAW_DATA;
}


/*******************************************************************************
 *
 * FUNCTION:    OpcDoEisaId
 *
 * PARAMETERS:  Node        - Parse node
 *
 * RETURN:      None
 *
 *
 * DESCRIPTION: Convert a string EISA ID to numeric representation
 *
 ******************************************************************************/

void
OpcDoEisaId (
    ASL_PARSE_NODE          *Node)
{
    UINT32                  id;
    UINT32                  SwappedId;
    NATIVE_CHAR             *InString;


    InString = Node->Value.String;

    /* Create ID big-endian first */

    id = 0;
    id |= (InString[0] - '@') << 26;
    id |= (InString[1] - '@') << 21;
    id |= (InString[2] - '@') << 16;

    id |= (UtHexCharToValue (InString[3])) << 12;
    id |= (UtHexCharToValue (InString[4])) << 8;
    id |= (UtHexCharToValue (InString[5])) << 4;
    id |= UtHexCharToValue (InString[6]);

    /* swap to little-endian  */

    SwappedId = (id & 0xFF) << 24;
    SwappedId |= ((id >> 8) & 0xFF) << 16;
    SwappedId |= ((id >> 16) & 0xFF) << 8;
    SwappedId |= (id >> 24) & 0xFF;

    Node->Value.Integer32 = SwappedId;

    /* Node is now an integer */

    Node->ParseOpcode = INTEGER;
    OpcSetOptimalIntegerSize (Node);
}


/*******************************************************************************
 *
 * FUNCTION:    OpcGenerateAmlOpcode
 *
 * PARAMETERS:  Node        - Parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Generate the AML opcode associated with the node and its
 *              parse (lex/flex) keyword opcode.  Essentially implements
 *              a mapping between the parse opcodes and the actual AML opcodes.
 *
 ******************************************************************************/

void
OpcGenerateAmlOpcode (
    ASL_PARSE_NODE          *Node)
{

    UINT16                  Index;


    Index = (UINT16) (Node->ParseOpcode - ASL_PARSE_OPCODE_BASE);

    Node->AmlOpcode  = AslKeywordMapping[Index].AmlOpcode;
    Node->AcpiBtype  = AslKeywordMapping[Index].AcpiBtype;
    Node->Flags     |= AslKeywordMapping[Index].Flags;

    if (!Node->Value.Integer)
    {
        Node->Value.Integer = AslKeywordMapping[Index].Value;
    }

    /* Special handling for some opcodes */

    switch (Node->ParseOpcode)
    {
    case INTEGER:
        /*
         * Set the opcode based on the size of the integer
         */
        OpcSetOptimalIntegerSize (Node);
        break;

    case OFFSET:
        Node->AmlOpcodeLength = 1;
        break;

    case ACCESSAS:
        OpcDoAccessAs (Node);
        break;

    case EISAID:
        OpcDoEisaId (Node);
        break;

    case UNICODE:
        OpcDoUnicode (Node);
        break;

    case INCLUDE:
        Node->Child->ParseOpcode = DEFAULT_ARG;
        Gbl_HasIncludeFiles = TRUE;
        break;

    case EXTERNAL:
        Node->Child->ParseOpcode = DEFAULT_ARG;
        Node->Child->Peer->ParseOpcode = DEFAULT_ARG;
        break;

    case PACKAGE:
        /*
         * The variable-length package has a different opcode
         */
        if ((Node->Child->ParseOpcode != DEFAULT_ARG) &&
            (Node->Child->ParseOpcode != INTEGER)     &&
            (Node->Child->ParseOpcode != BYTECONST))
        {
            Node->AmlOpcode = AML_VAR_PACKAGE_OP;
        }
    }

    return;
}


