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
 * templates in Acpi_GblAmlOpInfo[]
 */

#include "acpi.h"
#include "parser.h"
#include "dispatch.h"
#include "amlcode.h"
#include "namesp.h"
#include "debugger.h"

#define _COMPONENT          PARSER
        MODULE_NAME         ("psparse");


UINT32                      Acpi_GblDepth = 0;
extern UINT32               Acpi_GblScopeDepth;



/*******************************************************************************
 *
 * FUNCTION:    AcpiPsDeleteCompletedOp
 *
 * PARAMETERS:  State           - Walk state
 *              Op              - Completed op
 *
 * RETURN:      AE_OK
 *
 * DESCRIPTION: Callback function for AcpiPsGetNextWalkOp().  Used during
 *              AcpiPsDeleteParse tree to delete Op objects when all sub-objects
 *              have been visited (and deleted.)
 *
 ******************************************************************************/

ACPI_STATUS 
AcpiPsDeleteCompletedOp (
    ACPI_WALK_STATE         *State,
    ACPI_GENERIC_OP         *Op)
{

    AcpiPsFreeOp (Op);
    return AE_OK;
}


#ifndef PARSER_ONLY
/*******************************************************************************
 *
 * FUNCTION:    AcpiPsDeleteParseTree
 *
 * PARAMETERS:  Root            - Root of tree (or subtree) to delete
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete a portion of or an entire parse tree.
 *
 ******************************************************************************/

