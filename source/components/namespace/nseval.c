
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


#define __NSEVAL_C__

#include <acpi.h>
#include <amlcode.h>
#include <interpreter.h>
#include <namespace.h>


#define _THIS_MODULE        "nseval.c"
#define _COMPONENT          NAMESPACE


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", 'I', "Package stack not empty at method exit", "Package stack not empty at method exit"},
    {"0001", '1', "Method stack not empty at method exit", "Method stack not empty at method exit"},
    {"0002", 'I', "Object stack not empty at method exit", "Object stack not empty at method exit"},
    {"0003", '1', "Descriptor Allocation Failure", "Descriptor Allocation Failure"},
    {NULL, 'I', NULL, NULL}
};



/****************************************************************************
 *
 * FUNCTION:    NsEvaluateRelative
 *
 * PARAMETERS:  ObjEntry            - NTE of containing object
 *              *Pathname           - Name of method to execute, If NULL, the
 *                                    handle is the object to execute
 *              *ReturnObject       - Where to put method's return value (if 
 *                                    any).  If NULL, no value is returned.
 *              **Params            - List of parameters to pass to
 *                                    method, terminated by NULL.
 *                                    Params itself may be NULL
 *                                    if no parameters are being
 *                                    passed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Find and execute the requested method using the handle as a
 *              scope
 *
 ****************************************************************************/

ACPI_STATUS
NsEvaluateRelative (
    NAME_TABLE_ENTRY        *ObjEntry, 
    char                    *Pathname, 
    ACPI_OBJECT             *ReturnObject, 
    ACPI_OBJECT             **Params)
{
    char                    NameBuffer[PATHNAME_MAX];
    ACPI_STATUS             Status;
    UINT32                  MaxObjectPathLength = PATHNAME_MAX - 1;


    FUNCTION_TRACE ("NsEvaluateRelative");

    /*
     *  Must have a valid object NTE
     */
    if (!ObjEntry) 
    {
        FUNCTION_EXIT;
        return AE_BAD_PARAMETER;
    }

    /*
     *  If the caller specified a method then it must be a path relative to
     *  the object indicated by the handle we need to reserve space in the
     *  buffer to append the CM name later
     */
    if (Pathname) 
    {
        /*
         *  We will append the method name to the device pathname
         */
        MaxObjectPathLength -= (strlen (Pathname) + 1);
    }

    /*
     *  Get the device pathname
     */
    Status = NsHandleToPathname (ObjEntry, MaxObjectPathLength, NameBuffer);
    if (Status != AE_OK) 
    {
        /*
         *  Failed the conversion
         */
        FUNCTION_EXIT;
        return Status;
    }

    /*
     *  If the caller specified a method then it must be a path relative to
     *  the object indicated by the handle
     */
    if (Pathname) 
    {
        /*
         * Append the method name to the device pathname
         * (Path separator is a period) 
         */
        strcat (NameBuffer, ".");
        strcat (NameBuffer, Pathname);
    }

    /*
     *  Execute the method
     */
    Status = NsEvaluateByName (NameBuffer, ReturnObject, Params);

    FUNCTION_EXIT;
    return Status;
}


