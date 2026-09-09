/*******************************************************************************
 *
 * Module Name: nssearch - Namespace search
 *
 ******************************************************************************/

/******************************************************************************
 *
 * Copyright (c) 1999 - 2026, Intel Corp.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 *
 *****************************************************************************/

#include "acpi.h"
#include "accommon.h"
#include "acnamesp.h"

#ifdef ACPI_ASL_COMPILER
#include "amlcode.h"
#endif

#define _COMPONENT          ACPI_NAMESPACE
        ACPI_MODULE_NAME    ("nssearch")

/* Local prototypes */

static ACPI_STATUS
AcpiNsSearchParentTree (
    UINT32                  TargetName,
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_OBJECT_TYPE        Type,
    ACPI_NAMESPACE_NODE     **ReturnNode);

#ifdef ACPI_USE_NS_SEARCH_ACCELERATION
static ACPI_NAMESPACE_NODE *
AcpiNsSearchOneScopeCoreAccelerated(
    UINT32                  TargetName,
    ACPI_NAMESPACE_NODE     *ParentNode);
#endif


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsSearchOneScopeCore
 *
 * PARAMETERS:  TargetName      - Ascii ACPI name to search for
 *              ParentNode      - Node to search under
 *
 * RETURN:      The matching node or NULL, when a node with the provided name,
 *              parented by the provided node doesn't exist.
 *
 * DESCRIPTION: This function iterates over the list of child nodes in O(n)
 *
 ******************************************************************************/

static ACPI_NAMESPACE_NODE *
AcpiNsSearchOneScopeCore(
    UINT32                  TargetName,
    ACPI_NAMESPACE_NODE     *ParentNode)
{
    ACPI_NAMESPACE_NODE     *Node;

    ACPI_FUNCTION_TRACE (AcpiNsSearchOneScopeCore);

    Node = ParentNode->Child;
    while (Node)
    {
        /* Check for match against the name */
        if (Node->Name.Integer == TargetName)
        {
            return Node;
        }

        /* Didn't match name, move on to the next peer object */
        Node = Node->Peer;
    }

    return NULL;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsSearchOneScope
 *
 * PARAMETERS:  TargetName      - Ascii ACPI name to search for
 *              ParentNode      - Starting node where search will begin
 *              Type            - Object type to match
 *              ReturnNode      - Where the matched Named obj is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Search a single level of the namespace. Performs a
 *              simple search of the specified level, and does not add
 *              entries or search parents.
 *
 *
 *      Named object lists are built (and subsequently dumped) in the
 *      order in which the names are encountered during the namespace load;
 *
 *      The namespace searching has a slow path and a fast path. The slow path
 *      is based on iterating over the nodes in linear time, while the fast path
 *      is using a hash map for lookup.
 *
 *      If compiled with ACPI_USE_NS_SEARCH_ACCELERATION, the fast path will
 *      be used, unless it is unavailable (e.g. due to hash table allocation
 *      failure during initialisation), at which point execution falls back to
 *      the slow path.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiNsSearchOneScope (
    UINT32                  TargetName,
    ACPI_NAMESPACE_NODE     *ParentNode,
    ACPI_OBJECT_TYPE        Type,
    ACPI_NAMESPACE_NODE     **ReturnNode)
{
    ACPI_NAMESPACE_NODE     *Node = NULL;


    ACPI_FUNCTION_TRACE (NsSearchOneScope);


#ifdef ACPI_DEBUG_OUTPUT
    if (ACPI_LV_NAMES & AcpiDbgLevel)
    {
        char                *ScopeName;

        ScopeName = AcpiNsGetNormalizedPathname (ParentNode, TRUE);
        if (ScopeName)
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_NAMES,
                "Searching %s (%p) For [%4.4s] (%s)\n",
                ScopeName, ParentNode, ACPI_CAST_PTR (char, &TargetName),
                AcpiUtGetTypeName (Type)));

            ACPI_FREE (ScopeName);
        }
    }
