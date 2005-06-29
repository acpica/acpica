
%{
/******************************************************************************
 *
 * Module Name: aslcompiler.y - Bison input file (ASL grammar and actions)
 *              $Revision: 1.43 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, 2001, Intel Corp.
 * All rights reserved.
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

#define YYDEBUG 1
#define YYERROR_VERBOSE 1

/*
 * State stack - compiler will fault if it overflows.   (Default was 200)
 */
#define YYINITDEPTH 600

#include "aslcompiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acpi.h"

#define _COMPONENT          COMPILER
        MODULE_NAME         ("aslparse")


/*
 * Next statement is important - this makes everything public so that
 * we can access some of the parser tables from other modules
 */
#define static
#undef alloca
#define alloca      AslLocalAllocate
#define YYERROR_VERBOSE     1

void *
AslLocalAllocate (unsigned int Size);

/*
 * The windows version of bison defines this incorrectly as "32768" (Not negative).
 * Using a custom (edited binary) version of bison that defines YYFLAG as YYFBAD
 * instead (#define YYFBAD      32768), so we can define it correctly here.
 *
 * The problem is that if YYFLAG is positive, the extended syntax error messages
 * are disabled.
 */

#define YYFLAG              -32768


%}


/*
 * Declare the type of values in the grammar
 */

%union {
    UINT64          i;
    char            *s;
    ASL_PARSE_NODE  *n;
}

/*
 * Token types: These are returned by the lexer
 */

%token <i> ACCESSAS
%token <i> ACCESSATTRIB_BLOCK
%token <i> ACCESSATTRIB_BYTE
%token <i> ACCESSATTRIB_CALL
%token <i> ACCESSATTRIB_QUICK
%token <i> ACCESSATTRIB_SND_RCV
%token <i> ACCESSATTRIB_WORD
%token <i> ACCESSTYPE_ANY
%token <i> ACCESSTYPE_BUF
%token <i> ACCESSTYPE_BYTE
%token <i> ACCESSTYPE_DWORD
%token <i> ACCESSTYPE_QWORD
%token <i> ACCESSTYPE_WORD
%token <i> ACQUIRE
%token <i> ADD
%token <i> ADDRESSSPACE_FFIXEDHW
%token <i> ADDRESSTYPE_ACPI
%token <i> ADDRESSTYPE_MEMORY
%token <i> ADDRESSTYPE_NVS
%token <i> ADDRESSTYPE_RESERVED
%token <i> ALIAS
%token <i> AND
%token <i> ARG0
%token <i> ARG1
%token <i> ARG2
%token <i> ARG3
%token <i> ARG4
%token <i> ARG5
%token <i> ARG6
%token <i> BANKFIELD
%token <i> BREAK
%token <i> BREAKPOINT
%token <i> BUFFER
%token <i> BUSMASTERTYPE_MASTER
%token <i> BUSMASTERTYPE_NOTMASTER
%token <i> BYTECONST
%token <i> CASE
%token <i> CONCATENATE
%token <i> CONCATENATERESTEMPLATE
%token <i> CONDREFOF
%token <i> CONTINUE
%token <i> COPYOBJECT
%token <i> CREATEBITFIELD
%token <i> CREATEBYTEFIELD
%token <i> CREATEDWORDFIELD
%token <i> CREATEFIELD
%token <i> CREATEQWORDFIELD
%token <i> CREATEWORDFIELD
%token <i> DATATABLEREGION
%token <i> DEBUG
%token <i> DECODETYPE_POS
%token <i> DECODETYPE_SUB
%token <i> DECREMENT
%token <i> DEFAULT
%token <i> DEFAULT_ARG
%token <i> DEFINITIONBLOCK
%token <i> DEREFOF
%token <i> DEVICE
%token <i> DIVIDE
%token <i> DMA
%token <i> DMATYPE_A
%token <i> DMATYPE_COMPATIBILITY
%token <i> DMATYPE_B
%token <i> DMATYPE_F
%token <i> DWORDCONST
%token <i> DWORDIO
%token <i> DWORDMEMORY
%token <i> EISAID
%token <i> ELSE
%token <i> ELSEIF
%token <i> ENDDEPENDENTFN
%token <i> ERRORNODE
%token <i> EVENT
%token <i> EXTERNAL
%token <i> FATAL
%token <i> FIELD
%token <i> FINDSETLEFTBIT
%token <i> FINDSETRIGHTBIT
%token <i> FIXEDIO
%token <i> FROMBCD
%token <i> IF
%token <i> INCLUDE
%token <i> INCLUDE_CSTYLE
%token <i> INCLUDE_END
%token <i> INCREMENT
%token <i> INDEX
%token <i> INDEXFIELD
%token <i> INTEGER
%token <i> INTERRUPT
%token <i> INTLEVEL_ACTIVEHIGH
%token <i> INTLEVEL_ACTIVELOW
%token <i> INTTYPE_EDGE
%token <i> INTTYPE_LEVEL
%token <i> IO
%token <i> IODECODETYPE_10
%token <i> IODECODETYPE_16
%token <i> IRQ
%token <i> IRQNOFLAGS
%token <i> LAND
%token <i> LEQUAL
%token <i> LGREATER
%token <i> LGREATEREQUAL
%token <i> LLESS
%token <i> LLESSEQUAL
%token <i> LNOT
%token <i> LNOTEQUAL
%token <i> LOAD
%token <i> LOADTABLE
%token <i> LOCAL0
%token <i> LOCAL1
%token <i> LOCAL2
%token <i> LOCAL3
%token <i> LOCAL4
%token <i> LOCAL5
%token <i> LOCAL6
%token <i> LOCAL7
%token <i> LOCKRULE_LOCK
%token <i> LOCKRULE_NOLOCK
%token <i> LOR
%token <i> MATCH
%token <i> MATCHTYPE_MEQ
%token <i> MATCHTYPE_MGE
%token <i> MATCHTYPE_MGT
%token <i> MATCHTYPE_MLE
%token <i> MATCHTYPE_MLT
%token <i> MATCHTYPE_MTR
%token <i> MAXTYPE_FIXED
%token <i> MAXTYPE_NOTFIXED
%token <i> MEMORY24
%token <i> MEMORY32
%token <i> MEMORY32FIXED
%token <i> MEMTYPE_CACHEABLE
%token <i> MEMTYPE_NONCACHEABLE
%token <i> MEMTYPE_PREFETCHABLE
%token <i> MEMTYPE_WRITECOMBINING
%token <i> METHOD
%token <i> METHODCALL
%token <i> MID
%token <i> MINTYPE_FIXED
%token <i> MINTYPE_NOTFIXED
%token <i> MOD
%token <i> MULTIPLY
%token <i> MUTEX
%token <i> NAME
%token <s> NAMESEG
%token <s> NAMESTRING
%token <i> NAND
%token <i> NOOP
%token <i> NOR
%token <i> NOT
%token <i> NOTIFY
%token <i> OBJECTTYPE
%token <i> OBJECTTYPE_BFF
%token <i> OBJECTTYPE_BUF
%token <i> OBJECTTYPE_DDB
%token <i> OBJECTTYPE_DEV
%token <i> OBJECTTYPE_EVT
%token <i> OBJECTTYPE_FLD
%token <i> OBJECTTYPE_INT
%token <i> OBJECTTYPE_MTH
%token <i> OBJECTTYPE_MTX
%token <i> OBJECTTYPE_OPR
%token <i> OBJECTTYPE_PKG
%token <i> OBJECTTYPE_POW
%token <i> OBJECTTYPE_STR
%token <i> OBJECTTYPE_THZ
%token <i> OBJECTTYPE_UNK
%token <i> OFFSET
%token <i> ONE
%token <i> ONES
%token <i> OPERATIONREGION
%token <i> OR
%token <i> PACKAGE
%token <i> PACKAGE_LENGTH
%token <i> POWERRESOURCE
%token <i> PROCESSOR
%token <i> QWORDCONST
%token <i> QWORDIO
%token <i> QWORDMEMORY
%token <i> RANGETYPE_ENTIRE
%token <i> RANGETYPE_ISAONLY
%token <i> RANGETYPE_NONISAONLY
%token <i> RAW_DATA
%token <i> READWRITETYPE_BOTH
%token <i> READWRITETYPE_READONLY
%token <i> REFOF
%token <i> REGIONSPACE_CMOS
%token <i> REGIONSPACE_EC
%token <i> REGIONSPACE_IO
%token <i> REGIONSPACE_MEM
%token <i> REGIONSPACE_PCI
%token <i> REGIONSPACE_PCIBAR
%token <i> REGIONSPACE_SMBUS
%token <i> REGISTER
%token <i> RELEASE
%token <i> RESERVED_BYTES
%token <i> RESET
%token <i> RESOURCETEMPLATE
%token <i> RESOURCETYPE_CONSUMER
%token <i> RESOURCETYPE_PRODUCER
%token <i> RETURN
%token <i> REVISION
%token <i> SCOPE
%token <i> SERIALIZERULE_NOTSERIAL
%token <i> SERIALIZERULE_SERIAL
%token <i> SHARETYPE_EXCLUSIVE
%token <i> SHARETYPE_SHARED
%token <i> SHIFTLEFT
%token <i> SHIFTRIGHT
%token <i> SIGNAL
%token <i> SIZEOF
%token <i> SLEEP
%token <i> STALL
%token <i> STARTDEPENDENTFN
%token <i> STARTDEPENDENTFN_NOPRI
%token <i> STORE
%token <s> STRING_LITERAL
%token <i> SUBTRACT
%token <i> SWITCH
%token <i> THERMALZONE
%token <i> TOBCD
%token <i> TOBUFFER
%token <i> TODECIMALSTRING
%token <i> TOHEXSTRING
%token <i> TOINTEGER
%token <i> TOSTRING
%token <i> TRANSLATIONTYPE_DENSE
%token <i> TRANSLATIONTYPE_SPARSE
%token <i> TYPE_STATIC
%token <i> TYPE_TRANSLATION
%token <i> UNICODE
%token <i> UNLOAD
%token <i> UPDATERULE_ONES
%token <i> UPDATERULE_PRESERVE
%token <i> UPDATERULE_ZEROS
%token <i> VENDORLONG
%token <i> VENDORSHORT
%token <i> WAIT
%token <i> WHILE
%token <i> WORDBUSNUMBER
%token <i> WORDCONST
%token <i> WORDIO
%token <i> XFERTYPE_8
%token <i> XFERTYPE_8_16
%token <i> XFERTYPE_16
%token <i> XOR
%token <i> ZERO


