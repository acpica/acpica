
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
 * 2.1. Intel grants, free of charge, to any person ("Licensee") obtaining a 
 * copy of the source code appearing in this file ("Covered Code") a license 
 * under Intel's copyrights in the base code distributed originally by Intel 
 * ("Original Intel Code") to copy, make derivatives, distribute, use and 
 * display any portion of the Covered Code in any form; and
 *
 * 2.2. Intel grants Licensee a non-exclusive and non-transferable patent 
 * license (without the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell, 
 * offer to sell, and import the Covered Code and derivative works thereof 
 * solely to the minimum extent necessary to exercise the above copyright 
 * license, and in no event shall the patent license extend to any additions to
 * or modifications of the Original Intel Code.  No other license or right is 
 * granted directly or by implication, estoppel or otherwise;
 *
 * the above copyright and patent license is granted only if the following 
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of source code of any substantial portion of the Covered 
 * Code or modification must include the above Copyright Notice, the above 
 * License, this list of Conditions, and the following Disclaimer and Export 
 * Compliance provision.  In addition, Licensee must cause all Covered Code to 
 * which Licensee contributes to contain a file documenting the changes 
 * Licensee made to create that Covered Code and the date of any change.  
 * Licensee must include in that file the documentation of any changes made by
 * any predecessor Licensee.  Licensee must include a prominent statement that
 * the modification is derived, directly or indirectly, from Original Intel 
 * Code.
 *
 * 3.2. Redistribution in binary form of any substantial portion of the Covered 
 * Code or modification must reproduce the above Copyright Notice, and the 
 * following Disclaimer and Export Compliance provision in the documentation 
 * and/or other materials provided with the distribution.
 *
 * 3.3. Intel retains all right, title, and interest in and to the Original 
 * Intel Code.
 *
 * 3.4. Neither the name Intel nor any other trademark owned or controlled by 
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
 * event Licensee exports any such software from the United States or re-
 * exports any such software from a foreign destination, Licensee shall ensure
 * that the distribution and export/re-export of the software is in compliance 
 * with all laws, regulations, orders, or other restrictions of the U.S. Export 
 * Administration Regulations. Licensee agrees that neither it nor any of its 
 * subsidiaries will export/re-export any technical data, process, software, or 
 * service, directly or indirectly, to any country for which the United States 
 * government or any agency thereof requires an export license, other 
 * governmental approval, or letter of assurance, without first obtaining such
 * license, approval or letter.
 *
 *****************************************************************************/


#define __ISDUMP_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>
#include <string.h>


#define _THIS_MODULE        "isdump.c"
#define _COMPONENT          INTERPRETER


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", '1', "AmlDumpStackEntry: Unknown OPCODE", "AmlDumpStackEntry: Unknown OPCODE"},
    {"0001", '1', "AmlDumpStackEntry: unknown ValType", "AmlDumpStackEntry: unknown ValType"},
    {NULL, 'I', NULL, NULL}
};


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
DumpBuffer (char *Buffer, UINT32 Count, INT32 Flags, INT32 ComponentId)
{
    UINT32      i = 0;
    UINT32      j;
    UINT8       BufChar;


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

        OsdPrintf (NULL, "%05X    ", i);


        /* Print 16 hex chars */

        for (j = 0; j < 16; j++)
        {
            if (i + j >= Count)
                goto cleanup;


            /* Make sure that the char doesn't get sign-extended! */

            BufChar = Buffer[i + j];
            OsdPrintf (NULL, "%02X ", BufChar);
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

                OsdPrintf (NULL, "%c", BufChar);
            else
                OsdPrintf (NULL, ".");
                
        }

        /* Done with that line. */

        OsdPrintf (NULL, "\n");
        i += 16;
    }

    return;

