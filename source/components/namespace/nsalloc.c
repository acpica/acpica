
/******************************************************************************
 *
 * Module Name: nsalloc - Namespace allocation and deletion utilities
 *              $Revision: 1.37 $
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
#include "acnamesp.h"
#include "acinterp.h"


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nsalloc");


UINT32  AcpiGbl_CurrentNameTableCount = 0;
UINT32  AcpiGbl_CurrentNameTableSize = 0;
UINT32  AcpiGbl_NameTableAllocSize;

#define DECREMENT_NAME_TABLE_METRICS(a) \
    AcpiGbl_CurrentNameTableCount--; \
    AcpiGbl_CurrentNameTableSize -= (a)

#define INCREMENT_NAME_TABLE_METRICS(a) \
    AcpiGbl_CurrentNameTableCount++; \
    AcpiGbl_CurrentNameTableSize+= (a)


/****************************************************************************
 *
 * FUNCTION:    AcpiNsAllocateNameTable
 *
 * PARAMETERS:  NteCount            - Count of NTEs to allocate
 *
 * RETURN:      The address of the first nte in the array, or NULL
 *
 * DESCRIPTION: Allocate an array of nte, including prepended link space
 *              Array is set to all zeros via AcpiOsCallcate().
 *
 ***************************************************************************/

