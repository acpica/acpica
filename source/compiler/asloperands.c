
/******************************************************************************
 *
 * Module Name: aslopcode - AML opcode generation
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
#include "amlcode.h"
#include "acnamesp.h"




/*******************************************************************************
 *
 * FUNCTION:    OpnDoMethod
 *
 * PARAMETERS:  Node        - The parent parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Construct the operands for the METHOD ASL keyword.
 *
 ******************************************************************************/

void
OpnDoMethod (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;

    /* Optional arguments for this opcode with defaults */

    UINT8                       NumArgs = 0;
    UINT8                       Serialized = 0;
    UINT8                       Concurrency = 0;
    UINT8                       MethodFlags;


    /* Opcode and package length first */
    /* Method name */

    Next = Node->Child;

    /* Num args */

    Next = Next->Peer;
    if (Next->ParseOpcode != DEFAULT_ARG)
    {
        NumArgs = Next->Value.Integer8;
        Next->ParseOpcode = DEFAULT_ARG;
    }

    /* Serialized Flag */

    Next = Next->Peer;
    if (Next->ParseOpcode != DEFAULT_ARG)
    {
        Serialized = Next->Value.Integer8;
        Next->ParseOpcode = DEFAULT_ARG;
    }

    /* Concurrency value (0-15 valid) */

    Next = Next->Peer;
    if (Next->ParseOpcode != DEFAULT_ARG)
    {
        Concurrency = Next->Value.Integer8;
    }

    /* Put the bits in their proper places */

    MethodFlags = (NumArgs & 0x7) | ((Serialized & 0x1) << 3) | ((Concurrency & 0xF) << 4);

    /* Use the last node for the combined flags byte */

    Next->Value.Integer = MethodFlags;
    Next->AmlOpcode = AML_RAW_DATA_BYTE;
    Next->AmlLength = 1;
    Next->ParseOpcode = RAW_DATA;
}


/*******************************************************************************
 *
 * FUNCTION:    OpnDoFieldCommon
 *
 * PARAMETERS:  Node        - The parent parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Construct the AML operands for the various field keywords,
 *              FIELD, BANKFIELD, INDEXFIELD
 *
 ******************************************************************************/

