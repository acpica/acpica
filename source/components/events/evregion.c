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
#include <namesp.h>
#include <interp.h>
#include <amlcode.h>
#include <methods.h>

#define _COMPONENT          EVENT_HANDLING
        MODULE_NAME         ("evregion");




#define PCI_ROOT_HID        "PNP0A03"



/******************************************************************************
 * 
 * FUNCTION:    EvFindOnePciRootBus
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: 
 *
 *****************************************************************************/

ACPI_STATUS
EvFindOnePciRootBus (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue)
{
    NAME_TABLE_ENTRY        *Entry;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_STATUS             Status;

    
    Entry = (NAME_TABLE_ENTRY *) ObjHandle;
    ObjDesc = ((NAME_TABLE_ENTRY *)ObjHandle)->Object;


    /*
     * We are looking for all valid _HID objects.
     */

    if ((Entry->Name != *(UINT32 *) METHOD_NAME__HID) ||
        (!ObjDesc))
    {
        return AE_OK;
    }


    /*
     * Found an _HID object. 
     * Now we need a HID with the value EISAID("PNP0A03")
     * HID can be either a number or a string.
     */

    switch (ObjDesc->Common.Type)
    {
    case ACPI_TYPE_Number:

        /* TBD: What should this number be?  */

        if (ObjDesc->Number.Value != 0x12345678)
        {
            return AE_OK;
        }

        break;

    case ACPI_TYPE_String:

        if (STRNCMP (ObjDesc->String.Pointer, PCI_ROOT_HID, sizeof (PCI_ROOT_HID)))
        {
            return AE_OK;
        }

        break;

    default:

        return AE_OK;
    }


    /*
     * We found a valid PCI_ROOT_HID.
     * The parent of the HID entry is the PCI device;  Install the default PCI
     * handler for this PCI device.
     */


    /* TBD: Namespace is LOCKED here.  This call might deadlock. */

    Status = AcpiInstallAddressSpaceHandler (Entry->ParentEntry,
                ADDRESS_SPACE_PCI_CONFIG, ACPI_DEFAULT_HANDLER, NULL, NULL);

    return AE_OK;
}



/******************************************************************************
 * 
 * FUNCTION:    EvFindPciRootBuses
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: 
 *
 *****************************************************************************/

ACPI_STATUS
EvFindPciRootBuses (
    char                    *NameArg)
{
    
    NsWalkNamespace (ACPI_TYPE_Any, ACPI_ROOT_OBJECT, ACPI_UINT32_MAX,
                        FALSE, EvFindOnePciRootBus, NameArg, NULL);

    return AE_OK;
}



/**************************************************************************
 *
 * FUNCTION:    EvInstallDefaultAddressSpaceHandlers
 *
 * PARAMETERS:  
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Installs the core subsystem address space handlers.
 *
 *************************************************************************/

ACPI_STATUS
EvInstallDefaultAddressSpaceHandlers (
    void)
{
    ACPI_STATUS             Status;
    

    FUNCTION_TRACE ("EvInstallDefaultAddressSpaceHandlers");

    /*
     * NOTE:    All address spaces (PCI Config, EC, SMBus) are scope dependent
     *          and registration must occur for a specific device.  In the case
     *          system memory and IO address spaces there is currently no device
     *          associated with the address space.  For these we use the root.
     */

    Status = AcpiInstallAddressSpaceHandler (Gbl_RootObject,
                ADDRESS_SPACE_SYSTEM_MEMORY, ACPI_DEFAULT_HANDLER, NULL, NULL);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    Status = AcpiInstallAddressSpaceHandler (Gbl_RootObject,
                ADDRESS_SPACE_SYSTEM_IO, ACPI_DEFAULT_HANDLER, NULL, NULL);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /*
     *  Install PCI config space handler for all PCI root bridge.  A PCI root
     *  bridge is found by searching for devices containing a HID with the value
     *  EISAID("PNP0A03")
     *
     *  BUGBUG  BUGBUG  BUGBUG  BUGBUG  BUGBUG  BUGBUG  BUGBUG  BUGBUG  BUGBUG
     *
     *  For now, I am hardcoding the installation of the PCI buses in.  This 
     *  needs to be fixed ASAP.
     *
     *  BUGBUG  BUGBUG  BUGBUG  BUGBUG  BUGBUG  BUGBUG  BUGBUG  BUGBUG  BUGBUG
     */

    {
        char *PCIBus_devices[] = {"\\_SB_.PCI0", "\\_SB_.PCI1", "\\_SB_.PCI2", "\\_SB_.CBN", NULL };
        NATIVE_UINT i = 0;

        ACPI_HANDLE PCIBusHandle;

        while (PCIBus_devices[i]) 
        {
            Status = AcpiGetHandle (NULL, PCIBus_devices[i], &PCIBusHandle);
            if (ACPI_SUCCESS(Status))
            {
                Status = AcpiInstallAddressSpaceHandler (PCIBusHandle,
                            ADDRESS_SPACE_PCI_CONFIG, ACPI_DEFAULT_HANDLER, NULL, NULL);

                if (ACPI_FAILURE (Status))
                {
                    return_ACPI_STATUS (Status);
                }

            }
            i++;
        }
    } /* PCI Address space handler install */

    return_ACPI_STATUS (Status);
}


