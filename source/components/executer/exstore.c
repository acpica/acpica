
/******************************************************************************
 * 
 * Module Name: iexecute - ACPI AML (p-code) execution
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


#define __IEXECUTE_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>
#include <string.h>


#define _THIS_MODULE        "iexecute.c"
#define _COMPONENT          INTERPRETER


static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", '1', "AmlExecStore: Descriptor Allocation Failure", "AmlExecStore: Descriptor Allocation Failure"},
    {"0001", '1', "AmlGetRvalue: Descriptor Allocation Failure", "AmlGetRvalue: Descriptor Allocation Failure"},
    {"0002", '1', "AmlExecMonadic2/IncDec: stack overflow", "AmlExecMonadic2/IncDec: stack overflow"},
    {"0003", '1', "AmlExecMonadic2/IncDec: Descriptor Allocation Failure", "AmlExecMonadic2/IncDec: Descriptor Allocation Failure"},
    {"0004", '1', "AmlExecMonadic2/ObjectTypeOp: Descriptor Allocation Failure", "AmlExecMonadic2/ObjectTypeOp: Descriptor Allocation Failure"},
    {"0005", '1', "AmlExecDyadic2R/ConcatOp: String allocation failure", "AmlExecDyadic2R/ConcatOp: String allocation failure"},
    {"0006", '1', "AmlExecDyadic2R/ConcatOp: Buffer allocation failure", "AmlExecDyadic2R/ConcatOp: Buffer allocation failure"},
    {NULL, 'I', NULL, NULL}
};


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecStore
 *
 * PARAMETERS:  *ValDesc            - Value to be stored
 *              *DestDesc           - Where to store it -- must be an (NsHandle)
 *                                    or an OBJECT_DESCRIPTOR of type Lvalue;
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
AmlExecStore(OBJECT_DESCRIPTOR *ValDesc, OBJECT_DESCRIPTOR *DestDesc)
{
    NsHandle        TempHandle;
    ACPI_STATUS     Status = AE_AML_ERROR;
    INT32           Stacked = FALSE;
    INT32           Locked = FALSE;


    FUNCTION_TRACE ("AmlExecStore");

    DEBUG_PRINT (ACPI_INFO, ("entered AmlExecStore: Val=%p, Dest=%p\n", 
                    ValDesc, DestDesc));

    if (!ValDesc || !DestDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore: internal error: null pointer\n"));
    }

    else if (IS_NS_HANDLE (DestDesc))
    {
        /* Dest is an NsHandle */

        TempHandle = (NsHandle) DestDesc;
        DestDesc = AllocateObjectDesc (&KDT[0]);
        if (!DestDesc)
        {   
            /*  allocation failure  */
            
            return AE_NO_MEMORY;
        }
        else
        {
            /* DestDesc is valid */

            DestDesc->ValType       = (UINT8) TYPE_Lvalue;
            DestDesc->Lvalue.OpCode = AML_NameOp;
            DestDesc->Lvalue.Ref    = TempHandle;

            /* Push the descriptor on TOS temporarily
             * to protect it from garbage collection
             */
            Status = AmlPushIfExec (MODE_Exec);
            if (AE_OK != Status)
            {
                DELETE (DestDesc);
            }
            else
            {
                ObjStack[ObjStackTop] = DestDesc;
                Stacked = TRUE;
            }
        }
    }

    else
    {
        /* DestDesc is not an NsHandle  */

        Status = AE_OK;
    }

    if ((AE_OK == Status) && 
        (DestDesc->ValType != TYPE_Lvalue))
    {   
        /*  Store target is not an Lvalue   */

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore: Store target is not an Lvalue [%s]\n",
                        NsTypeNames[DestDesc->ValType]));

        DUMP_STACK_ENTRY (ValDesc);
        DUMP_STACK_ENTRY (DestDesc);
        DUMP_STACK (MODE_Exec, "AmlExecStore", 2, "target not Lvalue");

        Status = AE_AML_ERROR;
    }

    if (AE_OK != Status)
    {
        return Status;   /*  temporary hack  */
    }


    /* Now examine the opcode */

    switch (DestDesc->Lvalue.OpCode)
    {
    case AML_NameOp:

        /* Storing into a Name */

        TempHandle = DestDesc->Lvalue.Ref;
        switch (NsGetType (TempHandle)) 
        {
            /* Type of Name's existing value */

        case TYPE_Alias:
#if 1
            DEBUG_PRINT (ACPI_ERROR, (
                      "AmlExecStore/NameOp: Store into %s not implemented\n",
                      NsTypeNames[NsGetType (TempHandle)]));
            Status = AE_AML_ERROR;
#else
            DEBUG_PRINT (ACPI_WARN,
                        ("AmlExecStore/NameOp: Store into %s not implemented\n",
                        NsTypeNames[NsGetType(TempHandle)]));
            Status = AE_OK;
#endif
            DELETE (DestDesc);
            break;

        case TYPE_BankField:

            /* 
             * Storing into a BankField.
             * If value is not a Number, try to resolve it to one.
             */
            if ((ValDesc->ValType != TYPE_Number) &&
               ((Status = AmlGetRvalue (&ValDesc)) != AE_OK))
            {
                DELETE (DestDesc);
            }

            else if (ValDesc->ValType != TYPE_Number)
            {
               DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore: Value assigned to BankField must be Number, not %d\n",
                        ValDesc->ValType));
                DELETE (DestDesc);
                Status = AE_AML_ERROR;
            }

            else
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DELETE (DestDesc);
                DestDesc = NsGetValue (TempHandle);
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/BankField: internal error: null old-value pointer\n"));
                    Status = AE_AML_ERROR;
                }
            }


            if ((AE_OK == Status) && 
                (TYPE_BankField != DestDesc->ValType))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/BankField: internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                        TempHandle, NsGetType (TempHandle), DestDesc->ValType, DestDesc));
                AmlAppendBlockOwner (DestDesc);
                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* Set Bank value to select proper Bank */
                /* Check lock rule prior to modifing the field */

                if (DestDesc->BankField.LockRule == (UINT16) GLOCK_AlwaysLock)
                {
                    /* Lock Rule is Lock */

                    if (OsGetGlobalLock () != AE_OK)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! */

                        Status = AE_AML_ERROR;
                    }

                    else
                    {
                        Locked = TRUE;
                    }
                }
            }


            if (AE_OK == Status)
            {

                /* Perform the update (Set Bank Select) */

                Status = AmlSetNamedFieldValue (DestDesc->BankField.BankSelect,
                                            DestDesc->BankField.BankVal);

                DEBUG_PRINT (ACPI_INFO,
                            ("AmlExecStore: set bank select returned %s\n", ExceptionNames[Status]));
            }


            if (AE_OK == Status)
            {
                /* Set bank select successful, next set data value  */
                
                Status = AmlSetNamedFieldValue (DestDesc->BankField.BankSelect,
                                               ValDesc->BankField.BankVal);
                DEBUG_PRINT (ACPI_INFO,
                            ("AmlExecStore: set bank select returned %s\n", ExceptionNames[Status]));
            }
            
            break;  /*  Global Lock released below  */


        case TYPE_DefField:

            /* 
             * Storing into a Field defined in a Region.
             * If value is not a Number, try to resolve it to one.
             */

            if ((ValDesc->ValType != TYPE_Number) && 
               ((Status = AmlGetRvalue (&ValDesc)) != AE_OK))
            {
                DELETE (DestDesc);
            }

            else if (ValDesc->ValType != TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/DefField: Value assigned to Field must be Number, not %d\n",
                        ValDesc->ValType));
                DELETE (DestDesc);
                Status = AE_AML_ERROR;
            }

            else
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DELETE (DestDesc);
                DestDesc = NsGetValue (TempHandle);
            
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/DefField: internal error: null old-value pointer\n"));
                    Status = AE_AML_ERROR;
                }
            }

            if ((AE_OK == Status) && 
                (TYPE_DefField != DestDesc->ValType))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/DefField:internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                        TempHandle, NsGetType (TempHandle), DestDesc->ValType, DestDesc));
                AmlAppendBlockOwner (DestDesc);
                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* Check lock rule prior to modifing the field */
            
                if (ValDesc->Field.LockRule == (UINT16) GLOCK_AlwaysLock)
                {
                    /* Lock Rule is Lock */
                
                    if (OsGetGlobalLock () != AE_OK)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock!  */
                    
                        Status = AE_AML_ERROR;
                    }
                    else
                    {
                        Locked = TRUE;
                    }
                }
            }
                
            if (AE_OK == Status)
            {
                /* perform the update */
                
                Status = AmlSetNamedFieldValue (TempHandle, ValDesc->Number.Number);
            }
                
            break;      /* Global Lock released below   */


        case TYPE_IndexField:
            
            /* 
             * Storing into an IndexField.
             * If value is not a Number, try to resolve it to one.
             */
            
            if ((ValDesc->ValType != TYPE_Number) &&
               ((Status = AmlGetRvalue (&ValDesc)) != AE_OK))
            {
                DELETE (DestDesc);
            }

            else if (ValDesc->ValType != TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore: Value assigned to IndexField must be Number, not %d\n",
                        ValDesc->ValType));
                DELETE (DestDesc);
                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DELETE (DestDesc);
                DestDesc = NsGetValue (TempHandle);
            
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/IndexField: internal error: null old-value pointer\n"));
                    Status = AE_AML_ERROR;
                }
            }

            if ((AE_OK == Status) &&
                (TYPE_IndexField != DestDesc->ValType))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/IndexField:internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                        TempHandle, NsGetType (TempHandle), DestDesc->ValType, DestDesc));
                AmlAppendBlockOwner (DestDesc);
                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* Set Index value to select proper Data register */
                /* Check lock rule prior to modifing the field */
            
                if (DestDesc->IndexField.LockRule == (UINT16) GLOCK_AlwaysLock)
                {
                    /* Lock Rule is Lock */
               
                    if (OsGetGlobalLock () != AE_OK)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock!  */
                    
                        Status = AE_AML_ERROR;
                    }
                    else
                    {
                        Locked = TRUE;
                    }
                }
            }
                
            if (AE_OK == Status)
            {
                /* perform the update (Set index) */

                Status = AmlSetNamedFieldValue (DestDesc->IndexField.Index,
                                               DestDesc->IndexField.IndexVal);
                DEBUG_PRINT (ACPI_INFO,
                            ("AmlExecStore: IndexField: set index returned %s\n", ExceptionNames[Status]));
            }

            if (AE_OK == Status)
            {
                /* set index successful, next set Data value */
                
                Status = AmlSetNamedFieldValue (DestDesc->IndexField.Data,
                                               ValDesc->Number.Number);
                DEBUG_PRINT (ACPI_INFO,
                            ("AmlExecStore: IndexField: set data returned %s\n", ExceptionNames[Status]));
            }

            break;      /* Global Lock released below   */


        case TYPE_FieldUnit:
            
            /* 
             * Storing into a FieldUnit (defined in a Buffer).
             * If value is not a Number, try to resolve it to one.
             */
            if ((ValDesc->ValType != TYPE_Number) &&
               ((Status = AmlGetRvalue (&ValDesc)) != AE_OK))
            {
                DELETE (DestDesc);
            }

            else if (ValDesc->ValType != TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/FieldUnit: Value assigned to Field must be Number, not %d\n",
                          ValDesc->ValType));
                DELETE (DestDesc);
                Status = AE_AML_ERROR;
            }


            if (AE_OK == Status)
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */
                DELETE (DestDesc);
                DestDesc = NsGetValue (TempHandle);
            
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/FieldUnit: internal error: null old-value pointer\n"));
                    Status = AE_AML_ERROR;
                }

                else
                {
                    DEBUG_PRINT (ACPI_INFO,
                        ("AmlExecStore: FieldUnit: name's value DestDesc=%p, DestDesc->ValType=%02Xh\n",
                        DestDesc, DestDesc->ValType));
                }
            }

            if ((AE_OK == Status) &&
                (DestDesc->ValType != (UINT8) NsGetType (TempHandle)))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/FieldUnit:internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                          TempHandle, NsGetType(TempHandle), DestDesc->ValType, DestDesc));
                AmlAppendBlockOwner (DestDesc);
                Status = AE_AML_ERROR;
            }

            if ((AE_OK == Status) &&
               (!DestDesc->FieldUnit.Container ||
                TYPE_Buffer != DestDesc->FieldUnit.Container->ValType ||
                DestDesc->FieldUnit.ConSeq
                    != DestDesc->FieldUnit.Container->Buffer.Sequence))
            {
                NsDumpPathname (TempHandle, "AmlExecStore/FieldUnit: bad container in: ", 
                                ACPI_ERROR, _COMPONENT);
                DUMP_ENTRY (TempHandle);
                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* Check lock rule prior to modifing the field */
            
                if (DestDesc->FieldUnit.LockRule == (UINT16) GLOCK_AlwaysLock)
                {
                    /* Lock Rule is Lock */
                
                    if (OsGetGlobalLock () != AE_OK)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! */
                    
                        Status = AE_AML_ERROR;
                    }
                
                    else
                    {
                        /* Set the Locked Flag */
                    
                        Locked = TRUE;
                    }
                }
            }

            if ((AE_OK == Status) &&
                (DestDesc->FieldUnit.DatLen + DestDesc->FieldUnit.BitOffset > 32))
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/FieldUnit: implementation limitation: Field exceeds UINT32\n"));
                Status = AE_AML_ERROR;
            }
            
            if (AE_OK == Status)
            {
                UINT8           *Location=NULL;
                UINT32          Mask;


                /* Field location is (base of buffer) + (byte offset) */
                
                Location = DestDesc->FieldUnit.Container->Buffer.Buffer
                                + DestDesc->FieldUnit.Offset;
                
                /* 
                 * Construct Mask with 1 bits where the field is,
                 * 0 bits elsewhere
                 */
                Mask = ((UINT32) 1 << DestDesc->FieldUnit.DatLen) - ((UINT32)1
                                    << DestDesc->FieldUnit.BitOffset);

                DEBUG_PRINT (TRACE_BFIELD,
                        ("** Store %lx in buffer %p byte %ld bit %d width %d addr %p mask %08lx\n",
                        ValDesc->Number.Number,
                        DestDesc->FieldUnit.Container->Buffer.Buffer,
                        DestDesc->FieldUnit.Offset,
                        DestDesc->FieldUnit.BitOffset,
                        DestDesc->FieldUnit.DatLen,
                        Location, Mask));

                /* zero out the field in the buffer */
                
                *(UINT32 *) Location &= ~Mask;

                /* 
                 * Shift and mask the new value into position,
                 * and or it into the buffer.
                 */
                *(UINT32 *) Location |=
                    (ValDesc->Number.Number << DestDesc->FieldUnit.BitOffset) & Mask;
                
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
            memcpy ((void *) DestDesc, (void *) ValDesc, sizeof (*ValDesc));
            
            if (TYPE_Buffer == DestDesc->ValType)
            {
                /* Assign a new sequence number */

                DestDesc->Buffer.Sequence = AmlBufSeq ();
            }

            NsSetValue (TempHandle, DestDesc, DestDesc->ValType);

            if (Stacked)
            {
                NsDumpPathname (TempHandle, "AmlExecStore: set ", ACPI_INFO, _COMPONENT);

                DUMP_ENTRY (TempHandle);
                DUMP_STACK_ENTRY (DestDesc);
            }

            break;
        }

        break;  /* Case NameOp */


    case AML_ZeroOp: case AML_OneOp: case AML_OnesOp:

        /* 
         * Storing to a constant is a no-op -- see spec sec 15.2.3.3.1.
         * Delete the result descriptor.
         */
        DELETE (DestDesc);
        break;


    case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
    case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:

        Status = AmlSetMethodValue (LCLBASE + DestDesc->Lvalue.OpCode - AML_Local0, ValDesc, DestDesc);
        break;


    case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
    case AML_Arg4: case AML_Arg5: case AML_Arg6:

        Status = AmlSetMethodValue (ARGBASE + DestDesc->Lvalue.OpCode - AML_Arg0, ValDesc, DestDesc);
        break;


    case Debug1:

        /* 
         * Storing to the Debug object causes the value stored to be
         * displayed and otherwise has no effect -- see sec. 15.2.3.3.3.
         */
        DEBUG_PRINT (ACPI_INFO, ("DebugOp: \n"));
        DUMP_STACK_ENTRY (ValDesc);

        DELETE (DestDesc);
        break;

