
/******************************************************************************
 * 
 * Module Name: nsdump - table dumping routines for debug
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

#define __NSDUMP_C__

#include <acpi.h>
#include <interp.h>
#include <namesp.h>
#include <tables.h>


#define _COMPONENT          NAMESPACE
        MODULE_NAME         ("nsdump");



#ifdef ACPI_DEBUG

/****************************************************************************
 *
 * FUNCTION:    NsDumpPathname   
 *
 * PARAMETERS:  Handle              - Object
 *              Msg                 - Prefix message
 *              Level               - Desired debug level
 *              Component           - Caller's component ID
 *
 * DESCRIPTION: Print an object's full namespace pathname
 *              Manages allocation/freeing of a pathname buffer
 *
 ***************************************************************************/

ACPI_STATUS
NsDumpPathname (
    ACPI_HANDLE             Handle, 
    char                    *Msg, 
    UINT32                  Level, 
    UINT32                  Component)
{
    char                    *Buffer;
    UINT32                  Length;

    
    FUNCTION_TRACE ("NsDumpPathname");

    /* Do this only if the requested debug level and component are enabled */

    if (!(DebugLevel & Level) || !(DebugLayer & Component))
    {
        return_ACPI_STATUS (AE_OK);
    }

    Buffer = CmAllocate (PATHNAME_MAX);
    if (!Buffer)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Convert handle to a full pathname and print it (with supplied message) */

    Length = PATHNAME_MAX;
    if (ACPI_SUCCESS (NsHandleToPathname (Handle, &Length, Buffer)))
    {
        OsdPrintf ("%s %s (%p)\n", Msg, Buffer, Handle);
    }

    CmFree (Buffer);

    return_ACPI_STATUS (AE_OK);
}


/****************************************************************************
 *
 * FUNCTION:    NsDumpOneObject   
 *
 * PARAMETERS:  Handle              - Entry to be dumped
 *              Level               - Nesting level of the handle
 *              Context             - Passed into WalkNamespace
 *
 * DESCRIPTION: Dump a single nte
 *              This procedure is a UserFunction called by NsWalkNamespace.
 *
 ***************************************************************************/

