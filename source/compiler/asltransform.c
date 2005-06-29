
/******************************************************************************
 *
 * Module Name: asltransform - Parse tree transforms
 *              $Revision: 1.5 $
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

#define _COMPONENT          ACPI_COMPILER
        MODULE_NAME         ("asltransform")




/*******************************************************************************
 *
 * FUNCTION:    TrAmlGetNextTempName
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: +
 *
 ******************************************************************************/

char *
TrAmlGetNextTempName (
    char                    **NamePath)
{
    char                    *TempName;


    if (Gbl_TempCount > 255)
    {
        /* Too many temps */
        /* TBD: issue eror message */
        *NamePath = "ERROR";
        return ("Error");
    }

    TempName = UtLocalCalloc (6);
    UtConvertByteToHex ((UINT8) Gbl_TempCount, (UINT8 *) &TempName [1]);
    Gbl_TempCount++;

    /* First three characters are always "\_T" */

    TempName[0] = '\\';
    TempName[1] = '_';
    TempName[2] = 'T';

    *NamePath = TempName;
    return (&TempName[1]);
}


/*******************************************************************************
 *
 * FUNCTION:    TrAmlInitLineNumbers
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
TrAmlInitLineNumbers (
    ASL_PARSE_NODE          *Node,
    ASL_PARSE_NODE          *Neighbor)
{

    Node->EndLine           = Neighbor->EndLine;
    Node->EndLogicalLine    = Neighbor->EndLogicalLine;
    Node->LineNumber        = Neighbor->LineNumber;
    Node->LogicalByteOffset = Neighbor->LogicalByteOffset;
    Node->LogicalLineNumber = Neighbor->LogicalLineNumber;
}


/*******************************************************************************
 *
 * FUNCTION:    TrAmlInitNode
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
TrAmlInitNode (
    ASL_PARSE_NODE          *Node,
    UINT16                  ParseOpcode)
{

    Node->ParseOpcode = ParseOpcode;
    strncpy (Node->ParseOpName, UtGetOpName (ParseOpcode), 12);

}



/*******************************************************************************
 *
 * FUNCTION:    TrAmlSetSubtreeParent
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
TrAmlSetSubtreeParent (
    ASL_PARSE_NODE          *Node,
    ASL_PARSE_NODE          *Parent)
{
    ASL_PARSE_NODE          *Next;

    Next = Node;
    while (Next)
    {
        Next->Parent    = Parent;
        Next            = Next->Peer;
    }
}



/*******************************************************************************
 *
 * FUNCTION:    TrAmlInsertPeer
 *
 * PARAMETERS:  
 *
 * RETURN:      None
 *
 * DESCRIPTION: 
 *
 ******************************************************************************/

void
TrAmlInsertPeer (
    ASL_PARSE_NODE          *Node,
    ASL_PARSE_NODE          *NewPeer)
{

    NewPeer->Peer   = Node->Peer;
    Node->Peer      = NewPeer;
}



/*******************************************************************************
 *
 * FUNCTION:    TrAmlTransformWalk
 *
 * PARAMETERS:  ASL_WALK_CALLBACK
 *
 * RETURN:      None
 *
 * DESCRIPTION: Parse tree walk to generate both the AML opcodes and the AML
 *              operands.
 *
 ******************************************************************************/

ACPI_STATUS
TrAmlTransformWalk (
    ASL_PARSE_NODE          *Node,
    UINT32                  Level,
    void                    *Context)
{


    TrTransformSubtree (Node);
    return (AE_OK);
}




/*******************************************************************************
 *
 * FUNCTION:    TrTransformSubtree
 *
 * PARAMETERS:  Node        - The parent parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prepare nodes to be output as AML data and operands.  The more
 *              complex AML opcodes require processing of the child nodes
 *              (arguments/operands).
 *
 ******************************************************************************/