void
OpnDoFieldCommon (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;
    ASL_PARSE_NODE              *PkgLengthNode;
    UINT32                      CurrentBitOffset;
    UINT32                      NewBitOffset;
    UINT8                       AccessType;
    UINT8                       LockRule;
    UINT8                       UpdateRule;
    UINT8                       FieldFlags;


    /* AccessType -- not optional, so no need to check for DEFAULT_ARG */

    AccessType = Node->Value.Integer8;
    Node->ParseOpcode = DEFAULT_ARG;

    /* LockRule -- not optional, so no need to check for DEFAULT_ARG */

    Next = Node->Peer;
    LockRule = Next->Value.Integer8;
    Next->ParseOpcode = DEFAULT_ARG;

    /* UpdateRule -- not optional, so no need to check for DEFAULT_ARG */

    Next = Next->Peer;
    UpdateRule = Next->Value.Integer8;

    /* Generate the flags byte */

    FieldFlags = (AccessType & 0x0F) | ((LockRule & 0x01) << 4) | ((UpdateRule & 0x03) << 5);

    /* Use the previous node to be the FieldFlags node */

    /* Set the node to RAW_DATA */

    Next->Value.Integer = FieldFlags;
    Next->AmlOpcode = AML_RAW_DATA_BYTE;
    Next->AmlLength = 1;
    Next->ParseOpcode = RAW_DATA;

    /*  Process the FieldUnitList */

    Next = Next->Peer;
    CurrentBitOffset = 0;

    while (Next)
    {
        switch (Next->ParseOpcode)
        {
        case ACCESSAS:
            break;

        case OFFSET:
            PkgLengthNode = Next->Child;
            NewBitOffset = PkgLengthNode->Value.Integer32 * 8;
            if (NewBitOffset < CurrentBitOffset)
            {
                DbgPrint ("Offset less than current offset\n");
            }

            PkgLengthNode->Value.Integer = NewBitOffset - CurrentBitOffset;
            CurrentBitOffset = NewBitOffset;
            break;

        case NAMESEG:
        case RESERVED_BYTES:
            PkgLengthNode = Next->Child;
            NewBitOffset = PkgLengthNode->Value.Integer32;
            CurrentBitOffset += NewBitOffset;
            break;

        }
        Next = Next->Peer;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    OpnDoField
 *
 * PARAMETERS:  Node        - The parent parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Construct the AML operands for the FIELD ASL keyword
 *
 ******************************************************************************/

void
OpnDoField (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;


    /* Opcode is parent node */
    /* First child is field name */

    Next = Node->Child;

    /* Second child is the AccessType */

    OpnDoFieldCommon (Next->Peer);
}


/*******************************************************************************
 *
 * FUNCTION:    OpnDoIndexField
 *
 * PARAMETERS:  Node        - The parent parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Construct the AML operands for the INDEXFIELD ASL keyword
 *
 ******************************************************************************/

void
OpnDoIndexField (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;


    /* Opcode is parent node */
    /* First child is the index name */

    Next = Node->Child;

    /* Second child is the data name */

    Next = Next->Peer;

    /* Third child is the AccessType */

    OpnDoFieldCommon (Next->Peer);

}


/*******************************************************************************
 *
 * FUNCTION:    OpnDoBankField
 *
 * PARAMETERS:  Node        - The parent parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Construct the AML operands for the BANKFIELD ASL keyword
 *
 ******************************************************************************/

void
OpnDoBankField (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Next;


    /* Opcode is parent node */
    /* First child is the region name */

    Next = Node->Child;

    /* Second child is the bank name */

    Next = Next->Peer;

    /* Third child is the bank value */

    Next = Next->Peer;

    /* Fourth child is the AccessType */

    OpnDoFieldCommon (Next->Peer);

}


/*******************************************************************************
 *
 * FUNCTION:    OpnDoBuffer
 *
 * PARAMETERS:  Node        - The parent parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Construct the AML operands for the BUFFER ASL keyword.  We
 *              build a single raw byte buffer from the initialization nodes,
 *              each parse node contains a buffer byte.
 *
 ******************************************************************************/

void
OpnDoBuffer (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *InitializerNode;
    ASL_PARSE_NODE              *BufferLengthNode;

    /* Optional arguments for this opcode with defaults */

    UINT32                      BufferLength = 0;



    /* Opcode and package length first */
    /* Buffer Length is next, followed by the initializer list */

    BufferLengthNode = Node->Child;
    InitializerNode = BufferLengthNode->Peer;

    /*
     * If the BufferLength is not an INTEGER or was not specified in the ASL
     * (DEFAULT_ARG), it is a TermArg that is
     * evaluated at run-time, and we are therefore finished.
     */
    if ((BufferLengthNode->ParseOpcode != INTEGER) &&
        (BufferLengthNode->ParseOpcode != DEFAULT_ARG))
    {
        return;
    }

    /*
     * We want to count the number of items in the initializer list, because if
     * it is larger than the buffer length, we will define the buffer size
     * to be the size of the initializer list (Per ACPI Spec)
     */
    switch (InitializerNode->ParseOpcode)
    {

    case INTEGER:
    case BYTECONST:
    case WORDCONST:
    case DWORDCONST:

        /* The peer list contains the byte list (if any...) */

        while (InitializerNode)
        {
            /* For buffers, this is a list of raw bytes */

            InitializerNode->AmlOpcode      = AML_RAW_DATA_BYTE;
            InitializerNode->AmlLength      = 1;
            InitializerNode->ParseOpcode    = RAW_DATA;

            BufferLength++;
            InitializerNode = ASL_GET_PEER_NODE (InitializerNode);
        }
        break;


    case STRING_LITERAL:

        /*
         * Only one initializer, the string.  Buffer must be big enough to hold
         * the string plus the null termination byte
         */

        BufferLength = strlen (InitializerNode->Value.String) + 1;

        InitializerNode->AmlOpcode      = AML_RAW_DATA_BUFFER;
        InitializerNode->AmlLength      = BufferLength;
        InitializerNode->ParseOpcode    = RAW_DATA;
        break;


    case DEFAULT_ARG:
        break;


    default:
        printf ("Unknown buffer initializer opcode [%s]\n",
                        UtGetOpName (InitializerNode->ParseOpcode));
        return;
    }


    /* Check if initializer list is longer than the buffer length */

    if (BufferLengthNode->Value.Integer > BufferLength)
    {
        BufferLength = BufferLengthNode->Value.Integer32;
    }

    if (!BufferLength)
    {
        /* No length AND no items -- issue a warning */

        AslError (ASL_WARNING, ASL_MSG_BUFFER_LENGTH, BufferLengthNode, NULL);

        /* But go ahead and put the buffer length of zero into the AML */
    }


    /*
     * Just set the buffer size node to be the buffer length, regardless
     * of whether it was previously an integer or a default_arg placeholder
     */

    BufferLengthNode->ParseOpcode   = INTEGER;
    BufferLengthNode->AmlOpcode     = AML_DWORD_OP;
    BufferLengthNode->Value.Integer = BufferLength;

    OpcSetOptimalIntegerSize (BufferLengthNode);

    /* Remaining nodes are handled via the tree walk */
}


/*******************************************************************************
 *
 * FUNCTION:    OpnDoPackage
 *
 * PARAMETERS:  Node        - The parent parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Construct the AML operands for the PACKAGE ASL keyword.
 *
 ******************************************************************************/

void
OpnDoPackage (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *InitializerNode;
    ASL_PARSE_NODE              *PackageLengthNode;

    /* Optional arguments for this opcode with defaults */

    UINT32                      PackageLength = 0;


    /* Opcode and package length first */
    /* Buffer Length is next, followed by the initializer list */

    PackageLengthNode = Node->Child;
    InitializerNode = PackageLengthNode->Peer;

    /*
     * We always count the number of items in the initializer list, because if
     * it is larger than the buffer length, we will define the buffer size
     * to be the size of the initializer list (Per ACPI Spec)
     */
    if (InitializerNode->ParseOpcode != DEFAULT_ARG)
    {
        /* The peer list contains the byte list (if any...) */

        while (InitializerNode)
        {
            PackageLength++;
            InitializerNode = InitializerNode->Peer;
        }
    }


    /* Check if initializer list is longer than the buffer length */

    if (PackageLengthNode->ParseOpcode == INTEGER)
    {
        if (PackageLengthNode->Value.Integer > PackageLength)
        {
            PackageLength = PackageLengthNode->Value.Integer32;
        }
    }


    if (!PackageLength)
    {
        /* No length AND no items -- issue a warning */

        AslError (ASL_WARNING, ASL_MSG_PACKAGE_LENGTH, PackageLengthNode, NULL);

        /* But go ahead and put the buffer length of zero into the AML */
    }


    /*
     * Just set the buffer size node to be the buffer length, regardless
     * of whether it was previously an integer or a default_arg placeholder
     */

    PackageLengthNode->AmlOpcode = AML_RAW_DATA_BYTE;
    PackageLengthNode->AmlLength = 1;
    PackageLengthNode->ParseOpcode = RAW_DATA;
    PackageLengthNode->Value.Integer = PackageLength;

    /* Remaining nodes are handled via the tree walk */
}


/*******************************************************************************
 *
 * FUNCTION:    OpnDoDefinitionBlock
 *
 * PARAMETERS:  Node        - The parent parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Construct the AML operands for the DEFINTIONBLOCK ASL keyword
 *
 ******************************************************************************/

void
OpnDoDefinitionBlock (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *Child;


    /*
     * These nodes get stuffed into the table header.  They are special
     * cased when the table is written to the output file.
     *
     * Mark all of these nodes as non-usable so they won't get output
     * as AML opcodes!
     */


    /* AML filename */

    Child = Node->Child;
    if ((Child->Value.Pointer) && (Gbl_UseDefaultAmlFilename))
    {
        Gbl_OutputFilename = Child->Value.Pointer;
    }
    Child->ParseOpcode = DEFAULT_ARG;

    /* Signature */

    Child = Child->Peer;
    Child->ParseOpcode = DEFAULT_ARG;

    /* Revision */

    Child = Child->Peer;
    Child->ParseOpcode = DEFAULT_ARG;

    /* OEMID */

    Child = Child->Peer;
    Child->ParseOpcode = DEFAULT_ARG;

    /* OEM TableID */

    Child = Child->Peer;
    Child->ParseOpcode = DEFAULT_ARG;

    /* OEM Revision */

    Child = Child->Peer;
    Child->ParseOpcode = DEFAULT_ARG;
}


/*******************************************************************************
 *
 * FUNCTION:    UtGetArg
 *
 * PARAMETERS:  Op              - Get an argument for this op
 *              Argn            - Nth argument to get
 *
 * RETURN:      The argument (as an Op object).  NULL if argument does not exist
 *
 * DESCRIPTION: Get the specified op's argument (peer)
 *
 ******************************************************************************/

ASL_PARSE_NODE  *
UtGetArg (
    ASL_PARSE_NODE          *Op,
    UINT32                  Argn)
{
    ASL_PARSE_NODE          *Arg = NULL;


    /* Get the requested argument object */

    Arg = Op->Child;
    while (Arg && Argn)
    {
        Argn--;
        Arg = Arg->Peer;
    }

    return (Arg);
}


/*******************************************************************************
 *
 * FUNCTION:    OpnAttachNameToNode
 *
 * PARAMETERS:  Node        - The parent parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: For the named ASL/AML operators, get the actual name from the
 *              argument list and attach it to the parent node so that we
 *              can get to it quickly later.
 *
 ******************************************************************************/

void
OpnAttachNameToNode (
    ASL_PARSE_NODE          *PsNode)
{
    ASL_PARSE_NODE          *Child = NULL;
    ACPI_STATUS             Status;


    if (PsNode->ParseOpcode == EXTERNAL)
    {
        Child = UtGetArg (PsNode, 0);
    }

    else switch (PsNode->AmlOpcode)
    {

    case AML_DATA_REGION_OP:
    case AML_DEVICE_OP:
    case AML_EVENT_OP:
    case AML_METHOD_OP:
    case AML_MUTEX_OP:
    case AML_REGION_OP:
    case AML_POWER_RES_OP:
    case AML_PROCESSOR_OP:
    case AML_THERMAL_ZONE_OP:
    case AML_NAME_OP:
    case AML_SCOPE_OP:

        Child = UtGetArg (PsNode, 0);
        break;


    case AML_ALIAS_OP:

        Child = UtGetArg (PsNode, 1);
        break;


    case AML_BIT_FIELD_OP:
    case AML_BYTE_FIELD_OP:
    case AML_WORD_FIELD_OP:
    case AML_DWORD_FIELD_OP:
    case AML_QWORD_FIELD_OP:

        Child = UtGetArg (PsNode, 2);
        break;


    case AML_CREATE_FIELD_OP:

        Child = UtGetArg (PsNode, 3);
        break;


    case AML_BANK_FIELD_OP:
    case AML_INDEX_FIELD_OP:
    case AML_DEF_FIELD_OP:

        return;
        break;


    default:
        return;
        break;
    }


    if (Child)
    {
        PsNode->ExternalName = Child->Value.String;
        Status = AcpiNsInternalizeName (Child->Value.String, &PsNode->Namepath);
        if (ACPI_FAILURE (Status))
        {
        }
    }
}


/*******************************************************************************
 *
 * FUNCTION:    OpnGenerateAmlOperands
 *
 * PARAMETERS:  Node        - The parent parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prepare nodes to be output as AML data and operands.  The more
 *              complex AML opcodes require processing of the child nodes 
 *              (arguments/operands).
 *
 ******************************************************************************/

void
OpnGenerateAmlOperands (
    ASL_PARSE_NODE              *Node)
{


    if (Node->AmlOpcode == AML_RAW_DATA_BYTE)
    {
        return;
    }


    switch (Node->ParseOpcode)
    {
    case DEFINITIONBLOCK:
        OpnDoDefinitionBlock (Node);
        break;

    case METHOD:
        OpnDoMethod (Node);
        break;

    case FIELD:
        OpnDoField (Node);
        break;

    case INDEXFIELD:
        OpnDoIndexField (Node);
        break;

    case BANKFIELD:
        OpnDoBankField (Node);
        break;

    case BUFFER:
        OpnDoBuffer (Node);
        break;

    case PACKAGE:
        OpnDoPackage (Node);
        break;

    case RESOURCETEMPLATE:
        RsDoResourceTemplate (Node);
        break;

    case NAMESEG:
    case NAMESTRING:
    case METHODCALL:
    case STRING_LITERAL:
        break;

    default:
        break;
    }


    /* TBD: move */

    OpnAttachNameToNode (Node);
}


