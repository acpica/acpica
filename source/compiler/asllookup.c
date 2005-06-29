/******************************************************************************
 *
 * Module Name: asllookup- Namespace lookup
 *              $Revision: 1.68 $
 *
 *****************************************************************************/

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


#include "aslcompiler.h"
#include "aslcompiler.y.h"

#include "acparser.h"
#include "amlcode.h"
#include "acnamesp.h"
#include "acdispat.h"


#define _COMPONENT          ACPI_COMPILER
        ACPI_MODULE_NAME    ("asllookup")


/*******************************************************************************
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
 ******************************************************************************/

ACPI_STATUS
LsDoOneNamespaceObject (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_NAMESPACE_NODE     *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;
    ACPI_PARSE_OBJECT       *Op;


    Gbl_NumNamespaceObjects++;

    FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "%5d  [%d]  %*s %4.4s - %s",
                        Gbl_NumNamespaceObjects, Level, (Level * 3), " ",
                        &Node->Name,
                        AcpiUtGetTypeName (Node->Type));

    Op = ACPI_CAST_PTR (ACPI_PARSE_OBJECT, Node->Object);

    if (Op)
    {
        if (Op->Asl.ParseOpcode == PARSEOP_NAME)
        {
            Op = Op->Asl.Child;
        }

        switch (Node->Type)
        {
        case ACPI_TYPE_INTEGER:

            if ((Op->Asl.ParseOpcode == PARSEOP_NAMESEG)  ||
                (Op->Asl.ParseOpcode == PARSEOP_NAMESTRING))
            {
                Op = Op->Asl.Next;
            }

            if (Op->Asl.Value.Integer > ACPI_UINT32_MAX)
            {
                FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "    [Initial Value = 0x%X%X]",
                            ACPI_HIDWORD (Op->Asl.Value.Integer64), Op->Asl.Value.Integer32);
            }
            else
            {
                FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "    [Initial Value = 0x%X]",
                            Op->Asl.Value.Integer32);
            }
            break;


        case ACPI_TYPE_STRING:
            if ((Op->Asl.ParseOpcode == PARSEOP_NAMESEG)  ||
                (Op->Asl.ParseOpcode == PARSEOP_NAMESTRING))
            {
                Op = Op->Asl.Next;
            }

            FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "    [Initial Value = \"%s\"]",
                        Op->Asl.Value.String);
            break;


        case INTERNAL_TYPE_REGION_FIELD:
            if ((Op->Asl.ParseOpcode == PARSEOP_NAMESEG)  ||
                (Op->Asl.ParseOpcode == PARSEOP_NAMESTRING))
            {
                Op = Op->Asl.Child;
            }
            FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "    [Length = 0x%02X]",
                        Op->Asl.Value.Integer32);
            break;


        default:
            /* Nothing to do for other types */
            break;
        }
    }

    FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "\n");
    return (AE_OK);
}


/*******************************************************************************
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
 ******************************************************************************/

