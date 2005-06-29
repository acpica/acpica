
/******************************************************************************
 * 
 * Module Name: ievalue - ACPI AML (p-code) execution - get value routines
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
 * license (without the right to sublicense), under only those claims of Intel
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

#define __IEVALUE_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>


#define _THIS_MODULE        "ievalue.c"
#define _COMPONENT          INTERPRETER



/*****************************************************************************
 * 
 * FUNCTION:    AmlIsMethodValue
 *
 * PARAMETERS:  *ObjDesc 
 *
 * RETURN:      TRUE if the descriptor is the value of an Arg or
 *              Local in a currently-active Method, else FALSE
 *
 * DESCRIPTION: Test if object is the value of an Arg or Local in a currently
 *              active method.
 *
 ****************************************************************************/

BOOLEAN
AmlIsMethodValue (
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{
    INT32                   MethodNestLevel;
    INT32                   Index;


    FUNCTION_TRACE ("AmlIsMethodValue");


    /* For each active Method */
    
    for (MethodNestLevel = MethodStackTop; MethodNestLevel >= 0; --MethodNestLevel)
    {
        /* For each possible Arg and Local */
        
        for (Index = 0; Index < (MTH_ARG_BASE + MTH_NUM_ARGS); ++Index)
        {
            if (ObjDesc == MethodStack[MethodNestLevel][Index])
            {
                FUNCTION_EXIT;
                return TRUE;
            }
        }
    }

    FUNCTION_EXIT;
    return FALSE;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlGetFieldUnitValue
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
AmlGetFieldUnitValue (
    ACPI_OBJECT_INTERNAL    *FieldDesc, 
    ACPI_OBJECT_INTERNAL    *ResultDesc)
{
    ACPI_STATUS             Status = AE_AML_ERROR;
    UINT32                  Mask;
    UINT8                   *Location = NULL;
    BOOLEAN                 Locked = FALSE;


    FUNCTION_TRACE ("AmlGetFieldUnitValue");


    if (!FieldDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: internal error - null field pointer\n"));
    }

    else if (!FieldDesc->FieldUnit.Container)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: internal error - null container pointer\n"));
    }

    else if (TYPE_Buffer != FieldDesc->FieldUnit.Container->Type)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: internal error - container is not a Buffer\n"));
    }

    else if (FieldDesc->FieldUnit.Sequence
                != FieldDesc->FieldUnit.Container->Buffer.Sequence)
    {
        DEBUG_PRINT (ACPI_ERROR, (
                "AmlGetFieldUnitValue: internal error - stale Buffer [%lx != %lx]\n",
                FieldDesc->FieldUnit.Sequence,
                FieldDesc->FieldUnit.Container->Buffer.Sequence));
    }

    else if (!ResultDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: internal error - null result pointer\n"));
    }

    else 
    {
        /* Input parameters are valid */

        Status = AE_OK;

        /* Get the global lock if needed */

        Locked = AmlAcquireGlobalLock (FieldDesc->FieldUnit.LockRule);
    }

    if (AE_OK == Status)
    {   
        /* Input parameters valid and global lock possibly acquired */

        if (FieldDesc->FieldUnit.Length + FieldDesc->FieldUnit.BitOffset > 32)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: implementation limitation: Field exceeds UINT32\n"));
            Status = AE_AML_ERROR;
        }
    }

    if (AE_OK == Status)
    {   
        /* Field location is (base of buffer) + (byte offset) */
    
        Location = FieldDesc->FieldUnit.Container->Buffer.Pointer
                    + FieldDesc->FieldUnit.Offset;

        /* Construct Mask with as many 1 bits as the field width */
    
        Mask = ((UINT32) 1 << FieldDesc->FieldUnit.Length) - (UINT32) 1;

        ResultDesc->Number.Type = (UINT8) TYPE_Number;

        /* Shift the word containing the field, and mask the value */
    
        ResultDesc->Number.Value
            = *(UINT32 *) Location >> FieldDesc->FieldUnit.BitOffset & Mask;

        DEBUG_PRINT (ACPI_INFO,
            ("** Read from buffer %p byte %ld bit %d width %d addr %p mask %08lx val %08lx\n",
            FieldDesc->FieldUnit.Container->Buffer.Pointer,
            FieldDesc->FieldUnit.Offset,
            FieldDesc->FieldUnit.BitOffset,
            FieldDesc->FieldUnit.Length,
            Location, Mask, ResultDesc->Number.Value));
    }

    /* Release global lock if we acquired it earlier */

    AmlReleaseGlobalLock (Locked);


    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlGetRvalue
 *
 * PARAMETERS:  **StackPtr          - Points to entry on ObjStack, which can 
 *                                    be either an (ACPI_OBJECT_INTERNAL *)
 *                                    or an ACPI_HANDLE.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert Lvalue entries on ObjStack to Rvalues
 *
 ****************************************************************************/

