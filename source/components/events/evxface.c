/******************************************************************************
 * 
 * Module Name: evapi - External interfaces for ACPI events
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
 * Redistribution of source code of any substantial porton of the Covered
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
#include <hardware.h>
#include <namespace.h>
#include <events.h>

#define _THIS_MODULE        "evapi.c"
#define _COMPONENT          EVENT_HANDLING



extern FIXED_EVENT_HANDLER  FixedEventHandlers[NUM_FIXED_EVENTS];



/**************************************************************************
 *
 * FUNCTION:    AcpiEnable
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Ensures that the system
 *              control interrupt (SCI) is properly configured, disables
 *              SCI event sources, installs the SCI handler, and
 *              transfers the system into ACPI mode.
 *
 *************************************************************************/

ACPI_STATUS
AcpiEnable (void)
{
    FUNCTION_TRACE ("AcpiEnable");


    if (!RSDP)
    {
        /*  ACPI tables are not available   */

        DEBUG_PRINT (ACPI_WARN, ("No ACPI tables present!\n"));
        return_ACPI_STATUS (AE_NO_ACPI_TABLES);
    }

    /*  ACPI tables are available or not required */

    if (SYS_MODE_LEGACY == HwGetModeCapabilities ())
    {   
        /*
         * No ACPI mode support provided by BIOS
         */

        /* TBD: verify input file specified */

        DEBUG_PRINT (ACPI_WARN, ("Only legacy mode supported!\n"));
        return_ACPI_STATUS (AE_ERROR);
    }

    OriginalMode = HwGetMode();

    if (EvInstallSciHandler () != AE_OK)
    {   
        /* Unable to install SCI handler */

        DEBUG_PRINT (ACPI_FATAL, ("Unable to install System Control Interrupt Handler"));
        return_ACPI_STATUS (AE_ERROR);
    }
    
    /*  SCI Interrupt Handler installed properly    */

    if (SYS_MODE_ACPI != OriginalMode)
    {   
        /*  legacy mode */
                
        if (AE_OK != HwSetMode (SYS_MODE_ACPI))
        {   
            /*  Unable to transition to ACPI Mode   */

            DEBUG_PRINT (ACPI_FATAL, ("Could not transition to ACPI mode.\n"));
            return_ACPI_STATUS (AE_ERROR);    
        }
        else
        {
            DEBUG_PRINT (ACPI_OK, ("Transition to ACPI mode successful\n"));
        }
        
        /* Initialize GPEs now. */
        
        if (EvGpeInitialize () != AE_OK)
        {
            /* Unable to initialize GPEs. */
        
            DEBUG_PRINT (ACPI_FATAL, ("Unable to initialize general purpose events.\n"));
            return_ACPI_STATUS (AE_ERROR);
        }
    
        EvInitGpeControlMethods ();

    }

    return_ACPI_STATUS (AE_OK);
}
    

/**************************************************************************
 *
 * FUNCTION:    AcpiDisable
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Returns the system to original ACPI/legacy mode, and 
 *              uninstalls the SCI interrupt handler.
 *
 *************************************************************************/

