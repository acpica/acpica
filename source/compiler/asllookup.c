/******************************************************************************
 *
 * Module Name: asllookup- Namespace lookup
 *              $Revision: 1.41 $
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


#include "aslcompiler.h"
#include "aslcompiler.y.h"

#include "acparser.h"
#include "amlcode.h"
#include "acnamesp.h"
#include "acdispat.h"


#define _COMPONENT          ACPI_COMPILER
        MODULE_NAME         ("asllookup")


/*****************************************************************************
 *
 * FUNCTION:    LsDoOneNamespaceObject
 *
 * PARAMETERS:  ACPI_WALK_CALLBACK
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dump a namespace object to the namespace output file.
 *              Called during the walk of the namespace to dump all objects.
 *
 ****************************************************************************/

ACPI_STATUS
LsDoOneNamespaceObject (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_NAMESPACE_NODE     *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;
    ASL_PARSE_NODE          *Pnode;


    Gbl_NumNamespaceObjects++;

    FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "%5d  [%d]  %*s %4.4s - %s",
                        Gbl_NumNamespaceObjects, Level, (Level * 3), " ",
                        &Node->Name,
                        AcpiUtGetTypeName (Node->Type));

    Pnode = (ASL_PARSE_NODE *) Node->Object;

    if (Pnode)
    {
        if (Pnode->ParseOpcode == NAME)
        {
            Pnode = Pnode->Child;
        }


        switch (Node->Type)
        {
        case ACPI_TYPE_INTEGER:

            if ((Pnode->ParseOpcode == NAMESEG)  ||
                (Pnode->ParseOpcode == NAMESTRING))
            {
                Pnode = Pnode->Peer;
            }

            if (Pnode->Value.Integer64 > ACPI_UINT32_MAX)
            {
                FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "    [Initial Value = 0x%X%X]",
                            HIDWORD (Pnode->Value.Integer64), Pnode->Value.Integer32);
            }
            else
            {
                FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "    [Initial Value = 0x%X]",
                            Pnode->Value.Integer32);
            }
            break;


        case ACPI_TYPE_STRING:
            if ((Pnode->ParseOpcode == NAMESEG)  ||
                (Pnode->ParseOpcode == NAMESTRING))
            {
                Pnode = Pnode->Peer;
            }

            FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "    [Initial Value = \"%s\"]",
                        Pnode->Value.String);

            break;


        case INTERNAL_TYPE_REGION_FIELD:
            if ((Pnode->ParseOpcode == NAMESEG)  ||
                (Pnode->ParseOpcode == NAMESTRING))
            {
                Pnode = Pnode->Child;
            }
            FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "    [Length = 0x%02X]",
                        Pnode->Value.Integer32);

            break;

        }

    }

    FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "\n");

    return (AE_OK);
}


/*****************************************************************************
 *
 * FUNCTION:    LsDisplayNamespace
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Walk the namespace an display information about each node
 *              in the tree.  Information is written to the optional
 *              namespace output file.
 *
 ****************************************************************************/

ACPI_STATUS
LsDisplayNamespace (void)
{
    ACPI_STATUS             Status;


    if (!Gbl_NsOutputFlag)
    {
        return (AE_OK);
    }

    /* File header */

    FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "Contents of ACPI Namespace\n\n");
    FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "Count  Depth    Name - Type\n\n");

    /* Walk entire namespace from the supplied root */

    Status = AcpiNsWalkNamespace (ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
                                ACPI_UINT32_MAX, FALSE, LsDoOneNamespaceObject,
                                NULL, NULL);

    return (AE_OK);
}


/*****************************************************************************
 *
 * FUNCTION:    LsCompareOneNamespaceObject
 *
 * PARAMETERS:  ACPI_WALK_CALLBACK
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Compare name of one object.
 *
 ****************************************************************************/

ACPI_STATUS
LsCompareOneNamespaceObject (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_NAMESPACE_NODE     *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;


    /* Simply check the name */

    if (*((UINT32 *) (Context)) == Node->Name)
    {
        /* Abort walk if we found one instance */

        return (AE_CTRL_TRUE);
    }

    return (AE_OK);
}


