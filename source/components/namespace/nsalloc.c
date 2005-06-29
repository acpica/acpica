
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

#include <acpi.h>
#include <namespace.h>
#include <interpreter.h>


#define _THIS_MODULE        "nsalloc.c"
#define _COMPONENT          NAMESPACE



/*****************************************************************************
 * 
 * FUNCTION:    NsIsInSystemTable
 *
 * PARAMETERS:  *Where              - Pointer to be examined
 *
 * RETURN:      TRUE if Where is within the AML stream
 *              FALSE otherwise
 *
 ****************************************************************************/

BOOLEAN
NsIsInSystemTable (
    void                    *Where)
{
    UINT32                  i;
    ACPI_TABLE_DESC         *TableDesc;
    ACPI_TABLE_HEADER       *Table;


    /* No function trace, called too often! */


    /* Ignore null pointer */

    if (!Where)
    {
        return (FALSE);
    }


    /* Check for a pointer within the DSDT */

    if (IS_IN_ACPI_TABLE (Where, Gbl_DSDT))
    {
        return (TRUE);
    }


    /* Check each of the loaded SSDTs (if any)*/

    TableDesc = &Gbl_AcpiTables[TABLE_SSDT];

    for (i = 0; i < Gbl_AcpiTables[TABLE_SSDT].Count; i++)
    {
        Table = TableDesc->Pointer;

        if (IS_IN_ACPI_TABLE (Where, Table))
        {
            return (TRUE);
        }

        TableDesc = TableDesc->Next;
    }


    /* TBD: Need to check the PSDTs? */


    return (FALSE);
}


/****************************************************************************
 *
 * FUNCTION:    NsAllocateNameTable
 *
 * PARAMETERS:  NteCount            - Count of NTEs to allocate
 *
 * RETURN:      The address of the first nte in the array, or NULL
 *
 * DESCRIPTION: Allocate an array of nte, including prepended link space
 *              Array is set to all zeros via OsdCallcate().
 *
 ***************************************************************************/

NAME_TABLE_ENTRY *
NsAllocateNameTable (
    INT32                   NteCount)
{
    NAME_TABLE_ENTRY        *NameTable = NULL;
    ACPI_SIZE               AllocSize;


    FUNCTION_TRACE ("NsAllocateNameTable");


    AllocSize = (ACPI_SIZE) NteCount * sizeof (NAME_TABLE_ENTRY);

    
    /* Allow room for link to appendage */
    
    AllocSize += sizeof (NAME_TABLE_ENTRY *);

  
    NameTable = CmCallocate (AllocSize);
    if (NameTable)
    {
        /* Move past the appendage pointer */
    
        NameTable = (NAME_TABLE_ENTRY *) (((UINT8 *) NameTable) + 
                        sizeof (NAME_TABLE_ENTRY *));
    }

    DEBUG_PRINT (TRACE_EXEC, ("NsAllocateNameTable: NameTable=%p\n", NameTable));

    return_VALUE (NameTable);
}


/****************************************************************************
 *
 * FUNCTION:    NsDeleteNamespace
 *
 * PARAMETERS:  None.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete the entire namespace.  This includes all objects stored
 *              within it, as well as the actual namespace tables.
 *
 ***************************************************************************/

ACPI_STATUS
NsDeleteNamespace (void)
{
    ACPI_HANDLE             ChildHandle;
    ACPI_HANDLE             ParentHandle;
    ACPI_HANDLE             Dummy;
    UINT32                  Level;


    FUNCTION_TRACE ("NsDeleteNamespace");


    /* Begin deletion walk at the root object */

    ParentHandle    = Gbl_RootObject;
    ChildHandle     = 0;
    Level           = 1;

    /* 
     * Traverse the tree of objects until we bubble back up 
     * to where we started.
     */

    while (Level > 0)
    {
        /* Get the next typed object in this scope.  Null returned if not found */

        if (ACPI_SUCCESS (AcpiGetNextObject (ACPI_TYPE_Any, ParentHandle, ChildHandle, &ChildHandle)))
        {
            /* Found an object - delete the object within the Value field */

            NsDetachObject (ChildHandle);

            /* Check if this object has any children */

            if (ACPI_SUCCESS (AcpiGetNextObject (ACPI_TYPE_Any, ChildHandle, 0, &Dummy)))
            {
                /* There is at least one child of this object, visit the object */

                Level++;
                ParentHandle    = ChildHandle;
                ChildHandle     = 0;
            }

            else
            {
                /* There may be a name table even if there are no children */

                NsDeleteScope (((NAME_TABLE_ENTRY *) ChildHandle)->Scope);

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

            NsDeleteScope (((NAME_TABLE_ENTRY *) ParentHandle)->Scope);

            /* New "last child" is this parent object */

            ChildHandle = ParentHandle;

            /* Now we can move up the tree to the grandparent */

            AcpiGetParent (ParentHandle, &ParentHandle);
        }
    }

    /* Detach any object(s) attached to the root */
    
    NsDetachObject (Gbl_RootObject);
    Gbl_RootObject->Scope = NULL;

    REPORT_SUCCESS ("Entire namespace and objects deleted");

    return_ACPI_STATUS (AE_OK); 
}


/****************************************************************************
 *
 * FUNCTION:    NsDeleteScope
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
NsDeleteScope (
    ACPI_HANDLE             Scope)
{
    NAME_TABLE_ENTRY        *ThisTable;
    char                    *AllocatedTable;


	FUNCTION_TRACE ("NsDeleteScope");
    DEBUG_PRINT (ACPI_INFO, ("NsDeleteScope: Deleting Scope %p \n", Scope));

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

        AllocatedTable =  (((UINT8 *) ThisTable) - sizeof (NAME_TABLE_ENTRY *));
        ThisTable = NEXTSEG (ThisTable);

        DEBUG_PRINT (ACPI_INFO, ("NsDeleteScope: Deleting Name Table at %p \n", AllocatedTable));
        
        /* Now we can free the table */

        CmFree (AllocatedTable); 

    } while (ThisTable);
    
    return_VOID;
}


