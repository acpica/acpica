
/******************************************************************************
 * 
 * Module Name: dsutils - Dispatcher utilities
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

#define __DSUTILS_C__

#include <acpi.h>
#include <parser.h>
#include <amlcode.h>
#include <dispatch.h>
#include <interp.h>
#include <namesp.h>
#include <debugger.h>

#define _COMPONENT          PARSER
        MODULE_NAME         ("dsutils");



/*****************************************************************************
 *
 * FUNCTION:    DsDeleteResultIfNotUsed
 *
 * PARAMETERS:  Op
 *              ResultObj
 *              WalkState
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Used after interpretation of an opcode.  If there is an internal
 *              result descriptor, check if the parent opcode will actually use
 *              this result.  If not, delete the result now so that it will 
 *              not become orphaned.
 *
 ****************************************************************************/

void
DsDeleteResultIfNotUsed (
    ACPI_GENERIC_OP         *Op,
    ACPI_OBJECT_INTERNAL    *ResultObj,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OP_INFO            *ParentInfo;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_STATUS             Status;


    FUNCTION_TRACE_PTR ("DsDeleteResultIfNotUsed", ResultObj);


    if (!Op)
    {
        DEBUG_PRINT (ACPI_ERROR, ("DsDeleteResultIfNotUsed: Null Op=%X\n",
                        Op));
        return_VOID;
    }

    if (!ResultObj)
    {
        return_VOID;
    }

    if (!Op->Parent)
    {
        /* 
         * If there is no parent, the result can't possibly be used!
         * (An executing method typically has no parent, since each method is parsed separately
         */

        /* Must pop the result stack (ObjDesc should be equal to ResultObj) */

        Status = DsResultStackPop (&ObjDesc, WalkState);
        if (ACPI_FAILURE (Status))
        {
            return;
        }

        CmDeleteInternalObject (ObjDesc);

        return_VOID;
    }


    /*
     * Get info on the parent.  The root Op is AML_Scope
     */

    ParentInfo = PsGetOpcodeInfo (Op->Parent->Opcode);
    if (!ParentInfo)
    {
        DEBUG_PRINT (ACPI_ERROR, ("DsDeleteResultIfNotUsed: Unknown parent opcode. Op=%X\n",
                        Op));

        return_VOID;
    }


    /* Never delete the return value associated with a return opcode */

    if (Op->Parent->Opcode == AML_ReturnOp)
    {
        DEBUG_PRINT (TRACE_DISPATCH, ("DsDeleteResultIfNotUsed: No delete, [RETURN] opcode=%X Op=%X\n",
                        Op->Opcode, Op));
        return_VOID;
    }


    /*
     * Decide what to do with the result based on the parent.  If the parent opcode
     * will not use the result, delete the object.  Otherwise leave it as is, it will
     * be deleted when it is used as an operand later.
     */

    switch (ParentInfo->Flags & OP_INFO_TYPE)
    {
    /*
     * In these cases, the parent will never use the return object, so delete it 
     * here and now.
     */
    case OPTYPE_CONTROL:        /* IF, ELSE, WHILE only */
    case OPTYPE_NAMED_OBJECT:   /* Scope, method, etc. */

        DEBUG_PRINT (TRACE_DISPATCH, ("DsDeleteResultIfNotUsed: Deleting result, Parent opcode=%X Op=%X\n",
                        Op->Opcode, Op));

        /* Must pop the result stack (ObjDesc should be equal to ResultObj) */

        Status = DsResultStackPop (&ObjDesc, WalkState);
        if (ACPI_FAILURE (Status))
        {
            return_VOID;
        }

        CmDeleteInternalObject (ObjDesc);
        break;

    /* 
     * In all other cases. the parent will actually use the return object, so keep it.
     */
    default:
        break;
    }

    return_VOID;
}




/*****************************************************************************
 *
 * FUNCTION:    DsCreateOperand
 *
 * PARAMETERS:  WalkState
 *              Arg
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Translate a parse tree object that is an argument to an AML
 *              opcode to the equivalent interpreter object.  This may include
 *              looking up a name or entering a new name into the internal
 *              namespace.
 *
 ****************************************************************************/