void
AcpiPsDeleteParseTree (
    ACPI_GENERIC_OP         *Root)
{
    ACPI_GENERIC_OP         *Op;
    ACPI_WALK_STATE         WalkState;



    WalkState.Origin = Root;
    Op = Root;

    /* TBD: [Restructure] hack for root case */

    if (Op == Acpi_GblParsedNamespaceRoot)
    {
        Op = AcpiPsGetChild (Op);
    }

    /* Save the root until last, so that we know when the tree has been walked */

    WalkState.NextOp = Op;
    WalkState.NextOpInfo = NEXT_OP_DOWNWARD;

    while (WalkState.NextOp)
    {
        AcpiPsGetNextWalkOp (&WalkState, WalkState.NextOp, AcpiPsDeleteCompletedOp);
    }
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    AcpiPsPeekOpcode
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get next AML opcode (without incrementing AML pointer)
 *
 ******************************************************************************/

UINT32
AcpiPsGetOpcodeSize (
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
 * FUNCTION:    AcpiPsPeekOpcode
 *
 * PARAMETERS:  ParserState         - A parser state object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get next AML opcode (without incrementing AML pointer)
 *
 ******************************************************************************/

UINT16
AcpiPsPeekOpcode (
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
     *          && (GET8 (AcpiAml) == AML_LEQUAL
     *               || GET8 (AcpiAml) == AML_LGREATER
     *               || GET8 (AcpiAml) == AML_LLESS)))      extended Opcode, !=, <=, or >= 
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
 * FUNCTION:    AcpiPsCreateState  
 *
 * PARAMETERS:  AcpiAml             - AcpiAml code pointer
 *              AcpiAmlSize         - Length of AML code
 *
 * RETURN:      A new parser state object
 *
 * DESCRIPTION: Create and initialize a new parser state object
 *
 ******************************************************************************/

ACPI_PARSE_STATE *
AcpiPsCreateState (
    UINT8                   *Aml, 
    INT32                   AmlSize)
{
    ACPI_PARSE_STATE        *ParserState; 


    FUNCTION_TRACE ("PsInitState");


    ParserState = AcpiCmCallocate (sizeof (ACPI_PARSE_STATE));
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
 * FUNCTION:    AcpiPsFindObject
 *
 * PARAMETERS:  Opcode          - Current opcode
 *              ParserState     - Current state
 *              WalkState       - Current state
 *              *Op             - Where found/new op is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Find a named object.  Two versions - one to search the parse
 *              tree (for parser-only applications such as acpidump), another
 *              to search the ACPI internal namespace (the parse tree may no
 *              longer exist)
 *
 ******************************************************************************/

#ifdef PARSER_ONLY

ACPI_STATUS
AcpiPsFindObject (
    UINT16                  Opcode,
    ACPI_PARSE_STATE        *ParserState,
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         **Op)
{
    char                    *Path;



    /* Find the name in the parse tree */

    Path = AcpiPsGetNextNamestring (ParserState);

    *Op = AcpiPsFind (AcpiPsGetParentScope (ParserState),
                 Path, Opcode, 1);

    if (!(*Op))
    {
        return AE_NOT_FOUND;
    }

    return AE_OK;
}
#else

ACPI_STATUS
AcpiPsFindObject (
    UINT16                  Opcode,
    ACPI_PARSE_STATE        *ParserState,
    ACPI_WALK_STATE         *WalkState,
    ACPI_GENERIC_OP         **OutOp)
{
    char                    *Path;
    ACPI_GENERIC_OP         *Op;
    OBJECT_TYPE_INTERNAL    DataType; 
    ACPI_STATUS             Status;
    NAME_TABLE_ENTRY        *Nte = NULL;


    FUNCTION_TRACE ("PsFindInNamespace");

    
    /*
     * The full parse tree has already been deleted -- therefore, we are parsing
     * a control method.  We can lookup the name in the namespace instead of
     * the parse tree!
     */


    Path = AcpiPsGetNextNamestring (ParserState);

    /* Map the raw opcode into an internal object type */

    DataType = AcpiDsMapNamedOpcodeToDataType (Opcode);

    /* 
     * Enter the object into the namespace
     */

    Status = AcpiNsLookup (WalkState->ScopeInfo, Path, DataType, IMODE_LOAD_PASS1,   /* Create if not found */
                            NS_NO_UPSEARCH, WalkState, &Nte);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Create a new op */

    Op = AcpiPsAllocOp (Opcode);
    if (!Op)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Initialize */

    ((ACPI_NAMED_OP *)Op)->Name = Nte->Name;
    Op->NameTableEntry = Nte;


    AcpiPsAppendArg (AcpiPsGetParentScope (ParserState), Op);

    *OutOp = Op;


    return_ACPI_STATUS (AE_OK);
}
#endif





/*******************************************************************************
 *
 * FUNCTION:    AcpiPsParseLoop 
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
AcpiPsParseLoop (
    ACPI_PARSE_STATE        *ParserState,
    ACPI_WALK_STATE         *WalkState,
    UINT32                  ParseFlags)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_GENERIC_OP         *Op = NULL;            /* current op */
    ACPI_OP_INFO            *OpInfo;
    ACPI_GENERIC_OP         *Arg = NULL;
    ACPI_DEFERRED_OP        *DeferredOp;
    UINT32                  ArgCount;       /* push for fixed or variable arguments */
    UINT32                  ArgTypes = 0;
    ACPI_PTRDIFF            AmlOffset;
    UINT16                  Opcode;
    ACPI_GENERIC_OP         PreOp;
 


#ifndef PARSER_ONLY
    OBJECT_TYPE_INTERNAL    DataType; 
#endif

    FUNCTION_TRACE_PTR ("PsParseLoop", ParserState);



    /*
     * Iterative parsing loop, while there is more aml to process:
     */
    while (ParserState->Aml < ParserState->AmlEnd)
    {
        if (!Op)
        {
            /* Get the next opcode from the AML stream */

            AmlOffset   = ParserState->Aml - ParserState->AmlStart;
            Opcode      = AcpiPsPeekOpcode (ParserState);
            OpInfo      = AcpiPsGetOpcodeInfo (Opcode);

            /*
             * First cut to determine what we have found:
             * 1) A valid AML opcode
             * 2) A name string
             * 3) An unknown/invalid opcode
             */

            if (OpInfo)
            {
                /* Found opcode info, this is a normal opcode */

                ParserState->Aml += AcpiPsGetOpcodeSize (Opcode);
                ArgTypes = OpInfo->ParseArgs;
            }

            else if (AcpiPsIsPrefixChar (Opcode) || AcpiPsIsLeadingChar (Opcode))
            {
                /* 
                 * Starts with a valid prefix or ASCII char, this is a name string.
                 * Convert the bare name string to a namepath. 
                 */

                Opcode = AML_NAMEPATH_OP;
                ArgTypes = ARGP_NAMESTRING;
            }

            else
            {
                /* The opcode is unrecognized.  We simply skip unknown opcodes */

                DEBUG_PRINT (TRACE_PARSE, ("ParseLoop: Found unknown opcode %lX, skipping\n", Opcode));

                ParserState->Aml += AcpiPsGetOpcodeSize (Opcode);
                continue;
            }
        

            /* Create Op structure and append to parent's argument list */

            if (AcpiPsIsNamedOp (Opcode))
            {
                PreOp.Value.Arg = NULL;
                PreOp.Opcode = Opcode;

                while (GET_CURRENT_ARG_TYPE (ArgTypes) != ARGP_NAME)
                {
                    Arg = AcpiPsGetNextArg (ParserState, GET_CURRENT_ARG_TYPE (ArgTypes), &ArgCount);
                    AcpiPsAppendArg (&PreOp, Arg);
                    INCREMENT_ARG_LIST (ArgTypes);
                }

      
                /* We know that this arg is a name, move to next arg */

                INCREMENT_ARG_LIST (ArgTypes);

                Status = AcpiPsFindObject (Opcode, ParserState, WalkState, &Op);
                if (ACPI_FAILURE (Status))
                {
                    return_ACPI_STATUS (AE_NOT_FOUND);
                }

                AcpiPsAppendArg (Op, PreOp.Value.Arg);
                Acpi_GblDepth++;


                if (Op->Opcode == AML_REGION_OP)
                {
                    DeferredOp = AcpiPsToDeferredOp (Op);
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

                Op = AcpiPsAllocOp (Opcode);
                if (!Op)
                {
                    return_ACPI_STATUS (AE_NO_MEMORY);
                }

                AcpiPsAppendArg (AcpiPsGetParentScope (ParserState), Op);
            }
        
            Op->AmlOffset = AmlOffset;

            if (OpInfo)
            {
                DEBUG_PRINT (TRACE_PARSE, ("ParseLoop:  Op=%p Opcode=%4.4lX Offset=%5.5lX\n",
                                Op, Op->Opcode, Op->AmlOffset));
            }
        }


        ArgCount = 0;
        if (ArgTypes)   /* Are there any arguments that must be processed? */
        {
            /* get arguments */

            switch (Op->Opcode)
            {
            case AML_BYTE_OP:       /* AML_BYTEDATA_ARG */
            case AML_WORD_OP:       /* AML_WORDDATA_ARG */
            case AML_DWORD_OP:      /* AML_DWORDATA_ARG */
            case AML_STRING_OP:     /* AML_ASCIICHARLIST_ARG */

                /* fill in constant or string argument directly */

                AcpiPsGetNextSimpleArg (ParserState, GET_CURRENT_ARG_TYPE (ArgTypes), Op);
                break;

            case AML_NAMEPATH_OP:   /* AML_NAMESTRING_ARG */

                AcpiPsGetNextNamepath (ParserState, Op, &ArgCount, 1);
                ArgTypes = 0;
                break;


            default:

                /* Op is not a constant or string, append each argument */

                while (GET_CURRENT_ARG_TYPE (ArgTypes) && !ArgCount)
                {
                    AmlOffset = ParserState->Aml - ParserState->AmlStart;
                    Arg = AcpiPsGetNextArg (ParserState, GET_CURRENT_ARG_TYPE (ArgTypes), &ArgCount);
                
                    if (Arg)
                    {
                        Arg->AmlOffset = AmlOffset;
                    }

                    AcpiPsAppendArg (Op, Arg);
                    INCREMENT_ARG_LIST (ArgTypes);
                }


                /* For a method, save the length and address of the body */

                if (Op->Opcode == AML_METHOD_OP)
                {
                    DeferredOp = AcpiPsToDeferredOp (Op);
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

            if (AcpiPsIsNamedOp (Op->Opcode))
            {
                if (Acpi_GblDepth)
                {
                    Acpi_GblDepth--;
                }

                if (Op->Opcode == AML_REGION_OP)
                {
                    DeferredOp = AcpiPsToDeferredOp (Op);
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
            
            
#ifndef PARSER_ONLY
                DataType = AcpiDsMapNamedOpcodeToDataType (Op->Opcode);

                if (Op->Opcode == AML_NAME_OP)
                {
                    if (Op->Value.Arg)
                    {
            
                        DataType = AcpiDsMapOpcodeToDataType ((Op->Value.Arg)->Opcode, NULL);
                        ((NAME_TABLE_ENTRY *)Op->NameTableEntry)->Type = (UINT8) DataType;
                    }
                }

                /* Pop the scope stack */

                if (AcpiNsOpensScope (DataType))
                {

                    DEBUG_PRINT (TRACE_DISPATCH, ("AmlEndNamespaceScope: Popping scope for Op %p type [%s]\n",
                                                    Op, AcpiCmGetTypeName (DataType)));
                    AcpiDsScopeStackPop (WalkState);
                }
#endif                
            }


            ParserState->Scope->ArgCount--;


            /* Delete op if asked to */

#ifndef PARSER_ONLY
            if (ParseFlags & PARSE_DELETE_TREE)
            {
                AcpiPsDeleteParseTree (Op);
            }
#endif                
            
                
            if (AcpiPsHasCompletedScope (ParserState))
            {
                AcpiPsPopScope (ParserState, &Op, &ArgTypes);
            }

            else
            {
                Op = NULL;
            }
        }

        else
        {
            /* complex argument, push Op and prepare for argument */

            AcpiPsPushScope (ParserState, Op, ArgTypes, ArgCount);
            Op = NULL;
        }

    } /* while ParserState->Aml */
    

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiPsParseAml
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
AcpiPsParseAml (
    ACPI_GENERIC_OP         *StartScope,
    UINT8                   *Aml, 
    UINT32                  AmlSize,
    UINT32                  ParseFlags)
{
    ACPI_STATUS             Status;
    ACPI_PARSE_STATE        *ParserState;
    ACPI_WALK_STATE         *WalkState;
    ACPI_WALK_LIST          WalkList;
    NAME_TABLE_ENTRY        *Nte = NULL;


    FUNCTION_TRACE ("PsParseAml");

    DEBUG_PRINT (TRACE_PARSE, ("PsParseAml: Entered with Scope=%p Aml=%p size=%lX\n", StartScope, Aml, AmlSize));


    /* Initialize parser state and scope */

    ParserState = AcpiPsCreateState (Aml, AmlSize);
    if (!ParserState)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    AcpiPsInitScope (ParserState, StartScope);


    /* Initialize a new walk list */

    WalkList.WalkState = NULL;

    WalkState = AcpiDsCreateWalkState (TABLE_ID_DSDT, NULL, NULL, &WalkList);
    if (!WalkState)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }


    /* Setup the current scope */

    Nte = ParserState->StartOp->NameTableEntry;
    if (Nte)
    {
        /* Push start scope on scope stack and make it current  */

        Status = AcpiDsScopeStackPush (Nte->Scope, Nte->Type, WalkState);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }

    }


    /* Create the parse tree */

    Status = AcpiPsParseLoop (ParserState, WalkState, ParseFlags);


Cleanup:

    /* Cleanup */

    AcpiDsDeleteWalkState (WalkState);
    AcpiPsCleanupScope (ParserState);
    AcpiCmFree (ParserState);


    return_ACPI_STATUS (Status);
}


