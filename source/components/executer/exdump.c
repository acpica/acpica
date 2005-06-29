
/******************************************************************************
 * 
 * Module Name: isdump - Scanner debug output routines
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

#define __ISDUMP_C__

#include <acpi.h>
#include <interp.h>
#include <amlcode.h>
#include <namesp.h>
#include <tables.h>
#include <acpiosd.h>

#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("isdump");


/*
 * The following routines are used for debug output only 
 */

#ifdef ACPI_DEBUG

/*****************************************************************************
 *
 * FUNCTION:    AmlShowHexValue
 *
 * PARAMETERS:  ByteCount           - Number of bytes to print (1, 2, or 4)
 *              *AmlPtr             - Address in AML stream of bytes to print
 *              InterpreterMode     - Current running mode (load1/Load2/Exec)
 *              LeadSpace           - # of spaces to print ahead of value
 *                                    0 => none ahead but one behind
 *
 * DESCRIPTION: Print ByteCount byte(s) starting at AmlPtr as a single value,
 *              in hex.  If ByteCount > 1 or the value printed is > 9, also
 *              print in decimal.
 *
 ****************************************************************************/

void 
AmlShowHexValue (
    INT32                   ByteCount, 
    UINT8                   *AmlPtr, 
    INT32                   LeadSpace)
{
    INT32                   Value;                  /*  Value retrieved from AML stream */
    INT32                   ShowDecimalValue;
    INT32                   Length;                 /*  Length of printed field */
    UINT8                   *CurrentAmlPtr = NULL;  /*  Pointer to current byte of AML value    */


    FUNCTION_TRACE ("AmlShowHexValue");


    if (!AmlPtr)
    {
        REPORT_ERROR ("AmlShowHexValue: null pointer");
    }

    /* 
     * AML numbers are always stored little-endian,
     * even if the processor is big-endian.
     */
    for (CurrentAmlPtr = AmlPtr + ByteCount, Value = 0; CurrentAmlPtr > AmlPtr; )
    {
        Value = (Value << 8) + (INT32)* --CurrentAmlPtr;
    }

    Length = LeadSpace * ByteCount + 2;
    if (ByteCount > 1)
    {
        Length += (ByteCount - 1);
    }

    ShowDecimalValue = (ByteCount > 1 || Value > 9);
    if (ShowDecimalValue)
    {
        Length += 3 + AmlDigitsNeeded (Value, 10);
    }

    DEBUG_PRINT (TRACE_LOAD, (""));

    for (Length = LeadSpace; Length; --Length )
    {
        DEBUG_PRINT_RAW (TRACE_LOAD, (" "));
    }

    while (ByteCount--)
    {
        DEBUG_PRINT_RAW (TRACE_LOAD, ("%02x", *AmlPtr++));

        if (ByteCount)
        {
            DEBUG_PRINT_RAW (TRACE_LOAD, (" "));
        }
    }

    if (ShowDecimalValue)
    {
        DEBUG_PRINT_RAW (TRACE_LOAD, (" [%ld]", Value));
    }

    if (0 == LeadSpace)
    {
        DEBUG_PRINT_RAW (TRACE_LOAD, (" "));
    }

    DEBUG_PRINT_RAW (TRACE_LOAD, ("\n"));
    return_VOID;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlDumpOperand
 *
 * PARAMETERS:  *EntryDesc          - Pointer to entry to be dumped
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dump a stack entry
 *
 ****************************************************************************/

ACPI_STATUS
AmlDumpOperand (
    ACPI_OBJECT_INTERNAL    *EntryDesc)
{
    UINT8                   *Buf = NULL;
    UINT32                  Length;
    UINT32                  i;


    if (!EntryDesc)
    {
        /* 
         * This usually indicates that something serious is wrong -- since most (if not all) 
         * code that dumps the stack expects something to be there! 
         */
        DEBUG_PRINT (ACPI_INFO, ("AmlDumpOperand: *** Possible error: Null stack entry ptr\n"));
        return AE_OK;
    }

    if (VALID_DESCRIPTOR_TYPE (EntryDesc, DESC_TYPE_NTE))
    {
        DEBUG_PRINT (ACPI_INFO, ("AmlDumpOperand: Name Table Entry (NTE): \n"));
        DUMP_ENTRY (EntryDesc, ACPI_INFO);
        return AE_OK;
    }

    if (TbSystemTablePointer (EntryDesc))
    {
        DEBUG_PRINT (ACPI_INFO, ("AmlDumpOperand: %p is a Pcode pointer\n",
                        EntryDesc));
        return AE_OK;
    }

    if (!VALID_DESCRIPTOR_TYPE (EntryDesc, DESC_TYPE_ACPI_OBJ))
    {
        DEBUG_PRINT (ACPI_INFO, ("AmlDumpOperand: %p Not a local object \n", EntryDesc));
        DUMP_BUFFER (EntryDesc, sizeof (ACPI_OBJECT_INTERNAL));
        return AE_OK;
    }

    /*  EntryDesc is a valid object  */

    DEBUG_PRINT (ACPI_INFO, ("AmlDumpOperand: %p ", EntryDesc));

    switch (EntryDesc->Common.Type)
    {
    case INTERNAL_TYPE_Lvalue:

        switch (EntryDesc->Lvalue.OpCode)
        {
        case AML_ZeroOp:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Lvalue: Zero\n"));
            break;


        case AML_OneOp:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Lvalue: One\n"));
            break;


        case AML_OnesOp:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Lvalue: Ones\n"));
            break;


        case AML_DebugOp:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Lvalue: Debug\n"));
            break;


        case AML_NameOp:

            DUMP_PATHNAME (EntryDesc->Lvalue.Object, "Lvalue: Name: ", 
                            ACPI_INFO, _COMPONENT);
            DUMP_ENTRY (EntryDesc->Lvalue.Object, ACPI_INFO);
            break;


        case AML_IndexOp:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Lvalue: Index %p\n",
                        EntryDesc->Lvalue.Object));
            break;


        case AML_ArgOp:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Lvalue: Arg%d",
                        EntryDesc->Lvalue.Offset));

            if (ACPI_TYPE_Number == EntryDesc->Common.Type)
            {
                /* Value is a Number */
            
                DEBUG_PRINT_RAW (ACPI_INFO, (" value is [%ld]", 
                                            EntryDesc->Number.Value));
            }

            DEBUG_PRINT_RAW (ACPI_INFO, ("\n")); 
            break;


        case AML_LocalOp:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Lvalue: Local%d",
                        EntryDesc->Lvalue.Offset));

            if (ACPI_TYPE_Number == EntryDesc->Common.Type)
            {

                /* Value is a Number */
            
                DEBUG_PRINT_RAW (ACPI_INFO, (" value is [%ld]", 
                                            EntryDesc->Number.Value));
            }

            DEBUG_PRINT_RAW (ACPI_INFO, ("\n")); 
            break;


        default:

            /*  unknown opcode  */

            DEBUG_PRINT_RAW (ACPI_INFO, ("Unknown opcode=%X\n", EntryDesc->Lvalue.OpCode)); 
            REPORT_ERROR ("AmlDumpOperand: Unknown AML Opcode");
            break;

        }

        break;


    case ACPI_TYPE_Buffer:

        DEBUG_PRINT_RAW (ACPI_INFO, ("Buffer[%d] seq %lx @ %p \n",
                    EntryDesc->Buffer.Length, EntryDesc->Buffer.Sequence,
                    EntryDesc->Buffer.Pointer));

        Length = EntryDesc->Buffer.Length;

        if (Length > 64)
        {
            Length = 64;
        }

        /* Debug only -- dump the buffer contents */

        if (EntryDesc->Buffer.Pointer)
        {
            DEBUG_PRINT_RAW (ACPI_INFO, ("Buffer Contents: "));
                           
            for (Buf = EntryDesc->Buffer.Pointer; Length--; ++Buf)
            {
                DEBUG_PRINT_RAW (ACPI_INFO,(Length ? " %02x" : " %02x", *Buf));
            }
            DEBUG_PRINT_RAW (ACPI_INFO,("\n"));
        }

        break;


    case ACPI_TYPE_Number:

        DEBUG_PRINT_RAW (ACPI_INFO, ("Number 0x%lx\n",
                    EntryDesc->Number.Value));
        break;


    case INTERNAL_TYPE_If:

        DEBUG_PRINT_RAW (ACPI_INFO, ("If [Number] 0x%lx\n",
                    EntryDesc->Number.Value));
        break;


    case INTERNAL_TYPE_While:

        DEBUG_PRINT_RAW (ACPI_INFO, ("While [Number] 0x%lx\n",
                    EntryDesc->Number.Value));
        break;


    case ACPI_TYPE_Package:

        DEBUG_PRINT_RAW (ACPI_INFO, ("Package[%d] @ %p\n",
                    EntryDesc->Package.Count, EntryDesc->Package.Elements));


        /* 
         * If elements exist, package vector pointer is valid,
         * and debug_level exceeds 1, dump package's elements.
         */
        if (EntryDesc->Package.Count &&
            EntryDesc->Package.Elements &&
            GetDebugLevel () > 1)
        {
            ACPI_OBJECT_INTERNAL**Element;
            UINT16              ElementIndex;

            for (ElementIndex = 0, Element = EntryDesc->Package.Elements;
                  ElementIndex < EntryDesc->Package.Count;
                  ++ElementIndex, ++Element)
            {
                AmlDumpOperand (*Element);
            }
        }

        DEBUG_PRINT_RAW (ACPI_INFO, ("\n"));

        break;


    case ACPI_TYPE_Region:

        if (EntryDesc->Region.SpaceId >= NUM_REGION_TYPES)
        {
            DEBUG_PRINT_RAW (ACPI_INFO, ("Region **** Unknown ID=0x%X",
                                EntryDesc->Region.SpaceId));
        }
        else
        {
            DEBUG_PRINT_RAW (ACPI_INFO, ("Region %s",
                                Gbl_RegionTypes[EntryDesc->Region.SpaceId]));
        }

        /* 
         * If the address and length have not been evaluated,
         * don't print them.
         */
        if (0 == EntryDesc->Region.DataValid)
        {
            DEBUG_PRINT_RAW (ACPI_INFO, ("\n"));
        }
        else
        {
            DEBUG_PRINT_RAW (ACPI_INFO,
                        (" base %p Length 0x%X\n",
                        EntryDesc->Region.Address, EntryDesc->Region.Length));
        }
        break;


    case ACPI_TYPE_String:

        DEBUG_PRINT_RAW (ACPI_INFO, ("String[%d] @ %p\n\n",
                    EntryDesc->String.Length, EntryDesc->String.Pointer));

        for (i=0; i < EntryDesc->String.Length; i++)
        {
            DEBUG_PRINT_RAW (ACPI_INFO, ("%c",
                        EntryDesc->String.Pointer[i]));
        }

        DEBUG_PRINT_RAW (ACPI_INFO, ("\n\n"));
        break;


    case INTERNAL_TYPE_BankField:

        DEBUG_PRINT_RAW (ACPI_INFO, ("BankField\n"));
        break;


    case INTERNAL_TYPE_DefField:

        DEBUG_PRINT_RAW (ACPI_INFO,
                    ("DefField: bits=%d  acc=%d lock=%d update=%d at byte=%lx bit=%d of below:\n",
                    EntryDesc->Field.Length,   EntryDesc->Field.Access,
                    EntryDesc->Field.LockRule, EntryDesc->Field.UpdateRule,
                    EntryDesc->Field.Offset,   EntryDesc->Field.BitOffset));
        DUMP_STACK_ENTRY (EntryDesc->Field.Container);
        break;


    case INTERNAL_TYPE_IndexField:

        DEBUG_PRINT_RAW (ACPI_INFO, ("IndexField\n"));
        break;


    case ACPI_TYPE_FieldUnit:

        DEBUG_PRINT_RAW (ACPI_INFO,
                    ("FieldUnit: %d bits acc %d lock %d update %d at byte %lx bit %d of \n",
                    EntryDesc->FieldUnit.Length,   EntryDesc->FieldUnit.Access,
                    EntryDesc->FieldUnit.LockRule, EntryDesc->FieldUnit.UpdateRule,
                    EntryDesc->FieldUnit.Offset,   EntryDesc->FieldUnit.BitOffset));

        if (!EntryDesc->FieldUnit.Container)
        {
            DEBUG_PRINT (ACPI_INFO, ("*NULL* \n"));
        }

        else if (ACPI_TYPE_Buffer != EntryDesc->FieldUnit.Container->Common.Type)
        {
            DEBUG_PRINT_RAW (ACPI_INFO, ("*not a Buffer* \n"));
        }

        else
        {
            if (EntryDesc->FieldUnit.Sequence
                    != EntryDesc->FieldUnit.Container->Buffer.Sequence)
            {
                DEBUG_PRINT_RAW (ACPI_INFO,
                              ("[stale] %lx \n", EntryDesc->FieldUnit.Sequence));
            }

            DUMP_STACK_ENTRY (EntryDesc->FieldUnit.Container);
        }
        break;


    case ACPI_TYPE_Event:

        DEBUG_PRINT_RAW (ACPI_INFO, ("Event\n"));
        break;


    case ACPI_TYPE_Method:

        DEBUG_PRINT_RAW (ACPI_INFO,
                    ("Method(%d) @ %p:%lx:%lx\n",
                    EntryDesc->Method.ParamCount, EntryDesc->Method.AcpiTable,
                    EntryDesc->Method.Pcode, EntryDesc->Method.PcodeLength));
        break;


    case ACPI_TYPE_Mutex:

        DEBUG_PRINT_RAW (ACPI_INFO, ("Mutex\n"));
        break;


    case ACPI_TYPE_Device:

        DEBUG_PRINT_RAW (ACPI_INFO, ("Device\n"));
        break;


    case ACPI_TYPE_Power:

        DEBUG_PRINT_RAW (ACPI_INFO, ("Power\n"));
        break;


    case ACPI_TYPE_Processor:

        DEBUG_PRINT_RAW (ACPI_INFO, ("Processor\n"));
        break;


    case ACPI_TYPE_Thermal:

        DEBUG_PRINT_RAW (ACPI_INFO, ("Thermal\n"));
        break;


    default:
        /*  unknown EntryDesc->Common.Type value    */

        DEBUG_PRINT_RAW (ACPI_INFO, ("Unknown Type %X\n", EntryDesc->Common.Type));
        REPORT_ERROR ("AmlDumpOperand: Unknown Type");
        
