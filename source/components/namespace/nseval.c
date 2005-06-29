
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
 * license (without the right to sublicense), under only those claims of Intel
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
#include <interpreter.h>
#include <namespace.h>


#define _THIS_MODULE        "nseval.c"
#define _COMPONENT          NAMESPACE



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
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }


    /* Build an internal name string for the method */

    Status = NsInternalizeName (Pathname, &InternalPath);
    if (ACPI_FAILURE (Status))
    {
        FUNCTION_STATUS_EXIT (Status);
        return Status;
    }


    /* Lookup the name in the namespace */

    Status = NsLookup (RelObjEntry->Scope, InternalPath, TYPE_Any, MODE_Exec, 
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
                                    Pathname, ObjEntry, ObjEntry->Value));

        Status = NsEvaluateByHandle (ObjEntry, Params, ReturnObject);

        DEBUG_PRINT (ACPI_INFO, ("NsEvaluateRelative: *** Completed eval of object %s ***\n",
                                    Pathname));
    }


    /* Cleanup */

    OsdFree (InternalPath);

    FUNCTION_STATUS_EXIT (Status);
    return Status;
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
            FUNCTION_STATUS_EXIT (Status);
            return Status;
        }
    }


    /* Lookup the name in the namespace */

    Status = NsLookup (NULL, InternalPath, TYPE_Any, MODE_Exec, 
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
                                    Pathname, ObjEntry, ObjEntry->Value));

        Status = NsEvaluateByHandle (ObjEntry, Params, ReturnObject);

        DEBUG_PRINT (ACPI_INFO, ("NsEvaluateByName: *** Completed eval of object %s ***\n",
                                    Pathname));
    }


    /* Cleanup */

    if (InternalPath)
    {
        OsdFree (InternalPath);
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
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


    FUNCTION_TRACE ("NsEvaluateByHandle");


    /* Parameter Validation */

    if (!RootObject->Scope)
    {
        /* 
         * If the name space has not been initialized, the Method has surely
         * not been defined and there is nothing to execute.
         */

        DEBUG_PRINT (ACPI_ERROR, ("NsEvaluateByHandle: Name space not initialized - method not defined\n"));
        FUNCTION_STATUS_EXIT (AE_NO_NAMESPACE);
        return AE_NO_NAMESPACE;
    }

    if (!ObjEntry)
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }

    if (ReturnObject)
    {
        /* Initialize the return value to an invalid object */

        memset (ReturnObject, 0, sizeof (ACPI_OBJECT_INTERNAL));
        ReturnObject->ValType = TYPE_Invalid;
    }


    /*
     * Two major cases here:
     * 1) The object is an actual control method -- execute it.
     * 2) The object is not a method -- just return it's current value
     */

    if (NsGetType (ObjEntry) == TYPE_Method)
    {
        /* Case 1) We have an actual control method to execute */

        Status = NsExecuteControlMethod (ObjEntry, Params);
    }

    else
    {
        /* Case 2) Object is NOT a method, just return its current value */
    
        Status = NsGetObjectValue (ObjEntry);
    }


    /*
     * Check if there is a return value on the stack that must be dealt with 
     */

    if (AE_RETURN_VALUE == Status)
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

            (*ReturnObject) = *((ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop]);            
        }

        /* 
         * Now that the return value (object) has been copied, we must purge the stack 
         * of the return value by deleting the object and popping the stack!
         *
         * TBD: There a difference between what is returned by NsExecuteControlMethod and
         * NsGetObjectValue - ObjStackTop is one vs. zero (respectively).  
         * What is the real reason for this??
         */

        LocalDeleteObject ((ACPI_OBJECT_INTERNAL **) &ObjStack[ObjStackTop]);
        if (ObjStackTop)
        {
            if (ObjStackTop > 1)
            {
                DEBUG_PRINT (ACPI_ERROR, ("NsEvaluateByHandle: Object stack not empty: %d\n",
                                ObjStackTop));
            }

            /* In all cases, clear the object stack! */

            ObjStackTop = 0;
        }

        /* Map AE_RETURN_VALUE to AE_OK, we are done with it */

        Status = AE_OK;
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
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
    ACPI_OBJECT_INTERNAL    **Params)
{
    ACPI_STATUS             Status;
    UINT32                  i;


    FUNCTION_TRACE ("NsExecuteControlMethod");


    /* Verify that there is a method associated with this object */

    if (!MethodEntry->Value)
    {
        DEBUG_PRINT (ACPI_ERROR, ("Control method is undefined (nil value)\n"));
        FUNCTION_STATUS_EXIT (AE_ERROR);
        return AE_ERROR;
    }

    /* 
     * Valid method, Set the current scope to that of the Method, and execute it.
     */

    DEBUG_PRINT (ACPI_INFO,
                ("Control method at Offset %x Length %lx]\n",
                ((METHOD_INFO *) MethodEntry->Value)->Offset + 1,
                ((METHOD_INFO *) MethodEntry->Value)->Length - 1));

    NsDumpPathname (MethodEntry->Scope, "NsExecuteControlMethod: Setting scope to", 
                    TRACE_NAMES, _COMPONENT);

    /* Reset the current scope to the beginning of scope stack */

    CurrentScope = &ScopeStack[0];

    /* Push current scope on scope stack and make Method->Scope current  */

    NsPushCurrentScope (MethodEntry->Scope, TYPE_Method);

    NsDumpPathname (MethodEntry, "NsExecuteControlMethod: Executing", 
                    TRACE_NAMES, _COMPONENT);

    DEBUG_PRINT (TRACE_NAMES, ("At offset %8XH\n",
                      ((METHOD_INFO *) MethodEntry->Value)->Offset + 1));

    /* Clear both the package and object stacks */

    AmlClearPkgStack ();
    AmlClearObjStack ();
    
    /* 
     * Excecute the method via the interpreter
     */
    Status = AmlExecuteMethod (((METHOD_INFO *) MethodEntry->Value)->Offset + 1,
                               ((METHOD_INFO *) MethodEntry->Value)->Length - 1,
                               Params);

    if (AmlPkgStackLevel ())
    {
        /* Package stack not empty at method exit and should be */

        REPORT_ERROR ("Package stack not empty at method exit");
    }

    if (AmlMthStackLevel () > -1)
    {
        /* Method stack not empty at method exit and should be */

        REPORT_ERROR ("Method stack not empty at method exit");
    }

    if ((AmlObjStackLevel ()) &&
        (Status != AE_RETURN_VALUE))
    {
        /* Object stack is not empty at method exit and should be */

        REPORT_ERROR ("Object stack not empty at method exit");
        DEBUG_PRINT (ACPI_ERROR, ("%d Remaining: \n", ObjStackTop));

        for (i = 0; i < (UINT32) ObjStackTop; i++)
        {
            DEBUG_PRINT (ACPI_ERROR, ("Object Stack [%d]: %p\n", i, ObjStack[ObjStackTop]));
        }

        AmlDumpObjStack (MODE_Exec, "Remaining Object Stack entries", -1, "");
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
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
    NAME_TABLE_ENTRY        *ObjectEntry)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    FUNCTION_TRACE ("NsGetObjectValue");


    ObjDesc = AllocateObjectDesc ();
    if (!ObjDesc)
    {
        /* Descriptor allocation failure */

        FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
        return AE_NO_MEMORY;
    }

    /* Construct a descriptor pointing to the name */

    ObjDesc->Lvalue.ValType = (UINT8) TYPE_Lvalue;
    ObjDesc->Lvalue.OpCode  = (UINT8) AML_NameOp;
    ObjDesc->Lvalue.Ref     = (void *) ObjectEntry;


    /* 
     * Put the ObjDesc on the stack, and use AmlGetRvalue() to get 
     * the associated value.  Note that ObjStackTop points to the 
     * top valid entry, not to the first unused position.
     */

    LocalDeleteObject ((ACPI_OBJECT_INTERNAL **) &ObjStack[ObjStackTop]);
    ObjStack[ObjStackTop] = (void *) ObjDesc;

    /* This causes ObjDesc (allocated above) to always be deleted */

    Status = AmlGetRvalue ((ACPI_OBJECT_INTERNAL **) &ObjStack[ObjStackTop]);

    /* 
     * If AmlGetRvalue() succeeded, treat the top stack entry as
     * a return value.
     */

    if (Status == AE_OK)
    {
        Status = AE_RETURN_VALUE;
    }

    DEBUG_PRINT (ACPI_INFO, ("NsGetObjectValue: Returning object value (on obj stack)\n"));

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}