ACPI_STATUS
LsDisplayNamespace (
    void)
{
    ACPI_STATUS             Status;


    if (!Gbl_NsOutputFlag)
    {
        return (AE_OK);
    }

    /* File header */

    FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "Contents of ACPI Namespace\n\n");
    FlPrintFile (ASL_FILE_NAMESPACE_OUTPUT, "Count  Depth    Name - Type\n\n");

    /* Walk entire namespace from the root */

    Status = AcpiNsWalkNamespace (ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
                                ACPI_UINT32_MAX, FALSE, LsDoOneNamespaceObject,
                                NULL, NULL);
    return (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    LsCompareOneNamespaceObject
 *
 * PARAMETERS:  ACPI_WALK_CALLBACK
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Compare name of one object.
 *
 ******************************************************************************/

ACPI_STATUS
LsCompareOneNamespaceObject (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_NAMESPACE_NODE     *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;


    /* Simply check the name */

    if (*((UINT32 *) (Context)) == Node->Name.Integer)
    {
        /* Abort walk if we found one instance */

        return (AE_CTRL_TRUE);
    }

    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    LkObjectExists
 *
 * PARAMETERS:  Name            - 4 char ACPI name
 *
 * RETURN:      TRUE if name exists in namespace
 *
 * DESCRIPTION: Walk the namespace to find an object
 *
 ******************************************************************************/

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


/*******************************************************************************
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
 ******************************************************************************/

ACPI_STATUS
LkCrossReferenceNamespace (
    void)
{
    ACPI_WALK_STATE         *WalkState;


    DbgPrint (ASL_DEBUG_OUTPUT, "\nCross referencing namespace\n\n");

    /*
     * Create a new walk state for use when looking up names
     * within the namespace (Passed as context to the callbacks)
     */
    WalkState = AcpiDsCreateWalkState (TABLE_ID_DSDT, NULL, NULL, NULL);
    if (!WalkState)
    {
        return AE_NO_MEMORY;
    }

    /* Walk the entire parse tree */

    TrWalkParseTree (RootNode, ASL_WALK_VISIT_TWICE, LkNamespaceLocateBegin,
                        LkNamespaceLocateEnd, WalkState);
    return AE_OK;
}


/*******************************************************************************
 *
 * FUNCTION:    LkCheckFieldRange
 *
 * PARAMETERS:  RegionBitLength     - Length of entire parent region
 *              FieldBitOffset      - Start of the field unit (within region)
 *              FieldBitLength      - Entire length of field unit
 *              AccessBitWidth      - Access width of the field unit
 *
 * RETURN:      None
 *
 * DESCRIPTION: Check one field unit to make sure it fits in the parent
 *              op region.
 *
 * Note: AccessBitWidth must be either 8,16,32, or 64
 *
 ******************************************************************************/

void
LkCheckFieldRange (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  RegionBitLength,
    UINT32                  FieldBitOffset,
    UINT32                  FieldBitLength,
    UINT32                  AccessBitWidth)
{
    UINT32                  FieldEndBitOffset;

    /*
     * Check each field unit against the region size.  The entire
     * field unit (start offset plus length) must fit within the
     * region.
     */
    FieldEndBitOffset = FieldBitOffset + FieldBitLength;

    if (FieldEndBitOffset > RegionBitLength)
    {
        /* Field definition itself is beyond the end-of-region */

        AslError (ASL_ERROR, ASL_MSG_FIELD_UNIT_OFFSET, Op, NULL);
        return;
    }

    /*
     * Now check that the field plus AccessWidth doesn't go beyond
     * the end-of-region.  Assumes AccessBitWidth is a power of 2
     */
    FieldEndBitOffset = ACPI_ROUND_UP (FieldEndBitOffset, AccessBitWidth);

    if (FieldEndBitOffset > RegionBitLength)
    {
        /* Field definition combined with the access is beyond EOR */

        AslError (ASL_ERROR, ASL_MSG_FIELD_UNIT_ACCESS_WIDTH, Op, NULL);
    }
}

UINT32 OptTotal = 0;
/*******************************************************************************
 *
 * FUNCTION:    LkOptimizeNamedReference
 *
 * PARAMETERS:  Op                  - Current parser op
 *              WalkState           - Current state
 *              AmlNameString       - Unoptimized namepath
 *              TargetNode          - Node to which AmlNameString refers
 *
 * RETURN:      None.  If path is optimized, the Op is updated with new path
 *
 * DESCRIPTION: Optimize a Named Reference to the minimal length.  Must take
 *              into account both the current location in the namespace and
 *              the actual reference path.
 *
 ******************************************************************************/

void
LkOptimizeNamePath (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Flags,
    ACPI_WALK_STATE         *WalkState,
    NATIVE_CHAR             *AmlNameString,
    ACPI_NAMESPACE_NODE     *TargetNode)
{
    ACPI_STATUS             Status;
    ACPI_BUFFER             TargetPath;
    ACPI_BUFFER             CurrentPath;
    ACPI_SIZE               TargetPathLength;
    ACPI_SIZE               CurrentPathLength;
    ACPI_SIZE               AmlNameStringLength;
    UINT32                  NumCommonSegments;
    UINT32                  MaxCommonSegments;
    ACPI_NAMESPACE_NODE     *CurrentNode;
    ACPI_NAMESPACE_NODE     *Node = NULL;
    char                    *ExternalNameString;
    char                    *NewPath = NULL;
    char                    *NewPathExternal;
    UINT32                  OptCount = 0;
    NATIVE_UINT             Index;
    UINT32                  NumCarats;
    NATIVE_UINT             i;
    ACPI_GENERIC_STATE      ScopeInfo;


    ACPI_FUNCTION_TRACE ("LkOptimizeNamedReference");

#if 0
    if (Flags & AML_NAMED)
    {
        return_VOID;
    }
#endif
    /* This is an optional optimization */

    if (!Gbl_ReferenceOptimizationFlag)
    {
        return_VOID;
    }

    /* Various required items */

    if (!TargetNode || !WalkState)
    {
        return_VOID;
    }

    /* We don't want to optimize paths for certain opcodes */

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "%5d [%12.12s] [%12.12s] ", 
        Op->Asl.LogicalLineNumber, 
        AcpiPsGetOpcodeName (Op->Common.Parent->Common.AmlOpcode), 
        AcpiPsGetOpcodeName (Op->Common.AmlOpcode)));

    if (Flags & AML_NAMED)
    {
#if 0
        if (Op->Common.AmlOpcode == AML_ALIAS_OP)
        {
            Flags &= ~AML_NAMED;
        }
#endif
    }
#if 0
    else if (Flags & AML_CREATE)
    {
    }
#endif
    else
    {
        /* We don't want to fuss with actual name declaration nodes here */

        if (Op->Asl.CompileFlags & NODE_IS_NAME_DECLARATION)
        {
            ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "******* NAME DECLARATION")); 
            goto Exit;
        }
    }

    /* 
     * The original path must be longer than one NameSeg (4 chars) for there
     * to be any possibility that it can be optimized to a shorter string 
     */
    AmlNameStringLength = ACPI_STRLEN (AmlNameString);
    if (AmlNameStringLength <= ACPI_NAME_SIZE)
    {
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "NAMESEG %4.4s", AmlNameString)); 
        goto Exit;
    }

    CurrentNode = AcpiGbl_RootNode;
    if (Flags & (AML_NAMED | AML_CREATE))
    {
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "NAME"));
        if (WalkState->ScopeInfo)
        {
            if (AcpiNsOpensScope (TargetNode->Type))
            {
                CurrentNode = AcpiNsGetParentNode (WalkState->ScopeInfo->Scope.Node);
            }
            else
            {
                CurrentNode = WalkState->ScopeInfo->Scope.Node;
            }
        }
    }
    else
    {
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "REF "));
        if (WalkState->ScopeInfo)
        {
            CurrentNode = WalkState->ScopeInfo->Scope.Node;
        }
    }

    ScopeInfo.Scope.Node = CurrentNode;

    /*
     * Convert the namestrings (Target and current namespace location) to
     * external format -- something we can easily manipulate
     */
    TargetPath.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    Status = AcpiNsHandleToPathname (TargetNode, &TargetPath);
    if (ACPI_FAILURE (Status))
    {
        AslAbort ();
    }
    TargetPathLength = ACPI_STRLEN (TargetPath.Pointer);

    /* CurrentPath is the path to this scope (where we are in the namespace) */

    CurrentPath.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    Status = AcpiNsHandleToPathname (CurrentNode, &CurrentPath);
    if (ACPI_FAILURE (Status))
    {
        AslAbort ();
    }
    CurrentPathLength = ACPI_STRLEN (CurrentPath.Pointer);

    /* Debug output only */

    Status = AcpiNsExternalizeName (ACPI_UINT32_MAX, AmlNameString, 
                NULL, &ExternalNameString);
    if (ACPI_FAILURE (Status))
    {
        AslAbort ();
    }

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, 
        "%37s (%2d) ==> %-32s(%2d) %-32s",
        (char *) CurrentPath.Pointer, CurrentPathLength,
        (char *) TargetPath.Pointer, TargetPathLength, ExternalNameString));

    ACPI_MEM_FREE (ExternalNameString);

    Status = AE_NOT_FOUND;
    if (!(Flags & (AML_NAMED | AML_CREATE)))
    {
        /* 
         * Check if search-to-root can be utilized.  Use the last NameSeg of
         * the NamePath and 1) See if can be found and 2) If found, make
         * sure that it is the same node that we want.  If there is another
         * name in the search path before the one we want, the nodes will
         * not match, and we cannot use this optimization.
         */
        NewPath = &(((NATIVE_CHAR *) TargetPath.Pointer)[TargetPathLength - ACPI_NAME_SIZE]);
        NewPathExternal = NewPath;

        /* Lookup the NameSeg using SEARCH_PARENT (search-to-root) */

        Status = AcpiNsLookup (&ScopeInfo,  NewPath,
                                ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
                                ACPI_NS_SEARCH_PARENT, WalkState, &(Node));
        if (ACPI_SUCCESS (Status))
        {
            /* 
             * We found the name, but we must check to make sure that the node
             * matches.  Otherwise, there is another identical name in the search
             * path that precludes the use of this optimization.
             */
            if (Node == TargetNode)
            {
                /* Found the node, we can use this optimization */

                ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
                    "NAMESEG:   %-24s", NewPath));
                OptCount = (AmlNameStringLength - ACPI_NAME_SIZE);

                /* We must allocate a new string for the name (TargetPath gets deleted) */

                NewPath = ACPI_MEM_CALLOCATE (ACPI_NAME_SIZE + 1);
                ACPI_STRCPY (NewPath, NewPathExternal);

                AslError (ASL_OPTIMIZATION, ASL_MSG_SINGLE_NAME_OPTIMIZATION, Op, 
                    NewPathExternal);
            }
            else
            {
                /* This means that another object with the same name was found first */

                Status = AE_NOT_FOUND;
            }
        }
    }
    else
    {
        if (((CurrentNode == AcpiGbl_RootNode) || 
            (Op->Common.Parent->Asl.ParseOpcode == PARSEOP_DEFINITIONBLOCK)) && 
                (AmlNameString[0] == '\\'))
        {
            NewPath = &AmlNameString[1];

            Status = AcpiNsExternalizeName (ACPI_UINT32_MAX, NewPath, 
                        NULL, &ExternalNameString);
            if (ACPI_FAILURE (Status))
            {
                /* TBD: this simply quietly aborts! */

                AslAbort ();
            }
            AslError (ASL_OPTIMIZATION, ASL_MSG_NAME_OPTIMIZATION, Op, ExternalNameString);
            
            ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
                "AT ROOT:   %-24s", ExternalNameString));

            ACPI_MEM_FREE (ExternalNameString);
            OptCount = 1;
            Status = AE_OK;
        }
    }

    /*
     * If search-to-root could not be used, attempt to optimize the namestring
     * with carats (up-arrow)
     */
    if (ACPI_FAILURE (Status))
    {
        /*
         * Determine the maximum number of NameSegs that the Target and Current paths
         * can possibly have in common.  (To optimize, we have to have at least 1) 
         * 
         * Note: The external NamePath string lengths are always a multiple of 5 
         * (ACPI_NAME_SIZE + separator)
         */
        MaxCommonSegments = TargetPathLength / PATH_SEGMENT_LENGTH;
        if (CurrentPathLength < TargetPathLength)
        {
            MaxCommonSegments = CurrentPathLength / PATH_SEGMENT_LENGTH;
        }

        /* 
         * Determine how many NameSegs the two paths have in common.
         * (Starting from the root)
         */
        for (NumCommonSegments = 0; 
             NumCommonSegments < MaxCommonSegments; 
             NumCommonSegments++)
        {
            /* Compare two single NameSegs */

            if (ACPI_STRNCMP (
                &((NATIVE_CHAR *) TargetPath.Pointer)[(NumCommonSegments * PATH_SEGMENT_LENGTH) + 1],
                &((NATIVE_CHAR *) CurrentPath.Pointer)[(NumCommonSegments * PATH_SEGMENT_LENGTH) + 1],
                ACPI_NAME_SIZE))
            {
                break;
            }
        }

        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " COMMON: %d", NumCommonSegments));

        /* There must be at least 1 common NameSeg in order to optimize */

        if (NumCommonSegments > 0)
        {
            /* Determine how many prefix Carats are required */

            NumCarats = (CurrentPathLength / PATH_SEGMENT_LENGTH) - NumCommonSegments;
            Index = (NumCommonSegments * PATH_SEGMENT_LENGTH) + 1 - NumCarats;

            /* Insert the Carats into the Target string */

            for (i = 0; i < NumCarats; i++)
            {
                ((NATIVE_CHAR *) TargetPath.Pointer)[Index + i] = '^';
            }

            NewPathExternal = &((NATIVE_CHAR *) TargetPath.Pointer)[Index];
            ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " %-24s", NewPathExternal));

            /*
             * Internalize the new target string and check it against the original string
             * to make sure that this is in fact an optimization.  If the original string
             * is already optimal, there is no point in continuing.
             */
            AcpiNsInternalizeName (NewPathExternal, &NewPath);

            if (ACPI_STRLEN (NewPath) < AmlNameStringLength)
            {
                /* 
                 * Check to make sure that the optimization finds the node we are
                 * looking for.  This is simply a sanity check on the new
                 * path that has been created.
                 */
                Status = AcpiNsLookup (&ScopeInfo,  NewPath,
                                        ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
                                        0, WalkState, &(Node));
                if (ACPI_SUCCESS (Status))
                {
                    /* Found the namepath, but make sure the node is correct */

                    if (Node == TargetNode)
                    {
                        /* The lookup matched the node, accept this optimization */

                        OptCount = (AmlNameStringLength - ACPI_STRLEN (NewPath));
                        AslError (ASL_OPTIMIZATION, ASL_MSG_NAME_OPTIMIZATION, Op, NewPathExternal);
                    }
                    else
                    {
                        /* Node is not correct, do not use this optimization */

                        Status = AE_NOT_FOUND;
                        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " WRONG NODE"));
                        AslError (ASL_WARNING, ASL_MSG_COMPILER_INTERNAL, Op, 
                            "Not using optimized name - found wrong node");
                    }
                }
                else
                {
                    /* The lookup failed, we obviously cannot use this optimization */

                    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " NOT FOUND"));
                    AslError (ASL_WARNING, ASL_MSG_COMPILER_INTERNAL, Op, 
                        "Not using optimized name - did not find node");
                }
            }
            else
            {
                ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " NOT SHORTER (New %d old %d)", 
                    ACPI_STRLEN (NewPath), AmlNameStringLength));
            }
        }
    }

    /* 
     * Success from above indicates that the NamePath was successfully
     * optimized
     */
    if (ACPI_SUCCESS (Status))
    {
        OptTotal += OptCount;
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " REDUCED %2d (%d)", OptCount, OptTotal));

        if (Flags & AML_NAMED)
        {
            Op->Asl.Child->Asl.Value.String = NewPath;
            Op->Asl.Child->Asl.AmlLength = ACPI_STRLEN (NewPath);
        }
        else if (Flags & AML_CREATE)
        {
            ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " NOT HANDLED - CREATE FIELD"));
        }
        else
        {
            /* Update the parse node with the new NamePath */

            Op->Asl.Value.String = NewPath;
            Op->Asl.AmlLength = ACPI_STRLEN (NewPath);
        }
    }
    else
    {
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " ALREADY OPTIMAL"));
    }

    ACPI_MEM_FREE (TargetPath.Pointer);
    ACPI_MEM_FREE (CurrentPath.Pointer);

