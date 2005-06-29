
%{
/******************************************************************************
 *
 * Module Name: aslcompiler.y - Bison input file (ASL grammar and actions)
 *              $Revision: 1.22 $
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

#define YYDEBUG 1
#define YYERROR_VERBOSE 1

/*
 * State stack - compiler will fault if it overflows.   (Default was 200)
 */
#define YYINITDEPTH 600

#include "AslCompiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acpi.h"

extern int      AslCompilererror(char* s);
extern int      AslCompilerlex();
extern char     *AslCompilertext;

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
 * instead (#define	YYFBAD		32768), so we can define it correctly here.
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
	int             i;
	long            l;
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
%token <i> COPY
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
%token <i> STRING
%token <s> STRING_LITERAL
%token <i> SUBTRACT
%token <i> SWITCH
%token <i> THERMALZONE
%token <i> TOBCD
%token <i> TOBUFFER
%token <i> TODECIMALSTRING
%token <i> TOHEXSTRING
%token <i> TOINTEGER
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
%type <n> DataRefObject
%type <n> ComputationalData
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

%type <n> Type1Opcode
%type <n> Type2Opcode
%type <n> Type3Opcode
%type <n> Type4Opcode
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
%type <n> CopyTerm
%type <n> CopyTarget
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
%type <n> StringTerm
%type <n> SubtractTerm
%type <n> ToBCDTerm
%type <n> ToBufferTerm
%type <n> ToDecimalStringTerm
%type <n> ToHexStringTerm
%type <n> ToIntegerTerm
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
%type <n> UserDefRegionSpace
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
%type <n> DwordConst
%type <n> QwordConst

%type <n> String

%type <n> ConstTerm
%type <n> ByteConstExpr
%type <n> WordConstExpr
%type <n> DWordConstExpr
%type <n> QWordConstExpr
%type <n> ConstExprTerm

%type <n> BufferTerm
%type <n> BufferData
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


/* TBD: Could not find in spec */

%type <n> ObjectReference
%type <n> DDBHandle


%type <n> NameString
%type <n> NameSeg


/* Local types that help construct the AML, not in ACPI spec */

%type <n> IncludeEndTerm
%type <n> AmlPackageLengthTerm
%type <n> OptionalComma
%type <n> OptionalByteConstExpr
%type <n> OptionalDWordConstExpr
%type <n> OptionalAccessAttribKeyword
%type <n> OptionalSerializeRuleKeyword
%type <n> OptionalResourceType
%type <n> OptionalMinType
%type <n> OptionalMaxType
%type <n> OptionalMemType
%type <n> OptionalDecodeType
%type <n> OptionalRangeType
%type <n> OptionalShareType
%type <n> OptionalTermList
%type <n> OptionalType
%type <n> OptionalTranslationType
%type <n> OptionalStringData 
%type <n> OptionalNameString 
%type <n> OptionalNameString_First 
%type <n> OptionalAddressRange

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
    ;

DefinitionBlockTerm
    : DEFINITIONBLOCK '('       {$$ = TrCreateLeafNode (DEFINITIONBLOCK)}
        String ','
        String ','
        ByteConst ','
        String ','
        String ','
        DwordConst
        ')'                     {TrSetEndLineNumber ($<n>3)}
            '{' TermList '}'    {$$ = TrLinkChildren ($<n>3,7,$4,$6,$8,$10,$12,$14,$18)}
                                
    ;

TermList
    :                           {$$ = NULL}
    | Term TermList             {$$ = TrLinkPeerNode ($1,$2)}
    ;

Term
    : Object                    {}
    | Type1Opcode               {}
    | Type2Opcode               {}
    | error                     {$$= NULL}
    ;

CompilerDirective
    : IncludeTerm               {}
    | IncludeCStyleTerm         {$$= NULL}
    | ExternalTerm              {}
    ;

ObjectList
    :                           {$$ = NULL}
    | Object ObjectList         {$$ = TrLinkPeerNode ($1,$2)}
    ;

Object
    : CompilerDirective         {}
    | NamedObject               {}
    | NameSpaceModifier         {}
    ;

DataObject
    : BufferData                {}
    | PackageData               {}
    | IntegerData               {}
    | StringData                {}
    ;

DataRefObject
    : DataObject                {}
    | ObjectReference           {}
    | DDBHandle                 {}
    ;

ComputationalData
    : BufferData                {}
    | IntegerData               {}
    | StringData                {}
    ;

BufferData
    : Type5Opcode               {}
    | BufferTerm                {}
    ;

PackageData
    : PackageTerm               {}
    ;

IntegerData
    : Type3Opcode               {}
    | Integer                   {}
    | ConstTerm                 {}
    ;
    
StringData
    : Type4Opcode               {}
    | String                    {}
    ;

NamedObject
    : BankFieldTerm             {}
    | CreateBitFieldTerm        {}
    | CreateByteFieldTerm       {}
    | CreateDWordFieldTerm      {}
    | CreateFieldTerm           {}
    | CreateQWordFieldTerm      {}
    | CreateWordFieldTerm       {}
    | DataRegionTerm            {}
    | DeviceTerm                {}
    | EventTerm                 {}
    | FieldTerm                 {}
    | IndexFieldTerm            {}
    | MethodTerm                {}
    | MutexTerm                 {}
    | OpRegionTerm              {}
    | PowerResTerm              {}
    | ProcessorTerm             {}
    | ThermalZoneTerm           {}
    ;

NameSpaceModifier
    : AliasTerm                 {}
    | NameTerm                  {}
    | ScopeTerm                 {}
    ;

UserTerm
    : NameString '('            {TrUpdateNode (METHODCALL, $1)}
        ArgList ')'             {$$ = TrLinkChildNode ($1,$4)}
    ;

ArgList
    :                           {$$ = NULL}
    | TermArg ArgListTail       {$$ = TrLinkPeerNode ($1,$2)}
    ;

ArgListTail
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}   /* Allows a trailing comma at list end */
    | ',' TermArg ArgListTail   {$$ = TrLinkPeerNode ($2,$3)}
    ;

TermArg
    : Type2Opcode               {}
    | DataRefObject             {}
    | ArgTerm                   {}
    | LocalTerm                 {}
    | error                     {$$= NULL}
    ;

Target 
    :                           {$$ = TrCreateLeafNode (ZERO)}       /* Placeholder is a ZeroOp object */
    | ','                       {$$ = TrCreateLeafNode (ZERO)}       /* Placeholder is a ZeroOp object */
    | ',' SuperName             {$$ = TrSetNodeFlags ($2, NODE_IS_TARGET)}
    | error                     {$$= NULL}
    ;


/* Opcode types */

Type1Opcode
    : BreakTerm                 {}
    | BreakPointTerm            {}
    | ContinueTerm              {}
    | FatalTerm                 {}
    | IfElseTerm                {}
    | LoadTerm                  {}
    | NoOpTerm                  {}
    | NotifyTerm                {}
    | ReleaseTerm               {}
    | ResetTerm                 {}
    | ReturnTerm                {}
    | SignalTerm                {}
    | SleepTerm                 {}
    | StallTerm                 {}
    | SwitchTerm                {}
    | UnloadTerm                {}
    | WhileTerm                 {}
    ;

Type2Opcode
    : AcquireTerm               {}
    | AddTerm                   {}
    | AndTerm                   {}
    | ConcatTerm                {}
    | ConcatResTerm             {}
    | CondRefOfTerm             {}
    | CopyTerm                  {}
    | DecTerm                   {}
    | DerefOfTerm               {}
    | DivideTerm                {}
    | FindSetLeftBitTerm        {}
    | FindSetRightBitTerm       {}
    | FromBCDTerm               {}
    | IncTerm                   {}
    | IndexTerm                 {}
    | LAndTerm                  {}
    | LEqualTerm                {}
    | LGreaterTerm              {}
    | LGreaterEqualTerm         {}
    | LLessTerm                 {}
    | LLessEqualTerm            {}
    | LNotTerm                  {}
    | LNotEqualTerm             {}
    | LoadTableTerm             {}
    | LOrTerm                   {}
    | MatchTerm                 {}
    | MidTerm                   {}
    | ModTerm                   {}
    | MultiplyTerm              {}
    | NAndTerm                  {}
    | NOrTerm                   {}
    | NotTerm                   {}
    | ObjectTypeTerm            {}
    | OrTerm                    {}
    | RefOfTerm                 {}
    | ShiftLeftTerm             {}
    | ShiftRightTerm            {}
    | SizeOfTerm                {}
    | StoreTerm                 {}
    | StringTerm                {}
    | SubtractTerm              {}
    | ToBCDTerm                 {}
    | ToBufferTerm              {}
    | ToDecimalStringTerm       {}
    | ToHexStringTerm           {}
    | ToIntegerTerm             {}
    | WaitTerm                  {}
    | XOrTerm                   {}
    | UserTerm                  {}
    ;


/*
 * A type 3 opcode evaluates to an Integer and cannot have a destination operand
 */

Type3Opcode
    : AddTerm                   {}
    | AndTerm                   {}
    | DecTerm                   {}
    | DivideTerm                {}
    | EISAIDTerm                {}
    | FindSetLeftBitTerm        {}
    | FindSetRightBitTerm       {}
    | FromBCDTerm               {}
    | IncTerm                   {}
    | IndexTerm                 {}
    | LAndTerm                  {}
    | LEqualTerm                {}
    | LGreaterTerm              {}
    | LGreaterEqualTerm         {}
    | LLessTerm                 {}
    | LLessEqualTerm            {}
    | LNotTerm                  {}
    | LNotEqualTerm             {}
    | LOrTerm                   {}
    | MatchTerm                 {}
    | ModTerm                   {}
    | MultiplyTerm              {}
    | NAndTerm                  {}
    | NOrTerm                   {}
    | NotTerm                   {}
    | OrTerm                    {}
    | ShiftLeftTerm             {}
    | ShiftRightTerm            {} 
    | SubtractTerm              {}
    | ToBCDTerm                 {}
    | ToIntegerTerm             {}
    | XOrTerm                   {}
    ;

Type4Opcode
    : ConcatTerm                {}
    | ToDecimalStringTerm       {}
    | ToHexStringTerm           {}
    | MidTerm                   {}
    | StringTerm                {}
    ;

Type5Opcode
    : ToBufferTerm              {}
    | ConcatTerm                {}
    | ConcatResTerm             {}
    | MidTerm                   {}
    | ResourceTemplateTerm      {}
    | UnicodeTerm               {}
    ;

Type6Opcode
    : RefOfTerm                 {}
    | DerefOfTerm               {}
    | IndexTerm                 {}
    | UserTerm                  {}
    ;

IncludeTerm
    : INCLUDE '('               {$$ = TrCreateLeafNode (INCLUDE)}
        String  ')'             {$$ = TrLinkChildren ($<n>3,1,$4);FlOpenIncludeFile ($4);}
        OptionalTermList        
        IncludeEndTerm          {$$ = TrLinkPeerNodes (3,$<n>3,$7,$8)}                     
    ;

IncludeEndTerm
    : INCLUDE_END               {$$ = TrCreateLeafNode (INCLUDE_END)}
    ;

IncludeCStyleTerm
    : INCLUDE_CSTYLE
        String                  {FlOpenIncludeFile ($2)}
    ;

ExternalTerm
    : EXTERNAL '('
        NameString ','
        ObjectTypeKeyword
        ')'                     {$$ = TrCreateNode (EXTERNAL,2,$3,$5)}
    ;



/******* Named Objects *******************************************************/


BankFieldTerm
    : BANKFIELD '('             {$$ = TrCreateLeafNode (BANKFIELD)}
        NameString ','
        NameString ','
        TermArg ','
        AccessTypeKeyword ','
        LockRuleKeyword ','
        UpdateRuleKeyword
        ')' '{' 
            FieldUnitList '}'
                                {$$ = TrLinkChildren ($<n>3,7,$4,$6,$8,$10,$12,$14,$17)}
    ;

FieldUnitList
    :                           {$$ = NULL}
    | FieldUnit 
        FieldUnitListTail       {$$ = TrLinkPeerNode ($1,$2)}
    ;

FieldUnitListTail
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}  /* Allows a trailing comma at list end */
    | ',' FieldUnit 
            FieldUnitListTail   {$$ = TrLinkPeerNode ($2,$3)}
    ;

