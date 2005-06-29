
/******************************************************************************
 *
 * Module Name: asltree - parse tree management
 *              $Revision: 1.38 $
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

#define _COMPONENT          ACPI_COMPILER
        MODULE_NAME         ("asltree")


/*******************************************************************************
 *
 * FUNCTION:    TrGetNextNode
 *
 * PARAMETERS:  None
 *
 * RETURN:      New parse node.  Aborts on allocation failure
 *
 * DESCRIPTION: Allocate a new parse node for the parse tree.  Bypass the local
 *              dynamic memory manager for performance reasons (This has a
 *              major impact on the speed of the compiler.)
 *
 ******************************************************************************/

ASL_PARSE_NODE *
TrGetNextNode (void)
{

    if (Gbl_NodeCacheNext >= Gbl_NodeCacheLast)
    {
        Gbl_NodeCacheNext = UtLocalCalloc (sizeof (ASL_PARSE_NODE) * ASL_NODE_CACHE_SIZE);
        Gbl_NodeCacheLast = Gbl_NodeCacheNext + ASL_NODE_CACHE_SIZE;
    }

    return (Gbl_NodeCacheNext++);
}


/*******************************************************************************
 *
 * FUNCTION:    TrAllocateNode
 *
 * PARAMETERS:  ParseOpcode         - Opcode to be assigned to the node
 *
 * RETURN:      New parse node.  Aborts on allocation failure
 *
 * DESCRIPTION: Allocate and initialize a new parse node for the parse tree
 *
 ******************************************************************************/

ASL_PARSE_NODE *
TrAllocateNode (
    UINT32                  ParseOpcode)
{
    ASL_PARSE_NODE          *Node;


    Node = TrGetNextNode ();

    Node->ParseOpcode       = (UINT16) ParseOpcode;
    Node->Filename          = Gbl_Files[ASL_FILE_INPUT].Filename;
    Node->LineNumber        = Gbl_CurrentLineNumber;
    Node->LogicalLineNumber = Gbl_LogicalLineNumber;
    Node->LogicalByteOffset = Gbl_CurrentLineOffset;
    Node->Column            = Gbl_CurrentColumn;

    strncpy (Node->ParseOpName, UtGetOpName (ParseOpcode), 12);

    return Node;
}


/*******************************************************************************
 *
 * FUNCTION:    TrReleaseNode
 *
 * PARAMETERS:  Node            - Node to be released
 *
 * RETURN:      None
 *
 * DESCRIPTION: "release" a node.  In truth, nothing is done since the node
 *              is part of a larger buffer
 *
 ******************************************************************************/

void
TrReleaseNode (
    ASL_PARSE_NODE          *Node)
{
}


/*******************************************************************************
 *
 * FUNCTION:    TrUpdateNode
 *
 * PARAMETERS:  ParseOpcode         - New opcode to be assigned to the node
 *              Node                - An existing parse node
 *
 * RETURN:      The updated node
 *
 * DESCRIPTION: Change the parse opcode assigned to a node.  Usually used to
 *              change an opcode to DEFAULT_ARG so that the node is ignored
 *              during the code generation.  Also used to set generic integers
 *              to a specific size (8, 16, 32, or 64 bits)
 *
 ******************************************************************************/

ASL_PARSE_NODE *
TrUpdateNode (
    UINT32                  ParseOpcode,
    ASL_PARSE_NODE          *Node)
{


    if (!Node)
    {
        return NULL;
    }

    DbgPrint (ASL_PARSE_OUTPUT,
        "\nUpdateNode: Old - %s, New - %s\n\n",
        UtGetOpName (Node->ParseOpcode),
        UtGetOpName (ParseOpcode));

    /* Assign new opcode and name */

    Node->ParseOpcode = (UINT16) ParseOpcode;
    strncpy (Node->ParseOpName, UtGetOpName (ParseOpcode), 12);

    /*
     * For the BYTE, WORD, and DWORD constants, make sure that the integer
     * that was passed in will actually fit into the data type
     */
    switch (ParseOpcode)
    {
    case BYTECONST:
        Node = UtCheckIntegerRange (Node, 0x00, ACPI_UINT8_MAX);
        break;

    case WORDCONST:
        Node = UtCheckIntegerRange (Node, 0x00, ACPI_UINT16_MAX);
        break;

    case DWORDCONST:
        Node = UtCheckIntegerRange (Node, 0x00, ACPI_UINT32_MAX);
        break;
    }

    return Node;
}


