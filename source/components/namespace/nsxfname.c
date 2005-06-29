
/******************************************************************************
 * 
 * Module Name: nsapinam - Public interfaces to the ACPI subsystem
 *                         ACPI Namespace oriented interfaces
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

#define __NSAPINAM_C__

#include <acpi.h>
#include <interpreter.h>
#include <namespace.h>
#include <methods.h>
#include <amlcode.h>
#include <acpiobj.h>
#include <pnp.h>


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nsapinam");


/******************************************************************************
 *
 * FUNCTION:    AcpiLoadNamespace
 *
 * PARAMETERS:  DisplayAmlDuringLoad
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load the name space from what ever is pointed to by DSDT.
 *              (DSDT points to either the BIOS or a buffer.)
 *
 ******************************************************************************/

ACPI_STATUS
AcpiLoadNamespace (
    void)
{
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AcpiLoadNameSpace");


    /* Are the tables loaded yet? */

    if (Gbl_DSDT == NULL)
    {
        DEBUG_PRINT (ACPI_ERROR, ("DSDT is not in memory\n"));
        return_ACPI_STATUS (AE_NO_ACPI_TABLES);
    }

    /*
     * Now that the tables are loaded, finish some other initialization
     */


    /* Everything OK, now init the hardware */

    Status = CmHardwareInitialize ();
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    /* Initialize the namespace */
    
    Status = NsSetup ();
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    /* 
     * Load the namespace via the interpreter.  The DSDT is required,
     * but the SSDT and PSDT tables are optional.
     */


    Status = AmlLoadTable (TABLE_DSDT);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    Status = AmlLoadTable (TABLE_SSDT);
    Status = AmlLoadTable (TABLE_PSDT);


    DUMP_TABLES (NS_ALL, ACPI_INT_MAX);

    DEBUG_PRINT (ACPI_OK, ("**** ACPI Namespace successfully loaded! [%p]\n", 
                    Gbl_RootObject->Scope));


    /* Install the default OpRegion handlers, ignore the return code right now. */

    EvInstallDefaultAddressSpaceHandlers ();
    
    return_ACPI_STATUS (Status);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNameToHandle
 *
 * PARAMETERS:  Parent          - Object to search under (search scope).
 *              Name            - Pointer to an ascii string containing the name
 *              RetHandle       - Where the return handle is placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This routine will search for a caller specified name in the
 *              name space.  The caller can restrict the search region by
 *              specifying a non NULL parent.  The parent value is itself a 
 *              namespace handle. 
 *
 ******************************************************************************/

ACPI_STATUS 
AcpiNameToHandle (
    ACPI_HANDLE             Parent, 
    ACPI_NAME               Name, 
    ACPI_HANDLE             *RetHandle)
{
    NAME_TABLE_ENTRY        *ThisEntry;
    ACPI_HANDLE             LocalParent = Parent;


    if (!RetHandle)
    {
        return AE_BAD_PARAMETER;
    }

    /* Special case for root, since we can't search for it */

    if (Name == NS_ROOT)
    {
        *RetHandle = NsConvertEntryToHandle(Gbl_RootObject);
        return AE_OK;
    }

    /* Null parent means root object */

    if (!Parent)
    {
        LocalParent = Gbl_RootObject;
    }

    /* Validate the Parent handle */

    if (!(ThisEntry = NsConvertHandleToEntry (LocalParent)))
    {
        return AE_BAD_PARAMETER;
    }
    
    /* It is the scope that we are really after */

    ThisEntry = ThisEntry->Scope;

    /* Search for the name within this Parent */

    while (ThisEntry)
    {
        if (ThisEntry->Name == Name)
        {
            *RetHandle = NsConvertEntryToHandle(ThisEntry);
            return AE_OK;
        }

        ThisEntry = ThisEntry->NextEntry;
    }

    *RetHandle = NULL;
    return AE_NOT_FOUND;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiHandleToName
 *
 * PARAMETERS:  Handle          - Handle to be converted to a name
 *              RetName         - Where the 4 char (UINT32) name is placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This routine returns the name associated with ACPI_HANDLE.  This
 *              and the AcpiNameToHandle are complementary functions.
 *
 *                  Handle == AcpiNameToHandle(AcpiHandleToName(Handle))
 *              and
 *                  Name == AcpiHandleToName(AcpiNameToHandle(Name, NULL))
 *
 ******************************************************************************/

ACPI_STATUS 
AcpiHandleToName (
    ACPI_HANDLE             Handle, 
    ACPI_NAME               *RetName)
{
    NAME_TABLE_ENTRY        *ObjEntry;


    if (!RetName)
    {
        return AE_BAD_PARAMETER;
    }

    /* Validate handle and convert to and NTE */

    if (!(ObjEntry = NsConvertHandleToEntry (Handle)))
    {
        *RetName = 0;
        return AE_BAD_PARAMETER;
    }


    /* Just extract the name field */

    *RetName = ObjEntry->Name;
    return AE_OK;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiPathnameToHandle
 *
 * PARAMETERS:  Pathname        - pointer to ascii string containing full pathname
 *              RetHandle       - Where the return handle is stored
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This routine will search for a caller specified name in the
 *              name space.  The pathname provided must be a fully qualified 
 *              path from the root of the namespace.
 *
 ******************************************************************************/

ACPI_STATUS 
AcpiPathnameToHandle (
    ACPI_STRING             Pathname, 
    ACPI_HANDLE             *RetHandle)
{
    NAME_TABLE_ENTRY     *TmpNte;
    ACPI_STATUS     Status;

    if (!RetHandle || !Pathname)
    {
        return AE_BAD_PARAMETER;
    }

    /* Special case for root, since we can't search for it */

    if (STRCMP (Pathname, NS_ROOT_PATH) == 0)
    {
        *RetHandle = NsConvertEntryToHandle(Gbl_RootObject);
        return AE_OK;
    }

    /*
     *  Find the Nte and convert to the user format
     */
    TmpNte = NULL;
    Status = NsGetNte (Pathname, NS_ALL, &TmpNte);

   *RetHandle = NsConvertEntryToHandle(TmpNte);

    return (Status);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiHandleToPathname
 *
 * PARAMETERS:  Handle          - Handle to be converted to a pathname
 *              RetPathPtr      - Buffer for returned path
 *
 * RETURN:      pointer to a string containing the fully qualified Name.
 *
 * DESCRIPTION: This routine returns the fully qualified name associated with
 *              the Handle parameter.  This and the AcpiPathnameToHandle are 
 *              complementary functions.
 *
 ******************************************************************************/


ACPI_STATUS 
AcpiHandleToPathname (
    ACPI_HANDLE             Handle, 
    ACPI_BUFFER             *RetPathPtr)
{
    ACPI_STATUS             Status;


    /* Buffer pointer must be valid always */

    if (!RetPathPtr)
    {
        return AE_BAD_PARAMETER;
    }

    /* Allow length to be zero and ignore the pointer */

    if ((RetPathPtr->Length) &&
       (!RetPathPtr->Pointer))
    {
        return AE_BAD_PARAMETER;
    }

    Status = NsHandleToPathname (Handle, &RetPathPtr->Length, RetPathPtr->Pointer);

    return Status;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiGetDeviceInfo
 *
 * PARAMETERS:  Handle          - Handle to a device
 *              Info            - Where the device info is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Returns information about the device as gleaned from running
 *              several standard control methods.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiGetObjectInfo (
    ACPI_HANDLE             Device, 
    ACPI_DEVICE_INFO        *Info)
{
    DEVICE_ID               Hid;
    DEVICE_ID               Uid;
    ACPI_STATUS             Status;
    UINT32                  DeviceStatus = 0;
    UINT32                  Address = 0;
    NAME_TABLE_ENTRY        *DeviceEntry;


    /* Parameter validation */

    if (!Device || !Info)
    {
        return AE_BAD_PARAMETER;
    }

    if (!(DeviceEntry = NsConvertHandleToEntry (Device)))
    {
        return AE_BAD_PARAMETER;
    }

    Info->Type = DeviceEntry->Type;
    Info->Name = DeviceEntry->Name;
    Info->Parent = NsConvertEntryToHandle(DeviceEntry->ParentEntry);

    if (DeviceEntry->Type != ACPI_TYPE_Device)
    {
        /*
         *  We're done, get out
         */
        return AE_OK;
    }
    Info->Valid = 0;

    /* Execute the _HID method and save the result */

    Status = Execute_HID (DeviceEntry, &Hid);
    if (ACPI_SUCCESS (Status))
    {
        Info->HardwareId = Hid.Data.Number;
        Info->Valid |= ACPI_VALID_HID;
    }

    /* Execute the _UID method and save the result */

    Status = Execute_UID (DeviceEntry, &Uid);
    if (ACPI_SUCCESS (Status))
    {
        Info->UniqueId = Uid.Data.Number;
        Info->Valid |= ACPI_VALID_UID;
    }

    /* 
     * Execute the _STA method and save the result
     * _STA is not always present 
     */

    Status = Execute_STA (DeviceEntry, &DeviceStatus);
    if (ACPI_SUCCESS (Status))
    {
        Info->CurrentStatus = DeviceStatus;
        Info->Valid |= ACPI_VALID_STA;
    }

    /* 
     * Execute the _ADR method and save result if successful
     * _ADR is not always present
     */

    Status = Execute_ADR (DeviceEntry, &Address);
    if (ACPI_SUCCESS (Status))
    {
        Info->Address = Address;
        Info->Valid |= ACPI_VALID_ADR;
    }

    return AE_OK;
}



/* OBSOLETE FUNCTIONS */

/****************************************************************************
 *
 * FUNCTION:    AcpiEnumerateDevice
 *
 * PARAMETERS:  DevHandle       - handle to the device to  enumerate
 *              HidPtr          - Pointer to a DEVICE_ID structure to return 
 *                                the device's HID
 *              EnumPtr         - Pointer to a BOOLEAN flag that if set to TRUE 
 *                                indicate that the enumeration of this device 
 *                                is owned by ACPI.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Returns HID in the HidPtr structure and an indication that the
 *              device should be enumerated in the field pointed to by EnumPtr
 *
 ******************************************************************************/

ACPI_STATUS
AcpiEnumerateDevice (
    ACPI_HANDLE             DevHandle, 
    DEVICE_ID               *HidPtr, 
    BOOLEAN                 *EnumPtr)
{

    HidPtr->Data.String = NULL;
    *EnumPtr = FALSE;

    return (AE_OK);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiGetNextSubDevice
 *
 * PARAMETERS:  DevHandle       - handle to the device to enumerate
 *              Count           - zero based counter of the sub-device to locate
 *              RetHandle       - Where handle for next device is placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This routine is used in the enumeration process to locate devices
 *              located within the namespace of another device.
 *
 ******************************************************************************/

ACPI_STATUS 
AcpiGetNextSubDevice (
    ACPI_HANDLE             DevHandle, 
    UINT32                  Count, 
    ACPI_HANDLE             *RetHandle)
{

    if (!RetHandle)
    {
        return AE_BAD_PARAMETER;
    }

    *RetHandle = NULL;

    return (AE_OK);
}