/*****************************************************************************
 *
 * FUNCTION:    LkObjectExists
 *
 * PARAMETERS:  Name            - 4 char ACPI name
 *
 * RETURN:      TRUE if name exists in namespace
 *
 * DESCRIPTION: Walk the namespace to find an object
 *
 ****************************************************************************/

BOOLEAN
LkObjectExists (
    char                    *Name)
{
    ACPI_STATUS             Status;


    /* Walk entire namespace from the supplied root */

    Status = AcpiNsWalkNamespace (ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
                                ACPI_UINT32_MAX, FALSE, LsCompareOneNamespaceObject,
                                Name, NULL);

    if (Status == AE_CTRL_TRUE)
    {
        /* At least one instance of the name was found */

        return (TRUE);
    }

    return (FALSE);
}


/*****************************************************************************
 *
 * FUNCTION:    LkCrossReferenceNamespace
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perform a cross reference check of the parse tree against the
 *              namespace.  Every named referenced within the parse tree
 *              should be get resolved with a namespace lookup.  If not, the
 *              original reference in the ASL code is invalid -- i.e., refers
 *              to a non-existent object.
 *
 * NOTE:  The ASL "External" operator causes the name to be inserted into the
 *        namespace so that references to the external name will be resolved
 *        correctly here.
 *
 ****************************************************************************/

ACPI_STATUS
LkCrossReferenceNamespace (void)
{
    ACPI_WALK_STATE         *WalkState;
    ACPI_WALK_LIST          WalkList;


    DbgPrint (ASL_DEBUG_OUTPUT, "\nCross referencing namespace\n\n");

    /*
     * Create a new walk state for use when looking up names
     * within the namespace (Passed as context to the callbacks)
     */

    WalkList.WalkState = NULL;
    WalkState = AcpiDsCreateWalkState (TABLE_ID_DSDT, NULL, NULL, &WalkList);
    if (!WalkState)
    {
        return AE_NO_MEMORY;
    }


    /* Walk the entire parse tree */

    TrWalkParseTree (RootNode, ASL_WALK_VISIT_TWICE, LkNamespaceLocateBegin,
                        LkNamespaceLocateEnd, WalkState);

    return AE_OK;
}


/*****************************************************************************
 *
 * FUNCTION:    LkNamespaceLocateBegin
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Descending callback used during cross-reference.  For named
 *              object references, attempt to locate the name in the
 *              namespace.
 *
 * NOTE: ASL references to named fields within resource descriptors are
 *       resolve to integer values here.  Therefore, this step is an
 *       important part of the code generation.  We don't know that the
 *       name refers to a resource descriptor until now.
 *
 ****************************************************************************/

