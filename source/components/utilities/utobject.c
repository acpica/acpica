 
/******************************************************************************
 * 
 * Module Name: cmobject - ACPI object create/delete/cache routines
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

#define __CMOBJECT_C__

#include <acpi.h>
#include <acobject.h>
#include <interp.h>
#include <namesp.h>
#include <pnp.h>


#define _COMPONENT          MISCELLANEOUS
        MODULE_NAME         ("cmobject");


/*****************************************************************************
 * 
 * FUNCTION:    _CmAllocateObjectDesc
 *
 * PARAMETERS:  ModuleName          - Caller's module name (for error output)
 *              LineNumber          - Caller's line number (for error output)
 *              ComponentId         - Caller's component ID (for error output)
 *              Message             - Error message to use on failure
 *
 * RETURN:      Pointer to newly allocated object descriptor.  Null on error
 *
 * DESCRIPTION: Allocate a new object descriptor.  Gracefully handle
 *              error conditions.
 *
 ****************************************************************************/

void *
_CmAllocateObjectDesc (
    char                    *ModuleName, 
    INT32                   LineNumber, 
    INT32                   ComponentId)
{
    ACPI_OBJECT_INTERNAL    *Object;
    

    FUNCTION_TRACE ("_AllocateObjectDesc");


    CmAcquireMutex (MTX_CACHES);

    Gbl_ObjectCacheRequests++;

    /* Check the cache first */

    if (Gbl_ObjectCache)
    {
        /* There is an object available, use it */

        Object = Gbl_ObjectCache;
        Gbl_ObjectCache = Object->Common.Next;
        Object->Common.Next = NULL;

        Gbl_ObjectCacheHits++;
        Gbl_ObjectCacheDepth--;

        CmReleaseMutex (MTX_CACHES);
    }

    else
    {
        /* The cache is empty, create a new object */

        CmReleaseMutex (MTX_CACHES);

        /* Attempt to allocate new descriptor */

        Object = _CmCallocate (sizeof (ACPI_OBJECT_INTERNAL), ComponentId,
                                    ModuleName, LineNumber);
        
        if (!Object)
        {
            /* Allocation failed */
        
            _REPORT_ERROR (ModuleName, LineNumber, ComponentId, 
                            "Could not allocate Object Descriptor");

            return_VALUE (NULL);
        }
    }

    /* Mark the descriptor type */

    Object->Common.DataType = DESC_TYPE_ACPI_OBJ;

    DEBUG_PRINT (TRACE_ALLOCATIONS, ("AllocateObjectDesc: %p Size 0x%x\n",
                    Object, sizeof (ACPI_OBJECT_INTERNAL)));

    return_VALUE (Object);
}



/*****************************************************************************
 * 
 * FUNCTION:    CmDeleteObjectDesc
 *
 * PARAMETERS:  Object          - Acpi internal object to be deleted
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Free an ACPI object descriptor or add it to the object cache
 *
 ****************************************************************************/

void
CmDeleteObjectDesc (
    ACPI_OBJECT_INTERNAL    *Object)
{


    /* Object must be an ACPI_OBJECT_INTERNAL */

    if (Object->Common.DataType != DESC_TYPE_ACPI_OBJ)
    {
        DEBUG_PRINT (ACPI_ERROR, ("CmDeleteObjectDesc: Obj %p is not an ACPI object\n", Object));
        return;
    }

    /* Make sure that the object isn't already in the cache */

    if (Object->Common.Next)
    {
        DEBUG_PRINT (ACPI_ERROR, ("CmDeleteObjectDesc: Obj %p is already in the object cache\n", Object));
        return;
    }


    /* If cache is full, just free this object */

    if (Gbl_ObjectCacheDepth >= MAX_OBJECT_CACHE_DEPTH)
    {
        /* 
         * Memory allocation metrics.  Call the macro here since we only
         * care about dynamically allocated objects.
         */
        DECREMENT_OBJECT_METRICS (Gbl_ObjectCache->Common.Size);

        CmFree (Object);
        return;
    }

    CmAcquireMutex (MTX_CACHES);

    /* Clear the entire object.  This is important! */

    MEMSET (Object, 0, sizeof (ACPI_OBJECT_INTERNAL));
    Object->Common.DataType = DESC_TYPE_ACPI_OBJ;

    /* Put the object at the head of the global cache list */

    Object->Common.Next = Gbl_ObjectCache;
    Gbl_ObjectCache = Object;
    Gbl_ObjectCacheDepth++;


    CmReleaseMutex (MTX_CACHES);
}



/******************************************************************************
 *
 * FUNCTION:    CmDeleteObjectCache
 *
 * PARAMETERS:  None
 * 
 * RETURN:      Status
 * 
 * DESCRIPTION: Purge the global state object cache.  Used during subsystem
 *              termination.
 *
 ******************************************************************************/

void
CmDeleteObjectCache (
    void)
{
    ACPI_OBJECT_INTERNAL    *Next;


    FUNCTION_TRACE ("CmDeleteObjectCache");


    /* Traverse the global cache list */

    while (Gbl_ObjectCache)
    {
        /* Delete one cached state object */

        Next = Gbl_ObjectCache->Common.Next;
        Gbl_ObjectCache->Common.Next = NULL;

        /* 
         * Memory allocation metrics.  Call the macro here since we only
         * care about dynamically allocated objects.
         */
        DECREMENT_OBJECT_METRICS (Gbl_ObjectCache->Common.Size);
        
        CmFree (Gbl_ObjectCache);
        Gbl_ObjectCache = Next;
    }

    return_VOID;
}
 

/*****************************************************************************
 * 
 * FUNCTION:    CmInitStaticObject
 *
 * PARAMETERS:  ObjDesc             - Pointer to a "static" object - on stack
 *                                    or in the data segment.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Initialize a static object.  Sets flags to disallow dynamic
 *              deletion of the object.
 *
 ****************************************************************************/

void
CmInitStaticObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{

    FUNCTION_TRACE_PTR ("CmInitStaticObject", ObjDesc);


    if (!ObjDesc)
    {
        return_VOID;
    }


    /*
     * Clear the entire descriptor 
     */
    MEMSET ((void *) ObjDesc, 0, sizeof (ACPI_OBJECT_INTERNAL));


    /*
     * Initialize the header fields
     * 1) This is an ACPI_OBJECT_INTERNAL descriptor
     * 2) The size is the full object (worst case)
     * 3) The flags field indicates static allocation 
     * 4) Reference count starts at one (not really necessary since the
     *    object can't be deleted, but keeps everything sane)
     */

    ObjDesc->Common.DataType        = DESC_TYPE_ACPI_OBJ;
    ObjDesc->Common.Size            = sizeof (ACPI_OBJECT_INTERNAL);
    ObjDesc->Common.Flags           = AO_STATIC_ALLOCATION;
    ObjDesc->Common.ReferenceCount  = 1;

    return_VOID;
}

