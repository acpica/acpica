
/******************************************************************************
 *
 * Module Name: aslresource - Resource templates and descriptors
 *              $Revision: 1.2 $
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

void
RsDoXXXDescriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      i;

    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->Iop.DescriptorType  = RESOURCE_DESC_IO_PORT;


    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Decode size */

            Descriptor->Iop.AddressMin = InitializerNode->Value.Integer16;
            break;

        case 1:  /* Min Address */

            Descriptor->Iop.AddressMin = InitializerNode->Value.Integer16;
            break;

        case 2: /* Max Address */

            Descriptor->Iop.AddressMax = InitializerNode->Value.Integer16;
            break;

        case 3: /* Alignment */

            Descriptor->Iop.Alignment = InitializerNode->Value.Integer8;
            break;

        case 4: /* Length */

            Descriptor->Iop.Length = InitializerNode->Value.Integer8;
            break;

        case 5: /* Name */

            /* TBD: What do we do with this? */
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) &Descriptor->Iop.Length) + 1);
    return;
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
RsDoDmaDescriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      i;
    UINT8                       DmaChannelMask = 0;


    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->Iop.DescriptorType  = RESOURCE_DESC_DMA_FORMAT;


    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* DMA type */

            RsSetFlagBits (&Descriptor->Dma.Flags, InitializerNode, 5, 0);
            break;

        case 1: /* Bus Master */

            RsSetFlagBits (&Descriptor->Dma.Flags, InitializerNode, 2, 0);
            break;

        case 2: /* Xfer Type */

            RsSetFlagBits (&Descriptor->Dma.Flags, InitializerNode, 0, 0);
            break;

        case 3: /* Name */

            /* TBD: What do we do with this? */
            break;

        default:

            /* DMA channel bytes are handled here, after the flags and name */

            DmaChannelMask |= (1 << InitializerNode->Value.Integer8);
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }


    /* Now we can set the channel mask */

    Descriptor->Dma.DmaChannelMask = DmaChannelMask;

    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) &Descriptor->Dma.Flags) + 1);
    return;
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
RsDoDwordIoDescriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      DescriptorSize = DEFAULT_RESOURCE_DESC_SIZE;
    UINT32                      StringLength = 0;
    UINT32                      OptionIndex = 0;
    UINT32                      i;


    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->Das.DescriptorType  = RESOURCE_DESC_DWORD_ADDRESS_SPACE;
    Descriptor->Das.ResourceType    = RESOURCE_TYPE_IO_RANGE;


    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* MinType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 2, 0);
            break;

        case 2: /* MaxType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 3, 0);
            break;

        case 3: /* DecodeType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 1, 0);
            break;

        case 4: /* Range Type */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 0, 3);
            break;

        case 5: /* Address Granularity */

            Descriptor->Das.Granularity = InitializerNode->Value.Integer32;
            break;

        case 6: /* Address Min */

            Descriptor->Das.AddressMin = InitializerNode->Value.Integer32;
            break;

        case 7: /* Address Max */

            Descriptor->Das.AddressMax = InitializerNode->Value.Integer32;
            break;

        case 8: /* Translation Offset */

            Descriptor->Das.TranslationOffset = InitializerNode->Value.Integer32;
            break;

        case 9: /* Address Length */

            Descriptor->Das.AddressLength = InitializerNode->Value.Integer32;
            break;

        case 10: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Das.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
            }
            break;

        case 11: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                StringLength = strlen (InitializerNode->Value.Pointer);
                if (StringLength)
                {
                    DescriptorSize += StringLength;                     /* Null terminator already accounted for */
                    Descriptor = UtLocalRealloc (Descriptor, DescriptorSize);

                    strcpy (&Descriptor->Das.OptionalFields[OptionIndex], 
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 12: /* ResourceTag */

            /* TBD:  What to do with this? Just mark unused for now */
            break;

        case 13: /* Type */
            
            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 4, 0);
            break;

        case 14: /* Translation Type */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 5, 0);
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) Descriptor->Das.OptionalFields) + 
                                            (OptionIndex + StringLength));
    return;
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
RsDoDwordMemoryDescriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      DescriptorSize = DEFAULT_RESOURCE_DESC_SIZE;
    UINT32                      StringLength = 0;
    UINT32                      OptionIndex = 0;
    UINT32                      i;


    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->Das.DescriptorType  = RESOURCE_DESC_DWORD_ADDRESS_SPACE;
    Descriptor->Das.ResourceType    = RESOURCE_TYPE_MEMORY_RANGE;


    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* DecodeType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 1, 0);
            break;

        case 2: /* MinType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 2, 0);
            break;

        case 3: /* MaxType */

            RsSetFlagBits (&Descriptor->Das.Flags, InitializerNode, 3, 0);
            break;

        case 4: /* Memory Type */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 1, 0);
            break;

        case 5: /* Read/Write Type */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 0, 1);
            break;

        case 6: /* Address Granularity */

            Descriptor->Das.Granularity = InitializerNode->Value.Integer32;
            break;

        case 7: /* Min Address */

            Descriptor->Das.AddressMin = InitializerNode->Value.Integer32;
            break;

        case 8: /* Max Address */

            Descriptor->Das.AddressMax = InitializerNode->Value.Integer32;
            break;

        case 9: /* Translation Offset */    

            Descriptor->Das.TranslationOffset = InitializerNode->Value.Integer32;
            break;

        case 10: /* Address Length */

            Descriptor->Das.AddressLength = InitializerNode->Value.Integer32;
            break;

        case 11: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Das.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
            }
            break;

        case 12: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                StringLength = strlen (InitializerNode->Value.Pointer);
                if (StringLength)
                {
                    DescriptorSize += StringLength;                     /* Null terminator already accounted for */
                    Descriptor = UtLocalRealloc (Descriptor, DescriptorSize);

                    strcpy (&Descriptor->Das.OptionalFields[OptionIndex], 
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 13: /* ResourceTag */
            break;


        case 14: /* Address Range */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 3, 0);
            break;

        case 15: /* Type Translation */

            RsSetFlagBits (&Descriptor->Das.SpecificFlags, InitializerNode, 5, 0);
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) Descriptor->Das.OptionalFields) + 
                                            (OptionIndex + StringLength));
    return;
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
CgDoIoDescriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      i;


    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->Iop.DescriptorType  = RESOURCE_DESC_IO_PORT;


    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Decode size */

            RsSetFlagBits (&Descriptor->Iop.Information, InitializerNode, 0, 1);
            break;

        case 1:  /* Min Address */

            Descriptor->Iop.AddressMin = InitializerNode->Value.Integer16;
            break;

        case 2: /* Max Address */

            Descriptor->Iop.AddressMax = InitializerNode->Value.Integer16;
            break;

        case 3: /* Alignment */

            Descriptor->Iop.Alignment = InitializerNode->Value.Integer8;
            break;

        case 4: /* Length */

            Descriptor->Iop.Length = InitializerNode->Value.Integer8;
            break;

        case 5: /* Name */

            /* TBD: What do we do with this? */
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) &Descriptor->Iop.Length) + 1);
    return;
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
RsDoMemory24Descriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      i;


    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->M24.DescriptorType  = RESOURCE_DESC_MEMORY_24;
    Descriptor->M24.Length = 9;


    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Read/Write type */

            RsSetFlagBits (&Descriptor->M24.Information, InitializerNode, 0, 1);
            break;

        case 1:  /* Min Address */

            Descriptor->M24.AddressMin = InitializerNode->Value.Integer16;
            break;

        case 2: /* Max Address */

            Descriptor->M24.AddressMax = InitializerNode->Value.Integer16;
            break;

        case 3: /* Alignment */

            Descriptor->M24.Alignment = InitializerNode->Value.Integer16;
            break;

        case 4: /* Length */

            Descriptor->M24.RangeLength = InitializerNode->Value.Integer16;
            break;

        case 5: /* Name */

            /* TBD: What do we do with this? */
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) &Descriptor->M24.RangeLength) + 1);
    return;
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
RsDoMemory32Descriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      i;


    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->M32.DescriptorType  = RESOURCE_DESC_MEMORY_32;
    Descriptor->M32.Length = 17;


    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Read/Write type */

            RsSetFlagBits (&Descriptor->M32.Information, InitializerNode, 0, 1);
            break;

        case 1:  /* Min Address */

            Descriptor->M32.AddressMin = InitializerNode->Value.Integer32;
            break;

        case 2: /* Max Address */

            Descriptor->M32.AddressMax = InitializerNode->Value.Integer32;
            break;

        case 3: /* Alignment */

            Descriptor->M32.Alignment = InitializerNode->Value.Integer32;
            break;

        case 4: /* Length */

            Descriptor->M32.RangeLength = InitializerNode->Value.Integer32;
            break;

        case 5: /* Name */

            /* TBD: What do we do with this? */
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) &Descriptor->M32.RangeLength) + 1);
    return;
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
RsDoMemory32FixedDescriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      i;


    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->F32.DescriptorType  = RESOURCE_DESC_FIXED_MEMORY_32;
    Descriptor->F32.Length = 9;


    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Read/Write type */

            RsSetFlagBits (&Descriptor->F32.Information, InitializerNode, 0, 1);
            break;

        case 1:  /* Address */

            Descriptor->F32.BaseAddress = InitializerNode->Value.Integer32;
            break;

        case 2: /* Length */

            Descriptor->F32.RangeLength = InitializerNode->Value.Integer32;
            break;

        case 3: /* Name */

            /* TBD: What do we do with this? */
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) &Descriptor->F32.RangeLength) + 1);
    return;
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
RsDoQwordIoDescriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      DescriptorSize = DEFAULT_RESOURCE_DESC_SIZE;
    UINT32                      StringLength = 0;
    UINT32                      OptionIndex = 0;
    UINT32                      i;


    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->Qas.DescriptorType  = RESOURCE_DESC_QWORD_ADDRESS_SPACE;
    Descriptor->Qas.ResourceType    = RESOURCE_TYPE_IO_RANGE;


    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* MinType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 2, 0);
            break;

        case 2: /* MaxType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 3, 0);
            break;

        case 3: /* DecodeType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 1, 0);
            break;

        case 4: /* Range Type */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 0, 3);
            break;

        case 5: /* Address Granularity */

            Descriptor->Qas.Granularity = InitializerNode->Value.Integer64;
            break;

        case 6: /* Address Min */

            Descriptor->Qas.AddressMin = InitializerNode->Value.Integer64;
            break;

        case 7: /* Address Max */

            Descriptor->Qas.AddressMax = InitializerNode->Value.Integer64;
            break;

        case 8: /* Translation Offset */

            Descriptor->Qas.TranslationOffset = InitializerNode->Value.Integer64;
            break;

        case 9: /* Address Length */

            Descriptor->Qas.AddressLength = InitializerNode->Value.Integer64;
            break;

        case 10: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Qas.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
            }
            break;

        case 11: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                StringLength = strlen (InitializerNode->Value.Pointer);
                if (StringLength)
                {
                    DescriptorSize += StringLength;                     /* Null terminator already accounted for */
                    Descriptor = UtLocalRealloc (Descriptor, DescriptorSize);

                    strcpy (&Descriptor->Qas.OptionalFields[OptionIndex], 
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 12: /* ResourceTag */

            /* TBD:  What to do with this? Just mark unused for now */
            break;

        case 13: /* Type */
            
            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 4, 0);
            break;

        case 14: /* Translation Type */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 5, 0);
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) Descriptor->Qas.OptionalFields) + 
                                            (OptionIndex + StringLength));
    return;
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
RsDoQwordMemoryDescriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      DescriptorSize = DEFAULT_RESOURCE_DESC_SIZE;
    UINT32                      StringLength = 0;
    UINT32                      OptionIndex = 0;
    UINT32                      i;


    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->Qas.DescriptorType  = RESOURCE_DESC_QWORD_ADDRESS_SPACE;
    Descriptor->Qas.ResourceType    = RESOURCE_TYPE_MEMORY_RANGE;


    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* DecodeType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 1, 0);
            break;

        case 2: /* MinType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 2, 0);
            break;

        case 3: /* MaxType */

            RsSetFlagBits (&Descriptor->Qas.Flags, InitializerNode, 3, 0);
            break;

        case 4: /* Memory Type */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 1, 0);
            break;

        case 5: /* Read/Write Type */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 0, 1);
            break;

        case 6: /* Address Granularity */

            Descriptor->Qas.Granularity = InitializerNode->Value.Integer64;
            break;

        case 7: /* Min Address */

            Descriptor->Qas.AddressMin = InitializerNode->Value.Integer64;
            break;

        case 8: /* Max Address */

            Descriptor->Qas.AddressMax = InitializerNode->Value.Integer64;
            break;

        case 9: /* Translation Offset */    

            Descriptor->Qas.TranslationOffset = InitializerNode->Value.Integer64;
            break;

        case 10: /* Address Length */

            Descriptor->Qas.AddressLength = InitializerNode->Value.Integer64;
            break;

        case 11: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Qas.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
            }
            break;

        case 12: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                StringLength = strlen (InitializerNode->Value.Pointer);
                if (StringLength)
                {
                    DescriptorSize += StringLength;                     /* Null terminator already accounted for */
                    Descriptor = UtLocalRealloc (Descriptor, DescriptorSize);

                    strcpy (&Descriptor->Qas.OptionalFields[OptionIndex], 
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 13: /* ResourceTag */
            break;


        case 14: /* Address Range */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 3, 0);
            break;

        case 15: /* Type Translation */

            RsSetFlagBits (&Descriptor->Qas.SpecificFlags, InitializerNode, 5, 0);
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) Descriptor->Qas.OptionalFields) + 
                                            (OptionIndex + StringLength));
    return;
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
RsDoWordIoDescriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      DescriptorSize = DEFAULT_RESOURCE_DESC_SIZE;
    UINT32                      StringLength = 0;
    UINT32                      OptionIndex = 0;
    UINT32                      i;


    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->Was.DescriptorType  = RESOURCE_DESC_WORD_ADDRESS_SPACE;
    Descriptor->Was.ResourceType    = RESOURCE_TYPE_IO_RANGE;


    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* MinType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 2, 0);
            break;

        case 2: /* MaxType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 3, 0);
            break;

        case 3: /* DecodeType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 1, 0);
            break;

        case 4: /* Range Type */

            RsSetFlagBits (&Descriptor->Was.SpecificFlags, InitializerNode, 0, 3);
            break;

        case 5: /* Address Granularity */

            Descriptor->Was.Granularity = InitializerNode->Value.Integer16;
            break;

        case 6: /* Address Min */

            Descriptor->Was.AddressMin = InitializerNode->Value.Integer16;
            break;

        case 7: /* Address Max */

            Descriptor->Was.AddressMax = InitializerNode->Value.Integer16;
            break;

        case 8: /* Translation Offset */

            Descriptor->Was.TranslationOffset = InitializerNode->Value.Integer16;
            break;

        case 9: /* Address Length */

            Descriptor->Was.AddressLength = InitializerNode->Value.Integer16;
            break;

        case 10: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Was.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
            }
            break;

        case 11: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                StringLength = strlen (InitializerNode->Value.Pointer);
                if (StringLength)
                {
                    DescriptorSize += StringLength;                     /* Null terminator already accounted for */
                    Descriptor = UtLocalRealloc (Descriptor, DescriptorSize);

                    strcpy (&Descriptor->Was.OptionalFields[OptionIndex], 
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 12: /* ResourceTag */

            /* TBD:  What to do with this? Just mark unused for now */
            break;

        case 13: /* Type */
            
            RsSetFlagBits (&Descriptor->Was.SpecificFlags, InitializerNode, 4, 0);
            break;

        case 14: /* Translation Type */

            RsSetFlagBits (&Descriptor->Was.SpecificFlags, InitializerNode, 5, 0);
            break;
        }

        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }

    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) Descriptor->Was.OptionalFields) + 
                                            (OptionIndex + StringLength));
    return;
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
CgDoWordBusNumberDescriptor (
    ASL_PARSE_NODE              *Node,
    ASL_RESOURCE_DESC           **DescriptorPtr)
{
    ASL_RESOURCE_DESC           *Descriptor = *DescriptorPtr;
    ASL_PARSE_NODE              *InitializerNode;
    UINT32                      DescriptorSize = DEFAULT_RESOURCE_DESC_SIZE;
    UINT32                      StringLength = 0;
    UINT32                      OptionIndex = 0;
    UINT32                      i;


    Node->ParseOpcode = DEFAULT_ARG;

    Descriptor->Was.DescriptorType  = RESOURCE_DESC_WORD_ADDRESS_SPACE;
    Descriptor->Was.ResourceType    = RESOURCE_TYPE_BUS_NUMBER_RANGE;

    /* TBD: don't hardcode this */

    Descriptor->Was.Length          = 13;


    /* TBD: add support for defaults if node= DEFAULT_ARG */

    InitializerNode = Node->Child;
    for (i = 0; InitializerNode; i++)
    {
        switch (i)
        {
        case 0: /* Resource Type */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 0, 1);
            break;

        case 1: /* MinType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 2, 0);
            break;

        case 2: /* MaxType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 3, 0);
            break;

        case 3: /* DecodeType */

            RsSetFlagBits (&Descriptor->Was.Flags, InitializerNode, 1, 0);
            break;

        case 4: /* Address Granularity */

            Descriptor->Was.Granularity = InitializerNode->Value.Integer16;
            break;

        case 5: /* Min Address */

            Descriptor->Was.AddressMin = InitializerNode->Value.Integer16;
            break;

        case 6: /* Max Address */

            Descriptor->Was.AddressMax = InitializerNode->Value.Integer16;
            break;

        case 7: /* Translation Offset */    

            Descriptor->Was.TranslationOffset = InitializerNode->Value.Integer16;
            break;

        case 8: /* Address Length */

            Descriptor->Was.AddressLength = InitializerNode->Value.Integer16;
            break;

        case 9: /* ResSourceIndex [Optional Field - BYTE] */

            if (InitializerNode->ParseOpcode != DEFAULT_ARG)
            {
                Descriptor->Was.OptionalFields[0] = InitializerNode->Value.Integer8;
                OptionIndex++;
            }
            break;

        case 10: /* ResSource [Optional Field - STRING] */

            if ((InitializerNode->ParseOpcode != DEFAULT_ARG) &&
                (InitializerNode->Value.Pointer))
            {
                StringLength = strlen (InitializerNode->Value.Pointer);
                if (StringLength)
                {
                    DescriptorSize += StringLength;                     /* Null terminator already accounted for */
                    Descriptor = UtLocalRealloc (Descriptor, DescriptorSize);

                    strcpy (&Descriptor->Was.OptionalFields[OptionIndex], 
                            InitializerNode->Value.Pointer);
                }
            }
            break;

        case 11: /* ResourceTag */

            /* TBD:  What to do with this? Just mark unused for now */
            break;
        }


        InitializerNode = RsCompleteNodeAndGetNext (InitializerNode);
    }


    *DescriptorPtr = (ASL_RESOURCE_DESC *) (((char *) Descriptor->Was.OptionalFields) + 
                                            (OptionIndex + StringLength));
    return;
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
CgDoResourceTemplate (
    ASL_PARSE_NODE              *Node)
{
    ASL_PARSE_NODE              *BufferLengthNode;
    ASL_PARSE_NODE              *BufferNode;
    ASL_PARSE_NODE              *DescriptorTypeNode;
    ASL_RESOURCE_DESC           *StartOfDescriptor;
    ASL_RESOURCE_DESC           *Descriptor;
    UINT32                      ValidDataLength;


    /* Allocate a worst-case descriptor */

    Descriptor = UtLocalCalloc (DEFAULT_RESOURCE_DESC_SIZE);
    StartOfDescriptor = Descriptor;

    /* ResourceTemplate Opcode is first (Node) */
    /* Buffer Length node is first child */

    BufferLengthNode = ASL_GET_CHILD_NODE (Node);

    /* Buffer Node is first peer */

    BufferNode = ASL_GET_PEER_NODE (BufferLengthNode);

    /* First Descriptor type is next */

    DescriptorTypeNode = ASL_GET_PEER_NODE (BufferNode);


    /* Process all resource descriptors in the list */

    while (DescriptorTypeNode)
    {
        /* Determine type of resource */

        switch (DescriptorTypeNode->ParseOpcode)
        {
        case DMA:
            RsDoDmaDescriptor (DescriptorTypeNode, &Descriptor);
            break;

        case DWORDIO:
            RsDoDwordIoDescriptor (DescriptorTypeNode, &Descriptor);
            break;

        case DWORDMEMORY:
            RsDoDwordMemoryDescriptor (DescriptorTypeNode, &Descriptor);
            break;

        case ENDDEPENDENTFN:
        case FIXEDIO:
        case INTERRUPT:
            break;

        case IO:
            CgDoIoDescriptor (DescriptorTypeNode, &Descriptor);
            break;

        case IRQNOFLAGS:
        case IRQ:
            break;

        case MEMORY24:
            RsDoMemory24Descriptor (DescriptorTypeNode, &Descriptor);
            break;

        case MEMORY32FIXED:
            RsDoMemory32FixedDescriptor (DescriptorTypeNode, &Descriptor);
            break;

        case MEMORY32:
            RsDoMemory32Descriptor (DescriptorTypeNode, &Descriptor);
            break;

        case QWORDIO:
            RsDoQwordIoDescriptor (DescriptorTypeNode, &Descriptor);
            break;

        case QWORDMEMORY:
            RsDoQwordMemoryDescriptor (DescriptorTypeNode, &Descriptor);
            break;


        case REGISTER:
        case STARTDEPENDENTFN:
        case STARTDEPENDENTFN_NOPRI:
        case VENDORLONG:
        case VENDORSHORT:
            break;

        case WORDBUSNUMBER:
            CgDoWordBusNumberDescriptor (DescriptorTypeNode, &Descriptor);
            break;

        case WORDIO:
            RsDoWordIoDescriptor (DescriptorTypeNode, &Descriptor);
            break;

        default:
            printf ("Unknown resource descriptor type [%s]\n", 
                        DescriptorTypeNode->ParseOpName);
            break;
        }

        /* Get the next descriptor in the list */

        DescriptorTypeNode = ASL_GET_PEER_NODE (DescriptorTypeNode);
        if (DescriptorTypeNode)
        {
            ValidDataLength = (((char *) Descriptor) - ((char *) StartOfDescriptor));

            StartOfDescriptor = UtLocalRealloc (StartOfDescriptor, 
                                    ValidDataLength + DEFAULT_RESOURCE_DESC_SIZE);

            Descriptor = (ASL_RESOURCE_DESC *) (((char *) StartOfDescriptor) + ValidDataLength);
        }
    }

    /* Insert the EndTag descriptor after all other descriptors have been processed */

    Descriptor->Et.DescriptorType = RESOURCE_DESC_END_TAG;
    Descriptor->Et.Checksum = 0;

    /* Length of the entire buffer is the end of the EndTag minus the start pointer */

    ValidDataLength = ((char *) &Descriptor->Et.Checksum - (char *) StartOfDescriptor + 1);

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
    BufferLengthNode->Value.Integer = ValidDataLength;
    CgSetOptimalIntegerSize (BufferLengthNode);

    BufferNode->ParseOpcode         = RAW_DATA;
    BufferNode->AmlOpcode           = AML_RAW_DATA_BUFFER;
    BufferNode->AmlOpcodeLength     = 0;
    BufferNode->AmlLength           = ValidDataLength;
    BufferNode->Value.Pointer       = StartOfDescriptor;

    return;
}


