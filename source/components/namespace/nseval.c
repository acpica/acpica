
/******************************************************************************
 *
 * Module Name: nseval - Object evaluation interfaces -- includes control
 *                       method lookup and execution.
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

#define __NSEVAL_C__

#include "acpi.h"
#include "amlcode.h"
#include "acparser.h"
#include "acinterp.h"
#include "acnamesp.h"


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nseval");


/****************************************************************************
 *
 * FUNCTION:    AcpiNsEvaluateRelative
 *
 * PARAMETERS:  RelObjEntry         - NTE of the relative containing object
 *              *Pathname           - Name of method to execute, If NULL, the
 *                                    handle is the object to execute
 *              **Params            - List of parameters to pass to the method,
 *                                    terminated by NULL.  Params itself may be
 *                                    NULL if no parameters are being passed.
 *              *ReturnObject       - Where to put method's return value (if
 *                                    any).  If NULL, no value is returned.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Find and execute the requested method using the handle as a
 *              scope
 *
 * MUTEX:       Locks Namespace
 *
 ****************************************************************************/

ACPI_STATUS
AcpiNsEvaluateRelative (
    ACPI_NAMED_OBJECT       *Handle,
    NATIVE_CHAR             *Pathname,
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    **ReturnObject)
{
    ACPI_NAMED_OBJECT       *RelObjEntry;
    ACPI_STATUS             Status;
    ACPI_NAMED_OBJECT       *ObjEntry = NULL;
    NATIVE_CHAR             *InternalPath = NULL;
    ACPI_GENERIC_STATE      ScopeInfo;


    FUNCTION_TRACE ("NsEvaluateRelative");


    /*
     * Must have a valid object handle
     */
    if (!Handle)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Build an internal name string for the method */

    Status = AcpiNsInternalizeName (Pathname, &InternalPath);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Get the prefix handle and NTE */

    AcpiCmAcquireMutex (ACPI_MTX_NAMESPACE);

    RelObjEntry = AcpiNsConvertHandleToEntry (Handle);
    if (!RelObjEntry)
    {
        AcpiCmReleaseMutex (ACPI_MTX_NAMESPACE);
        Status = AE_BAD_PARAMETER;
        goto Cleanup;
    }

    /* Lookup the name in the namespace */

    ScopeInfo.Scope.NameTable = RelObjEntry->ChildTable;
    Status = AcpiNsLookup (&ScopeInfo, InternalPath, ACPI_TYPE_ANY,
                            IMODE_EXECUTE,
                            NS_NO_UPSEARCH, NULL,
                            &ObjEntry);

    AcpiCmReleaseMutex (ACPI_MTX_NAMESPACE);

    if (ACPI_FAILURE (Status))
    {
        DEBUG_PRINT (ACPI_INFO,
            ("NsEvaluateRelative: Object [%s] not found [%.4X]\n",
            InternalPath, Status));
        goto Cleanup;
    }

    /*
     * Now that we have a handle to the object, we can attempt
     * to evaluate it.
     */

    DEBUG_PRINT (ACPI_INFO,
        ("NsEvaluateRelative: %s [%p] Value %p\n",
        Pathname, ObjEntry, ObjEntry->Object));

    Status = AcpiNsEvaluateByHandle (ObjEntry, Params, ReturnObject);

    DEBUG_PRINT (ACPI_INFO,
        ("NsEvaluateRelative: *** Completed eval of object %s ***\n",
        Pathname));

Cleanup:

    /* Cleanup */

    AcpiCmFree (InternalPath);

    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsEvaluateByName
 *
 * PARAMETERS:  Pathname            - Fully qualified pathname to the object
 *              *ReturnObject       - Where to put method's return value (if
 *                                    any).  If NULL, no value is returned.
 *              **Params            - List of parameters to pass to the method,
 *                                    terminated by NULL.  Params itself may be
 *                                    NULL if no parameters are being passed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Find and execute the requested method passing the given
 *              parameters
 *
 * MUTEX:       Locks Namespace
 *
 ****************************************************************************/

