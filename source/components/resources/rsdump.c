
/******************************************************************************
 *
 * Module Name: rsdump - Functions do dump out the resource structures.
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


#define __RSDUMP_C__

#include "acpi.h"

#define _COMPONENT          RESOURCE_MANAGER
        MODULE_NAME         ("rsdump");


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpIrq
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpIrq (
    RESOURCE_DATA           *Data)
{
    IRQ_RESOURCE            *IrqData = (IRQ_RESOURCE*) Data;
    UINT8                   Index = 0;


    AcpiOsdPrintf ("\tIRQ Resource\n");

    AcpiOsdPrintf ("\t\t%s Triggered\n", LEVEL_SENSITIVE == IrqData->EdgeLevel ? "Level" : "Edge");
    AcpiOsdPrintf ("\t\tActive %s\n", ACTIVE_LOW == IrqData->ActiveHighLow ? "Low" : "High");
    AcpiOsdPrintf ("\t\t%s\n", SHARED == IrqData->SharedExclusive ? "Shared" : "Exclusive");
    AcpiOsdPrintf ("\t\t%d Interrupts ( ", IrqData->NumberOfInterrupts);

    for (Index = 0; Index < IrqData->NumberOfInterrupts; Index++)
    {
        AcpiOsdPrintf ("%d ", IrqData->Interrupts[Index]);
    }

    AcpiOsdPrintf (")\n");
    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpDma
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpDma (
    RESOURCE_DATA           *Data)
{
    DMA_RESOURCE            *DmaData = (DMA_RESOURCE*) Data;
    UINT8                   Index = 0;


    AcpiOsdPrintf ("\tDMA Resource\n");

    switch (DmaData->Type)
    {
    case COMPATIBILITY:
        AcpiOsdPrintf ("\t\tCompatibility mode\n");
        break;

    case TYPE_A:
        AcpiOsdPrintf ("\t\tType A\n");
        break;

    case TYPE_B:
        AcpiOsdPrintf ("\t\tType B\n");
        break;

    case TYPE_F:
        AcpiOsdPrintf ("\t\tType F\n");
        break;

    default:
        AcpiOsdPrintf ("\t\tInvalid DMA type\n");
        break;
    }

    AcpiOsdPrintf ("\t\t%sBus Master\n", BUS_MASTER == DmaData->BusMaster ? "" : "Not a ");

    switch (DmaData->Transfer)
    {
    case TRANSFER_8:
        AcpiOsdPrintf ("\t\t8-bit only transfer\n");
        break;

    case TRANSFER_8_16:
        AcpiOsdPrintf ("\t\t8 and 16-bit transfer\n");
        break;

    case TRANSFER_16:
        AcpiOsdPrintf ("\t\t16 bit only transfer\n");
        break;

    default:
        AcpiOsdPrintf ("\t\tInvalid transfer preference\n");
        break;
    }

    AcpiOsdPrintf ("\t\tNumber of Channels: %d ( ", DmaData->NumberOfChannels);

    for (Index = 0; Index < DmaData->NumberOfChannels; Index++)
    {
        AcpiOsdPrintf ("%d ", DmaData->Channels[Index]);
    }

    AcpiOsdPrintf (")\n");
    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpStartDependentFunctions
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpStartDependentFunctions (
    RESOURCE_DATA               *Data)
{
    START_DEPENDENT_FUNCTIONS_RESOURCE *SdfData = (START_DEPENDENT_FUNCTIONS_RESOURCE*) Data;


    AcpiOsdPrintf ("\tStart Dependent Functions Resource\n");

    switch (SdfData->CompatibilityPriority)
    {
    case GOOD_CONFIGURATION:
        AcpiOsdPrintf ("\t\tGood configuration\n");
        break;

    case ACCEPTABLE_CONFIGURATION:
        AcpiOsdPrintf ("\t\tAcceptable configuration\n");
        break;

    case SUB_OPTIMAL_CONFIGURATION:
        AcpiOsdPrintf ("\t\tSub-optimal configuration\n");
        break;

    default:
        AcpiOsdPrintf ("\t\tInvalid compatibility priority\n");
        break;
    }

    switch(SdfData->PerformanceRobustness)
    {
    case GOOD_CONFIGURATION:
        AcpiOsdPrintf ("\t\tGood configuration\n");
        break;

    case ACCEPTABLE_CONFIGURATION:
        AcpiOsdPrintf ("\t\tAcceptable configuration\n");
        break;

    case SUB_OPTIMAL_CONFIGURATION:
        AcpiOsdPrintf ("\t\tSub-optimal configuration\n");
        break;

    default:
        AcpiOsdPrintf ("\t\tInvalid performance robustness preference\n");
        break;
    }

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpIo
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpIo (
    RESOURCE_DATA       *Data)
{
    IO_RESOURCE         *IoData = (IO_RESOURCE*) Data;


    AcpiOsdPrintf ("\tIo Resource\n");
    AcpiOsdPrintf ("\t\t%d bit decode\n", DECODE_16 == IoData->IoDecode ? 16 : 10);
    AcpiOsdPrintf ("\t\tRange minimum base: 0x%08x\n", IoData->MinBaseAddress);
    AcpiOsdPrintf ("\t\tRange maximum base: 0x%08x\n", IoData->MaxBaseAddress);
    AcpiOsdPrintf ("\t\tAlignment: 0x%08x\n", IoData->Alignment);
    AcpiOsdPrintf ("\t\tRange Length: 0x%08x\n", IoData->RangeLength);

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpFixedIo
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpFixedIo (
    RESOURCE_DATA           *Data)
{
    FIXED_IO_RESOURCE       *FixedIoData = (FIXED_IO_RESOURCE*) Data;


    AcpiOsdPrintf ("\tFixed Io Resource\n");
    AcpiOsdPrintf ("\t\tRange base address: 0x%08x", FixedIoData->BaseAddress);
    AcpiOsdPrintf ("\t\tRange length: 0x%08x", FixedIoData->RangeLength);

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpVendorSpecific
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpVendorSpecific (
    RESOURCE_DATA           *Data)
{
    VENDOR_RESOURCE         *VendorData = (VENDOR_RESOURCE*) Data;
    UINT16                  Index = 0;


    AcpiOsdPrintf ("\tVendor Specific Resource\n");
    AcpiOsdPrintf ("\t\tLength: 0x%08x\n", VendorData->Length);

    for (Index = 0; Index < VendorData->Length; Index++)
    {
        AcpiOsdPrintf ("\t\tByte %d: 0x%08x\n", Index, VendorData->Reserved[Index]);
    }

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpMemory24
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpMemory24 (
    RESOURCE_DATA           *Data)
{
    MEMORY24_RESOURCE       *Memory24Data = (MEMORY24_RESOURCE*) Data;


    AcpiOsdPrintf ("\t24-Bit Memory Range Resource\n");

    AcpiOsdPrintf ("\t\tRead%s\n", READ_WRITE_MEMORY == Memory24Data->ReadWriteAttribute ? "/Write" : " only");
    AcpiOsdPrintf ("\t\tRange minimum base: 0x%08x\n", Memory24Data->MinBaseAddress);
    AcpiOsdPrintf ("\t\tRange maximum base: 0x%08x\n", Memory24Data->MaxBaseAddress);
    AcpiOsdPrintf ("\t\tAlignment: 0x%08x\n", Memory24Data->Alignment);
    AcpiOsdPrintf ("\t\tRange length: 0x%08x\n", Memory24Data->RangeLength);

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpMemory32
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpMemory32 (
    RESOURCE_DATA           *Data)
{
    MEMORY32_RESOURCE       *Memory32Data = (MEMORY32_RESOURCE*) Data;


    AcpiOsdPrintf ("\t32-Bit Memory Range Resource\n");

    AcpiOsdPrintf ("\t\tRead%s\n", READ_WRITE_MEMORY == Memory32Data->ReadWriteAttribute ? "/Write" : " only");
    AcpiOsdPrintf ("\t\tRange minimum base: 0x%08x\n", Memory32Data->MinBaseAddress);
    AcpiOsdPrintf ("\t\tRange maximum base: 0x%08x\n", Memory32Data->MaxBaseAddress);
    AcpiOsdPrintf ("\t\tAlignment: 0x%08x\n", Memory32Data->Alignment);
    AcpiOsdPrintf ("\t\tRange length: 0x%08x\n", Memory32Data->RangeLength);

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpFixedMemory32
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpFixedMemory32 (
    RESOURCE_DATA           *Data)
{
    FIXED_MEMORY32_RESOURCE *FixedMemory32Data = (FIXED_MEMORY32_RESOURCE*) Data;


    AcpiOsdPrintf ("\t32-Bit Fixed Location Memory Range Resource\n");
    AcpiOsdPrintf ("\t\tRead%s\n", READ_WRITE_MEMORY == FixedMemory32Data->ReadWriteAttribute ? "/Write" : " Only");
    AcpiOsdPrintf ("\t\tRange base address: 0x%08x\n", FixedMemory32Data->RangeBaseAddress);
    AcpiOsdPrintf ("\t\tRange length: 0x%08x\n", FixedMemory32Data->RangeLength);

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpAddress16
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpAddress16 (
    RESOURCE_DATA           *Data)
{
    ADDRESS16_RESOURCE      *Address16Data = (ADDRESS16_RESOURCE*) Data;


    AcpiOsdPrintf ("\t16-Bit Address Space Resource\n");
    AcpiOsdPrintf ("\t\tResource Type: ");

    switch (Address16Data->ResourceType)
    {
    case MEMORY_RANGE:

        AcpiOsdPrintf ("Memory Range\n");

        switch (Address16Data->Attribute.Memory.CacheAttribute)
        {
        case NON_CACHEABLE_MEMORY:
            AcpiOsdPrintf ("\t\tType Specific: Noncacheable memory\n");
            break;

        case CACHABLE_MEMORY:
            AcpiOsdPrintf ("\t\tType Specific: Cacheable memory\n");
            break;

        case WRITE_COMBINING_MEMORY:
            AcpiOsdPrintf ("\t\tType Specific: Write-combining memory\n");
            break;

        case PREFETCHABLE_MEMORY:
            AcpiOsdPrintf ("\t\tType Specific: Prefetchable memory\n");
            break;

        default:
            AcpiOsdPrintf ("\t\tType Specific: Invalid cache attribute\n");
            break;
        }

        AcpiOsdPrintf ("\t\tType Specific: Read%s\n",
            READ_WRITE_MEMORY == Address16Data->Attribute.Memory.ReadWriteAttribute ?
            "/Write" : " Only");
        break;

    case IO_RANGE:

        AcpiOsdPrintf ("I/O Range\n");

        switch (Address16Data->Attribute.Io.RangeAttribute)
        {
        case NON_ISA_ONLY_RANGES:
            AcpiOsdPrintf ("\t\tType Specific: Non-ISA Io Addresses\n");
            break;

        case ISA_ONLY_RANGES:
            AcpiOsdPrintf ("\t\tType Specific: ISA Io Addresses\n");
            break;

        case ENTIRE_RANGE:
            AcpiOsdPrintf ("\t\tType Specific: ISA and non-ISA Io Addresses\n");
            break;

        default:
            AcpiOsdPrintf ("\t\tType Specific: Invalid range attribute\n");
            break;
        }
        break;

    case BUS_NUMBER_RANGE:

        AcpiOsdPrintf ("Bus Number Range\n");
        break;

    default:

        AcpiOsdPrintf ("Invalid resource type. Exiting.\n");
        return;
    }

    AcpiOsdPrintf ("\t\tResource %s\n", CONSUMER == Address16Data->ProducerConsumer ? "Consumer" : "Producer");
    AcpiOsdPrintf ("\t\t%s decode\n", SUB_DECODE == Address16Data->Decode ? "Subtractive" : "Positive");
    AcpiOsdPrintf ("\t\tMin address is %s fixed\n", ADDRESS_FIXED == Address16Data->MinAddressFixed ? "" : "not");
    AcpiOsdPrintf ("\t\tMax address is %s fixed\n", ADDRESS_FIXED == Address16Data->MaxAddressFixed ? "" : "not");
    AcpiOsdPrintf ("\t\tGranularity: 0x%08x\n", Address16Data->Granularity);
    AcpiOsdPrintf ("\t\tAddress range min: 0x%08x\n", Address16Data->MinAddressRange);
    AcpiOsdPrintf ("\t\tAddress range max: 0x%08x\n", Address16Data->MaxAddressRange);
    AcpiOsdPrintf ("\t\tAddress translation offset: 0x%08x\n", Address16Data->AddressTranslationOffset);
    AcpiOsdPrintf ("\t\tAddress Length: 0x%08x\n", Address16Data->AddressLength);

    if (0xFF != Address16Data->ResourceSourceIndex)
    {
        AcpiOsdPrintf ("\t\tResource Source Index: %d\n", Address16Data->ResourceSourceIndex);
        AcpiOsdPrintf ("\t\tResource Source: %s\n", Address16Data->ResourceSource);
    }

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpAddress32
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpAddress32 (
    RESOURCE_DATA           *Data)
{
    ADDRESS32_RESOURCE      *Address32Data = (ADDRESS32_RESOURCE*) Data;


    AcpiOsdPrintf ("\t32-Bit Address Space Resource\n");

    switch (Address32Data->ResourceType)
    {
    case MEMORY_RANGE:

        AcpiOsdPrintf ("\t\tResource Type: Memory Range\n");

        switch (Address32Data->Attribute.Memory.CacheAttribute)
        {
        case NON_CACHEABLE_MEMORY:
            AcpiOsdPrintf ("\t\tType Specific: Noncacheable memory\n");
            break;

        case CACHABLE_MEMORY:
            AcpiOsdPrintf ("\t\tType Specific: Cacheable memory\n");
            break;

        case WRITE_COMBINING_MEMORY:
            AcpiOsdPrintf ("\t\tType Specific: Write-combining memory\n");
            break;

        case PREFETCHABLE_MEMORY:
            AcpiOsdPrintf ("\t\tType Specific: Prefetchable memory\n");
            break;

        default:
            AcpiOsdPrintf ("\t\tType Specific: Invalid cache attribute\n");
            break;
        }

        AcpiOsdPrintf ("\t\tType Specific: Read%s\n",
            READ_WRITE_MEMORY == Address32Data->Attribute.Memory.ReadWriteAttribute ?
            "/Write" : " Only");
        break;

    case IO_RANGE:

        AcpiOsdPrintf ("\t\tResource Type: Io Range\n");

        switch (Address32Data->Attribute.Io.RangeAttribute)
            {
            case NON_ISA_ONLY_RANGES:
                AcpiOsdPrintf ("\t\tType Specific: Non-ISA Io Addresses\n");
                break;

            case ISA_ONLY_RANGES:
                AcpiOsdPrintf ("\t\tType Specific: ISA Io Addresses\n");
                break;

            case ENTIRE_RANGE:
                AcpiOsdPrintf ("\t\tType Specific: ISA and non-ISA Io Addresses\n");
                break;

            default:
                AcpiOsdPrintf ("\t\tType Specific: Invalid Range attribute");
                break;
            }
        break;

    case BUS_NUMBER_RANGE:

        AcpiOsdPrintf ("\t\tResource Type: Bus Number Range\n");
        break;

    default:

        AcpiOsdPrintf ("\t\tInvalid Resource Type..exiting.\n");
        return;
    }

    AcpiOsdPrintf ("\t\tResource %s\n", CONSUMER == Address32Data->ProducerConsumer ? "Consumer" : "Producer");
    AcpiOsdPrintf ("\t\t%s decode\n", SUB_DECODE == Address32Data->Decode ? "Subtractive" : "Positive");
    AcpiOsdPrintf ("\t\tMin address is %s fixed\n", ADDRESS_FIXED == Address32Data->MinAddressFixed ? "" : "not ");
    AcpiOsdPrintf ("\t\tMax address is %s fixed\n", ADDRESS_FIXED == Address32Data->MaxAddressFixed ? "" : "not ");
    AcpiOsdPrintf ("\t\tGranularity: 0x%08x\n", Address32Data->Granularity);
    AcpiOsdPrintf ("\t\tAddress range min: 0x%08x\n", Address32Data->MinAddressRange);
    AcpiOsdPrintf ("\t\tAddress range max: 0x%08x\n", Address32Data->MaxAddressRange);
    AcpiOsdPrintf ("\t\tAddress translation offset: 0x%08x\n", Address32Data->AddressTranslationOffset);
    AcpiOsdPrintf ("\t\tAddress Length: 0x%08x\n", Address32Data->AddressLength);

    if(0xFF != Address32Data->ResourceSourceIndex)
    {
        AcpiOsdPrintf ("\t\tResource Source Index: %d\n", Address32Data->ResourceSourceIndex);
        AcpiOsdPrintf ("\t\tResource Source: %s\n", Address32Data->ResourceSource);
    }

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpExtendedIrq
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Prints out the various members of the Data structure type.
 *
 ******************************************************************************/