#endif

#ifdef ACPI_USE_NS_SEARCH_ACCELERATION
    Node = AcpiNsSearchOneScopeCoreAccelerated (TargetName, ParentNode);
    /* Fallback in case accelerated search is not available */
    if (!Node)
#endif
    Node = AcpiNsSearchOneScopeCore (TargetName, ParentNode);

    if (Node)
    {
        /* Resolve a control method alias if any */
        if (AcpiNsGetType (Node) == ACPI_TYPE_LOCAL_METHOD_ALIAS)
        {
            Node = ACPI_CAST_PTR (ACPI_NAMESPACE_NODE, Node->Object);
        }

        /* Found matching entry */

        ACPI_DEBUG_PRINT ((ACPI_DB_NAMES,
            "Name [%4.4s] (%s) %p found in scope [%4.4s] %p\n",
            ACPI_CAST_PTR (char, &TargetName),
            AcpiUtGetTypeName (Node->Type),
            Node, AcpiUtGetNodeName (ParentNode), ParentNode));

        *ReturnNode = Node;
        return_ACPI_STATUS (AE_OK);
    }

    /* Searched entire namespace level, not found */

    ACPI_DEBUG_PRINT ((ACPI_DB_NAMES,
        "Name [%4.4s] (%s) not found in search in scope [%4.4s] "
        "%p first child %p\n",
        ACPI_CAST_PTR (char, &TargetName), AcpiUtGetTypeName (Type),
        AcpiUtGetNodeName (ParentNode), ParentNode, ParentNode->Child));

    return_ACPI_STATUS (AE_NOT_FOUND);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsSearchParentTree
 *
 * PARAMETERS:  TargetName      - Ascii ACPI name to search for
 *              Node            - Starting node where search will begin
 *              Type            - Object type to match
 *              ReturnNode      - Where the matched Node is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Called when a name has not been found in the current namespace
 *              level. Before adding it or giving up, ACPI scope rules require
 *              searching enclosing scopes in cases identified by AcpiNsLocal().
 *
 *              "A name is located by finding the matching name in the current
 *              name space, and then in the parent name space. If the parent
 *              name space does not contain the name, the search continues
 *              recursively until either the name is found or the name space
 *              does not have a parent (the root of the name space). This
 *              indicates that the name is not found" (From ACPI Specification,
 *              section 5.3)
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiNsSearchParentTree (
    UINT32                  TargetName,
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_OBJECT_TYPE        Type,
    ACPI_NAMESPACE_NODE     **ReturnNode)
{
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *ParentNode;


    ACPI_FUNCTION_TRACE (NsSearchParentTree);


    ParentNode = Node->Parent;

    /*
     * If there is no parent (i.e., we are at the root) or type is "local",
     * we won't be searching the parent tree.
     */
    if (!ParentNode)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_NAMES, "[%4.4s] has no parent\n",
            ACPI_CAST_PTR (char, &TargetName)));
        return_ACPI_STATUS (AE_NOT_FOUND);
    }

    if (AcpiNsLocal (Type))
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_NAMES,
            "[%4.4s] type [%s] must be local to this scope (no parent search)\n",
            ACPI_CAST_PTR (char, &TargetName), AcpiUtGetTypeName (Type)));
        return_ACPI_STATUS (AE_NOT_FOUND);
    }

    /* Search the parent tree */

    ACPI_DEBUG_PRINT ((ACPI_DB_NAMES,
        "Searching parent [%4.4s] for [%4.4s]\n",
        AcpiUtGetNodeName (ParentNode), ACPI_CAST_PTR (char, &TargetName)));

    /* Search parents until target is found or we have backed up to the root */

    while (ParentNode)
    {
        /*
         * Search parent scope. Use TYPE_ANY because we don't care about the
         * object type at this point, we only care about the existence of
         * the actual name we are searching for. Typechecking comes later.
         */
        Status = AcpiNsSearchOneScope (
            TargetName, ParentNode, ACPI_TYPE_ANY, ReturnNode);
        if (ACPI_SUCCESS (Status))
        {
            return_ACPI_STATUS (Status);
        }

        /* Not found here, go up another level (until we reach the root) */

        ParentNode = ParentNode->Parent;
    }

    /* Not found in parent tree */

    return_ACPI_STATUS (AE_NOT_FOUND);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsSearchAndEnter
 *
 * PARAMETERS:  TargetName          - Ascii ACPI name to search for (4 chars)
 *              WalkState           - Current state of the walk
 *              Node                - Starting node where search will begin
 *              InterpreterMode     - Add names only in ACPI_MODE_LOAD_PASS_x.
 *                                    Otherwise,search only.
 *              Type                - Object type to match
 *              Flags               - Flags describing the search restrictions
 *              ReturnNode          - Where the Node is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Search for a name segment in a single namespace level,
 *              optionally adding it if it is not found. If the passed
 *              Type is not Any and the type previously stored in the
 *              entry was Any (i.e. unknown), update the stored type.
 *
 *              In ACPI_IMODE_EXECUTE, search only.
 *              In other modes, search and add if not found.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiNsSearchAndEnter (
    UINT32                  TargetName,
    ACPI_WALK_STATE         *WalkState,
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_INTERPRETER_MODE   InterpreterMode,
    ACPI_OBJECT_TYPE        Type,
    UINT32                  Flags,
    ACPI_NAMESPACE_NODE     **ReturnNode)
{
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *NewNode;


    ACPI_FUNCTION_TRACE (NsSearchAndEnter);


    /* Parameter validation */

    if (!Node || !TargetName || !ReturnNode)
    {
        ACPI_ERROR ((AE_INFO,
            "Null parameter: Node %p Name 0x%X ReturnNode %p",
            Node, TargetName, ReturnNode));
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /*
     * Name must consist of valid ACPI characters. We will repair the name if
     * necessary because we don't want to abort because of this, but we want
     * all namespace names to be printable. A warning message is appropriate.
     *
     * This issue came up because there are in fact machines that exhibit
     * this problem, and we want to be able to enable ACPI support for them,
     * even though there are a few bad names.
     */
    AcpiUtRepairName (ACPI_CAST_PTR (char, &TargetName));

    /* Try to find the name in the namespace level specified by the caller */

    *ReturnNode = ACPI_ENTRY_NOT_FOUND;
    Status = AcpiNsSearchOneScope (TargetName, Node, Type, ReturnNode);
    if (Status != AE_NOT_FOUND)
    {
        /*
         * If we found it AND the request specifies that a find is an error,
         * return the error
         */
        if (Status == AE_OK)
        {
            /* The node was found in the namespace */

            /*
             * If the namespace override feature is enabled for this node,
             * delete any existing attached sub-object and make the node
             * look like a new node that is owned by the override table.
             */
            if (Flags & ACPI_NS_OVERRIDE_IF_FOUND)
            {
                ACPI_DEBUG_PRINT ((ACPI_DB_NAMES,
                    "Namespace override: %4.4s pass %u type %X Owner %X\n",
                    ACPI_CAST_PTR(char, &TargetName), InterpreterMode,
                    (*ReturnNode)->Type, WalkState->OwnerId));

                AcpiNsDeleteChildren (*ReturnNode);
                if (AcpiGbl_RuntimeNamespaceOverride)
                {
                    AcpiUtRemoveReference ((*ReturnNode)->Object);
                    (*ReturnNode)->Object = NULL;
                    (*ReturnNode)->OwnerId = WalkState->OwnerId;
                }
                else
                {
                    AcpiNsRemoveNode (*ReturnNode);
                    *ReturnNode = ACPI_ENTRY_NOT_FOUND;
                }
            }

            /* Return an error if we don't expect to find the object */

            else if (Flags & ACPI_NS_ERROR_IF_FOUND)
            {
                Status = AE_ALREADY_EXISTS;
            }
        }

#ifdef ACPI_ASL_COMPILER
        if (*ReturnNode && (*ReturnNode)->Type == ACPI_TYPE_ANY)
        {
            (*ReturnNode)->Flags |= ANOBJ_IS_EXTERNAL;
        }
#endif

        /* Either found it or there was an error: finished either way */

        return_ACPI_STATUS (Status);
    }

    /*
     * The name was not found. If we are NOT performing the first pass
     * (name entry) of loading the namespace, search the parent tree (all the
     * way to the root if necessary.) We don't want to perform the parent
     * search when the namespace is actually being loaded. We want to perform
     * the search when namespace references are being resolved (load pass 2)
     * and during the execution phase.
     */
    if ((InterpreterMode != ACPI_IMODE_LOAD_PASS1) &&
        (Flags & ACPI_NS_SEARCH_PARENT))
    {
        /*
         * Not found at this level - search parent tree according to the
         * ACPI specification
         */
        Status = AcpiNsSearchParentTree (TargetName, Node, Type, ReturnNode);
        if (ACPI_SUCCESS (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    /* In execute mode, just search, never add names. Exit now */

    if (InterpreterMode == ACPI_IMODE_EXECUTE)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_NAMES,
            "%4.4s Not found in %p [Not adding]\n",
            ACPI_CAST_PTR (char, &TargetName), Node));

        return_ACPI_STATUS (AE_NOT_FOUND);
    }

    /* Create the new named object */

    NewNode = AcpiNsCreateNode (TargetName);
    if (!NewNode)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

#ifdef ACPI_ASL_COMPILER

    /* Node is an object defined by an External() statement */

    if (Flags & ACPI_NS_EXTERNAL ||
        (WalkState && WalkState->Opcode == AML_SCOPE_OP))
    {
        NewNode->Flags |= ANOBJ_IS_EXTERNAL;
    }
#endif

    if (Flags & ACPI_NS_TEMPORARY)
    {
        NewNode->Flags |= ANOBJ_TEMPORARY;
    }

    /* Install the new object into the parent's list of children */

    AcpiNsInstallNode (WalkState, Node, NewNode, Type);
    *ReturnNode = NewNode;
    return_ACPI_STATUS (AE_OK);
}


#ifdef ACPI_USE_NS_SEARCH_ACCELERATION

/* TODO: Rather than fixed value, scale this heuristically */
static const int                      AcpiNsSearchHashBits = 10;
static ACPI_NS_SEARCH_LIST_HEAD_TYPE *AcpiNsSearchHashTable = NULL;


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsSearchAccelerationInit
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status (currently always AE_OK)
 *
 * DESCRIPTION: Initializes the hash table that is used to accelerate the
 *              namespace search queries. If allocating memory fails,
 *              a warning is emitted (and no acceleration is used later).
 *
 ******************************************************************************/

ACPI_STATUS
AcpiNsSearchAccelerationInit (
    void)
{
    int             HashTableBuckets = (1 << AcpiNsSearchHashBits);
    int             HashTableSize = HashTableBuckets *
                                    sizeof(ACPI_NS_SEARCH_LIST_HEAD_TYPE);

    ACPI_FUNCTION_TRACE (AcpiNsSearchAccelerationInit);

    /* If already initialized, nothing to do */
    if (AcpiNsSearchHashTable)
        return_ACPI_STATUS (AE_OK);

    AcpiNsSearchHashTable = ACPI_ALLOCATE_ZEROED (HashTableSize);
    if (!AcpiNsSearchHashTable)
    {
        ACPI_WARNING((
            AE_INFO,
            "Failed to allocate %ud bytes for namespace search hash table. "
            "Acceleration will not be used.",
            HashTableSize));
    }

    return_ACPI_STATUS(AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsSearchAccelerationTerminate
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Frees up memory of the hash table that is used to accelerate the
 *              namespace search queries.
 *
 ******************************************************************************/

void
AcpiNsSearchAccelerationTerminate(
    void)
{
    ACPI_FUNCTION_TRACE (AcpiNsSearchAccelerationTerminate);

    ACPI_FREE (AcpiNsSearchHashTable);
    AcpiNsSearchHashTable = NULL;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsSearchHashParentAndName
 *
 * PARAMETERS:  TargetName      - Ascii ACPI name
 *              ParentNode      - Pointer to a namespace node
 *
 * RETURN:      A hash of the provided parameters
 *
 * DESCRIPTION: Computes a hash for use in accelerating namespace searches
 *
 ******************************************************************************/

static UINT32
AcpiNsSearchHashParentAndName(
    ACPI_NAMESPACE_NODE     *ParentNode,
    UINT32                  Name)
{
    return ACPI_HASH_PTR (ParentNode, AcpiNsSearchHashBits) ^
           ACPI_HASH_UINT32 (Name, AcpiNsSearchHashBits);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsSearchHashNode
 *
 * PARAMETERS:  Node - The namespace node to compute a hash for
 *
 * RETURN:      A hash of the provided node's name and parent node pointer
 *
 * DESCRIPTION: Computes a hash for use in accelerating namespace searches
 *
 ******************************************************************************/

static UINT32
AcpiNsSearchHashNode(
    ACPI_NAMESPACE_NODE     *Node)
{
    return AcpiNsSearchHashParentAndName (Node->Parent, Node->Name.Integer);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsSearchAccelerationAddNode
 *
 * PARAMETERS:  Node - namespace node to add to the acceleration
 *
 * RETURN:      None
 *
 * DESCRIPTION: This function adds the node to the hash table used to
 *              accelerate namespace searches
 *
 ******************************************************************************/

void
AcpiNsSearchAccelerationAddNode(
    ACPI_NAMESPACE_NODE     *Node)
{
    ACPI_FUNCTION_TRACE (AcpiNsSearchAccelerationAddNode);

    if (AcpiNsSearchHashTable)
    {
        UINT32              Key;

        Key = AcpiNsSearchHashNode (Node);

        ACPI_NS_SEARCH_LIST_ADD_HEAD (&Node->SearchListNode,
                                      &AcpiNsSearchHashTable[Key]);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsSearchAccelerationDeleteNode
 *
 * PARAMETERS:  Node - namespace node to remove from the acceleration
 *
 * RETURN:      None
 *
 * DESCRIPTION: This function removes the node from the hash table used to
 *              accelerate namespace searches
 *
 ******************************************************************************/

void
AcpiNsSearchAccelerationDeleteNode(
    ACPI_NAMESPACE_NODE     *Node)
{
    ACPI_FUNCTION_TRACE (AcpiNsSearchAccelerationDeleteNode);

    if (AcpiNsSearchHashTable)
    {
        ACPI_HASH_DEL (&Node->SearchListNode);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiNsSearchOneScopeCoreAccelerated
 *
 * PARAMETERS:  TargetName      - Ascii ACPI name to search for
 *              ParentNode      - Node to search under
 *
 * RETURN:      The matching node or NULL, when a node with the provided name,
 *              parented by the provided node doesn't exist.
 *
 * DESCRIPTION: This function uses a hash-based lookup table with a best-case
 *              O(1) lookup time.
 *
 ******************************************************************************/

static ACPI_NAMESPACE_NODE *
AcpiNsSearchOneScopeCoreAccelerated(
    UINT32                  TargetName,
    ACPI_NAMESPACE_NODE     *ParentNode)
{
    ACPI_NAMESPACE_NODE     *Node;
    UINT32                  Key;

    if (!AcpiNsSearchHashTable)
        return NULL;

    Key = AcpiNsSearchHashParentAndName (ParentNode, TargetName);

    ACPI_LIST_FOR_EACH_ENTRY (Node,
                              &AcpiNsSearchHashTable[Key],
                              SearchListNode)
    {
        if (Node->Parent == ParentNode && Node->Name.Integer == TargetName)
            return Node;
    }

    return NULL;
}

#endif
