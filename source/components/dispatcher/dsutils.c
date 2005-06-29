
/******************************************************************************
 * 
 * Module Name: psxutils - Parser/Interpreter interface utilities
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

#define __PSXUTILS_C__

#include <acpi.h>
#include <amlcode.h>
#include <parser.h>
#include <interpreter.h>
#include <namespace.h>

#define _COMPONENT          PARSER
        MODULE_NAME         ("psxutils");



/*****************************************************************************
 *
 * FUNCTION:    PsxInitObjectFromOp
 *
 * PARAMETERS:  Op              - Parser op used to init the internal object
 *              Opcode          - AML opcode associated with the object
 *              ObjDesc         - Namespace object to be initialized
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize a namespace object from a parser Op and its 
 *              associated arguments.  The namespace object is a more compact
 *              representation of the Op and its arguments.
 *
 ****************************************************************************/

ACPI_STATUS
PsxInitObjectFromOp (
    ACPI_GENERIC_OP         *Op,
    UINT32                  Opcode,
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{
    ACPI_GENERIC_OP         *Arg;
    ACPI_BYTELIST_OP        *ByteList;


    switch (ObjDesc->Common.Type)
    {
    case ACPI_TYPE_Buffer:

        /* First arg is the buffer size */

        Arg = Op->Value.Arg;
        ObjDesc->Buffer.Length = Arg->Value.Size;

        /* Allocate the buffer */

        ObjDesc->Buffer.Pointer = CmCallocate (Arg->Value.Size);
        if (!ObjDesc->Buffer.Pointer)
        {
            return AE_NO_MEMORY;
        }

        /* Second arg is the buffer data (optional) */
        /* TBD: What about string initializer? */

        ByteList = (ACPI_BYTELIST_OP *) Arg->Next;
        if (ByteList)
        {
            if (ByteList->Opcode != AML_BYTELIST)
            {
                DEBUG_PRINT (ACPI_ERROR, ("InitObject: Expecting bytelist, got: %x\n",
                                ByteList));
                return AE_TYPE;
            }

            MEMCPY (ObjDesc->Buffer.Pointer, ByteList->Data, ObjDesc->Buffer.Length);
        }

        break;

    case ACPI_TYPE_Number:
        ObjDesc->Number.Value = Op->Value.Integer;
        break;

    case ACPI_TYPE_String:
        ObjDesc->String.Pointer = Op->Value.String;
        ObjDesc->String.Length = STRLEN (Op->Value.String);
        break;

    case ACPI_TYPE_Method:
        break;

    case INTERNAL_TYPE_Lvalue:
        ObjDesc->Lvalue.OpCode = Opcode;

        /* 
         * TBD:
         * Special case for debugOp, this could be removed now that there is room for a 2-byte opcode 
         * in the Lvalue object
         */
        if (Opcode == AML_DebugOp)
        {
            ObjDesc->Lvalue.OpCode = Debug1;
        }
        break;

    default:

        DEBUG_PRINT (ACPI_ERROR, ("InitObject: Unimplemented data type: %x\n",
                        ObjDesc->Common.Type));

        break;
    }

    return AE_OK;
}


/*****************************************************************************
 *
 * FUNCTION:    PsxStoreOrDeleteResult
 *
 * PARAMETERS:  
 *
 * RETURN:      Status
 *
 * DESCRIPTION: 
 *
 ****************************************************************************/

void
PsxSaveOrDeleteResult (
    ACPI_GENERIC_OP         *Op)
{
    ACPI_OP_INFO            *ParentInfo;


    if (!Op)
    {
        DEBUG_PRINT (ACPI_ERROR, ("PsxStoreOrDeleteResult: Null Op=%X\n",
                        Op));
        return;
    }

    if (!Op->Parent)
    {
        /* If there is no parent, the result can't possibly be used! */
        /* (An executing method typically has no parent, since each method is parsed separately */

        if (Op->ResultObj)
        {
            CmDeleteInternalObject (Op->ResultObj);
            Op->ResultObj = NULL;
        }

        return;
    }


    /*
     * Get info on the parent.  The root Op is AML_Scope
     */

    ParentInfo = PsGetOpcodeInfo (Op->Parent->Opcode);
    if (!ParentInfo)
    {
        DEBUG_PRINT (ACPI_ERROR, ("PsxStoreOrDeleteResult: Unknown parent opcode. Op=%X\n",
                        Op));

        return;
    }


    /*
     * Decide what to do with the result based on the parent.  If the parent opcode
     * will not use the result, delete the object.  Otherwise leave it as is, it will
     * be deleted when it is used as an operand later.
     */
    switch (ParentInfo->Type)
    {

    /*
     * In these cases, the parent will never use the return object, so delete it 
     * here and now.
     */
    case OPTYPE_CONTROL:        /* IF, ELSE, WHILE only */
    case OPTYPE_NAMED_OBJECT:   /* Scope, method, etc. */

        if (Op->ResultObj)
        {
            CmDeleteInternalObject (Op->ResultObj);
            Op->ResultObj = NULL;
        }
        break;

    /* 
     * In all other cases. the parent will actually use the return object, so keep it.
     */
    default:
        break;
    }

    return;
}


/*****************************************************************************
 *
 * FUNCTION:    PsxCreateOperands
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
PsxCreateOperands (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *FirstArg)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_GENERIC_OP         *Arg;
    ACPI_OBJECT_TYPE        DataType; 
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    char                    *NameString;
    UINT32                  NameLength;
    UINT32                  Opcode;
    UINT32                  Flags;

    

    FUNCTION_TRACE_PTR ("PsxCreateOperands", FirstArg);

    Arg = FirstArg;


    /* For all arguments in the list... */

    while (Arg)
    {

        /* A valid name must be looked up in the namespace */

        if ((Arg->Opcode == AML_NAMEPATH) &&
            (Arg->Value.String))
        {
            DEBUG_PRINT (TRACE_PARSE, ("PsxCreateOperands: Getting a name: Arg=%p\n", Arg));


            /* Get the entire name string from the AML stream */

            Status = AmlGetNameString (ACPI_TYPE_Any, Arg->Value.String, &NameString, &NameLength);
            if (ACPI_FAILURE (Status))
            {
                goto Cleanup;
            }

            /* All prefixes have been handled, and the name is in NameString */

            Status = NsLookup (Gbl_CurrentScope->Scope, NameString, ACPI_TYPE_Any, IMODE_Execute, 
                                        NS_SEARCH_PARENT, (NAME_TABLE_ENTRY **) &ObjDesc);

            PsxObjStackPush (ObjDesc, WalkState);

            /* Returned object is already on object stack, we are done! */

            CmFree (NameString);

            /* Check status from the lookup */

            if (ACPI_FAILURE (Status))
            {
                goto Cleanup;
            }
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

                DEBUG_PRINT (TRACE_PARSE, ("PsxCreateOperands: Null namepath: Arg=%p\n", Arg));

                /* TBD: anything else needed for the zero op lvalue? */
            }

            else
            {
                Opcode = Arg->Opcode;
            }


            /* Get the data type of the argument */

            DataType = PsxMapOpcodeToDataType (Opcode, &Flags);
            if (DataType == INTERNAL_TYPE_Invalid)
            {
                Status = AE_NOT_IMPLEMENTED;
                goto Cleanup;
            }

            if (Flags & OP_HAS_RETURN_VALUE)
            {
                DEBUG_PRINT (TRACE_PARSE, ("PsxCreateOperands: Argument computed earlier! \n"));

                /* 
                 * Use value that was already previously returned by the evaluation of this argument
                 */

                ObjDesc = Arg->ResultObj;
                if (!ObjDesc)
                {
                    DEBUG_PRINT (ACPI_ERROR, ("PsxCreateOperands: But result obj is null! 1stArg=%X\n", FirstArg));
                    Status = AE_AML_ERROR;
                    goto Cleanup;
                }

                PsxObjStackPush (ObjDesc, WalkState);
            }

            else
            {
                /* Create an ACPI_INTERNAL_OBJECT for the argument */

                ObjDesc = CmCreateInternalObject (DataType);
                if (!ObjDesc)
                {
                    Status = AE_NO_MEMORY;
                    goto Cleanup;
                }

                /* Initialize the new object */

                Status = PsxInitObjectFromOp (Arg, Opcode, ObjDesc);
                if (ACPI_FAILURE (Status))
                {
                    CmFree (ObjDesc);
                    goto Cleanup;
                }

                /* Put the operand object on the object stack */

                PsxObjStackPush (ObjDesc, WalkState);
            }
        }


        /* Move on to next argument, if any */

        DEBUG_PRINT (TRACE_PARSE, ("PsxCreateOperands: %p done, Param=%X Arg1=%p\n", 
                                Arg, ObjDesc, FirstArg));
        Arg = Arg->Next;
    }


    return_ACPI_STATUS (Status);