FieldUnit
    : FieldUnitEntry            {}
    | OffsetTerm                {}
    | AccessAsTerm              {}
    ;

FieldUnitEntry
    : ',' AmlPackageLengthTerm  {$$ = TrCreateNode (RESERVED_BYTES,1,$2)}
    | NameSeg ',' 
        AmlPackageLengthTerm    {$$ = TrLinkChildNode ($1,$3)}
    ;

OffsetTerm
    : OFFSET '('
        AmlPackageLengthTerm
        ')'                     {$$ = TrCreateNode (OFFSET,1,$3)}
    ;

AccessAsTerm
    : ACCESSAS '('
        AccessTypeKeyword
        OptionalAccessAttribTerm
        ')'                     {$$ = TrCreateNode (ACCESSAS,2,$3,$4)}
    ;

CreateBitFieldTerm
    : CREATEBITFIELD '('        {$$ = TrCreateLeafNode (CREATEBITFIELD)}
        TermArg ','
        TermArg ','
        NameString 
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$8)}
    ;

CreateByteFieldTerm
    : CREATEBYTEFIELD '('       {$$ = TrCreateLeafNode (CREATEBYTEFIELD)}
        TermArg ','
        TermArg ','
        NameString 
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$8)}
    ;

CreateDWordFieldTerm
    : CREATEDWORDFIELD '('      {$$ = TrCreateLeafNode (CREATEDWORDFIELD)}
        TermArg ','
        TermArg ','
        NameString 
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$8)}
    ;

CreateFieldTerm
    : CREATEFIELD '('           {$$ = TrCreateLeafNode (CREATEFIELD)}
        TermArg ','
        TermArg ','
        TermArg ','
        NameString 
        ')'                     {$$ = TrLinkChildren ($<n>3,4,$4,$6,$8,$10)}
    ;

CreateQWordFieldTerm
    : CREATEQWORDFIELD '('      {$$ = TrCreateLeafNode (CREATEQWORDFIELD)}
        TermArg ','
        TermArg ','
        NameString 
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$8)}
    ;

CreateWordFieldTerm
    : CREATEWORDFIELD '('       {$$ = TrCreateLeafNode (CREATEWORDFIELD)}
        TermArg ','
        TermArg ','
        NameString 
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$8)}
    ;

DataRegionTerm
    : DATATABLEREGION '('       {$$ = TrCreateLeafNode (DATATABLEREGION)}
        NameString ','
        TermArg ','
        TermArg ','
        TermArg 
        ')'                     {$$ = TrLinkChildren ($<n>3,4,$4,$6,$8,$10)}
    ;

DeviceTerm
    : DEVICE '('                {$$ = TrCreateLeafNode (DEVICE)}
        NameString
        ')' '{' 
            ObjectList '}' 
                                {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;

EventTerm
    : EVENT '('                 {$$ = TrCreateLeafNode (EVENT)}
        NameString
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

FieldTerm
    : FIELD '('                 {$$ = TrCreateLeafNode (FIELD)}
        NameString ','
        AccessTypeKeyword ','
        LockRuleKeyword ','
        UpdateRuleKeyword
        ')' '{' 
            FieldUnitList '}' 
                                {$$ = TrLinkChildren ($<n>3,5,$4,$6,$8,$10,$13)}
    ;

IndexFieldTerm
    : INDEXFIELD '('            {$$ = TrCreateLeafNode (INDEXFIELD)}
        NameString ','
        NameString ','
        AccessTypeKeyword ','
        LockRuleKeyword ','
        UpdateRuleKeyword
        ')' '{' 
            FieldUnitList '}' 
                                {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$12,$15)}
    ;

