/******************************************************************************
 * 
 * Module Name: psopcode - Parser opcode information table
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
#include <amlcode.h>



#define _COMPONENT          PARSER
        MODULE_NAME         ("psopcode");


/*******************************************************************************
 *
 * FUNCTION:    PsGetOpcodeInfo
 *
 * PARAMETERS:  Opcode              - The AML opcode
 *
 * RETURN:      A pointer to the info about the opcode.  NULL if the opcode was
 *              not found in the table.
 *
 * DESCRIPTION: Find AML opcode description based on the opcode
 *
 ******************************************************************************/

ACPI_OP_INFO *
PsGetOpcodeInfo (
    UINT16                  Opcode)
{
    ACPI_OP_INFO             *Op;
    INT32                   Hash;


    /* compute hash/index into the AcpiAmlOpIndex table */

    switch (Opcode >> 8)
    {
    case 0:

        /* Simple (8-bit) opcode */

        Hash = Opcode;
        break;


    case AML_EXTOP:

        /* Extended (16-bit, prefix+opcode) opcode */

        Hash = (Opcode + AML_EXTOP_HASH_OFFSET) & 0xff;
        break;



    case AML_LNotOp:

        /* This case is for the bogus opcodes LNOTEQUAL, LLESSEQUAL, LGREATEREQUAL */

        Hash = (Opcode + AML_LNOT_HASH_OFFSET) & 0xff;
        break;


    default:

        DEBUG_PRINT (ACPI_ERROR, ("PsGetOpcodeInfo: Unknown extended Opcode=%X\n",
                Opcode));
    
        return NULL;
    }


    /* Get the Op info pointer for this opcode */

    Op = &Gbl_AmlOpInfo [(INT32) Gbl_AmlOpInfoIndex [Hash]];


    /* If the returned opcode matches, we have a valid opcode */

    if (Op->Opcode == Opcode)
    {
        return Op;
    }

    /* Otherwise, the opcode is an ASCII char or other non-opcode value */

    return NULL;
}


/*******************************************************************************
 *
 * FUNCTION:    PsGetOpcodeName
 *
 * PARAMETERS:  Opcode              - The AML opcode
 *
 * RETURN:      A pointer to the name of the opcode (ASCII String)
 *              Note: Never returns NULL.
 *
 * DESCRIPTION: Translate an opcode into a human-readable string
 *
 ******************************************************************************/

char *
PsGetOpcodeName (
    UINT16                  Opcode)
{
    ACPI_OP_INFO             *Op;


    Op = PsGetOpcodeInfo (Opcode);

    if (!Op)
    {
        return "*ERROR*";
    }

    DEBUG_EXEC (return Op->Name);
    NORMAL_EXEC (return "AE_NOT_CONFIGURED");
}


/*******************************************************************************
 *
 * NAME:        Gbl_AmlOpInfo
 *
 * DESCRIPTION: Opcode table. Each entry contains <opcode, type, name, operands>
 *              The name is a simple ascii string, the operand specifier is an 
 *              ascii string with one letter per operand.  The letter specifies 
 *              the operand type.
 *
 ******************************************************************************/


/*
 * Flags byte: 0-4 (5 bits) = Opcode Type
 *             5   (1 bit)  = Has arguments flag
 *             6-7 (2 bits) = Reserved
 */
#define AML_NO_ARGS         0
#define AML_HAS_ARGS        OP_INFO_HAS_ARGS


