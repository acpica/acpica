
/******************************************************************************
 * 
 * Module Name: nsutils - Utilities for accessing ACPI namespace
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

#include <acpi.h>
#include <namespace.h>
#include <interpreter.h>
#include <amlcode.h>
#include <tables.h>


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nsutils");


/****************************************************************************
 *
 * FUNCTION:    NsGetType
 *
 * PARAMETERS:  Handle              - Handle of nte to be examined
 *
 * RETURN:      Type field from nte whose handle is passed
 *
 ***************************************************************************/

ACPI_OBJECT_TYPE
NsGetType (
    ACPI_HANDLE             handle)
{
    FUNCTION_TRACE ("NsGetType");


    if (!handle)
    {
        /*  Handle invalid  */

        REPORT_WARNING ("NsGetType: Null handle");
        return_VALUE (ACPI_TYPE_Any);
    }

    return_VALUE (((NAME_TABLE_ENTRY *) handle)->Type);
}


/****************************************************************************
 *
 * FUNCTION:    NsLocal
 *
 * PARAMETERS:  Type            - A namespace object type
 *
 * RETURN:      LOCAL if names must be found locally in objects of the
 *              passed type, 0 if enclosing scopes should be searched
 *
 ***************************************************************************/

INT32
NsLocal (
    ACPI_OBJECT_TYPE        Type)
{
    FUNCTION_TRACE ("NsLocal");


    if (Type > INTERNAL_TYPE_MAX)
    {
        /*  type code out of range  */

        REPORT_WARNING ("NsLocal: Type code out of range");
        return_VALUE (0);
    }

    return_VALUE ((INT32) Gbl_NsProperties[Type] & NSP_LOCAL);
}


/****************************************************************************
 *
 * FUNCTION:    NsInternalizeName
 *
 * PARAMETERS:  *DottedName             - External representation of name
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
NsInternalizeName (
    char                    *DottedName,
    char                    **ConvertedName)
{
    char                    *Result = NULL;
    char                    *InternalName;
    ACPI_SIZE               NumSegments;
    BOOLEAN                 FullyQualified = FALSE;
    UINT32                  Length;


    FUNCTION_TRACE ("NsInternalizeName");


    if (!DottedName || !ConvertedName)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /* 
     * For the internal name, the required length is 4 bytes per segment, 
     * plus 1 each for RootPrefix, MultiNamePrefixOp, segment count, trailing null 
     * (which is not really needed, but no there's harm in putting it there)
     *
     * strlen() + 1 covers the first NameSeg, which has no path separator
     */

    if (DottedName[0] == '\\')
    {
        FullyQualified = TRUE;
        DottedName++;
    }

    Length = STRLEN (DottedName);
    NumSegments = (Length + 1) / PATH_SEGMENT_LENGTH;    /* Number of NameSegs in the path */

    /* Name must be at least 4 characters */

    if (Length < 4)
    {
        return_ACPI_STATUS (AE_BAD_PATHNAME);
    }

    /* Pathname must be an exact multiple of segments */

    if (Length > 4)
    {
        if ((Length + 1) % PATH_SEGMENT_LENGTH)
        {
            return_ACPI_STATUS (AE_BAD_PATHNAME);
        }
    }

    /* We need a segment to store the internal version of the name */

    InternalName = CmCallocate ((ACPI_NAME_SIZE * NumSegments) + 4);
    if (!InternalName)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }


    /* Setup the correct prefixes, counts, and pointers */

    if (FullyQualified)
    {
        InternalName[0] = '\\';
        InternalName[1] = AML_MultiNamePrefixOp;
        InternalName[2] = NumSegments;
        Result = &InternalName[3];
    }
    else
    {
        InternalName[0] = AML_MultiNamePrefixOp;
        InternalName[1] = NumSegments;
        Result = &InternalName[2];
    }


    /* Build the name (minus path separators) */

    for (; NumSegments; NumSegments--)
    {
        STRNCPY (Result, DottedName, ACPI_NAME_SIZE);
        Result += ACPI_NAME_SIZE;
        DottedName += PATH_SEGMENT_LENGTH;
    }

    
    /* Return the completed name */

    *Result = '\0';                     /* Terminate the string! */
    *ConvertedName = InternalName;


    if (FullyQualified)
    {
        DEBUG_PRINT (TRACE_EXEC,("NsInternalizeName: returning [%p] (abs) \"\\%s\"\n", 
                                InternalName, &InternalName[3])); 
    }
    else
    {
        DEBUG_PRINT (TRACE_EXEC,("NsInternalizeName: returning [%p] (rel) \"%s\"\n", 
                                InternalName, &InternalName[2])); 
    }

    return_ACPI_STATUS (AE_OK);
}


/****************************************************************************
 *
 * FUNCTION:    NsConvertHandleToEntry
 *
 * PARAMETERS:  Handle          - Handle to be converted to an NTE
 *
 * RETURN:      A Name table entry pointer
 *
 * DESCRIPTION: Convert a namespace handle to a real NTE
 *
 ****************************************************************************/

NAME_TABLE_ENTRY *
NsConvertHandleToEntry (
    ACPI_HANDLE             Handle)
{

    /* 
     * Simple implementation for now;
     * TBD: Real integer handles allow for more verification 
     * and keep all pointers within this subsystem!
     */

    if (!Handle)
    {
        return NULL;
    }

    if (Handle == ACPI_ROOT_OBJECT)
    {
        return Gbl_RootObject;
    }


/* TBD: No longer needed ???

    if (Handle == ACPI_ROOT_SCOPE)
    {
        return (NAME_TABLE_ENTRY *) Gbl_RootObject->Scope;
    }

*/

    return (NAME_TABLE_ENTRY *) Handle;
}

/****************************************************************************
 *
 * FUNCTION:    NsConvertEntryToHandle
 *
 * PARAMETERS:  Nte          - NTE to be converted to a Handle
 *
 * RETURN:      An USER ACPI_HANDLE
 *
 * DESCRIPTION: Convert a real NTE to a namespace handle
 *
 ****************************************************************************/

ACPI_HANDLE
NsConvertEntryToHandle(NAME_TABLE_ENTRY *Nte)
{

    return (ACPI_HANDLE) Nte;

    /* 
     * Simple implementation for now;
     * TBD: Real integer handles allow for more verification 
     * and keep all pointers within this subsystem!
     */

    if (!Nte)
    {
        return NULL;
    }

    if (Nte == Gbl_RootObject)
    {
        return ACPI_ROOT_OBJECT;
    }


/* TBD: no longer needed ??

    if (Nte == Gbl_RootObject->Scope)
    {
        return ACPI_ROOT_SCOPE;
    }
*/


    return (ACPI_HANDLE) Nte;
}


/******************************************************************************
 *
 * FUNCTION:    NsTerminate
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: free memory allocated for table storage.
 *
 ******************************************************************************/

void
NsTerminate (void)
{
    FUNCTION_TRACE ("NsTerminate");


    /*
     * 1) Free the entire namespace -- all objects, tables, and stacks
     */

    NsDeleteNamespace ();
    NsScopeStackClear ();
    CmFree (Gbl_CurrentScope);      /* Free the root scope */

    DEBUG_PRINT (ACPI_INFO, ("NsTerminate: Namespace freed\n"));


    /* 
     * 2) Now we can delete the ACPI tables 
     */

    TbDeleteAcpiTables ();

    DEBUG_PRINT (ACPI_INFO, ("NsTerminate: ACPI Tables freed\n"));

	return_VOID;
}

 

