/*******************************************************************************
 *
 * Module Name: dbdisasm - parser op tree display routines
 *              $Revision: 1.68 $
 *
 ******************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2002, Intel Corp.
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
#include "acparser.h"
#include "amlcode.h"
#include "acnamesp.h"
#include "acdebug.h"


#ifdef ENABLE_DEBUGGER

#define _COMPONENT          ACPI_DEBUGGER
        ACPI_MODULE_NAME    ("dbdisasm")


#define BLOCK_NONE          0
#define BLOCK_PAREN         1
#define BLOCK_BRACE         2
#define BLOCK_COMMA_LIST    4


NATIVE_CHAR                 *AcpiGbl_DbDisasmIndent = "....";

#define ACPI_PARSEOP_IGNORE                   0x10
#define ACPI_PARSEOP_PARAMLIST                0x20
#define ACPI_PARSEOP_EMPTY_TERMLIST           0x40



/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode control method flags
 *
 ******************************************************************************/

UINT32
AcpiDmDumpName (
    char                    *Name)
{
    UINT32                  i;
    UINT32                  Length;
    char                    *End = Name + ACPI_NAME_SIZE;


    for (i = 0; i < ACPI_NAME_SIZE; i++)
    {
        if (Name[i] != '_')
        {
            End = &Name[i];
        }
    }

    Length = (End - Name) + 1;
    for (i = 0; i < Length; i++)
    {
        AcpiOsPrintf ("%c", Name[i]);
    }

    return (Length);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDoMethodFlags
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode control method flags
 *
 ******************************************************************************/

ACPI_PARSE_OBJECT *
AcpiDmDoMethodFlags (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  Flags;
    UINT32                  Args;


    if (Op->Named.Name == 'INIX')
    {
        AcpiOsPrintf ("/* FOUND XINI */\n");
    }

    /* The next Op contains the flags */

    Op = AcpiPsGetDepthNext (NULL, Op);
    Flags = Op->Common.Value.Integer8;
    Args = Flags & 0x7;

    /* Mark the Op as completed */

    Op->Common.Flags |= ACPI_PARSEOP_IGNORE;

    /* 1) Method argument count */

    AcpiOsPrintf (", %d, ", Args);

    /* 2) Serialize rule */

    if (!(Flags & 0x4))
    {
        AcpiOsPrintf ("Not");
    }

    AcpiOsPrintf ("Serialized");

    /* 3) SyncLevel */

    if (Flags & 0xF0)
    {
        AcpiOsPrintf (", %d", Flags >> 4);
    }

    return (Op);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDoFieldFlags
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode control method flags
 *
 ******************************************************************************/

ACPI_PARSE_OBJECT *
AcpiDmDoFieldFlags (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  Flags;


    /* The next Op contains the flags */

    Op = AcpiPsGetDepthNext (NULL, Op);
    Flags = Op->Common.Value.Integer8;

    /* Mark the Op as completed */

    Op->Common.Flags |= ACPI_PARSEOP_IGNORE;

    AcpiOsPrintf ("%s, ", AcpiGbl_AccessTypes [Flags & 0x0F]);
    AcpiOsPrintf ("%s, ", AcpiGbl_LockRule [(Flags & 0x10) >> 5]);
    AcpiOsPrintf ("%s)",  AcpiGbl_UpdateRules [(Flags & 0x60) >> 6]);


    return (Op);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDoRegionFlags
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode region flags
 *
 ******************************************************************************/

ACPI_PARSE_OBJECT *
AcpiDmDoRegionFlags (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  SpaceId;



    /* The next Op contains the SpaceId */

    Op = AcpiPsGetDepthNext (NULL, Op);
    SpaceId = Op->Common.Value.Integer8;

    /* Mark the Op as completed */

    Op->Common.Flags |= ACPI_PARSEOP_IGNORE;

    if (SpaceId > ACPI_NUM_PREDEFINED_REGIONS)
    {
        AcpiOsPrintf (", 0x%X, ", SpaceId);
    }
    else
    {
        AcpiOsPrintf (", %s, ", AcpiGbl_RegionTypes [SpaceId]);
    }


    return (Op);
}



/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDoMethodOp
 *
 * PARAMETERS:  Op              - Object to be examined
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Decode region flags
 *
 ******************************************************************************/

ACPI_PARSE_OBJECT *
AcpiDmDoMethodOp (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *NextOp;


    NextOp = AcpiPsGetDepthNext (NULL, Op);
    NextOp = NextOp->Common.Next;

    NextOp->Common.AmlOpcode = AML_INT_STATICSTRING_OP;
    NextOp->Common.Value.String = (char *) AcpiGbl_MatchOps[NextOp->Common.Value.Integer32];

    NextOp = NextOp->Common.Next;
    NextOp = NextOp->Common.Next;
    NextOp->Common.AmlOpcode = AML_INT_STATICSTRING_OP;
    NextOp->Common.Value.String = (char *) AcpiGbl_MatchOps[NextOp->Common.Value.Integer32];

    return (Op);
}



/*******************************************************************************
 *
 * FUNCTION:    AcpiDmCommaIfListMember 
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: Insert a comma if this Op is a member of an argument list.
 *
 ******************************************************************************/

void 
AcpiDmCommaIfListMember (
    ACPI_PARSE_OBJECT       *Op)
{
    if (!Op->Common.Next)
    {
        return;
    }

    if (AcpiDmListType (Op->Common.Parent) & BLOCK_COMMA_LIST)
    {
        /* Check for a NULL target operand */

        if ((Op->Common.Next->Common.AmlOpcode == AML_INT_NAMEPATH_OP) &&
            (!Op->Common.Next->Common.Value.String))
        {
            return;
        }

        if ((Op->Common.Flags & ACPI_PARSEOP_PARAMLIST) &&
            (!(Op->Common.Next->Common.Flags & ACPI_PARSEOP_PARAMLIST)))
        {
            return;
        }

        AcpiOsPrintf (", ");
    }

    else if ((Op->Common.Flags & ACPI_PARSEOP_PARAMLIST) &&
        (Op->Common.Next->Common.Flags & ACPI_PARSEOP_PARAMLIST))
    {
        AcpiOsPrintf (", ");
    }

}

void 
AcpiDmCommaIfFieldMember (
    ACPI_PARSE_OBJECT       *Op)
{
    if (Op->Common.Next)
    {
        AcpiOsPrintf (", ");
    }
}

/*******************************************************************************
 *
 * FUNCTION:    AcpiPsDisplayObjectPathname
 *
 * PARAMETERS:  Op              - Object whose pathname is to be obtained
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Diplay the pathname associated with a named object.  Two
 *              versions. One searches the parse tree (for parser-only
 *              applications suchas AcpiDump), and the other searches the
 *              ACPI namespace (the parse tree is probably deleted)
 *
 ******************************************************************************/

#ifdef PARSER_ONLY

ACPI_STATUS
AcpiPsDisplayObjectPathname (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *TargetOp;
    char                    *Name;


    if (Op->Common.Flags & ACPI_PARSEOP_GENERIC)
    {
        Name = Op->Common.Value.Name;
        if (Name[0] == '\\')
        {
            AcpiOsPrintf ("  (Fully Qualified Pathname)");
            return (AE_OK);
        }
    }
    else
    {
        Name = (char *) &Op->Named.Name;
    }

    /* Search parent tree up to the root if necessary */

    TargetOp = AcpiPsFind (Op, Name, 0, 0);
    if (!TargetOp)
    {
        /*
         * Didn't find the name in the parse tree.  This may be
         * a problem, or it may simply be one of the predefined names
         * (such as _OS_).  Rather than worry about looking up all
         * the predefined names, just display the name as given
         */
        AcpiOsPrintf ("  **** Path not found in parse tree");
    }
    else
    {
        /* The target was found, print the name and complete path */

        AcpiOsPrintf ("  (Path ");
        AcpiDmDisplayPath (TargetOp);
        AcpiOsPrintf (")");
    }

    return (AE_OK);
}

#else

ACPI_STATUS
AcpiPsDisplayObjectPathname (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_BUFFER             Buffer;
    UINT32                  DebugLevel;


    /* Save current debug level so we don't get extraneous debug output */

    DebugLevel = AcpiDbgLevel;
    AcpiDbgLevel = 0;

    /* Just get the Node out of the Op object */

    Node = Op->Common.Node;
    if (!Node)
    {
        /* Node not defined in this scope, look it up */

        Status = AcpiNsLookup (WalkState->ScopeInfo, Op->Common.Value.String, ACPI_TYPE_ANY,
                        ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT, WalkState, &(Node));

        if (ACPI_FAILURE (Status))
        {
            /*
             * We can't get the pathname since the object
             * is not in the namespace.  This can happen during single
             * stepping where a dynamic named object is *about* to be created.
             */
            AcpiOsPrintf ("  [Path not found]");
            goto Exit;
        }

        /* Save it for next time. */

        Op->Common.Node = Node;
    }

    /* Convert NamedDesc/handle to a full pathname */

    Buffer.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    Status = AcpiNsHandleToPathname (Node, &Buffer);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("****Could not get pathname****)");
        goto Exit;
    }

    AcpiOsPrintf ("  (Path %s)", Buffer.Pointer);
    ACPI_MEM_FREE (Buffer.Pointer);


Exit:
    /* Restore the debug level */

    AcpiDbgLevel = DebugLevel;
    return (Status);
}

#endif



/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDisplayNamestring
 *
 * PARAMETERS:  Name                - ACPI Name string to store
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display namestring. Handles prefix characters
 *
 ******************************************************************************/

void
AcpiDmDisplayNamestring (
    NATIVE_CHAR             *Name)
{
    UINT32                  SegCount;


    if (!Name)
    {
//        AcpiOsPrintf ("<NULL NAME PTR>");
        return;
    }

    /* Handle all Scope Prefix operators */

    while (AcpiPsIsPrefixChar (ACPI_GET8 (Name)))
    {
        /* Append prefix character */

        AcpiOsPrintf ("%1c", ACPI_GET8 (Name));
        Name++;
    }

    switch (ACPI_GET8 (Name))
    {
    case 0:
        SegCount = 0;
        break;

    case AML_DUAL_NAME_PREFIX:
        SegCount = 2;
        Name++;
        break;

    case AML_MULTI_NAME_PREFIX_OP:
        SegCount = (UINT32) ACPI_GET8 (Name + 1);
        Name += 2;
        break;

    default:
        SegCount = 1;
        break;
    }

    while (SegCount)
    {
        /* Append Name segment */

        AcpiDmDumpName ((char *) Name);

        SegCount--;
        if (SegCount)
        {
            /* Not last name, append dot separator */

            AcpiOsPrintf (".");
        }
        Name += ACPI_NAME_SIZE;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDisplayPath
 *
 * PARAMETERS:  Op                  - Named Op whose path is to be constructed
 *
 * RETURN:      None
 *
 * DESCRIPTION: Walk backwards from current scope and display the name
 *              of each previous level of scope up to the root scope
 *              (like "pwd" does with file systems)
 *
 ******************************************************************************/

void
AcpiDmDisplayPath (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Prev;
    ACPI_PARSE_OBJECT       *Search;
    UINT32                  Name;
    BOOLEAN                 DoDot = FALSE;
    ACPI_PARSE_OBJECT       *NamePath;
    const ACPI_OPCODE_INFO  *OpInfo;


    /* We are only interested in named objects */

    OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
    if (!(OpInfo->Flags & AML_NSNODE))
    {
        return;
    }

    if (OpInfo->Flags & AML_CREATE)
    {
        /* Field creation - check for a fully qualified namepath */

        if (Op->Common.AmlOpcode == AML_CREATE_FIELD_OP)
        {
            NamePath = AcpiPsGetArg (Op, 3);
        }
        else
        {
            NamePath = AcpiPsGetArg (Op, 2);
        }

        if ((NamePath) &&
            (NamePath->Common.Value.String) &&
            (NamePath->Common.Value.String[0] == '\\'))
        {
            AcpiDmDisplayNamestring (NamePath->Common.Value.String);
            return;
        }
    }

    Prev = NULL;            /* Start with Root Node */

    while (Prev != Op)
    {
        /* Search upwards in the tree to find scope with "prev" as its parent */

        Search = Op;
        for (; ;)
        {
            if (Search->Common.Parent == Prev)
            {
                break;
            }

            /* Go up one level */

            Search = Search->Common.Parent;
        }

        if (Prev)
        {
            OpInfo = AcpiPsGetOpcodeInfo (Search->Common.AmlOpcode);
            if (!(OpInfo->Flags & AML_FIELD))
            {
                /* below root scope, append scope name */

                if (DoDot)
                {
                    /* append dot */

                    AcpiOsPrintf (".");
                }

                if (OpInfo->Flags & AML_CREATE)
                {
                    if (Op->Common.AmlOpcode == AML_CREATE_FIELD_OP)
                    {
                        NamePath = AcpiPsGetArg (Op, 3);
                    }
                    else
                    {
                        NamePath = AcpiPsGetArg (Op, 2);
                    }

                    if ((NamePath) &&
                        (NamePath->Common.Value.String))
                    {
                        AcpiDmDumpName (NamePath->Common.Value.String);
                    }
                }
                else
                {
                    Name = AcpiPsGetName (Search);
                    AcpiDmDumpName ((char *) &Name);
                }

                DoDot = TRUE;
            }
        }

        Prev = Search;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDmDisplayOpcode
 *
 * PARAMETERS:  Op                  - Op that is to be printed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store printed op in a Buffer and return its length
 *              (or -1 if out of space)
 *
 * NOTE: Terse mode prints out ASL-like code.  Verbose mode adds more info.
 *
 ******************************************************************************/

ACPI_PARSE_OBJECT *
AcpiDmDisplayOpcode (
    ACPI_WALK_STATE         *WalkState,
    ACPI_OP_WALK_INFO       *Info,    
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  i;
    const ACPI_OPCODE_INFO  *OpInfo = NULL;
    UINT32                  Offset;


    if (!Op)
    {
        AcpiOsPrintf ("<NULL OP PTR>");
        return (Op);
    }

    /* op and arguments */

    switch (Op->Common.AmlOpcode)
    {
    case AML_ZERO_OP:

        AcpiOsPrintf ("Zero");
        break;


    case AML_ONE_OP:

        AcpiOsPrintf ("One");
        break;


    case AML_ONES_OP:

        AcpiOsPrintf ("Ones");
        break;


    case AML_REVISION_OP:

        AcpiOsPrintf ("Revision");
        break;


    case AML_BYTE_OP:

        AcpiOsPrintf ("0x%X", (UINT32) Op->Common.Value.Integer8);
        break;


    case AML_WORD_OP:

        AcpiOsPrintf ("0x%X", (UINT32) Op->Common.Value.Integer16);
        break;


    case AML_DWORD_OP:

        AcpiOsPrintf ("0x%X", Op->Common.Value.Integer32);
        break;


    case AML_QWORD_OP:

        AcpiOsPrintf ("0x%X%8.8X", Op->Common.Value.Integer64.Hi,
                                  Op->Common.Value.Integer64.Lo);
        break;


    case AML_STRING_OP:

        if (Op->Common.Value.String)
        {
            AcpiOsPrintf ("\"");
            for (i = 0; Op->Common.Value.String[i]; i++)
            {
                switch (Op->Common.Value.String[i])
                {
                case '"':
                    AcpiOsPrintf ("\\");
                    break;

                /* TBD: Handle escapes here */
                default:
                    break;
                }

                AcpiOsPrintf ("%c", Op->Common.Value.String[i]);
            }
            AcpiOsPrintf ("\"");
        }
        else
        {
            AcpiOsPrintf ("<\"NULL STRING PTR\">");
        }
        break;


    case AML_BUFFER_OP:

        if (AcpiDmIsResourceDescriptor (Op))
        {
            AcpiOsPrintf ("ResourceTemplate");
        }
        else
        {
            AcpiOsPrintf ("Buffer");
        }
        break;


    case AML_INT_STATICSTRING_OP:

        if (Op->Common.Value.String)
        {
            AcpiOsPrintf ("%s", Op->Common.Value.String);
        }
        else
        {
            AcpiOsPrintf ("\"<NULL STATIC STRING PTR>\"");
        }
        break;


    case AML_INT_NAMEPATH_OP:

        AcpiDmDisplayNamestring (Op->Common.Value.Name);
        break;


    case AML_INT_NAMEDFIELD_OP:

        AcpiDmDumpName ((char *) &Op->Named.Name);
        AcpiOsPrintf (", %d", Op->Common.Value.Integer32);
        AcpiDmCommaIfFieldMember (Op);

        Info->BitOffset += Op->Common.Value.Integer32;
        break;


    case AML_INT_RESERVEDFIELD_OP:

        /* TBD: offset is wrong, must account for previous offsets */

        Offset = Op->Common.Value.Integer32;
        Info->BitOffset += Offset;

        if (Info->BitOffset % 8 == 0)
        {
            AcpiOsPrintf ("Offset (0x%X)", (Info->BitOffset / 8));
        }
        else
        {
            AcpiOsPrintf ("    , %d", Offset);
        }

        AcpiDmCommaIfFieldMember (Op);
        break;


    case AML_INT_ACCESSFIELD_OP:

        AcpiOsPrintf ("AccessAs (%s, 0x%X)", AcpiGbl_AccessTypes [Op->Common.Value.Integer32 >> 8], Op->Common.Value.Integer32 & 0x0F);
        AcpiDmCommaIfFieldMember (Op);
        break;


    case AML_INT_BYTELIST_OP:

        AcpiDmDoByteList (Info, Op);
        break;


    case AML_INT_METHODCALL_OP:

        OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
        Op = AcpiPsGetDepthNext (NULL, Op);
        Op->Common.Flags |= ACPI_PARSEOP_IGNORE;

        AcpiDmDisplayNamestring (Op->Common.Value.Name);
        break;


    default:

        /* Just get the opcode name and print it */

        OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
        AcpiOsPrintf ("%s", OpInfo->Name);


#ifndef PARSER_ONLY
        if ((Op->Common.AmlOpcode == AML_INT_RETURN_VALUE_OP) &&
            (WalkState) &&
            (WalkState->Results) &&
            (WalkState->Results->Results.NumResults))
        {
            AcpiDbDecodeInternalObject (
                WalkState->Results->Results.ObjDesc [WalkState->Results->Results.NumResults-1]);
        }
#endif
        break;
    }

    return (Op);
}

#endif  /* ENABLE_DEBUGGER */