ACPI_OP_INFO        Gbl_AmlOpInfo[] =
{
/*                          Opcode                 Opcode Type           Has Arguments? Child  Name               Args */
 
/*  00 */   OP_INFO_ENTRY (AML_ZeroOp,            OPTYPE_CONSTANT|        AML_NO_ARGS|    0,  "ZeroOp",           NULL),
/*  01 */   OP_INFO_ENTRY (AML_OneOp,             OPTYPE_CONSTANT|        AML_NO_ARGS|    0,  "OneOp",            NULL),
/*  02 */   OP_INFO_ENTRY (AML_AliasOp,           OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Alias",            "nn"),
/*  03 */   OP_INFO_ENTRY (AML_NameOp,            OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Name",             "no"),
/*  04 */   OP_INFO_ENTRY (AML_ByteOp,            OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "ByteConst",        "b"),
/*  05 */   OP_INFO_ENTRY (AML_WordOp,            OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "WordConst",        "w"),
/*  06 */   OP_INFO_ENTRY (AML_DWordOp,           OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "DwordConst",       "d"),
/*  07 */   OP_INFO_ENTRY (AML_StringOp,          OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "String",           "A"),
/*  08 */   OP_INFO_ENTRY (AML_ScopeOp,           OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Scope",            "pnT"),
/*  09 */   OP_INFO_ENTRY (AML_BufferOp,          OPTYPE_DATA_TERM|       AML_HAS_ARGS|   0,  "Buffer",           "ptB"),
/*  0A */   OP_INFO_ENTRY (AML_PackageOp,         OPTYPE_DATA_TERM|       AML_HAS_ARGS|   0,  "Package",          "pbO"),
/*  0B */   OP_INFO_ENTRY (AML_MethodOp,          OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Method",           "pnbT"),
/*  0C */   OP_INFO_ENTRY (AML_Local0,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local0",           NULL),
/*  0D */   OP_INFO_ENTRY (AML_Local1,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local1",           NULL),
/*  0E */   OP_INFO_ENTRY (AML_Local2,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local2",           NULL),
/*  0F */   OP_INFO_ENTRY (AML_Local3,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local3",           NULL),
/*  10 */   OP_INFO_ENTRY (AML_Local4,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local4",           NULL),
/*  11 */   OP_INFO_ENTRY (AML_Local5,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local5",           NULL),
/*  12 */   OP_INFO_ENTRY (AML_Local6,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local6",           NULL),
/*  13 */   OP_INFO_ENTRY (AML_Local7,            OPTYPE_LOCAL_VARIABLE|  AML_NO_ARGS|    0,  "Local7",           NULL),
/*  14 */   OP_INFO_ENTRY (AML_Arg0,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg0",             NULL),
/*  15 */   OP_INFO_ENTRY (AML_Arg1,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg1",             NULL),
/*  16 */   OP_INFO_ENTRY (AML_Arg2,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg2",             NULL),
/*  17 */   OP_INFO_ENTRY (AML_Arg3,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg3",             NULL),
/*  18 */   OP_INFO_ENTRY (AML_Arg4,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg4",             NULL),
/*  19 */   OP_INFO_ENTRY (AML_Arg5,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg5",             NULL),
/*  1A */   OP_INFO_ENTRY (AML_Arg6,              OPTYPE_METHOD_ARGUMENT| AML_NO_ARGS|    0,  "Arg6",             NULL),
/*  1B */   OP_INFO_ENTRY (AML_StoreOp,           OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "Store",            "ts"),
/*  1C */   OP_INFO_ENTRY (AML_RefOfOp,           OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "RefOf",            "s"),
/*  1D */   OP_INFO_ENTRY (AML_AddOp,             OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Add",              "ttl"),
/*  1E */   OP_INFO_ENTRY (AML_ConcatOp,          OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Concat",           "ttl"),
/*  1F */   OP_INFO_ENTRY (AML_SubtractOp,        OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Subtract",         "ttl"),
/*  20 */   OP_INFO_ENTRY (AML_IncrementOp,       OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "Increment",        "s"),
/*  21 */   OP_INFO_ENTRY (AML_DecrementOp,       OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "Decrement",        "s"),
/*  22 */   OP_INFO_ENTRY (AML_MultiplyOp,        OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Multiply",         "ttl"),
/*  23 */   OP_INFO_ENTRY (AML_DivideOp,          OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Divide",           "ttll"),
/*  24 */   OP_INFO_ENTRY (AML_ShiftLeftOp,       OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "ShiftLeft",        "ttl"),
/*  25 */   OP_INFO_ENTRY (AML_ShiftRightOp,      OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "ShiftRight",       "ttl"),
/*  26 */   OP_INFO_ENTRY (AML_BitAndOp,          OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "And",              "ttl"),
/*  27 */   OP_INFO_ENTRY (AML_BitNandOp,         OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "NAnd",             "ttl"),
/*  28 */   OP_INFO_ENTRY (AML_BitOrOp,           OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "Or",               "ttl"),
/*  29 */   OP_INFO_ENTRY (AML_BitNorOp,          OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "NOr",              "ttl"),
/*  2A */   OP_INFO_ENTRY (AML_BitXorOp,          OPTYPE_DYADIC2R|        AML_HAS_ARGS|   0,  "XOr",              "ttl"),
/*  2B */   OP_INFO_ENTRY (AML_BitNotOp,          OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "Not",              "tl"),
/*  2C */   OP_INFO_ENTRY (AML_FindSetLeftBitOp,  OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "FindSetLeftBit",   "tl"),
/*  2D */   OP_INFO_ENTRY (AML_FindSetRightBitOp, OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "FindSetRightBit",  "tl"),
/*  2E */   OP_INFO_ENTRY (AML_DerefOfOp,         OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "DerefOf",          "t"),
/*  2F */   OP_INFO_ENTRY (AML_NotifyOp,          OPTYPE_DYADIC1|         AML_HAS_ARGS|   0,  "Notify",           "st"),
/*  30 */   OP_INFO_ENTRY (AML_SizeOfOp,          OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "SizeOf",           "s"),
/*  31 */   OP_INFO_ENTRY (AML_IndexOp,           OPTYPE_INDEX|           AML_HAS_ARGS|   0,  "Index",            "ttl"),
/*  32 */   OP_INFO_ENTRY (AML_MatchOp,           OPTYPE_MATCH|           AML_HAS_ARGS|   0,  "Match",            "tbtbtt"),
/*  33 */   OP_INFO_ENTRY (AML_DWordFieldOp,      OPTYPE_CREATE_FIELD|    AML_HAS_ARGS|   0,  "CreateDWordField", "ttn"),
/*  34 */   OP_INFO_ENTRY (AML_WordFieldOp,       OPTYPE_CREATE_FIELD|    AML_HAS_ARGS|   0,  "CreateWordField",  "ttn"),
/*  35 */   OP_INFO_ENTRY (AML_ByteFieldOp,       OPTYPE_CREATE_FIELD|    AML_HAS_ARGS|   0,  "CreateByteField",  "ttn"),
/*  36 */   OP_INFO_ENTRY (AML_BitFieldOp,        OPTYPE_CREATE_FIELD|    AML_HAS_ARGS|   0,  "CreateBitField",   "ttn"),
/*  37 */   OP_INFO_ENTRY (AML_TypeOp,            OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "ObjectType",       "s"),
/*  38 */   OP_INFO_ENTRY (AML_LAndOp,            OPTYPE_DYADIC2|         AML_HAS_ARGS|   0,  "LAnd",             "tt"),
/*  39 */   OP_INFO_ENTRY (AML_LOrOp,             OPTYPE_DYADIC2|         AML_HAS_ARGS|   0,  "LOr",              "tt"),
/*  3A */   OP_INFO_ENTRY (AML_LNotOp,            OPTYPE_MONADIC2|        AML_HAS_ARGS|   0,  "LNot",             "t"),
/*  3B */   OP_INFO_ENTRY (AML_LEqualOp,          OPTYPE_DYADIC2|         AML_HAS_ARGS|   0,  "LEqual",           "tt"),
/*  3C */   OP_INFO_ENTRY (AML_LGreaterOp,        OPTYPE_DYADIC2|         AML_HAS_ARGS|   0,  "LGreater",         "tt"),
/*  3D */   OP_INFO_ENTRY (AML_LLessOp,           OPTYPE_DYADIC2|         AML_HAS_ARGS|   0,  "LLess",            "tt"),
/*  3E */   OP_INFO_ENTRY (AML_IfOp,              OPTYPE_CONTROL|         AML_HAS_ARGS|   0,  "If",               "ptT"),
/*  3F */   OP_INFO_ENTRY (AML_ElseOp,            OPTYPE_CONTROL|         AML_HAS_ARGS|   0,  "Else",             "pT"),
/*  40 */   OP_INFO_ENTRY (AML_WhileOp,           OPTYPE_CONTROL|         AML_HAS_ARGS|   0,  "While",            "ptT"),
/*  41 */   OP_INFO_ENTRY (AML_NoopCode,          OPTYPE_CONTROL|         AML_NO_ARGS|    0,  "Noop",             NULL),
/*  42 */   OP_INFO_ENTRY (AML_ReturnOp,          OPTYPE_CONTROL|         AML_HAS_ARGS|   0,  "Return",           "t"),
/*  43 */   OP_INFO_ENTRY (AML_BreakOp,           OPTYPE_CONTROL|         AML_NO_ARGS|    0,  "Break",            NULL),
/*  44 */   OP_INFO_ENTRY (AML_BreakPointOp,      OPTYPE_CONTROL|         AML_NO_ARGS|    0,  "BreakPoint",       NULL),
/*  45 */   OP_INFO_ENTRY (AML_OnesOp,            OPTYPE_CONSTANT|        AML_NO_ARGS|    0,  "OnesOp",           NULL),

/* Prefixed opcodes (Two-byte opcodes with a prefix op) */
    
/*  46 */   OP_INFO_ENTRY (AML_MutexOp,           OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Mutex",            "nb"),
/*  47 */   OP_INFO_ENTRY (AML_EventOp,           OPTYPE_NAMED_OBJECT|    AML_NO_ARGS|    0,  "Event",            "n"),
/*  48 */   OP_INFO_ENTRY (AML_CondRefOfOp,       OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "CondRefOf",        "ss"),
/*  49 */   OP_INFO_ENTRY (AML_CreateFieldOp,     OPTYPE_CREATE_FIELD|    AML_HAS_ARGS|   0,  "CreateField",      "tttn"),
/*  4A */   OP_INFO_ENTRY (AML_LoadOp,            OPTYPE_RECONFIGURATION| AML_HAS_ARGS|   0,  "Load",             "ns"),
/*  4B */   OP_INFO_ENTRY (AML_StallOp,           OPTYPE_MONADIC1|        AML_HAS_ARGS|   0,  "Stall",            "t"),
/*  4C */   OP_INFO_ENTRY (AML_SleepOp,           OPTYPE_MONADIC1|        AML_HAS_ARGS|   0,  "Sleep",            "t"),
/*  4D */   OP_INFO_ENTRY (AML_AcquireOp,         OPTYPE_DYADIC2S|        AML_HAS_ARGS|   0,  "Acquire",          "sw"),
/*  4E */   OP_INFO_ENTRY (AML_SignalOp,          OPTYPE_MONADIC1|        AML_HAS_ARGS|   0,  "Signal",           "s"),
/*  4F */   OP_INFO_ENTRY (AML_WaitOp,            OPTYPE_DYADIC2S|        AML_HAS_ARGS|   0,  "Wait",             "st"),
/*  50 */   OP_INFO_ENTRY (AML_ResetOp,           OPTYPE_MONADIC1|        AML_HAS_ARGS|   0,  "Reset",            "s"),
/*  51 */   OP_INFO_ENTRY (AML_ReleaseOp,         OPTYPE_MONADIC1|        AML_HAS_ARGS|   0,  "Release",          "s"),
/*  52 */   OP_INFO_ENTRY (AML_FromBCDOp,         OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "FromBCD",          "tl"),
/*  53 */   OP_INFO_ENTRY (AML_ToBCDOp,           OPTYPE_MONADIC2R|       AML_HAS_ARGS|   0,  "ToBCD",            "tl"),
/*  54 */   OP_INFO_ENTRY (AML_UnLoadOp,          OPTYPE_RECONFIGURATION| AML_HAS_ARGS|   0,  "Unload",           "s"),
/*  55 */   OP_INFO_ENTRY (AML_RevisionOp,        OPTYPE_CONSTANT|        AML_NO_ARGS|    0,  "Revision",         NULL),
/*  56 */   OP_INFO_ENTRY (AML_DebugOp,           OPTYPE_CONSTANT|        AML_NO_ARGS|    0,  "Debug",            NULL),
/*  57 */   OP_INFO_ENTRY (AML_FatalOp,           OPTYPE_FATAL|           AML_HAS_ARGS|   0,  "Fatal",            "bdt"),
/*  58 */   OP_INFO_ENTRY (AML_RegionOp,          OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "OpRegion",         "nbtt"),
/*  59 */   OP_INFO_ENTRY (AML_DefFieldOp,        OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Field",            "pnbF"),
/*  5A */   OP_INFO_ENTRY (AML_DeviceOp,          OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Device",           "pnP"),
/*  5B */   OP_INFO_ENTRY (AML_ProcessorOp,       OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "Processor",        "pnbdbP"),
/*  5C */   OP_INFO_ENTRY (AML_PowerResOp,        OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "PowerRes",         "pnbwP"),
/*  5D */   OP_INFO_ENTRY (AML_ThermalZoneOp,     OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "ThermalZone",      "pnP"),
/*  5E */   OP_INFO_ENTRY (AML_IndexFieldOp,      OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "IndexField",       "pnnbF"),
/*  5F */   OP_INFO_ENTRY (AML_BankFieldOp,       OPTYPE_NAMED_OBJECT|    AML_HAS_ARGS|   0,  "BankField",        "pnntbF"),

/* Internal opcodes that map to invalid AML opcodes */

/*  60 */   OP_INFO_ENTRY (AML_LNOTEQUAL,         OPTYPE_BOGUS|           AML_HAS_ARGS|   0,  "LNotEqual",        "tt"),
/*  61 */   OP_INFO_ENTRY (AML_LLESSEQUAL,        OPTYPE_BOGUS|           AML_HAS_ARGS|   0,  "LLessEqual",       "tt"),
/*  62 */   OP_INFO_ENTRY (AML_LGREATEREQUAL,     OPTYPE_BOGUS|           AML_HAS_ARGS|   0,  "LGreaterEqual",    "tt"),
/*  63 */   OP_INFO_ENTRY (AML_NAMEPATH,          OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "NamePath",         "n"),
/*  64 */   OP_INFO_ENTRY (AML_METHODCALL,        OPTYPE_METHOD_CALL|     AML_HAS_ARGS|   0,  "MethodCall",       "n"),
/*  65 */   OP_INFO_ENTRY (AML_BYTELIST,          OPTYPE_LITERAL|         AML_NO_ARGS|    0,  "ByteList",         "n"),
/*  66 */   OP_INFO_ENTRY (AML_RESERVEDFIELD,     OPTYPE_BOGUS|           AML_NO_ARGS|    0,  "ReservedField",    "n"),
/*  67 */   OP_INFO_ENTRY (AML_NAMEDFIELD,        OPTYPE_BOGUS|           AML_NO_ARGS|    0,  "NamedField",       "n"),
/*  68 */   OP_INFO_ENTRY (AML_ACCESSFIELD,       OPTYPE_BOGUS|           AML_NO_ARGS|    0,  "AccessField",      "n"),
/*  69 */   OP_INFO_ENTRY (AML_STATICSTRING,      OPTYPE_BOGUS|           AML_NO_ARGS|    0,  "StaticString",     "n"),
/*  6A */   OP_INFO_ENTRY (0,                     OPTYPE_BOGUS|           AML_HAS_ARGS|   0,  "UNKNOWN_OP!",      "n"),
            OP_INFO_ENTRY (0,                     0|                      AML_HAS_ARGS|   0,  NULL,               NULL)
};

#define _UNK                0x6A
#define _UNKNOWN_OPCODE     0x02    /* An example unknown opcode */

/*
 * This table is directly indexed by the opcodes, and returns an
 * index into the table above
 */

UINT8 Gbl_AmlOpInfoIndex[256] =
{
/*              0     1     2     3     4     5     6     7  */
/* 0x00 */    0x00, 0x01, _UNK, _UNK, _UNK, _UNK, 0x02, _UNK,
/* 0x08 */    0x03, _UNK, 0x04, 0x05, 0x06, 0x07, _UNK, _UNK,
/* 0x10 */    0x08, 0x09, 0x0a, _UNK, 0x0b, _UNK, _UNK, 0x46,
/* 0x18 */    0x47, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x20 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x28 */    0x48, 0x49, _UNK, _UNK, _UNK, 0x63, _UNK, _UNK,
/* 0x30 */    0x67, 0x66, 0x68, 0x65, 0x69, 0x64, 0x4a, 0x4b,
/* 0x38 */    0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53,
/* 0x40 */    0x54, _UNK, _UNK, _UNK, _UNK, _UNK, 0x55, 0x56,
/* 0x48 */    0x57, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x50 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x58 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x60 */    0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13,
/* 0x68 */    0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, _UNK,
/* 0x70 */    0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22,
/* 0x78 */    0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a,
/* 0x80 */    0x2b, 0x2c, 0x2d, 0x2e, _UNK, _UNK, 0x2f, 0x30,
/* 0x88 */    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, _UNK,
/* 0x90 */    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x58, 0x59,
/* 0x98 */    0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, _UNK, _UNK,
/* 0xA0 */    0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x60, 0x61,
/* 0xA8 */    0x62, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xB0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xB8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xC0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xC8 */    _UNK, _UNK, _UNK, _UNK, 0x44, _UNK, _UNK, _UNK,
/* 0xD0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xD8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xE0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xE8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xF0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xF8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, 0x45,
};
