/******************************************************************************
 * 
 * Module Name: pswalk - Parser routines to walk parsed op tree(s)
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



#include <acpi.h>
#include <amlcode.h>
#include <parser.h>
#include <namespace.h>
#include <interpreter.h>

#define _COMPONENT          PARSER
        MODULE_NAME         ("pswalk");



ACPI_STATUS
PsxObjStackDeleteAll (
    ACPI_WALK_STATE         *WalkState)
{
    UINT32                  i;


    FUNCTION_TRACE_PTR ("PsxObjStackDeleteAll", WalkState);


    for (i = 0; i < OBJ_NUM_OPERANDS; i++)
    {
        if (WalkState->Operands[i])
        {
            CmDeleteOperand (&WalkState->Operands[i]);
        }
    }

    return_ACPI_STATUS (AE_OK);
}



ACPI_STATUS
PsxObjStackPush (
    void                    *Object,
    ACPI_WALK_STATE         *WalkState)
{


    if (WalkState->NumOperands >= OBJ_NUM_OPERANDS)
    {
        DEBUG_PRINT (ACPI_ERROR, ("PsxObjStackPush: overflow! Obj=%X State=%X #Ops=%X\n", 
                        Object, WalkState, WalkState->NumOperands));
        return AE_STACK_OVERFLOW;
    }

    WalkState->Operands [WalkState->NumOperands] = Object;
    WalkState->NumOperands++;

    DEBUG_PRINT (TRACE_EXEC, ("PsxObjStackPush: Obj=%X State=%X #Ops=%X\n", 
                    Object, WalkState, WalkState->NumOperands));
}


ACPI_STATUS
PsxObjStackPop (
    UINT32                  PopCount,
    ACPI_WALK_STATE         *WalkState)
{
    UINT32                  i;


    for (i = 0; i < PopCount; i++)
    {
        if (WalkState->NumOperands == 0)
        {
            DEBUG_PRINT (ACPI_ERROR, ("PsxObjStackPop: Underflow! Count=%X State=%X #Ops=%X\n", 
                            PopCount, WalkState, WalkState->NumOperands));
            return AE_STACK_UNDERFLOW;
        }

        WalkState->NumOperands--;
        WalkState->Operands [WalkState->NumOperands] = NULL;
    }

    DEBUG_PRINT (TRACE_EXEC, ("PsxObjStackPop: Count=%X State=%X #Ops=%X\n", 
                    PopCount, WalkState, WalkState->NumOperands));
}

    
void *
PsxObjStackGetValue (
    UINT32                  Index,
    ACPI_WALK_STATE         *WalkState)
{

    FUNCTION_TRACE_PTR ("PsxObjStackGetValue", WalkState);


    if (WalkState->NumOperands == 0)
    {
        return_VALUE (NULL);
    }

    if (Index > (WalkState->NumOperands - (UINT32) 1))
    {
        return_VALUE (NULL);
    }

    return_VALUE (WalkState->Operands [(WalkState->NumOperands - 1) - Index]);
}


/*******************************************************************************
 *
 * FUNCTION:    PsGetCurrentWalkState
 *
 * PARAMETERS:  WalkList        - Get current active state for this walk list
 *
 * RETURN:      Pointer to the current walk state
 *
 * DESCRIPTION: Get the walk state that is at the head of the list (the "current"
 *              walk state.
 *
 ******************************************************************************/

ACPI_WALK_STATE *
PsGetCurrentWalkState (
    ACPI_WALK_LIST          *WalkList)

{

    DEBUG_PRINT (TRACE_PARSE, ("PsGetCurrentWalkState, =%p\n", WalkList->WalkState));

    return WalkList->WalkState;
}


/*******************************************************************************
 *
 * FUNCTION:    PsPushWalkState
 *
 * PARAMETERS:  WalkState       - State to push
 *              WalkList        - The list that owns the walk stack
 *
 * RETURN:      None
 *
 * DESCRIPTION: Place the WalkState at the head of the state list.
 *
 ******************************************************************************/

