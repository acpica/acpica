
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
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>
#include <acpiosd.h>

#define _THIS_MODULE        "isdump.c"
#define _COMPONENT          INTERPRETER


/* TBD: Move this routine to common code */

/*****************************************************************************
 * 
 * FUNCTION:    DumpBuffer
 *
 * PARAMETERS:  Buffer              - Buffer to dump
 *              Count               - Amount to dump, in bytes
 *              Flags               - Options (not implemented)
 *              ComponentID         - Caller's component ID
 *
 * RETURN:      None
 *
 * DESCRIPTION: Generic dump buffer in both hex and ascii.
 *
 ****************************************************************************/

void
DumpBuffer (
    char                    *Buffer, 
    UINT32                  Count, 
    INT32                   Flags, 
    INT32                   ComponentId)
{
    UINT32                  i = 0;
    UINT32                  j;
    UINT8                   BufChar;


    /* Only dump the buffer if tracing is enabled */

    if (!((TRACE_TABLES & DebugLevel) && (ComponentId & DebugLayer)))
    {
        return;
    }


    /*
     * Nasty little dump buffer routine!
     */
    while (i <= Count)
    {
        /* Print current offset */

        OsdPrintf ("%05X    ", i);


        /* Print 16 hex chars */

        for (j = 0; j < 16; j++)
        {
            if (i + j >= Count)
                goto cleanup;


            /* Make sure that the char doesn't get sign-extended! */

            BufChar = Buffer[i + j];
            OsdPrintf ("%02X ", BufChar);
        }

        /* 
         * Print the ASCII equivalent characters
         * But watch out for the bad unprintable ones...
         */

        for (j = 0; j < 16; j++)
        {
            if (i + j >= Count)
                goto cleanup;

            BufChar = Buffer[i + j];
            if ((BufChar > 0x1F && BufChar < 0x2E) ||
                (BufChar > 0x2F && BufChar < 0x61) ||
                (BufChar > 0x60 && BufChar < 0x7F))

                OsdPrintf ("%c", BufChar);
            else
                OsdPrintf (".");
                
        }

        /* Done with that line. */

        OsdPrintf ("\n");
        i += 16;
    }

    return;

cleanup:
    OsdPrintf ("\n");
    return;

}


/****************************************************************************
 * 
 * FUNCTION:    AmlDumpBuffer
 *
 * PARAMETERS:  NumBytes            - Number of AML stream bytes to dump
 *
 * DESCRIPTION: Hex display current AML without consuming the bytes
 *
 ***************************************************************************/

