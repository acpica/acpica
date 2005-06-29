
/******************************************************************************
 * 
 * Module Name: istorent - AML Interpreter object store support, store to NTE
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

#define __ISTORENT_C__

#include <acpi.h>
#include <parser.h>
#include <dispatch.h>
#include <interp.h>
#include <amlcode.h>
#include <namesp.h>
#include <tables.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("istorent");



/*****************************************************************************
 * 
 * FUNCTION:    AmlStoreObjectToNte
 *
 * PARAMETERS:  *ValDesc            - Value to be stored
 *              *Entry              - Named object to recieve the value
 *              
 * RETURN:      Status
 *
 * DESCRIPTION: Store the object to the named object.
 *
 *              The Assignment of an object to a named object is handled here
 *              The val passed in will replace the current value (if any)
 *              with the input value.
 *
 *              When storing into an object the data is converted to the
 *              target object type then stored in the object.  This means
 *              that the target object type (for an initialized target) will
 *              not be changed by a store operation.
 *
 *              NOTE: the global lock is acquired early.  This will result
 *              in the global lock being held a bit longer.  Also, if the
 *              function fails during set up we may get the lock when we
 *              don't really need it.  I don't think we care.
 *
 ****************************************************************************/

ACPI_STATUS
AmlStoreObjectToNte (
    ACPI_OBJECT_INTERNAL    *ValDesc,
    NAME_TABLE_ENTRY        *Entry)
{
    ACPI_STATUS             Status = AE_OK;
    UINT8                   *Buffer = NULL;
    UINT32                  Length = 0;
    UINT32                  Mask;
    UINT32                  NewValue;
    BOOLEAN                 Locked = FALSE;
    UINT8                   *Location=NULL;
    ACPI_OBJECT_INTERNAL    *DestDesc;
    ACPI_OBJECT_TYPE        DestinationType = ACPI_TYPE_Any;


    FUNCTION_TRACE ("AmlStoreObjectToNte");

    DEBUG_PRINT (ACPI_INFO, ("entered AmlStoreObjectToNte: NTE=%p, Obj=%p\n", 
                    Entry, ValDesc));

    /*
     *  Assuming the parameters are valid!!!
     */
    ACPI_ASSERT((Entry) && (ValDesc));

    DestinationType = NsGetType (Entry);

    DEBUG_PRINT (ACPI_INFO, ("AmlStoreObjectToNte: Storing %s into %s\n",
                    CmGetTypeName (ValDesc->Common.Type),
                    CmGetTypeName (DestinationType)));

    /*
     *  First ensure we have a value that can be stored in the target
     */
    switch (DestinationType) 
    {
        /* Type of Name's existing value */

    case INTERNAL_TYPE_Alias: 

        /* 
         *  Aliases are resolved by AmlPrepOperands
         */

        DEBUG_PRINT (ACPI_WARN, ("AmlStoreObjectToNte: Store into Alias - should never happen\n"));
        Status = AE_AML_INTERNAL;
        break;


    case INTERNAL_TYPE_BankField:
    case INTERNAL_TYPE_IndexField:
    case ACPI_TYPE_FieldUnit:
    case ACPI_TYPE_Number:

        /*
         *  These cases all require only number values or values that
         *  can be converted to numbers.
         *
         *  If value is not a Number, try to resolve it to one.
         */

        if (ValDesc->Common.Type != ACPI_TYPE_Number) 
        {
            /*
             *  Initially not a number, convert
             */
            Status = AmlResolveToValue (&ValDesc);
            if ((Status == AE_OK) &&
                (ValDesc->Common.Type != ACPI_TYPE_Number)) 
            {
                /*
                 *  Conversion successful but still not a number
                 */
                DEBUG_PRINT (ACPI_ERROR, ("AmlStoreObjectToNte: Value assigned to %s must be Number, not %s\n",
                                CmGetTypeName (DestinationType),
                                CmGetTypeName (ValDesc->Common.Type)));
                Status = AE_AML_OPERAND_TYPE;
            }
        }

        break;

    case ACPI_TYPE_String:
    case ACPI_TYPE_Buffer:
    case INTERNAL_TYPE_DefField:

        /* 
         *  Storing into a Field in a region or into a buffer or into
         *  a string all is essentially the same.
         *
         *  If value is not a valid type, try to resolve it to one.
         */

        if ((ValDesc->Common.Type != ACPI_TYPE_Number) && 
            (ValDesc->Common.Type != ACPI_TYPE_Buffer) &&
            (ValDesc->Common.Type != ACPI_TYPE_String)) 
        {
            /*
             *  Initially not a valid type, convert
             */
            Status = AmlResolveToValue (&ValDesc);
            if ((Status == AE_OK) &&
                (ValDesc->Common.Type != ACPI_TYPE_Number) && 
                (ValDesc->Common.Type != ACPI_TYPE_Buffer) &&
                (ValDesc->Common.Type != ACPI_TYPE_String)) 
            {
                /*
                 *  Conversion successful but still not a valid type
                 */
                DEBUG_PRINT (ACPI_ERROR, ("AmlStoreObjectToNte: Assign wrong type %s to %s (must be type Num/Str/Buf)\n",
                                CmGetTypeName (ValDesc->Common.Type),
                                CmGetTypeName (DestinationType)));
                Status = AE_AML_OPERAND_TYPE;
            }
        }
        break;


    case ACPI_TYPE_Package: 

        /*
         *  BUGBUG: Not real sure what to do here
         */
        Status = AE_NOT_IMPLEMENTED;
        break;


    default: 
        
        /* 
         * All other types than Alias and the various Fields come here.
         * Store ValDesc as the new value of the Name, and set
         * the Name's type to that of the value being stored in it.
         * ValDesc reference count is incremented by AttachObject.
         */

        Status = NsAttachObject (Entry, ValDesc, ValDesc->Common.Type);

        DEBUG_PRINT (ACPI_INFO, ("AmlStoreObjectToNte: Store %s into %s via Attach\n",
                            CmGetTypeName (ValDesc->Common.Type),
                            CmGetTypeName (DestinationType)));
    
        goto CleanUpAndBailOut;
        break;
    }

    /* Exit now if failure above */

    if (Status != AE_OK)
    {
        goto CleanUpAndBailOut;
    }

    /*
     *  Get descriptor for object attached to NTE
     */
    DestDesc = NsGetAttachedObject (Entry);
    if (!DestDesc)
    {
        /*
         *  There is no existing object attached to this NTE
         */
        DEBUG_PRINT (ACPI_ERROR, ("AmlStoreObjectToNte: Internal error - no destination object for %4.4s type %d\n",
                        &Entry->Name, DestinationType));
        Status = AE_AML_INTERNAL;
        goto CleanUpAndBailOut;
    }

    /* 
     *  Make sure the destination Object is the same as the NTE
     */
    if (DestDesc->Common.Type != (UINT8) DestinationType)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlStoreObjectToNte: Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                        &Entry->Name, NsGetType (Entry), 
                        DestDesc->Common.Type, DestDesc));
        Status = AE_AML_INTERNAL;
        goto CleanUpAndBailOut;
    }

    /*
     * Everything is ready to execute now,  We have 
     * a value we can handle, just perform the update
     */

    switch (DestinationType) 
    {
        /* Type of Name's existing value */

    case INTERNAL_TYPE_BankField:

        /*
         * Get the global lock if needed
         */
        Locked = AmlAcquireGlobalLock (DestDesc->BankField.LockRule);

        /*
         *  Set Bank value to select proper Bank
         *  Perform the update (Set Bank Select)
         */

        Status = AmlSetNamedFieldValue (DestDesc->BankField.BankSelect,
                                    &DestDesc->BankField.Value,
                                    sizeof (DestDesc->BankField.Value));
        if (Status == AE_OK)
        {
            /* Set bank select successful, set data value  */
        
            Status = AmlSetNamedFieldValue (DestDesc->BankField.BankSelect,
                                           &ValDesc->BankField.Value,
                                           sizeof (ValDesc->BankField.Value));
        }

        break;


    case INTERNAL_TYPE_DefField:

        /*
         * Get the global lock if needed
         */
        Locked = AmlAcquireGlobalLock (ValDesc->Field.LockRule);

        /*
         *  Perform the update
         */
       
        switch (ValDesc->Common.Type)
        {
        case ACPI_TYPE_Number:
            Buffer = (UINT8 *) &ValDesc->Number.Value;
            Length = sizeof (ValDesc->Number.Value);
            break;

        case ACPI_TYPE_Buffer:
            Buffer = (UINT8 *) ValDesc->Buffer.Pointer;
            Length = ValDesc->Buffer.Length; 
            break;

        case ACPI_TYPE_String:
            Buffer = (UINT8 *) ValDesc->String.Pointer;
            Length = ValDesc->String.Length; 
            break;
        }

        Status = AmlSetNamedFieldValue (Entry, Buffer, Length);
        break;      /* Global Lock released below   */


    case ACPI_TYPE_String:

        /*
         *  Perform the update
         */
        
        switch (ValDesc->Common.Type)
        {
        case ACPI_TYPE_Number:
            Buffer = (UINT8 *) &ValDesc->Number.Value;
            Length = sizeof (ValDesc->Number.Value);
            break;

        case ACPI_TYPE_Buffer:
            Buffer = (UINT8 *) ValDesc->Buffer.Pointer;
            Length = ValDesc->Buffer.Length; 
            break;

        case ACPI_TYPE_String:
            Buffer = (UINT8 *) ValDesc->String.Pointer;
            Length = ValDesc->String.Length; 
            break;
        }

        /*
         *  Setting a string value replaces the old string
         */

        if (Length < DestDesc->String.Length)
        {
            /*
             *  Zero fill, not willing to do pointer arithmetic for
             *  archetecture independance.  Just clear the whole thing
             */
            MEMSET(DestDesc->String.Pointer, 0, DestDesc->String.Length);
            MEMCPY(DestDesc->String.Pointer, Buffer, Length);
        }
        else
        {
            /*
             *  Free the current buffer, then allocate a buffer
             *  large enough to hold the value
             */
            if ( DestDesc->String.Pointer &&
                !TbSystemTablePointer (DestDesc->String.Pointer))
            {
                /*
                 *  Only free if not a pointer into the DSDT
                 */

                CmFree(DestDesc->String.Pointer);
            }

            DestDesc->String.Pointer = CmAllocate ((ACPI_SIZE) (Length + 1));
            DestDesc->String.Length = Length;

			if (!DestDesc->String.Pointer)
			{
				Status = AE_NO_MEMORY;
				goto CleanUpAndBailOut;
			}

            MEMCPY(DestDesc->String.Pointer, Buffer, Length);
        }
        break;


    case ACPI_TYPE_Buffer:

        /*
         *  Perform the update to the buffer
         */
        
        switch (ValDesc->Common.Type)
        {
        case ACPI_TYPE_Number:
            Buffer = (UINT8 *) &ValDesc->Number.Value;
            Length = sizeof (ValDesc->Number.Value);
            break;

        case ACPI_TYPE_Buffer:
            Buffer = (UINT8 *) ValDesc->Buffer.Pointer;
            Length = ValDesc->Buffer.Length; 
            break;

        case ACPI_TYPE_String:
            Buffer = (UINT8 *) ValDesc->String.Pointer;
            Length = ValDesc->String.Length; 
            break;
        }

        /*
         *  Buffer is a static allocation,
         *  only place what will fit in the buffer.
         */
        if (Length <= DestDesc->Buffer.Length)
        {
            /*
             *  Zero fill first, not willing to do pointer arithmetic for
             *  archetecture independence.  Just clear the whole thing
             */
            MEMSET(DestDesc->Buffer.Pointer, 0, DestDesc->Buffer.Length);
            MEMCPY(DestDesc->Buffer.Pointer, Buffer, Length);
        }
        else
        {
            /*
             *  truncate, copy only what will fit
             */
            MEMCPY(DestDesc->Buffer.Pointer, Buffer, DestDesc->Buffer.Length);
            DEBUG_PRINT (ACPI_INFO, ("AmlStoreObjectToNte: Truncating src buffer from %d to %d\n", 
                            Length, DestDesc->Buffer.Length));
        }
        break;


    case INTERNAL_TYPE_IndexField:
            
        /*
         * Get the global lock if needed
         */
        Locked = AmlAcquireGlobalLock (DestDesc->IndexField.LockRule);

        /*
         *  Set Index value to select proper Data register
         *  perform the update (Set index)
         */

        Status = AmlSetNamedFieldValue (DestDesc->IndexField.Index,
                                       &DestDesc->IndexField.Value,
                                       sizeof (DestDesc->IndexField.Value));
        
        DEBUG_PRINT (ACPI_INFO, ("AmlStoreObjectToNte: IndexField: set index returned %s\n",
                         CmFormatException (Status)));
        
        if (AE_OK == Status)
        {
            /* set index successful, next set Data value */
        
            Status = AmlSetNamedFieldValue (DestDesc->IndexField.Data,
                                           &ValDesc->Number.Value, sizeof (ValDesc->Number.Value));
            DEBUG_PRINT (ACPI_INFO, ("AmlStoreObjectToNte: IndexField: set data returned %s\n",
                            CmFormatException (Status)));
        }
        break;


    case ACPI_TYPE_FieldUnit:

        if ((!DestDesc->FieldUnit.Container ||
            ACPI_TYPE_Buffer != DestDesc->FieldUnit.Container->Common.Type ||
            DestDesc->FieldUnit.Sequence != DestDesc->FieldUnit.Container->Buffer.Sequence))
        {
            DUMP_PATHNAME (Entry, "AmlStoreObjectToNte: FieldUnit: Bad container in ", ACPI_ERROR, _COMPONENT);
            DUMP_ENTRY (Entry, ACPI_ERROR);
            DEBUG_PRINT (ACPI_ERROR, ("Container: %p", DestDesc->FieldUnit.Container));

            if (DestDesc->FieldUnit.Container)
            {
                DEBUG_PRINT_RAW (ACPI_ERROR, (" Type %d, FuSeq %x BufSeq %x",
                                    DestDesc->FieldUnit.Container->Common.Type,
                                    DestDesc->FieldUnit.Sequence,
                                    DestDesc->FieldUnit.Container->Buffer.Sequence));
            }
            DEBUG_PRINT_RAW (ACPI_ERROR, ("\n"));

            Status = AE_AML_INTERNAL;
            goto CleanUpAndBailOut;
        }

        /*
         *  Get the global lock if needed
         */
        Locked = AmlAcquireGlobalLock (DestDesc->FieldUnit.LockRule);

        /*
         * TBD: REMOVE this limitation
         *  Make sure the operation is within the limits of our implementation
         *  this is not a Spec limitation!!   BUGBUG
         */
        if (DestDesc->FieldUnit.Length + DestDesc->FieldUnit.BitOffset > 32)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlStoreObjectToNte: FieldUnit: Implementation limitation - Field exceeds UINT32\n"));
            Status = AE_NOT_IMPLEMENTED;
            goto CleanUpAndBailOut;
        }
        
        /* Field location is (base of buffer) + (byte offset) */
        
        Location = DestDesc->FieldUnit.Container->Buffer.Pointer
                        + DestDesc->FieldUnit.Offset;
        
        /* 
         * Construct Mask with 1 bits where the field is,
         * 0 bits elsewhere
         */
        Mask = ((UINT32) 1 << DestDesc->FieldUnit.Length) - ((UINT32)1
                            << DestDesc->FieldUnit.BitOffset);

        DEBUG_PRINT (TRACE_EXEC, ("** Store %lx in buffer %p byte %ld bit %d width %d addr %p mask %08lx\n",
                        ValDesc->Number.Value, DestDesc->FieldUnit.Container->Buffer.Pointer,
                        DestDesc->FieldUnit.Offset, DestDesc->FieldUnit.BitOffset,
                        DestDesc->FieldUnit.Length,Location, Mask));

        /* Zero out the field in the buffer */
        
        STORE32TO32 (&NewValue, Location);
        NewValue &= ~Mask;

        /* 
         * Shift and mask the new value into position,
         * and or it into the buffer.
         */
        NewValue |= (ValDesc->Number.Value << DestDesc->FieldUnit.BitOffset) & Mask;
        
        /* Store back the value */

        STORE32TO32 (Location, &NewValue);

        DEBUG_PRINT (TRACE_EXEC, ("New Field value %08lx\n", NewValue));
        break;


    case ACPI_TYPE_Number:

        DestDesc->Number.Value = ValDesc->Number.Value;
        break;


    case ACPI_TYPE_Package:

        /*
         *  BUGBUG: Not real sure what to do here
         */
        Status = AE_NOT_IMPLEMENTED;
        break;


    default: 
            
        /* 
         * All other types than Alias and the various Fields come here.
         * Store ValDesc as the new value of the Name, and set
         * the Name's type to that of the value being stored in it.
         * ValDesc reference count is incremented by AttachObject.
         */

        DEBUG_PRINT (ACPI_WARN, ("AmlStoreObjectToNte: Store into %s not implemented\n",
                        CmGetTypeName (NsGetType (Entry))));
    
        Status = AE_NOT_IMPLEMENTED;
        break;
    }



CleanUpAndBailOut:

    /*
     * Release global lock if we acquired it earlier
     */
    AmlReleaseGlobalLock (Locked);

    return_ACPI_STATUS (Status);
}


