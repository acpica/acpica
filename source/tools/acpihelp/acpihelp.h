/******************************************************************************
 *
 * Module Name: acpihelp.h - Include file for AcpiHelp utility
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2017, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights. You may have additional license terms from the party that provided
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
 * to or modifications of the Original Intel Code. No other license or right
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
 * and the following Disclaimer and Export Compliance provision. In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change. Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee. Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution. In
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
 * HERE. ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT, ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES. INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS. INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES. THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government. In the
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

#ifndef __ACPIHELP_H
#define __ACPIHELP_H


#include "acpi.h"
#include "accommon.h"
#include "acapps.h"

#include <sys/types.h>
#ifdef WIN32
#include <io.h>
#include <direct.h>
#endif


/*
 * Global variables. Defined in ahmain.c only, externed in all other files
 */
#undef ACPI_GLOBAL
#undef ACPI_INIT_GLOBAL

#ifdef DEFINE_AHELP_GLOBALS
#define ACPI_GLOBAL(type,name) \
    extern type name; \
    type name

#define ACPI_INIT_GLOBAL(type,name,value) \
    type name=value

#else
#ifndef ACPI_GLOBAL
#define ACPI_GLOBAL(type,name) \
    extern type name
#endif

#ifndef ACPI_INIT_GLOBAL
#define ACPI_INIT_GLOBAL(type,name,value) \
    extern type name
#endif
#endif


#define AH_BUFFER_LENGTH                128
#define AH_LINE_BUFFER_LENGTH           512
#define AH_MAX_ASL_LINE_LENGTH          70
#define AH_MAX_AML_LINE_LENGTH          100

ACPI_GLOBAL (char,                      Gbl_Buffer[AH_BUFFER_LENGTH]);
ACPI_GLOBAL (char,                      Gbl_LineBuffer[AH_LINE_BUFFER_LENGTH]);


#define AH_DISPLAY_EXCEPTION(Status, Name) \
    printf ("%.4X: %s\n", Status, Name)

#define AH_DISPLAY_EXCEPTION_TEXT(Status, Exception) \
    printf ("%.4X: %-28s (%s)\n", Status,\
    Exception->Name, Exception->Description)


typedef enum
{
    AH_DECODE_DEFAULT           = 0,
    AH_DECODE_ASL,
    AH_DECODE_ASL_KEYWORD,
    AH_DECODE_PREDEFINED_NAME,
    AH_DECODE_AML,
    AH_DECODE_AML_OPCODE,
    AH_DECODE_AML_TYPE,
    AH_DECODE_ASL_AML,
    AH_DECODE_EXCEPTION,

    AH_DISPLAY_DEVICE_IDS,
    AH_DISPLAY_UUIDS,
    AH_DISPLAY_TABLES,
    AH_DISPLAY_DIRECTIVES

} AH_OPTION_TYPES;

typedef struct ah_aml_opcode
{
    UINT16          OpcodeRangeStart;
    UINT16          OpcodeRangeEnd;
    char            *OpcodeString;
    char            *OpcodeName;
    char            *Type;
    char            *FixedArguments;
    char            *VariableArguments;
    char            *Grammar;

} AH_AML_OPCODE;

typedef struct ah_aml_type
{
    char            *Name;
    char            *Description;

} AH_AML_TYPE;

typedef struct ah_asl_operator
{
    char            *Name;
    char            *Syntax;
    char            *Description;

} AH_ASL_OPERATOR;

typedef struct ah_asl_keyword
{
    char            *Name;
    char            *Description;
    char            *KeywordList;

} AH_ASL_KEYWORD;

typedef struct ah_directive_info
{
    char            *Name;
    char            *Description;

} AH_DIRECTIVE_INFO;


/* Externals for various data tables */

extern const AH_AML_OPCODE          Gbl_AmlOpcodeInfo[];
extern const AH_AML_TYPE            Gbl_AmlTypesInfo[];
extern const AH_ASL_OPERATOR        Gbl_AslOperatorInfo[];
extern const AH_ASL_KEYWORD         Gbl_AslKeywordInfo[];
extern const AH_UUID                Gbl_AcpiUuids[];
extern const AH_DIRECTIVE_INFO      Gbl_PreprocessorDirectives[];
extern const AH_TABLE               Gbl_AcpiSupportedTables[];


void
AhFindAmlOpcode (
    char                    *Name);

void
AhDecodeAmlOpcode (
    char                    *Name);

void
AhDecodeException (
    char                    *Name);

void
AhFindPredefinedNames (
    char                    *Name);

void
AhFindAslAndAmlOperators (
    char                    *Name);

UINT32
AhFindAslOperators (
    char                    *Name);

void
AhFindAslKeywords (
    char                    *Name);

void
AhFindAmlTypes (
    char                    *Name);

void
AhDisplayDeviceIds (
    char                    *Name);

void
AhDisplayTables (
    void);

const AH_TABLE *
AcpiAhGetTableInfo (
    char                    *Signature);

void
AhDisplayUuids (
    void);

void
AhDisplayDirectives (
    void);

void
AhPrintOneField (
    UINT32                  Indent,
    UINT32                  CurrentPosition,
    UINT32                  MaxPosition,
    const char              *Field);

#endif /* __ACPIHELP_H */