/*
 * Production names
 */

%type <n> ASLCode
%type <n> DefinitionBlockTerm
%type <n> TermList
%type <n> Term
%type <n> CompilerDirective
%type <n> ObjectList
%type <n> Object
%type <n> DataObject
%type <n> BufferData
%type <n> PackageData
%type <n> IntegerData
%type <n> StringData
%type <n> NamedObject
%type <n> NameSpaceModifier
%type <n> UserTerm
%type <n> ArgList
%type <n> ArgListTail
%type <n> TermArg
%type <n> Target
%type <n> RequiredTarget
%type <n> SimpleTarget

%type <n> Type1Opcode
%type <n> Type2Opcode
%type <n> Type2IntegerOpcode
%type <n> Type2StringOpcode
%type <n> Type2BufferOpcode
%type <n> Type2BufferOrStringOpcode
%type <n> Type3Opcode

/* Obsolete %type <n> Type4Opcode */

%type <n> Type5Opcode
%type <n> Type6Opcode


%type <n> IncludeTerm
%type <n> IncludeCStyleTerm
%type <n> ExternalTerm

%type <n> FieldUnitList
%type <n> FieldUnitListTail
%type <n> FieldUnit
%type <n> FieldUnitEntry

%type <n> OffsetTerm
%type <n> AccessAsTerm
%type <n> OptionalAccessAttribTerm


/* Named Objects */

%type <n> BankFieldTerm
%type <n> CreateBitFieldTerm
%type <n> CreateByteFieldTerm
%type <n> CreateDWordFieldTerm
%type <n> CreateFieldTerm
%type <n> CreateQWordFieldTerm
%type <n> CreateWordFieldTerm
%type <n> DataRegionTerm
%type <n> DeviceTerm
%type <n> EventTerm
%type <n> FieldTerm
%type <n> IndexFieldTerm
%type <n> MethodTerm
%type <n> MutexTerm
%type <n> OpRegionTerm
%type <n> OpRegionSpaceIdTerm
%type <n> PowerResTerm
%type <n> ProcessorTerm
%type <n> ThermalZoneTerm


/* Namespace modifiers */

%type <n> AliasTerm
%type <n> NameTerm
%type <n> ScopeTerm

/* Type 1 opcodes */

%type <n> BreakTerm
%type <n> BreakPointTerm
%type <n> ContinueTerm
%type <n> FatalTerm
%type <n> IfElseTerm
%type <n> IfTerm
%type <n> ElseTerm
%type <n> LoadTerm
%type <n> NoOpTerm
%type <n> NotifyTerm
%type <n> ReleaseTerm
%type <n> ResetTerm
%type <n> ReturnTerm
%type <n> SignalTerm
%type <n> SleepTerm
%type <n> StallTerm
%type <n> SwitchTerm
%type <n> CaseTermList
%type <n> DefaultTermList
%type <n> CaseTerm
%type <n> DefaultTerm
%type <n> UnloadTerm
%type <n> WhileTerm

/* Type 2 opcodes */

%type <n> AcquireTerm
%type <n> AddTerm
%type <n> AndTerm
%type <n> ConcatTerm
%type <n> ConcatResTerm
%type <n> CondRefOfTerm
%type <n> CopyObjectTerm
%type <n> DecTerm
%type <n> DerefOfTerm
%type <n> DivideTerm
%type <n> FindSetLeftBitTerm
%type <n> FindSetRightBitTerm
%type <n> FromBCDTerm
%type <n> IncTerm
%type <n> IndexTerm
%type <n> LAndTerm
%type <n> LEqualTerm
%type <n> LGreaterTerm
%type <n> LGreaterEqualTerm
%type <n> LLessTerm
%type <n> LLessEqualTerm
%type <n> LNotTerm
%type <n> LNotEqualTerm
%type <n> LoadTableTerm
%type <n> LOrTerm
%type <n> MatchTerm
%type <n> MidTerm
%type <n> ModTerm
%type <n> MultiplyTerm
%type <n> NAndTerm
%type <n> NOrTerm
%type <n> NotTerm
%type <n> ObjectTypeTerm
%type <n> OrTerm
%type <n> RefOfTerm
%type <n> ShiftLeftTerm
%type <n> ShiftRightTerm
%type <n> SizeOfTerm
%type <n> StoreTerm
%type <n> SubtractTerm
%type <n> ToBCDTerm
%type <n> ToBufferTerm
%type <n> ToDecimalStringTerm
%type <n> ToHexStringTerm
%type <n> ToIntegerTerm
%type <n> ToStringTerm
%type <n> WaitTerm
%type <n> XOrTerm

%type <n> OptionalTermArg
%type <n> OptionalListTermArg


/* Keywords */

%type <n> ObjectTypeKeyword
%type <n> AccessTypeKeyword
%type <n> AccessAttribKeyword
%type <n> LockRuleKeyword
%type <n> UpdateRuleKeyword
%type <n> RegionSpaceKeyword
%type <n> AddressSpaceKeyword
%type <n> MatchOpKeyword
%type <n> SerializeRuleKeyword
%type <n> DMATypeKeyword
%type <n> BusMasterKeyword
%type <n> XferTypeKeyword
%type <n> ResourceTypeKeyword
%type <n> MinKeyword
%type <n> MaxKeyword
%type <n> DecodeKeyword
%type <n> RangeTypeKeyword
%type <n> MemTypeKeyword
%type <n> ReadWriteKeyword
%type <n> InterruptTypeKeyword
%type <n> InterruptLevel
%type <n> ShareTypeKeyword
%type <n> IODecodeKeyword
%type <n> TypeKeyword
%type <n> TranslationKeyword
%type <n> AddressKeyword

/* Types */

%type <n> SuperName
%type <n> ArgTerm
%type <n> LocalTerm
%type <n> DebugTerm


%type <n> Integer

%type <n> ByteConst
%type <n> WordConst
%type <n> DWordConst
%type <n> QWordConst

/* Useless
%type <n> WordConst
%type <n> QWordConst
*/

%type <n> String

%type <n> ConstTerm
%type <n> ByteConstExpr
%type <n> WordConstExpr
%type <n> DWordConstExpr
%type <n> QWordConstExpr
%type <n> ConstExprTerm

%type <n> BufferTerm
%type <n> ByteList
%type <n> ByteListTail
%type <n> DWordList
%type <n> DWordListTail

%type <n> PackageTerm
%type <n> PackageLengthTerm
%type <n> PackageList
%type <n> PackageListTail
%type <n> PackageElement

%type <n> EISAIDTerm
%type <n> ResourceTemplateTerm
%type <n> UnicodeTerm
%type <n> ResourceMacroList
%type <n> ResourceMacroTerm

%type <n> DMATerm
%type <n> DWordIOTerm
%type <n> DWordMemoryTerm
%type <n> EndDependentFnTerm
%type <n> FixedIOTerm
%type <n> InterruptTerm
%type <n> IOTerm
%type <n> IRQNoFlagsTerm
%type <n> IRQTerm
%type <n> Memory24Term
%type <n> Memory32FixedTerm
%type <n> Memory32Term
%type <n> QWordIOTerm
%type <n> QWordMemoryTerm
%type <n> RegisterTerm
%type <n> StartDependentFnTerm
%type <n> StartDependentFnNoPriTerm
%type <n> VendorLongTerm
%type <n> VendorShortTerm
%type <n> WordBusNumberTerm
%type <n> WordIOTerm

%type <n> NameString
%type <n> NameSeg


/* Local types that help construct the AML, not in ACPI spec */

%type <n> IncludeEndTerm
%type <n> AmlPackageLengthTerm
%type <n> OptionalByteConstExpr
%type <n> OptionalDWordConstExpr
%type <n> OptionalSerializeRuleKeyword
%type <n> OptionalResourceType_First
%type <n> OptionalMinType
%type <n> OptionalMaxType
%type <n> OptionalMemType
%type <n> OptionalCount
%type <n> OptionalDecodeType
%type <n> OptionalRangeType
%type <n> OptionalShareType
%type <n> OptionalType
%type <n> OptionalType_Last
%type <n> OptionalTranslationType_Last
%type <n> OptionalStringData
%type <n> OptionalNameString
%type <n> OptionalNameString_First
%type <n> OptionalNameString_Last
%type <n> OptionalAddressRange
%type <n> OptionalObjectTypeKeyword
%type <n> OptionalReference


%type <n> TermArgItem
%type <n> NameStringItem

%%


/*******************************************************************************
 *
 * Production rules start here
 *
 ******************************************************************************/

/*
 * ASL Names
 */


/*
 * Blocks, Data, and Opcodes
 */

ASLCode
    : DefinitionBlockTerm
    | error                         {YYABORT; $$ = NULL;}
    ;

DefinitionBlockTerm
    : DEFINITIONBLOCK '('           {$$ = TrCreateLeafNode (DEFINITIONBLOCK);}
        String ','
        String ','
        ByteConst ','
        String ','
        String ','
        DWordConst
        ')'                         {TrSetEndLineNumber ($<n>3);}
            '{' TermList '}'        {$$ = TrLinkChildren ($<n>3,7,$4,$6,$8,$10,$12,$14,$18);}
    ;