ACPI_NAME_TABLE *
AcpiNsAllocateNameTable (
    UINT32                  NumEntries)
{
    ACPI_NAME_TABLE         *NameTable = NULL;
    UINT32                  AllocSize;


    FUNCTION_TRACE ("NsAllocateNameTable");


    AllocSize = sizeof (ACPI_NAME_TABLE) + ((NumEntries - 1) *
                sizeof (ACPI_NAMED_OBJECT));

    NameTable = AcpiCmCallocate (AllocSize);
    if (NameTable)
    {
        AcpiGbl_NameTableAllocSize = AllocSize;
        INCREMENT_NAME_TABLE_METRICS (AllocSize);
    }

    DEBUG_PRINT (TRACE_EXEC,
        ("NsAllocateNameTable: NameTable=%p\n", NameTable));

    return_PTR (NameTable);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsDeleteNameTable
 *
 * PARAMETERS:  Scope           - A handle to the scope to be deleted
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete a namespace Name Table with zero or
 *              more appendages.  The table and all appendages are deleted.
 *
 ***************************************************************************/

void
AcpiNsDeleteNameTable (
    ACPI_NAME_TABLE         *NameTable)
{
    ACPI_NAME_TABLE         *ThisTable;
    ACPI_NAME_TABLE         *NextTable;


    FUNCTION_TRACE_PTR ("AcpiNsDeleteNameTable", NameTable);


    if (!NameTable)
    {
        return_VOID;
    }

    ThisTable = NameTable;


    /*
     * Deallocate the name table and all appendages
     */
    do
    {
        NextTable = ThisTable->NextTable;

        DEBUG_PRINT (ACPI_INFO,
            ("AcpiNsDeleteNameTable: Table %p \n", ThisTable));

        /* Now we can free the table */

        AcpiCmFree (ThisTable);

        DECREMENT_NAME_TABLE_METRICS (AcpiGbl_NameTableAllocSize);

        ThisTable = NextTable;

    } while (ThisTable);

    return_VOID;
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
    ACPI_NAMED_OBJECT       *ParentEntry)
{
    ACPI_NAMED_OBJECT       *ChildEntry;
    UINT32                  Level;
    ACPI_OBJECT_INTERNAL    *ObjDesc;


    FUNCTION_TRACE ("NsDeleteNamespaceSubtree");


    ChildEntry     = 0;
    Level           = 1;

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

        ChildEntry = AcpiNsGetNextObject (ACPI_TYPE_ANY,
                                            ParentEntry,
                                            ChildEntry);

        if (ChildEntry)
        {
            /*
             * Found an object - delete the object within
             * the Value field
             */

            ObjDesc = AcpiNsGetAttachedObject (ChildEntry);
            if (ObjDesc)
            {
                AcpiNsDetachObject (ChildEntry);
                AcpiCmRemoveReference (ObjDesc);
            }


            /*
             * Clear the NTE in case this scope is reused
             * (e.g., a control method scope)
             */

            ChildEntry->Type = ACPI_TYPE_ANY;
            ChildEntry->Name = 0;

            /* Check if this object has any children */

            if (AcpiNsGetNextObject (ACPI_TYPE_ANY, ChildEntry, 0))
            {
                /*
                 * There is at least one child of this object,
                 * visit the object
                 */

                Level++;
                ParentEntry    = ChildEntry;
                ChildEntry     = 0;
            }

            else
            {
                /*
                 * There may be a name table even if there are
                 * no children
                 */

                AcpiNsDeleteNameTable (ChildEntry->ChildTable);
                ChildEntry->ChildTable = NULL;

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
             * Delete the scope (Name Table) associated with
             * the parent object
             */
            /* Don't delete the top level scope, this allows
             * the dynamic deletion of objects created underneath
             * control methods!
             */

            if (Level != 0)
            {
                AcpiNsDeleteNameTable (ParentEntry->ChildTable);
                ParentEntry->ChildTable = NULL;
            }

            /* New "last child" is this parent object */

            ChildEntry = ParentEntry;

            /* Now we can move up the tree to the grandparent */

            ParentEntry = AcpiNsGetParentEntry (ParentEntry);
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
    ACPI_NAMED_OBJECT       *Entry)
{
    ACPI_NAMED_OBJECT       *ThisEntry;


    /* There may be a name table even if there are no children */

    AcpiNsDeleteNameTable (Entry->ChildTable);
    Entry->ChildTable = NULL;


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

            if (ThisEntry->ChildTable)
            {
                AcpiNsDeleteNameTable (ThisEntry->ChildTable);
                ThisEntry->ChildTable = NULL;
            }

            /*
             * Mark the entry free
             * (This doesn't deallocate anything)
             */

            AcpiNsFreeTableEntry (ThisEntry);

        }

        /* Move up to parent */

        ThisEntry = AcpiNsGetParentEntry (ThisEntry);
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
    ACPI_NAMED_OBJECT       *ChildEntry;
    UINT32                  Level;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_NAMED_OBJECT       *ParentEntry;


    FUNCTION_TRACE ("NsDeleteNamespaceSubtree");


    ParentEntry    = AcpiGbl_RootObject;
    ChildEntry     = 0;
    Level           = 1;

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

        ChildEntry = AcpiNsGetNextObject (ACPI_TYPE_ANY,
                                            ParentEntry,
                                            ChildEntry);

        if (ChildEntry)
        {
            if (ChildEntry->OwnerId == OwnerId)
            {
                /*
                 * Found an object - delete the object within
                 * the Value field
                 */

                ObjDesc = AcpiNsGetAttachedObject (ChildEntry);
                if (ObjDesc)
                {
                    AcpiNsDetachObject (ChildEntry);
                    AcpiCmRemoveReference (ObjDesc);
                }
            }

            /* Check if this object has any children */

            if (AcpiNsGetNextObject (ACPI_TYPE_ANY, ChildEntry, 0))
            {
                /*
                 * There is at least one child of this object,
                 * visit the object
                 */

                Level++;
                ParentEntry    = ChildEntry;
                ChildEntry     = 0;
            }

            else if (ChildEntry->OwnerId == OwnerId)
            {
                AcpiNsRemoveReference (ChildEntry);
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
             * Delete the scope (Name Table) associated with
             * the parent object
             */
            /* Don't delete the top level scope, this allows
             * the dynamic deletion of objects created underneath
             * control methods!
             */


            if (Level != 0)
            {
                if (ParentEntry->OwnerId == OwnerId)
                {
                    AcpiNsRemoveReference (ParentEntry);
                }
            }


            /* New "last child" is this parent object */

            ChildEntry = ParentEntry;

            /* Now we can move up the tree to the grandparent */

            ParentEntry = AcpiNsGetParentEntry (ParentEntry);
        }
    }


    return_ACPI_STATUS (AE_OK);
}



