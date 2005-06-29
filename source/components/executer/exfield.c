/******************************************************************************
 * 
 * Module Name: iefield - ACPI AML (p-code) execution - field manipulation
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


#define __IEFIELD_C__

#include <acpi.h>
#include <dispatch.h>
#include <interp.h>
#include <amlcode.h>
#include <namesp.h>
#include <hardware.h>
#include <events.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("iefield");




/*****************************************************************************
 * 
 * FUNCTION:    AmlSetupField
 *
 * PARAMETERS:  *ObjDesc            - Field to be read or written
 *              *RgnDesc            - Region containing field
 *              FieldBitWidth       - Field Width in bits (8, 16, or 32)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Common processing for AmlReadField and AmlWriteField
 *
 *  ACPI SPECIFICATION REFERENCES:
 *  16.2.4.3    Each of the Type1Opcodes is defined as specified in in-line
 *              comments below. For each one, use the following definitions.
 *  16.2.4.2    DefBitField     :=  BitFieldOp      SourceBuff  BitIndex    Destination
 *  16.2.4.2    DefByteField    :=  ByteFieldOp     SourceBuff  ByteIndex   Destination
 *  16.2.4.2    DefCreateField  :=  CreateFieldOp   SourceBuff  BitIndex    NumBits     NameString
 *  16.2.4.2    DefDWordField   :=  DWordFieldOp    SourceBuff  ByteIndex   Destination
 *  16.2.4.2    DefWordField    :=  WordFieldOp     SourceBuff  ByteIndex   Destination
 *  16.2.4.2    BitIndex        :=  TermArg=>Integer
 *  16.2.4.2    ByteIndex       :=  TermArg=>Integer
 *  16.2.4.2    Destination     :=  NameString
 *  16.2.4.2    NumBits         :=  TermArg=>Integer
 *  16.2.4.2    SourceBuff      :=  TermArg=>Buffer
 *
 ****************************************************************************/

ACPI_STATUS
AmlSetupField (
    ACPI_OBJECT_INTERNAL    *ObjDesc, 
    ACPI_OBJECT_INTERNAL    *RgnDesc, 
    INT32                   FieldBitWidth)
{
    ACPI_STATUS             Status = AE_OK;
    INT32                   FieldByteWidth;


    FUNCTION_TRACE ("AmlSetupField");


    /* Parameter validation */

    if (!ObjDesc || !RgnDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlSetupField: Internal error - null handle\n"));
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }

    if (ACPI_TYPE_Region != RgnDesc->Common.Type)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlSetupField: Needed Region, found type %x %s\n",
                        RgnDesc->Common.Type, CmGetTypeName (RgnDesc->Common.Type)));
        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    }


    /* Init and validate Field width */
    
    FieldByteWidth = DIV_8 (FieldBitWidth);     /*  possible values are 1, 2, 4 */

    if ((FieldBitWidth != 8) && 
        (FieldBitWidth != 16) && 
        (FieldBitWidth != 32))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlSetupField: Internal error - bad width %d\n", FieldBitWidth));
        return_ACPI_STATUS (AE_AML_OPERAND_VALUE);
    }


    /* 
     * If the address and length have not been previously evaluated,
     * evaluate them and save the results.
     */
    if (!(RgnDesc->Region.RegionFlags & REGION_AGRUMENT_DATA_VALID))
    {

        Status = DsGetRegionArguments (RgnDesc);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }


    /* 
     * If (offset rounded up to next multiple of field width)
     * exceeds region length, indicate an error.
     */

    if (RgnDesc->Region.Length <
       (ObjDesc->Field.Offset & ~((UINT32) FieldByteWidth - 1)) + FieldByteWidth)
    {
        /*  
         * Offset rounded up to next multiple of field width
         * exceeds region length, indicate an error
         */

        DUMP_STACK_ENTRY (RgnDesc);
        DUMP_STACK_ENTRY (ObjDesc);

        DEBUG_PRINT (ACPI_ERROR,
                ("AmlSetupField: Operation at %08lX width %d bits exceeds len %08lX field=%p region=%p\n",
                ObjDesc->Field.Offset, FieldBitWidth, RgnDesc->Region.Length, ObjDesc, RgnDesc));

        return_ACPI_STATUS (AE_AML_REGION_LIMIT);
    }

    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlAccessNamedField
 *
 * PARAMETERS:  Mode                - ACPI_READ or ACPI_WRITE
 *              NamedField          - Handle for field to be accessed
 *              *Buffer             - Value(s) to be read or written
 *              BufferLength          - Number of bytes to transfer
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read or write a named field
 *
 ****************************************************************************/

