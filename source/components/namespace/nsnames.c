
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


#define __NSNAMES_C__

#include <acpi.h>
#include <amlcode.h>
#include <interpreter.h>
#include <namespace.h>


#define _THIS_MODULE        "nsnames.c"
#define _COMPONENT          NAMESPACE


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", '1', "NsNameOfScope: allocation failure", "NsNameOfScope: allocation failure"},
    {"0001", '1', "Current scope pointer trashed", "Current scope pointer trashed"},
    {"0002", '1', "NsFindNames: allocation failure", "NsFindNames: allocation failure"},
    {NULL, 'I', NULL, NULL}
};



/****************************************************************************
 *
 * FUNCTION:    NsNameOfScope
 *
 * PARAMETERS:  *EntryToSearch          - Scope whose name is needed
 *
 * RETURN:      Pointer to storage containing the fully qualified name of
 *              the scope, in Label format (all segments strung together
 *              with no separators)
 *
 * DESCRIPTION: Used via NsNameOfCurrentScope() and NsLastFQN()
 *              for label generation in the interpreter, and for debug
 *              printing in NsSearchTable().
 *
 ***************************************************************************/

char *
NsNameOfScope (
    NAME_TABLE_ENTRY        *EntryToSearch)
{
    NAME_TABLE_ENTRY        *Temp = NULL;
    char                    *NameBuffer;
    size_t                  Size;


    FUNCTION_TRACE ("NsNameOfScope");


    if (!RootObject->Scope || !EntryToSearch)
    {
        /* 
         * If the name space has not been initialized,
         * this function should not have been called.
         */
        FUNCTION_EXIT;
        return NULL;
    }

    /* Calculate required buffer size based on depth below root NT */
    
    for (Size = 1, Temp = EntryToSearch;
            Temp->ParentScope;
            Temp = Temp->ParentScope)
    {
        Size += 4;
    }


    NameBuffer = LocalCallocate (Size + 1);
    if (!NameBuffer)
    {
        REPORT_ERROR (&KDT[0]);
        FUNCTION_EXIT;
        return NULL;
    }
    

    /* Store terminator byte, then build name backwards */
    
    NameBuffer[Size] = '\0';
    while ((Size > 4) && EntryToSearch->ParentScope)
    {
        Size -= 4;
        *(UINT32 *) (NameBuffer + Size) = 
                        *(UINT32 *) NsFindParentName (EntryToSearch, 0);
        EntryToSearch = EntryToSearch->ParentScope;
    }

    NameBuffer[--Size] = AML_RootPrefix;

    if (Size != 0)
    {
        DEBUG_PRINT (ACPI_ERROR, ("NsNameOfScope:  Bad pointer returned; size = %d\n", Size));
    }

    FUNCTION_EXIT;
    return NameBuffer;
}


/****************************************************************************
 *
 * FUNCTION:    NsNameOfCurrentScope
 *
 * PARAMETERS:  none
 *
 * RETURN:      pointer to storage containing the name of the current scope
 *
 ***************************************************************************/

char *
NsNameOfCurrentScope (void)
{
    FUNCTION_TRACE ("NsNameOfCurrentScope");


    if (CurrentScope && CurrentScope->Scope)
    {
        FUNCTION_EXIT;
        return NsNameOfScope (CurrentScope->Scope);
    }
    
    REPORT_ERROR (&KDT[1]);

    FUNCTION_EXIT;
    return NULL;
}


/****************************************************************************
 *
 * FUNCTION:    NsHandleToPathname
 *
 * PARAMETERS:  TargetHandle            - Handle of nte whose name is to be found
 *              BufSize                 - Size of the buffer provided 
 *              UserBuffer              - Where the pathname is returned
 *
 * RETURN:      Status, Buffer is filled with pathname if status == AE_OK
 *
 * DESCRIPTION: Build and return a full namespace pathname
 *
 ***************************************************************************/

ACPI_STATUS
NsHandleToPathname (
    ACPI_HANDLE             TargetHandle, 
    UINT32                  BufSize, 
    char                    *UserBuffer)
{
    NAME_TABLE_ENTRY        *EntryToSearch = NULL;
    NAME_TABLE_ENTRY        *Temp = NULL;
    size_t                  FqnSize = 0;
    size_t                  Size;
    INT32                   TraceFQN = 0;


    FUNCTION_TRACE ("NsHandleToPathname");


    if (!RootObject->Scope || !TargetHandle)
    {
        /* 
         * If the name space has not been initialized,
         * this function should not have been called.
         */

        FUNCTION_EXIT;
        return AE_NO_NAMESPACE;
    }

    if (!(EntryToSearch = NsConvertHandleToEntry (TargetHandle)))
    {
        FUNCTION_EXIT;
        return AE_BAD_PARAMETER;
    }

    /* Compute length of pathname as 5 * number of name segments */
    
    for (Size = 5, Temp = EntryToSearch;
          Temp->ParentScope;
          Temp = Temp->ParentScope)
    {
        Size += 5;
    }

    
    /* Check if the user buffer is sufficiently large */

    FqnSize = Size + 1;
    if (FqnSize > BufSize)
    {
        FUNCTION_EXIT;
        return AE_BUFFER_OVERFLOW;
    }

          
    /* Store null termination */
    
    UserBuffer[Size] = '\0';
    Size -= 4;
    
    if (TraceFQN)
    {
        DEBUG_PRINT (ACPI_INFO, ("%d:%08lx \n", Size, EntryToSearch->Name));
    }
    
    *(UINT32 *) (UserBuffer + Size) = EntryToSearch->Name;
    UserBuffer[--Size] = '.';

    /* Build name backwards, putting "." between segments */
    
    while ((Size > 4) && EntryToSearch)
    {
        Size -= 4;
        *(UINT32 *) (UserBuffer + Size) = 
                        *(UINT32 *) NsFindParentName (EntryToSearch, TraceFQN);
        
        if (TraceFQN)
        {
            DEBUG_PRINT (ACPI_INFO,
                            ("%d:%08lx \n", Size, *(UINT32 *)(UserBuffer + Size)));
        }

        UserBuffer[--Size] = '.';
        EntryToSearch = EntryToSearch->ParentScope;
    }

    /* Overlay the "." preceding the first segment with root name "\" */
    
    UserBuffer[Size] = '\\';
    FUNCTION_EXIT;
    return AE_OK;
}