ACPI_STATUS
DsCreateOperand (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Arg)
{
    ACPI_STATUS             Status = AE_OK;
    char                    *NameString;
    UINT32                  NameLength;
    ACPI_OBJECT_TYPE        DataType; 
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_GENERIC_OP         *ParentOp;
    UINT16                  Opcode;
    UINT32                  Flags;
    OPERATING_MODE          InterpreterMode;


    FUNCTION_TRACE_PTR ("DsCreateOperand", Arg);


    /* A valid name must be looked up in the namespace */

    if ((Arg->Opcode == AML_NAMEPATH) &&
        (Arg->Value.String))
    {
        DEBUG_PRINT (TRACE_DISPATCH, ("DsCreateOperand: Getting a name: Arg=%p\n", Arg));

        /* Get the entire name string from the AML stream */

        Status = AmlGetNameString (ACPI_TYPE_Any, Arg->Value.Buffer, &NameString, &NameLength);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        /* All prefixes have been handled, and the name is in NameString */

        /*
         * Differentiate between a namespace "create" operation versus a "lookup" operation 
         * (IMODE_LoadPass2 vs. IMODE_Execute) in order to support the creation of namespace
         * objects during the execution of control methods.
         */

        ParentOp = Arg->Parent;
        if ((PsIsNamedObjectOp (ParentOp->Opcode)) &&
            (ParentOp->Opcode != AML_METHODCALL) &&
            (ParentOp->Opcode != AML_NAMEPATH))
        {
            /* Enter name into namespace if not found */

            InterpreterMode = IMODE_LoadPass2;
        }

        else
        {
            /* Return a failure if name not found */

            InterpreterMode = IMODE_Execute;
        }

        Status = NsLookup (WalkState->ScopeInfo, NameString, ACPI_TYPE_Any, InterpreterMode, 
                                    NS_SEARCH_PARENT | NS_DONT_OPEN_SCOPE, WalkState, (NAME_TABLE_ENTRY **) &ObjDesc);

        /* Free the namestring created above */

        CmFree (NameString);

        /*
         * The only case where we pass through (ignore) a NOT_FOUND error is for the 
         * CondRefOf opcode.
         */

        if ((Status == AE_NOT_FOUND) &&
            (ParentOp->Opcode == AML_CondRefOfOp))
        {
            ObjDesc = (ACPI_OBJECT_INTERNAL *) Gbl_RootObject;
            Status = AE_OK;
        }

        /* Check status from the lookup */

        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        DsObjStackPush (ObjDesc, WalkState);
        DEBUG_EXEC (DbDisplayArgumentObject (ObjDesc));
    }


    else
    {
        /* Check for null name case */

        if (Arg->Opcode == AML_NAMEPATH)
        {
            /*
             * If the name is null, this means that this is an optional result parameter that was
             * not specified in the original ASL.  Create an Lvalue for a placeholder 
             */
            Opcode = AML_ZeroOp;        /* Has no arguments! */

            DEBUG_PRINT (TRACE_DISPATCH, ("DsCreateOperand: Null namepath: Arg=%p\n", Arg));

            /* TBD: anything else needed for the zero op lvalue? */
        }

        else
        {
            Opcode = Arg->Opcode;
        }


        /* Get the data type of the argument */

        DataType = DsMapOpcodeToDataType (Opcode, &Flags);
        if (DataType == INTERNAL_TYPE_Invalid)
        {
            return_ACPI_STATUS (AE_NOT_IMPLEMENTED);
        }

        if (Flags & OP_HAS_RETURN_VALUE)
        {
            DEBUG_PRINT (TRACE_DISPATCH, ("DsCreateOperand: Argument already created, getting from result stack \n"));

            /* 
             * Use value that was already previously returned by the evaluation of this argument
             */

            Status = DsResultStackPop (&ObjDesc, WalkState);
            if (ACPI_FAILURE (Status))
            {
                /*
                 * Only error is underflow, and this indicates a missing operand!
                 */
                DEBUG_PRINT (ACPI_ERROR, ("DsCreateOperand: Could not pop result\n"));
                return_ACPI_STATUS (AE_AML_NO_OPERAND);
            }

            /* There must be a valid value on the stack or something is seriously wrong */

            if (!ObjDesc)
            {
                DEBUG_PRINT (ACPI_ERROR, ("DsCreateOperand: But result obj is null! Arg=%X\n", Arg));
                return_ACPI_STATUS (AE_AML_NO_OPERAND);
            }
        }

        else
        {
            /* Create an ACPI_INTERNAL_OBJECT for the argument */

            ObjDesc = CmCreateInternalObject (DataType);
            if (!ObjDesc)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            /* Initialize the new object */

            Status = DsInitObjectFromOp (WalkState, Arg, Opcode, ObjDesc);
            if (ACPI_FAILURE (Status))
            {
                CmFree (ObjDesc);
                return_ACPI_STATUS (Status);
            }
        }


        /* Put the operand object on the object stack */

        DsObjStackPush (ObjDesc, WalkState);
        DEBUG_EXEC (DbDisplayArgumentObject (ObjDesc));
    }


    return_ACPI_STATUS (AE_OK);
}



