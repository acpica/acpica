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
        FUNCTION_STATUS_EXIT (AE_NO_ACPI_TABLES);
        return AE_NO_ACPI_TABLES;
    }

    /*  ACPI tables are available or not required */

    if (SYS_MODE_LEGACY == HwGetModeCapabilities ())
    {   
        /*
         * No ACPI mode support provided by BIOS
         */

        /* TBD: verify input file specified */

        DEBUG_PRINT (ACPI_WARN, ("Only legacy mode supported!\n"));
        FUNCTION_STATUS_EXIT (AE_ERROR);
        return AE_ERROR;
    }

    OriginalMode = HwGetMode();

    if (EvInstallSciHandler () != AE_OK)
    {   
        /* Unable to install SCI handler */

        DEBUG_PRINT (ACPI_FATAL, ("Unable to install System Control Interrupt Handler"));
        FUNCTION_STATUS_EXIT (AE_ERROR);
        return AE_ERROR;
    }
    
    /*  SCI Interrupt Handler installed properly    */

    if (SYS_MODE_ACPI != OriginalMode)
    {   
        /*  legacy mode */
                
        if (AE_OK != HwSetMode (SYS_MODE_ACPI))
        {   
            /*  Unable to transition to ACPI Mode   */

            DEBUG_PRINT (ACPI_FATAL, ("Could not transition to ACPI mode.\n"));
            FUNCTION_STATUS_EXIT (AE_ERROR);
            return AE_ERROR;    
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
            FUNCTION_STATUS_EXIT (AE_ERROR);
            return AE_ERROR;
        }
    
        EvInitGpeControlMethods ();

    }

    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;

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

    FUNCTION_STATUS_EXIT (Status);
    return Status;
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

    FUNCTION_TRACE ("AcpiInstallFixedEventHandler");

    /* Sanity check the parameters. */

    if (Event >= NUM_FIXED_EVENTS)
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }
    
    /* Don't allow two handlers. */

    if (NULL != FixedEventHandlers[Event])
    {
        FUNCTION_STATUS_EXIT (AE_EXIST);
        return AE_EXIST;
    }
    
    /* Install the handler before enabling the event - just in case... */

    FixedEventHandlers[Event] = Handler;
    
    if (1 != HwRegisterIO (ACPI_WRITE, Event + TMR_EN, 1))
    {
        DEBUG_PRINT (ACPI_WARN, ("Could not write to fixed event enable register.\n"));
        FixedEventHandlers[Event] = NULL;
        FUNCTION_STATUS_EXIT (AE_ERROR);
        return AE_ERROR;
    }

    DEBUG_PRINT (ACPI_INFO, ("Enabled fixed event %d.  Handler: %x\n", Event, Handler));    
    
    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
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

    FUNCTION_TRACE ("AcpiRemoveFixedEventHandler");

    /* Sanity check the parameters. */

    if (Event >= NUM_FIXED_EVENTS)
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }
    
    /* Disable the event before removing the handler - just in case... */

    if (0 != HwRegisterIO (ACPI_WRITE, Event + TMR_EN, 0))
    {
        DEBUG_PRINT (ACPI_WARN, ("Could not write to fixed event enable register.\n"));
        FUNCTION_STATUS_EXIT (AE_ERROR);
        return AE_ERROR;
    }

    FixedEventHandlers[Event] = NULL;    
    DEBUG_PRINT (ACPI_INFO, ("Disabled fixed event %d.\n", Event));    
    
    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
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
    FUNCTION_TRACE ("AcpiInstallGpeHandler");


    /* Parameter validation */

    if (!Handler || (GpeNumber >= GpeRegisterCount))
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }


    /* TBD: Mutex */

    /* Make sure that there isn't a handler there already */

    if (GpeInfo[GpeNumber].Handler)
    {
        FUNCTION_STATUS_EXIT (AE_EXIST);
        return AE_EXIST;
    }


    /* Install the handler */

    GpeInfo[GpeNumber].Handler = Handler;
    GpeInfo[GpeNumber].Context = Context;


    /* Now we can enable the GPE */

    HwEnableGpe (GpeNumber);

    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
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
    FUNCTION_TRACE ("AcpiRemoveGpeHandler");


    /* Parameter validation */

    if (!Handler || (GpeNumber >= GpeRegisterCount))
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }


    /* TBD: Mutex */

    /* Make sure that the installed handler is the same */

    if (GpeInfo[GpeNumber].Handler != Handler)
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }


    /* Disable the GPE before removing the handler */

    HwDisableGpe (GpeNumber);


    /* Remove the handler */

    GpeInfo[GpeNumber].Handler = NULL;
    GpeInfo[GpeNumber].Context = NULL;

 
    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiInstallNotifyHandler
 *
 * PARAMETERS:  Device          - The device for which notifies will be handled
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
    NOTIFY_HANDLER          Handler, 
    void                    *Context)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    NAME_TABLE_ENTRY        *ObjEntry;


    FUNCTION_TRACE ("AcpiInstallNotifyHandler");


    /* Parameter validation */

    if (!Handler)
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }


    /* Convert and validate the device handle */

    if (!(ObjEntry = NsConvertHandleToEntry (Device)))
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }

    /*
     * The handle must refer to either a device or a thermal zone.  These
     * are the ONLY objects that can receive ACPI notifications
     */

    if ((ObjEntry->Type != TYPE_Device) &&
        (ObjEntry->Type != TYPE_Thermal))
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }


    /* Check for an existing internal object */

    if (!ObjEntry->Value)
    {
        /* We must create one */

        ObjDesc = AllocateObjectDesc ();
        if (!ObjDesc)
        {
            /* Descriptor allocation failure   */

            FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
            return AE_NO_MEMORY;
        }

        /* Init */

        ObjDesc->Type = ObjEntry->Type;
        ObjEntry->Value = ObjDesc;
    }

    else
    {
        /* Object exists; check for an existing handler */

        ObjDesc = ObjEntry->Value;
        if (ObjDesc->Device.Handler)
        {
            FUNCTION_STATUS_EXIT (AE_EXIST);
            return AE_EXIST;
        }
    }

    /* 
     * Now we can install the handler
     * Devices and Thermal zones share a common structure
     */

    /* TBD: Mutex?? */

    ObjDesc->Device.Handler = Handler;
    ObjDesc->Device.Context = Context;


    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiRemoveNotifyHandler
 *
 * PARAMETERS:  Device          - The device for which notifies will be handled
 *              Handler         - Address of the handler
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a handler for notifies on an ACPI device
 *
 ******************************************************************************/