MethodTerm
    : METHOD  '('               {$$ = TrCreateLeafNode (METHOD)}
        NameString
        OptionalByteConstExpr
        OptionalSerializeRuleKeyword
        OptionalByteConstExpr
        ')' '{' 
            TermList '}'        {$$ = TrLinkChildren ($<n>3,5,$4,$5,$6,$7,$10)}
    ;

MutexTerm
    : MUTEX '('                 {$$ = TrCreateLeafNode (MUTEX)}
        NameString ','
        ByteConstExpr
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

OpRegionTerm
    : OPERATIONREGION '('       {$$ = TrCreateLeafNode (OPERATIONREGION)}
        NameString ',' 
        OpRegionSpaceIdTerm ',' 
        TermArg ',' 
        TermArg 
        ')'                     {$$ = TrLinkChildren ($<n>3,4,$4,$6,$8,$10)}
    ;

OpRegionSpaceIdTerm
    : RegionSpaceKeyword {}
    | ByteConst {}
    ;

PowerResTerm
    : POWERRESOURCE '('         {$$ = TrCreateLeafNode (POWERRESOURCE)}
        NameString ','
        ByteConstExpr ','
        WordConstExpr
        ')' '{' 
            ObjectList '}'      {$$ = TrLinkChildren ($<n>3,4,$4,$6,$8,$11)}
    ;

ProcessorTerm
    : PROCESSOR '('             {$$ = TrCreateLeafNode (PROCESSOR)}
        NameString ','
        ByteConstExpr
        OptionalDWordConstExpr
        OptionalByteConstExpr
        ')' '{' 
            ObjectList '}'      {$$ = TrLinkChildren ($<n>3,5,$4,$6,$7,$8,$11)}
    ;

ThermalZoneTerm
    : THERMALZONE '('           {$$ = TrCreateLeafNode (THERMALZONE)}
        NameString
        ')' '{' 
            ObjectList '}'      {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;



/******* Namespace modifiers *************************************************/


AliasTerm
    : ALIAS '('                 {$$ = TrCreateLeafNode (ALIAS)}
        NameString ','
        NameString 
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

NameTerm
    : NAME '('                  {$$ = TrCreateLeafNode (NAME)}
        NameString ','
        DataRefObject 
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

ScopeTerm
    : SCOPE '('                 {$$ = TrCreateLeafNode (SCOPE)}
        NameString
        ')' '{' 
            ObjectList '}'      {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;



/******* Type 1 opcodes *******************************************************/


BreakTerm
    : BREAK                     {$$ = TrCreateNode (BREAK, 0)}
    ;

BreakPointTerm
    : BREAKPOINT                {$$ = TrCreateNode (BREAKPOINT, 0)}
    ;

ContinueTerm
    : CONTINUE                  {$$ = TrCreateNode (CONTINUE, 0)}
    ;

FatalTerm
    : FATAL '('                 {$$ = TrCreateLeafNode (FATAL)}
        ByteConstExpr ','
        DWordConstExpr ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$8)}
    ;

IfElseTerm
    : IfTerm ElseTerm           {$$ = TrLinkPeerNode ($1,$2)}
    ;

IfTerm 
    : IF '('                    {$$ = TrCreateLeafNode (IF)}
        TermArg
        ')' '{' 
            TermList '}' 
                                {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;

ElseTerm
    :                           {$$ = NULL}
    | ELSE '{'                  {$$ = TrCreateLeafNode (ELSE)}
        TermList '}' 
                                {$$ = TrLinkChildren ($<n>3,1,$4)}

    | ELSEIF '{'                {$$ = TrCreateLeafNode (ELSEIF)}
        TermList '}' 
        ElseTerm 
                                {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

LoadTerm
    : LOAD '('                  {$$ = TrCreateLeafNode (LOAD)}
        NameString ','
        SuperName 
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

NoOpTerm
    : NOOP                      {$$ = TrCreateNode (NOOP, 0)}
    ;

NotifyTerm 
    : NOTIFY '('                {$$ = TrCreateLeafNode (NOTIFY)}
        SuperName ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

ReleaseTerm
    : RELEASE '('               {$$ = TrCreateLeafNode (RELEASE)}
        SuperName
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    

ResetTerm
    : RESET '('                 {$$ = TrCreateLeafNode (RESET)}
        SuperName
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

ReturnTerm
    : RETURN '('                {$$ = TrCreateLeafNode (RETURN)}
        OptionalTermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

SignalTerm
    : SIGNAL '('                {$$ = TrCreateLeafNode (SIGNAL)}
        SuperName
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

SleepTerm
    : SLEEP '('                 {$$ = TrCreateLeafNode (SLEEP)}
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;
StallTerm
    : STALL '('                 {$$ = TrCreateLeafNode (STALL)}
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

SwitchTerm
    : SWITCH '('                {$$ = TrCreateLeafNode (SWITCH)}
        TermArg
        ')' '{' 
            CaseTermList '}' 
                                {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;

CaseTermList
    :                           {}
    | CaseTerm                  {}
    | DefaultTerm 
        DefaultTermList         {}
    | CaseTerm 
        CaseTermList            {}
    ;

DefaultTermList
    :                           {}
    | CaseTerm                  {}
    | CaseTerm 
        DefaultTermList         {}
    ;

CaseTerm
    : CASE '('                  {$$ = TrCreateLeafNode (CASE)}
        DataObject
        ')' '{' 
            TermList '}' 
                                {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;

DefaultTerm
    : DEFAULT '{'               {$$ = TrCreateLeafNode (DEFAULT)}  
        TermList '}' 
                                {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

UnloadTerm
    : UNLOAD '('                {$$ = TrCreateLeafNode (UNLOAD)}  
        SuperName
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

WhileTerm
    : WHILE '('                 {$$ = TrCreateLeafNode (WHILE)}  
        TermArg
        ')' '{' TermList '}' 
                                {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;


/******* Type 2 opcodes *******************************************************/

AcquireTerm
    : ACQUIRE '('               {$$ = TrCreateLeafNode (ACQUIRE)}  
        SuperName ','
        WordConstExpr
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}

AddTerm
    : ADD '('                   {$$ = TrCreateLeafNode (ADD)}  
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

AndTerm
    : AND '('                   {$$ = TrCreateLeafNode (AND)}  
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

ConcatTerm
    : CONCATENATE '('           {$$ = TrCreateLeafNode (CONCATENATE)}  
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

ConcatResTerm
    : CONCATENATERESTEMPLATE '('    {$$ = TrCreateLeafNode (CONCATENATERESTEMPLATE)}  
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

CondRefOfTerm
    : CONDREFOF '('             {$$ = TrCreateLeafNode (CONDREFOF)}  
        SuperName
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$5)}
    ;

CopyTerm
    : COPY '('                  {$$ = TrCreateLeafNode (COPY)}  
        TermArg ','
        CopyTarget
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

CopyTarget
    : NameString {}
    | LocalTerm {}
    | ArgTerm {}
    ;

DecTerm
    : DECREMENT '('             {$$ = TrCreateLeafNode (DECREMENT)}  
        SuperName
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

DerefOfTerm
    : DEREFOF '('               {$$ = TrCreateLeafNode (DEREFOF)}  
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

DivideTerm
    : DIVIDE '('                {$$ = TrCreateLeafNode (DIVIDE)}  
        TermArg ','
        TermArg
        Target
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,4,$4,$6,$7,$8)}
    ;

FindSetLeftBitTerm
    : FINDSETLEFTBIT '('        {$$ = TrCreateLeafNode (FINDSETLEFTBIT)}  
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$5)}
    ;

