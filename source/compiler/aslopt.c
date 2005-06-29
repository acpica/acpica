/******************************************************************************
 *
 * Module Name: aslopt- Compiler optimizations
 *              $Revision: 1.3 $
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
        ACPI_MODULE_NAME    ("aslopt")


UINT32 OptTotal = 0;


/*******************************************************************************
 *
 * FUNCTION:    LkSearchToRoot
 *
 * PARAMETERS:  Op                  - Current parser op
 *              WalkState           - Current state
 *              AmlNameString       - Unoptimized namepath
 *              TargetNode          - Node to which AmlNameString refers
 *
 * RETURN:      Status
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

ACPI_STATUS
LkSearchToRoot (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState,
    ACPI_NAMESPACE_NODE     *CurrentNode,
    ACPI_NAMESPACE_NODE     *TargetNode,
    ACPI_BUFFER             *TargetPath,
    char                    **NewPath)
{
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_GENERIC_STATE      ScopeInfo;
    ACPI_STATUS             Status;
    char                    *Path;


    ACPI_FUNCTION_NAME ("LkSearchToRoot");


    /* 
     * Check if search-to-root can be utilized.  Use the last NameSeg of
     * the NamePath and 1) See if can be found and 2) If found, make
     * sure that it is the same node that we want.  If there is another
     * name in the search path before the one we want, the nodes will
     * not match, and we cannot use this optimization.
     */
    Path = &(((NATIVE_CHAR *) TargetPath->Pointer)[TargetPath->Length - ACPI_NAME_SIZE]),
    ScopeInfo.Scope.Node = CurrentNode;

    /* Lookup the NameSeg using SEARCH_PARENT (search-to-root) */

    Status = AcpiNsLookup (&ScopeInfo, Path, ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
                    ACPI_NS_SEARCH_PARENT | ACPI_NS_DONT_OPEN_SCOPE, 
                    WalkState, &(Node));
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* 
     * We found the name, but we must check to make sure that the node
     * matches.  Otherwise, there is another identical name in the search
     * path that precludes the use of this optimization.
     */
    if (Node != TargetNode)
    {
        /* 
         * This means that another object with the same name was found first,
         * and we cannot use this optimization.
         */
        return (AE_NOT_FOUND);
    }

    /* Found the node, we can use this optimization */

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
        "NAMESEG:   %-24s", Path));

    /* We must allocate a new string for the name (TargetPath gets deleted) */

    *NewPath = ACPI_MEM_CALLOCATE (ACPI_NAME_SIZE + 1);
    ACPI_STRCPY (*NewPath, Path);

    AslError (ASL_OPTIMIZATION, ASL_MSG_SINGLE_NAME_OPTIMIZATION, Op, 
            *NewPath);

    return (AE_OK);
}




