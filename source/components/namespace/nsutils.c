
/******************************************************************************
 *
 * Module Name: nsutils - Utilities for accessing ACPI namespace, accessing
 *                          parents and siblings and Scope manipulation
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

#define __NSUTILS_C__

#include "acpi.h"
#include "namesp.h"
#include "interp.h"
#include "amlcode.h"
#include "tables.h"

#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nsutils");


/****************************************************************************
 *
 * FUNCTION:    AcpiNsValidRootPrefix
 *
 * PARAMETERS:  Prefix          - Character to be checked
 *
 * RETURN:      TRUE if a valid prefix
 *
 * DESCRIPTION: Check if a character is a valid ACPI Root prefix
 *
 ***************************************************************************/

BOOLEAN
AcpiNsValidRootPrefix (
    char                    Prefix)
{

    return ((BOOLEAN) (Prefix == '\\'));
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsValidPathSeparator
 *
 * PARAMETERS:  Sep              - Character to be checked
 *
 * RETURN:      TRUE if a valid path separator
 *
 * DESCRIPTION: Check if a character is a valid ACPI path separator
 *
 ***************************************************************************/

BOOLEAN
AcpiNsValidPathSeparator (
    char                    Sep)
{

    return ((BOOLEAN) (Sep == '.'));
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsGetType
 *
 * PARAMETERS:  Handle              - Handle of nte to be examined
 *
 * RETURN:      Type field from nte whose handle is passed
 *
 ***************************************************************************/

OBJECT_TYPE_INTERNAL
AcpiNsGetType (
    ACPI_HANDLE             handle)
{
    FUNCTION_TRACE ("NsGetType");


    if (!handle)
    {
        /*  Handle invalid  */

        REPORT_WARNING ("NsGetType: Null handle");
        return_VALUE (ACPI_TYPE_ANY);
    }

    return_VALUE (((ACPI_NAMED_OBJECT*) handle)->Type);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsLocal
 *
 * PARAMETERS:  Type            - A namespace object type
 *
 * RETURN:      LOCAL if names must be found locally in objects of the
 *              passed type, 0 if enclosing scopes should be searched
 *
 ***************************************************************************/

INT32
AcpiNsLocal (
    OBJECT_TYPE_INTERNAL    Type)
{
    FUNCTION_TRACE ("NsLocal");


    if (!AcpiCmValidObjectType (Type))
    {
        /*  type code out of range  */

        REPORT_WARNING ("NsLocal: Invalid Object Type");
        return_VALUE (NSP_NORMAL);
    }

    return_VALUE ((INT32) AcpiGbl_NsProperties[Type] & NSP_LOCAL);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsInternalizeName
 *
 * PARAMETERS:  *ExternalName             - External representation of name
 *              **Converted Name        - Where to return the resulting
 *                                        internal represention of the name
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert an external representation (e.g. "\_PR_.CPU0")
 *              to internal form (e.g. 5c 2f 02 5f 50 52 5f 43 50 55 30)
 *
 ****************************************************************************/

ACPI_STATUS
AcpiNsInternalizeName (
    char                    *ExternalName,
    char                    **ConvertedName)
{
    char                    *Result = NULL;
    char                    *InternalName;
    ACPI_SIZE               NumSegments;
    BOOLEAN                 FullyQualified = FALSE;
    UINT32                  i;


    FUNCTION_TRACE ("NsInternalizeName");


    if ((!ExternalName)      ||
        (*ExternalName == 0) ||
        (!ConvertedName))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /*
     * For the internal name, the required length is 4 bytes
     * per segment, plus 1 each for RootPrefix, MultiNamePrefixOp,
     * segment count, trailing null (which is not really needed,
     * but no there's harm in putting it there)
     *
     * strlen() + 1 covers the first NameSeg, which has no
     * path separator
     */

    if (AcpiNsValidRootPrefix (ExternalName[0]))
    {
        FullyQualified = TRUE;
        ExternalName++;
    }


    /*
     * Determine the number of ACPI name "segments" by counting
     * the number of path separators within the string.  Start
     * with one segment since the segment count is (# separators)
     * + 1, and zero separators is ok.
     */

    NumSegments = 1;
    for (i = 0; ExternalName[i]; i++)
    {
        if (AcpiNsValidPathSeparator (ExternalName[i]))
        {
            NumSegments++;
        }
    }


    /* We need a segment to store the internal version of the name */

    InternalName = AcpiCmCallocate ((ACPI_NAME_SIZE * NumSegments) + 4);
    if (!InternalName)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }


    /* Setup the correct prefixes, counts, and pointers */

    if (FullyQualified)
    {
        InternalName[0] = '\\';
        InternalName[1] = AML_MULTI_NAME_PREFIX_OP;
        InternalName[2] = (char) NumSegments;
        Result = &InternalName[3];
    }
    else
    {
        InternalName[0] = AML_MULTI_NAME_PREFIX_OP;
        InternalName[1] = (char) NumSegments;
        Result = &InternalName[2];
    }


    /* Build the name (minus path separators) */

    for (; NumSegments; NumSegments--)
    {
        for (i = 0; i < ACPI_NAME_SIZE; i++)
        {
            if (AcpiNsValidPathSeparator (*ExternalName) ||
               (*ExternalName == 0))
            {
                /*
                 * Pad the segment with underscore(s) if
                 * segment is short
                 */

                Result[i] = '_';
            }

            else
            {
                /* Convert char to uppercase and save it */

                Result[i] = (char) TOUPPER (*ExternalName);
                ExternalName++;
            }

        }

        /* Now we must have a path separator, or the pathname is bad */

        if (!AcpiNsValidPathSeparator (*ExternalName) &&
            (*ExternalName != 0))
        {
            AcpiCmFree (InternalName);
            return_ACPI_STATUS (AE_BAD_PARAMETER);
        }

        /* Move on the next segment */

        ExternalName++;
        Result += ACPI_NAME_SIZE;
    }


    /* Return the completed name */

    /* Terminate the string! */
    *Result = 0;
    *ConvertedName = InternalName;


    if (FullyQualified)
    {
        DEBUG_PRINT (TRACE_EXEC,
            ("NsInternalizeName: returning [%p] (abs) \"\\%s\"\n",
            InternalName, &InternalName[3]));
    }
    else
    {
        DEBUG_PRINT (TRACE_EXEC,
            ("NsInternalizeName: returning [%p] (rel) \"%s\"\n",
            InternalName, &InternalName[2]));
    }

    return_ACPI_STATUS (AE_OK);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsExternalizeName
 *
 * PARAMETERS:  *InternalName          - Internal representation of name
 *              **ConvertedName        - Where to return the resulting
 *                                        external representation of name
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert internal name (e.g. 5c 2f 02 5f 50 52 5f 43 50 55 30)
 *              to its external form (e.g. "\_PR_.CPU0")
 *
 ****************************************************************************/

ACPI_STATUS
AcpiNsExternalizeName (
    UINT32                  InternalNameLength,
    char                    *InternalName,
    UINT32                  *ConvertedNameLength,
    char                    **ConvertedName)
{
    UINT32                  PrefixLength = 0;
    UINT32                  NamesIndex = 0;
    UINT32                  NamesCount = 0;
    UINT32                  i = 0;
    UINT32                  j = 0;

    FUNCTION_TRACE ("NsExternalizeName");

    if (InternalNameLength < 0 ||
        !InternalName ||
        !ConvertedNameLength ||
        !ConvertedName)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /*
     * Check for a prefix (one '\' | one or more '^').
     */
    switch (InternalName[0])
    {
    case '\\':
        PrefixLength = 1;
        break;

    case '^':
        for (i = 0; i < InternalNameLength; i++)
        {
            if (InternalName[i] != '^')
            {
                PrefixLength = i + 1;
            }
        }

        if (i == InternalNameLength)
        {
            PrefixLength = i;
        }

        break;
    }

    /*
     * Check for object names.  Note that there could be 0-255 of these
     * 4-byte elements.
     */
    if (PrefixLength < InternalNameLength)
    {
        switch (InternalName[PrefixLength])
        {

        /* <count> 4-byte names */

        case AML_MULTI_NAME_PREFIX_OP:
            NamesIndex = PrefixLength + 2;
            NamesCount = (UINT32) InternalName[PrefixLength + 1];
            break;


        /* two 4-byte names */

        case AML_DUAL_NAME_PREFIX:
            NamesIndex = PrefixLength + 1;
            NamesCount = 2;
            break;


        /* NullName */

        case 0:
            NamesIndex = 0;
            NamesCount = 0;
            break;


        /* one 4-byte name */

        default:
            NamesIndex = PrefixLength;
            NamesCount = 1;
            break;
        }
    }

    /*
     * Calculate the length of ConvertedName, which equals the length
     * of the prefix, length of all object names, length of any required
     * punctuation ('.') between object names, plus the NULL terminator.
     */
    *ConvertedNameLength = PrefixLength + (4 * NamesCount) +
                        ((NamesCount > 0) ? (NamesCount - 1) : 0) + 1;

    /*
     * Check to see if we're still in bounds.  If not, there's a problem
     * with InternalName (invalid format).
     */
    if (*ConvertedNameLength > InternalNameLength)
    {
        REPORT_ERROR ("NsExternalizeName: Invalid internal name.\n");
        return_ACPI_STATUS (AE_BAD_PATHNAME);
    }

    /*
     * Build ConvertedName...
     */

    (*ConvertedName) = AcpiCmCallocate (*ConvertedNameLength);
    if (!(*ConvertedName))
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    j = 0;

    for (i = 0; i < PrefixLength; i++)
    {
        (*ConvertedName)[j++] = InternalName[i];
    }

    if (NamesCount > 0)
    {
        for (i = 0; i < NamesCount; i++)
        {
            if (i > 0)
            {
                (*ConvertedName)[j++] = '.';
            }

            (*ConvertedName)[j++] = InternalName[NamesIndex++];
            (*ConvertedName)[j++] = InternalName[NamesIndex++];
            (*ConvertedName)[j++] = InternalName[NamesIndex++];
            (*ConvertedName)[j++] = InternalName[NamesIndex++];
        }
    }

    return_ACPI_STATUS (AE_OK);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsConvertHandleToEntry
 *
 * PARAMETERS:  Handle          - Handle to be converted to an NTE
 *
 * RETURN:      A Name table entry pointer
 *
 * DESCRIPTION: Convert a namespace handle to a real NTE
 *
 ****************************************************************************/

ACPI_NAMED_OBJECT*
AcpiNsConvertHandleToEntry (
    ACPI_HANDLE             Handle)
{

    /*
     * Simple implementation for now;
     * TBD: [Future] Real integer handles allow for more verification
     * and keep all pointers within this subsystem!
     */

    if (!Handle)
    {
        return NULL;
    }

    if (Handle == ACPI_ROOT_OBJECT)
    {
        return AcpiGbl_RootObject;
    }


    /* We can at least attempt to verify the handle */

    if (!VALID_DESCRIPTOR_TYPE (Handle, ACPI_DESC_TYPE_NAMED))
    {
        return NULL;
    }

    return (ACPI_NAMED_OBJECT*) Handle;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsConvertEntryToHandle
 *
 * PARAMETERS:  Nte          - NTE to be converted to a Handle
 *
 * RETURN:      An USER ACPI_HANDLE
 *
 * DESCRIPTION: Convert a real NTE to a namespace handle
 *
 ****************************************************************************/

ACPI_HANDLE
AcpiNsConvertEntryToHandle(ACPI_NAMED_OBJECT*Nte)
{


    /*
     * Simple implementation for now;
     * TBD: [Future] Real integer handles allow for more verification
     * and keep all pointers within this subsystem!
     */

    return (ACPI_HANDLE) Nte;


/* ---------------------------------------------------

    if (!Nte)
    {
        return NULL;
    }

    if (Nte == AcpiGbl_RootObject)
    {
        return ACPI_ROOT_OBJECT;
    }


    return (ACPI_HANDLE) Nte;
------------------------------------------------------*/
}


/******************************************************************************
 *
 * FUNCTION:    AcpiNsTerminate
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: free memory allocated for table storage.
 *
 ******************************************************************************/

void
AcpiNsTerminate (void)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_NAMED_OBJECT       *Entry;


    FUNCTION_TRACE ("NsTerminate");


    Entry = AcpiGbl_RootObject;

    /*
     * 1) Free the entire namespace -- all objects, tables, and stacks
     */
    /*
     * Delete all objects linked to the root
     * (additional table descriptors)
     */

    AcpiNsDeleteNamespaceSubtree (Entry);

    /* Detach any object(s) attached to the root */

    ObjDesc = AcpiNsGetAttachedObject (Entry);
    if (ObjDesc)
    {
        AcpiNsDetachObject (Entry);
        AcpiCmRemoveReference (ObjDesc);
    }

    AcpiNsDeleteNameTable (Entry->ChildTable);
    Entry->ChildTable = NULL;


    REPORT_SUCCESS ("Entire namespace and objects deleted");
    DEBUG_PRINT (ACPI_INFO, ("NsTerminate: Namespace freed\n"));


    /*
     * 2) Now we can delete the ACPI tables
     */

    AcpiTbDeleteAcpiTables ();

    DEBUG_PRINT (ACPI_INFO, ("NsTerminate: ACPI Tables freed\n"));

    return_VOID;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsOpensScope
 *
 * PARAMETERS:  Type        - A valid namespace type
 *
 * RETURN:      NEWSCOPE if the passed type "opens a name scope" according
 *              to the ACPI specification, else 0
 *
 ***************************************************************************/

INT32
AcpiNsOpensScope (
    OBJECT_TYPE_INTERNAL    Type)
{
    FUNCTION_TRACE_U32 ("NsOpensScope", Type);


    if (!AcpiCmValidObjectType (Type))
    {
        /* type code out of range  */

        REPORT_WARNING ("NsOpensScope: Invalid Object Type");
        return_VALUE (NSP_NORMAL);
    }

    return_VALUE (((INT32) AcpiGbl_NsProperties[Type]) & NSP_NEWSCOPE);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsGetNamedObject
 *
 * PARAMETERS:  *Pathname   - Name to be found, in external (ASL) format. The
 *                            \ (backslash) and ^ (carat) prefixes, and the
 *                            . (period) to separate segments are supported.
 *              InScope     - Root of subtree to be searched, or NS_ALL for the
 *                            root of the name space.  If Name is fully
 *                            qualified (first char is '\'), the passed value
 *                            of Scope will not be accessed.
 *              OutNte      - Where the Nte is returned
 *
 * DESCRIPTION: Look up a name relative to a given scope and return the
 *              corresponding NTE.  NOTE: Scope can be null.
 *
 * MUTEX:       Locks namespace
 *
 ***************************************************************************/

ACPI_STATUS
AcpiNsGetNamedObject (
    char                    *Pathname,
    ACPI_NAME_TABLE         *InScope,
    ACPI_NAMED_OBJECT       **OutNte)
{
    ACPI_GENERIC_STATE      ScopeInfo;
    ACPI_STATUS             Status;
    ACPI_NAMED_OBJECT       *ObjEntry = NULL;
    char                    *InternalPath = NULL;


    FUNCTION_TRACE_PTR ("NsGetNte", Pathname);


    ScopeInfo.Scope.NameTable = InScope;

    /* Ensure that the namespace has been initialized */

    if (!AcpiGbl_RootObject->ChildTable)
    {
        return_ACPI_STATUS (AE_NO_NAMESPACE);
    }

    if (!Pathname)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /* Convert path to internal representation */

    Status = AcpiNsInternalizeName (Pathname, &InternalPath);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    AcpiCmAcquireMutex (ACPI_MTX_NAMESPACE);

    /* NS_ALL means start from the root */

    if (NS_ALL == ScopeInfo.Scope.NameTable)
    {
        ScopeInfo.Scope.NameTable = AcpiGbl_RootObject->ChildTable;
    }

    else
    {
        ScopeInfo.Scope.NameTable = InScope;
        if (!ScopeInfo.Scope.NameTable)
        {
            Status = AE_BAD_PARAMETER;
            goto UnlockAndExit;
        }
    }

    /* Lookup the name in the namespace */

    Status = AcpiNsLookup (&ScopeInfo, InternalPath,
                            ACPI_TYPE_ANY, IMODE_EXECUTE,
                            NS_NO_UPSEARCH | NS_DONT_OPEN_SCOPE,
                            NULL, &ObjEntry);

    if (Status != AE_OK)
    {
        DEBUG_PRINT (ACPI_INFO, ("NsGetNte: %s, %s\n",
                        InternalPath, AcpiCmFormatException (Status)));
    }

    /* Return what was wanted - the NTE that matches the name */

    *OutNte = ObjEntry;


UnlockAndExit:

    AcpiCmReleaseMutex (ACPI_MTX_NAMESPACE);

    /* Cleanup */

    AcpiCmFree (InternalPath);

    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsFindParentName
 *
 * PARAMETERS:  *ChildEntry             - nte whose name is to be found
 *
 * RETURN:      The ACPI name
 *
 * DESCRIPTION: Search for the given nte in its parent scope and return the
 *              name segment, or "????" if the parent name can't be found
 *              (which "should not happen").
 *
 ***************************************************************************/

ACPI_NAME
AcpiNsFindParentName (
    ACPI_NAMED_OBJECT       *ChildEntry)
{
    ACPI_NAMED_OBJECT       *ParentEntry;


    FUNCTION_TRACE ("FindParentName");


    if (ChildEntry)
    {
        /* Valid entry.  Get the parent Nte */

        ParentEntry = AcpiNsGetParentEntry (ChildEntry);
        if (ParentEntry)
        {
            DEBUG_PRINT (TRACE_EXEC,
                ("Parent of %p [%4.4s] is %p [%4.4s]\n",
                ChildEntry, &ChildEntry->Name, ParentEntry,
                &ParentEntry->Name));

            if (ParentEntry->Name)
            {
                return_VALUE (ParentEntry->Name);
            }
        }

        DEBUG_PRINT (TRACE_EXEC,
            ("FindParentName: unable to find parent of %p (%4.4s)\n",
            ChildEntry, &ChildEntry->Name));
    }


    return_VALUE (ACPI_UNKNOWN_NAME);
}

/****************************************************************************
 *
 * FUNCTION:    AcpiNsExistDownstreamSibling
 *
 * PARAMETERS:  *ThisEntry          - pointer to first nte to examine
 *
 * RETURN:      TRUE if sibling is found, FALSE otherwise
 *
 * DESCRIPTION: Searches remainder of scope being processed to determine
 *              whether there is a downstream sibling to the current
 *              object.  This function is used to determine what type of
 *              line drawing character to use when displaying namespace
 *              trees.
 *
 ***************************************************************************/

BOOLEAN
AcpiNsExistDownstreamSibling (
    ACPI_NAMED_OBJECT       *ThisEntry)
{

    if (!ThisEntry)
    {
        return FALSE;
    }

    if (ThisEntry->Name)
    {
        return TRUE;
    }


/* TBD: what did this really do?
    if (ThisEntry->NextEntry)
    {
        return TRUE;
    }
*/
    return FALSE;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsGetOwnerTable
 *
 * PARAMETERS:
 *
 * RETURN:
 *
 * DESCRIPTION:
 *
 ***************************************************************************/


ACPI_NAME_TABLE *
AcpiNsGetOwnerTable (
    ACPI_NAMED_OBJECT       *ThisEntry)
{

    /*
     * Given an entry in the NameTable->Entries field of a name table,
     * we can create a pointer to the beginning of the table as follows:
     *
     * 1) Starting with the the pointer to the entry,
     * 2) Subtract the entry index * size of each entry to get a
     *    pointer to Entries[0]
     * 3) Subtract the size of NAME_TABLE structure to get a pointer
     *    to the start.
     *
     * This saves having to put a pointer in every entry that points
     * back to the beginning of the table and/or a pointer back to
     * the parent.
     */

    return (ACPI_NAME_TABLE *) ((char *) ThisEntry -
                            (ThisEntry->ThisIndex *
                            sizeof (ACPI_NAMED_OBJECT)) -
                            (sizeof (ACPI_NAME_TABLE) -
                            sizeof (ACPI_NAMED_OBJECT)));

}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsGetParentEntry
 *
 * PARAMETERS:  ThisEntry       - Current table entry
 *
 * RETURN:      Parent entry of the given entry
 *
 * DESCRIPTION: Obtain the parent entry for a given entry in the namespace.
 *
 ***************************************************************************/


ACPI_NAMED_OBJECT *
AcpiNsGetParentEntry (
    ACPI_NAMED_OBJECT       *ThisEntry)
{
    ACPI_NAME_TABLE         *NameTable;


    NameTable = AcpiNsGetOwnerTable (ThisEntry);

    /*
     * Now that we have a pointer to the name table, we can just pluck
     * the parent
     */

    return (NameTable->ParentEntry);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsGetNextValidEntry
 *
 * PARAMETERS:  ThisEntry       - Current table entry
 *
 * RETURN:      Next valid object in the table.  NULL if no more valid
 *              objects
 *
 * DESCRIPTION: Find the next valid object within a name table.
 *
 ***************************************************************************/


ACPI_NAMED_OBJECT *
AcpiNsGetNextValidEntry (
    ACPI_NAMED_OBJECT       *ThisEntry)
{
    ACPI_NAME_TABLE         *NameTable;
    UINT32                  Index;


    Index = ThisEntry->ThisIndex + 1;
    NameTable = AcpiNsGetOwnerTable (ThisEntry);


    while (NameTable)
    {
        if (Index >= NS_TABLE_SIZE)
        {
            /* We are at the end of this table */

            NameTable = NameTable->NextTable;
            Index = 0;
            continue;
        }


        /* Is this a valid (occupied) slot? */

        if (NameTable->Entries[Index].Name)
        {
            /* Found a valid entry, all done */

            return (&NameTable->Entries[Index]);
        }

        /* Go to the next slot */

        Index++;
    }

    /* No more valid entries in this name table */

    return NULL;
}


