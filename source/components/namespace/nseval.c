
/******************************************************************************
 * 
 * Module Name: nsapiexe - Public interfaces for ACPI control method 
 *                         lookup and execution
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


#define __NSAPIEXE_C__

#include <acpi.h>
#include <amlcode.h>
#include <interpreter.h>
#include <namespace.h>
#include <string.h>


#define _THIS_MODULE        "nsapiexe.c"
#define _COMPONENT          NAMESPACE


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", 'I', "Package stack not empty at method exit", "Package stack not empty at method exit"},
    {"0001", '1', "Method stack not empty at method exit", "Method stack not empty at method exit"},
    {"0002", 'I', "Object stack not empty at method exit", "Object stack not empty at method exit"},
    {"0003", '1', "Descriptor Allocation Failure", "Descriptor Allocation Failure"},
    {NULL, 'I', NULL, NULL}
};


ACPI_STATUS
AcpiExecuteMethodByHandle (NsHandle Handle, OBJECT_DESCRIPTOR *ReturnObject,
                            OBJECT_DESCRIPTOR **Params);

/****************************************************************************
 *
 * FUNCTION:    AcpiExecuteRelativeMethod
 *
 * PARAMETERS:  Handle              - Handle of containing object
 *              *MethodName         - Name of method to execute, If NULL, the
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
AcpiExecuteRelativeMethod (NsHandle Handle,
                           char * MethodName,
                           OBJECT_DESCRIPTOR *ReturnObject,
                           OBJECT_DESCRIPTOR **Params)
{
    char                NameBuffer[PATHNAME_MAX];
    ACPI_STATUS         Status;
    UINT32              MaxObjectPathLength = PATHNAME_MAX - 1;


    FUNCTION_TRACE ("AcpiExecuteRelativeMethod");

    /*
     *  Must have a valid handle
     */
    if (!Handle) 
    {
        FUNCTION_EXIT;
        return AE_BAD_PARAMETER;
    }

    /*
     *  If the caller specified a method then it must be a path relative to
     *  the object indicated by the handle we need to reserve space in the
     *  buffer to append the CM name later
     */
    if (MethodName) 
    {
        /*
         *  We will append the method name to the device pathname
         */
        MaxObjectPathLength -= (strlen (MethodName) + 1);
    }

    /*
     *  Get the device pathname
     */
    Status = NsHandleToPathname (Handle, MaxObjectPathLength, NameBuffer);
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
    if (MethodName) 
    {
        /*
         * Append the method name to the device pathname
         * (Path separator is a period) 
         */
        strcat (NameBuffer, ".");
        strcat (NameBuffer, MethodName);
    }

    /*
     *  Execute the method
     */
    Status = AcpiExecuteMethod (NameBuffer, ReturnObject, Params);

    FUNCTION_EXIT;
    return Status;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiExecuteMethod
 *
 * PARAMETERS:  *MethodName         - Name of method to execute
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
AcpiExecuteMethod (char * MethodName, OBJECT_DESCRIPTOR *ReturnObject,
                    OBJECT_DESCRIPTOR **Params)
{
    ACPI_STATUS         Status = AE_ERROR;
    nte                 *MethodNte = NULL;



    FUNCTION_TRACE ("AcpiExecuteMethod");


    /* Parameter validation */

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

    if (!MethodName)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AcpiExecuteMethod: MethodName is NULL\n"));
        FUNCTION_EXIT;
        return AE_BAD_PARAMETER;
    }

    /* Build an internal name string for the method */

    if (MethodName[0] != '\\' || MethodName[1] != '/')
    {
        MethodName = NsInternalizeName (MethodName);
    }


    /* Lookup the name in the namespace */

    Status = NsEnter (MethodName, TYPE_Any, MODE_Exec, (NsHandle *) &MethodNte);

    if (Status != AE_OK)
    {
        DEBUG_PRINT (ACPI_INFO, ("Method [%s] was not found, status=%.4X\n",
                        MethodName, Status));
        return Status;
    }


    /*
     * Now that we have a handle to the object, we can attempt
     * to execute it.
     */

    DEBUG_PRINT (ACPI_INFO, ("[%s Method %p Value %p\n",
                                MethodName, MethodNte, MethodNte->Value));

    Status = AcpiExecuteMethodByHandle ((NsHandle *) MethodNte, ReturnObject, Params);

    DEBUG_PRINT (ACPI_INFO, ("*** Completed execution of method %s ***\n",
                                MethodName));

    FUNCTION_EXIT;
    return Status;
}