FindSetRightBitTerm
    : FINDSETRIGHTBIT '('       {$$ = TrCreateLeafNode (FINDSETRIGHTBIT)}  
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$5)}
    ;

FromBCDTerm
    : FROMBCD '('               {$$ = TrCreateLeafNode (FROMBCD)}  
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$5)}
    ;

IncTerm
    : INCREMENT '('             {$$ = TrCreateLeafNode (INCREMENT)}  
        SuperName
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

IndexTerm
    : INDEX '('                 {$$ = TrCreateLeafNode (INDEX)}  
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

LAndTerm
    : LAND '('                  {$$ = TrCreateLeafNode (LAND)}  
        TermArg ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

LEqualTerm
    : LEQUAL '('                {$$ = TrCreateLeafNode (LEQUAL)}
        TermArg ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

LGreaterTerm
    : LGREATER '('              {$$ = TrCreateLeafNode (LGREATER)}
        TermArg ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

LGreaterEqualTerm
    : LGREATEREQUAL '('         {$$ = TrCreateLeafNode (LGREATEREQUAL)}
        TermArg ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

LLessTerm
    : LLESS '('                 {$$ = TrCreateLeafNode (LLESS)}
        TermArg ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

LLessEqualTerm
    : LLESSEQUAL '('            {$$ = TrCreateLeafNode (LLESSEQUAL)}
        TermArg ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

LNotTerm
    : LNOT '('                  {$$ = TrCreateLeafNode (LNOT)}
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

LNotEqualTerm
    : LNOTEQUAL '('             {$$ = TrCreateLeafNode (LNOTEQUAL)}
        TermArg ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

LoadTableTerm
    : LOADTABLE '('             {$$ = TrCreateLeafNode (LOADTABLE)}
        TermArg ','
        TermArg ','
        TermArg
        OptionalListTermArg
        OptionalListTermArg
        OptionalListTermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$9,$10,$11)}
    ;

LOrTerm
    : LOR '('                   {$$ = TrCreateLeafNode (LOR)}
        TermArg ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

MatchTerm
    : MATCH '('                 {$$ = TrCreateLeafNode (MATCH)}
        TermArg ','
        MatchOpKeyword ','
        TermArg ','
        MatchOpKeyword ','
        TermArg ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$12,$14)}
    ;

MidTerm
    : MID '('                   {$$ = TrCreateLeafNode (MID)}
        TermArg ','
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,4,$4,$6,$8,$9)}
    ;

ModTerm
    : MOD '('                   {$$ = TrCreateLeafNode (MOD)}
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

MultiplyTerm
    : MULTIPLY '('              {$$ = TrCreateLeafNode (MULTIPLY)}
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

NAndTerm
    : NAND '('                  {$$ = TrCreateLeafNode (NAND)}
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

NOrTerm
    : NOR '('                   {$$ = TrCreateLeafNode (NOR)}
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

NotTerm
    : NOT '('                   {$$ = TrCreateLeafNode (NOT)}
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$5)}
    ;

ObjectTypeTerm
    : OBJECTTYPE '('            {$$ = TrCreateLeafNode (OBJECTTYPE)}
        SuperName
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

OrTerm
    : OR '('                    {$$ = TrCreateLeafNode (OR)}
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

/*
 * In RefOf, the node isn't really a target, but we can't keep track of it after
 * we've taken a pointer to it. (hard to tell if a local becomes initialized this way.)
 */
RefOfTerm
    : REFOF '('                 {$$ = TrCreateLeafNode (REFOF)}
        SuperName
        ')'                     {$$ = TrLinkChildren ($<n>3,1,TrSetNodeFlags ($4, NODE_IS_TARGET))}
    ;

ShiftLeftTerm
    : SHIFTLEFT '('             {$$ = TrCreateLeafNode (SHIFTLEFT)}
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

ShiftRightTerm
    : SHIFTRIGHT '('            {$$ = TrCreateLeafNode (SHIFTRIGHT)}
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

SizeOfTerm
    : SIZEOF '('                {$$ = TrCreateLeafNode (SIZEOF)}
        SuperName
        ')'                     {$$ = TrLinkChildren ($<n>3,1,$4)}
    ;

StoreTerm
    : STORE '('                 {$$ = TrCreateLeafNode (STORE)}
        TermArg ','
        SuperName
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,TrSetNodeFlags ($6, NODE_IS_TARGET))}
    ;

StringTerm
    : STRING '('                {$$ = TrCreateLeafNode (STRING)}
        TermArg
        OptionalListTermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6)}
    ;

SubtractTerm
    : SUBTRACT '('              {$$ = TrCreateLeafNode (SUBTRACT)}
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

ToBCDTerm
    : TOBCD '('                 {$$ = TrCreateLeafNode (TOBCD)}
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$5)}
    ;

ToBufferTerm
    : TOBUFFER '('              {$$ = TrCreateLeafNode (TOBUFFER)}
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$5)}
    ;

ToDecimalStringTerm
    : TODECIMALSTRING '('       {$$ = TrCreateLeafNode (TODECIMALSTRING)}
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$5)}
    ;

ToHexStringTerm
    : TOHEXSTRING '('           {$$ = TrCreateLeafNode (TOHEXSTRING)}
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$5)}
    ;

ToIntegerTerm
    : TOINTEGER '('             {$$ = TrCreateLeafNode (TOINTEGER)}
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$5)}
    ;

WaitTerm
    : WAIT '('                  {$$ = TrCreateLeafNode (WAIT)}
        SuperName ','
        TermArg
        ')'                     {$$ = TrLinkChildren ($<n>3,2,$4,$6)}
    ;

XOrTerm
    : XOR '('                   {$$ = TrCreateLeafNode (XOR)}
        TermArg ','
        TermArg
        Target
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;



/******* Keywords *************************************************************/


ObjectTypeKeyword
    : OBJECTTYPE_UNK            {$$ = TrCreateLeafNode (OBJECTTYPE_UNK)}
    | OBJECTTYPE_INT            {$$ = TrCreateLeafNode (OBJECTTYPE_INT)}
    | OBJECTTYPE_STR            {$$ = TrCreateLeafNode (OBJECTTYPE_STR)}
    | OBJECTTYPE_BUF            {$$ = TrCreateLeafNode (OBJECTTYPE_BUF)}
    | OBJECTTYPE_PKG            {$$ = TrCreateLeafNode (OBJECTTYPE_PKG)}
    | OBJECTTYPE_FLD            {$$ = TrCreateLeafNode (OBJECTTYPE_FLD)}
    | OBJECTTYPE_DEV            {$$ = TrCreateLeafNode (OBJECTTYPE_DEV)}
    | OBJECTTYPE_EVT            {$$ = TrCreateLeafNode (OBJECTTYPE_EVT)}
    | OBJECTTYPE_MTH            {$$ = TrCreateLeafNode (OBJECTTYPE_MTH)}
    | OBJECTTYPE_MTX            {$$ = TrCreateLeafNode (OBJECTTYPE_MTX)}
    | OBJECTTYPE_OPR            {$$ = TrCreateLeafNode (OBJECTTYPE_OPR)}
    | OBJECTTYPE_POW            {$$ = TrCreateLeafNode (OBJECTTYPE_POW)}
    | OBJECTTYPE_THZ            {$$ = TrCreateLeafNode (OBJECTTYPE_THZ)}
    | OBJECTTYPE_BFF            {$$ = TrCreateLeafNode (OBJECTTYPE_BFF)}
    | OBJECTTYPE_DDB            {$$ = TrCreateLeafNode (OBJECTTYPE_DDB)}
    | error                     {$$= NULL}
    ;

