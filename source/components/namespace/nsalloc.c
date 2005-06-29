/*******************************************************************************
 *
 * Module Name: nsalloc - Namespace allocation and deletion utilities
 *              $Revision: 1.40 $
 *
 ******************************************************************************/

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


#define __NSALLOC_C__

#include "acpi.h"
#include "acnamesp.h"
#include "acinterp.h"


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nsalloc")



/*******************************************************************************
 *
 * FUNCTION:    AcpiNsCreateNamedObject
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

ACPI_NAMED_OBJECT *
AcpiNsCreateNamedObject (
    UINT32                  AcpiName)
{
    ACPI_NAMED_OBJECT       *NameDesc;

    FUNCTION_TRACE ("NsCreateNamedObject");


    NameDesc = AcpiCmCallocate (sizeof (ACPI_NAMED_OBJECT));
    if (!NameDesc)
    {
        return_PTR (NULL);
    }

    INCREMENT_NAME_TABLE_METRICS (sizeof (ACPI_NAMED_OBJECT));
    
    NameDesc->DataType       = ACPI_DESC_TYPE_NAMED;
    NameDesc->Name           = AcpiName;
    NameDesc->ReferenceCount = 1;

    return_PTR (NameDesc);
}



/*******************************************************************************
 *
 * FUNCTION:    AcpiNsDeleteNamedObject
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
AcpiNsDeleteNamedObject (
    ACPI_NAMED_OBJECT       *NameDesc)
{
    ACPI_NAMED_OBJECT       *ParentDesc;
    ACPI_NAMED_OBJECT       *PrevDesc;
    ACPI_NAMED_OBJECT       *NextDesc;


    FUNCTION_TRACE_PTR ("NsDeleteNamedObject", NameDesc);

    ParentDesc = AcpiNsGetParentObject (NameDesc);

    PrevDesc = NULL;
    NextDesc = ParentDesc->Child;

    while (NextDesc != NameDesc)
    {
        PrevDesc = NextDesc;
        NextDesc = PrevDesc->Peer;
    }

    if (PrevDesc)
    {
        PrevDesc->Peer = NextDesc->Peer;
        if (NextDesc->Flags & ANOBJ_END_OF_PEER_LIST)
        {
            PrevDesc->Flags |= ANOBJ_END_OF_PEER_LIST;
        }
    }
    else
    {
        ParentDesc->Child = NextDesc->Peer;
    }


    DECREMENT_NAME_TABLE_METRICS (sizeof (ACPI_NAMED_OBJECT));

    /*
     * Detach an object if there is one 
     */

    if (NameDesc->Object)
    {
        AcpiNsDetachObject (NameDesc);
    }

    AcpiCmFree (NameDesc);


    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsInstallNamedObject
 *
 * PARAMETERS:  WalkState       - Current state of the walk
 *              ParentDesc      - The parent of the new Named Object
 *              NameDesc        - The new Named Object to install
 *              Type            - ACPI object type of the new Named Object
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize a new entry within a namespace table.
 *
 ******************************************************************************/

