
/******************************************************************************
 * 
 * Module Name: iecreate - Named object creation
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

#define __IECREATE_C__

#include <acpi.h>
#include <parser.h>
#include <interp.h>
#include <amlcode.h>
#include <namesp.h>
#include <events.h>
#include <dispatch.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("iecreate");

         
 /*****************************************************************************
 * 
 * FUNCTION:    AmlExecCreateField
 *
 * PARAMETERS:  Opcode              - The opcode to be executed
 *              Operands            - List of operands for the opcode
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute CreateField operators: CreateBitFieldOp,
 *              CreateByteFieldOp, CreateWordFieldOp, CreateDWordFieldOp,
 *              CreateFieldOp (which define fields in buffers)
 *
 * ALLOCATION:  Deletes CreateFieldOp's count operand descriptor
 *
 *
 *  ACPI SPECIFICATION REFERENCES:
 *  16.2.4.2    DefCreateBitField   :=  CreateBitFieldOp    SourceBuff  BitIndex    NameString
 *  16.2.4.2    DefCreateByteField  :=  CreateByteFieldOp   SourceBuff  ByteIndex   NameString
 *  16.2.4.2    DefCreateDWordField :=  CreateDWordFieldOp  SourceBuff  ByteIndex   NameString
 *  16.2.4.2    DefCreateField      :=  CreateFieldOp       SourceBuff  BitIndex    NumBits     NameString
 *  16.2.4.2    DefCreateWordField  :=  CreateWordFieldOp   SourceBuff  ByteIndex   NameString
 *  16.2.4.2    BitIndex            :=  TermArg=>Integer
 *  16.2.4.2    ByteIndex           :=  TermArg=>Integer
 *  16.2.4.2    NumBits             :=  TermArg=>Integer
 *  16.2.4.2    SourceBuff          :=  TermArg=>Buffer
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecCreateField (
    UINT16                  Opcode,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OBJECT_INTERNAL    *ResDesc = NULL;
    ACPI_OBJECT_INTERNAL    *CntDesc = NULL;
    ACPI_OBJECT_INTERNAL    *OffDesc = NULL;
    ACPI_OBJECT_INTERNAL    *SrcDesc = NULL;
    ACPI_OBJECT_INTERNAL    *FieldDesc;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    OBJECT_TYPE_INTERNAL    ResType;
    ACPI_STATUS             Status;
    UINT32                  NumOperands = 3;
    UINT32                  Offset;
    UINT32                  BitOffset;
    UINT16                  BitCount;
    UINT8                   TypeFound;



    FUNCTION_TRACE ("AmlExecCreateField");


    /* Resolve the operands */

    Status = AmlResolveOperands (Opcode, WALK_OPERANDS);
    DUMP_OPERANDS (WALK_OPERANDS, IMODE_Execute, PsGetOpcodeName (Opcode), NumOperands, "after AmlResolveOperands");


    /* Get the operands */

    Status |= DsObjStackPopObject (&ResDesc, WalkState);
    if (AML_CreateFieldOp == Opcode)
    {
        NumOperands = 4;
        Status |= DsObjStackPopObject (&CntDesc, WalkState);
    }

    Status |= DsObjStackPopObject (&OffDesc, WalkState);
    Status |= DsObjStackPopObject (&SrcDesc, WalkState);

    if (Status != AE_OK)
    {
        /* Invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, Opcode, WALK_OPERANDS, 3);
        goto Cleanup;
    }



    Offset = OffDesc->Number.Value;



    /* If ResDesc is a Name, it will be a direct name pointer after AmlResolveOperands() */
    
    if (!VALID_DESCRIPTOR_TYPE (ResDesc, DESC_TYPE_NTE))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecCreateField (%s): destination must be a Name(NTE)\n", PsGetOpcodeName (Opcode)));
        Status = AE_AML_OPERAND_TYPE;
        goto Cleanup;
    }


    /*
     * Setup the Bit offsets and counts, according to the opcode
     */

    switch (Opcode)
    {

    /* DefCreateBitField   :=  CreateBitFieldOp    SourceBuff  BitIndex    NameString  */

    case AML_BitFieldOp:

        BitOffset = Offset;                         /* offset is in bits */
        BitCount = 1;                               /* field is a bit */
        break;


    /* DefCreateByteField  :=  CreateByteFieldOp   SourceBuff  ByteIndex   NameString  */

    case AML_ByteFieldOp:

        BitOffset = 8 * Offset;                     /* offset is in bytes */
        BitCount = 8;                               /* field is a Byte */
        break;


    /* DefCreateWordField  :=  CreateWordFieldOp   SourceBuff  ByteIndex   NameString  */

    case AML_WordFieldOp:

        BitOffset = 8 * Offset;                     /* offset is in bytes */
        BitCount = 16;                              /* field is a Word */
        break;


    /* DefCreateDWordField :=  CreateDWordFieldOp  SourceBuff  ByteIndex   NameString  */

    case AML_DWordFieldOp:

        BitOffset = 8 * Offset;                     /* offset is in bytes */
        BitCount = 32;                              /* field is a DWord */
        break;


    /* DefCreateField  :=  CreateFieldOp   SourceBuff  BitIndex    NumBits NameString  */

    case AML_CreateFieldOp:

        BitOffset = Offset;                         /* offset is in bits */
        BitCount = (UINT16) CntDesc->Number.Value;  /* as is count */
        break;


    default:

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecCreateField: Internal error - unknown field creation opcode %02x\n",
                        Opcode));
        Status = AE_AML_BAD_OPCODE;
        goto Cleanup;
    }


    /*
     * Setup field according to the object type
     */

    switch (SrcDesc->Common.Type)
    {
    
    /* SourceBuff  :=  TermArg=>Buffer */

    case ACPI_TYPE_Buffer:

        if (BitOffset + (UINT32) BitCount > 8 * (UINT32) SrcDesc->Buffer.Length)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecCreateField: Field exceeds Buffer %d > %d\n",
                            BitOffset + (UINT32) BitCount,
                            8 * (UINT32) SrcDesc->Buffer.Length));
            Status = AE_AML_BUFFER_LIMIT;
            goto Cleanup;
        }


        /* Allocate an object for the field */

        FieldDesc = CmCreateInternalObject (ACPI_TYPE_FieldUnit);
        if (!FieldDesc)
        {
            Status = AE_NO_MEMORY;
            goto Cleanup;
        }

        /* Construct the field object */

        FieldDesc->FieldUnit.Access       = (UINT8) ACCESS_AnyAcc;
        FieldDesc->FieldUnit.LockRule     = (UINT8) GLOCK_NeverLock;
        FieldDesc->FieldUnit.UpdateRule   = (UINT8) UPDATE_Preserve;
        FieldDesc->FieldUnit.Length       = BitCount;
        FieldDesc->FieldUnit.BitOffset    = (UINT8) (BitOffset % 8);
        FieldDesc->FieldUnit.Offset       = DIV_8 (BitOffset);
        FieldDesc->FieldUnit.Container    = SrcDesc;
        FieldDesc->FieldUnit.Sequence     = SrcDesc->Buffer.Sequence;

        /* An additional reference for SrcDesc */

        CmAddReference (SrcDesc);

        break;


    /* Improper object type */

    default:

        TypeFound = SrcDesc->Common.Type;

        if ((TypeFound > (UINT8) INTERNAL_TYPE_Reference) ||
            !CmValidObjectType (TypeFound))
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecCreateField: Tried to create field in invalid object type - 0x%X\n",
                            TypeFound));
        }

        else
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecCreateField: Tried to create field in improper object type - %s\n",
                            CmGetTypeName (TypeFound)));
        }

        Status = AE_AML_OPERAND_TYPE;
        goto Cleanup;
    
    } /* switch */


    if (AML_CreateFieldOp == Opcode)
    {
        /* Delete object descriptor unique to CreateField  */

        CmRemoveReference (CntDesc);
        CntDesc = NULL;
    }

    /* 
     * This operation is supposed to cause the destination Name to refer
     * to the defined FieldUnit -- it must not store the constructed
     * FieldUnit object (or its current value) in some location that the
     * Name may already be pointing to.  So, if the Name currently contains
     * a reference which would cause AmlExecStore() to perform an indirect
     * store rather than setting the value of the Name itself, clobber that
     * reference before calling AmlExecStore().
     */

    ResType = NsGetType (ResDesc);
    switch (ResType)                /* Type of Name's existing value */
    {

    case ACPI_TYPE_FieldUnit:

    case INTERNAL_TYPE_Alias:
    case INTERNAL_TYPE_BankField:
    case INTERNAL_TYPE_DefField:
    case INTERNAL_TYPE_IndexField:

        ObjDesc = NsGetAttachedObject (ResDesc);
        if (ObjDesc)
        {
            /* There is an existing object here;  delete it and zero out the NTE */

            DUMP_PATHNAME (ResDesc, "AmlExecCreateField: Removing Current Reference", TRACE_BFIELD, _COMPONENT);

            DUMP_ENTRY (ResDesc, TRACE_BFIELD);
            DUMP_STACK_ENTRY (ObjDesc);
        
            CmRemoveReference (ObjDesc);
            NsAttachObject (ResDesc, NULL, ACPI_TYPE_Any);
        }
        
        /* Set the type to ANY (or the store below will fail) */

        ((NAME_TABLE_ENTRY *) ResDesc)->Type = ACPI_TYPE_Any;

        break;


    default:

        break;
    }


    /* Store constructed field descriptor in result location */

    Status = AmlExecStore (FieldDesc, ResDesc);

    /*
     * If the field descriptor was not physically stored (or if a failure above), we
     * must delete it
     */
    if (FieldDesc->Common.ReferenceCount <= 1)
    {
        CmRemoveReference (FieldDesc);
    }