/*******************************************************************************
 *
 * FUNCTION:    LkBuildShortestPath
 *
 * PARAMETERS:  Op                  - Current parser op
 *              WalkState           - Current state
 *              AmlNameString       - Unoptimized namepath
 *              TargetNode          - Node to which AmlNameString refers
 *
 * RETURN:      Status
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

ACPI_STATUS
LkBuildShortestPath (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState,
    ACPI_NAMESPACE_NODE     *CurrentNode,
    ACPI_NAMESPACE_NODE     *TargetNode,
    ACPI_BUFFER             *CurrentPath,
    ACPI_BUFFER             *TargetPath,
    ACPI_SIZE               AmlNameStringLength,
    UINT8                   IsDeclaration,
    char                    **ReturnNewPath)
{
    UINT32                  NumCommonSegments;
    UINT32                  MaxCommonSegments;
    NATIVE_UINT             Index;
    UINT32                  NumCarats;
    NATIVE_UINT             i;
    char                    *NewPath;
    char                    *NewPathExternal;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_GENERIC_STATE      ScopeInfo;
    ACPI_STATUS             Status;
    BOOLEAN                 SubPath = FALSE;


    ACPI_FUNCTION_NAME ("LkBuildShortestPath");


    ScopeInfo.Scope.Node = CurrentNode;

    /*
     * Determine the maximum number of NameSegs that the Target and Current paths
     * can possibly have in common.  (To optimize, we have to have at least 1) 
     * 
     * Note: The external NamePath string lengths are always a multiple of 5 
     * (ACPI_NAME_SIZE + separator)
     */
    MaxCommonSegments = TargetPath->Length / PATH_SEGMENT_LENGTH;
    if (CurrentPath->Length < TargetPath->Length)
    {
        MaxCommonSegments = CurrentPath->Length / PATH_SEGMENT_LENGTH;
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
            &((NATIVE_CHAR *) TargetPath->Pointer)[(NumCommonSegments * PATH_SEGMENT_LENGTH) + 1],
            &((NATIVE_CHAR *) CurrentPath->Pointer)[(NumCommonSegments * PATH_SEGMENT_LENGTH) + 1],
            ACPI_NAME_SIZE))
        {
            /* Mismatch */

            break;
        }
    }

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " COMMON: %d", NumCommonSegments));

    /* There must be at least 1 common NameSeg in order to optimize */

    if (NumCommonSegments == 0)
    {
        return (AE_NOT_FOUND);
    }

    if (NumCommonSegments == MaxCommonSegments)
    {
        if (CurrentPath->Length == TargetPath->Length)
        {
            ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " SAME PATH"));
            return (AE_NOT_FOUND);
        }
        else
        {
            ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " SUBPATH"));
            SubPath = TRUE;
        }
    }

    /* Determine how many prefix Carats are required */

    NumCarats = (CurrentPath->Length / PATH_SEGMENT_LENGTH) - NumCommonSegments;

    /*
     * Construct a new target string
     */
    NewPathExternal = ACPI_MEM_CALLOCATE (TargetPath->Length + NumCarats);

    /* Insert the Carats into the Target string */

    for (i = 0; i < NumCarats; i++)
    {
        NewPathExternal[i] = '^';
    }

    /* Copy only the necessary (optimal) segments from the original target string */

    Index = (NumCommonSegments * PATH_SEGMENT_LENGTH) + 1;

    /* Special handling for exact subpath in a name declaration */

    if (IsDeclaration && SubPath)
    {
        /* We must include one more NameSeg */

        Index -= PATH_SEGMENT_LENGTH;
    }
    ACPI_STRCPY (&NewPathExternal[i], &((NATIVE_CHAR *) TargetPath->Pointer)[Index]);
    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " %-24s", NewPathExternal));

    /*
     * Internalize the new target string and check it against the original string
     * to make sure that this is in fact an optimization.  If the original string
     * is already optimal, there is no point in continuing.
     */
    Status = AcpiNsInternalizeName (NewPathExternal, &NewPath);
    ACPI_MEM_FREE (NewPathExternal);

#if 0
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }
#endif

    if (ACPI_STRLEN (NewPath) >= AmlNameStringLength)
    {
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " NOT SHORTER (New %d old %d)", 
            ACPI_STRLEN (NewPath), AmlNameStringLength));
        return (AE_NOT_FOUND);
    }

    /* 
     * Check to make sure that the optimization finds the node we are
     * looking for.  This is simply a sanity check on the new
     * path that has been created.
     */
    Status = AcpiNsLookup (&ScopeInfo,  NewPath,
                    ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
                    ACPI_NS_DONT_OPEN_SCOPE, WalkState, &(Node));
    if (ACPI_SUCCESS (Status))
    {
        /* Found the namepath, but make sure the node is correct */

        if (Node == TargetNode)
        {
            /* The lookup matched the node, accept this optimization */

            AslError (ASL_OPTIMIZATION, ASL_MSG_NAME_OPTIMIZATION, 
                Op, NewPathExternal);
            *ReturnNewPath = NewPath;
        }
        else
        {
            /* Node is not correct, do not use this optimization */

            Status = AE_NOT_FOUND;
            ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " ***** WRONG NODE"));
            AslError (ASL_WARNING, ASL_MSG_COMPILER_INTERNAL, Op, 
                "Not using optimized name - found wrong node");
        }
    }
    else
    {
        /* The lookup failed, we obviously cannot use this optimization */

        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " ***** NOT FOUND"));
        AslError (ASL_WARNING, ASL_MSG_COMPILER_INTERNAL, Op, 
            "Not using optimized name - did not find node");
    }

    return (Status);
}