AccessTypeKeyword
    : ACCESSTYPE_ANY            {$$ = TrCreateLeafNode (ACCESSTYPE_ANY)}
    | ACCESSTYPE_BYTE           {$$ = TrCreateLeafNode (ACCESSTYPE_BYTE)}
    | ACCESSTYPE_WORD           {$$ = TrCreateLeafNode (ACCESSTYPE_WORD)}
    | ACCESSTYPE_DWORD          {$$ = TrCreateLeafNode (ACCESSTYPE_DWORD)}
    | ACCESSTYPE_QWORD          {$$ = TrCreateLeafNode (ACCESSTYPE_QWORD)}
    | ACCESSTYPE_BUF            {$$ = TrCreateLeafNode (ACCESSTYPE_BUF)}
    | error                     {$$= NULL}
    ;

AccessAttribKeyword
    : ACCESSATTRIB_QUICK        {$$ = TrCreateLeafNode (ACCESSATTRIB_QUICK )}
    | ACCESSATTRIB_SND_RCV      {$$ = TrCreateLeafNode (ACCESSATTRIB_SND_RCV)}
    | ACCESSATTRIB_BYTE         {$$ = TrCreateLeafNode (ACCESSATTRIB_BYTE)}
    | ACCESSATTRIB_WORD         {$$ = TrCreateLeafNode (ACCESSATTRIB_WORD)}
    | ACCESSATTRIB_BLOCK        {$$ = TrCreateLeafNode (ACCESSATTRIB_BLOCK)}
    | ACCESSATTRIB_CALL         {$$ = TrCreateLeafNode (ACCESSATTRIB_CALL)}
    | error                     {$$= NULL}
    ;

LockRuleKeyword
    : LOCKRULE_LOCK             {$$ = TrCreateLeafNode (LOCKRULE_LOCK)}
    | LOCKRULE_NOLOCK           {$$ = TrCreateLeafNode (LOCKRULE_NOLOCK)}
    | error                     {$$= NULL}
    ;

UpdateRuleKeyword
    : UPDATERULE_PRESERVE       {$$ = TrCreateLeafNode (UPDATERULE_PRESERVE)}
    | UPDATERULE_ONES           {$$ = TrCreateLeafNode (UPDATERULE_ONES)}
    | UPDATERULE_ZEROS          {$$ = TrCreateLeafNode (UPDATERULE_ZEROS)}
    | error                     {$$= NULL}
    ;

RegionSpaceKeyword
    : UserDefRegionSpace        {}
    | REGIONSPACE_IO            {$$ = TrCreateLeafNode (REGIONSPACE_IO)}
    | REGIONSPACE_MEM           {$$ = TrCreateLeafNode (REGIONSPACE_MEM)}
    | REGIONSPACE_PCI           {$$ = TrCreateLeafNode (REGIONSPACE_PCI)}
    | REGIONSPACE_EC            {$$ = TrCreateLeafNode (REGIONSPACE_EC)}
    | REGIONSPACE_SMBUS         {$$ = TrCreateLeafNode (REGIONSPACE_SMBUS)}
    | REGIONSPACE_CMOS          {$$ = TrCreateLeafNode (REGIONSPACE_CMOS)}
    | REGIONSPACE_PCIBAR        {$$ = TrCreateLeafNode (REGIONSPACE_PCIBAR)}
    | error                     {$$= NULL}
    ;

AddressSpaceKeyword
    : RegionSpaceKeyword        {}
    | ADDRESSSPACE_FFIXEDHW     {$$ = TrCreateLeafNode (ADDRESSSPACE_FFIXEDHW)}
    | error                     {$$= NULL}
    ;

UserDefRegionSpace
    : ByteConst                 {}
    ;

SerializeRuleKeyword
    : SERIALIZERULE_SERIAL      {$$ = TrCreateLeafNode (SERIALIZERULE_SERIAL)}
    | SERIALIZERULE_NOTSERIAL   {$$ = TrCreateLeafNode (SERIALIZERULE_NOTSERIAL)}
    | error                     {$$= NULL}
    ;

MatchOpKeyword
    : MATCHTYPE_MTR             {$$ = TrCreateLeafNode (MATCHTYPE_MTR)}
    | MATCHTYPE_MEQ             {$$ = TrCreateLeafNode (MATCHTYPE_MEQ)}
    | MATCHTYPE_MLE             {$$ = TrCreateLeafNode (MATCHTYPE_MLE)}
    | MATCHTYPE_MLT             {$$ = TrCreateLeafNode (MATCHTYPE_MLT)}
    | MATCHTYPE_MGE             {$$ = TrCreateLeafNode (MATCHTYPE_MGE)}
    | MATCHTYPE_MGT             {$$ = TrCreateLeafNode (MATCHTYPE_MGT)}
    | error                     {$$= NULL}
    ;

DMATypeKeyword
    : DMATYPE_A                 {$$ = TrCreateLeafNode (DMATYPE_A)}
    | DMATYPE_COMPATIBILITY     {$$ = TrCreateLeafNode (DMATYPE_COMPATIBILITY)}
    | DMATYPE_B                 {$$ = TrCreateLeafNode (DMATYPE_B)}
    | DMATYPE_F                 {$$ = TrCreateLeafNode (DMATYPE_F)}
    | error                     {$$= NULL}
    ;

BusMasterKeyword
    : BUSMASTERTYPE_MASTER      {$$ = TrCreateLeafNode (BUSMASTERTYPE_MASTER)}
    | BUSMASTERTYPE_NOTMASTER   {$$ = TrCreateLeafNode (BUSMASTERTYPE_NOTMASTER)}
    | error                     {$$= NULL}
    ;

XferTypeKeyword
    : XFERTYPE_8                {$$ = TrCreateLeafNode (XFERTYPE_8)}
    | XFERTYPE_8_16             {$$ = TrCreateLeafNode (XFERTYPE_8_16)}
    | XFERTYPE_16               {$$ = TrCreateLeafNode (XFERTYPE_16)}
    | error                     {$$= NULL}
    ;

ResourceTypeKeyword
    : RESOURCETYPE_CONSUMER     {$$ = TrCreateLeafNode (RESOURCETYPE_CONSUMER)}
    | RESOURCETYPE_PRODUCER     {$$ = TrCreateLeafNode (RESOURCETYPE_PRODUCER)}
    | error                     {$$= NULL}
    ;

MinKeyword
    : MINTYPE_FIXED             {$$ = TrCreateLeafNode (MINTYPE_FIXED)}
    | MINTYPE_NOTFIXED          {$$ = TrCreateLeafNode (MINTYPE_NOTFIXED)}
    | error                     {$$= NULL}
    ;

MaxKeyword
    : MAXTYPE_FIXED             {$$ = TrCreateLeafNode (MAXTYPE_FIXED)}
    | MAXTYPE_NOTFIXED          {$$ = TrCreateLeafNode (MAXTYPE_NOTFIXED)}
    | error                     {$$= NULL}
    ;

DecodeKeyword
    : DECODETYPE_POS            {$$ = TrCreateLeafNode (DECODETYPE_POS)}
    | DECODETYPE_SUB            {$$ = TrCreateLeafNode (DECODETYPE_SUB)}
    | error                     {$$= NULL}
    ;

RangeTypeKeyword
    : RANGETYPE_ISAONLY         {$$ = TrCreateLeafNode (RANGETYPE_ISAONLY)}
    | RANGETYPE_NONISAONLY      {$$ = TrCreateLeafNode (RANGETYPE_NONISAONLY)}
    | RANGETYPE_ENTIRE          {$$ = TrCreateLeafNode (RANGETYPE_ENTIRE)}
    | error                     {$$= NULL}
    ;

