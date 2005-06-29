/******************************************************************************
 * 
 * Module Name: psparse - Parser top level AML parse routines
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


/*
 * Parse the AML and build an operation tree as most interpreters,
 * like Perl, do.  Parsing is done by hand rather than with a YACC
 * generated parser to tightly constrain stack and dynamic memory
 * usage.  At the same time, parsing is kept flexible and the code
 * fairly compact by parsing based on a list of AML opcode
 * templates in Gbl_AmlOpInfo[]
 */

#include <acpi.h>
#include <parser.h>
#include <dispatch.h>
#include <amlcode.h>
#include <namesp.h>
#include <debugger.h>

#define _COMPONENT          PARSER
        MODULE_NAME         ("psparse");


UINT32                      Gbl_Depth = 0;
extern UINT32               Gbl_ScopeDepth;



/*******************************************************************************
 *
 * FUNCTION:    PsDeleteCompletedOp
 *
 * PARAMETERS:  State           - Walk state
 *              Op              - Completed op
 *
 * RETURN:      AE_OK
 *
 * DESCRIPTION: Callback function for PsGetNextWalkOp().  Used during
 *              PsDeleteParse tree to delete Op objects when all sub-objects
 *              have been visited (and deleted.)
 *
 ******************************************************************************/

ACPI_STATUS 
PsDeleteCompletedOp (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op)
{

    CmFree (Op);
    return AE_OK;
}


#ifndef PARSER_ONLY
/*******************************************************************************
 *
 * FUNCTION:    PsDeleteParseTree
 *
 * PARAMETERS:  Root            - Root of tree (or subtree) to delete
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete a portion of or an entire parse tree.
 *
 ******************************************************************************/