Cleanup:

    /* Always delete the operands */

    CmRemoveReference (OffDesc);
    CmRemoveReference (SrcDesc);

    if (AML_CreateFieldOp == Opcode)
    {
        CmRemoveReference (CntDesc);
    }

    /* On failure, delete the result descriptor */

    if (ACPI_FAILURE (Status))
    {
        CmRemoveReference (ResDesc);     /* Result descriptor */
    }

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    AmlExecCreateAlias
 *
 * PARAMETERS:  Operands            - List of operands for the opcode
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new named alias
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecCreateAlias (
    ACPI_WALK_STATE         *WalkState)
{
    NAME_TABLE_ENTRY        *SrcEntry;
    NAME_TABLE_ENTRY        *AliasEntry;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecCreateAlias");


    /* Get the source/alias operands (both NTEs) */

    Status = DsObjStackPopObject ((ACPI_OBJECT_INTERNAL **) &SrcEntry, WalkState);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    AliasEntry  = DsObjStackGetValue (0, WalkState);    /* Don't pop it, it gets popped later */

    /* Add an additional reference to the object */

    CmAddReference (SrcEntry->Object);

    /* 
     * Attach the original source NTE to the new Alias NTE.
     */
    Status = NsAttachObject (AliasEntry, SrcEntry->Object, SrcEntry->Type);


    /* 
     * The new alias assumes the type of the source, but it points
     * to the same object.  The reference count of the object has two additional
     * references to prevent deletion out from under either the source
     * or the alias NTE 
     */

    /* Since both operands are NTEs, we don't need to delete them */

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    AmlExecCreateEvent 
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new event object
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecCreateEvent (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    FUNCTION_TRACE ("AmlExecCreateEvent");


 BREAKPOINT3;

    ObjDesc = CmCreateInternalObject (ACPI_TYPE_Event);
    if (!ObjDesc)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    /* Create the actual OS semaphore */

    Status = OsdCreateSemaphore (1, &ObjDesc->Event.Semaphore);
    if (ACPI_FAILURE (Status))
    {
        CmRemoveReference (ObjDesc);
        goto Cleanup;
    }

    /* Attach object to the NTE */

    Status = NsAttachObject (DsObjStackGetValue (0, WalkState), ObjDesc, (UINT8) ACPI_TYPE_Event);
    if (ACPI_FAILURE (Status))
    {
        OsdDeleteSemaphore (ObjDesc->Event.Semaphore);
        CmRemoveReference (ObjDesc);
        goto Cleanup;
    }



Cleanup:

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    AmlExecCreateMutex
 *
 * PARAMETERS:  InterpreterMode     - Current running mode (load1/Load2/Exec)
 *              Operands            - List of operands for the opcode
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new mutex object
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecCreateMutex (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OBJECT_INTERNAL    *SyncDesc;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    
    FUNCTION_TRACE_PTR ("AmlExecCreateMutex", WALK_OPERANDS);


    /* Get the operand */

    Status = DsObjStackPopObject (&SyncDesc, WalkState);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Attempt to allocate a new object */

    ObjDesc = CmCreateInternalObject (ACPI_TYPE_Mutex);
    if (!ObjDesc)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    /* Create the actual OS semaphore */

    Status = OsdCreateSemaphore (1, &ObjDesc->Mutex.Semaphore);
    if (ACPI_FAILURE (Status))
    {
        CmRemoveReference (ObjDesc);
        goto Cleanup;
    }

    ObjDesc->Mutex.SyncLevel = (UINT8) SyncDesc->Number.Value;

    /* ObjDesc was on the stack top, and the name is below it */

    Status = NsAttachObject (DsObjStackGetValue (0, WalkState),  /* Name */
                                ObjDesc, (UINT8) ACPI_TYPE_Mutex);
    if (ACPI_FAILURE (Status))
    {
        OsdDeleteSemaphore (ObjDesc->Mutex.Semaphore);
        CmRemoveReference (ObjDesc);
        goto Cleanup;
    }


Cleanup:

    /* Always delete the operand */

    CmRemoveReference (SyncDesc);

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    AmlExecCreateRegion
 *
 * PARAMETERS:  AmlPtr              - Pointer to the region declaration AML
 *              AmlLength           - Max length of the declaration AML
 *              Operands            - List of operands for the opcode
 *              InterpreterMode     - Load1/Load2/Execute
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new operation region object
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecCreateRegion (
    UINT8                   *AmlPtr,
    UINT32                  AmlLength,
    UINT32                  RegionSpace,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    *ObjDescRegion;
    ACPI_HANDLE             *Entry;


    FUNCTION_TRACE ("AmlExecCreateRegion");


    if (RegionSpace >= NUM_REGION_TYPES)
    {
        /* TBD: should this return an error, or should we just keep going? */

        DEBUG_PRINT (TRACE_LOAD, ("AmlDoNamedObject: Type out of range [*???*]\n"));
        REPORT_WARNING ("Unable to decode the RegionSpace");
    }

    DEBUG_PRINT (TRACE_LOAD, ("AmlDoNamedObject: Region Type [%s]\n",
                    Gbl_RegionTypes[RegionSpace]));


    /* Get the NTE from the object stack  */

    Entry = DsObjStackGetValue (0, WalkState);


    /* Create the region descriptor */

    ObjDescRegion = CmCreateInternalObject (ACPI_TYPE_Region);
    if (!ObjDescRegion)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    /*
     * Allocate a method object for this region.
     */
    ObjDescRegion->Region.Method = CmCreateInternalObject (ACPI_TYPE_Method);
    if (!ObjDescRegion->Region.Method)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    /* Init the region from the operands */

    ObjDescRegion->Region.SpaceId   = (UINT16) RegionSpace;
    ObjDescRegion->Region.Address   = 0;
    ObjDescRegion->Region.Length    = 0;
    ObjDescRegion->Region.RegionFlags = 0;

    /* 
     * Remember location in AML stream of address & length
     * operands since they need to be evaluated at run time.
     */
    ObjDescRegion->Region.Method->Method.Pcode       = AmlPtr;
    ObjDescRegion->Region.Method->Method.PcodeLength = AmlLength;

                    
    /* Install the new region object in the parent NTE */

    ObjDescRegion->Region.Nte = (NAME_TABLE_ENTRY *) Entry;

    Status = NsAttachObject (Entry, ObjDescRegion, (UINT8) ACPI_TYPE_Region);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }

Cleanup:

    if (Status != AE_OK)
    {
        /* Delete region object and method subobject */

        if (ObjDescRegion)
        {
            CmRemoveReference (ObjDescRegion);     /* Deletes both objects! */
            ObjDescRegion = NULL;
        }
    }


    /*
     * If we have a valid region, initialize it
     */
    if (ObjDescRegion)
    {      
        /*
         *  TBD: Is there anything we can or could do when this fails?
         *          We need to do something useful with a failure.
         */
        (void *) EvInitializeRegion (ObjDescRegion, TRUE);  /* Namespace IS locked */
    }

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    AmlExecCreateProcessor 
 *
 * PARAMETERS:  Op           - Op containing the Processor definition and args
 *              ProcessorNTE - NTE for the containing NTE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new processor object and populate the fields
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecCreateProcessor (
    ACPI_GENERIC_OP         *Op,
    ACPI_HANDLE             ProcessorNTE)
{
    ACPI_STATUS             Status;
    ACPI_GENERIC_OP         *Arg;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    FUNCTION_TRACE_PTR ("AmlExecCreateProcessor", Op);


    ObjDesc = CmCreateInternalObject (ACPI_TYPE_Processor);
    if (!ObjDesc)
    {
        Status = AE_NO_MEMORY;
        return_ACPI_STATUS (Status);
    }

    /* Install the new processor object in the parent NTE */

    Status = NsAttachObject (ProcessorNTE, ObjDesc, (UINT8) ACPI_TYPE_Processor);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS(Status);
    }

    Arg = Op->Value.Arg;

    /* check existence */

    if (!Arg)
    {
        Status = AE_AML_NO_OPERAND;
        return_ACPI_STATUS (Status);
    }

    /* First arg is the Processor ID */

    ObjDesc->Processor.ProcId = (UINT8) Arg->Value.Integer;

    /* Move to next arg and check existence */

    Arg = Arg->Next;
    if (!Arg)
    {
        Status = AE_AML_NO_OPERAND;
        return_ACPI_STATUS (Status);
    }

    /* Second arg is the PBlock Address */

    ObjDesc->Processor.PBLKAddress = (ACPI_IO_ADDRESS) Arg->Value.Integer;

    /* Move to next arg and check existence */

    Arg = Arg->Next;
    if (!Arg)
    {
        Status = AE_AML_NO_OPERAND;
        return_ACPI_STATUS (Status);
    }

    /* Third arg is the PBlock Length */

    ObjDesc->Processor.PBLKLength = (UINT8) Arg->Value.Integer;

    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 *
 * FUNCTION:    AmlExecCreatePowerResource
 *
 * PARAMETERS:  Op           - Op containing the PowerResource definition and args
 *              PowerResNTE - NTE for the containing NTE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new PowerResource object and populate the fields
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecCreatePowerResource (
    ACPI_GENERIC_OP         *Op,
    ACPI_HANDLE             PowerResNTE)
{
    ACPI_STATUS             Status;
    ACPI_GENERIC_OP         *Arg;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    FUNCTION_TRACE_PTR ("AmlExecCreatePowerResource", Op);


    ObjDesc = CmCreateInternalObject (ACPI_TYPE_Power);
    if (!ObjDesc)
    {
        Status = AE_NO_MEMORY;
        return_ACPI_STATUS (Status);
    }

    /* Install the new power resource object in the parent NTE */

    Status = NsAttachObject (PowerResNTE, ObjDesc, (UINT8) ACPI_TYPE_Power);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS(Status);
    }

    Arg = Op->Value.Arg;

    /* check existence */

    if (!Arg)
    {
        Status = AE_AML_NO_OPERAND;
        return_ACPI_STATUS (Status);
    }

    /* First arg is the SystemLevel */

    ObjDesc->PowerResource.SystemLevel = (UINT8) Arg->Value.Integer;

    /* Move to next arg and check existence */

    Arg = Arg->Next;
    if (!Arg)
    {
        Status = AE_AML_NO_OPERAND;
        return_ACPI_STATUS (Status);
    }

    /* Second arg is the PBlock Address */

    ObjDesc->PowerResource.ResourceOrder = (UINT16) Arg->Value.Integer;

    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 *
 * FUNCTION:    AmlExecCreateMethod
 *
 * PARAMETERS:  InterpreterMode     - Current running mode (load1/Load2/Exec)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new mutex object
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecCreateMethod (
    UINT8                   *AmlPtr,
    UINT32                  AmlLength,
    UINT32                  MethodFlags,
    ACPI_HANDLE             Method)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE_PTR ("AmlExecCreateMethod", Method);


    /* Create a new method object */

    ObjDesc = CmCreateInternalObject (ACPI_TYPE_Method);
    if (!ObjDesc)
    {
       return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Get the method's AML pointer/length from the Op */

    ObjDesc->Method.Pcode       = AmlPtr;
    ObjDesc->Method.PcodeLength = AmlLength;

    /* First argument is the Method Flags (contains parameter count for the method) */

    ObjDesc->Method.MethodFlags = (UINT8) MethodFlags;
    ObjDesc->Method.ParamCount  = (UINT8) (MethodFlags & METHOD_FLAGS_ARG_COUNT);
    
    /* 
     * Get the concurrency count
     * If required, a semaphore will be created for this method when it is parsed.
     *
     * TBD:  for APCI 2.0, there will be a SyncLevel value, not just a flag
     * Concurrency = SyncLevel + 1;.
     */
    if (MethodFlags & METHOD_FLAGS_SERIALIZED)
    {
        ObjDesc->Method.Concurrency = 1;
    }
    else
    {
        ObjDesc->Method.Concurrency = INFINITE_CONCURRENCY;
    }

    /* Mark the Method as not parsed yet */

    ObjDesc->Method.ParserOp    = NULL;

    /* Another  +1 gets added when PsxExecute is called, no need for: ObjDesc->Method.Pcode++; */

    ObjDesc->Method.AcpiTable   = NULL;     /* TBD: was (UINT8 *) PcodeAddr; */
    ObjDesc->Method.TableLength = 0;        /* TBD: needed? (UINT32) (WalkState->amlEnd - PcodeAddr); */

    /* Attach the new object to the method NTE */

    Status = NsAttachObject (Method, ObjDesc, (UINT8) ACPI_TYPE_Method);
    if (ACPI_FAILURE (Status))
    {
        CmFree (ObjDesc);
    }

    return_ACPI_STATUS (Status);
}
    




 
