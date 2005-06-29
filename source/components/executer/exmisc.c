
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

#define __IEOPEXEC_C__

#include <acpi.h>
#include <parser.h>
#include <interp.h>
#include <amlcode.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("ieopexec");



/*****************************************************************************
 * 
 * FUNCTION:    AmlExecFatal
 *
 * PARAMETERS:  none
 *
 * RETURN:      Status.  If the OS returns from the OSD call, we just keep
 *              on going.
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
AmlExecFatal (    
    ACPI_OBJECT_INTERNAL    **Operands)
{
    ACPI_OBJECT_INTERNAL    *TypeDesc;
    ACPI_OBJECT_INTERNAL    *CodeDesc;
    ACPI_OBJECT_INTERNAL    *ArgDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecFatal");


    Status = AmlPrepOperands ("nnn", Operands);

    if (Status != AE_OK)
    {
        /* invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, (UINT16) AML_FatalOp, Operands, 3);
        goto Cleanup;
    }

    DUMP_OPERANDS (Operands, IMODE_Execute, PsGetOpcodeName (AML_FatalOp), 3, "after AmlPrepOperands");


    /* DefFatal    :=  FatalOp FatalType   FatalCode   FatalArg    */

    ArgDesc  = Operands[0];
    CodeDesc = Operands[-1];
    TypeDesc = Operands[-2];

    DEBUG_PRINT (ACPI_INFO, ("FatalOp: Type %x Code %x Arg %x <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n",
                    TypeDesc->Number.Value, CodeDesc->Number.Value, ArgDesc->Number.Value));


    /* TBD: call OSD interface to notify OS of fatal error requiring shutdown! */


Cleanup:

    /* Free the operands */

    CmDeleteOperand (&Operands[0]);
    CmDeleteOperand (&Operands[-1]);
    CmDeleteOperand (&Operands[-2]);


    /* If we get back from the OS call, we might as well keep going. */

    DEBUG_PRINT (ACPI_ERROR, ("AmlExecFatal: FatalOp executed\n"));
    return_ACPI_STATUS (AE_OK);
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
AmlExecIndex (
    ACPI_OBJECT_INTERNAL    **Operands,
    ACPI_OBJECT_INTERNAL    **ReturnDesc)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *IdxDesc;
    ACPI_OBJECT_INTERNAL    *ResDesc;
    ACPI_OBJECT_INTERNAL    *RetDesc = NULL;
    ACPI_OBJECT_INTERNAL    *TmpDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AmlExecIndex");


    /* First operand can be either a package or a buffer */

    Status = AmlPrepOperands ("lnp", Operands);

    if (Status == AE_TYPE)
    {
        Status = AmlPrepOperands ("lnb", Operands);
    }

    if (Status != AE_OK)
    {
        /* invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, (UINT16) AML_IndexOp, Operands, 3);
        goto Cleanup;
    }

    DUMP_OPERANDS (Operands, IMODE_Execute, PsGetOpcodeName (AML_IndexOp), 3, "after AmlPrepOperands");

    ResDesc = Operands[0];
    IdxDesc = Operands[-1];
    ObjDesc = Operands[-2];


    RetDesc = CmCreateInternalObject (INTERNAL_TYPE_Lvalue);
    if (!RetDesc)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }


    /*
     * At this point, the ObjDesc operand is either a Package or a Buffer
     */

    if (ObjDesc->Common.Type == ACPI_TYPE_Package)
    {
        /* Object to be indexed is a Package */

        if (IdxDesc->Number.Value >= ObjDesc->Package.Count)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecIndex: Index value out of range\n"));
            Status = AE_AML_PACKAGE_LIMIT;
            goto Cleanup;
        }

        if ((ResDesc->Common.Type == INTERNAL_TYPE_Lvalue) &&
            (ResDesc->Lvalue.OpCode == AML_ZeroOp))
        {
            /* 
             * There is no actual result descriptor (the ZeroOp Result descriptor is a placeholder),
             * so just delete the placeholder and return a reference to the package element
             */

            CmDeleteInternalObject (ResDesc);
        }

        else
        {
            /* 
             * TBD - possible dangling reference: if the package vector changes
             * TBD - before this pointer is used, the results may be surprising.
             */

            /* 
             * Each element of the package is an internal object.  Get the one
             * we are after.
             */

            TmpDesc                      = ObjDesc->Package.Elements[IdxDesc->Number.Value];
            RetDesc->Lvalue.OpCode       = AML_IndexOp;
            RetDesc->Lvalue.TargetType   = TmpDesc->Common.Type;
            RetDesc->Lvalue.Object       = TmpDesc;

            Status = AmlExecStore (RetDesc, ResDesc);
            RetDesc->Lvalue.Object       = NULL;
        }

        /*
         * The local return object must always be a reference to the package element,
         * not the element itself.
         */
        RetDesc->Lvalue.OpCode       = AML_IndexOp;
        RetDesc->Lvalue.TargetType   = ACPI_TYPE_Package;
        RetDesc->Lvalue.Where        = &ObjDesc->Package.Elements[IdxDesc->Number.Value];
    }

    else
    {
        /* Object to be indexed is a Buffer */

        if (IdxDesc->Number.Value >= ObjDesc->Buffer.Length)
        {
            DEBUG_PRINT (ACPI_ERROR, ("AmlExecIndex: Index value out of range\n"));
            Status = AE_AML_BUFFER_LIMIT;
            goto Cleanup;
        }

        /* 
         * TBD - possible dangling reference: if the package vector changes
         * TBD - before this pointer is used, the results may be surprising.
         */
        RetDesc->Lvalue.OpCode       = AML_IndexOp;
        RetDesc->Lvalue.TargetType   = ACPI_TYPE_Buffer;
        RetDesc->Lvalue.Object       = ObjDesc;
        RetDesc->Lvalue.Offset       = IdxDesc->Number.Value;

        Status = AmlExecStore (RetDesc, ResDesc);
    }


