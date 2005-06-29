/******************************************************************************
 * 
 * Module Name: parser.h - AML Parser subcomponent prototypes and defines
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


#ifndef _PARSER_H_
#define _PARSER_H_


#ifndef NULL
#define NULL                ((void*) 0)
#endif


/*
 * Access I/O memory
 */
#define GET8(addr)          (*(UINT8*)(addr))
#define GET16(addr)         (*(UINT16*)(addr))
#define GET32(addr)         (*(UINT32*)(addr))



/* push current scope for single or variable arguments */

#define ACPI_PUSH_SCOPE_SINGLE_ARG      1
#define ACPI_PUSH_SCOPE_VAR_ARGS        2



/*
 * AML opcode, name, and argument layout
 */
typedef struct acpi_aml_op
{
    INT32                   opcode;         /* AML opcode */
    char                    *name;          /* op name */
    char                    *args;          /* argument format */
    UINT8                   group;
    UINT8                   type;

} ACPI_AML_OP;


typedef union acpi_op_value
{
    UINT32                  integer;        /* integer constant */
    char                    *string;        /* NULL terminated string */
    UINT8                   *name;          /* name string */
    struct acpi_generic_op  *arg;           /* arguments and contained ops */
    UINT32                  size;           /* bytelist or field size */

} ACPI_OP_VALUE;


/*
 * generic operation (eg. If, While, Store)
 */
typedef struct acpi_generic_op
{
    INT32                   opcode;         /* AML opcode */
    char                    OpName[12];     /* Debug Only! */
    ACPI_OP_VALUE           value;          /* Value or args associated with the opcode */
    ACPI_AML_OP             *AmlOp;         /* Aml opcode struct */
    ACPI_PTRDIFF            AmlOffset;      /* offset of declaration in AML */
    struct acpi_generic_op  *next;          /* next op */
    struct acpi_generic_op  *parent;        /* parent op */
    void                    *Entry;         /* for use by interpreter */

} ACPI_GENERIC_OP;


/*
 * operation with a name (eg. Scope, Method, Name, NamedField, ...)
 */
typedef struct acpi_named_op
{
    ACPI_GENERIC_OP         op;             /* acpi_op data */
    UINT32                  name;           /* 4-byte name or 0 if none */

} ACPI_NAMED_OP;


/*
 * special operation for bytelists (ByteList only)
 */
typedef struct acpi_bytelist_op
{
    ACPI_GENERIC_OP         op;             /* acpi_op data */
    UINT8                   *data;          /* bytelist data */

} ACPI_BYTELIST_OP;




typedef struct acpi_parse_scope
{
    ACPI_GENERIC_OP         *op;            /* current op being parsed */
    char                    *nextArg;       /* next argument to parse */
    UINT8                   *argEnd;        /* current argument end */
    UINT8                   *pkgEnd;        /* current package end */
    struct acpi_parse_scope *parent;        /* parent scope */
    UINT32                  AmliState;      /* interpreter state */

} ACPI_PARSE_SCOPE;

typedef struct acpi_parse_state
{
    UINT8                   *amlEnd;        /* (last + 1) AML byte */
    UINT8                   *aml;           /* next AML byte */
    UINT8                   *pkgEnd;        /* current package end */
    struct acpi_parse_scope *scope;         /* current scope */
    struct acpi_parse_scope *scopeAvail;    /* unused (extra) scope structs */
    UINT8                   *amlStart;      /* first AML byte */
    UINT32                  AmliState;      /* interpreter state */

} ACPI_PARSE_STATE;



typedef
ACPI_STATUS (*INTERPRETER_CALLBACK) (
    UINT8                   *PcodeAddr, 
    ACPI_PARSE_STATE        *state,
    ACPI_GENERIC_OP         *op);






/*
 * psscope
 */

void
PsInitScope (
    ACPI_PARSE_STATE        *state);

ACPI_GENERIC_OP *
PsGetParentScope (
    ACPI_PARSE_STATE        *state);

