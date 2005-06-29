
/******************************************************************************
 * 
 * Module Name: nsapiobj - Public interfaces to the ACPI subsystem
 *                         ACPI Object oriented interfaces
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


#define __NSAPIOBJ_C__

#include <acpi.h>
#include <interpreter.h>
#include <namespace.h>
#include <methods.h>
#include <acpiobj.h>
#include <pnp.h>


#define _THIS_MODULE        "nsapiobj.c"
#define _COMPONENT          NAMESPACE


/****************************************************************************
 *
 * FUNCTION:    AcpiEvaluateObject
 *
 * PARAMETERS:  Handle              - Object handle (optional)
 *              *Pathname           - Object pathname (optional)
 *              **Params            - List of parameters to pass to
 *                                    method, terminated by NULL.
 *                                    Params itself may be NULL
 *                                    if no parameters are being
 *                                    passed.
 *              *ReturnObject       - Where to put method's return value (if 
 *                                    any).  If NULL, no value is returned.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Find and evaluate the given object, passing the given
 *              parameters if necessary.  One of "Handle" or "Pathname" must
 *              be valid (non-null)
 *
 ****************************************************************************/

ACPI_STATUS
AcpiEvaluateObject (
    ACPI_HANDLE             Handle, 
    char                    *Pathname, 
    ACPI_OBJECT_LIST        *ParamObjects,
    ACPI_BUFFER             *ReturnBuffer)
{
    ACPI_STATUS             Status;
    NAME_TABLE_ENTRY        *ObjEntry;
    ACPI_OBJECT_INTERNAL    InternalRetObj;
    ACPI_OBJECT_INTERNAL    **ParamPtr = NULL;
    ACPI_OBJECT_INTERNAL    *ReturnPtr = NULL;
    ACPI_OBJECT_INTERNAL    *ObjectPtr = NULL;
    UINT32                  BufferSpaceNeeded;
    UINT32                  Count;
    UINT32                  i;


    FUNCTION_TRACE ("AcpiEvaluateObject");


    /* 
     * If there are parameters, the external objects must be converted
     * to internal objects
     */

    if (ParamObjects && ParamObjects->Count)
    {
        /* 
         * Allocate a new parameter block for the internal objects
         * Add 1 to count to allow for null terminated internal list
         * TBD: merge into single allocation!
         */

        Count = ParamObjects->Count;
        ParamPtr = LocalCallocate ((Count + 1) * 
                                    sizeof (void *));
        if (!ParamPtr)
        {
            FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
            return AE_NO_MEMORY;
        }

        ObjectPtr = LocalCallocate ((Count) * 
                                    sizeof (ACPI_OBJECT_INTERNAL));
        if (!ObjectPtr)
        {
            OsdFree (ParamPtr);
            FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
            return AE_NO_MEMORY;
        }

        /*
         * Init the param array of pointers and NULL terminate the list
         */

        for (i = 0; i < Count; i++)
        {
            ParamPtr[i] = &ObjectPtr[i];
        }
        ParamPtr[Count] = NULL;                 

        /* 
         * Convert each external object in the list to an internal object
         */
        for (i = 0; i < Count; i++)
        {
            Status = CmBuildInternalObject (&ParamObjects->Pointer[i], ParamPtr[i]);
            if (ACPI_FAILURE (Status))
            {
                CmDeleteInternalObjectList (ParamPtr);
                FUNCTION_STATUS_EXIT (Status);
                return Status;
            }
        }
    }

    if (ReturnBuffer && ReturnBuffer->Pointer)
    {
        ReturnPtr = &InternalRetObj;
    }

    /*
     *  If the pathname exists and is fully qualified then just eval by name
     */

    if ((Pathname) && (Pathname[0] == '\\'))
    {
BREAKPOINT3;
        Status = NsEvaluateByName (Pathname, ParamPtr, ReturnPtr);
        goto Cleanup;
    }

    if (!Handle)
    {
        /*
         *  Handle is optional iff fully qualified pathname is specified, we've already handled
         *  fully qualified names, so this is an error
         */
        if (!Pathname)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AcpiEvaluateObject: Both Handle and Pathname are NULL\n"));
        }

        else
        {
            DEBUG_PRINT (ACPI_ERROR, ("AcpiEvaluateObject: Handle is NULL and Pathname is relative\n"));
        }

        Status = AE_BAD_PARAMETER;
        goto Cleanup;
    }


    /*
     *  We get here we have a handle, and if we have a pathname it is relative.
     *
     *  Validate the handle
     */
    if (!(ObjEntry = NsConvertHandleToEntry (Handle)))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AcpiEvaluateObject: Bad Handle\n"));
        Status = AE_BAD_PARAMETER;
        goto Cleanup;
    }

    if (!Pathname)
    {
        /*
         *  The null pathname case means the handle is for the object
         */
        Status = NsEvaluateByHandle (ObjEntry, ParamPtr, ReturnPtr);
    }

    else
    {
       /*
        *   Have both Handle and a relative Pathname
        */
        Status = NsEvaluateRelative (ObjEntry, Pathname, ParamPtr, ReturnPtr);
    }



    /*
     * Common cleanup: We must free the input parameter list (if we created one),
     * and copy the return object to the caller's buffer (if necessary)
     */

