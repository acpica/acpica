
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

#define __NSACCESS_C__

#include <acpi.h>
#include <amlcode.h>
#include <interp.h>
#include <namesp.h>
#include <dispatch.h>


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nsaccess");



/****************************************************************************
 * 
 * FUNCTION:    NsRootCreateScope
 *
 * PARAMETERS:  Entry               - NTE for which a scope will be created
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a scope table for the given name table entry
 *
 * MUTEX:       Expects namespace to be locked
 *
 ***************************************************************************/

ACPI_STATUS
NsRootCreateScope (
    NAME_TABLE_ENTRY        *Entry)
{
    FUNCTION_TRACE ("NsRootCreateScope");


    /* Allocate a scope table */

    if (Entry->Scope)
    {
        return_ACPI_STATUS (AE_EXIST);
    }

    Entry->Scope = NsAllocateNameTable (NS_TABLE_SIZE);
    if (!Entry->Scope)
    {
        /*  root name table allocation failure  */

        REPORT_ERROR ("Root name table allocation failure");
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* 
     * Init the scope first entry -- since it is the exemplar of 
     * the scope (Some fields are duplicated to new entries!) 
     */
    NsInitializeTable (Entry->Scope, NULL, Entry);
    return_ACPI_STATUS (AE_OK);

}



/****************************************************************************
 * 
 * FUNCTION:    NsRootInitialize
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Allocate and initialize the root name table
 *
 * MUTEX:       Locks namespace for entire execution
 *
 ***************************************************************************/

ACPI_STATUS
NsRootInitialize (void)
{
    ACPI_STATUS             Status = AE_OK;
    PREDEFINED_NAMES        *InitVal = NULL;
    NAME_TABLE_ENTRY        *NewEntry;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    FUNCTION_TRACE ("NsRootInitialize");


    CmAcquireMutex (MTX_NAMESPACE);
    
    /* 
     * Root is initially NULL, so a non-NULL value indicates
     * that NsRootInitialize() has already been called; just return.
     */

    if (Gbl_RootObject->Scope)
    {
        Status = AE_OK;
        goto UnlockAndExit;
    }


    /* Create the root scope */

    Status = NsRootCreateScope (Gbl_RootObject);
    if (ACPI_FAILURE (Status))
    {
        goto UnlockAndExit;
    }

    /* Enter the pre-defined names in the name table */
    
    DEBUG_PRINT (ACPI_INFO, ("Entering predefined name table entries into namespace\n"));

    for (InitVal = Gbl_PreDefinedNames; InitVal->Name; InitVal++)
    {
        Status = NsLookup (NULL, InitVal->Name, InitVal->Type, 
                                    IMODE_LoadPass2, NS_NO_UPSEARCH, NULL, &NewEntry);

        /* 
         * if name entered successfully
         *  && its entry in PreDefinedNames[] specifies an initial value
         */
        
        if ((Status == AE_OK) && 
            NewEntry && InitVal->Val)
        {
            /* Entry requests an initial value, allocate a descriptor for it. */
            
            ObjDesc = CmCreateInternalObject (InitVal->Type);
            if (!ObjDesc)
            {
                Status = AE_NO_MEMORY;
                goto UnlockAndExit;
            }

            /* 
             * Convert value string from table entry to internal representation.
             * Only types actually used for initial values are implemented here.
             */

            switch (InitVal->Type)
            {

            case ACPI_TYPE_Number:

                ObjDesc->Number.Value = (UINT32) STRTOUL (InitVal->Val, NULL, 10);
                break;


            case ACPI_TYPE_String:

                ObjDesc->String.Length = (UINT16) STRLEN (InitVal->Val);

                /* 
                 * Allocate a buffer for the string.  All String.Pointers must be
                 * allocated buffers! (makes deletion simpler)
                 */
                ObjDesc->String.Pointer = CmAllocate ((ACPI_SIZE) (ObjDesc->String.Length + 1));
                if (!ObjDesc->String.Pointer)
                {
                    REPORT_ERROR ("Initial value string allocation failure");
                    CmRemoveReference (ObjDesc);
                    Status = AE_NO_MEMORY;
                    goto UnlockAndExit;
                }

                STRCPY ((char *) ObjDesc->String.Pointer, InitVal->Val);
                break;


            case ACPI_TYPE_Mutex:

                ObjDesc->Mutex.SyncLevel = (UINT16) STRTOUL (InitVal->Val, NULL, 10);
                Status = OsdCreateSemaphore (1, &ObjDesc->Mutex.Semaphore);
                if (ACPI_FAILURE (Status))
                {
                    goto UnlockAndExit;
                }

                if (STRCMP (InitVal->Name, "_GL_") == 0)
                {
                    /* We just created the mutex for the global lock, save it */

                    Gbl_GlobalLockSemaphore = ObjDesc->Mutex.Semaphore;
                }

                /* TBD: These fields may be obsolete */

                ObjDesc->Mutex.LockCount = 0;
                ObjDesc->Mutex.ThreadId  = 0;
                break;


            default:
                REPORT_ERROR ("Unsupported initial type value");
                CmRemoveReference (ObjDesc);
                ObjDesc = NULL;
                continue;
            }

            /* Store pointer to value descriptor in nte */
        
            NsAttachObject (NewEntry, ObjDesc, ObjDesc->Common.Type);
        }
    }


UnlockAndExit:
    CmReleaseMutex (MTX_NAMESPACE);
    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    NsLookup
 *
 * PARAMETERS:  PrefixScope     - Search scope if name is not fully qualified
 *              Name            - Name to be entered, in internal format
 *                                as represented in the AML stream
 *              Type            - Type associated with name
 *              InterpreterMode - IMODE_LoadPass2 => add name if not found
 *              RetEntry        - Where the new entry (NTE) is placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Find or enter the passed name in the name space.
 *              Log an error if name not found in Exec mode.
 *
 * MUTEX:       Assumes namespace is locked.
 *
 ***************************************************************************/

ACPI_STATUS
NsLookup (
    SCOPE_STACK             *ScopeInfo,
    char                    *Name, 
    ACPI_OBJECT_TYPE        Type, 
    OPERATING_MODE          InterpreterMode,
	UINT32					Flags,
    ACPI_WALK_STATE			*WalkState,
    NAME_TABLE_ENTRY        **RetEntry)
{
    NAME_TABLE_ENTRY        *PrefixScope;
    ACPI_STATUS             Status;
    NAME_TABLE_ENTRY        *EntryToSearch = NULL;
    NAME_TABLE_ENTRY        *ThisEntry = NULL;
    NAME_TABLE_ENTRY        *ScopeToPush = NULL;
    UINT32                  NumSegments;
    ACPI_OBJECT_TYPE        TypeToCheckFor;              /* Type To Check For */
    UINT32                  i;
    BOOLEAN                 NullNamePath = FALSE;


    FUNCTION_TRACE ("NsLookup");


    if (!RetEntry)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

   
    Gbl_NsLookupCount++;

    *RetEntry = ENTRY_NOT_FOUND;
    if (!Gbl_RootObject->Scope)
    {
        /* 
         * If the name space has not been initialized:
         * -  In Pass1 of Load mode, we need to initialize it
         *    before trying to define a name.
         * -  In Exec mode, there are no names to be found.
         */

        if (IMODE_LoadPass1 == InterpreterMode)
        {
            if ((Status = NsRootInitialize ()) != AE_OK)
            {
                return_ACPI_STATUS (Status);
            }
        }
        else
        {
            return_ACPI_STATUS (AE_NOT_FOUND);
        }
    }


    /* Get the prefix scope */

    if (!ScopeInfo)
    {
        PrefixScope = Gbl_RootObject->Scope;
    }
    else
    {
        PrefixScope = ScopeInfo->Scope;
    }


    /*
     * This check is explicitly split provide relax the TypeToCheckFor
     * conditions for BankFieldDefn.  Originally, both BankFieldDefn and
     * DefFieldDefn caused TypeToCheckFor to be set to ACPI_TYPE_Region,
     * but the BankFieldDefn may also check for a Field definition as well
     * as an OperationRegion.
     */

    if (INTERNAL_TYPE_DefFieldDefn == Type)
    {
        /* DefFieldDefn defines fields in a Region */

        TypeToCheckFor = ACPI_TYPE_Region;
    }

    else if (INTERNAL_TYPE_BankFieldDefn == Type)
    {
        /* BankFieldDefn defines data fields in a Field Object */

        TypeToCheckFor = ACPI_TYPE_Any;
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
        ThisEntry = Gbl_RootObject;

        DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Null Name (Zero segments),  Flags=%x\n", Flags));
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
        
            EntryToSearch = Gbl_RootObject->Scope;
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
            
                EntryToSearch = EntryToSearch->ParentEntry;
                if (!EntryToSearch)
                {
                    /* Current scope has no parent scope */
                
                    REPORT_ERROR ("NsLookup: Too many parent prefixes or scope has no parent");

                    return_ACPI_STATUS (AE_NOT_FOUND);
                }

                EntryToSearch = EntryToSearch->Scope;
            }
        }


        /* Examine the name prefix opcode, if any, to determine the number of segments */

        if (*Name == AML_DualNamePrefix)
        {
            NumSegments = 2;
            Name++;                             /* point to first segment */

            DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Dual Name (2 segments, Flags=%X)\n", Flags));
        }
    
        else if (*Name == AML_MultiNamePrefixOp)
        {
            NumSegments = (INT32)* (UINT8 *) ++Name;
            Name++;                             /* point to first segment */
        
            DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Multi Name (%d Segments, Flags=%X) \n", NumSegments, Flags));
        }

        else
        {
            /* 
             * No Dual or Multi prefix, hence there is only one
             * segment and Name is already pointing to it.
             */
            NumSegments = 1;

            DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Simple Name (1 segment, Flags=%X)\n", Flags));
        }


        /* Debug only: print the entire name that we are about to lookup */

        DEBUG_PRINT (TRACE_NAMES, ("NsLookup: ["));
        for (i = 0; i < NumSegments; i++)
        {
            DEBUG_PRINT_RAW (TRACE_NAMES, ("%4.4s/", &Name[i * 4]));
        }
        DEBUG_PRINT_RAW (TRACE_NAMES, ("]\n"));
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

        Status = NsSearchAndEnter (*(UINT32 *) Name, WalkState, EntryToSearch, InterpreterMode,
                                    NumSegments == 0 ? Type : ACPI_TYPE_Any, Flags, &ThisEntry);
        if (Status != AE_OK)
        {
            if (Status == AE_NOT_FOUND)
            {
                /* Name not in ACPI namespace  */

                if (IMODE_LoadPass1 == InterpreterMode || 
                    IMODE_LoadPass2 == InterpreterMode)
                {
                    REPORT_ERROR ("Name table overflow");
                }

                else
                {
                    DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Name not found in this scope\n"));
                }
            }

            return_ACPI_STATUS (Status);
        }

        if (NumSegments         == 0  &&                            /* If last segment                  */
            TypeToCheckFor      != ACPI_TYPE_Any &&                 /* and looking for a specific type  */
            TypeToCheckFor      != INTERNAL_TYPE_DefAny &&          /* which is not a local type        */
            TypeToCheckFor      != INTERNAL_TYPE_Scope &&           /*   "   "   "  "   "     "         */
            TypeToCheckFor      != INTERNAL_TYPE_IndexFieldDefn &&  /*   "   "   "  "   "     "         */
            ThisEntry->Type     != ACPI_TYPE_Any &&                 /* and type of entry is known       */
            ThisEntry->Type     != TypeToCheckFor)                  /* and entry does not match request */
        {                                                           /* complain.                        */
            /* Complain about type mismatch */

            REPORT_WARNING ("Type mismatch");
            DEBUG_PRINT (ACPI_WARN, ("NsLookup: %4.4s, type 0x%X, checking for type 0x%X\n", 
                                        Name, ThisEntry->Type, TypeToCheckFor));
        }

        /*
         * If last segment and not looking for a specific type, but type of
         * found entry is known, use that type to see if it opens a scope.
         */

        if ((0 == NumSegments) && (ACPI_TYPE_Any == Type))
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

            DEBUG_PRINT (ACPI_INFO, ("NsLookup: Load mode=%d  ThisEntry=%x\n", InterpreterMode, ThisEntry));

            if ((IMODE_LoadPass1 == InterpreterMode) || 
                (IMODE_LoadPass2 == InterpreterMode))
            {   
                /* First or second pass load mode ==> locate the next scope */
                
                DEBUG_PRINT (TRACE_NAMES, ("NsLookup: Creating and adding a new scope\n"));
                ThisEntry->Scope = NsAllocateNameTable (NS_TABLE_SIZE);

                if (!ThisEntry->Scope)
                {
                    return_ACPI_STATUS (AE_NO_MEMORY);
                }
            }

            /* Now complain if there is no next scope */
            
            if (ThisEntry->Scope == NULL)
            {
                if (IMODE_LoadPass1 == InterpreterMode || 
                    IMODE_LoadPass2 == InterpreterMode)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("NsLookup: ***Error - No child scope at entry %p\n", ThisEntry));
                    REPORT_ERROR ("Name Table allocation failure");
                    return_ACPI_STATUS (AE_NOT_FOUND);
                }

                DEBUG_PRINT (ACPI_INFO, ("NsLookup: No child scope at entry %p\n", ThisEntry));

                return_ACPI_STATUS (AE_NOT_FOUND);
            }


            /* Scope table initialization */

            if (IMODE_LoadPass1 == InterpreterMode || 
                IMODE_LoadPass2 == InterpreterMode)
            {
                /* Initialize the new table */

                NsInitializeTable (ThisEntry->Scope, EntryToSearch, ThisEntry);
            }
        }

        EntryToSearch = ThisEntry->Scope;
        Name += ACPI_NAME_SIZE;                 /* point to next name segment */
    }


    if (!(Flags & NS_DONT_OPEN_SCOPE) && (WalkState))
    {
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

            Status = DsScopeStackPush (ScopeToPush, Type, WalkState);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }

            DEBUG_PRINT (ACPI_INFO, ("NsLookup: Set global scope to %p\n", ScopeToPush));
        }
    }

    *RetEntry = ThisEntry;
    return_ACPI_STATUS (AE_OK);
}