void
PsDeleteParseTree (
    ACPI_GENERIC_OP         *Root)
{
    ACPI_GENERIC_OP         *Op;
    ACPI_WALK_STATE         WalkState;



    WalkState.Origin = Root;
    Op = Root;

    /* TBD: hack for root case */

    if (Op == Gbl_ParsedNamespaceRoot)
    {
        DEBUG_EXEC (DbGenerateStatistics ());
        Op = PsGetChild (Op);
    }

    /* Save the root until last, so that we know when the tree has been walked */

    WalkState.NextOp = Op;
    WalkState.NextOpInfo = NEXT_OP_DOWNWARD;

    while (WalkState.NextOp)
    {
        PsGetNextWalkOp (&WalkState, WalkState.NextOp, PsDeleteCompletedOp);
    }
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    PsPeekOpcode
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get next AML opcode (without incrementing AML pointer)
 *
 ******************************************************************************/

UINT32
PsGetOpcodeSize (
    UINT32                  Opcode)
{
    
    /* Extended (2-byte) opcode if > 255 */

    if (Opcode > 0x00FF)
    {
        return 2;
    }

    /* Otherwise, just a single byte opcode */

    return 1;
}


/*******************************************************************************
 *
 * FUNCTION:    PsPeekOpcode
 *
 * PARAMETERS:  ParserState         - A parser state object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get next AML opcode (without incrementing AML pointer)
 *
 ******************************************************************************/

UINT16
PsPeekOpcode (
    ACPI_PARSE_STATE        *ParserState)
{
    UINT8                   *Aml;
    UINT16                  Opcode;


    Aml = ParserState->Aml;
    Opcode = (UINT16) GET8 (Aml);

    Aml++;


    /* 
     * Original code special cased LNOTEQUAL, LLESSEQUAL, LGREATEREQUAL.  These opcodes are 
     * no longer recognized. Instead, they are broken into two opcodes.
     *
     *
     *    if (Opcode == AML_EXTOP
     *       || (Opcode == AML_LNOT
     *          && (GET8 (Aml) == AML_LEQUAL
     *               || GET8 (Aml) == AML_LGREATER
     *               || GET8 (Aml) == AML_LLESS)))      extended Opcode, !=, <=, or >= 
     */

    if (Opcode == AML_EXTOP)
    {
        /* Extended opcode */

        Opcode = (UINT16) ((Opcode << 8) | GET8 (Aml));
        Aml++;
    }

    /* don't convert bare name to a namepath */

    return Opcode;
}


/*******************************************************************************
 *
 * FUNCTION:    PsCreateState  
 *
 * PARAMETERS:  Aml             - Aml code pointer
 *              AmlSize         - Length of AML code
 *
 * RETURN:      A new parser state object
 *
 * DESCRIPTION: Create and initialize a new parser state object
 *
 ******************************************************************************/

ACPI_PARSE_STATE *
PsCreateState (
    UINT8                   *Aml, 
    INT32                   AmlSize)
{
    ACPI_PARSE_STATE        *ParserState; 


    FUNCTION_TRACE ("PsInitState");


    ParserState = CmCallocate (sizeof (ACPI_PARSE_STATE));
    if (!ParserState)
    {
        return_VALUE (NULL);
    }

    ParserState->Aml       = Aml;
    ParserState->AmlEnd    = Aml + AmlSize;
    ParserState->PkgEnd    = ParserState->AmlEnd;
    ParserState->AmlStart  = Aml;


    return_PTR (ParserState);
}


/*******************************************************************************
 *
 * FUNCTION:    PsParseLoop 
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Parse AML (pointed to by the current parser state) and return 
 *              a tree of ops.
 *
 ******************************************************************************/

ACPI_STATUS
PsParseLoop (
    ACPI_PARSE_STATE        *ParserState)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_GENERIC_OP         *Op;            /* current op */
    char                    *Args = NULL;   /* current op next argument */
    ACPI_OP_INFO            *Opc;
    ACPI_GENERIC_OP         *Arg = NULL;
    ACPI_DEFERRED_OP        *DeferredOp;
    UINT32                  ArgCount;       /* push for fixed or variable arguments */
    ACPI_PTRDIFF            AmlOffset;
    UINT16                  Opcode;
 

    FUNCTION_TRACE_PTR ("PsParseLoop", ParserState);


    /*
     * Handle the case where we are restarting a control method that has
     * just completed a scope
     *
     * TBD: Obsolete now that we don't execute and parse at the same time?
     */

    if (PsHasCompletedScope (ParserState))
    {
        PsPopScope (ParserState, &Op, &Args);
    }

    else
    {
        Op = NULL;
    }



    /*
     * Iterative parsing loop, while there is more aml to process:
     */
    while (ParserState->Aml < ParserState->AmlEnd)
    {
        if (!Op)
        {
            /* Get the next opcode from the AML stream */

            AmlOffset   = ParserState->Aml - ParserState->AmlStart;
            Opcode      = PsPeekOpcode (ParserState);
            Opc         = PsGetOpcodeInfo (Opcode);

            /*
             * First cut to determine what we have found:
             * 1) A valid AML opcode
             * 2) A name string
             * 3) An unknown/invalid opcode
             */

            if (Opc)
            {
                /* Found opcode info, this is a normal opcode */

                ParserState->Aml += PsGetOpcodeSize (Opcode);
                Args = Opc->Args;
            }

            else if (PsIsPrefixChar (Opcode) || PsIsLeadingChar (Opcode))
            {
                /* 
                 * Starts with a valid prefix or ASCII char, this is a name string.
                 * Convert the bare name string to a namepath. 
                 */

                Opcode = AML_NAMEPATH;
                Args = "n";
            }

            else
            {
                /* The opcode is unrecognized.  We simply skip unknown opcodes */

                DEBUG_PRINT (TRACE_PARSE, ("ParseLoop: Found unknown opcode %lX, skipping\n", Opcode));

                ParserState->Aml += PsGetOpcodeSize (Opcode);
                continue;
            }
        

            /* Create Op structure and append to parent's argument list */

            if (PsIsNamedOp (Opcode))
            {
                if (*Args == AML_PKGLENGTH_ARG)
                {
                    /* get package length (nothing is returned) */

                    PsGetNextArg (ParserState, *Args, &ArgCount);
                    Args++;
                }

      
                if (Opcode == AML_AliasOp)
                {
                    Arg = PsGetNextArg (ParserState, *Args, &ArgCount);
                
                    if (Arg)
                    {
                        Arg->AmlOffset = AmlOffset;
                    }

                    AmlOffset   = ParserState->Aml - ParserState->AmlStart;
                    Args = NULL;
                }

                else
                    Args++;


                /* Find the name in the parse tree */
                /* TBD: what if a control method references outside its scope? */
                /* ie - should we be using nslookup here? */

                Op = PsFind (PsGetParentScope (ParserState),
                             PsGetNextNamestring (ParserState), Opcode, 1);

                if (!Op)
                {
                    return_ACPI_STATUS (AE_NOT_FOUND);
                }

                Gbl_Depth++;

                if (Opcode == AML_AliasOp)
                {
                    PsAppendArg (Op, Arg);
                }


                if (Op->Opcode == AML_RegionOp)
                {
                    DeferredOp = PsToDeferredOp (Op);
                    if (DeferredOp)
                    {
                        /* 
                         * Skip parsing of control method or opregion body, because we don't
                         * have enough info in the first pass to parse them correctly.
                         *
                         * Backup to beginning of OpRegion declaration (2 for Opcode, 4 for name)
                         */

                        DeferredOp->Body        = ParserState->Aml - 6;
                        DeferredOp->BodyLength  = 0; /* Unknown until we parse the body */
                    }
                }
            }

            else
            {
                /* Not a named opcode, just allocate Op and append to parent */

                Op = PsAllocOp (Opcode);
                if (!Op)
                {
                    return_ACPI_STATUS (AE_NO_MEMORY);
                }

                PsAppendArg (PsGetParentScope (ParserState), Op);
            }
        
            Op->AmlOffset = AmlOffset;

            if (Opc)
            {
                DEBUG_PRINT (TRACE_PARSE, ("ParseLoop:  Op=%p (%s) Opcode=%4.4lX Offset=%5.5lX\n",
                                Op, Opc->Name, Op->Opcode, Op->AmlOffset));
            }
        }


        ArgCount = 0;
        if (Args)
        {
            /* get arguments */

            switch (Op->Opcode)
            {
            case AML_ByteOp:        /* AML_BYTEDATA_ARG */
            case AML_WordOp:        /* AML_WORDDATA_ARG */
            case AML_DWordOp:       /* AML_DWORDATA_ARG */
            case AML_StringOp:      /* AML_ASCIICHARLIST_ARG */

                /* fill in constant or string argument directly */

                PsGetNextSimpleArg (ParserState, *Args, Op);
                break;

            case AML_NAMEPATH:      /* AML_NAMESTRING_ARG */

                PsGetNextNamepath (ParserState, Op, &ArgCount, 1);
                Args = NULL;
                break;


            default:

                /* Op is not a constant or string, append each argument */

                while (*Args && !ArgCount)
                {
                    AmlOffset = ParserState->Aml - ParserState->AmlStart;
                    Arg = PsGetNextArg (ParserState, *Args, &ArgCount);
                
                    if (Arg)
                    {
                        Arg->AmlOffset = AmlOffset;
                    }

                    PsAppendArg (Op, Arg);
                    Args++;
                }


                /* For a method, save the length and address of the body */

                if (Op->Opcode == AML_MethodOp)
                {
                    DeferredOp = PsToDeferredOp (Op);
                    if (DeferredOp)
                    {
                        /* 
                         * Skip parsing of control method or opregion body, because we don't
                         * have enough info in the first pass to parse them correctly.
                         */

                        DeferredOp->Body        = ParserState->Aml;
                        DeferredOp->BodyLength  = ParserState->PkgEnd - ParserState->Aml;

                        /*
                         * Skip body of method.  For OpRegions, we must continue parsing because the
                         * opregion is not a standalone package (We don't know where the end is).
                         */
                        ParserState->Aml        = ParserState->PkgEnd;
                        ArgCount                = 0;
                    }
                }

                break;
            }
        }

        if (!ArgCount)
        {
            /* completed Op, prepare for next */

            if (PsIsNamedOp (Op->Opcode))
            {
                if (Gbl_Depth)
                {
                    Gbl_Depth--;
                }

                if (Op->Opcode == AML_RegionOp)
                {
                    DeferredOp = PsToDeferredOp (Op);
                    if (DeferredOp)
                    {
                        /* 
                         * Skip parsing of control method or opregion body, because we don't
                         * have enough info in the first pass to parse them correctly.
                         *
                         * Completed parsing an OpRegion declaration, we now know the length.
                         */

                        DeferredOp->BodyLength  = ParserState->Aml - DeferredOp->Body;
                    }
                }
             }

            ParserState->Scope->ArgCount--;

            if (PsHasCompletedScope (ParserState))
            {
                PsPopScope (ParserState, &Op, &Args);
            }

            else
            {
                Op = NULL;
            }
        }

        else
        {
            /* complex argument, push Op and prepare for argument */

            PsPushScope (ParserState, Op, Args, ArgCount);
            Op = NULL;
        }

    } /* while ParserState->Aml */
    
    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    PsParseAml
 *
 * PARAMETERS:  StartScope      - The starting point of the parse.  Becomes the
 *                                root of the parsed op tree.
 *              Aml             - Pointer to the raw AML code to parse
 *              AmlSize         - Length of the AML to parse
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Parse raw AML and return a tree of ops
 *
 ******************************************************************************/

ACPI_STATUS
PsParseAml (
    ACPI_GENERIC_OP         *StartScope,
    UINT8                   *Aml, 
    INT32                   AmlSize)
{
    ACPI_STATUS             Status;
    ACPI_PARSE_STATE        *ParserState;


    FUNCTION_TRACE ("PsParseAml");

    DEBUG_PRINT (TRACE_PARSE, ("PsParseAml: Entered with Scope=%p Aml=%p size=%lX\n", StartScope, Aml, AmlSize));


    /* Initialize parser state and scope */

    ParserState = PsCreateState (Aml, AmlSize);
    if (!ParserState)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    PsInitScope (ParserState, StartScope);


    /* Create the parse tree */

    Status = PsParseLoop (ParserState);


    /* Cleanup */

    PsCleanupScope (ParserState);
    CmFree (ParserState);


    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    PsParseTable
 *
 * PARAMETERS:  Aml                 - Pointer to the raw AML code to parse
 *              AmlSize             - Length of the AML to parse
 *              DescendingCallback  - Called as each opcode is encountered during
 *                                    descent of the parse tree
 *              AscendingCallback   - Called as each opcode is completed, during
 *                                    ascent of the parse tree
 *              RootObject          - TBD: REMOVE??
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Parse AML within an ACPI table and return a tree of ops
 *
 ******************************************************************************/

ACPI_STATUS
PsParseTable (
    UINT8                   *Aml, 
    INT32                   AmlSize,
    INTERPRETER_CALLBACK    DescendingCallback,
    INTERPRETER_CALLBACK    AscendingCallback,
    ACPI_GENERIC_OP         **RootObject)
{
    ACPI_STATUS             Status;



    FUNCTION_TRACE ("PsParseTable");


    /* Create the root object */

    Gbl_ParsedNamespaceRoot = PsAllocOp (AML_ScopeOp);
    if (!Gbl_ParsedNamespaceRoot)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Initialize the root object */

    ((ACPI_NAMED_OP *) Gbl_ParsedNamespaceRoot)->Name = * (UINT32 *) NS_ROOT;

    /* Pass 1:  Parse everything except control method bodies */

    Status = PsParseAml (Gbl_ParsedNamespaceRoot, Aml, AmlSize); 
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

#ifndef PARSER_ONLY

    DEBUG_PRINT (TRACE_PARSE, ("PsParseTable: Building Internal Namespace\n"));
BREAKPOINT3;

/* TBD: Temp only */

    PsWalkParsedAml (PsGetChild (Gbl_ParsedNamespaceRoot), Gbl_ParsedNamespaceRoot, NULL, NULL, NULL, NULL,
                        DsLoad1BeginOp, DsLoad1EndOp);


    PsWalkParsedAml (PsGetChild (Gbl_ParsedNamespaceRoot), Gbl_ParsedNamespaceRoot, NULL, NULL, NULL, NULL,
                        DescendingCallback, AscendingCallback);


    /*
     * Now that the internal namespace has been constructed, we can delete the
     * parsed namespace, since it is no longer needed
     */

    DEBUG_PRINT (TRACE_PARSE, ("PsParseTable: Deleting Parsed Namespace\n"));
BREAKPOINT3;


    PsDeleteParseTree (Gbl_ParsedNamespaceRoot);
    Gbl_ParsedNamespaceRoot = NULL;
#endif

    if (RootObject)
        *RootObject = Gbl_ParsedNamespaceRoot;

    return_ACPI_STATUS (AE_OK);
}


