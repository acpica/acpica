/******************************************************************************
 * 
 * Module Name: evregion - ACPI AddressSpace / OpRegion handler dispatch
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

#include <acpi.h>
#include <events.h>
#include <namespace.h>

#define _THIS_MODULE        "evregion.c"
#define _COMPONENT          EVENT_HANDLING


#define GO_NO_FURTHER   (void *) 0xffffffff


/**************************************************************************
 *
 * FUNCTION:    EvAddressSpaceDispatch
 *
 * PARAMETERS:  SpaceId             - ID of the address space (0-255)
 *              Function            - Read or Write operation
 *              Address             - Where in the space to read or write
 *              BitWidth            - Field width in bits (8, 16, or 32)
 *              Value               - Pointer to in or out value
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dispatch an address space or operation region access to  
 *              a previously installed handler.
 *
 *************************************************************************/

ACPI_STATUS
EvAddressSpaceDispatch (
    ACPI_OBJECT_INTERNAL   *Obj,
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value)
{
    ACPI_STATUS             Status;
    ADDRESS_SPACE_HANDLER   Handler;
    void                   *Context;

    /* Check for an installed handler */

    if (!Obj->Region.AddrHandler)
    {
        return AE_EXIST;
    }

    /* 
     * Invoke the handler.  
     * Value of "Value" is used in case this is a write operation 
     */

    Handler = Obj->Region.AddrHandler->AddrHandler.Handler;
    Context = Obj->Region.AddrHandler->AddrHandler.Context;
    Status = Handler (Function, Address, BitWidth, Value, Context);

    return Status;
}

/******************************************************************************
 *
 * FUNCTION:    EvDisassociateRegionAndHandler
 *
 * PARAMETERS:  HandlerObj      - Handler Object
 *              RegionObj       - Region Object
 *
 * RETURN:      None
 *
 * DESCRIPTION: Break the association between the handler and the region
 *              this is a two way association.
 *
 ******************************************************************************/

void
EvDisassociateRegionAndHandler(
    ACPI_OBJECT_INTERNAL    *HandlerObj,
    ACPI_OBJECT_INTERNAL    *RegionObj)
{
    ACPI_OBJECT_INTERNAL   *ObjDesc;
    ACPI_OBJECT_INTERNAL   **LastObjPtr;


    FUNCTION_TRACE ("EvDisassociateRegionAndHandler");


    /*
     *  First stop region accesses by executing the _REG
     *  methods
     */

    //  BUGBUG: Need to call _REG for this region

    /*
     *  Remove handler reference in the region
     *
     *  NOTE: this doesn't mean that the region goes away
     *  The region is just inaccessible as indicated to
     *  the _REG method
     */

    /*
     *  Find this region in the handler's list
     */
    ObjDesc = HandlerObj->AddrHandler.RegionList;
    LastObjPtr = &ObjDesc->AddrHandler.RegionList;

    while (ObjDesc)
    {
        /*
         *  See if this is the one
         */
        if (ObjDesc == RegionObj)
        {
            /*
             *  This is it, remove it from the handler's list
             */
            *LastObjPtr = ObjDesc->Region.Link;

            /*
             *  Remove handler reference in the region and
             *  the region reference in the handler
             */
            CmUpdateObjectReference (RegionObj, REF_DECREMENT);
            CmUpdateObjectReference (HandlerObj, REF_DECREMENT);

            return;

        } /* found the right handler */

        /*
         *  Move through the linked list of handlers
         */
        LastObjPtr = &ObjDesc->Region.Link;
        ObjDesc = ObjDesc->Region.Link;
    }

    /*
     *  If we get here, the region was not not in the handler's region list
     */

}  /* EvDisassociateRegionAndHandler */


/******************************************************************************
 *
 * FUNCTION:    EvAssociateRegionAndHander
 *
 * PARAMETERS:  HandlerObj      - Handler Object
 *              RegionObj       - Region Object
 *
 * RETURN:      None
 *
 * DESCRIPTION: Create the association between the handler and the region
 *              this is a two way association.
 *
 ******************************************************************************/

