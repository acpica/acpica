
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
    {"0000", '1', "ExecStore: Descriptor Allocation Failure", "ExecStore: Descriptor Allocation Failure"},
    {"0001", '1', "GetRvalue: Descriptor Allocation Failure", "GetRvalue: Descriptor Allocation Failure"},
    {"0002", '1', "ExecMonadic2/IncDec: stack overflow", "ExecMonadic2/IncDec: stack overflow"},
    {"0003", '1', "ExecMonadic2/IncDec: Descriptor Allocation Failure", "ExecMonadic2/IncDec: Descriptor Allocation Failure"},
    {"0004", '1', "ExecMonadic2/ObjectTypeOp: Descriptor Allocation Failure", "ExecMonadic2/ObjectTypeOp: Descriptor Allocation Failure"},
    {"0005", '1', "ExecDyadic2R/ConcatOp: String allocation failure", "ExecDyadic2R/ConcatOp: String allocation failure"},
    {"0006", '1', "ExecDyadic2R/ConcatOp: Buffer allocation failure", "ExecDyadic2R/ConcatOp: Buffer allocation failure"},
    {NULL, 'I', NULL, NULL}
};


/*****************************************************************************
 * 
 * FUNCTION:    ExecStore
 *
 * PARAMETERS:  OBJECT_DESCRIPTOR *ValDesc  value to be stored
 *              OBJECT_DESCRIPTOR *DestDesc where to store it -- must be
 *                                          either an (NsHandle) or an
 *                                          OBJECT_DESCRIPTOR of type Lvalue;
 *                                          if the latter the descriptor will
 *                                          be either reused or deleted.
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Store the value described by ValDesc into the location
 *              described by DestDesc.  Called by various interpreter
 *              functions to store the result of an operation into
 *              the destination operand.
 *
 * ALLOCATION:
 *  Reference      Size                    Pool    Owner       Description
 *  nte.ValDesc    s(OBJECT_DESCRIPTOR)    bu      amlexec     Name(Lvalue)
 *
 ****************************************************************************/

