/******************************************************************************
 *
 * Module Name: dswload - Dispatcher namespace load callbacks
 *              $Revision: 1.23 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, 2001, Intel Corp.
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

#define __ASLLOAD_C__

#include "acpi.h"
#include "acparser.h"
#include "amlcode.h"
#include "acdispat.h"
#include "acinterp.h"
#include "acnamesp.h"
#include "acevents.h"
#include "aslcompiler.h"

#include "aslcompiler.y.h"

#define _COMPONENT          ACPI_COMPILER
        MODULE_NAME         ("aslload")


/*******************************************************************************
 *
 * FUNCTION:    LdLoadNamespace
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perform a walk of the parse tree that in turn loads all of the
 *              named ASL/AML objects into the namespace.  The namespace is
 *              constructed in order to resolve named references and references
 *              to named fields within resource templates/descriptors.
 *
 ******************************************************************************/

ACPI_STATUS
LdLoadNamespace (void)
{
    ACPI_WALK_STATE         *WalkState;
    ACPI_WALK_LIST          WalkList;


    DbgPrint (ASL_DEBUG_OUTPUT, "\nCreating namespace\n\n");


    /* Create a new walk state */

    WalkList.WalkState = NULL;
    WalkState = AcpiDsCreateWalkState (TABLE_ID_DSDT, NULL, NULL, &WalkList);
    if (!WalkState)
    {
        return AE_NO_MEMORY;
    }


    /* Perform the walk of the parse tree */

    TrWalkParseTree (RootNode, ASL_WALK_VISIT_TWICE, LdNamespace1Begin,
                        LdNamespace1End, WalkState);


    /* Dump the namespace if debug is enabled */

    AcpiNsDumpTables (NS_ALL, ACPI_UINT32_MAX);

    return AE_OK;
}


/*******************************************************************************
 *
 * FUNCTION:    LdLoadFieldElements
 *
 * PARAMETERS:  PsNode          - Parent node (Field)
 *              WalkState       - Current walk state
 *
 * RETURN:      None
 *
 * DESCRIPTION: Enter the named elements of the field (children of the parent)
 *              into the namespace.
 *
 ******************************************************************************/