ACPI_STATUS
AcpiNsEvaluateByName (
    NATIVE_CHAR             *Pathname,
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    **ReturnObject)
{
    ACPI_STATUS             Status;
    ACPI_NAMED_OBJECT       *ObjEntry = NULL;
    NATIVE_CHAR             *InternalPath = NULL;


    FUNCTION_TRACE ("NsEvaluateByName");


    /* Build an internal name string for the method */

    Status = AcpiNsInternalizeName (Pathname, &InternalPath);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    AcpiCmAcquireMutex (ACPI_MTX_NAMESPACE);

    /* Lookup the name in the namespace */

    Status = AcpiNsLookup (NULL, InternalPath, ACPI_TYPE_ANY,
                            IMODE_EXECUTE,
                            NS_NO_UPSEARCH, NULL,
                            &ObjEntry);

    AcpiCmReleaseMutex (ACPI_MTX_NAMESPACE);

    if (ACPI_FAILURE (Status))
    {
        DEBUG_PRINT (ACPI_INFO,
            ("NsEvaluateByName: Object at [%s] was not found, status=%.4X\n",
            InternalPath, Status));
        goto Cleanup;
    }

    /*
     * Now that we have a handle to the object, we can attempt
     * to evaluate it.
     */

    DEBUG_PRINT (ACPI_INFO,
        ("NsEvaluateByName: %s [%p] Value %p\n",
        Pathname, ObjEntry, ObjEntry->Object));

    Status = AcpiNsEvaluateByHandle (ObjEntry, Params, ReturnObject);

    DEBUG_PRINT (ACPI_INFO,
        ("NsEvaluateByName: *** Completed eval of object %s ***\n",
        Pathname));


Cleanup:

    /* Cleanup */

    if (InternalPath)
    {
        AcpiCmFree (InternalPath);
    }

    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsEvaluateByHandle
 *
 * PARAMETERS:  ObjEntry            - NTE of method to execute
 *              *ReturnObject       - Where to put method's return value (if
 *                                    any).  If NULL, no value is returned.
 *              **Params            - List of parameters to pass to the method,
 *                                    terminated by NULL.  Params itself may be
 *                                    NULL if no parameters are being passed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute the requested method passing the given parameters
 *
 * MUTEX:       Locks Namespace
 *
 ****************************************************************************/

