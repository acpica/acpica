
/******************************************************************************
 * 
 * Module Name: iexecute - ACPI AML (p-code) execution, top-level routines
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


#define _THIS_MODULE        "iexecute.c"
#define _COMPONENT          INTERPRETER



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
AmlExecuteMethod (
    INT32                   Offset, 
    INT32                   Length, 
    ACPI_OBJECT             **Params)
{
    ACPI_STATUS             Status;
    INT32                   i1;
    INT32                   i2;


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
    
        for (i1 = 0; (i1 < MTH_NUM_LOCALS) && (Status == AE_OK); ++i1)
        {
            Status = AmlMthStackSetValue (i1 + MTH_LOCAL_BASE, NULL, NULL);
        }

        if (AE_OK == Status)
        {
            /*  Copy passed parameters into method stack frame  */
                
            for (i2 = i1 = 0; (i1 < MTH_NUM_ARGS) && (AE_OK == Status); ++i1)
            {   
                if (Params && Params[i2])   
                {
                    /*  parameter/argument specified    */
                    /*  define ppsParams[i2++] argument object descriptor   */
                    
                    Status = AmlMthStackSetValue (i1 + MTH_ARG_BASE, Params[i2++], NULL);
                }
                else    
                {
                    /*  no parameter/argument object descriptor definition  */
                    
                    Status = AmlMthStackSetValue (i1 + MTH_ARG_BASE, NULL, NULL);
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
            Status = AmlPkgPopExec ();            /* package stack -- inverse of AmlPrepExec() */
        }

        else
        {
            if (AE_RETURN_VALUE == Status)
            {
                DEBUG_PRINT (ACPI_INFO, ("Method returned: \n"));
                DUMP_STACK_ENTRY ((ACPI_OBJECT *) ObjStack[ObjStackTop]);
                DEBUG_PRINT (ACPI_INFO, (" at stack level %d\n", ObjStackTop));
            }

            AmlPkgPopExec ();            /* package stack -- inverse of AmlPrepExec() */
        }

        MethodStackTop--;          /* pop our frame off method stack */

    }

    if (ObjStackTop)
    {
        DEBUG_PRINT (ACPI_INFO, ("AmlExecuteMethod: Obj stack at exit %p, idx=%d\n",
                        ObjStack, ObjStackTop));
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecStore
 *
 * PARAMETERS:  *ValDesc            - Value to be stored
 *              *DestDesc           - Where to store it -- must be an (ACPI_HANDLE)
 *                                    or an ACPI_OBJECT of type Lvalue;
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
    ACPI_OBJECT             *ValDesc, 
    ACPI_OBJECT             *DestDesc)
{
    ACPI_HANDLE             TempHandle;
    ACPI_STATUS             Status = AE_AML_ERROR;
    INT32                   Stacked = FALSE;
    BOOLEAN                 Locked = FALSE;
    ACPI_OBJECT             *DeleteDestDesc = NULL;
    UINT8                   *Location=NULL;
    UINT32                  Mask;




    FUNCTION_TRACE ("AmlExecStore");

    DEBUG_PRINT (ACPI_INFO, ("entered AmlExecStore: Val=%p, Dest=%p\n", 
                    ValDesc, DestDesc));

    if (!ValDesc || !DestDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore: internal error - null pointer\n"));
    }

    else if (IS_NS_HANDLE (DestDesc))
    {
        /* Dest is an ACPI_HANDLE */

        TempHandle = (ACPI_HANDLE) DestDesc;
        DestDesc = AllocateObjectDesc ();
        if (!DestDesc)
        {   
            /* Allocation failure  */
            
            FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
            return AE_NO_MEMORY;
        }
        else
        {
            /* DestDesc is valid */

            DestDesc->ValType       = (UINT8) TYPE_Lvalue;
            DestDesc->Lvalue.OpCode = AML_NameOp;
            DestDesc->Lvalue.Ref    = TempHandle;

            /* 
             * Push the descriptor on TOS temporarily
             * to protect it from garbage collection
             */

            Status = AmlObjPushIfExec (MODE_Exec);
            if (AE_OK != Status)
            {
                OsdFree (DestDesc);
                DestDesc = NULL;
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
        /* DestDesc is not an ACPI_HANDLE  */

        DEBUG_PRINT (ACPI_INFO, 
                        ("AmlExecStore: Dest is object (not handle) - may be deleted!\n", 
                        DestDesc));
        Status = AE_OK;
    }

    if ((AE_OK == Status) && 
        (DestDesc->ValType != TYPE_Lvalue))
    {   
        /* Store target is not an Lvalue */

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore: Store target is not an Lvalue [%s]\n",
                        NsTypeNames[DestDesc->ValType]));

        DUMP_STACK_ENTRY (ValDesc);
        DUMP_STACK_ENTRY (DestDesc);
        DUMP_STACK (MODE_Exec, "AmlExecStore", 2, "target not Lvalue");

        Status = AE_AML_ERROR;
    }

    if (AE_OK != Status)
    {
        FUNCTION_STATUS_EXIT (Status);
        return Status;   /* TBD: temporary hack */
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

            DEBUG_PRINT (ACPI_WARN,
                        ("AmlExecStore/NameOp: Store into %s not implemented\n",
                        NsTypeNames[NsGetType(TempHandle)]));
#if 1
            Status = AE_AML_ERROR;
#else
            Status = AE_OK;
#endif
            DeleteDestDesc = DestDesc;
            break;


        case TYPE_BankField:

            /* 
             * Storing into a BankField.
             * If value is not a Number, try to resolve it to one.
             */

            if ((ValDesc->ValType != TYPE_Number) &&
               ((Status = AmlGetRvalue (&ValDesc)) != AE_OK))
            {
                DeleteDestDesc = DestDesc;
            }

            else if (ValDesc->ValType != TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore: Value assigned to BankField must be Number, not %d\n",
                        ValDesc->ValType));

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
                if (Stacked)
                {
                    /* Must clear the top of the stack or it will get deleted twice */

                    ObjStack[ObjStackTop] = NULL;
                }

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

                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* Get the global lock if needed */

                Locked = AmlAcquireGlobalLock (DestDesc->BankField.LockRule);

                /* Set Bank value to select proper Bank */
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
            
            break;  /* Global Lock released below  */


        case TYPE_DefField:

            /* 
             * Storing into a Field defined in a Region.
             * If value is not a Number, try to resolve it to one.
             */

            if ((ValDesc->ValType != TYPE_Number) && 
               ((Status = AmlGetRvalue (&ValDesc)) != AE_OK))
            {
                DeleteDestDesc = DestDesc;
            }

            else if (ValDesc->ValType != TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/DefField: Value assigned to Field must be Number, not %d\n",
                        ValDesc->ValType));

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
                if (Stacked)
                {
                    /* Must clear the top of the stack or it will get deleted twice */

                    ObjStack[ObjStackTop] = NULL;
                }

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

                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* Get the global lock if needed */

                Locked = AmlAcquireGlobalLock (ValDesc->Field.LockRule);

                /* Perform the update */
                
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
                DeleteDestDesc = DestDesc;
            }

            else if (ValDesc->ValType != TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore: Value assigned to IndexField must be Number, not %d\n",
                        ValDesc->ValType));

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
                if (Stacked)
                {
                    /* Must clear the top of the stack or it will get deleted twice */

                    ObjStack[ObjStackTop] = NULL;
                }

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

                Status = AE_AML_ERROR;
            }

            if (AE_OK == Status)
            {
                /* Get the global lock if needed */

                Locked = AmlAcquireGlobalLock (DestDesc->IndexField.LockRule);

                /* Set Index value to select proper Data register */
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
                DeleteDestDesc = DestDesc;
            }

            else if (ValDesc->ValType != TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlExecStore/FieldUnit: Value assigned to Field must be Number, not %d\n",
                          ValDesc->ValType));

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
                if (Stacked)
                {
                    /* Must clear the top of the stack or it will get deleted twice */

                    ObjStack[ObjStackTop] = NULL;
                }

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
                /* Get the global lock if needed */

                Locked = AmlAcquireGlobalLock (DestDesc->FieldUnit.LockRule);
            }

            if ((AE_OK == Status) &&
                (DestDesc->FieldUnit.DatLen + DestDesc->FieldUnit.BitOffset > 32))
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/FieldUnit: implementation limitation: Field exceeds UINT32\n"));
                Status = AE_AML_ERROR;
            }
            
            if (AE_OK == Status)
            {
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

        DeleteDestDesc = DestDesc;
        break;


    case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
    case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:

        Status = AmlMthStackSetValue (MTH_LOCAL_BASE + DestDesc->Lvalue.OpCode - AML_Local0, ValDesc, DestDesc);
        break;


    case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
    case AML_Arg4: case AML_Arg5: case AML_Arg6:

        Status = AmlMthStackSetValue (MTH_ARG_BASE + DestDesc->Lvalue.OpCode - AML_Arg0, ValDesc, DestDesc);
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
                    ("AmlExecStore:internal error: Unknown Lvalue subtype %02x\n",
                    DestDesc->Lvalue.OpCode));
        
        /* TBD:  use object dump routine !! */

        DUMP_BUFFER (DestDesc, sizeof (ACPI_OBJECT),0);

        DeleteDestDesc = DestDesc;
        Status = AE_AML_ERROR;
    
    }   /* switch(DestDesc->Lvalue.OpCode) */


    /* Release global lock if we acquired it earlier */

    AmlReleaseGlobalLock (Locked);

    /* Cleanup */

    if (DeleteDestDesc)
    {
        OsdFree (DeleteDestDesc);
        if (ObjStack[ObjStackTop] == DeleteDestDesc)
        {
            /* 
             * Clear the object from the stack entry so that it won't be used
             * again -- but don't actually pop the stack!
             */

            DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore - Deleted desc was at stack top %p (idx %d)\n",
                            &ObjStack[ObjStackTop], ObjStackTop));
            ObjStack[ObjStackTop] = NULL;
        }
    }

    if (Stacked)
    {
        ObjStack[ObjStackTop] = NULL;
        ObjStackTop--;
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


