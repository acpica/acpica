
/******************************************************************************
 * 
 * Module Name: nsalloc - Namespace allocation and deletion utilities
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


#define __NSALLOC_C__

#include "acpi.h"
#include "namesp.h"
#include "interp.h"


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nsalloc");



/****************************************************************************
 *
 * FUNCTION:    AcpiNsAllocateNameTable
 *
 * PARAMETERS:  NteCount            - Count of NTEs to allocate
 *
 * RETURN:      The address of the first nte in the array, or NULL
 *
 * DESCRIPTION: Allocate an array of nte, including prepended link space
 *              Array is set to all zeros via AcpiOsdCallcate().
 *
 ***************************************************************************/

NAME_TABLE_ENTRY *
AcpiNsAllocateNameTable (
    INT32                   NteCount)
{
    NAME_TABLE_ENTRY        *NameTable = NULL;
    ACPI_SIZE               AllocSize;


    FUNCTION_TRACE ("NsAllocateNameTable");


    AllocSize = (ACPI_SIZE) NteCount * sizeof (NAME_TABLE_ENTRY);

    
    /* Allow room for link to appendage */
    
    AllocSize += sizeof (NAME_TABLE_ENTRY *);

  
    NameTable = AcpiCmCallocate (AllocSize);
    if (NameTable)
    {
        /* Move past the appendage pointer */
    
        NameTable = (NAME_TABLE_ENTRY *) (((UINT8 *) NameTable) + 
                        sizeof (NAME_TABLE_ENTRY *));
    }

    DEBUG_PRINT (TRACE_EXEC, ("NsAllocateNameTable: NameTable=%p\n", NameTable));

    return_PTR (NameTable);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsDeleteNamespaceSubtree
 *
 * PARAMETERS:  None.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete a subtree of the namespace.  This includes all objects stored
 *              within the subtree.  Scope tables are deleted also
 *
 ***************************************************************************/

ACPI_STATUS
AcpiNsDeleteNamespaceSubtree (
    NAME_TABLE_ENTRY        *ParentHandle)
{
    NAME_TABLE_ENTRY        *ChildHandle;
    UINT32                  Level;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    FUNCTION_TRACE ("NsDeleteNamespaceSubtree");



    ChildHandle     = 0;
    Level           = 1;

    /* 
     * Traverse the tree of objects until we bubble back up 
     * to where we started.
     */

    while (Level > 0)
    {
        /* Get the next typed object in this scope.  Null returned if not found */

        ChildHandle = AcpiNsGetNextObject (ACPI_TYPE_ANY, ParentHandle, ChildHandle);
        if (ChildHandle)
        {
            /* Found an object - delete the object within the Value field */

            ObjDesc = AcpiNsGetAttachedObject (ChildHandle);
            if (ObjDesc)
            {
                AcpiNsDetachObject (ChildHandle);
                AcpiCmRemoveReference (ObjDesc);
            }


            /* Clear the NTE in case this scope is reused (e.g., a control method scope) */

            ChildHandle->Type = ACPI_TYPE_ANY;
            ChildHandle->Name = 0;

            /* Check if this object has any children */

            if (AcpiNsGetNextObject (ACPI_TYPE_ANY, ChildHandle, 0))
            {
                /* There is at least one child of this object, visit the object */

                Level++;
                ParentHandle    = ChildHandle;
                ChildHandle     = 0;
            }

            else
            {
                /* There may be a name table even if there are no children */

                AcpiNsDeleteScope (((NAME_TABLE_ENTRY *) ChildHandle)->Scope);
                ((NAME_TABLE_ENTRY *) ChildHandle)->Scope = NULL;

            }
        }

        else
        {
            /* 
             * No more children in this object.  
             * We will move up to the grandparent.
             */
            Level--;

            /* Delete the scope (Name Table) associated with the parent object */
            /* Don't delete the top level scope, this allows the dynamic deletion of
             * objects created underneath control methods!
             */

            if (Level != 0)
            {
                AcpiNsDeleteScope (((NAME_TABLE_ENTRY *) ParentHandle)->Scope);
                ((NAME_TABLE_ENTRY *) ParentHandle)->Scope = NULL;
            }

            /* New "last child" is this parent object */

            ChildHandle = ParentHandle;

            /* Now we can move up the tree to the grandparent */

            ParentHandle = ParentHandle->ParentEntry;
        }
    }


    return_ACPI_STATUS (AE_OK); 
}




/****************************************************************************
 *
 * FUNCTION:    AcpiNsRemoveReference
 *
 * PARAMETERS:  Entry           - NTE whose reference count is to be decremented
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Remove an NTE reference.  Decrements the reference count of
 *              all parent NTEs up to the root.  Any NTE along the way that
 *              reaches zero references is freed.
 *
 ***************************************************************************/

void
AcpiNsRemoveReference (
    NAME_TABLE_ENTRY        *Entry)
{
    NAME_TABLE_ENTRY        *ThisEntry;


    /* There may be a name table even if there are no children */

    AcpiNsDeleteScope (Entry->Scope);
    Entry->Scope = NULL;


    /* 
     * Decrement the reference count(s) of all parents up to the root,
     * And delete anything with zero remaining references.
     */
    ThisEntry = Entry;
    while (ThisEntry)
    {
        /* Decrement the reference */

        ThisEntry->ReferenceCount--;

        /* Delete entry if no more references */

        if (!ThisEntry->ReferenceCount)
        {
            /* Delete the scope if present */

            if (ThisEntry->Scope)
            {
                AcpiNsDeleteScope (ThisEntry->Scope);
                ThisEntry->Scope = NULL;
            }

            /* Mark the entry free  (This doesn't deallocate anything) */

            AcpiNsFreeTableEntry (ThisEntry);

        }

        /* Move up to parent */

        ThisEntry = ThisEntry->ParentEntry;
    }
}



/****************************************************************************
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
 ***************************************************************************/

ACPI_STATUS
AcpiNsDeleteNamespaceByOwner (
    UINT16                  OwnerId)
{
    NAME_TABLE_ENTRY        *ChildHandle;
    UINT32                  Level;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    NAME_TABLE_ENTRY        *ParentHandle;


    FUNCTION_TRACE ("NsDeleteNamespaceSubtree");


    ParentHandle    = Acpi_GblRootObject;
    ChildHandle     = 0;
    Level           = 1;

    /* 
     * Traverse the tree of objects until we bubble back up 
     * to where we started.
     */

    while (Level > 0)
    {
        /* Get the next typed object in this scope.  Null returned if not found */

        ChildHandle = AcpiNsGetNextObject (ACPI_TYPE_ANY, ParentHandle, ChildHandle);
        if (ChildHandle)
        {
            if (ChildHandle->OwnerId == OwnerId)
            {
                /* Found an object - delete the object within the Value field */

                ObjDesc = AcpiNsGetAttachedObject (ChildHandle);
                if (ObjDesc)
                {
                    AcpiNsDetachObject (ChildHandle);
                    AcpiCmRemoveReference (ObjDesc);
                }
            }

            /* Check if this object has any children */

            if (AcpiNsGetNextObject (ACPI_TYPE_ANY, ChildHandle, 0))
            {
                /* There is at least one child of this object, visit the object */

                Level++;
                ParentHandle    = ChildHandle;
                ChildHandle     = 0;
            }

            else if (ChildHandle->OwnerId == OwnerId)
            {
                AcpiNsRemoveReference (ChildHandle);
            }
        }

        else
        {
            /* 
             * No more children in this object.  
             * We will move up to the grandparent.
             */
            Level--;

            /* Delete the scope (Name Table) associated with the parent object */
            /* Don't delete the top level scope, this allows the dynamic deletion of
             * objects created underneath control methods!
             */

            if (Level != 0)
            {
                if (ParentHandle->OwnerId == OwnerId)
                {
                    AcpiNsRemoveReference (ParentHandle);
                }
            }


            /* New "last child" is this parent object */

            ChildHandle = ParentHandle;

            /* Now we can move up the tree to the grandparent */

            ParentHandle = ParentHandle->ParentEntry;
        }
    }


    return_ACPI_STATUS (AE_OK); 
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsDeleteScope
 *
 * PARAMETERS:  Scope           - A handle to the scope to be deleted
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete a namespace scope, which is a Name Table with zero or
 *              more appendages.  The table and all appendages are deleted.
 *
 ***************************************************************************/

void
AcpiNsDeleteScope (
    ACPI_HANDLE             Scope)
{
    NAME_TABLE_ENTRY        *ThisTable;
    char                    *AllocatedTable;


    FUNCTION_TRACE_PTR ("NsDeleteScope", Scope);


    if (!Scope)
    {
        return_VOID;
    }

    ThisTable = (NAME_TABLE_ENTRY *) Scope;


    /*
     * Deallocate the name table and all appendages
     */
    do
    {
        /* 
         * Create the original allocated pointer (backup to before appendage ptr),
         * and get the next appendage pointer.  This ptr is null at end-of-list.
         */

        AllocatedTable =  (((char *) ThisTable) - sizeof (NAME_TABLE_ENTRY *));
        ThisTable = NEXTSEG (ThisTable);

        DEBUG_PRINT (ACPI_INFO, ("NsDeleteScope: Deleting Name Table at %p \n", AllocatedTable));
        
        /* Now we can free the table */

        AcpiCmFree (AllocatedTable); 

    } while (ThisTable);
    
    return_VOID;
}


