/******************************************************************************
 *
 * Module Name: preprocess.h - header for iASL Preprocessor
 *
 *****************************************************************************/

/******************************************************************************
 *
 * Copyright (c) 1999 - 2026, Intel Corp.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 *
 *****************************************************************************/

#define __PREPROCESS_H__

#ifndef _PREPROCESS
#define _PREPROCESS

#undef PR_EXTERN

#ifdef _DECLARE_PR_GLOBALS
#define PR_EXTERN
#define PR_INIT_GLOBAL(a,b)         (a)=(b)
#else
#define PR_EXTERN                   extern
#define PR_INIT_GLOBAL(a,b)         (a)
#endif


/*
 * Configuration
 */
#define PR_MAX_MACRO_ARGS       32              /* Max number of macro args */
#define PR_MAX_ARG_INSTANCES    24              /* Max instances of any one arg */
#define PR_MAX_MACRO_DEPTH      5               /* Max nested macro expansions */
#define PR_LINES_PER_BLOCK      4096            /* Max input source lines per block */


/*
 * Local defines and macros
 */
#define PR_TOKEN_SEPARATORS     " ,(){}\t\n"
#define PR_MACRO_SEPARATORS     " ,(){}[];?:~!*/%+-<>=&^|\"\t\n"
#define PR_MACRO_ARGUMENTS      " ,\t\n"
#define PR_EXPR_SEPARATORS      " ,(){}[];?:~!*/%+-<>=&^|\"\t\n"

#define PR_PREFIX_ID            "Pr(%.4u) - "             /* Used for debug output */

#define THIS_TOKEN_OFFSET(t)    ((AslGbl_MainTokenBuffer - t) + 1)


/*
 * Preprocessor structures
 */
typedef struct pr_macro_arg
{
    char                        *Name;
    UINT32                      Offset[PR_MAX_ARG_INSTANCES];
    BOOLEAN                     Stringize[PR_MAX_ARG_INSTANCES];
    UINT16                      UseCount;

} PR_MACRO_ARG;

typedef struct pr_define_info
{
    struct pr_define_info       *Previous;
    struct pr_define_info       *Next;
    char                        *Identifier;
    char                        *Replacement;
    char                        *Body;          /* Macro body */
    PR_MACRO_ARG                *Args;          /* Macro arg list */
    UINT16                      ArgCount;       /* Macro arg count */
    BOOLEAN                     Variadic;       /* Macro has variadic args */
    BOOLEAN                     Persist;        /* Keep for entire compiler run */

} PR_DEFINE_INFO;

typedef struct pr_directive_info
{
    char                        *Name;          /* Directive name */
    UINT8                       ArgCount;       /* Required # of args */

} PR_DIRECTIVE_INFO;

typedef struct pr_operator_info
{
    char                        *Op;

} PR_OPERATOR_INFO;

typedef struct pr_file_node
{
    struct pr_file_node         *Next;
    FILE                        *File;
    char                        *Filename;
    UINT32                      CurrentLineNumber;

} PR_FILE_NODE;

#define MAX_ARGUMENT_LENGTH     24

typedef struct directive_info
{
    struct directive_info       *Next;
    char                        Argument[MAX_ARGUMENT_LENGTH];
    int                         Directive;
    BOOLEAN                     IgnoringThisCodeBlock;

} DIRECTIVE_INFO;


/*
 * Globals
 */
PR_EXTERN char                  PR_INIT_GLOBAL (*AslGbl_MainTokenBuffer, NULL); /* [ASL_LINE_BUFFER_SIZE]; */
PR_EXTERN char                  PR_INIT_GLOBAL (*AslGbl_MacroTokenBuffer, NULL); /* [ASL_LINE_BUFFER_SIZE]; */
PR_EXTERN char                  PR_INIT_GLOBAL (*AslGbl_MacroTokenReplaceBuffer, NULL); /* [ASL_LINE_BUFFER_SIZE]; */
PR_EXTERN char                  PR_INIT_GLOBAL (*AslGbl_ExpressionTokenBuffer, NULL); /* [ASL_LINE_BUFFER_SIZE]; */

