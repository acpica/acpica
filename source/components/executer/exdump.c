/*__________________________________________________________________________
 |
 |
 |               Copyright (C) Intel Corporation 1994-1996
 |
 | All rights reserved.  No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | ModuleName: isdump.c - Scanner debug output routines
 |__________________________________________________________________________
*/



#define __ISDUMP_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>
#include <string.h>


#define _THIS_MODULE        "isdump.c"
#define _COMPONENT          INTERPRETER


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", '1', "DumpStackEntry: Unknown OPCODE", "DumpStackEntry: Unknown OPCODE"},
    {"0001", '1', "DumpStackEntry: unknown ValType", "DumpStackEntry: unknown ValType"},
    {NULL, 'I', NULL, NULL}
};


/*****************************************************************************
 * 
 * FUNCTION:    DumpBuffer
 *
 * RETURN:      none
 *
 * DESCRIPTION: Generic dump buffer in hex and ascii.
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


/******************************************************************************
 * 
 * FUNCTION:    DumpCode
 *
 * PARAMETERS:  OpMode LoadExecMode        Load or Exec -- controls printing
 *
 * DESCRIPTION: Consume and dump the remainder of the current code package.
 *              Characters which may legally appear in a name are printed
 *              as such; everything else is printed in hex.
 *
 *****************************************************************************/

void
DumpCode (OpMode LoadExecMode)
{
    UINT8           *Code;
    UINT32          i = 0;
    UINT32          j = 0;
    UINT8           LineBuf[16];


    FUNCTION_TRACE ("DumpCode");

    /* Only dump the code if tracing is enabled */

    if (!(TRACE_TABLES & DebugLevel))
    {
        return;
    }

    DEBUG_PRINT (TRACE_TABLES, ("Hex dump of remainder of AML package:\n"));

    /* dump the package, but not too much of it */

    while ((Code = ConsumeAMLByte (1)) && (j < 1024))
    {
        OsdPrintf (NULL, "%02X ", *Code);
        LineBuf[i] = *Code;

        i++;
        j++;
        if (i > 15)
        {
            for (i = 0; i < 16; i++)
            {
                if (NcOK ((INT32) LineBuf[i]))
                {
                    OsdPrintf (NULL, "%c", LineBuf[i]);
                }

                else
                {
                    OsdPrintf (NULL, ".");
                }
            }

            /* Done with that line. */

            OsdPrintf (NULL, "\n");
            i = 0;
        }
    }

    OsdPrintf (NULL, "\n");
}


/****************************************************************************
 * 
 * FUNCTION:    DumpAMLBuffer
 *
 * PARAMETERS:  size_t  NumBytes    number of AML stream bytes to dump
 *
 * DESCRIPTION: Hex display current AML without consuming the bytes
 *
 ***************************************************************************/

void
DumpAMLBuffer (size_t NumBytes)
{

    FUNCTION_TRACE ("DumpAMLBuffer");


    DEBUG_PRINT (TRACE_TABLES, ("AML from %p:\n", PCodeHandle ()));
    DumpBuffer ((UINT8 *) PCodeHandle (), NumBytes, HEX, INTERPRETER);
}


/*****************************************************************************
 * 
 * FUNCTION:    DumpStackEntry
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *EntryDesc    ptr to SE to be dumped
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Dump a stack entry
 *
 ****************************************************************************/