/*******************************************************************************
 *
 * FUNCTION:    TrSetNodeFlags
 *
 * PARAMETERS:  Node                - An existing parse node
 *              Flags               - New flags word
 *
 * RETURN:      The updated node
 *
 * DESCRIPTION: Set bits in the node flags word.  Will not clear bits, only set
 *
 ******************************************************************************/

ASL_PARSE_NODE *
TrSetNodeFlags (
    ASL_PARSE_NODE          *Node,
    UINT32                  Flags)
{

    DbgPrint (ASL_PARSE_OUTPUT,
        "\nSetNodeFlags: Node %p, %d\n\n", Node, Flags);

    if (!Node)
    {
        return NULL;
    }

    Node->Flags |= Flags;
    return Node;
}


/*******************************************************************************
 *
 * FUNCTION:    TrSetEndLineNumber
 *
 * PARAMETERS:  Node                - An existing parse node
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Set the ending line numbers (file line and logical line) of a
 *              parse node to the current line numbers.
 *
 ******************************************************************************/

void
TrSetEndLineNumber (
    ASL_PARSE_NODE          *Node)
{

    /* If the end line # is already set, just return */

    if (Node->EndLine)
    {
        return;
    }

    Node->EndLine        = Gbl_CurrentLineNumber;
    Node->EndLogicalLine = Gbl_LogicalLineNumber;
}


/*******************************************************************************
 *
 * FUNCTION:    TrCreateLeafNode
 *
 * PARAMETERS:  ParseOpcode         - New opcode to be assigned to the node
 *
 * RETURN:      Pointer to the new node.  Aborts on allocation failure
 *
 * DESCRIPTION: Create a simple leaf node (no children or peers, and no value
 *              assigned to the node)
 *
 ******************************************************************************/

ASL_PARSE_NODE *
TrCreateLeafNode (
    UINT32                  ParseOpcode)
{
    ASL_PARSE_NODE          *Node;


    Node = TrAllocateNode (ParseOpcode);

    DbgPrint (ASL_PARSE_OUTPUT,
        "\nCreateLeafNode  Line %d NewNode %p  Op %s\n\n",
        Node->LineNumber, Node, UtGetOpName(ParseOpcode));

    return Node;
}


/*******************************************************************************
 *
 * FUNCTION:    TrCreateValuedLeafNode
 *
 * PARAMETERS:  ParseOpcode         - New opcode to be assigned to the node
 *              Value               - Value to be assigned to the node
 *
 * RETURN:      Pointer to the new node.  Aborts on allocation failure
 *
 * DESCRIPTION: Create a leaf node (no children or peers) with a value
 *              assigned to it
 *
 ******************************************************************************/

ASL_PARSE_NODE *
TrCreateValuedLeafNode (
    UINT32                  ParseOpcode,
    ACPI_INTEGER            Value)
{
    ASL_PARSE_NODE          *Node;


    Node = TrAllocateNode (ParseOpcode);

    DbgPrint (ASL_PARSE_OUTPUT,
        "\nCreateValuedLeafNode  Line %d NewNode %p  Op %s  Value %lX  ",
        Node->LineNumber, Node, UtGetOpName(ParseOpcode), Value);
    Node->Value.Integer = Value;

    switch (ParseOpcode)
    {
    case STRING_LITERAL:
        DbgPrint (ASL_PARSE_OUTPUT, "STRING->%s", Value);
        break;

    case NAMESEG:
        DbgPrint (ASL_PARSE_OUTPUT, "NAMESEG->%s", Value);
        break;

    case NAMESTRING:
        DbgPrint (ASL_PARSE_OUTPUT, "NAMESTRING->%s", Value);
        break;

    case EISAID:
        DbgPrint (ASL_PARSE_OUTPUT, "EISAID->%s", Value);
        break;

    case METHOD:
        DbgPrint (ASL_PARSE_OUTPUT, "METHOD");
        break;

    case INTEGER:
        DbgPrint (ASL_PARSE_OUTPUT, "INTEGER");
        break;

    default:
        break;
    }

    DbgPrint (ASL_PARSE_OUTPUT, "\n\n");
    return Node;
}


/*******************************************************************************
 *
 * FUNCTION:    TrCreateNode
 *
 * PARAMETERS:  ParseOpcode         - Opcode to be assigned to the node
 *              NumChildren         - Number of children to follow
 *              ...                 - A list of child nodes to link to the new
 *                                    node.  NumChildren long.
 *
 * RETURN:      Pointer to the new node.  Aborts on allocation failure
 *
 * DESCRIPTION: Create a new parse node and link together a list of child
 *              nodes underneath the new node.
 *
 ******************************************************************************/