ACPI_STATUS
AmlGetRvalue (
    ACPI_OBJECT_INTERNAL    **StackPtr)
{
    ACPI_HANDLE             TempHandle = NULL;
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    ACPI_OBJECT_INTERNAL    *ValDesc = NULL;
    ACPI_STATUS             Status = AE_OK;
    UINT32                  TempVal;
    UINT8				    MvIndex = 0;
    BOOLEAN                 Locked;


    FUNCTION_TRACE ("AmlGetRvalue");


    if (!StackPtr || !*StackPtr)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: Internal error - null pointer\n"));
        FUNCTION_STATUS_EXIT (AE_AML_ERROR);
        return AE_AML_ERROR;
    }

    switch ((*StackPtr)->Type)
    {
    case TYPE_Lvalue:

        switch ((*StackPtr)->Lvalue.OpCode)
        {

        case AML_NameOp:
            
            /* Convert indirect name ptr to direct name ptr */
            
            TempHandle = (*StackPtr)->Lvalue.Object;
            OsdFree (*StackPtr);
            (*StackPtr) = TempHandle;
            Status = AE_OK;
            break;


        case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
        case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:

            MvIndex = (*StackPtr)->Lvalue.OpCode - AML_Local0;

            DEBUG_PRINT (ACPI_INFO,
                            ("AmlGetRvalue: [Local%d] before AmlMthStackGetValue %p %p %08lx \n",
                            MvIndex, StackPtr, *StackPtr, *(UINT32 *)* StackPtr));

            Status = AmlMthStackGetValue (MTH_LOCAL_BASE + (*StackPtr)->Lvalue.OpCode - AML_Local0,
                                            *StackPtr);

            DEBUG_PRINT (ACPI_INFO,
                        ("AmlGetRvalue: [Local%d] after MSGV Status=%s %p %p %08lx \n",
                            MvIndex, ExceptionNames[Status], StackPtr, *StackPtr,
                            *(UINT32 *)* StackPtr));
            
            if (TYPE_Number == (*StackPtr)->Type)
            {
                /* Value is a Number */
                
                DEBUG_PRINT (ACPI_INFO, ("AmlGetRvalue: [Local%d] value is [%ld] \n", 
                                            MvIndex, (*StackPtr)->Number.Value));
            }
            break;


        case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
        case AML_Arg4: case AML_Arg5: case AML_Arg6:

            DEBUG_PRINT (TRACE_EXEC,
                            ("AmlGetRvalue: [Arg%d] before AmlMthStackGetValue %p %p %08lx \n",
                            MvIndex = (*StackPtr)->Lvalue.OpCode - AML_Arg0,
                            StackPtr, *StackPtr, *(UINT32 *)* StackPtr));

            Status = AmlMthStackGetValue (MTH_ARG_BASE + (*StackPtr)->Lvalue.OpCode - AML_Arg0,
                                            *StackPtr);
        
            DEBUG_PRINT (TRACE_EXEC,
                            ("AmlGetRvalue: [Arg%d] MSGV returned %s %p %p %08lx \n",
                            MvIndex, ExceptionNames[Status], StackPtr, *StackPtr,
                            *(UINT32 *)* StackPtr));

            if (TYPE_Number == (*StackPtr)->Type)
            {
                /* Value is a Number */
                
                DEBUG_PRINT (ACPI_INFO, ("AmlGetRvalue: [Arg%d] value is [%ld] \n", 
                                            MvIndex, (*StackPtr)->Number.Value));
            }

            break;


        case AML_ZeroOp:

            (*StackPtr)->Type = (UINT8) TYPE_Number;
            (*StackPtr)->Number.Value = 0;
            Status = AE_OK;
            break;


        case AML_OneOp:

            (*StackPtr)->Type = (UINT8) TYPE_Number;
            (*StackPtr)->Number.Value = 1;
            Status = AE_OK;
            break;


        case AML_OnesOp:

            (*StackPtr)->Type = (UINT8) TYPE_Number;
            (*StackPtr)->Number.Value = 0xFFFFFFFF;
            Status = AE_OK;
            break;


        default:

            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: Unknown Lvalue subtype %02x\n",
                            (*StackPtr)->Lvalue.OpCode));
            Status = AE_AML_ERROR;

        }   /* switch ((*StackPtr)->Lvalue.OpCode) */

        if (AE_OK != Status)
        {
            FUNCTION_STATUS_EXIT (Status);
            return Status;
        }

        break;


    case TYPE_FieldUnit:

        ObjDesc = AllocateObjectDesc ();
        if (!ObjDesc)
        {   
            /* Descriptor allocation failure  */
            
            FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
            return AE_NO_MEMORY;
        }

        if ((Status = AmlGetFieldUnitValue (*StackPtr, ObjDesc)) != AE_OK)
        {
            OsdFree (ObjDesc);
            ObjDesc = NULL;
        }
        
        *StackPtr = (void *) ObjDesc;
        FUNCTION_STATUS_EXIT (Status);
        return Status;


    case TYPE_BankField:

        ObjDesc = AllocateObjectDesc ();
        if (!ObjDesc)
        {   
            /* Descriptor allocation failure */
            
            FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
            return AE_NO_MEMORY;
        }

        if ((Status = AmlGetFieldUnitValue (*StackPtr, ObjDesc)) != AE_OK)
        {
            OsdFree(ObjDesc);
            ObjDesc = NULL;
        }

        *StackPtr = (void *) ObjDesc;
        FUNCTION_STATUS_EXIT (Status);
        return Status;
        break;


    /* TBD: - may need to handle IndexField, and DefField someday */

    default:

        break;

    }   /* switch ((*StackPtr)->Type) */



    if (IS_NS_HANDLE (*StackPtr))       /* Direct name ptr */
    {

        DEBUG_PRINT (TRACE_EXEC, ("AmlGetRvalue: found direct name ptr \n"));

        ValDesc = (ACPI_OBJECT_INTERNAL *) NsGetValue ((ACPI_HANDLE)* StackPtr);

        DEBUG_PRINT (TRACE_EXEC,
                    ("AmlGetRvalue: NsGetValue(%p) returned Val=%p\n", *StackPtr, ValDesc));

        switch (NsGetType ((ACPI_HANDLE)* StackPtr))
        {

        case TYPE_Package:

            /* 
             * ValDesc should point to either an ACPI_OBJECT_INTERNAL of
             * type Package, or an initialization in the AML stream.
             */
            if (!ValDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue/Package: internal error - null ValuePtr\n"));
                DEBUG_PRINT (TRACE_EXEC,
                            ("leave AmlGetRvalue: NULL Package ValuePtr ==> AE_AML_ERROR\n"));

                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            if (AML_PackageOp == *(UINT8 *) ValDesc)
            {
                /* 
                 * The value pointer in the name table entry
                 * points to a package definition in the AML stream.
                 * Convert it to an object.
                 */

                if (AE_OK != (Status = AmlObjPushIfExec (MODE_Exec)))             /* ObjStack */
                {
                    FUNCTION_STATUS_EXIT (Status);
                    return Status;
                }

                if (AE_OK == (Status = AmlPkgPushExec ((UINT8 *) ValDesc + 1, 0L)) && /*PkgStack*/
                    AE_OK == (Status = AmlDoPkg (TYPE_Package, MODE_Exec)) &&
                    AE_OK == (Status = AmlPkgPopExec ()))                 /* PkgStack */
                {
                    NsSetValue ((ACPI_HANDLE)* StackPtr, ObjStack[ObjStackTop],
                                    (UINT8) TYPE_Package);

                    /* Refresh local value pointer to reflect newly set value */
                    
                    ValDesc = (ACPI_OBJECT_INTERNAL *) NsGetValue ((ACPI_HANDLE)* StackPtr);
                    ObjStackTop--;
                }
                
                else
                {
                    ObjStackTop--;
                    FUNCTION_STATUS_EXIT (Status);
                    return Status;
                }
            }
            
            if (!ValDesc || (TYPE_Package != ValDesc->Type))
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue:internal error - Bad package value\n"));
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc ();
            if (!ObjDesc)
            {   
                /* Descriptor allocation failure */
                
                FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                return AE_NO_MEMORY;
            }

            memcpy ((void *) ObjDesc, (void *) ValDesc, sizeof (*ObjDesc));
            break;


        case TYPE_String:

            /* TBD: - Is there a problem here if the nte points to an AML definition? */
            
            if (TYPE_String != ValDesc->Type)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error - Bad string value\n"));
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc ();
            if (!ObjDesc)
            {   
                /* Descriptor allocation failure */

                FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                return AE_NO_MEMORY;
            }

            memcpy ((void *) ObjDesc, (void *) ValDesc, sizeof (*ObjDesc));
            break;


        case TYPE_Buffer:

            if (!ValDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error - null Buffer ValuePtr\n"));
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            if (AML_BufferOp == *(UINT8 *) ValDesc)
            {
                /* 
                 * The value pointer in the name table entry
                 * points to a buffer definition in the AML stream.
                 * Convert it to an object.
                 */
                if (AE_OK != (Status = AmlObjPushIfExec (MODE_Exec)))                /* ObjStack */
                {
                    FUNCTION_STATUS_EXIT (Status);
                    return Status;
                }

                if (AE_OK == (Status = AmlPkgPushExec ((UINT8 *) ValDesc + 1, 0L)) &&   /*PkgStack*/
                    AE_OK == (Status = AmlDoPkg (TYPE_Buffer, MODE_Exec)) &&
                    AE_OK == (Status = AmlPkgPopExec ()))                     /* PkgStack */
                {
                    NsSetValue ((ACPI_HANDLE) *StackPtr, ObjStack[ObjStackTop],
                                    (UINT8) TYPE_Buffer);
                    
                    /* Refresh local value pointer to reflect newly set value */
                    
                    ValDesc = (ACPI_OBJECT_INTERNAL *) NsGetValue ((ACPI_HANDLE)* StackPtr);
                    ObjStackTop--;
                }
                
                else
                {
                    ObjStackTop--;
                    FUNCTION_STATUS_EXIT (Status);
                    return Status;
                }
            }
            
            if (!ValDesc || (TYPE_Buffer != ValDesc->Type))
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: Bad buffer value\n"));
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc ();
            if (!ObjDesc)
            {   
                /* Descriptor allocation failure */
                
                FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                return AE_NO_MEMORY;
            }

            memcpy ((void *) ObjDesc, (void *) ValDesc, sizeof (*ObjDesc));

            /* Assign a new sequence number */
            
            ObjDesc->Buffer.Sequence = AmlBufSeq();
            
            DEBUG_PRINT (TRACE_BFIELD,
                        ("AmlGetRvalue: new Buffer descriptor seq %ld @ %p \n",
                        ObjDesc->Buffer.Sequence, ObjDesc));

            break;


        case TYPE_Number:

            DEBUG_PRINT (TRACE_EXEC, ("AmlGetRvalue: case Number \n"));

            if (!ValDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error - null Number ValuePtr\n"));
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            if (TYPE_Number == ValDesc->Type)
            {
                ObjDesc = AllocateObjectDesc ();
                if (!ObjDesc)
                {   
                    /* Descriptor allocation failure  */
                    
                    FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                    return AE_NO_MEMORY;
                }
                
                memcpy ((void *) ObjDesc, (void *) ValDesc, sizeof (*ObjDesc));
            }
            
            else
            {
                /* 
                 * nte type is Number, but it does not point to a Number,
                 * so it had better point to a Literal in the AML stream.
                 */
                if (!AmlIsInPCodeBlock ((UINT8 *) ValDesc))
                {
                    DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue/Number: internal error - not a Number\n"));
                    FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                    return AE_AML_ERROR;
                }

                ObjDesc = AllocateObjectDesc ();
                if (!ObjDesc)
                {   
                    /* Descriptor allocation failure  */
                    
                    FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                    return AE_NO_MEMORY;
                }
                
                switch (*(UINT8 *) ValDesc)
                {
                case AML_ZeroOp:

                    ObjDesc->Number.Value = 0;
                    break;


                case AML_OneOp:

                    ObjDesc->Number.Value = 1;
                    break;


                case AML_OnesOp:

                    ObjDesc->Number.Value = 0xFFFFFFFF;
                    break;


                case AML_ByteOp:

                    ObjDesc->Number.Value = (UINT32)((UINT8 *) ValDesc)[1];
                    break;


                /* 
                 *  XXX - WordOp and DWordOp will not work properly if the
                 *  XXX - processor's endianness does not match the AML's.
                 */
                case AML_WordOp:

                    ObjDesc->Number.Value = (UINT32)*(UINT16 *)&((UINT8 *) ValDesc)[1];
                    break;


                case AML_DWordOp:

                    ObjDesc->Number.Value = *(UINT32 *)&((UINT8 *) ValDesc)[1];
                    break;


                default:

                    OsdFree (ObjDesc);
                    DEBUG_PRINT (ACPI_ERROR, (
                            "AmlGetRvalue/Number: internal error - expected AML number, found %02x\n",
                            *(UINT8 *) ValDesc));
                    FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                    return AE_AML_ERROR;
                

                }   /* switch */
                
                ObjDesc->Number.Type = (UINT8) TYPE_Number;
            }

            break;


        case TYPE_DefField:

            /* 
             * XXX - Implementation limitation: Fields are implemented as type
             * XXX - Number, but they really are supposed to be type Buffer.
             * XXX - The two are interchangeable only for lengths <= 32 bits.
             */
            Status = AmlGetNamedFieldValue ((ACPI_HANDLE)* StackPtr, &TempVal);
            if (AE_OK != Status)
            {
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc ();
            if (!ObjDesc)
            {   
                /* Descriptor allocation failure  */
                
                FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                return AE_NO_MEMORY;
            }

            ObjDesc->Number.Type = (UINT8) TYPE_Number;
            ObjDesc->Number.Value = TempVal;
            break;


        case TYPE_BankField:

            if (!ValDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error - null BankField ValuePtr\n"));
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            if (TYPE_BankField != ValDesc->Type)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlGetRvalue/BankField:internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                        *StackPtr, TYPE_BankField, ValDesc->Type, ValDesc));
                
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }


            /* Get the global lock if needed */

            ObjDesc = *StackPtr;
            Locked = AmlAcquireGlobalLock (ObjDesc->FieldUnit.LockRule);
            {

                /* Set Index value to select proper Data register */
                /* perform the update */
            
                Status = AmlSetNamedFieldValue (ValDesc->BankField.BankSelect,
                                               ValDesc->BankField.Value);
            }
            AmlReleaseGlobalLock (Locked);


            if (AE_OK != Status)
            {
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }
            
            /* Read Data value */
            
            Status = AmlGetNamedFieldValue ((ACPI_HANDLE) ValDesc->BankField.Container, &TempVal);
            if (AE_OK != Status)
            {
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc ();
            if (!ObjDesc)
            {
                /* Descriptor allocation failure  */

                FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                return AE_NO_MEMORY;
            }

            ObjDesc->Number.Type = (UINT8) TYPE_Number;
            ObjDesc->Number.Value = TempVal;
            break;


        case TYPE_IndexField:

            if (!ValDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error - null IndexField ValuePtr\n"));
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            if (TYPE_IndexField != ValDesc->Type)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlGetRvalue/IndexField: internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                        *StackPtr, TYPE_IndexField, ValDesc->Type, ValDesc));
                
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }


            /* Set Index value to select proper Data register */
            /* Get the global lock if needed */

            ObjDesc = *StackPtr;
            Locked = AmlAcquireGlobalLock (ObjDesc->FieldUnit.LockRule);
            {
                /* Perform the update */
                
                Status = AmlSetNamedFieldValue (ValDesc->IndexField.Index,
                                                ValDesc->IndexField.Value);
            }
            AmlReleaseGlobalLock (Locked);

            if (AE_OK != Status)
            {
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            /* Read Data value */
            
            Status = AmlGetNamedFieldValue (ValDesc->IndexField.Data, &TempVal);
            if (AE_OK != Status)
            {
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc ();
            if (!ObjDesc)
            {
                /* Descriptor allocation failure  */

                FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                return AE_NO_MEMORY;
            }

            ObjDesc->Number.Type = (UINT8) TYPE_Number;
            ObjDesc->Number.Value = TempVal;
            break;


        case TYPE_FieldUnit:

            if (!ValDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error - null FieldUnit ValuePtr\n"));
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
            }

            if (ValDesc->Type != (UINT8) NsGetType ((ACPI_HANDLE)* StackPtr))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlGetRvalue/FieldUnit:internal error - Name %4.4s type %d does not match value-type %d at %p\n",
                          *StackPtr, NsGetType ((ACPI_HANDLE)* StackPtr),
                          ValDesc->Type, ValDesc));
                
                FUNCTION_STATUS_EXIT (AE_AML_ERROR);
                return AE_AML_ERROR;
                break;
            }

            ObjDesc = AllocateObjectDesc ();
            if (!ObjDesc)
            {
                /* Descriptor allocation failure  */

                FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                return AE_NO_MEMORY;
            }

            if ((Status = AmlGetFieldUnitValue (ValDesc, ObjDesc)) != AE_OK)
            {
                OsdFree (ObjDesc);
                FUNCTION_STATUS_EXIT (Status);
                return Status;
            }

            break;


        /* Cases which just return the name as the rvalue */
        
        case TYPE_Device:

            FUNCTION_STATUS_EXIT (AE_OK);
            return AE_OK;
            break;



        case TYPE_Method:        /* XXX - unimplemented, handled elsewhere */
        case TYPE_Power:         /* XXX - unimplemented, may not be needed */
        case TYPE_Processor:     /* XXX - unimplemented, may not be needed */
        case TYPE_Thermal:       /* XXX - unimplemented, may not be needed */
        case TYPE_Event:         /* XXX - unimplemented, may not be needed */
        case TYPE_Mutex:         /* XXX - unimplemented, may not be needed */
        case TYPE_Region:        /* XXX - unimplemented, may not be needed */

        case TYPE_Any:

            DEBUG_PRINT (TRACE_EXEC, ("case %s \n",
                        NsTypeNames[NsGetType ((ACPI_HANDLE)* StackPtr)]));
          
#ifdef HACK
            DEBUG_PRINT (ACPI_WARN,
                        ("** AmlGetRvalue: Fetch from [%s] not implemented, using value 0\n",
                        NsTypeNames[NsGetType ((ACPI_HANDLE)* StackPtr)]));
            
            ObjDesc = AllocateObjectDesc ();
            if (!ObjDesc)
            {
                /* Descriptor allocation failure  */
                
                FUNCTION_STATUS_EXIT (AE_NO_MEMORY);
                return AE_NO_MEMORY;
            }

            ObjDesc->Number.Type = (UINT8) Number;
            ObjDesc->Number.Value = 0x0;
            break;
#else
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlGetRvalue: Fetch from [%s] not implemented\n",
                    NsTypeNames[NsGetType ((ACPI_HANDLE)* StackPtr)]));
            
            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
#endif /* HACK */

        default:

            DEBUG_PRINT (TRACE_EXEC, 
                        ("AmlGetRvalue: case default handle type unexpected: AE_AML_ERROR \n"));

            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: Unknown NsType %d\n",
                            NsGetType ((ACPI_HANDLE)* StackPtr)));
            
            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
        }

        *StackPtr = (void *) ObjDesc;
    }

    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
}


    