INT32
ExecStore(OBJECT_DESCRIPTOR *ValDesc, OBJECT_DESCRIPTOR *DestDesc)
{
    NsHandle        TempHandle;
    INT32           Excep = S_ERROR;
    INT32           Stacked = FALSE;
    INT32           Locked = FALSE;


    FUNCTION_TRACE ("ExecStore");

    DEBUG_PRINT (ACPI_INFO, ("entered ExecStore: Val=%p, Dest=%p\n", 
                    ValDesc, DestDesc));

    if (!ValDesc || !DestDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("ExecStore: internal error: null pointer\n"));
    }

    else if (IsNsHandle (DestDesc))
    {
        /* Dest is an NsHandle */

        TempHandle = (NsHandle) DestDesc;
        DestDesc = AllocateObjectDesc (&KDT[0]);
        if (!DestDesc)
        {   
            /*  allocation failure  */
            
            return S_ERROR;
        }
        else
        {
            /* DestDesc is valid */

            DestDesc->ValType       = (UINT8) Lvalue;
            DestDesc->Lvalue.OpCode = NameOp;
            DestDesc->Lvalue.Ref    = TempHandle;

            /* Push the descriptor on TOS temporarily
             * to protect it from garbage collection
             */
            Excep = PushIfExec (Exec);
            if (S_SUCCESS != Excep)
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

        Excep = S_SUCCESS;
    }

    if ((S_SUCCESS == Excep) && 
        (DestDesc->ValType != Lvalue))
    {   
        /*  Store target is not an Lvalue   */

        DEBUG_PRINT (ACPI_ERROR, ("ExecStore: Store target is not an Lvalue [%s]\n",
                        NsTypeNames[DestDesc->ValType]));

        DUMP_STACK_ENTRY (ValDesc);
        DUMP_STACK_ENTRY (DestDesc);
        DUMP_STACK (Exec, "ExecStore", 2, "target not Lvalue");

        Excep = S_ERROR;
    }

    if (S_SUCCESS != Excep)
    {
        return Excep;   /*  temporary hack  */
    }


    /* Now examine the opcode */

    switch (DestDesc->Lvalue.OpCode)
    {
    case NameOp:

        /* Storing into a Name */

        TempHandle = DestDesc->Lvalue.Ref;
        switch (NsValType (TempHandle)) 
        {
            /* Type of Name's existing value */

        case Alias:
#if 1
            DEBUG_PRINT (ACPI_ERROR, (
                      "ExecStore/NameOp: Store into %s not implemented\n",
                      NsTypeNames[NsValType (TempHandle)]));
            Excep = S_ERROR;
#else
            DEBUG_PRINT (ACPI_WARN,
                        ("ExecStore/NameOp: Store into %s not implemented\n",
                        NsTypeNames[NsValType(TempHandle)]));
            Excep = S_SUCCESS;
#endif
            DELETE (DestDesc);
            break;

        case BankField:

            /* 
             * Storing into a BankField.
             * If value is not a Number, try to resolve it to one.
             */
            if ((ValDesc->ValType != Number) &&
               ((Excep = GetRvalue (&ValDesc)) != S_SUCCESS))
            {
                DELETE (DestDesc);
            }

            else if (ValDesc->ValType != Number)
            {
               DEBUG_PRINT (ACPI_ERROR, (
                        "ExecStore: Value assigned to BankField must be Number, not %d\n",
                        ValDesc->ValType));
                DELETE (DestDesc);
                Excep = S_ERROR;
            }

            else
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DELETE (DestDesc);
                DestDesc = NsValPtr (TempHandle);
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("ExecStore/BankField: internal error: null old-value pointer\n"));
                    Excep = S_ERROR;
                }
            }


            if ((S_SUCCESS == Excep) && 
                (BankField != DestDesc->ValType))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "ExecStore/BankField: internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                        TempHandle, NsValType (TempHandle), DestDesc->ValType, DestDesc));
                AmlAppendBlockOwner (DestDesc);
                Excep = S_ERROR;
            }

            if (S_SUCCESS == Excep)
            {
                /* Set Bank value to select proper Bank */
                /* Check lock rule prior to modifing the field */

                if (DestDesc->BankField.LockRule == (UINT16) Lock)
                {
                    /* Lock Rule is Lock */

                    if (GetGlobalLock () == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! */

                        Excep = S_ERROR;
                    }

                    else
                    {
                        Locked = TRUE;
                    }
                }
            }


            if (S_SUCCESS == Excep)
            {

                /* Perform the update (Set Bank Select) */

                Excep = SetNamedFieldValue (DestDesc->BankField.BankSelect,
                                            DestDesc->BankField.BankVal);

                DEBUG_PRINT (ACPI_INFO,
                            ("ExecStore: set bank select returned %s\n", RV[Excep]));
            }


            if (S_SUCCESS == Excep)
            {
                /* Set bank select successful, next set data value  */
                
                Excep = SetNamedFieldValue (DestDesc->BankField.BankSelect,
                                            ValDesc->BankField.BankVal);
                DEBUG_PRINT (ACPI_INFO,
                            ("ExecStore: set bank select returned %s\n", RV[Excep]));
            }
            
            break;  /*  Global Lock released below  */


        case DefField:

            /* 
             * Storing into a Field defined in a Region.
             * If value is not a Number, try to resolve it to one.
             */

            if ((ValDesc->ValType != Number) && 
               ((Excep = GetRvalue (&ValDesc)) != S_SUCCESS))
            {
                DELETE (DestDesc);
            }

            else if (ValDesc->ValType != Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "ExecStore/DefField: Value assigned to Field must be Number, not %d\n",
                        ValDesc->ValType));
                DELETE (DestDesc);
                Excep = S_ERROR;
            }

            else
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DELETE (DestDesc);
                DestDesc = NsValPtr (TempHandle);
            
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("ExecStore/DefField: internal error: null old-value pointer\n"));
                    Excep = S_ERROR;
                }
            }

            if ((S_SUCCESS == Excep) && 
                (DefField != DestDesc->ValType))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "ExecStore/DefField:internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                        TempHandle, NsValType (TempHandle), DestDesc->ValType, DestDesc));
                AmlAppendBlockOwner (DestDesc);
                Excep = S_ERROR;
            }

            if (S_SUCCESS == Excep)
            {
                /* Check lock rule prior to modifing the field */
            
                if (ValDesc->Field.LockRule == (UINT16) Lock)
                {
                    /* Lock Rule is Lock */
                
                    if (GetGlobalLock () == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock!  */
                    
                        Excep = S_ERROR;
                    }
                    else
                    {
                        Locked = TRUE;
                    }
                }
            }
                
            if (S_SUCCESS == Excep)
            {
                /* perform the update */
                
                Excep = SetNamedFieldValue (TempHandle, ValDesc->Number.Number);
            }
                
            break;      /* Global Lock released below   */


        case IndexField:
            
            /* 
             * Storing into an IndexField.
             * If value is not a Number, try to resolve it to one.
             */
            
            if ((ValDesc->ValType != Number) &&
               ((Excep = GetRvalue (&ValDesc)) != S_SUCCESS))
            {
                DELETE (DestDesc);
            }

            else if (ValDesc->ValType != Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "ExecStore: Value assigned to IndexField must be Number, not %d\n",
                        ValDesc->ValType));
                DELETE (DestDesc);
                Excep = S_ERROR;
            }

            if (S_SUCCESS == Excep)
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */

                DELETE (DestDesc);
                DestDesc = NsValPtr (TempHandle);
            
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("ExecStore/IndexField: internal error: null old-value pointer\n"));
                    Excep = S_ERROR;
                }
            }

            if ((S_SUCCESS == Excep) &&
                (IndexField != DestDesc->ValType))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "ExecStore/IndexField:internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                        TempHandle, NsValType (TempHandle), DestDesc->ValType, DestDesc));
                AmlAppendBlockOwner (DestDesc);
                Excep = S_ERROR;
            }

            if (S_SUCCESS == Excep)
            {
                /* Set Index value to select proper Data register */
                /* Check lock rule prior to modifing the field */
            
                if (DestDesc->IndexField.LockRule == (UINT16) Lock)
                {
                    /* Lock Rule is Lock */
               
                    if (GetGlobalLock () == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock!  */
                    
                        Excep = S_ERROR;
                    }
                    else
                    {
                        Locked = TRUE;
                    }
                }
            }
                
            if (S_SUCCESS == Excep)
            {
                /* perform the update (Set index) */

                Excep = SetNamedFieldValue (DestDesc->IndexField.Index,
                                            DestDesc->IndexField.IndexVal);
                DEBUG_PRINT (ACPI_INFO,
                            ("ExecStore: IndexField: set index returned %s\n", RV[Excep]));
            }

            if (S_SUCCESS == Excep)
            {
                /* set index successful, next set Data value */
                
                Excep = SetNamedFieldValue (DestDesc->IndexField.Data,
                                            ValDesc->Number.Number);
                DEBUG_PRINT (ACPI_INFO,
                            ("ExecStore: IndexField: set data returned %s\n", RV[Excep]));
            }

            break;      /* Global Lock released below   */


        case FieldUnit:
            
            /* 
             * Storing into a FieldUnit (defined in a Buffer).
             * If value is not a Number, try to resolve it to one.
             */
            if ((ValDesc->ValType != Number) &&
               ((Excep = GetRvalue (&ValDesc)) != S_SUCCESS))
            {
                DELETE (DestDesc);
            }

            else if (ValDesc->ValType != Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "ExecStore/FieldUnit: Value assigned to Field must be Number, not %d\n",
                          ValDesc->ValType));
                DELETE (DestDesc);
                Excep = S_ERROR;
            }


            if (S_SUCCESS == Excep)
            {
                /* 
                 * Delete descriptor that points to name,
                 * and point to descriptor for name's value instead.
                 */
                DELETE (DestDesc);
                DestDesc = NsValPtr (TempHandle);
            
                if (!DestDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("ExecStore/FieldUnit: internal error: null old-value pointer\n"));
                    Excep = S_ERROR;
                }

                else
                {
                    DEBUG_PRINT (ACPI_INFO,
                        ("ExecStore: FieldUnit: name's value DestDesc=%p, DestDesc->ValType=%02Xh\n",
                        DestDesc, DestDesc->ValType));
                }
            }

            if ((S_SUCCESS == Excep) &&
                (DestDesc->ValType != (UINT8) NsValType (TempHandle)))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "ExecStore/FieldUnit:internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                          TempHandle, NsValType(TempHandle), DestDesc->ValType, DestDesc));
                AmlAppendBlockOwner (DestDesc);
                Excep = S_ERROR;
            }

            if ((S_SUCCESS == Excep) &&
               (!DestDesc->FieldUnit.Container ||
                Buffer != DestDesc->FieldUnit.Container->ValType ||
                DestDesc->FieldUnit.ConSeq
                    != DestDesc->FieldUnit.Container->Buffer.Sequence))
            {
                char *FullyQN = NsFullyQualifiedName (TempHandle);


                DEBUG_PRINT (ACPI_ERROR,
                            ("ExecStore/FieldUnit: bad container in %s (%p)\n",
                             FullyQN, TempHandle));
                DUMP_ENTRY (TempHandle);


                DEBUG_PRINT (ACPI_ERROR, (
                            "ExecStore/FieldUnit: bad container %p in %s\n",
                            DestDesc->FieldUnit.Container, FullyQN));
                Excep = S_ERROR;
            }

            if (S_SUCCESS == Excep)
            {
                /* Check lock rule prior to modifing the field */
            
                if (DestDesc->FieldUnit.LockRule == (UINT16) Lock)
                {
                    /* Lock Rule is Lock */
                
                    if (GetGlobalLock () == S_ERROR)
                    {
                        /* the ownship failed - Bad Bad Bad, this is a single threaded */
                        /* implementation so there is no way some other process should */
                        /* own this.  This means something grabbed it and did not */
                        /* release the Global Lock! */
                    
                        Excep = S_ERROR;
                    }
                
                    else
                    {
                        /* Set the Locked Flag */
                    
                        Locked = TRUE;
                    }
                }
            }

            if ((S_SUCCESS == Excep) &&
                (DestDesc->FieldUnit.DatLen + DestDesc->FieldUnit.BitOffset > 32))
            {
                DEBUG_PRINT (ACPI_ERROR, ("ExecStore/FieldUnit: implementation limitation: Field exceeds UINT32\n"));
                Excep = S_ERROR;
            }
            
            if (S_SUCCESS == Excep)
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
                Mask = ((UINT32) 1 << DestDesc->FieldUnit.DatLen) - (UINT32)1
                                    << DestDesc->FieldUnit.BitOffset;

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
            
            if (Buffer == DestDesc->ValType)
            {
                /* Assign a new sequence number */

                DestDesc->Buffer.Sequence = AmlBufSeq ();
            }

            NsSetValue (TempHandle, DestDesc, DestDesc->ValType);

            if (Stacked)
            {
                DEBUG_PRINT (ACPI_INFO, ("ExecStore: set %s (%p)\n",
                             NsFullyQualifiedName (TempHandle), TempHandle));
                DUMP_ENTRY (TempHandle);
                DUMP_STACK_ENTRY (DestDesc);
            }

            break;
        }

        break;  /* Case NameOp */


    case ZeroOp: case OneOp: case OnesOp:

        /* 
         * Storing to a constant is a no-op -- see spec sec 15.2.3.3.1.
         * Delete the result descriptor.
         */
        DELETE (DestDesc);
        break;


    case Local0: case Local1: case Local2: case Local3:
    case Local4: case Local5: case Local6: case Local7:

        Excep = SetMethodValue (LCLBASE + DestDesc->Lvalue.OpCode - Local0, ValDesc, DestDesc);
        break;


    case Arg0: case Arg1: case Arg2: case Arg3:
    case Arg4: case Arg5: case Arg6:

        Excep = SetMethodValue (ARGBASE + DestDesc->Lvalue.OpCode - Arg0, ValDesc, DestDesc);
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
                    ("ExecStore:internal error: Unknown Lvalue subtype %02x\n",
                    DestDesc->Lvalue.OpCode));
        
        /* TBD:  use object dump routine !! */

        DUMP_BUFFER (DestDesc, sizeof (OBJECT_DESCRIPTOR),0);

        DELETE (DestDesc);
        Excep = S_ERROR;
    
    }   /* switch(DestDesc->Lvalue.OpCode) */


    if (Locked)
    {
        /* Release lock if we own it */

        ReleaseGlobalLock ();
    }

    if (Stacked)
    {
        ObjStackTop--;
    }

    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecMonadic1
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 1 monadic operator
 *              with numeric operand on object stack
 *
 * ALLOCATION:  Deletes the operand
 *
 ****************************************************************************/

