/******************************************************************************
 * 
 * Module Name: aeexec - Top level parse and execute routines
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
#include <parser.h>
#include <amlcode.h>
#include <namesp.h>
#include <debugger.h>
#include "aecommon.h"

#include <stdio.h>



#define _COMPONENT          PARSER
        MODULE_NAME         ("aeexec");



ACPI_GENERIC_OP             *Gbl_ParsedNamespaceRoot;
ACPI_GENERIC_OP             *root;
UINT8                       *AmlPtr;
UINT32                      AmlLength;
UINT8                       *DsdtPtr;
UINT32                      DsdtLength;

DEBUG_REGIONS	            Regions;


/******************************************************************************
 * 
 * FUNCTION:    RegionHandler
 *
 * PARAMETERS:  Standard region handler parameters
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Test handler - Handles some dummy regions via memory that can
 *				be manipulated in Ring 3.
 *
 *****************************************************************************/

ACPI_STATUS 
RegionHandler (
    UINT32                      Function,
    UINT32                      Address,
    UINT32                      BitWidth,
    UINT32                      *Value,
    void                        *Context)
{

    ACPI_OBJECT_INTERNAL	*RegionObject = (ACPI_OBJECT_INTERNAL *)Context;
	UINT32					BaseAddress;
	UINT32					Length;
	BOOLEAN					BufferExists;
	REGION					*RegionElement;
    void                    *BufferValue;
    UINT32                  ByteWidth;
		
    printf ("Received an OpRegion request\n");

	/*
	 * If the object is not a region, simply return
	 */
	if (RegionObject->Region.Type != ACPI_TYPE_Region)
	{
		return AE_OK;
	}

	/*
	 * Find the region's address space and length before searching
	 *	the linked list.
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
		RegionElement = malloc (sizeof(REGION));
		if (!RegionElement)
		{
			return AE_NO_MEMORY;
		}

		RegionElement->Buffer = malloc (Length);
		if (!RegionElement->Buffer)
		{
			free(RegionElement);
			return AE_NO_MEMORY;
		}

		RegionElement->Address = BaseAddress;
		
		RegionElement->Length = Length;
		
		MEMSET(RegionElement->Buffer, 0, Length);

		RegionElement->NextRegion = NULL;

		/*
		 * Increment the number of regions and put this one
		 *	at the head of the list as it will probably get accessed
		 *	more often anyway.
		 */
		Regions.NumberOfRegions += 1;
		
        if (NULL != Regions.RegionList)
        {
            RegionElement->NextRegion = Regions.RegionList->NextRegion;
        }
		
        Regions.RegionList = RegionElement;
	}

	/*
	 * The buffer exists and is pointed to by RegionElement.
     *	We now need to verify the request is valid and perform the operation.
     *
     * NOTE: RegionElement->Length is in bytes, therefore it is multiplied by
     *  the bitwidth of a byte.
	 */ 
    if ((Address + BitWidth) > (RegionElement->Address + (RegionElement->Length * 8)))
    {
        return AE_BUFFER_OVERFLOW;
    }

    /*
     * Get BufferValue to point to the "address" in the buffer
     */
    BufferValue = ((UINT8 *)RegionElement->Buffer + (Address - RegionElement->Address));
    
    /*
     * Calculate the size of the memory copy
     */
    ByteWidth = (BitWidth / 8);

    if (BitWidth % 8)
    {
        ByteWidth += 1;
    }

    /*
     * Perform a read or write to the buffer space
     */
    switch (Function)
    {
    case ADDRESS_SPACE_READ:
        /*
         * Set the pointer Value to whatever is in the buffer
         */
        MEMCPY (Value, BufferValue, ByteWidth);
        break;

    case ADDRESS_SPACE_WRITE:
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
 * FUNCTION:    NotifyHandler 
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
NotifyHandler (
    ACPI_HANDLE                 Device,
    UINT32                      Value,
    void                        *Context)
{

    printf ("**** Notify Handler: Value 0x%x\n", Value);

    switch (Value)
    {
    case 0:
        printf ("**** Method Error: Results not equal\n");
        if (DebugFile)
        {
            OsdPrintf ("**** Method Error: Results not equal\n");
        }
        break;


    case 1:
        printf ("**** Method Error: Incorrect numeric result\n");
        if (DebugFile)
        {
            OsdPrintf ("**** Method Error: Incorrect numeric result\n");
        }
        break;


    case 2:
        printf ("**** Method Error: An operand was overwritten\n");
        if (DebugFile)
        {
            OsdPrintf ("**** Method Error: An operand was overwritten\n");
        }
        break;
    

    default:
        printf ("**** Unknown notify value=%d\n", Value);
        if (DebugFile)
        {
            OsdPrintf ("**** Unknown notify value=%d\n", Value);
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


    Status = AcpiInstallNotifyHandler (ACPI_ROOT_OBJECT, ACPI_SYSTEM_NOTIFY,
                                        NotifyHandler, NULL);
    if (ACPI_FAILURE (Status))
    {
        printf ("Could not install a global notify handler\n");
    }

    for (i = 0; i < 3; i++)
    {
        Status = AcpiRemoveAddressSpaceHandler (Gbl_RootObject, i, RegionHandler);

        /* Install handler at the root object. 
         * TBD: all default handlers should be installed here!
         */
        Status = AcpiInstallAddressSpaceHandler (Gbl_RootObject, i, RegionHandler, NULL, NULL);
        if (ACPI_FAILURE (Status))
        {
            printf ("Could not install an OpRegion handler\n");
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




/******************************************************************************
 * 
 * FUNCTION:    AdSecondPassParse
 *
 * PARAMETERS:  Root            - Root of the parse tree
 *
 * RETURN:      None
 *
 * DESCRIPTION: Need to wait until second pass to parse the control methods
 *
 *****************************************************************************/

ACPI_STATUS
AdSecondPassParse (
    ACPI_GENERIC_OP         *Root)
{
    ACPI_GENERIC_OP         *Op = Root;
    ACPI_DEFERRED_OP        *Method;
    ACPI_GENERIC_OP         *SearchOp;
    ACPI_GENERIC_OP         *StartOp;
    ACPI_STATUS             Status = AE_OK;
    UINT32                  BaseAmlOffset;


    /* Walk entire tree */

    while (Op)
    {
        /* We are looking for control methods */

        if (Op->Opcode == AML_MethodOp)
        {
            Method = (ACPI_DEFERRED_OP *) Op;
            Status = PsParseAml (Op, Method->Body, Method->BodyLength);

          
            BaseAmlOffset = (Method->Value.Arg)->AmlOffset + 1;
            StartOp = (Method->Value.Arg)->Next;
            SearchOp = StartOp;

            while (SearchOp)
            {
                SearchOp->AmlOffset += BaseAmlOffset;
                SearchOp = PsGetDepthNext (StartOp, SearchOp);
            }

        }

        if (Op->Opcode == AML_RegionOp)
        {
            /* TBD: this isn't quite the right thing to do! */

            // Method = (ACPI_DEFERRED_OP *) Op;
            // Status = PsParseAml (Op, Method->Body, Method->BodyLength);
        }

        if (ACPI_FAILURE (Status))
        {
            return Status;
        }

        Op = PsGetDepthNext (Root, Op);
    }

    return Status;
}



/******************************************************************************
 * 
 * FUNCTION:    AdGetTables
 *
 * PARAMETERS:  Filename        - Optional filename
 *
 * RETURN:      None
 *
 * DESCRIPTION: Get the ACPI tables from either memory or a file
 *
 *****************************************************************************/

ACPI_STATUS
AdGetTables (
    char                    *Filename)
{
    ACPI_STATUS             Status;


    Status = DbLoadAcpiTable (Filename);

    return Status;
}