PR_EXTERN UINT32                AslGbl_PreprocessorLineNumber;
PR_EXTERN int                   AslGbl_IfDepth;
PR_EXTERN PR_FILE_NODE          *AslGbl_InputFileList;
PR_EXTERN BOOLEAN               PR_INIT_GLOBAL (AslGbl_PreprocessorError, FALSE);
PR_EXTERN BOOLEAN               PR_INIT_GLOBAL (AslGbl_IgnoringThisCodeBlock, FALSE);
PR_EXTERN PR_DEFINE_INFO        PR_INIT_GLOBAL (*AslGbl_DefineList, NULL);
PR_EXTERN DIRECTIVE_INFO        PR_INIT_GLOBAL (*AslGbl_DirectiveStack, NULL);

#if 0 /* TBD for macros */
PR_EXTERN char                  PR_INIT_GLOBAL (*XXXEvalBuffer, NULL); /* [ASL_LINE_BUFFER_SIZE]; */
#endif


/*
 * prscan - Preprocessor entry
 */
void
PrInitializePreprocessor (
    void);

void
PrInitializeGlobals (
    void);

void
PrTerminatePreprocessor (
    void);

void
PrDoPreprocess (
    void);

UINT64
PrIsDefined (
    char                    *Identifier);

UINT64
PrResolveDefine (
    char                    *Identifier);

int
PrInitLexer (
    char                    *String);

void
PrTerminateLexer (
    void);


/*
 * prmacros - Support for #defines and macros
 */
void
PrDumpPredefinedNames (
    void);

void
PrAddBuiltInMacros (
    void);

PR_DEFINE_INFO *
PrAddDefine (
    char                    *Token,
    char                    *Token2,
    BOOLEAN                 Persist);

void
PrRemoveDefine (
    char                    *DefineName);

PR_DEFINE_INFO *
PrMatchDefine (
    char                    *MatchString);

void
PrAddMacro (
    char                    *Name,
    char                    **Next);

void
PrExpandLineMacros (
    char                    *TokenBuffer,
    char                    *Separators);

BOOLEAN
PrDoMacroInvocation (
    char                    *TokenBuffer,
    char                    *MacroStart,
    PR_DEFINE_INFO          *DefineInfo,
    char                    **Next,
    UINT32                  TokenOffset,
    int                     *OffsetAdjust);


/*
 * prexpress - #if expression support
 */
ACPI_STATUS
PrResolveIntegerExpression (
    char                    *Line,
    UINT64                  *ReturnValue);

char *
PrPrioritizeExpression (
    char                    *OriginalLine);

/*
 * prparser - lex/yacc expression parser
 */
UINT64
PrEvaluateExpression (
    char                    *ExprString);


/*
 * prutils - Preprocessor utilities
 */
char *
PrGetNextToken (
    char                    *Buffer,
    char                    *MatchString,
    char                    **Next);

void
PrError (
    UINT8                   Level,
    UINT16                  MessageId,
    UINT32                  Column);

void
PrReplaceResizeSubstring(
    PR_MACRO_ARG            *Args,
    UINT32                  Diff1,
    UINT32                  Diff2,
    UINT32                  i,
    char                    *Token,
    BOOLEAN                 Stringize);

void
PrResolveTokenPasting (
    void);

char *
PrReplaceData (
    char                    *Buffer,
    UINT32                  LengthToRemove,
    char                    *BufferToAdd,
    UINT32                  LengthToAdd);

FILE *
PrOpenIncludeFile (
    char                    *Filename,
    char                    *OpenMode,
    char                    **FullPathname);

FILE *
PrOpenIncludeWithPrefix (
    char                    *PrefixDir,
    char                    *Filename,
    char                    *OpenMode,
    char                    **FullPathname);

void
PrPushInputFileStack (
    FILE                    *InputFile,
    char                    *Filename);

BOOLEAN
PrPopInputFileStack (
    void);

#endif