Exit:
    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "\n"));
    return_VOID;
}

#if 0
/*******************************************************************************
 *
 * FUNCTION:    LkOptimizeName
 *
 * PARAMETERS:  Op                  - Current parser op
 *              WalkState           - Current state
 *              AmlNameString       - Unoptimized namepath
 *              TargetNode          - Node to which AmlNameString refers
 *
 * RETURN:      None.  If path is optimized, the Op is updated with new path
 *
 * DESCRIPTION: Optimize a Name to the minimal length.  Must take
 *              into account both the current location in the namespace and
 *              the actual path.
 *
 ******************************************************************************/

void
LkOptimizeName (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState,
    NATIVE_CHAR             *AmlNameString,
    ACPI_NAMESPACE_NODE     *TargetNode)
{
    ACPI_SIZE               AmlNameStringLength;
    char                    *ExternalNameString;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE ("LkOptimizeName");



    /* This is an optional optimization */

    if (!Gbl_ReferenceOptimizationFlag)
    {
        return_VOID;
    }

    /* 
     * The original path must be longer than one NameSeg (4 chars) for there
     * to be any possibility that it can be optimized to a shorter string 
     */
    AmlNameStringLength = ACPI_STRLEN (AmlNameString);
    if (AmlNameStringLength <= 4)
    {
        return_VOID;
    }

    if (!WalkState->ScopeInfo || 
        (WalkState->ScopeInfo->Scope.Node == AcpiGbl_RootNode))
    {
        if (AmlNameString[0] == '\\')
        {
            Op->Asl.Child->Asl.Value.String = &AmlNameString[1];
            Op->Asl.Child->Asl.AmlLength = AmlNameStringLength - 1;

            Status = AcpiNsExternalizeName (ACPI_UINT32_MAX, Op->Asl.Child->Asl.Value.String, 
                        NULL, &ExternalNameString);
            if (ACPI_FAILURE (Status))
            {
                /* TBD: this simply quietly aborts! */

                AslAbort ();
            }
            AslError (ASL_OPTIMIZATION, ASL_MSG_NAME_OPTIMIZATION, Op, ExternalNameString);
            ACPI_MEM_FREE (ExternalNameString);
        }
    }

    return_VOID;
}

