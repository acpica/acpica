
/******************************************************************************
 * 
 * Module Name: nsaccess - Top-level functions for accessing ACPI namespace
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
 * license (without the right to sublicense), under only those claims of Intel
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

#define __NSACCESS_C__

#include <acpi.h>
#include <amlcode.h>
#include <interpreter.h>
#include <namespace.h>


#define _THIS_MODULE        "nsaccess.c"
#define _COMPONENT          NAMESPACE




/****************************************************************************
 * 
 * FUNCTION:    NsSetup()
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Allocate and initialize the root name table
 *
 ***************************************************************************/

ACPI_STATUS
NsSetup (void)
{
    ACPI_STATUS             Status;
    PREDEFINED_NAMES        *InitVal = NULL;
    NAME_TABLE_ENTRY        *NewEntry;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    FUNCTION_TRACE ("NsSetup");


    /* 
     * Root is initially NULL, so a non-NULL value indicates
     * that NsSetup() has already been called; just return.
     */

    if (RootObject->Scope)
    {
        FUNCTION_STATUS_EXIT (AE_OK);
        return AE_OK;
    }

    /* Allocate a root scope table */

    RootObject->Scope = NsAllocateNteDesc (NS_TABLE_SIZE);
    if (!RootObject->Scope)
    {
        /*  root name table allocation failure  */

        REPORT_ERROR ("Root name table allocation failure");
        FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
        return AE_NO_MEMORY;
    }

    /* 
     * Init the root scope first entry -- since it is the exemplar of 
     * the scope (Some fields are duplicated to new entries!) 
     */
    NsInitializeTable (RootObject->Scope, NULL, RootObject);

    /* Push the root name table on the scope stack */
    
    ScopeStack[0].Scope = RootObject->Scope;
    ScopeStack[0].Type = TYPE_Any;
    CurrentScope = &ScopeStack[0];

    /* Enter the pre-defined names in the name table */
    
    DEBUG_PRINT (ACPI_INFO, ("Entering predefined name table into namespace\n"));

    for (InitVal = PreDefinedNames; InitVal->Name; InitVal++)
    {
        Status = NsLookup (CurrentScope->Scope, InitVal->Name, InitVal->Type, 
                                    MODE_Load, NS_NO_UPSEARCH, &NewEntry);

        /* 
         * if name entered successfully
         *  && its entry in PreDefinedNames[] specifies an initial value
         */
        
        if ((Status == AE_OK) && NewEntry && InitVal->Val)
        {
            /* Entry requests an initial value, allocate a descriptor for it. */
            
            ObjDesc = AllocateObjectDesc ();
            if (!ObjDesc)
            {
                FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                return AE_NO_MEMORY;
            }

            else
            {
                ObjDesc->ValType = (UINT8) InitVal->Type;

                /* 
                 * Convert value string from table entry to internal representation.
                 * Only types actually used for initial values are implemented here.
                 */

                switch (InitVal->Type)
                {
                case TYPE_Number:
                    ObjDesc->Number.Number = (UINT32) strtoul (InitVal->Val, NULL, 10);
                    break;

                case TYPE_String:
                    ObjDesc->String.StrLen = (UINT16) strlen (InitVal->Val);

                    /* 
                     * XXX - if this OsdAllocate() causes a garbage collection pass,
                     * XXX - ObjDesc will get deleted since no NT points to it yet.
                     * XXX - This "should not happen" during initialization.
                     */

                    ObjDesc->String.String = OsdAllocate ((ACPI_SIZE) (ObjDesc->String.StrLen + 1));
                    if (!ObjDesc->String.String)
                    {
                        REPORT_ERROR ("Initial value string allocation failure");
                        FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                        return AE_NO_MEMORY;
                    }
                    else
                    {
                        strcpy ((char *) ObjDesc->String.String, InitVal->Val);
                    }
                    
                    break;

                default:
                    OsdFree (ObjDesc);
                    ObjDesc = NULL;
                    continue;
                }

                /* Store pointer to value descriptor in nte */
            
                NsSetValue (NewEntry, ObjDesc, ObjDesc->ValType);
            }
        }
    }

    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
}


/****************************************************************************
 *
 * FUNCTION:    NsLookup
 *
 * PARAMETERS:  PrefixScope     - Search scope if name is not fully qualified
 *              Name            - Name to be entered, in internal format
 *                                as represented in the AML stream
 *              Type            - Type associated with name
 *              LoadMode        - MODE_Load => add name if not found
 *              RetEntry        - Where the new entry (NTE) is placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Find or enter the passed name in the name space.
 *              Log an error if name not found in Exec mode.
 *
 ***************************************************************************/

