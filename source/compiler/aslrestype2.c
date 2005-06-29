
/******************************************************************************
 *
 * Module Name: aslrestype2 - Long (type2) resource templates and descriptors
 *              $Revision: 1.6 $
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


#include "AslCompiler.h"
#include "AslCompiler.y.h"
#include "aslresource.h"
#include "amlcode.h"

#define _COMPONENT          COMPILER
        MODULE_NAME         ("aslrestype2")


/*******************************************************************************
 *
 * FUNCTION:    RsGetStringDataLength
 *
 * PARAMETERS:  InitializerNode     - Start of a subtree of init nodes
 *
 * RETURN:      Valid string length if a string node is found
 *
 * DESCRIPTION: In a list of peer nodes, find the first one that contains a
 *              string and return the length of the string.
 *
 ******************************************************************************/

UINT32
RsGetStringDataLength (
    ASL_PARSE_NODE          *InitializerNode)
{

    while (InitializerNode)
    {
        if (InitializerNode->ParseOpcode == STRING_LITERAL)
        {
            return (strlen (InitializerNode->Value.String) + 1);
        }

        InitializerNode = ASL_GET_PEER_NODE (InitializerNode);
    }

    return 0;
}


/*******************************************************************************
 *
 * FUNCTION:    RsDoDwordIoDescriptor
 *
 * PARAMETERS:  Node                - Parent resource descriptor parse node
 *              CurrentByteOffset   - Offset into the resource template AML
 *                                    buffer (to track references to the desc)
 *
 * RETURN:      Completed resource node
 *
 * DESCRIPTION: Construct a long "DwordIO" descriptor
 *
 ******************************************************************************/

ASL_RESOURCE_NODE *
RsDoDwordIoDescriptor (
    ASL_PARSE_NODE          *Node,
    UINT32                  CurrentByteOffset)
{
    ASL_RESOURCE_DESC       *Descriptor;
    ASL_PARSE_NODE          *InitializerNode;
    ASL_RESOURCE_NODE       *Rnode;
    UINT32                  StringLength = 0;
    UINT32                  OptionIndex = 0;
    UINT32                  i;


    InitializerNode = Node->Child;
    StringLength = RsGetStringDataLength (InitializerNode);

    Rnode = RsAllocateResourceNode (sizeof (ASL_DWORD_ADDRESS_DESC) +
                                    StringLength);

    Descriptor = Rnode->Buffer;
    Descriptor->Das.DescriptorType  = RESOURCE_DESC_DWORD_ADDRESS_SPACE;
    Descriptor->Das.ResourceType    = RESOURCE_TYPE_IO_RANGE;

    /*
     * Initial descriptor length -- may be enlarged if there are
     * optional fields present
     */
    Descriptor->Das.Length          = ASL_RESDESC_OFFSET (Das.OptionalFields) -
                                      ASL_RESDESC_OFFSET (Das.ResourceType);


    /*
     * Process all child initialization nodes
     */
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* MinType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 2, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MINTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.Flags), 2);
            break;

        case 2: /* MaxType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 3, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MAXTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.Flags), 3);
            break;

        case 3: /* DecodeType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 1, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_DECODE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.Flags), 1);
            break;

        case 4: /* Range Type */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 0, 3);
            RsCreateBitField (InitializerNode, ASL_RESNAME_RANGETYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.SpecificFlags), 0);
            break;

        case 5: /* Address Granularity */

            Descriptor->Das.Granularity = InitializerNode->Value.Integer32;
            RsCreateByteField (InitializerNode, ASL_RESNAME_GRANULARITY,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.Granularity));
            break;

        case 6: /* Address Min */

            Descriptor->Das.AddressMin = InitializerNode->Value.Integer32;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MINADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.AddressMin));
            break;

        case 7: /* Address Max */

            Descriptor->Das.AddressMax = InitializerNode->Value.Integer32;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MAXADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.AddressMax));
            break;

        case 8: /* Translation Offset */

            Descriptor->Das.TranslationOffset = InitializerNode->Value.Integer32;
            RsCreateByteField (InitializerNode, ASL_RESNAME_TRANSLATION,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.TranslationOffset));
            break;

        case 9: /* Address Length */

            Descriptor->Das.AddressLength = InitializerNode->Value.Integer32;
            RsCreateByteField (InitializerNode, ASL_RESNAME_LENGTH,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.AddressLength));
            break;

        case 10: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Das.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
                Descriptor->Das.Length++;
            }
            break;

        case 11: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                if (StringLength)
                {
                    Descriptor->Das.Length += StringLength;

                    strcpy (&Descriptor->Das.OptionalFields[OptionIndex],
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 12: /* ResourceTag */

            UtAttachNamepathToOwner (Node, InitializerNode);
            break;

        case 13: /* Type */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 4, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_TYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.SpecificFlags), 4);
            break;

        case 14: /* Translation Type */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 5, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_TRANSTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.SpecificFlags), 5);
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    Rnode->BufferLength = (ASL_RESDESC_OFFSET (Das.OptionalFields) -
                           ASL_RESDESC_OFFSET (Das.DescriptorType))
                           + OptionIndex + StringLength;
    return (Rnode);
}


