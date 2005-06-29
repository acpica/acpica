
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
 * license (without the right to sublicense), under only those claims of Intel
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

    FUNCTION_EXIT;
    return NameTable;
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
    ACPI_HANDLE             ObjHandle = 0;
    ACPI_HANDLE             StartHandle;
    ACPI_HANDLE             Scope;
    ACPI_HANDLE             NewScope;


    FUNCTION_TRACE ("NsDeleteNamespace");


    /* Begin search in the scope owned by the starting object */

    Scope = RootObject->Scope;
    StartHandle = RootObject;

    /* 
     * Traverse the tree of objects until we bubble back up 
     * to where we started.
     */

    while (ObjHandle != StartHandle)
    {
        /* Get the next typed object in this scope.  Null returned if not found */

        if (ACPI_SUCCESS (AcpiGetNextObject (TYPE_Any, Scope, ObjHandle, &ObjHandle)))
        {
            /* Found an object - delete the object within the Value field */

            NsDeleteValue (ObjHandle);

            /* Check for a valid scope for this object */

            if (ACPI_SUCCESS (AcpiGetScope (ObjHandle, &NewScope)))
            {
                /* There is a valid scope, we will check for child objects */

                ObjHandle = 0;
                Scope = NewScope;
            }
        }

        else
        {
            /*
             * No more objects in this scope, get the scope parent, then we can
             * delete the scope.
             */
            AcpiGetParent (Scope, &ObjHandle);
            NsDeleteScope (Scope);

            /*
             * Go back up to the parent's scope 
             * (But only back up to where we started the search)
             */
            AcpiGetContainingScope (ObjHandle, &Scope);
        }
    }


    REPORT_SUCCESS ("Entire namespace and objects deleted");
    RootObject->Scope = NULL;

    FUNCTION_STATUS_EXIT (AE_OK);
    return AE_OK; 
}


/****************************************************************************
 *
 * FUNCTION:    NsDeleteValue
 *
 * PARAMETERS:  Object           - An object whose Value will be deleted
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete the Value associated with a namespace object.  If the
 *              Value is an allocated object, it is freed.  Otherwise, the
 *              field is simply cleared.
 *
 ***************************************************************************/

void
NsDeleteValue (
    ACPI_HANDLE             Object)
{
    NAME_TABLE_ENTRY        *Entry = Object;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    void                    *ObjPointer = NULL;
    
    FUNCTION_TRACE ("NsDeleteValue");

    ObjDesc = Entry->Value;
    if (!ObjDesc)
    {
    	FUNCTION_EXIT;
        return;
    }

    /* Found a valid value */

    DEBUG_PRINT (ACPI_INFO, ("NsDeleteValue: Object=%p Value=%p Name %4.4s\n", 
                            Entry, ObjDesc, &Entry->Name));

    /* Not every value is an object allocated via CmCallocate, must check */

    if (!AmlIsInPCodeBlock ((UINT8 *)    ObjDesc)) /*&&
        !IS_NS_HANDLE                   (ObjDesc))*/
    {

        /* Object was allocated, there may be some sub objects that must be deleted */

        switch (Entry->Type)
        {
        case TYPE_DefField:
            DEBUG_PRINT (ACPI_INFO, ("NsDeleteValue: ***** Field found %p, container %p (not freeing)\n", 
                                    ObjDesc, ObjDesc->Field.Container));
            break;

        case TYPE_String:
            ObjPointer = ObjDesc->String.Pointer;
            DEBUG_PRINT (ACPI_INFO, ("NsDeleteValue: ***** String found %p, ptr %p\n", 
                                    ObjDesc, ObjDesc->String.Pointer));
            break;

        case TYPE_Buffer:
            ObjPointer = ObjDesc->Buffer.Pointer;
            DEBUG_PRINT (ACPI_INFO, ("NsDeleteValue: ***** Buffer found %p, ptr %p\n", 
                                    ObjDesc, ObjDesc->Buffer.Pointer));
            break;

        case TYPE_Package:
            DEBUG_PRINT (ACPI_INFO, ("NsDeleteValue: ***** Package of count %d\n", 
                                    ObjDesc->Package.Count));
            break;
    
        case TYPE_Method:
            DEBUG_PRINT (ACPI_INFO, ("NsDeleteValue: ***** Method found %p\n", 
                                    ObjDesc));
            break;

        case TYPE_Lvalue:
            ObjPointer = ObjDesc->Lvalue.Object;
            DEBUG_PRINT (ACPI_INFO, ("NsDeleteValue: ***** Lvalue: %p\n", 
                                    ObjPointer));
            break;

        default:
            break;
        }

        if (ObjPointer)
        {
            if (!AmlIsInPCodeBlock ((UINT8 *)    ObjPointer))
            {
                DEBUG_PRINT (ACPI_INFO, ("Deleting Object Pointer %p \n", ObjPointer));
    
                CmFree (ObjPointer);
            }
        }


        DEBUG_PRINT (ACPI_INFO, ("Deleting Object %p \n", ObjDesc));
    
        CmFree (ObjDesc);
    }

    /* Clear the entry in all cases */

    Entry->Value = NULL;
    
    FUNCTION_EXIT;
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
    
    FUNCTION_EXIT;
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
    	FUNCTION_EXIT;
        return;
    }


    /* Free the table */

    NsFreeAcpiTable (&AcpiTables[Type]);


    /* Clear the appropriate "typed" global table pointer */

    switch (Type)
    {
    case TABLE_RSDP:
        RSDP = NULL;
        break;

    case TABLE_APIC:
        APIC = NULL;
        break;

    case TABLE_DSDT:
        DSDT = NULL;
        break;

    case TABLE_FACP:
        FACP = NULL;
        break;

    case TABLE_FACS:
        FACS = NULL;
        break;

    case TABLE_PSDT:
        PSDT = NULL;
        break;

    case TABLE_RSDT:
        RSDT = NULL;
        break;

    case TABLE_SSDT:
        SSDT = NULL;
        break;

    case TABLE_SBDT:
        SBDT = NULL;

    default:
        break;
    }

	FUNCTION_EXIT;
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
    ACPI_TABLE_INFO         *TableInfo)
{
	FUNCTION_TRACE ("NsFreeAcpiTable");


    if (TableInfo->Pointer)
    {
        /* Valid table, determine type of memory */

        switch (TableInfo->Allocation)
        {

        case ACPI_MEM_NOT_ALLOCATED:

            break;


        case ACPI_MEM_ALLOCATED:

            CmFree (TableInfo->Pointer);
            break;


        case ACPI_MEM_MAPPED:

            OsdUnMapMemory (TableInfo->Pointer, TableInfo->Length);
            break;
        }
    }

    /* Clear the table entry */

    TableInfo->Pointer    = NULL;
    TableInfo->Allocation = ACPI_MEM_NOT_ALLOCATED;
    TableInfo->Length     = 0;

    FUNCTION_EXIT;
}



