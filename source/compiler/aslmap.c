
/******************************************************************************
 *
 * Module Name: aslmap - parser to AML opcode mapping table
 *              $Revision: 1.12 $
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
#include "amlcode.h"

/* 
 * TBD:
 * AccessAttrib
 * AccessType
 * AMlop for DMA?
 * ObjectType keywords
 * Register
 */

/*******************************************************************************
 *
 * DATA STRUCTURE:  AslKeywordMapping
 *
 * DESCRIPTION:     Maps the ParseOpcode to the actual AML opcode.  The parse
 *                  opcodes are generated from Bison, and this table must
 *                  track any additions to them.
 *
 * Each entry in the table contains the following items:
 *
 * AML opcode   - Opcode that is written to the AML file
 * Value        - Value of the object to be written (if applicable)
 * Flags        - 1) Whether this opcode opens an AML "package".
 *
 ******************************************************************************/

ASL_MAPPING_ENTRY AslKeywordMapping [] = 
{

/* ACCESSAS */                  OP_TABLE_ENTRY (AML_ACCESSFIELD_OP,         0,                  0),
/* ACCESSATTRIB_BLOCK */        OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BLOCK_ACC,   0),
/* ACCESSATTRIB_BYTE */         OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,    0),
/* ACCESSATTRIB_CALL */         OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,    0),
/* ACCESSATTRIB_QUICK */        OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,    0),
/* ACCESSATTRIB_SND_RCV */      OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,    0),
/* ACCESSATTRIB_WORD */         OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,    0),
/* ACCESSTYPE_ANY */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_ANY_ACC,     0),
/* ACCESSTYPE_BUF */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_ANY_ACC,     0),
/* ACCESSTYPE_BYTE */           OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_BYTE_ACC,    0),
/* ACCESSTYPE_DWORD */          OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_DWORD_ACC,   0),
/* ACCESSTYPE_QWORD */          OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_DWORD_ACC,   0),
/* ACCESSTYPE_WORD */           OP_TABLE_ENTRY (AML_BYTE_OP,                ACCESS_WORD_ACC,    0),
/* ACQUIRE */                   OP_TABLE_ENTRY (AML_ACQUIRE_OP,             0,                  0),
/* ADD */                       OP_TABLE_ENTRY (AML_ADD_OP,                 0,                  0),
/* ADDRESSSPACE_FFIXEDHW */     OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),  /* TBD: is this used ? */
/* ADDRESSTYPE_ACPI */          OP_TABLE_ENTRY (AML_BYTE_OP,                2,                  0),
/* ADDRESSTYPE_MEMORY */        OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* ADDRESSTYPE_NVS */           OP_TABLE_ENTRY (AML_BYTE_OP,                3,                  0),
/* ADDRESSTYPE_RESERVED */      OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* ALIAS */                     OP_TABLE_ENTRY (AML_ALIAS_OP,               0,                  0),
/* AND */                       OP_TABLE_ENTRY (AML_BIT_AND_OP,             0,                  0),
/* ARG0 */                      OP_TABLE_ENTRY (AML_ARG0,                   0,                  0),
/* ARG1 */                      OP_TABLE_ENTRY (AML_ARG1,                   0,                  0),
/* ARG2 */                      OP_TABLE_ENTRY (AML_ARG2,                   0,                  0),
/* ARG3 */                      OP_TABLE_ENTRY (AML_ARG3,                   0,                  0),
/* ARG4 */                      OP_TABLE_ENTRY (AML_ARG4,                   0,                  0),
/* ARG5 */                      OP_TABLE_ENTRY (AML_ARG5,                   0,                  0),
/* ARG6 */                      OP_TABLE_ENTRY (AML_ARG6,                   0,                  0),
/* BANKFIELD */                 OP_TABLE_ENTRY (AML_BANK_FIELD_OP,          0,                  NODE_AML_PACKAGE),
/* BREAK */                     OP_TABLE_ENTRY (AML_BREAK_OP,               0,                  0),
/* BREAKPOINT */                OP_TABLE_ENTRY (AML_BREAK_POINT_OP,         0,                  0),
/* BUFFER */                    OP_TABLE_ENTRY (AML_BUFFER_OP,              0,                  NODE_AML_PACKAGE),
/* BUSMASTERTYPE_MASTER */      OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* BUSMASTERTYPE_NOTMASTER */   OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* BYTECONST */                 OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          0,                  0),
/* CASE */                      OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* CONCATENATE */               OP_TABLE_ENTRY (AML_CONCAT_OP,              0,                  0),
/* CONCATENATERESTEMPLATE */    OP_TABLE_ENTRY (AML_CONCAT_TPL_OP,          0,                  0),
/* CONDREFOF */                 OP_TABLE_ENTRY (AML_COND_REF_OF_OP,         0,                  0),
/* CONTINUE */                  OP_TABLE_ENTRY (AML_CONTINUE_OP,            0,                  0),
/* COPY */                      OP_TABLE_ENTRY (AML_COPY_OP,                0,                  0),
/* CREATEBITFIELD */            OP_TABLE_ENTRY (AML_BIT_FIELD_OP,           0,                  0),
/* CREATEBYTEFIELD */           OP_TABLE_ENTRY (AML_BYTE_FIELD_OP,          0,                  0),
/* CREATEDWORDFIELD */          OP_TABLE_ENTRY (AML_DWORD_FIELD_OP,         0,                  0),
/* CREATEFIELD */               OP_TABLE_ENTRY (AML_CREATE_FIELD_OP,        0,                  0),
/* CREATEQWORDFIELD */          OP_TABLE_ENTRY (AML_QWORD_FIELD_OP,         0,                  0),
/* CREATEWORDFIELD */           OP_TABLE_ENTRY (AML_WORD_FIELD_OP,          0,                  0),
/* DATATABLEREGION */           OP_TABLE_ENTRY (AML_DATA_REGION_OP,         0,                  0),
/* DEBUG */                     OP_TABLE_ENTRY (AML_DEBUG_OP,               0,                  0),
/* DECODETYPE_POS */            OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* DECODETYPE_SUB */            OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* DECREMENT */                 OP_TABLE_ENTRY (AML_DECREMENT_OP,           0,                  0),
/* DEFAULT */                   OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* DEFAULT_ARG */               OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* DEFINITIONBLOCK */           OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* DEREFOF */                   OP_TABLE_ENTRY (AML_DEREF_OF_OP,            0,                  0),
/* DEVICE */                    OP_TABLE_ENTRY (AML_DEVICE_OP,              0,                  NODE_AML_PACKAGE),
/* DIVIDE */                    OP_TABLE_ENTRY (AML_DIVIDE_OP,              0,                  0),
/* DMA */                       OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* DMATYPE_A */                 OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* DMATYPE_COMPATIBILITY */     OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* DMATYPE_B */                 OP_TABLE_ENTRY (AML_BYTE_OP,                2,                  0),
/* DMATYPE_F */                 OP_TABLE_ENTRY (AML_BYTE_OP,                3,                  0),
/* DWORDCONST */                OP_TABLE_ENTRY (AML_RAW_DATA_DWORD,         0,                  0),
/* DWORDIO */                   OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* DWORDMEMORY */               OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* EISAID */                    OP_TABLE_ENTRY (AML_DWORD_OP,               0,                  0),
/* ELSE */                      OP_TABLE_ENTRY (AML_ELSE_OP,                0,                  NODE_AML_PACKAGE),
/* ELSEIF */                    OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  NODE_AML_PACKAGE),
/* ENDDEPENDENTFN */            OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* EVENT */                     OP_TABLE_ENTRY (AML_EVENT_OP,               0,                  0),
/* EXTERNAL */                  OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* FATAL */                     OP_TABLE_ENTRY (AML_FATAL_OP,               0,                  0),
/* FIELD */                     OP_TABLE_ENTRY (AML_DEF_FIELD_OP,           0,                  NODE_AML_PACKAGE),
/* FINDSETLEFTBIT */            OP_TABLE_ENTRY (AML_FIND_SET_LEFT_BIT_OP,   0,                  0),
/* FINDSETRIGHTBIT */           OP_TABLE_ENTRY (AML_FIND_SET_RIGHT_BIT_OP,  0,                  0),
/* FIXEDIO */                   OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* FROMBCD */                   OP_TABLE_ENTRY (AML_FROM_BCD_OP,            0,                  0),
/* IF */                        OP_TABLE_ENTRY (AML_IF_OP,                  0,                  NODE_AML_PACKAGE),
/* INCLUDE */                   OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* INCLUDE_CSTYLE */            OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* INCLUDE_END */               OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* INCREMENT */                 OP_TABLE_ENTRY (AML_INCREMENT_OP,           0,                  0),
/* INDEX */                     OP_TABLE_ENTRY (AML_INDEX_OP,               0,                  0),
/* INDEXFIELD */                OP_TABLE_ENTRY (AML_INDEX_FIELD_OP,         0,                  NODE_AML_PACKAGE),
/* INTEGER */                   OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* INTERRUPT */                 OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* INTLEVEL_ACTIVEHIGH */       OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* INTLEVEL_ACTIVELOW */        OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* INTTYPE_EDGE */              OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* INTTYPE_LEVEL */             OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* IO */                        OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* IODECODETYPE_10 */           OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* IODECODETYPE_16 */           OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* IRQ */                       OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* IRQNOFLAGS */                OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* LAND */                      OP_TABLE_ENTRY (AML_LAND_OP,                0,                  0),
/* LEQUAL */                    OP_TABLE_ENTRY (AML_LEQUAL_OP,              0,                  0),
/* LGREATER */                  OP_TABLE_ENTRY (AML_LGREATER_OP,            0,                  0),
/* LGREATEREQUAL */             OP_TABLE_ENTRY (AML_LGREATEREQUAL_OP,       0,                  0),
/* LLESS */                     OP_TABLE_ENTRY (AML_LLESS_OP,               0,                  0),
/* LLESSEQUAL */                OP_TABLE_ENTRY (AML_LLESSEQUAL_OP,          0,                  0),
/* LNOT */                      OP_TABLE_ENTRY (AML_LNOT_OP,                0,                  0),
/* LNOTEQUAL */                 OP_TABLE_ENTRY (AML_LNOTEQUAL_OP,           0,                  0),
/* LOAD */                      OP_TABLE_ENTRY (AML_LOAD_OP,                0,                  0),
/* LOADTABLE */                 OP_TABLE_ENTRY (AML_LOAD_TABLE_OP,          0,                  0),
/* LOCAL0 */                    OP_TABLE_ENTRY (AML_LOCAL0,                 0,                  0),
/* LOCAL1 */                    OP_TABLE_ENTRY (AML_LOCAL1,                 0,                  0),
/* LOCAL2 */                    OP_TABLE_ENTRY (AML_LOCAL2,                 0,                  0),
/* LOCAL3 */                    OP_TABLE_ENTRY (AML_LOCAL3,                 0,                  0),
/* LOCAL4 */                    OP_TABLE_ENTRY (AML_LOCAL4,                 0,                  0),
/* LOCAL5 */                    OP_TABLE_ENTRY (AML_LOCAL5,                 0,                  0),
/* LOCAL6 */                    OP_TABLE_ENTRY (AML_LOCAL6,                 0,                  0),
/* LOCAL7 */                    OP_TABLE_ENTRY (AML_LOCAL7,                 0,                  0),
/* LOCKRULE_LOCK */             OP_TABLE_ENTRY (AML_BYTE_OP,                GLOCK_ALWAYS_LOCK,  0),
/* LOCKRULE_NOLOCK */           OP_TABLE_ENTRY (AML_BYTE_OP,                GLOCK_NEVER_LOCK,   0),
/* LOR */                       OP_TABLE_ENTRY (AML_LOR_OP,                 0,                  0),
/* MATCH */                     OP_TABLE_ENTRY (AML_MATCH_OP,               0,                  0),
/* MATCHTYPE_MEQ */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          MATCH_MEQ,          0),
/* MATCHTYPE_MGE */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          MATCH_MGE,          0),
/* MATCHTYPE_MGT */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          MATCH_MGT,          0),
/* MATCHTYPE_MLE */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          MATCH_MLE,          0),
/* MATCHTYPE_MLT */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          MATCH_MLT,          0),
/* MATCHTYPE_MTR */             OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          MATCH_MTR,          0),
/* MAXTYPE_FIXED */             OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* MAXTYPE_NOTFIXED */          OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* MEMORY24 */                  OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* MEMORY32 */                  OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* MEMORY32FIXED */             OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* MEMTYPE_CACHEABLE */         OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* MEMTYPE_NONCACHEABLE */      OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* MEMTYPE_PREFETCHABLE */      OP_TABLE_ENTRY (AML_BYTE_OP,                3,                  0),
/* MEMTYPE_WRITECOMBINING */    OP_TABLE_ENTRY (AML_BYTE_OP,                2,                  0),
/* METHOD */                    OP_TABLE_ENTRY (AML_METHOD_OP,              0,                  NODE_AML_PACKAGE),
/* METHODCALL */                OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* MID */                       OP_TABLE_ENTRY (AML_MID_OP,                 0,                  0),
/* MINTYPE_FIXED */             OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* MINTYPE_NOTFIXED */          OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* MOD */                       OP_TABLE_ENTRY (AML_MOD_OP,                 0,                  0),
/* MULTIPLY */                  OP_TABLE_ENTRY (AML_MULTIPLY_OP,            0,                  0),
/* MUTEX */                     OP_TABLE_ENTRY (AML_MUTEX_OP,               0,                  0),
/* NAME */                      OP_TABLE_ENTRY (AML_NAME_OP,                0,                  0),
/* NAMESEG */                   OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* NAMESTRING */                OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* NAND */                      OP_TABLE_ENTRY (AML_BIT_NAND_OP,            0,                  0),
/* NOOP */                      OP_TABLE_ENTRY (AML_NOOP_OP,                0,                  0),
/* NOR */                       OP_TABLE_ENTRY (AML_BIT_NOR_OP,             0,                  0),
/* NOT */                       OP_TABLE_ENTRY (AML_BIT_NOT_OP,             0,                  0),
/* NOTIFY */                    OP_TABLE_ENTRY (AML_NOTIFY_OP,              0,                  0),
/* OBJECTTYPE */                OP_TABLE_ENTRY (AML_TYPE_OP,                0,                  0),
/* OBJECTTYPE_BFF */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_BUFFER_FIELD,0),
/* OBJECTTYPE_BUF */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_BUFFER,   0),
/* OBJECTTYPE_DDB */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_DDB_HANDLE,0),
/* OBJECTTYPE_DEV */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_DEVICE,   0),
/* OBJECTTYPE_EVT */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_EVENT,    0),
/* OBJECTTYPE_FLD */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_FIELD_UNIT,0),
/* OBJECTTYPE_INT */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_NUMBER,   0),
/* OBJECTTYPE_MTH */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_METHOD,   0),
/* OBJECTTYPE_MTX */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_MUTEX,    0),
/* OBJECTTYPE_OPR */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_REGION,   0),
/* OBJECTTYPE_PKG */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_PACKAGE,  0),
/* OBJECTTYPE_POW */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_POWER,    0),
/* OBJECTTYPE_STR */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_STRING,   0),
/* OBJECTTYPE_THZ */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_THERMAL,  0),
/* OBJECTTYPE_UNK */            OP_TABLE_ENTRY (AML_BYTE_OP,                ACPI_TYPE_ANY,      0),
/* OFFSET */                    OP_TABLE_ENTRY (AML_RESERVEDFIELD_OP,       0,                  0),
/* ONE */                       OP_TABLE_ENTRY (AML_ONE_OP,                 0,                  0),
/* ONES */                      OP_TABLE_ENTRY (AML_ONES_OP,                0,                  0),
/* OPERATIONREGION */           OP_TABLE_ENTRY (AML_REGION_OP,              0,                  0),
/* OR */                        OP_TABLE_ENTRY (AML_BIT_OR_OP,              0,                  0),
/* PACKAGE */                   OP_TABLE_ENTRY (AML_PACKAGE_OP,             0,                  NODE_AML_PACKAGE),
/* PACKAGEP_LENGTH */           OP_TABLE_ENTRY (AML_PACKAGE_LENGTH,         0,                  NODE_AML_PACKAGE),
/* POWERRESOURCE */             OP_TABLE_ENTRY (AML_POWER_RES_OP,           0,                  NODE_AML_PACKAGE),
/* PROCESSOR */                 OP_TABLE_ENTRY (AML_PROCESSOR_OP,           0,                  NODE_AML_PACKAGE),
/* QWORDCONST */                OP_TABLE_ENTRY (AML_RAW_DATA_QWORD,         0,                  0),
/* QWORDIO */                   OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* QWORDMEMORY */               OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* RANGE_TYPE_ENTIRE */         OP_TABLE_ENTRY (AML_BYTE_OP,                3,                  0),
/* RANGE_TYPE_ISAONLY */        OP_TABLE_ENTRY (AML_BYTE_OP,                2,                  0),
/* RANGE_TYPE_NONISAONLY */     OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* RAW_DATA */                  OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* READWRITETYPE_BOTH */        OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* READWRITETYPE_READONLY */    OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* REFOF */                     OP_TABLE_ENTRY (AML_REF_OF_OP,              0,                  0),
/* REGIONSPACE_CMOS */          OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_CMOS,        0),
/* REGIONSPACE_EC */            OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_EC,          0),
/* REGIONSPACE_IO */            OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_IO,          0),
/* REGIONSPACE_MEM */           OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_MEMORY,      0),
/* REGIONSPACE_PCI */           OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_PCI_CONFIG,  0),
/* REGIONSPACE_PCIBAR */        OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_PCI_BAR,     0),
/* REGIONSPACE_SMBUS */         OP_TABLE_ENTRY (AML_RAW_DATA_BYTE,          REGION_SMBUS,       0),
/* REGISTER */                  OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* RELEASE */                   OP_TABLE_ENTRY (AML_RELEASE_OP,             0,                  0),
/* RESERVED_BYTES */            OP_TABLE_ENTRY (AML_RESERVEDFIELD_OP,       0,                  0),
/* RESET */                     OP_TABLE_ENTRY (AML_RESET_OP,               0,                  0),
/* RESOURCETEMPLATE */          OP_TABLE_ENTRY (AML_BUFFER_OP,              0,                  0),
/* RESOURCETYPE_CONSUMER */     OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* RESOURCETYPE_PRODUCER */     OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* RETURN */                    OP_TABLE_ENTRY (AML_RETURN_OP,              0,                  0),
/* SCOPE */                     OP_TABLE_ENTRY (AML_SCOPE_OP,               0,                  NODE_AML_PACKAGE),
/* SERIALIZERULE_NOTSERIAL */   OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* SERIALIZERULE_SERIAL */      OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* SHARETYPE_EXCLUSIVE */       OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* SHARETYPE_SHARED */          OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* SHIFTLEFT */                 OP_TABLE_ENTRY (AML_SHIFT_LEFT_OP,          0,                  0),
/* SHIFTRIGHT */                OP_TABLE_ENTRY (AML_SHIFT_RIGHT_OP,         0,                  0),
/* SIGNAL */                    OP_TABLE_ENTRY (AML_SIGNAL_OP,              0,                  0),
/* SIZEOF */                    OP_TABLE_ENTRY (AML_SIZE_OF_OP,             0,                  0),
/* SLEEP */                     OP_TABLE_ENTRY (AML_SLEEP_OP,               0,                  0),
/* STALL */                     OP_TABLE_ENTRY (AML_STALL_OP,               0,                  0),
/* STARTDEPENDENTFN */          OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* STARTDEPENDENTFN_NOPRI */    OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* STORE */                     OP_TABLE_ENTRY (AML_STORE_OP,               0,                  0),
/* STRING */                    OP_TABLE_ENTRY (AML_STRING_OP,              0,                  0),
/* STRING_LITERAL */            OP_TABLE_ENTRY (AML_STRING_OP,              0,                  0),
/* SUBTRACT */                  OP_TABLE_ENTRY (AML_SUBTRACT_OP,            0,                  0),
/* SWITCH */                    OP_TABLE_ENTRY (AML_DEFAULT_ARG_OP,         0,                  0),
/* THERMALZONE */               OP_TABLE_ENTRY (AML_THERMAL_ZONE_OP,        0,                  NODE_AML_PACKAGE),
/* TOBCD */                     OP_TABLE_ENTRY (AML_TO_BCD_OP,              0,                  0),
/* TOBUFFER */                  OP_TABLE_ENTRY (AML_BUFF_OP,                0,                  0),
/* TODECIMALSTRING */           OP_TABLE_ENTRY (AML_DEC_STR_OP,             0,                  0),
/* TOHEXSTRING */               OP_TABLE_ENTRY (AML_HEX_STR_OP,             0,                  0),
/* TOINTEGER */                 OP_TABLE_ENTRY (AML_INT_OP,                 0,                  0),
/* TRANSLATIONTYPE_DENSE */     OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* TRANSLATIONTYPE_SPARSE */    OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* TYPE_STATIC */               OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* TYPE_TRANSLATION */          OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* UNICODE */                   OP_TABLE_ENTRY (AML_BUFFER_OP,              0,                  0),
/* UNLOAD */                    OP_TABLE_ENTRY (AML_UNLOAD_OP,              0,                  0),
/* UPDATERULE_ONES */           OP_TABLE_ENTRY (AML_BYTE_OP,                UPDATE_WRITE_AS_ONES,   0),
/* UPDATERULE_PRESERVE */       OP_TABLE_ENTRY (AML_BYTE_OP,                UPDATE_PRESERVE,        0),
/* UPDATERULE_ZEROS */          OP_TABLE_ENTRY (AML_BYTE_OP,                UPDATE_WRITE_AS_ZEROS,  0),
/* VENDORLONG */                OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* VENDORSHORT */               OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* WAIT */                      OP_TABLE_ENTRY (AML_WAIT_OP,                0,                  0),
/* WHILE */                     OP_TABLE_ENTRY (AML_WHILE_OP,               0,                  NODE_AML_PACKAGE),
/* WORDBUSNUMBER */             OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* WORDCONST */                 OP_TABLE_ENTRY (AML_RAW_DATA_WORD,          0,                  0),
/* WORDIO */                    OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* XFERTYPE_8 */                OP_TABLE_ENTRY (AML_BYTE_OP,                0,                  0),
/* XFERTYPE_8_16 */             OP_TABLE_ENTRY (AML_BYTE_OP,                1,                  0),
/* XFERTYPE_16 */               OP_TABLE_ENTRY (AML_BYTE_OP,                2,                  0),
/* XOR */                       OP_TABLE_ENTRY (AML_BIT_XOR_OP,             0,                  0),
/* ZERO */                      OP_TABLE_ENTRY (AML_ZERO_OP,                0,                  0),

};



