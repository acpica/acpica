
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

#define __NSSEARCH_C__

#include "acpi.h"
#include "amlcode.h"
#include "acinterp.h"
#include "acnamesp.h"


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nssearch");


/****************************************************************************
 *
 * FUNCTION:    AcpiNsSearchNameTable
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
AcpiNsSearchNameTable (
    UINT32                  EntryName,
    ACPI_NAME_TABLE         *NameTable,
    OBJECT_TYPE_INTERNAL    Type,
    ACPI_NAMED_OBJECT       **RetEntry,
    NS_SEARCH_DATA          *RetInfo)
{
    UINT32                  Position;
    ACPI_NAME_TABLE         *ThisTable;
    ACPI_NAME_TABLE         *PreviousTable = NameTable;
    ACPI_NAMED_OBJECT       *Entries;
    BOOLEAN                 TableFull = TRUE;
    ACPI_NAME_TABLE         *TableWithEmptySlots = NULL;
    UINT32                  EmptySlotPosition = 0;


    FUNCTION_TRACE ("NsSearchNameTable");

    {
        DEBUG_EXEC (INT8 *ScopeName = AcpiNsGetTablePathname (NameTable));
        DEBUG_PRINT (TRACE_NAMES,
            ("NsSearchNameTable: Searching %s [%p]\n",
            ScopeName, NameTable));
        DEBUG_PRINT (TRACE_NAMES,
            ("NsSearchNameTable: For %4.4s (type 0x%X)\n",
            &EntryName, Type));
        DEBUG_EXEC (AcpiCmFree (ScopeName));
    }

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
    ThisTable = NameTable;
    Entries = ThisTable->Entries;


    /* Init return data */

    if (RetInfo)
    {
        RetInfo->NameTable = ThisTable;
    }


    /*
     * Search entire name table, including all linked appendages
     */

    while (ThisTable)
    {
        /*
         * Search for name in table, starting at Position.  Stop
         * searching upon examining all entries in the table.
         *
         */

        Entries = ThisTable->Entries;
        while (Position < NS_TABLE_SIZE)
        {
            /* Check for a valid entry */

            if (!Entries[Position].Name)
            {
                if (TableFull)
                {
                    /*
                     * There is room in the table for more
                     * entries, if necessary
                     */

                    TableFull = FALSE;
                    TableWithEmptySlots = ThisTable;
                    EmptySlotPosition = Position;
                }
            }

            /* Search for name in table */

            else if (Entries[Position].Name == EntryName)
            {
                /*
                 * Found matching entry.  Capture type if
                 * appropriate before returning the entry.
                 */

                /*
                 * The DefFieldDefn and BankFieldDefn cases
                 * are actually looking up the Region in which
                 * the field will be defined
                 */

                if ((INTERNAL_TYPE_DEF_FIELD_DEFN == Type) ||
                    (INTERNAL_TYPE_BANK_FIELD_DEFN == Type))
                {
                    Type = ACPI_TYPE_REGION;
                }

                /*
                 * Scope, DefAny, and IndexFieldDefn are bogus
                 * "types" which do not actually have anything
                 * to do with the type of the name being looked
                 * up.  For any other value of Type, if the type
                 * stored in the entry is Any (i.e. unknown),
                 * save the actual type.
                 */

                if (Type != INTERNAL_TYPE_SCOPE &&
                    Type != INTERNAL_TYPE_DEF_ANY &&
                    Type != INTERNAL_TYPE_INDEX_FIELD_DEFN &&
                    Entries[Position].Type == ACPI_TYPE_ANY)
                {
                    Entries[Position].Type = (UINT8) Type;
                }

                DEBUG_PRINT (TRACE_NAMES,
                    ("NsSearchNameTable: Name %4.4s (actual type 0x%X) found at %p\n",
                    &EntryName, Entries[Position].Type, &Entries[Position]));

                *RetEntry = &Entries[Position];
                return_ACPI_STATUS (AE_OK);
            }


            /* Didn't match name, move on to the next entry */

            Position++;
        }


        /*
         * Just examined last slot in this table, move on
         *  to next appendate.
         * All appendages, even to the root NT, contain
         *  NS_TABLE_SIZE entries.
         */

        PreviousTable = ThisTable;
        ThisTable = ThisTable->NextTable;

        DEBUG_PRINT (TRACE_EXEC,
            ("NsSearchNameTable: Search appendage Entries=%p\n", Entries));
        Position = 0;
    }


    /* Searched entire table, not found */

    DEBUG_PRINT (TRACE_NAMES,
        ("NsSearchNameTable: Name %4.4s (type 0x%X) not found at %p\n",
        &EntryName, Type, &Entries[Position]));


    if (RetInfo)
    {
        /*
         * Save info on if/where a slot is available
         * (name was not found)
         */

        RetInfo->TableFull  = TableFull;
        if (TableFull)
        {
            RetInfo->NameTable  = PreviousTable;
        }

        else
        {
            RetInfo->Position   = EmptySlotPosition;
            RetInfo->NameTable  = TableWithEmptySlots;
        }
    }

    return_ACPI_STATUS (AE_NOT_FOUND);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsSearchParentTree
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
 *              searching enclosing scopes in cases identified by AcpiNsLocal().
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
AcpiNsSearchParentTree (
    UINT32                  EntryName,
    ACPI_NAME_TABLE         *NameTable,
    OBJECT_TYPE_INTERNAL    Type,
    ACPI_NAMED_OBJECT       **RetEntry)
{
    ACPI_STATUS             Status;
    ACPI_NAMED_OBJECT       *ParentEntry;
    ACPI_NAMED_OBJECT       *Entries;


    FUNCTION_TRACE ("NsSearchParentTree");


    Entries = NameTable->Entries;

    /*
     * If no parent or type is "local", we won't be searching the
     * parent tree.
     */

    if (!AcpiNsLocal (Type) &&
        NameTable->ParentEntry)
    {
        ParentEntry = NameTable->ParentEntry;
        DEBUG_PRINT (TRACE_NAMES,
            ("NsSearchParentTree: Searching parent for %4.4s\n",
            &EntryName));

        /*
         * Search parents until found or we have backed up to
         * the root
         */

        while (ParentEntry)
        {
            /* Search parent scope */
            /* TBD: [Investigate] Why ACPI_TYPE_ANY? */

            Status = AcpiNsSearchNameTable (EntryName,
                                            ParentEntry->ChildTable,
                                            ACPI_TYPE_ANY,
                                            RetEntry, NULL);

            if (ACPI_SUCCESS (Status))
            {
                return_ACPI_STATUS (Status);
            }

            /*
             * Not found here, go up another level
             * (until we reach the root)
             */

            ParentEntry = AcpiNsGetParentEntry (ParentEntry);
        }

        /* Not found in parent tree */
    }

    else
    {
        if (!NameTable->ParentEntry)
        {
            DEBUG_PRINT (TRACE_NAMES,
                ("NsSearchParentTree: [%4.4s] has no parent\n",
                &EntryName));
        }

        else if (AcpiNsLocal (Type))
        {
            DEBUG_PRINT (TRACE_NAMES,
                ("NsSearchParentTree: [%4.4s] (type 0x%X) is local (no search)\n",
                &EntryName, Type));
        }
    }

    return_ACPI_STATUS (AE_NOT_FOUND);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsCreateAndLinkNewTable
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
AcpiNsCreateAndLinkNewTable (
    ACPI_NAME_TABLE         *NameTable)
{
    ACPI_NAME_TABLE         *NewTable;
    ACPI_NAMED_OBJECT       *ParentEntry;
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("NsCreateAndLinkNewTable");


    /* Sanity check on the data structure */

    if (NameTable->NextTable)
    {
        /* We should never get here (an appendage already allocated) */

        DEBUG_PRINT (ACPI_ERROR,
            ("NsCreateAndLinkNewTable: appendage %p already exists!\n",
            NameTable->NextTable));
        return (AE_AML_INTERNAL);
    }


    /*
     * We can use the parent entries from the current table
     * Since the parent information remains the same.
     */
    ParentEntry = NameTable->ParentEntry;


    /* Allocate and chain an appendage to the filled table */

    NewTable = AcpiNsAllocateNameTable (NS_TABLE_SIZE);
    if (!NewTable)
    {
        REPORT_ERROR ("Name Table appendage allocation failure");
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /*
     * Allocation successful. Init the new table.
     */
    NameTable->NextTable = NewTable;
    AcpiNsInitializeTable (NewTable, ParentEntry->ChildTable,
                            ParentEntry);

    DEBUG_PRINT (TRACE_EXEC,
        ("NsCreateAndLinkNewTable: NewTable=%p, ParentEntry=%p, ChildTable=%p\n",
        NewTable, ParentEntry, ParentEntry->ChildTable));

    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsInitializeTable
 *
 * PARAMETERS:  NewTable            - The new table to be initialized
 *              ParentTable         - The parent (owner) scope
 *              ParentEntry         - The NTE for the parent
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize a new namespace table.  Simple, but called
 *              from several places -- code should be kept in one place.
 *
 ***************************************************************************/

void
AcpiNsInitializeTable (
    ACPI_NAME_TABLE         *NewTable,
    ACPI_NAME_TABLE         *ParentTable,
    ACPI_NAMED_OBJECT       *ParentEntry)
{
    UINT8                  i;


    NewTable->ParentEntry   = ParentEntry;
    NewTable->ParentTable   = ParentTable;


    /* Init each named object entry in the table */

    for (i = 0; i < NS_TABLE_SIZE; i++)
    {
        NewTable->Entries[i].ThisIndex = i;
        NewTable->Entries[i].DataType = ACPI_DESC_TYPE_NAMED;
    }

    DEBUG_PRINT (TRACE_NAMES, ("NsInitializeTable: %x\n", NewTable));
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsInitializeEntry
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
AcpiNsInitializeEntry (
    ACPI_WALK_STATE         *WalkState,
    ACPI_NAME_TABLE         *NameTable,
    UINT32                  Position,
    UINT32                  EntryName,
    OBJECT_TYPE_INTERNAL    Type)
{
    ACPI_NAMED_OBJECT       *NewEntry;
    UINT16                  OwnerId = TABLE_ID_DSDT;
    ACPI_NAMED_OBJECT       *Entries;


    FUNCTION_TRACE ("NsInitializeEntry");


    /*
     * Get the owner ID from the Walk state
     * The owner ID is used to track table deletion and
     * deletion of objects created by methods
     */
    if (WalkState)
    {
        OwnerId = WalkState->OwnerId;
    }

    /* The new entry is given by two parameters */

    Entries = NameTable->Entries;
    NewEntry = &Entries[Position];

    /* Init the new entry */

    NewEntry->DataType       = ACPI_DESC_TYPE_NAMED;
    NewEntry->Name           = EntryName;
    NewEntry->OwnerId        = OwnerId;
    NewEntry->ReferenceCount = 1;


    /*
     * If adding a name with unknown type, or having to
     * add the region in order to define fields in it, we
     * have a forward reference.
     */

    if ((ACPI_TYPE_ANY == Type) ||
        (INTERNAL_TYPE_DEF_FIELD_DEFN == Type) ||
        (INTERNAL_TYPE_BANK_FIELD_DEFN == Type))
    {
        /*
         * We don't want to abort here, however!
         * We will fill in the actual type when the
         * real definition is found later.
         */

        DEBUG_PRINT (ACPI_INFO,
            ("[%4.4s] is a forward reference into the namespace\n",
            &EntryName));

    }

    /*
     * The DefFieldDefn and BankFieldDefn cases are actually
     * looking up the Region in which the field will be defined
     */

    if ((INTERNAL_TYPE_DEF_FIELD_DEFN == Type) ||
        (INTERNAL_TYPE_BANK_FIELD_DEFN == Type))
    {
        Type = ACPI_TYPE_REGION;
    }

    /*
     * Scope, DefAny, and IndexFieldDefn are bogus "types" which do
     * not actually have anything to do with the type of the name
     * being looked up.  Save any other value of Type as the type of
     * the entry.
     */

    if ((Type != INTERNAL_TYPE_SCOPE) &&
        (Type != INTERNAL_TYPE_DEF_ANY) &&
        (Type != INTERNAL_TYPE_INDEX_FIELD_DEFN))
    {
        NewEntry->Type = (UINT8) Type;
    }

    DEBUG_PRINT (TRACE_NAMES,
        ("NsInitializeEntry: %4.4s added to %p at %p\n",
        &EntryName, NameTable, NewEntry));

    return_VOID;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsSearchAndEnter
 *
 * PARAMETERS:  EntryName           - Ascii ACPI name to search for (4 chars)
 *              *NameTable          - Starting table where search will begin
 *              InterpreterMode     - Add names only in MODE_LoadPassX.  Otherwise,
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
 *              In IMODE_EXECUTE, search only.
 *              In other modes, search and add if not found.
 *
 ***************************************************************************/

ACPI_STATUS
AcpiNsSearchAndEnter (
    UINT32                  EntryName,
    ACPI_WALK_STATE         *WalkState,
    ACPI_NAME_TABLE         *NameTable,
    OPERATING_MODE          InterpreterMode,
    OBJECT_TYPE_INTERNAL    Type,
    UINT32                  Flags,
    ACPI_NAMED_OBJECT       **RetEntry)
{
    UINT32                  Position;       /* position in table */
    ACPI_STATUS             Status;
    NS_SEARCH_DATA          SearchInfo;
    ACPI_NAMED_OBJECT       *Entry;
    ACPI_NAMED_OBJECT       *Entries;


    FUNCTION_TRACE ("NsSearchAndEnter");


    /* Parameter validation */

    if (!NameTable || !EntryName || !RetEntry)
    {
        REPORT_ERROR ("NsSearchAndEnter: bad parameter");
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /* Name must consist of printable characters */

    if (!AcpiCmValidAcpiName (EntryName))
    {
        DEBUG_PRINT (ACPI_ERROR,
            ("NsSearchAndEnter:  *** Bad character in name: %08lx *** \n",
            EntryName));

        REPORT_ERROR ("NsSearchAndEnter: Bad character in Entry Name");
        return_ACPI_STATUS (AE_BAD_CHARACTER);
    }


    /* Try to find the name in the table specified by the caller */

    *RetEntry = ENTRY_NOT_FOUND;
    Status = AcpiNsSearchNameTable (EntryName, NameTable,
                                    Type, RetEntry, &SearchInfo);
    if (Status != AE_NOT_FOUND)
    {
        /*
         * Either found it or there was an error
         * -- finished either way
         */

        return_ACPI_STATUS (Status);
    }


    /*
     * Not found in the table.  If we are NOT performing the
     * first pass (name entry) of loading the namespace, search
     * the parent tree (all the way to the root if necessary.)
     * We don't want to perform the parent search when the
     * namespace is actually being loaded.  We want to perform
     * the search when namespace references are being resolved
     * (load pass 2) and during the execution phase.
     */

    if ((InterpreterMode != IMODE_LOAD_PASS1) &&
        (Flags & NS_SEARCH_PARENT))
    {
        /*
         * Not found in table - search parent tree according
         * to ACPI specification
         */

        Status = AcpiNsSearchParentTree (EntryName, NameTable,
                                            Type, RetEntry);

        if (ACPI_SUCCESS (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }


    /*
     * In execute mode, just search, never add names.  Exit now.
     */

    if (InterpreterMode == IMODE_EXECUTE)
    {
        DEBUG_PRINT (TRACE_NAMES,
            ("NsSearchAndEnter: %4.4s Not found in %p [Not adding]\n",
            &EntryName, NameTable));

        return_ACPI_STATUS (AE_NOT_FOUND);
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
        Status = AcpiNsCreateAndLinkNewTable (NameTable);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        /* Point to the first slot in the new table */

        NameTable = NameTable->NextTable;
        Position = 0;
    }


    /*
     * There is room in the table (or we have just allocated a new one.)
     * Initialize the new entry
     */

    AcpiNsInitializeEntry (WalkState, NameTable, Position,
                            EntryName, Type);


    Entries     = NameTable->Entries;
    *RetEntry   = &Entries[Position];
    Entry       = &Entries[Position];

    /*
     * Increment the reference count(s) of all parents up to
     * the root!
     */

    while (AcpiNsGetParentEntry (Entry))
    {
        Entry = AcpiNsGetParentEntry (Entry);
        Entry->ReferenceCount++;
    }


    return_ACPI_STATUS (AE_OK);
}

