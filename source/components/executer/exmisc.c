
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


#define __IEOPEXEC_C__

#include <acpi.h>
#include <interpreter.h>
#include <amlcode.h>
#include <namespace.h>
#include <string.h>


#define _THIS_MODULE        "ieopexec.c"
#define _COMPONENT          INTERPRETER

static ST_KEY_DESC_TABLE KDT[] = {
    {"0000", '1', "AmlExecStore: Descriptor Allocation Failure", "AmlExecStore: Descriptor Allocation Failure"},
    {"0001", '1', "AmlGetRvalue: Descriptor Allocation Failure", "AmlGetRvalue: Descriptor Allocation Failure"},
    {NULL, 'I', NULL, NULL}
};



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
AmlExecCreateField (UINT16 opcode)
{
    OBJECT_DESCRIPTOR       *ResDesc = NULL;
    OBJECT_DESCRIPTOR       *CntDesc = NULL;
    OBJECT_DESCRIPTOR       *OffDesc = NULL;
    OBJECT_DESCRIPTOR       *SrcDesc = NULL;
    ACPI_STATUS             Status;
    char                    *OpName = NULL;
    INT32                   NumOperands;
    UINT16                  BitCount;
    UINT32                  BitOffset;
    UINT8       			bTypeFound;
    char        			TypeFound[20];
    char        			*TypeFoundPtr = NULL;




    FUNCTION_TRACE ("AmlExecCreateField");


    /*  DefCreateField := CreateFieldOp SourceBuff BitIndex NumBits NameString  */

    if (AML_CreateFieldOp == opcode)
    {
        Status = AmlPrepStack ("lnnb");
        NumOperands = 4;
        OpName = LongOps[opcode & 0x00ff];
    }

    
    /*  Create[Bit|Byte|DWord|Word]Field    */
    /*  DefCreate*Field := Create*FieldOp SourceBuff [Bit|Byte]Index NameString */

    else
    {
        Status = AmlPrepStack ("lnb");
        NumOperands = 3;
        OpName = ShortOps[opcode];
    }

    if (Status != AE_OK)
    {
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, opcode, NumOperands);
        FUNCTION_EXIT;
        return Status;
    }

    AmlDumpStack (MODE_Exec, OpName, NumOperands, "after AmlPrepStack");

    ResDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];        /* result */
    
    if (AML_CreateFieldOp == opcode)
    {
        CntDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];        /* count */
    }

    OffDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop--];        /* offset */
    SrcDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];          /* source */
    ObjStackTop += NumOperands - 1;

    /* If ResDesc is a Name, it will be a direct name pointer after AmlPrepStack() */
    
    if (!IS_NS_HANDLE (ResDesc))
    {
        DEBUG_PRINT (ACPI_ERROR, ("%s: destination must be a Name\n", OpName));
        FUNCTION_EXIT;
        return AE_AML_ERROR;
    }

    switch (opcode)
    {


    /*  DefCreateBitField   :=  CreateBitFieldOp    SourceBuff  BitIndex    NameString  */

    case AML_BitFieldOp:
        BitOffset = OffDesc->Number.Number;             /* offset is in bits */
        BitCount = 1;                                   /* field is a bit */
        break;


    /*  DefCreateByteField  :=  CreateByteFieldOp   SourceBuff  ByteIndex   NameString  */

    case AML_ByteFieldOp:
        BitOffset = 8 * OffDesc->Number.Number;         /* offset is in bytes */
        BitCount = 8;                                   /* field is a Byte */
        break;


    /*  DefCreateWordField  :=  CreateWordFieldOp   SourceBuff  ByteIndex   NameString  */

    case AML_WordFieldOp:
        BitOffset = 8 * OffDesc->Number.Number;         /* offset is in bytes */
        BitCount = 16;                                  /* field is a Word */
        break;


    /*  DefCreateDWordField :=  CreateDWordFieldOp  SourceBuff  ByteIndex   NameString  */

    case AML_DWordFieldOp:
        BitOffset = 8 * OffDesc->Number.Number;         /* offset is in bytes */
        BitCount = 32;                                  /* field is a DWord */
        break;


    /*  DefCreateField  :=  CreateFieldOp   SourceBuff  BitIndex    NumBits NameString  */

    case AML_CreateFieldOp:
        BitOffset = OffDesc->Number.Number;             /* offset is in bits */
        BitCount = (UINT16) CntDesc->Number.Number;       /* as is count */
        break;

    default:
        DEBUG_PRINT (ACPI_ERROR, (
                "AmlExecCreateField:internal error: Unknown field creation opcode %02x\n",
                opcode));
        FUNCTION_EXIT;
        return AE_AML_ERROR;

    } /* switch */


    switch (SrcDesc->ValType)
    {
    
    /*  SourceBuff  :=  TermArg=>Buffer */

    case TYPE_Buffer:
        if (BitOffset + (UINT32) BitCount > 8 * (UINT32) SrcDesc->Buffer.BufLen)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecCreateField: Field exceeds Buffer %d > %d\n",
                            BitOffset + (UINT32)BitCount,
                            8 * (UINT32)SrcDesc->Buffer.BufLen));
            FUNCTION_EXIT;
            return AE_AML_ERROR;
        }

        /* Reuse "OffDesc" descriptor to build result */
        
        OffDesc->ValType                = (UINT8) TYPE_FieldUnit;
        OffDesc->FieldUnit.Access       = (UINT16) ACCESS_AnyAcc;
        OffDesc->FieldUnit.LockRule     = (UINT16) GLOCK_NeverLock;
        OffDesc->FieldUnit.UpdateRule   = (UINT16) UPDATE_Preserve;
        OffDesc->FieldUnit.DatLen       = BitCount;
        OffDesc->FieldUnit.BitOffset    = (UINT16) BitOffset % 8;
        OffDesc->FieldUnit.Offset       = BitOffset / 8;
        OffDesc->FieldUnit.Container    = SrcDesc;
        OffDesc->FieldUnit.ConSeq       = SrcDesc->Buffer.Sequence;
        break;

    default:
        bTypeFound = SrcDesc->ValType;

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
        FUNCTION_EXIT;
        return AE_AML_ERROR;
    
    } /* switch */


    if (AML_CreateFieldOp == opcode)
    {
        /*  delete object descriptor unique to CreateField  */

        OsdFree (CntDesc);
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
    ObjStackTop -= NumOperands - 1;
    
    FUNCTION_EXIT;
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
    OBJECT_DESCRIPTOR       *TypeDesc;
    OBJECT_DESCRIPTOR       *CodeDesc;
    OBJECT_DESCRIPTOR       *ArgDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecFatal");


    Status = AmlPrepStack ("nnn");

    if (Status != AE_OK)
    {
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, (UINT16) AML_FatalOp, 3);
        FUNCTION_EXIT;
        return Status;
    }

    AmlDumpStack (MODE_Exec, LongOps[AML_FatalOp & 0x00ff], 3, "after AmlPrepStack");


    /*  DefFatal    :=  FatalOp FatalType   FatalCode   FatalArg    */

    ArgDesc  = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    CodeDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];
    TypeDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 2];

    DEBUG_PRINT (ACPI_INFO,
                ("FatalOp: Type %x Code %x Arg %x <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n",
                TypeDesc->Number.Number, CodeDesc->Number.Number,
                ArgDesc->Number.Number));

    DEBUG_PRINT (ACPI_ERROR, ("AmlExecFatal: FatalOp executed\n"));
    FUNCTION_EXIT;
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
    OBJECT_DESCRIPTOR       *PkgDesc;
    OBJECT_DESCRIPTOR       *IdxDesc;
    OBJECT_DESCRIPTOR       *ResDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecIndex");


    Status = AmlPrepStack ("lnp");

    if (Status != AE_OK)
    {
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, (UINT16) AML_IndexOp, 3);
    }

    else
    {
        AmlDumpStack (MODE_Exec, ShortOps[AML_IndexOp], 3, "after AmlPrepStack");

        ResDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
        IdxDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];
        PkgDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 2];

        if (IdxDesc->Number.Number < 0 || 
            IdxDesc->Number.Number >= (UINT32) PkgDesc->Package.PkgCount)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecIndex: Index value out of range\n"));
            Status = AE_AML_ERROR;
        }

        else
        {
            /* 
             * XXX - possible dangling reference: if the package vector changes
             * XXX - before this pointer is used, the results may be surprising.
             */
            PkgDesc->Lvalue.Ref     = (void *) &PkgDesc->Package.PackageElems[IdxDesc->Number.Number];
            PkgDesc->ValType        = (UINT8) TYPE_Lvalue;
            PkgDesc->Lvalue.OpCode  = AML_IndexOp;

            Status = AmlExecStore (PkgDesc, ResDesc);
        }

        if (AE_OK == Status)
        {
            OsdFree (IdxDesc);
        }

        ObjStackTop -= 2;
    }

    FUNCTION_EXIT;
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
    OBJECT_DESCRIPTOR       *PkgDesc;
    OBJECT_DESCRIPTOR       *Op1Desc;
    OBJECT_DESCRIPTOR       *V1Desc;
    OBJECT_DESCRIPTOR       *Op2Desc;
    OBJECT_DESCRIPTOR       *V2Desc;
    OBJECT_DESCRIPTOR       *StartDesc;
    ACPI_STATUS             Status;
    UINT32                  Look;
    UINT32                  MatchValue = (UINT32) -1;


    FUNCTION_TRACE ("AmlExecMatch");


    Status = AmlPrepStack ("nnnnnp");

    if (Status != AE_OK)
    {
        /*  invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, (UINT16) AML_MatchOp, 6);
        FUNCTION_EXIT;
        return Status;
    }

    AmlDumpStack (MODE_Exec, ShortOps[AML_MatchOp], 6, "after AmlPrepStack");

    StartDesc = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop];
    V2Desc    = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 1];
    Op2Desc   = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 2];
    V1Desc    = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 3];
    Op1Desc   = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 4];
    PkgDesc   = (OBJECT_DESCRIPTOR *) ObjStack[ObjStackTop - 5];

    /* Validate match comparison sub-opcodes */
    
    if (Op1Desc->Number.Number < 0 || Op1Desc->Number.Number > 5 || 
        Op2Desc->Number.Number < 0 || Op2Desc->Number.Number > 5)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMatch: operation encoding out of range\n"));
        FUNCTION_EXIT;
        return AE_AML_ERROR;
    }

    Look = StartDesc->Number.Number;
    if (Look < 0 || Look >= (UINT32) PkgDesc->Package.PkgCount)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMatch: start position value out of range\n"));
        FUNCTION_EXIT;
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

    for ( ; Look < (UINT32) PkgDesc->Package.PkgCount ; ++Look)
    {
        /* 
         * Treat any NULL or non-numeric elements as non-matching.
         * XXX - if an element is a Name, should we examine its value?
         */
        if (!PkgDesc->Package.PackageElems[Look] ||
            TYPE_Number != PkgDesc->Package.PackageElems[Look]->ValType)
        {
            continue;
        }

        /* 
         * Within these switch statements:
         *      "break" (exit from the switch) signifies a match;
         *      "continue" (proceed to next iteration of enclosing
         *          "for" loop) signifies a non-match.
         */
        switch (Op1Desc->Number.Number)
        {
        case MATCH_MTR:   /*  always true */
            break;

        case MATCH_MEQ:   /*  true if equal   */
            if (PkgDesc->Package.PackageElems[Look]->Number.Number
                 != V1Desc->Number.Number)
            {
                continue;
            }
            break;

        case MATCH_MLE:   /*  true if less than or equal  */
            if (PkgDesc->Package.PackageElems[Look]->Number.Number
                 > V1Desc->Number.Number)
            {
                continue;
            }
            break;

        case MATCH_MLT:   /*  true if less than   */
            if (PkgDesc->Package.PackageElems[Look]->Number.Number
                 >= V1Desc->Number.Number)
            {
                continue;
            }
            break;

        case MATCH_MGE:   /*  true if greater than or equal   */
            if (PkgDesc->Package.PackageElems[Look]->Number.Number
                 < V1Desc->Number.Number)
            {
                continue;
            }
            break;

        case MATCH_MGT:   /*  true if greater than    */
            if (PkgDesc->Package.PackageElems[Look]->Number.Number
                 <= V1Desc->Number.Number)
            {
                continue;
            }
            break;

        default:    /*  undefined   */
            continue;
        }
 
        
        switch(Op2Desc->Number.Number)
        {
        case MATCH_MTR:
            break;

        case MATCH_MEQ:
            if (PkgDesc->Package.PackageElems[Look]->Number.Number
                 != V2Desc->Number.Number)
            {
                continue;
            }
            break;

        case MATCH_MLE:
            if (PkgDesc->Package.PackageElems[Look]->Number.Number
                 > V2Desc->Number.Number)
            {
                continue;
            }
            break;

        case MATCH_MLT:
            if (PkgDesc->Package.PackageElems[Look]->Number.Number
                 >= V2Desc->Number.Number)
            {
                continue;
            }
            break;

        case MATCH_MGE:
            if (PkgDesc->Package.PackageElems[Look]->Number.Number
                 < V2Desc->Number.Number)
            {
                continue;
            }
            break;

        case MATCH_MGT:
            if (PkgDesc->Package.PackageElems[Look]->Number.Number
                 <= V2Desc->Number.Number)
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

    PkgDesc->ValType = (UINT8) TYPE_Number;
    PkgDesc->Number.Number = MatchValue;

    OsdFree (StartDesc);
    OsdFree (V2Desc);
    OsdFree (Op2Desc);
    OsdFree (V1Desc);
    OsdFree (Op1Desc);
    
    ObjStackTop -= 5;          /* Remove operands */

    FUNCTION_EXIT;
    return AE_OK;
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
AmlGetFieldUnitValue (OBJECT_DESCRIPTOR *FieldDesc, OBJECT_DESCRIPTOR *ResultDesc)
{
    ACPI_STATUS         Status = AE_AML_ERROR;
    UINT8               *Location = NULL;
    UINT32              Mask;
    INT32               Locked = FALSE;


    FUNCTION_TRACE ("AmlGetFieldUnitValue");


    if (!FieldDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: internal error: null field pointer\n"));
    }

    else if (!FieldDesc->FieldUnit.Container)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: internal error: null container pointer\n"));
    }

    else if (TYPE_Buffer != FieldDesc->FieldUnit.Container->ValType)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: internal error: container is not a Buffer\n"));
    }

    else if (FieldDesc->FieldUnit.ConSeq
                != FieldDesc->FieldUnit.Container->Buffer.Sequence)
    {
        DEBUG_PRINT (ACPI_ERROR, (
                "AmlGetFieldUnitValue: internal error: stale Buffer [%lx != %lx]\n",
                FieldDesc->FieldUnit.ConSeq,
                FieldDesc->FieldUnit.Container->Buffer.Sequence));
    }

    else if (!ResultDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: internal error: null result pointer\n"));
    }

    else 
    {
        /*  input parameters valid  */

        Status = AE_OK;

        /* Check lock rule prior to modifing the field */

        if (FieldDesc->FieldUnit.LockRule == (UINT16) GLOCK_AlwaysLock)
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
                /* set the Locked Flag */

                Locked = TRUE;
            }
        }
    }


    if (AE_OK == Status)
    {   
        /*  input parameters valid and global lock possibly acquired    */

        if (FieldDesc->FieldUnit.DatLen + FieldDesc->FieldUnit.BitOffset > 32)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetFieldUnitValue: implementation limitation: Field exceeds UINT32\n"));
            Status = AE_AML_ERROR;
        }
    }

    if (AE_OK == Status)
    {   
        /* Field location is (base of buffer) + (byte offset) */
    
        Location = FieldDesc->FieldUnit.Container->Buffer.Buffer
                    + FieldDesc->FieldUnit.Offset;

        /* Construct Mask with as many 1 bits as the field width */
    
        Mask = ((UINT32) 1 << FieldDesc->FieldUnit.DatLen) - (UINT32) 1;

        ResultDesc->Number.ValType = (UINT8) TYPE_Number;

        /* Shift the word containing the field, and mask the value */
    
        ResultDesc->Number.Number
            = *(UINT32 *) Location >> FieldDesc->FieldUnit.BitOffset & Mask;

        DEBUG_PRINT (ACPI_INFO,
            ("** Read from buffer %p byte %ld bit %d width %d addr %p mask %08lx val %08lx\n",
            FieldDesc->FieldUnit.Container->Buffer.Buffer,
            FieldDesc->FieldUnit.Offset,
            FieldDesc->FieldUnit.BitOffset,
            FieldDesc->FieldUnit.DatLen,
            Location, Mask, ResultDesc->Number.Number));
    }

    if (Locked)
    {
        /* Release the Global Lock */
        
        OsReleaseGlobalLock ();
    }

    FUNCTION_EXIT;
    return Status;
}