INT32
ExecMonadic1 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR *     ObjDesc;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecMonadic1");


    if (SleepOp == opcode || StallOp == opcode)
    {
        Excep = PrepStack ("n");                 /* operand should be a Number */
    }
    else
    {
        Excep = PrepStack ("l");                 /* operand should be an Lvalue */
    }

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 1);
        return Excep;
    }


    DumpStack (Exec, LongOps[opcode & 0x00ff], 1, "after PrepStack");

    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];

    switch (opcode)
    {

    /*  DefRelease  :=  ReleaseOp   MutexObject */

    case ReleaseOp:
        if (Mutex != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "ExecMonadic1/ReleaseOp: Needed Mutex, found %d\n",
                    ObjDesc->ValType));
            return S_ERROR;
        }

        return (ReleaseOpRqst (ObjDesc));


    /*  DefReset        :=  ResetOp     EventObject */

    case ResetOp:
        if (Event != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "ExecMonadic1/ResetOp: Needed Event, found %d\n", ObjDesc->ValType));
            return S_ERROR;
        }

        return (ResetOpRqst (ObjDesc));


    /*  DefSignal   :=  SignalOp        EventObject */
    
    case SignalOp:
        if (Event != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "ExecMonadic1/SignalOp: Needed Event, found %d\n", ObjDesc->ValType));
            return S_ERROR;
        }
        return (SignalOpRqst (ObjDesc));


    /*  DefSleep    :=  SleepOp MsecTime    */
    
    case SleepOp:
        DoSuspend (ObjDesc->Number.Number);
        break;


    /*  DefStall    :=  StallOp UsecTime    */
    
    case StallOp:
        OsdSleepUsec (ObjDesc->Number.Number);
        break;


    /*  unknown opcode  */
    
    default:
        DEBUG_PRINT (ACPI_ERROR, ("ExecMonadic1: Unknown monadic opcode %02x\n", opcode));
        return S_ERROR;
    
    } /* switch */


    DELETE (ObjDesc);
    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecMonadic2R
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 monadic operator with numeric operand and
 *              result operand on operand stack
 *
 ****************************************************************************/

