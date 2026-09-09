/******************************************************************************
 *
 * Module Name: prexpress - Preprocessor #if expression support
 *
 *****************************************************************************/

/******************************************************************************
 *
 * Copyright (c) 1999 - 2026, Intel Corp.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 *
 *****************************************************************************/

#include "aslcompiler.h"

#define _COMPONENT          ASL_PREPROCESSOR
        ACPI_MODULE_NAME    ("prexpress")

#ifdef _UNDER_DEVELOPMENT
/******************************************************************************
 *
 * FUNCTION:    PrUnTokenize
 *
 * PARAMETERS:  Buffer              - Token Buffer
 *              Next                - "Next" buffer from GetNextToken
 *
 * RETURN:      None
 *
 * DESCRIPTION: Un-tokenized the current token buffer. The implementation is
 *              to simply set the null inserted by GetNextToken to a blank.
 *              If Next is NULL, there were no tokens found in the Buffer,
 *              so there is nothing to do.
 *
 *****************************************************************************/

static void
PrUnTokenize (
    char                    *Buffer,
    char                    *Next)
{
    UINT32                  Length = strlen (Buffer);


    if (!Next)
    {
        return;
    }

    if (Buffer[Length] != '\n')
    {
        Buffer[strlen(Buffer)] = ' ';
    }
}
#endif


/******************************************************************************
 *
 * FUNCTION:    PrIsDefined
 *
 * PARAMETERS:  Identifier          - Name to be resolved
 *
 * RETURN:      64-bit boolean integer value
 *
 * DESCRIPTION: Returns TRUE if the name is defined, FALSE otherwise (0).
 *
 *****************************************************************************/

UINT64
PrIsDefined (
    char                    *Identifier)
{
    UINT64                  Value;
    PR_DEFINE_INFO          *DefineInfo;


    DbgPrint (ASL_DEBUG_OUTPUT, PR_PREFIX_ID
        "**** Is defined?:  %s\n", AslGbl_CurrentLineNumber, Identifier);

    Value = 0; /* Default is "Not defined" -- FALSE */

    DefineInfo = PrMatchDefine (Identifier);
    if (DefineInfo)
    {
        Value = ACPI_UINT64_MAX; /* TRUE */
    }

    DbgPrint (ASL_DEBUG_OUTPUT, PR_PREFIX_ID
        "[#if defined %s] resolved to: %8.8X%8.8X\n",
        AslGbl_CurrentLineNumber, Identifier, ACPI_FORMAT_UINT64 (Value));

    return (Value);
}


/******************************************************************************
 *
 * FUNCTION:    PrResolveDefine
 *
 * PARAMETERS:  Identifier          - Name to be resolved
 *
 * RETURN:      A 64-bit boolean integer value
 *
 * DESCRIPTION: Returns TRUE if the name is defined, FALSE otherwise (0).
 *
 *****************************************************************************/

UINT64
PrResolveDefine (
    char                    *Identifier)
{
    UINT64                  Value;
    PR_DEFINE_INFO          *DefineInfo;


    DbgPrint (ASL_DEBUG_OUTPUT, PR_PREFIX_ID
        "**** Resolve #define:  %s\n", AslGbl_CurrentLineNumber, Identifier);

    Value = 0; /* Default is "Not defined" -- FALSE */

    DefineInfo = PrMatchDefine (Identifier);
    if (DefineInfo)
    {
        Value = ACPI_UINT64_MAX; /* TRUE */
    }

    DbgPrint (ASL_DEBUG_OUTPUT, PR_PREFIX_ID
        "[#if defined %s] resolved to: %8.8X%8.8X\n",
        AslGbl_CurrentLineNumber, Identifier, ACPI_FORMAT_UINT64 (Value));

    return (Value);
}


/******************************************************************************
 *
 * FUNCTION:    PrResolveIntegerExpression
 *
 * PARAMETERS:  Line                - Pointer to integer expression
 *              ReturnValue         - Where the resolved 64-bit integer is
 *                                    returned.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Resolve an integer expression to a single value. Supports
 *              both integer constants and labels.
 *
 *****************************************************************************/

ACPI_STATUS
PrResolveIntegerExpression (
    char                    *Line,
    UINT64                  *ReturnValue)
{
    UINT64                  Result;
    DbgPrint (ASL_DEBUG_OUTPUT, PR_PREFIX_ID
        "**** Resolve #if:  %s\n", AslGbl_CurrentLineNumber, Line);

    /* Expand all macros within the expression first */

    PrExpandLineMacros (AslGbl_ExpressionTokenBuffer, PR_EXPR_SEPARATORS);

    /* Now we can evaluate the expression */

    Result = PrEvaluateExpression (Line);
    DbgPrint (ASL_DEBUG_OUTPUT, PR_PREFIX_ID
        "**** Expression Resolved to: %8.8X%8.8X\n",
        AslGbl_CurrentLineNumber, ACPI_FORMAT_UINT64 (Result));

    *ReturnValue = Result;
    return (AE_OK);

#if 0
InvalidExpression:

    ACPI_FREE (EvalBuffer);
    PrError (ASL_ERROR, ASL_MSG_INVALID_EXPRESSION, 0);
    return (AE_ERROR);


NormalExit:

    DbgPrint (ASL_DEBUG_OUTPUT, PR_PREFIX_ID
        "**** Expression Resolved to: %8.8X%8.8X\n",
        AslGbl_CurrentLineNumber, ACPI_FORMAT_UINT64 (Value1));

    *ReturnValue = Value1;
    return (AE_OK);
#endif
}
