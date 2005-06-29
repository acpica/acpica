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
#include <psopcode.h>



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
    INT32                   Opcode)
{
    ACPI_OP_INFO             *Op;
    INT32                   Hash;


    /* compute hash/index into the AcpiAmlOpIndex table */

    switch (Opcode >> 8)
    {
    case 0:
        Hash = Opcode;
        break;

    case AML_EXTOP:
        Hash = (Opcode + AML_EXTOP_HASH_OFFSET) & 0xff;
        break;

    /* This case is for the bogus opcodes LNOTEQUAL, LLESSEQUAL, LGREATEREQUAL */

    case AML_LNOT:
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
 *
 * DESCRIPTION: Opcode table.
 *              Each entry contains <opcode, type, name, operands>
 *              The name is a simple ascii string, the operand specifier is an 
 *              ascii string with one letter per operand.  The letter specifies 
 *              the operand type.
 *
 ******************************************************************************/


ACPI_OP_INFO        Gbl_AmlOpInfo[] =
{
/*           Opcode                     Opcode Type              Name               Args */
 
/*  00 */   {AML_ZEROOP,                OPTYPE_CONSTANT,        "ZeroOp",           NULL},
/*  01 */   {AML_ONEOP,                 OPTYPE_CONSTANT,        "OneOp",            NULL},
/*  02 */   {AML_ALIAS,                 OPTYPE_NAMED_OBJECT,    "Alias",            "nn"},
/*  03 */   {AML_NAME,                  OPTYPE_NAMED_OBJECT,    "Name",             "no"},
/*  04 */   {AML_BYTECONST,             OPTYPE_LITERAL,         "ByteConst",        "b"},
/*  05 */   {AML_WORDCONST,             OPTYPE_LITERAL,         "WordConst",        "w"},
/*  06 */   {AML_DWORDCONST,            OPTYPE_LITERAL,         "DwordConst",       "d"},
/*  07 */   {AML_STRING,                OPTYPE_LITERAL,         "String",           "A"},
/*  08 */   {AML_SCOPE,                 OPTYPE_NAMED_OBJECT,    "Scope",            "pnT"},
/*  09 */   {AML_BUFFER,                OPTYPE_DATA_TERM,       "Buffer",           "ptB"},
/*  0A */   {AML_PACKAGE,               OPTYPE_DATA_TERM,       "Package",          "pbO"},
/*  0B */   {AML_METHOD,                OPTYPE_NAMED_OBJECT,    "Method",           "pnbT"},
/*  0C */   {AML_LOCAL0,                OPTYPE_LOCAL_VARIABLE,  "Local0",           NULL},
/*  0D */   {AML_LOCAL1,                OPTYPE_LOCAL_VARIABLE,  "Local1",           NULL},
/*  0E */   {AML_LOCAL2,                OPTYPE_LOCAL_VARIABLE,  "Local2",           NULL},
/*  0F */   {AML_LOCAL3,                OPTYPE_LOCAL_VARIABLE,  "Local3",           NULL},
/*  10 */   {AML_LOCAL4,                OPTYPE_LOCAL_VARIABLE,  "Local4",           NULL},
/*  11 */   {AML_LOCAL5,                OPTYPE_LOCAL_VARIABLE,  "Local5",           NULL},
/*  12 */   {AML_LOCAL6,                OPTYPE_LOCAL_VARIABLE,  "Local6",           NULL},
/*  13 */   {AML_LOCAL7,                OPTYPE_LOCAL_VARIABLE,  "Local7",           NULL},
/*  14 */   {AML_ARG0,                  OPTYPE_METHOD_ARGUMENT, "Arg0",             NULL},
/*  15 */   {AML_ARG1,                  OPTYPE_METHOD_ARGUMENT, "Arg1",             NULL},
/*  16 */   {AML_ARG2,                  OPTYPE_METHOD_ARGUMENT, "Arg2",             NULL},
/*  17 */   {AML_ARG3,                  OPTYPE_METHOD_ARGUMENT, "Arg3",             NULL},
/*  18 */   {AML_ARG4,                  OPTYPE_METHOD_ARGUMENT, "Arg4",             NULL},
/*  19 */   {AML_ARG5,                  OPTYPE_METHOD_ARGUMENT, "Arg5",             NULL},
/*  1A */   {AML_ARG6,                  OPTYPE_METHOD_ARGUMENT, "Arg6",             NULL},
/*  1B */   {AML_STORE,                 OPTYPE_MONADIC2R,       "Store",            "ts"},
/*  1C */   {AML_REFOF,                 OPTYPE_MONADIC2,        "RefOf",            "s"},
/*  1D */   {AML_ADD,                   OPTYPE_DYADIC2R,        "Add",              "ttl"},
/*  1E */   {AML_CONCAT,                OPTYPE_DYADIC2R,        "Concat",           "ttl"},
/*  1F */   {AML_SUBTRACT,              OPTYPE_DYADIC2R,        "Subtract",         "ttl"},
/*  20 */   {AML_INCREMENT,             OPTYPE_MONADIC2,        "Increment",        "s"},
/*  21 */   {AML_DECREMENT,             OPTYPE_MONADIC2,        "Decrement",        "s"},
/*  22 */   {AML_MULTIPLY,              OPTYPE_DYADIC2R,        "Multiply",         "ttl"},
/*  23 */   {AML_DIVIDE,                OPTYPE_DYADIC2R,        "Divide",           "ttll"},
/*  24 */   {AML_SHIFTLEFT,             OPTYPE_DYADIC2R,        "ShiftLeft",        "ttl"},
/*  25 */   {AML_SHIFTRIGHT,            OPTYPE_DYADIC2R,        "ShiftRight",       "ttl"},
/*  26 */   {AML_AND,                   OPTYPE_DYADIC2R,        "And",              "ttl"},
/*  27 */   {AML_NAND,                  OPTYPE_DYADIC2R,        "NAnd",             "ttl"},
/*  28 */   {AML_OR,                    OPTYPE_DYADIC2R,        "Or",               "ttl"},
/*  29 */   {AML_NOR,                   OPTYPE_DYADIC2R,        "NOr",              "ttl"},
/*  2A */   {AML_XOR,                   OPTYPE_DYADIC2R,        "XOr",              "ttl"},
/*  2B */   {AML_NOT,                   OPTYPE_MONADIC2R,       "Not",              "tl"},
/*  2C */   {AML_FINDSETLEFTBIT,        OPTYPE_MONADIC2R,       "FindSetLeftBit",   "tl"},
/*  2D */   {AML_FINDSETRIGHTBIT,       OPTYPE_MONADIC2R,       "FindSetRightBit",  "tl"},
/*  2E */   {AML_DEREFOF,               OPTYPE_MONADIC2,        "DerefOf",          "t"},
/*  2F */   {AML_NOTIFY,                OPTYPE_DYADIC1,         "Notify",           "st"},
/*  30 */   {AML_SIZEOF,                OPTYPE_MONADIC2,        "SizeOf",           "s"},
/*  31 */   {AML_INDEX,                 OPTYPE_INDEX,           "Index",            "ttl"},
/*  32 */   {AML_MATCH,                 OPTYPE_MATCH,           "Match",            "tbtbtt"},
/*  33 */   {AML_CREATEDWORDFIELD,      OPTYPE_CREATE_FIELD,    "CreateDWordField", "ttn"},
/*  34 */   {AML_CREATEWORDFIELD,       OPTYPE_CREATE_FIELD,    "CreateWordField",  "ttn"},
/*  35 */   {AML_CREATEBYTEFIELD,       OPTYPE_CREATE_FIELD,    "CreateByteField",  "ttn"},
/*  36 */   {AML_CREATEBITFIELD,        OPTYPE_CREATE_FIELD,    "CreateBitField",   "ttn"},
/*  37 */   {AML_OBJECTTYPE,            OPTYPE_MONADIC2,        "ObjectType",       "s"},
/*  38 */   {AML_LAND,                  OPTYPE_DYADIC2,         "LAnd",             "tt"},
/*  39 */   {AML_LOR,                   OPTYPE_DYADIC2,         "LOr",              "tt"},
/*  3A */   {AML_LNOT,                  OPTYPE_MONADIC2,        "LNot",             "t"},
/*  3B */   {AML_LEQUAL,                OPTYPE_DYADIC2,         "LEqual",           "tt"},
/*  3C */   {AML_LGREATER,              OPTYPE_DYADIC2,         "LGreater",         "tt"},
/*  3D */   {AML_LLESS,                 OPTYPE_DYADIC2,         "LLess",            "tt"},
/*  3E */   {AML_IF,                    OPTYPE_CONTROL,         "If",               "ptT"},
/*  3F */   {AML_ELSE,                  OPTYPE_CONTROL,         "Else",             "pT"},
/*  40 */   {AML_WHILE,                 OPTYPE_CONTROL,         "While",            "ptT"},
/*  41 */   {AML_NOOP,                  OPTYPE_CONTROL,         "Noop",             NULL},
/*  42 */   {AML_RETURN,                OPTYPE_CONTROL,         "Return",           "t"},
/*  43 */   {AML_BREAK,                 OPTYPE_CONTROL,         "Break",            NULL},
/*  44 */   {AML_BREAKPOINT,            OPTYPE_CONTROL,         "BreakPoint",       NULL},
/*  45 */   {AML_ONESOP,                OPTYPE_CONSTANT,        "OnesOp",           NULL},
/*  46 */   {AML_MUTEX,                 OPTYPE_NAMED_OBJECT,    "Mutex",            "nb"},
/*  47 */   {AML_EVENT,                 OPTYPE_NAMED_OBJECT,    "Event",            "n"},
/*  48 */   {AML_CONDREFOF,             OPTYPE_MONADIC2R,       "CondRefOf",        "ss"},
/*  49 */   {AML_CREATEFIELD,           OPTYPE_CREATE_FIELD,    "CreateField",      "tttn"},
/*  4A */   {AML_LOAD,                  OPTYPE_RECONFIGURATION, "Load",             "ns"},
/*  4B */   {AML_STALL,                 OPTYPE_MONADIC1,        "Stall",            "t"},
/*  4C */   {AML_SLEEP,                 OPTYPE_MONADIC1,        "Sleep",            "t"},
/*  4D */   {AML_ACQUIRE,               OPTYPE_DYADIC2S,        "Acquire",          "sw"},
/*  4E */   {AML_SIGNAL,                OPTYPE_MONADIC1,        "Signal",           "s"},
/*  4F */   {AML_WAIT,                  OPTYPE_DYADIC2S,        "Wait",             "st"},
/*  50 */   {AML_RESET,                 OPTYPE_MONADIC1,        "Reset",            "s"},
/*  51 */   {AML_RELEASE,               OPTYPE_MONADIC1,        "Release",          "s"},
/*  52 */   {AML_FROMBCD,               OPTYPE_MONADIC2R,       "FromBCD",          "tl"},
/*  53 */   {AML_TOBCD,                 OPTYPE_MONADIC2R,       "ToBCD",            "tl"},
/*  54 */   {AML_UNLOAD,                OPTYPE_RECONFIGURATION, "Unload",           "s"},
/*  55 */   {AML_REVISION,              OPTYPE_CONSTANT,        "Revision",         NULL},
/*  56 */   {AML_DEBUG,                 OPTYPE_CONSTANT,        "Debug",            NULL},
/*  57 */   {AML_FATAL,                 OPTYPE_FATAL,           "Fatal",            "bdt"},
/*  58 */   {AML_OPREGION,              OPTYPE_NAMED_OBJECT,    "OpRegion",         "nbtt"},
/*  59 */   {AML_FIELD,                 OPTYPE_NAMED_OBJECT,    "Field",            "pnbF"},
/*  5A */   {AML_DEVICE,                OPTYPE_NAMED_OBJECT,    "Device",           "pnP"},
/*  5B */   {AML_PROCESSOR,             OPTYPE_NAMED_OBJECT,    "Processor",        "pnbdbP"},
/*  5C */   {AML_POWERRES,              OPTYPE_NAMED_OBJECT,    "PowerRes",         "pnbwP"},
/*  5D */   {AML_THERMALZONE,           OPTYPE_NAMED_OBJECT,    "ThermalZone",      "pnP"},
/*  5E */   {AML_INDEXFIELD,            OPTYPE_NAMED_OBJECT,    "IndexField",       "pnnbF"},
/*  5F */   {AML_BANKFIELD,             OPTYPE_NAMED_OBJECT,    "BankField",        "pnntbF"},
/*  60 */   {AML_LNOTEQUAL,             OPTYPE_BOGUS,           "LNotEqual",        "tt"},
/*  61 */   {AML_LLESSEQUAL,            OPTYPE_BOGUS,           "LLessEqual",       "tt"},
/*  62 */   {AML_LGREATEREQUAL,         OPTYPE_BOGUS,           "LGreaterEqual",    "tt"},
/*  63 */   {AML_NAMEPATH,              OPTYPE_LITERAL,         "NamePath",         "n"},
/*  64 */   {AML_METHODCALL,            OPTYPE_METHOD_CALL,     "MethodCall",       "n"},
/*  65 */   {AML_BYTELIST,              OPTYPE_LITERAL,         "ByteList",         "n"},
/*  66 */   {AML_RESERVEDFIELD,         OPTYPE_BOGUS,           "ReservedField",    "n"},
/*  67 */   {AML_NAMEDFIELD,            OPTYPE_BOGUS,           "NamedField",       "n"},
/*  68 */   {AML_ACCESSFIELD,           OPTYPE_BOGUS,           "AccessField",      "n"},
/*  69 */   {AML_STATICSTRING,          OPTYPE_BOGUS,           "StaticString",     "n"},
/*  6A */   {0,                         OPTYPE_BOGUS,           "UNKNOWN_OP!",      "n"},
            {0,                         0,                      NULL,               NULL}
};

#define _UNK                0x6A
#define _UNKOWN_OPCODE      0x02    /* An example unknown opcode */

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