Cleanup:
    if (ParamPtr)
    {
        /* Free the allocated parameter block */

        CmDeleteInternalObjectList (ParamPtr);
    }

    if (ReturnPtr)
    {
        if (Status == AE_RETURN_VALUE)
        {
            /*
             *  Find out how large a buffer is needed to contain the
             *  returned object
             */
            Status = CmGetObjectSize (ReturnPtr, &BufferSpaceNeeded);
            if (Status != AE_OK) 
            {
                /*
                 *  Failed the call
                 */
                ReturnBuffer->Length = 0;
                FUNCTION_STATUS_EXIT (Status);
                return Status;
            }


            if (ReturnBuffer->Length < BufferSpaceNeeded) 
            {
                /*
                 *  Caller's buffer is too small, can't give him partial results
                 *  fail the call but return the buffer size needed
                 */
                ReturnBuffer->Length = BufferSpaceNeeded;
                FUNCTION_STATUS_EXIT (AE_BUFFER_OVERFLOW);
                return AE_BUFFER_OVERFLOW;
            }

            /*
             *  We have enough space for the object, build it
             */
            Status = CmBuildExternalObject (ReturnPtr, ReturnBuffer);
            ReturnBuffer->Length = BufferSpaceNeeded;
        }

        else
        {
            /* Nothing was returned */

            ReturnBuffer->Length = 0;
        }
    }

    /* Never pass AE_RETURN_VALUE back to the caller */

    if (Status == AE_RETURN_VALUE)
    {
        Status = AE_OK;
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}