/* TBD: Move to the methods directory */

/**************************************************************************
 *
 * FUNCTION:    EvExecuteRegMethod
 *
 * PARAMETERS:  RegionObj           - Object structure
 *              Function            - On (1) or Off (0)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute _REG method for a region
 *
 *************************************************************************/

ACPI_STATUS
EvExecuteRegMethod (
    ACPI_OBJECT_INTERNAL   *RegionObj,
    UINT32                  Function)
{
    ACPI_OBJECT_INTERNAL   *Params[3];
    ACPI_OBJECT_INTERNAL    SpaceID_Obj;
    ACPI_OBJECT_INTERNAL    Function_Obj;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("EvExecuteRegMethod");


    if (RegionObj->Region.REGMethod == NULL)
    {
        return_ACPI_STATUS (AE_OK);
    }

    /*
     *  _REG method has two arguments
     *  Arg0:   Integer: Operation region space ID
     *          Same value as RegionObj->Region.SpaceId
     *  Arg1:   Integer: connection status
     *          1 for connecting the handler,
     *          0 for disconnecting the handler
     *          Passed as a parameter
     */

    CmInitStaticObject (&SpaceID_Obj);
    CmInitStaticObject (&Function_Obj);

    /*
     *  Method requires two parameters.
     */
    Params [0] = &SpaceID_Obj;
    Params [1] = &Function_Obj;
    Params [2] = NULL;

    /*
     *  Set up the parameter objects
     */
    SpaceID_Obj.Common.Type    = ACPI_TYPE_Number;
    SpaceID_Obj.Number.Value   = RegionObj->Region.SpaceId;

    Function_Obj.Common.Type   = ACPI_TYPE_Number;
    Function_Obj.Number.Value  = Function;

    /*
     *  Execute the method, no return value
     */
    Status = NsEvaluateByHandle (RegionObj->Region.REGMethod, Params, NULL);
    return_ACPI_STATUS (Status);
} 