#define _COMPONENT          MISCELLANEOUS
        MODULE_NAME         ("aslmap")




#include "amlcode.h"
#include "acdispat.h"
#include "acparser.h"

/*
 * TBD:
 *
 * These are here temporarily until they are segregated out into separate
 * modules in the main subsystem source.
 */

/*******************************************************************************
 *
 * FUNCTION:    AcpiAmlValidateObjectType
 *
 * PARAMETERS:  Type            Object type to validate
 *
 * DESCRIPTION: Determine if a type is a valid ACPI object type
 *
 ******************************************************************************/

BOOLEAN
AcpiAmlValidateObjectType (
    ACPI_OBJECT_TYPE        Type)
{

    if ((Type > ACPI_TYPE_MAX && Type < INTERNAL_TYPE_BEGIN) ||
        (Type > INTERNAL_TYPE_MAX))
    {
        return (FALSE);
    }

    return (TRUE);
}



/*******************************************************************************
 *
 * FUNCTION:    AcpiDsMapOpcodeToDataType
 *
 * PARAMETERS:  Opcode          - AML opcode to map
 *              OutFlags        - Additional info about the opcode
 *
 * RETURN:      The ACPI type associated with the opcode
 *
 * DESCRIPTION: Convert a raw AML opcode to the associated ACPI data type,
 *              if any.  If the opcode returns a value as part of the
 *              intepreter execution, a flag is returned in OutFlags.
 *
 ******************************************************************************/