ACPI_STATUS
LkNamespaceLocateBegin (
    ASL_PARSE_NODE          *PsNode,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_WALK_STATE         *WalkState = (ACPI_WALK_STATE *) Context;
    ACPI_NAMESPACE_NODE     *NsNode;
    ACPI_STATUS             Status;
    ACPI_OBJECT_TYPE8       DataType;
    NATIVE_CHAR             *Path;
    UINT8                   PassedArgs;
    ASL_PARSE_NODE          *Next;
    ASL_PARSE_NODE          *OwningPsNode;
    UINT32                  MinimumLength;
    UINT32                  Temp;
    const ACPI_OPCODE_INFO  *OpInfo;


    PROC_NAME ("LkNamespaceLocateBegin");
    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH, "NamespaceLocateBegin: PsNode %p\n", PsNode));


    /* We are only interested in opcodes that have an associated name */

    OpInfo = AcpiPsGetOpcodeInfo (PsNode->AmlOpcode);

    if ((!(OpInfo->Flags & AML_NAMED)) &&
        (PsNode->ParseOpcode != NAMESTRING) &&
        (PsNode->ParseOpcode != NAMESEG)    &&
        (PsNode->ParseOpcode != METHODCALL))
    {
        return (AE_OK);
    }

    if (OpInfo->Flags & AML_NAMED)
    {
        Path = PsNode->Child->Value.String;
    }
    else
    {
        Path = PsNode->Value.String;
    }


    /* Map the raw opcode into an internal object type */

    DataType = AcpiDsMapNamedOpcodeToDataType (PsNode->AmlOpcode);


    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH, "NamespaceLocateBegin: Type=%x\n", DataType));


    /*
     * Lookup the name in the namespace.  Name must exist at this point, or it
     * is an invalid reference.
     *
     * The namespace is also used as a lookup table for references to resource
     * descriptors and the fields within them.
     */
    Gbl_NsLookupCount++;

    Status = AcpiNsLookup (WalkState->ScopeInfo,  Path,
                            DataType, IMODE_EXECUTE,
                            NS_SEARCH_PARENT, WalkState, &(NsNode));

    if (ACPI_FAILURE (Status))
    {
        if (Status == AE_NOT_FOUND)
        {
            /*
             * We didn't find the name reference by path -- we can qualify this
             * a little better before we print an error message
             */

            if (strlen (Path) == ACPI_NAME_SIZE)
            {
                /* A simple, one-segment ACPI name */

                if (LkObjectExists (Path))
                {
                    /* There exists such a name, but we couldn't get to it from this scope */

                    AslError (ASL_WARNING, ASL_MSG_NOT_REACHABLE, PsNode, PsNode->ExternalName);
                }
                else
                {
                    /* The name doesn't exist, period */

                    AslError (ASL_WARNING, ASL_MSG_NOT_EXIST, PsNode, PsNode->ExternalName);
                }
            }

            else
            {
                /* Check for a fully qualified path */

                if (Path[0] == AML_ROOT_PREFIX)
                {
                    /* Gave full path, the object does not exist */

                    AslError (ASL_WARNING, ASL_MSG_NOT_EXIST, PsNode, PsNode->ExternalName);
                }
                else
                {
                    /* We can't tell whether it doesn't exist or just can't be reached. */

                    AslError (ASL_WARNING, ASL_MSG_NOT_FOUND, PsNode, PsNode->ExternalName);
                }
            }
        }
        return (Status);
    }


    /* 1) Check for a reference to a resource descriptor */

    if ((NsNode->Type == INTERNAL_TYPE_RESOURCE_FIELD) ||
        (NsNode->Type == INTERNAL_TYPE_RESOURCE))
    {
        /*
         * This was a reference to a field within a resource descriptor.  Extract
         * the associated field offset (either a bit or byte offset depending on
         * the field type) and change the named reference into an integer for
         * AML code generation
         */
        Temp = (UINT32) NsNode->OwnerId;
        if (NsNode->Flags & ANOBJ_IS_BIT_OFFSET)
        {
            PsNode->Flags |= NODE_IS_BIT_OFFSET;
        }


        /* Perform BitOffset <--> ByteOffset conversion if necessary */

        switch (PsNode->Parent->AmlOpcode)
        {
        case AML_CREATE_FIELD_OP:

            /* We allow a Byte offset to Bit Offset conversion for this op */

            if (!(PsNode->Flags & NODE_IS_BIT_OFFSET))
            {
                /* Simply multiply byte offset times 8 to get bit offset */

                Temp = MUL_8 (Temp);
            }
            break;


        case AML_CREATE_BIT_FIELD_OP:

            /* This op requires a Bit Offset */

            if (!(PsNode->Flags & NODE_IS_BIT_OFFSET))
            {
                AslError (ASL_ERROR, ASL_MSG_BYTES_TO_BITS, PsNode, NULL);
            }
            break;


        case AML_CREATE_BYTE_FIELD_OP:
        case AML_CREATE_WORD_FIELD_OP:
        case AML_CREATE_DWORD_FIELD_OP:
        case AML_CREATE_QWORD_FIELD_OP:
        case AML_INDEX_OP:

            /* These Ops require Byte offsets */

            if (PsNode->Flags & NODE_IS_BIT_OFFSET)
            {
                AslError (ASL_ERROR, ASL_MSG_BITS_TO_BYTES, PsNode, NULL);
            }
            break;
        }

        /* Now convert this node to an integer whose value is the field offset */

        PsNode->ParseOpcode     = INTEGER;
        PsNode->Value.Integer   = (UINT64) Temp;
        PsNode->Flags           |= NODE_IS_RESOURCE_FIELD;

        OpcGenerateAmlOpcode (PsNode);
        PsNode->AmlLength = OpcSetOptimalIntegerSize (PsNode);
    }


    /* 2) Check for a method invocation */

    else if ((((PsNode->ParseOpcode == NAMESTRING) || (PsNode->ParseOpcode == NAMESEG)) &&
        (NsNode->Type == ACPI_TYPE_METHOD) &&
        (PsNode->Parent) &&
        (PsNode->Parent->ParseOpcode != METHOD))   ||

        (PsNode->ParseOpcode == METHODCALL))
    {

        /*
         * There are two types of method invocation:
         * 1) Invocation with arguments -- the parser recognizes this as a METHODCALL
         * 2) Invocation with no arguments --the parser cannot determine that this is a method
         *    invocation, therefore we have to figure it out here.
         */

        if (NsNode->Type != ACPI_TYPE_METHOD)
        {
            sprintf (MsgBuffer, "%s is a %s", PsNode->ExternalName, AcpiUtGetTypeName (NsNode->Type));

            AslError (ASL_ERROR, ASL_MSG_NOT_METHOD, PsNode, MsgBuffer);
            return (AE_OK);
        }

        /*
         * This is a method invocation, with or without arguments.
         * Count the number of arguments, each appears as a child
         * under the parent node
         */
        PsNode->ParseOpcode = METHODCALL;
        PassedArgs          = 0;
        Next                = PsNode->Child;

        while (Next)
        {
            PassedArgs++;
            Next = Next->Peer;
        }

        if (NsNode->OwnerId != ASL_EXTERNAL_METHOD)
        {
            /*
             * Check the parsed arguments with the number expected by the
             * method declaration itself
             */
            if (PassedArgs != NsNode->OwnerId)
            {
                sprintf (MsgBuffer, "%s requires %d", PsNode->ExternalName,
                            NsNode->OwnerId);

                if (PassedArgs < NsNode->OwnerId)
                {
                    AslError (ASL_ERROR, ASL_MSG_ARG_COUNT_LO, PsNode, MsgBuffer);

                    if (NsNode->OwnerId > 7)
                    {
                        printf ("too many arguments defined for method [%4.4s]\n", (char *) &NsNode->Name);
                        return (AE_BAD_PARAMETER);
                    }
                }
                else
                {
                    AslError (ASL_ERROR, ASL_MSG_ARG_COUNT_HI, PsNode, MsgBuffer);
                }
            }

            /*
             * Check if the method caller expects this method to return a value and
             * if the called method in fact returns a value.
             */

            if (!(PsNode->Flags & NODE_RESULT_NOT_USED))
            {
                /* 1) The result from the method is used (the method is a TermArg) */

                OwningPsNode = NsNode->Object;
                if (OwningPsNode->Flags & NODE_METHOD_NO_RETVAL)
                {
                    /*
                     * 2) Method NEVER returns a value
                     */
                    AslError (ASL_ERROR, ASL_MSG_NO_RETVAL, PsNode, PsNode->ExternalName);
                }

                else if (OwningPsNode->Flags & NODE_METHOD_SOME_NO_RETVAL)
                {
                    /*
                     * 2) Method SOMETIMES returns a value, SOMETIMES not
                     */
                    AslError (ASL_WARNING, ASL_MSG_SOME_NO_RETVAL, PsNode, PsNode->ExternalName);
                }
            }
        }
    }


    /* 3) Check for an ASL Field definition */

    else if ((PsNode->Parent) &&
            ((PsNode->Parent->ParseOpcode == FIELD)     ||
             (PsNode->Parent->ParseOpcode == BANKFIELD) ||
             (PsNode->Parent->ParseOpcode == INDEXFIELD)))
    {
        /*
         * Offset checking for fields.  If the parent operation region has a
         * constant length (known at compile time), we can check fields
         * defined in that region against the region length.  This will catch
         * fields and field units that cannot possibly fit within the region.
         */
        if (PsNode == PsNode->Parent->Child)
        {
            /*
             * This is the first child of the field node, which is
             * the name of the region.  Get the parse node for the
             * region -- which contains the length of the regoin.
             */

            OwningPsNode = (ASL_PARSE_NODE *) NsNode->Object;
            PsNode->Parent->ExtraValue = MUL_8 (OwningPsNode->Value.Integer32);

            /* Examine the field access width */

            switch (PsNode->Parent->Value.Integer8)
            {
            case ACCESS_ANY_ACC:
            case ACCESS_BYTE_ACC:
            default:
                MinimumLength = 1;
                break;

            case ACCESS_WORD_ACC:
                MinimumLength = 2;
                break;

            case ACCESS_DWORD_ACC:
                MinimumLength = 4;
                break;

            case ACCESS_QWORD_ACC:
                MinimumLength = 8;
                break;
            }

            /* Is the region at least as big as the access width? */

            if (OwningPsNode->Value.Integer32 < MinimumLength)
            {
                AslError (ASL_ERROR, ASL_MSG_FIELD_ACCESS_WIDTH, PsNode, NULL);
            }
        }

        else
        {
            /*
             * This is one element of the field list
             */
            if (PsNode->Parent->ExtraValue && PsNode->Child)
            {
                /*
                 * Check each field unit against the region size.  The entire
                 * field unit (start offset plus length) must fit within the
                 * region.
                 */
                if (PsNode->Parent->ExtraValue <
                   (PsNode->ExtraValue + PsNode->Child->Value.Integer32))
                {
                    AslError (ASL_ERROR, ASL_MSG_FIELD_UNIT_OFFSET, PsNode, NULL);
                }
            }
        }

    }


    PsNode->NsNode = NsNode;

    return (Status);
}