INT32
ExecMonadic2R (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ResDesc;
    UINT32                  ResVal;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecMonadic2R");


    Excep = PrepStack ("ln");

    if (Excep != S_SUCCESS)
    {
        /* Invalid parameters on object stack   */
        /* This was added since it is allowable to return a buffer so */
        /* ln is a local and a number and that will fail.  lb is a local */
        /* and a buffer which will pass.  */
        
        Excep = PrepStack ("lb");

        if (Excep != S_SUCCESS)
        {
            AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
            return Excep;
        }
    }

    DumpStack (Exec, ShortOps[opcode], 2, "after PrepStack");

    ResDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    switch (opcode)
    {
        INT32           d0, d1, d2, d3;


    /*  DefNot  :=  NotOp   Operand Result  */
    
    case BitNotOp:
        ObjDesc->Number.Number = ~ObjDesc->Number.Number;
        break;


    /*  DefFindSetLeftBit   :=  FindSetLeftBitOp    Operand Result  */

    case FindSetLeftBitOp:
        for (ResVal = 0; ObjDesc->Number.Number && ResVal < 33; ++ResVal)
        {
            ObjDesc->Number.Number >>= 1;
        }

        ObjDesc->Number.Number = ResVal;
        break;


    /*  DefFindSetRightBit  :=  FindSetRightBitOp   Operand Result  */

    case FindSetRightBitOp:
        for (ResVal = 0; ObjDesc->Number.Number && ResVal < 33; ++ResVal)
        {
            ObjDesc->Number.Number <<= 1;
        }

        ObjDesc->Number.Number = ResVal == 0 ? 0 : 33 - ResVal;
        break;


    /*  DefFromBDC  :=  FromBCDOp   BCDValue    Result  */

    case FromBCDOp:
        d0 = (INT32) (ObjDesc->Number.Number & 15);
        d1 = (INT32) (ObjDesc->Number.Number >> 4 & 15);
        d2 = (INT32) (ObjDesc->Number.Number >> 8 & 15);
        d3 = (INT32) (ObjDesc->Number.Number >> 12 & 15);
        
        if (d0 > 9 || d1 > 9 || d2 > 9 || d3 > 9)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "ExecMonadic2R/FromBCDOp: improper BCD digit %d %d %d %d\n",
                    d3, d2, d1, d0));
            return S_ERROR;
        }
        
        ObjDesc->Number.Number = d0 + d1 * 10 + d2 * 100 + d3 * 1000;
        break;


    /*  DefToBDC    :=  ToBCDOp Operand Result  */
    
    case ToBCDOp:
        if (ObjDesc->Number.Number > 9999)
        {
            DEBUG_PRINT (ACPI_ERROR, ("iExecMonadic2R/ToBCDOp: BCD overflow: %d\n",
                    ObjDesc->Number.Number));
            return S_ERROR;
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

    case ShiftLeftBitOp:
    case ShiftRightBitOp:
    case CondRefOfOp:
        
        DEBUG_PRINT (ACPI_ERROR, ("ExecMonadic2R: %s unimplemented\n",
                (opcode > UCHAR_MAX) ? LongOps[opcode & 0x00ff] : ShortOps[opcode]));
        return S_ERROR;

    case StoreOp:
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("ExecMonadic2R: internal error: Unknown monadic opcode %02x\n",
                    opcode));
        return S_ERROR;
    }
    
    Excep = ExecStore (ObjDesc, ResDesc);
    ObjStackTop--;

    DEBUG_PRINT (TRACE_EXEC, ("leave iExecMonadic2R: %s\n", RV[Excep]));
    
    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecMonadic2
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 monadic operator with numeric operand:
 *              DerefOfOp, RefOfOp, SizeOfOp, TypeOp, IncrementOp,
 *              DecrementOp, LNotOp,
 *
 * ALLOCATION:
 *  Reference   Size                    Pool    Owner       Description
 *  ObjStack    s(OBJECT_DESCRIPTOR)    bu      amlexec     Number
 *
 ****************************************************************************/