void
AcpiNsInstallNamedObject (
    ACPI_WALK_STATE         *WalkState,
    ACPI_NAMED_OBJECT       *ParentDesc,    /* Parent */
    ACPI_NAMED_OBJECT       *NameDesc,      /* New Child*/
    OBJECT_TYPE_INTERNAL    Type)
{
    UINT16                  OwnerId = TABLE_ID_DSDT;
    ACPI_NAMED_OBJECT       *ChildDesc;


    FUNCTION_TRACE ("NsInstallNamedObject");


    /*
     * Get the owner ID from the Walk state
     * The owner ID is used to track table deletion and
     * deletion of objects created by methods
     */
    if (WalkState)
    {
        OwnerId = WalkState->OwnerId;
    }


    /* link the new entry into the parent and existing children */

    /* TBD: Could be first, last, or alphabetic */

    ChildDesc = ParentDesc->Child;
    if (!ChildDesc)
    {
        ParentDesc->Child = NameDesc;
    }

    else 
    {
        while (!(ChildDesc->Flags & ANOBJ_END_OF_PEER_LIST))
        {
            ChildDesc = ChildDesc->Peer;
        }

        ChildDesc->Peer = NameDesc;

        /* Clear end-of-list flag */

        ChildDesc->Flags &= ~ANOBJ_END_OF_PEER_LIST;
    }

    /* Init the new entry */

    NameDesc->OwnerId   = OwnerId;
    NameDesc->Flags     |= ANOBJ_END_OF_PEER_LIST;
    NameDesc->Peer      = ParentDesc;


    /*
     * If adding a name with unknown type, or having to
     * add the region in order to define fields in it, we
     * have a forward reference.
     */

    if ((ACPI_TYPE_ANY == Type) ||
        (INTERNAL_TYPE_DEF_FIELD_DEFN == Type) ||
        (INTERNAL_TYPE_BANK_FIELD_DEFN == Type))
    {
        /*
         * We don't want to abort here, however!
         * We will fill in the actual type when the
         * real definition is found later.
         */

        DEBUG_PRINT (ACPI_INFO,
            ("NsInstallNamedObject: [%4.4s] is a forward reference\n",
            &NameDesc->Name));

    }

    /*
     * The DefFieldDefn and BankFieldDefn cases are actually
     * looking up the Region in which the field will be defined
     */

    if ((INTERNAL_TYPE_DEF_FIELD_DEFN == Type) ||
        (INTERNAL_TYPE_BANK_FIELD_DEFN == Type))
    {
        Type = ACPI_TYPE_REGION;
    }

    /*
     * Scope, DefAny, and IndexFieldDefn are bogus "types" which do
     * not actually have anything to do with the type of the name
     * being looked up.  Save any other value of Type as the type of
     * the entry.
     */

    if ((Type != INTERNAL_TYPE_SCOPE) &&
        (Type != INTERNAL_TYPE_DEF_ANY) &&
        (Type != INTERNAL_TYPE_INDEX_FIELD_DEFN))
    {
        NameDesc->Type = (UINT8) Type;
    }

    DEBUG_PRINT (TRACE_NAMES,
        ("NsInstallNamedObject: %4.4s added to %p at %p\n",
        &NameDesc->Name, ParentDesc, NameDesc));

    /*
     * Increment the reference count(s) of all parents up to
     * the root!
     */

    while ((NameDesc = AcpiNsGetParentObject (NameDesc)) != NULL)
    {
        NameDesc->ReferenceCount++;
    }

    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsDeleteChildren
 *
 * PARAMETERS:  ParentDesc      - Delete this objects children
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete all children of the parent object. Deletes a
 *              "scope".
 *
 ******************************************************************************/

void
AcpiNsDeleteChildren (
    ACPI_NAMED_OBJECT       *ParentDesc)
{
    ACPI_NAMED_OBJECT       *ChildDesc;
    ACPI_NAMED_OBJECT       *NextDesc;
    UINT8                   Flags;


    FUNCTION_TRACE_PTR ("AcpiNsDeleteChildren", ParentDesc);


    if (!ParentDesc)
    {
        return_VOID;
    }

    /* If no children, all done! */

    ChildDesc = ParentDesc->Child;
    if (!ChildDesc)
    {
        return_VOID;
    }

    /*
     * Deallocate all children at this level
     */
    do
    {
        /* Get the things we need */

        NextDesc    = ChildDesc->Peer;
        Flags       = ChildDesc->Flags;

        /* Grandchildren should have all been deleted already */

        if (ChildDesc->Child)
        {
            DEBUG_PRINT (ACPI_ERROR, 
                ("NsDeleteChildren: Found a grandchild! P=%X C=%X\n",
                ParentDesc, ChildDesc));
        }

        /* Now we can free this child object */

        DECREMENT_NAME_TABLE_METRICS (sizeof (ACPI_NAMED_OBJECT));

        DEBUG_PRINT (ACPI_INFO,
            ("AcpiNsDeleteChildren: Object %p, Remaining %d\n", 
            ChildDesc, AcpiGbl_CurrentNamedObjectCount));

        /*
         * Detach an object if there is one 
         */

        if (ChildDesc->Object)
        {
            AcpiNsDetachObject (ChildDesc);
        }

        AcpiCmFree (ChildDesc);

        /* And move on to the next child in the list */

        ChildDesc = NextDesc;

    } while (!(Flags & ANOBJ_END_OF_PEER_LIST));


    /* Clear the parent's child pointer */

    ParentDesc->Child = NULL;

    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsDeleteNamespaceSubtree
 *
 * PARAMETERS:  None.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete a subtree of the namespace.  This includes all objects 
 *              stored within the subtree.  Scope tables are deleted also
 *
 ******************************************************************************/

ACPI_STATUS
AcpiNsDeleteNamespaceSubtree (
    ACPI_NAMED_OBJECT       *ParentDesc)
{
    ACPI_NAMED_OBJECT       *ChildDesc;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    UINT32                  Level;


    FUNCTION_TRACE ("NsDeleteNamespaceSubtree");


    if (!ParentDesc)
    {
        return_ACPI_STATUS (AE_OK);
    }


    ChildDesc   = 0;
    Level       = 1;

    /*
     * Traverse the tree of objects until we bubble back up
     * to where we started.
     */

    while (Level > 0)
    {
        /*
         * Get the next typed object in this scope.
         * Null returned if not found
         */

        ChildDesc = AcpiNsGetNextObject (ACPI_TYPE_ANY, ParentDesc,
                                            ChildDesc);
        if (ChildDesc)
        {
            /*
             * Found an object - delete the object within
             * the Value field
             */

            ObjDesc = AcpiNsGetAttachedObject (ChildDesc);
            if (ObjDesc)
            {
                AcpiNsDetachObject (ChildDesc);
                AcpiCmRemoveReference (ObjDesc);
            }


            /* Check if this object has any children */

            if (AcpiNsGetNextObject (ACPI_TYPE_ANY, ChildDesc, 0))
            {
                /*
                 * There is at least one child of this object,
                 * visit the object
                 */

                Level++;
                ParentDesc    = ChildDesc;
                ChildDesc     = 0;
            }
        }

        else
        {
            /*
             * No more children in this object.
             * We will move up to the grandparent.
             */
            Level--;

            /*
             * Now delete all of the children of this parent
             * all at the same time.
             */
            AcpiNsDeleteChildren (ParentDesc);

            /* New "last child" is this parent object */

            ChildDesc = ParentDesc;

            /* Now we can move up the tree to the grandparent */

            ParentDesc = AcpiNsGetParentObject (ParentDesc);
        }
    }


    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsRemoveReference
 *
 * PARAMETERS:  NameDesc           - Named object whose reference count is to be 
 *                                decremented
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Remove a Named Object reference.  Decrements the reference count
 *              of all parent Named Objects up to the root.  Any object along 
 *              the way that reaches zero references is freed.
 *
 ******************************************************************************/

void
AcpiNsRemoveReference (
    ACPI_NAMED_OBJECT       *NameDesc)
{
    ACPI_NAMED_OBJECT       *CurrentDesc;


    /*
     * Decrement the reference count(s) of this object and all
     * objects up to the root,  Delete anything with zero remaining references.
     */
    CurrentDesc = NameDesc;
    while (CurrentDesc)
    {
        /* Decrement the reference count on this object*/

        CurrentDesc->ReferenceCount--;

        /* Delete the object if no more references */

        if (!CurrentDesc->ReferenceCount)
        {
            /* Delete all children and delete the object */

            AcpiNsDeleteChildren (CurrentDesc);
            AcpiNsDeleteNamedObject (CurrentDesc);
        }

        /* Move up to parent */

        CurrentDesc = AcpiNsGetParentObject (CurrentDesc);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsDeleteNamespaceByOwner
 *
 * PARAMETERS:  None.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete entries within the namespace that are owned by a
 *              specific ID.  Used to delete entire ACPI tables.  All
 *              reference counts are updated.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiNsDeleteNamespaceByOwner (
    UINT16                  OwnerId)
{
    ACPI_NAMED_OBJECT       *ChildDesc;
    UINT32                  Level;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_NAMED_OBJECT       *ParentDesc;


    FUNCTION_TRACE ("NsDeleteNamespaceSubtree");


    ParentDesc  = AcpiGbl_RootObject;
    ChildDesc   = 0;
    Level       = 1;

    /*
     * Traverse the tree of objects until we bubble back up
     * to where we started.
     */

    while (Level > 0)
    {
        /*
         * Get the next typed object in this scope.
         * Null returned if not found
         */

        ChildDesc = AcpiNsGetNextObject (ACPI_TYPE_ANY, ParentDesc,
                                            ChildDesc);

        if (ChildDesc)
        {
            if (ChildDesc->OwnerId == OwnerId)
            {
                /*
                 * Found an object - delete the object within
                 * the Value field
                 */

                ObjDesc = AcpiNsGetAttachedObject (ChildDesc);
                if (ObjDesc)
                {
                    AcpiNsDetachObject (ChildDesc);
                    AcpiCmRemoveReference (ObjDesc);
                }
            }

            /* Check if this object has any children */

            if (AcpiNsGetNextObject (ACPI_TYPE_ANY, ChildDesc, 0))
            {
                /*
                 * There is at least one child of this object,
                 * visit the object
                 */

                Level++;
                ParentDesc    = ChildDesc;
                ChildDesc     = 0;
            }

            else if (ChildDesc->OwnerId == OwnerId)
            {
                AcpiNsRemoveReference (ChildDesc);
            }
        }

        else
        {
            /*
             * No more children in this object.  Move up to grandparent.
             */
            Level--;

            if (Level != 0)
            {
                if (ParentDesc->OwnerId == OwnerId)
                {
                    AcpiNsRemoveReference (ParentDesc);
                }
            }

            /* New "last child" is this parent object */

            ChildDesc = ParentDesc;

            /* Now we can move up the tree to the grandparent */

            ParentDesc = AcpiNsGetParentObject (ParentDesc);
        }
    }


    return_ACPI_STATUS (AE_OK);
}