/****************************************************************************
 *
 * FUNCTION:    NsEvaluateByName
 *
 * PARAMETERS:  Pathname            - Fully qualified pathname to the object
 *              *ReturnObject       - Where to put method's return value (if 
 *                                    any).  If NULL, no value is returned.
 *              **Params            - List of parameters to pass to
 *                                    method, terminated by NULL.
 *                                    Params itself may be NULL
 *                                    if no parameters are being
 *                                    passed.
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
    ACPI_OBJECT             *ReturnObject,
    ACPI_OBJECT             **Params)
{
    ACPI_STATUS             Status = AE_ERROR;
    NAME_TABLE_ENTRY        *ObjEntry = NULL;

    
    FUNCTION_TRACE ("NsEvaluateByName");


    /* Build an internal name string for the method */

    if (Pathname[0] != '\\' || Pathname[1] != '/')
    {
        Pathname = NsInternalizeName (Pathname);
    }


    /* Lookup the name in the namespace */

    Status = NsEnter (Pathname, TYPE_Any, MODE_Exec, &ObjEntry);

    if (Status != AE_OK)
    {
        DEBUG_PRINT (ACPI_INFO, ("Method [%s] was not found, status=%.4X\n",
                        Pathname, Status));
        return Status;
    }


    /*
     * Now that we have a handle to the object, we can attempt
     * to evaluate it.
     */

    DEBUG_PRINT (ACPI_INFO, ("[%s Method %p Value %p\n",
                                Pathname, ObjEntry, ObjEntry->Value));

    Status = NsEvaluateByHandle (ObjEntry, ReturnObject, Params);

    DEBUG_PRINT (ACPI_INFO, ("*** Completed execution of method %s ***\n",
                                Pathname));

    FUNCTION_EXIT;
    return Status;
}


/****************************************************************************
 *
 * FUNCTION:    NsEvaluateByHandle
 *
 * PARAMETERS:  ObjEntry            - NTE of method to execute
 *              *ReturnObject       - Where to put method's return value (if 
 *                                    any).  If NULL, no value is returned.
 *              **Params            - List of parameters to pass to
 *                                    method, terminated by NULL.
 *                                    Params itself may be NULL
 *                                    if no parameters are being
 *                                    passed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute the requested method passing the given parameters
 *
 ****************************************************************************/