/* Gbl_Aml table pertains to old parser only */
/* TBD: fix for new parser or remove this code */

#ifdef _RPARSER        
        if (AML_UNASSIGNED != Gbl_Aml[(INT32) EntryDesc->Common.Type])
        {
            DEBUG_PRINT_RAW (ACPI_ERROR,
                          ("AmlDumpOperand: Unhandled opcode (AML %s) \n", 
                          Gbl_ShortOps[Gbl_Aml[(INT32) EntryDesc->Common.Type]]));
        }

#endif

        /* Back up to previous entry ?? */

        EntryDesc--;


        /* TBD:  Change to use dump object routine !! */
        /* TBD:  What is all of this?? */

        DUMP_BUFFER (EntryDesc, sizeof (ACPI_OBJECT_INTERNAL));
        DUMP_BUFFER (++EntryDesc, sizeof (ACPI_OBJECT_INTERNAL));
        DUMP_BUFFER (++EntryDesc, sizeof (ACPI_OBJECT_INTERNAL));
        break;

    }
 
    return AE_OK;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlDumpOperands
 *
 * PARAMETERS:  InterpreterMode      - Load or Exec
 *              *Ident              - Identification
 *              NumLevels           - # of stack entries to dump above line
 *              *Note               - Output notation
 *
 * DESCRIPTION: Dump the object stack
 *
 ****************************************************************************/

