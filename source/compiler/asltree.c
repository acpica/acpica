
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "AslCompiler.y.h"
#include "AslCompiler.h"
#include "acpi.h"


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
TgUpdateNode (
    UINT32                  ParseOpcode,
    ASL_PARSE_NODE          *Node)
{


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

    DbgPrint ("\nCreateNode  NewNode %p  Opcode %X  ", Node, ParseOpcode);
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

    DbgPrint ("\nCreateLeafNode  NewNode %p  Opcode %X  Value %X  ", Node, ParseOpcode, Value);
    Node->Value = Value;

    switch (ParseOpcode)
    {
    case STRING_LITERAL:
        DbgPrint ("STRING->%s", Value);
        break;

    case INTEGER:
        DbgPrint ("INTEGER->0x%X", Value);
        break;

    case BYTECONST:
        DbgPrint ("BYTECONST->0x%02.2X", Value);
        Node->Value = (void *) (((UINT32) Value) & 0xFF);
        break;

    case WORDCONST:
        DbgPrint ("WORDCONST->0x%04.4X", Value);
        Node->Value = (void *) (((UINT32) Value) & 0xFFFF);
        break;

    case DWORDCONST:
        DbgPrint ("DWORDCONST->0x%08.8X", Value);
        break;

    case NAMESEG:
        DbgPrint ("NAMESEG->%s", Value);
        break;

    case NAMESTRING:
        DbgPrint ("NAMESTRING->%s", Value);
        break;

    case ZERO:
        DbgPrint ("ZERO Op");
        break;

    case ONE:
        DbgPrint ("ONE Op");
        break;

    case ONES:
        DbgPrint ("ONES Op");
        break;

    case DEBUG:
        DbgPrint ("DEBUG Op");
        break;

    case ARG0:
        DbgPrint ("ARG0 Op");
        break;

    case ARG1:
        DbgPrint ("ARG1 Op");
        break;

    case ARG2:
        DbgPrint ("ARG2 Op");
        break;

    case ARG3:
        DbgPrint ("ARG3 Op");
        break;

    case ARG4:
        DbgPrint ("ARG4 Op");
        break;

    case ARG5:
        DbgPrint ("ARG5 Op");
        break;

    case ARG6:
        DbgPrint ("ARG6 Op");
        break;

    case LOCAL0:
        DbgPrint ("LOCAL0 Op");
        break;

    case LOCAL1:
        DbgPrint ("LOCAL1 Op");
        break;

    case LOCAL2:
        DbgPrint ("LOCAL2 Op");
        break;

    case LOCAL3:
        DbgPrint ("LOCAL3 Op");
        break;

    case LOCAL4:
        DbgPrint ("LOCAL4 Op");
        break;

    case LOCAL5:
        DbgPrint ("LOCAL5 Op");
        break;

    case LOCAL6:
        DbgPrint ("LOCAL6 Op");
        break;

    case LOCAL7:
        DbgPrint ("LOCAL7 Op");
        break;

    case EISAID:
        DbgPrint ("EISAID->%s", Value);
        break;

    default: 
        DbgPrint ("UNKNOWN type");
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

    DbgPrint ("LinkPeerNode: 1=%p, 2=%p\n", Node1, Node2);

    if (!Node1 || !Node2)
    {
        return Node1;
    }

    Node1->Parent = Node2->Parent;
    Node1->Peer = Node2;

    return Node1;

}



ASL_PARSE_NODE *
_TgLinkChildNode (
    ASL_PARSE_NODE          *Node1,
    ASL_PARSE_NODE          *Node2)
{

    DbgPrint ("LinkChildNode: Parent=%p, Child=%p\n", Node1, Node2);

    if (!Node1 || !Node2)
    {
        return Node1;
    }

    Node1->Child = Node2;
    Node2->Parent = Node1;

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


