 
/******************************************************************************
 * 
 * Module Name: cmdelete - object deletion utilities
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

#define __CMDELETE_C__

#include <acpi.h>
#include <acpiobj.h>
#include <interpreter.h>
#include <namespace.h>


#define _THIS_MODULE        "cmdelete.c"
#define _COMPONENT          MISCELLANEOUS



/******************************************************************************
 *
 * FUNCTION:    CmUpdateRefCount
 *
 * PARAMETERS:  *Object         - Object whose ref count is to be updated
 *              Count           - Current ref count
 *              Action          - What to do
 * 
 * RETURN:      New ref count
 * 
 * DESCRIPTION: Modify the ref count and return it.
 *
 ******************************************************************************/

UINT32
CmUpdateRefCount (
    void                    *Object,
    UINT32                  Count,
    INT32                   Action)
{
    UINT32                  NewCount = Count;



    switch (Action)
    {

    case REF_INCREMENT:

        NewCount++;

        DEBUG_PRINT (ACPI_INFO, ("CmUpdateRefCount: Obj %p Refs=%d, [Incremented]\n",
                        Object, NewCount));
        break;


    case REF_DECREMENT:

        if (Count < 1)
        {
            DEBUG_PRINT (ACPI_INFO, ("CmUpdateRefCount: Obj %p Refs=%d, can't decrement! (Set to 0)\n",
                            Object, NewCount));

            NewCount = 0;
        }

        else
        {
            NewCount--;
            
            DEBUG_PRINT (ACPI_INFO, ("CmUpdateRefCount: Obj %p Refs=%d, [Decremented]\n",
                            Object, NewCount));
        }

        break;


    case REF_FORCE_DELETE:

        DEBUG_PRINT (ACPI_INFO, ("CmUpdateRefCount: Obj %p Refs=%d, Force delete! (Set to 0)\n",
                        Object, Count));
        
        NewCount = 0;
        break;


    default: 

        DEBUG_PRINT (ACPI_ERROR, ("CmUpdateRefCount: Unknown action (%d)\n", 
                        Action));
        break;
    }


    return (NewCount);
}


/******************************************************************************
 *
 * FUNCTION:    CmUpdateObjectReference
 *
 * PARAMETERS:  *Object             - Increment ref count for this object
 *                                    and all sub-objects
 *              Action              - Either REF_INCREMENT or REF_DECREMENT or
 *                                    REF_FORCE_DELETE
 * 
 * RETURN:      Status
 * 
 * DESCRIPTION: Increment the object reference count
 *
 * Object references are incremented when:
 * 1) An object is added as a value in an Name Table Entry (NTE)
 * 2) An object is copied (all subobjects must be incremented)
 *
 * Object references are decremented when:
 * 1) An object is removed from an NTE
 *
 ******************************************************************************/

