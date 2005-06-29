
/******************************************************************************
 * 
 * Module Name: iresolve - AML Interpreter object resolution
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

#define __IRESOLVE_C__

#include "acpi.h"
#include "amlcode.h"
#include "parser.h"
#include "dispatch.h"
#include "interp.h"
#include "namesp.h"
#include "tables.h"
#include "events.h"


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("iresolve");



/*****************************************************************************
 * 
 * FUNCTION:    AcpiAmlGetFieldUnitValue
 *
 * PARAMETERS:  *FieldDesc          - Pointer to a FieldUnit
 *              *ResultDesc         - Pointer to an empty descriptor
 *                                    which will become a Number
 *                                    containing the field's value.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve the value from a FieldUnit
 *
 ****************************************************************************/

ACPI_STATUS
AcpiAmlGetFieldUnitValue (
    ACPI_OBJECT_INTERNAL    *FieldDesc, 
    ACPI_OBJECT_INTERNAL    *ResultDesc)
{
    ACPI_STATUS             Status = AE_OK;
    UINT32                  Mask;
    UINT8                   *Location = NULL;
    BOOLEAN                 Locked = FALSE;


    FUNCTION_TRACE ("AmlGetFieldUnitValue");


    if (!FieldDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: Internal error - null field pointer\n"));
        Status = AE_AML_NO_OPERAND;
    }

    else if (!FieldDesc->FieldUnit.Container)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: Internal error - null container pointer\n"));
        Status = AE_AML_INTERNAL;
    }

    else if (ACPI_TYPE_BUFFER != FieldDesc->FieldUnit.Container->Common.Type)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: Internal error - container is not a Buffer\n"));
        Status = AE_AML_OPERAND_TYPE;
    }

    else if (FieldDesc->FieldUnit.Sequence
                != FieldDesc->FieldUnit.Container->Buffer.Sequence)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: Internal error - stale Buffer [%lx != %lx]\n",
                        FieldDesc->FieldUnit.Sequence,
                        FieldDesc->FieldUnit.Container->Buffer.Sequence));
        Status = AE_AML_INTERNAL;
    }

    else if (!ResultDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: Internal error - null result pointer\n"));
        Status = AE_AML_INTERNAL;
    }

    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


        /* Get the global lock if needed */

    Locked = AcpiAmlAcquireGlobalLock (FieldDesc->FieldUnit.LockRule);

    /* Field location is (base of buffer) + (byte offset) */

    Location = FieldDesc->FieldUnit.Container->Buffer.Pointer
                + FieldDesc->FieldUnit.Offset;

    /* Construct Mask with as many 1 bits as the field width 
     * 
     * NOTE: Only the bottom 5 bits are valid for a shift operation, so
     *  special care must be taken for any shift greater than 31 bits. 
     *
     * TBD: [Unhandled] Fields greater than 32-bits will not work.
     */

    if (FieldDesc->FieldUnit.Length < 32)
    {
        Mask = ((UINT32) 1 << FieldDesc->FieldUnit.Length) - (UINT32) 1;
    }
    else
    {
        Mask = 0xFFFFFFFF;
    }

    ResultDesc->Number.Type = (UINT8) ACPI_TYPE_NUMBER;

    /* Get the 32 bit value at the location */

    STORE32TO32 (&ResultDesc->Number.Value, Location);

    /* Shift the 32-bit word containing the field, and mask off the resulting value */

    ResultDesc->Number.Value = (ResultDesc->Number.Value >> FieldDesc->FieldUnit.BitOffset) & Mask;

    DEBUG_PRINT (ACPI_INFO, ("** Read from buffer %p byte %ld bit %d width %d addr %p mask %08lx val %08lx\n",
                    FieldDesc->FieldUnit.Container->Buffer.Pointer,
                    FieldDesc->FieldUnit.Offset,
                    FieldDesc->FieldUnit.BitOffset,
                    FieldDesc->FieldUnit.Length,
                    Location, Mask, ResultDesc->Number.Value));

    /* Release global lock if we acquired it earlier */

    AcpiAmlReleaseGlobalLock (Locked);

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AcpiAmlResolveToValue
 *
 * PARAMETERS:  **StackPtr          - Points to entry on ObjStack, which can 
 *                                    be either an (ACPI_OBJECT_INTERNAL *)
 *                                    or an ACPI_HANDLE.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert Reference entries on ObjStack to Rvalues
 *
 ****************************************************************************/

ACPI_STATUS
AcpiAmlResolveToValue (
    ACPI_OBJECT_INTERNAL    **StackPtr)
{
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE_PTR ("AmlResolveToValue", StackPtr);


    if (!StackPtr || !*StackPtr)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlResolveToValue: Internal error - null pointer\n"));
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }


    /* 
     * The entity pointed to by the StackPtr can be either
     * 1) A valid ACPI_OBJECT_INTERNAL, or
     * 2) A NAME_TABLE_ENTRY (nte)
     */

    if (VALID_DESCRIPTOR_TYPE (*StackPtr, DESC_TYPE_ACPI_OBJ))       
    {

        Status = AcpiAmlResolveObjectToValue (StackPtr);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    /* 
     * Object on the stack may have changed if AcpiAmlResolveObjectToValue() was called
     * (i.e., we can't use an _else_ here.)
     */

    if (VALID_DESCRIPTOR_TYPE (*StackPtr, DESC_TYPE_NTE))       
    {
        Status = AcpiAmlResolveEntryToValue ((NAME_TABLE_ENTRY **) StackPtr);
    }


    DEBUG_PRINT (ACPI_INFO, ("AmlResolveToValue: Returning resolved object %p\n", *StackPtr));

    return_ACPI_STATUS (Status);
}
    
