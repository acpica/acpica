
/******************************************************************************
 * 
 * Module Name: iexecute - ACPI AML (p-code) execution, exec/store routine
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

#define __IEXECUTE_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>


#define _THIS_MODULE        "iexecute.c"
#define _COMPONENT          INTERPRETER



/******************************************************************************
 * 
 * FUNCTION:    AmlExecute
 *
 * PARAMETERS:  Pcode               - Pointer to the pcode stream
 *              PcodeLength         - Length of pcode that comprises the method
 *              **Params            - List of parameters to pass to method, 
 *                                    terminated by NULL. Params itself may be 
 *                                    NULL if no parameters are being passed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a control method
 *
 *****************************************************************************/

ACPI_STATUS
AmlExecute (
    UINT8                   *Pcode, 
    UINT32                  PcodeLength, 
    ACPI_OBJECT_INTERNAL    **Params)
{
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecute");


    /* Prepare the package stack */

    Status = AmlPrepExec (Pcode, PcodeLength);
    if (ACPI_FAILURE (Status))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecute: Exec Stack Overflow\n"));
        goto Cleanup;
    }

    /* Push new frame on Method stack */
    
    Status = AmlMthStackPush (Params);
    if (ACPI_FAILURE (Status))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecute: Could not push Method Stack\n"));

        /* TBD: do we need to pop the package stack here? */

        goto Cleanup;
    }


    /* This is where we really execute the method */

    while ((Status = AmlDoCode (IMODE_Execute)) == AE_OK)
    {;}


    /* 
     * Normal exit is with Status == AE_RETURN_VALUE when a ReturnOp has been executed,
     * or with Status == AE_PENDING at end of AML block (end of Method code)
     */

    if (AE_PENDING == Status)
    {
        Status = AmlPkgPopExec ();            /* package stack -- inverse of AmlPrepExec() */
    }

    else
    {
        if (AE_RETURN_VALUE == Status)
        {
            DEBUG_PRINT (ACPI_INFO, ("Method returned: \n"));
            DUMP_STACK_ENTRY (AmlObjStackGetValue (STACK_TOP));
            DEBUG_PRINT (ACPI_INFO, (" at stack level %d\n", AmlObjStackLevel()));
        }

        AmlPkgPopExec ();            /* package stack -- inverse of AmlPrepExec() */
    }

    AmlMthStackPop ();         /* pop our frame off method stack */


    if (AmlObjStackLevel())
    {
        DEBUG_PRINT (ACPI_INFO, ("AmlExecute: Obj TOS at exit=%d\n",
                        AmlObjStackLevel()));
    }


