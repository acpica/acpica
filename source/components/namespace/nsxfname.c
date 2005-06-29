
/******************************************************************************
 * 
 * Module Name: nsapinam - Public interfaces to the ACPI subsystem
 *                         ACPI Name oriented interfaces
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


#define __NSAPINAM_C__

#include <acpi.h>
#include <interpreter.h>
#include <namespace.h>
#include <methods.h>
#include <acpiobj.h>
#include <pnp.h>
#include <string.h>


#define _THIS_MODULE        "nsapinam.c"
#define _COMPONENT          NAMESPACE


/****************************************************************************
 *
 * FUNCTION:    AcpiNameToHandle
 *
 * PARAMETERS:  Scope           - Handle for a search scope.
 *              Name            - Pointer to an ascii string containing the name
 *              RetHandle       - Where the return handle is placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This routine will search for a caller specified name in the
 *              name space.  The caller can restrict the search region by
 *              specifying a non NULL scope.  The Scope value is itself a namespace
 *              handle.  If the scope value is NULL or the NsName specified is
 *              fully qualified, teh Scope value is ignored.
 *
 ******************************************************************************/

ACPI_STATUS 
AcpiNameToHandle (NsHandle Scope, UINT32 Name, NsHandle *RetHandle)
{
    nte         *ThisEntry;
    NsHandle    LocalScope = Scope;


    if (!RetHandle)
    {
        return AE_BAD_PARAMETER;
    }

    /* Special case for root, since we can't search for it */

    if (Name == NS_ROOT)
    {
        *RetHandle = RootObject;
        return AE_OK;
    }

    /* Null scope means root scope */

    if (!Scope)
    {
        LocalScope = RootObject->Scope;
    }

    /* Search for the name within this scope */

    ThisEntry = (nte *) LocalScope;

    while (ThisEntry)
    {
        if (ThisEntry->Name == Name)
        {
            *RetHandle = ThisEntry;
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
 * DESCRIPTION: This routine returns the name associated with NsHandle.  This
 *              and the AcpiNameToHandle are complementary functions.
 *
 *                  Handle == AcpiNameToHandle(AcpiHandleToName(Handle))
 *              and
 *                  Name == AcpiHandleToName(AcpiNameToHandle(Name, NULL))
 *
 ******************************************************************************/

ACPI_STATUS 
AcpiHandleToName (NsHandle Handle, UINT32 *RetName)
{
    nte         *Object;

    if (!RetName)
    {
        return AE_BAD_PARAMETER;
    }

    if (!Handle)
    {
        *RetName = 0;
        return AE_BAD_PARAMETER;
    }

    Object = (nte *) Handle;

    *RetName = Object->Name;
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
AcpiPathnameToHandle (char *Pathname, NsHandle *RetHandle)
{

    if (!RetHandle || !Pathname)
    {
        return AE_BAD_PARAMETER;
    }

    /* Special case for root, since we can't search for it */

    if (strcmp (Pathname, NS_ROOT_PATH) == 0)
    {
        *RetHandle = RootObject;
        return AE_OK;
    }

    *RetHandle = NULL;
    return (NsGetHandle (Pathname, NS_ALL, RetHandle));
}


/****************************************************************************
 *
 * FUNCTION:    AcpiHandleToPathname
 *
 * PARAMETERS:  Handle          - Handle to be converted to a pathname
 *              RetPathPtr      - APICBuffer for returned path
 *
 * RETURN:      pointer to a string containing the fully qualified Name.
 *
 * DESCRIPTION: This routine returns the fully qualified name associated with
 *              the Handle parameter.  This and the AcpiPathnameToHandle are 
 *              complementary functions.
 *
 ******************************************************************************/


ACPI_STATUS 
AcpiHandleToPathname (NsHandle Handle, APIBuffer *RetPathPtr)
{
    if ((!RetPathPtr->BufferPtr)    ||
        (!RetPathPtr->Length)       ||
        (!Handle))
    {
        return AE_BAD_PARAMETER;
    }

    return (NsHandleToPathname (Handle, RetPathPtr->Length, RetPathPtr->BufferPtr));
}


