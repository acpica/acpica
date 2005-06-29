
/******************************************************************************
 *
 * Module Name: asltree - parse tree management
 *              $Revision: 1.4 $
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


#include "AslCompiler.h"
#include "AslCompiler.y.h"


extern const char * const       yytname[];



/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/


ASL_PARSE_NODE *
TgAllocateNode (
    UINT32                  ParseOpcode)
{
    ASL_PARSE_NODE          *Node;


    Node = calloc (sizeof (ASL_PARSE_NODE), 1);
    if (!Node)
    {
        fprintf (stderr, "Memory allocation failure while building parse tree\n");
        printf ("Memory allocation failure while building parse tree\n");
        exit (0);
    }

    Node->ParseOpcode = ParseOpcode;
    return Node;
}



/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

char *
_TgUpdateNode (
    UINT32                  ParseOpcode,
    ASL_PARSE_NODE          *Node)
{


    DbgPrint ("\nUpdateNode: Old - %s, New - %s\n\n",
                UtGetOpName (Node->ParseOpcode),
                UtGetOpName (ParseOpcode));

    Node->ParseOpcode = ParseOpcode;
    return (char *) Node;
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

char *
TgCreateNode (
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

    Node = TgAllocateNode (ParseOpcode);

    DbgPrint ("\nCreateNode  NewParent %p Child %d Op %s  ", 
                Node, NumChildren, UtGetOpName(ParseOpcode));
    RootNode = Node;


    switch (ParseOpcode)
    {
    case DEFINITIONBLOCK:
        DbgPrint ("DEFINITION_BLOCK (Tree Completed)->");
        break;

    case OPERATIONREGION:
        DbgPrint ("OPREGION->"); 
        break;

    case OR:
        DbgPrint ("OR->");
        break;
    }


    /* Link the new node to it's children */

    PrevChild = NULL;
    FirstChild = TRUE;
    for (i = 0; i < NumChildren; i++)
    {
        Child = va_arg (ap, ASL_PARSE_NODE *);
        DbgPrint ("%p, ", Child);


        /* 
         * If child is NULL, this means that an optional argument
         * was omitted.  We must create a placeholder with a special
         * opcode (DEFAULT_ARG) so that the code generator will know
         * that it must emit the correct default for this argument
         */

        if (!Child)
        {
            Child = TgAllocateNode (DEFAULT_ARG);
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

    DbgPrint ("\n\n");


    return (char *) Node;
}



/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

char *
TgCreateLeafNode (
    UINT32                  ParseOpcode,
    void                    *Value)
{
    ASL_PARSE_NODE          *Node;


    Node = TgAllocateNode (ParseOpcode);

    DbgPrint ("\nCreateLeafNode  NewNode %p  Op %s  Value %X  ", 
                Node, UtGetOpName(ParseOpcode), Value);
    Node->Value.Pointer = Value;

    switch (ParseOpcode)
    {
    case STRING_LITERAL:
        DbgPrint ("STRING->%s", Value);
        break;

    case NAMESEG:
        DbgPrint ("NAMESEG->%s", Value);
        break;

    case NAMESTRING:
        DbgPrint ("NAMESTRING->%s", Value);
        break;

    case EISAID:
        DbgPrint ("EISAID->%s", Value);
        break;

    default: 
        break;
    }

    DbgPrint ("\n\n");

    return (char *) Node;
}


/*******************************************************************************
 *
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

ASL_PARSE_NODE *
_TgLinkPeerNode (
    ASL_PARSE_NODE          *Node1,
    ASL_PARSE_NODE          *Node2)
{
    ASL_PARSE_NODE          *Next;

    DbgPrint ("\nLinkPeerNode: 1=%p (%s), 2=%p (%s)\n\n", 
        Node1, Node1 ? UtGetOpName(Node1->ParseOpcode) : NULL, 
        Node2, Node2 ? UtGetOpName(Node2->ParseOpcode) : NULL);

    if (!Node1 || !Node2)
    {
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
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

ASL_PARSE_NODE *
_TgLinkChildNode (
    ASL_PARSE_NODE          *Node1,
    ASL_PARSE_NODE          *Node2)
{
    ASL_PARSE_NODE          *Next;


    DbgPrint ("\nLinkChildNode: Parent=%p (%s), Child=%p (%s)\n\n", 
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
 * FUNCTION:    
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
TgWalkParseTree (
    UINT32                      Visitation,
    ASL_WALK_CALLBACK           Callback,
    void                        *Context)
{
    ASL_PARSE_NODE              *Node;
    UINT32                      Level;
    BOOLEAN                     NodePreviouslyVisited;

    
    if (!RootNode)
    {
        return;
    }


    Level = 0;
    NodePreviouslyVisited = FALSE;
    Node = RootNode;

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
                Callback (Node, Level, Context);

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

            /* No children or peers, re-visit parent */

            else
            {
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
                Callback (Node, Level, Context);
            }

            /* Visit children first, once */

            else
            {
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

            /* No children or peers, re-visit parent */

            else
            {
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
         break;  /* Not implemented */

    }
}