void
AmlDumpBuffer (
    ACPI_SIZE               NumBytes)
{

    FUNCTION_TRACE ("AmlDumpBuffer");


    DEBUG_PRINT (TRACE_TABLES, ("AML from %p:\n", AmlGetPCodeHandle ()));
    DumpBuffer ((UINT8 *) AmlGetPCodeHandle (), NumBytes, HEX, INTERPRETER);

    return_VOID;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlDumpObjStackEntry
 *
 * PARAMETERS:  *EntryDesc          - Pointer to entry to be dumped
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dump a stack entry
 *
 ****************************************************************************/

ACPI_STATUS
AmlDumpObjStackEntry (
    ACPI_OBJECT_INTERNAL    *EntryDesc)
{
    char                    *OutString = NULL;
    UINT8                   *Buf = NULL;
    UINT16                  Length;


    FUNCTION_TRACE ("AmlDumpObjStackEntry");


    if (!EntryDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlDumpObjStackEntry: ***NULL stack entry pointer***\n"));
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    else if (IS_NS_HANDLE (EntryDesc))
    {
        DEBUG_PRINT (ACPI_INFO, ("AmlDumpObjStackEntry: Name \n"));
        DUMP_ENTRY (EntryDesc);
    }

    else
    {
        /*  EntryDesc is valid  */

        DEBUG_PRINT (ACPI_INFO, ("AmlDumpObjStackEntry: Entry %p - ", EntryDesc));

        switch (EntryDesc->Type)
        {
        case TYPE_Lvalue:

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


            case Debug1:

                DEBUG_PRINT_RAW (ACPI_INFO, ("Lvalue: Debug\n"));
                break;


            case AML_NameOp:

                NsDumpPathname (EntryDesc->Lvalue.Object, "Lvalue: Name: ", 
                                ACPI_INFO, _COMPONENT);
                DUMP_ENTRY (EntryDesc->Lvalue.Object);
                break;
 

            case AML_IndexOp:

                DEBUG_PRINT_RAW (ACPI_INFO, ("Lvalue: Index %p\n",
                            EntryDesc->Lvalue.Object));
                break;
 

            case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
            case AML_Arg4: case AML_Arg5: case AML_Arg6:

                DEBUG_PRINT_RAW (ACPI_INFO, ("Lvalue: Arg%d",
                            EntryDesc->Lvalue.OpCode - AML_Arg0));

                if (TYPE_Number == EntryDesc->Type)
                {
                    /* Value is a Number */
                
                    DEBUG_PRINT_RAW (ACPI_INFO, (" value is [%ld]", 
                                                EntryDesc->Number.Value));
                }

                DEBUG_PRINT_RAW (ACPI_INFO, ("\n")); 
                break;


            case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
            case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:

                DEBUG_PRINT_RAW (ACPI_INFO, ("Lvalue: Local%d",
                            EntryDesc->Lvalue.OpCode - AML_Local0));

                if (TYPE_Number == EntryDesc->Type)
                {

                    /* Value is a Number */
                
                    DEBUG_PRINT_RAW (ACPI_INFO, (" value is [%ld]", 
                                                EntryDesc->Number.Value));
                }

                DEBUG_PRINT_RAW (ACPI_INFO, ("\n")); 
                break;


            default:

                /*  unknown opcode  */

                REPORT_ERROR ("AmlDumpObjStackEntry: Unknown AML Opcode");
                break;

            }
            break;


        case TYPE_Buffer:

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


        case TYPE_Number:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Number 0x%lx\n",
                        EntryDesc->Number.Value));
            break;


        case TYPE_If:

            DEBUG_PRINT_RAW (ACPI_INFO, ("If [Number] 0x%lx\n",
                        EntryDesc->Number.Value));
            break;


        case TYPE_While:

            DEBUG_PRINT_RAW (ACPI_INFO, ("While [Number] 0x%lx\n",
                        EntryDesc->Number.Value));
            break;


        case TYPE_Package:

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
                    AmlDumpObjStackEntry (*Element);
                }
            }

            DEBUG_PRINT_RAW (ACPI_INFO, ("\n"));

            break;


        case TYPE_Region:

            if (EntryDesc->Region.SpaceId >= NUM_REGION_TYPES)
            {
                OutString = "**UNRECOGNIZED**";
            }
            else
            {
                OutString = RegionTypes[EntryDesc->Region.SpaceId];
            }

            /* 
             * If the address and length have not been evaluated,
             * don't print them.
             */
            if (0 == EntryDesc->Region.DataValid)
            {
                DEBUG_PRINT_RAW (ACPI_INFO, ("Region %s\n", OutString));
            }
            else
            {
                DEBUG_PRINT_RAW (ACPI_INFO,
                            ("Region %s base %08lx Length %08lx\n", OutString,
                            EntryDesc->Region.Address, EntryDesc->Region.Length));
            }
            break;


        case TYPE_String:

            DEBUG_PRINT_RAW (ACPI_INFO, ("String[%d] @ %p\n",
                        EntryDesc->String.Length, EntryDesc->String.Pointer));
            break;


        case TYPE_BankField:

            DEBUG_PRINT_RAW (ACPI_INFO, ("BankField\n"));
            break;


        case TYPE_DefField:

            DEBUG_PRINT_RAW (ACPI_INFO,
                        ("DefField: %d bits acc %d lock %d update %d at byte %lx bit %d of \n",
                        EntryDesc->Field.Length,   EntryDesc->Field.Access,
                        EntryDesc->Field.LockRule, EntryDesc->Field.UpdateRule,
                        EntryDesc->Field.Offset,   EntryDesc->Field.BitOffset));
            DUMP_STACK_ENTRY (EntryDesc->Field.Container);
            break;


        case TYPE_IndexField:

            DEBUG_PRINT_RAW (ACPI_INFO, ("IndexField\n"));
            break;


        case TYPE_FieldUnit:

            DEBUG_PRINT_RAW (ACPI_INFO,
                        ("FieldUnit: %d bits acc %d lock %d update %d at byte %lx bit %d of \n",
                        EntryDesc->FieldUnit.Length,   EntryDesc->FieldUnit.Access,
                        EntryDesc->FieldUnit.LockRule, EntryDesc->FieldUnit.UpdateRule,
                        EntryDesc->FieldUnit.Offset,   EntryDesc->FieldUnit.BitOffset));

            if (!EntryDesc->FieldUnit.Container)
            {
                DEBUG_PRINT (ACPI_INFO, ("*NULL* \n"));
            }
            else if (TYPE_Buffer != EntryDesc->FieldUnit.Container->Type)
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


        case TYPE_Event:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Event\n"));
            break;


        case TYPE_Method:

            DEBUG_PRINT_RAW (ACPI_INFO,
                        ("Method(%d) @ %p:%lx:%lx\n",
                        EntryDesc->Method.ParamCount, EntryDesc->Method.AmlBase,
                        EntryDesc->Method.AmlOffset, EntryDesc->Method.Length));
            break;


        case TYPE_Mutex:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Mutex\n"));
            break;


        case TYPE_Device:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Device\n"));
            break;


        case TYPE_Power:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Power\n"));
            break;


        case TYPE_Processor:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Processor\n"));
            break;


        case TYPE_Thermal:

            DEBUG_PRINT_RAW (ACPI_INFO, ("Thermal\n"));
            break;


        default:
            /*  unknown EntryDesc->Type value    */

            REPORT_ERROR ("AmlDumpObjStackEntry: Unknown Type");
            
            if (AML_UNASSIGNED != Aml[(INT32) EntryDesc->Type])
            {
                DEBUG_PRINT_RAW (ACPI_ERROR,
                              ("AmlDumpObjStackEntry: Unhandled opcode (AML %s) \n", 
                              ShortOps[Aml[(INT32) EntryDesc->Type]]));
            }


            /* !!!! POINTER STUFF COMMENTED OUT !!!! */

