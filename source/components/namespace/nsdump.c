/*_________________________________________________________________________
 |
 |
 |           Copyright (C) Intel Corporation 1994-1997
 |
 | All rights reserved.  No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | ModuleName: nsdump - table dumping routines for debug
 |__________________________________________________________________________
*/

#define __NSDUMP_C__

#include <acpi.h>
#include <interpreter.h>
#include <namespace.h>


#define _THIS_MODULE        "nsdump.c"
#define _COMPONENT          NAMESPACE


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", '1', "Invalid Name", "Invalid Name"},
    {NULL, 'I', NULL, NULL}
};



/****************************************************************************
 * 
 * FUNCTION:    NsDumpTable
 *
 * PARAMETERS:  nte *ThisEntry              table to be dumped
 *              INT32 Size                  size of table
 *              INT32 Level                 Number of ancestor levels
 *              INT32 MaxDepth              See description in NsDumpTables()
 *
 * DESCRIPTION: Dump a name table and its descendents
 *
 ***************************************************************************/

static void
NsDumpTable (nte *ThisEntry, INT32 Size, INT32 Level, INT32 MaxDepth)
{
    nte                 *Appendage;
    UINT32              DownstreamSiblingMask = 0;
    INT32               LevelTmp;
    NsType              Type;
    UINT32              WhichBit;


    FUNCTION_TRACE ("NsDumpTable");


    /* Only dump the table if tracing is enabled */

    if (!(TRACE_TABLES & DebugLevel))
    {
        return;
    }


    if (0 == MaxDepth || !ThisEntry)
    {
        /* reached requested depth, or nothing to dump */
        
        return;
    }


    /* Locate appendage, if any, before losing original scope pointer */
    
    if (1 == Size)
    {
        Appendage = NULL;
    }
    else
    {
        Appendage = NEXTSEG (ThisEntry);
    }


    /* for each entry in table */
    
    while (Size--)
    {
        if (ThisEntry->NameSeg)
        {
            LevelTmp    = Level;
            Type        = ThisEntry->NtType;
            WhichBit    = 1;


            /* non-empty entry */
            /* print appropriate graphic characters to form tree structure */
            
            while (LevelTmp--)
            {
                /*  print appropriate graphic characters to form tree structure */

                if (LevelTmp)
                {
                    if (DownstreamSiblingMask & WhichBit)
                    {    
                        DEBUG_PRINT_RAW (TRACE_TABLES, ("| "));
                    }
                    
                    else
                    {
                        DEBUG_PRINT_RAW (TRACE_TABLES, ("  "));
                    }
                    
                    WhichBit <<= 1;
                }
                
                else
                {
                    if (ExistDownstreamSibling (ThisEntry + 1, Size, Appendage))
                    {
                        DownstreamSiblingMask |= (1 << (Level - 1));
                        DEBUG_PRINT_RAW (TRACE_TABLES, ("+-"));
                    }
                    
                    else
                    {
                        DownstreamSiblingMask &= 0xffffffff ^ (1 << (Level - 1));
                        DEBUG_PRINT_RAW (TRACE_TABLES, ("+-"));
                    }

                    if (ThisEntry->ChildScope == NULL)
                    {
                        DEBUG_PRINT_RAW (TRACE_TABLES, ("- "));
                    }
                    
                    else if (ExistDownstreamSibling (ThisEntry->ChildScope, TABLSIZE,
                                                        NEXTSEG (ThisEntry->ChildScope)))
                    {
                        DEBUG_PRINT_RAW (TRACE_TABLES, ("+ "));
                    }
                    
                    else
                    {
                        DEBUG_PRINT_RAW (TRACE_TABLES, ("- "));
                    }
                }
            }

            if (OUTRANGE (Type, NsTypeNames))
            {
                Type = DefAny;                                 /* prints as *ERROR* */
            }
            
            if (!NcOK ((INT32)* (char *) &ThisEntry->NameSeg))
            {
                REPORT_WARNING (&KDT[0]);
            }

            if (Method == Type && ThisEntry->ptrVal)
            {
                /* name is a Method and its AML offset/length are set */
                
                
                DEBUG_PRINT_RAW (TRACE_TABLES,
                            ("%4.4s [%8.8s] ", &ThisEntry->NameSeg, NsTypeNames[Type]));
                
                DEBUG_PRINT_RAW (TRACE_TABLES, ("N:%p", ThisEntry));
                
                DEBUG_PRINT_RAW (TRACE_TABLES, (" C:%p P:%p",
                        ThisEntry->ChildScope, ThisEntry->ParentScope));

                DEBUG_PRINT_RAW (TRACE_TABLES, (" At: %04x(%04lx)\n",
                            ((meth *) ThisEntry->ptrVal)->Offset,
                            ((meth *) ThisEntry->ptrVal)->Length));                
            }
            
            else
            {
                UINT8           *Value = ThisEntry->ptrVal;


                /* name is not a Method, or the AML offset/length are not set */
                
                DEBUG_PRINT_RAW (TRACE_TABLES,
                            ("%4.4s [%8.8s] ", &ThisEntry->NameSeg, NsTypeNames[Type]));
                
                DEBUG_PRINT_RAW (TRACE_TABLES, ("N:%p", ThisEntry));
                
                DEBUG_PRINT_RAW (TRACE_TABLES, (" C:%p P:%p V:%p\n",
                            ThisEntry->ChildScope, ThisEntry->ParentScope, ThisEntry->ptrVal));

#if 0
                /* debug code used to show parents */
                
                if ((IndexField == Type) && (0 == Size) && (0 == Level) &&
                    ThisEntry->ParentScope)
                {
                    DEBUG_PRINT_RAW (TRACE_TABLES, ("  in "));
                    ++TRACE;
                    DEBUG_PRINT_RAW (TRACE_TABLES,
                                ("call NsDumpEntry %p\n", ThisEntry->ParentScope));
                    
                    NsDumpEntry ((NsHandle) ThisEntry->ParentScope, DisplayBitFlags);
                    DEBUG_PRINT_RAW (TRACE_TABLES,
                                ("ret from NsDumpEntry %p\n", ThisEntry->ParentScope));
                    --TRACE;
                }
#endif
                /* if debug turned on, display values */
                
                while (Value && (DebugLevel & TRACE_VALUES))
                {
                    UINT8               bT = ((OBJECT_DESCRIPTOR *) Value)->ValType;


                    DEBUG_PRINT_RAW (TRACE_TABLES,
                                ("                 %p  %02x %02x %02x %02x %02x %02x",
                                Value, Value[0], Value[1], Value[2], Value[3], Value[4],
                                Value[5]));
                    DEBUG_PRINT_RAW (TRACE_TABLES,
                                (" %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
                                Value[6], Value[7], Value[8], Value[9], Value[10],
                                Value[11], Value[12], Value[13], Value[14], Value[15]));
                    
                    if (bT == String || bT == Buffer || bT == Package
                     || bT == FieldUnit || bT == DefField || bT == BankField
                     || bT == IndexField || bT == Lvalue)
                    {
                        /* 
                         * Get pointer to next level.  ThisEntry assumes that all of
                         * the above-listed variants of OBJECT_DESCRIPTOR have
                         * compatible mappings.
                         */
                        Value = ((OBJECT_DESCRIPTOR *)Value)->Buffer.Buffer;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (ThisEntry->ChildScope && MaxDepth > 1)
            {
                /* dump next scope level */
                
                NsDumpTable (ThisEntry->ChildScope, TABLSIZE, Level+1,
                                MaxDepth - 1);
            }
        }

        if (0 == Size && Appendage)
        {
            /* Just examined last entry, but table has an appendage.  */
            
            ThisEntry = Appendage;
            Size += TABLSIZE;
            Appendage = NEXTSEG (ThisEntry);
        }
        else
        {
            ThisEntry++;
        }
    }



    DEBUG_PRINT (TRACE_EXEC, ("leave NsDumpTable %p\n", ThisEntry));
}


/****************************************************************************
 * 
 * FUNCTION:    NsDumpTables
 *
 * PARAMETERS:  NsHandle SearchBase         Root of subtree to be dumped, or
 *                                          NS_ALL to dump the entire namespace
 *              INT32   MaxDepth            Maximum depth of dump.  Use INT_MAX
 *                                          for an effectively unlimited depth.
 *
 * DESCRIPTION: Dump the name space, or a portion of it.
 *
 ***************************************************************************/

void
NsDumpTables (NsHandle SearchBase, INT32 MaxDepth)
{

    FUNCTION_TRACE ("NsDumpTables");


    if (!Root)
    {      
        /* 
         * If the name space has not been initialized,
         * there is nothing to dump.
         */
        DEBUG_PRINT (TRACE_TABLES, ("NsDumpTables: name space not initialized!\n"));
        return;
    }

    if (NS_ALL == SearchBase)
    {
        /*  entire namespace    */

        SearchBase = Root;
        DEBUG_PRINT (TRACE_TABLES, ("\\\n"));
    }

    NsDumpTable (SearchBase, SearchBase == Root ? NsRootSize : TABLSIZE,
                    1, MaxDepth);
}


/****************************************************************************
 *
 * FUNCTION:    NsDumpEntry    
 *
 * PARAMETERS:  NsHandle Handle          Entry to be dumped
 *
 * DESCRIPTION: Dump a single nte
 *
 ***************************************************************************/

void
NsDumpEntry (NsHandle Handle)
{

    FUNCTION_TRACE ("NsDumpEntry");

    
    NsDumpTable ((nte *) Handle, 1, 0, 1);
    
    DEBUG_PRINT (TRACE_EXEC, ("leave NsDumpEntry %p\n", Handle));
}