EvAssociateRegionAndHander(
    ACPI_OBJECT_INTERNAL    *HandlerObj,
    ACPI_OBJECT_INTERNAL    *RegionObj)
{
    FUNCTION_TRACE ("EvAssociateRegionAndHander");


    /*
     *  BUGBUG:  We should invoke _REG here up to 2 times, If there was
     *           a previous handler, it should have _REG run and the new
     *           handler too.
     */

    /*
     *  Break any old associations
     */
    if (RegionObj->Region.AddrHandler)
    {
        EvDisassociateRegionAndHandler(RegionObj->Region.AddrHandler, RegionObj);
    }

    /*
     *  We need to update the reference for the handler and the region
     */
    CmUpdateObjectReference (HandlerObj, REF_INCREMENT);
    CmUpdateObjectReference (RegionObj, REF_INCREMENT);

    /*
     *  Link this region to the front of the handler's list
     */

    RegionObj->Region.Link = HandlerObj->AddrHandler.RegionList;
    HandlerObj->AddrHandler.RegionList = RegionObj;

    return_ACPI_STATUS (AE_OK);

}  /* EvAssociateRegionAndHander */


/****************************************************************************
 *
 * FUNCTION:    EvAddrHandlerHelper   
 *
 * PARAMETERS:  Handle              - Entry to be dumped
 *              Level               - Nesting level of the handle
 *              Context             - Passed into NsWalkNamespace
 *
 * DESCRIPTION: This routine checks to see if the object is a Region if it
 *              is then the address handler is installed in it.
 *
 *              If the Object is a Device, and the device has a handler of
 *              the same type then the search is terminated in that branch.
 *
 *              This is because the existing handler is closer in proximity
 *              to any more regions than the one we are trying to install.
 *
 ***************************************************************************/

void *
EvAddrHandlerHelper (
    ACPI_HANDLE             ObjHandle, 
    UINT32                  Level, 
    void                    *Context)
{
    ACPI_OBJECT_INTERNAL   *HandlerObj;
    ACPI_OBJECT_INTERNAL   *TmpObj;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    NAME_TABLE_ENTRY        *ObjEntry;


    FUNCTION_TRACE ("InsAddrHandlerHelper");


    HandlerObj = (ACPI_OBJECT_INTERNAL *) Context;

    /* Parameter validation */

    if (!HandlerObj)
    {
        return (void *) AE_OK;
    }

    /* Convert and validate the device handle */

    if (!(ObjEntry = NsConvertHandleToEntry (ObjHandle)))
    {
        return (void *) AE_BAD_PARAMETER;
    }

    /*
     *  We only care about regions.and objects
     *  that can have address handlers
     */

    if ((ObjEntry->Type != TYPE_Device) &&
        (ObjEntry->Type != TYPE_Region))
    {
        return (void *) AE_OK;
    }

    /* Check for an existing internal object */

    ObjDesc = ObjEntry->Object;
    if (!ObjDesc)
    {
        /*
         *  The object DNE, this is bad
         */
        return (void *) AE_AML_ERROR;
    }

    if (ObjDesc->Type == TYPE_Device)
    {
        TmpObj = ObjDesc->Device.AddrHandler;
        while (TmpObj)
        {
            /*
             *  This device has an Address handler, see if this is
             *  the same user address space.
             */
            if(TmpObj->AddrHandler.SpaceId == HandlerObj->AddrHandler.SpaceId)
            {
                return GO_NO_FURTHER;
            }
            /*
             *  Move through the linked list of handlers
             */
            TmpObj = TmpObj->AddrHandler.Link;
        }
        return (void *) AE_OK;
    }

    /*
     *  Object is a Region, update the handler overwriting whatever
     *  is there.  First decrement the reference count in the old handler
     */

    EvAssociateRegionAndHander(HandlerObj, ObjDesc);

    return (void *) AE_OK;
}

/******************************************************************************
 *
 * FUNCTION:    EvGetAddressSpaceHandler
 *
 * PARAMETERS:  Parent     - parent NTE
 *              RegionObj  - Region we are searching for
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler for accesses on an Operation Region
 *
 ******************************************************************************/