/****************************************************************************
 *
 * FUNCTION:    AcpiExecuteMethodByHandle
 *
 * PARAMETERS:  Handle              - Handle of method to execute
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
AcpiExecuteMethodByHandle (NsHandle Handle, OBJECT_DESCRIPTOR *ReturnObject,
                            OBJECT_DESCRIPTOR **Params)
{
    nte                 *MethodNte;
    ACPI_STATUS         Status = AE_ERROR;
    OBJECT_DESCRIPTOR   *ObjDesc;


    FUNCTION_TRACE ("AcpiExecuteMethodByHandle");


    /* Parameter Validation */

    if (!Handle)
    {
        return AE_BAD_PARAMETER;
    }

    if (ReturnObject)
    {
        /* Initialize the return value */

        memset (ReturnObject, 0, sizeof (OBJECT_DESCRIPTOR));
    }


    /*
     * Two major cases here:
     * 1) The object is an actual control method -- execute it.
     * 2) The object is not a method -- just return it's current value
     */

    MethodNte = (nte *) Handle;
    if (NsGetType (MethodNte) == TYPE_Method)
    {

/* TBD: 
        NsExecuteControlMethod (MethodNte, Params);

    else
        NsGetObjectValue (MethodNte);
*/
        /* 
         * Case 1) We have an actual control method to execute
         */

        if (!MethodNte->Value)
        {
            DEBUG_PRINT (ACPI_ERROR, ("Method is undefined\n"));
        }

        else
        {
            /* 
             * Valid method, Set the current scope to that of the Method, and execute it.
             */

            DEBUG_PRINT (ACPI_INFO,
                        ("Control method at Offset %x Length %lx]\n",
                        ((meth *) MethodNte->Value)->Offset + 1,
                        ((meth *) MethodNte->Value)->Length - 1));

            NsDumpPathname (MethodNte->Scope, "AcpiExecuteMethodByHandle: Setting scope to", 
                            TRACE_NAMES, _COMPONENT);

            /* Reset the current scope to the beginning of scope stack */

            CurrentScope = &ScopeStack[0];

            /* Push current scope on scope stack and make Method->Scope current  */

            NsPushCurrentScope (MethodNte->Scope, TYPE_Method);

            NsDumpPathname (MethodNte, "AcpiExecuteMethodByHandle: Executing", 
                            TRACE_NAMES, _COMPONENT);

            DEBUG_PRINT (TRACE_NAMES, ("At offset %8XH\n",
                              ((meth *) MethodNte->Value)->Offset + 1));
    
            AmlClearPkgStack ();
            ObjStackTop = 0;    /* Clear object stack */
            

            /* 
             * Excecute the method via the interpreter
             */
            Status = AmlExecuteMethod (
                             ((meth *) MethodNte->Value)->Offset + 1,
                             ((meth *) MethodNte->Value)->Length - 1,
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
        }
    }

    else
    {
        /* 
         * Case 2) Object is NOT a method, just return its current value
         */
    
        ObjDesc = AllocateObjectDesc (&KDT[3]);
        if (ObjDesc)
        {
            /* Construct a descriptor pointing to the name */
        
            ObjDesc->Lvalue.ValType = (UINT8) TYPE_Lvalue;
            ObjDesc->Lvalue.OpCode  = (UINT8) AML_NameOp;
            ObjDesc->Lvalue.Ref     = (void *) MethodNte;

            /* 
             * Put it on the stack, and use AmlGetRvalue() to get the value.
             * Note that ObjStackTop points to the top valid entry, not to
             * the first unused position.
             */

            LocalDeleteObject ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]);
            ObjStack[ObjStackTop] = (void *) ObjDesc;

            /* This causes ObjDesc (allocated above) to always be deleted */

            Status = AmlGetRvalue ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop]);

            /* 
             * If AmlGetRvalue() succeeded, treat the top stack entry as
             * a return value.
             */

            if (AE_OK == Status)
            {
                Status = AE_RETURN_VALUE;
            }
        }

        else
        {
            /* Descriptor allocation failure */

            Status = AE_NO_MEMORY;
        }
    }


    /* TBD: Unecessary mapping? */

    if (AE_AML_ERROR == Status)
    {
        Status = AE_ERROR;
    }

    if (AE_RETURN_VALUE == Status)
    {
        /* 
         * If the Method returned a value and the caller provided a place
         * to store a returned value, Copy the returned value to the object
         * descriptor provided by the caller.
         */

        if (ReturnObject)
        {
            (*ReturnObject) = *((OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop]);            
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