TermList
    :                               {$$ = NULL;}
    | Term TermList                 {$$ = TrLinkPeerNode (TrSetNodeFlags ($1, NODE_RESULT_NOT_USED),$2);}
    ;

Term
    : Object                        {}
    | Type1Opcode                   {}
    | Type2Opcode                   {}
    | Type2IntegerOpcode            {}
    | Type2StringOpcode             {}
    | Type2BufferOpcode             {}
    | Type2BufferOrStringOpcode     {}
    | error                         {$$ = AslDoError(); yyclearin; yyerrok;}
    ;

CompilerDirective
    : IncludeTerm                   {}
    | IncludeCStyleTerm             {$$ = NULL;}
    | ExternalTerm                  {}
    ;

ObjectList
    :                               {$$ = NULL;}
    | Object ObjectList             {$$ = TrLinkPeerNode ($1,$2);}
    ;

Object
    : CompilerDirective             {}
    | NamedObject                   {}
    | NameSpaceModifier             {}
    ;

DataObject
    : BufferData                    {}
    | PackageData                   {}
    | IntegerData                   {}
/*    | StringData                    {} */ /* Caused a reduce/reduce conflict BufferData->StringData */
    ;

BufferData
    : Type5Opcode                   {}
    | Type2BufferOrStringOpcode     {}
    | Type2BufferOpcode             {}
    | BufferTerm                    {}
    ;

PackageData
    : PackageTerm                   {}
    ;

IntegerData
    : Type2IntegerOpcode            {}
    | Type3Opcode                   {}
    | Integer                       {}
    | ConstTerm                     {}
    ;

StringData
    : Type2StringOpcode             {}
    | String                        {}
    ;

NamedObject
    : BankFieldTerm                 {}
    | CreateBitFieldTerm            {}
    | CreateByteFieldTerm           {}
    | CreateDWordFieldTerm          {}
    | CreateFieldTerm               {}
    | CreateQWordFieldTerm          {}
    | CreateWordFieldTerm           {}
    | DataRegionTerm                {}
    | DeviceTerm                    {}
    | EventTerm                     {}
    | FieldTerm                     {}
    | IndexFieldTerm                {}
    | MethodTerm                    {}
    | MutexTerm                     {}
    | OpRegionTerm                  {}
    | PowerResTerm                  {}
    | ProcessorTerm                 {}
    | ThermalZoneTerm               {}
    ;

NameSpaceModifier
    : AliasTerm                     {}
    | NameTerm                      {}
    | ScopeTerm                     {}
    ;

UserTerm
    : NameString '('                {TrUpdateNode (METHODCALL, $1);}
        ArgList ')'                 {$$ = TrLinkChildNode ($1,$4);}
    ;

ArgList
    :                               {$$ = NULL;}
    | TermArg ArgListTail           {$$ = TrLinkPeerNode ($1,$2);}
    ;

ArgListTail
    :                               {$$ = NULL;}
    | ',' TermArg ArgListTail       {$$ = TrLinkPeerNode ($2,$3);}
    | ','                           {$$ = NULL;}   /* Allows a trailing comma at list end */
    ;

TermArg
    : Type2Opcode                   {}
    | Type2IntegerOpcode            {}
    | Type2StringOpcode             {}
    | Type2BufferOpcode             {}
    | Type2BufferOrStringOpcode     {}
    | DataObject                    {}
    | NameString                    {}
    | ArgTerm                       {}
    | LocalTerm                     {}
    ;

Target
    :                               {$$ = TrCreateLeafNode (ZERO);}       /* Placeholder is a ZeroOp object */
    | ','                           {$$ = TrCreateLeafNode (ZERO);}       /* Placeholder is a ZeroOp object */
    | ',' SuperName                 {$$ = TrSetNodeFlags ($2, NODE_IS_TARGET);}
    ;

RequiredTarget
    : ',' SuperName                 {$$ = TrSetNodeFlags ($2, NODE_IS_TARGET);}

SimpleTarget
    : NameString                    {}
    | LocalTerm                     {}
    | ArgTerm                       {}
    ;


/* Opcode types */

Type1Opcode
    : BreakTerm                     {}
    | BreakPointTerm                {}
    | ContinueTerm                  {}
    | FatalTerm                     {}
    | IfElseTerm                    {}
    | LoadTerm                      {}
    | NoOpTerm                      {}
    | NotifyTerm                    {}
    | ReleaseTerm                   {}
    | ResetTerm                     {}
    | ReturnTerm                    {}
    | SignalTerm                    {}
    | SleepTerm                     {}
    | StallTerm                     {}
    | SwitchTerm                    {}
    | UnloadTerm                    {}
    | WhileTerm                     {}
    ;

Type2Opcode
    : AcquireTerm                   {}
    | CondRefOfTerm                 {}
    | CopyObjectTerm                {}
    | DerefOfTerm                   {}
    | ObjectTypeTerm                {}
    | RefOfTerm                     {}
    | SizeOfTerm                    {}
    | StoreTerm                     {}
    | WaitTerm                      {}
    | UserTerm                      {}
    ;

/*
 * A type 2 opcode evaluates to an Integer and cannot have a destination operand
 */

Type2IntegerOpcode                  /* "Type3" opcodes */
    : AddTerm                       {}
    | AndTerm                       {}
    | DecTerm                       {}
    | DivideTerm                    {}
    | FindSetLeftBitTerm            {}
    | FindSetRightBitTerm           {}
    | FromBCDTerm                   {}
    | IncTerm                       {}
    | IndexTerm                     {}
    | LAndTerm                      {}
    | LEqualTerm                    {}
    | LGreaterTerm                  {}
    | LGreaterEqualTerm             {}
    | LLessTerm                     {}
    | LLessEqualTerm                {}
    | LNotTerm                      {}
    | LNotEqualTerm                 {}
    | LoadTableTerm                 {}
    | LOrTerm                       {}
    | MatchTerm                     {}
    | ModTerm                       {}
    | MultiplyTerm                  {}
    | NAndTerm                      {}
    | NOrTerm                       {}
    | NotTerm                       {}
    | OrTerm                        {}
    | ShiftLeftTerm                 {}
    | ShiftRightTerm                {}
    | SubtractTerm                  {}
    | ToBCDTerm                     {}
    | ToIntegerTerm                 {}
    | XOrTerm                       {}
    ;


Type2StringOpcode                   /* "Type4" Opcodes */
    : ToDecimalStringTerm           {}
    | ToHexStringTerm               {}
    | ToStringTerm                  {}
    ;

Type2BufferOpcode                   /* "Type5" Opcodes */
    : ToBufferTerm                  {}
    | ConcatResTerm                 {}
    ;

Type2BufferOrStringOpcode
    : ConcatTerm                    {}
    | MidTerm                       {}
    ;

/*
 * A type 3 opcode evaluates to an Integer and cannot have a destination operand
 */

Type3Opcode
    : EISAIDTerm                    {}
    ;

/* Obsolete
Type4Opcode
    : ConcatTerm                    {}
    | ToDecimalStringTerm           {}
    | ToHexStringTerm               {}
    | MidTerm                       {}
    | ToStringTerm                  {}
    ;
*/


Type5Opcode
    : ResourceTemplateTerm          {}
    | UnicodeTerm                   {}
    ;

Type6Opcode
    : RefOfTerm                     {}
    | DerefOfTerm                   {}
    | IndexTerm                     {}
    | UserTerm                      {}
    ;

IncludeTerm
    : INCLUDE '('                   {$$ = TrCreateLeafNode (INCLUDE);}
        String  ')'                 {$$ = TrLinkChildren ($<n>3,1,$4);FlOpenIncludeFile ($4);}
        TermList
        IncludeEndTerm              {$$ = TrLinkPeerNodes (3,$<n>3,$7,$8);}
    ;

IncludeEndTerm
    : INCLUDE_END                   {$$ = TrCreateLeafNode (INCLUDE_END);}
    ;

IncludeCStyleTerm
    : INCLUDE_CSTYLE
        String                      {FlOpenIncludeFile ($2);}
    ;

ExternalTerm
    : EXTERNAL '('
        NameString
        OptionalObjectTypeKeyword
        ')'                         {$$ = TrCreateNode (EXTERNAL,2,$3,$4);}
    | EXTERNAL '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;


/******* Named Objects *******************************************************/


BankFieldTerm
    : BANKFIELD '('                 {$$ = TrCreateLeafNode (BANKFIELD);}
        NameString
        NameStringItem
        TermArgItem
        ',' AccessTypeKeyword
        ',' LockRuleKeyword
        ',' UpdateRuleKeyword
        ')' '{'
            FieldUnitList '}'       {$$ = TrLinkChildren ($<n>3,7,$4,$5,$6,$8,$10,$12,$15);}
    | BANKFIELD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

FieldUnitList
    :                               {$$ = NULL;}
    | FieldUnit
        FieldUnitListTail           {$$ = TrLinkPeerNode ($1,$2);}
    ;

FieldUnitListTail
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}  /* Allows a trailing comma at list end */
    | ',' FieldUnit
            FieldUnitListTail       {$$ = TrLinkPeerNode ($2,$3);}
    ;

FieldUnit
    : FieldUnitEntry                {}
    | OffsetTerm                    {}
    | AccessAsTerm                  {}
    ;

FieldUnitEntry
    : ',' AmlPackageLengthTerm      {$$ = TrCreateNode (RESERVED_BYTES,1,$2);}
    | NameSeg ','
        AmlPackageLengthTerm        {$$ = TrLinkChildNode ($1,$3);}
    ;

OffsetTerm
    : OFFSET '('
        AmlPackageLengthTerm
        ')'                         {$$ = TrCreateNode (OFFSET,1,$3);}
    | OFFSET '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