ASL_PARSE_NODE *
TrCreateNode (
    UINT32                  ParseOpcode,
    UINT32                  NumChildren,
    ...)
{
    ASL_PARSE_NODE          *Node;
    ASL_PARSE_NODE          *Child;
    ASL_PARSE_NODE          *PrevChild;
    va_list                 ap;
    UINT32                  i;
    BOOLEAN                 FirstChild;


    va_start (ap, NumChildren);

    /* Allocate one new node */

    Node = TrAllocateNode (ParseOpcode);

    DbgPrint (ASL_PARSE_OUTPUT,
        "\nCreateNode  Line %d NewParent %p Child %d Op %s  ",
        Node->LineNumber, Node, NumChildren, UtGetOpName(ParseOpcode));
    RootNode = Node;

    /* Some extra debug output based on the parse opcode */

    switch (ParseOpcode)
    {
    case DEFINITIONBLOCK:
        DbgPrint (ASL_PARSE_OUTPUT, "DEFINITION_BLOCK (Tree Completed)->");
        break;

    case OPERATIONREGION:
        DbgPrint (ASL_PARSE_OUTPUT, "OPREGION->");
        break;

    case OR:
        DbgPrint (ASL_PARSE_OUTPUT, "OR->");
        break;
    }


    /* Link the new node to its children */

    PrevChild = NULL;
    FirstChild = TRUE;
    for (i = 0; i < NumChildren; i++)
    {
        /* Get the next child */

        Child = va_arg (ap, ASL_PARSE_NODE *);
        DbgPrint (ASL_PARSE_OUTPUT, "%p, ", Child);

        /*
         * If child is NULL, this means that an optional argument
         * was omitted.  We must create a placeholder with a special
         * opcode (DEFAULT_ARG) so that the code generator will know
         * that it must emit the correct default for this argument
         */
        if (!Child)
        {
            Child = TrAllocateNode (DEFAULT_ARG);
        }

        /* Link first child to parent */

        if (FirstChild)
        {
            FirstChild = FALSE;
            Node->Child = Child;
        }

        /* Point all children to parent */

        Child->Parent = Node;

        /* Link children in a peer list */

        if (PrevChild)
        {
            PrevChild->Peer = Child;
        };

        /*
         * This child might be a list, point all nodes in the list
         * to the same parent
         */
        while (Child->Peer)
        {
            Child = Child->Peer;
            Child->Parent = Node;
        }

        PrevChild = Child;
    }
    va_end(ap);

    DbgPrint (ASL_PARSE_OUTPUT, "\n\n");
    return Node;
}


/*******************************************************************************
 *
 * FUNCTION:    TrLinkChildren
 *
 * PARAMETERS:  Node                - An existing parse node
 *              NumChildren         - Number of children to follow
 *              ...                 - A list of child nodes to link to the new
 *                                    node.  NumChildren long.
 *
 * RETURN:      The updated (linked) node
 *
 * DESCRIPTION: Link a group of nodes to an existing parse node
 *
 ******************************************************************************/

ASL_PARSE_NODE *
TrLinkChildren (
    ASL_PARSE_NODE          *Node,
    UINT32                  NumChildren,
    ...)
{
    ASL_PARSE_NODE          *Child;
    ASL_PARSE_NODE          *PrevChild;
    va_list                 ap;
    UINT32                  i;
    BOOLEAN                 FirstChild;


    va_start (ap, NumChildren);


    TrSetEndLineNumber (Node);

    DbgPrint (ASL_PARSE_OUTPUT,
        "\nLinkChildren  Line [%d to %d] NewParent %p Child %d Op %s  ",
        Node->LineNumber, Node->EndLine,
        Node, NumChildren, UtGetOpName(Node->ParseOpcode));
    RootNode = Node;

    switch (Node->ParseOpcode)
    {
    case DEFINITIONBLOCK:
        DbgPrint (ASL_PARSE_OUTPUT, "DEFINITION_BLOCK (Tree Completed)->");
        break;

    case OPERATIONREGION:
        DbgPrint (ASL_PARSE_OUTPUT, "OPREGION->");
        break;

    case OR:
        DbgPrint (ASL_PARSE_OUTPUT, "OR->");
        break;
    }

    /* Link the new node to it's children */

    PrevChild = NULL;
    FirstChild = TRUE;
    for (i = 0; i < NumChildren; i++)
    {
        Child = va_arg (ap, ASL_PARSE_NODE *);

        if ((Child == PrevChild) && (Child != NULL))
        {
            AslError (ASL_WARNING, ASL_MSG_COMPILER_INTERNAL, Child, "Child node list invalid");
            return Node;
        }

        DbgPrint (ASL_PARSE_OUTPUT, "%p, ", Child);

        /*
         * If child is NULL, this means that an optional argument
         * was omitted.  We must create a placeholder with a special
         * opcode (DEFAULT_ARG) so that the code generator will know
         * that it must emit the correct default for this argument
         */
        if (!Child)
        {
            Child = TrAllocateNode (DEFAULT_ARG);
        }

        /* Link first child to parent */

        if (FirstChild)
        {
            FirstChild = FALSE;
            Node->Child = Child;
        }

        /* Point all children to parent */

        Child->Parent = Node;

        /* Link children in a peer list */

        if (PrevChild)
        {
            PrevChild->Peer = Child;
        };

        /*
         * This child might be a list, point all nodes in the list
         * to the same parent
         */
        while (Child->Peer)
        {
            Child = Child->Peer;
            Child->Parent = Node;
        }
        PrevChild = Child;
    }
    va_end(ap);

    DbgPrint (ASL_PARSE_OUTPUT, "\n\n");
    return Node;
}