void
AmlDumpOperands (
    ACPI_OBJECT_INTERNAL    **Operands,
    OPERATING_MODE          InterpreterMode, 
    char                    *Ident, 
    INT32                   NumLevels, 
    char                    *Note,
    char                    *ModuleName, 
    INT32                   LineNumber)
{
    UINT32                  i;
    ACPI_OBJECT_INTERNAL    **EntryDesc;

    
    if (!Ident)
    {
        Ident = "?";
    }

    if (!Note)
    {
        Note = "?";
    }


    DEBUG_PRINT (ACPI_INFO, ("************* AmlDumpOperands  Mode=%X ******************\n", 
                            InterpreterMode));
    DEBUG_PRINT (ACPI_INFO, ("From %12s(%d)  %s: %s\n", ModuleName, LineNumber, Ident, Note));

    if (NumLevels == 0)
        NumLevels = 1;

    /* Dump the stack starting at the top, working down */

    for (i = 0; NumLevels > 0; i--, NumLevels--)
    {
        EntryDesc = &Operands[i];

        if (AE_OK != AmlDumpOperand (*EntryDesc))
        {
            break;
        }
    }

    return;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlDumpNameTableEntry
 *
 * PARAMETERS:  *Entry              - Descriptor to dump
 *              Flags               - Force display
 *
 * DESCRIPTION: Dumps the members of the NTE given.
 *
 ****************************************************************************/

void
AmlDumpNameTableEntry (
    NAME_TABLE_ENTRY        *Entry,
    UINT32                  Flags)
{

    if (!Flags)
    {
	    if (!((TRACE_OBJECTS & DebugLevel) && (_COMPONENT & DebugLayer)))
        {
            return;
        }
    }


    OsdPrintf ("%20s : %4.4s\n",    "Name", &Entry->Name);
    OsdPrintf ("%20s : %s\n",       "Type", Gbl_NsTypeNames [Entry->Type]);
    OsdPrintf ("%20s : 0x%X\n",     "Flags", Entry->Flags);
    OsdPrintf ("%20s : 0x%p\n",     "Attached Object", Entry->Object);
    OsdPrintf ("%20s : 0x%p\n",     "Scope", Entry->Scope);
    OsdPrintf ("%20s : 0x%p\n",     "Parent", Entry->ParentEntry);
    OsdPrintf ("%20s : 0x%p\n",     "Next", Entry->NextEntry);
    OsdPrintf ("%20s : 0x%p\n",     "Previous", Entry->PrevEntry);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlDumpObjectDescriptor
 *
 * PARAMETERS:  *Object             - Descriptor to dump
 *              Flags               - Force display
 *
 * DESCRIPTION: Dumps the members of the object descriptor given.
 *
 ****************************************************************************/

void
AmlDumpObjectDescriptor (
    ACPI_OBJECT_INTERNAL    *Object,
    UINT32                  Flags)
{
	FUNCTION_TRACE ("AmlDumpObjectDescriptor");

    
    if (!Flags)
    {
	    if (!((TRACE_OBJECTS & DebugLevel) && (_COMPONENT & DebugLayer)))
        {
            return;
        }
    }
	
	switch (Object->Common.Type)
	{
	case ACPI_TYPE_Number:

		OsdPrintf ("%20s : %s\n", "Type", "Number");
        OsdPrintf ("%20s : %x\n", "Value", Object->Number.Value);
		break;
 
        
	case ACPI_TYPE_String:

	    OsdPrintf ("%20s : %s\n", "Type", "String");
        OsdPrintf ("%20s : %x\n", "Length", Object->String.Length);
        OsdPrintf ("%20s : %x\n", "Pointer", Object->String.Pointer);
		break;


	case ACPI_TYPE_Buffer:

		OsdPrintf ("%20s : %s\n", "Type", "Buffer");
		OsdPrintf ("%20s : %x\n", "Length", Object->Buffer.Length);
        OsdPrintf ("%20s : %x\n", "Sequence", Object->Buffer.Sequence);
        OsdPrintf ("%20s : %x\n", "Pointer", Object->Buffer.Pointer);
		break;
        
        
	case ACPI_TYPE_Package:

		OsdPrintf ("%20s : %s\n", "Type", "Package");
	    OsdPrintf ("%20s : %x\n", "Count", Object->Package.Count);
	    OsdPrintf ("%20s : %x\n", "Elements", Object->Package.Elements);
	    OsdPrintf ("%20s : %x\n", "NextElement", Object->Package.NextElement);
		break;
        

	case ACPI_TYPE_FieldUnit:

		OsdPrintf ("%20s : %s\n", "Type", "FieldUnit");
		OsdPrintf ("%20s : %x\n", "Access", Object->FieldUnit.Access);
	    OsdPrintf ("%20s : %x\n", "LockRule", Object->FieldUnit.LockRule);
	    OsdPrintf ("%20s : %x\n", "UpdateRule", Object->FieldUnit.UpdateRule);
	    OsdPrintf ("%20s : %x\n", "Length", Object->FieldUnit.Length);
	    OsdPrintf ("%20s : %x\n", "BitOffset", Object->FieldUnit.BitOffset);
	    OsdPrintf ("%20s : %x\n", "Offset", Object->FieldUnit.Offset);
	    OsdPrintf ("%20s : %x\n", "Sequence", Object->FieldUnit.Sequence);
	    OsdPrintf ("%20s : %x\n", "Container", Object->FieldUnit.Container);
	    break;
        

	case ACPI_TYPE_Device:

		OsdPrintf ("%20s : %s\n", "Type", "Device");
	    OsdPrintf ("%20s : %x\n", "Handle", Object->Device.Handle);
	    OsdPrintf ("%20s : %p\n", "AddrHandler", Object->Device.AddrHandler);
	    OsdPrintf ("%20s : %p\n", "SysHandler", Object->Device.SysHandler);
	    OsdPrintf ("%20s : %p\n", "DrvHandler", Object->Device.DrvHandler);
        break;

	case ACPI_TYPE_Event:

		OsdPrintf ("%20s : %s\n", "Type", "Event");
	    OsdPrintf ("%20s : %x\n", "SignalCount", Object->Event.SignalCount);
	    OsdPrintf ("%20s : %x\n", "Semaphore", Object->Event.Semaphore);
	    OsdPrintf ("%20s : %x\n", "LockCount", Object->Event.LockCount);
	    OsdPrintf ("%20s : %x\n", "ThreadId", Object->Event.ThreadId);
	    break;


	case ACPI_TYPE_Method:

		OsdPrintf ("%20s : %s\n", "Type", "Method");
	    OsdPrintf ("%20s : %x\n", "ParamCount", Object->Method.ParamCount);
	    OsdPrintf ("%20s : %x\n", "PcodeLength", Object->Method.PcodeLength);
	    OsdPrintf ("%20s : %x\n", "Pcode", Object->Method.Pcode);
	    OsdPrintf ("%20s : %x\n", "AcpiTable", Object->Method.AcpiTable);
	    break;
	

	case ACPI_TYPE_Mutex:

		OsdPrintf ("%20s : %s\n", "Type", "Mutex");
	    OsdPrintf ("%20s : %x\n", "SyncLevel", Object->Mutex.SyncLevel);
	    OsdPrintf ("%20s : %x\n", "Semaphore", Object->Mutex.Semaphore);
	    OsdPrintf ("%20s : %x\n", "LockCount", Object->Mutex.LockCount);
	    OsdPrintf ("%20s : %x\n", "ThreadId", Object->Mutex.ThreadId);
	    break;


	case ACPI_TYPE_Region:

		OsdPrintf ("%20s : %s\n", "Type", "Region");
	    OsdPrintf ("%20s : %x\n", "SpaceId", Object->Region.SpaceId);
	    OsdPrintf ("%20s : %x\n", "DataValid", Object->Region.DataValid);
	    OsdPrintf ("%20s : %x\n", "Address", Object->Region.Address);
	    OsdPrintf ("%20s : %x\n", "Length", Object->Region.Length);
	    OsdPrintf ("%20s : %x\n", "Method", Object->Region.Method);
	    OsdPrintf ("%20s : %x\n", "AddrHandler", Object->Region.AddrHandler);
	    OsdPrintf ("%20s : %x\n", "Link", Object->Region.Link);
 	    break;


	case ACPI_TYPE_Power:

		OsdPrintf ("%20s : %s\n", "Type", "PowerResource");
	    OsdPrintf ("%20s : %x\n", "Handle", Object->PowerResource.Handle);
	    OsdPrintf ("%20s : %p\n", "SysHandler", Object->PowerResource.SysHandler);
	    OsdPrintf ("%20s : %p\n", "DrvHandler", Object->PowerResource.DrvHandler);
	    break;


	case ACPI_TYPE_Processor:

		OsdPrintf ("%20s : %s\n", "Type", "Processor");
	    OsdPrintf ("%20s : %x\n", "Handle", Object->Processor.Handle);
	    OsdPrintf ("%20s : %p\n", "SysHandler", Object->Processor.SysHandler);
	    OsdPrintf ("%20s : %p\n", "DrvHandler", Object->Processor.DrvHandler);
	    break;


	case ACPI_TYPE_Thermal:

		OsdPrintf ("%20s : %s\n", "Type", "ThermalZone");
	    OsdPrintf ("%20s : %x\n", "Handle", Object->ThermalZone.Handle);
	    OsdPrintf ("%20s : %p\n", "SysHandler", Object->ThermalZone.SysHandler);
	    OsdPrintf ("%20s : %p\n", "DrvHandler", Object->ThermalZone.DrvHandler);
	    break;

	case INTERNAL_TYPE_BankField:

		OsdPrintf ("%20s : %s\n", "Type", "BankField");
	    OsdPrintf ("%20s : %x\n", "Access", Object->BankField.Access);
	    OsdPrintf ("%20s : %x\n", "LockRule", Object->BankField.LockRule);
	    OsdPrintf ("%20s : %x\n", "UpdateRule", Object->BankField.UpdateRule);
	    OsdPrintf ("%20s : %x\n", "Length", Object->BankField.Length);
	    OsdPrintf ("%20s : %x\n", "BitOffset", Object->BankField.BitOffset);
	    OsdPrintf ("%20s : %x\n", "Offset", Object->BankField.Offset);
	    OsdPrintf ("%20s : %x\n", "Value", Object->BankField.Value);
		OsdPrintf ("%20s : %x\n", "Container", Object->BankField.Container);
	    OsdPrintf ("%20s : %x\n", "BankSelect", Object->BankField.BankSelect);
	    break;


	case INTERNAL_TYPE_IndexField:

		OsdPrintf ("%20s : %s\n", "Type", "IndexField");
	    OsdPrintf ("%20s : %x\n", "Access", Object->IndexField.Access);
	    OsdPrintf ("%20s : %x\n", "LockRule", Object->IndexField.LockRule);
	    OsdPrintf ("%20s : %x\n", "UpdateRule", Object->IndexField.UpdateRule);
	    OsdPrintf ("%20s : %x\n", "Length", Object->IndexField.Length);
	    OsdPrintf ("%20s : %x\n", "BitOffset", Object->IndexField.BitOffset);
	    OsdPrintf ("%20s : %x\n", "Value", Object->IndexField.Value);
		OsdPrintf ("%20s : %x\n", "Index", Object->IndexField.Index);
	    OsdPrintf ("%20s : %x\n", "Data", Object->IndexField.Data);
	    break;


	case INTERNAL_TYPE_Lvalue:

		OsdPrintf ("%20s : %s\n", "Type", "Lvalue");
	    OsdPrintf ("%20s : %x\n", "OpCode", Object->Lvalue.OpCode);
	    OsdPrintf ("%20s : %x\n", "Object", Object->Lvalue.Object);
		break;


	case INTERNAL_TYPE_AddressHandler:

		OsdPrintf ("%20s : %s\n", "Type", "Address Handler");
	    OsdPrintf ("%20s : %x\n", "SpaceId", Object->AddrHandler.SpaceId);
	    OsdPrintf ("%20s : %x\n", "Link", Object->AddrHandler.Link);
	    OsdPrintf ("%20s : %x\n", "RegionList", Object->AddrHandler.RegionList);
	    OsdPrintf ("%20s : %x\n", "Nte", Object->AddrHandler.Nte);
	    OsdPrintf ("%20s : %x\n", "Handler", Object->AddrHandler.Handler);
	    OsdPrintf ("%20s : %x\n", "Context", Object->AddrHandler.Context);
		break;

	case INTERNAL_TYPE_Notify:

		OsdPrintf ("%20s : %s\n", "Type", "Notify Handler");
	    OsdPrintf ("%20s : %x\n", "Nte", Object->NotifyHandler.Nte);
	    OsdPrintf ("%20s : %x\n", "Handler", Object->NotifyHandler.Handler);
	    OsdPrintf ("%20s : %x\n", "Context", Object->NotifyHandler.Context);
		break;


    case INTERNAL_TYPE_Alias:
	case INTERNAL_TYPE_DefField:
	case INTERNAL_TYPE_DefFieldDefn:
	case INTERNAL_TYPE_BankFieldDefn:
	case INTERNAL_TYPE_IndexFieldDefn:
	case INTERNAL_TYPE_If:
	case INTERNAL_TYPE_Else:
	case INTERNAL_TYPE_While:
	case INTERNAL_TYPE_Scope:
	case INTERNAL_TYPE_DefAny:

		OsdPrintf ("*** Structure display not implemented for type %d! ***\n",
        	Object->Common.Type);
		break;


	default:

		OsdPrintf ("*** Cannot display unknown type %d! ***\n", Object->Common.Type);
		break;
	}

    return_VOID;
}

#endif

