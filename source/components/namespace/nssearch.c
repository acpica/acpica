
/******************************************************************************
 * 
 * Module Name: nssearch - Namespace search
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


#define __NSSEARCH_C__

#include <acpi.h>
#include <amlcode.h>
#include <interpreter.h>
#include <namespace.h>


#define _THIS_MODULE        "nssearch.c"
#define _COMPONENT          NAMESPACE



/****************************************************************************
 *
 * FUNCTION:    NsSearchOnly
 *
 * PARAMETERS:  *EntryName          - Ascii ACPI name to search for
 *              *NameTable          - Starting table where search will begin
 *              Type                - Object type to match
 *              **RetEntry          - Where the matched NTE is returned
 *              *RetInfo            - Where info about the search is returned
 *
 * RETURN:      Status and return information via NS_SEARCH_DATA
 *
 * DESCRIPTION: Search a single namespace table.  Performs a simple search,
 *              does not add entries or search parents.
 *
 ***************************************************************************/

ACPI_STATUS
NsSearchOnly (
    char                    *EntryName, 
    NAME_TABLE_ENTRY        *NameTable, 
    ACPI_OBJECT_TYPE        Type, 
    NAME_TABLE_ENTRY        **RetEntry, 
    NS_SEARCH_DATA          *RetInfo)
{
    UINT32                  Position;
    UINT32                  Tries;
    char                    *ScopeName;


    FUNCTION_TRACE ("NsSearchOnly");

    /* Debug only */

    ScopeName = NsNameOfScope (NameTable);
    DEBUG_PRINT (TRACE_NAMES,
                    ("NsSearchOnly: search %s [%p] for %4.4s (type %d)\n",
                    ScopeName, NameTable, EntryName, Type));

    OsdFree (ScopeName);

    /* 
     * Name tables are built (and subsequently dumped) in the
     * order in which the names are encountered during the namespace load;
     *
     * All namespace searching will be linear;  If a table overflows an 
     * additional segment will be allocated and added (chained).
     *
     * Start linear search at top of table
     */
    Position = 0;

    /* Init return data */

    if (RetInfo)
    {
        RetInfo->PreviousEntry = NULL;
        RetInfo->NameTable = NameTable;
    }

    /* 
     * Search for name in table, starting at Position.  Stop searching upon
     * finding an unused entry or after examining all entries in the table.
     *
     * Moving to the "next" entry is done at the bottom of the loop instead
     * of in the iteration expression because the method used depends on
     * whether or not USE_HASHING is in effect.
     */

    for (Tries = NS_TABLE_SIZE; Tries && 0 != NameTable[Position].Name; Tries--)
    {
        /*  search for name in table    */

        CheckTrash ("top of NsSearchTable loop");
        
        if (NameTable[Position].Name == *(UINT32 *) EntryName)
        {
            /* 
             * Found matching entry.  Capture type if appropriate before
             * returning the entry.
             */

            /* 
             * The DefFieldDefn and BankFieldDefn cases are actually
             * looking up the Region in which the field will be defined
             */

            if (TYPE_DefFieldDefn == Type || TYPE_BankFieldDefn == Type)
            {
                Type = TYPE_Region;
            }

            /* 
             * Scope, DefAny, and IndexFieldDefn are bogus "types" which do
             * not actually have anything to do with the type of the name
             * being looked up.  For any other value of Type, if the type
             * stored in the entry is Any (i.e. unknown), save the actual type.
             */

            if (Type != TYPE_Scope && 
                Type != TYPE_DefAny &&
                Type != TYPE_IndexFieldDefn && 
                NameTable[Position].Type == TYPE_Any)
            {
                NameTable[Position].Type = Type;
            }

            DEBUG_PRINT (TRACE_NAMES, ("NsSearchOnly: Name %4.4s (actual type %d) found at %p\n", 
                            EntryName, NameTable[Position].Type, &NameTable[Position]));
            
            CheckTrash ("leave NsSearchTable FOUND");
            *RetEntry = &NameTable[Position];
            FUNCTION_EXIT;
            return AE_OK;
        }

        if (RetInfo)
        {
            /* Save a pointer to this entry, it might become the previous entry */

            RetInfo->PreviousEntry = &NameTable[Position];
        }
        

        /* Done with this table? */

        if ((1 == Tries) && 
            (NEXTSEG (NameTable)))
        {
            /* 
             * Just examined last slot, but table has an appendage.
             * All appendages, even to the root NT, contain NS_DEFAULT_TABLE_SIZE entries.
             */

            NameTable = NEXTSEG (NameTable);
            DEBUG_PRINT (TRACE_EXEC, ("NsSearchOnly: Search appendage NameTable=%p\n", NameTable));
            Position = 0;
            Tries += NS_TABLE_SIZE;
        }
        
        else
        {
            ++Position;
        }
    }


    /* Searched entire table, not found */

    DEBUG_PRINT (TRACE_NAMES, ("NsSearchOnly: Name %4.4s (type %d) not found at %p\n", 
                                EntryName, Type, &NameTable[Position]));


    if (RetInfo)
    {
        /* Save the final information (name was not found) */

        RetInfo->TableFull  = !(Tries);      /* Table is full if no more tries available */
        RetInfo->Position   = Position;
        RetInfo->NameTable  = NameTable;
    }

    FUNCTION_EXIT;
    return AE_NOT_FOUND;
}


