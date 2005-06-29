
/******************************************************************************
 * 
 * Module Name: psxmargs - control method arguments and local variables
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

#define __PSXMARGS_C__

#include <acpi.h>
#include <parser.h>
#include <interp.h>
#include <amlcode.h>
#include <namesp.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("psxmargs");


#define NAMEOF_LOCAL_NTE    "__L0"
#define NAMEOF_ARG_NTE      "__A0"

/*****************************************************************************
 * 
 * FUNCTION:    PsxIsMethodValue
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
PsxIsMethodValue (
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{
    FUNCTION_TRACE ("PsxIsMethodValue");


    /* For each active Method */
    
    /* TBD: may no longer be necessary */
    /* IF so, we must walk the list of active control methods */

    return_VALUE (FALSE);
}



/*****************************************************************************
 * 
 * FUNCTION:    PsxMthStackInit
 *
 * PARAMETERS:  *ObjDesc 
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize the data structures that hold the method's arguments
 *              and locals.  The data struct is an array of NTEs for each.
 *              This allows RefOf and DeRefOf to work properly for these special
 *              data types.
 *
 ****************************************************************************/

ACPI_STATUS
PsxMthStackInit (
    ACPI_WALK_STATE         *WalkState)
{
    UINT32                  i;


    FUNCTION_TRACE ("PsxMthStackInit");

    /*
     * WalkState fields are initialized to zero by the CmCallocate().
     *
     * An NTE is assigned to each argument and local so that RefOf() can return
     * a pointer to the NTE.
     */

    /* Init the method arguments */

    for (i = 0; i < MTH_NUM_ARGS; i++)
    {
        WalkState->Arguments[i].DataType        = DESC_TYPE_NTE;
        WalkState->Arguments[i].Type            = INTERNAL_TYPE_MethodArgument;
        WalkState->Arguments[i].Name            = *((UINT32 *) NAMEOF_ARG_NTE) | (i << 24);
    }

    /* Init the method locals */

    for (i = 0; i < MTH_NUM_LOCALS; i++)
    {
        WalkState->LocalVariables[i].DataType   = DESC_TYPE_NTE;
        WalkState->LocalVariables[i].Type       = INTERNAL_TYPE_MethodLocalVar;
        WalkState->LocalVariables[i].Name       = *((UINT32 *) NAMEOF_LOCAL_NTE) | (i << 24);
    }


    return_ACPI_STATUS (AE_OK);
}



/*****************************************************************************
 * 
 * FUNCTION:    PsxMthStackPush
 *
 * PARAMETERS:  None.
 *
 * RETURN:      Push the method stack.
 *
 ****************************************************************************/

