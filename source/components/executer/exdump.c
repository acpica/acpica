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

VOID
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

    DEBUG_PRINT (ACPI_INFO, ("Hex dump of remainder of AML package:\n"));

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


    DEBUG_PRINT (ACPI_INFO, ("AML from %p:\n", PCodeHandle ()));
    DumpBuffer ((UINT8 *) PCodeHandle (), NumBytes, HEX);
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

#ifdef VERBOSE_DEBUG
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

                (VOID) IncIndent ();

                for (ElementIndex = 0, Element = EntryDesc->Package.PackageElems;
                      ElementIndex < EntryDesc->Package.PkgCount;
                      ++ElementIndex, ++Element)
                {
                    DumpStackEntry (*Element);
                }
           
                DecIndent ();
            }
#endif
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

VOID
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