ACPI_STATUS
NsEvaluateByHandle (
    NAME_TABLE_ENTRY        *ObjEntry, 
    ACPI_OBJECT             *ReturnObject,
    ACPI_OBJECT             **Params)
{
    ACPI_STATUS             Status = AE_ERROR;


    FUNCTION_TRACE ("NsEvaluateByHandle");


    /* Parameter Validation */

    if (!RootObject->Scope)
    {
        /* 
         * If the name space has not been initialized, the Method has surely
         * not been defined and there is nothing to execute.
         */

        DEBUG_PRINT (ACPI_ERROR, ("Name space not initialized ==> method not defined\n"));
        FUNCTION_EXIT;
        return AE_NO_NAMESPACE;
    }

    if (!ObjEntry)
    {
        FUNCTION_EXIT;
        return AE_BAD_PARAMETER;
    }

    if (ReturnObject)
    {
        /* Initialize the return value */

        memset (ReturnObject, 0, sizeof (ACPI_OBJECT));
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


    /* TBD: Unecessary mapping? */

    if (AE_AML_ERROR == Status)
    {
        Status = AE_ERROR;
    }


    /*
     * Check if there is a return value on the stack that must be dealt with 
     */

    if (AE_RETURN_VALUE == Status)
    {
        /* 
         * If the Method returned a value and the caller provided a place
         * to store a returned value, Copy the returned value to the object
         * descriptor provided by the caller.
         */

        if (ReturnObject)
        {
            (*ReturnObject) = *((ACPI_OBJECT *) ObjStack[ObjStackTop]);            
        }
    
        /* 
         * TBD: do we ever want to delete this??? 
         * There are clearly cases that we don't and this will fault
         */

        /* OsdFree (ObjStack[ObjStackTop]); */

        Status = AE_OK;
    }

    FUNCTION_EXIT;
    return Status;
}


/****************************************************************************
 *
 * FUNCTION:    NsExecuteControlMethod
 *
 * PARAMETERS:  MethodEntry         - The Nte of the object/method
 *              **Params            - List of parameters to pass to
 *                                    method, terminated by NULL.
 *                                    Params itself may be NULL
 *                                    if no parameters are being
 *                                    passed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: execute the requested method passing the given parameters
 *
 ****************************************************************************/

ACPI_STATUS
NsExecuteControlMethod (
    NAME_TABLE_ENTRY        *MethodEntry, 
    ACPI_OBJECT             **Params)
{
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("NsExecuteControlMethod");


    /* Verify that there is a method associated with this object */

    if (!MethodEntry->Value)
    {
        DEBUG_PRINT (ACPI_ERROR, ("Method is undefined\n"));
        FUNCTION_EXIT;
        return AE_ERROR;
    }

    /* 
     * Valid method, Set the current scope to that of the Method, and execute it.
     */

    DEBUG_PRINT (ACPI_INFO,
                ("Control method at Offset %x Length %lx]\n",
                ((METHOD_INFO *) MethodEntry->Value)->Offset + 1,
                ((METHOD_INFO *) MethodEntry->Value)->Length - 1));

    NsDumpPathname (MethodEntry->Scope, "NsEvaluateByHandle: Setting scope to", 
                    TRACE_NAMES, _COMPONENT);

    /* Reset the current scope to the beginning of scope stack */

    CurrentScope = &ScopeStack[0];

    /* Push current scope on scope stack and make Method->Scope current  */

    NsPushCurrentScope (MethodEntry->Scope, TYPE_Method);

    NsDumpPathname (MethodEntry, "NsEvaluateByHandle: Executing", 
                    TRACE_NAMES, _COMPONENT);

    DEBUG_PRINT (TRACE_NAMES, ("At offset %8XH\n",
                      ((METHOD_INFO *) MethodEntry->Value)->Offset + 1));

    AmlClearPkgStack ();
    ObjStackTop = 0;    /* Clear object stack */
    

    /* 
     * Excecute the method via the interpreter
     */
    Status = AmlExecuteMethod (((METHOD_INFO *) MethodEntry->Value)->Offset + 1,
                               ((METHOD_INFO *) MethodEntry->Value)->Length - 1,
                               Params);

    if (AmlPackageNested ())
    {
        /*  Package stack not empty at method exit and should be  */

        REPORT_INFO (&KDT[0]);
    }

    if (AmlGetMethodDepth () > -1)
    {
        /*  Method stack not empty at method exit and should be */

        REPORT_ERROR (&KDT[1]);
    }

    if (ObjStackTop)
    {
        /* Object stack is not empty at method exit and should be */

        REPORT_INFO (&KDT[2]);
        AmlDumpStack (MODE_Exec, "Remaining Object Stack entries", -1, "");
    }

    FUNCTION_EXIT;
    return Status;
}


/****************************************************************************
 *
 * FUNCTION:    NsGetObjectValue
 *
 * PARAMETERS:  ObjectEntry         - The Nte of the object
 *              **Params            - List of parameters to pass to
 *                                    method, terminated by NULL.
 *                                    Params itself may be NULL
 *                                    if no parameters are being
 *                                    passed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: return the current value of the object
 *
 ****************************************************************************/

ACPI_STATUS
NsGetObjectValue (
    NAME_TABLE_ENTRY        *ObjectEntry)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT             *ObjDesc;


    FUNCTION_TRACE ("NsGetObjectValue");


    ObjDesc = AllocateObjectDesc (&KDT[3]);
    if (!ObjDesc)
    {
        /* Descriptor allocation failure */

        FUNCTION_EXIT;
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

    LocalDeleteObject ((ACPI_OBJECT **) &ObjStack[ObjStackTop]);
    ObjStack[ObjStackTop] = (void *) ObjDesc;

    /* This causes ObjDesc (allocated above) to always be deleted */

    Status = AmlGetRvalue ((ACPI_OBJECT **) &ObjStack[ObjStackTop]);

    /* 
     * If AmlGetRvalue() succeeded, treat the top stack entry as
     * a return value.
     */

    if (Status == AE_OK)
    {
        Status = AE_RETURN_VALUE;
    }


    FUNCTION_EXIT;
    return Status;
}