ACPI_STATUS
AcpiRemoveNotifyHandler (
    ACPI_HANDLE             Device, 
    NOTIFY_HANDLER          Handler)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    NAME_TABLE_ENTRY        *ObjEntry;


    FUNCTION_TRACE ("AcpiRemoveNotifyHandler");


    /* Parameter validation */

    if (!Handler)
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }


    /* Convert and validate the device handle */

    if (!(ObjEntry = NsConvertHandleToEntry (Device)))
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }

    /*
     * The handle must refer to either a device or a thermal zone.  These
     * are the ONLY objects that can receive ACPI notifications
     */

    if ((ObjEntry->Type != TYPE_Device) &&
        (ObjEntry->Type != TYPE_Thermal))
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }


    /* Check for an existing internal object */

    if (!ObjEntry->Value)
    {
        FUNCTION_STATUS_EXIT (AE_NOT_EXIST);
        return AE_NOT_EXIST;
        
    }

    /* Make sure handler matches */

    ObjDesc = ObjEntry->Value;
    if (ObjDesc->Device.Handler != Handler)
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }


    /* 
     * Now we can remove the handler
     * Devices and Thermal zones share a common structure
     */

    /* TBD: Mutex?? */

    ObjDesc->Device.Handler = NULL;
    ObjDesc->Device.Context = NULL;


    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AcpiInstallAddressSpaceHandler
 *
 * PARAMETERS:  SpaceId         - The address space ID
 *              Handler         - Address of the handler
 *              Context         - Value passed to the handler on each GPE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler for accesses on an Operation Region
 *
 ******************************************************************************/

ACPI_STATUS
AcpiInstallAddressSpaceHandler (
    UINT32                  SpaceId, 
    ADDRESS_SPACE_HANDLER   Handler, 
    void                    *Context)
{
    FUNCTION_TRACE ("AcpiInstallAddressSpaceHandler");


    /* Parameter validation */

    if ((!Handler) ||
        (SpaceId > ACPI_MAX_ADDRESS_SPACE))
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }


    /* TBD: Mutex */


    /* Check for an existing handler */

    if (AddressSpaces[SpaceId].Handler)
    {
        FUNCTION_STATUS_EXIT (AE_EXIST);
        return AE_EXIST;
    }

    /* Install the handler */

    AddressSpaces[SpaceId].Handler = Handler;
    AddressSpaces[SpaceId].Context = Context;


    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
}


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
    UINT32                  SpaceId, 
    ADDRESS_SPACE_HANDLER   Handler)
{
    FUNCTION_TRACE ("AcpiRemoveAddressSpaceHandler");


    /* Parameter validation */

    if ((!Handler) ||
        (SpaceId > ACPI_MAX_ADDRESS_SPACE))
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }

    /* TBD: Mutex */

    /* Make sure that the installed handler is the same */

    if (AddressSpaces[SpaceId].Handler != Handler)
    {
        FUNCTION_STATUS_EXIT (AE_BAD_PARAMETER);
        return AE_BAD_PARAMETER;
    }

    /* Remove the handler */

    AddressSpaces[SpaceId].Handler = NULL;
    AddressSpaces[SpaceId].Context = NULL;


    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
}
