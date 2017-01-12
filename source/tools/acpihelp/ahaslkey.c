/******************************************************************************
 *
 * Module Name: ahaslkey - Table of all known ASL non-operator keywords and
 *                         table of iASL Preprocessor directives
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2017, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights. You may have additional license terms from the party that provided
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
 * to or modifications of the Original Intel Code. No other license or right
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
 * and the following Disclaimer and Export Compliance provision. In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change. Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee. Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution. In
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
 * HERE. ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT, ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES. INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS. INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES. THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government. In the
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

#include "acpihelp.h"

/*
 * ASL Keyword types and associated actual keywords.
 * This table was extracted from the ACPI specification.
 */
const AH_ASL_KEYWORD        Gbl_AslKeywordInfo[] =
{
    {"AccessAttribKeyword", "Serial Bus Attributes (with legacy SMBus aliases)",
        ":= AttribQuick (SMBusQuick) | AttribSendReceive (SMBusSendReceive) | "
        "AttribByte (SMBusByte) | AttribWord (SMBusWord) | "
        "AttribBlock (SMBusBlock) | AttribProcessCall (SMBusProcessCall) | "
        "AttribBlockProcessCall (SMBusProcessCall)"},
    {"AccessTypeKeyword", "Field Access Types",
        ":= AnyAcc | ByteAcc | WordAcc | DWordAcc | QWordAcc | BufferAcc"},
    {"AddressingModeKeyword", "Mode - Resource Descriptors",
        ":= AddressingMode7Bit | AddressingMode10Bit"},
    {"AddressKeyword", "ACPI memory range types",
        ":= AddressRangeMemory | AddressRangeReserved | "
        "AddressRangeNVS | AddressRangeACPI"},
    {"AddressSpaceKeyword", "Operation Region Address Space Types",
        ":= RegionSpaceKeyword | FFixedHW"},
    {"BusMasterKeyword", "DMA Bus Mastering",
        ":= BusMaster | NotBusMaster"},
    {"ByteLengthKeyword", "Bits per Byte - Resource Descriptors",
        ":= DataBitsFive | DataBitsSix | DataBitsSeven | DataBitsEight | DataBitsNine"},
    {"ClockPhaseKeyword", "Resource Descriptors",
        ":= ClockPhaseFirst | ClockPhaseSecond"},
    {"ClockPolarityKeyword", "Resource Descriptors",
        ":= ClockPolarityLow | ClockPolarityHigh"},
    {"DecodeKeyword", "Type of Memory Decoding - Resource Descriptors",
        ":= SubDecode | PosDecode"},
    {"DmaTypeKeyword", "DMA Types - DMA Resource Descriptor",
        ":= Compatibility | TypeA | TypeB | TypeF"},
    {"EndianKeyword", "Endian type - Resource Descriptor",
        ":= BigEndian | LittleEndian"},
    {"ExtendedAttribKeyword", "Extended Bus Attributes",
        ":= AttribBytes (AccessLength) | AttribRawBytes (AccessLength) | "
        "AttribRawProcessBytes (AccessLength)"},
    {"FlowControlKeyword", "Resource Descriptor",
        ":= FlowControlNone | FlowControlXon | FlowControlHardware"},
    {"InterruptLevelKeyword", "Interrupt Active Types",
        ":= ActiveHigh | ActiveLow | ActiveBoth"},
    {"InterruptTypeKeyword", "Interrupt Types",
        ":= Edge | Level"},
    {"IoDecodeKeyword", "I/O Decoding - IO Resource Descriptor",
        ":= Decode16 | Decode10"},
    {"IoRestrictionKeyword", "I/O Restriction - GPIO Resource Descriptors",
        ":= IoRestrictionNone | IoRestrictionInputOnly | "
        "IoRestrictionOutputOnly | IoRestrictionNoneAndPreserve"},
    {"LockRuleKeyword", "Global Lock use for Field Operator",
        ":= Lock | NoLock"},
    {"MatchOpKeyword", "Types for Match Operator",
        ":= MTR | MEQ | MLE | MLT | MGE | MGT"},
    {"MaxKeyword", "Max Range Type - Resource Descriptors",
        ":= MaxFixed | MaxNotFixed"},
    {"MemTypeKeyword", "Memory Types - Resource Descriptors",
        ":= Cacheable | WriteCombining | Prefetchable | NonCacheable"},
    {"MinKeyword", "Min Range Type - Resource Descriptors",
        ":= MinFixed | MinNotFixed"},
    {"ObjectTypeKeyword", "ACPI Object Types",
        ":= UnknownObj | IntObj | StrObj | BuffObj | PkgObj | FieldUnitObj | "
        "DeviceObj | EventObj | MethodObj | MutexObj | OpRegionObj | PowerResObj | "
        "ProcessorObj | ThermalZoneObj | BuffFieldObj | DDBHandleObj"},
    {"ParityKeyword", "Resource Descriptors",
        ":= ParityTypeNone | ParityTypeSpace | ParityTypeMark | "
        "ParityTypeOdd | ParityTypeEven"},
    {"PinConfigKeyword", "Pin Configuration - GPIO Resource Descriptors",
        ":= PullDefault | PullUp | PullDown | PullNone"},
    {"PolarityKeyword", "Resource Descriptors",
        ":= PolarityHigh | PolarityLow"},
    {"RangeTypeKeyword", "I/O Range Types - Resource Descriptors",
        ":= ISAOnlyRanges | NonISAOnlyRanges | EntireRange"},
    {"ReadWriteKeyword", "Memory Access Types - Resource Descriptors",
        ":= ReadWrite | ReadOnly"},
    {"RegionSpaceKeyword", "Operation Region Address Space Types",
        ":= UserDefRegionSpace | SystemIO | SystemMemory | PCI_Config | "
        "EmbeddedControl | SMBus | SystemCMOS | PciBarTarget | IPMI | "
        "GeneralPurposeIo, GenericSerialBus"},
    {"ResourceTypeKeyword", "Resource Usage - Resource Descriptors",
        ":= ResourceConsumer | ResourceProducer"},
    {"SerializeRuleKeyword", "Control Method Serialization",
        ":= Serialized | NotSerialized"},
    {"ShareTypeKeyword", "Interrupt Sharing - Resource Descriptors",
        ":= Shared | Exclusive | SharedAndWake | ExclusiveAndWake"},
    {"SlaveModeKeyword", "Resource Descriptors",
        ":= ControllerInitiated | DeviceInitiated"},
    {"StopBitsKeyword", "Resource Descriptors",
        ":= StopBitsZero | StopBitsOne | StopBitsOnePlusHalf | StopBitsTwo"},
    {"TransferWidthKeyword", "DMA Widths - Fixed DMA Resource Descriptor",
        ":= Width8bit | Width16bit | Width32bit | Width64bit | "
        "Width128bit | Width256bit"},
    {"TranslationKeyword", "Translation Density Types - Resource Descriptors",
        ":= SparseTranslation | DenseTranslation"},
    {"TypeKeyword", "Translation Types - Resource Descriptors",
        ":= TypeTranslation | TypeStatic"},
    {"UpdateRuleKeyword", "Field Update Rules",
        ":= Preserve | WriteAsOnes | WriteAsZeros"},
    {"UserDefRegionSpace", "User defined address spaces",
        ":= IntegerData => 0x80 - 0xFF"},
    {"WireModeKeyword", "SPI Wire Mode - Resource Descriptors",
        ":= ThreeWireMode | FourWireMode"},
    {"XferTypeKeyword", "DMA Transfer Types",
        ":= Transfer8 | Transfer16 | Transfer8_16"},
    {NULL, NULL, NULL}
};