INT32
DumpStackEntry (OBJECT_DESCRIPTOR *EntryDesc)
{
    char        *OutString = NULL;
    char        *FullyQualifiedName = NULL;
    UINT8       *Buf = NULL;
    UINT16      Length;


    FUNCTION_TRACE ("DumpStackEntry");


    if (!EntryDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("***NULL stack entry pointer***\n"));
        return S_ERROR;
    }

    else if (IsNsHandle (EntryDesc))
    {
        DEBUG_PRINT (ACPI_INFO, ("Name \n"));
        DUMP_ENTRY (EntryDesc);
    }

    else
    {
        /*  EntryDesc is valid  */

        switch (EntryDesc->ValType)
        {
        case Lvalue:

            switch (EntryDesc->Lvalue.OpCode)
            {
            case ZeroOp:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Zero\n"));
                break;

            case OneOp:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: One\n"));
                break;

            case OnesOp:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Ones\n"));
                break;

            case Debug1:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Debug\n"));
                break;

            case NameOp:
                FullyQualifiedName = NsFullyQualifiedName
                                        (EntryDesc->Lvalue.Ref);

                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Name %s\n            ",
                                FullyQualifiedName ? FullyQualifiedName : "invalid"));
                DUMP_ENTRY (EntryDesc->Lvalue.Ref);
                break;
 
            case IndexOp:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Index %p\n",
                            EntryDesc->Lvalue.Ref));
                break;
 
            case Arg0: case Arg1: case Arg2: case Arg3:
            case Arg4: case Arg5: case Arg6:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Arg%d\n",
                            EntryDesc->Lvalue.OpCode - Arg0));
                break;

            case Local0: case Local1: case Local2: case Local3:
            case Local4: case Local5: case Local6: case Local7:
                DEBUG_PRINT (ACPI_INFO, ("Lvalue: Local%d\n",
                            EntryDesc->Lvalue.OpCode - Local0));
                break;

            default:
                /*  unknown opcode  */

                REPORT_ERROR (&KDT[0]);
                break;

            }
            break;

        case Buffer:
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

        case Number:
            DEBUG_PRINT (ACPI_INFO, ("Number 0x%lx\n",
                        EntryDesc->Number.Number));
            break;

        case If:
            DEBUG_PRINT (ACPI_INFO, ("If [Number] 0x%lx\n",
                        EntryDesc->Number.Number));
            break;

        case While:
            DEBUG_PRINT (ACPI_INFO, ("While [Number] 0x%lx\n",
                        EntryDesc->Number.Number));
            break;

        case Package:
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

                (void) IncIndent ();

                for (ElementIndex = 0, Element = EntryDesc->Package.PackageElems;
                      ElementIndex < EntryDesc->Package.PkgCount;
                      ++ElementIndex, ++Element)
                {
                    DumpStackEntry (*Element);
                }
           
                DecIndent ();
            }

            DEBUG_PRINT (ACPI_INFO, ("\n"));

            break;

        case Region:
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

        case String:
            DEBUG_PRINT (ACPI_INFO, ("String[%d] @ %p\n",
                        EntryDesc->String.StrLen, EntryDesc->String.String));
            break;

        case BankField:
            DEBUG_PRINT (ACPI_INFO, ("BankField\n"));
            break;

        case DefField:
            DEBUG_PRINT (ACPI_INFO,
                        ("DefField: %d bits acc %d lock %d update %d at byte %lx bit %d of \n",
                        EntryDesc->Field.DatLen,   EntryDesc->Field.Access,
                        EntryDesc->Field.LockRule, EntryDesc->Field.UpdateRule,
                        EntryDesc->Field.Offset,   EntryDesc->Field.BitOffset));
            IncIndent ();
            DUMP_STACK_ENTRY (EntryDesc->Field.Container);
            DecIndent ();
            break;

        case IndexField:
            DEBUG_PRINT (ACPI_INFO, ("IndexField\n"));
            break;

        case FieldUnit:
            DEBUG_PRINT (ACPI_INFO,
                        ("FieldUnit: %d bits acc %d lock %d update %d at byte %lx bit %d of \n",
                        EntryDesc->FieldUnit.DatLen,   EntryDesc->FieldUnit.Access,
                        EntryDesc->FieldUnit.LockRule, EntryDesc->FieldUnit.UpdateRule,
                        EntryDesc->FieldUnit.Offset,   EntryDesc->FieldUnit.BitOffset));

            if (!EntryDesc->FieldUnit.Container)
            {
                DEBUG_PRINT (ACPI_INFO, ("*NULL* \n"));
            }
            else if (Buffer != EntryDesc->FieldUnit.Container->ValType)
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

                IncIndent ();
                DUMP_STACK_ENTRY (EntryDesc->FieldUnit.Container);
                DecIndent ();
            }
            break;

        case Event:
            DEBUG_PRINT (ACPI_INFO, ("Event\n"));
            break;

        case Method:
            DEBUG_PRINT (ACPI_INFO,
                        ("Method(%d) @ %p:%lx:%lx\n",
                        EntryDesc->Method.NumParam, EntryDesc->Method.AmlBase,
                        EntryDesc->Method.AmlOffset, EntryDesc->Method.Length));
            break;

        case Mutex:
            DEBUG_PRINT (ACPI_INFO, ("Mutex\n"));
            break;

        case Device:
            DEBUG_PRINT (ACPI_INFO, ("Device\n"));
            break;

        case Power:
            DEBUG_PRINT (ACPI_INFO, ("Power\n"));
            break;

        case Processor:
            DEBUG_PRINT (ACPI_INFO, ("Processor\n"));
            break;

        case Thermal:
            DEBUG_PRINT (ACPI_INFO, ("Thermal\n"));
            break;

        default:
            /*  unknown EntryDesc->ValType value    */

            REPORT_ERROR (&KDT[0]);
            
            if (UNASSIGNED != Aml[(INT32) EntryDesc->ValType])
            {
                DEBUG_PRINT (ACPI_ERROR,
                              ("(AML %s) \n", ShortOps[Aml[(INT32) EntryDesc->ValType]]));
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
 
    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    DumpStack
 *
 * PARAMETERS:  OpMode    LoadExecMode      Load or Exec
 *              char      *Ident            Identification
 *              INT32     NumLevels         # of stack entries to dump above line
 *              char      *Note             Output notation
 *
 * DESCRIPTION: Dump the object stack
 *
 ****************************************************************************/

void
DumpStack (OpMode LoadExecMode, char *Ident, INT32 NumLevels, char *Note)
{
    OBJECT_DESCRIPTOR   **EntryDesc;

    
    FUNCTION_TRACE ("DumpStack");


    if (!Ident)
    {
        Ident = "?";
    }

    if (!Note)
    {
        Note = "?";
    }

    DEBUG_PRINT (ACPI_INFO,
                ("*******************DumpStack***********************\n"));
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
         *  - DumpStackEntry fails on an entry other than the first, or
         *  - the entire stack has been dumped.
         */
        if ((S_SUCCESS != DumpStackEntry (*EntryDesc) &&
            (OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop] != EntryDesc) || 
            (OBJECT_DESCRIPTOR **) &ObjStack[0] == EntryDesc)
        {
            break;
        }
    }
}


