
/******************************************************************************
 * 
 * Name: acpisubsys.h - external interfaces to the ACPI subsystem
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
 * 2.1. Intel grants, free of charge, to any person ("Licensee") obtaining a 
 * copy of the source code appearing in this file ("Covered Code") a license 
 * under Intel's copyrights in the base code distributed originally by Intel 
 * ("Original Intel Code") to copy, make derivatives, distribute, use and 
 * display any portion of the Covered Code in any form; and
 *
 * 2.2. Intel grants Licensee a non-exclusive and non-transferable patent 
 * license (without the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell, 
 * offer to sell, and import the Covered Code and derivative works thereof 
 * solely to the minimum extent necessary to exercise the above copyright 
 * license, and in no event shall the patent license extend to any additions to
 * or modifications of the Original Intel Code.  No other license or right is 
 * granted directly or by implication, estoppel or otherwise;
 *
 * the above copyright and patent license is granted only if the following 
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of source code of any substantial portion of the Covered 
 * Code or modification must include the above Copyright Notice, the above 
 * License, this list of Conditions, and the following Disclaimer and Export 
 * Compliance provision.  In addition, Licensee must cause all Covered Code to 
 * which Licensee contributes to contain a file documenting the changes 
 * Licensee made to create that Covered Code and the date of any change.  
 * Licensee must include in that file the documentation of any changes made by
 * any predecessor Licensee.  Licensee must include a prominent statement that
 * the modification is derived, directly or indirectly, from Original Intel 
 * Code.
 *
 * 3.2. Redistribution in binary form of any substantial portion of the Covered 
 * Code or modification must reproduce the above Copyright Notice, and the 
 * following Disclaimer and Export Compliance provision in the documentation 
 * and/or other materials provided with the distribution.
 *
 * 3.3. Intel retains all right, title, and interest in and to the Original 
 * Intel Code.
 *
 * 3.4. Neither the name Intel nor any other trademark owned or controlled by 
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
 * event Licensee exports any such software from the United States or re-
 * exports any such software from a foreign destination, Licensee shall ensure
 * that the distribution and export/re-export of the software is in compliance 
 * with all laws, regulations, orders, or other restrictions of the U.S. Export 
 * Administration Regulations. Licensee agrees that neither it nor any of its 
 * subsidiaries will export/re-export any technical data, process, software, or 
 * service, directly or indirectly, to any country for which the United States 
 * government or any agency thereof requires an export license, other 
 * governmental approval, or letter of assurance, without first obtaining such
 * license, approval or letter.
 *
 *****************************************************************************/


#ifndef __ACPISUBSYS_H__
#define __ACPISUBSYS_H__

#include <datatypes.h>
#include <acpitables.h>
#include <acpiobj.h>

#define ACPI_MODE               1
#define LEGACY_MODE             2



/*
 * Global interfaces
 */

ACPI_STATUS
AcpiInitialize (
    char                    *AcpiFile);


/*
 * Interpreter interfaces
 */

ACPI_STATUS
AcpiEvaluateObject (
    ACPI_HANDLE             Handle, 
    char                    *Pathname, 
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    *ReturnObject);


/*
 * Namespace and enumeration interfaces
 */

ACPI_STATUS
AcpiLoadNamespace (
    void);

ACPI_STATUS
AcpiLoadTable (
    ACPI_TABLE_HEADER       *TablePtr,
    ACPI_HANDLE             *OutTableHandle);

ACPI_STATUS
AcpiUnLoadTable (
    ACPI_HANDLE             TableHandle);

ACPI_STATUS
AcpiLoadTableFromFile (
    char                    *FileName,
    ACPI_HANDLE             *OutTableHandle);

ACPI_STATUS
AcpiGetTableHeader (
    ACPI_TABLE_TYPE         TableType,
    char                    *OutTableHeader);

ACPI_STATUS
AcpiGetTable (
    ACPI_TABLE_TYPE         TableType,
    ACPI_BUFFER             *RetBuffer);

ACPI_STATUS
AcpiNameToHandle (
    UINT32                  Name,
    ACPI_HANDLE             Scope, 
    ACPI_HANDLE             *OutHandle);

ACPI_STATUS
AcpiHandleToName (
    ACPI_HANDLE             Handle,
    UINT32                  *RetName);

ACPI_STATUS
AcpiPathnameToHandle (
    char                    *Pathname,
    ACPI_HANDLE             *OutHandle);

