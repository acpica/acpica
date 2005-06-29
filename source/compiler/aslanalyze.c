
/******************************************************************************
 *
 * Module Name: aslanalyze.c - check for semantic errors
 *              $Revision: 1.5 $
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
AnSemanticAnalysisWalkBegin (
    ASL_PARSE_NODE              *Node,
    UINT32                      Level,
    void                        *Context)
{
    ASL_ANALYSIS_WALK_INFO      *WalkInfo = (ASL_ANALYSIS_WALK_INFO *) Context;
    ASL_METHOD_INFO             *MethodInfo = WalkInfo->MethodStack;
    ASL_PARSE_NODE              *Next;
    UINT32                      RegisterNumber;
    char                        LocalName[] = "Local0";
    char                        ArgName[] = "Arg0";


    UtPrintFormattedName (Node->ParseOpcode, Level);
    DbgPrint ("DOWN\n");


    switch (Node->ParseOpcode)
    {
    case METHOD:

        MethodInfo = UtLocalCalloc (sizeof (ASL_METHOD_INFO));
        MethodInfo->Next = WalkInfo->MethodStack;
        WalkInfo->MethodStack = MethodInfo;

        /* Get the NumArguments node */

        Next = Node->Child;
        Next = Next->Peer;
        MethodInfo->NumArguments = (Next->Value.Integer8 & 0x07);

        DbgPrint ("Method obj %p pushed\n", MethodInfo);

        break;


    case LOCAL0:
    case LOCAL1:
    case LOCAL2:
    case LOCAL3:
    case LOCAL4:
    case LOCAL5:
    case LOCAL6:
    case LOCAL7:
        RegisterNumber = (Node->AmlOpcode & 0x000F);
        DbgPrint ("Found Local%d ", RegisterNumber);

        if (Node->Flags & NODE_IS_TARGET)
        {
            DbgPrint ("[IS a target]\n");
            if (!MethodInfo->LocalInitialized[RegisterNumber])
            {
                DbgPrint ("First init of this local\n");
            }
            MethodInfo->LocalInitialized[RegisterNumber] = TRUE;

        }
        else
        {
            DbgPrint ("[Is NOT a target]\n");
            if (!MethodInfo->LocalInitialized[RegisterNumber])
            {
                LocalName[strlen (LocalName) -1] = RegisterNumber + 0x30;
                AslErrorMsg (ASL_ERROR_LOCAL_INIT, Node->LineNumber, LocalName);
            }
        }
        break;


    case ARG0:
    case ARG1:
    case ARG2:
    case ARG3:
    case ARG4:
    case ARG5:
    case ARG6:
        RegisterNumber = (Node->AmlOpcode & 0x000F) - 8;
        DbgPrint ("Found Arg%d ", RegisterNumber);

        if (RegisterNumber >= MethodInfo->NumArguments)
        {
            ArgName[strlen (ArgName) -1] = RegisterNumber + 0x30;
            AslErrorMsg (ASL_ERROR_ARG_INVALID, Node->LineNumber, ArgName);
        }
        if (Node->Flags & NODE_IS_TARGET)
        {
            DbgPrint ("[IS a target]\n");
        }
        else
        {
            DbgPrint ("[Is NOT a target]\n");
        }
        break;
        

    case RETURN:

        if ((Node->Child) &&
            (Node->Child->ParseOpcode != DEFAULT_ARG))
        {
            MethodInfo->NumReturnWithValue++;
        }
        else
        {
            MethodInfo->NumReturnNoValue++;
        }
        break;


    case NAMESEG:
    case NAMESTRING:

       break;

    } /* end switch */


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

BOOLEAN
AnLastStatementIsReturn (
    ASL_PARSE_NODE              *Node)
{    
    ASL_PARSE_NODE              *Next;


    /*
     * Check if last statement is a return
     */
    Next = ASL_GET_CHILD_NODE (Node);
    while (Next)
    {
        if ((!Next->Peer) &&
            (Next->ParseOpcode == RETURN))
        {
            return TRUE;
        }

        Next = ASL_GET_PEER_NODE (Next);
    }

    return FALSE;
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
AnSemanticAnalysisWalkEnd (
    ASL_PARSE_NODE              *Node,
    UINT32                      Level,
    void                        *Context)
{
    ASL_ANALYSIS_WALK_INFO      *WalkInfo = (ASL_ANALYSIS_WALK_INFO *) Context;
    ASL_METHOD_INFO             *MethodInfo;
    ASL_PARSE_NODE              *Next;
    ASL_PARSE_NODE              *SecondToLastNode = NULL;
    ASL_PARSE_NODE              *LastNode = NULL;




    UtPrintFormattedName (Node->ParseOpcode, Level);
    DbgPrint ("UP\n");


    switch (Node->ParseOpcode)
    {
    case METHOD:

        MethodInfo = WalkInfo->MethodStack;
        WalkInfo->MethodStack = MethodInfo->Next;



        Next = ASL_GET_CHILD_NODE (Node);
        while (Next)
        {
            SecondToLastNode = LastNode;
            LastNode = Next;
            Next = ASL_GET_PEER_NODE (Next);
        }

        if ((SecondToLastNode) &&
            (LastNode) &&
            (SecondToLastNode->ParseOpcode == IF) &&
            (LastNode->ParseOpcode == ELSE) &&
            AnLastStatementIsReturn (SecondToLastNode) &&
            AnLastStatementIsReturn (LastNode))
        {
        }
        
        /*
         * Check if last statement is a return
         */
        else if (!AnLastStatementIsReturn (Node))
        {
            /* No return statement, this is equivalent to Return () */

            MethodInfo->NumReturnNoValue++;
        }


        /*
         * Check for case where some return statements have a return value
         * and some do not.  Exit without a return statement is a return with
         * no value
         */

        if (MethodInfo->NumReturnNoValue &&
            MethodInfo->NumReturnWithValue)
        {
            AslWarningMsg (ASL_WARNING_RETURN_TYPES, Node->LineNumber, Node->ExternalName);
        }


        /*
         * Check predefined method names for correct return behavior
         */
/******** TBD: needs to be more sophisticated
        if (!strcmp (Node->ExternalName, "_STA"))
        {
            if (MethodInfo->NumReturnNoValue)
            {
                AslErrorMsg (ASL_ERROR_PREDEFINED_METHOD_RETURN, 
                                Node->LineNumber, Node->ExternalName);
            }
        }
*/

        DbgPrint ("Method obj %p popped\n", MethodInfo);
        free (MethodInfo);

        break;
    }



}