INT32
ExecMonadic2 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ResDesc;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecMonadic2");


    if (LNotOp == opcode)
    {
        Excep = PrepStack ("n");
    }
    else
    {
        Excep = PrepStack ("l");
    }

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 1);
        return Excep;
    }

    DumpStack (Exec, ShortOps[opcode], 1, "after PrepStack");

    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];


    switch (opcode)
    {

    /*  DefLNot :=  LNotOp  Operand */

    case LNotOp:
        ObjDesc->Number.Number = (!ObjDesc->Number.Number) - (UINT32) 1;
        break;


    /*  DefDecrement    :=  DecrementOp Target  */
    /*  DefIncrement    :=  IncrementOp Target  */

    case DecrementOp:
    case IncrementOp:

        if ((Excep = PushIfExec (Exec)) != S_SUCCESS)
        {
            REPORT_ERROR (&KDT[2]);
            return S_ERROR;
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
            return S_ERROR;
        }

        /* Convert the top copy to a Number */
        
        Excep = PrepStack ("n");
        if (Excep != S_SUCCESS)
        {
            AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 1);
            return Excep;
        }

        /* get the Number in ObjDesc and the Lvalue in ResDesc */
        
        ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
        ResDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

        /* do the ++ or -- */
        
        if (IncrementOp == opcode)
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
        
        Excep = ExecStore (ObjDesc, ResDesc);
        ObjStackTop--;
        return Excep;



    /*  DefObjectType   :=  ObjectTypeOp    SourceObject    */

    case TypeOp:
        
        /* This case uses Excep to hold the type encoding */
        
        if (Lvalue == ObjDesc->ValType)
        {
            /* 
             * Not a Name -- an indirect name pointer would have
             * been converted to a direct name pointer in PrepStack
             */
            switch (ObjDesc->Lvalue.OpCode)
            {
            case ZeroOp: case OneOp: case OnesOp:
                
                /* Constants are of type Number */
                
                Excep = (INT32) Number;
                break;

            case Debug1:
                
                /* Per spec, Debug object is of type Region */
                
                Excep = (INT32) Region;
                break;

            case IndexOp:
                DEBUG_PRINT (ACPI_ERROR, ("ExecMonadic2/TypeOp: determining type of Index result is not implemented\n"));
                return S_ERROR;

            case Local0: case Local1: case Local2: case Local3:
            case Local4: case Local5: case Local6: case Local7:
                Excep = (INT32) GetMethodValTyp (LCLBASE + ObjDesc->Lvalue.OpCode - Local0);
                break;

            case Arg0: case Arg1: case Arg2: case Arg3:
            case Arg4: case Arg5: case Arg6:
                Excep = (INT32) GetMethodValTyp (ARGBASE + ObjDesc->Lvalue.OpCode - Arg0);
                break;

            default:
                DEBUG_PRINT (ACPI_ERROR, (
                        "ExecMonadic2/TypeOp:internal error: Unknown Lvalue subtype %02x\n",
                        ObjDesc->Lvalue.OpCode));
                return S_ERROR;
            }
        }
        
        else
        {
            /* 
             * Since we passed PrepStack("l") and it's not an Lvalue,
             * it must be a direct name pointer.  Allocate a descriptor
             * to hold the type.
             */
            Excep = (INT32) NsValType ((NsHandle) ObjDesc);

            ObjDesc = AllocateObjectDesc (&KDT[4]);
            if (!ObjDesc)
            {
                return S_ERROR;
            }

            /* 
             * Replace (NsHandle) on TOS with descriptor containing result.
             * No need to DeleteObject() first since TOS is an NsHandle.
             */

            ObjStack[ObjStackTop] = (void *) ObjDesc;
        }
        
        ObjDesc->ValType = (UINT8) Number;
        ObjDesc->Number.Number = (UINT32) Excep;
        break;


    /*  DefSizeOf   :=  SizeOfOp    SourceObject    */

    case SizeOfOp:
        switch (ObjDesc->ValType)
        {
        case Buffer:
            ObjDesc->Number.Number = ObjDesc->Buffer.BufLen;
            ObjDesc->ValType = (UINT8) Number;
            break;

        case String:
            ObjDesc->Number.Number = ObjDesc->String.StrLen;
            ObjDesc->ValType = (UINT8) Number;
            break;

        case Package:
            ObjDesc->Number.Number = ObjDesc->Package.PkgCount;
            ObjDesc->ValType = (UINT8) Number;
            break;

        default:
           DEBUG_PRINT (ACPI_ERROR, (
                    "ExecMonadic2: Needed aggregate, found %d\n", ObjDesc->ValType));
            return S_ERROR;
        }
        break;


    /*  DefRefOf    :=  RefOfOp     SourceObject    */
    /*  DefDerefOf  :=  DerefOfOp   ObjReference    */

    case RefOfOp:
    case DerefOfOp:
        DEBUG_PRINT (ACPI_ERROR, ("ExecMonadic2: %s unimplemented\n",
                (opcode > UCHAR_MAX) ? LongOps[opcode & 0x00ff] : ShortOps[opcode]));
        ObjStackTop++;  /*  dummy return value  */
        return S_ERROR;

    default:
        DEBUG_PRINT (ACPI_ERROR, (
                    "ExecMonadic2:internal error: Unknown monadic opcode %02x\n",
                    opcode));
        return S_ERROR;
    }

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecDyadic1
 *
 * PARAMETERS:  UINT16 opcode  The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 1 dyadic operator with numeric operands:
 *              NotifyOp
 *
 * ALLOCATION:  Deletes both operands
 *
 ****************************************************************************/

