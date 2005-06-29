
/******************************************************************************
 * 
 * Module Name: ieopexec - ACPI AML (p-code) execution - specific opcodes
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

#define __IEOPEXEC_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>


#define _THIS_MODULE        "ieopexec.c"
#define _COMPONENT          INTERPRETER


 
 /*****************************************************************************
 * 
 * FUNCTION:    AmlExecCreateField
 *
 * PARAMETERS:  opcode              - The opcode to be executed
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
    UINT16                  opcode)
{
    ACPI_OBJECT_INTERNAL    *ResDesc = NULL;
    ACPI_OBJECT_INTERNAL    *CntDesc = NULL;
    ACPI_OBJECT_INTERNAL    *OffDesc = NULL;
    ACPI_OBJECT_INTERNAL    *SrcDesc = NULL;
    ACPI_STATUS             Status;
    char                    *OpName = NULL;
    UINT32                  NumOperands;
    UINT16                  BitCount;
    UINT32                  BitOffset;
    UINT32                  i;
    UINT8                   bTypeFound;
    char                    TypeFound[20];
    char                    *TypeFoundPtr = NULL;




    FUNCTION_TRACE ("AmlExecCreateField");


    /* DefCreateField := CreateFieldOp SourceBuff BitIndex NumBits NameString  */

    if (AML_CreateFieldOp == opcode)
    {
        Status = AmlPrepObjStack ("lnnb");
        NumOperands = 4;
        OpName = LongOps[opcode & 0x00ff];
    }

    
    /* 
     * Create[Bit|Byte|DWord|Word]Field
     * DefCreate*Field := Create*FieldOp SourceBuff [Bit|Byte]Index NameString
     */

    else
    {
        Status = AmlPrepObjStack ("lnb");
        NumOperands = 3;
        OpName = ShortOps[opcode];
    }

    if (Status != AE_OK)
    {
        /* Invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, NumOperands);
        FUNCTION_STATUS_EXIT (Status);
        return Status;
    }

    /* Get pointers to everything that is now on the object stack */

    AmlDumpObjStack (MODE_Exec, OpName, NumOperands, "after AmlPrepObjStack");

    ResDesc = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop--];        /* result */
    
    if (AML_CreateFieldOp == opcode)
    {
        CntDesc = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop--];        /* count */
    }

    OffDesc = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop--];        /* offset */
    SrcDesc = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop];          /* source */
    ObjStackTop += NumOperands - 1;

    /* If ResDesc is a Name, it will be a direct name pointer after AmlPrepObjStack() */
    
    if (!IS_NS_HANDLE (ResDesc))
    {
        DEBUG_PRINT (ACPI_ERROR, ("%s: destination must be a Name\n", OpName));
        FUNCTION_STATUS_EXIT (AE_AML_ERROR);
        return AE_AML_ERROR;
    }


    /*
     * Setup the Bit offsets and counts, according to the opcode
     */

    switch (opcode)
    {

    /* DefCreateBitField   :=  CreateBitFieldOp    SourceBuff  BitIndex    NameString  */

    case AML_BitFieldOp:

        BitOffset = OffDesc->Number.Value;              /* offset is in bits */
        BitCount = 1;                                   /* field is a bit */
        break;


    /* DefCreateByteField  :=  CreateByteFieldOp   SourceBuff  ByteIndex   NameString  */

    case AML_ByteFieldOp:

        BitOffset = 8 * OffDesc->Number.Value;          /* offset is in bytes */
        BitCount = 8;                                   /* field is a Byte */
        break;


    /* DefCreateWordField  :=  CreateWordFieldOp   SourceBuff  ByteIndex   NameString  */

    case AML_WordFieldOp:

        BitOffset = 8 * OffDesc->Number.Value;          /* offset is in bytes */
        BitCount = 16;                                  /* field is a Word */
        break;


    /* DefCreateDWordField :=  CreateDWordFieldOp  SourceBuff  ByteIndex   NameString  */

    case AML_DWordFieldOp:

        BitOffset = 8 * OffDesc->Number.Value;          /* offset is in bytes */
        BitCount = 32;                                  /* field is a DWord */
        break;


    /* DefCreateField  :=  CreateFieldOp   SourceBuff  BitIndex    NumBits NameString  */

    case AML_CreateFieldOp:

        BitOffset = OffDesc->Number.Value;              /* offset is in bits */
        BitCount = (UINT16) CntDesc->Number.Value;      /* as is count */
        break;


    default:

        DEBUG_PRINT (ACPI_ERROR, (
                "AmlExecCreateField:internal error: Unknown field creation opcode %02x\n",
                opcode));
        FUNCTION_STATUS_EXIT (AE_AML_ERROR);
        return AE_AML_ERROR;

    } /* switch */



    /*
     * Setup field according to the object type
     */

    switch (SrcDesc->Type)
    {
    
    /* SourceBuff  :=  TermArg=>Buffer */

    case TYPE_Buffer:

        if (BitOffset + (UINT32) BitCount > 8 * (UINT32) SrcDesc->Buffer.Length)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecCreateField: Field exceeds Buffer %d > %d\n",
                            BitOffset + (UINT32)BitCount,
                            8 * (UINT32)SrcDesc->Buffer.Length));
            FUNCTION_STATUS_EXIT (AE_AML_ERROR);
            return AE_AML_ERROR;
        }

        /* Reuse "OffDesc" descriptor to build result */
        
        OffDesc->Type                   = (UINT8) TYPE_FieldUnit;
        OffDesc->FieldUnit.Access       = (UINT16) ACCESS_AnyAcc;
        OffDesc->FieldUnit.LockRule     = (UINT16) GLOCK_NeverLock;
        OffDesc->FieldUnit.UpdateRule   = (UINT16) UPDATE_Preserve;
        OffDesc->FieldUnit.Length       = BitCount;
        OffDesc->FieldUnit.BitOffset    = (UINT16) BitOffset % 8;
        OffDesc->FieldUnit.Offset       = BitOffset / 8;
        OffDesc->FieldUnit.Container    = SrcDesc;
        OffDesc->FieldUnit.Sequence     = SrcDesc->Buffer.Sequence;
        break;


    default:

        bTypeFound = SrcDesc->Type;

        if ((bTypeFound > (UINT8) TYPE_Lvalue) ||
            (BadType == NsTypeNames[bTypeFound]))
        {
            sprintf (TypeFound, "encoding %d", bTypeFound);
            TypeFoundPtr = TypeFound;
        }
        else
        {
            TypeFoundPtr = NsTypeNames[bTypeFound];
        }

        DEBUG_PRINT (ACPI_ERROR, (
                "AmlExecCreateField: Tried to create field in improper object type %s\n",
                TypeFoundPtr));
        FUNCTION_STATUS_EXIT (AE_AML_ERROR);
        return AE_AML_ERROR;
    
    } /* switch */


    if (AML_CreateFieldOp == opcode)
    {
        /* Delete object descriptor unique to CreateField  */

        CmFree (CntDesc);
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

    switch (NsGetType (ResDesc))                /* Type of Name's existing value */
    {

    case TYPE_Alias:
    case TYPE_BankField:
    case TYPE_DefField:
    case TYPE_FieldUnit:
    case TYPE_IndexField:

        NsDumpPathname (ResDesc, "AmlExecCreateField: clobber ", TRACE_BFIELD, _COMPONENT);

        DUMP_ENTRY (ResDesc);
        DUMP_STACK_ENTRY (NsGetValue (ResDesc));
        
        NsSetValue (ResDesc, NULL, TYPE_Any);
        break;


    default:

        break;
    }


    /* Store constructed field descriptor in result location */
    
    Status = AmlExecStore (OffDesc, ResDesc);

    /* Pop off everything from the stack */

    for (i = 0; i < (NumOperands - 1); i++)
    {
        ObjStack[ObjStackTop] = NULL;
        ObjStackTop--;
    }    
    ObjStack[ObjStackTop] = NULL;
    

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecFatal
 *
 * PARAMETERS:  none
 *
 * RETURN:      Status - AE_AML_ERROR on success
 *
 * DESCRIPTION: Execute Fatal operator
 *
 *  ACPI SPECIFICATION REFERENCES:
 *  16.2.4.3    DefFatal    :=  FatalOp FatalType   FatalCode   FatalArg
 *  16.2.4.3    FatalType   :=  ByteData
 *  16.2.4.3    FatalCode   :=  DWordData
 *  16.2.4.3    FatalArg    :=  TermArg=>Integer
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecFatal (void)
{
    ACPI_OBJECT_INTERNAL    *TypeDesc;
    ACPI_OBJECT_INTERNAL    *CodeDesc;
    ACPI_OBJECT_INTERNAL    *ArgDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecFatal");


    Status = AmlPrepObjStack ("nnn");

    if (Status != AE_OK)
    {
        /* invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, (UINT16) AML_FatalOp, 3);
        FUNCTION_STATUS_EXIT (Status);
        return Status;
    }

    AmlDumpObjStack (MODE_Exec, LongOps[AML_FatalOp & 0x00ff], 3, "after AmlPrepObjStack");


    /* DefFatal    :=  FatalOp FatalType   FatalCode   FatalArg    */

    ArgDesc  = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop];
    CodeDesc = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop - 1];
    TypeDesc = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop - 2];

    DEBUG_PRINT (ACPI_INFO,
                ("FatalOp: Type %x Code %x Arg %x <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n",
                TypeDesc->Number.Value, CodeDesc->Number.Value,
                ArgDesc->Number.Value));

    DEBUG_PRINT (ACPI_ERROR, ("AmlExecFatal: FatalOp executed\n"));
    FUNCTION_STATUS_EXIT (AE_AML_ERROR);
    return AE_AML_ERROR;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecIndex
 *
 * PARAMETERS:  none
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Index operator
 *
 * ALLOCATION:  Deletes one operand descriptor -- other remains on stack
 *
 *  ACPI SPECIFICATION REFERENCES:
 *  16.2.4.4    DefIndex    :=  IndexOp BuffPkgObj IndexValue Result
 *  16.2.4.4    IndexValue  :=  TermArg=>Integer
 *  16.2.1      NameString  :=  <RootChar NamePath> | <PrefixPath NamePath>
 *  16.2.4.4    Result      :=  SuperName
 *  16.2.1      SuperName   :=  NameString | ArgObj | LocalObj | DebugObj | DefIndex
 *                              Local4Op | Local5Op | Local6Op | Local7Op
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecIndex (void)
{
    ACPI_OBJECT_INTERNAL    *PkgDesc;
    ACPI_OBJECT_INTERNAL    *IdxDesc;
    ACPI_OBJECT_INTERNAL    *ResDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecIndex");


    Status = AmlPrepObjStack ("lnp");

    if (Status != AE_OK)
    {
        /* invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, (UINT16) AML_IndexOp, 3);
    }

    else
    {
        AmlDumpObjStack (MODE_Exec, ShortOps[AML_IndexOp], 3, "after AmlPrepObjStack");

        ResDesc = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop];
        IdxDesc = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop - 1];
        PkgDesc = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop - 2];

        if (IdxDesc->Number.Value < 0 || 
            IdxDesc->Number.Value >= (UINT32) PkgDesc->Package.Count)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecIndex: Index value out of range\n"));
            Status = AE_AML_ERROR;
        }

        else
        {
            /* 
             * TBD - possible dangling reference: if the package vector changes
             * TBD - before this pointer is used, the results may be surprising.
             */
            PkgDesc->Lvalue.Object  = (void *) &PkgDesc->Package.Elements[IdxDesc->Number.Value];
            PkgDesc->Type           = (UINT8) TYPE_Lvalue;
            PkgDesc->Lvalue.OpCode  = AML_IndexOp;

            Status = AmlExecStore (PkgDesc, ResDesc);
        }

        if (AE_OK == Status)
        {
            CmFree (IdxDesc);
        }

        ObjStackTop -= 2;
    }

    FUNCTION_STATUS_EXIT (Status);
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlExecMatch
 *
 * PARAMETERS:  none
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Match operator
 *
 * ALLOCATION:  Deletes 5 operands
 *
 *  ACPI SPECIFICATION REFERENCES:
 *  16.2.4.4    DefMatch    :=  MatchOp SearchPkg   Opcode1     Operand1
 *                              Opcode2 Operand2    StartIndex
 *  16.2.4.4    Opcode1     :=  ByteData: MTR, MEQ, MLE, MLT, MGE, or MGT
 *  16.2.4.4    Opcode2     :=  ByteData: MTR, MEQ, MLE, MLT, MGE, or MGT
 *  16.2.4.4    Operand1    :=  TermArg=>Integer
 *  16.2.4.4    Operand2    :=  TermArg=>Integer
 *  16.2.4.4    SearchPkg   :=  TermArg=>PackageObject
 *  16.2.4.4    StartIndex  :=  TermArg=>Integer
 *
 ****************************************************************************/