/*****************************************************************************
 *
 * FUNCTION:    DsCreateOperands
 *
 * PARAMETERS:  FirstArg            - First argument of a parser argument tree
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert an operator's arguments from a parse tree format to
 *              namespace objects and place those argument object on the object
 *              stack in preparation for evaluation by the interpreter.
 *
 ****************************************************************************/

ACPI_STATUS
DsCreateOperands (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *FirstArg)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_GENERIC_OP         *Arg;
    UINT32                  ArgsPushed = 0;
 

    FUNCTION_TRACE_PTR ("DsCreateOperands", FirstArg);

    Arg = FirstArg;


    /* For all arguments in the list... */

    while (Arg)
    {

        Status = DsCreateOperand (WalkState, Arg);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }

        DEBUG_PRINT (TRACE_DISPATCH, ("DsCreateOperands: Arg #%d (%p) done, Arg1=%p\n", 
                        ArgsPushed, Arg, FirstArg));

        /* Move on to next argument, if any */

        Arg = Arg->Next;
        ArgsPushed++;
    }

    return_ACPI_STATUS (Status);


Cleanup:
    /* 
     * We must undo everything done above; meaning that we must pop everything off
     * of the operand stack and delete those objects 
     */

    DsObjStackPopAndDelete (ArgsPushed, WalkState);

    DEBUG_PRINT (ACPI_ERROR, ("DsCreateOperands: Error while creating Arg %d - %s\n",
                    (ArgsPushed+1), CmFormatException (Status)));
    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    DsResolveOperands
 *
 * PARAMETERS:  WalkState           - Current walk state with operands on stack
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Resolve all operands to their values.  Used to prepare arguments
 *              to a control method invocation (a call from one method to another.)
 *
 ****************************************************************************/