AccessAsTerm
    : ACCESSAS '('
        AccessTypeKeyword
        OptionalAccessAttribTerm
        ')'                         {$$ = TrCreateNode (ACCESSAS,2,$3,$4);}
    | ACCESSAS '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

CreateBitFieldTerm
    : CREATEBITFIELD '('            {$$ = TrCreateLeafNode (CREATEBITFIELD);}
        TermArg
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | CREATEBITFIELD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

CreateByteFieldTerm
    : CREATEBYTEFIELD '('           {$$ = TrCreateLeafNode (CREATEBYTEFIELD);}
        TermArg
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | CREATEBYTEFIELD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

CreateDWordFieldTerm
    : CREATEDWORDFIELD '('          {$$ = TrCreateLeafNode (CREATEDWORDFIELD);}
        TermArg
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | CREATEDWORDFIELD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

CreateFieldTerm
    : CREATEFIELD '('               {$$ = TrCreateLeafNode (CREATEFIELD);}
        TermArg
        TermArgItem
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,4,$4,$5,$6,$7);}
    | CREATEFIELD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

CreateQWordFieldTerm
    : CREATEQWORDFIELD '('          {$$ = TrCreateLeafNode (CREATEQWORDFIELD);}
        TermArg
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | CREATEQWORDFIELD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

CreateWordFieldTerm
    : CREATEWORDFIELD '('           {$$ = TrCreateLeafNode (CREATEWORDFIELD);}
        TermArg
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | CREATEWORDFIELD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

DataRegionTerm
    : DATATABLEREGION '('           {$$ = TrCreateLeafNode (DATATABLEREGION);}
        NameString
        TermArgItem
        TermArgItem
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,4,$4,$5,$6,$7);}
    | DATATABLEREGION '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

DeviceTerm
    : DEVICE '('                    {$$ = TrCreateLeafNode (DEVICE);}
        NameString
        ')' '{'
            ObjectList '}'          {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | DEVICE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

EventTerm
    : EVENT '('                     {$$ = TrCreateLeafNode (EVENT);}
        NameString
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | EVENT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

FieldTerm
    : FIELD '('                     {$$ = TrCreateLeafNode (FIELD);}
        NameString
        ',' AccessTypeKeyword
        ',' LockRuleKeyword
        ',' UpdateRuleKeyword
        ')' '{'
            FieldUnitList '}'       {$$ = TrLinkChildren ($<n>3,5,$4,$6,$8,$10,$13);}
    | FIELD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

IndexFieldTerm
    : INDEXFIELD '('                {$$ = TrCreateLeafNode (INDEXFIELD);}
        NameString
        NameStringItem
        ',' AccessTypeKeyword
        ',' LockRuleKeyword
        ',' UpdateRuleKeyword
        ')' '{'
            FieldUnitList '}'       {$$ = TrLinkChildren ($<n>3,6,$4,$5,$7,$9,$11,$14);}
    | INDEXFIELD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

MethodTerm
    : METHOD  '('                   {$$ = TrCreateLeafNode (METHOD);}
        NameString
        OptionalByteConstExpr
        OptionalSerializeRuleKeyword
        OptionalByteConstExpr
        ')' '{'
            TermList '}'            {$$ = TrLinkChildren ($<n>3,5,$4,$5,$6,$7,$10);}
    | METHOD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

MutexTerm
    : MUTEX '('                     {$$ = TrCreateLeafNode (MUTEX);}
        NameString
        ',' ByteConstExpr
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$6);}
    | MUTEX '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

OpRegionTerm
    : OPERATIONREGION '('           {$$ = TrCreateLeafNode (OPERATIONREGION);}
        NameString
        ',' OpRegionSpaceIdTerm
        TermArgItem
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,4,$4,$6,$7,$8);}
    | OPERATIONREGION '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

OpRegionSpaceIdTerm
    : RegionSpaceKeyword            {}
    | ByteConst                     {$$ = UtCheckIntegerRange ($1, 0x80, 0xFF);}
    ;

PowerResTerm
    : POWERRESOURCE '('             {$$ = TrCreateLeafNode (POWERRESOURCE);}
        NameString
        ',' ByteConstExpr
        ',' WordConstExpr
        ')' '{'
            ObjectList '}'          {$$ = TrLinkChildren ($<n>3,4,$4,$6,$8,$11);}
    | POWERRESOURCE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ProcessorTerm
    : PROCESSOR '('                 {$$ = TrCreateLeafNode (PROCESSOR);}
        NameString
        ',' ByteConstExpr
        OptionalDWordConstExpr
        OptionalByteConstExpr
        ')' '{'
            ObjectList '}'          {$$ = TrLinkChildren ($<n>3,5,$4,$6,$7,$8,$11);}
    | PROCESSOR '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ThermalZoneTerm
    : THERMALZONE '('               {$$ = TrCreateLeafNode (THERMALZONE);}
        NameString
        ')' '{'
            ObjectList '}'          {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | THERMALZONE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;


/******* Namespace modifiers *************************************************/


AliasTerm
    : ALIAS '('                     {$$ = TrCreateLeafNode (ALIAS);}
        NameString
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | ALIAS '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

NameTerm
    : NAME '('                      {$$ = TrCreateLeafNode (NAME);}
        NameString
        ',' DataObject
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$6);}
    | NAME '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ScopeTerm
    : SCOPE '('                     {$$ = TrCreateLeafNode (SCOPE);}
        NameString
        ')' '{'
            ObjectList '}'          {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | SCOPE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;


/******* Type 1 opcodes *******************************************************/


BreakTerm
    : BREAK                         {$$ = TrCreateNode (BREAK, 0);}
    ;

BreakPointTerm
    : BREAKPOINT                    {$$ = TrCreateNode (BREAKPOINT, 0);}
    ;

ContinueTerm
    : CONTINUE                      {$$ = TrCreateNode (CONTINUE, 0);}
    ;

FatalTerm
    : FATAL '('                     {$$ = TrCreateLeafNode (FATAL);}
        ByteConstExpr
        ',' DWordConstExpr
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7);}
    | FATAL '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

IfElseTerm
    : IfTerm ElseTerm               {$$ = TrLinkPeerNode ($1,$2);}
    ;

