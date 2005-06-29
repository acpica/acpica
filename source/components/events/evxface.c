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
 * Redistribution of source code of any substantial prton of the Covered
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
#include <namesp.h>
#include <events.h>
#include <amlcode.h>
#include <interp.h>

#define _COMPONENT          EVENT_HANDLING
        MODULE_NAME         ("evapi");


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
    UINT32                  i;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AcpiEnable");


    if (!Gbl_RSDP)
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

    Gbl_OriginalMode = HwGetMode ();

    if (EvInstallSciHandler () != AE_OK)
    {   
        /* Unable to install SCI handler */

        DEBUG_PRINT (ACPI_FATAL, ("Unable to install System Control Interrupt Handler\n"));
        return_ACPI_STATUS (AE_ERROR);
    }
    
    /*  SCI Interrupt Handler installed properly    */

    if (SYS_MODE_ACPI != Gbl_OriginalMode)
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
        
        /* Initialize the structure that keeps track of fixed event handler. */

        for (i = 0; i < NUM_FIXED_EVENTS; i++)
        {
        	Gbl_FixedEventHandlers[i].Handler = NULL;
        	Gbl_FixedEventHandlers[i].Context = NULL;
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


    Status = EvInitGlobalLockHandler ();

    return_ACPI_STATUS (Status);
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

    if (AE_OK != HwSetMode (Gbl_OriginalMode))
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

    if (NULL != Gbl_FixedEventHandlers[Event].Handler)
    {
        Status = AE_EXIST;
        goto Cleanup;
    }
    

    /* Install the handler before enabling the event - just in case... */

    Gbl_FixedEventHandlers[Event].Handler = Handler;
    Gbl_FixedEventHandlers[Event].Context = Context;
    
    if (1 != HwRegisterIO (ACPI_WRITE, Event + TMR_EN, 1))
    {
        DEBUG_PRINT (ACPI_WARN, ("Could not write to fixed event enable register.\n"));
        
        /* Remove the handler */

        Gbl_FixedEventHandlers[Event].Handler = NULL;
        Gbl_FixedEventHandlers[Event].Context = NULL;

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

    Gbl_FixedEventHandlers[Event].Handler = NULL;
    Gbl_FixedEventHandlers[Event].Context = NULL;
    
    DEBUG_PRINT (ACPI_INFO, ("Disabled fixed event %d.\n", Event));    
    

Cleanup:
    CmReleaseMutex (MTX_FIXED_EVENT);
    return_ACPI_STATUS (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiInstallNotifyHandler
 *
 * PARAMETERS:  Device          - The device for which notifies will be handled
 *              HandlerType     - The type of handler:
 *                                  ACPI_SYSTEM_NOTIFY: SystemHandler (00-7f)
 *                                  ACPI_DEVICE_NOTIFY: DriverHandler (80-ff)
 *              Handler         - Address of the handler
 *              Context         - Value passed to the handler on each GPE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler for notifies on an ACPI device
 *
 ******************************************************************************/

ACPI_STATUS
AcpiInstallNotifyHandler (
    ACPI_HANDLE             Device,
    UINT32                  HandlerType, 
    NOTIFY_HANDLER          Handler, 
    void                    *Context)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *NotifyObj;
    NAME_TABLE_ENTRY        *ObjEntry;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AcpiInstallNotifyHandler");


    /* Parameter validation */

    if ((!Handler) ||
        (HandlerType > ACPI_MAX_NOTIFY_HANDLER_TYPE))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Convert and validate the device handle */


    ObjEntry = NsConvertHandleToEntry (Device);
    if (!ObjEntry)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /*
     * Support for global notify handlers.  These handlers are invoked for
     * every notifiy of the type specifiec
     */

    if (Device == ACPI_ROOT_OBJECT)
    {
        /*
         *  Make sure the handler is not already installed.
         */

        if (((HandlerType == ACPI_SYSTEM_NOTIFY) && Gbl_SysNotify.Handler) ||
            ((HandlerType == ACPI_DEVICE_NOTIFY) && Gbl_DrvNotify.Handler))
        {
            return_ACPI_STATUS (AE_EXIST);
        }

        if (HandlerType == ACPI_SYSTEM_NOTIFY)
        {
            Gbl_SysNotify.Nte = ObjEntry;
            Gbl_SysNotify.Handler = Handler;
            Gbl_SysNotify.Context = Context;
        }

        else
        {
            Gbl_DrvNotify.Nte = ObjEntry;
            Gbl_DrvNotify.Handler = Handler;
            Gbl_DrvNotify.Context = Context;
        }


        /* Global notify handler installed */

        return_ACPI_STATUS (AE_OK);
    }


    /*
     * These are the ONLY objects that can receive ACPI notifications
     */

    if ((ObjEntry->Type != ACPI_TYPE_Device)     &&
        (ObjEntry->Type != ACPI_TYPE_Processor)  &&
        (ObjEntry->Type != ACPI_TYPE_Power)      &&
        (ObjEntry->Type != ACPI_TYPE_Thermal))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Check for an existing internal object */

    ObjDesc = NsGetAttachedObject ((ACPI_HANDLE) ObjEntry);
    if (ObjDesc)
    {
        /*
         *  The object exists.
         *
         *  Make sure the handler is not already installed.
         */

        if (((HandlerType == ACPI_SYSTEM_NOTIFY) && ObjDesc->Device.SysHandler) ||
            ((HandlerType == ACPI_DEVICE_NOTIFY) && ObjDesc->Device.DrvHandler))
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

    NotifyObj = CmCreateInternalObject (INTERNAL_TYPE_Notify);
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
/* TBRM
    CmUpdateObjectReference (ObjDesc, REF_INCREMENT);
*/
    if (HandlerType == ACPI_SYSTEM_NOTIFY)
    {
        ObjDesc->Device.SysHandler = NotifyObj;
    }

    else
    {
        ObjDesc->Device.DrvHandler = NotifyObj;
    }

    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiRemoveNotifyHandler
 *
 * PARAMETERS:  Device          - The device for which notifies will be handled
 *              HandlerType     - The type of handler:
 *                                  ACPI_SYSTEM_NOTIFY: SystemHandler (00-7f)
 *                                  ACPI_DEVICE_NOTIFY: DriverHandler (80-ff)
 *              Handler         - Address of the handler
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a handler for notifies on an ACPI device
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRemoveNotifyHandler (
    ACPI_HANDLE             Device,
    UINT32                  HandlerType, 
    NOTIFY_HANDLER          Handler)
{
    ACPI_OBJECT_INTERNAL    *NotifyObj;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    NAME_TABLE_ENTRY        *ObjEntry;


    FUNCTION_TRACE ("AcpiRemoveNotifyHandler");


    /* Parameter validation */

    if ((!Handler) ||
        (HandlerType > ACPI_MAX_NOTIFY_HANDLER_TYPE))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Convert and validate the device handle */

    ObjEntry = NsConvertHandleToEntry (Device);
    if (!ObjEntry)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /*
     * These are the ONLY objects that can receive ACPI notifications
     */

    if ((ObjEntry->Type != ACPI_TYPE_Device)     &&
        (ObjEntry->Type != ACPI_TYPE_Processor)  &&
        (ObjEntry->Type != ACPI_TYPE_Power)      &&
        (ObjEntry->Type != ACPI_TYPE_Thermal))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Check for an existing internal object */

    ObjDesc = NsGetAttachedObject ((ACPI_HANDLE) ObjEntry);
    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    /*
     *  The object exists.
     *
     *  Make sure the handler is installed.
     */

    if (HandlerType == ACPI_SYSTEM_NOTIFY)
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

    if (HandlerType == ACPI_SYSTEM_NOTIFY)
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
/* TBRM
    CmUpdateObjectReference (ObjDesc, REF_DECREMENT);
*/

    return_ACPI_STATUS (AE_OK);
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
    ACPI_ADDRESS_SPACE_TYPE SpaceId, 
    ADDRESS_SPACE_HANDLER   Handler, 
    void                    *Context)
{
    ACPI_OBJECT_INTERNAL   *ObjDesc;
    ACPI_OBJECT_INTERNAL   *HandlerObj;
    NAME_TABLE_ENTRY       *ObjEntry;
    ACPI_STATUS             Status;
    ACPI_OBJECT_TYPE        Type;
    UINT16                  Flags = 0;


    FUNCTION_TRACE ("AcpiInstallAddressSpaceHandler");


    /* Parameter validation */

    if ((!Device)   ||
        ((!Handler)  && (Handler != ACPI_DEFAULT_HANDLER)) ||
        (SpaceId > ACPI_MAX_ADDRESS_SPACE))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Convert and validate the device handle */

    ObjEntry = NsConvertHandleToEntry (Device);
    if (!ObjEntry)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /*
     *  This registration is valid for only the types below
     *  and the root.  This is where the default handlers
     *  get placed.
     */

    if ((ObjEntry->Type != ACPI_TYPE_Device)     &&
        (ObjEntry->Type != ACPI_TYPE_Processor)  &&
        (ObjEntry->Type != ACPI_TYPE_Thermal)    &&
        (ObjEntry != Gbl_RootObject))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    if (Handler == ACPI_DEFAULT_HANDLER)
    {
        Flags = AH_DEFAULT_HANDLER;

        switch (SpaceId)
        {
        case ADDRESS_SPACE_SYSTEM_MEMORY:
            Handler = AmlSystemMemorySpaceHandler;
            break;

        case ADDRESS_SPACE_SYSTEM_IO:
            Handler = AmlSystemIoSpaceHandler;
            break;

        case ADDRESS_SPACE_PCI_CONFIG:
            Handler = AmlPciConfigSpaceHandler;
            break;

        default:
            return_ACPI_STATUS (AE_NOT_EXIST);
        }
    }

    /* Check for an existing internal object */

    ObjDesc = NsGetAttachedObject ((ACPI_HANDLE) ObjEntry);
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
             *  We have an Address handler, see if user requested this
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
        DEBUG_PRINT (TRACE_OPREGION, ("Creating object on Device 0x%X while installing handler\n", 
                        ObjEntry));

        /* ObjDesc does not exist, create one */

        if (ObjEntry->Type == ACPI_TYPE_Any)
        {
            Type = ACPI_TYPE_Device;
        }

        else
        {
            Type = ObjEntry->Type;
        }

        ObjDesc = CmCreateInternalObject (Type);
        if (!ObjDesc)
        {
            /* Descriptor allocation failure   */

            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        /* Init new descriptor */

        ObjDesc->Common.Type = (UINT8) Type;

        /* Attach the new object to the NTE */

        Status = NsAttachObject (Device, ObjDesc, (UINT8) Type);
        if (ACPI_FAILURE (Status))
        {
            CmDeleteInternalObject (ObjDesc);
            return_ACPI_STATUS (Status);
        }

        /* TBD: Will this always be of type DEVICE? */

        if (Type == ACPI_TYPE_Device)
        {
            ObjDesc->Device.Handle = Device;
        }
    }

    DEBUG_PRINT (TRACE_OPREGION, ("Installing address handler for %s on Device 0x%X (0x%X)\n", 
                    Gbl_RegionTypes[SpaceId], ObjEntry, ObjDesc));

    /* 
     *  Now we can install the handler
     *
     *  At this point we know that the handler we are installing DNE. 
     *  So, we just allocate the object for the handler and link it
     *  into the list.
     */

    HandlerObj = CmCreateInternalObject (INTERNAL_TYPE_AddressHandler);
    if (!HandlerObj)
    {
        /* Descriptor allocation failure   */
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    HandlerObj->AddrHandler.SpaceId     = (UINT16) SpaceId;
    HandlerObj->AddrHandler.Hflags      = Flags;
    HandlerObj->AddrHandler.Link        = ObjDesc->Device.AddrHandler;
    HandlerObj->AddrHandler.RegionList  = NULL;
    HandlerObj->AddrHandler.Nte         = ObjEntry;
    HandlerObj->AddrHandler.Handler     = Handler;
    HandlerObj->AddrHandler.Context     = Context;


    /*
     *  Now walk the namespace finding all of the regions this
     *  handler will manage.
     *
     *  We start at the device and search the branch toward
     *  the leaf nodes until either the leaf is encountered or
     *  a device is detected that has an address handler of the
     *  same type.
     *
     *  In either case we back up and search down the remainder
     *  of the branch
     */
    Status = AcpiWalkNamespace (ACPI_TYPE_Any, Device, ACPI_INT32_MAX, EvAddrHandlerHelper, 
                                HandlerObj, NULL);

    /*
     *  Place this handler 1st on the list
     */
/* TBRM
    HandlerObj->Common.ReferenceCount = ObjDesc->Common.ReferenceCount;
    
    CmUpdateObjectReference (HandlerObj, REF_INCREMENT);

*/

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
    ACPI_ADDRESS_SPACE_TYPE SpaceId, 
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
        ((!Handler)  && (Handler != ACPI_DEFAULT_HANDLER)) ||
        (SpaceId > ACPI_MAX_ADDRESS_SPACE))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Convert and validate the device handle */

    ObjEntry = NsConvertHandleToEntry (Device);
    if (!ObjEntry)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /* Make sure the internal object exists */

    ObjDesc = NsGetAttachedObject ((ACPI_HANDLE) ObjEntry);
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
            DEBUG_PRINT (TRACE_OPREGION,
                ("Removing address handler 0x%X (0x%X) for %s on Device 0x%X (0x%X)\n", 
                    HandlerObj, Handler, Gbl_RegionTypes[SpaceId], ObjEntry, ObjDesc));

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
                EvDisassociateRegionFromHandler(RegionObj);

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
            CmDeleteInternalObject (HandlerObj);

            /*
             *  Remove handler reference in the device
             */
/* TBRM
            CmUpdateObjectReference (ObjDesc, REF_DECREMENT);
*/
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
    DEBUG_PRINT (TRACE_OPREGION,
        ("Unable to remove address handler xxxx (0x%X) for %s on Device 0x%X (0x%X)\n", 
        Handler, Gbl_RegionTypes[SpaceId], ObjEntry, ObjDesc));

    return_ACPI_STATUS (AE_NOT_EXIST);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiInstallGpeHandler
 *
 * PARAMETERS:  GpeNumber       - The GPE number.  The numbering scheme is 
 *                                bank 0 first, then bank 1.
 *              Trigger         - Whether this GPE should be treated as an
 *                                edge- or level-triggered interrupt.
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
    UINT32                  Type,
    GPE_HANDLER             Handler,
    void                    *Context)
{
    ACPI_STATUS             Status = AE_OK;
    
    FUNCTION_TRACE ("AcpiInstallGpeHandler");

    /* Parameter validation */

    if (!Handler || (GpeNumber > NUM_GPE) || (Type != EVENT_LEVEL_TRIGGERED && Type != EVENT_EDGE_TRIGGERED))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Ensure that we have a valid GPE number */

    if (Gbl_GpeValid[GpeNumber] == GPE_INVALID)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    CmAcquireMutex (MTX_GP_EVENT);

    /* Make sure that there isn't a handler there already */

    if (Gbl_GpeInfo[GpeNumber].Handler)
    {
        Status = AE_EXIST;
        goto Cleanup;
    }

    /* Install the handler */

    Gbl_GpeInfo[GpeNumber].Handler = Handler;
    Gbl_GpeInfo[GpeNumber].Context = Context;
    Gbl_GpeInfo[GpeNumber].Type = (UINT8) Type;

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

    if (!Handler || (GpeNumber > NUM_GPE))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Ensure that we have a valid GPE number */

    if (Gbl_GpeValid[GpeNumber] == GPE_INVALID)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    CmAcquireMutex (MTX_GP_EVENT);

    /* Make sure that the installed handler is the same */

    if (Gbl_GpeInfo[GpeNumber].Handler != Handler)
    {
        Status = AE_BAD_PARAMETER;
        goto Cleanup;
    }


    /* Disable the GPE before removing the handler */

    HwDisableGpe (GpeNumber);


    /* Remove the handler */

    Gbl_GpeInfo[GpeNumber].Handler = NULL;
    Gbl_GpeInfo[GpeNumber].Context = NULL;

 
Cleanup:
    CmReleaseMutex (MTX_GP_EVENT);
    return_ACPI_STATUS (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiEnableEvent
 *
 * PARAMETERS:  Event           - The fixed event or GPE to be enabled
 *              Type            - The type of event
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enable an ACPI event (fixed and general purpose)
 *
 ******************************************************************************/

ACPI_STATUS
AcpiEnableEvent (
    UINT32                  Event,
    UINT32                  Type)
{
    ACPI_STATUS             Status = AE_OK;

    FUNCTION_TRACE ("AcpiEnableEvent");

    switch (Type)
    {
    case EVENT_FIXED:
        /*
         * TBD - Fixed events...
         */
        Status = AE_NOT_IMPLEMENTED;
        break;

    case EVENT_GPE:

        /* Ensure that we have a valid GPE number */

        if (Gbl_GpeValid[Event] == GPE_INVALID)
        {
            Status = AE_BAD_PARAMETER;
        }
        else
        {
            HwEnableGpe (Event);
        }

        break;

    default:
        Status = AE_BAD_PARAMETER;
    }

    return_ACPI_STATUS (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDisableEvent
 *
 * PARAMETERS:  Event           - The fixed event or GPE to be enabled
 *              Type            - The type of event
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Disable an ACPI event (fixed and general purpose)
 *
 ******************************************************************************/

ACPI_STATUS
AcpiDisableEvent (
    UINT32                  Event,
    UINT32                  Type)
{
    ACPI_STATUS             Status = AE_OK;

    FUNCTION_TRACE ("AcpiDisableEvent");

    switch (Type)
    {
    case EVENT_FIXED:
        /*
         * TBD - Fixed events...
         */
        Status = AE_NOT_IMPLEMENTED;
        break;

    case EVENT_GPE:

        /* Ensure that we have a valid GPE number */

        if (Gbl_GpeValid[Event] == GPE_INVALID)
        {
            Status = AE_BAD_PARAMETER;
        }
        else
        {
            HwDisableGpe (Event);
        }

        break;

    default:
        Status = AE_BAD_PARAMETER;
    }

    return_ACPI_STATUS (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiClearEvent
 *
 * PARAMETERS:  Event           - The fixed event or GPE to be enabled
 *              Type            - The type of event
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Clear an ACPI event (fixed and general purpose)
 *
 ******************************************************************************/

ACPI_STATUS
AcpiClearEvent (
    UINT32                  Event,
    UINT32                  Type)
{
    ACPI_STATUS             Status = AE_OK;

    FUNCTION_TRACE ("AcpiClearEvent");

    switch (Type)
    {
    case EVENT_FIXED:
        /*
         * TBD - Fixed events...
         */
        Status = AE_NOT_IMPLEMENTED;
        break;

    case EVENT_GPE:

        /* Ensure that we have a valid GPE number */

        if (Gbl_GpeValid[Event] == GPE_INVALID)
        {
            Status = AE_BAD_PARAMETER;
        }
        else
        {
            HwClearGpe (Event);
        }

        break;

    default:
        Status = AE_BAD_PARAMETER;
    }

    return_ACPI_STATUS (Status);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiGetEventStatus
 *
 * PARAMETERS:  Event           - The fixed event or GPE to be enabled
 *              Type            - The type of event
 *              Status          - The current status of the event
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Computes the current status of the event
 *
 ******************************************************************************/


ACPI_STATUS
AcpiGetEventStatus (
    UINT32                  Event,
    UINT32                  Type,
    ACPI_EVENT_STATUS       *EventStatus)
{
    ACPI_STATUS             Status = AE_OK;

    FUNCTION_TRACE ("AcpiGetEventStatus");

    if (!EventStatus)
    {
        return_ACPI_STATUS(AE_BAD_PARAMETER);
    }

    switch (Type)
    {
    case EVENT_FIXED:
        /*
         * TBD - Fixed events...
         */
        Status = AE_NOT_IMPLEMENTED;
        break;

    case EVENT_GPE:

        /* Ensure that we have a valid GPE number */

        if (Gbl_GpeValid[Event] == GPE_INVALID)
        {
            Status = AE_BAD_PARAMETER;
        }
        else
        {
            HwGetGpeStatus (Event, EventStatus);
        }

        break;

    default:
        Status = AE_BAD_PARAMETER;
    }

    return_ACPI_STATUS (Status);
}

