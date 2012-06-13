/*******************************************************************************
 *
 * Module Name: dbexec - debugger control method execution
 *
 ******************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2012, Intel Corp.
 * All rights reserved.
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


#include "acpi.h"
#include "accommon.h"
#include "acdebug.h"
#include "acnamesp.h"

#ifdef ACPI_DEBUGGER

#define _COMPONENT          ACPI_CA_DEBUGGER
        ACPI_MODULE_NAME    ("dbexec")


static ACPI_DB_METHOD_INFO          AcpiGbl_DbMethodInfo;
#define DB_DEFAULT_PKG_ELEMENTS     33

/* Local prototypes */

static ACPI_STATUS
AcpiDbExecuteMethod (
    ACPI_DB_METHOD_INFO     *Info,
    ACPI_BUFFER             *ReturnObj);

static void
AcpiDbExecuteSetup (
    ACPI_DB_METHOD_INFO     *Info);

static UINT32
AcpiDbGetOutstandingAllocations (
    void);

static void ACPI_SYSTEM_XFACE
AcpiDbMethodThread (
    void                    *Context);

static ACPI_STATUS
AcpiDbExecutionWalk (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue);

static ACPI_STATUS
AcpiDbHexCharToValue (
    int                     HexChar,
    UINT8                   *ReturnValue);

static ACPI_STATUS
AcpiDbConvertToPackage (
    char                    *String,
    ACPI_OBJECT             *Object);

static ACPI_STATUS
AcpiDbConvertToObject (
    ACPI_OBJECT_TYPE        Type,
    char                    *String,
    ACPI_OBJECT             *Object);