/*******************************************************************************
 *
 * FUNCTION:    RsDoDwordMemoryDescriptor
 *
 * PARAMETERS:  Node                - Parent resource descriptor parse node
 *              CurrentByteOffset   - Offset into the resource template AML
 *                                    buffer (to track references to the desc)
 *
 * RETURN:      Completed resource node
 *
 * DESCRIPTION: Construct a long "DwordMemory" descriptor
 *
 ******************************************************************************/

ASL_RESOURCE_NODE *
RsDoDwordMemoryDescriptor (
    ASL_PARSE_NODE          *Node,
    UINT32                  CurrentByteOffset)
{
    ASL_RESOURCE_DESC       *Descriptor;
    ASL_PARSE_NODE          *InitializerNode;
    ASL_RESOURCE_NODE       *Rnode;
    UINT32                  StringLength = 0;
    UINT32                  OptionIndex = 0;
    UINT32                  i;


    InitializerNode = Node->Child;
    StringLength = RsGetStringDataLength (InitializerNode);

    Rnode = RsAllocateResourceNode (sizeof (ASL_DWORD_ADDRESS_DESC) +
                                    StringLength);

    Descriptor = Rnode->Buffer;
    Descriptor->Das.DescriptorType  = RESOURCE_DESC_DWORD_ADDRESS_SPACE;
    Descriptor->Das.ResourceType    = RESOURCE_TYPE_MEMORY_RANGE;

    /*
     * Initial descriptor length -- may be enlarged if there are
     * optional fields present
     */
    Descriptor->Das.Length          = ASL_RESDESC_OFFSET (Das.OptionalFields) -
                                      ASL_RESDESC_OFFSET (Das.ResourceType);

    /*
     * Process all child initialization nodes
     */
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* DecodeType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 1, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_DECODE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.Flags), 1);
            break;

        case 2: /* MinType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 2, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MINTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.Flags), 2);
            break;

        case 3: /* MaxType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 3, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MAXTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.Flags), 3);
            break;

        case 4: /* Memory Type */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 1, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MEMTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.SpecificFlags), 1);
            break;

        case 5: /* Read/Write Type */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 0, 1);
            RsCreateBitField (InitializerNode, ASL_RESNAME_READWRITETYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.SpecificFlags), 0);
            break;

        case 6: /* Address Granularity */

            Descriptor->Das.Granularity = InitializerNode->Value.Integer32;
            RsCreateByteField (InitializerNode, ASL_RESNAME_GRANULARITY,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.Granularity));
            break;

        case 7: /* Min Address */

            Descriptor->Das.AddressMin = InitializerNode->Value.Integer32;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MINADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.AddressMin));
            break;

        case 8: /* Max Address */

            Descriptor->Das.AddressMax = InitializerNode->Value.Integer32;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MAXADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.AddressMax));
            break;

        case 9: /* Translation Offset */

            Descriptor->Das.TranslationOffset = InitializerNode->Value.Integer32;
            RsCreateByteField (InitializerNode, ASL_RESNAME_TRANSLATION,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.TranslationOffset));
            break;

        case 10: /* Address Length */

            Descriptor->Das.AddressLength = InitializerNode->Value.Integer32;
            RsCreateByteField (InitializerNode, ASL_RESNAME_LENGTH,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.AddressLength));
            break;

        case 11: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Das.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
                Descriptor->Das.Length++;
            }
            break;

        case 12: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                if (StringLength)
                {
                    Descriptor->Das.Length += StringLength;

                    strcpy (&Descriptor->Das.OptionalFields[OptionIndex],
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 13: /* ResourceTag */

            UtAttachNamepathToOwner (Node, InitializerNode);
            break;


        case 14: /* Address Range */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 3, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MEMATTRIBUTES,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.SpecificFlags), 3);
            break;

        case 15: /* Type */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 5, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_TYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Das.SpecificFlags), 5);
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    Rnode->BufferLength = (ASL_RESDESC_OFFSET (Das.OptionalFields) -
                           ASL_RESDESC_OFFSET (Das.DescriptorType))
                           + OptionIndex + StringLength;
    return (Rnode);
}


