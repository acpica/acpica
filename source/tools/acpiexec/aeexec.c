/******************************************************************************
 *
 * Module Name: aeexec - Support routines for AcpiExec utility
 *              $Revision: 1.50 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2002, Intel Corp.
 * All rights reserved.
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


#include "acpi.h"
#include "acparser.h"
#include "amlcode.h"
#include "acnamesp.h"
#include "acdebug.h"
#include "aecommon.h"

#include <stdio.h>


#define _COMPONENT          ACPI_TOOLS
        MODULE_NAME         ("aeexec")


ACPI_PARSE_OBJECT           *AcpiGbl_ParsedNamespaceRoot;
ACPI_PARSE_OBJECT           *root;
UINT8                       *AmlStart;
UINT32                      AmlLength;
UINT8                       *DsdtPtr;
UINT32                      AcpiDsdtLength;

DEBUG_REGIONS               Regions;
RSDP_DESCRIPTOR             LocalRsdp;


/******************************************************************************
 *
 * FUNCTION:    AeLocalGetRootPointer
 *
 * PARAMETERS:
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Return a local RSDP, used to dynamically load tables via the
 *              standard ACPI mechanism.
 *
 *****************************************************************************/

ACPI_STATUS
AeLocalGetRootPointer (
    UINT32                  Flags,
    ACPI_PHYSICAL_ADDRESS   *RsdpPhysicalAddress)
{

    STRCPY (LocalRsdp.Signature, RSDP_SIG);
    LocalRsdp.Revision = 1;

    return (AE_NOT_FOUND);
}


/******************************************************************************
 *
 * FUNCTION:    AeRegionHandler
 *
 * PARAMETERS:  Standard region handler parameters
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Test handler - Handles some dummy regions via memory that can
 *              be manipulated in Ring 3.
 *
 *****************************************************************************/

ACPI_STATUS
AeRegionHandler (
    UINT32                  Function,
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT32                  BitWidth,
    ACPI_INTEGER            *Value,
    void                    *HandlerContext,
    void                    *RegionContext)
{

    ACPI_OPERAND_OBJECT     *RegionObject = (ACPI_OPERAND_OBJECT*) RegionContext;
    ACPI_PHYSICAL_ADDRESS   BaseAddress;
    UINT32                  Length;
    BOOLEAN                 BufferExists;
    REGION                  *RegionElement;
    void                    *BufferValue;
    UINT32                  ByteWidth;


    PROC_NAME ("AeRegionHandler");


    /*
     * If the object is not a region, simply return
     */
    if (RegionObject->Region.Type != ACPI_TYPE_REGION)
    {
        return AE_OK;
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_OPREGION, "Operation Region request on %s at 0x%X\n",
            AcpiUtGetRegionName (RegionObject->Region.SpaceId),
            Address));


    /*
     * Find the region's address space and length before searching
     *  the linked list.
     */
    BaseAddress = RegionObject->Region.Address;
    Length = RegionObject->Region.Length;

    /*
     * Search through the linked list for this region's buffer
     */
    BufferExists = FALSE;
    RegionElement = Regions.RegionList;

    if (0 != Regions.NumberOfRegions)
    {
        while (!BufferExists && RegionElement)
        {
            if (RegionElement->Address == BaseAddress &&
                RegionElement->Length == Length)
            {
                BufferExists = TRUE;
            }
            else
            {
                RegionElement = RegionElement->NextRegion;
            }
        }
    }

    /*
     * If the Region buffer does not exist, create it now
     */
    if (FALSE == BufferExists)
    {
        /*
         * Do the memory allocations first
         */
        RegionElement = AcpiOsAllocate (sizeof (REGION));
        if (!RegionElement)
        {
            return AE_NO_MEMORY;
        }

        RegionElement->Buffer = AcpiOsCallocate (Length);
        if (!RegionElement->Buffer)
        {
            AcpiOsFree (RegionElement);
            return AE_NO_MEMORY;
        }

        RegionElement->Address      = BaseAddress;
        RegionElement->Length       = Length;
        RegionElement->NextRegion   = NULL;

        /*
         * Increment the number of regions and put this one
         *  at the head of the list as it will probably get accessed
         *  more often anyway.
         */
        Regions.NumberOfRegions += 1;

        if (NULL != Regions.RegionList)
        {
            RegionElement->NextRegion = Regions.RegionList->NextRegion;
        }

        Regions.RegionList = RegionElement;
    }

    /*
     * Calculate the size of the memory copy
     */
    ByteWidth = (BitWidth / 8);

    if (BitWidth % 8)
    {
        ByteWidth += 1;
    }

    /*
     * The buffer exists and is pointed to by RegionElement.
     * We now need to verify the request is valid and perform the operation.
     *
     * NOTE: RegionElement->Length is in bytes, therefore it we compare against
     * ByteWidth (see above)
     */
    if (((ACPI_INTEGER) Address + ByteWidth) >
        ((ACPI_INTEGER)(RegionElement->Address) + RegionElement->Length))
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_WARN, "Request on [%4.4s] is beyond region limit Req-%lX+%lX, Base=%lX, Len-%lX\n",
                &((RegionObject->Region.Node)->Name), (UINT32) Address, ByteWidth, (UINT32)(RegionElement->Address),
                RegionElement->Length));

        return AE_AML_REGION_LIMIT;
    }

    /*
     * Get BufferValue to point to the "address" in the buffer
     */
    BufferValue = ((UINT8 *) RegionElement->Buffer +
                    ((ACPI_INTEGER) Address - (ACPI_INTEGER) RegionElement->Address));

    /*
     * Perform a read or write to the buffer space
     */
    switch (Function)
    {
    case ACPI_READ:
        /*
         * Set the pointer Value to whatever is in the buffer
         */
        MEMCPY (Value, BufferValue, ByteWidth);
        break;

    case ACPI_WRITE:
        /*
         * Write the contents of Value to the buffer
         */
        MEMCPY (BufferValue, Value, ByteWidth);
        break;

    default:
        return AE_BAD_PARAMETER;
    }

    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AeRegionInit
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Opregion init function.
 *
 *****************************************************************************/