/****************************************************************************
 *
 * FUNCTION:    NsSearchParentTree 
 *
 * PARAMETERS:  *EntryName          - Ascii ACPI name to search for
 *              *NameTable          - Starting table where search will begin
 *              Type                - Object type to match
 *              **RetEntry          - Where the matched NTE is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Called when a name has not been found in the current namespace
 *              table.  Before adding it or giving up, ACPI scope rules require 
 *              searching enclosing scopes in cases identified by NsLocal().
 *
 *              "A name is located by finding the matching name in the current 
 *              name space, and then in the parent name space. If the parent 
 *              name space does not contain the name, the search continues 
 *              recursively until either the name is found or the name space 
 *              does not have a parent (the root of the name space).  This 
 *              indicates that the name is not found" (From ACPI Specification, 
 *              section 5.3)
 *
 ***************************************************************************/


ACPI_STATUS
NsSearchParentTree (
    char                    *EntryName, 
    NAME_TABLE_ENTRY        *NameTable, 
    ACPI_OBJECT_TYPE        Type, 
    NAME_TABLE_ENTRY        **RetEntry)
{
    ACPI_STATUS             Status;
    NAME_TABLE_ENTRY        *ParentScope;


    FUNCTION_TRACE ("NsSearchParentTree");


    /* 
     * NameTable[0] will be an unused entry if the table being searched is empty,
     * However, its ParentScope member will have been filled in
     * when the table was allocated (unless it is the root name table).
     */

   
    if (!NsLocal (Type) && 
        NameTable[0].ParentScope)
    {
        ParentScope = NameTable[0].ParentScope;
        DEBUG_PRINT (TRACE_NAMES, ("NsSearchParentTree: Searching parent for %.4s\n", EntryName));

        /* Search parents until found or we have backed up to the root */

        while (ParentScope)
        {
            /* Search parent scope */
            /* TBD: Why TYPE_Any? */

            Status = NsSearchOnly (EntryName, ParentScope, TYPE_Any, RetEntry, NULL);
            if (Status == AE_OK)
            {
                CheckTrash ("leave NsSearchTable FOUND in parent");
                FUNCTION_EXIT;
                return Status;
            }

            /* Not found here, go up another level (until we reach the root) */

            ParentScope = ParentScope->ParentScope;
        }

        /* Not found in parent tree */
    }
 
    else
    {
        /*
         * No parent, or type is "local".  We won't be searching the parent tree.
         */

        if (!NameTable[0].ParentScope)
        {
            DEBUG_PRINT (TRACE_NAMES, ("NsSearchParentTree: [%.4s] has no parent\n", EntryName));
        }

        else if (NsLocal (Type))
        {
            DEBUG_PRINT (TRACE_NAMES, ("NsSearchParentTree: [%.4s] (type %d) is local (no search)\n", 
                                        EntryName, Type));
        }
    }

    FUNCTION_EXIT;
    return AE_NOT_FOUND;
}


/****************************************************************************
 *
 * FUNCTION:    NsCreateAndLinkNewTable
 *
 * PARAMETERS:  *NameTable          - The table that is to be "extended" by
 *                                    the creation of an appendage table.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Allocate a new namespace table, initialize it, and link it
 *              into the parent table.
 *
 *              NOTE: We are in the first or second pass load mode, want to 
 *              add a new table entry, and the current table is full.
 *
 ***************************************************************************/

ACPI_STATUS
NsCreateAndLinkNewTable (
    NAME_TABLE_ENTRY        *NameTable)
{
    NAME_TABLE_ENTRY        *NewTable;
    NAME_TABLE_ENTRY        *ParentScope;
    NAME_TABLE_ENTRY        *ParentEntry;
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("NsCreateAndLinkNewTable");


    /* Sanity check on the data structure */

    if (NEXTSEG (NameTable))
    {
        /* We should never get here (an appendage already allocated) */

        DEBUG_PRINT (ACPI_ERROR,
                    ("NsCreateAndLinkNewTable: appendage %p about to be overwritten\n",
                    NEXTSEG (NameTable)));
    }


    /*
     * We can use the parent entries from the start of the current table 
     * Since the parent information remains the same.
     */

    ParentScope = NameTable[0].ParentScope;
    ParentEntry = NameTable[0].ParentEntry;


    /* Allocate and chain an appendage to the filled table */
    
    NewTable = NsAllocateNteDesc (NS_TABLE_SIZE);
    if (!NewTable)
    {
        REPORT_ERROR ("Name Table appendage allocation failure");
        Status = AE_NO_MEMORY;
    }

    else
    {
        /* 
         * Allocation successful. Init the new table.
         */
        NEXTSEG (NameTable) = NewTable;
        NsInitializeTable (NewTable, ParentScope, ParentEntry);

        DEBUG_PRINT (TRACE_EXEC, 
            ("NsCreateAndLinkNewTable: NewTable=%p, ParentScope=%p, Scope=%p\n",
                NewTable, ParentScope, NameTable->Scope));
    }

    FUNCTION_EXIT;
    return Status;
}