INT32
ExecDyadic1 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc = NULL;
    OBJECT_DESCRIPTOR       *ValDesc = NULL;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecDyadic1");


    Excep = PrepStack ("nl");

    if (Excep != S_SUCCESS)
    {
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
        return Excep;
    }

    DumpStack (Exec, ShortOps[opcode], 2, "after PrepStack");

    ValDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    switch (opcode)
    {


    /*  DefNotify   :=  NotifyOp    NotifyObject    NotifyValue */

    case NotifyOp:

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
            case Device:
            case Thermal:
            
                /* XXX - Requires that sDevice and sThermalZone
                 * XXX - be compatible mappings
                 */

                DoNotifyOp (ValDesc, ObjDesc);
                break;

            default:
                DEBUG_PRINT (ACPI_ERROR, (
                        "ExecDyadic1/NotifyOp: unexpected notify object type %d\n",
                        ObjDesc->ValType));
                return S_ERROR;
            }
        }
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR, ("ExecDyadic1: Unknown dyadic opcode %02x\n", opcode));
        return S_ERROR;
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

    return S_SUCCESS;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecDyadic2R
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 dyadic operator with numeric operands and
 *              one or two result operands
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *  Reference       Size        Pool    Owner   Description
 *  String.String varies     bu    amlexec   result of Concat
 *  Buffer.Buffer varies     bu    amlexec   result of Concat
 *
 ****************************************************************************/