/*****************************************************************************
 * 
 * FUNCTION:    AmlGetRvalue
 *
 * PARAMETERS:  **StackPtr          - Points to entry on ObjStack, which can 
 *                                    be either an (OBJECT_DESCRIPTOR *)
 *                                    or an NsHandle.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert Lvalue entries on ObjStack to rvalues
 *
 ****************************************************************************/

ACPI_STATUS
AmlGetRvalue (OBJECT_DESCRIPTOR **StackPtr)
{
    NsHandle            TempHandle = NULL;
    OBJECT_DESCRIPTOR   *ObjDesc = NULL;
    ACPI_STATUS         Status = AE_OK;
    UINT8				MvIndex = 0;


    FUNCTION_TRACE ("AmlGetRvalue");


    if (!StackPtr || !*StackPtr)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error: null pointer\n"));
        FUNCTION_EXIT;
        return AE_AML_ERROR;
    }

    switch ((*StackPtr)->ValType)
    {
    case TYPE_Lvalue:

        switch ((*StackPtr)->Lvalue.OpCode)
        {

        case AML_NameOp:
            
            /* Convert indirect name ptr to direct name ptr */
            
            TempHandle = (*StackPtr)->Lvalue.Ref;
            OsdFree (*StackPtr);
            (*StackPtr) = TempHandle;
            Status = AE_OK;
            break;

        case AML_Local0: case AML_Local1: case AML_Local2: case AML_Local3:
        case AML_Local4: case AML_Local5: case AML_Local6: case AML_Local7:

            MvIndex = (*StackPtr)->Lvalue.OpCode - AML_Local0;

            DEBUG_PRINT (ACPI_INFO,
                        ("AmlGetRvalue:Lcl%d: before AmlGetMethodValue %p %p %08lx \n",
                        MvIndex,
                        StackPtr, *StackPtr, *(UINT32 *)* StackPtr));

            Status = AmlGetMethodValue (LCLBASE + (*StackPtr)->Lvalue.OpCode - AML_Local0,
                                    *StackPtr);

            DEBUG_PRINT (ACPI_INFO,
                        ("AmlGetRvalue:Lcl%d: iGMV Status=%s %p %p %08lx \n",
                        MvIndex, ExceptionNames[Status], StackPtr, *StackPtr,
                        *(UINT32 *)* StackPtr));
            
            if (TYPE_Number == (*StackPtr)->ValType)
            {
                /* Value is a Number */
                
                DEBUG_PRINT (ACPI_INFO,
                            ("[%ld] \n", (*StackPtr)->Number.Number));
            }
            break;

        case AML_Arg0: case AML_Arg1: case AML_Arg2: case AML_Arg3:
        case AML_Arg4: case AML_Arg5: case AML_Arg6:

            DEBUG_PRINT (TRACE_EXEC,
                        ("AmlGetRvalue:Arg%d: before AmlGetMethodValue %p %p %08lx \n",
                        MvIndex = (*StackPtr)->Lvalue.OpCode - AML_Arg0,
                        StackPtr, *StackPtr, *(UINT32 *)* StackPtr));

            Status = AmlGetMethodValue (ARGBASE + (*StackPtr)->Lvalue.OpCode - AML_Arg0,
                                    *StackPtr);
        
            DEBUG_PRINT (TRACE_EXEC,
                        ("AmlGetRvalue:Arg%d: iGMV returned %s %p %p %08lx \n",
                        MvIndex, ExceptionNames[Status], StackPtr, *StackPtr,
                        *(UINT32 *)* StackPtr));

            if (TYPE_Number == (*StackPtr)->ValType)
            {
                /* Value is a Number */
                
                DEBUG_PRINT (ACPI_INFO,
                            ("[%ld] \n", (*StackPtr)->Number.Number));
            }

            break;

        case AML_ZeroOp:
            (*StackPtr)->ValType = (UINT8) TYPE_Number;
            (*StackPtr)->Number.Number = 0;
            Status = AE_OK;
            break;

        case AML_OneOp:
            (*StackPtr)->ValType = (UINT8) TYPE_Number;
            (*StackPtr)->Number.Number = 1;
            Status = AE_OK;
            break;

        case AML_OnesOp:
            (*StackPtr)->ValType = (UINT8) TYPE_Number;
            (*StackPtr)->Number.Number = 0xFFFFFFFF;
            Status = AE_OK;
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: Unknown Lvalue subtype %02x\n",
                            (*StackPtr)->Lvalue.OpCode));
            Status = AE_AML_ERROR;

        }   /* switch ((*StackPtr)->Lvalue.OpCode) */

        if (AE_OK != Status)
        {
            FUNCTION_EXIT;
            return Status;
        }

        break;

    case TYPE_FieldUnit:
        ObjDesc = AllocateObjectDesc (&KDT[1]);
        if (!ObjDesc)
        {   
            /*  descriptor allocation failure   */
            
            FUNCTION_EXIT;
            return AE_NO_MEMORY;
        }

        if ((Status = AmlGetFieldUnitValue (*StackPtr, ObjDesc)) != AE_OK)
        {
            OsdFree (ObjDesc);
            ObjDesc = NULL;
        }
        
        *StackPtr = (void *) ObjDesc;
        FUNCTION_EXIT;
        return Status;

    case TYPE_BankField:
        ObjDesc = AllocateObjectDesc (&KDT[1]);
        if (!ObjDesc)
        {   
            /*  descriptor allocation failure   */
            
            FUNCTION_EXIT;
            return AE_NO_MEMORY;
        }

        if ((Status = AmlGetFieldUnitValue (*StackPtr, ObjDesc)) != AE_OK)
        {
            OsdFree(ObjDesc);
            ObjDesc = NULL;
        }

        *StackPtr = (void *) ObjDesc;
        FUNCTION_EXIT;
        return Status;
        break;

    /* XXX - may need to handle IndexField, and DefField someday */

    default:
        break;

    }   /* switch ((*StackPtr)->ValType) */



    if (IS_NS_HANDLE (*StackPtr))       /* direct name ptr */
    {
        OBJECT_DESCRIPTOR   *ValDesc = NULL;
                
            

        DEBUG_PRINT (TRACE_EXEC,
                    ("AmlGetRvalue: found direct name ptr \n"));

        ValDesc = (OBJECT_DESCRIPTOR *) NsGetValue ((NsHandle)* StackPtr);

        DEBUG_PRINT (TRACE_EXEC,
                    ("AmlGetRvalue: NsGetValue(%p) returned Val=%p\n", *StackPtr, ValDesc));

        switch (NsGetType ((NsHandle)* StackPtr))
        {
            UINT32          TempVal;

        case TYPE_Package:

            /* 
             * ValDesc should point to either an OBJECT_DESCRIPTOR of
             * type Package, or an initialization in the AML stream.
             */
            if (!ValDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue/Package:internal error: null ValPtr\n"));
                DEBUG_PRINT (TRACE_EXEC,
                            ("leave AmlGetRvalue: NULL Package ValuePtr ==> AE_AML_ERROR\n"));

                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            if (AML_PackageOp == *(UINT8 *) ValDesc)
            {
                /* 
                 * The value pointer in the name table entry
                 * points to a package definition in the AML stream.
                 * Convert it to an object.
                 */

                if (AE_OK != (Status = AmlPushIfExec (MODE_Exec)))             /* ObjStack */
                {
                    FUNCTION_EXIT;
                    return Status;
                }

                if (AE_OK == (Status = AmlPushExec ((UINT8 *) ValDesc + 1, 0L)) && /*PkgStack*/
                    AE_OK == (Status = AmlDoPkg (TYPE_Package, MODE_Exec)) &&
                    AE_OK == (Status = AmlPopExec ()))                 /* PkgStack */
                {
                    NsSetValue ((NsHandle)* StackPtr,
                                    ObjStack[ObjStackTop],
                                    (UINT8) TYPE_Package);

                    /* Refresh local value pointer to reflect newly set value */
                    
                    ValDesc = (OBJECT_DESCRIPTOR *) NsGetValue ((NsHandle)* StackPtr);
                    ObjStackTop--;
                }
                
                else
                {
                    ObjStackTop--;
                    FUNCTION_EXIT;
                    return Status;
                }
            }
            
            if (!ValDesc || (TYPE_Package != ValDesc->ValType))
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue:internal error: Bad package value\n"));
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc (&KDT[1]);
            if (!ObjDesc)
            {   
                /*  descriptor allocation failure   */
                
                FUNCTION_EXIT;
                return AE_NO_MEMORY;
            }

            memcpy ((void *) ObjDesc, (void *) ValDesc, sizeof (*ObjDesc));
            break;

        case TYPE_String:

            /* XXX - Is there a problem here if the nte points to an AML definition? */
            
            if (TYPE_String != ValDesc->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue:internal error: Bad string value\n"));
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc (&KDT[1]);
            if (!ObjDesc)
            {   
                /*  descriptor allocation failure   */

                FUNCTION_EXIT;
                return AE_NO_MEMORY;
            }

            memcpy ((void *) ObjDesc, (void *) ValDesc, sizeof (*ObjDesc));
            break;

        case TYPE_Buffer:
            if (!ValDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error: null Buffer ValuePtr\n"));
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            if (AML_BufferOp == *(UINT8 *) ValDesc)
            {
                /* 
                 * The value pointer in the name table entry
                 * points to a buffer definition in the AML stream.
                 * Convert it to an object.
                 */
                if (AE_OK != (Status = AmlPushIfExec (MODE_Exec)))                /* ObjStack */
                {
                    FUNCTION_EXIT;
                    return Status;
                }

                if (AE_OK == (Status = AmlPushExec ((UINT8 *) ValDesc + 1, 0L)) &&   /*PkgStack*/
                    AE_OK == (Status = AmlDoPkg (TYPE_Buffer, MODE_Exec)) &&
                    AE_OK == (Status = AmlPopExec ()))                     /* PkgStack */
                {
                    NsSetValue ((NsHandle) *StackPtr,
                                    ObjStack[ObjStackTop],
                                    (UINT8) TYPE_Buffer);
                    
                    /* Refresh local value pointer to reflect newly set value */
                    
                    ValDesc = (OBJECT_DESCRIPTOR *) NsGetValue ((NsHandle)* StackPtr);
                    ObjStackTop--;
                }
                
                else
                {
                    ObjStackTop--;
                    FUNCTION_EXIT;
                    return Status;
                }
            }
            
            if (!ValDesc || (TYPE_Buffer != ValDesc->ValType))
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: Bad buffer value\n"));
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc (&KDT[1]);
            if (!ObjDesc)
            {   
                /*  descriptor allocation failure   */
                
                FUNCTION_EXIT;
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
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error: null Number ValuePtr\n"));
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            if (TYPE_Number == ValDesc->ValType)
            {
                ObjDesc = AllocateObjectDesc (&KDT[1]);
                if (!ObjDesc)
                {   
                    /*  descriptor allocation failure   */
                    
                    FUNCTION_EXIT;
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
                    DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue/Number: internal error: not a Number\n"));
                    FUNCTION_EXIT;
                    return AE_AML_ERROR;
                }

                ObjDesc = AllocateObjectDesc (&KDT[1]);
                if (!ObjDesc)
                {   
                    /*  descriptor allocation failure   */
                    
                    FUNCTION_EXIT;
                    return AE_NO_MEMORY;
                }
                
                switch (*(UINT8 *) ValDesc)
                {
                case AML_ZeroOp:
                    ObjDesc->Number.Number = 0;
                    break;

                case AML_OneOp:
                    ObjDesc->Number.Number = 1;
                    break;

                case AML_OnesOp:
                    ObjDesc->Number.Number = 0xFFFFFFFF;
                    break;

                case AML_ByteOp:
                    ObjDesc->Number.Number = (UINT32)((UINT8 *) ValDesc)[1];
                    break;

                /* 
                 *  XXX - WordOp and DWordOp will not work properly if the
                 *  XXX - processor's endianness does not match the AML's.
                 */
                case AML_WordOp:
                    ObjDesc->Number.Number = (UINT32)*(UINT16 *)&((UINT8 *) ValDesc)[1];
                    break;

                case AML_DWordOp:
                    ObjDesc->Number.Number = *(UINT32 *)&((UINT8 *) ValDesc)[1];
                    break;

                default:
                    OsdFree (ObjDesc);
                    DEBUG_PRINT (ACPI_ERROR, (
                            "AmlGetRvalue/Number: internal error: Expected AML number, found %02x\n",
                            *(UINT8 *) ValDesc));
                    FUNCTION_EXIT;
                    return AE_AML_ERROR;
                
                }   /* switch */
                
                ObjDesc->Number.ValType = (UINT8) TYPE_Number;
            }
            break;

        case TYPE_DefField:

            /* 
             * XXX - Implementation limitation: Fields are implemented as type
             * XXX - Number, but they really are supposed to be type Buffer.
             * XXX - The two are interchangeable only for lengths <= 32 bits.
             */
            Status = AmlGetNamedFieldValue ((NsHandle)* StackPtr, &TempVal);
            if (AE_OK != Status)
            {
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc (&KDT[1]);
            if (!ObjDesc)
            {   
                /*  descriptor allocation failure   */
                
                FUNCTION_EXIT;
                return AE_NO_MEMORY;
            }

            ObjDesc->Number.ValType = (UINT8) TYPE_Number;
            ObjDesc->Number.Number = TempVal;
            break;

        case TYPE_BankField:
            if (!ValDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error: null BankField ValuePtr\n"));
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            if (TYPE_BankField != ValDesc->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlGetRvalue/BankField:internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                        *StackPtr, TYPE_BankField, ValDesc->ValType, ValDesc));
                
                AmlAppendBlockOwner (ValDesc);
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            /* Set Index value to select proper Data register */
            /* Check lock rule prior to modifing the field */
            
            if (ObjDesc->FieldUnit.LockRule == (UINT16) GLOCK_AlwaysLock)
            {
                /* Lock Rule is Lock */
                
                if (OsGetGlobalLock () != AE_OK)
                {
                    /* the ownship failed - Bad Bad Bad, this is a single threaded */
                    /* implementation so there is no way some other process should */
                    /* own this.  This means something grabbed it and did not */
                    /* release the Global Lock! */
                    
                    FUNCTION_EXIT;
                    return (AE_AML_ERROR);
                }
            }


            /* perform the update */
            
            Status = AmlSetNamedFieldValue (ValDesc->BankField.BankSelect,
                                           ValDesc->BankField.BankVal);


            if ((UINT16) GLOCK_AlwaysLock == ObjDesc->FieldUnit.LockRule)   /*  Lock Rule is Lock   */
            {
                OsReleaseGlobalLock ();
            }

            if (AE_OK != Status)
            {
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }
            
            /* Read Data value */
            
            Status = AmlGetNamedFieldValue ((NsHandle) ValDesc->BankField.Container, &TempVal);
            if (AE_OK != Status)
            {
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc (&KDT[1]);
            if (!ObjDesc)
            {
                /*  descriptor allocation failure   */

                FUNCTION_EXIT;
                return AE_NO_MEMORY;
            }

            ObjDesc->Number.ValType = (UINT8) TYPE_Number;
            ObjDesc->Number.Number = TempVal;
            break;


        case TYPE_IndexField:
            if (!ValDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error: null IndexField ValuePtr\n"));
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            if (TYPE_IndexField != ValDesc->ValType)
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlGetRvalue/IndexField: internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                        *StackPtr, TYPE_IndexField, ValDesc->ValType, ValDesc));
                
                AmlAppendBlockOwner (ValDesc);
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            /* Set Index value to select proper Data register */
            /* Check lock rule prior to modifing the field */
            
            if (ObjDesc->FieldUnit.LockRule == (UINT16) GLOCK_AlwaysLock)
            {
                /* Lock Rule is Lock */
                
                if (OsGetGlobalLock () != AE_OK)
                {
                    /* the ownship failed - Bad Bad Bad, this is a single threaded */
                    /* implementation so there is no way some other process should */
                    /* own this.  This means something grabbed it and did not */
                    /* release the Global Lock!  */
                    
                    FUNCTION_EXIT;
                    return (AE_AML_ERROR);
                }
                
                else
                {
                    /* perform the update */
                    
                    Status = AmlSetNamedFieldValue (ValDesc->IndexField.Index,
                                                   ValDesc->IndexField.IndexVal);
                }
                
                /* Release the Global Lock */
                
                OsReleaseGlobalLock ();
            }
            
            else
            {
                /* Lock Rule is NoLock */
                /* perform the update */
                
                Status = AmlSetNamedFieldValue (ValDesc->IndexField.Index,
                                               ValDesc->IndexField.IndexVal);
            }

            if (AE_OK != Status)
            {
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            /* Read Data value */
            
            Status = AmlGetNamedFieldValue (ValDesc->IndexField.Data, &TempVal);
            if (AE_OK != Status)
            {
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            ObjDesc = AllocateObjectDesc (&KDT[1]);
            if (!ObjDesc)
            {
                /*  descriptor allocation failure   */

                FUNCTION_EXIT;
                return AE_NO_MEMORY;
            }

            ObjDesc->Number.ValType = (UINT8) TYPE_Number;
            ObjDesc->Number.Number = TempVal;
            break;

        case TYPE_FieldUnit:
            if (!ValDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: internal error: null FieldUnit ValuePtr\n"));
                FUNCTION_EXIT;
                return AE_AML_ERROR;
            }

            if (ValDesc->ValType != (UINT8) NsGetType ((NsHandle)* StackPtr))
            {
                DEBUG_PRINT (ACPI_ERROR, (
                        "AmlGetRvalue/FieldUnit:internal error: Name %4.4s type %d does not match value-type %d at %p\n",
                          *StackPtr, NsGetType ((NsHandle)* StackPtr),
                          ValDesc->ValType, ValDesc));
                
                AmlAppendBlockOwner (ValDesc);
                FUNCTION_EXIT;
                return AE_AML_ERROR;
                break;
            }

            ObjDesc = AllocateObjectDesc (&KDT[1]);
            if (!ObjDesc)
            {
                /*  descriptor allocation failure   */

                FUNCTION_EXIT;
                return AE_NO_MEMORY;
            }

            if ((Status = AmlGetFieldUnitValue (ValDesc, ObjDesc)) != AE_OK)
            {
                OsdFree (ObjDesc);
                FUNCTION_EXIT;
                return Status;
            }

            break;

        /* cases which just return the name as the rvalue */
        
        case TYPE_Device:
            FUNCTION_EXIT;
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
                        NsTypeNames[NsGetType ((NsHandle)* StackPtr)]));
          
#ifdef HACK
            DEBUG_PRINT (ACPI_WARN,
                        ("** AmlGetRvalue: Fetch from [%s] not implemented, using value 0\n",
                        NsTypeNames[NsGetType ((NsHandle)* StackPtr)]));
            
            ObjDesc = AllocateObjectDesc (&KDT[1]);
            if (!ObjDesc)
            {
                /*  descriptor allocation failure   */
                
                FUNCTION_EXIT;
                return AE_NO_MEMORY;
            }

            ObjDesc->Number.ValType = (UINT8) Number;
            ObjDesc->Number.Number = 0x0;
            break;
#else
            DEBUG_PRINT (ACPI_ERROR, (
                    "AmlGetRvalue: Fetch from [%s] not implemented\n",
                    NsTypeNames[NsGetType ((NsHandle)* StackPtr)]));
            
            FUNCTION_EXIT;
            return AE_AML_ERROR;
#endif /* HACK */

        default:

            DEBUG_PRINT (TRACE_EXEC, 
                        ("AmlGetRvalue: case default handle type unexpected: AE_AML_ERROR \n"));

            DEBUG_PRINT (ACPI_ERROR, ("AmlGetRvalue: Unknown NsType %d\n",
                            NsGetType ((NsHandle)* StackPtr)));
            FUNCTION_EXIT;
            return AE_AML_ERROR;
        }

        *StackPtr = (void *) ObjDesc;
    }

    DEBUG_PRINT (TRACE_EXEC, ("leave AmlGetRvalue: AE_OK\n"));

    FUNCTION_EXIT;
    return AE_OK;
}


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
AmlIsMethodValue (OBJECT_DESCRIPTOR *ObjDesc)
{
    INT32           MethodNestLevel;
    INT32           Index;


    FUNCTION_TRACE ("AmlIsMethodValue");


    /* For each active Method */
    
    for (MethodNestLevel = MethodStackTop; MethodNestLevel >= 0; --MethodNestLevel)
    {
        /* For each possible Arg and Local */
        
        for (Index = 0; Index < (ARGBASE + NUMARG); ++Index)
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