ACPI_STATUS
DsResolveOperands (
    ACPI_WALK_STATE         *WalkState)
{
    UINT32                  i;
    ACPI_STATUS             Status = AE_OK;

    
    FUNCTION_TRACE_PTR ("DsResolveOperands", WalkState);


    /* 
     * Attempt to resolve each of the valid operands 
     * Method arguments are passed by value, not by reference
     */
    
    /*
     * TBD: Note from previous parser:
     *
     * TBD: RefOf problem with AmlGetRvalue() conversion.
     */

    for (i = 0; i < WalkState->NumOperands; i++)
    {
        Status = AmlGetRvalue (&WalkState->Operands[i]);
        if (ACPI_FAILURE (Status))
        {
            break;
        }
    }

    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    DsMapOpcodeToDataType
 *
 * PARAMETERS:  Opcode          - AML opcode to map
 *              OutFlags        - Additional info about the opcode
 *
 * RETURN:      The ACPI type associated with the opcode
 *
 * DESCRIPTION: Convert a raw AML opcode to the associated ACPI data type,
 *              if any.  If the opcode returns a value as part of the 
 *              intepreter execution, a flag is returned in OutFlags.
 *
 ****************************************************************************/

ACPI_OBJECT_TYPE
DsMapOpcodeToDataType (
    UINT16                  Opcode,
    UINT32                  *OutFlags)
{
    ACPI_OBJECT_TYPE        DataType = INTERNAL_TYPE_Invalid;
    ACPI_OP_INFO            *OpInfo;
    UINT32                  Flags = 0;


    OpInfo = PsGetOpcodeInfo (Opcode);
    if (!OpInfo)
    {
        /* Unknown opcode */

        return DataType;
    }

    switch (OpInfo->Flags & OP_INFO_TYPE)
    {

    case OPTYPE_LITERAL:

        switch (Opcode)
        {
        case AML_ByteOp:
        case AML_WordOp:
        case AML_DWordOp:

            DataType = ACPI_TYPE_Number;
            break;


        case AML_StringOp:

            DataType = ACPI_TYPE_String;
            break;

        case AML_NAMEPATH:
            DataType = INTERNAL_TYPE_Reference;
            break;
        }

        break;


    case OPTYPE_DATA_TERM:

        switch (Opcode)
        {
        case AML_BufferOp:

            DataType = ACPI_TYPE_Buffer;
            break;

        case AML_PackageOp:

            DataType = ACPI_TYPE_Package;
            break;
        }

        break;


    case OPTYPE_CONSTANT:
    case OPTYPE_METHOD_ARGUMENT:
    case OPTYPE_LOCAL_VARIABLE:

        DataType = INTERNAL_TYPE_Lvalue;
        break;


    case OPTYPE_MONADIC2:
    case OPTYPE_MONADIC2R:
    case OPTYPE_DYADIC2:
    case OPTYPE_DYADIC2R:
    case OPTYPE_DYADIC2S:
    case OPTYPE_INDEX:
    case OPTYPE_MATCH:

        Flags = OP_HAS_RETURN_VALUE;
        DataType = ACPI_TYPE_Any;

        break;

    case OPTYPE_METHOD_CALL:

        Flags = OP_HAS_RETURN_VALUE;
        DataType = ACPI_TYPE_Method;

        break;


    case OPTYPE_NAMED_OBJECT:

        DataType = DsMapNamedOpcodeToDataType (Opcode);

        break;


    case OPTYPE_DYADIC1:
    case OPTYPE_CONTROL:

        /* No mapping needed at this time */

        break;


    default:

        DEBUG_PRINT (ACPI_ERROR, ("MapOpcode: Unimplemented data type opcode: %x\n",
                        Opcode));
        break;
    }

    /* Return flags to caller if requested */

    if (OutFlags)
    {
        *OutFlags = Flags;
    }

    return DataType;
}


/*****************************************************************************
 *
 * FUNCTION:    DsMapNamedOpcodeToDataType
 *
 * PARAMETERS:  Opcode              - The Named AML opcode to map
 *
 * RETURN:      The ACPI type associated with the named opcode
 *
 * DESCRIPTION: Convert a raw Named AML opcode to the associated data type.
 *              Named opcodes are a subsystem of the AML opcodes.
 *
 ****************************************************************************/

ACPI_OBJECT_TYPE 
DsMapNamedOpcodeToDataType (
    UINT16                  Opcode)
{
    ACPI_OBJECT_TYPE        DataType; 


    /* Decode Opcode */

    switch (Opcode)
    {
    case AML_ScopeOp:
        DataType = INTERNAL_TYPE_Scope;
        break;

    case AML_DeviceOp:
        DataType = ACPI_TYPE_Device;
        break;

    case AML_ThermalZoneOp:
        DataType = ACPI_TYPE_Thermal;
        break;

    case AML_MethodOp:
        DataType = ACPI_TYPE_Method;
        break;

    case AML_PowerResOp:
        DataType = ACPI_TYPE_Power;
        break;

    case AML_ProcessorOp:
        DataType = ACPI_TYPE_Processor;
        break;

    case AML_DefFieldOp:                            /* DefFieldOp */
        DataType = INTERNAL_TYPE_DefFieldDefn;
        break;

    case AML_IndexFieldOp:                          /* IndexFieldOp */
        DataType = INTERNAL_TYPE_IndexFieldDefn;
        break;

    case AML_BankFieldOp:                           /* BankFieldOp */
        DataType = INTERNAL_TYPE_BankFieldDefn;
        break;

    case AML_NAMEDFIELD:                            /* NO CASE IN ORIGINAL  */
        DataType = ACPI_TYPE_Any;
        break;

    case AML_NameOp:                                /* NameOp - special code in original */
    case AML_NAMEPATH:                    
        DataType = ACPI_TYPE_Any;
        break;

    case AML_AliasOp:
        DataType = INTERNAL_TYPE_Alias;
        break;

    case AML_MutexOp:
        DataType = ACPI_TYPE_Mutex;
        break;

    case AML_EventOp:
        DataType = ACPI_TYPE_Event;
        break;

    case AML_RegionOp:
        DataType = ACPI_TYPE_Region;
        break;


    default:
        DataType = ACPI_TYPE_Any;
        break;

    }

    return DataType;
}