ACPI_STATUS
CmUpdateObjectReference (
    ACPI_OBJECT_INTERNAL    *Object,
    INT32                   Action)
{
    UINT32                  i;
    ACPI_OBJECT_INTERNAL    *Next;


    FUNCTION_TRACE_PTR ("CmUpdateObjectReference", Object);


    /* Ignore a null object ptr */

    if (!Object)
    {
        return_ACPI_STATUS (AE_OK);
    }


    /* 
     * Make sure that this isn't a namespace handle or an AML pointer
     */

    if (IS_NS_HANDLE ((NAME_TABLE_ENTRY *) Object))
    {
        DEBUG_PRINT (ACPI_INFO, ("CmUpdateObjectReference: Object %p is NS handle\n",
                        Object));
        return_ACPI_STATUS (AE_OK);
    }

    if (NsIsInSystemTable (Object))
    {
        DEBUG_PRINT (ACPI_INFO, ("CmUpdateObjectReference: **** Object %p is Pcode Ptr\n",
                        Object));
        return_ACPI_STATUS (AE_OK);
    }


    /*
     * All sub-objects must have their reference count incremented also.
     * Different object types have different subobjects.
     */
    switch (Object->Common.Type)
    {

    case ACPI_TYPE_Device:

/* TBD:
        CmUpdateObjectReference (Object->Device.AddrHandler, Action);
*/
        CmUpdateObjectReference (Object->Device.SysHandler, Action);
        CmUpdateObjectReference (Object->Device.DrvHandler, Action);
        break;


    case INTERNAL_TYPE_AddressHandler:

        /* Must walk list of address handlers */

        Next = Object->AddrHandler.Link;
        while (Next)
        {
            Next->Common.ReferenceCount = CmUpdateRefCount (Next, 
                                            Next->Common.ReferenceCount, Action);

            Next = Next->AddrHandler.Link;
        }
        break;


    case ACPI_TYPE_Package:

        /* 
         * We must update all the sub-objects of the package
         * (Each of whom may have their own sub-objects, etc.
         */
        for (i = 0; i < Object->Package.Count; i++)
        {
            /* Check for end-of-list (partially constructed package) */

            if (!Object->Package.Elements[i])
            {
                break;
            }

            CmUpdateObjectReference (Object->Package.Elements[i], Action);
        }
        break;


    case ACPI_TYPE_FieldUnit:

        CmUpdateObjectReference (Object->FieldUnit.Container, Action);
        break;


    case INTERNAL_TYPE_DefField:

        CmUpdateObjectReference (Object->Field.Container, Action);
        break;


    case INTERNAL_TYPE_BankField:

        CmUpdateObjectReference (Object->BankField.Container, Action);
        CmUpdateObjectReference (Object->BankField.BankSelect, Action);
        break;


    case ACPI_TYPE_Region:

        CmUpdateObjectReference (Object->Region.Method, Action);
/* TBD:
        CmUpdateObjectReference (Object->Region.AddrHandler, Action);
*/
        break;


    case INTERNAL_TYPE_Lvalue:

        break;
    }


    /*
     * Now we can update the count in the main object
     */

    Object->Common.ReferenceCount = CmUpdateRefCount (Object, 
                                        Object->Common.ReferenceCount, Action);

    return_ACPI_STATUS (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    CmDeleteInternalObj
 *
 * PARAMETERS:  *Object        - Pointer to the list to be deleted
 * 
 * RETURN:      None
 * 
 * DESCRIPTION: Low level object deletion, after reference counts have been
 *              updated (All reference counts, including sub-objects!)
 *
 ******************************************************************************/

void
CmDeleteInternalObj (
    ACPI_OBJECT_INTERNAL    *Object)
{
    void                    *ObjPointer = NULL;
    UINT32                  i;
    ACPI_OBJECT_INTERNAL    *Next;
    ACPI_OBJECT_INTERNAL    *New;


    FUNCTION_TRACE_PTR ("CmDeleteInternalObj", Object);


    /* Only delete the object when the reference count reaches zero */

    if (Object->Common.ReferenceCount > 0)
    {
        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: Refs=%d, No delete\n", 
                                Object->Common.ReferenceCount));

        return_VOID;
    }

    
    /* Handle sub-objects and buffers within the object */

    switch (Object->Common.Type)
    {

    case ACPI_TYPE_Device:

        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: **** Device %p\n", 
                                Object));

        /* TBD: temp fix for handler ref count issues */

        CmUpdateObjectReference (Object->Device.AddrHandler, REF_DECREMENT);
        CmDeleteInternalObj (Object->Device.AddrHandler);
        CmDeleteInternalObj (Object->Device.SysHandler);
        CmDeleteInternalObj (Object->Device.DrvHandler);
        break;


    case INTERNAL_TYPE_AddressHandler:

        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: **** AddressHandler %p\n", 
                                Object));

        Next = Object->AddrHandler.Link;
        while (Next)
        {
            New = Next->AddrHandler.Link;
            if (!(Next->Common.Flags & AO_STATIC_ALLOCATION))
            {
                CmFree (Next);
            }

            Next = New;
        }
        break;

    case ACPI_TYPE_String:

        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: **** String %p, ptr %p\n", 
                                Object, Object->String.Pointer));

        /* Free the actual string buffer */

        ObjPointer = Object->String.Pointer;
        break;


    case ACPI_TYPE_Buffer:
        
        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: **** Buffer %p, ptr %p\n", 
                                Object, Object->Buffer.Pointer));

        /* Free the actual buffer */

        ObjPointer = Object->Buffer.Pointer;
        break;


    case ACPI_TYPE_Package:
        
        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: **** Package of count %d\n", 
                                Object->Package.Count));

        /* Free each object in the element array */

        for (i = 0; i < Object->Package.Count; i++)
        {
            /* Check for end-of-list (partially constructed package) */

            if (!Object->Package.Elements[i])
            {
                break;
            }

            CmDeleteInternalObj (Object->Package.Elements[i]);
        }

        /* Free the (variable length) element pointer array */

        ObjPointer = Object->Package.Elements;
        break;


    case ACPI_TYPE_FieldUnit:
        
        CmDeleteInternalObj (Object->FieldUnit.Container);
        break;


    case INTERNAL_TYPE_DefField:
        
        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: **** Field %p, container %p\n", 
                                Object, Object->Field.Container));

        CmDeleteInternalObj (Object->Field.Container);
        break;


    case INTERNAL_TYPE_BankField:
        
        CmDeleteInternalObj (Object->BankField.Container);
        CmDeleteInternalObj (Object->BankField.BankSelect);  /* TBD: is this necessary? */
        break;


    case ACPI_TYPE_Region:
        
        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: ***** Region %p, method %p\n", 
                                Object, Object->Region.Method));

        CmDeleteInternalObj (Object->Region.Method); 
