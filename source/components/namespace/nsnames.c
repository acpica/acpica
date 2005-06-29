
/******************************************************************************
 *
 * Module Name: nsnames - Name manipulation and search
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

#define __NSNAMES_C__

#include "acpi.h"
#include "amlcode.h"
#include "interp.h"
#include "namesp.h"


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nsnames");


/****************************************************************************
 *
 * FUNCTION:    AcpiNsNameOfScope
 *
 * PARAMETERS:  Scope           - Scope whose name is needed
 *
 * RETURN:      Pointer to storage containing the fully qualified name of
 *              the scope, in Label format (all segments strung together
 *              with no separators)
 *
 * DESCRIPTION: Used via AcpiNsNameOfCurrentScope() and AcpiNsLastFQN()
 *              for label generation in the interpreter, and for debug
 *              printing in AcpiNsSearchTable().
 *
 ***************************************************************************/

char *
AcpiNsNameOfScope (
    ACPI_NAME_TABLE         *Scope)
{
    char                    *NameBuffer;
    UINT32                  Size;
    ACPI_NAME               Name;
    ACPI_NAMED_OBJECT       *EntryToSearch;
    ACPI_NAMED_OBJECT       *ParentEntry;


    FUNCTION_TRACE ("NsNameOfScope");


    if (!AcpiGbl_RootObject->ChildTable || !Scope)
    {
        /*
         * If the name space has not been initialized,
         * this function should not have been called.
         */
        return_PTR (NULL);
    }

    EntryToSearch = Scope->Entries;


    /* Calculate required buffer size based on depth below root NT */

    Size = 1;
    ParentEntry = EntryToSearch;
    while (ParentEntry)
    {
        ParentEntry = AcpiNsGetParentEntry (ParentEntry);
        if (ParentEntry)
        {
            Size += ACPI_NAME_SIZE;
        }
    }


    /* Allocate the buffer */

    NameBuffer = AcpiCmCallocate (Size + 1);
    if (!NameBuffer)
    {
        REPORT_ERROR ("NsNameOfScope: allocation failure");
        return_PTR (NULL);
    }


    /* Store terminator byte, then build name backwards */

    NameBuffer[Size] = '\0';
    while ((Size > ACPI_NAME_SIZE) &&
        AcpiNsGetParentEntry (EntryToSearch))
    {
        Size -= ACPI_NAME_SIZE;
        Name = AcpiNsFindParentName (EntryToSearch);

        /* Put the name into the buffer */

        MOVE_UNALIGNED32_TO_32 ((NameBuffer + Size), &Name);
        EntryToSearch = AcpiNsGetParentEntry (EntryToSearch);
    }

    NameBuffer[--Size] = AML_ROOT_PREFIX;

    if (Size != 0)
    {
        DEBUG_PRINT (ACPI_ERROR,
            ("NsNameOfScope:  Bad pointer returned; size = %d\n", Size));
    }

    return_PTR (NameBuffer);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsNameOfCurrentScope
 *
 * PARAMETERS:  none
 *
 * RETURN:      pointer to storage containing the name of the current scope
 *
 ***************************************************************************/

char *
AcpiNsNameOfCurrentScope (
    ACPI_WALK_STATE         *WalkState)
{
    char                    *ScopeName;


    FUNCTION_TRACE ("NsNameOfCurrentScope");


    if (WalkState && WalkState->ScopeInfo)
    {
        ScopeName =
            AcpiNsNameOfScope (WalkState->ScopeInfo->Scope.NameTable);

        return_PTR (ScopeName);
    }

    REPORT_ERROR ("Current scope pointer is invalid");

    return_PTR (NULL);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsHandleToPathname
 *
 * PARAMETERS:  TargetHandle            - Handle of nte whose name is to be found
 *              BufSize                 - Size of the buffer provided
 *              UserBuffer              - Where the pathname is returned
 *
 * RETURN:      Status, Buffer is filled with pathname if status == AE_OK
 *
 * DESCRIPTION: Build and return a full namespace pathname
 *
 * MUTEX:       Locks Namespace
 *
 ***************************************************************************/

ACPI_STATUS
AcpiNsHandleToPathname (
    ACPI_HANDLE             TargetHandle,
    UINT32                  *BufSize,
    char                    *UserBuffer)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_NAMED_OBJECT       *EntryToSearch = NULL;
    ACPI_NAMED_OBJECT       *Temp = NULL;
    UINT32                  PathLength = 0;
    UINT32                  Size;
    UINT32                  UserBufSize;
    ACPI_NAME               Name;
    BOOLEAN                 NamespaceWasLocked;


    FUNCTION_TRACE_PTR ("NsHandleToPathname", TargetHandle);


    if (!AcpiGbl_RootObject->ChildTable || !TargetHandle)
    {
        /*
         * If the name space has not been initialized,
         * this function should not have been called.
         */

        return_ACPI_STATUS (AE_NO_NAMESPACE);
    }

    NamespaceWasLocked = AcpiGbl_AcpiMutexInfo[ACPI_MTX_NAMESPACE].Locked;
    if (!NamespaceWasLocked)
    {
        AcpiCmAcquireMutex (ACPI_MTX_NAMESPACE);
    }

    EntryToSearch = AcpiNsConvertHandleToEntry (TargetHandle);
    if (!EntryToSearch)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /*
     * Compute length of pathname as 5 * number of name segments.
     * Go back up the parent tree to the root
     */
    for (Size = 0, Temp = EntryToSearch;
          AcpiNsGetParentEntry (Temp);
          Temp = AcpiNsGetParentEntry (Temp))
    {
        Size += PATH_SEGMENT_LENGTH;
    }

    /* Set return length to the required path length */

    PathLength = Size + 1;
    UserBufSize = *BufSize;
    *BufSize = PathLength;

    /* Check if the user buffer is sufficiently large */

    if (PathLength > UserBufSize)
    {
        Status = AE_BUFFER_OVERFLOW;
        goto UnlockAndExit;
    }

    /* Store null terminator */

    UserBuffer[Size] = 0;
    Size -= ACPI_NAME_SIZE;

    /* Put the original ACPI name at the end of the path */

    MOVE_UNALIGNED32_TO_32 ((UserBuffer + Size),
                            &EntryToSearch->Name);

    UserBuffer[--Size] = PATH_SEPARATOR;

    /* Build name backwards, putting "." between segments */

    while ((Size > ACPI_NAME_SIZE) && EntryToSearch)
    {
        Size -= ACPI_NAME_SIZE;
        Name = AcpiNsFindParentName (EntryToSearch);
        MOVE_UNALIGNED32_TO_32 ((UserBuffer + Size), &Name);

        UserBuffer[--Size] = PATH_SEPARATOR;
        EntryToSearch = AcpiNsGetParentEntry (EntryToSearch);
    }

    /*
     * Overlay the "." preceding the first segment with
     * the root name "\"
     */

    UserBuffer[Size] = '\\';

    DEBUG_PRINT (TRACE_EXEC,
        ("NsHandleToPathname: Len=%d, %s \n",
        PathLength, UserBuffer));


UnlockAndExit:

    if (!NamespaceWasLocked)
    {
        AcpiCmReleaseMutex (ACPI_MTX_NAMESPACE);
    }

    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsPatternMatch
 *
 * PARAMETERS:  ObjEntry        - A namespace entry
 *              SearchFor       - Wildcard pattern string
 *
 * DESCRIPTION: Matches a namespace name against a wildcard pattern.  Only
 *              a very simple pattern - 4 chars, either a valid char or a "?"
 *              to match any.
 *
 ***************************************************************************/

BOOLEAN
AcpiNsPatternMatch (
    ACPI_NAMED_OBJECT       *ObjEntry,
    char                    *SearchFor)
{
    INT32                   i;


    for (i = 0; i < ACPI_NAME_SIZE; i++)
    {
        if (SearchFor[i] != '?' &&
            SearchFor[i] != ((char *) &ObjEntry->Name)[i])
        {
            /* No match */

            return FALSE;
        }
    }

    /* name matches pattern */

    return TRUE;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsNameCompare
 *
 * PARAMETERS:  ObjHandle       - A namespace entry
 *              Level           - Current nesting level
 *              Context         - A FIND_CONTEXT structure
 *
 * DESCRIPTION: A UserFunction called by AcpiNsWalkNamespace().  It performs
 *              a pattern match for AcpiNsLowFindNames(), and updates the list
 *              and count as required.
 *
 ***************************************************************************/

ACPI_STATUS
AcpiNsNameCompare (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *Context,
    void                    **ReturnValue)
{
    FIND_CONTEXT            *Find = Context;


    /* Match, yes or no? */

    if (AcpiNsPatternMatch ((ACPI_NAMED_OBJECT*) ObjHandle,
                            Find->SearchFor))
    {
        /* Name matches pattern */

        if (Find->List)
        {
            DEBUG_PRINT (TRACE_NAMES,
                ("FindName: Match found: %.4s\n",
                &((ACPI_NAMED_OBJECT*) ObjHandle)->Name));

            Find->List[*(Find->Count)] = ObjHandle;
        }

        ++*(Find->Count);
    }

     /* Don't terminate the walk */
    return AE_OK;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsLowFindNames
 *
 * PARAMETERS:  *ThisEntry          - Table to be searched
 *              *SearchFor          - Pattern to be found.
 *                                    4 bytes, ? matches any character.
 *              *Count              - Output count of matches found.
 *                                    Outermost caller should preset to 0
 *              List[]              - Output array of handles.  If
 *                                    null, only the count is obtained.
 *              MaxDepth            - Maximum depth of search.  Use
 *                                    INT_MAX for an effectively
 *                                    unlimited depth.
 *
 * DESCRIPTION: Low-level find name.
 *              Traverse the name space finding names which match a search
 *              pattern, and return an array of handles in List[].
 *
 ***************************************************************************/

void
AcpiNsLowFindNames (
    ACPI_NAMED_OBJECT       *ThisEntry,
    char                    *SearchFor,
    INT32                   *Count,
    ACPI_HANDLE             List[],
    INT32                   MaxDepth)
{
    FIND_CONTEXT            Find;


    FUNCTION_TRACE ("NsLowFindNames");


    if (0 == MaxDepth || !ThisEntry || !SearchFor || !Count)
    {
        /*
         * Zero requested depth, nothing to search,
         * nothing to search for, or count pointer bad
         */

        return_VOID;
    }

    /* Init the context structure used by compare routine */

    Find.List       = List;
    Find.Count      = Count;
    Find.SearchFor  = SearchFor;

    /* Walk the namespace and find all matches */

    AcpiNsWalkNamespace (ACPI_TYPE_ANY, (ACPI_HANDLE) ThisEntry,
                        MaxDepth, NS_WALK_NO_UNLOCK,
                        AcpiNsNameCompare, &Find, NULL);

    if (List)
    {
        /* null-terminate the output array */

        List[*Count] = (ACPI_HANDLE) 0;
    }

    return_VOID;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsFindNames

 *
 * PARAMETERS:  *SearchFor          - pattern to be found.
 *                                    4 bytes, ? matches any character.
 *                                    If NULL, "????" will be used.
 *              StartHandle         - Root of subtree to be searched, or
 *                                    NS_ALL to search the entire namespace
 *              MaxDepth            - Maximum depth of search.  Use INT_MAX
 *                                    for an effectively unlimited depth.
 *
 * DESCRIPTION: Traverse the name space finding names which match a search
 *              pattern, and return an array of handles.  The end of the
 *              array is marked by the value (ACPI_HANDLE)0.  A return value
 *              of (ACPI_HANDLE *)0 indicates that no matching names were
 *              found or that space for the list could not be allocated.
 *              if StartHandle is NS_ALL (null) search from the root,
 *              else it is a handle whose children are to be searched.
 *
 ***************************************************************************/

ACPI_HANDLE *
AcpiNsFindNames (
    char                    *SearchFor,
    ACPI_HANDLE             StartHandle,
    INT32                   MaxDepth)
{
    ACPI_HANDLE             *List = NULL;
    INT32                   Count;


    FUNCTION_TRACE ("NsFindNames");


    if (!AcpiGbl_RootObject->ChildTable)
    {
        /*
         * If the name space has not been initialized,
         * there surely are no matching names.
         */
        return_PTR (NULL);
    }

    if (NS_ALL == StartHandle)
    {
        /* base is root */

        StartHandle = AcpiGbl_RootObject;
    }

    else if (((ACPI_NAMED_OBJECT *) StartHandle)->ChildTable)
    {
        /* base has children to search */

        StartHandle =
            ((ACPI_NAMED_OBJECT *) StartHandle)->ChildTable->Entries;
    }

    else
    {
        /*
         * If base is not the root and has no children,
         * there is nothing to search.
         */
        return_PTR (NULL);
    }

    if (!SearchFor)
    {
        /* Search name not specified */

        SearchFor = "????";
    }


    /* Pass 1.  Get required buffer size, don't try to build list */

    Count = 0;
    AcpiNsLowFindNames (StartHandle, SearchFor, &Count,
                        NULL, MaxDepth);

    if (0 == Count)
    {
        return_PTR (NULL);
    }

    /* Allow for trailing null */
    Count++;
    
    List = AcpiCmCallocate (Count * sizeof(ACPI_HANDLE));
    if (!List)
    {
        REPORT_ERROR ("NsFindNames: allocation failure");
        return_PTR (NULL);
    }

    /* Pass 2.  Fill buffer */

    Count = 0;
    AcpiNsLowFindNames (StartHandle, SearchFor, &Count, List, MaxDepth);

    return_PTR (List);
}