/*******************************************************************************
 *
 * FUNCTION:    RsDoQwordIoDescriptor
 *
 * PARAMETERS:  Node                - Parent resource descriptor parse node
 *              CurrentByteOffset   - Offset into the resource template AML
 *                                    buffer (to track references to the desc)
 *
 * RETURN:      Completed resource node
 *
 * DESCRIPTION: Construct a long "QwordIO" descriptor
 *
 ******************************************************************************/

ASL_RESOURCE_NODE *
RsDoQwordIoDescriptor (
    ASL_PARSE_NODE          *Node,
    UINT32                  CurrentByteOffset)
{
    ASL_RESOURCE_DESC       *Descriptor;
    ASL_PARSE_NODE          *InitializerNode;
    ASL_RESOURCE_NODE       *Rnode;
    UINT32                  StringLength = 0;
    UINT32                  OptionIndex = 0;
    UINT32                  i;


    InitializerNode = Node->Child;
    StringLength = RsGetStringDataLength (InitializerNode);

    Rnode = RsAllocateResourceNode (sizeof (ASL_QWORD_ADDRESS_DESC) +
                                    StringLength);

    Descriptor = Rnode->Buffer;
    Descriptor->Qas.DescriptorType  = RESOURCE_DESC_QWORD_ADDRESS_SPACE;
    Descriptor->Qas.ResourceType    = RESOURCE_TYPE_IO_RANGE;

    /*
     * Initial descriptor length -- may be enlarged if there are
     * optional fields present
     */
    Descriptor->Qas.Length          = ASL_RESDESC_OFFSET (Qas.OptionalFields) -
                                      ASL_RESDESC_OFFSET (Qas.ResourceType);
    /*
     * Process all child initialization nodes
     */
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* MinType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 2, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MINTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.Flags), 2);
            break;

        case 2: /* MaxType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 3, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MAXTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.Flags), 3);
            break;

        case 3: /* DecodeType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 1, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_DECODE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.Flags), 1);
            break;

        case 4: /* Range Type */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 0, 3);
            RsCreateBitField (InitializerNode, ASL_RESNAME_RANGETYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.SpecificFlags), 0);
            break;

        case 5: /* Address Granularity */

            Descriptor->Qas.Granularity = InitializerNode->Value.Integer64;
             RsCreateByteField (InitializerNode, ASL_RESNAME_GRANULARITY,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.Granularity));
           break;

        case 6: /* Address Min */

            Descriptor->Qas.AddressMin = InitializerNode->Value.Integer64;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MINADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.AddressMin));
            break;

        case 7: /* Address Max */

            Descriptor->Qas.AddressMax = InitializerNode->Value.Integer64;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MAXADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.AddressMax));
            break;

        case 8: /* Translation Offset */

            Descriptor->Qas.TranslationOffset = InitializerNode->Value.Integer64;
            RsCreateByteField (InitializerNode, ASL_RESNAME_TRANSLATION,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.TranslationOffset));
            break;

        case 9: /* Address Length */

            Descriptor->Qas.AddressLength = InitializerNode->Value.Integer64;
            RsCreateByteField (InitializerNode, ASL_RESNAME_LENGTH,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.AddressLength));
            break;

        case 10: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Qas.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
                Descriptor->Qas.Length++;
            }
            break;

        case 11: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                if (StringLength)
                {
                    Descriptor->Qas.Length += StringLength;

                    strcpy (&Descriptor->Qas.OptionalFields[OptionIndex],
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 12: /* ResourceTag */

            UtAttachNamepathToOwner (Node, InitializerNode);
            break;

        case 13: /* Type */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 4, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_TYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.SpecificFlags), 4);
            break;

        case 14: /* Translation Type */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 5, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_TRANSTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.SpecificFlags), 5);
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    Rnode->BufferLength = (ASL_RESDESC_OFFSET (Qas.OptionalFields) -
                           ASL_RESDESC_OFFSET (Qas.DescriptorType))
                           + OptionIndex + StringLength;
    return (Rnode);
}


