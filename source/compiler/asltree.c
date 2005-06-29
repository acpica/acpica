
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "AslCompiler.y.h"
#include "AslCompiler.h"
#include "acpi.h"


extern const char * const       yytname[];

char *
TgGetOpName (
    UINT32              ParseOpcode)
{
    return (char *) yytname [ParseOpcode - 255];
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
TgAddNode (
    void                    *Thing)
{


    DbgPrint ("\nAddNode: %p\n\n", Thing);

    return (char *) ((UINT32) Thing + 1);
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
                TgGetOpName (Node->ParseOpcode),
                TgGetOpName (ParseOpcode));

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
                Node, NumChildren, TgGetOpName(ParseOpcode));
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
                Node, TgGetOpName(ParseOpcode), Value);
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
        Node1, Node1 ? TgGetOpName(Node1->ParseOpcode) : NULL, 
        Node2, Node2 ? TgGetOpName(Node2->ParseOpcode) : NULL);

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



ASL_PARSE_NODE *
_TgLinkChildNode (
    ASL_PARSE_NODE          *Node1,
    ASL_PARSE_NODE          *Node2)
{
    ASL_PARSE_NODE          *Next;


    DbgPrint ("\nLinkChildNode: Parent=%p (%s), Child=%p (%s)\n\n", 
        Node1, Node1 ? TgGetOpName(Node1->ParseOpcode): NULL,
        Node2, Node2 ? TgGetOpName(Node2->ParseOpcode): NULL);

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
                 *
                 * NOTE: The callback may visit several "grouped" nodes simultaneously
                 * and change the value of "node" (and Level) so that these nodes are not 
                 * visited twice.
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



/*******************************************************************************
 *
 * FUNCTION:   OBSOLETE 
 *
 * PARAMETERS:  
 *
 * RETURN:      
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/


void
TgWalkTree (void)
{
    ASL_PARSE_NODE          *Node;
    UINT32                  Level;
    UINT32                  i;
    BOOLEAN                 Visited;

    
    if (!RootNode)
    {
        return;
    }


    Level = 0;
    Visited = FALSE;
    Node = RootNode;
    while (Node)
    {
        if (!Visited)
        {
            for (i = 0; i < Level; i++)
            {
                DbgPrint ("    ");
            }

            if ((Node->ParseOpcode > 255) && (Node->ParseOpcode < 500))
                DbgPrint ("%s\n", yytname[Node->ParseOpcode-255]);

            if (Node->Child)
            {
                if ((UINT32) Node->Child < 0x0000FFFF)
                {
                    printf ("bogus child\n");
                }
                else
                {
                    Level++;
                    Node = Node->Child;
                    continue;
                }
            }
        }

        if (Node->Peer)
        {
            Node = Node->Peer;
            Visited = FALSE;
        }
        else
        {
            Level--;
            Node = Node->Parent;
            Visited = TRUE;
        }
    }

}