INT32
ExecDyadic2R (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc = NULL;
    OBJECT_DESCRIPTOR       *ObjDesc2 = NULL;
    OBJECT_DESCRIPTOR       *ResDesc = NULL;
    OBJECT_DESCRIPTOR       *ResDesc2 = NULL;
    UINT32                  remain;
    INT32                   Excep;
    INT32                   NumOperands;


    FUNCTION_TRACE ("ExecDyadic2R");


    switch (opcode)
    {


    /*  DefConcat   :=  ConcatOp    Data1   Data2   Result  */

    case ConcatOp:
        Excep = PrepStack ("lss");
        NumOperands = 3;
        break;


    /*  DefDivide   :=  DivideOp Dividend Divisor Remainder Quotient    */

    case DivideOp:
        Excep = PrepStack ("llnn");
        NumOperands = 4;
        break;


    /*  DefX    :=  XOp Operand1    Operand2    Result  */

    default:
        Excep = PrepStack ("lnn");
        NumOperands = 3;
        break;
    }

    if (Excep != S_SUCCESS)
    {
        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, NumOperands);
        return Excep;
    }

    DumpStack (Exec, ShortOps[opcode], NumOperands, "after PrepStack");

    if (DivideOp == opcode)
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

    case AddOp:
        ObjDesc->Number.Number += ObjDesc2->Number.Number;
        break;
 
        
    /*  DefAnd  :=  AndOp   Operand1    Operand2    Result  */

    case BitAndOp:
        ObjDesc->Number.Number &= ObjDesc2->Number.Number;
        break;

        
    /*  DefNAnd :=  NAndOp  Operand1    Operand2    Result  */

    case BitNandOp:
        ObjDesc->Number.Number = ~(ObjDesc->Number.Number & ObjDesc2->Number.Number);
        break;
   
       
    /*  DefOr       :=  OrOp    Operand1    Operand2    Result  */
        
    case BitOrOp:
        ObjDesc->Number.Number |= ObjDesc2->Number.Number;
        break;

        
    /*  DefNOr  :=  NOrOp   Operand1    Operand2    Result  */

    case BitNorOp:
        ObjDesc->Number.Number = ~(ObjDesc->Number.Number | ObjDesc2->Number.Number);
        break;

        
    /*  DefXOr  :=  XOrOp   Operand1    Operand2    Result  */

    case BitXorOp:
        ObjDesc->Number.Number ^= ObjDesc2->Number.Number;
        break;

        
    /*  DefDivide   :=  DivideOp Dividend Divisor Remainder Quotient    */

    case DivideOp:
        if ((UINT32) 0 == ObjDesc2->Number.Number)
        {
            DEBUG_PRINT (ACPI_ERROR, ("ExecDyadic2R/DivideOp: divide by zero\n"));
            return S_ERROR;
        }

        remain = ObjDesc->Number.Number % ObjDesc2->Number.Number;
        ObjDesc->Number.Number /= ObjDesc2->Number.Number;
        ObjDesc2->Number.Number = remain;
        break;

        
    /*  DefMultiply :=  MultiplyOp  Operand1    Operand2    Result  */

    case MultiplyOp:
        ObjDesc->Number.Number *= ObjDesc2->Number.Number;
        break;

        
    /*  DefShiftLeft    :=  ShiftLeftOp Operand ShiftCount  Result  */

    case ShiftLeftOp:
        ObjDesc->Number.Number <<= ObjDesc2->Number.Number;
        break;

        
    /*  DefShiftRight   :=  ShiftRightOp    Operand ShiftCount  Result  */

    case ShiftRightOp:
        ObjDesc->Number.Number >>= ObjDesc2->Number.Number;
        break;

        
    /*  DefSubtract :=  SubtractOp  Operand1    Operand2    Result  */

    case SubtractOp:
        ObjDesc->Number.Number -= ObjDesc2->Number.Number;
        break;


    /*  DefConcat   :=  ConcatOp    Data1   Data2   Result  */

    case ConcatOp:
        if (ObjDesc2->ValType != ObjDesc->ValType)
        {
            DEBUG_PRINT (ACPI_ERROR, (
                    "ExecDyadic2R/ConcatOp: operand type mismatch %d %d\n",
                    ObjDesc->ValType, ObjDesc2->ValType));
            return S_ERROR;
        }

        /* Both operands are now known to be the same */
        
        if (String == ObjDesc->ValType)
        {
            /*  Operand1 is string  */

            char *NewBuf = OsdAllocate ((size_t) (ObjDesc->String.StrLen
                                                + ObjDesc2->String.StrLen + 1));
            if (!NewBuf)
            {
                REPORT_ERROR (&KDT[5]);
                return S_ERROR;
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
                    return S_ERROR;
                }

                DEBUG_PRINT (ACPI_ERROR, (
                            "ExecDyadic2R/ConcatOp: Buffer allocation failure %d\n",
                            ObjDesc->Buffer.BufLen + ObjDesc2->Buffer.BufLen));
                return S_ERROR;
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
        DEBUG_PRINT (ACPI_ERROR, ("ExecDyadic2R: Unknown dyadic opcode %02x\n", opcode));
        return S_ERROR;
    }
    
    if ((Excep = ExecStore (ObjDesc, ResDesc)) != S_SUCCESS)
    {
        ObjStackTop -= NumOperands - 1;
        return Excep;
    }
    
    if (DivideOp == opcode)
    {
        Excep = ExecStore(ObjDesc2, ResDesc2);
    }

    /* Don't delete ObjDesc because it remains on the stack */
    /* deleting psObjDescOperand2 is valid for DivideOp since we preserved
     * remainder on stack
     */
    
    DELETE (ObjDesc2);
    ObjStackTop -= NumOperands - 1;
    
    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecDyadic2S
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 dyadic synchronization operator
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *
 ****************************************************************************/

INT32
ExecDyadic2S (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *TimeDesc;
    OBJECT_DESCRIPTOR       *ResDesc;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecDyadic2S");


    Excep = PrepStack ("nl");

    if (Excep != S_SUCCESS)
    {   
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
    }

    else
    {
        DumpStack (Exec, LongOps[opcode & 0x00ff], 2, "after PrepStack");

        TimeDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
        ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

        switch (opcode)
        {


        /*  DefAcquire  :=  AcquireOp   MutexObject Timeout */

        case AcquireOp:
            if (Mutex != ObjDesc->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "ExecDyadic2S/AcquireOp: Needed Mutex, found %d\n",
                        ResDesc->ValType));
                Excep = S_ERROR;
            }
            else
            {
                Excep = AcquireOpRqst (TimeDesc, ObjDesc);
            }



        /*  DefWait :=  WaitOp  EventObject Timeout */

        case WaitOp:
            if (Event != ObjDesc->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "ExecDyadic2S/WaitOp: Needed Event, found %d\n",
                        ResDesc->ValType));
                Excep = S_ERROR;
            }
            else
            {
                Excep = WaitOpRqst (TimeDesc, ObjDesc);
            }


        default:
            DEBUG_PRINT (ACPI_ERROR, (
                    "ExecDyadic2S: Unknown dyadic synchronization opcode %02x\n",
                    opcode));
            Excep = S_ERROR;
        }

        /*  delete TimeOut object descriptor before removing it from object stack   */
    
        DELETE (TimeDesc);

        /*  remove TimeOut parameter from object stack  */

        ObjStackTop--;
    
    }
    return Excep;
}


/*****************************************************************************
 * 
 * FUNCTION:    ExecDyadic2
 *
 * PARAMETERS:  UINT16  opcode      The opcode to be executed
 *
 * RETURN:      S_SUCCESS or S_ERROR
 *
 * DESCRIPTION: Execute Type 2 dyadic operator with numeric operands and
 *              no result operands
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *              containing result value
 *
 ****************************************************************************/

