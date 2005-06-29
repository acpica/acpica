/******************************************************************************
 *
 * Module Name: evrgnini- ACPI AddressSpace / OpRegion init
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


#define __EVRGNINI_C__

#include "acpi.h"
#include "acevents.h"
#include "acnamesp.h"
#include "acinterp.h"
#include "amlcode.h"

#define _COMPONENT          EVENT_HANDLING
        MODULE_NAME         ("evrgnini");


/*****************************************************************************
 *
 * FUNCTION:    AcpiEvSystemMemoryRegionSetup
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
AcpiEvSystemMemoryRegionSetup (
    ACPI_HANDLE             Handle,
    UINT32                  Function,
    void                    *HandlerContext,
    void                    **ReturnContext)
{
    MEM_HANDLER_CONTEXT     *MemContext;
    ACPI_OBJECT_INTERNAL    *RegionObj = (ACPI_OBJECT_INTERNAL *) Handle;


    FUNCTION_TRACE ("EvSystemMemoryRegionSetup");


    if (Function == ACPI_REGION_DEACTIVATE)
    {
        RegionObj->Region.RegionFlags &= ~(REGION_INITIALIZED);

        *ReturnContext = NULL;
        if (HandlerContext)
        {
            MemContext = HandlerContext;
            *ReturnContext = MemContext->HandlerContext;

            AcpiCmFree (MemContext);
        }
        return_ACPI_STATUS (AE_OK);
    }


    /* Activate.  Create a new context */

    MemContext = AcpiCmCallocate (sizeof (MEM_HANDLER_CONTEXT));
    if (!MemContext)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Init.  (Mapping fields are all set to zeros above) */

    MemContext->HandlerContext = HandlerContext;
    RegionObj->Region.RegionFlags |= REGION_INITIALIZED;

    *ReturnContext = MemContext;
    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiEvIoSpaceRegionSetup
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
AcpiEvIoSpaceRegionSetup (
    ACPI_HANDLE             Handle,
    UINT32                  Function,
    void                    *HandlerContext,
    void                    **ReturnContext)
{
    ACPI_OBJECT_INTERNAL    *RegionObj = (ACPI_OBJECT_INTERNAL *) Handle;


    FUNCTION_TRACE ("EvIoSpaceRegionSetup");


    if (Function == ACPI_REGION_DEACTIVATE)
    {
        RegionObj->Region.RegionFlags &= ~(REGION_INITIALIZED);
        *ReturnContext = HandlerContext;
        return_ACPI_STATUS (AE_OK);
    }

    /* Activate the region */

    RegionObj->Region.RegionFlags |= REGION_INITIALIZED;
    *ReturnContext = HandlerContext;

    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiEvPciConfigRegionSetup
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
 * MUTEX:       Assumes namespace is locked
 *
 ****************************************************************************/

ACPI_STATUS
AcpiEvPciConfigRegionSetup (
    ACPI_HANDLE             Handle,
    UINT32                  Function,
    void                    *HandlerContext,
    void                    **ReturnContext)
{
    ACPI_STATUS             Status = AE_OK;
    UINT32                  Temp;
    PCI_HANDLER_CONTEXT     *PciContext;
    ACPI_OBJECT_INTERNAL    *HandlerObj;
    ACPI_NAMED_OBJECT       *SearchScope;
    ACPI_OBJECT_INTERNAL    *RegionObj = (ACPI_OBJECT_INTERNAL *) Handle;


    FUNCTION_TRACE ("EvPciConfigRegionSetup");


    HandlerObj = RegionObj->Region.AddrHandler;

    if (!HandlerObj)
    {
        /*
         *  No installed handler. This shouldn't happen because the dispatch
         *  routine checks before we get here, but we check again just in case.
         */
        DEBUG_PRINT (TRACE_OPREGION,
            ("Attempting to init a region 0x%X, with no handler\n", RegionObj));
        return_ACPI_STATUS(AE_EXIST);
    }

    if (Function == ACPI_REGION_DEACTIVATE)
    {
        RegionObj->Region.RegionFlags &= ~(REGION_INITIALIZED);

        *ReturnContext = NULL;
        if (HandlerContext)
        {
            PciContext = HandlerContext;
            *ReturnContext = PciContext->HandlerContext;

            AcpiCmFree (PciContext);
        }

        return_ACPI_STATUS (Status);
    }


    /* Create a new context */

    PciContext = AcpiCmAllocate (sizeof(PCI_HANDLER_CONTEXT));
    if (!PciContext)
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

    SearchScope = AcpiNsGetParentEntry (RegionObj->Region.Nte);


    AcpiCmReleaseMutex (ACPI_MTX_NAMESPACE);

    /* AcpiEvaluate the _ADR object */

    Status = AcpiCmEvaluateNumericObject (METHOD_NAME__ADR, SearchScope, &Temp);
    /*
     *  The default is zero, since the allocation above zeroed the data, just
     *  do nothing on failures.
     */
    if (ACPI_SUCCESS (Status))
    {
        /*
         *  Got it..
         */
        PciContext->DevFunc = Temp;
    }

    /*
     *  Get the _SEG and _BBN values from the device upon which the handler
     *  is installed.
     *
     *  We need to get the _SEG and _BBN objects relative to the PCI BUS device.
     *  This is the device the handler has been registered to handle.
     */

    SearchScope = HandlerObj->AddrHandler.Nte;

    Status = AcpiCmEvaluateNumericObject (METHOD_NAME__SEG, SearchScope, &Temp);
    if (ACPI_SUCCESS (Status))
    {
        /*
         *  Got it..
         */
        PciContext->Seg = Temp;
    }

    Status = AcpiCmEvaluateNumericObject (METHOD_NAME__BBN, SearchScope, &Temp);
    if (ACPI_SUCCESS (Status))
    {
        /*
         *  Got it..
         */
        PciContext->Bus = Temp;
    }

    /*
     * Finally, include the original Handler context in the newly created PciContext 
     */
    PciContext->HandlerContext = HandlerContext;

    AcpiCmAcquireMutex (ACPI_MTX_NAMESPACE);

    *ReturnContext = PciContext;

    RegionObj->Region.RegionFlags |= REGION_INITIALIZED;
    
    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 *
 * FUNCTION:    AcpiEvDefaultRegionSetup
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
AcpiEvDefaultRegionSetup (
    ACPI_HANDLE             Handle,
    UINT32                  Function,
    void                    *HandlerContext,
    void                    **ReturnContext)
{
    ACPI_OBJECT_INTERNAL    *RegionObj = (ACPI_OBJECT_INTERNAL *) Handle;


    FUNCTION_TRACE ("EvDefaultRegionSetup");


    if (Function == ACPI_REGION_DEACTIVATE)
    {
        RegionObj->Region.RegionFlags &= ~(REGION_INITIALIZED);
        *ReturnContext = NULL;
    }
    else
    {
        RegionObj->Region.RegionFlags |= REGION_INITIALIZED;
        *ReturnContext = HandlerContext;
    }

    return_ACPI_STATUS (AE_OK);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiEvInitializeRegion
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
AcpiEvInitializeRegion (
    ACPI_OBJECT_INTERNAL    *RegionObj,
    BOOLEAN                 AcpiNsLocked)
{
    ACPI_OBJECT_INTERNAL   *HandlerObj;
    ACPI_OBJECT_INTERNAL   *ObjDesc;
    UINT32                  SpaceId;
    ACPI_NAMED_OBJECT      *Entry;        /* Namespace Object */
    ACPI_STATUS             Status;
    ACPI_NAMED_OBJECT      *RegEntry;
    ACPI_NAME              *RegNamePtr = (ACPI_NAME *) METHOD_NAME__REG;


    FUNCTION_TRACE ("EvInitializeRegion");


    if (!RegionObj)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    ACPI_ASSERT(RegionObj->Region.Nte);

    Entry = AcpiNsGetParentEntry (RegionObj->Region.Nte);
    SpaceId = RegionObj->Region.SpaceId;

    RegionObj->Region.AddrHandler = NULL;
    RegionObj->Region.REGMethod = NULL;
    RegionObj->Region.RegionFlags = INITIAL_REGION_FLAGS;

    /*
     *  Find any "_REG" associated with this region definition
     */
    Status = AcpiNsSearchNameTable (*RegNamePtr, Entry->ChildTable,
                                   ACPI_TYPE_METHOD, &RegEntry, NULL);
    if (ACPI_SUCCESS (Status))
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
     *  ie: AcpiGbl_RootObject->ParentEntry being set to NULL
     */
    while (Entry)
    {
        /*
         *  Check to see if a handler exists
         */
        HandlerObj = NULL;
        ObjDesc = AcpiNsGetAttachedObject ((ACPI_HANDLE) Entry);
        if (ObjDesc)
        {
            /*
             *  can only be a handler if the object exists
             */
            switch (Entry->Type)
            {
            case ACPI_TYPE_DEVICE:

                HandlerObj = ObjDesc->Device.AddrHandler;
                break;

            case ACPI_TYPE_PROCESSOR:

                HandlerObj = ObjDesc->Processor.AddrHandler;
                break;

            case ACPI_TYPE_THERMAL:

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
                    DEBUG_PRINT (TRACE_OPREGION,
                        ("Found handler (0x%X) for region 0x%X in obj 0x%X\n",
                        HandlerObj, RegionObj, ObjDesc));

                    /*
                     *  Found it! Now update the region and the handler
                     */
                    AcpiEvAssociateRegionAndHandler(HandlerObj, RegionObj);
                    return_ACPI_STATUS (AE_OK);
                }

                HandlerObj = HandlerObj->AddrHandler.Link;

            } /* while handlerobj */
        }

        /*
         *  This one does not have the handler we need
         *  Pop up one level
         */
        Entry = AcpiNsGetParentEntry (Entry);

    } /* while Entry != ROOT */

    /*
     *  If we get here, there is no handler for this region
     */
    DEBUG_PRINT (TRACE_OPREGION,
        ("Unable to find handler for region 0x%X\n", RegionObj));

    return_ACPI_STATUS (AE_NOT_EXIST);
}

