/******************************************************************************
 * 
 * Module Name: ieregion - ACPI default OpRegion (address space) handlers
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


#define __IEREGION_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>
#include <hardware.h>


#define _THIS_MODULE        "ieregion.c"
#define _COMPONENT          INTERPRETER


/*****************************************************************************
 * 
 * FUNCTION:    AmlSystemMemorySpaceHandler
 *
 * PARAMETERS:  Function            - Read or Write operation
 *              Address             - Where in the space to read or write
 *              BitWidth            - Field width in bits (8, 16, or 32)
 *              Value               - Pointer to in or out value
 *              Context             - Context pointer
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handler for the System Memory address space (Op Region)
 *
 ****************************************************************************/

ACPI_STATUS
AmlSystemMemorySpaceHandler (
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value,
    void                    *Context)
{
    ACPI_STATUS             Status = AE_OK;
    void                    *PhysicalAddrPtr = NULL;


    FUNCTION_TRACE ("AmlSystemMemorySpaceHandler");


    /* Decode the function parameter */

    switch (Function)
    {

    case ADDRESS_SPACE_READ:

        /* XXX: was PhysicalAddrPtr = PHYStoFP(Address); */

        /* 
         * XXX: This may be too high an overhead to do every time.
         * Probably should have a mapping cached.
         */

        PhysicalAddrPtr = OsdMapMemory ((void *) Address, 4);

        switch (BitWidth)
        {
        /* System memory width */

        case 8:
            *Value = (UINT32)* (UINT8 *) PhysicalAddrPtr;
            break;

        case 16:
            *Value = (UINT32)* (UINT16 *) PhysicalAddrPtr;
            break;

        case 32:
            *Value = * (UINT32 *) PhysicalAddrPtr;
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR,
                    ("AmlSystemMemorySpaceHandler: Invalid SystemMemory width %d\n", BitWidth));
            Status = AE_AML_ERROR;
        }

        OsdUnMapMemory (PhysicalAddrPtr, 4);
        break;


    case ADDRESS_SPACE_WRITE:

        /* XXX: was PhysicalAddrPtr = PHYStoFP(Address); */

        /* XXX: This may be too high an overhead to do every time.
         * Probably should have a mapping cached.
         */

        PhysicalAddrPtr = OsdMapMemory ((void *) Address, 4);
                
        switch (BitWidth)
        {
        case 8:
            *(UINT8 *) PhysicalAddrPtr = (UINT8) *Value;
            break;

        case 16:
            *(UINT16 *) PhysicalAddrPtr = (UINT16) *Value;
            break;

        case 32:
            *(UINT32 *) PhysicalAddrPtr = *Value;
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlSystemMemorySpaceHandler: Invalid SystemMemory width %d\n", BitWidth));
            Status = AE_AML_ERROR;
        }

        OsdUnMapMemory (PhysicalAddrPtr, 4);
        break;


    default:
        Status = AE_BAD_PARAMETER;
        break;
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlSystemIoSpaceHandler
 *
 * PARAMETERS:  Function            - Read or Write operation
 *              Address             - Where in the space to read or write
 *              BitWidth            - Field width in bits (8, 16, or 32)
 *              Value               - Pointer to in or out value
 *              Context             - Context pointer
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handler for the System IO address space (Op Region)
 *
 ****************************************************************************/

ACPI_STATUS
AmlSystemIoSpaceHandler (
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value,
    void                    *Context)
{
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("AmlSystemIoSpaceHandler");


    /* Decode the function parameter */

    switch (Function)
    {

    case ADDRESS_SPACE_READ:

        switch (BitWidth)
        {
        /* I/O Port width */

        case 8:
            *Value = (UINT32) OsdIn8 ((UINT16) Address);
            break;

        case 16:
            *Value = (UINT32) OsdIn16 ((UINT16) Address);
            break;

        case 32:
            *Value = OsdIn32 ((UINT16) Address);
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR,
                    ("AmlSystemIoSpaceHandler: Invalid SystemIO width %d\n", BitWidth));
            Status = AE_AML_ERROR;
        }

        break;


    case ADDRESS_SPACE_WRITE:

        switch (BitWidth)
        {
        /* I/O Port width */

        case 8:
            OsdOut8 ((UINT16) Address, (UINT8) *Value);
            break;

        case 16:
            OsdOut16 ((UINT16) Address, (UINT16) *Value);
            break;

        case 32:
            OsdOut32 ((UINT16) Address, *Value);
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlSystemIoSpaceHandler: Invalid SystemIO width %d\n", BitWidth));
            Status = AE_AML_ERROR;
        }

        break;


    default:
        Status = AE_BAD_PARAMETER;
        break;
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlPciConfigSpaceHandler
 *
 * PARAMETERS:  Function            - Read or Write operation
 *              Address             - Where in the space to read or write
 *              BitWidth            - Field width in bits (8, 16, or 32)
 *              Value               - Pointer to in or out value
 *              Context             - Context pointer
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handler for the PCI Config address space (Op Region)
 *
 ****************************************************************************/

ACPI_STATUS
AmlPciConfigSpaceHandler (
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value,
    void                    *Context)
{
    ACPI_STATUS             Status = AE_OK;
    UINT8                   PciBus;
    UINT8                   DevFunc;
    UINT8                   PciReg;


    FUNCTION_TRACE ("AmlPciConfigSpaceHandler");


    /* Decode the function parameter */

    switch (Function)
    {

    case ADDRESS_SPACE_READ:

        PciBus  = (UINT8) (Address >> 16);
        DevFunc = (UINT8) (Address >> 8);
        PciReg  = (UINT8) ((Address >> 2) & 0x3f);
        *Value  = 0;

        switch (BitWidth)
        {
        /* PCI Register width */

        case 8:
            Status = OsdReadPciCfgByte (PciBus, DevFunc, PciReg, (UINT8 *) Value);
            break;

        case 16:
            Status = OsdReadPciCfgWord (PciBus, DevFunc, PciReg, (UINT16 *) Value);
            break;

        case 32:
            Status = OsdReadPciCfgDword (PciBus, DevFunc, PciReg, Value);
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR,
                    ("AmlPciConfigSpaceHandler: Invalid PCIConfig width %d\n", BitWidth));
            Status = AE_AML_ERROR;
        }

        break;


    case ADDRESS_SPACE_WRITE:

        PciBus  = (UINT8) (Address >> 16);
        DevFunc = (UINT8) (Address >> 8);
        PciReg  = (UINT8) ((Address >> 2) & 0x3f);

        switch (BitWidth)
        {
        /* PCI Register width */

        case 8:
            Status = OsdWritePciCfgByte (PciBus, DevFunc, PciReg, *(UINT8 *) Value);
            break;

        case 16:
            Status = OsdWritePciCfgWord (PciBus, DevFunc, PciReg, *(UINT16 *) Value);
            break;

        case 32:
            Status = OsdWritePciCfgDword (PciBus, DevFunc, PciReg, *Value);
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlPciConfigSpaceHandler: Invalid PCIConfig width %d\n", BitWidth));
            Status = AE_AML_ERROR;
        }

        break;


    default:
        Status = AE_BAD_PARAMETER;
        break;
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlEmbeddedControllerSpaceHandler
 *
 * PARAMETERS:  Function            - Read or Write operation
 *              Address             - Where in the space to read or write
 *              BitWidth            - Field width in bits (8, 16, or 32)
 *              Value               - Pointer to in or out value
 *              Context             - Context pointer
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handler for the Embedded Controller (EC) address space (Op Region)
 *
 ****************************************************************************/

ACPI_STATUS
AmlEmbeddedControllerSpaceHandler (
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value,
    void                    *Context)
{
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("AmlEmbeddedControllerSpaceHandler");

    DEBUG_PRINT (ACPI_ERROR, ("AmlEmbeddedControllerSpaceHandler: **** EC OpRegion not implemented\n"));
    FUNCTION_STATUS_EXIT (AE_NOT_IMPLEMENTED);
    return AE_NOT_IMPLEMENTED;


    /* Decode the function parameter */

    switch (Function)
    {
    case ADDRESS_SPACE_READ:
        break;

    case ADDRESS_SPACE_WRITE:
        break;

    default:
        Status = AE_BAD_PARAMETER;
        break;
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlSmBusSpaceHandler
 *
 * PARAMETERS:  Function            - Read or Write operation
 *              Address             - Where in the space to read or write
 *              BitWidth            - Field width in bits (8, 16, or 32)
 *              Value               - Pointer to in or out value
 *              Context             - Context pointer
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handler for the SM Bus address space (Op Region)
 *
 ****************************************************************************/

ACPI_STATUS
AmlSmBusSpaceHandler (
    UINT32                  Function,
    UINT32                  Address,
    UINT32                  BitWidth,
    UINT32                  *Value,
    void                    *Context)
{
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("AmlSmBusSpaceHandler");

    DEBUG_PRINT (ACPI_ERROR, ("AmlSmBusSpaceHandler: **** SmBus OpRegion not implemented\n"));
    FUNCTION_STATUS_EXIT (AE_NOT_IMPLEMENTED);
    return AE_NOT_IMPLEMENTED;


    /* Decode the function parameter */

    switch (Function)
    {
    case ADDRESS_SPACE_READ:
        break;

    case ADDRESS_SPACE_WRITE:
        break;

    default:
        Status = AE_BAD_PARAMETER;
        break;
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}