MemTypeKeyword
    : MEMTYPE_CACHEABLE         {$$ = TrCreateLeafNode (MEMTYPE_CACHEABLE)}
    | MEMTYPE_WRITECOMBINING    {$$ = TrCreateLeafNode (MEMTYPE_WRITECOMBINING)}
    | MEMTYPE_PREFETCHABLE      {$$ = TrCreateLeafNode (MEMTYPE_PREFETCHABLE)}
    | MEMTYPE_NONCACHEABLE      {$$ = TrCreateLeafNode (MEMTYPE_NONCACHEABLE)}
    | error                     {$$= NULL}
    ;

ReadWriteKeyword
    : READWRITETYPE_BOTH        {$$ = TrCreateLeafNode (READWRITETYPE_BOTH)}
    | READWRITETYPE_READONLY    {$$ = TrCreateLeafNode (READWRITETYPE_READONLY)}
    | error                     {$$= NULL}
    ;

InterruptTypeKeyword
    : INTTYPE_EDGE              {$$ = TrCreateLeafNode (INTTYPE_EDGE)}
    | INTTYPE_LEVEL             {$$ = TrCreateLeafNode (INTTYPE_LEVEL)}
    | error                     {$$= NULL}
    ;

InterruptLevel
    : INTLEVEL_ACTIVEHIGH       {$$ = TrCreateLeafNode (INTLEVEL_ACTIVEHIGH)}
    | INTLEVEL_ACTIVELOW        {$$ = TrCreateLeafNode (INTLEVEL_ACTIVELOW)}
    | error                     {$$= NULL}
    ;

ShareTypeKeyword
    : SHARETYPE_SHARED          {$$ = TrCreateLeafNode (SHARETYPE_SHARED)}
    | SHARETYPE_EXCLUSIVE       {$$ = TrCreateLeafNode (SHARETYPE_EXCLUSIVE)}
    | error                     {$$= NULL}
    ;

IODecodeKeyword
    : IODECODETYPE_16           {$$ = TrCreateLeafNode (IODECODETYPE_16)}
    | IODECODETYPE_10           {$$ = TrCreateLeafNode (IODECODETYPE_10)}
    | error                     {$$= NULL}
    ;

TypeKeyword
    : TYPE_TRANSLATION          {$$ = TrCreateLeafNode (TYPE_TRANSLATION)}
    | TYPE_STATIC               {$$ = TrCreateLeafNode (TYPE_STATIC)}
    | error                     {$$= NULL}
    ;

TranslationKeyword
    : TRANSLATIONTYPE_SPARSE    {$$ = TrCreateLeafNode (TRANSLATIONTYPE_SPARSE)}
    | TRANSLATIONTYPE_DENSE     {$$ = TrCreateLeafNode (TRANSLATIONTYPE_DENSE)}
    | error                     {$$= NULL}
    ;

AddressKeyword
    : ADDRESSTYPE_MEMORY        {$$ = TrCreateLeafNode (ADDRESSTYPE_MEMORY)}
    | ADDRESSTYPE_RESERVED      {$$ = TrCreateLeafNode (ADDRESSTYPE_RESERVED)}
    | ADDRESSTYPE_NVS           {$$ = TrCreateLeafNode (ADDRESSTYPE_NVS)}
    | ADDRESSTYPE_ACPI          {$$ = TrCreateLeafNode (ADDRESSTYPE_ACPI)}
    | error                     {$$= NULL}
    ;

   

/******* Miscellaneous Types **************************************************/


SuperName
    : NameString                {}
    | ArgTerm                   {}
    | LocalTerm                 {}
    | DebugTerm                 {}
    | Type6Opcode               {}
    | UserTerm                  {}
    | error                     {$$= NULL}
    ;

ArgTerm
    : ARG0                      {$$ = TrCreateLeafNode (ARG0)}
    | ARG1                      {$$ = TrCreateLeafNode (ARG1)}
    | ARG2                      {$$ = TrCreateLeafNode (ARG2)}
    | ARG3                      {$$ = TrCreateLeafNode (ARG3)}
    | ARG4                      {$$ = TrCreateLeafNode (ARG4)}
    | ARG5                      {$$ = TrCreateLeafNode (ARG5)}
    | ARG6                      {$$ = TrCreateLeafNode (ARG6)}
    | error                     {$$= NULL}
    ;

LocalTerm
    : LOCAL0                    {$$ = TrCreateLeafNode (LOCAL0)}
    | LOCAL1                    {$$ = TrCreateLeafNode (LOCAL1)}
    | LOCAL2                    {$$ = TrCreateLeafNode (LOCAL2)}
    | LOCAL3                    {$$ = TrCreateLeafNode (LOCAL3)}
    | LOCAL4                    {$$ = TrCreateLeafNode (LOCAL4)}
    | LOCAL5                    {$$ = TrCreateLeafNode (LOCAL5)}
    | LOCAL6                    {$$ = TrCreateLeafNode (LOCAL6)}
    | LOCAL7                    {$$ = TrCreateLeafNode (LOCAL7)}
    | error                     {$$= NULL}
    ;

DebugTerm
    : DEBUG                     {$$ = TrCreateLeafNode (DEBUG)}
    | error                     {$$= NULL}
    ;

Integer
    : INTEGER                   {$$ = TrCreateValuedLeafNode (INTEGER, (void *) AslCompilerlval.i)}
    | error                     {$$= NULL}
    ;

ByteConst
    : Integer                   {$$ = TrUpdateNode (BYTECONST, $1)}
    ;

WordConst
    : Integer                   {$$ = TrUpdateNode (WORDCONST, $1)}
    ;

DwordConst
    : Integer                   {$$ = TrUpdateNode (DWORDCONST, $1)}
    ;

QwordConst
    : Integer                   {$$ = TrUpdateNode (QWORDCONST, $1)}
    ;

String
    : STRING_LITERAL            {$$ = TrCreateValuedLeafNode (STRING_LITERAL, AslCompilerlval.s)}
    ;

/* REMOVED ERROR FROM ABOVE     | error                     {$$= NULL}
*/

/* 
 * TBD: Needs     | REVISION
 */

ConstTerm
    : ZERO                      {$$ = TrCreateLeafNode (ZERO)}
    | ONE                       {$$ = TrCreateLeafNode (ONE)}
    | ONES                      {$$ = TrCreateLeafNode (ONES)}
    | error                     {$$= NULL}
    ;

ByteConstExpr
    : Type3Opcode               {$$ = TrUpdateNode (BYTECONST, $1)}
    | ConstExprTerm             {$$ = TrUpdateNode (BYTECONST, $1)}
    | Integer                   {$$ = TrUpdateNode (BYTECONST, $1)}
    ;


WordConstExpr
    : Type3Opcode               {$$ = TrUpdateNode (WORDCONST, $1)}
    | ConstExprTerm             {$$ = TrUpdateNode (WORDCONST, $1)}
    | Integer                   {$$ = TrUpdateNode (WORDCONST, $1)}
    ;

DWordConstExpr
    : Type3Opcode               {$$ = TrUpdateNode (DWORDCONST, $1)}
    | ConstExprTerm             {$$ = TrUpdateNode (DWORDCONST, $1)}
    | Integer                   {$$ = TrUpdateNode (DWORDCONST, $1)}
    ;

QWordConstExpr
    : Type3Opcode               {$$ = TrUpdateNode (QWORDCONST, $1)}
    | ConstExprTerm             {$$ = TrUpdateNode (QWORDCONST, $1)}
    | Integer                   {$$ = TrUpdateNode (QWORDCONST, $1)}
    ;

ConstExprTerm
    : ZERO                      {$$ = TrCreateLeafNode (ZERO)}
    | ONE                       {$$ = TrCreateLeafNode (ONE)}
    | ONES                      {$$ = TrCreateLeafNode (ONES)}
    | error                     {$$= NULL}
    ;