/*****************************************************************************
 * 
 * FUNCTION:    DumpObjectDescriptor
 *
 * DESCRIPTION: Dumps the members of the object descriptor given.
 *
 ****************************************************************************/

void
DumpObjectDescriptor (OBJECT_DESCRIPTOR *Object)
{
	
	FUNCTION_TRACE ("DumpObjectDescriptor");

		
	switch (Object->ValType)
	{
	case Number:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Number"));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Number.Reserved1));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Number.Reserved2));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Number", Object->Number.Number));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Number.Reserved3));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Number.Reserved4));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->Number.Reserved5));
		break;
    
	case String:

	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "String"));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->String.Reserved1));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "StrLen", Object->String.StrLen));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->String.Reserved2));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->String.Reserved3));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "String", Object->String.String));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->String.Reserved4));
		break;

	case Buffer:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Buffer"));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Buffer.Reserved1));
		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "BufLen", Object->Buffer.BufLen));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Buffer.Reserved2));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Sequence", Object->Buffer.Sequence));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Buffer", Object->Buffer.Buffer));
        DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Buffer.Reserved4));
		break;
        
        
	case Package:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Package"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Package.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "PkgCount", Object->Package.PkgCount));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Package.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Package.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "PackageElems", Object->Package.PackageElems));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "NextElement", Object->Package.NextElement));
		break;
        
	case FieldUnit:

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
        
	case Device:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Device"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Device.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Device.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Device.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Device.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Device", Object->Device.Device));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->Device.Reserved5));
        break;

	case Event:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Event"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Event.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "SignalCount", Object->Event.SignalCount));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Semaphore", Object->Event.Semaphore));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "LockCount", Object->Event.LockCount));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "ThreadId", Object->Event.ThreadId));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Event.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->Event.Reserved5));
	    break;

	case Method:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Method"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "NumParam", Object->Method.NumParam));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Length", Object->Method.Length));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "AmlOffset", Object->Method.AmlOffset));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Method.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "AmlBase", Object->Method.AmlBase));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Method.Reserved4));
	    break;
	
	case Mutex:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Mutex"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "SyncLevel", Object->Mutex.SyncLevel));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Mutex.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Semaphore", Object->Mutex.Semaphore));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "LockCount", Object->Mutex.LockCount));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "ThreadId", Object->Mutex.ThreadId));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Mutex.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->Mutex.Reserved5));
	    break;

	case Region:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Region"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "SpaceId", Object->Region.SpaceId));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "AdrLenValid", Object->Region.AdrLenValid));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Address", Object->Region.Address));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Length", Object->Region.Length));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "AdrLoc", Object->Region.AdrLoc));
	    break;

	case Power:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "PowerResource"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->PowerResource.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->PowerResource.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->PowerResource.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->PowerResource.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "PowerResource", Object->PowerResource.PowerResource));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->PowerResource.Reserved5));
	    break;

	case Processor:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Processor"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Processor.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Processor.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Processor.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Processor.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Processor", Object->Processor.Processor));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->Processor.Reserved5));
	    break;

	case Thermal:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "ThermalZone"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->ThermalZone.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->ThermalZone.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->ThermalZone.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->ThermalZone.Reserved4));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "ThermalZone", Object->ThermalZone.ThermalZone));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved5", Object->ThermalZone.Reserved5));
	    break;

	case BankField:

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

	case IndexField:

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

	case Lvalue:

		DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %s\n", "ValType", "Lvalue"));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "OpCode", Object->Lvalue.OpCode));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved1", Object->Lvalue.Reserved1));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved2", Object->Lvalue.Reserved2));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved3", Object->Lvalue.Reserved3));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Ref", Object->Lvalue.Ref));
	    DEBUG_PRINT (TRACE_OBJECTS, ("%20s : %x\n", "Reserved4", Object->Lvalue.Reserved4));
		break;
	
	case Alias:
	case DefField:
	case DefFieldDefn:
	case BankFieldDefn:
	case IndexFieldDefn:
	case If:
	case Else:
	case While:
	case Scope:
	case DefAny:

		DEBUG_PRINT (ACPI_ERROR, ("*** Structure display not implemented for type %d! ***\n",
                        Object->ValType));
		break;


	default:

		DEBUG_PRINT (ACPI_ERROR, ("*** Cannot display unknown type %d! ***\n", Object->ValType));
		break;
	}

}