ACPI_STATUS
EvGetAddressSpaceHandler ( ACPI_OBJECT_INTERNAL *RegionObj)
{
    ACPI_OBJECT_INTERNAL   *HandlerObj;
    UINT32                  SpaceId; 
    NAME_TABLE_ENTRY       *Nte;        /* Namespace Object */


    FUNCTION_TRACE ("EvGetAddressSpaceHandler");


    Nte = RegionObj->Region.Parent;
    SpaceId = RegionObj->Region.SpaceId;
    RegionObj->Region.AddrHandler = NULL;

    while (Nte != Gbl_RootObject)
    {
        /*
         *  Check to see if a handler exists
         */
        switch (Nte->Type)
        {
        case TYPE_Device:

            HandlerObj = ((ACPI_OBJECT_INTERNAL *)Nte->Object)->Device.AddrHandler;
            break;

        case TYPE_Processor:

            HandlerObj = ((ACPI_OBJECT_INTERNAL *)Nte->Object)->Processor.AddrHandler;
            break;

        case TYPE_Thermal:

            HandlerObj = ((ACPI_OBJECT_INTERNAL *)Nte->Object)->ThermalZone.AddrHandler;
            break;

        default:
            HandlerObj = NULL;
            break;
        }


        while (HandlerObj)
        {
            /*
             *  This guy has at least one address handler
             *  see if it has the type we want 
             */
            if (HandlerObj->AddrHandler.SpaceId == SpaceId)
            {
                /*
                 *  Found it!!! Now update the region and the handler
                 */
                EvAssociateRegionAndHander(HandlerObj, RegionObj);
                return_ACPI_STATUS (AE_OK);
            }

            HandlerObj = HandlerObj->AddrHandler.Link;
        } /* while handlerobj */

        /*
         *  This one does not have the handler we need
         *  Pop up one level
         */
        Nte = Nte->ParentEntry;

    } /* while Nte != ROOT */

    /*
     *  If we get here the handler DNE, get out with error
     */
    return_ACPI_STATUS (AE_NOT_EXIST);
}


/******************************************************************************
 *
 * FUNCTION:    EvWalkNamespace
 *
 * PARAMETERS:  Type                - ACPI_OBJECT_TYPE to search for
 *              StartObject         - Handle in namespace where search begins
 *              MaxDepth            - Depth to which search is to reach
 *              UserFunction        - Called when an object of "Type" is found
 *              Context             - Passed to user function
 *
 * RETURNS      Return value from the UserFunction if terminated early.
 *              Otherwise, returns NULL.
 *
 * DESCRIPTION: Identical to the AcpiWalkNamespace except. Checks the return
 *              value from the user function for the special value GO_NO_FURTHER
 *
 *              When that value is encountered the progression down a branch of
 *              tree halts but the search continues in the parent.
 *
 ******************************************************************************/

ACPI_STATUS
EvWalkNamespace (
    ACPI_OBJECT_TYPE        Type, 
    ACPI_HANDLE             StartObject, 
    UINT32                  MaxDepth,
    WALK_CALLBACK           UserFunction, 
    void                    *Context, 
    void                    **ReturnValue)
{
    ACPI_HANDLE             ChildHandle;
    ACPI_HANDLE             ParentHandle;
    ACPI_HANDLE             Dummy;
    UINT32                  Level;
    void                    *UserReturnVal;


    FUNCTION_TRACE ("EvWalkNamespace");

    /* Parameter validation */

    if ((Type > ACPI_TABLE_MAX) ||
        (!MaxDepth)             || 
        (!UserFunction))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Special case for the namespace root object */

    if (StartObject == ACPI_ROOT_OBJECT)
    {
        StartObject = Gbl_RootObject;
    }

    /* Init return value, if any */

    if (ReturnValue)
    {
        *ReturnValue = NULL;
    }

    /* Null child means "get first object" */

    ParentHandle    = StartObject;
    ChildHandle     = 0;
    Level           = 1;

    /* 
     * Traverse the tree of objects until we bubble back up to where we
     * started. When Level is zero, the loop is done because we have 
     * bubbled up to (and passed) the original parent handle (StartHandle)
     */

    while (Level > 0)
    {
        /* Get the next typed object in this scope.  Null returned if not found */

        if (ACPI_SUCCESS (AcpiGetNextObject (Type, ParentHandle, ChildHandle, &ChildHandle))) 
        {
            /* Found an object - process by calling the user function */

            UserReturnVal = UserFunction (ChildHandle, Level, Context);

            if ((UserReturnVal) && (UserReturnVal != GO_NO_FURTHER))
            {
                /* Non-zero from user function means "exit now" */

                if (ReturnValue)
                {
                    /* Pass return value back to the caller */

                    *ReturnValue = UserReturnVal;
                }

                return_ACPI_STATUS (AE_OK);
            }

            /* Go down another level in the namespace if we are allowed to */

            if ((Level < MaxDepth) && (UserReturnVal != GO_NO_FURTHER))
            {
                /* Check if this object has any children */

                if (ACPI_SUCCESS (AcpiGetNextObject (Type, ChildHandle, 0, &Dummy)))
                {
                    /* There is at least one child of this object, visit the object */

                    Level++;
                    ParentHandle    = ChildHandle;
                    ChildHandle     = 0;
                }
            }
        }

        else
        {
            /* 
             * No more children in this object, go back up to the object's parent
             */
            Level--;
            ChildHandle = ParentHandle;
            AcpiGetParent (ParentHandle, &ParentHandle);
        }
    }


    return_ACPI_STATUS (AE_OK);                   /* Complete walk, not terminated by user function */
}



