/******************************************************************************
 *
 * Module Name: ahops.h - Tables of all known ASL operators
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2011, Intel Corp.
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

#ifndef __AHOPS_H
#define __AHOPS_H


/*
 * ASL operators with syntax (directly from ACPI specification)
 * Note: All tokens require a space separator.
 * Long lines are automatically split during output.
 */
const char * AslOperatorSyntax [] =
{
    "Acquire (SyncObject, TimeoutValue) => Boolean",
    "Add (Addend1, Addend2, Result) => Integer",
    "Alias (SourceObject, AliasObject)",
    "And (Source1, Source2, Result) => Integer",
    "BankField (RegionName, BankName, BankValue, AccessType, LockRule, UpdateRule) {FieldUnitList}",
    "Break",
    "BreakPoint",
    "Buffer (BufferSize) {String or ByteList} => Buffer",
    "Case (Value) {TermList}",
    "Concatenate (Source1, Source2, Result) => ComputationalData",
    "ConcatenateResTemplate (Source1, Source2, Result) => Buffer",
    "CondRefOf (Source, Result) => Boolean",
    "Continue",
    "CopyObject (Source, Destination) => DataRefObject",
    "CreateBitField (SourceBuffer, BitIndex, BitFieldName)",
    "CreateByteField (SourceBuffer, ByteIndex, ByteFieldName)",
    "CreateDWordField (SourceBuffer, ByteIndex, DWordFieldName)",
    "CreateField (SourceBuffer, BitIndex, NumBits, FieldName)",
    "CreateQWordField (SourceBuffer, ByteIndex, QWordFieldName)",
    "CreateWordField (SourceBuffer, ByteIndex, WordFieldName)",
    "DataTableRegion (RegionName, SignatureString, OemIDString, OemTableIDString)",
    "Debug",
    "Decrement (Minuend) => Integer",
    "Default {TermList}",
    "DefinitionBlock (AMLFileName, TableSignature, ComplianceRevision, OEMID, TableID, OEMRevision) {TermList}",
    "DerefOf (Source) => Object",
    "Device (DeviceName) {ObjectList}",
    "Divide (Dividend, Divisor, Remainder, Result) => Integer",
    "DMA (DmaType, IsBusMaster, DmaTransferSize, DescriptorName) {DmaChannelList} => Buffer",
    "DWordIO (ResourceUsage, IsMinFixed, IsMaxFixed, Decode, ISARanges, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, ResourceSourceIndex, ResourceSource, DescriptorName, TranslationType, TranslationDensity)",
    "DWordMemory (ResourceUsage, Decode, IsMinFixed, IsMaxFixed, Cacheable, ReadAndWrite, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, ResourceSourceIndex, ResourceSource, DescriptorName, MemoryType, TranslationType)",
    "DWordSpace (ResourceType, ResourceUsage, Decode, IsMinFixed, IsMaxFixed, TypeSpecificFlags, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, ResourceSourceIndex, ResourceSource, DescriptorName)",
    "EISAID (EisaIdString) => DWordConst",
    "Else {TermList}",
    "ElseIf (Predicate)",
    "EndDependentFn () => Buffer",
    "ExtendedIO (ResourceUsage, IsMinFixed, IsMaxFixed, Decode, ISARanges, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, TypeSpecificAttributes, DescriptorName, TranslationType, TranslationDensity)",
    "ExtendedMemory (ResourceUsage, Decode, IsMinFixed, IsMaxFixed, Cacheable, ReadAndWrite, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, TypeSpecificAttributes, DescriptorName, MemoryType, TranslationType)",
    "ExtendedSpace (ResourceType, ResourceUsage, Decode, IsMinFixed, IsMaxFixed, TypeSpecificFlags, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, TypeSpecificAttributes, DescriptorName)",
    "External (ObjectName, ObjectType, ReturnType, ParameterTypes)",
    "Fatal (Type, Code, Arg)",
    "Field (RegionName, AccessType, LockRule, UpdateRule) {FieldUnitList}",
    "FindSetLeftBit (Source, Result) => Integer",
    "FindSetRightBit (Source, Result) => Integer",
    "FixedIO (AddressBase, RangeLength, DescriptorName) => Buffer",
    "FromBCD (BCDValue, Result) => Integer",
    "Function (FunctionName, ReturnType, ParameterTypes) {TermList}",
    "If (Predicate) {TermList}",
    "Include (FilePathName)",
    "Increment (Addend) => Integer",
    "Index (Source, Index, Destination) => ObjectReference",
    "IndexField (IndexName, DataName, AccessType, LockRule, UpdateRule) {FieldUnitList}",
    "Interrupt (ResourceUsage, EdgeLevel, ActiveLevel, Shared, ResourceSourceIndex, ResourceSource, DescriptorName) {InterruptList} => Buffer",
    "IO (Decode, AddressMin, AddressMax, AddressAlignment, RangeLength, DescriptorName) => Buffer",
    "IRQ (EdgeLevel, ActiveLevel, Shared, DescriptorName) {InterruptList} => Buffer",
    "IRQNoFlags (DescriptorName) {InterruptList} => Buffer",
    "LAnd (Source1, Source2) => Boolean",
    "LEqual (Source1, Source2) => Boolean",
    "LGreater (Source1, Source2) => Boolean",
    "LGreaterEqual (Source1, Source2) => Boolean",
    "LLess (Source1, Source2) => Boolean",
    "LLessEqual (Source1, Source2) => Boolean",
    "LNot (Source) => Boolean",
    "LNotEqual (Source1, Source2) => Boolean",
    "Load (Object, DDBHandle)",
    "LoadTable (SignatureString, OEMIDString, OEMTableIDString, RootPathString, ParameterPathString, ParameterData) => DDBHandle",
    "LOr (Source1, Source2) => Boolean",
    "Match (SearchPackage, Op1, MatchObject1, Op2, MatchObject2, StartIndex) => Ones | Integer",
    "Memory24 (ReadAndWrite, AddressMinimum, AddressMaximum, AddressAlignment, RangeLength, DescriptorName)",
    "Memory32 (ReadAndWrite, AddressMinimum, AddressMaximum, AddressAlignment, RangeLength, DescriptorName)",
    "Memory32Fixed (ReadAndWrite, AddressBase, RangeLength, DescriptorName)",
    "Method (MethodName, NumArgs, SerializeRule, SyncLevel, ReturnType, ParameterTypes) {TermList}",
    "Mid (Source, Index, Length, Result) => Buffer or String",
    "Mod (Dividend, Divisor, Result) => Integer",
    "Multiply (Multiplicand, Multiplier, Result) => Integer",
    "Mutex (MutexName, SyncLevel)",
    "Name (ObjectName, Object)",
    "NAnd (Source1, Source2, Result) => Integer",
    "NoOp",
    "NOr (Source1, Source2, Result) => Integer",
    "Not (Source, Result) => Integer",
    "Notify (Object, NotificationValue)",
    "ObjectType (Object) => Integer",
    "One => Integer",
    "Ones => Integer",
    "OperationRegion (RegionName, RegionSpace, Offset, Length)",
    "Or (Source1, Source2, Result) => Integer",
    "Package (NumElements) {PackageList} => Package",
    "PowerResource (ResourceName, SystemLevel, ResourceOrder) {ObjectList}",
    "Processor (ProcessorName, ProcessorID, PBlockAddress, PblockLength) {ObjectList}",
    "QWordIO (ResourceUsage, IsMinFixed, IsMaxFixed, Decode, ISARanges, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, ResourceSourceIndex, ResourceSource, DescriptorName, TranslationType, TranslationDensity)",
    "QWordMemory (ResourceUsage, Decode, IsMinFixed, IsMaxFixed, Cacheable, ReadAndWrite, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, ResourceSourceIndex, ResourceSource, DescriptorName, MemoryType, TranslationType)",
    "QWordSpace (ResourceType, ResourceUsage, Decode, IsMinFixed, IsMaxFixed, TypeSpecificFlags, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, ResourceSourceIndex, ResourceSource, DescriptorName)",
    "RefOf (Object) => ObjectReference",
    "Register (AddressSpaceKeyword, RegisterBitWidth, RegisterBitOffset, RegisterAddress, AccessSize, DescriptorName)",
    "Release (SyncObject)",
    "Reset (SyncObject)",
    "ResourceTemplate () {ResourceMacroList} => Buffer",
    "Revision => Integer",
    "Scope (Location) {ObjectList}",
    "ShiftLeft (Source, ShiftCount, Result) => Integer",
    "ShiftRight (Source, ShiftCount, Result) => Integer",
    "Signal (SyncObject)",
    "SizeOf (ObjectName) => Integer",
    "Sleep (MilliSeconds)",
    "Stall (MicroSeconds)",
    "StartDependentFn (CompatibilityPriority, PerformancePriority) {ResourceList}",
    "StartDependentFnNoPri () {ResourceList}",
    "Store (Source, Destination) => DataRefObject",
    "Subtract (Minuend, Subtrahend, Result) => Integer",
    "Switch (Expression) {CaseTermList}",
    "ThermalZone (ThermalZoneName) {ObjectList}",
    "Timer => Integer",
    "ToBCD (Value, Result) => Integer",
    "ToBuffer (Data, Result) => Buffer",
    "ToDecimalString (Data, Result) => String",
    "ToHexString (Data, Result) => String",
    "ToInteger (Data, Result) => Integer",
    "ToString (Source, Length, Result) => String",
    "ToUUID (AsciiString) => Buffer",
    "Unicode (String) => Buffer",
    "Unload (Handle)",
    "VendorLong (DescriptorName) {VendorByteList}",
    "VendorShort (DescriptorName) {VendorByteList}",
    "Wait (SyncObject, TimeoutValue) => Boolean",
    "While (Predicate) {TermList}",
    "WordBusNumber (ResourceUsage, IsMinFixed, IsMaxFixed, Decode, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, ResourceSourceIndex, ResourceSource, DescriptorName)",
    "WordIO (ResourceUsage, IsMinFixed, IsMaxFixed, Decode, ISARanges, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, ResourceSourceIndex, ResourceSource, DescriptorName, TranslationType, TranslationDensity)",
    "WordSpace (ResourceType, ResourceUsage, Decode, IsMinFixed, IsMaxFixed, TypeSpecificFlags, AddressGranularity, AddressMinimum, AddressMaximum, AddressTranslation, RangeLength, ResourceSourceIndex, ResourceSource, DescriptorName)",
    "XOr (Source1, Source2, Result) => Integer",
    "Zero => Integer",
    NULL
};