ACPI_STATUS
PsxMthStackPush (
    ACPI_OBJECT_INTERNAL    **Params)
{
    FUNCTION_TRACE ("PsxMthStackPush");


    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 * 
 * FUNCTION:    PsxMthStackDeleteArgs
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Delete method locals and arguments.  Arguments are only
 *              deleted if this method was called from another method.
 *
 ****************************************************************************/

ACPI_STATUS
PsxMthStackDeleteArgs (
    ACPI_WALK_STATE         *WalkState)
{
    UINT32                  Index;
    ACPI_OBJECT_INTERNAL    *Object;


    FUNCTION_TRACE ("PsxMthStackDeleteArgs");


    for (Index = 0; Index < MTH_NUM_LOCALS; Index++)
    {
        Object = WalkState->LocalVariables[Index].Object;
        WalkState->LocalVariables[Index].Object = NULL;

        if (Object)

        {
            CmUpdateObjectReference (Object, REF_DECREMENT);   /* Removed from Stack */
            CmDeleteInternalObject (Object);
        }
    }

    for (Index = 0; Index < MTH_NUM_ARGS; Index++)
    {
        Object = WalkState->Arguments[Index].Object;
        WalkState->Arguments[Index].Object = NULL;

        if (Object)
        {
            CmUpdateObjectReference (Object, REF_DECREMENT);   /* Removed from Stack */
            if (Object->Common.ReferenceCount <= 1)
            {
                /* Delete the object since it has no owner  */

                CmDeleteInternalObject (Object);
            }
        }
    }

    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 * 
 * FUNCTION:    PsxMthStackInitArgs
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize arguments for a method
 *
 ****************************************************************************/

ACPI_STATUS
PsxMthStackInitArgs (
    ACPI_OBJECT_INTERNAL    **Params,
    UINT32                  MaxParamCount)
{
    ACPI_STATUS             Status;
    UINT32                  Mindex;
    UINT32                  Pindex;


    FUNCTION_TRACE_PTR ("PsxMthStackInitArgs", Params);


    if (!Params)
    {
        DEBUG_PRINT (TRACE_EXEC, ("PsxMthStackInitArgs: No param list passed to method\n"));
        return_ACPI_STATUS (AE_OK);
    }

    /* Copy passed parameters into the new method stack frame  */
        
    for (Pindex = Mindex = 0; (Mindex < MTH_NUM_ARGS) && (Pindex < MaxParamCount); Mindex++)
    {   
        if (Params[Pindex])   
        {
            /*
             * A valid parameter.
             * Set the current method argument to the Params[Pindex++] argument object descriptor   
             */
            Status = PsxMthStackSetValue (MTH_TYPE_ARG, Mindex, Params[Pindex]);
            if (ACPI_FAILURE (Status))
            {
                break;
            }

            Pindex++;
        }

        else
        {
            break;
        }
    }

    DEBUG_PRINT (TRACE_EXEC, ("PsxMthStackInitArgs: %d args passed to method\n", Pindex));
    return_ACPI_STATUS (AE_OK);
}



/*****************************************************************************
 * 
 * FUNCTION:    PsxMthStackGetEntry
 *
 * PARAMETERS:  Type                - Either MTH_TYPE_LOCAL or MTH_TYPE_ARG
 *              Index               - Which localVar or argument to get
 *              Entry               - Pointer to where a pointer to the stack
 *                                    entry is returned.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get the address of the stack entry given by Type:Index
 *
 ****************************************************************************/

ACPI_STATUS
PsxMthStackGetEntry (
    UINT32                  Type,
    UINT32                  Index,
    ACPI_OBJECT_INTERNAL    ***Entry)
{
    ACPI_WALK_STATE         *WalkState;


    FUNCTION_TRACE_U32 ("PsxMthStackGetEntry", Index);


    WalkState = PsGetCurrentWalkState (Gbl_CurrentWalkList);

    /* 
     * Get the requested object.
     * The stack "Type" is either a LocalVariable or an Argument 
     */

    switch (Type)
    {

    case MTH_TYPE_LOCAL:

        if (Index > MTH_MAX_LOCAL)
        {
            DEBUG_PRINT (ACPI_ERROR, ("PsxMthStackGetEntry: LocalVar index %d is invalid (max %d)\n",
                                    Index, MTH_MAX_LOCAL));
            return_ACPI_STATUS (AE_BAD_PARAMETER);
        }
        
        *Entry = (ACPI_OBJECT_INTERNAL **) &WalkState->LocalVariables[Index].Object;
        break;


    case MTH_TYPE_ARG:

        if (Index > MTH_MAX_ARG)
        {
            DEBUG_PRINT (ACPI_ERROR, ("PsxMthStackGetEntry: Argument index %d is invalid (max %d)\n",
                                    Index, MTH_MAX_ARG));
            return_ACPI_STATUS (AE_BAD_PARAMETER);
        }
        
        *Entry = (ACPI_OBJECT_INTERNAL **) &WalkState->Arguments[Index].Object;
        break;


    default:
        DEBUG_PRINT (ACPI_ERROR, ("PsxMthStackGetEntry: Stack type %d is invalid\n",
                                Type));
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 * 
 * FUNCTION:    PsxMthStackSetEntry
 *
 * PARAMETERS:  Type                - Either MTH_TYPE_LOCAL or MTH_TYPE_ARG
 *              Index               - Which localVar or argument to get
 *              Object              - Object to be inserted into the stack entry
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Insert an object onto the method stack at entry Type:Index.
 *
 ****************************************************************************/

ACPI_STATUS
PsxMthStackSetEntry (
    UINT32                  Type,
    UINT32                  Index,
    ACPI_OBJECT_INTERNAL    *Object)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    **Entry;


    FUNCTION_TRACE ("PsxMthStackSetEntry");


    /* Get a pointer to the stack entry to set */

    Status = PsxMthStackGetEntry (Type, Index, &Entry);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Increment ref count so object can't be deleted while installed */

    CmUpdateObjectReference (Object, REF_INCREMENT);
    
    /* Install the object into the stack entry */

    *Entry = Object;

    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 * 
 * FUNCTION:    PsxMthStackGetType
 *
 * PARAMETERS:  Type                - Either MTH_TYPE_LOCAL or MTH_TYPE_ARG
 *              Index               - Which localVar or argument whose type to get
 *
 * RETURN:      Data type of selected Arg or Local
 *              Used only in ExecMonadic2()/TypeOp.
 *
 ****************************************************************************/

ACPI_OBJECT_TYPE
PsxMthStackGetType (
    UINT32                  Type,
    UINT32                  Index)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    **Entry;
    ACPI_OBJECT_INTERNAL    *Object;


    FUNCTION_TRACE ("PsxMthStackGetType");


    /* Get a pointer to the requested stack entry */

    Status = PsxMthStackGetEntry (Type, Index, &Entry);
    if (ACPI_FAILURE (Status))
    {
        return_VALUE ((ACPI_OBJECT_TYPE) -1);
    }

    /* Get the object from the method stack */

    Object = *Entry;

    /* Get the object type */

    if (!Object)
    {
        return_VALUE (ACPI_TYPE_Any); /* Any == 0 => "uninitialized" -- see spec 15.2.3.5.2.28 */
    }

    return_VALUE (Object->Common.Type);
}


/*****************************************************************************
 * 
 * FUNCTION:    PsxMthStackGetNte
 *
 * PARAMETERS:  Type                - Either MTH_TYPE_LOCAL or MTH_TYPE_ARG
 *              Index               - Which localVar or argument whose type to get
 *
 * RETURN:      Get the NTE associated with a local or arg.
 *
 ****************************************************************************/

NAME_TABLE_ENTRY *
PsxMthStackGetNte (
    UINT32                  Type,
    UINT32                  Index)
{
    NAME_TABLE_ENTRY        *Entry = NULL;
    ACPI_WALK_STATE         *WalkState;


    FUNCTION_TRACE ("PsxMthStackGetNte");


    WalkState = PsGetCurrentWalkState (Gbl_CurrentWalkList);


    switch (Type)
    {

    case MTH_TYPE_LOCAL:

        if (Index > MTH_MAX_LOCAL)
        {
            DEBUG_PRINT (ACPI_ERROR, ("PsxMthStackGetEntry: LocalVar index %d is invalid (max %d)\n",
                                    Index, MTH_MAX_LOCAL));
            return_VALUE (Entry);
        }
        
        Entry =  &WalkState->LocalVariables[Index];
        break;


    case MTH_TYPE_ARG:

        if (Index > MTH_MAX_ARG)
        {
            DEBUG_PRINT (ACPI_ERROR, ("PsxMthStackGetEntry: Argument index %d is invalid (max %d)\n",
                                    Index, MTH_MAX_ARG));
            return_VALUE (Entry);
        }
        
        Entry = &WalkState->Arguments[Index];
        break;


    default:
        DEBUG_PRINT (ACPI_ERROR, ("PsxMthStackGetEntry: Stack type %d is invalid\n",
                                Type));
        break;
    }


    return_VALUE (Entry);
}


/*****************************************************************************
 * 
 * FUNCTION:    PsxMthStackGetValue
 *
 * PARAMETERS:  Type                - Either MTH_TYPE_LOCAL or MTH_TYPE_ARG
 *              Index               - Which localVar or argument to get
 *              *DestDesc            - Descriptor into which selected Arg
 *                                    or Local value should be copied
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve value of selected Arg or Local from the method frame
 *              at the current top of the method stack.
 *              Used only in AmlGetRvalue().
 *
 ****************************************************************************/

ACPI_STATUS
PsxMthStackGetValue (
    UINT32                  Type,
    UINT32                  Index, 
    ACPI_OBJECT_INTERNAL    **DestDesc)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    **Entry;
    ACPI_OBJECT_INTERNAL    *Object;


    FUNCTION_TRACE ("PsxMthStackGetValue");


    /* Validate the object descriptor */

    if (!DestDesc)
    {
        DEBUG_PRINT (ACPI_ERROR, ("PsxMthStackGetValue: NULL object descriptor pointer\n"));
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }
    

    /* Get a pointer to the requested method stack entry */

    Status = PsxMthStackGetEntry (Type, Index, &Entry);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Get the object from the method stack */

    Object = *Entry;


    /* Examine the returned object, it must be valid. */

    if (!Object)
    {
        /* 
         * Index points to uninitialized object stack value.  This means
         * that either 1) The expected argument was not passed to the method,
         * or 2) A local variable was referenced by the method (via the ASL)
         * before it was initialized.  Either case is an error.
         */ 

        switch (Type)
        {
        case MTH_TYPE_ARG:
            DEBUG_PRINT (ACPI_ERROR, ("PsxMthStackGetValue: Uninitialized Arg[%d] at entry %X\n",
                            Index, Entry));
            break;

        case MTH_TYPE_LOCAL:
            DEBUG_PRINT (ACPI_ERROR, ("PsxMthStackGetValue: Uninitialized Local[%d] at entry %X\n",
                            Index, Entry));
            break;
        }

        return_ACPI_STATUS (AE_AML_ERROR);
    }


    /* 
     * Index points to initialized and valid object stack value.
     * Return an additional reference to the object
     */

    *DestDesc = Object;
    CmUpdateObjectReference (Object, REF_INCREMENT);

    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 * 
 * FUNCTION:    PsxMthStackDeleteValue
 *
 * PARAMETERS:  Type                - Either MTH_TYPE_LOCAL or MTH_TYPE_ARG
 *              Index               - Which localVar or argument to delete
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Delete the entry at Type:Index on the method stack.  Inserts
 *              a null into the stack slot after the object is deleted.
 *
 ****************************************************************************/

ACPI_STATUS
PsxMthStackDeleteValue (
    UINT32                  Type,
    UINT32                  Index) 
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    **Entry;
    ACPI_OBJECT_INTERNAL    *Object;


    FUNCTION_TRACE ("PsxMthStackDeleteValue");


    /* Get a pointer to the requested method stack entry */

    Status = PsxMthStackGetEntry (Type, Index, &Entry);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Get the current entry in this slot on the method stack */

    Object = *Entry;

    /* Always clear the entry */

    *Entry = NULL;

    /* 
     * Undefine the Arg or Local by setting its descriptor pointer to NULL.
     * If it is currently defined, delete the old descriptor first.
     *
     * Locals/Args can contain both ACPI_OBJECT_INTERNALs and NAME_TABLE_ENTRYs
     */
    if ((Object) &&
        (VALID_DESCRIPTOR_TYPE (Object, DESC_TYPE_ACPI_OBJ)))
    {
        /*
         * There is a valid object in this slot, go ahead and delete
         * it before clearing the entry.
         */

        if (ACPI_TYPE_Buffer == Object->Common.Type)
        {
            /* 
             * Ensure the about-to-be-deleted Buffer's sequence number
             * will no longer match any FieldUnits defined within it,
             * by inverting its most-significant bit.
             *
             * TBD: Is this still necessary??
             */
            Object->Buffer.Sequence ^= 0x80000000;
        }


        /* 
         * Decrement the reference count by one to balance the increment when the 
         * object was put on the stack.  Then we can attempt to delete it.
         */

        CmUpdateObjectReference (Object, REF_DECREMENT);
        CmDeleteInternalObject (Object);
    }


    return_ACPI_STATUS (AE_OK);
}


/*****************************************************************************
 * 
 * FUNCTION:    PsxMthStackSetValue
 *
 * PARAMETERS:  Type                - Either MTH_TYPE_LOCAL or MTH_TYPE_ARG
 *              Index               - Which localVar or argument to set
 *              *SrcDesc            - Value to be stored
 *              *DestDesc           - Descriptor into which *SrcDesc
 *                                    can be copied, or NULL if one must
 *                                    be allocated for the purpose.  If
 *                                    provided, this descriptor will be
 *                                    used for the new value.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store a value in an Arg or Local.  The SrcDesc is installed
 *              as the new value for the Arg or Local and the reference count
 *              is incremented.
 *
 ****************************************************************************/

ACPI_STATUS
PsxMthStackSetValue (
    UINT32                  Type,
    UINT32                  Index, 
    ACPI_OBJECT_INTERNAL    *SrcDesc) 
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_INTERNAL    **Entry;


    FUNCTION_TRACE ("PsxMthStackSetValue");
    DEBUG_PRINT (TRACE_EXEC, ("PsxMthStackSetValue: Type=%d Idx=%d Obj=%p\n",
                    Type, Index, SrcDesc));


    /* Parameter validation */

    if (!SrcDesc)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /* Get a pointer to the requested method stack entry */

    Status = PsxMthStackGetEntry (Type, Index, &Entry);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }

    if (*Entry == SrcDesc)
    {
        DEBUG_PRINT (TRACE_EXEC, ("PsxMthStackSetValue: Obj=%p already installed!\n",
                        SrcDesc));
        goto Cleanup;
    }


    /*
     * If there is an object already in this slot, we either have to delete it, or if
     * this is an argument and there is an object reference stored there, we have to do
     * an indirect store!
     */

    if (*Entry)
    {
        /*
         * Check for an indirect store if an argument contains an object reference (stored as an NTE).
         * We don't allow this automatic dereferencing for locals, since a store to a local should overwrite
         * anything there, including an object reference.
         *
         * If both Arg0 and Local0 contain RefOf (Local4):
         *
         * Store (1, Arg0)                  - Causes indirect store to local4
         * Store (1, Local0)                - Stores 1 in local0, overwriting the reference to local4
         * Store (1, DeRefof (Local0))      - Causes indirect store to local4
         *
         * Weird, but true.
         */

        if ((Type == MTH_TYPE_ARG) &&
            (VALID_DESCRIPTOR_TYPE (*Entry, DESC_TYPE_NTE)))
        {
            DEBUG_PRINT (TRACE_EXEC, ("PsxMthStackSetValue: Arg (%p) is an ObjRef(NTE), storing in %p\n",
                            SrcDesc, *Entry));

            /* Detach an existing object from the NTE */

            NsDetachObject (*Entry);

            /* Store this object into the NTE (do the indirect store) */

            Status = NsAttachObject (*Entry, SrcDesc, SrcDesc->Common.Type);
            return_ACPI_STATUS (Status);
        }


        /* Otherwise, just delete the existing object before storing the new one */

        PsxMthStackDeleteValue (Type, Index);
    }


    /* 
     * Install the ObjStack descriptor (*SrcDesc) into the descriptor for the
     * Arg or Local.
     * Install the new object in the stack entry
     * (increments the object reference count by one)
     */

    Status = PsxMthStackSetEntry (Type, Index, SrcDesc);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }

    /* Normal exit */

    return_ACPI_STATUS (AE_OK);


    /* Error exit */

Cleanup:

    return_ACPI_STATUS (Status);
}