ACPI_STATUS
NsDumpOneObject (
    ACPI_HANDLE             ObjHandle, 
    UINT32                  Level, 
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_WALK_INFO          *Info = (ACPI_WALK_INFO *) Context;
    NAME_TABLE_ENTRY        *Appendage = NULL;
    NAME_TABLE_ENTRY        *ThisEntry;
    UINT8                   *Value;
    ACPI_OBJECT_INTERNAL    *ObjDesc = NULL;
    ACPI_OBJECT_TYPE        ObjType;
    ACPI_OBJECT_TYPE        Type;
    UINT32                  BytesToDump;
    UINT32                  DownstreamSiblingMask = 0;
    INT32                   LevelTmp;
    UINT32                  WhichBit;
    UINT32                  Size = 0;


    ThisEntry = NsConvertHandleToEntry (ObjHandle);

    LevelTmp    = Level;
    Type        = ThisEntry->Type;
    WhichBit    = 1;


    if (!(DebugLevel & Info->DebugLevel))
    {
        return AE_OK;
    }
    
    if (!ObjHandle)
    {
        DEBUG_PRINT (ACPI_INFO, ("Null object handle\n"));
        return AE_OK;
    }

    /* Check if the owner matches */

    if ((Info->OwnerId != ACPI_UINT32_MAX) &&
        (Info->OwnerId != ThisEntry->OwnerId))
    {
        return AE_OK;
    }


    /* Indent the object according to the level */

    while (LevelTmp--)
    {

        /* Print appropriate characters to form tree structure */

        if (LevelTmp)
        {
            if (DownstreamSiblingMask & WhichBit)
            {    
                DEBUG_PRINT_RAW (TRACE_TABLES, ("|"));
            }

            else
            {
                DEBUG_PRINT_RAW (TRACE_TABLES, (" "));
            }
        
            WhichBit <<= 1;
        }
    
        else
        {
            if (NsExistDownstreamSibling (ThisEntry + 1, Size, Appendage))
            {
                DownstreamSiblingMask |= (1 << (Level - 1));
                DEBUG_PRINT_RAW (TRACE_TABLES, ("+"));
            }

            else
            {
                DownstreamSiblingMask &= 0xffffffff ^ (1 << (Level - 1));
                DEBUG_PRINT_RAW (TRACE_TABLES, ("+"));
            }

            if (ThisEntry->Scope == NULL)
            {
                DEBUG_PRINT_RAW (TRACE_TABLES, ("-"));
            }
        
            else if (NsExistDownstreamSibling (ThisEntry->Scope, NS_TABLE_SIZE,
                                                NEXTSEG (ThisEntry->Scope)))
            {
                DEBUG_PRINT_RAW (TRACE_TABLES, ("+"));
            }
        
            else
            {
                DEBUG_PRINT_RAW (TRACE_TABLES, ("-"));
            }
        }
    }


    /* Check the integrity of our data */

    if (Type > INTERNAL_TYPE_MAX)
    {
        Type = INTERNAL_TYPE_DefAny;                                 /* prints as *ERROR* */
    }
    
    if (!CmValidAcpiName (*(UINT32 *) &ThisEntry->Name))
    {
        REPORT_WARNING ("Invalid Name");
    }

    /*
     * Now we can print out the pertinent information
     */

    DEBUG_PRINT_RAW (TRACE_TABLES,
                (" %4.4s %-9s ", &ThisEntry->Name, CmGetTypeName (Type)));

    DEBUG_PRINT_RAW (TRACE_TABLES, ("%p S:%p O:%p",
                ThisEntry,
                ThisEntry->Scope, 
                ThisEntry->Object));


    if (!ThisEntry->Object)
    {
        /* No attached object, we are done */

        DEBUG_PRINT_RAW (TRACE_TABLES, ("\n"));
        return AE_OK;
    }

    switch (Type)
    {

    case ACPI_TYPE_Method:

        /* Name is a Method and its AML offset/length are set */
        
        DEBUG_PRINT_RAW (TRACE_TABLES, (" M:%p-%X\n",
                    ((ACPI_OBJECT_INTERNAL *) ThisEntry->Object)->Method.Pcode,
                    ((ACPI_OBJECT_INTERNAL *) ThisEntry->Object)->Method.PcodeLength));                

        break;
    

    case ACPI_TYPE_Number:
 
        DEBUG_PRINT_RAW (TRACE_TABLES, (" N:%X\n",
                    ((ACPI_OBJECT_INTERNAL *) ThisEntry->Object)->Number.Value));
        break;


    case ACPI_TYPE_String:

        DEBUG_PRINT_RAW (TRACE_TABLES, (" S:%p-%X\n",
                    ((ACPI_OBJECT_INTERNAL *) ThisEntry->Object)->String.Pointer,
                    ((ACPI_OBJECT_INTERNAL *) ThisEntry->Object)->String.Length));
        break;


    case ACPI_TYPE_Buffer:

        DEBUG_PRINT_RAW (TRACE_TABLES, (" B:%p-%X\n",
                    ((ACPI_OBJECT_INTERNAL *) ThisEntry->Object)->Buffer.Pointer,
                    ((ACPI_OBJECT_INTERNAL *) ThisEntry->Object)->Buffer.Length));
        break;


    default:

        DEBUG_PRINT_RAW (TRACE_TABLES, ("\n"));
        break;
    }
  
    /* If debug turned off, done */

    if (!(DebugLevel & TRACE_VALUES))
    {
        return AE_OK;
    }


    /* If there is an attached object, display it */

    Value = ThisEntry->Object;

    /* Dump attached objects */

    while (Value)
    {
        ObjType = INTERNAL_TYPE_Invalid;

        /* Decode the type of attached object and dump the contents */

        DEBUG_PRINT_RAW (TRACE_TABLES, ("        Attached Object %p: ", Value));

        if (TbSystemTablePointer (Value))
        {
            DEBUG_PRINT_RAW (TRACE_TABLES, ("(Ptr to AML Code)\n"));
            BytesToDump = 16;
        }

        else if (VALID_DESCRIPTOR_TYPE (Value, DESC_TYPE_NTE))
        {
            DEBUG_PRINT_RAW (TRACE_TABLES, ("(Ptr to Name Table Entry)\n"));
            BytesToDump = sizeof (NAME_TABLE_ENTRY);
        }


        else if (VALID_DESCRIPTOR_TYPE (Value, DESC_TYPE_ACPI_OBJ))
        {
            ObjDesc = (ACPI_OBJECT_INTERNAL *) Value;
            ObjType = ObjDesc->Common.Type;

            if (ObjType > INTERNAL_TYPE_MAX)
            {
                DEBUG_PRINT_RAW (TRACE_TABLES, ("(Ptr to ACPI Object type 0x%X [UNKNOWN])\n", ObjType));
                BytesToDump = 32;
            }

            else
            {
                DEBUG_PRINT_RAW (TRACE_TABLES, ("(Ptr to ACPI Object type 0x%X [%s])\n", 
                                    ObjType, CmGetTypeName (ObjType)));
                BytesToDump = ObjDesc->Common.Size;
            }
        }

        else
        {
            DEBUG_PRINT_RAW (TRACE_TABLES, ("(String or Buffer - not descriptor)\n", Value));
            BytesToDump = 16;
        }

        DUMP_BUFFER (Value, BytesToDump);

        /* If value is NOT an internal object, we are done */

        if ((TbSystemTablePointer (Value)) ||
            (VALID_DESCRIPTOR_TYPE (Value, DESC_TYPE_NTE)))
        {
            goto Cleanup;
        }

        /* 
         * Valid object, get the pointer to next level, if any
         */
        switch (ObjType)
        {
        case ACPI_TYPE_String:
            Value = (UINT8 *) ObjDesc->String.Pointer;
            break;

        case ACPI_TYPE_Buffer:
            Value = (UINT8 *) ObjDesc->Buffer.Pointer;
            break;

        case ACPI_TYPE_Package:
            Value = (UINT8 *) ObjDesc->Package.Elements;
            break;

        case ACPI_TYPE_Method:
            Value = (UINT8 *) ObjDesc->Method.Pcode;
            break;

        case ACPI_TYPE_FieldUnit:
            Value = (UINT8 *) ObjDesc->FieldUnit.Container;
            break;

        case INTERNAL_TYPE_DefField:
            Value = (UINT8 *) ObjDesc->Field.Container;
            break;

        case INTERNAL_TYPE_BankField:
            Value = (UINT8 *) ObjDesc->BankField.Container;
            break;

        case INTERNAL_TYPE_IndexField:
            Value = (UINT8 *) ObjDesc->IndexField.Index;
            break;

       default:
            goto Cleanup;
        }

        ObjType = INTERNAL_TYPE_Invalid;     /* Terminate loop after next pass */
    }

Cleanup:
    DEBUG_PRINT_RAW (TRACE_TABLES, ("\n"));
    return AE_OK;
}


