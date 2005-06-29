/******************************************************************************
 *
 * Module Name: dbdisply - debug display commands
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


#include "acpi.h"
#include "acparser.h"
#include "amlcode.h"
#include "acdispat.h"
#include "acnamesp.h"
#include "acparser.h"
#include "acevents.h"
#include "acinterp.h"
#include "acdebug.h"


#ifdef ENABLE_DEBUGGER


#define _COMPONENT          DEBUGGER
        MODULE_NAME         ("dbdisply");


/******************************************************************************
 *
 * FUNCTION:    AcpiDbGetPointer
 *
 * PARAMETERS:  Target          - Pointer to string to be converted
 *
 * RETURN:      Converted pointer
 *
 * DESCRIPTION: Convert an ascii pointer value to a real value
 *
 *****************************************************************************/

void *
AcpiDbGetPointer (
    void                    *Target)
{
    void                    *ObjPtr;


#ifdef _IA16
#include <stdio.h>

    /* Have to handle 16-bit pointers of the form segment:offset */

    if (!sscanf (Target, "%p", &ObjPtr))
    {
        AcpiOsPrintf ("Invalid pointer: %s\n", Target);
        return;
    }

#else

    /* Simple flat pointer */

    ObjPtr = (void *) STRTOUL (Target, NULL, 16);

#endif

    return (ObjPtr);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDbDumpParserDescriptor
 *
 * PARAMETERS:  Op              - A parser Op descriptor
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display a formatted parser object
 *
 *****************************************************************************/

void
AcpiDbDumpParserDescriptor (
    ACPI_GENERIC_OP         *Op)
{
    ACPI_OP_INFO            *Info;


    Info = AcpiPsGetOpcodeInfo (Op->Opcode);

    AcpiOsPrintf ("Parser Op Descriptor:\n");
    AcpiOsPrintf ("%20.20s : %4.4X\n", "Opcode", Op->Opcode);

    DEBUG_ONLY_MEMBERS (AcpiOsPrintf ("%20.20s : %s\n", "Opcode Name", Info->Name));

    AcpiOsPrintf ("%20.20s : %p\n", "Value/ArgList", Op->Value);
    AcpiOsPrintf ("%20.20s : %p\n", "Parent", Op->Parent);
    AcpiOsPrintf ("%20.20s : %p\n", "NextOp", Op->Next);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDbDecodeAndDisplayObject
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display a formatted ACPI object
 *
 *****************************************************************************/

void
AcpiDbDecodeAndDisplayObject (
    NATIVE_CHAR             *Target,
    NATIVE_CHAR             *OutputType)
{
    void                    *ObjPtr;
    ACPI_NAMED_OBJECT       *Entry;
    UINT32                  Display = DB_BYTE_DISPLAY;
    NATIVE_CHAR             Buffer[80];
    ACPI_BUFFER             RetBuf;
    ACPI_STATUS             Status;
    UINT32                  Size;


    if (!Target)
    {
        return;
    }

    if (OutputType)
    {
        STRUPR (OutputType);
        if (OutputType[0] == 'W')
        {
            Display = DB_WORD_DISPLAY;
        }
        else if (OutputType[0] == 'D')
         {
            Display = DB_DWORD_DISPLAY;
        }
        else if (OutputType[0] == 'Q')
         {
            Display = DB_QWORD_DISPLAY;
        }
    }


    RetBuf.Length = sizeof (Buffer);
    RetBuf.Pointer = Buffer;

    /* Differentiate between a number and a name */

    if ((Target[0] >= 0x30) && (Target[0] <= 0x39))
    {
        ObjPtr = AcpiDbGetPointer (Target);
        if (!AcpiOsReadable (ObjPtr, 16))
        {
            AcpiOsPrintf ("Address %p is invalid in this address space\n", ObjPtr);
            return;
        }

        if (VALID_DESCRIPTOR_TYPE ((ObjPtr), ACPI_DESC_TYPE_NAMED))
        {
            /* This is an NTE */

            if (!AcpiOsReadable (ObjPtr, sizeof (ACPI_NAMED_OBJECT)))
            {
                AcpiOsPrintf ("Cannot read entire NTE at address %p\n", ObjPtr);
                return;
            }

            Entry = ObjPtr;
            goto DumpNte;
        }

        else if (VALID_DESCRIPTOR_TYPE ((ObjPtr), ACPI_DESC_TYPE_INTERNAL))
        {
            /* This is an ACPI OBJECT */

            if (!AcpiOsReadable (ObjPtr, sizeof (ACPI_OBJECT_INTERNAL)))
            {
                AcpiOsPrintf ("Cannot read entire ACPI object at address %p\n", ObjPtr);
                return;
            }

            AcpiCmDumpBuffer (ObjPtr, sizeof (ACPI_OBJECT_INTERNAL), Display, ACPI_UINT32_MAX);
            AcpiAmlDumpObjectDescriptor (ObjPtr, 1);
        }

        else if (VALID_DESCRIPTOR_TYPE ((ObjPtr), ACPI_DESC_TYPE_PARSER))
        {
            /* This is an Parser Op object */

            if (!AcpiOsReadable (ObjPtr, sizeof (ACPI_GENERIC_OP)))
            {
                AcpiOsPrintf ("Cannot read entire Parser object at address %p\n", ObjPtr);
                return;
            }


            AcpiCmDumpBuffer (ObjPtr, sizeof (ACPI_GENERIC_OP), Display, ACPI_UINT32_MAX);
            AcpiDbDumpParserDescriptor ((ACPI_GENERIC_OP *) ObjPtr);
        }

        else
        {
            Size = 16;
            if (AcpiOsReadable (ObjPtr, 64))
            {
                Size = 64;
            }

            /* Just dump some memory */

            AcpiCmDumpBuffer (ObjPtr, Size, Display, ACPI_UINT32_MAX);
        }

        return;
    }


    /* The parameter is a name string that must be resolved to an NTE */

    Entry = AcpiDbLocalNsLookup (Target);
    if (!Entry)
    {
        return;
    }

DumpNte:
    /* Now dump the NTE */

    Status = AcpiGetName (Entry, ACPI_FULL_PATHNAME, &RetBuf);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not convert name to pathname\n");
        return;
    }

    AcpiOsPrintf ("Object Pathname:  %s\n", RetBuf.Pointer);
    if (!AcpiOsReadable (Entry, sizeof (ACPI_NAMED_OBJECT)))
    {
        AcpiOsPrintf ("Invalid NTE at address %p\n", Entry);
        return;
    }

    AcpiCmDumpBuffer ((void *) Entry, sizeof (ACPI_NAMED_OBJECT), Display, ACPI_UINT32_MAX);
    AcpiAmlDumpAcpiNamedObject (Entry, 1);

    if (Entry->Object)
    {
        AcpiOsPrintf ("\nAttached Object (0x%p):\n", Entry->Object);
        if (!AcpiOsReadable (Entry->Object, sizeof (ACPI_OBJECT_INTERNAL)))
        {
            AcpiOsPrintf ("Invalid internal ACPI Object at address %p\n", Entry->Object);
            return;
        }

        AcpiCmDumpBuffer (Entry->Object, sizeof (ACPI_OBJECT_INTERNAL), Display, ACPI_UINT32_MAX);
        AcpiAmlDumpObjectDescriptor (Entry->Object, 1);
    }
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDbDecodeInternalObject
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION: Short display of an internal object
 *
 *****************************************************************************/

void
AcpiDbDecodeInternalObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{

    if (!ObjDesc)
    {
        return;
    }

    AcpiOsPrintf (" %9.9s ", AcpiCmGetTypeName (ObjDesc->Common.Type));

    switch (ObjDesc->Common.Type)
    {
    case ACPI_TYPE_NUMBER:
        AcpiOsPrintf ("0x%.8X", ObjDesc->Number.Value, ObjDesc->Number.Value);
        break;

    case ACPI_TYPE_STRING:
        AcpiOsPrintf ("\"%.16s\"...", ObjDesc->String.Pointer);
        break;
    }
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDbDisplayInternalObject
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION: Short display of an internal object
 *
 *****************************************************************************/

void
AcpiDbDisplayInternalObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc,
    ACPI_WALK_STATE         *WalkState)
{
    UINT8                   Type;



    AcpiOsPrintf ("%p ", ObjDesc);

    if (!ObjDesc)
    {
        AcpiOsPrintf ("<NullObj>\n");
        return;
    }

    else if (VALID_DESCRIPTOR_TYPE (ObjDesc, ACPI_DESC_TYPE_PARSER))
    {
        AcpiOsPrintf ("<Parser>  ");
    }

    else if (VALID_DESCRIPTOR_TYPE (ObjDesc, ACPI_DESC_TYPE_NAMED))
    {
        AcpiOsPrintf ("<NTE>             Name %4.4s Type %s", &((ACPI_NAMED_OBJECT*)ObjDesc)->Name,
                                                            AcpiCmGetTypeName (((ACPI_NAMED_OBJECT*)ObjDesc)->Type));
    }

    else if (VALID_DESCRIPTOR_TYPE (ObjDesc, ACPI_DESC_TYPE_INTERNAL))
    {
        AcpiOsPrintf ("<Obj> ");
        Type = ObjDesc->Common.Type;
        if (Type > INTERNAL_TYPE_MAX)
        {
            AcpiOsPrintf (" Type %x [Invalid Type]", Type);
            return;
        }

        switch (ObjDesc->Common.Type)
        {
        case INTERNAL_TYPE_REFERENCE:
            switch (ObjDesc->Reference.OpCode)
            {
            case AML_ZERO_OP:
                AcpiOsPrintf ("[Const]     Number 0x%.8X", 0);
                break;

            case AML_ONES_OP:
                AcpiOsPrintf ("[Const]     Number 0x%.8X", ACPI_UINT32_MAX);
                break;

            case AML_ONE_OP:
                AcpiOsPrintf ("[Const]     Number 0x%.8X", 1);
                break;

            case AML_LOCAL_OP:
                AcpiOsPrintf ("[Local%d]", ObjDesc->Reference.Offset);
                if (WalkState)
                {
                    ObjDesc = WalkState->LocalVariables[ObjDesc->Reference.Offset].Object;
                    AcpiDbDecodeInternalObject (ObjDesc);
                }
                break;

            case AML_ARG_OP:
                AcpiOsPrintf ("[Arg%d]  ", ObjDesc->Reference.Offset);
                if (WalkState)
                {
                    ObjDesc = WalkState->Arguments[ObjDesc->Reference.Offset].Object;
                    AcpiDbDecodeInternalObject (ObjDesc);
                }
                break;

            case AML_DEBUG_OP:
                AcpiOsPrintf ("[Debug]  ");
                break;

            case AML_INDEX_OP:
                AcpiOsPrintf ("[Index]  ");
                AcpiDbDecodeInternalObject (ObjDesc->Reference.Object);
                break;

            default:
                break;

            }
            break;

        default:
            AcpiOsPrintf ("        ");
            AcpiDbDecodeInternalObject (ObjDesc);
            break;
        }
    }

    else
    {
        AcpiOsPrintf ("<Not a valid ACPI Object Descriptor> ");
    }

    AcpiOsPrintf ("\n");
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDbDisplayMethodInfo
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display information about the current method
 *
 *****************************************************************************/

void
AcpiDbDisplayMethodInfo (
    ACPI_GENERIC_OP         *StartOp)
{
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_NAMED_OBJECT       *Entry;
    ACPI_GENERIC_OP         *RootOp;
    ACPI_GENERIC_OP         *Op;
    ACPI_OP_INFO            *OpInfo;
    UINT32                  NumOps = 0;
    UINT32                  NumOperands = 0;
    UINT32                  NumOperators = 0;
    UINT32                  NumRemainingOps = 0;
    UINT32                  NumRemainingOperands = 0;
    UINT32                  NumRemainingOperators = 0;
    UINT32                  NumArgs;
    UINT32                  Concurrency;
    BOOLEAN                 CountRemaining = FALSE;


    WalkState = AcpiDsGetCurrentWalkState (AcpiGbl_CurrentWalkList);
    if (!WalkState)
    {
        AcpiOsPrintf ("There is no method currently executing\n");
        return;
    }

    ObjDesc = WalkState->MethodDesc;
    Entry = WalkState->Origin->AcpiNamedObject;

    NumArgs = ObjDesc->Method.ParamCount;
    Concurrency = ObjDesc->Method.Concurrency;

    AcpiOsPrintf ("Currently executing control method is [%4.4s]\n", &Entry->Name);
    AcpiOsPrintf ("%d arguments, max concurrency = %d\n", NumArgs, Concurrency);


    RootOp = StartOp;
    while (RootOp->Parent)
    {
        RootOp = RootOp->Parent;
    }

    Op = RootOp;

    while (Op)
    {
        if (Op == StartOp)
        {
            CountRemaining = TRUE;
        }

        NumOps++;
        if (CountRemaining)
        {
            NumRemainingOps++;
        }

        OpInfo = AcpiPsGetOpcodeInfo (Op->Opcode);
        if (ACPI_GET_OP_TYPE (OpInfo) != ACPI_OP_TYPE_OPCODE)
        {
            /* Bad opcode or ASCII character */

            continue;
        }


        /* Decode the opcode */

        switch (ACPI_GET_OP_CLASS (OpInfo))
        {
        case OPTYPE_CONSTANT:           /* argument type only */
        case OPTYPE_LITERAL:            /* argument type only */
        case OPTYPE_DATA_TERM:          /* argument type only */
        case OPTYPE_LOCAL_VARIABLE:     /* argument type only */
        case OPTYPE_METHOD_ARGUMENT:    /* argument type only */
            if (CountRemaining)
                NumRemainingOperands++;

            NumOperands++;
            break;

        default:
            if (CountRemaining)
                NumRemainingOperators++;

            NumOperators++;
            break;
        }


        Op = AcpiPsGetDepthNext (StartOp, Op);
    }

    AcpiOsPrintf ("Method contains:       %d AML Opcodes - %d Operators, %d Operands\n",
                NumOps, NumOperators, NumOperands);

    AcpiOsPrintf ("Remaining to execute:  %d AML Opcodes - %d Operators, %d Operands\n",
                NumRemainingOps, NumRemainingOperators, NumRemainingOperands);
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDbDisplayLocals
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display all locals for a control method
 *
 *****************************************************************************/

void
AcpiDbDisplayLocals (void)
{
    UINT32                  i;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_NAMED_OBJECT       *Entry;


    WalkState = AcpiDsGetCurrentWalkState (AcpiGbl_CurrentWalkList);
    if (!WalkState)
    {
        AcpiOsPrintf ("There is no method currently executing\n");
        return;
    }

    ObjDesc = WalkState->MethodDesc;
    Entry = WalkState->Origin->AcpiNamedObject;


    AcpiOsPrintf ("Local Variables for method [%4.4s]:\n", &Entry->Name);

    for (i = 0; i < MTH_NUM_LOCALS; i++)
    {
        ObjDesc = WalkState->LocalVariables[i].Object;
        AcpiOsPrintf ("Local%d: ", i);
        AcpiDbDisplayInternalObject (ObjDesc, WalkState);
    }
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDbDisplayArguments
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display all arguments for a control method
 *
 *****************************************************************************/

void
AcpiDbDisplayArguments (void)
{
    UINT32                  i;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    UINT32                  NumArgs;
    UINT32                  Concurrency;
    ACPI_NAMED_OBJECT       *Entry;


    WalkState = AcpiDsGetCurrentWalkState (AcpiGbl_CurrentWalkList);
    if (!WalkState)
    {
        AcpiOsPrintf ("There is no method currently executing\n");
        return;
    }

    ObjDesc = WalkState->MethodDesc;
    Entry = WalkState->Origin->AcpiNamedObject;

    NumArgs = ObjDesc->Method.ParamCount;
    Concurrency = ObjDesc->Method.Concurrency;

    AcpiOsPrintf ("Method [%4.4s] has %d arguments, max concurrency = %d\n", &Entry->Name, NumArgs, Concurrency);

    for (i = 0; i < NumArgs; i++)
    {
        ObjDesc = WalkState->Arguments[i].Object;
        AcpiOsPrintf ("Arg%d: ", i);
        AcpiDbDisplayInternalObject (ObjDesc, WalkState);
    }
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDbDisplayResults
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display current contents of a method result stack
 *
 *****************************************************************************/

void
AcpiDbDisplayResults (void)
{
    UINT32                  i;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    UINT32                  NumResults;
    ACPI_NAMED_OBJECT       *Entry;


    WalkState = AcpiDsGetCurrentWalkState (AcpiGbl_CurrentWalkList);
    if (!WalkState)
    {
        AcpiOsPrintf ("There is no method currently executing\n");
        return;
    }

    ObjDesc = WalkState->MethodDesc;
    Entry = WalkState->Origin->AcpiNamedObject;
    NumResults = WalkState->NumResults - WalkState->CurrentResult;

    AcpiOsPrintf ("Method [%4.4s] has %d stacked result objects\n", &Entry->Name, NumResults);

    for (i = WalkState->CurrentResult; i < WalkState->NumResults; i++)
    {
        ObjDesc = WalkState->Results[i];
        AcpiOsPrintf ("Result%d: ", i);
        AcpiDbDisplayInternalObject (ObjDesc, WalkState);
    }
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDbDisplayCallingTree
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display current calling tree of nested control methods
 *
 *****************************************************************************/

void
AcpiDbDisplayCallingTree (void)
{
    UINT32                  i;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ObjDesc;
    ACPI_NAMED_OBJECT       *Entry;


    WalkState = AcpiDsGetCurrentWalkState (AcpiGbl_CurrentWalkList);
    if (!WalkState)
    {
        AcpiOsPrintf ("There is no method currently executing\n");
        return;
    }

    ObjDesc = WalkState->MethodDesc;
    Entry = WalkState->Origin->AcpiNamedObject;

    AcpiOsPrintf ("Current Control Method Call Tree\n");

    for (i = 0; WalkState; i++)
    {
        ObjDesc = WalkState->MethodDesc;
        Entry = WalkState->Origin->AcpiNamedObject;

        AcpiOsPrintf ("    [%4.4s]\n", &Entry->Name);

        WalkState = WalkState->Next;
    }
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDbDisplayResultObject
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display the result of an AML opcode
 *
 *****************************************************************************/

void
AcpiDbDisplayResultObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc,
    ACPI_WALK_STATE         *WalkState)
{

    /* TBD: [Future] We don't always want to display the result.
     * For now, only display if single stepping
     * however, this output is very useful in other contexts also
     */

    if (!AcpiGbl_CmSingleStep)
    {
        return;
    }

    AcpiOsPrintf ("ResultObj: ");
    AcpiDbDisplayInternalObject (ObjDesc, WalkState);
    AcpiOsPrintf ("\n");
}


/******************************************************************************
 *
 * FUNCTION:    AcpiDbDisplayArgumentObject
 *
 * PARAMETERS:
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display the result of an AML opcode
 *
 *****************************************************************************/

void
AcpiDbDisplayArgumentObject (
    ACPI_OBJECT_INTERNAL    *ObjDesc,
    ACPI_WALK_STATE         *WalkState)
{


    if (!AcpiGbl_CmSingleStep)
    {
        return;
    }

    AcpiOsPrintf ("ArgObj:    ");
    AcpiDbDisplayInternalObject (ObjDesc, WalkState);
}

#endif /* ENABLE_DEBUGGER */