/*
 *           if (PtrOffset (EntryDesc) > sizeof (ACPI_OBJECT_INTERNAL))
 *           {
 *               --EntryDesc;
 *           }
 *           else
 *           {
 *               EntryDesc = (ACPI_OBJECT_INTERNAL *) (((char *) EntryDesc) - PtrOffset (EntryDesc));
 *           }
 */

            
            /* !!! FLAT MODEL EQUIVALENT !!! */

            /* Back up to previous entry ?? */

            EntryDesc--;


            /* TBD:  Change to use dump object routine !! */

            DUMP_BUFFER (EntryDesc, sizeof (ACPI_OBJECT_INTERNAL), 0);
            DUMP_BUFFER (++EntryDesc, sizeof (ACPI_OBJECT_INTERNAL), 0);
            DUMP_BUFFER (++EntryDesc, sizeof (ACPI_OBJECT_INTERNAL), 0);
            break;

        }
    }
 
    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlDumpObjStack
 *
 * PARAMETERS:  LoadExecMode        - Load or Exec
 *              *Ident              - Identification
 *              NumLevels           - # of stack entries to dump above line
 *              *Note               - Output notation
 *
 * DESCRIPTION: Dump the object stack
 *
 ****************************************************************************/

void
AmlDumpObjStack (
    OPERATING_MODE          LoadExecMode, 
    char                    *Ident, 
    INT32                   NumLevels, 
    char                    *Note)
{
    UINT32                  CurrentStackTop;
    ACPI_OBJECT_INTERNAL    **EntryDesc;

    
    FUNCTION_TRACE ("AmlDumpObjStack");


    if (!Ident)
    {
        Ident = "?";
    }

    if (!Note)
    {
        Note = "?";
    }

    CurrentStackTop = AmlObjStackLevel ();

    DEBUG_PRINT (ACPI_INFO, ("*************AmlDumpObjStack, TOS=%d******************\n", 
                                CurrentStackTop));
    DEBUG_PRINT (ACPI_INFO, ("%s: %s\n", Ident, Note));

    for (EntryDesc = AmlObjStackGetPtr (STACK_TOP);
          /* exit condition at bottom of loop */ ;
          --EntryDesc, --NumLevels)
    {
        /* 
         * When we have counted NumLevels down to zero, print a line.
         * By convention, callers pass NumLevels as the number of entries
         * which directly relate to the current operation; thus the line
         * separates those entries from any older ones which may be present.
         */
        if (0 == NumLevels)
        {
            DEBUG_PRINT (ACPI_INFO, ("--------\n"));
        }

        /* 
         * Stop dumping when
         *  - AmlDumpObjStackEntry fails on an entry other than the first, or
         *  - the entire stack has been dumped.
         */
        if ((AE_OK != AmlDumpObjStackEntry (*EntryDesc) &&
            AmlObjStackGetPtr (STACK_TOP)    != EntryDesc) || 
            AmlObjStackGetPtr (STACK_BOTTOM) == EntryDesc)
        {
            break;
        }
    }

    return_VOID;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlDumpObjectDescriptor
 *
 * PARAMETERS:  *Object             - Descriptor to dump
 *
 * DESCRIPTION: Dumps the members of the object descriptor given.
 *
 ****************************************************************************/

void
AmlDumpObjectDescriptor (
    ACPI_OBJECT_INTERNAL    *Object)
{
	FUNCTION_TRACE ("AmlDumpObjectDescriptor");
	
	if (!((TRACE_OBJECTS & DebugLevel) && (_COMPONENT & DebugLayer)))
    {
        return;
    }	
	
	switch (Object->Type)
	{
	case TYPE_Number:

		OsdPrintf ("%20s : %s\n", "Type", "Number");
        OsdPrintf ("%20s : %x\n", "Value", Object->Number.Value);
		break;
 
        
	case TYPE_String:

	    OsdPrintf ("%20s : %s\n", "Type", "String");
        OsdPrintf ("%20s : %x\n", "Length", Object->String.Length);
        OsdPrintf ("%20s : %x\n", "Pointer", Object->String.Pointer);
		break;


	case TYPE_Buffer:

		OsdPrintf ("%20s : %s\n", "Type", "Buffer");
		OsdPrintf ("%20s : %x\n", "Length", Object->Buffer.Length);
        OsdPrintf ("%20s : %x\n", "Sequence", Object->Buffer.Sequence);
        OsdPrintf ("%20s : %x\n", "Pointer", Object->Buffer.Pointer);
		break;
        
        
	case TYPE_Package:

		OsdPrintf ("%20s : %s\n", "Type", "Package");
	    OsdPrintf ("%20s : %x\n", "Count", Object->Package.Count);
	    OsdPrintf ("%20s : %x\n", "Elements", Object->Package.Elements);
	    OsdPrintf ("%20s : %x\n", "NextElement", Object->Package.NextElement);
		break;
        

	case TYPE_FieldUnit:

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
        

	case TYPE_Device:

		OsdPrintf ("%20s : %s\n", "Type", "Device");
	    OsdPrintf ("%20s : %x\n", "Handle", Object->Device.Handle);
	    OsdPrintf ("%20s : %p\n", "Handler", Object->Device.Handler);
	    OsdPrintf ("%20s : %p\n", "Context", Object->Device.Context);
        break;


	case TYPE_Event:

		OsdPrintf ("%20s : %s\n", "Type", "Event");
	    OsdPrintf ("%20s : %x\n", "SignalCount", Object->Event.SignalCount);
	    OsdPrintf ("%20s : %x\n", "Semaphore", Object->Event.Semaphore);
	    OsdPrintf ("%20s : %x\n", "LockCount", Object->Event.LockCount);
	    OsdPrintf ("%20s : %x\n", "ThreadId", Object->Event.ThreadId);
	    break;


	case TYPE_Method:

		OsdPrintf ("%20s : %s\n", "Type", "Method");
	    OsdPrintf ("%20s : %x\n", "ParamCount", Object->Method.ParamCount);
	    OsdPrintf ("%20s : %x\n", "Length", Object->Method.Length);
	    OsdPrintf ("%20s : %x\n", "AmlOffset", Object->Method.AmlOffset);
	    OsdPrintf ("%20s : %x\n", "AmlBase", Object->Method.AmlBase);
	    break;
	

	case TYPE_Mutex:

		OsdPrintf ("%20s : %s\n", "Type", "Mutex");
	    OsdPrintf ("%20s : %x\n", "SyncLevel", Object->Mutex.SyncLevel);
	    OsdPrintf ("%20s : %x\n", "Semaphore", Object->Mutex.Semaphore);
	    OsdPrintf ("%20s : %x\n", "LockCount", Object->Mutex.LockCount);
	    OsdPrintf ("%20s : %x\n", "ThreadId", Object->Mutex.ThreadId);
	    break;


	case TYPE_Region:

		OsdPrintf ("%20s : %s\n", "Type", "Region");
	    OsdPrintf ("%20s : %x\n", "SpaceId", Object->Region.SpaceId);
	    OsdPrintf ("%20s : %x\n", "DataValid", Object->Region.DataValid);
	    OsdPrintf ("%20s : %x\n", "Address", Object->Region.Address);
	    OsdPrintf ("%20s : %x\n", "Length", Object->Region.Length);
	    OsdPrintf ("%20s : %x\n", "AddressLocation", Object->Region.AddressLocation);
	    break;


	case TYPE_Power:

		OsdPrintf ("%20s : %s\n", "Type", "PowerResource");
	    OsdPrintf ("%20s : %x\n", "Handle", Object->PowerResource.Handle);
	    break;


	case TYPE_Processor:

		OsdPrintf ("%20s : %s\n", "Type", "Processor");
	    OsdPrintf ("%20s : %x\n", "Handle", Object->Processor.Handle);
	    break;


	case TYPE_Thermal:

		OsdPrintf ("%20s : %s\n", "Type", "ThermalZone");
	    OsdPrintf ("%20s : %x\n", "Handle", Object->ThermalZone.Handle);
	    OsdPrintf ("%20s : %p\n", "Handler", Object->ThermalZone.Handler);
	    OsdPrintf ("%20s : %p\n", "Context", Object->ThermalZone.Context);
	    break;


	case TYPE_BankField:

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


	case TYPE_IndexField:

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


	case TYPE_Lvalue:

		OsdPrintf ("%20s : %s\n", "Type", "Lvalue");
	    OsdPrintf ("%20s : %x\n", "OpCode", Object->Lvalue.OpCode);
	    OsdPrintf ("%20s : %x\n", "Object", Object->Lvalue.Object);
		break;
	

	case TYPE_Alias:
	case TYPE_DefField:
	case TYPE_DefFieldDefn:
	case TYPE_BankFieldDefn:
	case TYPE_IndexFieldDefn:
	case TYPE_If:
	case TYPE_Else:
	case TYPE_While:
	case TYPE_Scope:
	case TYPE_DefAny:

		OsdPrintf ("*** Structure display not implemented for type %d! ***\n",
        	Object->Type);
		break;


	default:

		OsdPrintf ("*** Cannot display unknown type %d! ***\n", Object->Type);
		break;
	}

    return_VOID;
}