Cleanup:

    DEBUG_PRINT (ACPI_ERROR, ("PsxCreateOperands: Error while creating! Status=%4.4X\n", Status));
    return_ACPI_STATUS (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    PsxMapOpcodeToDataType
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
PsxMapOpcodeToDataType (
    UINT32                  Opcode,
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

    switch (OpInfo->Type)
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

        /* TBD: Might not be correct */

        case AML_NAMEPATH:
            DataType = ACPI_TYPE_String;
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

        DataType = PsxMapNamedOpcodeToDataType (Opcode);

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
 * FUNCTION:    PsxMapNamedOpcodeToDataType
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
PsxMapNamedOpcodeToDataType (
    UINT32                  Opcode)
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

    case AML_DefFieldOp:                             /* DefFieldOp */
        DataType = INTERNAL_TYPE_DefFieldDefn;
        break;

    case AML_IndexFieldOp:                        /* IndexFieldOp */
        DataType = INTERNAL_TYPE_IndexFieldDefn;
        break;

    case AML_BankFieldOp:                         /* BankFieldOp */
        DataType = INTERNAL_TYPE_BankFieldDefn;
        break;

    case AML_NAMEDFIELD:                        /* NO CASE IN ORIGINAL  */
        DataType = ACPI_TYPE_Any;
        break;

    case AML_NameOp:                              /* NameOp - special code in original */
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



