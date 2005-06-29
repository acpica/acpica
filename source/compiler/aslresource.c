
/******************************************************************************
 *
 * Module Name: aslresource - Resource templates and descriptors
 *              $Revision: 1.10 $
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

ASL_RESOURCE_NODE *
RsAllocateResourceNode (
    UINT32                  Size)
{
    ASL_RESOURCE_NODE       *Rnode;


    /* Allocate the node */

    Rnode = UtLocalCalloc (sizeof (ASL_RESOURCE_NODE));

    /* Allocate the resource descriptor itself */

    Rnode->Buffer = UtLocalCalloc (Size);
    Rnode->BufferLength = Size;


    return (Rnode);
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
RsCreateBitField (
    ASL_PARSE_NODE              *Node,
    char                        *Name,
    UINT32                      ByteOffset,
    UINT32                      BitOffset)
{


    Node->ExternalName      = Name;
    Node->Value.Integer32   = (ByteOffset * 8) + BitOffset;
    Node->Flags             |= NODE_IS_RESOURCE_FIELD;
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
RsCreateByteField (
    ASL_PARSE_NODE              *Node,
    char                        *Name,
    UINT32                      ByteOffset)
{


    Node->ExternalName      = Name;
    Node->Value.Integer32   = ByteOffset;
    Node->Flags             |= NODE_IS_RESOURCE_FIELD;
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
RsSetFlagBits (
    UINT8                       *Flags,
    ASL_PARSE_NODE              *Node,
    UINT8                       Position,
    UINT8                       Default)
{


    if (Node->ParseOpcode == DEFAULT_ARG)
    {
        /* Use the default bit */

        *Flags |= (Default << Position);
    }

    else
    {
        /* Use the bit specified in the initialization node */

        *Flags |= (Node->Value.Integer8 << Position);
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

ASL_PARSE_NODE *
RsCompleteNodeAndGetNext (
    ASL_PARSE_NODE              *Node)
{


    /* Mark this node unused */

    Node->ParseOpcode = DEFAULT_ARG;

    /* Move on to the next peer node in the initializer list */

    return (ASL_GET_PEER_NODE (Node));
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

ASL_RESOURCE_NODE *
RsDoOneResourceDescriptor (
    ASL_PARSE_NODE          *DescriptorTypeNode,
    UINT32                  CurrentByteOffset)
{
    ASL_RESOURCE_NODE       *Rnode = NULL;


    /* Determine type of resource */

    switch (DescriptorTypeNode->ParseOpcode)
    {
    case DMA:
        Rnode = RsDoDmaDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case DWORDIO:
        Rnode = RsDoDwordIoDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case DWORDMEMORY:
        Rnode = RsDoDwordMemoryDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case ENDDEPENDENTFN:
        Rnode = RsDoEndDependentDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case FIXEDIO:
        Rnode = RsDoFixedIoDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case INTERRUPT:
        Rnode = RsDoInterruptDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case IO:
        Rnode = RsDoIoDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case IRQ:
        Rnode = RsDoIrqDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case IRQNOFLAGS:
        Rnode = RsDoIrqNoFlagsDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case MEMORY24:
        Rnode = RsDoMemory24Descriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case MEMORY32:
        Rnode = RsDoMemory32Descriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case MEMORY32FIXED:
        Rnode = RsDoMemory32FixedDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case QWORDIO:
        Rnode = RsDoQwordIoDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case QWORDMEMORY:
        Rnode = RsDoQwordMemoryDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case REGISTER:
        Rnode = RsDoGeneralRegisterDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case STARTDEPENDENTFN:
        Rnode = RsDoStartDependentDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case STARTDEPENDENTFN_NOPRI:
        Rnode = RsDoStartDependentNoPriDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case VENDORLONG:
        Rnode = RsDoVendorLargeDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case VENDORSHORT:
        Rnode = RsDoVendorSmallDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case WORDBUSNUMBER:
        Rnode = RsDoWordBusNumberDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case WORDIO:
        Rnode = RsDoWordIoDescriptor (DescriptorTypeNode, CurrentByteOffset);
        break;

    case DEFAULT_ARG:
        /* Just ignore any of these, they are used as fillers/placeholders */
        break;

    default:
        printf ("Unknown resource descriptor type [%s]\n",
                    DescriptorTypeNode->ParseOpName);
        break;
    }


    /*
     * Mark original node as unused, but head of a resource descriptor.
     * This allows the resource to be installed in the namespace so that
     * references to the descriptor can be resolved.
     */
    DescriptorTypeNode->ParseOpcode = DEFAULT_ARG;
    DescriptorTypeNode->Flags = NODE_IS_RESOURCE_DESC;


    return (Rnode);
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
RsLinkDescriptorChain (
    ASL_RESOURCE_NODE       **PreviousRnode,
    ASL_RESOURCE_NODE       *Rnode)
{
    ASL_RESOURCE_NODE       *LastRnode;
    UINT32                  CurrentByteOffset;


    if (!Rnode)
    {
        return 0;
    }

    (*PreviousRnode)->Next = Rnode;
    CurrentByteOffset = Rnode->BufferLength;

    LastRnode = Rnode;
    while (LastRnode->Next)
    {
        LastRnode = LastRnode->Next;
        CurrentByteOffset += LastRnode->BufferLength;
    }

    *PreviousRnode = LastRnode;
    return CurrentByteOffset;
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
RsDoResourceTemplate (
    ASL_PARSE_NODE          *Node)
{
    ASL_PARSE_NODE          *BufferLengthNode;
    ASL_PARSE_NODE          *BufferNode;
    ASL_PARSE_NODE          *DescriptorTypeNode;
    ASL_RESOURCE_DESC       *Descriptor;
    UINT32                  CurrentByteOffset = 0;
    ASL_RESOURCE_NODE       HeadRnode;
    ASL_RESOURCE_NODE       *PreviousRnode;
    ASL_RESOURCE_NODE       *Rnode;


    /* ResourceTemplate Opcode is first (Node) */
    /* Buffer Length node is first child */

    BufferLengthNode = ASL_GET_CHILD_NODE (Node);

    /* Buffer Node is first peer */

    BufferNode = ASL_GET_PEER_NODE (BufferLengthNode);

    /* First Descriptor type is next */

    DescriptorTypeNode = ASL_GET_PEER_NODE (BufferNode);


    /* Process all resource descriptors in the list */

    PreviousRnode = &HeadRnode;
    while (DescriptorTypeNode)
    {
        Rnode = RsDoOneResourceDescriptor (DescriptorTypeNode, CurrentByteOffset);

        /*
         * Update current byte offset to indicate the number of bytes from the
         * start of the buffer.  Buffer can include multiple descriptors, we
         * must keep track of the offset of not only each descriptor, but each
         * element (field) within each descriptor as well.
         */
        CurrentByteOffset += RsLinkDescriptorChain (&PreviousRnode, Rnode);

        /* Get the next descriptor in the list */

        DescriptorTypeNode = ASL_GET_PEER_NODE (DescriptorTypeNode);
    }


    /*
     * Insert the EndTag descriptor after all other descriptors have been processed
     */
    Rnode = RsAllocateResourceNode (sizeof (ASL_END_TAG_DESC));

    Descriptor = Rnode->Buffer;
    Descriptor->Et.DescriptorType = RESOURCE_DESC_END_TAG;
    Descriptor->Et.Checksum = 0;

    CurrentByteOffset += RsLinkDescriptorChain (&PreviousRnode, Rnode);


    /*
     * Transform the nodes into the following
     *
     * Node             -> AML_BUFFER_OP
     * First Child      -> BufferLength
     * Second Child     -> Descriptor Buffer (raw byte data)
     */
    Node->ParseOpcode               = BUFFER;
    Node->AmlOpcode                 = AML_BUFFER_OP;
    Node->Flags                     = NODE_AML_PACKAGE;

    BufferLengthNode->ParseOpcode   = INTEGER;
    BufferLengthNode->Value.Integer = CurrentByteOffset;

    OpcSetOptimalIntegerSize (BufferLengthNode);

    BufferNode->ParseOpcode         = RAW_DATA;
    BufferNode->AmlOpcode           = AML_RAW_DATA_CHAIN;
    BufferNode->AmlOpcodeLength     = 0;
    BufferNode->AmlLength           = CurrentByteOffset;
    BufferNode->Value.Pointer       = HeadRnode.Next;

    return;
}