ACPI_STATUS
AmlExecMatch (void)
{
    ACPI_OBJECT_INTERNAL    *PkgDesc;
    ACPI_OBJECT_INTERNAL    *Op1Desc;
    ACPI_OBJECT_INTERNAL    *V1Desc;
    ACPI_OBJECT_INTERNAL    *Op2Desc;
    ACPI_OBJECT_INTERNAL    *V2Desc;
    ACPI_OBJECT_INTERNAL    *StartDesc;
    ACPI_STATUS             Status;
    UINT32                  Look;
    UINT32                  MatchValue = (UINT32) -1;


    FUNCTION_TRACE ("AmlExecMatch");


    Status = AmlPrepObjStack ("nnnnnp");

    if (Status != AE_OK)
    {
        /* invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, (UINT16) AML_MatchOp, 6);
        FUNCTION_STATUS_EXIT (Status);
        return Status;
    }

    AmlDumpObjStack (MODE_Exec, ShortOps[AML_MatchOp], 6, "after AmlPrepObjStack");

    StartDesc = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop];
    V2Desc    = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop - 1];
    Op2Desc   = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop - 2];
    V1Desc    = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop - 3];
    Op1Desc   = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop - 4];
    PkgDesc   = (ACPI_OBJECT_INTERNAL *) ObjStack[ObjStackTop - 5];

    /* Validate match comparison sub-opcodes */
    
    if (Op1Desc->Number.Value < 0 || Op1Desc->Number.Value > 5 || 
        Op2Desc->Number.Value < 0 || Op2Desc->Number.Value > 5)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMatch: operation encoding out of range\n"));
        FUNCTION_STATUS_EXIT (AE_AML_ERROR);
        return AE_AML_ERROR;
    }

    Look = StartDesc->Number.Value;
    if (Look < 0 || Look >= (UINT32) PkgDesc->Package.Count)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMatch: start position value out of range\n"));
        FUNCTION_STATUS_EXIT (AE_AML_ERROR);
        return AE_AML_ERROR;
    }

    /* 
     * Examine each element until a match is found.  Within the loop,
     * "continue" signifies that the current element does not match
     * and the next should be examined.
     * Upon finding a match, the loop will terminate via "break" at
     * the bottom.  If it terminates "normally", MatchValue will be -1
     * (its initial value) indicating that no match was found.  When
     * returned as a Number, this will produce the Ones value as specified.
     */

    for ( ; Look < (UINT32) PkgDesc->Package.Count ; ++Look)
    {
        /* 
         * Treat any NULL or non-numeric elements as non-matching.
         * XXX - if an element is a Name, should we examine its value?
         */
        if (!PkgDesc->Package.Elements[Look] ||
            TYPE_Number != PkgDesc->Package.Elements[Look]->Type)
        {
            continue;
        }

        /* 
         * Within these switch statements:
         *      "break" (exit from the switch) signifies a match;
         *      "continue" (proceed to next iteration of enclosing
         *          "for" loop) signifies a non-match.
         */
        switch (Op1Desc->Number.Value)
        {

        case MATCH_MTR:   /* always true */

            break;


        case MATCH_MEQ:   /* true if equal   */

            if (PkgDesc->Package.Elements[Look]->Number.Value
                 != V1Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MLE:   /* true if less than or equal  */

            if (PkgDesc->Package.Elements[Look]->Number.Value
                 > V1Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MLT:   /* true if less than   */

            if (PkgDesc->Package.Elements[Look]->Number.Value
                 >= V1Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MGE:   /* true if greater than or equal   */

            if (PkgDesc->Package.Elements[Look]->Number.Value
                 < V1Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MGT:   /* true if greater than    */

            if (PkgDesc->Package.Elements[Look]->Number.Value
                 <= V1Desc->Number.Value)
            {
                continue;
            }
            break;


        default:    /* undefined   */

            continue;
        }
 
        
        switch(Op2Desc->Number.Value)
        {

        case MATCH_MTR:

            break;


        case MATCH_MEQ:

            if (PkgDesc->Package.Elements[Look]->Number.Value
                 != V2Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MLE:

            if (PkgDesc->Package.Elements[Look]->Number.Value
                 > V2Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MLT:

            if (PkgDesc->Package.Elements[Look]->Number.Value
                 >= V2Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MGE:

            if (PkgDesc->Package.Elements[Look]->Number.Value
                 < V2Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MGT:

            if (PkgDesc->Package.Elements[Look]->Number.Value
                 <= V2Desc->Number.Value)
            {
                continue;
            }
            break;


        default:

            continue;
        }

        /* Match found: exit from loop */
        
        MatchValue = Look;
        break;
    }

    PkgDesc->Type = (UINT8) TYPE_Number;
    PkgDesc->Number.Value = MatchValue;

    CmFree (StartDesc);
    CmFree (V2Desc);
    CmFree (Op2Desc);
    CmFree (V1Desc);
    CmFree (Op1Desc);
    
    ObjStackTop -= 5;          /* Remove operands */

    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK;
}