INT32
ExecDyadic2 (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ObjDesc;
    OBJECT_DESCRIPTOR       *ObjDesc2;
    INT32                   Excep;


    FUNCTION_TRACE ("ExecDyadic2");


    Excep = PrepStack ("nn");

    if (Excep != S_SUCCESS)
    {
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, 2);
        return Excep;
    }

    DumpStack (Exec, ShortOps[opcode], 2, "after PrepStack");

    ObjDesc2 = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    ObjDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];

    switch (opcode)
    {


    /*  DefLAnd :=  LAndOp  Operand1    Operand2    */

    case LAndOp:
        if (ObjDesc->Number.Number && ObjDesc2->Number.Number)
            Excep = 1;
        else
            Excep = 0;
        break;


    /*  DefLEqual   :=  LEqualOp    Operand1    Operand2    */

    case LEqualOp:
        if (ObjDesc->Number.Number == ObjDesc2->Number.Number)
            Excep = 1;
        else
            Excep = 0;
        break;


    /*  DefLGreater :=  LGreaterOp  Operand1    Operand2    */

    case LGreaterOp:
        if (ObjDesc->Number.Number > ObjDesc2->Number.Number)
            Excep = 1;
        else
            Excep = 0;
        break;


    /*  DefLLess    :=  LLessOp Operand1    Operand2    */

    case LLessOp:
        if (ObjDesc->Number.Number < ObjDesc2->Number.Number)
            Excep = 1;
        else
            Excep = 0;
        break;


    /*  DefLOr  :=  LOrOp   Operand1    Operand2    */

    case LOrOp:
        if (ObjDesc->Number.Number || ObjDesc2->Number.Number)
            Excep = 1;
        else
            Excep = 0;
        break;
    
    default:
        DEBUG_PRINT (ACPI_ERROR, ("ExecDyadic2: Unknown dyadic opcode %02x\n", opcode));
        return S_ERROR;
    }

    /* ObjDesc->ValType == Number was assured by PrepStack("nn") call */
    
    if (Excep)
    {
        ObjDesc->Number.Number = 0xffffffff;
    }
    else
    {
        ObjDesc->Number.Number = 0;
    }

    DELETE (ObjDesc2);
    ObjStackTop--;
    
    return S_SUCCESS;
}


/******************************************************************************
 * 
 * FUNCTION:    AmlExec
 *
 * PARAMETERS:  INT32               Offset      Offset to method in code block
 *              INT32               Length      Length of method
 *              OBJECT_DESCRIPTOR   **Params    list of parameters to pass to
 *                                              method, terminated by NULL.
 *                                              Params itself may be NULL if
 *                                              no parameters are being passed.
 *
 * RETURN:      S_SUCCESS, S_RETURN, or S_ERROR
 *
 * DESCRIPTION: Execute the method
 *
 *****************************************************************************/

INT32
AmlExec (INT32 Offset, INT32 Length, OBJECT_DESCRIPTOR **Params)
{
    INT32           Excep;
    INT32           i1;
    INT32           i2;


    FUNCTION_TRACE ("AmlExec");


    if (Excep = AmlPrepExec (Offset, Length) != S_SUCCESS)               /* package stack */
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExec: Exec Stack Overflow\n"));
    }

    /* Push new frame on Method stack */
    
    else if (++MethodStackTop >= AML_METHOD_MAX_NEST)
    {
        MethodStackTop--;
        DEBUG_PRINT (ACPI_ERROR, ("AmlExec: Method Stack Overflow\n"));
        Excep = S_ERROR;
    }

    else
    {
        /* Undefine all local variables */
    
        for (i1 = 0; (i1 < NUMLCL) && (Excep == S_SUCCESS); ++i1)
        {
            Excep = SetMethodValue (i1 + LCLBASE, NULL, NULL);
        }

        if (S_SUCCESS == Excep)
        {
            /*  Copy passed parameters into method stack frame  */
                
            for (i2 = i1 = 0; (i1 < NUMARG) && (S_SUCCESS == Excep); ++i1)
            {   
                if (Params && Params[i2])   
                {
                    /*  parameter/argument specified    */
                    /*  define ppsParams[i2++] argument object descriptor   */
                    
                    Excep = SetMethodValue (i1 + ARGBASE, Params[i2++], NULL);
                }
                else    
                {
                    /*  no parameter/argument object descriptor definition  */
                    
                    Excep = SetMethodValue (i1 + ARGBASE, NULL, NULL);
                }
            }
        }


        LINE_SET (0, Exec);


        /* 
         * Normal exit is with Excep == S_RETURN when a ReturnOp has been executed,
         * or with Excep == S_FAILURE at end of AML block (end of Method code)
         */

        if (S_SUCCESS == Excep)
        {
            while ((Excep = DoCode (Exec)) == S_SUCCESS)
            {;}
        }

        if (S_FAILURE == Excep)
        {
            Excep = PopExec ();            /* package stack -- inverse of AmlPrepExec() */
        }

        else
        {
            if (S_RETURN == Excep)
            {
                DEBUG_PRINT (ACPI_INFO, ("Method returned: \n"));
                DUMP_STACK_ENTRY ((OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop]);
                DEBUG_PRINT (ACPI_INFO, (" at stack level %d\n", ObjStackTop));
            }

            PopExec ();            /* package stack -- inverse of AmlPrepExec() */
        }

        MethodStackTop--;          /* pop our frame off method stack */

    }

    return Excep;
}