cleanup:
    OsdPrintf (NULL, "\n");
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
AmlDumpBuffer (size_t NumBytes)
{

    FUNCTION_TRACE ("AmlDumpBuffer");


    DEBUG_PRINT (TRACE_TABLES, ("AML from %p:\n", AmlGetPCodeHandle ()));
    DumpBuffer ((UINT8 *) AmlGetPCodeHandle (), NumBytes, HEX, INTERPRETER);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlDumpStackEntry
 *
 * PARAMETERS:  *EntryDesc          - Pointer to entry to be dumped
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dump a stack entry
 *
 ****************************************************************************/

ACPI_STATUS
AmlDumpStackEntry (OBJECT_DESCRIPTOR *EntryDesc)
{
    char        *OutString = NULL;
    char        *FullyQualifiedName = NULL;
    UINT8       *Buf = NULL;
    UINT16      Length;


    FUNCTION_TRACE ("AmlDumpStackEntry");


    if (!EntryDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlDumpStackEntry: ***NULL stack entry pointer***\n"));
        return AE_AML_ERROR;
    }

    else if (IS_NS_HANDLE (EntryDesc))
    {
        DEBUG_PRINT (ACPI_INFO, ("AmlDumpStackEntry: Name \n"));
        DUMP_ENTRY (EntryDesc);
    }

    else
    {
        /*  EntryDesc is valid  */

        switch (EntryDesc->ValType)
        {
        case TYPE_Lvalue:

            switch (EntryDesc->Lvalue.OpCode)
            {
            case AML_ZeroOp:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Zero\n"));
                break;

            case AML_OneOp:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: One\n"));
                break;

            case AML_OnesOp:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Ones\n"));
                break;

            case Debug1:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Debug\n"));
                break;

            case AML_NameOp:
                NsDumpPathname (EntryDesc->Lvalue.Ref, "Lvalue: Name: ", 
                                ACPI_INFO, _COMPONENT);
                DUMP_ENTRY (EntryDesc->Lvalue.Ref);
                break;
 
            case AML_IndexOp:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Index %p\n",
                            EntryDesc->Lvalue.Ref));
                break;
 
            case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
            case AML_Arg4: case AML_Arg5: case AML_Arg6:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Arg%d\n",
                            EntryDesc->Lvalue.OpCode - AML_Arg0));
                break;

            case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
            case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Local%d\n",
                            EntryDesc->Lvalue.OpCode - AML_Local0));
                break;

            default:
                /*  unknown opcode  */

                REPORT_ERROR (&KDT[0]);
                break;

            }
            break;

        case TYPE_Buffer:
            DEBUG_PRINT (ACPI_INFO, ("Buffer[%d] seq %lx @ %p \n",
                        EntryDesc->Buffer.BufLen, EntryDesc->Buffer.Sequence,
                        EntryDesc->Buffer.Buffer));

            Length = EntryDesc->Buffer.BufLen;

            if (Length > 64)
            {
                Length = 64;
            }

            if (EntryDesc->Buffer.Buffer)
            {
                for (Buf = EntryDesc->Buffer.Buffer; Length--; ++Buf)
                {
                    DEBUG_PRINT (ACPI_INFO,
                                (Length ? " %02x" : " %02x", *Buf));
                }
            }

            break;

        case TYPE_Number:
            DEBUG_PRINT (ACPI_INFO, ("Number 0x%lx\n",
                        EntryDesc->Number.Number));
            break;

        case TYPE_If:
            DEBUG_PRINT (ACPI_INFO, ("If [Number] 0x%lx\n",
                        EntryDesc->Number.Number));
            break;

        case TYPE_While:
            DEBUG_PRINT (ACPI_INFO, ("While [Number] 0x%lx\n",
                        EntryDesc->Number.Number));
            break;

        case TYPE_Package:
            DEBUG_PRINT (ACPI_INFO, ("Package[%d] @ %p\n",
                        EntryDesc->Package.PkgCount, EntryDesc->Package.PackageElems));


            /* 
             * If elements exist, package vector pointer is valid,
             * and debug_level exceeds 1, dump package's elements.
             */
            if (EntryDesc->Package.PkgCount &&
                EntryDesc->Package.PackageElems &&
                GetDebugLevel () > 1)
            {
                OBJECT_DESCRIPTOR   **Element;
                UINT16              ElementIndex;

                for (ElementIndex = 0, Element = EntryDesc->Package.PackageElems;
                      ElementIndex < EntryDesc->Package.PkgCount;
                      ++ElementIndex, ++Element)
                {
                    AmlDumpStackEntry (*Element);
                }
            }

            DEBUG_PRINT (ACPI_INFO, ("\n"));

            break;

        case TYPE_Region:
            if (OUTRANGE (EntryDesc->Region.SpaceId, RegionTypes))
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
            if (0 == EntryDesc->Region.AdrLenValid)
            {
                DEBUG_PRINT (ACPI_INFO, ("Region %s\n", OutString));
            }
            else
            {
                DEBUG_PRINT (ACPI_INFO,
                            ("Region %s base %08lx Length %08lx\n", OutString,
                            EntryDesc->Region.Address, EntryDesc->Region.Length));
            }
            break;

        case TYPE_String:
            DEBUG_PRINT (ACPI_INFO, ("String[%d] @ %p\n",
                        EntryDesc->String.StrLen, EntryDesc->String.String));
            break;

        case TYPE_BankField:
            DEBUG_PRINT (ACPI_INFO, ("BankField\n"));
            break;

        case TYPE_DefField:
            DEBUG_PRINT (ACPI_INFO,
                        ("DefField: %d bits acc %d lock %d update %d at byte %lx bit %d of \n",
                        EntryDesc->Field.DatLen,   EntryDesc->Field.Access,
                        EntryDesc->Field.LockRule, EntryDesc->Field.UpdateRule,
                        EntryDesc->Field.Offset,   EntryDesc->Field.BitOffset));
            DUMP_STACK_ENTRY (EntryDesc->Field.Container);
            break;

        case TYPE_IndexField:
            DEBUG_PRINT (ACPI_INFO, ("IndexField\n"));
            break;

        case TYPE_FieldUnit:
            DEBUG_PRINT (ACPI_INFO,
                        ("FieldUnit: %d bits acc %d lock %d update %d at byte %lx bit %d of \n",
                        EntryDesc->FieldUnit.DatLen,   EntryDesc->FieldUnit.Access,
                        EntryDesc->FieldUnit.LockRule, EntryDesc->FieldUnit.UpdateRule,
                        EntryDesc->FieldUnit.Offset,   EntryDesc->FieldUnit.BitOffset));

            if (!EntryDesc->FieldUnit.Container)
            {
                DEBUG_PRINT (ACPI_INFO, ("*NULL* \n"));
            }
            else if (TYPE_Buffer != EntryDesc->FieldUnit.Container->ValType)
            {
                DEBUG_PRINT (ACPI_INFO, ("*not a Buffer* \n"));
            }
            else
            {
                if (EntryDesc->FieldUnit.ConSeq
                        != EntryDesc->FieldUnit.Container->Buffer.Sequence)
                {
                    DEBUG_PRINT (ACPI_INFO,
                                  ("[stale] %lx \n", EntryDesc->FieldUnit.ConSeq));
                }

                DUMP_STACK_ENTRY (EntryDesc->FieldUnit.Container);
            }
            break;

        case TYPE_Event:
            DEBUG_PRINT (ACPI_INFO, ("Event\n"));
            break;

        case TYPE_Method:
            DEBUG_PRINT (ACPI_INFO,
                        ("Method(%d) @ %p:%lx:%lx\n",
                        EntryDesc->Method.NumParam, EntryDesc->Method.AmlBase,
                        EntryDesc->Method.AmlOffset, EntryDesc->Method.Length));
            break;

        case TYPE_Mutex:
            DEBUG_PRINT (ACPI_INFO, ("Mutex\n"));
            break;

        case TYPE_Device:
            DEBUG_PRINT (ACPI_INFO, ("Device\n"));
            break;

        case TYPE_Power:
            DEBUG_PRINT (ACPI_INFO, ("Power\n"));
            break;

        case TYPE_Processor:
            DEBUG_PRINT (ACPI_INFO, ("Processor\n"));
            break;

        case TYPE_Thermal:
            DEBUG_PRINT (ACPI_INFO, ("Thermal\n"));
            break;

        default:
            /*  unknown EntryDesc->ValType value    */

            REPORT_ERROR (&KDT[0]);
            
            if (AML_UNASSIGNED != Aml[(INT32) EntryDesc->ValType])
            {
                DEBUG_PRINT (ACPI_ERROR,
                              ("AmlDumpStackEntry: Unhandled opcode (AML %s) \n", 
                              ShortOps[Aml[(INT32) EntryDesc->ValType]]));
            }


            /* !!!! POINTER STUFF COMMENTED OUT !!!! */