/*******************************************************************************
 *
 * FUNCTION:    TrLinkPeerNode
 *
 * PARAMETERS:  Node1           - First peer
 *              Node2           - Second peer
 *
 * RETURN:      Node1 or the non-null node.
 *
 * DESCRIPTION: Link two nodes as peers.  Handles cases where one peer is null.
 *
 ******************************************************************************/

ASL_PARSE_NODE *
TrLinkPeerNode (
    ASL_PARSE_NODE          *Node1,
    ASL_PARSE_NODE          *Node2)
{
    ASL_PARSE_NODE          *Next;


    DbgPrint (ASL_PARSE_OUTPUT,
        "\nLinkPeerNode: 1=%p (%s), 2=%p (%s)\n\n",
        Node1, Node1 ? UtGetOpName(Node1->ParseOpcode) : NULL,
        Node2, Node2 ? UtGetOpName(Node2->ParseOpcode) : NULL);


    if ((!Node1) && (!Node2))
    {
        DbgPrint (ASL_PARSE_OUTPUT, "\nTwo Null nodes!\n");
        return Node1;
    }

    /* If one of the nodes is null, just return the non-null node */

    if (!Node2)
    {
        return Node1;
    }

    if (!Node1)
    {
        return Node2;
    }

    if (Node1 == Node2)
    {
        DbgPrint (ASL_DEBUG_OUTPUT,
            "\n\n************* Internal error, linking node to itself %p\n\n\n", Node1);
        AslError (ASL_WARNING, ASL_MSG_COMPILER_INTERNAL, Node1, "Linking node to itself");
        return Node1;
    }

    Node1->Parent = Node2->Parent;

    /*
     * Node 1 may already have a peer list (such as an IF/ELSE pair),
     * so we must walk to the end of the list and attach the new
     * peer at the end
     */
    Next = Node1;
    while (Next->Peer)
    {
        Next = Next->Peer;
    }

    Next->Peer = Node2;
    return Node1;
}


/*******************************************************************************
 *
 * FUNCTION:    TrLinkPeerNodes
 *
 * PARAMETERS:  NumPeers            - The number of nodes in the list to follow
 *              ...                 - A list of nodes to link together as peers
 *
 * RETURN:      The first node in the list (head of the peer list)
 *
 * DESCRIPTION: Link together an arbitrary number of peer nodes.
 *
 ******************************************************************************/

ASL_PARSE_NODE *
TrLinkPeerNodes (
    UINT32                  NumPeers,
    ...)
{
    ASL_PARSE_NODE          *This;
    ASL_PARSE_NODE          *Next;
    va_list                 ap;
    UINT32                  i;
    ASL_PARSE_NODE          *Start;


    DbgPrint (ASL_PARSE_OUTPUT,
        "\nLinkPeerNodes: (%d) ", NumPeers);

    va_start (ap, NumPeers);
    This = va_arg (ap, ASL_PARSE_NODE *);
    Start = This;

    /*
     * Link all peers
     */
    for (i = 0; i < (NumPeers -1); i++)
    {
        DbgPrint (ASL_PARSE_OUTPUT, "%d=%p ", (i+1), This);

        while (This->Peer)
        {
            This = This->Peer;
        }

        /* Get another peer node */

        Next = va_arg (ap, ASL_PARSE_NODE *);
        if (!Next)
        {
            Next = TrAllocateNode (DEFAULT_ARG);
        }

        /* link new node to the current node */

        This->Peer = Next;
        This = Next;
    }

    DbgPrint (ASL_PARSE_OUTPUT,"\n\n");
    return (Start);
}