void
PsPushWalkState (
    ACPI_WALK_STATE         *WalkState,
    ACPI_WALK_LIST          *WalkList)
{


    FUNCTION_TRACE ("PsPushWalkState");


    WalkState->Next     = WalkList->WalkState;
    WalkList->WalkState = WalkState;

    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    PsPopWalkState 
 *
 * PARAMETERS:  WalkList        - The list that owns the walk stack
 *
 * RETURN:      A WalkState object popped from the stack
 *
 * DESCRIPTION: Remove and return the walkstate object that is at the head of
 *              the walk stack for the given walk list.  NULL indicates that 
 *              the list is empty.
 *
 ******************************************************************************/

ACPI_WALK_STATE *
PsPopWalkState (
    ACPI_WALK_LIST          *WalkList)
{
    ACPI_WALK_STATE         *WalkState;


    FUNCTION_TRACE ("PsPopWalkState");


    WalkState = WalkList->WalkState;

    if (WalkState)
    {
        /* Next walk state becomes the current walk state */

        WalkList->WalkState = WalkState->Next;
        WalkState->Next = NULL;
    }

    return_VALUE (WalkState);
}


/*******************************************************************************
 *
 * FUNCTION:    PsCreateWalkState
 *
 * PARAMETERS:  Origin          - Starting point for this walk
 *              WalkList        - Owning walk list
 *
 * RETURN:      Pointer to the new walk state.
 *
 * DESCRIPTION: Allocate and initialize a new walk state.  The current walk state
 *              is set to this new state.
 *
 ******************************************************************************/

ACPI_WALK_STATE *
PsCreateWalkState (
    ACPI_GENERIC_OP         *Origin,
    ACPI_WALK_LIST          *WalkList)
{
    ACPI_WALK_STATE         *WalkState;


    FUNCTION_TRACE ("PsCreateWalkState");


    WalkState = CmCallocate (sizeof (ACPI_WALK_STATE));
    if (!WalkState)
    {
        return_VALUE (NULL);
    }

    WalkState->Origin           = Origin;

    /* Put the new state at the head of the walk list */

    PsPushWalkState (WalkState, WalkList);

    return_VALUE (WalkState);
}



/*******************************************************************************
 *
 * FUNCTION:    PsGetNextWalkOp
 *
 * PARAMETERS:  WalkState           - Current state of the walk
 *              Op                  - Current Op to be walked
 *              AscendingCallback   - Procedure called when Op is complete
 *              PrevOp              - Where the previous Op is stored
 *              NextOp              - Where the next Op in the walk is stored
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get the next Op in a walk of the parse tree.
 *
 ******************************************************************************/

ACPI_STATUS
PsGetNextWalkOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         *Op,
    INTERPRETER_CALLBACK    AscendingCallback,
    ACPI_GENERIC_OP         **PrevOp,
    ACPI_GENERIC_OP         **NextOp)
{
    ACPI_GENERIC_OP         *Next;
    ACPI_GENERIC_OP         *Parent;
    ACPI_GENERIC_OP         *GrandParent;
    ACPI_STATUS             Status;


    FUNCTION_TRACE_PTR ("PsGetNextWalkOp", Op);


    /* Look for an argument or child of the current op */

    Next = PsGetArg (Op, 0);
    if (Next)
    {
        /* Still going downward in tree (Op is not completed yet) */

        *PrevOp = Op;
        *NextOp = Next;
        return_ACPI_STATUS (AE_OK);
    }

    /* 
     * No more children, this Op is complete.  Save Next and Parent
     * in case the Op object gets deleted by the callback routine
     */

    Next = Op->Next;
    Parent = Op->Parent;

    Status = AscendingCallback (WalkState, Op);

    /* Look for a sibling to the current op */

    if (Next)
    {
        /* There is a sibling, it will be next */

        *PrevOp = Op;
        *NextOp = Next;
        return_ACPI_STATUS (Status);
    }


    /* Abort on error from callback routine */

    if (Status != AE_OK)
    {
        /* Next op will be the parent */

        *PrevOp = Op;
        *NextOp = Parent;
        return_ACPI_STATUS (Status);
    }


    /*
     * Look for a sibling of the current Op's parent
     * Continue moving up the tree until we find a node that has not been 
     * visited, or we get back to where we started.
     */
    while (Parent)
    {
        /* We are moving up the tree, therefore this parent Op is complete */

        GrandParent = Parent->Parent;
        Next        = Parent->Next;

        Status = AscendingCallback (WalkState, Parent);

        /* All evaluated predicates come through here */

        if (Status == AE_FALSE)
        {
            /*
             * Predicate was false, so instead of moving on to the
             * body (TermList), we close out the IF/WHILE
             */

            Parent      = GrandParent;
            Next        = GrandParent->Next;
            GrandParent = GrandParent->Parent;

            Status = AscendingCallback (WalkState, Parent);

            /* Now continue to the next node in the tree */
        }

        else if (Status == AE_TRUE)
        {
            /* 
             * Predicate of a WHILE was true and the loop just completed an execution.
             * Go back to the start of the loop and reevaluate the predicate.
             */

            Op = WalkState->ControlState->PredicateOp;    /* Points to the predicate */

            *PrevOp = Op->Parent;
            *NextOp = Op;               /* Evaluate the predicate again (next) */
            return_ACPI_STATUS (AE_OK);
        }

        else if (Status == AE_TERMINATE)
        {
            /* 
             * A control method was terminated via a RETURN statement.
             * The walk of this method is complete.
             */
            *PrevOp = WalkState->Origin;
            *NextOp = NULL;
            return_ACPI_STATUS (AE_OK);
        }

        /*
         * If we are back to the starting point, the walk is complete.
         */
        if (Parent == WalkState->Origin)
        {
            /* reached point of origin, end search */

            *PrevOp = Parent;
            *NextOp = NULL;
            return_ACPI_STATUS (Status);
        }


        /*
         * If there is a sibling to this parent (it is not the starting point Op),
         * then we will visit it.
         */
        if (Next)
        {
            /* found sibling of parent */

            *PrevOp = Parent;
            *NextOp = Next;
            return_ACPI_STATUS (Status);
        }

        /*
         * No sibling, check for an error from closing the parent 
         */
        if (Status != AE_OK)
        {
            *PrevOp = Parent;
            *NextOp = GrandParent;
            return_ACPI_STATUS (Status);
        }

        /* No siblings, no errors, just move up one more level in the tree */

        Op = Parent;
        Parent = GrandParent;
        *PrevOp = Op;
    }


    /* Got all the way to the top of the tree, we must be done! */
    /* However, the code should have terminated in the loop above */

    *NextOp = NULL;
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    PsWalkLoop
 *
 * PARAMETERS:  WalkList            - State of the walk
 *              StartOp             - Starting Op of the subtree to be walked
 *              DescendingCallback  - Procedure called when a new Op is encountered
 *              AscendingCallback   - Procedure called when Op is complete
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perform a walk of the parsed AML tree.  Begins and terminates at
 *              the StartOp.  
 *
 ******************************************************************************/

ACPI_STATUS
PsWalkLoop (
    ACPI_WALK_LIST          *WalkList,
    ACPI_GENERIC_OP         *StartOp,
    INTERPRETER_CALLBACK    DescendingCallback,
    INTERPRETER_CALLBACK    AscendingCallback)
{
    ACPI_WALK_STATE         *WalkState;
    ACPI_WALK_STATE         *PreviousWalkState;
    ACPI_GENERIC_OP         *Op = StartOp;
    ACPI_GENERIC_OP         *NextOp;
    ACPI_GENERIC_OP         *PrevOp;
    ACPI_STATUS             Status;
    ACPI_DEFERRED_OP        *Method;
    NAME_TABLE_ENTRY        *MethodNte;


    FUNCTION_TRACE_PTR ("PsWalkLoop", StartOp);


    WalkState = PsGetCurrentWalkState (WalkList);


    /* Walk entire subtree, visiting all nodes depth-first */

    while (Op)
    {
        Status = DescendingCallback (WalkState, Op);

        /* 
         * A TRUE exception means that an ELSE was detected, but the IF predicate evaluated TRUE.
         * Simply ignore the entire ELSE block by moving on the the next opcode.
         */
        if (Status == AE_TRUE)
        {
            Op = Op->Next;
            continue;
        }

        /* Get the next node (op) in the depth-first walk */

        Status = PsGetNextWalkOp (WalkState, Op, AscendingCallback, &PrevOp, &NextOp);

        /* A PENDING exception means that a control method invocation has been detected */

        if (Status == AE_PENDING)
        {

            DEBUG_PRINT (TRACE_PARSE, ("PsWalkLoop, execute method %p, currentstate=%p\n", PrevOp, WalkState));
            BREAKPOINT3;

            /* Move this code to the ParseAml procedure? */

            /*
             * PrevOp points to the METHOD_CALL Op.
             * Get the NTE entry (in the METHOD_CALL->NAME Op) and the corresponding METHOD Op
             */

            MethodNte = (PrevOp->Value.Arg)->ResultObj;
            Method = ((ACPI_OBJECT_INTERNAL *) MethodNte->Object)->Method.ParserOp;
            if (!Method)
            {
                DEBUG_PRINT (TRACE_PARSE, ("PsWalkLoop, parsing control method\n"));

                DEBUG_PRINT (ACPI_ERROR, ("PsWalkLoop, Method not parsed!!! \n"));

                /* Method has not been parsed! */
                /* TBD: Parse method */
            }

            /* Save the next Op for when this walk is restarted */

            WalkState->PrevOp = Op;
            WalkState->NextOp = NextOp;

            /* Create a new state for the preempting walk */

            PreviousWalkState = WalkState;
            WalkState = PsCreateWalkState ((ACPI_GENERIC_OP *) Method, WalkList);
            if (!WalkState)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            /* 
             * Initialize the arguments for the method.  The resolved arguments were put 
             * on the previous walk state's operand stack
             */

            Status = PsxMthStackInitArgs (&PreviousWalkState->Operands[0], PreviousWalkState->NumOperands);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }

            /* Delete the operands on the previous walkstate operand stack (they were copied to new objects) */

            PsxObjStackDeleteAll (PreviousWalkState);

            /* The next op will be the beginning of the method */

            NextOp = (ACPI_GENERIC_OP *) Method;

            DEBUG_PRINT (TRACE_PARSE, ("PsWalkLoop, starting nested execution, newstate=%p\n", WalkState));
            BREAKPOINT3;
        }

        /* Abort the walk on any exception */

        else if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        Op = NextOp;
    }

    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    PsWalkParsedAml
 *
 * PARAMETERS:  StartOp             - Starting Op of the subtree to be walked
 *              EndOp               - Where to terminate the walk
 *              DescendingCallback  - Procedure called when a new Op is encountered
 *              AscendingCallback   - Procedure called when Op is complete
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Top level interface to walk the parsed AML tree.  Handles
 *              preemption of executing control methods.
 *
 *              NOTE: The EndOp is usually only different from the StartOp if 
 *              we don't want to visit the StartOp during the tree descent.
 *
 ******************************************************************************/

ACPI_STATUS
PsWalkParsedAml (
    ACPI_GENERIC_OP         *StartOp,
    ACPI_GENERIC_OP         *EndOp,
    ACPI_OBJECT_INTERNAL    **Params,
    ACPI_OBJECT_INTERNAL    **CallerReturnDesc,
    INTERPRETER_CALLBACK    DescendingCallback,
    INTERPRETER_CALLBACK    AscendingCallback)
{
    ACPI_GENERIC_OP         *Op;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_INTERNAL    *ReturnDesc;
    ACPI_STATUS             Status;
    ACPI_WALK_LIST          WalkList;
    ACPI_WALK_LIST          *PrevWalkList;


    FUNCTION_TRACE_PTR ("PsWalkParsedAml", StartOp);


    /* Parameter Validation */

    if (!StartOp || !EndOp)
    {
        return AE_BAD_PARAMETER;
    }

    /* Initialize a new walk list */

    WalkList.WalkState = NULL;

    WalkState = PsCreateWalkState (EndOp, &WalkList);
    if (!WalkState)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* TBD:
     * TEMP until we pass WalkState to the interpreter
     */
    PrevWalkList = Gbl_CurrentWalkList;
    Gbl_CurrentWalkList = &WalkList;

    /* Init arguments if this is a control method */

    PsxMthStackInitArgs (Params, MTH_NUM_ARGS);

    Op = StartOp;
    Status = AE_OK;
    
    /*
     * Execute the walk loop as long as there is a valid Walk State.  This handles nested
     * control method invocations without recursion.
     */

    DEBUG_PRINT (TRACE_PARSE, ("PsWalkParsedAml: Entering walk loop at Op=%X State=%X\n", Op, WalkState));
    BREAKPOINT3;

    while (WalkState)
    {
        if (Status == AE_OK)
        {
            Status = PsWalkLoop (&WalkList, Op, DescendingCallback, AscendingCallback);
        }

        DEBUG_PRINT (TRACE_PARSE, ("PsWalkParsedAml: Completed one call to walk loop, State=%X\n", WalkState));

        /* We are done with this walk, move on to the parent if any */

        WalkState = PsPopWalkState (&WalkList);
        ReturnDesc = WalkState->Operands[0];    /* Extract return value before we delete WalkState */
        PsxMthStackDeleteArgs (WalkState);      /* Delete all arguments and locals (if a method completed) */

        CmFree (WalkState);

        /* Check if we have restarted a preempted walk */

        WalkState = PsGetCurrentWalkState (&WalkList);
        if (WalkState &&
            Status == AE_OK)
        {
            DEBUG_PRINT (TRACE_PARSE, ("PsWalkParsedAml: Restarting a method, state=%p\n", WalkState));

            /* Get the return value (if any) from the previous method.  NULL if no return value */

            /* TBD: Check if parent will actually use the value, delete if not */
            if (ReturnDesc)
            {
                BREAKPOINT3;

                /* Find the METHOD_CALL Op. It is either the previous op or its parent */

                Op = WalkState->PrevOp;
                while (Op->Opcode != AML_METHODCALL)
                {
                    Op = Op->Parent;
                }

                /* Store the return value in the METHOD_CALL op for use by the invoking method */

                Op->ResultObj = ReturnDesc;
            }


            /*
             * Currently, the only way a method can be preempted is by the nested execution
             * of another method.  Therefore, we can safely pop the scope stack here
             * because we know that a nested control method just finished.
             */
            /* Pop scope stack */
            
            NsScopeStackPop (ACPI_TYPE_Any);

            /* Continue the previous method at the next Op in the walk */

            Op = WalkState->NextOp;
        }

        /* Just completed a 1st-level method, save the final internal return value (if any) */

        else if (CallerReturnDesc)
        {
            if (ReturnDesc)
                *CallerReturnDesc = ReturnDesc;
            else
                *CallerReturnDesc = NULL;
        }
    }


    Gbl_CurrentWalkList = PrevWalkList;

    return_ACPI_STATUS (Status);
}