/*****************************************************************************
 *
 * FUNCTION:    LkNamespaceLocateEnd
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Ascending callback used during cross reference.  We only
 *              need to worry about scope management here.
 *
 ****************************************************************************/

ACPI_STATUS
LkNamespaceLocateEnd (
    ASL_PARSE_NODE          *PsNode,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_WALK_STATE         *WalkState = (ACPI_WALK_STATE *) Context;
    ACPI_OBJECT_TYPE8       DataType;
    const ACPI_OPCODE_INFO  *OpInfo;


    PROC_NAME ("LkNamespaceLocateEnd");


    /* We are only interested in opcodes that have an associated name */

    OpInfo = AcpiPsGetOpcodeInfo (PsNode->AmlOpcode);
    if (!(OpInfo->Flags & AML_NAMED))
    {
        return (AE_OK);
    }


    /* Get the type to determine if we should pop the scope */

    DataType = AcpiDsMapNamedOpcodeToDataType (PsNode->AmlOpcode);

    if (PsNode->AmlOpcode == AML_NAME_OP)
    {
        /* For Name opcode, check the argument */

        if (PsNode->Child)
        {
/*
            DataType = AcpiDsMapOpcodeToDataType (
                            PsNode->Child->AmlOpcode, NULL);
            ((ACPI_NAMESPACE_NODE *)Op->Node)->Type =
                            (UINT8) DataType;
*/
        }
    }


    /* Pop the scope stack */

    if (AcpiNsOpensScope (DataType))
    {

        ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
            "%s: Popping scope for Op %p\n",
            AcpiUtGetTypeName (DataType), PsNode));


        AcpiDsScopeStackPop (WalkState);

    }

    return (AE_OK);
}