/****************************************************************************
 *
 * FUNCTION:    NsInitializeTable
 *
 * PARAMETERS:  NewTable            - The new table to be initialized
 *              ParentScope         - The parent (owner) scope
 *              ParentEntry         - The NTE for the parent
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize a new namespace table.  Simple, but called
 *              from several places -- code should be kept in one place.
 *
 ***************************************************************************/

void
NsInitializeTable (
    NAME_TABLE_ENTRY        *NewTable, 
    NAME_TABLE_ENTRY        *ParentScope, 
    NAME_TABLE_ENTRY        *ParentEntry)
{


    NewTable->ParentScope     = ParentScope;
    NewTable->ParentEntry     = ParentEntry;


    DEBUG_PRINT (TRACE_NAMES, ("NsInitializeTable: %x\n", NewTable));
}


/****************************************************************************
 *
 * FUNCTION:    NsInitializeEntry
 *
 * PARAMETERS:  NameTable       - The containing table for the new NTE
 *              Position        - Position (index) of the new NTE in the table
 *              EntryName       - ACPI name of the new entry
 *              Type            - ACPI object type of the new entry
 *              PreviousEntry   - Link back to the previous entry (can span
 *                                multiple tables)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize a new entry within a namespace table.
 *
 ***************************************************************************/

void
NsInitializeEntry (
    NAME_TABLE_ENTRY        *NameTable, 
    UINT32                  Position, 
    char                    *EntryName, 
    ACPI_OBJECT_TYPE        Type, 
    NAME_TABLE_ENTRY        *PreviousEntry)
{
    NAME_TABLE_ENTRY        *NewEntry;


    FUNCTION_TRACE ("NsInitializeEntry");


    NewEntry = &NameTable[Position];
    
    /*  first or second pass load mode, NameTable valid   */

    CheckTrash ("NsSearchTable about to add");

    NewEntry->Name          = *(UINT32 *) EntryName;
    NewEntry->ParentScope   = NameTable[0].ParentScope;
    NewEntry->ParentEntry   = NameTable[0].ParentEntry;

    /* 
     * Set forward and back links.
     * Important:  These are the links that tie the tables together
     * so that when walking the links, it is invisible that their
     * are separate, disjoint tables.
     */
    if (PreviousEntry)
    {
        PreviousEntry->NextEntry = NewEntry;
    }

    NewEntry->PrevEntry = PreviousEntry;
    NewEntry->NextEntry = NULL;

    CheckTrash ("NsInitializeEntry added name");

    /* 
     * If adding a name with unknown type, or having to add the region in
     * order to define fields in it, we have a forward reference.
     */

    if ((TYPE_Any == Type) || 
        (TYPE_DefFieldDefn == Type) || 
        (TYPE_BankFieldDefn == Type))
    {
        /* 
         * We don't want to abort here, however!
         * We will fill in the actual type when the real definition
         * is found later.
         */

        DEBUG_PRINT (ACPI_INFO, ("[%4.4s] is a forward reference into the namespace",
                        EntryName));

    }

    /* 
     * The DefFieldDefn and BankFieldDefn cases are actually
     * looking up the Region in which the field will be defined
     */

    if ((TYPE_DefFieldDefn == Type) || (TYPE_BankFieldDefn == Type))
    {
        Type = TYPE_Region;
    }

    /* 
     * Scope, DefAny, and IndexFieldDefn are bogus "types" which do
     * not actually have anything to do with the type of the name
     * being looked up.  Save any other value of Type as the type of
     * the entry.
     */

    if ((Type != TYPE_Scope) && 
        (Type != TYPE_DefAny) && 
        (Type != TYPE_IndexFieldDefn))
    {
        NewEntry->Type = Type;
        CheckTrashA ("NsInitializeEntry added type",
                        &NewEntry->Name, NewEntry->Name, Hash,
                        &NewEntry->Type, NewEntry->Type, Type, (void *) NameTable);
    }

    DEBUG_PRINT (TRACE_NAMES, ("NsInitializeEntry: %.4s added to %p at %p\n", 
                                EntryName, NameTable, NewEntry));
    CheckTrash ("leave NsInitializeEntry ADDED");
    
    FUNCTION_EXIT;
}