/*
 *           if (PtrOffset (EntryDesc) > sizeof (OBJECT_DESCRIPTOR))
 *           {
 *               --EntryDesc;
 *           }
 *           else
 *           {
 *               EntryDesc = (OBJECT_DESCRIPTOR *) (((char *) EntryDesc) - PtrOffset (EntryDesc));
 *           }
 */

            
            /* !!! FLAT MODEL EQUIVALENT !!! */

            /* Back up to previous entry ?? */

            EntryDesc--;


            /* TBD:  Change to use dump object routine !! */

            DUMP_BUFFER (EntryDesc, sizeof (OBJECT_DESCRIPTOR), 0);
            DUMP_BUFFER (++EntryDesc, sizeof (OBJECT_DESCRIPTOR), 0);
            DUMP_BUFFER (++EntryDesc, sizeof (OBJECT_DESCRIPTOR), 0);
            break;

        }
    }
 
    return AE_OK;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlDumpStack
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
AmlDumpStack (OpMode LoadExecMode, char *Ident, INT32 NumLevels, char *Note)
{
    OBJECT_DESCRIPTOR   **EntryDesc;

    
    FUNCTION_TRACE ("AmlDumpStack");


    if (!Ident)
    {
        Ident = "?";
    }

    if (!Note)
    {
        Note = "?";
    }

    DEBUG_PRINT (ACPI_INFO,
                ("*******************AmlDumpStack***********************\n"));
    DEBUG_PRINT (ACPI_INFO, ("%s: %s\n", Ident, Note));

    for (EntryDesc = (OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop] ;
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
         *  - AmlDumpStackEntry fails on an entry other than the first, or
         *  - the entire stack has been dumped.
         */
        if ((AE_OK != AmlDumpStackEntry (*EntryDesc) &&
            (OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop] != EntryDesc) || 
            (OBJECT_DESCRIPTOR **) &ObjStack[0] == EntryDesc)
        {
            break;
        }
    }
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
AmlDumpObjectDescriptor (OBJECT_DESCRIPTOR *Object)
{
	
	FUNCTION_TRACE ("AmlDumpObjectDescriptor");
		
	switch (Object->ValType)
	{
	case TYPE_Number:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Number"));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Number.Reserved1));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Number.Reserved2));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Number", Object->Number.Number));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Number.Reserved3));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Number.Reserved4));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->Number.Reserved5));
		break;
    
	case TYPE_String:

	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "String"));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->String.Reserved1));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "StrLen", Object->String.StrLen));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->String.Reserved2));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->String.Reserved3));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "String", Object->String.String));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->String.Reserved4));
		break;

	case TYPE_Buffer:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Buffer"));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Buffer.Reserved1));
		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "BufLen", Object->Buffer.BufLen));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Buffer.Reserved2));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Sequence", Object->Buffer.Sequence));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Buffer", Object->Buffer.Buffer));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Buffer.Reserved4));
		break;
        
        
	case TYPE_Package:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Package"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Package.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "PkgCount", Object->Package.PkgCount));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Package.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Package.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "PackageElems", Object->Package.PackageElems));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "NextElement", Object->Package.NextElement));
		break;
        
	case TYPE_FieldUnit:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "FieldUnit"));
		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Access", Object->FieldUnit.Access));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "LockRule", Object->FieldUnit.LockRule));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "UpdateRule", Object->FieldUnit.UpdateRule));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->FieldUnit.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "DatLen", Object->FieldUnit.DatLen));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "BitOffset", Object->FieldUnit.BitOffset));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Offset", Object->FieldUnit.Offset));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "ConSeq", Object->FieldUnit.ConSeq));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Container", Object->FieldUnit.Container));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->FieldUnit.Reserved3));
	    break;
        
	case TYPE_Device:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Device"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Device.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Device.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Device.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Device.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Device", Object->Device.Device));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->Device.Reserved5));
        break;

	case TYPE_Event:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Event"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Event.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "SignalCount", Object->Event.SignalCount));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Semaphore", Object->Event.Semaphore));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "LockCount", Object->Event.LockCount));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "ThreadId", Object->Event.ThreadId));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Event.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->Event.Reserved5));
	    break;

	case TYPE_Method:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Method"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "NumParam", Object->Method.NumParam));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Length", Object->Method.Length));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "AmlOffset", Object->Method.AmlOffset));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Method.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "AmlBase", Object->Method.AmlBase));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Method.Reserved4));
	    break;
	
	case TYPE_Mutex:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Mutex"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "SyncLevel", Object->Mutex.SyncLevel));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Mutex.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Semaphore", Object->Mutex.Semaphore));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "LockCount", Object->Mutex.LockCount));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "ThreadId", Object->Mutex.ThreadId));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Mutex.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->Mutex.Reserved5));
	    break;

	case TYPE_Region:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Region"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "SpaceId", Object->Region.SpaceId));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "AdrLenValid", Object->Region.AdrLenValid));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Address", Object->Region.Address));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Length", Object->Region.Length));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "AdrLoc", Object->Region.AdrLoc));
	    break;

	case TYPE_Power:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "PowerResource"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->PowerResource.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->PowerResource.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->PowerResource.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->PowerResource.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "PowerResource", Object->PowerResource.PowerResource));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->PowerResource.Reserved5));
	    break;

	case TYPE_Processor:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Processor"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Processor.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Processor.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Processor.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Processor.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Processor", Object->Processor.Processor));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->Processor.Reserved5));
	    break;

	case TYPE_Thermal:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "ThermalZone"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->ThermalZone.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->ThermalZone.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->ThermalZone.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->ThermalZone.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "ThermalZone", Object->ThermalZone.ThermalZone));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->ThermalZone.Reserved5));
	    break;

	case TYPE_BankField:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "BankField"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Access", Object->BankField.Access));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "LockRule", Object->BankField.LockRule));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "UpdateRule", Object->BankField.UpdateRule));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->BankField.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "DatLen", Object->BankField.DatLen));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "BitOffset", Object->BankField.BitOffset));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Offset", Object->BankField.Offset));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "BankVal", Object->BankField.BankVal));
		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Container", Object->BankField.Container));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "BankSelect", Object->BankField.BankSelect));
	    break;

	case TYPE_IndexField:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "IndexField"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Access", Object->IndexField.Access));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "LockRule", Object->IndexField.LockRule));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "UpdateRule", Object->IndexField.UpdateRule));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->IndexField.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "DatLen", Object->IndexField.DatLen));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "BitOffset", Object->IndexField.BitOffset));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "IndexVal", Object->IndexField.IndexVal));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->IndexField.Reserved2));
		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Index", Object->IndexField.Index));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Data", Object->IndexField.Data));
	    break;

	case TYPE_Lvalue:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Lvalue"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "OpCode", Object->Lvalue.OpCode));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Lvalue.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Lvalue.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Lvalue.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Ref", Object->Lvalue.Ref));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Lvalue.Reserved4));
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

		DEBUG_PRINT (ACPI_ERROR, ("*** Structure display not implemented for type %d! ***\n",
                        Object->ValType));
		break;


	default:

		DEBUG_PRINT (ACPI_ERROR, ("*** Cannot display unknown type %d! ***\n", Object->ValType));
		break;
	}

}