/*******************************************************************************
 *
 * FUNCTION:    TrLinkChildNode
 *
 * PARAMETERS:  Node1           - Parent node
 *              Node2           - Node to become a child
 *
 * RETURN:      The parent node
 *
 * DESCRIPTION: Link two nodes together as a parent and child
 *
 ******************************************************************************/

ASL_PARSE_NODE *
TrLinkChildNode (
    ASL_PARSE_NODE          *Node1,
    ASL_PARSE_NODE          *Node2)
{
    ASL_PARSE_NODE          *Next;


    DbgPrint (ASL_PARSE_OUTPUT,
        "\nLinkChildNode: Parent=%p (%s), Child=%p (%s)\n\n",
        Node1, Node1 ? UtGetOpName(Node1->ParseOpcode): NULL,
        Node2, Node2 ? UtGetOpName(Node2->ParseOpcode): NULL);

    if (!Node1 || !Node2)
    {
        return Node1;
    }

    Node1->Child = Node2;

    /* Set the child and all peers of the child to point to the parent */

    Next = Node2;
    while (Next)
    {
        Next->Parent = Node1;
        Next = Next->Peer;
    }

    return Node1;
}


/*******************************************************************************
 *
 * FUNCTION:    TrWalkParseTree
 *
 * PARAMETERS:  Visitation              - Type of walk
 *              DescendingCallback      - Called during tree descent
 *              AscendingCallback       - Called during tree ascent
 *              Context                 - To be passed to the callbacks
 *
 * RETURN:      None
 *
 * DESCRIPTION: Walk the entire parse tree.
 *
 ******************************************************************************/

void
TrWalkParseTree (
    ASL_PARSE_NODE          *Node,
    UINT32                  Visitation,
    ASL_WALK_CALLBACK       DescendingCallback,
    ASL_WALK_CALLBACK       AscendingCallback,
    void                    *Context)
{
    UINT32                  Level;
    BOOLEAN                 NodePreviouslyVisited;


    if (!RootNode)
    {
        return;
    }

    Level = 0;
    NodePreviouslyVisited = FALSE;

    switch (Visitation)
    {
    case ASL_WALK_VISIT_DOWNWARD:

        while (Node)
        {
            if (!NodePreviouslyVisited)
            {
                /*
                 * Let the callback process the node.
                 */
                DescendingCallback (Node, Level, Context);

                /* Visit children first, once */

                if (Node->Child)
                {
                    Level++;
                    Node = Node->Child;
                    continue;
                }
            }

            /* No more children, visit peers */

            if (Node->Peer)
            {
                Node = Node->Peer;
                NodePreviouslyVisited = FALSE;
            }
            else
            {
                /* No children or peers, re-visit parent */

                if (Level != 0 )
                {
                    Level--;
                }
                Node = Node->Parent;
                NodePreviouslyVisited = TRUE;
            }
        }

        break;


    case ASL_WALK_VISIT_UPWARD:

        while (Node)
        {
            /* Visit leaf node (no children) or parent node on return trip */

            if ((!Node->Child) ||
                (NodePreviouslyVisited))
            {
                /*
                 * Let the callback process the node.
                 *
                 */
                AscendingCallback (Node, Level, Context);
            }
            else
            {
                /* Visit children first, once */

                Level++;
                Node = Node->Child;
                continue;
            }

            /* No more children, visit peers */

            if (Node->Peer)
            {
                Node = Node->Peer;
                NodePreviouslyVisited = FALSE;
            }
            else
            {
                /* No children or peers, re-visit parent */

                if (Level != 0 )
                {
                    Level--;
                }
                Node = Node->Parent;
                NodePreviouslyVisited = TRUE;
            }
        }
        break;


     case ASL_WALK_VISIT_TWICE:

        while (Node)
        {
            if (NodePreviouslyVisited)
            {
                AscendingCallback (Node, Level, Context);
            }
            else
            {
                /*
                 * Let the callback process the node.
                 */
                DescendingCallback (Node, Level, Context);

                /* Visit children first, once */

                if (Node->Child)
                {
                    Level++;
                    Node = Node->Child;
                    continue;
                }
            }

            /* No more children, visit peers */

            if (Node->Peer)
            {
                Node = Node->Peer;
                NodePreviouslyVisited = FALSE;
            }
            else
            {
                /* No children or peers, re-visit parent */

                if (Level != 0 )
                {
                    Level--;
                }
                Node = Node->Parent;
                NodePreviouslyVisited = TRUE;
            }
        }
        break;
    }
}