#if 0
    case IndexOp:
        break;
#endif

    default:
        DEBUG_PRINT (ACPI_ERROR,
                    ("AmlExecStore:internal error: Unknown Lvalue subtype %02x\n",
                    DestDesc->Lvalue.OpCode));
        
        /* TBD:  use object dump routine !! */

        DUMP_BUFFER (DestDesc, sizeof (OBJECT_DESCRIPTOR),0);

        DELETE (DestDesc);
        Status = AE_AML_ERROR;
    
    }   /* switch(DestDesc->Lvalue.OpCode) */


    if (Locked)
    {
        /* Release lock if we own it */

        OsReleaseGlobalLock ();
    }

    if (Stacked)
    {
        ObjStackTop--;
    }

    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecMonadic1
 *
 * PARAMETERS:  opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 1 monadic operator with numeric operand on 
 *              object stack
 *
 * ALLOCATION:  Deletes the operand
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecMonadic1 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecMonadic1");


    if (AML_SleepOp == opcode || AML_StallOp == opcode)
    {
        Status = AmlPrepStack ("n");                 /* operand should be a Number */
    }
    else
    {
        Status = AmlPrepStack ("l");                 /* operand should be an Lvalue */
    }

    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 1);
        return Status;
    }


    AmlDumpStack (MODE_Exec, LongOps[opcode & 0x00ff], 1, "after AmlPrepStack");

    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];

    switch (opcode)
    {

    /*  DefRelease  :=  ReleaseOp   MutexObject */

    case AML_ReleaseOp:
        if (TYPE_Mutex != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic1/ReleaseOp: Needed Mutex, found %d\n",
                    ObjDesc->ValType));
            return AE_AML_ERROR;
        }

        return (OsReleaseOpRqst (ObjDesc));


    /*  DefReset        :=  ResetOp     EventObject */

    case AML_ResetOp:
        if (TYPE_Event != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic1/ResetOp: Needed Event, found %d\n", ObjDesc->ValType));
            return AE_AML_ERROR;
        }

        return (OsResetOpRqst (ObjDesc));


    /*  DefSignal   :=  SignalOp        EventObject */
    
    case AML_SignalOp:
        if (TYPE_Event != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic1/SignalOp: Needed Event, found %d\n", ObjDesc->ValType));
            return AE_AML_ERROR;
        }
        return (OsSignalOpRqst (ObjDesc));


    /*  DefSleep    :=  SleepOp MsecTime    */
    
    case AML_SleepOp:
        OsDoSuspend (ObjDesc->Number.Number);
        break;


    /*  DefStall    :=  StallOp UsecTime    */
    
    case AML_StallOp:
        OsdSleepUsec (ObjDesc->Number.Number);
        break;


    /*  unknown opcode  */
    
    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic1: Unknown monadic opcode %02x\n", opcode));
        return AE_AML_ERROR;
    
    } /* switch */


    DELETE (ObjDesc);
    return AE_OK;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecMonadic2R
 *
 * PARAMETERS:  opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 monadic operator with numeric operand and
 *              result operand on operand stack
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecMonadic2R (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ResDesc;
    UINT32                  ResVal;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecMonadic2R");


    Status = AmlPrepStack ("ln");

    if (Status != AE_OK)
    {
        /* Invalid parameters on object stack   */
        /* This was added since it is allowable to return a buffer so */
        /* ln is a local and a number and that will fail.  lb is a local */
        /* and a buffer which will pass.  */
        
        Status = AmlPrepStack ("lb");

        if (Status != AE_OK)
        {
            AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
            return Status;
        }
    }

    AmlDumpStack (MODE_Exec, ShortOps[opcode], 2, "after AmlPrepStack");

    ResDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    switch (opcode)
    {
        INT32           d0, d1, d2, d3;


    /*  DefNot  :=  NotOp   Operand Result  */
    
    case AML_BitNotOp:
        ObjDesc->Number.Number = ~ObjDesc->Number.Number;
        break;


    /*  DefFindSetLeftBit   :=  FindSetLeftBitOp    Operand Result  */

    case AML_FindSetLeftBitOp:
        for (ResVal = 0; ObjDesc->Number.Number && ResVal < 33; ++ResVal)
        {
            ObjDesc->Number.Number >>= 1;
        }

        ObjDesc->Number.Number = ResVal;
        break;


    /*  DefFindSetRightBit  :=  FindSetRightBitOp   Operand Result  */

    case AML_FindSetRightBitOp:
        for (ResVal = 0; ObjDesc->Number.Number && ResVal < 33; ++ResVal)
        {
            ObjDesc->Number.Number <<= 1;
        }

        ObjDesc->Number.Number = ResVal == 0 ? 0 : 33 - ResVal;
        break;


    /*  DefFromBDC  :=  FromBCDOp   BCDValue    Result  */

    case AML_FromBCDOp:
        d0 = (INT32) (ObjDesc->Number.Number & 15);
        d1 = (INT32) (ObjDesc->Number.Number >> 4 & 15);
        d2 = (INT32) (ObjDesc->Number.Number >> 8 & 15);
        d3 = (INT32) (ObjDesc->Number.Number >> 12 & 15);
        
        if (d0 > 9 || d1 > 9 || d2 > 9 || d3 > 9)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic2R/FromBCDOp: improper BCD digit %d %d %d %d\n",
                    d3, d2, d1, d0));
            return AE_AML_ERROR;
        }
        
        ObjDesc->Number.Number = d0 + d1 * 10 + d2 * 100 + d3 * 1000;
        break;


    /*  DefToBDC    :=  ToBCDOp Operand Result  */
    
    case AML_ToBCDOp:
        if (ObjDesc->Number.Number > 9999)
        {
            DEBUG_PRINT (ACPI_ERROR, ("iExecMonadic2R/ToBCDOp: BCD overflow: %d\n",
                    ObjDesc->Number.Number));
            return AE_AML_ERROR;
        }
        
        ObjDesc->Number.Number
            = ObjDesc->Number.Number % 10
            + (ObjDesc->Number.Number / 10 % 10 << 4)
            + (ObjDesc->Number.Number / 100 % 10 << 8)
            + (ObjDesc->Number.Number / 1000 % 10 << 12);
        
        break;


    /*  DefShiftLeftBit     :=  ShiftLeftBitOp      Source          BitNum  */
    /*  DefShiftRightBit    :=  ShiftRightBitOp     Source          BitNum  */
    /*  DefCondRefOf        :=  CondRefOfOp         SourceObject    Result  */

    case AML_ShiftLeftBitOp:
    case AML_ShiftRightBitOp:
    case AML_CondRefOfOp:
        
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2R: %s unimplemented\n",
                (opcode > UCHAR_MAX) ? LongOps[opcode & 0x00ff] : ShortOps[opcode]));
        return AE_AML_ERROR;

    case AML_StoreOp:
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2R: internal error: Unknown monadic opcode %02x\n",
                    opcode));
        return AE_AML_ERROR;
    }
    
    Status = AmlExecStore (ObjDesc, ResDesc);
    ObjStackTop--;

    DEBUG_PRINT (TRACE_EXEC, ("leave iExecMonadic2R: %s\n", ExceptionNames[Status]));
    
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecMonadic2
 *
 * PARAMETERS:  opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 monadic operator with numeric operand:
 *              DerefOfOp, RefOfOp, SizeOfOp, TypeOp, IncrementOp,
 *              DecrementOp, LNotOp,
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecMonadic2 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ResDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecMonadic2");


    if (AML_LNotOp == opcode)
    {
        Status = AmlPrepStack ("n");
    }
    else
    {
        Status = AmlPrepStack ("l");
    }

    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 1);
        return Status;
    }

    AmlDumpStack (MODE_Exec, ShortOps[opcode], 1, "after AmlPrepStack");

    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];


    switch (opcode)
    {

    /*  DefLNot :=  LNotOp  Operand */

    case AML_LNotOp:
        ObjDesc->Number.Number = (!ObjDesc->Number.Number) - (UINT32) 1;
        break;


    /*  DefDecrement    :=  DecrementOp Target  */
    /*  DefIncrement    :=  IncrementOp Target  */

    case AML_DecrementOp:
    case AML_IncrementOp:

        if ((Status = AmlPushIfExec (MODE_Exec)) != AE_OK)
        {
            REPORT_ERROR (&KDT[2]);
            return AE_AML_ERROR;
        }

        /* duplicate the Lvalue on TOS */
        
        ResDesc = AllocateObjectDesc (&KDT[3]);
        if (ResDesc)
        {
            memcpy ((void *) ResDesc, (void *) ObjDesc, sizeof (*ObjDesc));
            
            /* push went into unused space, so no need to DeleteObject() */
            
            ObjStack[ObjStackTop] = (void *) ResDesc;
        }
        
        else
        {
            return AE_NO_MEMORY;
        }

        /* Convert the top copy to a Number */
        
        Status = AmlPrepStack ("n");
        if (Status != AE_OK)
        {
            AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 1);
            return Status;
        }

        /* get the Number in ObjDesc and the Lvalue in ResDesc */
        
        ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
        ResDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

        /* do the ++ or -- */
        
        if (AML_IncrementOp == opcode)
        {
            ObjDesc->Number.Number++;
        }
        else
        {
            ObjDesc->Number.Number--;
        }

        /* store result */
        
        DeleteObject ((OBJECT_DESCRIPTOR **) &ObjStack[ObjStackTop - 1]);
        ObjStack[ObjStackTop - 1] = (void *) ObjDesc;
        
        Status = AmlExecStore (ObjDesc, ResDesc);
        ObjStackTop--;
        return Status;



    /*  DefObjectType   :=  ObjectTypeOp    SourceObject    */

    case AML_TypeOp:
        
        /* This case uses Status to hold the type encoding */
        
        if (TYPE_Lvalue == ObjDesc->ValType)
        {
            /* 
             * Not a Name -- an indirect name pointer would have
             * been converted to a direct name pointer in AmlPrepStack
             */
            switch (ObjDesc->Lvalue.OpCode)
            {
            case AML_ZeroOp: case AML_OneOp: case AML_OnesOp:
                
                /* Constants are of type Number */
                
                Status = (INT32) TYPE_Number;
                break;

            case Debug1:
                
                /* Per spec, Debug object is of type Region */
                
                Status = (INT32) TYPE_Region;
                break;

            case AML_IndexOp:
                DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2/TypeOp: determining type of Index result is not implemented\n"));
                return AE_AML_ERROR;

            case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
            case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:
                Status = (INT32) AmlGetMethodType (LCLBASE + ObjDesc->Lvalue.OpCode - AML_Local0);
                break;

            case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
            case AML_Arg4: case AML_Arg5: case AML_Arg6:
                Status = (INT32) AmlGetMethodType (ARGBASE + ObjDesc->Lvalue.OpCode - AML_Arg0);
                break;

            default:
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecMonadic2/TypeOp:internal error: Unknown Lvalue subtype %02x\n",
                        ObjDesc->Lvalue.OpCode));
                return AE_AML_ERROR;
            }
        }
        
        else
        {
            /* 
             * Since we passed AmlPrepStack("l") and it's not an Lvalue,
             * it must be a direct name pointer.  Allocate a descriptor
             * to hold the type.
             */
            Status = (INT32) NsGetType ((NsHandle) ObjDesc);

            ObjDesc = AllocateObjectDesc (&KDT[4]);
            if (!ObjDesc)
            {
                return AE_NO_MEMORY;
            }

            /* 
             * Replace (NsHandle) on TOS with descriptor containing result.
             * No need to DeleteObject() first since TOS is an NsHandle.
             */

            ObjStack[ObjStackTop] = (void *) ObjDesc;
        }
        
        ObjDesc->ValType = (UINT8) TYPE_Number;
        ObjDesc->Number.Number = (UINT32) Status;
        break;


    /*  DefSizeOf   :=  SizeOfOp    SourceObject    */

    case AML_SizeOfOp:
        switch (ObjDesc->ValType)
        {
        case TYPE_Buffer:
            ObjDesc->Number.Number = ObjDesc->Buffer.BufLen;
            ObjDesc->ValType = (UINT8) TYPE_Number;
            break;

        case TYPE_String:
            ObjDesc->Number.Number = ObjDesc->String.StrLen;
            ObjDesc->ValType = (UINT8) TYPE_Number;
            break;

        case TYPE_Package:
            ObjDesc->Number.Number = ObjDesc->Package.PkgCount;
            ObjDesc->ValType = (UINT8) TYPE_Number;
            break;

        default:
           DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic2: Needed aggregate, found %d\n", ObjDesc->ValType));
            return AE_AML_ERROR;
        }
        break;


    /*  DefRefOf    :=  RefOfOp     SourceObject    */
    /*  DefDerefOf  :=  DerefOfOp   ObjReference    */

    case AML_RefOfOp:
    case AML_DerefOfOp:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMonadic2: %s unimplemented\n",
                (opcode > UCHAR_MAX) ? LongOps[opcode & 0x00ff] : ShortOps[opcode]));
        ObjStackTop++;  /*  dummy return value  */
        return AE_AML_ERROR;

    default:
        DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecMonadic2:internal error: Unknown monadic opcode %02x\n",
                    opcode));
        return AE_AML_ERROR;
    }

    return AE_OK;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic1
 *
 * PARAMETERS:  opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 1 dyadic operator with numeric operands:
 *              NotifyOp
 *
 * ALLOCATION:  Deletes both operands
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecDyadic1 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc = NULL;
    OBJECT_DESCRIPTOR       *ValDesc = NULL;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecDyadic1");


    Status = AmlPrepStack ("nl");

    if (Status != AE_OK)
    {
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
        return Status;
    }

    AmlDumpStack (MODE_Exec, ShortOps[opcode], 2, "after AmlPrepStack");

    ValDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    switch (opcode)
    {


    /*  DefNotify   :=  NotifyOp    NotifyObject    NotifyValue */

    case AML_NotifyOp:

        /* XXX - What should actually happen here [NotifyOp] ?
         * XXX - See ACPI 1.0 spec sec 5.6.3 p. 5-102.
         * XXX - We may need to simulate what an OS would
         * XXX - do in response to the Notify operation.
         * XXX - For value 1 (Ejection Request),
         * XXX -        some device method may need to be run.
         * XXX - For value 2 (Device Wake) if _PRW exists,
         * XXX -        the _PS0 method may need to be run.
         * XXX - For value 0x80 (Status Change) on the power button or
         * XXX -        sleep button, initiate soft-off or sleep operation?
         */

        if (ObjDesc)
        {
            switch (ObjDesc->ValType)
            {
            case TYPE_Device:
            case TYPE_Thermal:
            
                /* XXX - Requires that sDevice and sThermalZone
                 * XXX - be compatible mappings
                 */

                OsDoNotifyOp (ValDesc, ObjDesc);
                break;

            default:
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecDyadic1/NotifyOp: unexpected notify object type %d\n",
                        ObjDesc->ValType));
                return AE_AML_ERROR;
            }
        }
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic1: Unknown dyadic opcode %02x\n", opcode));
        return AE_AML_ERROR;
    }

    if (ValDesc)
    {
        DELETE (ValDesc);
    }

    if (ObjDesc)
    {
        DELETE (ObjDesc);
    }
    
    ObjStack[--ObjStackTop] = NULL;

    return AE_OK;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic2R
 *
 * PARAMETERS:  opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 dyadic operator with numeric operands and
 *              one or two result operands
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecDyadic2R (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc = NULL;
    OBJECT_DESCRIPTOR       *ObjDesc2 = NULL;
    OBJECT_DESCRIPTOR       *ResDesc = NULL;
    OBJECT_DESCRIPTOR       *ResDesc2 = NULL;
    ACPI_STATUS             Status;
    UINT32                  remain;
    INT32                   NumOperands;


    FUNCTION_TRACE ("AmlExecDyadic2R");


    switch (opcode)
    {


    /*  DefConcat   :=  ConcatOp    Data1   Data2   Result  */

    case AML_ConcatOp:
        Status = AmlPrepStack ("lss");
        NumOperands = 3;
        break;


    /*  DefDivide   :=  DivideOp Dividend Divisor Remainder Quotient    */

    case AML_DivideOp:
        Status = AmlPrepStack ("llnn");
        NumOperands = 4;
        break;


    /*  DefX    :=  XOp Operand1    Operand2    Result  */

    default:
        Status = AmlPrepStack ("lnn");
        NumOperands = 3;
        break;
    }

    if (Status != AE_OK)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, NumOperands);
        return Status;
    }

    AmlDumpStack (MODE_Exec, ShortOps[opcode], NumOperands, "after AmlPrepStack");

    if (AML_DivideOp == opcode)
    {
        ResDesc2 = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];
    }

    ResDesc     = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];
    ObjDesc2    = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];
    ObjDesc     = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjStackTop += NumOperands - 1;

    switch (opcode)
    {


    /*  DefAdd  :=  AddOp   Operand1    Operand2    Result  */

    case AML_AddOp:
        ObjDesc->Number.Number += ObjDesc2->Number.Number;
        break;
 
        
    /*  DefAnd  :=  AndOp   Operand1    Operand2    Result  */

    case AML_BitAndOp:
        ObjDesc->Number.Number &= ObjDesc2->Number.Number;
        break;

        
    /*  DefNAnd :=  NAndOp  Operand1    Operand2    Result  */

    case AML_BitNandOp:
        ObjDesc->Number.Number = ~(ObjDesc->Number.Number & ObjDesc2->Number.Number);
        break;
   
       
    /*  DefOr       :=  OrOp    Operand1    Operand2    Result  */
        
    case AML_BitOrOp:
        ObjDesc->Number.Number |= ObjDesc2->Number.Number;
        break;

        
    /*  DefNOr  :=  NOrOp   Operand1    Operand2    Result  */

    case AML_BitNorOp:
        ObjDesc->Number.Number = ~(ObjDesc->Number.Number | ObjDesc2->Number.Number);
        break;

        
    /*  DefXOr  :=  XOrOp   Operand1    Operand2    Result  */

    case AML_BitXorOp:
        ObjDesc->Number.Number ^= ObjDesc2->Number.Number;
        break;

        
    /*  DefDivide   :=  DivideOp Dividend Divisor Remainder Quotient    */

    case AML_DivideOp:
        if ((UINT32) 0 == ObjDesc2->Number.Number)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2R/DivideOp: divide by zero\n"));
            return AE_AML_ERROR;
        }

        remain = ObjDesc->Number.Number % ObjDesc2->Number.Number;
        ObjDesc->Number.Number /= ObjDesc2->Number.Number;
        ObjDesc2->Number.Number = remain;
        break;

        
    /*  DefMultiply :=  MultiplyOp  Operand1    Operand2    Result  */

    case AML_MultiplyOp:
        ObjDesc->Number.Number *= ObjDesc2->Number.Number;
        break;

        
    /*  DefShiftLeft    :=  ShiftLeftOp Operand ShiftCount  Result  */

    case AML_ShiftLeftOp:
        ObjDesc->Number.Number <<= ObjDesc2->Number.Number;
        break;

        
    /*  DefShiftRight   :=  ShiftRightOp    Operand ShiftCount  Result  */

    case AML_ShiftRightOp:
        ObjDesc->Number.Number >>= ObjDesc2->Number.Number;
        break;

        
    /*  DefSubtract :=  SubtractOp  Operand1    Operand2    Result  */

    case AML_SubtractOp:
        ObjDesc->Number.Number -= ObjDesc2->Number.Number;
        break;


    /*  DefConcat   :=  ConcatOp    Data1   Data2   Result  */

    case AML_ConcatOp:
        if (ObjDesc2->ValType != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecDyadic2R/ConcatOp: operand type mismatch %d %d\n",
                    ObjDesc->ValType, ObjDesc2->ValType));
            return AE_AML_ERROR;
        }

        /* Both operands are now known to be the same */
        
        if (TYPE_String == ObjDesc->ValType)
        {
            /*  Operand1 is string  */

            char *NewBuf = OsdAllocate ((size_t) (ObjDesc->String.StrLen
                                                + ObjDesc2->String.StrLen + 1));
            if (!NewBuf)
            {
                REPORT_ERROR (&KDT[5]);
                return AE_AML_ERROR;
            }
            
            strcpy (NewBuf, (char *) ObjDesc->String.String);
            strcpy (NewBuf + ObjDesc->String.StrLen,
                     (char *) ObjDesc2->String.String);
            
            /* Don't free old ObjDesc->String.String; the operand still exists */
            
            ObjDesc->String.String = (UINT8 *) NewBuf;
            ObjDesc->String.StrLen += ObjDesc2->String.StrLen;
        }
        
        else
        {
            /*  Operand1 is not string ==> buffer   */

            char *NewBuf = OsdAllocate ((size_t) (ObjDesc->Buffer.BufLen
                                                + ObjDesc2->Buffer.BufLen));
            if (!NewBuf)
            {
                /* Only bail out if the buffer is small */
                
                if (ObjDesc->Buffer.BufLen + ObjDesc2->Buffer.BufLen < 1024)
                {
                    REPORT_ERROR (&KDT[0]);
                    return AE_AML_ERROR;
                }

                DEBUG_PRINT (ACPI_ERROR, (
                            "AmlExecDyadic2R/ConcatOp: Buffer allocation failure %d\n",
                            ObjDesc->Buffer.BufLen + ObjDesc2->Buffer.BufLen));
                return AE_AML_ERROR;
            }

            memcpy (NewBuf, ObjDesc->Buffer.Buffer, (size_t) ObjDesc->Buffer.BufLen);
            memcpy (NewBuf + ObjDesc->Buffer.BufLen, ObjDesc2->Buffer.Buffer,
                    (size_t) ObjDesc2->Buffer.BufLen);
            
            /* Don't free old ObjDesc->Buffer.Buffer; the operand still exists */
            
            ObjDesc->Buffer.Buffer = (UINT8 *) NewBuf;
            ObjDesc->Buffer.BufLen += ObjDesc2->Buffer.BufLen;
        }
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2R: Unknown dyadic opcode %02x\n", opcode));
        return AE_AML_ERROR;
    }
    
    if ((Status = AmlExecStore (ObjDesc, ResDesc)) != AE_OK)
    {
        ObjStackTop -= NumOperands - 1;
        return Status;
    }
    
    if (AML_DivideOp == opcode)
    {
        Status = AmlExecStore(ObjDesc2, ResDesc2);
    }

    /* Don't delete ObjDesc because it remains on the stack */
    /* deleting psObjDescOperand2 is valid for DivideOp since we preserved
     * remainder on stack
     */
    
    DELETE (ObjDesc2);
    ObjStackTop -= NumOperands - 1;
    
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic2S
 *
 * PARAMETERS:  opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 dyadic synchronization operator
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecDyadic2S (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc = NULL;
    OBJECT_DESCRIPTOR       *TimeDesc = NULL;
    OBJECT_DESCRIPTOR       *ResDesc = NULL;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecDyadic2S");


    Status = AmlPrepStack ("nl");

    if (Status != AE_OK)
    {   
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
    }

    else
    {
        AmlDumpStack (MODE_Exec, LongOps[opcode & 0x00ff], 2, "after AmlPrepStack");

        TimeDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
        ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

        switch (opcode)
        {


        /*  DefAcquire  :=  AcquireOp   MutexObject Timeout */

        case AML_AcquireOp:
            if (TYPE_Mutex != ObjDesc->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecDyadic2S/AcquireOp: Needed Mutex, found %d\n",
                        ResDesc->ValType));
                Status = AE_AML_ERROR;
            }
            else
            {
                Status = OsAcquireOpRqst (TimeDesc, ObjDesc);
            }



        /*  DefWait :=  WaitOp  EventObject Timeout */

        case AML_WaitOp:
            if (TYPE_Event != ObjDesc->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecDyadic2S/WaitOp: Needed Event, found %d\n",
                        ResDesc->ValType));
                Status = AE_AML_ERROR;
            }
            else
            {
                Status = OsWaitOpRqst (TimeDesc, ObjDesc);
            }


        default:
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlExecDyadic2S: Unknown dyadic synchronization opcode %02x\n",
                    opcode));
            Status = AE_AML_ERROR;
        }

        /*  delete TimeOut object descriptor before removing it from object stack   */
    
        DELETE (TimeDesc);

        /*  remove TimeOut parameter from object stack  */

        ObjStackTop--;
    
    }
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecDyadic2
 *
 * PARAMETERS:  opcode              - The opcode to be executed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 2 dyadic operator with numeric operands and
 *              no result operands
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *              containing result value
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecDyadic2 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ObjDesc2;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecDyadic2");


    Status = AmlPrepStack ("nn");

    if (Status != AE_OK)
    {
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
        return Status;
    }

    AmlDumpStack (MODE_Exec, ShortOps[opcode], 2, "after AmlPrepStack");

    ObjDesc2 = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    Status = AE_OK;      /* Make sure AE_OK */
    switch (opcode)
    {


    /*  DefLAnd :=  LAndOp  Operand1    Operand2    */

    case AML_LAndOp:
        if (ObjDesc->Number.Number && ObjDesc2->Number.Number)
        {
            Status = AE_PENDING;
        }
        break;


    /*  DefLEqual   :=  LEqualOp    Operand1    Operand2    */

    case AML_LEqualOp:
        if (ObjDesc->Number.Number == ObjDesc2->Number.Number)
        {
            Status = AE_PENDING;
        }
        break;


    /*  DefLGreater :=  LGreaterOp  Operand1    Operand2    */

    case AML_LGreaterOp:
        if (ObjDesc->Number.Number > ObjDesc2->Number.Number)
        {
            Status = AE_PENDING;
        }
        break;


    /*  DefLLess    :=  LLessOp Operand1    Operand2    */

    case AML_LLessOp:
        if (ObjDesc->Number.Number < ObjDesc2->Number.Number)
        {
            Status = AE_PENDING;
        }
        break;


    /*  DefLOr  :=  LOrOp   Operand1    Operand2    */

    case AML_LOrOp:
        if (ObjDesc->Number.Number || ObjDesc2->Number.Number)
        {
            Status = AE_PENDING;
        }
        break;
    
    default:
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecDyadic2: Unknown dyadic opcode %02x\n", opcode));
        return AE_AML_ERROR;
    }

    /* ObjDesc->ValType == Number was assured by AmlPrepStack("nn") call */
    
    if (Status == AE_PENDING)
    {
        ObjDesc->Number.Number = 0xffffffff;
    }
    else
    {
        ObjDesc->Number.Number = 0;
    }

    DELETE (ObjDesc2);
    ObjStackTop--;
    
    return AE_OK;
}