/*******************************************************************************
 *
 * FUNCTION:    RsDoQwordMemoryDescriptor
 *
 * PARAMETERS:  Node                - Parent resource descriptor parse node
 *              CurrentByteOffset   - Offset into the resource template AML
 *                                    buffer (to track references to the desc)
 *
 * RETURN:      Completed resource node
 *
 * DESCRIPTION: Construct a long "QwordMemory" descriptor
 *
 ******************************************************************************/

ASL_RESOURCE_NODE *
RsDoQwordMemoryDescriptor (
    ASL_PARSE_NODE          *Node,
    UINT32                  CurrentByteOffset)
{
    ASL_RESOURCE_DESC       *Descriptor;
    ASL_PARSE_NODE          *InitializerNode;
    ASL_RESOURCE_NODE       *Rnode;
    UINT32                  StringLength = 0;
    UINT32                  OptionIndex = 0;
    UINT32                  i;


    InitializerNode = Node->Child;
    StringLength = RsGetStringDataLength (InitializerNode);

    Rnode = RsAllocateResourceNode (sizeof (ASL_QWORD_ADDRESS_DESC) +
                                    StringLength);

    Descriptor = Rnode->Buffer;
    Descriptor->Qas.DescriptorType  = RESOURCE_DESC_QWORD_ADDRESS_SPACE;
    Descriptor->Qas.ResourceType    = RESOURCE_TYPE_MEMORY_RANGE;

    /*
     * Initial descriptor length -- may be enlarged if there are
     * optional fields present
     */
    Descriptor->Qas.Length          = ASL_RESDESC_OFFSET (Qas.OptionalFields) -
                                      ASL_RESDESC_OFFSET (Qas.ResourceType);
    /*
     * Process all child initialization nodes
     */
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* DecodeType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 1, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_DECODE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.Flags), 1);
            break;

        case 2: /* MinType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 2, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MINTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.Flags), 2);
            break;

        case 3: /* MaxType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 3, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MAXTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.Flags), 3);
            break;

        case 4: /* Memory Type */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 1, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MEMTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.SpecificFlags), 1);
            break;

        case 5: /* Read/Write Type */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 0, 1);
            RsCreateBitField (InitializerNode, ASL_RESNAME_READWRITETYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.SpecificFlags), 0);
            break;

        case 6: /* Address Granularity */

            Descriptor->Qas.Granularity = InitializerNode->Value.Integer64;
            RsCreateByteField (InitializerNode, ASL_RESNAME_GRANULARITY,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.Granularity));
            break;

        case 7: /* Min Address */

            Descriptor->Qas.AddressMin = InitializerNode->Value.Integer64;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MINADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.AddressMin));
            break;

        case 8: /* Max Address */

            Descriptor->Qas.AddressMax = InitializerNode->Value.Integer64;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MAXADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.AddressMax));
            break;

        case 9: /* Translation Offset */

            Descriptor->Qas.TranslationOffset = InitializerNode->Value.Integer64;
            RsCreateByteField (InitializerNode, ASL_RESNAME_TRANSLATION,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.TranslationOffset));
            break;

        case 10: /* Address Length */

            Descriptor->Qas.AddressLength = InitializerNode->Value.Integer64;
            RsCreateByteField (InitializerNode, ASL_RESNAME_LENGTH,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.AddressLength));
            break;

        case 11: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Qas.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
                Descriptor->Qas.Length++;
            }
            break;

        case 12: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                if (StringLength)
                {
                    Descriptor->Qas.Length += StringLength;

                    strcpy (&Descriptor->Qas.OptionalFields[OptionIndex],
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 13: /* ResourceTag */

            UtAttachNamepathToOwner (Node, InitializerNode);
            break;


        case 14: /* Address Range */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 3, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MEMATTRIBUTES,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.SpecificFlags), 3);
            break;

        case 15: /* Type */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 5, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_TYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Qas.SpecificFlags), 5);
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    Rnode->BufferLength = (ASL_RESDESC_OFFSET (Qas.OptionalFields) -
                           ASL_RESDESC_OFFSET (Qas.DescriptorType))
                           + OptionIndex + StringLength;
    return (Rnode);
}