/****************************************************************************
 *
 * FUNCTION:    NsDumpObjects 
 *
 * PARAMETERS:  Type                - Object type to be dumped
 *              MaxDepth            - Maximum depth of dump.  Use ACPI_UINT32_MAX
 *                                    for an effectively unlimited depth.
 *              OwnerId             - Dump only objects owned by this ID.  Use
 *                                    ACPI_UINT32_MAX to match all owners.
 *              StartHandle         - Where in namespace to start/end search
 *
 * DESCRIPTION: Dump typed objects within the loaded namespace.
 *              Uses NsWalkNamespace in conjunction with NsDumpOneObject.
 *
 ***************************************************************************/

void
NsDumpObjects (
    ACPI_OBJECT_TYPE        Type, 
    UINT32                  MaxDepth, 
    UINT32                  OwnerId,
    ACPI_HANDLE             StartHandle)
{
    ACPI_WALK_INFO          Info;


    Info.DebugLevel = TRACE_TABLES;
    Info.OwnerId = OwnerId;

    NsWalkNamespace (Type, StartHandle, MaxDepth, NS_WALK_NO_UNLOCK, NsDumpOneObject, 
                        (void *) &Info, NULL);
}


/****************************************************************************
 *
 * FUNCTION:    NsDumpOneDevice   
 *
 * PARAMETERS:  Handle              - Entry to be dumped
 *              Level               - Nesting level of the handle
 *              Context             - Passed into WalkNamespace
 *
 * DESCRIPTION: Dump a single nte that represents a device
 *              This procedure is a UserFunction called by NsWalkNamespace.
 *
 ***************************************************************************/