Cleanup:

    /* Always delete operands */

    CmDeleteOperand (&Operands[-1]);
    CmDeleteOperand (&Operands[-2]);

    /* Delete return object on error */

    if (ACPI_FAILURE (Status) &&
        (RetDesc))
    {
        CmDeleteInternalObject (RetDesc);
        RetDesc = NULL;
    }


    /* Set the return object and exit */

    *ReturnDesc = RetDesc;
    return_ACPI_STATUS (Status);
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
AmlExecMatch (
    ACPI_OBJECT_INTERNAL    **Operands,
    ACPI_OBJECT_INTERNAL    **ReturnDesc)
{
    ACPI_OBJECT_INTERNAL    *PkgDesc;
    ACPI_OBJECT_INTERNAL    *Op1Desc;
    ACPI_OBJECT_INTERNAL    *V1Desc;
    ACPI_OBJECT_INTERNAL    *Op2Desc;
    ACPI_OBJECT_INTERNAL    *V2Desc;
    ACPI_OBJECT_INTERNAL    *StartDesc;
    ACPI_OBJECT_INTERNAL    *RetDesc = NULL;
    ACPI_STATUS             Status;
    UINT32                  Index;
    UINT32                  MatchValue = (UINT32) -1;


    FUNCTION_TRACE ("AmlExecMatch");


    Status = AmlPrepOperands ("nnnnnp", Operands);

    if (Status != AE_OK)
    {
        /* invalid parameters on object stack  */

        AmlAppendOperandDiag (_THIS_MODULE, __LINE__, (UINT16) AML_MatchOp, Operands, 6);
        goto Cleanup;
    }


    /* Get the parameters from the object stack */

    DUMP_OPERANDS (Operands, IMODE_Execute, PsGetOpcodeName (AML_MatchOp), 6, "after AmlPrepOperands");

    StartDesc = Operands[0];
    V2Desc    = Operands[-1];
    Op2Desc   = Operands[-2];
    V1Desc    = Operands[-3];
    Op1Desc   = Operands[-4];
    PkgDesc   = Operands[-5];

    /* Validate match comparison sub-opcodes */
    
    if ((Op1Desc->Number.Value > MAX_MATCH_OPERATOR) || 
        (Op2Desc->Number.Value > MAX_MATCH_OPERATOR))
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMatch: operation encoding out of range\n"));
        Status = AE_AML_OPERAND_VALUE;
        goto Cleanup;
    }

    Index = StartDesc->Number.Value;
    if (Index >= (UINT32) PkgDesc->Package.Count)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecMatch: start position value out of range\n"));
        Status = AE_AML_PACKAGE_LIMIT;
        goto Cleanup;
    }

    RetDesc = CmCreateInternalObject (ACPI_TYPE_Number);
    if (!RetDesc)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;

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

    for ( ; Index < PkgDesc->Package.Count; ++Index)
    {
        /* 
         * Treat any NULL or non-numeric elements as non-matching.
         * XXX - if an element is a Name, should we examine its value?
         */
        if (!PkgDesc->Package.Elements[Index] ||
            ACPI_TYPE_Number != PkgDesc->Package.Elements[Index]->Common.Type)
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

            if (PkgDesc->Package.Elements[Index]->Number.Value
                 != V1Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MLE:   /* true if less than or equal  */

            if (PkgDesc->Package.Elements[Index]->Number.Value
                 > V1Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MLT:   /* true if less than   */

            if (PkgDesc->Package.Elements[Index]->Number.Value
                 >= V1Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MGE:   /* true if greater than or equal   */

            if (PkgDesc->Package.Elements[Index]->Number.Value
                 < V1Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MGT:   /* true if greater than    */

            if (PkgDesc->Package.Elements[Index]->Number.Value
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

            if (PkgDesc->Package.Elements[Index]->Number.Value
                 != V2Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MLE:

            if (PkgDesc->Package.Elements[Index]->Number.Value
                 > V2Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MLT:

            if (PkgDesc->Package.Elements[Index]->Number.Value
                 >= V2Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MGE:

            if (PkgDesc->Package.Elements[Index]->Number.Value
                 < V2Desc->Number.Value)
            {
                continue;
            }
            break;


        case MATCH_MGT:

            if (PkgDesc->Package.Elements[Index]->Number.Value
                 <= V2Desc->Number.Value)
            {
                continue;
            }
            break;


        default:

            continue;
        }

        /* Match found: exit from loop */
        
        MatchValue = Index;
        break;
    }

    /* MatchValue is the return value */

    RetDesc->Number.Value = MatchValue;


Cleanup:

    /* Free the operands */

    CmDeleteOperand (&Operands[0]);
    CmDeleteOperand (&Operands[-1]);
    CmDeleteOperand (&Operands[-2]);
    CmDeleteOperand (&Operands[-3]);
    CmDeleteOperand (&Operands[-4]);
    CmDeleteOperand (&Operands[-5]);
    
    /* Delete return object on error */

    if (ACPI_FAILURE (Status) &&
        (RetDesc))
    {
        CmDeleteInternalObject (RetDesc);
        RetDesc = NULL;
    }


    /* Set the return object and exit */

    *ReturnDesc = RetDesc;
    return_ACPI_STATUS (Status);
}
