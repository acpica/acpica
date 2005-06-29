
/******************************************************************************
 * 
 * Module Name: nsobject - Utilities for objects attached to namespace table entries
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


#define __NSOBJECT_C__

#include "acpi.h"
#include "amlcode.h"
#include "namesp.h"
#include "interp.h"
#include "tables.h"


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nsobject");



/****************************************************************************
 *
 * FUNCTION:    AcpiNsAttachObject
 *
 * PARAMETERS:  Handle              - Handle of nte
 *              Object              - Object to be attached
 *              Type                - Type of object, or ACPI_TYPE_ANY if not known
 *
 * DESCRIPTION: Record the given object as the value associated with the
 *              name whose ACPI_HANDLE is passed.  If Object is NULL 
 *              and Type is ACPI_TYPE_ANY, set the name as having no value.
 *
 * MUTEX:       Assumes namespace is locked
 *
 ***************************************************************************/

ACPI_STATUS
AcpiNsAttachObject (
    ACPI_HANDLE             Handle, 
    ACPI_HANDLE             Object, 
    OBJECT_TYPE_INTERNAL    Type)
{
    NAME_TABLE_ENTRY        *ThisEntry = (NAME_TABLE_ENTRY *) Handle;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *PreviousObjDesc;
    OBJECT_TYPE_INTERNAL    ObjType = ACPI_TYPE_ANY;
    UINT8                   Flags;
    UINT16                  Opcode;


    FUNCTION_TRACE ("NsAttachObject");


    /*
     * Parameter validation
     */

    if (!Acpi_GblRootObject->Scope)
    {
        /* Name space not initialized  */

        REPORT_ERROR ("NsAttachObject: Name space not initialized");
        return_ACPI_STATUS (AE_NO_NAMESPACE);
    }
    
    if (!Handle)
    {
        /* Invalid handle */

        REPORT_ERROR ("NsAttachObject: Null name handle");
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }
    
    if (!Object && (ACPI_TYPE_ANY != Type))
    {
        /* Null object */

        REPORT_ERROR ("NsAttachObject: Null object, but type not ACPI_TYPE_ANY");
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }
    
    if (!VALID_DESCRIPTOR_TYPE (Handle, DESC_TYPE_NTE))
    {
        /* Not a name handle */

        REPORT_ERROR ("NsAttachObject: Invalid handle");
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Check if this object is already attached */

    if (ThisEntry->Object == Object)
    {
        DEBUG_PRINT (TRACE_EXEC,("NsAttachObject: Obj %p already installed in NTE %p\n",
                        Object, Handle));
    
        return_ACPI_STATUS (AE_OK);
    }


    /* Get the current flags field of the NTE */

    Flags = ThisEntry->Flags;
    Flags &= ~NTE_AML_ATTACHMENT;


    /* If null object, we will just install it */

    if (!Object)
    {
        ObjDesc = NULL;
        ObjType = ACPI_TYPE_ANY;
    }

    /*
     * If the object is an NTE with an attached object, 
     * we will use that (attached) object
     */

    else if (VALID_DESCRIPTOR_TYPE (Object, DESC_TYPE_NTE) && 
            ((NAME_TABLE_ENTRY *) Object)->Object)
    {
        /* 
         * Value passed is a name handle and that name has a non-null value.
         * Use that name's value and type.
         */

        ObjDesc = ((NAME_TABLE_ENTRY *) Object)->Object;
        ObjType = ((NAME_TABLE_ENTRY *) Object)->Type;

        /*
         * Copy appropriate flags
         */

        if (((NAME_TABLE_ENTRY *) Object)->Flags & NTE_AML_ATTACHMENT)
        {
            Flags |= NTE_AML_ATTACHMENT;
        }
    }


    /*
     * Otherwise, we will use the parameter object, but we must type it first
     */

    else
    {
        ObjDesc = (ACPI_OBJECT_INTERNAL *) Object;


        /* If a valid type (non-ANY) was given, just use it */

        if (ACPI_TYPE_ANY != Type)
        {
            ObjType = Type;
        }

    
        /* Type is TYPE_Any, we must try to determinte the actual type of the object */

        /*
         * Check if value points into the AML code
         */
        else if (AcpiTbSystemTablePointer (Object))
        {
            /* Object points into the AML stream.  Set a flag bit in the NTE to indicate this */
    
            Flags |= NTE_AML_ATTACHMENT;

            /* The next byte (perhaps the next two bytes) will be the AML opcode */

            STORE16 (&Opcode, Object);


            /* Check for a recognized OpCode */

            switch ((UINT8) Opcode)
            {

            case AML_OP_PREFIX:

                if (Opcode != AML_REVISION_OP)
                {
                    /* OpPrefix is unrecognized unless part of RevisionOp */
            
                    break;
                }

                /* Else fall through to set type as Number */
    

            case AML_ZERO_OP: case AML_ONES_OP: case AML_ONE_OP:
            case AML_BYTE_OP: case AML_WORD_OP: case AML_DWORD_OP:

                ObjType = ACPI_TYPE_NUMBER;
                break;


            case AML_STRING_OP:

                ObjType = ACPI_TYPE_STRING;
                break;


            case AML_BUFFER_OP:

                ObjType = ACPI_TYPE_BUFFER;
                break;


            case AML_MUTEX_OP:

                ObjType = ACPI_TYPE_MUTEX;
                break;


            case AML_PACKAGE_OP:

                ObjType = ACPI_TYPE_PACKAGE;
                break;


            default:

                DEBUG_PRINT (ACPI_ERROR, ("AML Opcode/Type [%x] not supported in attach\n", (UINT8) Opcode));

                return_ACPI_STATUS (AE_TYPE);
                break;
            }
        }

        else
        {
            /* 
             * Cannot figure out the type -- set to DefAny which will print as an
             * error in the name table dump
             */

            if (GetDebugLevel () > 0)
            {
                DUMP_PATHNAME (Handle, "NsAttachObject confused: setting bogus type for  ", 
                                ACPI_INFO, _COMPONENT);

                if (AcpiTbSystemTablePointer (Object))
                {
                    DEBUG_PRINT (ACPI_INFO,
                                ("AML-stream code %02x\n", *(UINT8 *) Object));
                }
        
                else if (VALID_DESCRIPTOR_TYPE (Object, DESC_TYPE_NTE))
                {
                    DUMP_PATHNAME (Object, "name ", ACPI_INFO, _COMPONENT);
                }
        
                else
                {
                    DUMP_PATHNAME (Object, "object ", ACPI_INFO, _COMPONENT);
                    DUMP_STACK_ENTRY (Object);
                }
            }

            ObjType = INTERNAL_TYPE_DEF_ANY;
        }
    }



    DEBUG_PRINT (TRACE_EXEC,("NsAttachObject: Installing obj %p into NTE %p\n",
                    ObjDesc, Handle));
    

    /* Must increment the new value's reference count (if it is an internal object) */

    AcpiCmAddReference (ObjDesc);

    /* Save the existing object (if any) for deletion later */

    PreviousObjDesc = ThisEntry->Object;

    /* Install the object and set the type, flags */

    ThisEntry->Object   = ObjDesc;
    ThisEntry->Type     = (UINT8) ObjType;
    ThisEntry->Flags    = Flags;


    /* 
     * Delete an existing attached object. 
     */

    if (PreviousObjDesc)
    {
        AcpiCmRemoveReference (PreviousObjDesc);    /* One for the attach to the NTE */
        AcpiCmRemoveReference (PreviousObjDesc);    /* Now delete */
    }

    return_ACPI_STATUS (AE_OK);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsAttachMethod
 *
 * PARAMETERS:  Handle              - Handle of nte to be set
 *              Offset              - Value to be set
 *              Length              - Length associated with value
 *
 * DESCRIPTION: Record the given offset and p-code length of the method
 *              whose handle is passed
 *
 * MUTEX:       Assumes namespace is locked
 *
 ***************************************************************************/

ACPI_STATUS
AcpiNsAttachMethod (
    ACPI_HANDLE             Handle, 
    UINT8                   *PcodeAddr, 
    UINT32                  PcodeLength)
{
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_OBJECT_INTERNAL    *PreviousObjDesc;
    NAME_TABLE_ENTRY        *ThisEntry = (NAME_TABLE_ENTRY *) Handle;


    FUNCTION_TRACE ("NsAttachMethod");


    /* Parameter validation */

    if (!Acpi_GblRootObject->Scope)
    {
        /* Name space uninitialized */

        REPORT_ERROR ("NsAttachMethod: name space uninitialized");
        return_ACPI_STATUS (AE_NO_NAMESPACE);
    }
    
    if (!Handle)
    {
        /* Null name handle */

        REPORT_ERROR ("NsAttachMethod: null name handle");
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    
    /* Allocate a method descriptor */

    ObjDesc = AcpiCmCreateInternalObject (ACPI_TYPE_METHOD);
    if (!ObjDesc)
    {
        /* Method allocation failure  */

        REPORT_ERROR ("NsAttachMethod: allocation failure");
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Init the method info */

    ObjDesc->Method.Pcode       = PcodeAddr;
    ObjDesc->Method.PcodeLength = PcodeLength;

    /* Update reference count and install */

    AcpiCmAddReference (ObjDesc);

    PreviousObjDesc = ThisEntry->Object;
    ThisEntry->Object = ObjDesc;


    /* 
     * Delete an existing object.  Don't try to re-use in case it is shared
     */
    if (PreviousObjDesc)
    {
        DEBUG_PRINT (ACPI_INFO, ("NsAttachMethod: ***Old: %p Obj %p Pcode %p Len 0x%X\n",
                                    Handle, PreviousObjDesc, PreviousObjDesc->Method.Pcode, PreviousObjDesc->Method.PcodeLength));

        AcpiCmRemoveReference (PreviousObjDesc);
    }

    DEBUG_PRINT (ACPI_INFO, ("NsAttachMethod: %p Obj %p Pcode %p Len 0x%X\n",
                            Handle, ObjDesc, ObjDesc->Method.Pcode, ObjDesc->Method.PcodeLength));

    return_ACPI_STATUS (AE_OK);
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsDetachObject
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
AcpiNsDetachObject (
    ACPI_HANDLE             Object)
{
    NAME_TABLE_ENTRY        *Entry = Object;
    ACPI_OBJECT_INTERNAL    *ObjDesc;

    
    FUNCTION_TRACE ("NsDetachObject");

    ObjDesc = Entry->Object;
    if (!ObjDesc)
    {
        return_VOID;
    }

    /* Clear the entry in all cases */

    Entry->Object = NULL;
    
    /* Found a valid value */

    DEBUG_PRINT (ACPI_INFO, ("NsDetachObject: Object=%p Value=%p Name %4.4s\n", 
                            Entry, ObjDesc, &Entry->Name));

    /* Not every value is an object allocated via AcpiCmCallocate, must check */

    if (!AcpiTbSystemTablePointer (ObjDesc))
    {
        /* Attempt to delete the object (and all subobjects) */

        AcpiCmRemoveReference (ObjDesc);
    }

    return_VOID;
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsGetAttachedObject
 *
 * PARAMETERS:  Handle              - Handle of nte to be examined
 *
 * RETURN:      Current value of the object field from nte whose handle is passed
 *
 ***************************************************************************/

void *
AcpiNsGetAttachedObject (
    ACPI_HANDLE             Handle)
{
    FUNCTION_TRACE_PTR ("NsGetAttachedObject", Handle);


    if (!Handle)
    {
        /* handle invalid */

        REPORT_WARNING ("NsGetAttachedObject: Null handle");
        return_PTR (NULL);
    }

    return_PTR (((NAME_TABLE_ENTRY *) Handle)->Object);
}


/****************************************************************************
 * 
 * FUNCTION:    AcpiNsCompareObject
 *
 * PARAMETERS:  ObjHandle           - A namespace entry
 *              Level               - Current nesting level
 *              ObjDesc             - The value to be compared
 *
 * DESCRIPTION: A UserFunction called by AcpiNsWalkNamespace().  It performs
 *              a comparison for AcpiNsFindAttachedObject().  The comparison is against
 *              the value in the value field of the ObjHandle (an NTE).
 *              If a match is found, the handle is returned, which aborts
 *              AcpiNsWalkNamespace.
 *
 ***************************************************************************/

ACPI_STATUS
AcpiNsCompareObject (
    ACPI_HANDLE             ObjHandle, 
    UINT32                  Level, 
    void                    *ObjDesc,
    void                    **ReturnValue)
{

    if (((NAME_TABLE_ENTRY *) ObjHandle)->Object == ObjDesc)
    {
        DEBUG_PRINT (ACPI_INFO, ("NsCompareObject: match found, Obj %x Val %x\n",
                        ObjHandle, ((NAME_TABLE_ENTRY *) ObjHandle)->Object));

        if (ReturnValue)
        {
            *ReturnValue = ObjHandle;
        }

        return AE_CTRL_TERMINATE;        /* Stop the walk */
    }

    return AE_OK;   /* Not found, continue the walk */
}


/****************************************************************************
 *
 * FUNCTION:    AcpiNsFindAttachedObject
 *
 * PARAMETERS:  *ObjDesc            - Value to be found in ptrVal field.
 *              StartHandle         - Root of subtree to be searched, or
 *                                    NS_ALL to search the entire namespace
 *              MaxDepth            - Maximum depth of search.  Use INT_MAX
 *                                    for an effectively unlimited depth.
 *
 * DESCRIPTION: Traverse the name space until finding a name whose Value field
 *              matches the ObjDesc parameter, and return a handle to that
 *              name, or (ACPI_HANDLE)0 if none exists.
 *              if StartHandle is NS_ALL (null) search from the root,
 *              else it is a handle whose children are to be searched.
 *
 ***************************************************************************/

ACPI_HANDLE
AcpiNsFindAttachedObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc, 
    ACPI_HANDLE             StartHandle, 
    INT32                   MaxDepth)
{
    ACPI_HANDLE             RetObject;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("NsFindAttachedObject");


    /* Parameter validation */

    if (!ObjDesc)
    {
        return_PTR (NULL);
    }

    if (0 == MaxDepth)
    {
        return_PTR (NULL);
    }

    if (!Acpi_GblRootObject->Scope)
    {
        /* 
         * If the name space has not been initialized,
         * there surely are no matching values.
         */
        return_PTR (NULL);
    }

    if (NS_ALL == StartHandle)
    {
        StartHandle = Acpi_GblRootObject;
    }
    
    else
    {
        /* 
         * If base is not the root and has no children,
         * there is nothing to search.
         */
        return_PTR (NULL);
    }


    /* 
     * Walk namespace until a match is found.
     * Either the matching object is returned, or NULL in case
     * of no match.
     */
    Status = AcpiNsWalkNamespace (ACPI_TYPE_ANY, StartHandle, MaxDepth, NS_WALK_NO_UNLOCK, AcpiNsCompareObject, 
                                ObjDesc, &RetObject);
    if (ACPI_FAILURE (Status))
    {
        DEBUG_PRINT (ACPI_ERROR, ("NsFindAttachedObject: WalkNamespace failed! %x\n", Status));
        RetObject = NULL;
    }

    return_PTR (RetObject);
}