/****************************************************************************
 *
 * FUNCTION:    NsSearchAndEnter
 *
 * PARAMETERS:  *EntryName          - Ascii ACPI name to search for
 *              *NameTable          - Starting table where search will begin
 *              LoadMode            - Add names only in MODE_Loadx.  Otherwise,
 *                                    search only.
 *              Type                - Object type to match
 *              **RetEntry          - Where the matched NTE is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Search for a name segment in a single name table,
 *              optionally adding it if it is not found.  If the passed
 *              Type is not Any and the type previously stored in the
 *              entry was Any (i.e. unknown), update the stored type.
 *
 *              In MODE_Exec, search only.
 *              In other modes, search and add if not found.
 *
 ***************************************************************************/

ACPI_STATUS
NsSearchAndEnter (
    char                    *EntryName, 
    NAME_TABLE_ENTRY        *NameTable,
    OPERATING_MODE          LoadMode, 
    ACPI_OBJECT_TYPE        Type, 
    NAME_TABLE_ENTRY        **RetEntry)
{
    UINT32                  Position;       /* position in table */
    ACPI_STATUS             Status;
    NS_SEARCH_DATA          SearchInfo;


    FUNCTION_TRACE ("NsSearchAndEnter");
    CheckTrash ("enter NsSearchAndEnter");


    /* Parameter validation */

    if (!NameTable || !EntryName || !RetEntry)
    {
        REPORT_ERROR ("NsSearchAndEnter: bad parameter");
        FUNCTION_EXIT;
        return AE_BAD_PARAMETER;
    }


    /* Name must consist of printable characters */

    if (!AmlGoodChar ((INT32) EntryName[0]) || 
        !AmlGoodChar ((INT32) EntryName[1]) || 
        !AmlGoodChar ((INT32) EntryName[2]) || 
        !AmlGoodChar ((INT32) EntryName[3]))
    {
        DEBUG_PRINT (ACPI_ERROR, ("NsSearchAndEnter:  *** bad name %08lx *** \n", 
                                    *(UINT32 *) EntryName));
        CheckTrash ("leave NsSearchTable BADNAME");
        FUNCTION_EXIT;
        return AE_BAD_CHARACTER;
    }


    /* Try to find the name in the table specified by the caller */

    *RetEntry = ENTRY_NOT_FOUND;
    Status = NsSearchOnly (EntryName, NameTable, Type, RetEntry, &SearchInfo);
    if (Status != AE_NOT_FOUND)
    {
        /* Either found it or there was an error -- finished either way */

        FUNCTION_EXIT;
        return Status;
    }


    /*
     * Not found in the table.  If we are NOT loading the namespace, search the 
     * parent tree (all the way to the root if necessary.)  We don't want to perform
     * the parent search when the namespace is actually being loaded.
     */

    /* TBD: should this be (LoadMode == MODE_Exec) to exclude MODE_Load1 from search? */

    if (LoadMode != MODE_Load)
    {
        /* Not found in table - search parent tree according to ACPI specification */

        Status = NsSearchParentTree (EntryName, NameTable, Type, RetEntry);
        if (Status == AE_OK)
        {
            FUNCTION_EXIT;
            return Status;
        }
    }


    /*
     * In execute mode, just search, never add names.  Exit now.
     */

    if (LoadMode == MODE_Exec)
    {
        DEBUG_PRINT (TRACE_NAMES, ("NsSearchAndEnter: Name %.4s Not found in %p (not adding)\n", 
                                    EntryName, NameTable));
        CheckTrash ("leave NsSearchTable NOTFOUND");
    
        FUNCTION_EXIT;
        return AE_NOT_FOUND;
    }


    /* 
     * Extract the pertinent info from the search result struct.
     * NameTable and position might now point to an appendage
     */
    NameTable = SearchInfo.NameTable;
    Position = SearchInfo.Position;


    /* 
     * This block handles the case where the existing table is full.
     * we must allocate a new table before we can initialize a new entry
     */

    if (SearchInfo.TableFull)
    {
        Status = NsCreateAndLinkNewTable (NameTable);
        if (Status != AE_OK)
        {
            FUNCTION_EXIT;
            return Status;
        }

        /* Point to the first slot in the new table */

        NameTable = NEXTSEG (NameTable);
        Position = 0;
    }


    /*
     * There is room in the table (or we have just allocated a new one.)
     * Initialize the new entry
     */

    NsInitializeEntry (NameTable, Position, EntryName, Type, 
                        SearchInfo.PreviousEntry);
    *RetEntry = &NameTable[Position];

    FUNCTION_EXIT;
    return AE_OK;
}