/*******************************************************************************
 *
 * FUNCTION:    RsDoWordIoDescriptor
 *
 * PARAMETERS:  Node                - Parent resource descriptor parse node
 *              CurrentByteOffset   - Offset into the resource template AML
 *                                    buffer (to track references to the desc)
 *
 * RETURN:      Completed resource node
 *
 * DESCRIPTION: Construct a long "WordIO" descriptor
 *
 ******************************************************************************/

ASL_RESOURCE_NODE *
RsDoWordIoDescriptor (
    ASL_PARSE_NODE          *Node,
    UINT32                  CurrentByteOffset)
{
    ASL_RESOURCE_DESC       *Descriptor;
    ASL_PARSE_NODE          *InitializerNode;
    ASL_RESOURCE_NODE       *Rnode;
    UINT32                  StringLength = 0;
    UINT32                  OptionIndex = 0;
    UINT32                  i;


    InitializerNode = Node->Child;
    StringLength = RsGetStringDataLength (InitializerNode);

    Rnode = RsAllocateResourceNode (sizeof (ASL_WORD_ADDRESS_DESC) +
                                    StringLength);

    Descriptor = Rnode->Buffer;
    Descriptor->Was.DescriptorType  = RESOURCE_DESC_WORD_ADDRESS_SPACE;
    Descriptor->Was.ResourceType    = RESOURCE_TYPE_IO_RANGE;

    /*
     * Initial descriptor length -- may be enlarged if there are
     * optional fields present
     */
    Descriptor->Was.Length          = ASL_RESDESC_OFFSET (Was.OptionalFields) -
                                      ASL_RESDESC_OFFSET (Was.ResourceType);

    /*
     * Process all child initialization nodes
     */
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* MinType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 2, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MINTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.Flags), 2);
            break;

        case 2: /* MaxType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 3, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MAXTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.Flags), 3);
            break;

        case 3: /* DecodeType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 1, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_DECODE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.Flags), 1);
            break;

        case 4: /* Range Type */

            RsSetFlagBits (&Descriptor->Was.SpecificFlags, InitializerNode, 0, 3);
            RsCreateBitField (InitializerNode, ASL_RESNAME_RANGETYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.SpecificFlags), 0);
            break;

        case 5: /* Address Granularity */

            Descriptor->Was.Granularity = InitializerNode->Value.Integer16;
            RsCreateByteField (InitializerNode, ASL_RESNAME_GRANULARITY,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.Granularity));
            break;

        case 6: /* Address Min */

            Descriptor->Was.AddressMin = InitializerNode->Value.Integer16;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MINADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.AddressMin));
            break;

        case 7: /* Address Max */

            Descriptor->Was.AddressMax = InitializerNode->Value.Integer16;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MAXADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.AddressMax));
            break;

        case 8: /* Translation Offset */

            Descriptor->Was.TranslationOffset = InitializerNode->Value.Integer16;
            RsCreateByteField (InitializerNode, ASL_RESNAME_TRANSLATION,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.TranslationOffset));
            break;

        case 9: /* Address Length */

            Descriptor->Was.AddressLength = InitializerNode->Value.Integer16;
            RsCreateByteField (InitializerNode, ASL_RESNAME_LENGTH,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.AddressLength));
            break;

        case 10: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Was.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
                Descriptor->Was.Length++;
            }
            break;

        case 11: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                if (StringLength)
                {
                    Descriptor->Was.Length += StringLength;

                    strcpy (&Descriptor->Was.OptionalFields[OptionIndex],
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 12: /* ResourceTag */

            UtAttachNamepathToOwner (Node, InitializerNode);
            break;

        case 13: /* Type */

            RsSetFlagBits (&Descriptor->Was.SpecificFlags, InitializerNode, 4, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_TYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.SpecificFlags), 4);
            break;

        case 14: /* Translation Type */

            RsSetFlagBits (&Descriptor->Was.SpecificFlags, InitializerNode, 5, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_TRANSTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.SpecificFlags), 5);
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    Rnode->BufferLength = (ASL_RESDESC_OFFSET (Was.OptionalFields) -
                           ASL_RESDESC_OFFSET (Was.DescriptorType))
                           + OptionIndex + StringLength;
    return (Rnode);
}