ACPI_STATUS
NsLookup (
    NAME_TABLE_ENTRY        *PrefixScope,
    char                    *Name, 
    ACPI_OBJECT_TYPE        Type, 
    OPERATING_MODE          LoadMode,
    UINT32                  Flags,
    NAME_TABLE_ENTRY        **RetEntry)
{
    ACPI_STATUS             Status;
    NAME_TABLE_ENTRY        *EntryToSearch = NULL;
    NAME_TABLE_ENTRY        *ThisEntry = NULL;
    NAME_TABLE_ENTRY        *ScopeToPush = NULL;
    INT32                   NumSegments;
    INT32                   NullNamePath = FALSE;
    ACPI_OBJECT_TYPE        TypeToCheckFor;              /* Type To Check For */


    FUNCTION_TRACE ("NsLookup");


    if (!RetEntry)
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }

    *RetEntry = ENTRY_NOT_FOUND;
    if (!RootObject->Scope)
    {
        /* 
         * If the name space has not been initialized:
         * -  In Pass1 of Load mode, we need to initialize it
         *    before trying to define a name.
         * -  In Exec mode, there are no names to be found.
         */

        if (MODE_Load1 == LoadMode)
        {
            if ((Status = NsSetup ()) != AE_OK)
            {
                FUNCTION_STATUS_EXIT (Status);
                return Status;
            }
        }
        else
        {
            FUNCTION_STATUS_EXIT (AE_NOT_FOUND);
            return AE_NOT_FOUND;
        }
    }


    /* DefFieldDefn and BankFieldDefn define fields in a Region */

    if (TYPE_DefFieldDefn == Type || TYPE_BankFieldDefn == Type)
    {
        TypeToCheckFor = TYPE_Region;
    }
    else
    {
        TypeToCheckFor = Type;
    }


    /* Examine the name pointer */

    if (!Name)
    {
        /*  8-12-98 ASL Grammar Update supports null NamePath   */

        NullNamePath = TRUE;
        NumSegments = 0;
        ThisEntry = RootObject;

        DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Null Name (Zero segments),  Flags=%x\n"));
    }

    else
    {
        /* 
         * Valid name pointer (Internal name format)
         *
         * Check for prefixes.  As represented in the AML stream, a Name consists
         * of an optional scope prefix followed by a segment part.
         *
         * If present, the scope prefix is either a RootPrefix (in which case the
         * name is fully qualified), or zero or more ParentPrefixes (in which case
         * the name's scope is relative to the current scope).
         *
         * The segment part consists of either:
         *  - A single 4-byte name segment, or
         *  - A DualNamePrefix followed by two 4-byte name segments, or
         *  - A MultiNamePrefixOp, followed by a byte indicating the number of
         *    segments and the segments themselves.
         */

        if (*Name == AML_RootPrefix)
        {
            /* Name is fully qualified, look in root name table */
        
            EntryToSearch = RootObject->Scope;
            Name++;                 /* point to segment part */

            DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Searching from root [%p]\n", 
                                        EntryToSearch));
        }
    
        else
        {
            /* Name is relative to current scope, start there */
        
            EntryToSearch = PrefixScope;

            DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Searching relative to pfx scope [%p]\n",
                                        PrefixScope));

            /* Handle up-prefix (carat).  More than one prefix is supported */

            while (*Name == AML_ParentPrefix)
            {
            
                /* Point to segment part or next ParentPrefix */

                Name++;     

                /*  Backup to the parent's scope  */
            
                EntryToSearch = EntryToSearch->ParentScope;
                if (!EntryToSearch)
                {
                    /* Current scope has no parent scope */
                
                    REPORT_ERROR ("NsLookup: Too many parent prefixes or scope has no parent");

                    FUNCTION_STATUS_EXIT (AE_NOT_FOUND);
                    return AE_NOT_FOUND;
                }
            }
        }


        /* Examine the name prefix opcode, if any, to determine the number of segments */

        if (*Name == AML_DualNamePrefix)
        {
            DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Dual Name (2 segments)\n"));

            NumSegments = 2;
            Name++;                             /* point to first segment */
        }
    
        else if (*Name == AML_MultiNamePrefixOp)
        {
            DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Multi Name (%d Segments) \n", Name[1]));
        
            NumSegments = (INT32)* (UINT8 *) ++Name;
            Name++;                             /* point to first segment */
        }

        else
        {
            /* 
             * No Dual or Multi prefix, hence there is only one
             * segment and Name is already pointing to it.
             */
            DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Simple Name (1 segment)\n"));
            NumSegments = 1;
        }

        DEBUG_PRINT (TRACE_NAMES, ("NsLookup: [%s] Segments=%d Flags=%x\n",
                                    Name, NumSegments, Flags));
    }


    /*
     * Search namespace for each segment of the name.
     * Loop through and verify/add each name segment.
     */

    while (NumSegments-- && EntryToSearch)
    {
        /* 
         * Search for the current segment in the table where it should be.
         * Type is significant only at the last level.
         */

        Status = NsSearchAndEnter (Name, EntryToSearch, LoadMode,
                                    NumSegments == 0 ? Type : TYPE_Any, Flags, &ThisEntry);
        if (Status != AE_OK)
        {
            if (Status == AE_NOT_FOUND)
            {
                /* Name not in ACPI namespace  */

                if (MODE_Load1 == LoadMode || MODE_Load == LoadMode)
                {
                    REPORT_ERROR ("Name table overflow");
                }

                else
                {
                    DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Name not found in this scope\n"));
                }
            }

            FUNCTION_STATUS_EXIT (Status);
            return Status;
        }

        if (NumSegments         == 0  &&                    /* If last segment                  */
            TypeToCheckFor      != TYPE_Any &&              /* and looking for a specific type  */
            TypeToCheckFor      != TYPE_DefAny &&           /* which is not a phoney type       */
            TypeToCheckFor      != TYPE_Scope &&            /*   "   "   "  "   "     "         */
            TypeToCheckFor      != TYPE_IndexFieldDefn &&   /*   "   "   "  "   "     "         */
            ThisEntry->Type     != TYPE_Any &&              /* and type of entry is known       */
            ThisEntry->Type     != TypeToCheckFor)          /* and entry does not match request */
        {                                                   /* complain.                        */
            /* Complain about type mismatch */

            REPORT_WARNING ("Type mismatch");
        }

        /*
         * If last segment and not looking for a specific type, but type of
         * found entry is known, use that type to see if it opens a scope.
         */

        if ((0 == NumSegments) && (TYPE_Any == Type))
        {
            Type = ThisEntry->Type;
        }

        if ((NumSegments || NsOpensScope (Type)) &&
            (ThisEntry->Scope == NULL))
        {
            /* 
             * More segments or the type implies enclosed scope, 
             * and the next scope has not been allocated.
             */

            DEBUG_PRINT (ACPI_INFO, ("NsLookup: Load mode=%d  ThisEntry=%x\n", LoadMode, ThisEntry));

            if ((MODE_Load1 == LoadMode) || (MODE_Load == LoadMode))
            {   
                /* First or second pass load mode ==> locate the next scope */
                
                DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Creating and adding a new scope\n"));
                ThisEntry->Scope = NsAllocateNteDesc (NS_TABLE_SIZE);

                if (!ThisEntry->Scope)
                {
                    FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                    return AE_NO_MEMORY;
                }
            }

            /* Now complain if there is no next scope */
            
            if (ThisEntry->Scope == NULL)
            {
                DEBUG_PRINT (ACPI_ERROR, ("NsLookup: No child scope at entry %p\n", ThisEntry));

                if (MODE_Load1 == LoadMode || MODE_Load == LoadMode)
                {
                    REPORT_ERROR ("Name Table allocation failure");
                    FUNCTION_STATUS_EXIT (AE_NOT_FOUND);
                    return AE_NOT_FOUND;
                }

                REPORT_ERROR ("Name not found");

                FUNCTION_STATUS_EXIT (AE_NOT_FOUND);
                return AE_NOT_FOUND;
            }


            /* Scope table initialization */

            if (MODE_Load1 == LoadMode || MODE_Load == LoadMode)
            {
                /* Initialize the new table */

                NsInitializeTable (ThisEntry->Scope, EntryToSearch, ThisEntry);
            }
        }

        EntryToSearch = ThisEntry->Scope;
        Name += ACPI_NAME_SIZE;                 /* point to next name segment */
    }


    /* 
     * If entry is a type which opens a scope,
     * push the new scope on the scope stack.
     */

    if (NsOpensScope (TypeToCheckFor))
    {
        /*  8-12-98 ASL Grammar Update supports null NamePath   */

        if (NullNamePath)
        {
            ScopeToPush = ThisEntry;
        }
        else
        {
            ScopeToPush = ThisEntry->Scope;
        }

        NsPushCurrentScope (ScopeToPush, Type);
    }

    *RetEntry = ThisEntry;
    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
}