/****************************************************************************
 * 
 * FUNCTION:    NsPatternMatch
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
NsPatternMatch (
    NAME_TABLE_ENTRY        *ObjEntry, 
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
 * FUNCTION:    NsNameCompare
 *
 * PARAMETERS:  ObjHandle       - A namespace entry
 *              Level           - Current nesting level
 *              Context         - A FIND_CONTEXT structure
 *
 * DESCRIPTION: A UserFunction called by NsWalkNamespace().  It performs
 *              a pattern match for NsLowFindNames(), and updates the list
 *              and count as required.
 *
 ***************************************************************************/

void *
NsNameCompare (
    ACPI_HANDLE             ObjHandle, 
    UINT32                  Level, 
    void                    *Context)
{
    FIND_CONTEXT            *Find = Context;


    /* Match, yes or no? */

    if (NsPatternMatch ((NAME_TABLE_ENTRY *) ObjHandle, Find->SearchFor))
    {
        /* name matches pattern */
        
        if (Find->List)
        {
            DEBUG_PRINT (TRACE_NAMES, ("FindName: match found: %.4s\n",
                            &((NAME_TABLE_ENTRY *) ObjHandle)->Name));

            Find->List[*(Find->Count)] = ObjHandle;
        }
        
        ++*(Find->Count);
    }

    return NULL;        /* Don't terminate the walk */
}


/****************************************************************************
 * 
 * FUNCTION:    NsLowFindNames
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
NsLowFindNames (
    NAME_TABLE_ENTRY        *ThisEntry, 
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
        
        FUNCTION_EXIT;
        return;
    }

    /* Init the context structure used by compare routine */

    Find.List       = List;
    Find.Count      = Count;
    Find.SearchFor  = SearchFor;

    /* Walk the namespace and find all matches */

    AcpiWalkNamespace (TYPE_Any, (ACPI_HANDLE) ThisEntry, MaxDepth, NsNameCompare, &Find, NULL);

    if (List)
    {
        /* null-terminate the output array */
        
        List[*Count] = (ACPI_HANDLE) 0;
    }

    FUNCTION_EXIT;
    return;
}


/****************************************************************************
 *
 * FUNCTION:    NsFindNames
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
NsFindNames (
    char                    *SearchFor, 
    ACPI_HANDLE             StartHandle, 
    INT32                   MaxDepth)
{
    ACPI_HANDLE             *List = NULL;
    INT32                   Count;


    FUNCTION_TRACE ("NsFindNames");


    if (!RootObject->Scope)
    {
        /* 
         * If the name space has not been initialized,
         * there surely are no matching names.
         */
        FUNCTION_EXIT;
        return NULL;
    }

    if (NS_ALL == StartHandle)
    {
        /*  base is root    */

        StartHandle = RootObject;
    }
    
    else if (((NAME_TABLE_ENTRY *) StartHandle)->Scope)
    {
        /*  base has children to search */

        StartHandle = ((NAME_TABLE_ENTRY *) StartHandle)->Scope;
    }
    
    else
    {
        /* 
         * If base is not the root and has no children,
         * there is nothing to search.
         */
        FUNCTION_EXIT;
        return NULL;
    }

    if (!SearchFor)
    {
        /*  search name not specified   */

        SearchFor = "????";
    }

    
    /* Pass 1.  Get required buffer size, don't try to build list */
    
    Count = 0;
    CheckTrash ("NsFindNames before count");

    NsLowFindNames (StartHandle, SearchFor, &Count, NULL, MaxDepth);
    CheckTrash ("NsFindNames after count");
    
    if (0 == Count)
    {
        FUNCTION_EXIT;
        return NULL;
    }

    Count++;                                            /* Allow for trailing null */
    List = LocalCallocate (Count * sizeof(ACPI_HANDLE));
    if (!List)
    {
        REPORT_ERROR (&KDT[2]);
        FUNCTION_EXIT;
        return NULL;
    }

    /* Pass 2.  Fill buffer */

    Count = 0;
    CheckTrash ("NsFindNames before list");

    NsLowFindNames (StartHandle, SearchFor, &Count, List, MaxDepth);
    CheckTrash ("NsFindNames after list");

    FUNCTION_EXIT;
    return List;
}