/*******************************************************************************
 *
 * FUNCTION:    LkOptimizeNameDeclaration
 *
 * PARAMETERS:  Op                  - Current parser op
 *              WalkState           - Current state
 *              AmlNameString       - Unoptimized namepath
 *              TargetNode          - Node to which AmlNameString refers
 *
 * RETURN:      Status. AE_OK If path is optimized
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

ACPI_STATUS
LkOptimizeNameDeclaration (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState,
    ACPI_NAMESPACE_NODE     *CurrentNode,
    NATIVE_CHAR             *AmlNameString,
    char                    **NewPath)
{
    ACPI_STATUS             Status;
    char                    *ExternalNameString;


    ACPI_FUNCTION_TRACE ("LkOptimizeNameDeclaration");


    if (((CurrentNode == AcpiGbl_RootNode) || 
        (Op->Common.Parent->Asl.ParseOpcode == PARSEOP_DEFINITIONBLOCK)) && 
            (AmlNameString[0] == '\\'))
    {
        /*
         * The current scope is the root, and the namepath has a root prefix
         * that is therefore extraneous.  Remove it.
         */
        *NewPath = &AmlNameString[1];

        /* Debug output */

        Status = AcpiNsExternalizeName (ACPI_UINT32_MAX, *NewPath, 
                    NULL, &ExternalNameString);
        if (ACPI_FAILURE (Status))
        {
            /* TBD: this simply quietly aborts! */

            AslAbort ();
        }

        AslError (ASL_OPTIMIZATION, ASL_MSG_NAME_OPTIMIZATION, 
            Op, ExternalNameString);
        
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
            "AT ROOT:   %-24s", ExternalNameString));

        ACPI_MEM_FREE (ExternalNameString);
        return (AE_OK);
    }

    /* Could not optimize */

    return (AE_NOT_FOUND);
}


/*******************************************************************************
 *
 * FUNCTION:    LkOptimizeNamePath
 *
 * PARAMETERS:  Op                  - Current parser op
 *              WalkState           - Current state
 *              AmlNameString       - Unoptimized namepath
 *              TargetNode          - Node to which AmlNameString refers
 *
 * RETURN:      None.  If path is optimized, the Op is updated with new path
 *
 * DESCRIPTION: Optimize a Named Declaration or Reference to the minimal length.
 *              Must take into account both the current location in the 
 *              namespace and the actual reference path.
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
    ACPI_SIZE               AmlNameStringLength;
    ACPI_NAMESPACE_NODE     *CurrentNode;
    char                    *ExternalNameString;
    char                    *NewPath = NULL;
    ACPI_SIZE               HowMuchShorter;


    ACPI_FUNCTION_TRACE ("LkOptimizeNamePath");


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

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "%5d [%12.12s] [%12.12s] ", 
        Op->Asl.LogicalLineNumber, 
        AcpiPsGetOpcodeName (Op->Common.Parent->Common.AmlOpcode), 
        AcpiPsGetOpcodeName (Op->Common.AmlOpcode)));

    if (!(Flags & (AML_NAMED | AML_CREATE)))
    {
        if (Op->Asl.CompileFlags & NODE_IS_NAME_DECLARATION)
        {
            /* We don't want to fuss with actual name declaration nodes here */

            ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, 
                "******* NAME DECLARATION\n")); 
            return_VOID;
        }
    }

    /* 
     * The original path must be longer than one NameSeg (4 chars) for there
     * to be any possibility that it can be optimized to a shorter string 
     */
    AmlNameStringLength = ACPI_STRLEN (AmlNameString);
    if (AmlNameStringLength <= ACPI_NAME_SIZE)
    {
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, 
            "NAMESEG %4.4s\n", AmlNameString)); 
        return_VOID;
    }

    /*
     * We need to obtain the node that represents the current scope -- where
     * we are right now in the namespace.  We will compare this path
     * against the Namepath, looking for commonality.
     */
    CurrentNode = AcpiGbl_RootNode;
    if (WalkState->ScopeInfo)
    {
        CurrentNode = WalkState->ScopeInfo->Scope.Node;
    }

    if (Flags & (AML_NAMED | AML_CREATE))
    {
        /* This is the declaration of a new name */

        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "NAME"));
