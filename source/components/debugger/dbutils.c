/******************************************************************************
 * 
 * Module Name: dbutils - AML debugger utilities
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


#include <acpi.h>
#include <parser.h>
#include <amlcode.h>
#include <namesp.h>
#include <parser.h>
#include <events.h>
#include <interp.h>
#include <debugger.h>


#ifdef ACPI_DEBUG

#define _COMPONENT          DEBUGGER
        MODULE_NAME         ("dbutils");


/******************************************************************************
 * 
 * FUNCTION:    DbSetOutputDestination
 *
 * PARAMETERS:  Address             - Pointer to the buffer
 *
 * RETURN:      None
 *
 * DESCRIPTION: Print a portion of a buffer
 *
 *****************************************************************************/

void
DbSetOutputDestination (
    INT32                   OutputFlags)
{
    
    Gbl_DbOutputFlags = (UINT8) OutputFlags;

    if (OutputFlags & DB_REDIRECTABLE_OUTPUT)
    {
        if (OutputToFile)
        {
            DebugLevel = Gbl_DbDebugLevel;
        }
    }
    else
    {
        DebugLevel = Gbl_DbConsoleDebugLevel;
    }
}

/******************************************************************************
 * 
 * FUNCTION:    DbDumpBuffer 
 *
 * PARAMETERS:  Address             - Pointer to the buffer
 *
 * RETURN:      None
 *
 * DESCRIPTION: Print a portion of a buffer
 *
 *****************************************************************************/

void
DbDumpBuffer (
    UINT32                  Address)
{

    OsdPrintf ("\nLocation 0x%X:\n", Address);

    DebugLevel |= TRACE_TABLES;
    CmDumpBuffer ((char *) Address, 64, DB_BYTE_DISPLAY, ACPI_UINT32_MAX);
}


/******************************************************************************
 * 
 * FUNCTION:    DbDumpObject
 *
 * PARAMETERS:  MethodName          - Method that returned the object
 *              ReturnObj           - The object to dump
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump the contents of an ACPI external object
 *
 *****************************************************************************/

void
DbDumpObject (
    ACPI_OBJECT             *ObjDesc,
    UINT32                  Level)
{
    UINT32                  i;


    if (!ObjDesc)
    {
        return;
    }

    for (i = 0; i < Level; i++)
    {
        OsdPrintf ("  ");
    }

    switch (ObjDesc->Type)
    {
    case ACPI_TYPE_Any:
        OsdPrintf ("[Object Reference]  Value: %p\n", ObjDesc->Reference.Handle);
        break;

    case ACPI_TYPE_Number:
        OsdPrintf ("[Number]  Value: %ld (0x%lX)\n", ObjDesc->Number.Value, ObjDesc->Number.Value);
        break;

    case ACPI_TYPE_String:
        OsdPrintf ("[String]  Value: ");
        for (i = 0; i < ObjDesc->String.Length; i++)
        {
            OsdPrintf ("%c", ObjDesc->String.Pointer[i]);
        }
        OsdPrintf ("\n");
        break;

    case ACPI_TYPE_Buffer:
        OsdPrintf ("[Buffer]  Value: ");
        CmDumpBuffer ((char *) ObjDesc->Buffer.Pointer, ObjDesc->Buffer.Length, DB_DWORD_DISPLAY, _COMPONENT);
        break;

    case ACPI_TYPE_Package:
        OsdPrintf ("[Package]  Contains %d Elements: \n", ObjDesc->Package.Count);

        for (i = 0; i < ObjDesc->Package.Count; i++)
        {
            DbDumpObject (&ObjDesc->Package.Elements[i], Level+1);
        }
        break;

    default:
        OsdPrintf ("[Unknown Type] 0x%X \n", ObjDesc->Type);
        break;
    }
}



/******************************************************************************
 * 
 * FUNCTION:    DbPrepNamestring
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Translate all forward slashes and dots to backslashes.
 *
 *****************************************************************************/

void
DbPrepNamestring (
    char                    *Name)
{


    if (!Name)
    {
        return;
    }

    /* Convert a leading forward slash to a backslash */

    if (*Name == '/')
    {
        *Name = '\\';
    }

    /* Ignore a leading backslash, this is the root prefix */

    if (*Name == '\\')
    {
        *Name++;
    }

    /* Convert all slash path separators to dots */

    while (*Name)
    {
        if ((*Name == '/') ||
            (*Name == '\\'))
        {
            *Name = '.';
        }

        Name++;
    }
}


/******************************************************************************
 * 
 * FUNCTION:    AdSecondPassParse
 *
 * PARAMETERS:  Root            - Root of the parse tree
 *
 * RETURN:      None
 *
 * DESCRIPTION: Need to wait until second pass to parse the control methods
 *
 *****************************************************************************/

ACPI_STATUS
DbSecondPassParse (
    ACPI_GENERIC_OP         *Root)
{
    ACPI_GENERIC_OP         *Op = Root;
    ACPI_DEFERRED_OP        *Method;
    ACPI_GENERIC_OP         *SearchOp;
    ACPI_GENERIC_OP         *StartOp;
    ACPI_STATUS             Status = AE_OK;
    UINT32                  BaseAmlOffset;


    OsdPrintf ("Pass two parse ....\n");

    while (Op)
    {
        if (Op->Opcode == AML_MethodOp)
        {
            Method = (ACPI_DEFERRED_OP *) Op;
            Status = PsParseAml (Op, Method->Body, Method->BodyLength);

          
            BaseAmlOffset = (Method->Value.Arg)->AmlOffset + 1;
            StartOp = (Method->Value.Arg)->Next;
            SearchOp = StartOp;

            while (SearchOp)
            {
                SearchOp->AmlOffset += BaseAmlOffset;
                SearchOp = PsGetDepthNext (StartOp, SearchOp);
            }

        }

        if (Op->Opcode == AML_RegionOp)
        {
            /* TBD: this isn't quite the right thing to do! */

            // Method = (ACPI_DEFERRED_OP *) Op;
            // Status = PsParseAml (Op, Method->Body, Method->BodyLength);
        }

        if (ACPI_FAILURE (Status))
        {
            return Status;
        }

        Op = PsGetDepthNext (Root, Op);
    }

    return Status;
}


/******************************************************************************
 * 
 * FUNCTION:    DbLocalNsLookup
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Lookup a name in the ACPI namespace
 *
 *****************************************************************************/

NAME_TABLE_ENTRY *
DbLocalNsLookup (
    char                    *Name)
{
    char                    *InternalPath;
    ACPI_STATUS             Status;
    NAME_TABLE_ENTRY        *Entry = NULL;


    DbPrepNamestring (Name);

    /* Build an internal namestring */

    Status = NsInternalizeName (Name, &InternalPath);
    if (ACPI_FAILURE (Status))
    {
        OsdPrintf ("Invalid namestring: %s\n", Name);
        return NULL;
    }

    /* Lookup the name */

    /* TBD: what scope do we use? */
    /* Use the root scope for the start of the search */

    Status = NsLookup (NULL, InternalPath, ACPI_TYPE_Any, IMODE_Execute, 
                                    NS_NO_UPSEARCH | NS_DONT_OPEN_SCOPE, NULL, &Entry);

    if (ACPI_FAILURE (Status))
    {
        OsdPrintf ("Could not locate name: %s %s\n", Name, CmFormatException (Status));
    }


    CmFree (InternalPath);

    return Entry;
}




#endif /* ACPI_DEBUG */