/****************************************************************************
 *
 * FUNCTION:    AcpiGetNextObject
 *
 * PARAMETERS:  Type            - Type of object to be searched for
 *              Scope           - Scope to search in (only if Handle is null)
 *              Handle          - Current object to search from
 *              RetHandle       - Where handle to the next object is placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Return the next peer object within the namespace.  If Handle is
 *              valid, Scope is ignored.  Otherwise, the first object within 
 *              Scope is returned.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiGetNextObject (
    ACPI_OBJECT_TYPE        Type, 
    ACPI_HANDLE             Scope, 
    ACPI_HANDLE             Handle, 
    ACPI_HANDLE             *RetHandle)
{
    NAME_TABLE_ENTRY        *ThisEntry;


    if (!RetHandle)
    {
        return AE_BAD_PARAMETER;
    }
    *RetHandle = NULL;


    if (OUTRANGE (Type, NsTypeNames))
    {
        return AE_BAD_PARAMETER;
    }


    /* If null handle, use the scope */

    if (!Handle)
    {
        if (!Scope)
        {
            return AE_NOT_FOUND;
        }

        /* Start search at the beginning of the specified scope */

        if (!(ThisEntry = NsConvertHandleToEntry (Scope)))
        {
            return AE_BAD_PARAMETER;
        }
    }

    /* Non-null handle, ignore the scope */

    else
    {
        /* Convert and validate the handle */

        if (!(ThisEntry = NsConvertHandleToEntry (Handle)))
        {
            return AE_BAD_PARAMETER;
        }

        /* Start search at the NEXT object */

        ThisEntry = ThisEntry->NextEntry;
    }


    /* If any type is OK, we are done */

    if (Type == TYPE_Any)
    {
        /* Make sure this is valid entry first */

        if (!ThisEntry)
        {
            return AE_NOT_FOUND;
        }

        if (!ThisEntry->Name)
        {
            return AE_NOT_FOUND;
        }

        *RetHandle = ThisEntry;
        return AE_OK;
    }


    /* Must search -- entries within this scope only */

    while (ThisEntry)
    {
        /* If type matches, we are done */

        if (ThisEntry->Type == Type)
        {
            *RetHandle = ThisEntry;
            return AE_OK;
        }

        /* Otherwise, move on to the next object */

        ThisEntry = ThisEntry->NextEntry;
    }


    return AE_NOT_FOUND;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiGetType
 *
 * PARAMETERS:  Handle          - Handle of object whose type is desired
 *              *RetType        - Where the type will be placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This routine returns the type associatd with a particular handle
 *
 ******************************************************************************/