ACPI_STATUS
AeRegionInit (
    ACPI_HANDLE                 RegionHandle,
    UINT32                      Function,
    void                        *HandlerContext,
    void                        **RegionContext)
{
    /*
     * Real simple, set the RegionContext to the RegionHandle
     */
    *RegionContext = RegionHandle;

    return AE_OK;
}


/******************************************************************************
 *
 * FUNCTION:    AeNotifyHandler
 *
 * PARAMETERS:  Standard notify handler parameters
 *
 * RETURN:      Status
 *
 * DESCRIPTION: System notify handler for AcpiExec utility.  Used by the ASL
 *              test suite(s) to communicate errors and other information to
 *              this utility via the Notify() operator.
 *
 *****************************************************************************/

void
AeNotifyHandler (
    ACPI_HANDLE                 Device,
    UINT32                      Value,
    void                        *Context)
{

    switch (Value)
    {
    case 0:
        printf ("**** Method Error 0x%X: Results not equal\n", Value);
        if (AcpiGbl_DebugFile)
        {
            AcpiOsPrintf ("**** Method Error: Results not equal\n");
        }
        break;


    case 1:
        printf ("**** Method Error: Incorrect numeric result\n");
        if (AcpiGbl_DebugFile)
        {
            AcpiOsPrintf ("**** Method Error: Incorrect numeric result\n");
        }
        break;


    case 2:
        printf ("**** Method Error: An operand was overwritten\n");
        if (AcpiGbl_DebugFile)
        {
            AcpiOsPrintf ("**** Method Error: An operand was overwritten\n");
        }
        break;


    default:
        printf ("**** Received a notify, value 0x%X\n", Value);
        if (AcpiGbl_DebugFile)
        {
            AcpiOsPrintf ("**** Received a notify, value 0x%X\n", Value);
        }
        break;
    }

}


/******************************************************************************
 *
 * FUNCTION:    AeInstallHandlers
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install handlers for the AcpiExec utility.
 *              NOTE: Currently only a system notify handler is installed.
 *
 *****************************************************************************/

ACPI_STATUS
AeInstallHandlers (void)
{
    ACPI_STATUS             Status;
    UINT32                  i;


    PROC_NAME ("AeInstallHandlers");


    Status = AcpiInstallNotifyHandler (ACPI_ROOT_OBJECT, ACPI_SYSTEM_NOTIFY,
                                        AeNotifyHandler, NULL);
    if (ACPI_FAILURE (Status))
    {
        printf ("Could not install a global notify handler, %s\n",
            AcpiFormatException (Status));
    }

    for (i = 0; i < 3; i++)
    {
        Status = AcpiRemoveAddressSpaceHandler (AcpiGbl_RootNode,
                        (ACPI_ADR_SPACE_TYPE) i, AeRegionHandler);

        /* Install handler at the root object.
         * TBD: all default handlers should be installed here!
         */
        Status = AcpiInstallAddressSpaceHandler (AcpiGbl_RootNode,
                        (ACPI_ADR_SPACE_TYPE) i, AeRegionHandler, AeRegionInit, NULL);
        if (ACPI_FAILURE (Status))
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_ERROR,
                "Could not install an OpRegion handler for %s space(%d), %s\n",
                AcpiUtGetRegionName((UINT8) i), i, AcpiFormatException (Status)));
            return (Status);
        }
    }

    /*
     * Initialize the global Region Handler space
     * MCW 3/23/00
     */
    Regions.NumberOfRegions = 0;
    Regions.RegionList = NULL;

    return Status;
}