/******************************************************************************
 * 
 * FUNCTION:    AmlExecuteMethod
 *
 * PARAMETERS:  Offset              - Offset to method in code block
 *              Length              - Length of method
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
AmlExecuteMethod (INT32 Offset, INT32 Length, OBJECT_DESCRIPTOR **Params)
{
    ACPI_STATUS     Status;
    INT32           i1;
    INT32           i2;


    FUNCTION_TRACE ("AmlExecuteMethod");


    if ((Status = AmlPrepExec (Offset, Length)) != AE_OK)  /* package stack */
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecuteMethod: Exec Stack Overflow\n"));
    }

    /* Push new frame on Method stack */
    
    else if (++MethodStackTop >= AML_METHOD_MAX_NEST)
    {
        MethodStackTop--;
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecuteMethod: Method Stack Overflow\n"));
        Status = AE_AML_ERROR;
    }

    else
    {
        /* Undefine all local variables */
    
        for (i1 = 0; (i1 < NUMLCL) && (Status == AE_OK); ++i1)
        {
            Status = AmlSetMethodValue (i1 + LCLBASE, NULL, NULL);
        }

        if (AE_OK == Status)
        {
            /*  Copy passed parameters into method stack frame  */
                
            for (i2 = i1 = 0; (i1 < NUMARG) && (AE_OK == Status); ++i1)
            {   
                if (Params && Params[i2])   
                {
                    /*  parameter/argument specified    */
                    /*  define ppsParams[i2++] argument object descriptor   */
                    
                    Status = AmlSetMethodValue (i1 + ARGBASE, Params[i2++], NULL);
                }
                else    
                {
                    /*  no parameter/argument object descriptor definition  */
                    
                    Status = AmlSetMethodValue (i1 + ARGBASE, NULL, NULL);
                }
            }
        }


        /* 
         * Normal exit is with Status == AE_RETURN_VALUE when a ReturnOp has been executed,
         * or with Status == AE_PENDING at end of AML block (end of Method code)
         */

        if (AE_OK == Status)
        {
            while ((Status = AmlDoCode (MODE_Exec)) == AE_OK)
            {;}
        }

        if (AE_PENDING == Status)
        {
            Status = AmlPopExec ();            /* package stack -- inverse of AmlPrepExec() */
        }

        else
        {
            if (AE_RETURN_VALUE == Status)
            {
                DEBUG_PRINT (ACPI_INFO, ("Method returned: \n"));
                DUMP_STACK_ENTRY ((OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop]);
                DEBUG_PRINT (ACPI_INFO, (" at stack level %d\n", ObjStackTop));
            }

            AmlPopExec ();            /* package stack -- inverse of AmlPrepExec() */
        }

        MethodStackTop--;          /* pop our frame off method stack */

    }

    return Status;
}