OBJECT_TYPE_INTERNAL
AcpiDsMapOpcodeToDataType (
    UINT16                  Opcode,
    UINT32                  *OutFlags)
{
    OBJECT_TYPE_INTERNAL    DataType = INTERNAL_TYPE_INVALID;
    ACPI_OPCODE_INFO        *OpInfo;
    UINT32                  Flags = 0;


    OpInfo = AcpiPsGetOpcodeInfo (Opcode);
    if (ACPI_GET_OP_TYPE (OpInfo) != ACPI_OP_TYPE_OPCODE)
    {
        /* Unknown opcode */

        DEBUG_PRINT (ACPI_ERROR,
            ("MapOpcode: Unknown AML opcode: %x\n",
            Opcode));

        return (DataType);
    }

    switch (ACPI_GET_OP_CLASS (OpInfo))
    {

    case OPTYPE_LITERAL:

        switch (Opcode)
        {
        case AML_BYTE_OP:
        case AML_WORD_OP:
        case AML_DWORD_OP:

            DataType = ACPI_TYPE_NUMBER;
            break;


        case AML_STRING_OP:

            DataType = ACPI_TYPE_STRING;
            break;

        case AML_NAMEPATH_OP:
            DataType = INTERNAL_TYPE_REFERENCE;
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR,
                ("MapOpcode: Unknown (type LITERAL) AML opcode: %x\n",
                Opcode));
            break;
        }
        break;


    case OPTYPE_DATA_TERM:

        switch (Opcode)
        {
        case AML_BUFFER_OP:

            DataType = ACPI_TYPE_BUFFER;
            break;

        case AML_PACKAGE_OP:

            DataType = ACPI_TYPE_PACKAGE;
            break;

        default:
            DEBUG_PRINT (ACPI_ERROR,
                ("MapOpcode: Unknown (type DATA_TERM) AML opcode: %x\n",
                Opcode));
            break;
        }
        break;


    case OPTYPE_CONSTANT:
    case OPTYPE_METHOD_ARGUMENT:
    case OPTYPE_LOCAL_VARIABLE:

        DataType = INTERNAL_TYPE_REFERENCE;
        break;


    case OPTYPE_MONADIC2:
    case OPTYPE_MONADIC2R:
    case OPTYPE_DYADIC2:
    case OPTYPE_DYADIC2R:
    case OPTYPE_DYADIC2S:
    case OPTYPE_INDEX:
    case OPTYPE_MATCH:
    case OPTYPE_RETURN:

        Flags = OP_HAS_RETURN_VALUE;
        DataType = ACPI_TYPE_ANY;
        break;

    case OPTYPE_METHOD_CALL:

        Flags = OP_HAS_RETURN_VALUE;
        DataType = ACPI_TYPE_METHOD;
        break;


    case OPTYPE_NAMED_OBJECT:

        DataType = AcpiDsMapNamedOpcodeToDataType (Opcode);
        break;


    case OPTYPE_DYADIC1:
    case OPTYPE_CONTROL:

        /* No mapping needed at this time */

        break;


    default:

        DEBUG_PRINT (ACPI_ERROR,
            ("MapOpcode: Unimplemented data type opcode: %x\n",
            Opcode));
        break;
    }

    /* Return flags to caller if requested */

    if (OutFlags)
    {
        *OutFlags = Flags;
    }

    return (DataType);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiDsMapNamedOpcodeToDataType
 *
 * PARAMETERS:  Opcode              - The Named AML opcode to map
 *
 * RETURN:      The ACPI type associated with the named opcode
 *
 * DESCRIPTION: Convert a raw Named AML opcode to the associated data type.
 *              Named opcodes are a subsystem of the AML opcodes.
 *
 ******************************************************************************/