void
TrTransformSubtree (
    ASL_PARSE_NODE              *Node)
{


    if (Node->AmlOpcode == AML_RAW_DATA_BYTE)
    {
        return;
    }


    switch (Node->ParseOpcode)
    {
    case DEFINITIONBLOCK:
        TrDoDefinitionBlock (Node);
        break;

    case ELSEIF:
        TrDoElseif (Node);
        break;

    case SWITCH:
        TrDoSwitch (Node);
        break;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    TrDoDefinitionBlock
 *
 * PARAMETERS:  Node        - Parse node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Find the end of the definition block and set a global to this
 *              node.  It is used by the compiler to insert compiler-generated
 *              names at the root level of the namespace.
 *
 ******************************************************************************/

void
TrDoDefinitionBlock (
    ASL_PARSE_NODE          *Node)
{
    ASL_PARSE_NODE          *Next;
    UINT32                  i;


    Next = Node->Child;
    for (i = 0; i < 5; i++)
    {
        Next = Next->Peer;
    }

    

    Gbl_FirstLevelInsertionNode = Next;
}


/*******************************************************************************
 *
 * FUNCTION:    TrDoElseif
 *
 * PARAMETERS:  Node        - Parse node for ELSEIF
 *
 * RETURN:      None
 *
 * DESCRIPTION: Transform an Elseif into an Else and If AML opcode
 *
 ******************************************************************************/

void
TrDoElseif (
    ASL_PARSE_NODE          *Node)
{
    ASL_PARSE_NODE          *IfNode;



    /* Change the ELSEIF into an ELSE */

    TrAmlInitNode (Node, ELSE);

    /* Create a new IF node */

    IfNode              = TrCreateLeafNode (IF);
    IfNode->Parent      = Node;
    TrAmlInitLineNumbers (IfNode, Node);


    /* Insert the the IF node first in the ELSE child list */

    IfNode->Child       = Node->Child;
    Node->Child         = IfNode;

    TrAmlSetSubtreeParent (IfNode->Child, IfNode);
}


/*******************************************************************************
 *
 * FUNCTION:    TrDoSwitch
 *
 * PARAMETERS:  StartNode        - Parse node for SWITCH
 *
 * RETURN:      None
 *
 *
 * DESCRIPTION: Translate switch to if/else pairs
 *
 ******************************************************************************/

void
TrDoSwitch (
    ASL_PARSE_NODE          *StartNode)
{
    ASL_PARSE_NODE          *Next;
    ASL_PARSE_NODE          *Case = NULL;
    ASL_PARSE_NODE          *CaseBlock = NULL;
    ASL_PARSE_NODE          *Default = NULL;
    ASL_PARSE_NODE          *CurrentParentNode;
    ASL_PARSE_NODE          *Conditional = NULL;
    ASL_PARSE_NODE          *Predicate;
    ASL_PARSE_NODE          *Peer;
    ASL_PARSE_NODE          *NewNode;
    ASL_PARSE_NODE          *NewNode2;
    char                    *PredicateValueName;
    char                    *PredicateValuePath;


    CurrentParentNode = StartNode;
    PredicateValueName = TrAmlGetNextTempName (&PredicateValuePath);

    /* First child is the predicate */

    Next = StartNode->Child;
    Peer = Next->Peer;

    /* CASE statements start at next child */

    while (Peer)
    {
        Next = Peer;
        Peer = Next->Peer;

        if (Next->ParseOpcode == CASE)
        {
            if (Case)
            {
                /* Add an ELSE to complete the previous CASE */

                NewNode             = TrCreateLeafNode (ELSE);
                NewNode->Parent     = Conditional->Parent;
                TrAmlInitLineNumbers (NewNode, NewNode->Parent);

                /* Link ELSE node as a peer to the previous IF */

                TrAmlInsertPeer (Conditional, NewNode);
                CurrentParentNode   = NewNode;
            }

            Case = Next;
            Conditional = Case;
            CaseBlock = Case->Child->Peer;
            Conditional->Child->Peer = NULL;

            /* 
             * change Case() to:  If (PredicateValue == CaseValue) {...}
             * Case->Child is the case value
             * Case->Child->Peer is the beginning of the case block
             */
            NewNode = TrCreateValuedLeafNode (NAMESTRING, 
                            (NATIVE_INT) PredicateValuePath);

            Predicate = Case->Child;
            Predicate->Peer = NewNode;
            TrAmlInitLineNumbers (NewNode, Predicate);


            NewNode2            = TrCreateLeafNode (LEQUAL);
            NewNode2->Parent    = Conditional;
            NewNode2->Child     = Predicate;
            TrAmlInitLineNumbers (NewNode2, Conditional);

            TrAmlSetSubtreeParent (Predicate, NewNode2);

            Predicate           = NewNode2;
            Predicate->Peer     = CaseBlock;

            TrAmlSetSubtreeParent (Predicate, Conditional);

            /* Reinitialize the CASE node to an IF node */

            Conditional->Child = Predicate;
            TrAmlInitNode (Conditional, IF);

            /*
             * The first CASE(IF) is not nested under an ELSE.
             * All other CASEs are children of a parent ELSE.
             */
            if (CurrentParentNode == StartNode)
            {
                Conditional->Parent = CurrentParentNode->Parent;

                /* Link IF into the peer list */

                TrAmlInsertPeer (CurrentParentNode, Conditional);
            }
            else
            {
                /* 
                 * The IF is a child of previous IF/ELSE.  It 
                 * is therefore without peer.
                 */
                CurrentParentNode->Child = Conditional;
                Conditional->Parent      = CurrentParentNode;
                Conditional->Peer        = NULL;
            }
        }

        else if (Next->ParseOpcode == DEFAULT)
        {
            if (Default)
            {
                /* More than one Default */
            }

            /* Save the DEFAULT node for later, after CASEs */

            Default = Next;
        }

        else
        {
            /* Unkown peer opcode */
            printf ("Unknown switch opcode\n");
        }
    }


    /*
     * Add the default at the end of the if/else construct
     */
    if (Default)
    {
        if (Case)
        {
            /* Add an ELSE first */

            TrAmlInitNode (Default, ELSE);
            Default->Parent = Conditional->Parent;
        }
        else
        {
            /* There were no CASE statements, no ELSE needed */

            TrAmlInsertPeer (CurrentParentNode, Default->Child);
        }
    }

    /*
     * Add a NAME node for the temp integer 
     */
    NewNode             = TrCreateLeafNode (NAME);
    NewNode->Parent     = Gbl_FirstLevelInsertionNode->Parent;

    NewNode2            = TrCreateValuedLeafNode (NAMESTRING, 
                                (NATIVE_INT) PredicateValueName);
    NewNode->Child      = NewNode2;
    NewNode2->Peer      = TrCreateValuedLeafNode (INTEGER, 0);

    TrAmlSetSubtreeParent (NewNode2, NewNode);

    /* Insert this node at the global level of the ASL */

    TrAmlInsertPeer (Gbl_FirstLevelInsertionNode, NewNode);
    TrAmlInitLineNumbers (NewNode, Gbl_FirstLevelInsertionNode);
    TrAmlInitLineNumbers (NewNode2, Gbl_FirstLevelInsertionNode);
    TrAmlInitLineNumbers (NewNode2->Peer, Gbl_FirstLevelInsertionNode);


    /*
     * Change the SWITCH node to a STORE (predicate value, _Txx)
     */
    TrAmlInitNode (StartNode, STORE);

    Predicate               = StartNode->Child;
    Predicate->Child        = NULL;

    NewNode                 = TrCreateValuedLeafNode (NAMESTRING, 
                                    (NATIVE_INT) PredicateValuePath);
    NewNode->Parent         = StartNode;
    Predicate->Peer         = NewNode;
}