/*******************************************************************************
 *
 * FUNCTION:    RsDoWordBusNumberDescriptor
 *
 * PARAMETERS:  Node                - Parent resource descriptor parse node
 *              CurrentByteOffset   - Offset into the resource template AML
 *                                    buffer (to track references to the desc)
 *
 * RETURN:      Completed resource node
 *
 * DESCRIPTION: Construct a long "WordBusNumber" descriptor
 *
 ******************************************************************************/

ASL_RESOURCE_NODE *
RsDoWordBusNumberDescriptor (
    ASL_PARSE_NODE          *Node,
    UINT32                  CurrentByteOffset)
{
    ASL_RESOURCE_DESC       *Descriptor;
    ASL_PARSE_NODE          *InitializerNode;
    ASL_RESOURCE_NODE       *Rnode;
    UINT32                  StringLength = 0;
    UINT32                  OptionIndex = 0;
    UINT32                  i;


    InitializerNode = Node->Child;
    StringLength = RsGetStringDataLength (InitializerNode);

    Rnode = RsAllocateResourceNode (sizeof (ASL_WORD_ADDRESS_DESC) +
                                    StringLength);

    Descriptor = Rnode->Buffer;
    Descriptor->Was.DescriptorType  = RESOURCE_DESC_WORD_ADDRESS_SPACE;
    Descriptor->Was.ResourceType    = RESOURCE_TYPE_BUS_NUMBER_RANGE;

    /*
     * Initial descriptor length -- may be enlarged if there are
     * optional fields present
     */
    Descriptor->Was.Length          = ASL_RESDESC_OFFSET (Was.OptionalFields) -
                                      ASL_RESDESC_OFFSET (Was.ResourceType);

    /*
     * Process all child initialization nodes
     */
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* MinType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 2, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MINTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.Flags), 2);
            break;

        case 2: /* MaxType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 3, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_MAXTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.Flags), 3);
            break;

        case 3: /* DecodeType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 1, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_DECODE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.Flags), 1);
            break;

        case 4: /* Address Granularity */

            Descriptor->Was.Granularity = InitializerNode->Value.Integer16;
            RsCreateByteField (InitializerNode, ASL_RESNAME_GRANULARITY,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.Granularity));
            break;

        case 5: /* Min Address */

            Descriptor->Was.AddressMin = InitializerNode->Value.Integer16;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MINADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.AddressMin));
            break;

        case 6: /* Max Address */

            Descriptor->Was.AddressMax = InitializerNode->Value.Integer16;
            RsCreateByteField (InitializerNode, ASL_RESNAME_MAXADDR,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.AddressMax));
            break;

        case 7: /* Translation Offset */

            Descriptor->Was.TranslationOffset = InitializerNode->Value.Integer16;
            RsCreateByteField (InitializerNode, ASL_RESNAME_TRANSLATION,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.TranslationOffset));
            break;

        case 8: /* Address Length */

            Descriptor->Was.AddressLength = InitializerNode->Value.Integer16;
            RsCreateByteField (InitializerNode, ASL_RESNAME_LENGTH,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Was.AddressLength));
            break;

        case 9: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Was.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
                Descriptor->Was.Length++;
            }
            break;

        case 10: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                if (StringLength)
                {
                    Descriptor->Was.Length += StringLength;

                    strcpy (&Descriptor->Was.OptionalFields[OptionIndex],
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 11: /* ResourceTag */

            UtAttachNamepathToOwner (Node, InitializerNode);
            break;
        }


        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }


    Rnode->BufferLength = (ASL_RESDESC_OFFSET (Was.OptionalFields) -
                           ASL_RESDESC_OFFSET (Was.DescriptorType))
                           + OptionIndex + StringLength;
    return (Rnode);
}