#endif

/*******************************************************************************
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
 *       resolved to integer values here.  Therefore, this step is an
 *       important part of the code generation.  We don't know that the
 *       name refers to a resource descriptor until now.
 *
 ******************************************************************************/

ACPI_STATUS
LkNamespaceLocateBegin (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_WALK_STATE         *WalkState = (ACPI_WALK_STATE *) Context;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_STATUS             Status;
    ACPI_OBJECT_TYPE        ObjectType;
    NATIVE_CHAR             *Path;
    UINT8                   PassedArgs;
    ACPI_PARSE_OBJECT       *NextOp;
    ACPI_PARSE_OBJECT       *OwningOp;
    ACPI_PARSE_OBJECT       *SpaceIdOp;
    UINT32                  MinimumLength;
    UINT32                  Temp;
    const ACPI_OPCODE_INFO  *OpInfo;


    ACPI_FUNCTION_NAME ("LkNamespaceLocateBegin");
    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH, "NamespaceLocateBegin: Op %p\n", Op));


    /*
     * If this node is the actual declaration of a name 
     * [such as the XXXX name in "Method (XXXX)"],
     * we are not interested in it here.  We only care about names that are
     * references to other objects within the namespace and the parent objects
     * of name declarations
     */
    if (Op->Asl.CompileFlags & NODE_IS_NAME_DECLARATION)
    {
        return (AE_OK);
    }

    /* We are only interested in opcodes that have an associated name */

    OpInfo = AcpiPsGetOpcodeInfo (Op->Asl.AmlOpcode);

    if ((!(OpInfo->Flags & AML_NAMED)) &&
        (!(OpInfo->Flags & AML_CREATE)) &&
        (Op->Asl.ParseOpcode != PARSEOP_NAMESTRING) &&
        (Op->Asl.ParseOpcode != PARSEOP_NAMESEG)    &&
        (Op->Asl.ParseOpcode != PARSEOP_METHODCALL))
    {
        return (AE_OK);
    }

    /* Get the NamePath from the appropriate place */

    if (OpInfo->Flags & AML_NAMED)
    {
        Path = Op->Asl.Child->Asl.Value.String;
        if (Op->Asl.AmlOpcode == AML_ALIAS_OP)
        {
            Path = Op->Asl.Child->Asl.Next->Asl.Value.String;
        }
    }
    else if (OpInfo->Flags & AML_CREATE)
    {
        /* Name must appear as the last parameter */

        NextOp = Op->Asl.Child;
        while (!(NextOp->Asl.CompileFlags & NODE_IS_NAME_DECLARATION))
        {
            NextOp = NextOp->Asl.Next;
        }
        Path = NextOp->Asl.Value.String;
    }
    else
    {
        Path = Op->Asl.Value.String;
    }

    ObjectType = AslMapNamedOpcodeToDataType (Op->Asl.AmlOpcode);
    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH, "NamespaceLocateBegin: Type=%X\n", ObjectType));

    /*
     * Lookup the name in the namespace.  Name must exist at this point, or it
     * is an invalid reference.
     *
     * The namespace is also used as a lookup table for references to resource
     * descriptors and the fields within them.
     */
    Gbl_NsLookupCount++;

    Status = AcpiNsLookup (WalkState->ScopeInfo,  Path,
                            ObjectType, ACPI_IMODE_EXECUTE,
                            ACPI_NS_SEARCH_PARENT, WalkState, &(Node));
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

                    AslError (ASL_ERROR, ASL_MSG_NOT_REACHABLE, Op, Op->Asl.ExternalName);
                }
                else
                {
                    /* The name doesn't exist, period */

                    AslError (ASL_ERROR, ASL_MSG_NOT_EXIST, Op, Op->Asl.ExternalName);
                }
            }
            else
            {
                /* Check for a fully qualified path */

                if (Path[0] == AML_ROOT_PREFIX)
                {
                    /* Gave full path, the object does not exist */

                    AslError (ASL_ERROR, ASL_MSG_NOT_EXIST, Op, Op->Asl.ExternalName);
                }
                else
                {
                    /* We can't tell whether it doesn't exist or just can't be reached. */

                    AslError (ASL_ERROR, ASL_MSG_NOT_FOUND, Op, Op->Asl.ExternalName);
                }
            }

            Status = AE_OK;
        }
        return (Status);
    }

    /* Attempt to optimize the NamePath */

    LkOptimizeNamePath (Op, OpInfo->Flags, WalkState, Path, Node);

    /* 1) Check for a reference to a resource descriptor */

    if ((Node->Type == INTERNAL_TYPE_RESOURCE_FIELD) ||
        (Node->Type == INTERNAL_TYPE_RESOURCE))
    {
        /*
         * This was a reference to a field within a resource descriptor.  Extract
         * the associated field offset (either a bit or byte offset depending on
         * the field type) and change the named reference into an integer for
         * AML code generation
         */
        Temp = (UINT32) Node->OwnerId;
        if (Node->Flags & ANOBJ_IS_BIT_OFFSET)
        {
            Op->Asl.CompileFlags |= NODE_IS_BIT_OFFSET;
        }

        /* Perform BitOffset <--> ByteOffset conversion if necessary */

        switch (Op->Asl.Parent->Asl.AmlOpcode)
        {
        case AML_CREATE_FIELD_OP:

            /* We allow a Byte offset to Bit Offset conversion for this op */

            if (!(Op->Asl.CompileFlags & NODE_IS_BIT_OFFSET))
            {
                /* Simply multiply byte offset times 8 to get bit offset */

                Temp = ACPI_MUL_8 (Temp);
            }
            break;


        case AML_CREATE_BIT_FIELD_OP:

            /* This op requires a Bit Offset */

            if (!(Op->Asl.CompileFlags & NODE_IS_BIT_OFFSET))
            {
                AslError (ASL_ERROR, ASL_MSG_BYTES_TO_BITS, Op, NULL);
            }
            break;


        case AML_CREATE_BYTE_FIELD_OP:
        case AML_CREATE_WORD_FIELD_OP:
        case AML_CREATE_DWORD_FIELD_OP:
        case AML_CREATE_QWORD_FIELD_OP:
        case AML_INDEX_OP:

            /* These Ops require Byte offsets */

            if (Op->Asl.CompileFlags & NODE_IS_BIT_OFFSET)
            {
                AslError (ASL_ERROR, ASL_MSG_BITS_TO_BYTES, Op, NULL);
            }
            break;


        default:
            /* Nothing to do for other opcodes */
            break;
        }

        /* Now convert this node to an integer whose value is the field offset */

        Op->Asl.ParseOpcode     = PARSEOP_INTEGER;
        Op->Asl.Value.Integer   = (UINT64) Temp;
        Op->Asl.CompileFlags   |= NODE_IS_RESOURCE_FIELD;

        OpcGenerateAmlOpcode (Op);
        Op->Asl.AmlLength = OpcSetOptimalIntegerSize (Op);
    }

    /* 2) Check for a method invocation */

    else if ((((Op->Asl.ParseOpcode == PARSEOP_NAMESTRING) || (Op->Asl.ParseOpcode == PARSEOP_NAMESEG)) &&
        (Node->Type == ACPI_TYPE_METHOD) &&
        (Op->Asl.Parent) &&
        (Op->Asl.Parent->Asl.ParseOpcode != PARSEOP_METHOD))   ||

        (Op->Asl.ParseOpcode == PARSEOP_METHODCALL))
    {
        /*
         * There are two types of method invocation:
         * 1) Invocation with arguments -- the parser recognizes this as a METHODCALL
         * 2) Invocation with no arguments --the parser cannot determine that this is a method
         *    invocation, therefore we have to figure it out here.
         */
        if (Node->Type != ACPI_TYPE_METHOD)
        {
            sprintf (MsgBuffer, "%s is a %s", Op->Asl.ExternalName, AcpiUtGetTypeName (Node->Type));

            AslError (ASL_ERROR, ASL_MSG_NOT_METHOD, Op, MsgBuffer);
            return (AE_OK);
        }

        if (Op->Asl.Parent->Asl.ParseOpcode == PARSEOP_CONDREFOF)
        {
            Op->Asl.Node = Node;
            return (AE_OK);
        }

        /*
         * This is a method invocation, with or without arguments.
         * Count the number of arguments, each appears as a child
         * under the parent node
         */
        Op->Asl.ParseOpcode = PARSEOP_METHODCALL;
        PassedArgs          = 0;
        NextOp              = Op->Asl.Child;

        while (NextOp)
        {
            PassedArgs++;
            NextOp = NextOp->Asl.Next;
        }

        if (Node->OwnerId != ASL_EXTERNAL_METHOD)
        {
            /*
             * Check the parsed arguments with the number expected by the
             * method declaration itself
             */
            if (PassedArgs != Node->OwnerId)
            {
                sprintf (MsgBuffer, "%s requires %d", Op->Asl.ExternalName,
                            Node->OwnerId);

                if (PassedArgs < Node->OwnerId)
                {
                    AslError (ASL_ERROR, ASL_MSG_ARG_COUNT_LO, Op, MsgBuffer);

                    if (Node->OwnerId > 7)
                    {
                        printf ("too many arguments defined for method [%4.4s]\n", (char *) &Node->Name);
                        return (AE_BAD_PARAMETER);
                    }
                }
                else
                {
                    AslError (ASL_ERROR, ASL_MSG_ARG_COUNT_HI, Op, MsgBuffer);
                }
            }

            /*
             * Check if the method caller expects this method to return a value and
             * if the called method in fact returns a value.
             */
            if (!(Op->Asl.CompileFlags & NODE_RESULT_NOT_USED))
            {
                /* 1) The result from the method is used (the method is a TermArg) */

                OwningOp = ACPI_CAST_PTR (ACPI_PARSE_OBJECT, Node->Object);
                if (OwningOp->Asl.CompileFlags & NODE_METHOD_NO_RETVAL)
                {
                    /*
                     * 2) Method NEVER returns a value
                     */
                    AslError (ASL_ERROR, ASL_MSG_NO_RETVAL, Op, Op->Asl.ExternalName);
                }
                else if (OwningOp->Asl.CompileFlags & NODE_METHOD_SOME_NO_RETVAL)
                {
                    /*
                     * 2) Method SOMETIMES returns a value, SOMETIMES not
                     */
                    AslError (ASL_WARNING, ASL_MSG_SOME_NO_RETVAL, Op, Op->Asl.ExternalName);
                }
            }
        }
    }

    /*
     * 3) Check for an ASL Field definition
     */
    else if ((Op->Asl.Parent) &&
            ((Op->Asl.Parent->Asl.ParseOpcode == PARSEOP_FIELD)     ||
             (Op->Asl.Parent->Asl.ParseOpcode == PARSEOP_BANKFIELD)))
    {
        /*
         * Offset checking for fields.  If the parent operation region has a
         * constant length (known at compile time), we can check fields
         * defined in that region against the region length.  This will catch
         * fields and field units that cannot possibly fit within the region.
         *
         * Note: Index fields do not directly reference an operation region,
         * thus they are not included in this check.
         */
        if (Op == Op->Asl.Parent->Asl.Child)
        {
            /*
             * This is the first child of the field node, which is
             * the name of the region.  Get the parse node for the
             * region -- which contains the length of the region.
             */
            OwningOp = ACPI_CAST_PTR (ACPI_PARSE_OBJECT, Node->Object);
            Op->Asl.Parent->Asl.ExtraValue = ACPI_MUL_8 (OwningOp->Asl.Value.Integer32);

            /* Examine the field access width */

            switch (Op->Asl.Parent->Asl.Value.Integer8)
            {
            case AML_FIELD_ACCESS_ANY:
            case AML_FIELD_ACCESS_BYTE:
            case AML_FIELD_ACCESS_BUFFER:
            default:
                MinimumLength = 1;
                break;

            case AML_FIELD_ACCESS_WORD:
                MinimumLength = 2;
                break;

            case AML_FIELD_ACCESS_DWORD:
                MinimumLength = 4;
                break;

            case AML_FIELD_ACCESS_QWORD:
                MinimumLength = 8;
                break;
            }

            /*
             * Is the region at least as big as the access width?
             * Note: DataTableRegions have 0 length
             */
            if ((OwningOp->Asl.Value.Integer32) &&
                (OwningOp->Asl.Value.Integer32 < MinimumLength))
            {
                AslError (ASL_ERROR, ASL_MSG_FIELD_ACCESS_WIDTH, Op, NULL);
            }

            /*
             * Check EC/CMOS/SMBUS fields to make sure that the correct
             * access type is used (BYTE for EC/CMOS, BUFFER for SMBUS)
             */
            SpaceIdOp = OwningOp->Asl.Child->Asl.Next;
            switch (SpaceIdOp->Asl.Value.Integer32)
            {
            case REGION_EC:
            case REGION_CMOS:

                if (Op->Asl.Parent->Asl.Value.Integer8 != AML_FIELD_ACCESS_BYTE)
                {
                    AslError (ASL_ERROR, ASL_MSG_REGION_BYTE_ACCESS, Op, NULL);
                }

                break;

            case REGION_SMBUS:

                if (Op->Asl.Parent->Asl.Value.Integer8 != AML_FIELD_ACCESS_BUFFER)
                {
                    AslError (ASL_ERROR, ASL_MSG_REGION_BUFFER_ACCESS, Op, NULL);
                }
                break;

            default:
                /* Nothing to do for other address spaces */
                break;
            }
        }
        else
        {
            /*
             * This is one element of the field list.  Check to make sure
             * that it does not go beyond the end of the parent operation region.
             *
             * In the code below:
             *    Op->Asl.Parent->Asl.ExtraValue      - Region Length (bits)
             *    Op->Asl.ExtraValue                  - Field start offset (bits)
             *    Op->Asl.Child->Asl.Value.Integer32  - Field length (bits)
             *    Op->Asl.Child->Asl.ExtraValue       - Field access width (bits)
             */
            if (Op->Asl.Parent->Asl.ExtraValue && Op->Asl.Child)
            {
                LkCheckFieldRange (Op,
                            Op->Asl.Parent->Asl.ExtraValue,
                            Op->Asl.ExtraValue,
                            Op->Asl.Child->Asl.Value.Integer32,
                            Op->Asl.Child->Asl.ExtraValue);
            }
        }
    }

    Op->Asl.Node = Node;
    return (Status);
}


/*******************************************************************************
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
 ******************************************************************************/

ACPI_STATUS
LkNamespaceLocateEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_WALK_STATE         *WalkState = (ACPI_WALK_STATE *) Context;
    const ACPI_OPCODE_INFO  *OpInfo;


    ACPI_FUNCTION_NAME ("LkNamespaceLocateEnd");


    /* We are only interested in opcodes that have an associated name */

    OpInfo = AcpiPsGetOpcodeInfo (Op->Asl.AmlOpcode);
    if (!(OpInfo->Flags & AML_NAMED))
    {
        return (AE_OK);
    }

    /*
     * TBD: do we ever need to check the argument of AML_NAME_OP
     * to get the correct type?
     *  if (Op->Asl.AmlOpcode == AML_NAME_OP)
     */

    /* Pop the scope stack */

    if (AcpiNsOpensScope (AslMapNamedOpcodeToDataType (Op->Asl.AmlOpcode)))
    {

        ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
            "%s: Popping scope for Op %p\n",
            AcpiUtGetTypeName (OpInfo->ObjectType), Op));

        AcpiDsScopeStackPop (WalkState);
    }
    return (AE_OK);
}


