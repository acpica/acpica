
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

#include <acpi.h>
#include <amlcode.h>
#include <parser.h>
#include <interp.h>
#include <namesp.h>


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nseval");



/****************************************************************************
 *
 * FUNCTION:    NsEvaluateRelative
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
 ****************************************************************************/

ACPI_STATUS
NsEvaluateRelative (
    NAME_TABLE_ENTRY        *RelObjEntry, 
    char                    *Pathname, 
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    *ReturnObject)
{
    ACPI_STATUS             Status;
    NAME_TABLE_ENTRY        *ObjEntry = NULL;
    char                    *InternalPath = NULL;


    FUNCTION_TRACE ("NsEvaluateRelative");


    /*
     * Must have a valid object NTE
     */
    if (!RelObjEntry) 
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /* Build an internal name string for the method */

    Status = NsInternalizeName (Pathname, &InternalPath);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    /* Lookup the name in the namespace */

    Status = NsLookup (RelObjEntry->Scope, InternalPath, ACPI_TYPE_Any, IMODE_Execute, 
                                NS_NO_UPSEARCH, &ObjEntry);
    if (Status != AE_OK)
    {
        DEBUG_PRINT (ACPI_INFO, ("NsEvaluateRelative: Object [%s] not found [%.4X]\n",
                        InternalPath, Status));

    }

    else
    {
        /*
         * Now that we have a handle to the object, we can attempt
         * to evaluate it.
         */

        DEBUG_PRINT (ACPI_INFO, ("NsEvaluateRelative: %s [%p] Value %p\n",
                                    Pathname, ObjEntry, ObjEntry->Object));

        Status = NsEvaluateByHandle (ObjEntry, Params, ReturnObject);

        DEBUG_PRINT (ACPI_INFO, ("NsEvaluateRelative: *** Completed eval of object %s ***\n",
                                    Pathname));
    }


    /* Cleanup */

    CmFree (InternalPath);

    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    NsEvaluateByName
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
 ****************************************************************************/

ACPI_STATUS
NsEvaluateByName (
    char                    *Pathname, 
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    *ReturnObject)
{
    ACPI_STATUS             Status;
    NAME_TABLE_ENTRY        *ObjEntry = NULL;
    char                    *InternalPath = NULL;

    
    FUNCTION_TRACE ("NsEvaluateByName");


    /* Build an internal name string for the method */

    if (Pathname[0] != '\\' || Pathname[1] != '/')
    {
        Status = NsInternalizeName (Pathname, &InternalPath);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }


    /* Lookup the name in the namespace */

    Status = NsLookup (NULL, InternalPath, ACPI_TYPE_Any, IMODE_Execute, 
                                NS_NO_UPSEARCH, &ObjEntry);
    if (Status != AE_OK)
    {
        DEBUG_PRINT (ACPI_INFO, ("NsEvaluateByName: Object at [%s] was not found, status=%.4X\n",
                        InternalPath, Status));

    }

    else
    {
        /*
         * Now that we have a handle to the object, we can attempt
         * to evaluate it.
         */

        DEBUG_PRINT (ACPI_INFO, ("NsEvaluateByName: %s [%p] Value %p\n",
                                    Pathname, ObjEntry, ObjEntry->Object));

        Status = NsEvaluateByHandle (ObjEntry, Params, ReturnObject);

        DEBUG_PRINT (ACPI_INFO, ("NsEvaluateByName: *** Completed eval of object %s ***\n",
                                    Pathname));
    }


    /* Cleanup */

    if (InternalPath)
    {
        CmFree (InternalPath);
    }

    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    NsEvaluateByHandle
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
 ****************************************************************************/

ACPI_STATUS
NsEvaluateByHandle (
    NAME_TABLE_ENTRY        *ObjEntry, 
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    *ReturnObject)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    *LocalReturnObject;


    FUNCTION_TRACE ("NsEvaluateByHandle");


    /* Parameter Validation */

    if (!Gbl_RootObject->Scope)
    {
        /* 
         * If the name space has not been initialized, the Method has surely
         * not been defined and there is nothing to execute.
         */

        DEBUG_PRINT (ACPI_ERROR, ("NsEvaluateByHandle: Name space not initialized - method not defined\n"));
        return_ACPI_STATUS (AE_NO_NAMESPACE);
    }

    if (!ObjEntry)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    if (ReturnObject)
    {
        /* Initialize the return value to an invalid object */

        CmInitStaticObject (ReturnObject);
        ReturnObject->Common.Type = INTERNAL_TYPE_Invalid;
    }


    /*
     * Two major cases here:
     * 1) The object is an actual control method -- execute it.
     * 2) The object is not a method -- just return it's current value
     */

    if (NsGetType (ObjEntry) == ACPI_TYPE_Method)
    {
        /* Case 1) We have an actual control method to execute */

        Status = NsExecuteControlMethod (ObjEntry, Params, &LocalReturnObject);
    }

    else
    {
        /* Case 2) Object is NOT a method, just return its current value */
    
        Status = NsGetObjectValue (ObjEntry, &LocalReturnObject);
    }


    /*
     * Check if there is a return value on the stack that must be dealt with 
     */

    if (Status == AE_RETURN_VALUE)
    {
BREAKPOINT3;
        /* 
         * If the Method returned a value and the caller provided a place
         * to store a returned value, Copy the returned value to the object
         * descriptor provided by the caller.
         */

        if (ReturnObject)
        {
            /* Valid return object, copy the returned object that is on the stack */

            Status = CmCopyInternalObject (LocalReturnObject, ReturnObject);
        }


        CmDeleteInternalObject (LocalReturnObject);

#if defined _RPARSER
        /* 
         * Now that the return value (object) has been copied, we must purge the stack 
         * of the return value by deleting the object and popping the stack!
         *
         * TBD: There a difference between what is returned by NsExecuteControlMethod and
         * NsGetObjectValue:  The PsxObjStackLevel() is one vs. zero (respectively).  
         * What is the real reason for this??
         */

        PsxObjStackSetValue (STACK_TOP, NULL);
        if (PsxObjStackLevel ())
        {
            DEBUG_PRINT (ACPI_ERROR, ("NsEvaluateByHandle: Object stack not empty: TOS=%d\n",
                            PsxObjStackLevel ()));

            /* In all cases, clear the object stack! */

            PsxObjStackClearAll ();
        }
#endif

        /* Map AE_RETURN_VALUE to AE_OK, we are done with it */

        if (Status == AE_RETURN_VALUE)
        {
            Status = AE_OK;
        }
    }

    else
    {
#if defined _RPARSER
        /* There could be an internal return value on the stack */

        PsxObjStackDeleteValue (STACK_TOP);
#endif
    }

    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    NsExecuteControlMethod
 *
 * PARAMETERS:  MethodEntry         - The Nte of the object/method
 *              **Params            - List of parameters to pass to the method,
 *                                    terminated by NULL.  Params itself may be 
 *                                    NULL if no parameters are being passed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute the requested method passing the given parameters
 *
 ****************************************************************************/

ACPI_STATUS
NsExecuteControlMethod (
    NAME_TABLE_ENTRY        *MethodEntry, 
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    **ReturnObjDesc)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    FUNCTION_TRACE ("NsExecuteControlMethod");


    /* Verify that there is a method associated with this object */

    if (!(ObjDesc = NsGetAttachedObject ((ACPI_HANDLE) MethodEntry)))
    {
        DEBUG_PRINT (ACPI_ERROR, ("Control method is undefined (nil value)\n"));
        return_ACPI_STATUS (AE_ERROR);
    }

    /* 
     * Valid method, Set the current scope to that of the Method, and execute it.
     */

    DEBUG_PRINT (ACPI_INFO, ("Control method at Offset %x Length %lx]\n",
                    ObjDesc->Method.Pcode + 1,
                    ObjDesc->Method.PcodeLength - 1));

    DUMP_PATHNAME (MethodEntry->Scope, "NsExecuteControlMethod: Setting scope to", 
                    TRACE_NAMES, _COMPONENT);

    /* Reset the current scope to the beginning of scope stack */

    NsScopeStackClear ();

    /* Push current scope on scope stack and make Method->Scope current  */

    Status = NsScopeStackPush (MethodEntry->Scope, ACPI_TYPE_Method);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    DUMP_PATHNAME (MethodEntry, "NsExecuteControlMethod: Executing", 
                    TRACE_NAMES, _COMPONENT);

    DEBUG_PRINT (TRACE_NAMES, ("At offset %8XH\n",
                      ObjDesc->Method.Pcode + 1));

    /* Clear both the package and object stacks */

    RPARSER_ONLY ((AmlClearPkgStack ()));     /* Recursive parser only */
    RPARSER_ONLY (PsxObjStackClearAll ());
    
    /* 
     * Excecute the method via the interpreter
     */
    Status = AmlExecuteMethod (ObjDesc, Params, ReturnObjDesc);


    /* TBD: remove vestiges of old parser */

#ifdef _RPARSER
    {

        UINT32                  i;


        if (AmlPkgStackLevel ())
        {
            /* Package stack not empty at method exit and should be */

            REPORT_ERROR ("Package stack not empty at method exit");
        }

        /* If this was a nested method call, the method stack won't be empty */

        /* Check the object stack */

        if ((PsxObjStackLevel ()) &&
            (Status != AE_RETURN_VALUE))
        {
            /* Object stack is not empty at method exit and should be */

            REPORT_ERROR ("Object stack not empty at method exit");
            DEBUG_PRINT (ACPI_ERROR, ("%d Remaining: \n", PsxObjStackLevel ()));

            for (i = 0; i < (UINT32) PsxObjStackLevel (); i++)
            {
                DEBUG_PRINT (ACPI_ERROR, ("Object Stack [-%d]: %p\n", i, PsxObjStackGetValue (i)));
            }

            DUMP_OPERANDS (PsxObjStackGetTopPtr(), IMODE_Execute, "Remaining Object Stack entries", -1, "");
        }
    }
#endif

    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    NsGetObjectValue
 *
 * PARAMETERS:  ObjectEntry         - The Nte of the object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Return the current value of the object
 *
 ****************************************************************************/

ACPI_STATUS
NsGetObjectValue (
    NAME_TABLE_ENTRY        *ObjectEntry,
    ACPI_OBJECT_INTERNAL    **ReturnObjDesc)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    FUNCTION_TRACE ("NsGetObjectValue");


    /* Create an Lvalue object to contain the object */

    ObjDesc = CmCreateInternalObject (INTERNAL_TYPE_Lvalue);
    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Construct a descriptor pointing to the name */

    ObjDesc->Lvalue.OpCode  = (UINT8) AML_NameOp;
    ObjDesc->Lvalue.Object  = (void *) ObjectEntry;

    /* 
     * Use AmlGetRvalue() to get the associated value.  The call to AmlGetRvalue causes 
     * ObjDesc (allocated above) to always be deleted.
     */

    Status = AmlGetRvalue (&ObjDesc);

    /* 
     * If AmlGetRvalue() succeeded, the return value was placed in ObjDesc.
     */

    if (Status == AE_OK)
    {
        Status = AE_RETURN_VALUE;

        *ReturnObjDesc = ObjDesc;
        DEBUG_PRINT (ACPI_INFO, ("NsGetObjectValue: Returning obj %p\n", 
                            *ReturnObjDesc));
    }


    return_ACPI_STATUS (Status);
}