BufferTerm
    : BUFFER '('                {$$ = TrCreateLeafNode (BUFFER)}
        OptionalTermArg
        ')' '{' 
            BufferData '}'      {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;

BufferData
    : ByteList                  {}
    | StringData                {}
    ;

ByteList
    : {$$ = NULL}
    | ByteConstExpr 
        ByteListTail            {$$ = TrLinkPeerNode ($1,$2)}
    ;

ByteListTail
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}   /* Allows a trailing comma at list end */
    | ',' ByteConstExpr 
        ByteListTail            {$$ = TrLinkPeerNode ($2,$3)}
    ;

DWordList
    :                           {$$ = NULL}
    | DWordConstExpr 
        DWordListTail           {$$ = TrLinkPeerNode ($1,$2)}
    ;

DWordListTail
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}   /* Allows a trailing comma at list end */
    | ',' DWordConstExpr 
        DWordListTail           {$$ = TrLinkPeerNode ($2,$3)}
    ;

PackageTerm
    : PACKAGE '('               {$$ = TrCreateLeafNode (PACKAGE)}
        PackageLengthTerm
        ')' '{' 
            PackageList '}'     {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;

PackageLengthTerm
    :                           {$$ = NULL}
    | ByteConstExpr             {}
    | TermArg                   {}
    ;

PackageList
    :                           {$$ = NULL}
    | PackageElement 
        PackageListTail         {$$ = TrLinkPeerNode ($1,$2)}
    ;

PackageListTail
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}   /* Allows a trailing comma at list end */
    | ',' PackageElement 
        PackageListTail         {$$ = TrLinkPeerNode ($2,$3)}
    ;

PackageElement
    : DataObject                {}
    | NameString                {}
    ;

EISAIDTerm
    : EISAID '(' 
        StringData ')'          {$$ = TrUpdateNode (EISAID, $3)}
    ;


/******* Resources and Memory ***********************************************/



ResourceTemplateTerm
    : RESOURCETEMPLATE '(' ')'
        '{' 
        ResourceMacroList '}'   {$$ = TrCreateNode (RESOURCETEMPLATE,3,
                                        TrCreateLeafNode (DEFAULT_ARG),
                                        TrCreateLeafNode (DEFAULT_ARG),$5)}
    ;

UnicodeTerm
    : UNICODE '('               {$$ = TrCreateLeafNode (UNICODE)}
        StringData
        ')'                     {$$ = TrLinkChildren ($<n>3,2,0,$4)}
    ;

ResourceMacroList
    :                           {$$ = NULL}
    | ResourceMacroTerm 
        ResourceMacroList       {$$ = TrLinkPeerNode ($1,$2)}
    ;

ResourceMacroTerm
    : DMATerm                   {}
    | DWordIOTerm               {}
    | DWordMemoryTerm           {}
    | EndDependentFnTerm        {}
    | FixedIOTerm               {}
    | InterruptTerm             {}
    | IOTerm                    {}
    | IRQNoFlagsTerm            {}
    | IRQTerm                   {}
    | Memory24Term              {}
    | Memory32FixedTerm         {}
    | Memory32Term              {}
    | QWordIOTerm               {}
    | QWordMemoryTerm           {}
    | RegisterTerm              {}
    | StartDependentFnTerm      {}
    | StartDependentFnNoPriTerm {}
    | VendorLongTerm            {}
    | VendorShortTerm           {}
    | WordBusNumberTerm         {}
    | WordIOTerm                {}
    ;

DMATerm
    : DMA '('                   {$$ = TrCreateLeafNode (DMA)}
        DMATypeKeyword ','
        BusMasterKeyword ','
        XferTypeKeyword
        OptionalNameString
        ')' '{'
            ByteList '}'        {$$ = TrLinkChildren ($<n>3,5,$4,$6,$8,$9,$12)}
    ;

DWordIOTerm
    : DWORDIO '('               {$$ = TrCreateLeafNode (DWORDIO)}
        OptionalResourceType
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        OptionalRangeType
        DWordConstExpr ','
        DWordConstExpr ','
        DWordConstExpr ','
        DWordConstExpr ','
        DWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalType
        OptionalTranslationType
        ')'                     {$$ = TrLinkChildren ($<n>3,15,$4,$5,$6,$7,$8,$9,$11,$13,$15,$17,$18,$19,$20,$21,$22)}
    ;

DWordMemoryTerm
    : DWORDMEMORY '('           {$$ = TrCreateLeafNode (DWORDMEMORY)}
        OptionalResourceType
        OptionalDecodeType
        OptionalMinType
        OptionalMaxType
        OptionalMemType
        ReadWriteKeyword ','
        DWordConstExpr ','
        DWordConstExpr ','
        DWordConstExpr ','
        DWordConstExpr ','
        DWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalAddressRange
        OptionalType
        ')'                     {$$ = TrLinkChildren ($<n>3,16,$4,$5,$6,$7,$8,$9,$11,$13,$15,$17,$19,$20,$21,$22,$23,$24)}
    ;

EndDependentFnTerm
    : ENDDEPENDENTFN '(' 
        ')'                     {$$ = TrCreateLeafNode (ENDDEPENDENTFN)}
    ;

FixedIOTerm
    : FIXEDIO '('               {$$ = TrCreateLeafNode (FIXEDIO)}
        WordConstExpr ','
        ByteConstExpr
        OptionalNameString
        ')'                     {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7)}
    ;

InterruptTerm
    : INTERRUPT '('             {$$ = TrCreateLeafNode (INTERRUPT)}
        OptionalResourceType
        InterruptTypeKeyword ','
        InterruptLevel
        OptionalShareType     
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        ')' '{'
            DWordList '}'       {$$ = TrLinkChildren ($<n>3,8,$4,$5,$7,$8,$9,$10,$11,$14)}
    ;

IOTerm
    : IO '('                    {$$ = TrCreateLeafNode (IO)}
        IODecodeKeyword ','
        WordConstExpr ','
        WordConstExpr ','
        ByteConstExpr ','
        ByteConstExpr
        OptionalNameString
        ')'                     {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$12,$13)}
    ;

IRQNoFlagsTerm
    : IRQNOFLAGS '('            {$$ = TrCreateLeafNode (IRQNOFLAGS)}
        OptionalNameString_First
        ')' '{' 
            ByteList '}'        {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;

IRQTerm
    : IRQ '('                   {$$ = TrCreateLeafNode (IRQ)}
        InterruptTypeKeyword ','
        InterruptLevel
        OptionalShareType     
        OptionalNameString
        ')' '{' 
            ByteList '}'        {$$ = TrLinkChildren ($<n>3,5,$4,$6,$7,$8,$11)}
    ;

Memory24Term
    : MEMORY24 '('              {$$ = TrCreateLeafNode (MEMORY24)}
        ReadWriteKeyword ','
        WordConstExpr ','
        WordConstExpr ','
        WordConstExpr ','
        WordConstExpr
        OptionalNameString
        ')'                     {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$12,$13)}
    ;

Memory32FixedTerm
    : MEMORY32FIXED '('         {$$ = TrCreateLeafNode (MEMORY32FIXED)}
        ReadWriteKeyword ','
        DWordConstExpr ','
        DWordConstExpr
        OptionalNameString
        ')'                     {$$ = TrLinkChildren ($<n>3,4,$4,$6,$8,$9)}
    ;

Memory32Term
    : MEMORY32 '('              {$$ = TrCreateLeafNode (MEMORY32)}
        ReadWriteKeyword ','
        DWordConstExpr ','
        DWordConstExpr ','
        DWordConstExpr ','
        DWordConstExpr
        OptionalNameString
        ')'                     {$$ = TrLinkChildren ($<n>3,6,$4,$6,$8,$10,$12,$13)}
    ;