ACPI_STATUS
AcpiHandleToPathname (
    ACPI_HANDLE             Handle,
    ACPI_BUFFER             *OutPathBuffer);

ACPI_STATUS
AcpiWalkNamespace (
    ACPI_OBJECT_TYPE        Type, 
    ACPI_HANDLE             StartHandle, 
    UINT32                  MaxDepth,
    void *                  (* UserFunction)(ACPI_HANDLE,UINT32,void *), 
    void                    *Context, 
    void *                  *ReturnValue);

ACPI_STATUS
AcpiGetDeviceInfo (
    ACPI_HANDLE             Device, 
    ACPI_DEVICE_INFO        *Info);


/* 
 * Object manipulation
 */

ACPI_STATUS
AcpiGetNextObject (
    ACPI_OBJECT_TYPE        Type, 
    ACPI_HANDLE             Scope, 
    ACPI_HANDLE             Handle,
    ACPI_HANDLE             *OutHandle);

ACPI_STATUS 
AcpiGetType (
    ACPI_HANDLE             Handle,
    ACPI_OBJECT_TYPE        *RetType);

ACPI_STATUS
AcpiGetParent (
    ACPI_HANDLE             Handle,
    ACPI_HANDLE             *OutHandle);

ACPI_STATUS
AcpiGetScope (
    ACPI_HANDLE             Handle,
    ACPI_HANDLE             *OutHandle);

ACPI_STATUS
AcpiGetContainingScope (
    ACPI_HANDLE             Handle,
    ACPI_HANDLE             *OutHandle);


/*
 * Event / System interfaces
 */

ACPI_STATUS
AcpiEnable (
	void);

ACPI_STATUS
AcpiDisable (
    void);

ACPI_STATUS
AcpiInstallFixedEventHandler (
    UINT32                  Event,
    FIXED_EVENT_HANDLER     Handler,
    void                    *Context);
    
ACPI_STATUS
AcpiRemoveFixedEventHandler (
    UINT32                  Event,
    FIXED_EVENT_HANDLER     Handler);

ACPI_STATUS
AcpiInstallGpeHandler (
    UINT32                  GpeNumber, 
    GPE_HANDLER             Handler, 
    void                    *Context);

ACPI_STATUS
AcpiRemoveGpeHandler (
    UINT32                  GpeNumber, 
    GPE_HANDLER             Handler);

ACPI_STATUS
AcpiInstallNotifyHandler (
    ACPI_HANDLE             Device, 
    NOTIFY_HANDLER          Handler, 
    void                    *Context);

ACPI_STATUS
AcpiRemoveNotifyHandler (
    ACPI_HANDLE             Device, 
    NOTIFY_HANDLER          Handler);

ACPI_STATUS
AcpiInstallOpRegionHandler (
    UINT32                  OpRegion, 
    OPREGION_HANDLER        Handler, 
    void                    *Context);

ACPI_STATUS
AcpiRemoveOpRegionHandler (
    UINT32                  OpRegion, 
    OPREGION_HANDLER        Handler);



/*
 * Resource related interfaces
 */

ACPI_STATUS
AcpiGetCurrentResources(
    ACPI_HANDLE             DeviceHandle,
    ACPI_BUFFER             *RetBuffer);

ACPI_STATUS
AcpiGetPossibleResources(
    ACPI_HANDLE             DeviceHandle,
    ACPI_BUFFER             *RetBuffer);

ACPI_STATUS
AcpiSetCurrentResources (
    ACPI_HANDLE             DeviceHandle,
    ACPI_BUFFER             *InBuffer);

ACPI_STATUS
AcpiGetIRQRoutingTable  (
    ACPI_HANDLE             BusDeviceHandle, 
    ACPI_BUFFER             *RetBuffer);

ACPI_STATUS
AcpiGetSystemInfo(
    ACPI_BUFFER             *RetBuffer);


/*
 * Hardware (ACPI device) interfaces
 */

ACPI_STATUS
AcpiSetMode (
    INT32                   Mode);

INT32
AcpiGetMode (
    void);

INT32
AcpiGetModeCapabilities (
    void);

ACPI_STATUS
AcpiSetFirmwareWakingVector (
    void                    *PhysicalAddress);

ACPI_STATUS
AcpiGetFirmwareWakingVector (
    void                    **PhysicalAddress);



#endif /* ACPISUBSYS_H */