/*******************************************************************************
 *
 * FUNCTION:    RsDoInterruptDescriptor
 *
 * PARAMETERS:  Node                - Parent resource descriptor parse node
 *              CurrentByteOffset   - Offset into the resource template AML
 *                                    buffer (to track references to the desc)
 *
 * RETURN:      Completed resource node
 *
 * DESCRIPTION: Construct a long "Interrupt" descriptor
 *
 ******************************************************************************/

ASL_RESOURCE_NODE *
RsDoInterruptDescriptor (
    ASL_PARSE_NODE          *Node,
    UINT32                  CurrentByteOffset)
{
    ASL_RESOURCE_DESC       *Descriptor;
    ASL_PARSE_NODE          *InitializerNode;
    ASL_RESOURCE_NODE       *Rnode;
    UINT32                  StringLength = 0;
    UINT32                  OptionIndex = 0;
    UINT32                  i;
    BOOLEAN                 HasResSourceIndex = FALSE;
    UINT8                   ResSourceIndex;
    UINT8                   *ResSourceString;


    InitializerNode = Node->Child;
    StringLength = RsGetStringDataLength (InitializerNode);

    Rnode = RsAllocateResourceNode (sizeof (ASL_EXTENDED_XRUPT_DESC) +
                                    StringLength);

    Descriptor = Rnode->Buffer;
    Descriptor->Exx.DescriptorType  = RESOURCE_DESC_EXTENDED_XRUPT;

    /*
     * Initial descriptor length -- may be enlarged if there are
     * optional fields present
     */
    Descriptor->Exx.Length          = 2;  /* Flags and table length byte */
    Descriptor->Exx.TableLength     = 0;

    /*
     * Process all child initialization nodes
     */
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type (Default: consumer (1) */

            RsSetFlagBits (&Descriptor->Exx.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* Interrupt Type (or Mode - edge/level) */

            RsSetFlagBits (&Descriptor->Exx.Flags, InitializerNode, 1, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_INTERRUPTTYPE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Exx.Flags), 0);
            break;

        case 2: /* Interrupt Level (or Polarity - Active high/low) */

            RsSetFlagBits (&Descriptor->Exx.Flags, InitializerNode, 2, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_INTERRUPTLEVEL,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Exx.Flags), 2);
            break;

        case 3: /* Share Type - Default: exclusive (0) */

            RsSetFlagBits (&Descriptor->Exx.Flags, InitializerNode, 3, 0);
            RsCreateBitField (InitializerNode, ASL_RESNAME_INTERRUPTSHARE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Exx.Flags), 3);
            break;

        case 4: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                HasResSourceIndex = TRUE;
                ResSourceIndex = InitializerNode->Value.Integer8;
                OptionIndex++;
            }
            break;

        case 5: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                if (StringLength)
                {
                    ResSourceString = InitializerNode->Value.Pointer;
                }
            }
            break;

        case 6: /* ResourceTag */

            UtAttachNamepathToOwner (Node, InitializerNode);
            break;


        default:

            /* Interrupt Numbers come through here, repeatedly */

            * ((UINT32 *) Descriptor) = InitializerNode->Value.Integer32;
            ((UINT32 *) Descriptor)++;

            /* StartOfDescriptor->Exx.TableLength++;
               StartOfDescriptor->Exx.Length += 4;

             */
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }


    /*
     * Add optional ResSourceIndex if present
     */
    if (HasResSourceIndex)
    {
        * ((UINT8 *) Descriptor) = ResSourceIndex;
        ((UINT8 *) Descriptor)++;

        /*
        StartOfDescriptor->Exx.Length++;
        */
    }


    /*
     * Add optional ResSource string if present
     */
    if (StringLength)
    {

        strcpy ((char *) Descriptor, ResSourceString);
        ((UINT8 *) Descriptor) += StringLength;
    }

    Rnode->BufferLength = (ASL_RESDESC_OFFSET (Exx.InterruptNumber) -
                           ASL_RESDESC_OFFSET (Exx.DescriptorType))
                           + OptionIndex + StringLength;
    return (Rnode);
}