ACPI_STATUS
NsDumpOneDevice (
    ACPI_HANDLE             ObjHandle, 
    UINT32                  Level, 
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_DEVICE_INFO        Info;
    ACPI_STATUS             Status;
    UINT32                  i;


    Status = NsDumpOneObject (ObjHandle, Level, Context, ReturnValue);

    Status = AcpiGetObjectInfo (ObjHandle, &Info);
    if (ACPI_SUCCESS (Status))
    {
        for (i = 0; i < Level; i++)
        {
            DEBUG_PRINT_RAW (TRACE_TABLES, (" "));
        }

        DEBUG_PRINT_RAW (TRACE_TABLES, ("    HID: %.8X, ADR: %.8X, Status: %x\n",
                        Info.HardwareId, Info.Address, Info.CurrentStatus));

    }

    return Status;
}


/****************************************************************************
 *
 * FUNCTION:    NsDumpRootDevices   
 *
 * PARAMETERS:  None
 *
 * DESCRIPTION: Dump all objects of type "device"
 *
 ***************************************************************************/

void
NsDumpRootDevices (void)
{
    ACPI_HANDLE             SysBusHandle;


    /* Only dump the table if tracing is enabled */

    if (!(TRACE_TABLES & DebugLevel))
    {
        return;
    }

    AcpiGetHandle (0, NS_SYSTEM_BUS, &SysBusHandle);

    DEBUG_PRINT (TRACE_TABLES, ("Display of all devices in the namespace:\n"));
    NsWalkNamespace (ACPI_TYPE_Device, SysBusHandle, ACPI_INT32_MAX, NS_WALK_NO_UNLOCK, 
                        NsDumpOneDevice, NULL, NULL);
}


/****************************************************************************
 * 
 * FUNCTION:    NsDumpTables
 *
 * PARAMETERS:  SearchBase          - Root of subtree to be dumped, or
 *                                    NS_ALL to dump the entire namespace
 *              MaxDepth            - Maximum depth of dump.  Use INT_MAX
 *                                    for an effectively unlimited depth.
 *
 * DESCRIPTION: Dump the name space, or a portion of it.
 *
 ***************************************************************************/

void
NsDumpTables (
    ACPI_HANDLE             SearchBase, 
    INT32                   MaxDepth)
{
    ACPI_HANDLE             SearchHandle = SearchBase;


    FUNCTION_TRACE ("NsDumpTables");


    if (!Gbl_RootObject->Scope)
    {      
        /* 
         * If the name space has not been initialized,
         * there is nothing to dump.
         */
        DEBUG_PRINT (TRACE_TABLES, ("NsDumpTables: name space not initialized!\n"));
        return_VOID;
    }

    if (NS_ALL == SearchBase)
    {
        /*  entire namespace    */

        SearchHandle = Gbl_RootObject;
        DEBUG_PRINT (TRACE_TABLES, ("\\\n"));
    }


    NsDumpObjects (ACPI_TYPE_Any, MaxDepth, ACPI_UINT32_MAX, SearchHandle);
    return_VOID;
}


/****************************************************************************
 *
 * FUNCTION:    NsDumpEntry    
 *
 * PARAMETERS:  Handle              - Entry to be dumped
 *              DebugLevel          - Output level
 *
 * DESCRIPTION: Dump a single nte
 *
 ***************************************************************************/

void
NsDumpEntry (
    ACPI_HANDLE             Handle,
    UINT32                  DebugLevel)
{
    ACPI_WALK_INFO          Info;


    FUNCTION_TRACE_PTR ("NsDumpEntry", Handle);

    Info.DebugLevel = DebugLevel;
    Info.OwnerId = ACPI_UINT32_MAX;

    NsDumpOneObject (Handle, 1, &Info, NULL);
    
    DEBUG_PRINT (TRACE_EXEC, ("leave NsDumpEntry %p\n", Handle));
    return_VOID;
}

#endif
 