static void
AcpiDbDeleteObjects (
    UINT32                  Count,
    ACPI_OBJECT             *Objects);


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbHexCharToValue
 *
 * PARAMETERS:  HexChar             - Ascii Hex digit, 0-9|a-f|A-F
 *              ReturnValue         - Where the converted value is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert a single hex character to a 4-bit number (0-16).
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiDbHexCharToValue (
    int                     HexChar,
    UINT8                   *ReturnValue)
{
    UINT8                   Value;


    /* Digit must be ascii [0-9a-fA-F] */

    if (!ACPI_IS_XDIGIT (HexChar))
    {
        return (AE_BAD_HEX_CONSTANT);
    }

    if (HexChar <= 0x39)
    {
        Value = (UINT8) (HexChar - 0x30);
    }
    else
    {
        Value = (UINT8) (ACPI_TOUPPER (HexChar) - 0x37);
    }

    *ReturnValue = Value;
    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbHexByteToBinary
 *
 * PARAMETERS:  HexByte             - Double hex digit (0x00 - 0xFF) in format:
 *                                    HiByte then LoByte.
 *              ReturnValue         - Where the converted value is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert two hex characters to an 8 bit number (0 - 255).
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiDbHexByteToBinary (
    char                    *HexByte,
    UINT8                   *ReturnValue)
{
    UINT8                   Local0;
    UINT8                   Local1;
    ACPI_STATUS             Status;


    /* High byte */

    Status = AcpiDbHexCharToValue (HexByte[0], &Local0);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* Low byte */

    Status = AcpiDbHexCharToValue (HexByte[1], &Local1);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    *ReturnValue = (UINT8) ((Local0 << 4) | Local1);
    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbConvertToBuffer
 *
 * PARAMETERS:  String              - Input string to be converted
 *              Object              - Where the buffer object is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert a string to a buffer object. String is treated a list
 *              of buffer elements, each separated by a space or comma.
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiDbConvertToBuffer (
    char                    *String,
    ACPI_OBJECT             *Object)
{
    UINT32                  i;
    UINT32                  j;
    UINT32                  Length;
    UINT8                   *Buffer;
    ACPI_STATUS             Status;


    /* Generate the final buffer length */

    for (i = 0, Length = 0; String[i];)
    {
        i+=2;
        Length++;

        while (String[i] &&
              ((String[i] == ',') || (String[i] == ' ')))
        {
            i++;
        }
    }

    Buffer = ACPI_ALLOCATE (Length);
    if (!Buffer)
    {
        return (AE_NO_MEMORY);
    }

    /* Convert the command line bytes to the buffer */

    for (i = 0, j = 0; String[i];)
    {
        Status = AcpiDbHexByteToBinary (&String[i], &Buffer[j]);
        if (ACPI_FAILURE (Status))
        {
            ACPI_FREE (Buffer);
            return (Status);
        }

        j++;
        i+=2;
        while (String[i] &&
              ((String[i] == ',') || (String[i] == ' ')))
        {
            i++;
        }
    }

    Object->Type = ACPI_TYPE_BUFFER;
    Object->Buffer.Pointer = Buffer;
    Object->Buffer.Length = Length;
    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbConvertToPackage
 *
 * PARAMETERS:  String              - Input string to be converted
 *              Object              - Where the package object is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert a string to a package object. Handles nested packages
 *              via recursion with AcpiDbConvertToObject.
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiDbConvertToPackage (
    char                    *String,
    ACPI_OBJECT             *Object)
{
    char                    *This;
    char                    *Next;
    UINT32                  i;
    ACPI_OBJECT_TYPE        Type;
    ACPI_OBJECT             *Elements;
    ACPI_STATUS             Status;


    Elements = ACPI_ALLOCATE_ZEROED (
        DB_DEFAULT_PKG_ELEMENTS * sizeof (ACPI_OBJECT));

    This = String;
    for (i = 0; i < (DB_DEFAULT_PKG_ELEMENTS - 1); i++)
    {
        This = AcpiDbGetNextToken (This, &Next, &Type);
        if (!This)
        {
            break;
        }

        /* Recursive call to convert each package element */

        Status = AcpiDbConvertToObject (Type, This, &Elements[i]);
        if (ACPI_FAILURE (Status))
        {
            AcpiDbDeleteObjects (i + 1, Elements);
            ACPI_FREE (Elements);
            return (Status);
        }

        This = Next;
    }

    Object->Type = ACPI_TYPE_PACKAGE;
    Object->Package.Count = i;
    Object->Package.Elements = Elements;
    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbConvertToObject
 *
 * PARAMETERS:  Type                - Object type as determined by parser
 *              String              - Input string to be converted
 *              Object              - Where the new object is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert a typed and tokenized string to an ACPI_OBJECT. Typing:
 *              1) String objects were surrounded by quotes.
 *              2) Buffer objects were surrounded by parentheses.
 *              3) Package objects were surrounded by brackets "[]".
 *              4) All standalone tokens are treated as integers.
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiDbConvertToObject (
    ACPI_OBJECT_TYPE        Type,
    char                    *String,
    ACPI_OBJECT             *Object)
{
    ACPI_STATUS             Status = AE_OK;


    switch (Type)
    {
    case ACPI_TYPE_STRING:
        Object->Type = ACPI_TYPE_STRING;
        Object->String.Pointer = String;
        Object->String.Length = (UINT32) ACPI_STRLEN (String);
        break;

    case ACPI_TYPE_BUFFER:
        Status = AcpiDbConvertToBuffer (String, Object);
        break;

    case ACPI_TYPE_PACKAGE:
        Status = AcpiDbConvertToPackage (String, Object);
        break;

    default:
        Object->Type = ACPI_TYPE_INTEGER;
        Status = AcpiUtStrtoul64 (String, 16, &Object->Integer.Value);
        break;
    }

    return (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbDeleteObjects
 *
 * PARAMETERS:  Count               - Count of objects in the list
 *              Objects             - Array of ACPI_OBJECTs to be deleted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete a list of ACPI_OBJECTS. Handles packages and nested
 *              packages via recursion.
 *
 ******************************************************************************/

static void
AcpiDbDeleteObjects (
    UINT32                  Count,
    ACPI_OBJECT             *Objects)
{
    UINT32                  i;


    for (i = 0; i < Count; i++)
    {
        switch (Objects[i].Type)
        {
        case ACPI_TYPE_BUFFER:
            ACPI_FREE (Objects[i].Buffer.Pointer);
            break;

        case ACPI_TYPE_PACKAGE:

            /* Recursive call to delete package elements */

            AcpiDbDeleteObjects (Objects[i].Package.Count,
                Objects[i].Package.Elements);

            /* Free the elements array */

            ACPI_FREE (Objects[i].Package.Elements);
            break;

        default:
            break;
        }
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbExecuteMethod
 *
 * PARAMETERS:  Info            - Valid info segment
 *              ReturnObj       - Where to put return object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a control method.
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiDbExecuteMethod (
    ACPI_DB_METHOD_INFO     *Info,
    ACPI_BUFFER             *ReturnObj)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_LIST        ParamObjects;
    ACPI_OBJECT             Params[ACPI_METHOD_NUM_ARGS];
    ACPI_HANDLE             Handle;
    ACPI_DEVICE_INFO        *ObjInfo;
    UINT32                  i;


    ACPI_FUNCTION_TRACE (DbExecuteMethod);


    if (AcpiGbl_DbOutputToFile && !AcpiDbgLevel)
    {
        AcpiOsPrintf ("Warning: debug output is not enabled!\n");
    }

    /* Get the NS node, determines existence also */

    Status = AcpiGetHandle (NULL, Info->Pathname, &Handle);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Get the object info for number of method parameters */

    Status = AcpiGetObjectInfo (Handle, &ObjInfo);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    ParamObjects.Pointer = NULL;
    ParamObjects.Count   = 0;

    if (ObjInfo->Type == ACPI_TYPE_METHOD)
    {
        /* Are there arguments to the method? */

        i = 0;
        if (Info->Args && Info->Args[0])
        {
            /* Get arguments passed on the command line */

            for (; Info->Args[i] &&
                (i < ACPI_METHOD_NUM_ARGS) &&
                (i < ObjInfo->ParamCount);
                i++)
            {
                /* Convert input string (token) to an actual ACPI_OBJECT */

                Status = AcpiDbConvertToObject (Info->Types[i],
                    Info->Args[i], &Params[i]);
                if (ACPI_FAILURE (Status))
                {
                    ACPI_EXCEPTION ((AE_INFO, Status,
                        "While parsing method arguments"));
                    goto Cleanup;
                }
            }
        }

        /* Create additional "default" parameters as needed */

        if (i < ObjInfo->ParamCount)
        {
            AcpiOsPrintf ("Adding %u arguments containing default values\n",
                ObjInfo->ParamCount - i);

            for (; i < ObjInfo->ParamCount; i++)
            {
                switch (i)
                {
                case 0:

                    Params[0].Type           = ACPI_TYPE_INTEGER;
                    Params[0].Integer.Value  = 0x01020304;
                    break;

                case 1:

                    Params[1].Type           = ACPI_TYPE_STRING;
                    Params[1].String.Length  = 12;
                    Params[1].String.Pointer = "AML Debugger";
                    break;

                default:

                    Params[i].Type           = ACPI_TYPE_INTEGER;
                    Params[i].Integer.Value  = i * (UINT64) 0x1000;
                    break;
                }
            }
        }

        ParamObjects.Count = ObjInfo->ParamCount;
        ParamObjects.Pointer = Params;
    }

    /* Prepare for a return object of arbitrary size */

    ReturnObj->Pointer = AcpiGbl_DbBuffer;
    ReturnObj->Length  = ACPI_DEBUG_BUFFER_SIZE;

    /* Do the actual method execution */

    AcpiGbl_MethodExecuting = TRUE;
    Status = AcpiEvaluateObject (NULL,
        Info->Pathname, &ParamObjects, ReturnObj);

    AcpiGbl_CmSingleStep = FALSE;
    AcpiGbl_MethodExecuting = FALSE;

    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "while executing %s from debugger", Info->Pathname));

        if (Status == AE_BUFFER_OVERFLOW)
        {
            ACPI_ERROR ((AE_INFO,
                "Possible overflow of internal debugger buffer (size 0x%X needed 0x%X)",
                ACPI_DEBUG_BUFFER_SIZE, (UINT32) ReturnObj->Length));
        }
    }

Cleanup:
    AcpiDbDeleteObjects (ObjInfo->ParamCount, Params);
    ACPI_FREE (ObjInfo);

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbExecuteSetup
 *
 * PARAMETERS:  Info            - Valid method info
 *
 * RETURN:      None
 *
 * DESCRIPTION: Setup info segment prior to method execution
 *
 ******************************************************************************/

static void
AcpiDbExecuteSetup (
    ACPI_DB_METHOD_INFO     *Info)
{

    /* Catenate the current scope to the supplied name */

    Info->Pathname[0] = 0;
    if ((Info->Name[0] != '\\') &&
        (Info->Name[0] != '/'))
    {
        ACPI_STRCAT (Info->Pathname, AcpiGbl_DbScopeBuf);
    }

    ACPI_STRCAT (Info->Pathname, Info->Name);
    AcpiDbPrepNamestring (Info->Pathname);

    AcpiDbSetOutputDestination (ACPI_DB_DUPLICATE_OUTPUT);
    AcpiOsPrintf ("Executing %s\n", Info->Pathname);

    if (Info->Flags & EX_SINGLE_STEP)
    {
        AcpiGbl_CmSingleStep = TRUE;
        AcpiDbSetOutputDestination (ACPI_DB_CONSOLE_OUTPUT);
    }

    else
    {
        /* No single step, allow redirection to a file */

        AcpiDbSetOutputDestination (ACPI_DB_REDIRECTABLE_OUTPUT);
    }
}


#ifdef ACPI_DBG_TRACK_ALLOCATIONS
UINT32
AcpiDbGetCacheInfo (
    ACPI_MEMORY_LIST        *Cache)
{

    return (Cache->TotalAllocated - Cache->TotalFreed - Cache->CurrentDepth);
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    AcpiDbGetOutstandingAllocations
 *
 * PARAMETERS:  None
 *
 * RETURN:      Current global allocation count minus cache entries
 *
 * DESCRIPTION: Determine the current number of "outstanding" allocations --
 *              those allocations that have not been freed and also are not
 *              in one of the various object caches.
 *
 ******************************************************************************/

static UINT32
AcpiDbGetOutstandingAllocations (
    void)
{
    UINT32                  Outstanding = 0;

#ifdef ACPI_DBG_TRACK_ALLOCATIONS

    Outstanding += AcpiDbGetCacheInfo (AcpiGbl_StateCache);
    Outstanding += AcpiDbGetCacheInfo (AcpiGbl_PsNodeCache);
    Outstanding += AcpiDbGetCacheInfo (AcpiGbl_PsNodeExtCache);
    Outstanding += AcpiDbGetCacheInfo (AcpiGbl_OperandCache);
#endif

    return (Outstanding);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbExecutionWalk
 *
 * PARAMETERS:  WALK_CALLBACK
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a control method.  Name is relative to the current
 *              scope.
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiDbExecutionWalk (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_NAMESPACE_NODE     *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;
    ACPI_BUFFER             ReturnObj;
    ACPI_STATUS             Status;


    ObjDesc = AcpiNsGetAttachedObject (Node);
    if (ObjDesc->Method.ParamCount)
    {
        return (AE_OK);
    }

    ReturnObj.Pointer = NULL;
    ReturnObj.Length = ACPI_ALLOCATE_BUFFER;

    AcpiNsPrintNodePathname (Node, "Execute");

    /* Do the actual method execution */

    AcpiOsPrintf ("\n");
    AcpiGbl_MethodExecuting = TRUE;

    Status = AcpiEvaluateObject (Node, NULL, NULL, &ReturnObj);

    AcpiOsPrintf ("[%4.4s] returned %s\n", AcpiUtGetNodeName (Node),
            AcpiFormatException (Status));
    AcpiGbl_MethodExecuting = FALSE;

    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbExecute
 *
 * PARAMETERS:  Name                - Name of method to execute
 *              Args                - Parameters to the method
 *              Flags               - single step/no single step
 *
 * RETURN:      None
 *
 * DESCRIPTION: Execute a control method.  Name is relative to the current
 *              scope.
 *
 ******************************************************************************/

void
AcpiDbExecute (
    char                    *Name,
    char                    **Args,
    ACPI_OBJECT_TYPE        *Types,
    UINT32                  Flags)
{
    ACPI_STATUS             Status;
    ACPI_BUFFER             ReturnObj;
    char                    *NameString;


#ifdef ACPI_DEBUG_OUTPUT
    UINT32                  PreviousAllocations;
    UINT32                  Allocations;


    /* Memory allocation tracking */

    PreviousAllocations = AcpiDbGetOutstandingAllocations ();
#endif

    if (*Name == '*')
    {
        (void) AcpiWalkNamespace (ACPI_TYPE_METHOD, ACPI_ROOT_OBJECT,
                    ACPI_UINT32_MAX, AcpiDbExecutionWalk, NULL, NULL, NULL);
        return;
    }
    else
    {
        NameString = ACPI_ALLOCATE (ACPI_STRLEN (Name) + 1);
        if (!NameString)
        {
            return;
        }

        ACPI_MEMSET (&AcpiGbl_DbMethodInfo, 0, sizeof (ACPI_DB_METHOD_INFO));

        ACPI_STRCPY (NameString, Name);
        AcpiUtStrupr (NameString);
        AcpiGbl_DbMethodInfo.Name = NameString;
        AcpiGbl_DbMethodInfo.Args = Args;
        AcpiGbl_DbMethodInfo.Types = Types;
        AcpiGbl_DbMethodInfo.Flags = Flags;

        ReturnObj.Pointer = NULL;
        ReturnObj.Length = ACPI_ALLOCATE_BUFFER;

        AcpiDbExecuteSetup (&AcpiGbl_DbMethodInfo);
        Status = AcpiDbExecuteMethod (&AcpiGbl_DbMethodInfo, &ReturnObj);
        ACPI_FREE (NameString);
    }

    /*
     * Allow any handlers in separate threads to complete.
     * (Such as Notify handlers invoked from AML executed above).
     */
    AcpiOsSleep ((UINT64) 10);


#ifdef ACPI_DEBUG_OUTPUT

    /* Memory allocation tracking */

    Allocations = AcpiDbGetOutstandingAllocations () - PreviousAllocations;

    AcpiDbSetOutputDestination (ACPI_DB_DUPLICATE_OUTPUT);

    if (Allocations > 0)
    {
        AcpiOsPrintf ("Outstanding: 0x%X allocations after execution\n",
                        Allocations);
    }
#endif

    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Execution of %s failed with status %s\n",
            AcpiGbl_DbMethodInfo.Pathname, AcpiFormatException (Status));
    }
    else
    {
        /* Display a return object, if any */

        if (ReturnObj.Length)
        {
            AcpiOsPrintf ("Execution of %s returned object %p Buflen %X\n",
                AcpiGbl_DbMethodInfo.Pathname, ReturnObj.Pointer,
                (UINT32) ReturnObj.Length);
            AcpiDbDumpExternalObject (ReturnObj.Pointer, 1);
        }
        else
        {
            AcpiOsPrintf ("No return object from execution of %s\n",
                AcpiGbl_DbMethodInfo.Pathname);
        }
    }

    AcpiDbSetOutputDestination (ACPI_DB_CONSOLE_OUTPUT);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbMethodThread
 *
 * PARAMETERS:  Context             - Execution info segment
 *
 * RETURN:      None
 *
 * DESCRIPTION: Debugger execute thread.  Waits for a command line, then
 *              simply dispatches it.
 *
 ******************************************************************************/

static void ACPI_SYSTEM_XFACE
AcpiDbMethodThread (
    void                    *Context)
{
    ACPI_STATUS             Status;
    ACPI_DB_METHOD_INFO     *Info = Context;
    ACPI_DB_METHOD_INFO     LocalInfo;
    UINT32                  i;
    UINT8                   Allow;
    ACPI_BUFFER             ReturnObj;


    /*
     * AcpiGbl_DbMethodInfo.Arguments will be passed as method arguments.
     * Prevent AcpiGbl_DbMethodInfo from being modified by multiple threads
     * concurrently.
     *
     * Note: The arguments we are passing are used by the ASL test suite
     * (aslts). Do not change them without updating the tests.
     */
    (void) AcpiOsWaitSemaphore (Info->InfoGate, 1, ACPI_WAIT_FOREVER);

    if (Info->InitArgs)
    {
        AcpiDbUint32ToHexString (Info->NumCreated, Info->IndexOfThreadStr);
        AcpiDbUint32ToHexString ((UINT32) AcpiOsGetThreadId (), Info->IdOfThreadStr);
    }

    if (Info->Threads && (Info->NumCreated < Info->NumThreads))
    {
        Info->Threads[Info->NumCreated++] = AcpiOsGetThreadId();
    }

    LocalInfo = *Info;
    LocalInfo.Args = LocalInfo.Arguments;
    LocalInfo.Arguments[0] = LocalInfo.NumThreadsStr;
    LocalInfo.Arguments[1] = LocalInfo.IdOfThreadStr;
    LocalInfo.Arguments[2] = LocalInfo.IndexOfThreadStr;
    LocalInfo.Arguments[3] = NULL;

    LocalInfo.Types = LocalInfo.ArgTypes;

    (void) AcpiOsSignalSemaphore (Info->InfoGate, 1);

    for (i = 0; i < Info->NumLoops; i++)
    {
        Status = AcpiDbExecuteMethod (&LocalInfo, &ReturnObj);
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("%s During execution of %s at iteration %X\n",
                AcpiFormatException (Status), Info->Pathname, i);
            if (Status == AE_ABORT_METHOD)
            {
                break;
            }
        }

#if 0
        if ((i % 100) == 0)
        {
            AcpiOsPrintf ("%u executions, Thread 0x%x\n", i, AcpiOsGetThreadId ());
        }

        if (ReturnObj.Length)
        {
            AcpiOsPrintf ("Execution of %s returned object %p Buflen %X\n",
                Info->Pathname, ReturnObj.Pointer, (UINT32) ReturnObj.Length);
            AcpiDbDumpExternalObject (ReturnObj.Pointer, 1);
        }
#endif
    }

    /* Signal our completion */

    Allow = 0;
    (void) AcpiOsWaitSemaphore (Info->ThreadCompleteGate, 1, ACPI_WAIT_FOREVER);
    Info->NumCompleted++;

    if (Info->NumCompleted == Info->NumThreads)
    {
        /* Do signal for main thread once only */
        Allow = 1;
    }

    (void) AcpiOsSignalSemaphore (Info->ThreadCompleteGate, 1);

    if (Allow)
    {
        Status = AcpiOsSignalSemaphore (Info->MainThreadGate, 1);
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("Could not signal debugger thread sync semaphore, %s\n",
                AcpiFormatException (Status));
        }
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDbCreateExecutionThreads
 *
 * PARAMETERS:  NumThreadsArg           - Number of threads to create
 *              NumLoopsArg             - Loop count for the thread(s)
 *              MethodNameArg           - Control method to execute
 *
 * RETURN:      None
 *
 * DESCRIPTION: Create threads to execute method(s)
 *
 ******************************************************************************/

void
AcpiDbCreateExecutionThreads (
    char                    *NumThreadsArg,
    char                    *NumLoopsArg,
    char                    *MethodNameArg)
{
    ACPI_STATUS             Status;
    UINT32                  NumThreads;
    UINT32                  NumLoops;
    UINT32                  i;
    UINT32                  Size;
    ACPI_MUTEX              MainThreadGate;
    ACPI_MUTEX              ThreadCompleteGate;
    ACPI_MUTEX              InfoGate;


    /* Get the arguments */

    NumThreads = ACPI_STRTOUL (NumThreadsArg, NULL, 0);
    NumLoops   = ACPI_STRTOUL (NumLoopsArg, NULL, 0);

    if (!NumThreads || !NumLoops)
    {
        AcpiOsPrintf ("Bad argument: Threads %X, Loops %X\n",
            NumThreads, NumLoops);
        return;
    }

    /*
     * Create the semaphore for synchronization of
     * the created threads with the main thread.
     */
    Status = AcpiOsCreateSemaphore (1, 0, &MainThreadGate);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not create semaphore for synchronization with the main thread, %s\n",
            AcpiFormatException (Status));
        return;
    }

    /*
     * Create the semaphore for synchronization
     * between the created threads.
     */
    Status = AcpiOsCreateSemaphore (1, 1, &ThreadCompleteGate);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not create semaphore for synchronization between the created threads, %s\n",
            AcpiFormatException (Status));
        (void) AcpiOsDeleteSemaphore (MainThreadGate);
        return;
    }

    Status = AcpiOsCreateSemaphore (1, 1, &InfoGate);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not create semaphore for synchronization of AcpiGbl_DbMethodInfo, %s\n",
            AcpiFormatException (Status));
        (void) AcpiOsDeleteSemaphore (ThreadCompleteGate);
        (void) AcpiOsDeleteSemaphore (MainThreadGate);
        return;
    }

    ACPI_MEMSET (&AcpiGbl_DbMethodInfo, 0, sizeof (ACPI_DB_METHOD_INFO));

    /* Array to store IDs of threads */

    AcpiGbl_DbMethodInfo.NumThreads = NumThreads;
    Size = sizeof (ACPI_THREAD_ID) * AcpiGbl_DbMethodInfo.NumThreads;
    AcpiGbl_DbMethodInfo.Threads = AcpiOsAllocate (Size);
    if (AcpiGbl_DbMethodInfo.Threads == NULL)
    {
        AcpiOsPrintf ("No memory for thread IDs array\n");
        (void) AcpiOsDeleteSemaphore (MainThreadGate);
        (void) AcpiOsDeleteSemaphore (ThreadCompleteGate);
        (void) AcpiOsDeleteSemaphore (InfoGate);
        return;
    }
    ACPI_MEMSET (AcpiGbl_DbMethodInfo.Threads, 0, Size);

    /* Setup the context to be passed to each thread */

    AcpiGbl_DbMethodInfo.Name = MethodNameArg;
    AcpiGbl_DbMethodInfo.Flags = 0;
    AcpiGbl_DbMethodInfo.NumLoops = NumLoops;
    AcpiGbl_DbMethodInfo.MainThreadGate = MainThreadGate;
    AcpiGbl_DbMethodInfo.ThreadCompleteGate = ThreadCompleteGate;
    AcpiGbl_DbMethodInfo.InfoGate = InfoGate;

    /* Init arguments to be passed to method */

    AcpiGbl_DbMethodInfo.InitArgs = 1;
    AcpiGbl_DbMethodInfo.Args = AcpiGbl_DbMethodInfo.Arguments;
    AcpiGbl_DbMethodInfo.Arguments[0] = AcpiGbl_DbMethodInfo.NumThreadsStr;
    AcpiGbl_DbMethodInfo.Arguments[1] = AcpiGbl_DbMethodInfo.IdOfThreadStr;
    AcpiGbl_DbMethodInfo.Arguments[2] = AcpiGbl_DbMethodInfo.IndexOfThreadStr;
    AcpiGbl_DbMethodInfo.Arguments[3] = NULL;

    AcpiGbl_DbMethodInfo.Types = AcpiGbl_DbMethodInfo.ArgTypes;
    AcpiGbl_DbMethodInfo.ArgTypes[0] = ACPI_TYPE_INTEGER;
    AcpiGbl_DbMethodInfo.ArgTypes[1] = ACPI_TYPE_INTEGER;
    AcpiGbl_DbMethodInfo.ArgTypes[2] = ACPI_TYPE_INTEGER;

    AcpiDbUint32ToHexString (NumThreads, AcpiGbl_DbMethodInfo.NumThreadsStr);

    AcpiDbExecuteSetup (&AcpiGbl_DbMethodInfo);

    /* Create the threads */

    AcpiOsPrintf ("Creating %X threads to execute %X times each\n",
        NumThreads, NumLoops);

    for (i = 0; i < (NumThreads); i++)
    {
        Status = AcpiOsExecute (OSL_DEBUGGER_THREAD, AcpiDbMethodThread,
            &AcpiGbl_DbMethodInfo);
        if (ACPI_FAILURE (Status))
        {
            break;
        }
    }

    /* Wait for all threads to complete */

    (void) AcpiOsWaitSemaphore (MainThreadGate, 1, ACPI_WAIT_FOREVER);

    AcpiDbSetOutputDestination (ACPI_DB_DUPLICATE_OUTPUT);
    AcpiOsPrintf ("All threads (%X) have completed\n", NumThreads);
    AcpiDbSetOutputDestination (ACPI_DB_CONSOLE_OUTPUT);

    /* Cleanup and exit */

    (void) AcpiOsDeleteSemaphore (MainThreadGate);
    (void) AcpiOsDeleteSemaphore (ThreadCompleteGate);
    (void) AcpiOsDeleteSemaphore (InfoGate);

    AcpiOsFree (AcpiGbl_DbMethodInfo.Threads);
    AcpiGbl_DbMethodInfo.Threads = NULL;
}

#endif /* ACPI_DEBUGGER */