IfTerm
    : IF '('                        {$$ = TrCreateLeafNode (IF);}
        TermArg
        ')' '{'
            TermList '}'
                                    {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | IF '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ElseTerm
    :                               {$$ = NULL;}
    | ELSE '{'                      {$$ = TrCreateLeafNode (ELSE);}
        TermList '}'
                                    {$$ = TrLinkChildren ($<n>3,1,$4);}

    | ELSEIF '('                    {$$ = TrCreateLeafNode (ELSEIF);}
        TermArg
        ')' '{'
        TermList '}'
        ElseTerm
                                    {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | ELSEIF '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

LoadTerm
    : LOAD '('                      {$$ = TrCreateLeafNode (LOAD);}
        NameString
        RequiredTarget
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | LOAD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

NoOpTerm
    : NOOP                          {$$ = TrCreateNode (NOOP, 0);}
    ;

NotifyTerm
    : NOTIFY '('                    {$$ = TrCreateLeafNode (NOTIFY);}
        SuperName
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | NOTIFY '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ReleaseTerm
    : RELEASE '('                   {$$ = TrCreateLeafNode (RELEASE);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | RELEASE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ResetTerm
    : RESET '('                     {$$ = TrCreateLeafNode (RESET);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | RESET '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ReturnTerm
    : RETURN '('                    {$$ = TrCreateLeafNode (RETURN);}
        OptionalTermArg
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | RETURN '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

SignalTerm
    : SIGNAL '('                    {$$ = TrCreateLeafNode (SIGNAL);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | SIGNAL '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

SleepTerm
    : SLEEP '('                     {$$ = TrCreateLeafNode (SLEEP);}
        TermArg
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | SLEEP '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

StallTerm
    : STALL '('                     {$$ = TrCreateLeafNode (STALL);}
        TermArg
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | STALL '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

SwitchTerm
    : SWITCH '('                    {$$ = TrCreateLeafNode (SWITCH);}
        TermArg
        ')' '{'
            CaseTermList '}'
                                    {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | SWITCH '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

CaseTermList
    :                               {$$ = NULL;}
    | CaseTerm                      {}
    | DefaultTerm
        DefaultTermList             {$$ = TrLinkPeerNode ($1,$2);}
    | CaseTerm
        CaseTermList                {$$ = TrLinkPeerNode ($1,$2);}
    ;

DefaultTermList
    :                               {$$ = NULL;}
    | CaseTerm                      {}
    | CaseTerm
        DefaultTermList             {$$ = TrLinkPeerNode ($1,$2);}
    ;

CaseTerm
    : CASE '('                      {$$ = TrCreateLeafNode (CASE);}
        TermArg
        ')' '{'
            TermList '}'            {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | CASE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

DefaultTerm
    : DEFAULT '{'                   {$$ = TrCreateLeafNode (DEFAULT);}
        TermList '}'                {$$ = TrLinkChildren ($<n>3,1,$4);}
    | DEFAULT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

UnloadTerm
    : UNLOAD '('                    {$$ = TrCreateLeafNode (UNLOAD);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | UNLOAD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

WhileTerm
    : WHILE '('                     {$$ = TrCreateLeafNode (WHILE);}
        TermArg
        ')' '{' TermList '}'
                                    {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | WHILE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;


/******* Type 2 opcodes *******************************************************/

AcquireTerm
    : ACQUIRE '('                   {$$ = TrCreateLeafNode (ACQUIRE);}
        SuperName
        ',' WordConstExpr
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$6);}
    | ACQUIRE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

AddTerm
    : ADD '('                       {$$ = TrCreateLeafNode (ADD);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | ADD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

AndTerm
    : AND '('                       {$$ = TrCreateLeafNode (AND);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | AND '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ConcatTerm
    : CONCATENATE '('               {$$ = TrCreateLeafNode (CONCATENATE);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | CONCATENATE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ConcatResTerm
    : CONCATENATERESTEMPLATE '('    {$$ = TrCreateLeafNode (CONCATENATERESTEMPLATE);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | CONCATENATERESTEMPLATE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

CondRefOfTerm
    : CONDREFOF '('                 {$$ = TrCreateLeafNode (CONDREFOF);}
        SuperName
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | CONDREFOF '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

CopyObjectTerm
    : COPYOBJECT '('                {$$ = TrCreateLeafNode (COPYOBJECT);}
        TermArg
        ',' SimpleTarget
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$6);}
    | COPYOBJECT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

DecTerm
    : DECREMENT '('                 {$$ = TrCreateLeafNode (DECREMENT);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | DECREMENT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

DerefOfTerm
    : DEREFOF '('                   {$$ = TrCreateLeafNode (DEREFOF);}
        TermArg
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | DEREFOF '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

DivideTerm
    : DIVIDE '('                    {$$ = TrCreateLeafNode (DIVIDE);}
        TermArg
        TermArgItem
        Target
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,4,$4,$5,$6,$7);}
    | DIVIDE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

FindSetLeftBitTerm
    : FINDSETLEFTBIT '('            {$$ = TrCreateLeafNode (FINDSETLEFTBIT);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | FINDSETLEFTBIT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

FindSetRightBitTerm
    : FINDSETRIGHTBIT '('           {$$ = TrCreateLeafNode (FINDSETRIGHTBIT);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | FINDSETRIGHTBIT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

FromBCDTerm
    : FROMBCD '('                   {$$ = TrCreateLeafNode (FROMBCD);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | FROMBCD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

IncTerm
    : INCREMENT '('                 {$$ = TrCreateLeafNode (INCREMENT);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | INCREMENT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

IndexTerm
    : INDEX '('                     {$$ = TrCreateLeafNode (INDEX);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | INDEX '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

LAndTerm
    : LAND '('                      {$$ = TrCreateLeafNode (LAND);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | LAND '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

LEqualTerm
    : LEQUAL '('                    {$$ = TrCreateLeafNode (LEQUAL);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | LEQUAL '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

LGreaterTerm
    : LGREATER '('                  {$$ = TrCreateLeafNode (LGREATER);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | LGREATER '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

LGreaterEqualTerm
    : LGREATEREQUAL '('             {$$ = TrCreateLeafNode (LGREATEREQUAL);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | LGREATEREQUAL '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

LLessTerm
    : LLESS '('                     {$$ = TrCreateLeafNode (LLESS);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | LLESS '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

LLessEqualTerm
    : LLESSEQUAL '('                {$$ = TrCreateLeafNode (LLESSEQUAL);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | LLESSEQUAL '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

LNotTerm
    : LNOT '('                      {$$ = TrCreateLeafNode (LNOT);}
        TermArg
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | LNOT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

LNotEqualTerm
    : LNOTEQUAL '('                 {$$ = TrCreateLeafNode (LNOTEQUAL);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | LNOTEQUAL '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

LoadTableTerm
    : LOADTABLE '('                 {$$ = TrCreateLeafNode (LOADTABLE);}
        TermArg
        TermArgItem
        TermArgItem
        OptionalListTermArg
        OptionalListTermArg
        OptionalReference
        ')'                         {$$ = TrLinkChildren ($<n>3,6,$4,$5,$6,$7,$8,$9);}
    | LOADTABLE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

LOrTerm
    : LOR '('                       {$$ = TrCreateLeafNode (LOR);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | LOR '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

MatchTerm
    : MATCH '('                     {$$ = TrCreateLeafNode (MATCH);}
        TermArg
        ',' MatchOpKeyword
        TermArgItem
        ',' MatchOpKeyword
        TermArgItem
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,6,$4,$6,$7,$9,$10,$11);}
    | MATCH '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

MidTerm
    : MID '('                       {$$ = TrCreateLeafNode (MID);}
        TermArg
        TermArgItem
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,4,$4,$5,$6,$7);}
    | MID '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ModTerm
    : MOD '('                       {$$ = TrCreateLeafNode (MOD);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | MOD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

MultiplyTerm
    : MULTIPLY '('                  {$$ = TrCreateLeafNode (MULTIPLY);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | MULTIPLY '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

NAndTerm
    : NAND '('                      {$$ = TrCreateLeafNode (NAND);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | NAND '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

NOrTerm
    : NOR '('                       {$$ = TrCreateLeafNode (NOR);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | NOR '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

NotTerm
    : NOT '('                       {$$ = TrCreateLeafNode (NOT);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | NOT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ObjectTypeTerm
    : OBJECTTYPE '('                {$$ = TrCreateLeafNode (OBJECTTYPE);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | OBJECTTYPE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

OrTerm
    : OR '('                        {$$ = TrCreateLeafNode (OR);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | OR '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

/*
 * In RefOf, the node isn't really a target, but we can't keep track of it after
 * we've taken a pointer to it. (hard to tell if a local becomes initialized this way.)
 */
RefOfTerm
    : REFOF '('                     {$$ = TrCreateLeafNode (REFOF);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,TrSetNodeFlags ($4, NODE_IS_TARGET));}
    | REFOF '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ShiftLeftTerm
    : SHIFTLEFT '('                 {$$ = TrCreateLeafNode (SHIFTLEFT);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | SHIFTLEFT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ShiftRightTerm
    : SHIFTRIGHT '('                {$$ = TrCreateLeafNode (SHIFTRIGHT);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | SHIFTRIGHT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

SizeOfTerm
    : SIZEOF '('                    {$$ = TrCreateLeafNode (SIZEOF);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | SIZEOF '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

StoreTerm
    : STORE '('                     {$$ = TrCreateLeafNode (STORE);}
        TermArg
        ',' SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,TrSetNodeFlags ($6, NODE_IS_TARGET));}
    | STORE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

SubtractTerm
    : SUBTRACT '('                  {$$ = TrCreateLeafNode (SUBTRACT);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | SUBTRACT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ToBCDTerm
    : TOBCD '('                     {$$ = TrCreateLeafNode (TOBCD);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | TOBCD '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ToBufferTerm
    : TOBUFFER '('                  {$$ = TrCreateLeafNode (TOBUFFER);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | TOBUFFER '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ToDecimalStringTerm
    : TODECIMALSTRING '('           {$$ = TrCreateLeafNode (TODECIMALSTRING);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | TODECIMALSTRING '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ToHexStringTerm
    : TOHEXSTRING '('               {$$ = TrCreateLeafNode (TOHEXSTRING);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | TOHEXSTRING '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ToIntegerTerm
    : TOINTEGER '('                 {$$ = TrCreateLeafNode (TOINTEGER);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | TOINTEGER '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ToStringTerm
    : TOSTRING '('                  {$$ = TrCreateLeafNode (TOSTRING);}
        TermArg
        OptionalCount
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | TOSTRING '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

WaitTerm
    : WAIT '('                      {$$ = TrCreateLeafNode (WAIT);}
        SuperName
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | WAIT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

XOrTerm
    : XOR '('                       {$$ = TrCreateLeafNode (XOR);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | XOR '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;


/******* Keywords *************************************************************/


ObjectTypeKeyword
    : OBJECTTYPE_UNK                {$$ = TrCreateLeafNode (OBJECTTYPE_UNK);}
    | OBJECTTYPE_INT                {$$ = TrCreateLeafNode (OBJECTTYPE_INT);}
    | OBJECTTYPE_STR                {$$ = TrCreateLeafNode (OBJECTTYPE_STR);}
    | OBJECTTYPE_BUF                {$$ = TrCreateLeafNode (OBJECTTYPE_BUF);}
    | OBJECTTYPE_PKG                {$$ = TrCreateLeafNode (OBJECTTYPE_PKG);}
    | OBJECTTYPE_FLD                {$$ = TrCreateLeafNode (OBJECTTYPE_FLD);}
    | OBJECTTYPE_DEV                {$$ = TrCreateLeafNode (OBJECTTYPE_DEV);}
    | OBJECTTYPE_EVT                {$$ = TrCreateLeafNode (OBJECTTYPE_EVT);}
    | OBJECTTYPE_MTH                {$$ = TrCreateLeafNode (OBJECTTYPE_MTH);}
    | OBJECTTYPE_MTX                {$$ = TrCreateLeafNode (OBJECTTYPE_MTX);}
    | OBJECTTYPE_OPR                {$$ = TrCreateLeafNode (OBJECTTYPE_OPR);}
    | OBJECTTYPE_POW                {$$ = TrCreateLeafNode (OBJECTTYPE_POW);}
    | OBJECTTYPE_THZ                {$$ = TrCreateLeafNode (OBJECTTYPE_THZ);}
    | OBJECTTYPE_BFF                {$$ = TrCreateLeafNode (OBJECTTYPE_BFF);}
    | OBJECTTYPE_DDB                {$$ = TrCreateLeafNode (OBJECTTYPE_DDB);}
    ;

AccessTypeKeyword
    : ACCESSTYPE_ANY                {$$ = TrCreateLeafNode (ACCESSTYPE_ANY);}
    | ACCESSTYPE_BYTE               {$$ = TrCreateLeafNode (ACCESSTYPE_BYTE);}
    | ACCESSTYPE_WORD               {$$ = TrCreateLeafNode (ACCESSTYPE_WORD);}
    | ACCESSTYPE_DWORD              {$$ = TrCreateLeafNode (ACCESSTYPE_DWORD);}
    | ACCESSTYPE_QWORD              {$$ = TrCreateLeafNode (ACCESSTYPE_QWORD);}
    | ACCESSTYPE_BUF                {$$ = TrCreateLeafNode (ACCESSTYPE_BUF);}
    ;

AccessAttribKeyword
    : ACCESSATTRIB_QUICK            {$$ = TrCreateLeafNode (ACCESSATTRIB_QUICK );}
    | ACCESSATTRIB_SND_RCV          {$$ = TrCreateLeafNode (ACCESSATTRIB_SND_RCV);}
    | ACCESSATTRIB_BYTE             {$$ = TrCreateLeafNode (ACCESSATTRIB_BYTE);}
    | ACCESSATTRIB_WORD             {$$ = TrCreateLeafNode (ACCESSATTRIB_WORD);}
    | ACCESSATTRIB_BLOCK            {$$ = TrCreateLeafNode (ACCESSATTRIB_BLOCK);}
    | ACCESSATTRIB_CALL             {$$ = TrCreateLeafNode (ACCESSATTRIB_CALL);}
    ;

LockRuleKeyword
    : LOCKRULE_LOCK                 {$$ = TrCreateLeafNode (LOCKRULE_LOCK);}
    | LOCKRULE_NOLOCK               {$$ = TrCreateLeafNode (LOCKRULE_NOLOCK);}
    ;

UpdateRuleKeyword
    : UPDATERULE_PRESERVE           {$$ = TrCreateLeafNode (UPDATERULE_PRESERVE);}
    | UPDATERULE_ONES               {$$ = TrCreateLeafNode (UPDATERULE_ONES);}
    | UPDATERULE_ZEROS              {$$ = TrCreateLeafNode (UPDATERULE_ZEROS);}
    ;


RegionSpaceKeyword
    : REGIONSPACE_IO                {$$ = TrCreateLeafNode (REGIONSPACE_IO);}
    | REGIONSPACE_MEM               {$$ = TrCreateLeafNode (REGIONSPACE_MEM);}
    | REGIONSPACE_PCI               {$$ = TrCreateLeafNode (REGIONSPACE_PCI);}
    | REGIONSPACE_EC                {$$ = TrCreateLeafNode (REGIONSPACE_EC);}
    | REGIONSPACE_SMBUS             {$$ = TrCreateLeafNode (REGIONSPACE_SMBUS);}
    | REGIONSPACE_CMOS              {$$ = TrCreateLeafNode (REGIONSPACE_CMOS);}
    | REGIONSPACE_PCIBAR            {$$ = TrCreateLeafNode (REGIONSPACE_PCIBAR);}
    ;

AddressSpaceKeyword
    : ByteConst                     {$$ = UtCheckIntegerRange ($1, 0x80, 0xFF);}
    | RegionSpaceKeyword            {}
    | ADDRESSSPACE_FFIXEDHW         {$$ = TrCreateLeafNode (ADDRESSSPACE_FFIXEDHW);}
    ;


SerializeRuleKeyword
    : SERIALIZERULE_SERIAL          {$$ = TrCreateLeafNode (SERIALIZERULE_SERIAL);}
    | SERIALIZERULE_NOTSERIAL       {$$ = TrCreateLeafNode (SERIALIZERULE_NOTSERIAL);}
    ;

MatchOpKeyword
    : MATCHTYPE_MTR                 {$$ = TrCreateLeafNode (MATCHTYPE_MTR);}
    | MATCHTYPE_MEQ                 {$$ = TrCreateLeafNode (MATCHTYPE_MEQ);}
    | MATCHTYPE_MLE                 {$$ = TrCreateLeafNode (MATCHTYPE_MLE);}
    | MATCHTYPE_MLT                 {$$ = TrCreateLeafNode (MATCHTYPE_MLT);}
    | MATCHTYPE_MGE                 {$$ = TrCreateLeafNode (MATCHTYPE_MGE);}
    | MATCHTYPE_MGT                 {$$ = TrCreateLeafNode (MATCHTYPE_MGT);}
    ;

DMATypeKeyword
    : DMATYPE_A                     {$$ = TrCreateLeafNode (DMATYPE_A);}
    | DMATYPE_COMPATIBILITY         {$$ = TrCreateLeafNode (DMATYPE_COMPATIBILITY);}
    | DMATYPE_B                     {$$ = TrCreateLeafNode (DMATYPE_B);}
    | DMATYPE_F                     {$$ = TrCreateLeafNode (DMATYPE_F);}
    ;

BusMasterKeyword
    : BUSMASTERTYPE_MASTER          {$$ = TrCreateLeafNode (BUSMASTERTYPE_MASTER);}
    | BUSMASTERTYPE_NOTMASTER       {$$ = TrCreateLeafNode (BUSMASTERTYPE_NOTMASTER);}
    ;

XferTypeKeyword
    : XFERTYPE_8                    {$$ = TrCreateLeafNode (XFERTYPE_8);}
    | XFERTYPE_8_16                 {$$ = TrCreateLeafNode (XFERTYPE_8_16);}
    | XFERTYPE_16                   {$$ = TrCreateLeafNode (XFERTYPE_16);}
    ;

ResourceTypeKeyword
    : RESOURCETYPE_CONSUMER         {$$ = TrCreateLeafNode (RESOURCETYPE_CONSUMER);}
    | RESOURCETYPE_PRODUCER         {$$ = TrCreateLeafNode (RESOURCETYPE_PRODUCER);}
    ;

MinKeyword
    : MINTYPE_FIXED                 {$$ = TrCreateLeafNode (MINTYPE_FIXED);}
    | MINTYPE_NOTFIXED              {$$ = TrCreateLeafNode (MINTYPE_NOTFIXED);}
    ;

MaxKeyword
    : MAXTYPE_FIXED                 {$$ = TrCreateLeafNode (MAXTYPE_FIXED);}
    | MAXTYPE_NOTFIXED              {$$ = TrCreateLeafNode (MAXTYPE_NOTFIXED);}
    ;

DecodeKeyword
    : DECODETYPE_POS                {$$ = TrCreateLeafNode (DECODETYPE_POS);}
    | DECODETYPE_SUB                {$$ = TrCreateLeafNode (DECODETYPE_SUB);}
    ;

RangeTypeKeyword
    : RANGETYPE_ISAONLY             {$$ = TrCreateLeafNode (RANGETYPE_ISAONLY);}
    | RANGETYPE_NONISAONLY          {$$ = TrCreateLeafNode (RANGETYPE_NONISAONLY);}
    | RANGETYPE_ENTIRE              {$$ = TrCreateLeafNode (RANGETYPE_ENTIRE);}
    ;

MemTypeKeyword
    : MEMTYPE_CACHEABLE             {$$ = TrCreateLeafNode (MEMTYPE_CACHEABLE);}
    | MEMTYPE_WRITECOMBINING        {$$ = TrCreateLeafNode (MEMTYPE_WRITECOMBINING);}
    | MEMTYPE_PREFETCHABLE          {$$ = TrCreateLeafNode (MEMTYPE_PREFETCHABLE);}
    | MEMTYPE_NONCACHEABLE          {$$ = TrCreateLeafNode (MEMTYPE_NONCACHEABLE);}
    ;

ReadWriteKeyword
    : READWRITETYPE_BOTH            {$$ = TrCreateLeafNode (READWRITETYPE_BOTH);}
    | READWRITETYPE_READONLY        {$$ = TrCreateLeafNode (READWRITETYPE_READONLY);}
    ;

InterruptTypeKeyword
    : INTTYPE_EDGE                  {$$ = TrCreateLeafNode (INTTYPE_EDGE);}
    | INTTYPE_LEVEL                 {$$ = TrCreateLeafNode (INTTYPE_LEVEL);}
    ;

InterruptLevel
    : INTLEVEL_ACTIVEHIGH           {$$ = TrCreateLeafNode (INTLEVEL_ACTIVEHIGH);}
    | INTLEVEL_ACTIVELOW            {$$ = TrCreateLeafNode (INTLEVEL_ACTIVELOW);}
    ;

ShareTypeKeyword
    : SHARETYPE_SHARED              {$$ = TrCreateLeafNode (SHARETYPE_SHARED);}
    | SHARETYPE_EXCLUSIVE           {$$ = TrCreateLeafNode (SHARETYPE_EXCLUSIVE);}
    ;

IODecodeKeyword
    : IODECODETYPE_16               {$$ = TrCreateLeafNode (IODECODETYPE_16);}
    | IODECODETYPE_10               {$$ = TrCreateLeafNode (IODECODETYPE_10);}
    ;

TypeKeyword
    : TYPE_TRANSLATION              {$$ = TrCreateLeafNode (TYPE_TRANSLATION);}
    | TYPE_STATIC                   {$$ = TrCreateLeafNode (TYPE_STATIC);}
    ;

TranslationKeyword
    : TRANSLATIONTYPE_SPARSE        {$$ = TrCreateLeafNode (TRANSLATIONTYPE_SPARSE);}
    | TRANSLATIONTYPE_DENSE         {$$ = TrCreateLeafNode (TRANSLATIONTYPE_DENSE);}
    ;

AddressKeyword
    : ADDRESSTYPE_MEMORY            {$$ = TrCreateLeafNode (ADDRESSTYPE_MEMORY);}
    | ADDRESSTYPE_RESERVED          {$$ = TrCreateLeafNode (ADDRESSTYPE_RESERVED);}
    | ADDRESSTYPE_NVS               {$$ = TrCreateLeafNode (ADDRESSTYPE_NVS);}
    | ADDRESSTYPE_ACPI              {$$ = TrCreateLeafNode (ADDRESSTYPE_ACPI);}
    ;


/******* Miscellaneous Types **************************************************/


SuperName
    : NameString                    {}
    | ArgTerm                       {}
    | LocalTerm                     {}
    | DebugTerm                     {}
    | Type6Opcode                   {}
/*    | UserTerm                      {} */  /* Caused reduce/reduce with Type6Opcode->UserTerm */
    ;

ArgTerm
    : ARG0                          {$$ = TrCreateLeafNode (ARG0);}
    | ARG1                          {$$ = TrCreateLeafNode (ARG1);}
    | ARG2                          {$$ = TrCreateLeafNode (ARG2);}
    | ARG3                          {$$ = TrCreateLeafNode (ARG3);}
    | ARG4                          {$$ = TrCreateLeafNode (ARG4);}
    | ARG5                          {$$ = TrCreateLeafNode (ARG5);}
    | ARG6                          {$$ = TrCreateLeafNode (ARG6);}
    ;

LocalTerm
    : LOCAL0                        {$$ = TrCreateLeafNode (LOCAL0);}
    | LOCAL1                        {$$ = TrCreateLeafNode (LOCAL1);}
    | LOCAL2                        {$$ = TrCreateLeafNode (LOCAL2);}
    | LOCAL3                        {$$ = TrCreateLeafNode (LOCAL3);}
    | LOCAL4                        {$$ = TrCreateLeafNode (LOCAL4);}
    | LOCAL5                        {$$ = TrCreateLeafNode (LOCAL5);}
    | LOCAL6                        {$$ = TrCreateLeafNode (LOCAL6);}
    | LOCAL7                        {$$ = TrCreateLeafNode (LOCAL7);}
    ;

DebugTerm
    : DEBUG                         {$$ = TrCreateLeafNode (DEBUG);}
    ;


ByteConst
    : Integer                       {$$ = TrUpdateNode (BYTECONST, $1);}
    ;

WordConst
    : Integer                       {$$ = TrUpdateNode (WORDCONST, $1);}
    ;

DWordConst
    : Integer                       {$$ = TrUpdateNode (DWORDCONST, $1);}
    ;

QWordConst
    : Integer                       {$$ = TrUpdateNode (QWORDCONST, $1);}
    ;

Integer
    : INTEGER                       {$$ = TrCreateValuedLeafNode (INTEGER, AslCompilerlval.i);}
    ;

String
    : STRING_LITERAL                {$$ = TrCreateValuedLeafNode (STRING_LITERAL, (ACPI_INTEGER) AslCompilerlval.s);}
    ;

ConstTerm
    : ConstExprTerm                 {}
    | REVISION                      {$$ = TrCreateLeafNode (REVISION);}
    ;

ByteConstExpr
    : Type3Opcode                   {$$ = TrUpdateNode (BYTECONST, $1);}
    | Type2IntegerOpcode            {$$ = TrUpdateNode (BYTECONST, $1);}
    | ConstExprTerm                 {$$ = TrUpdateNode (BYTECONST, $1);}
    | ByteConst                     {}
    ;

WordConstExpr
    : Type3Opcode                   {$$ = TrUpdateNode (WORDCONST, $1);}
    | Type2IntegerOpcode            {$$ = TrUpdateNode (WORDCONST, $1);}
    | ConstExprTerm                 {$$ = TrUpdateNode (WORDCONST, $1);}
    | WordConst                     {}
    ;

DWordConstExpr
    : Type3Opcode                   {$$ = TrUpdateNode (DWORDCONST, $1);}
    | Type2IntegerOpcode            {$$ = TrUpdateNode (DWORDCONST, $1);}
    | ConstExprTerm                 {$$ = TrUpdateNode (DWORDCONST, $1);}
    | DWordConst                    {}
    ;

QWordConstExpr
    : Type3Opcode                   {$$ = TrUpdateNode (QWORDCONST, $1);}
    | Type2IntegerOpcode            {$$ = TrUpdateNode (QWORDCONST, $1);}
    | ConstExprTerm                 {$$ = TrUpdateNode (QWORDCONST, $1);}
    | QWordConst                    {}
    ;

ConstExprTerm
    : ZERO                          {$$ = TrCreateLeafNode (ZERO);}
    | ONE                           {$$ = TrCreateLeafNode (ONE);}
    | ONES                          {$$ = TrCreateLeafNode (ONES);}
    ;

BufferTerm
    : BUFFER '('                    {$$ = TrCreateLeafNode (BUFFER);}
        OptionalTermArg
        ')' '{'
            BufferData '}'          {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | BUFFER '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

BufferData
    : ByteList                      {}
    | StringData                    {}
    ;

ByteList
    :     {$$ = NULL;}
    | ByteConstExpr
        ByteListTail                {$$ = TrLinkPeerNode ($1,$2);}
    ;

ByteListTail
    :                               {$$ = NULL;}
    |  ','                          {$$ = NULL;}   /* Allows a trailing comma at list end */
    |  ',' ByteConstExpr
         ByteListTail               {$$ = TrLinkPeerNode ($2,$3);}
    ;

DWordList
    :                               {$$ = NULL;}
    | DWordConstExpr
        DWordListTail               {$$ = TrLinkPeerNode ($1,$2);}
    ;

DWordListTail
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}   /* Allows a trailing comma at list end */
    | ',' DWordConstExpr
        DWordListTail               {$$ = TrLinkPeerNode ($2,$3);}
    ;

PackageTerm
    : PACKAGE '('                   {$$ = TrCreateLeafNode (PACKAGE);}
        PackageLengthTerm
        ')' '{'
            PackageList '}'         {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | PACKAGE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

PackageLengthTerm
    :                               {$$ = NULL;}
    | ByteConstExpr                 {}
    | TermArg                       {}
    ;

PackageList
    :                               {$$ = NULL;}
    | PackageElement
        PackageListTail             {$$ = TrLinkPeerNode ($1,$2);}
    ;

PackageListTail
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}   /* Allows a trailing comma at list end */
    | ',' PackageElement
        PackageListTail             {$$ = TrLinkPeerNode ($2,$3);}
    ;

PackageElement
    : DataObject                    {}
    | NameString                    {}
    ;

EISAIDTerm
    : EISAID '('
        StringData ')'              {$$ = TrUpdateNode (EISAID, $3);}
    | EISAID '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;


/******* Resources and Memory ***********************************************/


ResourceTemplateTerm
    : RESOURCETEMPLATE '(' ')'
        '{'
        ResourceMacroList '}'       {$$ = TrCreateNode (RESOURCETEMPLATE,3,
                                        TrCreateLeafNode (DEFAULT_ARG),
                                        TrCreateLeafNode (DEFAULT_ARG),$5);}
    ;

UnicodeTerm
    : UNICODE '('                   {$$ = TrCreateLeafNode (UNICODE);}
        StringData
        ')'                         {$$ = TrLinkChildren ($<n>3,2,0,$4);}
    | UNICODE '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

ResourceMacroList
    :                               {$$ = NULL;}
    | ResourceMacroTerm
        ResourceMacroList           {$$ = TrLinkPeerNode ($1,$2);}
    ;

ResourceMacroTerm
    : DMATerm                       {}
    | DWordIOTerm                   {}
    | DWordMemoryTerm               {}
    | EndDependentFnTerm            {}
    | FixedIOTerm                   {}
    | InterruptTerm                 {}
    | IOTerm                        {}
    | IRQNoFlagsTerm                {}
    | IRQTerm                       {}
    | Memory24Term                  {}
    | Memory32FixedTerm             {}
    | Memory32Term                  {}
    | QWordIOTerm                   {}
    | QWordMemoryTerm               {}
    | RegisterTerm                  {}
    | StartDependentFnTerm          {}
    | StartDependentFnNoPriTerm     {}
    | VendorLongTerm                {}
    | VendorShortTerm               {}
    | WordBusNumberTerm             {}
    | WordIOTerm                    {}
    ;

DMATerm
    : DMA '('                       {$$ = TrCreateLeafNode (DMA);}
        DMATypeKeyword
        ',' BusMasterKeyword
        ',' XferTypeKeyword
        OptionalNameString_Last
        ')' '{'
            ByteList '}'            {$$ = TrLinkChildren ($<n>3,5,$4,$6,$8,$9,$12);}
    | DMA '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

DWordIOTerm
    : DWORDIO '('                   {$$ = TrCreateLeafNode (DWORDIO);}
        OptionalResourceType_First
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        OptionalRangeType
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalType
        OptionalTranslationType_Last
        ')'                         {$$ = TrLinkChildren ($<n>3,15,$4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$19,$20,$21,$22,$23);}
    | DWORDIO '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

DWordMemoryTerm
    : DWORDMEMORY '('               {$$ = TrCreateLeafNode (DWORDMEMORY);}
        OptionalResourceType_First
        OptionalDecodeType
        OptionalMinType
        OptionalMaxType
        OptionalMemType
        ',' ReadWriteKeyword
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalAddressRange
        OptionalType_Last
        ')'                         {$$ = TrLinkChildren ($<n>3,16,$4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$20,$21,$22,$23,$24,$25);}
    | DWORDMEMORY '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

EndDependentFnTerm
    : ENDDEPENDENTFN '('
        ')'                         {$$ = TrCreateLeafNode (ENDDEPENDENTFN);}
    | ENDDEPENDENTFN '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

FixedIOTerm
    : FIXEDIO '('                   {$$ = TrCreateLeafNode (FIXEDIO);}
        WordConstExpr
        ',' ByteConstExpr
        OptionalNameString_Last
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7);}
    | FIXEDIO '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

InterruptTerm
    : INTERRUPT '('                 {$$ = TrCreateLeafNode (INTERRUPT);}
        OptionalResourceType_First
        ',' InterruptTypeKeyword
        ',' InterruptLevel
        OptionalShareType
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString_Last
        ')' '{'
            DWordList '}'           {$$ = TrLinkChildren ($<n>3,8,$4,$6,$8,$9,$10,$11,$12,$15);}
    | INTERRUPT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

IOTerm
    : IO '('                        {$$ = TrCreateLeafNode (IO);}
        IODecodeKeyword
        ',' WordConstExpr
        ',' WordConstExpr
        ',' ByteConstExpr
        ',' ByteConstExpr
        OptionalNameString_Last
        ')'                         {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$12,$13);}
    | IO '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

IRQNoFlagsTerm
    : IRQNOFLAGS '('                {$$ = TrCreateLeafNode (IRQNOFLAGS);}
        OptionalNameString_First
        ')' '{'
            ByteList '}'            {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | IRQNOFLAGS '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

IRQTerm
    : IRQ '('                       {$$ = TrCreateLeafNode (IRQ);}
        InterruptTypeKeyword
        ',' InterruptLevel
        OptionalShareType
        OptionalNameString_Last
        ')' '{'
            ByteList '}'            {$$ = TrLinkChildren ($<n>3,5,$4,$6,$7,$8,$11);}
    | IRQ '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

Memory24Term
    : MEMORY24 '('                  {$$ = TrCreateLeafNode (MEMORY24);}
        ReadWriteKeyword
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        OptionalNameString_Last
        ')'                         {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$12,$13);}
    | MEMORY24 '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

Memory32FixedTerm
    : MEMORY32FIXED '('             {$$ = TrCreateLeafNode (MEMORY32FIXED);}
        ReadWriteKeyword
        ',' DWordConstExpr
        ',' DWordConstExpr
        OptionalNameString_Last
        ')'                         {$$ = TrLinkChildren ($<n>3,4,$4,$6,$8,$9);}
    | MEMORY32FIXED '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

Memory32Term
    : MEMORY32 '('                  {$$ = TrCreateLeafNode (MEMORY32);}
        ReadWriteKeyword
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        ',' DWordConstExpr
        OptionalNameString_Last
        ')'                         {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$12,$13);}
    | MEMORY32 '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

QWordIOTerm
    : QWORDIO '('                   {$$ = TrCreateLeafNode (QWORDIO);}
        OptionalResourceType_First
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        OptionalRangeType
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalType
        OptionalTranslationType_Last
        ')'                         {$$ = TrLinkChildren ($<n>3,15,$4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$19,$20,$21,$22,$23);}
    | QWORDIO '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

QWordMemoryTerm
    : QWORDMEMORY '('               {$$ = TrCreateLeafNode (QWORDMEMORY);}
        OptionalResourceType_First
        OptionalDecodeType
        OptionalMinType
        OptionalMaxType
        OptionalMemType
        ',' ReadWriteKeyword
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        ',' QWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalAddressRange
        OptionalType_Last
        ')'                         {$$ = TrLinkChildren ($<n>3,16,$4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$20,$21,$22,$23,$24,$25);}
    | QWORDMEMORY '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

RegisterTerm
    : REGISTER '('                  {$$ = TrCreateLeafNode (REGISTER);}
        AddressSpaceKeyword
        ',' ByteConstExpr
        ',' ByteConstExpr
        ',' QWordConstExpr
        ')'                         {$$ = TrLinkChildren ($<n>3,4,$4,$6,$8,$10);}
    | REGISTER '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

StartDependentFnTerm
    : STARTDEPENDENTFN '('          {$$ = TrCreateLeafNode (STARTDEPENDENTFN);}
        ByteConstExpr
        ',' ByteConstExpr
        ')' '{'
        ResourceMacroList '}'       {$$ = TrLinkChildren ($<n>3,3,$4,$6,$9);}
    | STARTDEPENDENTFN '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

StartDependentFnNoPriTerm
    : STARTDEPENDENTFN_NOPRI '('    {$$ = TrCreateLeafNode (STARTDEPENDENTFN_NOPRI);}
        ')' '{'
        ResourceMacroList '}'       {$$ = TrLinkChildren ($<n>3,1,$6);}
    | STARTDEPENDENTFN_NOPRI '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

VendorLongTerm
    : VENDORLONG '('                {$$ = TrCreateLeafNode (VENDORLONG);}
        OptionalNameString_First
        ')' '{'
            ByteList '}'            {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | VENDORLONG '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

VendorShortTerm
    : VENDORSHORT '('               {$$ = TrCreateLeafNode (VENDORSHORT);}
        OptionalNameString_First
        ')' '{'
            ByteList '}'            {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | VENDORSHORT '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

WordBusNumberTerm
    : WORDBUSNUMBER '('             {$$ = TrCreateLeafNode (WORDBUSNUMBER);}
        OptionalResourceType_First
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString_Last
        ')'                         {$$ = TrLinkChildren ($<n>3,12,$4,$5,$6,$7,$9,$11,$13,$15,$17,$18,$19,$20);}
    | WORDBUSNUMBER '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;

WordIOTerm
    : WORDIO '('                    {$$ = TrCreateLeafNode (WORDIO);}
        OptionalResourceType_First
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        OptionalRangeType
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        ',' WordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalType
        OptionalTranslationType_Last
        ')'                         {$$ = TrLinkChildren ($<n>3,15,$4,$5,$6,$7,$8,$10,$12,$14,$16,$18,$19,$20,$21,$22,$23);}
    | WORDIO '('
        error ')'                   {$$ = AslDoError(); yyerrok;}
    ;


/******* Object References ***********************************************/


NameString
    : NameSeg                       {}
    | NAMESTRING                    {$$ = TrCreateValuedLeafNode (NAMESTRING, (ACPI_INTEGER) AslCompilerlval.s);}
    ;

NameSeg
    : NAMESEG                       {$$ = TrCreateValuedLeafNode (NAMESEG, (ACPI_INTEGER) AslCompilerlval.s);}
    ;


/******* Helper rules ****************************************************/


AmlPackageLengthTerm
    : Integer                       {$$ = TrUpdateNode (PACKAGE_LENGTH,(ASL_PARSE_NODE *) $1);}
    ;

OptionalAccessAttribTerm
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' ByteConstExpr             {$$ = $2;}
    | ',' AccessAttribKeyword       {$$ = $2;}
    ;

OptionalAddressRange
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' AddressKeyword            {$$ = $2;}
    ;

OptionalByteConstExpr
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' ByteConstExpr             {$$ = $2;}
    ;

OptionalCount
    :                               {$$ = TrCreateLeafNode (ONES);}       /* Placeholder is a OnesOp object */
    | ',' TermArg                   {$$ = $2;}
    ;

OptionalDecodeType
    : ','                           {$$ = NULL;}
    | ',' DecodeKeyword             {$$ = $2;}
    ;

OptionalDWordConstExpr
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' DWordConstExpr            {$$ = $2;}
    ;

OptionalListTermArg
    :                               {$$ = TrCreateLeafNode (ZERO);}       /* Placeholder is a ZeroOp object */
    | ','                           {$$ = TrCreateLeafNode (ZERO);}       /* Placeholder is a ZeroOp object */
    | ',' TermArg                   {$$ = $2;}
    ;

OptionalMaxType
    : ','                           {$$ = NULL;}
    | ',' MaxKeyword                {$$ = $2;}
    ;

OptionalMemType
    : ','                           {$$ = NULL;}
    | ',' MemTypeKeyword            {$$ = $2;}
    ;

OptionalMinType
    : ','                           {$$ = NULL;}
    | ',' MinKeyword                {$$ = $2;}
    ;

OptionalNameString
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' NameString                {$$ = $2;}
    ;

OptionalNameString_Last
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' NameString                {$$ = $2;}
    ;

OptionalNameString_First
    :                               {$$ = NULL;}
    | NameString                    {$$ = $1;}
    ;

OptionalObjectTypeKeyword
    :                               {$$ = TrCreateLeafNode (OBJECTTYPE_UNK);}
    | ',' ObjectTypeKeyword         {$$ = $2;}

OptionalRangeType
    : ','                           {$$ = NULL;}
    | ',' RangeTypeKeyword          {$$ = $2;}
    ;

OptionalReference
    :                               {$$ = TrCreateLeafNode (ZERO);}       /* Placeholder is a ZeroOp object */
    | ','                           {$$ = TrCreateLeafNode (ZERO);}       /* Placeholder is a ZeroOp object */
    | ',' DataObject                {$$ = $2;}
    | ',' NameString                {$$ = $2;}
    ;

OptionalResourceType_First
    :                               {$$ = NULL;}
    | ResourceTypeKeyword           {$$ = $1;}
    ;

OptionalSerializeRuleKeyword
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' SerializeRuleKeyword      {$$ = $2;}
    ;

OptionalShareType
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' ShareTypeKeyword          {$$ = $2;}
    ;

OptionalStringData
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' StringData                {$$ = $2;}
    ;

OptionalTermArg
    :                               {$$ = NULL;}
    | TermArg                       {$$ = $1;}
    ;

OptionalType
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' TypeKeyword               {$$ = $2;}
    ;

OptionalType_Last
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' TypeKeyword               {$$ = $2;}
    ;

OptionalTranslationType_Last
    :                               {$$ = NULL;}
    | ','                           {$$ = NULL;}
    | ',' TranslationKeyword        {$$ = $2;}
    ;


TermArgItem
    : ',' TermArg                   {$$ = $2;}
    | ',' error                     {$$ = AslDoError (); yyerrok;}
    ;

NameStringItem
    : ',' NameString                {$$ = $2;}
    | ',' error                     {$$ = AslDoError (); yyerrok;}
    ;


%%

/* programs */

int
AslCompilerwrap(void)
{
  return 1;
}

void *
AslLocalAllocate (unsigned int Size)
{
    void                *Mem;


    DbgPrint (ASL_PARSE_OUTPUT, "\nAslLocalAllocate: Expanding Stack to %d\n\n", Size);

    Mem = _UtCallocate (Size, 0, "", 0);
    if (!Mem)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_MEMORY_ALLOCATION,
                        Gbl_CurrentLineNumber, Gbl_LogicalLineNumber,
                        Gbl_InputByteCount, Gbl_CurrentColumn,
                        Gbl_Files[ASL_FILE_INPUT].Filename, NULL);
        exit (1);
    }

    return (Mem);
}

ASL_PARSE_NODE *
AslDoError (void)
{


    return (TrCreateLeafNode (ERRORNODE));

}