ACPI_STATUS     
AcpiDisable (void)
{
    UINT32                  Status;


    FUNCTION_TRACE ("AcpiDisable");


    /* Restore original mode  */

    if (AE_OK != HwSetMode (OriginalMode))
    {
        DEBUG_PRINT (ACPI_ERROR, ("Unable to transition to original mode"));
        Status = AE_ERROR;    
    }

    else
    {
        /* Unload the SCI interrupt handler  */

        EvRemoveSciHandler ();
        EvRestoreAcpiState ();
        
        Status = AE_OK;
        
    }

    return_ACPI_STATUS (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiInstallFixedEventHandler
 *
 * PARAMETERS:  Event           - Event type to enable.
 *              Handler         - Pointer to the handler function for the
 *                                event
 *              Context         - Value passed to the handler on each GPE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Saves the pointer to the handler function and then enables the
 *              event.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiInstallFixedEventHandler (
    UINT32                  Event,
    FIXED_EVENT_HANDLER     Handler,
    void                    *Context)
{
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("AcpiInstallFixedEventHandler");


    /* Sanity check the parameters. */

    if (Event >= NUM_FIXED_EVENTS)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }
    
    CmAcquireMutex (MTX_FIXED_EVENT);

    /* Don't allow two handlers. */

    if (NULL != FixedEventHandlers[Event])
    {
        Status = AE_EXIST;
        goto Cleanup;
    }
    
    /* Install the handler before enabling the event - just in case... */

    FixedEventHandlers[Event] = Handler;
    
    if (1 != HwRegisterIO (ACPI_WRITE, Event + TMR_EN, 1))
    {
        DEBUG_PRINT (ACPI_WARN, ("Could not write to fixed event enable register.\n"));
        FixedEventHandlers[Event] = NULL;
        Status = AE_ERROR;
        goto Cleanup;
    }

    DEBUG_PRINT (ACPI_INFO, ("Enabled fixed event %d.  Handler: %x\n", Event, Handler));    

Cleanup:
    CmReleaseMutex (MTX_FIXED_EVENT);
    return_ACPI_STATUS (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRemoveFixedEventHandler
 *
 * PARAMETERS:  Event           - Event type to disable.
 *              Handler         - Address of the handler
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Disables the event and unregisters the event handler.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRemoveFixedEventHandler (
    UINT32                  Event,
    FIXED_EVENT_HANDLER     Handler)
{
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("AcpiRemoveFixedEventHandler");


    /* Sanity check the parameters. */

    if (Event >= NUM_FIXED_EVENTS)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }
    
    CmAcquireMutex (MTX_FIXED_EVENT);

    /* Disable the event before removing the handler - just in case... */

    if (0 != HwRegisterIO (ACPI_WRITE, Event + TMR_EN, 0))
    {
        DEBUG_PRINT (ACPI_WARN, ("Could not write to fixed event enable register.\n"));
        Status = AE_ERROR;
        goto Cleanup;
    }

    /* Remove the handler */

    FixedEventHandlers[Event] = NULL;    
    DEBUG_PRINT (ACPI_INFO, ("Disabled fixed event %d.\n", Event));    
    
Cleanup:
    CmReleaseMutex (MTX_FIXED_EVENT);
    return_ACPI_STATUS (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiInstallGpeHandler
 *
 * PARAMETERS:  GpeNumber       - The GPE number.  The numbering scheme is 
 *                                bank 0 first, then bank 1.
 *              Handler         - Address of the handler
 *              Context         - Value passed to the handler on each GPE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler for a General Purpose Event.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiInstallGpeHandler (
    UINT32                  GpeNumber, 
    GPE_HANDLER             Handler, 
    void                    *Context)
{
    ACPI_STATUS             Status = AE_OK;

    
    FUNCTION_TRACE ("AcpiInstallGpeHandler");


    /* Parameter validation */

    if (!Handler || (GpeNumber >= GpeRegisterCount))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    CmAcquireMutex (MTX_GP_EVENT);

    /* Make sure that there isn't a handler there already */

    if (GpeInfo[GpeNumber].Handler)
    {
        Status = AE_EXIST;
        goto Cleanup;
    }


    /* Install the handler */

    GpeInfo[GpeNumber].Handler = Handler;
    GpeInfo[GpeNumber].Context = Context;


    /* Now we can enable the GPE */

    HwEnableGpe (GpeNumber);

Cleanup:
    CmReleaseMutex (MTX_GP_EVENT);
    return_ACPI_STATUS (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiRemoveGpeHandler
 *
 * PARAMETERS:  GpeNumber       - The event to remove a handler
 *              Handler         - Address of the handler
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a handler for a General Purpose Event.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRemoveGpeHandler (
    UINT32                  GpeNumber, 
    GPE_HANDLER             Handler)
{
    ACPI_STATUS             Status = AE_OK;

    
    FUNCTION_TRACE ("AcpiRemoveGpeHandler");


    /* Parameter validation */

    if (!Handler || (GpeNumber >= GpeRegisterCount))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    CmAcquireMutex (MTX_GP_EVENT);

    /* Make sure that the installed handler is the same */

    if (GpeInfo[GpeNumber].Handler != Handler)
    {
        Status = AE_BAD_PARAMETER;
        goto Cleanup;
    }


    /* Disable the GPE before removing the handler */

    HwDisableGpe (GpeNumber);


    /* Remove the handler */

    GpeInfo[GpeNumber].Handler = NULL;
    GpeInfo[GpeNumber].Context = NULL;

 
Cleanup:
    CmReleaseMutex (MTX_GP_EVENT);
    return_ACPI_STATUS (Status);
}

/******************************************************************************
 *
 * FUNCTION:    AcpiInstallNotifyHandler
 *
 * PARAMETERS:  Device          - The device for which notifies will be handled
 *              Handler         - Address of the handler
 *              Context         - Value passed to the handler on each GPE
 *              Type            -   0: SystemHandler (00-7f)
 *                                  1: DriverHandler (80-ff)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler for notifies on an ACPI device
 *
 ******************************************************************************/

ACPI_STATUS
AcpiInstallNotifyHandler (
    ACPI_HANDLE             Device, 
    NOTIFY_HANDLER          Handler, 
    void                    *Context,
    UINT32                  Type)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *NotifyObj;
    NAME_TABLE_ENTRY        *ObjEntry;
    ACPI_STATUS             Status;

    FUNCTION_TRACE ("AcpiInstallNotifyHandler");

    /* Parameter validation */

    if (!Handler)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Convert and validate the device handle */

    if (!(ObjEntry = NsConvertHandleToEntry (Device)))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /*
     * These are the ONLY objects that can receive ACPI notifications
     */

    if ((ObjEntry->Type != TYPE_Device)     &&
        (ObjEntry->Type != TYPE_Processor)  &&
        (ObjEntry->Type != TYPE_Power)      &&
        (ObjEntry->Type != TYPE_Thermal))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Check for an existing internal object */

    ObjDesc = ObjEntry->Object;

    if (ObjDesc)
    {
        /*
         *  The object exists.
         *
         *  Make sure the handler is not already installed.
         */

        if (((Type = 0) && ObjDesc->Device.SysHandler) ||
            ((Type = 1) && ObjDesc->Device.DrvHandler))
        {
            return_ACPI_STATUS (AE_EXIST);
        }
    }
    else
    {
        /* ObjDesc DNE: We must create one */

        ObjDesc = CmCreateInternalObject (ObjEntry->Type);
        if (!ObjDesc)
        {
            /* Descriptor allocation failure   */

            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        /* Attach the new object to the NTE */

        Status = NsAttachObject (Device, ObjDesc, (UINT8) ObjEntry->Type);

        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    /* 
     *  We get here, we know that there is no handler installed
     *  so let's party
     */

    NotifyObj = CmCreateInternalObject (TYPE_Notfy);
    if (!NotifyObj)
    {
        /* Descriptor allocation failure   */

        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* TBD: Mutex?? */

    NotifyObj->NotifyHandler.Nte = ObjEntry;
    NotifyObj->NotifyHandler.Handler = Handler;
    NotifyObj->NotifyHandler.Context = Context;

    /*
     *  Have a new reference for the device
     */
    CmUpdateObjectReference (ObjDesc, REF_INCREMENT);

    if (Type = 0)
    {
        ObjDesc->Device.SysHandler = NotifyObj;
    }
    else
    {
        ObjDesc->Device.DrvHandler = NotifyObj;
    }

    return_ACPI_STATUS (AE_OK);
}

#define GO_NO_FURTHER   (void *) 0xffffffff

/******************************************************************************
 *
 * FUNCTION:    AdrWalkNamespace
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
AdrWalkNamespace (
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


    FUNCTION_TRACE ("AdrWalkNamespace");

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
        StartObject = RootObject;
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

/*****************************************************************************
 *
 * FUNCTION:    AcpiRemoveNotifyHandler
 *
 * PARAMETERS:  Device          - The device for which notifies will be handled
 *              Handler         - Address of the handler
 *              Type            -   0: SystemHandler (00-7f)
 *                                  1: DriverHandler (80-ff)
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a handler for notifies on an ACPI device
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRemoveNotifyHandler (
    ACPI_HANDLE             Device, 
    NOTIFY_HANDLER          Handler,
    UINT32                  Type)
{
    ACPI_OBJECT_INTERNAL    *NotifyObj;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    NAME_TABLE_ENTRY        *ObjEntry;

    FUNCTION_TRACE ("AcpiRemoveNotifyHandler");

    /* Parameter validation */

    if (!Handler)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Convert and validate the device handle */

    if (!(ObjEntry = NsConvertHandleToEntry (Device)))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /*
     * These are the ONLY objects that can receive ACPI notifications
     */

    if ((ObjEntry->Type != TYPE_Device)     &&
        (ObjEntry->Type != TYPE_Processor)  &&
        (ObjEntry->Type != TYPE_Power)      &&
        (ObjEntry->Type != TYPE_Thermal))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Check for an existing internal object */

    if (!ObjEntry->Object)
    {
        return_ACPI_STATUS (AE_NOT_EXIST);
        
    }

    ObjDesc = ObjEntry->Object;

    /*
     *  The object exists.
     *
     *  Make sure the handler is installed.
     */

    if (Type = 0)
    {
        NotifyObj = ObjDesc->Device.SysHandler;
    }
    else
    {
        NotifyObj = ObjDesc->Device.DrvHandler;
    }

    if ((!NotifyObj) ||
        (NotifyObj->NotifyHandler.Handler != Handler))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* 
     * Now we can remove the handler
     */

    /* TBD: Mutex?? */
    if (Type = 0)
    {
        ObjDesc->Device.SysHandler = NULL;
    }
    else
    {
        ObjDesc->Device.DrvHandler = NULL;
    }

    CmDeleteInternalObject(NotifyObj);

    /*
     *  Remove handler reference in the device
     */
    CmUpdateObjectReference (ObjDesc, REF_DECREMENT);

    return_ACPI_STATUS (AE_OK);
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
 * FUNCTION:    InsAddrHandlerHelper   
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
InsAddrHandlerHelper (
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
 * FUNCTION:    AcpiInstallAddressSpaceHandler
 *
 * PARAMETERS:  Device          - Handle for the device 
 *              SpaceId         - The address space ID
 *              Handler         - Address of the handler
 *              Context         - Value passed to the handler on each access
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler for accesses on an address space controlled
 *              a specific device.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiInstallAddressSpaceHandler (
    ACPI_HANDLE             Device, 
    UINT32                  SpaceId, 
    ADDRESS_SPACE_HANDLER   Handler, 
    void                    *Context)
{
    ACPI_OBJECT_INTERNAL   *ObjDesc;
    ACPI_OBJECT_INTERNAL   *HandlerObj;
    NAME_TABLE_ENTRY       *ObjEntry;
    ACPI_STATUS             Status;

    FUNCTION_TRACE ("AcpiInstallAddressSpaceHandler");

    /* Parameter validation */

    if ((!Device)   ||
        (!Handler)  ||
        (SpaceId > ACPI_MAX_ADDRESS_SPACE))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Convert and validate the device handle */

    if (!(ObjEntry = NsConvertHandleToEntry (Device)))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /*
     *  This registration is valid for only the types below
     *  and the root.  This is where the default handlers
     *  get placed.
     */

    if ((ObjEntry->Type != TYPE_Device)     &&
        (ObjEntry->Type != TYPE_Processor)  &&
        (ObjEntry->Type != TYPE_Thermal)    &&
        (ObjEntry != RootObject))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Check for an existing internal object */

    ObjDesc = ObjEntry->Object;

    if (ObjDesc)
    {
        /*
         *  The object exists.
         *
         *  Make sure the handler is not already installed.
         */

        /* check the address handler the user requested */

        HandlerObj = ObjDesc->Device.AddrHandler;
        while (HandlerObj)
        {
            /*
             *  We have an Address handler, see if user request this
             *  address space.
             */
            if(HandlerObj->AddrHandler.SpaceId == SpaceId)
            {
                return_ACPI_STATUS (AE_EXIST);
            }
            /*
             *  Move through the linked list of handlers
             */
            HandlerObj = HandlerObj->AddrHandler.Link;
        }
    }
    else
    {
        /* ObjDesc DNE: We must create one */

        ObjDesc = CmCreateInternalObject (ObjEntry->Type);
        if (!ObjDesc)
        {
            /* Descriptor allocation failure   */

            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        /* Attach the new object to the NTE */

        Status = NsAttachObject (Device, ObjDesc, (UINT8) ObjEntry->Type);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    /* 
     *  Now we can install the handler
     *
     *  At this point we know that the handler we are installing DNE. 
     *  So, we just allocate the object for the handler and link it
     *  into the list.
     */

    HandlerObj = CmCreateInternalObject (TYPE_AddrHandler);
    if (!HandlerObj)
    {
        /* Descriptor allocation failure   */
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    HandlerObj->AddrHandler.SpaceId = SpaceId;
    HandlerObj->AddrHandler.Link = ObjDesc->Device.AddrHandler;
    HandlerObj->AddrHandler.RegionList = NULL;
    HandlerObj->AddrHandler.Nte = ObjEntry;
    HandlerObj->AddrHandler.Handler = Handler;
    HandlerObj->AddrHandler.Context = Context;


    /*
     *  Now walk the namespace finding all of the regions this
     *  handler will manage.
     *
     *  We start at the device and search the branch until toward
     *  the leaf nodes until either the leaf is encountered or
     *  a device is detected that has an address handler of the
     *  same type.
     *
     *  In either case we back up and search down the remainder
     *  of the branch
     */
    Status = AdrWalkNamespace ( TYPE_Any, Device, 100,
                    InsAddrHandlerHelper, HandlerObj, NULL);

    /*
     *  Place this handler 1st on the list
     */
    CmUpdateObjectReference (ObjDesc, REF_INCREMENT);
    ObjDesc->Device.AddrHandler = HandlerObj;

    return_ACPI_STATUS (AE_OK);

}  /* AcpiInstallAddressSpaceHandler */


/******************************************************************************
 *
 * FUNCTION:    AcpiRemoveAddressSpaceHandler
 *
 * PARAMETERS:  SpaceId         - The address space ID
 *              Handler         - Address of the handler
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler for accesses on an Operation Region
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRemoveAddressSpaceHandler (
    ACPI_HANDLE             Device, 
    UINT32                  SpaceId, 
    ADDRESS_SPACE_HANDLER   Handler)
{
    ACPI_OBJECT_INTERNAL   *ObjDesc;
    ACPI_OBJECT_INTERNAL   *HandlerObj;
    ACPI_OBJECT_INTERNAL   *RegionObj;
    ACPI_OBJECT_INTERNAL   **LastObjPtr;
    NAME_TABLE_ENTRY       *ObjEntry;

    FUNCTION_TRACE ("AcpiRemoveAddressSpaceHandler");

    /* Parameter validation */

    if ((!Device)   ||
        (!Handler)  ||
        (SpaceId > ACPI_MAX_ADDRESS_SPACE))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Convert and validate the device handle */

    if (!(ObjEntry = NsConvertHandleToEntry (Device)))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* TBD: Mutex */

    /* Make sure the internal object exists */

    ObjDesc = ObjEntry->Object;

    if (!ObjDesc)
    {
        /*
         *  The object DNE.
         */
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    /*
     *  find the address handler the user requested
     */

    HandlerObj = ObjDesc->Device.AddrHandler;
    LastObjPtr = &ObjDesc->Device.AddrHandler;
    while (HandlerObj)
    {
        /*
         *  We have a handler, see if user requested this one
         */

        if(HandlerObj->AddrHandler.SpaceId == SpaceId)
        {
            /*
             *  Got it, first dereference this in the Regions
             */
            RegionObj = HandlerObj->AddrHandler.RegionList;

            while (RegionObj)
            {
                /*
                 *  First disassociate the handler from the region.
                 *
                 *  NOTE: this doesn't mean that the region goes away
                 *  The region is just inaccessible as indicated to
                 *  the _REG method
                 */
                EvDisassociateRegionAndHandler(HandlerObj, RegionObj);

                /*
                 *  Walk the list, since we took the first region and it
                 *  was removed from the list by the dissassociate call
                 *  we just get the first item on the list again
                 */
                RegionObj = HandlerObj->AddrHandler.RegionList;
            } /* walk the handler's region list */

            /*
             *  Remove this Handler object from the list
             */
            *LastObjPtr = HandlerObj->AddrHandler.Link;

            /*
             *  Now we can actually delete the object
             */
            CmDeleteInternalObject(HandlerObj);

            /*
             *  Remove handler reference in the device
             */
            CmUpdateObjectReference (ObjDesc, REF_DECREMENT);

            return_ACPI_STATUS (AE_OK);
        } /* found the right handler */

        /*
         *  Move through the linked list of handlers
         */
        LastObjPtr = &HandlerObj->AddrHandler.Link;
        HandlerObj = HandlerObj->AddrHandler.Link;
    }

    /*
     *  If we get here the handler DNE, get out with error
     */
    return_ACPI_STATUS (AE_NOT_EXIST);
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

    while (Nte != RootObject)
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