void
AcpiRsDumpExtendedIrq (
    RESOURCE_DATA           *Data)
{
    EXTENDED_IRQ_RESOURCE   *ExtIrqData = (EXTENDED_IRQ_RESOURCE*) Data;
    UINT8                   Index = 0;


    AcpiOsdPrintf ("\tExtended IRQ Resource\n");

    AcpiOsdPrintf ("\t\tResource %s\n", CONSUMER == ExtIrqData->ProducerConsumer ? "Consumer" : "Producer");
    AcpiOsdPrintf ("\t\t%s\n", LEVEL_SENSITIVE == ExtIrqData->EdgeLevel ? "Level" : "Edge");
    AcpiOsdPrintf ("\t\tActive %s\n", ACTIVE_LOW == ExtIrqData->ActiveHighLow ? "low" : "high");
    AcpiOsdPrintf ("\t\t%s\n", SHARED == ExtIrqData->SharedExclusive ? "Shared" : "Exclusive");

    AcpiOsdPrintf ("\t\tInterrupts : %d ( ", ExtIrqData->NumberOfInterrupts);

    for (Index = 0; Index < ExtIrqData->NumberOfInterrupts; Index++)
    {
        AcpiOsdPrintf ("%d ", ExtIrqData->Interrupts[Index]);
    }

    AcpiOsdPrintf (")\n");

    if(0xFF != ExtIrqData->ResourceSourceIndex)
    {
        AcpiOsdPrintf ("\t\tResource Source Index: %d", ExtIrqData->ResourceSourceIndex);
        AcpiOsdPrintf ("\t\tResource Source: %s", ExtIrqData->ResourceSource);
    }

    return;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpResourceList
 *
 * PARAMETERS:  Data            - pointer to the resource structure to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Dispatches the structure to the correct dump routine.
 *
 ******************************************************************************/

void
AcpiRsDumpResourceList (
    RESOURCE            *Resource)
{
    INT8                Count = 0;
    BOOLEAN             Done = FALSE;


    if (DebugLevel & TRACE_RESOURCES && _COMPONENT & DebugLayer)
    {
        while (!Done)
        {
            AcpiOsdPrintf ("\tResource structure %x.\n", Count++);

            switch (Resource->Id)
            {
            case Irq:
                AcpiRsDumpIrq (&Resource->Data);
                break;

            case Dma:
                AcpiRsDumpDma (&Resource->Data);
                break;

            case StartDependentFunctions:
                AcpiRsDumpStartDependentFunctions (&Resource->Data);
                break;

            case EndDependentFunctions:
                AcpiOsdPrintf ("\tEndDependentFunctions Resource\n");
                /* AcpiRsDumpEndDependentFunctions (Resource->Data);*/
                break;

            case Io:
                AcpiRsDumpIo (&Resource->Data);
                break;

            case FixedIo:
                AcpiRsDumpFixedIo (&Resource->Data);
                break;

            case VendorSpecific:
                AcpiRsDumpVendorSpecific (&Resource->Data);
                break;

            case EndTag:
                /*RsDumpEndTag (Resource->Data);*/
                AcpiOsdPrintf ("\tEndTag Resource\n");
                Done = TRUE;
                break;

            case Memory24:
                AcpiRsDumpMemory24 (&Resource->Data);
                break;

            case Memory32:
                AcpiRsDumpMemory32 (&Resource->Data);
                break;

            case FixedMemory32:
                AcpiRsDumpFixedMemory32 (&Resource->Data);
                break;

            case Address16:
                AcpiRsDumpAddress16 (&Resource->Data);
                break;

            case Address32:
                AcpiRsDumpAddress32 (&Resource->Data);
                break;

            case ExtendedIrq:
                AcpiRsDumpExtendedIrq (&Resource->Data);
                break;

            default:
                AcpiOsdPrintf ("Invalid resource type\n");
                break;

            }
 
            Resource = (RESOURCE *) ((NATIVE_UINT) Resource + (NATIVE_UINT) Resource->Length);
        }
    }

    return;
}

/******************************************************************************
 *
 * FUNCTION:    AcpiRsDumpIrqList
 *
 * PARAMETERS:  Data            - pointer to the routing table to dump.
 *
 * RETURN:    
 *
 * DESCRIPTION: Dispatches the structures to the correct dump routine.
 *
 ******************************************************************************/

void
AcpiRsDumpIrqList (
    UINT8   *RouteTable)
{
    UINT8               *Buffer = RouteTable;
    INT8                Count = 0;
    BOOLEAN             Done = FALSE;
    PCI_ROUTING_TABLE   *PrtElement;


    if (DebugLevel & TRACE_RESOURCES && _COMPONENT & DebugLayer)
    {
        PrtElement = (PCI_ROUTING_TABLE *)Buffer;

        while (!Done)
        {
            AcpiOsdPrintf ("\tPCI IRQ Routing Table structure %x.\n", Count++);

            AcpiOsdPrintf ("\t\tAddress: 0x%x\n", PrtElement->Data.Address);
            AcpiOsdPrintf ("\t\tPin: 0x%x\n", PrtElement->Data.Pin);
            AcpiOsdPrintf ("\t\tSource: %s\n", PrtElement->Data.Source);
            AcpiOsdPrintf ("\t\tSourceIndex: 0x%x\n", PrtElement->Data.SourceIndex);

            Buffer += PrtElement->Length;

            PrtElement = (PCI_ROUTING_TABLE *)Buffer;

            if(0 == PrtElement->Length)
            {
                Done = TRUE;
            }
        }
    }

    return;
}