/*
 * ASL operator names in upper case for string matching
 * Names must be uppercase for fast compares, and
 * correspond one-to-one with table above.
 */
const char * AslOperatorNames[] =
{
    "ACQUIRE",
    "ADD",
    "ALIAS",
    "AND",
    "BANKFIELD",
    "BREAK",
    "BREAKPOINT",
    "BUFFER",
    "CASE",
    "CONCATENATE",
    "CONCATENATERESTEMPLATE",
    "CONDREFOF",
    "CONTINUE",
    "COPYOBJECT",
    "CREATEBITFIELD",
    "CREATEBYTEFIELD",
    "CREATEDWORDFIELD",
    "CREATEFIELD",
    "CREATEQWORDFIELD",
    "CREATEWORDFIELD",
    "DATATABLEREGION",
    "DEBUG",
    "DECREMENT",
    "DEFAULT",
    "DEFINITIONBLOCK",
    "DEREFOF",
    "DEVICE",
    "DIVIDE",
    "DMA",
    "DWORDIO",
    "DWORDMEMORY",
    "DWORDSPACE",
    "EISAID",
    "ELSE",
    "ELSEIF",
    "ENDDEPENDENTFN",
    "EXTENDEDIO",
    "EXTENDEDMEMORY",
    "EXTENDEDSPACE",
    "EXTERNAL",
    "FATAL",
    "FIELD",
    "FINDSETLEFTBIT",
    "FINDSETRIGHTBIT",
    "FIXEDIO",
    "FROMBCD",
    "FUNCTION",
    "IF",
    "INCLUDE",
    "INCREMENT",
    "INDEX",
    "INDEXFIELD",
    "INTERRUPT",
    "IO",
    "IRQ",
    "IRQNOFLAGS",
    "LAND",
    "LEQUAL",
    "LGREATER",
    "LGREATEREQUAL",
    "LLESS",
    "LLESSEQUAL",
    "LNOT",
    "LNOTEQUAL",
    "LOAD",
    "LOADTABLE",
    "LOR",
    "MATCH",
    "MEMORY24",
    "MEMORY32",
    "MEMORY32FIXED",
    "METHOD",
    "MID",
    "MOD",
    "MULTIPLY",
    "MUTEX",
    "NAME",
    "NAND",
    "NOOP",
    "NOR",
    "NOT",
    "NOTIFY",
    "OBJECTTYPE",
    "ONE",
    "ONES",
    "OPERATIONREGION",
    "OR",
    "PACKAGE",
    "POWERRESOURCE",
    "PROCESSOR",
    "QWORDIO",
    "QWORDMEMORY",
    "QWORDSPACE",
    "REFOF",
    "REGISTER",
    "RELEASE",
    "RESET",
    "RESOURCETEMPLATE",
    "REVISION",
    "SCOPE",
    "SHIFTLEFT",
    "SHIFTRIGHT",
    "SIGNAL",
    "SIZEOF",
    "SLEEP",
    "STALL",
    "STARTDEPENDENTFN",
    "STARTDEPENDENTFNNOPRI",
    "STORE",
    "SUBTRACT",
    "SWITCH",
    "THERMALZONE",
    "TIMER",
    "TOBCD",
    "TOBUFFER",
    "TODECIMALSTRING",
    "TOHEXSTRING",
    "TOINTEGER",
    "TOSTRING",
    "TOUUID",
    "UNICODE",
    "UNLOAD",
    "VENDORLONG",
    "VENDORSHORT",
    "WAIT",
    "WHILE",
    "WORDBUSNUMBER",
    "WORDIO",
    "WORDSPACE",
    "XOR",
    "ZERO",
    NULL
};

#endif