/* Preprocessor directives */

const AH_DIRECTIVE_INFO      Gbl_PreprocessorDirectives[] =
{
    {"#include \"Filename\"",               "Standard include of an ASCII ASL source code file"},
    {"#include <Filename>",                 "Alternate syntax for #include, alternate search path"},
    {"#includebuffer \"Filename\" <Name>",  "Include a binary file to create AML Buffer with ASL namepath"},
    {"#includebuffer <Filename> <Name>",    "Alternate syntax for #includebuffer, alternate search path"},

    {"",  ""},
    {"#define <Name>, <Defined name>",      "Simple macro definition (full macros not supported at this time)"},
    {"#define <Expression>, <Defined name>","Simple macro definition (full macros not supported at this time)"},
    {"#undef <Defined name>",               "Delete a previous #define"},

    {"",  ""},
    {"#if <Expression>",                    "Evaluate <Expression> and test return value"},
    {"#ifdef <Defined name>",               "Test existence of the <Defined Name>"},
    {"#ifndef <Defined name>",              "Test non-existence of the <Defined Name>"},
    {"#elif <Expression>",                  "Else-If contraction - evaluate #if <Expression>, test return value"},
    {"#else",                               "Execute alternate case for a previous #if, #ifdef or #ifndef block"},
    {"#endif",                              "Close a previous #if, #ifdef or #ifndef block"},

    {"",   ""},
    {"#line <LineNumber> [Filename]",       "Set the current ASL source code line number, optional filename"},

    {"",   ""},
    {"#error \"String\"",                   "Emit error message and abort compilation"},
    {"#warning \"String\"",                 "Emit an iASL warning at this location in the ASL source"},

    {"",  ""},
    {"#pragma disable (Error number)",      "Disable an iASL error or warning number"},
    {"#pragma message \"String\"",          "Emit an informational message to the output file(s)"},

    {"",  ""},
    {"__FILE__",                            "Return the simple filename of the current ASL file"},
    {"__PATH__",                            "Return the full pathname of the current ASL file"},
    {"__LINE__",                            "Return the current line number within the current ASL file"},
    {"__DATE__",                            "Return the current date"},
    {"__IASL__",                            "Permanently defined for the iASL compiler"},
    {NULL,                                   NULL}
};