/*******************************************************************************
 *
 * FUNCTION:    RsDoVendorLargeDescriptor
 *
 * PARAMETERS:  Node                - Parent resource descriptor parse node
 *              CurrentByteOffset   - Offset into the resource template AML
 *                                    buffer (to track references to the desc)
 *
 * RETURN:      Completed resource node
 *
 * DESCRIPTION: Construct a long "VendorLong" descriptor
 *
 ******************************************************************************/

ASL_RESOURCE_NODE *
RsDoVendorLargeDescriptor (
    ASL_PARSE_NODE          *Node,
    UINT32                  CurrentByteOffset)
{
    ASL_RESOURCE_DESC       *Descriptor;
    ASL_PARSE_NODE          *InitializerNode;
    ASL_RESOURCE_NODE       *Rnode;
    UINT32                  i;


    /* Count the number of data bytes */

    InitializerNode = Node->Child;

    for (i = 0; InitializerNode; i++)
    {
        InitializerNode = InitializerNode->Peer;
    }

    InitializerNode = Node->Child;
    Rnode = RsAllocateResourceNode (sizeof (ASL_LARGE_VENDOR_DESC) + (i + 1));

    Descriptor = Rnode->Buffer;
    Descriptor->Lgv.DescriptorType  = RESOURCE_DESC_LARGE_VENDOR;


    /*
     * Process all child initialization nodes
     */
    for (i = 0; InitializerNode; i++)
    {
        Descriptor->Lgv.VendorDefined[i] = InitializerNode->Value.Integer8;

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }


    return (Rnode);
}


/*******************************************************************************
 *
 * FUNCTION:    RsDoGeneralRegisterDescriptor
 *
 * PARAMETERS:  Node                - Parent resource descriptor parse node
 *              CurrentByteOffset   - Offset into the resource template AML
 *                                    buffer (to track references to the desc)
 *
 * RETURN:      Completed resource node
 *
 * DESCRIPTION: Construct a long "Register" descriptor
 *
 ******************************************************************************/

ASL_RESOURCE_NODE *
RsDoGeneralRegisterDescriptor (
    ASL_PARSE_NODE          *Node,
    UINT32                  CurrentByteOffset)
{
    ASL_RESOURCE_DESC       *Descriptor;
    ASL_PARSE_NODE          *InitializerNode;
    ASL_RESOURCE_NODE       *Rnode;
    UINT32                  i;


    InitializerNode = Node->Child;

    Rnode = RsAllocateResourceNode (sizeof (ASL_GENERAL_REGISTER_DESC));

    Descriptor = Rnode->Buffer;
    Descriptor->Grg.DescriptorType  = RESOURCE_DESC_GENERAL_REGISTER;

    Descriptor->Grg.Length          = 12;

    /*
     * Process all child initialization nodes
     */
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Address space */

            Descriptor->Grg.AddressSpaceId = InitializerNode->Value.Integer8;
            RsCreateByteField (InitializerNode, ASL_RESNAME_ADDRESSSPACE,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Grg.AddressSpaceId));
           break;

        case 1: /* Register Bit Width */

            Descriptor->Grg.BitWidth = InitializerNode->Value.Integer8;
            RsCreateByteField (InitializerNode, ASL_RESNAME_REGISTERBITWIDTH,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Grg.BitWidth));
            break;

        case 2: /* Register Bit Offset */

            Descriptor->Grg.BitOffset = InitializerNode->Value.Integer8;
            RsCreateByteField (InitializerNode, ASL_RESNAME_REGISTERBITOFFSET,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Grg.BitOffset));
            break;

        case 3: /* Register Address */

            Descriptor->Grg.Address = InitializerNode->Value.Integer8;
            RsCreateByteField (InitializerNode, ASL_RESNAME_ADDRESS,
                                CurrentByteOffset + ASL_RESDESC_OFFSET (Grg.Address));
            break;

        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }


    return (Rnode);
}