/****************************************************************************
 *
 * FUNCTION:    NsDeleteAcpiTables
 *
 * PARAMETERS:  None.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete all internal ACPI tables
 *
 ***************************************************************************/

void
NsDeleteAcpiTables (void)
{
    UINT32                      i;


    /*
     * Free memory allocated for ACPI tables
     * Memory can either be mapped or allocated
     */

    for (i = 0; i < ACPI_TABLE_MAX; i++)
    {
        NsDeleteAcpiTable (i);
    }

}


/****************************************************************************
 *
 * FUNCTION:    NsDeleteAcpiTable
 *
 * PARAMETERS:  Type                - The table type to be deleted
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete an internal ACPI table
 *
 ***************************************************************************/

void
NsDeleteAcpiTable (
    ACPI_TABLE_TYPE             Type)
{
	FUNCTION_TRACE ("NsDeleteAcpiTable");


    if (Type > ACPI_TABLE_MAX)
    {
        return_VOID;
    }


    /* Free the table */

    NsFreeAcpiTable (&Gbl_AcpiTables[Type]);


    /* Clear the appropriate "typed" global table pointer */

    switch (Type)
    {
    case TABLE_RSDP:
        Gbl_RSDP = NULL;
        break;

    case TABLE_APIC:
        Gbl_APIC = NULL;
        break;

    case TABLE_DSDT:
        Gbl_DSDT = NULL;
        break;

    case TABLE_FACP:
        Gbl_FACP = NULL;
        break;

    case TABLE_FACS:
        Gbl_FACS = NULL;
        break;

    case TABLE_PSDT:
        break;

    case TABLE_RSDT:
        Gbl_RSDT = NULL;
        break;

    case TABLE_SSDT:
        break;

    case TABLE_SBST:
        Gbl_SBST = NULL;

    default:
        break;
    }

    return_VOID;
}


/****************************************************************************
 *
 * FUNCTION:    NsFreeAcpiTable
 *
 * PARAMETERS:  TableInfo           - A table info struct
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Free the memory associated with an internal ACPI table
 *
 ***************************************************************************/

void
NsFreeAcpiTable (
    ACPI_TABLE_DESC         *ListHead)
{
    ACPI_TABLE_DESC         *TableDesc;
    UINT32                  Count;
    UINT32                  i;


	FUNCTION_TRACE ("NsFreeAcpiTable");


    /* Get the head of the list */

    TableDesc   = ListHead;
    Count       = ListHead->Count;

    /*
     * Walk the entire list, deleting both the allocated tables
     * and the table descriptors
     */

    for (i = 0; i < Count; i++)
    {
        if (TableDesc->Pointer)
        {
            /* Valid table, determine type of memory */

            switch (TableDesc->Allocation)
            {

            case ACPI_MEM_NOT_ALLOCATED:

                break;


            case ACPI_MEM_ALLOCATED:

                CmFree (TableDesc->Pointer);
                break;


            case ACPI_MEM_MAPPED:

                OsdUnMapMemory (TableDesc->Pointer, TableDesc->Length);
                break;
            }
        }

        /* Move to the next, delete the current descriptor */

        TableDesc = TableDesc->Next;
        if (i > 0)
        {
            CmFree (TableDesc->Prev);
        }
    }



    /* Clear the list head */

    ListHead->Prev      = ListHead;
    ListHead->Next      = ListHead;
    ListHead->Pointer   = NULL;
    ListHead->Length    = 0;
    ListHead->Count     = 0;

    return_VOID;
}


/****************************************************************************
 *
 * FUNCTION:    NsInstallAcpiTable
 *
 * PARAMETERS:  TableType           - The type of the table
 *              TableInfo           - A table info struct
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Install a table into the global data structs.
 *
 ***************************************************************************/

ACPI_STATUS
NsInstallAcpiTable (
    ACPI_TABLE_TYPE         TableType,
    ACPI_TABLE_DESC         *TableInfo)
{
    ACPI_TABLE_DESC         *ListHead;
    ACPI_TABLE_DESC         *TableDesc;


    FUNCTION_TRACE ("NsInstallAcpiTable");


    ListHead    = &Gbl_AcpiTables[TableType];
    TableDesc   = ListHead;
   
    if (Gbl_AcpiTableFlags[TableType] == ACPI_TABLE_SINGLE)
    {
        if (ListHead->Pointer)
        {
            NsFreeAcpiTable (ListHead);
        }

        TableDesc->Count = 1;
    }


    else 
    {
        if (ListHead->Pointer)
        {
            TableDesc = CmCallocate (sizeof (ACPI_TABLE_DESC));
            if (!TableDesc)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            ListHead->Count++;

            /* Update original previous */

            ListHead->Prev->Next = TableDesc;

            /* Update new entry */

            TableDesc->Prev = ListHead->Prev;
            TableDesc->Next = (ACPI_TABLE_DESC *) ListHead;

            /* Update list head */

            ListHead->Prev = TableDesc;
        }

        else
        {
            TableDesc->Count = 1;
        }
    }


    /* Common initialization of the table descriptor */

    TableDesc->Pointer      = TableInfo->Pointer;
    TableDesc->Length       = TableInfo->Length;
    TableDesc->Allocation   = TableInfo->Allocation;


    return_ACPI_STATUS (AE_OK);
}