#if 0
        if (WalkState->ScopeInfo)
        {
            if (AcpiNsOpensScope (TargetNode->Type))
            {
                /* The target has opened a scope, so we need to backup to the parent */

                CurrentNode = AcpiNsGetParentNode (WalkState->ScopeInfo->Scope.Node);
            }
        }
#endif
        CurrentNode = Op->Asl.Parent->Asl.Node;
        if (!CurrentNode)
        {
            CurrentNode = AcpiGbl_RootNode;
        }

    }
    else
    {
        /* This is a reference to an existing named object */

        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "REF "));
    }

    /*
     * Obtain the full paths to the two nodes that we are interested in
     * (Target and current namespace location) in external
     * format -- something we can easily manipulate
     */
    TargetPath.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    Status = AcpiNsHandleToPathname (TargetNode, &TargetPath);
    if (ACPI_FAILURE (Status))
    {
        AslAbort ();
    }
    TargetPath.Length--;    /* Subtract one for null terminator */

    /* CurrentPath is the path to this scope (where we are in the namespace) */

    CurrentPath.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    Status = AcpiNsHandleToPathname (CurrentNode, &CurrentPath);
    if (ACPI_FAILURE (Status))
    {
        AslAbort ();
    }
    CurrentPath.Length--;   /* Subtract one for null terminator */

    /* Debug output only */

    Status = AcpiNsExternalizeName (ACPI_UINT32_MAX, AmlNameString, 
                NULL, &ExternalNameString);
    if (ACPI_FAILURE (Status))
    {
        AslAbort ();
    }

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, 
        "%37s (%2d) ==> %-32s(%2d) %-32s",
        (char *) CurrentPath.Pointer, CurrentPath.Length,
        (char *) TargetPath.Pointer, TargetPath.Length, ExternalNameString));

    ACPI_MEM_FREE (ExternalNameString);

    /*
     * Attempt an optmization depending on the type of namepath
     */
    if (Flags & (AML_NAMED | AML_CREATE))
    {
        /* 
         * This is a named opcode and the namepath is a name declaration, not
         * a reference.
         */
        Status = LkOptimizeNameDeclaration (Op, WalkState, CurrentNode, 
                    AmlNameString, &NewPath);
        if (ACPI_FAILURE (Status))
        {
            /*
             * 2) Search-to-root could not be used, now attempt to 
             *    optimize the namestring with carats (up-arrow)
             */
            Status = LkBuildShortestPath (Op, WalkState, CurrentNode, 
                            TargetNode, &CurrentPath, &TargetPath, 
                            AmlNameStringLength, 1, &NewPath);
        }
    }
    else
    {
        /*
         * This is a reference to an existing named object
         *
         * 1) Check if search-to-root can be utilized using the last 
         *    NameSeg of the NamePath
         */
        Status = LkSearchToRoot (Op, WalkState, CurrentNode,
                        TargetNode, &TargetPath, &NewPath);
        if (ACPI_FAILURE (Status))
        {
            /*
             * 2) Search-to-root could not be used, now attempt to 
             *    optimize the namestring with carats (up-arrow)
             */
            Status = LkBuildShortestPath (Op, WalkState, CurrentNode, 
                            TargetNode, &CurrentPath, &TargetPath, 
                            AmlNameStringLength, 0, &NewPath);
        }
    }

    /* 
     * Success from above indicates that the NamePath was successfully
     * optimized.  We need to update the parse op with the new name
     */
    if (ACPI_SUCCESS (Status))
    {
        HowMuchShorter = (AmlNameStringLength - ACPI_STRLEN (NewPath));
        OptTotal += HowMuchShorter;
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " REDUCED %2d (%d)", 
            HowMuchShorter, OptTotal));

        if (Flags & AML_NAMED)
        {
            Op->Asl.Child->Asl.Value.String = NewPath;
            Op->Asl.Child->Asl.AmlLength = ACPI_STRLEN (NewPath);
        }
        else if (Flags & AML_CREATE)
        {
            /* TBD: Create case - must traverse to proper node */

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

    /* Cleanup path buffers */

    ACPI_MEM_FREE (TargetPath.Pointer);
    ACPI_MEM_FREE (CurrentPath.Pointer);

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "\n"));
    return_VOID;
}

