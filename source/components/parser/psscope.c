/******************************************************************************
 * 
 * Module Name: psscope - Parser scope stack management routines
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
#include <parser.h>

#define _COMPONENT          PARSER
        MODULE_NAME         ("psscope");



/*******************************************************************************
 *
 * FUNCTION:    PsGetParentScope 
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *
 * RETURN:      Pointer to an Op object
 *
 * DESCRIPTION: Get parent of current op being parsed
 *
 ******************************************************************************/

ACPI_GENERIC_OP *
PsGetParentScope (
    ACPI_PARSE_STATE        *ParserState)
{
    return ParserState->Scope->Op;
}


/*******************************************************************************
 *
 * FUNCTION:    PsHasCompletedScope
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *
 * RETURN:      Boolean, TRUE = scope completed.
 *
 * DESCRIPTION: Is parsing of current argument complete?  Determined by
 *              1) AML pointer is at or beyond the end of the scope
 *              2) The scope argument count has reached zero.
 *
 ******************************************************************************/

BOOLEAN
PsHasCompletedScope (
    ACPI_PARSE_STATE        *ParserState)
{
    return (ParserState->Aml >= ParserState->Scope->ArgEnd ||
            !ParserState->Scope->ArgCount);
}


/*******************************************************************************
 *
 * FUNCTION:    PsInitScope
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *              Root                - the root object of this new scope
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Allocate and init a new scope object
 *
 ******************************************************************************/

ACPI_STATUS
PsInitScope (
    ACPI_PARSE_STATE        *ParserState,
    ACPI_GENERIC_OP         *Root)
{
    ACPI_PARSE_SCOPE        *Scope;
    
    
    Scope = CmCallocate (sizeof (ACPI_PARSE_SCOPE));
    if (!Scope)
    {
        return AE_NO_MEMORY;
    }

    Scope->Op           = Root;
    Scope->ArgCount     = ACPI_VAR_ARGS;
    Scope->ArgEnd       = ParserState->AmlEnd;
    Scope->PkgEnd       = ParserState->AmlEnd;
    ParserState->Scope  = Scope;

    return AE_OK;
}


/*******************************************************************************
 *
 * FUNCTION:    PsPushScope
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *              Op                  - Current op to be pushed
 *              NextArg             - Next op argument (to be pushed)
 *              ArgCount            - Fixed or variable number of args 
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Push current op to begin parsing its argument
 *
 ******************************************************************************/

ACPI_STATUS
PsPushScope (
    ACPI_PARSE_STATE        *ParserState,
    ACPI_GENERIC_OP         *Op, 
    char                    *NextArg,
    UINT32                  ArgCount)
{
    ACPI_PARSE_SCOPE        *Scope = ParserState->ScopeAvail;


    FUNCTION_TRACE ("PsPushScope");


    if (Scope)
    {
        /* grabbed scope from available list */

        ParserState->ScopeAvail = Scope->Parent;
    }

    else
    {
        /* allocate scope from the heap */

        Scope = (ACPI_PARSE_SCOPE*) CmAllocate (sizeof (ACPI_PARSE_SCOPE));
        if (!Scope)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }
    }

    /* Always zero out the scope before init */

    MEMSET (Scope, 0, sizeof (*Scope));

    Scope->Op           = Op;
    Scope->NextArg      = NextArg;
    Scope->ArgCount     = ArgCount;
    Scope->PkgEnd       = ParserState->PkgEnd;
    Scope->Parent       = ParserState->Scope;
    ParserState->Scope  = Scope;
    
    if (ArgCount == ACPI_VAR_ARGS)
    {
        /* multiple arguments */

        Scope->ArgEnd = ParserState->PkgEnd;
    }
    
    else
    {
        /* single argument */

        Scope->ArgEnd = ACPI_MAX_AML;
    }
 
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    PsPopScope
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *              Op                  - Where the popped op is returned
 *              NextArg             - Where the popped "next argument" is returned
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Return to parsing a previous op
 *
 ******************************************************************************/

void
PsPopScope (
    ACPI_PARSE_STATE        *ParserState,
    ACPI_GENERIC_OP         **Op,
    char                    **NextArg)
{
    ACPI_PARSE_SCOPE        *Scope = ParserState->Scope;


    FUNCTION_TRACE ("PsPopScope");


    if (Scope->Parent)
    {
        /* return to parsing previous op */
        
        *Op = Scope->Op;
        *NextArg = Scope->NextArg;
        ParserState->PkgEnd = Scope->PkgEnd;
        ParserState->Scope = Scope->Parent;

        /* add scope to available list */

        Scope->Parent = ParserState->ScopeAvail;
        ParserState->ScopeAvail = Scope;
    }

    else
    {
        /* empty parse stack, prepare to fetch next opcode */

        *Op = NULL;
        *NextArg = NULL;
    }

    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    PsCleanupScope
 *
 * PARAMETERS:  ParserState         - Current parser state object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Destroy available list, remaining stack levels, and return 
 *              root scope
 *
 ******************************************************************************/

void
PsCleanupScope (
    ACPI_PARSE_STATE        *ParserState)
{
    ACPI_PARSE_SCOPE        *Scope; 


    FUNCTION_TRACE_PTR ("PsCleanupScope", ParserState);


    /* destroy available list */

    while (ParserState->ScopeAvail)
    {
        Scope = ParserState->ScopeAvail;
        ParserState->ScopeAvail = Scope->Parent;
        CmFree (Scope);
    }

    /* destroy scope stack */

    while (ParserState->Scope)
    {
        Scope = ParserState->Scope;
        ParserState->Scope = Scope->Parent;
        CmFree (Scope);
    }

    return_VOID;
}

