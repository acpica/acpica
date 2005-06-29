
/******************************************************************************
 * 
 * Module Name: nsdump - table dumping routines for debug
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


/*

    NsDumpTable (SearchBase, SearchBase == Root ? NsRootSize : TABLSIZE,
                    1, MaxDepth);

*/

static void
NsDumpDevices (NsType TargetType, nte *ThisEntry, INT32 Size, INT32 Level, INT32 MaxDepth)
{
    nte                 *Appendage;
    UINT32              DownstreamSiblingMask = 0;
    INT32               LevelTmp;
    NsType              Type;
    UINT32              WhichBit;


    FUNCTION_TRACE ("NsDumpRootDevices");



    if (OUTRANGE (TargetType, NsTypeNames))
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


            if (OUTRANGE (Type, NsTypeNames))
            {
                Type = TYPE_DefAny;                                 /* prints as *ERROR* */
            }
            
            if (!NcOK ((INT32)* (char *) &ThisEntry->NameSeg))
            {
                REPORT_WARNING (&KDT[0]);
            }

            if (Type == TargetType)
            {


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

                DEBUG_PRINT_RAW (TRACE_TABLES,
                            ("%4.4s [%s] ", &ThisEntry->NameSeg, NsTypeNames[Type]));
                
                DEBUG_PRINT_RAW (TRACE_TABLES, ("N:%p", ThisEntry));
                
                DEBUG_PRINT_RAW (TRACE_TABLES, (" C:%p P:%p\n",
                            ThisEntry->ChildScope, ThisEntry->ParentScope));
            }

            if (ThisEntry->ChildScope && MaxDepth > 1)
            {
                /* Recursive call: dump next scope level */
                
                NsDumpDevices (TargetType, ThisEntry->ChildScope, TABLSIZE, Level+1,
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
}


void
NsDumpRootDevices (void)
{

    /* Only dump the table if tracing is enabled */

    if (!(TRACE_TABLES & DebugLevel))
    {
        return;
    }


    DEBUG_PRINT (TRACE_TABLES, ("All devices in the namespace:\n"));
    NsDumpDevices (TYPE_Device, Root, NsRootSize, 1, INT_MAX);

}

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
                Type = TYPE_DefAny;                                 /* prints as *ERROR* */
            }
            
            if (!NcOK ((INT32)* (char *) &ThisEntry->NameSeg))
            {
                REPORT_WARNING (&KDT[0]);
            }

            if (TYPE_Method == Type && ThisEntry->ptrVal)
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
                    
                    if (bT == TYPE_String ||     bT == TYPE_Buffer   || bT == TYPE_Package
                     || bT == TYPE_FieldUnit ||  bT == TYPE_DefField || bT == TYPE_BankField
                     || bT == TYPE_IndexField || bT == TYPE_Lvalue)
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
                /*  Recursive call: dump next scope level */
                
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