QWordIOTerm
    : QWORDIO '('               {$$ = TrCreateLeafNode (QWORDIO)}
        OptionalResourceType
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        OptionalRangeType
        QWordConstExpr ','
        QWordConstExpr ','
        QWordConstExpr ','
        QWordConstExpr ','
        QWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalType
        OptionalTranslationType
        ')'                     {$$ = TrLinkChildren ($<n>3,15,$4,$5,$6,$7,$8,$9,$11,$13,$15,$17,$18,$19,$20,$21,$22)}
    ;

QWordMemoryTerm
    : QWORDMEMORY '('           {$$ = TrCreateLeafNode (QWORDMEMORY)}
        OptionalResourceType
        OptionalDecodeType
        OptionalMinType
        OptionalMaxType
        OptionalMemType
        ReadWriteKeyword ','
        QWordConstExpr ','
        QWordConstExpr ','
        QWordConstExpr ','
        QWordConstExpr ','
        QWordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalAddressRange
        OptionalType
        ')'                     {$$ = TrLinkChildren ($<n>3,16,$4,$5,$6,$7,$8,$9,$11,$13,$15,$17,$19,$20,$21,$22,$23,$24)}
    ;

RegisterTerm
    : REGISTER '('              {$$ = TrCreateLeafNode (REGISTER)}
        AddressKeyword ','
        ByteConstExpr ','
        ByteConstExpr ','
        QWordConstExpr
        ')'                     {$$ = TrLinkChildren ($<n>3,4,$4,$6,$8,$10)}
    ;

StartDependentFnTerm
    : STARTDEPENDENTFN '('      {$$ = TrCreateLeafNode (STARTDEPENDENTFN)}
        ByteConstExpr ','
        ByteConstExpr
        ')' '{' 
        ResourceMacroList '}'   {$$ = TrLinkChildren ($<n>3,3,$4,$6,$9)}
    ;
                
StartDependentFnNoPriTerm
    : STARTDEPENDENTFN_NOPRI '(' {$$ = TrCreateLeafNode (STARTDEPENDENTFN_NOPRI)}
        ')' '{' 
        ResourceMacroList '}'   {$$ = TrLinkChildren ($<n>3,1,$6)}
    ;
               
VendorLongTerm
    : VENDORLONG '('            {$$ = TrCreateLeafNode (VENDORLONG)}
        OptionalNameString_First
        ')' '{' 
            ByteList '}'        {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;
        
VendorShortTerm
    : VENDORSHORT '('           {$$ = TrCreateLeafNode (VENDORSHORT)}
        OptionalNameString_First
        ')' '{' 
            ByteList '}'        {$$ = TrLinkChildren ($<n>3,2,$4,$7)}
    ;
        
WordBusNumberTerm
    : WORDBUSNUMBER '('         {$$ = TrCreateLeafNode (WORDBUSNUMBER)}
        OptionalResourceType
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        WordConstExpr ','
        WordConstExpr ','
        WordConstExpr ','
        WordConstExpr ','
        WordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        ')'                     {$$ = TrLinkChildren ($<n>3,12,$4,$5,$6,$7,$8,$10,$12,$14,$16,$17,$18,$19)}
    ;

WordIOTerm
    : WORDIO '('                {$$ = TrCreateLeafNode (WORDIO)}
        OptionalResourceType
        OptionalMinType
        OptionalMaxType
        OptionalDecodeType
        OptionalRangeType
        WordConstExpr ','
        WordConstExpr ','
        WordConstExpr ','
        WordConstExpr ','
        WordConstExpr
        OptionalByteConstExpr
        OptionalStringData
        OptionalNameString
        OptionalType
        OptionalTranslationType
        ')'                     {$$ = TrLinkChildren ($<n>3,15,$4,$5,$6,$7,$8,$9,$11,$13,$15,$17,$18,$19,$20,$21,$22)}
    ;




/******* Object References ***********************************************/


NameString
    : NameSeg                   {}
    | NAMESTRING                {$$ = TrCreateValuedLeafNode (NAMESTRING, AslCompilerlval.s)}
    | error                     {$$ = NULL}
    ;

NameSeg 
    : NAMESEG                   {$$ = TrCreateValuedLeafNode (NAMESEG, AslCompilerlval.s)}
    | error                     {$$ = NULL}
    ;



/* TBD: Could not find in spec */

ObjectReference
    : NameString                {}
    ;

DDBHandle
    : String                    {}
    ;




/******* Helper rules ****************************************************/


AmlPackageLengthTerm
    : Integer                   {$$ = TrUpdateNode (PACKAGE_LENGTH,(ASL_PARSE_NODE *) $1)}
    ;


OptionalTermList
    :                           {$$ = NULL}
    | TermList                  {$$ = $1}
    ;


OptionalListTermArg
    :                           {$$ = NULL}
    | ',' TermArg               {$$ = $2}
    ;

OptionalTermArg
    :                           {$$ = NULL}
    | TermArg                   {$$ = $1}
    ;


OptionalComma
    :                           {}
    | ','                       {}
    ;

OptionalAccessAttribTerm
    :                           {$$ = NULL}
    | ',' ByteConstExpr         {$$ = $2}
    | ',' AccessAttribKeyword   {$$ = $2}
    | ','                       {$$ = NULL}
    ;

OptionalAccessAttribKeyword
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}
    | ',' AccessAttribKeyword   {$$ = $2}
    ;

OptionalSerializeRuleKeyword
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}
    | ',' SerializeRuleKeyword  {$$ = $2}


OptionalByteConstExpr
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}
    | ',' ByteConstExpr         {$$ = $2}
    ;

OptionalDWordConstExpr
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}
    | ',' DWordConstExpr        {$$ = $2}
    ;

OptionalStringData 
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}
    | ',' StringData            {$$ = $2}
    ;

OptionalNameString 
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}
    | ',' NameString            {$$ = $2}
    ;

OptionalNameString_First
    :                           {$$ = NULL}
    | NameString                {$$ = $1}
    ;


OptionalAddressRange
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}
    | ',' AddressKeyword        {$$ = $2}
    ;

OptionalResourceType
    : ','                       {$$ = NULL}
    | ResourceTypeKeyword ','   {$$ = $1}
    ;

OptionalMinType
    : ','                       {$$ = NULL}
    | MinKeyword ','            {$$ = $1}
    ;

OptionalMaxType
    : ','                       {$$ = NULL}
    | MaxKeyword ','            {$$ = $1}
    ;

OptionalMemType
    : ','                       {$$ = NULL}
    | MemTypeKeyword ','        {$$ = $1}
    ;

OptionalDecodeType
    : ','                       {$$ = NULL}
    | DecodeKeyword ','         {$$ = $1}
    ;

OptionalRangeType
    : ','                       {$$ = NULL}
    | RangeTypeKeyword ','      {$$ = $1}
    ;

OptionalShareType
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}
    | ',' ShareTypeKeyword      {$$ = $2}
    ;

OptionalType
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}
    | TypeKeyword ','           {$$ = $1}
    ;

OptionalTranslationType
    :                           {$$ = NULL}
    | ','                       {$$ = NULL}
    | TranslationKeyword ','    {$$ = $1}
    ;


%%

/* programs */

/*
 * ???
 */
int
AslCompilerwrap()
{
  return 1;
}

void *
AslLocalAllocate (unsigned int Size)
{
    void                *Mem;


    DbgPrint ("\nAslLocalAllocate: Expanding Stack to %d\n\n", Size);

    Mem = _CmCallocate (Size, 0, "", 0);
    if (!Mem)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_MEMORY_ALLOCATION, Gbl_CurrentLineNumber,
                    Gbl_LogicalLineNumber, Gbl_InputFilename, NULL);
        exit (1);
    }

    return (Mem);
}




