
/******************************************************************************
 * 
 * Module Name: istore - AML Interpreter object store support
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

#define __ISTORE_C__

#include <acpi.h>
#include <parser.h>
#include <dispatch.h>
#include <interp.h>
#include <amlcode.h>
#include <namesp.h>
#include <tables.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("istore");



/*****************************************************************************
 * 
 * FUNCTION:    AmlExecStore
 *
 * PARAMETERS:  *ValDesc            - Value to be stored
 *              *DestDesc           - Where to store it -- must be an (ACPI_HANDLE)
 *                                    or an ACPI_OBJECT_INTERNAL of type Reference;
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
    ACPI_OBJECT_INTERNAL    *ValDesc, 
    ACPI_OBJECT_INTERNAL    *DestDesc)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OBJECT_INTERNAL    *DeleteDestDesc = NULL;
    ACPI_OBJECT_INTERNAL    *TmpDesc;
    NAME_TABLE_ENTRY        *Entry = NULL;
    UINT8                   Value = 0;


    FUNCTION_TRACE ("AmlExecStore");

    DEBUG_PRINT (ACPI_INFO, ("entered AmlExecStore: Val=%p, Dest=%p\n", 
                    ValDesc, DestDesc));


    /* Validate parameters */

    if (!ValDesc || !DestDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore: Internal error - null pointer\n"));
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }

    /* Examine the datatype of the DestDesc */

    if (VALID_DESCRIPTOR_TYPE (DestDesc, DESC_TYPE_NTE))
    {
        /* Dest is an ACPI_HANDLE, create a new object */

        Entry = (NAME_TABLE_ENTRY *) DestDesc;
        DestDesc = CmCreateInternalObject (INTERNAL_TYPE_Reference);
        if (!DestDesc)
        {   
            /* Allocation failure  */
            
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        /* Build a new Reference wrapper around the handle */

        DestDesc->Reference.OpCode = AML_NameOp;
        DestDesc->Reference.Object = Entry;
    }

    else
    {
        /* DestDesc is not an ACPI_HANDLE  */

        DEBUG_PRINT (ACPI_INFO, ("AmlExecStore: Dest is object (not handle) - may be deleted!\n"));
    }

    /* Destination object must be of type Reference */

    if (DestDesc->Common.Type != INTERNAL_TYPE_Reference)
    {   
        /* Destination is not an Reference */

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore: Destination is not an Reference [%p]\n", DestDesc));

        DUMP_STACK_ENTRY (ValDesc);
        DUMP_STACK_ENTRY (DestDesc);
        DUMP_OPERANDS (&DestDesc, IMODE_Execute, "AmlExecStore", 2, "target not Reference");

        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    }

    /* Examine the Reference opcode */

    switch (DestDesc->Reference.OpCode)
    {

    case AML_NameOp:

        /*
         *  Storing into a Name
         */
        DeleteDestDesc = DestDesc;
        Status = AmlStoreObjectToNte (ValDesc, DestDesc->Reference.Object);

        break;  /* Case NameOp */


    case AML_IndexOp:

        DeleteDestDesc = DestDesc;
        
        /*
         * Actually, storing to a package is not so simple.  The source must be
         *  evaluated and converted to the type of the destination and then the
         *  source is copied into the destination - we can't just point to the
         *  source object.
         */
        if (DestDesc->Reference.TargetType == ACPI_TYPE_Package)
        {
            /* 
             * The object at *(DestDesc->Reference.Where) is the
             *  element within the package that is to be modified.
             */
            TmpDesc = *(DestDesc->Reference.Where);
            if (TmpDesc)
            {
                /*
                 * If the Destination element is a package, we will delete
                 *  that object and construct a new one.
                 *
                 * TBD: Should both the src and dest be required to be packages?
                 *       && (ValDesc->Common.Type == ACPI_TYPE_Package)
                 */
                if (TmpDesc->Common.Type == ACPI_TYPE_Package)
                {
                    /* Take away the reference for being part of a package and delete  */

                    CmRemoveReference (TmpDesc);
                    CmRemoveReference (TmpDesc);

                    TmpDesc = NULL;
                }
            }

            if (!TmpDesc)
            {
                /*
                 * If the TmpDesc is NULL, that means an uninitialized package
                 * has been used as a destination, therefore, we must create
                 * the destination element to match the type of the source element
                 * NOTE: ValDesc can be of any type.
                 */
                TmpDesc = CmCreateInternalObject (ValDesc->Common.Type);
                if (!TmpDesc)
                {
                    Status = AE_NO_MEMORY;
                    goto Cleanup;
                }

                /*
                 * If the source is a package, copy the source to the new dest
                 */
                if (ACPI_TYPE_Package == TmpDesc->Common.Type)
                {
                    Status = AmlBuildCopyInternalPackageObject (ValDesc, TmpDesc);
                    if (ACPI_FAILURE (Status))
                    {
                        CmRemoveReference (TmpDesc);
                        TmpDesc = NULL;
                        goto Cleanup;
                    }
                }

                /* 
                 * Install the new descriptor into the package and add a reference to the 
                 * newly created descriptor for now being part of the parent package 
                 */

                *(DestDesc->Reference.Where) = TmpDesc;
                CmAddReference (TmpDesc);   
            }

            if (ACPI_TYPE_Package != TmpDesc->Common.Type)
            {
                /* 
                 * The destination element is not a package, so we need to convert the contents of
                 * the source (ValDesc) and copy into the destination (TmpDesc)
                 */
                Status = AmlStoreObjectToObject(ValDesc, TmpDesc);
                if (ACPI_FAILURE (Status))
                {
                    /* 
                     * An error occurrered when copying the internal object
                     *  so delete the reference.
                     */
                    DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/Index: Unable to copy the internal object\n"));
                    Status = AE_AML_OPERAND_TYPE;
                }
            }

            break;
        }

        /*
         * Check that the destination is a Buffer Field type
         */
        if (DestDesc->Reference.TargetType != ACPI_TYPE_BufferField)
        {
            Status = AE_AML_OPERAND_TYPE;
            break;
        }
        
        /* 
         * Storing into a buffer at a location defined by an Index.
         * This is a little more complex than the package case.
         *
         * If value is not a Number, try to resolve it to one.
         */
        switch (ValDesc->Common.Type) 
        {
        /*
         * If the type is Integer, only the least significant
         *  8-bits are used
         */
        case ACPI_TYPE_Number:
            Value = (UINT8)ValDesc->Number.Value;
            break;

        /*
         * If the type is Buffer, the least significant
         *  8-bits are copied over (last element)
         */
        case ACPI_TYPE_Buffer:
            Value = *(ValDesc->Buffer.Pointer + ValDesc->Buffer.Length - 1);
            break;

        /*
         * If the type is String, the least significant
         *  8-bits are copied over (last element)
         */
        case ACPI_TYPE_String:
            Value = *(ValDesc->String.Pointer + ValDesc->String.Length - 1);
            break;

        /*
         * If value is not a Number, try to resolve it to one.
         */
        default:
            if ((ValDesc->Common.Type != ACPI_TYPE_Number) &&
               ((Status = AmlResolveToValue (&ValDesc)) != AE_OK))
            {
                DeleteDestDesc = DestDesc;
            }

            else if (ValDesc->Common.Type != ACPI_TYPE_Number)
            {
                DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore/Index: Index value must be Number, not %d\n",
                                ValDesc->Common.Type));

                DeleteDestDesc = DestDesc;
                Status = AE_AML_OPERAND_TYPE;
            }
            break;
        }

        /*
         * If we had an error, break out of this case statement.
         */
        if(AE_OK != Status)
        {
            break;
        }

        /* 
         * Delete descriptor that points to name,
         * and point to descriptor for name's value instead.
         */

        DeleteDestDesc = DestDesc;

        /*
         * Valid source value and destination reference pointer.
         *
         * ACPI Specification 1.0B section 15.2.3.4.2.13:
         * Destination should point to either a buffer or a package
         */

        /*
         *  Dereference the Buffer Field and set it equal to the ValDesc value
         */
        TmpDesc = DestDesc->Reference.Object;

        if (TmpDesc->Common.Type != ACPI_TYPE_Buffer)
        {
            Status = AE_AML_OPERAND_TYPE;
            break;
        }

        TmpDesc->Buffer.Pointer[DestDesc->Reference.Offset] = Value;

        DestDesc = TmpDesc;

        break;

    case AML_ZeroOp: 
    case AML_OneOp: 
    case AML_OnesOp:

        /* 
         * Storing to a constant is a no-op -- see spec sec 15.2.3.3.1.
         * Delete the result descriptor.
         */

        DeleteDestDesc = DestDesc;
        break;


    case AML_LocalOp:

        Status = DsMethodDataSetValue (MTH_TYPE_LOCAL, (DestDesc->Reference.Offset), ValDesc);
        DeleteDestDesc = DestDesc;
        break;


    case AML_ArgOp:

        Status = DsMethodDataSetValue (MTH_TYPE_ARG, (DestDesc->Reference.Offset), ValDesc);
        DeleteDestDesc = DestDesc;
        break;


    case AML_DebugOp:

        /* 
         * Storing to the Debug object causes the value stored to be
         * displayed and otherwise has no effect -- see sec. 15.2.3.3.3.
         */
        DEBUG_PRINT (ACPI_INFO, ("**** Write to Debug Object: ****: \n"));
        if (ValDesc->Common.Type == ACPI_TYPE_String)
        {
            DEBUG_PRINT (ACPI_INFO, ("%s\n", ValDesc->String.Pointer));
        }
        else
        {
            DUMP_STACK_ENTRY (ValDesc);
        }

        DeleteDestDesc = DestDesc;
        break;


    default:

        DEBUG_PRINT (ACPI_ERROR, ("AmlExecStore: Internal error - Unknown Reference subtype %02x\n",
                        DestDesc->Reference.OpCode));
        
        /* TBD:  use object dump routine !! */

        DUMP_BUFFER (DestDesc, sizeof (ACPI_OBJECT_INTERNAL));

        DeleteDestDesc = DestDesc;
        Status = AE_AML_INTERNAL;
    
    }   /* switch(DestDesc->Reference.OpCode) */




Cleanup:

    /* Cleanup and exit*/

    if (DeleteDestDesc)
    {
        CmRemoveReference (DeleteDestDesc);
    }

    return_ACPI_STATUS (Status);
}