void
LdLoadFieldElements (
    ASL_PARSE_NODE          *PsNode,
    ACPI_WALK_STATE         *WalkState)
{
    ASL_PARSE_NODE          *Child = NULL;
    ACPI_NAMESPACE_NODE     *NsNode;
    ACPI_STATUS             Status;


    /* Get the first named field element */

    switch (PsNode->AmlOpcode)
    {
    case AML_BANK_FIELD_OP:
        Child = UtGetArg (PsNode, 6);
        break;

    case AML_INDEX_FIELD_OP:
        Child = UtGetArg (PsNode, 5);
        break;

    case AML_FIELD_OP:
        Child = UtGetArg (PsNode, 4);
        break;
    }


    /* Enter all elements into the namespace */

    while (Child)
    {
        switch (Child->AmlOpcode)
        {
        case AML_RESERVEDFIELD_OP:
        case AML_ACCESSFIELD_OP:
            break;

        default:

            Status = AcpiNsLookup (WalkState->ScopeInfo, Child->Value.String,
                            INTERNAL_TYPE_REGION_FIELD, IMODE_LOAD_PASS1,
                            NS_NO_UPSEARCH | NS_DONT_OPEN_SCOPE,
                            NULL, &NsNode);
            if (ACPI_FAILURE (Status))
            {
                /* TBD - emit error */
                return;
            }

            Child->NsNode = NsNode;
            NsNode->Object = Child;
            break;
        }

        Child = Child->Peer;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    LdLoadResourceElements
 *
 * PARAMETERS:  PsNode          - Parent node (Resource Descriptor)
 *              WalkState       - Current walk state
 *
 * RETURN:      None
 *
 * DESCRIPTION: Enter the named elements of the resource descriptor (children
 *              of the parent) into the namespace.
 *
 * NOTE: In the real AML namespace, these named elements never exist.  But
 *       we simply use the namespace here as a symbol table so we can look
 *       them up as they are referenced.
 *
 ******************************************************************************/

void
LdLoadResourceElements (
    ASL_PARSE_NODE          *PsNode,
    ACPI_WALK_STATE         *WalkState)
{
    ASL_PARSE_NODE          *InitializerNode = NULL;
    ACPI_NAMESPACE_NODE     *NsNode;
    ACPI_STATUS             Status;


    /*
     * Enter the resouce name into the namespace
     * This opens a scope
     */
    Status = AcpiNsLookup (WalkState->ScopeInfo,
                    PsNode->Namepath,
                    INTERNAL_TYPE_RESOURCE,
                    IMODE_LOAD_PASS1,
                    NS_NO_UPSEARCH,
                    WalkState, &NsNode);


    /*
     * Now enter the predefined fields, for easy lookup when referenced
     * by the source ASL
     */
    InitializerNode = ASL_GET_CHILD_NODE (PsNode);
    while (InitializerNode)
    {

        if (InitializerNode->ExternalName)
        {
            Status = AcpiNsLookup (WalkState->ScopeInfo,
                            InitializerNode->ExternalName,
                            INTERNAL_TYPE_RESOURCE,
                            IMODE_LOAD_PASS1,
                            NS_NO_UPSEARCH | NS_DONT_OPEN_SCOPE,
                            NULL, &NsNode);

            if (ACPI_FAILURE (Status))
            {
                return;
            }

            /*
             * Store the field offset in the namespace node so it
             * can be used when the field is referenced
             */
            (UINT16) NsNode->OwnerId = InitializerNode->Value.Integer16;
            InitializerNode->NsNode = NsNode;
            NsNode->Object = InitializerNode;
        }

        InitializerNode = ASL_GET_PEER_NODE (InitializerNode);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    LdNamespace1Begin
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Descending callback used during the parse tree walk.  If this
 *              is a named AML opcode, enter into the namespace
 *
 ******************************************************************************/


ACPI_STATUS
LdNamespace1Begin (
    ASL_PARSE_NODE          *PsNode,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_WALK_STATE         *WalkState = (ACPI_WALK_STATE *) Context;
    ACPI_NAMESPACE_NODE     *NsNode;
    ACPI_STATUS             Status;
    OBJECT_TYPE_INTERNAL    DataType;
    NATIVE_CHAR             *Path;
    UINT32                  Flags = NS_NO_UPSEARCH;
    ASL_PARSE_NODE          *Arg;
    UINT32                  i;


    DEBUG_PRINT (TRACE_DISPATCH,
        ("Load1BeginOp: PsNode %p\n", PsNode));


    /* We are only interested in opcodes that have an associated name (or multiple names) */

    switch (PsNode->AmlOpcode)
    {
    case AML_BANK_FIELD_OP:
    case AML_INDEX_FIELD_OP:
    case AML_FIELD_OP:

        LdLoadFieldElements (PsNode, WalkState);
        return (AE_OK);
    }


    /* Check if this object has already been installed in the namespace */

    if (PsNode->NsNode)
    {
        return (AE_OK);
    }


    Path = PsNode->Namepath;
    if (!Path)
    {
        return (AE_OK);
    }


    /* Map the raw opcode into an internal object type */

    if (PsNode->ParseOpcode == NAME)
    {
        Arg = PsNode->Child;        /* Get the NameSeg/NameString node */
        Arg = Arg->Peer;            /* First peer is the object to be associated with the name */

        /* Get the data type associated with the named object, not the name itself */

        /* Log2 loop to convert from Btype (binary) to Etype (encoded) */

        DataType = 1;
        for (i = 1; i < Arg->AcpiBtype; i *= 2)
        {
            DataType++;
        }
    }

    else if (PsNode->ParseOpcode == EXTERNAL)
    {
        /* "External" simply enters a name and type into the namespace */
        /* first child is name, next child is ObjectType */

        DataType = PsNode->Child->Peer->Value.Integer8;
    }

    else if ((PsNode->ParseOpcode == DEFAULT_ARG) &&
             (PsNode->Flags == NODE_IS_RESOURCE_DESC))
    {
        /* TBD: Merge into AcpiDsMapNamedOpcodeToDataType */

        DataType = INTERNAL_TYPE_RESOURCE;
        LdLoadResourceElements (PsNode, WalkState);
        return AE_OK;
    }

    else
    {
        DataType = AcpiDsMapNamedOpcodeToDataType (PsNode->AmlOpcode);
    }

    DEBUG_PRINT (TRACE_DISPATCH,
        ("Load1BeginOp: Type=%x\n", DataType));


    if (PsNode->ParseOpcode != SCOPE)
    {
        Flags |= NS_ERROR_IF_FOUND;
    }

    /*
     * Enter the named type into the internal namespace.  We enter the name
     * as we go downward in the parse tree.  Any necessary subobjects that involve
     * arguments to the opcode must be created as we go back up the parse tree later.
     */
    Status = AcpiNsLookup (WalkState->ScopeInfo,  Path, DataType,
                    IMODE_LOAD_PASS1, Flags, WalkState, &(NsNode));

    if (ACPI_FAILURE (Status))
    {
        if (Status == AE_EXIST)
        {
            /* The name already exists in this scope */

            AslError (ASL_ERROR, ASL_MSG_NAME_EXISTS, PsNode, Path);
            return (Status);
        }

        printf ("Failure from lookup %s\n", AcpiCmFormatException (Status));
        return (Status);
    }

    /*
     * Point the parse node to the new namespace node, and point
     * the NsNode back to the original Parse node
     */
    PsNode->NsNode = NsNode;
    NsNode->Object = PsNode;


    if (PsNode->ParseOpcode == METHOD)
    {
        NsNode->OwnerId = PsNode->Extra;
    }


    return (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    LdNamespace1End
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Ascending callback used during the loading of the namespace,
 *              We only need to worry about managing the scope stack here.
 *
 ******************************************************************************/

ACPI_STATUS
LdNamespace1End (
    ASL_PARSE_NODE          *PsNode,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_WALK_STATE         *WalkState = (ACPI_WALK_STATE *) Context;
    OBJECT_TYPE_INTERNAL    DataType;


    /* We are only interested in opcodes that have an associated name */

    if (!PsNode->Namepath)
    {
        return (AE_OK);
    }


    /* Get the type to determine if we should pop the scope */

    if ((PsNode->ParseOpcode == DEFAULT_ARG) &&
        (PsNode->Flags == NODE_IS_RESOURCE_DESC))
    {
        /* TBD: Merge into AcpiDsMapNamedOpcodeToDataType */

        DataType = INTERNAL_TYPE_RESOURCE;
    }

    else
    {
        DataType = AcpiDsMapNamedOpcodeToDataType (PsNode->AmlOpcode);
    }


    /* Pop the scope stack */

    if (AcpiNsOpensScope (DataType))
    {

        DEBUG_PRINT (TRACE_DISPATCH,
            ("Load1EndOp/%s: Popping scope for Op %p\n",
            AcpiCmGetTypeName (DataType), PsNode));


        AcpiDsScopeStackPop (WalkState);

    }

    return (AE_OK);
}