ACPI_STATUS
AmlAccessNamedField (
    INT32                   Mode, 
    ACPI_HANDLE             NamedField, 
    void                    *Buffer,
    UINT32                  BufferLength)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    ACPI_STATUS             Status = AE_OK;
    BOOLEAN                 Locked = FALSE;
    UINT32                  BitGranularity = 0;
    UINT32                  ByteGranularity;
    UINT32                  DatumLength;
    UINT32                  ActualByteLength;
    UINT32                  ByteFieldLength;


    FUNCTION_TRACE_PTR ("AmlAccessNamedField", NamedField);


    /* Get the attached field object */

    ObjDesc = NsGetAttachedObject (NamedField);
    if (!ObjDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlAccessNamedField: Internal error - null value pointer\n"));
        return_ACPI_STATUS (AE_AML_INTERNAL);
    }

    /* Check the type */

    if (INTERNAL_TYPE_DefField != NsGetType (NamedField))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlAccessNamedField: Name %4.4s type %x is not a defined field\n",
                        &(((NAME_TABLE_ENTRY *) NamedField)->Name), NsGetType (NamedField)));
        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    }

    /* ObjDesc valid and NamedField is a defined field  */

    DEBUG_PRINT (ACPI_INFO, ("AccessNamedField: Obj=%p Type=%x Buf=%p Len=%x\n",
                    ObjDesc, ObjDesc->Common.Type, Buffer, BufferLength));
    DEBUG_PRINT (ACPI_INFO, ("AccessNamedField: Mode=%d FieldLen=%d, BitOffset=%d\n",
                    Mode, ObjDesc->FieldUnit.Length, ObjDesc->FieldUnit.BitOffset));
    DUMP_ENTRY (NamedField, ACPI_INFO);


    /* Double-check that the attached object is also a field */

    if (INTERNAL_TYPE_DefField != ObjDesc->Common.Type)
    {
        DEBUG_PRINT (ACPI_ERROR, (
                "AmlAccessNamedField: Internal error - Name %4.4s type %x does not match value-type %x at %p\n",
                &(((NAME_TABLE_ENTRY *) NamedField)->Name), NsGetType (NamedField), ObjDesc->Common.Type, ObjDesc));
        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    }


    /* Granularity was decoded from the field access type (AnyAcc will be the same as ByteAcc) */

    BitGranularity = ObjDesc->FieldUnit.Granularity;
    ByteGranularity = DIV_8 (BitGranularity);

    /* Check if request is too large for the field, and silently truncate if necessary */

    /* TBD: should an error be returned in this case? */

    ByteFieldLength = (UINT32) DIV_8 (ObjDesc->FieldUnit.Length + 7);


    ActualByteLength = BufferLength;
    if (BufferLength > ByteFieldLength)
    {
        ActualByteLength = ByteFieldLength;

        DEBUG_PRINT (ACPI_INFO, ("AmlAccessNamedField: Byte length too large, truncated to %x\n",
                           ActualByteLength));
    }


    /* Convert byte count to datum count, round up if necessary */

    DatumLength = (ActualByteLength + (ByteGranularity-1)) / ByteGranularity;

    DEBUG_PRINT (ACPI_INFO, ("ByteLen=%x, DatumLen=%x, BitGran=%x, ByteGran=%x\n",
                    ActualByteLength, DatumLength, BitGranularity, ByteGranularity));


    /* Get the global lock if needed */

    Locked = AmlAcquireGlobalLock (ObjDesc->FieldUnit.LockRule);


    /* Perform the actual read or write of the buffer */

    switch (Mode)
    {
    case ACPI_READ:

        Status = AmlReadField (ObjDesc, Buffer, BufferLength, ActualByteLength, DatumLength,
                                BitGranularity, ByteGranularity);
        break;


    case ACPI_WRITE:

        Status = AmlWriteField (ObjDesc, Buffer, BufferLength, ActualByteLength, DatumLength,
                                BitGranularity, ByteGranularity);
        break;


    default:

        DEBUG_PRINT (ACPI_ERROR, ("AccessNamedField: Unknown I/O Mode: %X\n", Mode));
        Status = AE_BAD_PARAMETER;
        break;
    }



    /* Release global lock if we acquired it earlier */

    AmlReleaseGlobalLock (Locked);

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlSetNamedFieldValue
 *
 * PARAMETERS:  NamedField          - Handle for field to be set
 *              Buffer              - Bytes to be stored
 *              BufferLength        - Number of bytes to be stored
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store the given value into the field
 *
 ****************************************************************************/

ACPI_STATUS
AmlSetNamedFieldValue (
    ACPI_HANDLE             NamedField,
    void                    *Buffer,
    UINT32                  BufferLength)
{
    ACPI_STATUS             Status;


    FUNCTION_TRACE_PTR ("AmlSetNamedFieldValue", NamedField);


    if (!NamedField)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlSetNamedFieldValue: Internal error - null handle\n"));
        return_ACPI_STATUS (AE_AML_INTERNAL);
    }

    Status = AmlAccessNamedField (ACPI_WRITE, NamedField, Buffer, BufferLength);
    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlGetNamedFieldValue
 *
 * PARAMETERS:  NamedField          - Handle for field to be read
 *              *Buffer             - Where to store value read from field
 *              BufferLength        - Max length to read
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve the value of the given field
 *
 ****************************************************************************/

ACPI_STATUS
AmlGetNamedFieldValue (
    ACPI_HANDLE             NamedField, 
    void                    *Buffer,
    UINT32                  BufferLength)
{
    ACPI_STATUS             Status;


    FUNCTION_TRACE_PTR ("AmlGetNamedFieldValue", NamedField);


    if ((!NamedField) || (!Buffer))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetNamedFieldValue: Internal error - null parameter\n"));
        return_ACPI_STATUS (AE_AML_INTERNAL);
    }

    Status = AmlAccessNamedField (ACPI_READ, NamedField, Buffer, BufferLength);
    return_ACPI_STATUS (Status);
}
  