OBJECT_TYPE_INTERNAL
AcpiDsMapNamedOpcodeToDataType (
    UINT16                  Opcode)
{
    OBJECT_TYPE_INTERNAL    DataType;


    /* Decode Opcode */

    switch (Opcode)
    {
    case AML_SCOPE_OP:
        DataType = INTERNAL_TYPE_SCOPE;
        break;

    case AML_DEVICE_OP:
        DataType = ACPI_TYPE_DEVICE;
        break;

    case AML_THERMAL_ZONE_OP:
        DataType = ACPI_TYPE_THERMAL;
        break;

    case AML_METHOD_OP:
        DataType = ACPI_TYPE_METHOD;
        break;

    case AML_POWER_RES_OP:
        DataType = ACPI_TYPE_POWER;
        break;

    case AML_PROCESSOR_OP:
        DataType = ACPI_TYPE_PROCESSOR;
        break;

    case AML_DEF_FIELD_OP:                          /* DefFieldOp */
        DataType = INTERNAL_TYPE_DEF_FIELD_DEFN;
        break;

    case AML_INDEX_FIELD_OP:                        /* IndexFieldOp */
        DataType = INTERNAL_TYPE_INDEX_FIELD_DEFN;
        break;

    case AML_BANK_FIELD_OP:                         /* BankFieldOp */
        DataType = INTERNAL_TYPE_BANK_FIELD_DEFN;
        break;

    case AML_NAMEDFIELD_OP:                         /* NO CASE IN ORIGINAL  */
        DataType = ACPI_TYPE_ANY;
        break;

    case AML_NAME_OP:                               /* NameOp - special code in original */
    case AML_NAMEPATH_OP:
        DataType = ACPI_TYPE_ANY;
        break;

    case AML_ALIAS_OP:
        DataType = INTERNAL_TYPE_ALIAS;
        break;

    case AML_MUTEX_OP:
        DataType = ACPI_TYPE_MUTEX;
        break;

    case AML_EVENT_OP:
        DataType = ACPI_TYPE_EVENT;
        break;

    case AML_REGION_OP:
        DataType = ACPI_TYPE_REGION;
        break;


    default:
        DataType = ACPI_TYPE_ANY;
        break;

    }

    return (DataType);
}