INT32
PsHasCompletedScope (
    ACPI_PARSE_STATE        *state);

void
PsPushScope (
    ACPI_PARSE_STATE        *state,
    ACPI_GENERIC_OP         *op,            /* current op (to be pushed) */
    char                    *nextArg,       /* next op argument (to be pushed) */
    INT32                   push);          /* push for single or multiple args */

void
PsPopScope (
    ACPI_PARSE_STATE        *state,
    ACPI_GENERIC_OP         **op,           /* (OUT) previous op */
    char                    **nextArg);     /* (OUT) previous op next argument */

ACPI_GENERIC_OP*
PsCleanupScope (
    ACPI_PARSE_STATE        *state);


/*
 * psargs
 */

UINT8*
PsNextNamestring (ACPI_PARSE_STATE *state);

ACPI_GENERIC_OP*
PsNextArg (ACPI_PARSE_STATE *state, INT32 argType, INT32 *push);

void
PsNextSimple (
    ACPI_PARSE_STATE        *state,
    INT32                   argType,        /* type of argument */
    ACPI_GENERIC_OP         *arg);           /* (OUT) argument data */


/*
 * psname
 */

void
PsAppendArg(ACPI_GENERIC_OP *op, ACPI_GENERIC_OP *arg);


/*
 * amlop.c
 */
extern ACPI_AML_OP acpiAmlOps[];
extern UINT8 acpiAmlOpIndex[256];


/*
 * ns.c
 */
ACPI_GENERIC_OP *
PsGetArg(ACPI_GENERIC_OP *op, INT32 argn);

void 
PsAppendArg(ACPI_GENERIC_OP *op, ACPI_GENERIC_OP *arg);

ACPI_GENERIC_OP *
PsGetChild(ACPI_GENERIC_OP *op);

ACPI_GENERIC_OP *
PsGetDepthNext(ACPI_GENERIC_OP *origin, ACPI_GENERIC_OP *op);

ACPI_GENERIC_OP *
PsFind(ACPI_GENERIC_OP *scope, ACPI_GENERIC_OP *path);

ACPI_GENERIC_OP *
PsCreate(ACPI_GENERIC_OP *scope,
    char *path,
    ACPI_GENERIC_OP *value);

/*
 * parse.c
 */
ACPI_AML_OP *
PsFindOpcode(INT32 opcode);

ACPI_STATUS
PsParse (
    UINT8                   *aml, 
    INT32                   amlSize,
    INTERPRETER_CALLBACK    DescendingCallback,
    INTERPRETER_CALLBACK    AscendingCallback,
    ACPI_GENERIC_OP         **RootObject);

INT32
PsPeekOpcode (
    ACPI_PARSE_STATE  *state);

/*
 * util.c
 */
ACPI_GENERIC_OP * 
PsAllocOp(INT32 opcode);

INT32 
PsSprintPath(char *str, INT32 size, ACPI_GENERIC_OP *op);

INT32 
PsSprintOp(char *str, INT32 size, ACPI_GENERIC_OP *op);

void 
PsShow(ACPI_GENERIC_OP *op);



INT32
PsIsLeadingChar (INT32 c);

INT32
PsIsPrefixChar (INT32 c);

INT32
PsIsNamedOp(INT32 opcode);

INT32
PsIsBytelistOp(INT32 opcode);

INT32
PsIsFieldOp(INT32 opcode);

ACPI_NAMED_OP*
PsToNamedOp(ACPI_GENERIC_OP* op);

ACPI_BYTELIST_OP*
PsToBytelistOp(ACPI_GENERIC_OP* op);

ACPI_GENERIC_OP*
PsToNonconstOp(ACPI_GENERIC_OP* op);

UINT32
PsGetName(ACPI_GENERIC_OP *op);

void
PsSetName(ACPI_GENERIC_OP *op, UINT32 name);







#endif /* _PARSER_H_ */