ACPI_STATUS 
AcpiGetType (
    ACPI_HANDLE             Handle,
    ACPI_OBJECT_TYPE        *RetType)
{
    NAME_TABLE_ENTRY        *Object;


    if (!RetType)
    {
        return AE_BAD_PARAMETER;
    }

    /* Convert and validate the handle */

    if (!(Object = NsConvertHandleToEntry (Handle)))
    {
        return AE_BAD_PARAMETER;
    }

    *RetType = Object->Type;
    return AE_OK;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiGetParent
 *
 * PARAMETERS:  Handle          - Handle of object whose parent is desired
 *              RetHandle       - Where the parent handle will be placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Returns a handle to the parent of the object represented by
 *              Handle.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiGetParent (
    ACPI_HANDLE             Handle, 
    ACPI_HANDLE             *RetHandle)
{
    NAME_TABLE_ENTRY        *Object;


    if (!RetHandle)
    {
        return AE_BAD_PARAMETER;
    }

    /* Convert and validate the handle */

    if (!(Object = NsConvertHandleToEntry (Handle)))
    {
        *RetHandle = INVALID_HANDLE;
        return AE_BAD_PARAMETER;
    }

   
    /* Get the parent entry */

    *RetHandle = Object->ParentEntry;

    /* Return exeption if parent is null */

    if (!Object->ParentEntry)
    {
        return AE_NULL_ENTRY;
    }

    return AE_OK;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiGetScope
 *
 * PARAMETERS:  Handle          - Handle of object whose scope is desired
 *              RetScope        - Where the scope handle is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Returns a handle to the scope that is owned by the object
 *              represented by handle.  NOTE: this is NOT the scope that
 *              contains the object (i.e., not the scope that the object is
 *              defined within.)
 *
 ******************************************************************************/

ACPI_STATUS
AcpiGetScope (
    ACPI_HANDLE             Handle, 
    ACPI_HANDLE             *RetScope)
{
    NAME_TABLE_ENTRY        *Object;


    if (!RetScope)
    {
        return AE_BAD_PARAMETER;
    }

    /* Convert and validate the handle */

    if (!(Object = NsConvertHandleToEntry (Handle)))
    {
        *RetScope = INVALID_HANDLE;
        return AE_BAD_PARAMETER;
    }

    /* Get the scope entry */

    *RetScope = Object->Scope;

    /* Return exception in the case of no scope */

    if (!Object->Scope)
    {
        return AE_NULL_ENTRY;
    }

    return AE_OK;
}



/****************************************************************************
 *
 * FUNCTION:    AcpiGetContainingScope
 *
 * PARAMETERS:  Handle          - Handle to object whose containing scope is desired
 *              RetHandle       - Where the containing scope handle is placed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Returns a handle for the scope that contains the object represented
 *              by Handle.  This is essentially the scope of the objects parent,
 *              and is the scope where the object is defined in the ASL.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiGetContainingScope (
    ACPI_HANDLE             Handle, 
    ACPI_HANDLE             *RetHandle)
{
    NAME_TABLE_ENTRY        *Object;


    if (!RetHandle)
    {
        return AE_BAD_PARAMETER;
    }

    /* Convert and validate the handle */

    if (!(Object = NsConvertHandleToEntry (Handle)))
    {
        *RetHandle = INVALID_HANDLE;
        return AE_BAD_PARAMETER;
    }

    /* If no parent, we are in the root scope */

    if (!Object->ParentEntry)
    {
        *RetHandle = RootObject->Scope;
    }
    else
    {
        *RetHandle = Object->ParentEntry->Scope;
    }

    return AE_OK;
}



/******************************************************************************
 *
 * FUNCTION:    AcpiWalkNamespace
 *
 * PARAMETERS:  Type                - ACPI_OBJECT_TYPE to search for
 *              StartHandle         - Handle in namespace where search begins
 *              MaxDepth            - Depth to which search is to reach
 *              UserFunction        - Called when an object of "Type" is found
 *              Context             - Passed to user function
 *
 * RETURNS      Return value from the UserFunction if terminated early.
 *              Otherwise, returns NULL.
 *
 * DESCRIPTION: Performs a modified depth-first walk of the namespace tree,
 *              starting (and ending) at the object specified by StartHandle.
 *              The UserFunction is called whenever an object that matches
 *              the type parameter is found.  If the user function returns
 *              a non-zero value, the search is terminated immediately and this
 *              value is returned to the caller.
 *
 *              The point of this procedure is to provide a generic namespace
 *              walk routine that can be called from multiple places to 
 *              provide multiple services;  the User Function can be tailored
 *              to each task, whether it is a print function, a compare 
 *              function, etc.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiWalkNamespace (
    ACPI_OBJECT_TYPE        Type, 
    ACPI_HANDLE             StartHandle, 
    UINT32                  MaxDepth,
    WALK_CALLBACK           UserFunction, 
    void                    *Context, 
    void                    **ReturnValue)
{
    ACPI_HANDLE             ObjHandle = 0;
    ACPI_HANDLE             Scope;
    ACPI_HANDLE             NewScope;
    void                    *UserReturnVal;
    UINT32                  Level = 1;


    FUNCTION_TRACE ("AcpiWalkNamespace");


    /* Parameter validation */

    if (OUTRANGE (Type, NsTypeNames))
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }

    if ((!MaxDepth) || (!UserFunction))
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }

    /* Begin search in the scope owned by the starting object */
    /* Failure could be bad scope or simply *no* scope */

    if (ACPI_FAILURE (AcpiGetScope (StartHandle, &Scope)))
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }

    /* Init return value, if any */

    if (ReturnValue)
        *ReturnValue = NULL;

    /* 
     * Traverse the tree of objects until we bubble back up 
     * to where we started.
     */

    while (ObjHandle != StartHandle)
    {
        /* Get the next typed object in this scope.  Null returned if not found */

        if (ACPI_SUCCESS (AcpiGetNextObject (Type, Scope, ObjHandle, &ObjHandle)))
        {
            /* Found an object - process by calling the user function */

            if ((UserReturnVal = UserFunction (ObjHandle, Level, Context)) != 0)
            {
                /* Non-zero from user function means "exit now" */

                if (ReturnValue)
                    *ReturnValue = UserReturnVal;

                FUNCTION_STATUS_EXIT (AE_OK);
                return AE_OK;
            }

            /* Go down another level if we are allowed to */

            if (Level < MaxDepth)
            {
                /* Check for a valid scope for this object */

                if (ACPI_SUCCESS (AcpiGetScope (ObjHandle, &NewScope)))
                {
                    /* There is a valid scope, we will check for child objects */

                    Level++;
                    ObjHandle = 0;
                    Scope = NewScope;
                }
            }
        }

        else
        {
            /* 
             * No more objects in this scope, go back up to the parent and the 
             * parent's scope (But only back up to where we started the search)
             */
            Level--;
            AcpiGetParent (Scope, &ObjHandle);
            AcpiGetContainingScope (ObjHandle, &Scope);
        }
    }

    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK; /* Complete walk, not terminated by user function */
}