Cleanup:
    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecStore
 *
 * PARAMETERS:  *ValDesc            - Value to be stored
 *              *DestDesc           - Where to store it -- must be an (ACPI_HANDLE)
 *                                    or an ACPI_OBJECT_INTERNAL of type Lvalue;
 *                                    if the latter the descriptor will be 
 *                                    either reused or deleted.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store the value described by ValDesc into the location
 *              described by DestDesc.  Called by various interpreter
 *              functions to store the result of an operation into
 *              the destination operand.
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecStore (
    ACPI_OBJECT_INTERNAL    *ValDesc, 
    ACPI_OBJECT_INTERNAL    *DestDesc)
{
    ACPI_HANDLE             TempHandle;
    ACPI_STATUS             Status = AE_OK;
    BOOLEAN                 Locked = FALSE;
    ACPI_OBJECT_INTERNAL    *DeleteDestDesc = NULL;
    UINT8                   *Location=NULL;
    UINT32                  Mask;



    FUNCTION_TRACE ("AmlExecStore");

    DEBUG_PRINT (ACPI_INFO, ("entered AmlExecStore: Val=%p, Dest=%p\n", 
                    ValDesc, DestDesc));


    /* Validate parameters */

    if (!ValDesc || !DestDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore: Internal error - null pointer\n"));
        return_ACPI_STATUS (AE_AML_ERROR);
    }

    /* Examine the datatype of the DestDesc */

    if (VALID_DESCRIPTOR_TYPE (DestDesc, DESC_TYPE_NTE))
    {
        /* Dest is an ACPI_HANDLE, create a new object */

        TempHandle = (ACPI_HANDLE) DestDesc;
        DestDesc = CmCreateInternalObject (INTERNAL_TYPE_Lvalue);
        if (!DestDesc)
        {   
            /* Allocation failure  */
            
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        /* Build a new Lvalue wrapper around the handle */

        DestDesc->Lvalue.OpCode = AML_NameOp;
        DestDesc->Lvalue.Object = TempHandle;
    }

    else
    {
        /* DestDesc is not an ACPI_HANDLE  */

        DEBUG_PRINT (ACPI_INFO, ("AmlExecStore: Dest is object (not handle) - may be deleted!\n"));
    }


    /* Destination object must be of type Lvalue */

    if (DestDesc->Common.Type != INTERNAL_TYPE_Lvalue)
    {   
        /* Destination is not an Lvalue */

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore: Destination is not an Lvalue [%p]\n",
                        DestDesc));

        DUMP_STACK_ENTRY (ValDesc);
        DUMP_STACK_ENTRY (DestDesc);
        DUMP_STACK (IMODE_Execute, "AmlExecStore", 2, "target not Lvalue");

        return_ACPI_STATUS (AE_AML_ERROR);
    }


    /* Examine the Lvalue opcode */

    switch (DestDesc->Lvalue.OpCode)
    {

    case AML_NameOp:

        /* Storing into a Name */

        TempHandle = DestDesc->Lvalue.Object;
        switch (NsGetType (TempHandle)) 
        {
            /* Type of Name's existing value */

        case INTERNAL_TYPE_Alias:

            DEBUG_PRINT (ACPI_WARN, ("AmlExecStore/NameOp: Store into %s not implemented\n",
                            Gbl_NsTypeNames[NsGetType (TempHandle)]));
            
            Status = AE_NOT_IMPLEMENTED;
            DeleteDestDesc = DestDesc;
            break;


        case INTERNAL_TYPE_BankField:

            /* 
             * Storing into a BankField.
             * If value is not a Number, try to resolve it to one.
             */

            if ((ValDesc->Common.Type != ACPI_TYPE_Number) &&
               ((Status = AmlGetRvalue (&ValDesc)) != AE_OK))
            {
                DeleteDestDesc = DestDesc;
            }

            else if (ValDesc->Common.Type != ACPI_TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore: Value assigned to BankField must be Number, not %d\n",
                        ValDesc->Common.Type));

                DeleteDestDesc = DestDesc;
                Status = AE_AML_ERROR;
            }

            else
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DeleteDestDesc = DestDesc;

                DestDesc = NsGetAttachedObject (TempHandle);
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/BankField: Internal error - null old-value pointer\n"));
                    Status = AE_AML_ERROR;
                }
            }


            if ((AE_OK == Status) && 
                (INTERNAL_TYPE_BankField != DestDesc->Common.Type))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/BankField: Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                        &(((NAME_TABLE_ENTRY *) TempHandle)->Name), NsGetType (TempHandle), 
                        DestDesc->Common.Type, DestDesc));

                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* Get the global lock if needed */

                Locked = AmlAcquireGlobalLock (DestDesc->BankField.LockRule);

                /* Set Bank value to select proper Bank */
                /* Perform the update (Set Bank Select) */

                Status = AmlSetNamedFieldValue (DestDesc->BankField.BankSelect,
                                            DestDesc->BankField.Value);

                DEBUG_PRINT (ACPI_INFO,
                            ("AmlExecStore: set bank select returned %s\n", Gbl_ExceptionNames[Status]));
            }


            if (AE_OK == Status)
            {
                /* Set bank select successful, next set data value  */
                
                Status = AmlSetNamedFieldValue (DestDesc->BankField.BankSelect,
                                               ValDesc->BankField.Value);
                DEBUG_PRINT (ACPI_INFO,
                            ("AmlExecStore: set bank select returned %s\n", Gbl_ExceptionNames[Status]));
            }
            
            break;  /* Global Lock released below  */


        case INTERNAL_TYPE_DefField:

            /* 
             * Storing into a Field defined in a Region.
             * If value is not a Number, try to resolve it to one.
             */

            if ((ValDesc->Common.Type != ACPI_TYPE_Number) && 
               ((Status = AmlGetRvalue (&ValDesc)) != AE_OK))
            {
                DeleteDestDesc = DestDesc;
            }

            else if (ValDesc->Common.Type != ACPI_TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, 
                        ("AmlExecStore/DefField: Value assigned to Field must be Number, not %d\n",
                        ValDesc->Common.Type));

                DeleteDestDesc = DestDesc;
                Status = AE_AML_ERROR;
            }

            else
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DeleteDestDesc = DestDesc;

                DestDesc = NsGetAttachedObject (TempHandle);
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/DefField: Internal error - null old-value pointer\n"));
                    Status = AE_AML_ERROR;
                }
            }

            if ((AE_OK == Status) && 
                (INTERNAL_TYPE_DefField != DestDesc->Common.Type))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/DefField: Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                        &(((NAME_TABLE_ENTRY *) TempHandle)->Name), NsGetType (TempHandle), 
                        DestDesc->Common.Type, DestDesc));

                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* Get the global lock if needed */

                Locked = AmlAcquireGlobalLock (ValDesc->Field.LockRule);

                /* Perform the update */
                
                Status = AmlSetNamedFieldValue (TempHandle, ValDesc->Number.Value);
            }
                
            break;      /* Global Lock released below   */


        case INTERNAL_TYPE_IndexField:
            
            /* 
             * Storing into an IndexField.
             * If value is not a Number, try to resolve it to one.
             */
            
            if ((ValDesc->Common.Type != ACPI_TYPE_Number) &&
               ((Status = AmlGetRvalue (&ValDesc)) != AE_OK))
            {
                DeleteDestDesc = DestDesc;
            }

            else if (ValDesc->Common.Type != ACPI_TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore: Value assigned to IndexField must be Number, not %d\n",
                        ValDesc->Common.Type));

                DeleteDestDesc = DestDesc;
                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DeleteDestDesc = DestDesc;

                DestDesc = NsGetAttachedObject (TempHandle);
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, 
                        ("AmlExecStore/IndexField: Internal error - null old-value pointer\n"));
                    Status = AE_AML_ERROR;
                }
            }

            if ((AE_OK == Status) &&
                (INTERNAL_TYPE_IndexField != DestDesc->Common.Type))
            {
                DEBUG_PRINT (ACPI_ERROR, 
                        ("AmlExecStore/IndexField: Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                        &(((NAME_TABLE_ENTRY *) TempHandle)->Name), NsGetType (TempHandle), 
                        DestDesc->Common.Type, DestDesc));

                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* Get the global lock if needed */

                Locked = AmlAcquireGlobalLock (DestDesc->IndexField.LockRule);

                /* Set Index value to select proper Data register */
                /* perform the update (Set index) */

                Status = AmlSetNamedFieldValue (DestDesc->IndexField.Index,
                                               DestDesc->IndexField.Value);
                DEBUG_PRINT (ACPI_INFO,
                            ("AmlExecStore: IndexField: set index returned %s\n", Gbl_ExceptionNames[Status]));
            }

            if (AE_OK == Status)
            {
                /* set index successful, next set Data value */
                
                Status = AmlSetNamedFieldValue (DestDesc->IndexField.Data,
                                               ValDesc->Number.Value);
                DEBUG_PRINT (ACPI_INFO,
                            ("AmlExecStore: IndexField: set data returned %s\n", Gbl_ExceptionNames[Status]));
            }

            break;      /* Global Lock released below   */


        case ACPI_TYPE_FieldUnit:
            
            /* 
             * Storing into a FieldUnit (defined in a Buffer).
             * If value is not a Number, try to resolve it to one.
             */
            if ((ValDesc->Common.Type != ACPI_TYPE_Number) &&
               ((Status = AmlGetRvalue (&ValDesc)) != AE_OK))
            {
                DeleteDestDesc = DestDesc;
            }

            else if (ValDesc->Common.Type != ACPI_TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/FieldUnit: Value assigned to Field must be Number, not %d\n",
                          ValDesc->Common.Type));

                DeleteDestDesc = DestDesc;
                Status = AE_AML_ERROR;
            }


            if (AE_OK == Status)
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DeleteDestDesc = DestDesc;

                DestDesc = NsGetAttachedObject (TempHandle);
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/FieldUnit: Internal error - null old-value pointer\n"));
                    Status = AE_AML_ERROR;
                }

                else
                {
                    DEBUG_PRINT (ACPI_INFO,
                        ("AmlExecStore: FieldUnit: Name's value DestDesc=%p, DestDesc->Common.Type=%02Xh\n",
                        DestDesc, DestDesc->Common.Type));
                }
            }

            if ((AE_OK == Status) &&
                (DestDesc->Common.Type != (UINT8) NsGetType (TempHandle)))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/FieldUnit: Internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                          &(((NAME_TABLE_ENTRY *) TempHandle)->Name), NsGetType(TempHandle), 
                          DestDesc->Common.Type, DestDesc));

                Status = AE_AML_ERROR;
            }

            if ((AE_OK == Status) &&
               (!DestDesc->FieldUnit.Container ||
                ACPI_TYPE_Buffer != DestDesc->FieldUnit.Container->Common.Type ||
                DestDesc->FieldUnit.Sequence
                    != DestDesc->FieldUnit.Container->Buffer.Sequence))
            {
                NsDumpPathname (TempHandle, "AmlExecStore/FieldUnit: Bad container in ", 
                                ACPI_ERROR, _COMPONENT);
                DUMP_ENTRY (TempHandle, ACPI_ERROR);

                DEBUG_PRINT (ACPI_ERROR, ("Container: %p", DestDesc->FieldUnit.Container));
                if (DestDesc->FieldUnit.Container)
                {
                    DEBUG_PRINT_RAW (ACPI_ERROR, (" Type %d, FuSeq %x BufSeq %x",
                        DestDesc->FieldUnit.Container->Common.Type,
                        DestDesc->FieldUnit.Sequence,
                        DestDesc->FieldUnit.Container->Buffer.Sequence));
                }
                DEBUG_PRINT_RAW (ACPI_ERROR, ("\n"));

                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* Get the global lock if needed */

                Locked = AmlAcquireGlobalLock (DestDesc->FieldUnit.LockRule);
            }

            if ((AE_OK == Status) &&
                (DestDesc->FieldUnit.Length + DestDesc->FieldUnit.BitOffset > 32))
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/FieldUnit: Implementation limitation - Field exceeds UINT32\n"));
                Status = AE_AML_ERROR;
            }
            
            if (AE_OK == Status)
            {
                /* Field location is (base of buffer) + (byte offset) */
                
                Location = DestDesc->FieldUnit.Container->Buffer.Pointer
                                + DestDesc->FieldUnit.Offset;
                
                /* 
                 * Construct Mask with 1 bits where the field is,
                 * 0 bits elsewhere
                 */
                Mask = ((UINT32) 1 << DestDesc->FieldUnit.Length) - ((UINT32)1
                                    << DestDesc->FieldUnit.BitOffset);

                DEBUG_PRINT (TRACE_BFIELD,
                        ("** Store %lx in buffer %p byte %ld bit %d width %d addr %p mask %08lx\n",
                        ValDesc->Number.Value,
                        DestDesc->FieldUnit.Container->Buffer.Pointer,
                        DestDesc->FieldUnit.Offset,
                        DestDesc->FieldUnit.BitOffset,
                        DestDesc->FieldUnit.Length,
                        Location, Mask));

                /* zero out the field in the buffer */
                
                *(UINT32 *) Location &= ~Mask;

                /* 
                 * Shift and mask the new value into position,
                 * and or it into the buffer.
                 */
                *(UINT32 *) Location |=
                    (ValDesc->Number.Value << DestDesc->FieldUnit.BitOffset) & Mask;
                
                DEBUG_PRINT (TRACE_BFIELD,
                            (" val %08lx\n", *(UINT32 *) Location));
            }
            break;  /* Global lock released below */


        default:
            
            /* 
             * All other types than Alias and the various Fields come here.
             * Store a copy of ValDesc as the new value of the Name, and set
             * the Name's type to that of the value being stored in it.
             */
            CmCopyInternalObject (ValDesc, DestDesc);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }
            
            if (ACPI_TYPE_Buffer == DestDesc->Common.Type)
            {
                /* Assign a new sequence number */

                DestDesc->Buffer.Sequence = AmlBufSeq ();
            }


            NsAttachObject (TempHandle, DestDesc, DestDesc->Common.Type);
            break;
        }

        break;  /* Case NameOp */


    case AML_ZeroOp: case AML_OneOp: case AML_OnesOp:

        /* 
         * Storing to a constant is a no-op -- see spec sec 15.2.3.3.1.
         * Delete the result descriptor.
         */

        DeleteDestDesc = DestDesc;
        break;


    case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
    case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:

        Status = AmlMthStackSetValue (MTH_TYPE_LOCAL, (DestDesc->Lvalue.OpCode - AML_Local0),
                                        ValDesc, DestDesc);
        break;


    case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
    case AML_Arg4: case AML_Arg5: case AML_Arg6:

        Status = AmlMthStackSetValue (MTH_TYPE_ARG, (DestDesc->Lvalue.OpCode - AML_Arg0), 
                                        ValDesc, DestDesc);
        break;


    case Debug1:

        /* 
         * Storing to the Debug object causes the value stored to be
         * displayed and otherwise has no effect -- see sec. 15.2.3.3.3.
         */
        DEBUG_PRINT (ACPI_INFO, ("DebugOp: \n"));
        DUMP_STACK_ENTRY (ValDesc);

        DeleteDestDesc = DestDesc;
        break;

#if 0
    case IndexOp:
        break;
#endif

    default:
        DEBUG_PRINT (ACPI_ERROR,
                    ("AmlExecStore: Internal error - Unknown Lvalue subtype %02x\n",
                    DestDesc->Lvalue.OpCode));
        
        /* TBD:  use object dump routine !! */

        DUMP_BUFFER (DestDesc, sizeof (ACPI_OBJECT_INTERNAL),0);

        DeleteDestDesc = DestDesc;
        Status = AE_AML_ERROR;
    
    }   /* switch(DestDesc->Lvalue.OpCode) */


    /* Release global lock if we acquired it earlier */

    AmlReleaseGlobalLock (Locked);

    /* Cleanup */

    if (DeleteDestDesc)
    {
        CmDeleteInternalObject (DeleteDestDesc);
    }

    return_ACPI_STATUS (Status);
}