ACPI_STATUS
AcpiNsEvaluateByHandle (
    ACPI_NAMED_OBJECT       *Handle,
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    **ReturnObject)
{
    ACPI_NAMED_OBJECT       *ObjEntry;
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    *LocalReturnObject;


    FUNCTION_TRACE ("NsEvaluateByHandle");


    /* Check if namespace has been initialized */

    if (!AcpiGbl_RootObject->ChildTable)
    {
        return_ACPI_STATUS (AE_NO_NAMESPACE);
    }

    /* Parameter Validation */

    if (!Handle)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    if (ReturnObject)
    {
        /* Initialize the return value to an invalid object */

        *ReturnObject = NULL;
    }

    /* Get the prefix handle and NTE */

    AcpiCmAcquireMutex (ACPI_MTX_NAMESPACE);

    ObjEntry = AcpiNsConvertHandleToEntry (Handle);
    if (!ObjEntry)
    {
        Status = AE_BAD_PARAMETER;
        goto UnlockAndExit;
    }


    /*
     * Two major cases here:
     * 1) The object is an actual control method -- execute it.
     * 2) The object is not a method -- just return it's current
     *      value
     *
     * In both cases, the namespace is unlocked by the
     *  AcpiNs* procedure
     */

    if (AcpiNsGetType (ObjEntry) == ACPI_TYPE_METHOD)
    {
        /*
         * Case 1) We have an actual control method to execute
         */

        Status = AcpiNsExecuteControlMethod (ObjEntry,
                                            Params,
                                            &LocalReturnObject);
    }

    else
    {
        /*
         * Case 2) Object is NOT a method, just return its
         * current value
         */

        Status = AcpiNsGetObjectValue (ObjEntry,
                                        &LocalReturnObject);
    }


    /*
     * Check if there is a return value on the stack that must
     * be dealt with
     */

    if (Status == AE_CTRL_RETURN_VALUE)
    {
        /*
         * If the Method returned a value and the caller
         * provided a place to store a returned value, Copy
         * the returned value to the object descriptor provided
         * by the caller.
         */

        if (ReturnObject)
        {
            /*
             * Valid return object, copy the pointer to
             * the returned object
             */

            *ReturnObject = LocalReturnObject;
        }


        /* Map AE_RETURN_VALUE to AE_OK, we are done with it */

        if (Status == AE_CTRL_RETURN_VALUE)
        {
            Status = AE_OK;
        }
    }

    /*
     * Namespace was unlocked by the handling AcpiNs* function,
     * so we just return
     */

    return_ACPI_STATUS (Status);


UnlockAndExit:

    AcpiCmReleaseMutex (ACPI_MTX_NAMESPACE);
    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsExecuteControlMethod
 *
 * PARAMETERS:  MethodEntry         - The Nte of the object/method
 *              **Params            - List of parameters to pass to the method,
 *                                    terminated by NULL.  Params itself may be
 *                                    NULL if no parameters are being passed.
 *              **ReturnObjDesc     - List of result objects to be returned
 *                                    from the method.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute the requested method passing the given parameters
 *
 * MUTEX:       Assumes namespace is locked
 *
 ****************************************************************************/

ACPI_STATUS
AcpiNsExecuteControlMethod (
    ACPI_NAMED_OBJECT       *MethodEntry,
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    **ReturnObjDesc)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    FUNCTION_TRACE ("NsExecuteControlMethod");


    /* Verify that there is a method associated with this object */

    ObjDesc = AcpiNsGetAttachedObject ((ACPI_HANDLE) MethodEntry);
    if (!ObjDesc)
    {
        DEBUG_PRINT (ACPI_ERROR,
            ("Control method is undefined (nil value)\n"));
        return_ACPI_STATUS (AE_ERROR);
    }


    DEBUG_PRINT (ACPI_INFO, ("Control method at Offset %x Length %lx]\n",
                    ObjDesc->Method.Pcode + 1,
                    ObjDesc->Method.PcodeLength - 1));

    DUMP_PATHNAME (MethodEntry, "NsExecuteControlMethod: Executing",
                    TRACE_NAMES, _COMPONENT);

    DEBUG_PRINT (TRACE_NAMES,
        ("At offset %8XH\n", ObjDesc->Method.Pcode + 1));


    /*
     * Unlock the namespace before execution.  This allows namespace access
     * via the external Acpi* interfaces while a method is being executed.
     * However, any namespace deletion must acquire both the namespace and
     * interpreter locks to ensure that no thread is using the portion of the
     * namespace that is being deleted.
     */

    AcpiCmReleaseMutex (ACPI_MTX_NAMESPACE);

    /*
     * Excecute the method via the interpreter
     */
    Status = AcpiAmlExecuteMethod (MethodEntry, Params, ReturnObjDesc);

    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsGetObjectValue
 *
 * PARAMETERS:  ObjectEntry         - The Nte of the object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Return the current value of the object
 *
 * MUTEX:       Assumes namespace is locked
 *
 ****************************************************************************/

ACPI_STATUS
AcpiNsGetObjectValue (
    ACPI_NAMED_OBJECT       *ObjectEntry,
    ACPI_OBJECT_INTERNAL    **ReturnObjDesc)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *ValDesc;


    FUNCTION_TRACE ("NsGetObjectValue");


    /*
     *  We take the value from certain objects directly
     */

    if ((ObjectEntry->Type == ACPI_TYPE_PROCESSOR) ||
        (ObjectEntry->Type == ACPI_TYPE_POWER))
    {

        /*
         *  Create a Reference object to contain the object
         */
        ObjDesc = AcpiCmCreateInternalObject (ObjectEntry->Type);
        if (!ObjDesc)
        {
           Status = AE_NO_MEMORY;
           goto UnlockAndExit;
        }

        /*
         *  Get the attached object
         */

        ValDesc = AcpiNsGetAttachedObject (ObjectEntry);
        if (!ValDesc)
        {
            Status = AE_NULL_OBJECT;
            goto UnlockAndExit;
        }

        /*
         *  Just copy from the original to the return object
         */

        MEMCPY (&ObjDesc->Common.FirstNonCommonByte,
                &ValDesc->Common.FirstNonCommonByte,
                (sizeof(ACPI_OBJECT_COMMON) -
                sizeof(ObjDesc->Common.FirstNonCommonByte)));
    }


    /*
     * Other objects require a reference object wrapper which we
     * then attempt to resolve.
     */
    else
    {
        /* Create an Reference object to contain the object */

        ObjDesc = AcpiCmCreateInternalObject (INTERNAL_TYPE_REFERENCE);
        if (!ObjDesc)
        {
           Status = AE_NO_MEMORY;
           goto UnlockAndExit;
        }

        /* Construct a descriptor pointing to the name */

        ObjDesc->Reference.OpCode  = (UINT8) AML_NAME_OP;
        ObjDesc->Reference.Object  = (void *) ObjectEntry;

        /*
         * Use AcpiAmlResolveToValue() to get the associated value.
         * The call to AcpiAmlResolveToValue causes
         * ObjDesc (allocated above) to always be deleted.
         *
         * NOTE: we can get away with passing in NULL for a walk state
         * because ObjDesc is guaranteed to not be a reference to either
         * a method local or a method argument
         */

        Status = AcpiAmlResolveToValue (&ObjDesc, NULL);
    }

    /*
     * If AcpiAmlResolveToValue() succeeded, the return value was
     * placed in ObjDesc.
     */

    if (ACPI_SUCCESS (Status))
    {
        Status = AE_CTRL_RETURN_VALUE;

        *ReturnObjDesc = ObjDesc;
        DEBUG_PRINT (ACPI_INFO,
            ("NsGetObjectValue: Returning obj %p\n", *ReturnObjDesc));
    }


UnlockAndExit:

    /* Unlock the namespace */

    AcpiCmReleaseMutex (ACPI_MTX_NAMESPACE);
    return_ACPI_STATUS (Status);
}