/* TBD       
        CmDeleteInternalObj (Object->Region.AddrHandler);        
*/
        break;


    case INTERNAL_TYPE_Lvalue:
        
        if ((Object->Lvalue.Object) &&
           (!IS_NS_HANDLE (Object->Lvalue.Object)))
        {   
            DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: ***** Lvalue: %p\n", 
                                Object->Lvalue.Object));
            CmDeleteInternalObj (Object->Lvalue.Object);
        }
        break;


    default:

        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: ***** Obj Type: %d, no subobject delete\n", 
                                Object->Common.Type));
        break;
    }


    /*
     * Delete any allocated memory found above 
     */

    if (ObjPointer)
    {
        if (!NsIsInSystemTable (ObjPointer))
        {
            DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: Deleting Obj Ptr %p \n", 
                                    ObjPointer));

            CmFree (ObjPointer);
        }
    }

    
    /* Only delete the object if it was dynamically allocated */

    if (Object->Common.Flags & AO_STATIC_ALLOCATION)
    {
        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: Obj %p [%s] static allocation!\n",
                                Object, Gbl_NsTypeNames[Object->Common.Type]));
    }

    else
    {
        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObj: Deleting Obj %p [%s]\n",
                                Object, Gbl_NsTypeNames[Object->Common.Type]));

        CmFree (Object);
    }

    return_VOID;
}


/******************************************************************************
 *
 * FUNCTION:    CmDeleteInternalObject
 *
 * PARAMETERS:  *Object        - Pointer to the list to be deleted
 * 
 * RETURN:      None
 * 
 * DESCRIPTION: This function deletes a simple (non-package) object.
 *
 ******************************************************************************/

void
CmDeleteInternalObject (
    ACPI_OBJECT_INTERNAL    *Object)
{

    FUNCTION_TRACE_PTR ("CmDeleteInternalObject", Object);


    /*
     * TBD: Most of this code should be deleted when object reference
     * counts are completely implemented!
     */

    if (!Object)
    {
        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObject: **** Null Object Ptr\n"));
        return_VOID;
    }

    if (NsIsInSystemTable (Object))
    {
        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObject: **** Object %p is Pcode Ptr\n",
                        Object));
        return_VOID;
    }

    if (IS_NS_HANDLE (Object))
    {
        DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObject: **** Object %p is NS handle\n",
                        Object));
        return_VOID;
    }

    DEBUG_PRINT (ACPI_INFO, ("CmDeleteInternalObject: Obj %x Refs=%d\n", 
                            Object, Object->Common.ReferenceCount));

    /*
     * Decrement the reference count, and only actually delete the object
     * if the reference count becomes 0.  (Must also decrement the ref count
     * of all subobjects!)
     */

    CmUpdateObjectReference  (Object, REF_DECREMENT);

    /* Now attempt to delete the object and all sub-objects */

    CmDeleteInternalObj (Object);

    return_VOID;
}



/******************************************************************************
 *
 * FUNCTION:    CmDeleteInternalObjectList
 *
 * PARAMETERS:  *ObjList        - Pointer to the list to be deleted
 * 
 * RETURN:      Status          - the status of the call
 * 
 * DESCRIPTION: This function deletes an internal object list, including both
 *              simple objects and package objects
 *
 ******************************************************************************/

ACPI_STATUS
CmDeleteInternalObjectList (
    ACPI_OBJECT_INTERNAL    **ObjList)
{
    ACPI_OBJECT_INTERNAL    **InternalObj;
 
    
    FUNCTION_TRACE ("CmDeleteInternalObjectList");


    /* Walk the null-terminated internal list */

    for (InternalObj = ObjList; *InternalObj; InternalObj++)
    {
        /* 
         * Check for a package
         * Simple objects are simply stored in the array and do not
         * need to be deleted separately.
         */

        if ((*InternalObj)->Common.Type == ACPI_TYPE_Package)
        {
            /* Delete the package */
            
            /*
             * TBD: This might not be the right thing to do, depending
             * on how the internal package object was allocated!!!
             */

            CmDeleteInternalObj (*InternalObj);
        }

    }


    /* Free the combined parameter pointer list and object array */

    CmFree (ObjList);

    return_ACPI_STATUS (AE_OK);
}