/**************************************************************************
 *
 * FUNCTION:    EvAddressSpaceDispatch
 *
 * PARAMETERS:  RegionObj           - internal region object
 *              SpaceId             - ID of the address space (0-255)
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
    ACPI_OBJECT_INTERNAL   *RegionObj,
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                 *Value)
{
    ACPI_STATUS             Status;
    ADDRESS_SPACE_HANDLER   Handler;
    REGION_SETUP_FUNCTION   RegionSetup;
    ACPI_OBJECT_INTERNAL    *HandlerDesc;
    void                   *RegionContext;

    FUNCTION_TRACE ("EvAddressSpaceDispatch");

    /*
     *  Check for an installed handler
     */
    HandlerDesc = RegionObj->Region.AddrHandler;

    if (!HandlerDesc)
    {
        DEBUG_PRINT (TRACE_OPREGION,
            ("Dispatch address access region 0x%X, no handler\n", RegionObj));
        return_ACPI_STATUS(AE_EXIST);
    }

    /*
     *  It may be the case that the region has never been initialized
     *  Some types of regions require special init code
     */
    if (!(RegionObj->Region.RegionFlags & REGION_INITIALIZED)) {
        /*
         *  This region has not been initialized yet, do it
         */
        RegionSetup = HandlerDesc->AddrHandler.RegionSetupFunction;
        if (!RegionSetup) {
            /*
             *  Bad news, no init routine and not init'd
             */
		    DEBUG_PRINT (ACPI_ERROR,
                ("EvAddressSpaceDispatch: No init routine for region %X\n", 
                  RegionObj));
            return_ACPI_STATUS(AE_UNKNOWN_STATUS);
        }
        Status = RegionSetup (  RegionObj,
                                ACPI_REGION_ACTIVATE,
                                HandlerDesc->AddrHandler.InstallTimeContext,
                                &RegionContext);
        /*
         *  Init routine may fail
         */
	    if (ACPI_FAILURE (Status))
	    {
		    DEBUG_PRINT (ACPI_ERROR, ("EvAddressSpaceDispatch: %s from region init, SpaceID %d\n", 
						    CmFormatException (Status), RegionObj->Region.SpaceId));
            return_ACPI_STATUS(Status);
	    }

        /*
         *  Save the returned context for use in all accesses to the region
         */
        HandlerDesc->AddrHandler.Context = RegionContext;
    }

    /*
     *  We have everything we need, begin the process
     */
    Handler = HandlerDesc->AddrHandler.Handler;

    DEBUG_PRINT ((TRACE_OPREGION | VERBOSE_INFO),
            ("Addrhandler 0x%X (0x%X), Address 0x%X\n", 
             RegionObj->Region.AddrHandler->AddrHandler, Handler, Address));

    if (!(HandlerDesc->AddrHandler.Flags & ADDR_HANDLER_DEFAULT_INSTALLED))
    {
        /*
         *  For handlers other than the default (supplied) handlers, we must
         *  exit the interpreter because the handler *might* block -- we don't
         *  know what it will do, so we can't hold the lock on the intepreter.
         */
        AmlExitInterpreter();
    }

    /* 
     *  Invoke the handler.
     */
    /*
     * MCW - TBD: This is not right, but I want to get it going quickly
     */ 
    HandlerDesc->AddrHandler.Context = RegionObj;

    Status = Handler (Function, Address, BitWidth, Value, HandlerDesc->AddrHandler.Context);

	if (ACPI_FAILURE (Status))
	{
		DEBUG_PRINT (ACPI_ERROR, ("EvAddressSpaceDispatch: %s from handler, SpaceID %d\n", 
						CmFormatException (Status), RegionObj->Region.SpaceId));
	}

    if (!(HandlerDesc->AddrHandler.Flags & ADDR_HANDLER_DEFAULT_INSTALLED))
    {
        /* We just returned from a non-default handler, we must re-enter the interpreter */

        AmlEnterInterpreter ();
    }

    return_ACPI_STATUS (Status);
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
EvDisassociateRegionFromHandler(
    ACPI_OBJECT_INTERNAL   *RegionObj)
{
    ACPI_OBJECT_INTERNAL   *HandlerObj;
    ACPI_OBJECT_INTERNAL   *ObjDesc;
    ACPI_OBJECT_INTERNAL  **LastObjPtr;
    REGION_SETUP_FUNCTION   RegionSetup;
    void                   *RegionContext;
    ACPI_STATUS             Status;

    FUNCTION_TRACE ("EvDisassociateRegionAndHandler");

    /*
     *  Get the address handler from the region object
     */

    HandlerObj = RegionObj->Region.AddrHandler;
    if (!HandlerObj)
    {
        /*
         *  This guy has no handler, we're done
         */
        return_VOID;
    }

    /*
     *  Find this region in the handler's list
     */

    ObjDesc = HandlerObj->AddrHandler.RegionList;
    LastObjPtr = &HandlerObj->AddrHandler.RegionList;

    while (ObjDesc)
    {
        /*
         *  See if this is the one
         */
        if (ObjDesc == RegionObj)
        {
            DEBUG_PRINT (TRACE_OPREGION, ("Removing Region 0x%X from address handler 0x%X\n",
                            RegionObj, HandlerObj));
            /*
             *  This is it, remove it from the handler's list
             */
            *LastObjPtr = ObjDesc->Region.Link;

            /*
             *  Now stop region accesses by executing the _REG
             *  method
             */
            EvExecuteRegMethod (RegionObj, 0);

            /*
             *  Tell undo region prep work
             */
            RegionSetup = HandlerObj->AddrHandler.RegionSetupFunction;
            Status = RegionSetup (  RegionObj,
                                    ACPI_REGION_DEACTIVATE,
                                    HandlerObj->AddrHandler.InstallTimeContext,
                                    &RegionContext);
            /*
             *  Init routine may fail
             */
	        if (ACPI_FAILURE (Status))
	        {
		        DEBUG_PRINT (ACPI_ERROR,
                    ("EvDisassociateRegionFromHandler: %s from region init, SpaceID %d\n", 
					 CmFormatException (Status), RegionObj->Region.SpaceId));
                /*
                 *  Just ignore failures for now
                 */
	        }

            /*
             *  Remove handler reference in the region
             *
             *  NOTE: this doesn't mean that the region goes away
             *  The region is just inaccessible as indicated to
             *  the _REG method
             *
             *  If the region is on the handler's list
             *  this better be the region's handler
             */
            ACPI_ASSERT (RegionObj->Region.AddrHandler == HandlerObj);

            RegionObj->Region.AddrHandler = NULL;

            return_VOID;

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
    DEBUG_PRINT (TRACE_OPREGION, ("Cannot remove region 0x%X from address handler 0x%X\n",
                    RegionObj, HandlerObj));

    return_VOID;
}

/*****************************************************************************
 * 
 * FUNCTION:    EvSystemMemoryRegionSetup
 *
 * PARAMETERS:  RegionObj           - region we are interested in
 *              Function            - start or stop
 *              HandlerContext      - Address space handler context
 *              Returned context    - context to be used with each call to the
 *                                    handler for this region
 * RETURN:      Status
 *
 * DESCRIPTION: Do any prep work for region handling, a nop for now
 *
 ****************************************************************************/

ACPI_STATUS
EvSystemMemoryRegionSetup (
    ACPI_OBJECT_INTERNAL        *RegionObj,
    UINT32                      Function,
    void                        *HandlerContext,
    void                        **ReturnContext)
{
    FUNCTION_TRACE ("EvSystemMemoryRegionSetup");

    if (Function == ACPI_REGION_DEACTIVATE) {
        RegionObj->Region.RegionFlags &= ~(REGION_INITIALIZED);
        *ReturnContext = NULL;
    } else {
        RegionObj->Region.RegionFlags |= REGION_INITIALIZED;
        *ReturnContext = HandlerContext;
    }

    return_ACPI_STATUS (AE_OK);
}

/*****************************************************************************
 * 
 * FUNCTION:    EvIoSpaceRegionSetup
 *
 * PARAMETERS:  RegionObj           - region we are interested in
 *              Function            - start or stop
 *              HandlerContext      - Address space handler context
 *              Returned context    - context to be used with each call to the
 *                                    handler for this region
 * RETURN:      Status
 *
 * DESCRIPTION: Do any prep work for region handling
 *
 ****************************************************************************/

ACPI_STATUS
EvIoSpaceRegionSetup (
    ACPI_OBJECT_INTERNAL        *RegionObj,
    UINT32                      Function,
    void                        *HandlerContext,
    void                        **ReturnContext)
{
    FUNCTION_TRACE ("EvIoSpaceRegionSetup");

    if (Function == ACPI_REGION_DEACTIVATE) {
        RegionObj->Region.RegionFlags &= ~(REGION_INITIALIZED);
        *ReturnContext = NULL;
    } else {
        RegionObj->Region.RegionFlags |= REGION_INITIALIZED;
        *ReturnContext = HandlerContext;
    }

    return_ACPI_STATUS (AE_OK);
}

/*****************************************************************************
 * 
 * FUNCTION:    EvPciConfigRegionSetup
 *
 * PARAMETERS:  RegionObj           - region we are interested in
 *              Function            - start or stop
 *              HandlerContext      - Address space handler context
 *              Returned context    - context to be used with each call to the
 *                                    handler for this region
 * RETURN:      Status
 *
 * DESCRIPTION: Do any prep work for region handling
 *
 ****************************************************************************/

ACPI_STATUS
EvPciConfigRegionSetup (
    ACPI_OBJECT_INTERNAL        *RegionObj,
    UINT32                      Function,
    void                        *HandlerContext,
    void                        **ReturnContext)
{
    ACPI_STATUS             Status = AE_OK;
    NATIVE_UINT             Temp;
    PCI_HANDLER_CONTEXT    *PCIContext;
    ACPI_OBJECT_INTERNAL   *HandlerObj;
    NAME_TABLE_ENTRY       *SearchScope;

    FUNCTION_TRACE ("EvPciConfigRegionSetup");

    HandlerObj = RegionObj->Region.AddrHandler;

    if(!HandlerObj) {
        /*
         *  No Handler ... bummer....
         *
         *  This cannot happen because the dispatch routine checks before
         *  we get here, but just in case.
         */
        DEBUG_PRINT (TRACE_OPREGION,
            ("Attempting to init a region 0x%X, with no handler\n", RegionObj));
        return_ACPI_STATUS(AE_EXIST);
    }

    if (Function == ACPI_REGION_DEACTIVATE) {
        /*
         *  For right now we just free the allocated space
         */
        RegionObj->Region.RegionFlags &= ~(REGION_INITIALIZED);
//        CmFree(HandlerObj->AddrHandler.Context)
        *ReturnContext = NULL;
        return_ACPI_STATUS (Status);
    }

    PCIContext = CmAllocate (sizeof(PCI_HANDLER_CONTEXT));

    if (!PCIContext)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /*
     *  For PCI Config space access, we have to pass the segment, bus,
     *  device and function numbers.  This routine must acquire those.
     */

    /*
     *  First get device and function numbers from the _ADR object
     *  in the parent's scope.
     */
    ACPI_ASSERT(RegionObj->Region.Nte);

    SearchScope = RegionObj->Region.Nte->ParentEntry;

    Status = EvaluateNumeric (METHOD_NAME__ADR, SearchScope, &Temp);
    /*
     *  The default is zero, since the allocation above zeroed the data, just
     *  do nothing on failures.
     */
    if (ACPI_SUCCESS (Status))
    {
        /*
         *  Got it..
         */
        PCIContext->DevFunc = Temp;
    }

    /*
     *  Get the _SEG and _BBN values from the device the handler is installed on
     *
     *  We need to get the _SEG and _BBN objects relative to the PCI BUS device.
     *  This is the device the handler has been registered to handle.
     */

    SearchScope = HandlerObj->AddrHandler.Nte;

    Status = EvaluateNumeric (METHOD_NAME__SEG, SearchScope, &Temp);
    if (ACPI_SUCCESS (Status))
    {
        /*
         *  Got it..
         */
        PCIContext->Seg = Temp;
    }

    Status = EvaluateNumeric (METHOD_NAME__BBN, SearchScope, &Temp);
    if (ACPI_SUCCESS (Status))
    {
        /*
         *  Got it..
         */
        PCIContext->Bus = Temp;
    }

    *ReturnContext = PCIContext;

    RegionObj->Region.RegionFlags |= REGION_INITIALIZED;
    return_ACPI_STATUS (AE_OK);
}

/*****************************************************************************
 * 
 * FUNCTION:    EvDefaultRegionSetup
 *
 * PARAMETERS:  RegionObj           - region we are interested in
 *              Function            - start or stop
 *              HandlerContext      - Address space handler context
 *              Returned context    - context to be used with each call to the
 *                                    handler for this region
 * RETURN:      Status
 *
 * DESCRIPTION: Do any prep work for region handling
 *
 ****************************************************************************/

ACPI_STATUS
EvDefaultRegionSetup (
    ACPI_OBJECT_INTERNAL        *RegionObj,
    UINT32                      Function,
    void                        *HandlerContext,
    void                        **ReturnContext)
{
    FUNCTION_TRACE ("EvDefaultRegionSetup");

    if (Function == ACPI_REGION_DEACTIVATE) {
        RegionObj->Region.RegionFlags &= ~(REGION_INITIALIZED);
        *ReturnContext = NULL;
    } else {
        RegionObj->Region.RegionFlags |= REGION_INITIALIZED;
        *ReturnContext = HandlerContext;
    }

    return_ACPI_STATUS (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    EvAssociateRegionAndHandler
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

ACPI_STATUS
EvAssociateRegionAndHandler(
    ACPI_OBJECT_INTERNAL    *HandlerObj,
    ACPI_OBJECT_INTERNAL    *RegionObj)
{
    ACPI_STATUS     Status;


    FUNCTION_TRACE ("EvAssociateRegionAndHandler");


    DEBUG_PRINT (TRACE_OPREGION, ("Adding Region 0x%X to address handler 0x%X\n", 
                    RegionObj, HandlerObj));

    ACPI_ASSERT (RegionObj->Region.SpaceId == HandlerObj->AddrHandler.SpaceId);
    ACPI_ASSERT (RegionObj->Region.AddrHandler == 0);

    /*
     *  Link this region to the front of the handler's list
     */

    RegionObj->Region.Link = HandlerObj->AddrHandler.RegionList;
    HandlerObj->AddrHandler.RegionList = RegionObj;

    /*
     *  set the region's handler
     */
    RegionObj->Region.AddrHandler = HandlerObj;

    /*
     *  Last thing, tell ASL region is usable
     */
    Status = EvExecuteRegMethod (RegionObj, 1);

    return_ACPI_STATUS (Status);
}


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

ACPI_STATUS
EvAddrHandlerHelper (
    ACPI_HANDLE             ObjHandle, 
    UINT32                  Level, 
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_OBJECT_INTERNAL    *HandlerObj;
    ACPI_OBJECT_INTERNAL    *TmpObj;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    NAME_TABLE_ENTRY        *ObjEntry;
    ACPI_STATUS             Status;


    HandlerObj = (ACPI_OBJECT_INTERNAL *) Context;

    /* Parameter validation */

    if (!HandlerObj)
    {
        return (AE_OK);
    }

    /* Convert and validate the device handle */

    ObjEntry = NsConvertHandleToEntry (ObjHandle);
    if (!ObjEntry)
    {
        return (AE_BAD_PARAMETER);
    }

    /*
     *  We only care about regions.and objects
     *  that can have address handlers
     */

    if ((ObjEntry->Type != ACPI_TYPE_Device) &&
        (ObjEntry->Type != ACPI_TYPE_Region) &&
        (ObjEntry != Gbl_RootObject))
    {
        return (AE_OK);
    }

    /* Check for an existing internal object */

    ObjDesc = NsGetAttachedObject ((ACPI_HANDLE) ObjEntry);
    if (!ObjDesc)
    {
        /*
         *  The object DNE, we don't care about it
         */
        return (AE_OK);
    }

    /*
     *  Devices are handled different than regions
     */
    if (IS_THIS_OBJECT_TYPE (ObjDesc, ACPI_TYPE_Device))
    {
        /*
         *  See if this guy has any handlers
         */
        TmpObj = ObjDesc->Device.AddrHandler;
        while (TmpObj)
        {
            /*
             *  Now let's see if it's for the same address space.
             */
            if (TmpObj->AddrHandler.SpaceId == HandlerObj->AddrHandler.SpaceId)
            {
                /*
                 *  It's for the same address space
                 */

                DEBUG_PRINT (TRACE_OPREGION, ("Found handler for %s in device 0x%X (0x%X) handler 0x%X\n",
                                Gbl_RegionTypes[HandlerObj->AddrHandler.SpaceId], ObjDesc, TmpObj, HandlerObj));
                
                /*
                 *  Since the object we found it on was a device, then it
                 *  means that someone has already installed a handler for
                 *  the branch of the namespace from this device on.  Just
                 *  bail out telling the walk routine to not traverse this
                 *  branch.  This preserves the scoping rule for handlers.
                 */
                return (AE_CTRL_DEPTH);
            }

            /*
             *  Move through the linked list of handlers
             */
            TmpObj = TmpObj->AddrHandler.Link;
        }

        /*
         *  As long as the device didn't have a handler for this
         *  space we don't care about it.  We just ignore it and
         *  proceed.
         */
        return (AE_OK);
    }

    /*
     *  Only here if it was a region
     */
    ACPI_ASSERT (ObjDesc->Common.Type == ACPI_TYPE_Region);

    if (ObjDesc->Region.SpaceId != HandlerObj->AddrHandler.SpaceId)
    {
        /*
         *  This region is for a different address space
         *  ignore it
         */
        return (AE_OK);
    }

    /*
     *  Now we have a region and it is for the handler's address
     *  space type.
     *
     *  First disconnect region for any previous handler (if any)
     */
    EvDisassociateRegionFromHandler (ObjDesc);

    /*
     *  Then connect the region to the new handler
     */
    Status = EvAssociateRegionAndHandler (HandlerObj, ObjDesc);

    return (Status);
}


/******************************************************************************
 *
 * FUNCTION:    EvInitializeRegion
 *
 * PARAMETERS:  RegionObj  - Region we are initializing
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initializes the region, finds any _REG methods and saves them
 *              for execution at a later time
 *
 *              Get the appropriate address space handler for a newly
 *              created region.
 *
 *              This also performs address space specific intialization.  For
 *              example, PCI regions must have an _ADR object that contains
 *              a PCI address in the scope of the defintion.  This address is
 *              required to perform an access to PCI config space.
 *
 ******************************************************************************/

ACPI_STATUS
EvInitializeRegion (
    ACPI_OBJECT_INTERNAL    *RegionObj,
    BOOLEAN                 NsLocked)
{
    ACPI_OBJECT_INTERNAL   *HandlerObj;
    ACPI_OBJECT_INTERNAL   *ObjDesc;
    UINT32                  SpaceId; 
    NAME_TABLE_ENTRY       *Nte;        /* Namespace Object */
    ACPI_STATUS             Status;
    NAME_TABLE_ENTRY       *RegEntry;
    ACPI_NAME              *RegNamePtr = (ACPI_NAME *) METHOD_NAME__REG;

    FUNCTION_TRACE ("EvInitializeRegion");

    if (!RegionObj)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    ACPI_ASSERT(RegionObj->Region.Nte);

    Nte = RegionObj->Region.Nte->ParentEntry;
    SpaceId = RegionObj->Region.SpaceId;

    RegionObj->Region.AddrHandler = NULL;
    RegionObj->Region.REGMethod = NULL;
    RegionObj->Region.RegionFlags = INITIAL_REGION_FLAGS;

    /*
     *  Find any "_REG" associated with this region definition
     */
    Status = NsSearchOneScope (*RegNamePtr, Nte->Scope, ACPI_TYPE_Method, &RegEntry, NULL);
    if (Status == AE_OK)
    {
        /*
         *  The _REG method is optional and there can be only one per region
         *  definition.  This will be executed when the handler is attached
         *  or removed
         */
        RegionObj->Region.REGMethod = RegEntry;
    }

    /*
     *  The following loop depends upon the root nte having no parent
     *  ie: Gbl_RootObject->ParentEntry being set to NULL
     */
    while (Nte)
    {
        /*
         *  Check to see if a handler exists
         */
        HandlerObj = NULL;
        ObjDesc = NsGetAttachedObject ((ACPI_HANDLE) Nte);
        if (ObjDesc) 
        {
            /*
             *  can only be a handler if the object exists
             */
            switch (Nte->Type)
            {
            case ACPI_TYPE_Device:

                HandlerObj = ObjDesc->Device.AddrHandler;
                break;

            case ACPI_TYPE_Processor:

                HandlerObj = ObjDesc->Processor.AddrHandler;
                break;

            case ACPI_TYPE_Thermal:

                HandlerObj = ObjDesc->ThermalZone.AddrHandler;
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
                    DEBUG_PRINT (TRACE_OPREGION, ("Found handler (0x%X) for region 0x%X in obj 0x%X\n",
                                    HandlerObj, RegionObj, ObjDesc));
                    
                    /*
                     *  Found it! Now update the region and the handler
                     */
                    EvAssociateRegionAndHandler(HandlerObj, RegionObj);
                    return_ACPI_STATUS (AE_OK);
                }

                HandlerObj = HandlerObj->AddrHandler.Link;

            } /* while handlerobj */
        }

        /*
         *  This one does not have the handler we need
         *  Pop up one level
         */
        Nte = Nte->ParentEntry;

    } /* while Nte != ROOT */

    /*
     *  If we get here, there is no handler for this region
     */
    DEBUG_PRINT (TRACE_OPREGION, ("Unable to find handler for region 0x%X\n", RegionObj));

    return_ACPI_STATUS (AE_NOT_EXIST);
}