/* NON-IMPLEMENTED FUNCTIONS */


/****************************************************************************
 *
 * FUNCTION:    AcpiGetObject
 *
 * PARAMETERS:  
 *
 * RETURN:      Status
 *
 * DESCRIPTION: TBD: Not completely defined, not implemented!
 *
 ******************************************************************************/

ACPI_STATUS
AcpiGetObject (
    char                    *Pathname, 
    ACPI_HANDLE             *RetHandle)
{

    if (!RetHandle)
    {
        return AE_BAD_PARAMETER;
    }


    *RetHandle = RootObject->Scope;
    return AE_OK;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiGetParentHandle
 *
 * PARAMETERS:  ChildHandle     - the handle of the object for which the 
 *                                parent is to be found
 *
 * RETURN:      Parent handle
 *
 * DESCRIPTION: This routine returns the handle for the parent of an object.
 *
 ******************************************************************************/

ACPI_HANDLE 
AcpiGetParentHandle (
    ACPI_HANDLE             ChildHandle)
{

    return ((ACPI_HANDLE) NULL);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiCurrentScopeName
 *
 * PARAMETERS:  none
 *
 * RETURN:      pointer to an ascii string with the absolute name of the scope
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

char * 
AcpiCurrentScopeName (void)
{
    return ((char *) NULL);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiIsNamespaceHandle
 *
 * PARAMETERS:  QueryHandle     - handle to be verified
 *
 * RETURN:      BOOLEAN -   TRUE if QueryHandle is a NameSpace handle
 *                          FALSE otherwise
 *
 * DESCRIPTION: This routine verifies the validity of a namespace handle
 *
 ******************************************************************************/

BOOLEAN 
AcpiIsNamesaceHandle (
    ACPI_HANDLE             QueryHandle)
{
    return (TRUE);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiIsNamesaceValue
 *
 * PARAMETERS:  Value
 *
 * RETURN:      TRUE if the value is a valid NS vakue, FALSE otherwise
 *
 * DESCRIPTION: This routine verifies the value is valid for ACPI_OBJECT_TYPE  what is the utility of this? RLM
 *
 ******************************************************************************/

BOOLEAN 
AcpiIsNamesaceValue (
    ACPI_OBJECT_TYPE        Value)
{
    return (TRUE);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiSetFirmwareWakingVector
 *
 * PARAMETERS:  PhysicalAddress     - Physical address of ACPI real mode
 *                                          entry point.
 *
 * RETURN:      AE_OK or AE_ERROR
 *
 * DESCRIPTION: Access function for dFirmwareWakingVector field in FACS
 *
 ******************************************************************************/

ACPI_STATUS
AcpiSetFirmwareWakingVector (
    void                    *PhysicalAddress)
{
    FUNCTION_TRACE ("AcpiSetFirmwareWakingVector");
    
    FUNCTION_STATUS_EXIT (AE_OK);
    return (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiGetFirmwareWakingVector
 *
 * PARAMETERS:  *PhysicalAddress    - Output buffer where contents of
 *                                          the dFirmwareWakingVector field of 
 *                                          the FACS will be stored.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Access function for dFirmwareWakingVector field in FACS
 *
 ******************************************************************************/

ACPI_STATUS
AcpiGetFirmwareWakingVector (
    void                    **PhysicalAddress)
{
    FUNCTION_TRACE ("AcpiGetFirmwareWakingVector");

    
    FUNCTION_STATUS_EXIT (AE_OK);
    return (AE_OK);
}

