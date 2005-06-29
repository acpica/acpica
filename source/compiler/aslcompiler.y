
%{
/******************************************************************************
 *
 * Module Name: aslcompiler.y - Bison input file (ASL grammar and actions)
 *              $Revision: 1.5 $
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
#define YYERROR_VERBOSE


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
%}


/*
 * Declare the type of values in the grammar
 */

%union {
	int             i;
	long            l;
	char            *s;
	char            *n;
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
%token <i> BUFF
%token <i> BUFFER
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
%token <i> DECREMENT
%token <i> DECSTR
%token <i> DEFAULT
%token <i> DEFAULT_ARG
%token <i> DEFINITIONBLOCK
%token <i> DEREFOF
%token <i> DEVICE
%token <i> DIVIDE
%token <i> DMA
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
%token <i> FROMBCD
%token <i> HEXSTR
%token <i> IF
%token <i> INCLUDE
%token <i> INCREMENT
%token <i> INDEX
%token <i> INDEXFIELD
%token <i> INT
%token <i> INTEGER
%token <i> INTERRUPT
%token <i> IO
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
%token <i> MEMORY24
%token <i> MEMORY32
%token <i> MEMORY32FIXED
%token <i> METHOD
%token <i> MID
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
%token <i> QWORDIO
%token <i> QWORDMEMORY
%token <i> RAW_DATA
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
%token <i> RETURN
%token <i> SCOPE
%token <i> SERIALIZERULE_NOTSERIAL
%token <i> SERIALIZERULE_SERIAL
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
%type <s> StringData
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
%type <n> BuffTerm
%type <n> ConcatTerm
%type <n> ConcatResTerm
%type <n> CondRefOfTerm
%type <n> CopyTerm
%type <n> CopyTarget
%type <n> DecTerm
%type <n> DecStrTerm
%type <n> DerefOfTerm
%type <n> DivideTerm
%type <n> FindSetLeftBitTerm
%type <n> FindSetRightBitTerm
%type <n> FromBCDTerm
%type <n> HexStrTerm
%type <n> IncTerm
%type <n> IndexTerm
%type <n> IntTerm
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
%type <n> WaitTerm
%type <n> XOrTerm

%type <n> OptionalTermArg
%type <n> OptionalListTermArg


/* Keywords */

%type <n> ObjectTypeKeyword
%type <n> AccessTypeKeyword
%type <n> AccessAttribKeyword
%type <n> OptionalAccessAttribKeyword
%type <n> LockRuleKeyword
%type <n> UpdateRuleKeyword
%type <n> RegionSpaceKeyword
%type <n> MatchOpKeyword
%type <n> SerializeRuleKeyword
%type <n> OptionalSerializeRuleKeyword

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
%type <n> OptionalByteConstExpr
%type <n> WordConstExpr
%type <n> DWordConstExpr
%type <n> ConstExprTerm


%type <n> BufferTerm
%type <n> BufferData
%type <n> ByteList
%type <n> ByteListTail

%type <n> PackageTerm
%type <n> PackageLengthTerm
%type <n> PackageList
%type <n> PackageListTail
%type <n> PackageElement

%type <n> EISAIDTerm
%type <n> ResourceTemplateTerm
%type <n> ResourceMacroList
%type <n> ResourceMacroTerm
%type <n> WordBusNumberTerm


/* TBD: Could not find in spec */

%type <n> ObjectReference
%type <n> DDBHandle


%type <s> NameString
%type <s> NameSeg


/* Local types that help construct the AML, not in ACPI spec */

%type <n> AmlPackageLengthTerm


%%

/*******************************************************************************
 *
 * Production starts here
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
    : DEFINITIONBLOCK '(' 
        String ','
        String ','
        ByteConst ','
        String ','
        String ','
        DwordConst
        ')' '{' TermList '}' 
            {$$ = TgCreateNode (DEFINITIONBLOCK,7,$3,$5,$7,$9,$11,$13,$16);}
    ;

TermList
    : {$$ = NULL}
    | Term TermList {$$ = TgLinkPeerNode ($1,$2);}
    ;

Term
    : Object {}
    | Type1Opcode {}
    | Type2Opcode {}
    | error {$$= NULL}
    ;

CompilerDirective
    : IncludeTerm {}
    | ExternalTerm {}
    ;

ObjectList
    : {$$ = NULL}
    | Object ObjectList {$$ = TgLinkPeerNode ($1,$2);}
    ;

Object
    : CompilerDirective {}
    | NamedObject {}
    | NameSpaceModifier {}
    ;

DataObject
    : BufferData {}
    | PackageData {}
    | IntegerData {}
    | StringData {}
    ;

DataRefObject
    : DataObject {}
    | ObjectReference {}
    | DDBHandle {}
    ;

ComputationalData
    : BufferData {}
    | IntegerData {}
    | StringData {}
    ;

BufferData
    : Type5Opcode {}
    | BufferTerm {}
    ;

PackageData
    : PackageTerm {}
    ;

IntegerData
    : Type3Opcode {}
    | Integer {}
    | ConstTerm {}
    ;
    
StringData
    : Type4Opcode {}
    | String {}
    ;

NamedObject
    : BankFieldTerm {}
    | CreateBitFieldTerm {}
    | CreateByteFieldTerm {}
    | CreateDWordFieldTerm {}
    | CreateFieldTerm {}
    | CreateQWordFieldTerm {}
    | CreateWordFieldTerm {}
    | DataRegionTerm {}
    | DeviceTerm {}
    | EventTerm {}
    | FieldTerm {}
    | IndexFieldTerm {}
    | MethodTerm {}
    | MutexTerm {}
    | OpRegionTerm {}
    | PowerResTerm {}
    | ProcessorTerm {}
    | ThermalZoneTerm {}
    ;

NameSpaceModifier
    : AliasTerm {}
    | NameTerm {}
    | ScopeTerm {}
    ;

UserTerm
    : NameString '(' 
        ArgList ')' {$$ = TgLinkChildNode ($1,$3);}
    ;

ArgList
    : {$$ = NULL}
    | TermArg ArgListTail {$$ = TgLinkPeerNode ($1,$2);}
    ;

ArgListTail
    : {$$ = NULL}
    | ',' {$$ = NULL}   /* Allows a trailing comma at list end */

    | ',' TermArg ArgListTail {$$ = TgLinkPeerNode ($2,$3);}
    ;

TermArg
    : Type2Opcode {}
    | DataRefObject {}
    | ArgTerm {}
    | LocalTerm {}
    | error {$$= NULL}
    ;

Target 
    : {$$ = TgCreateLeafNode (ZERO, NULL);}     /* Placeholder is a ZeroOp object */
    | ',' {$$ = TgCreateLeafNode (ZERO, NULL);} /* Placeholder is a ZeroOp object */
    | ',' SuperName {$$ = $2}
    ;


/* Opcode types */

Type1Opcode
    : BreakTerm {}
    | BreakPointTerm {}
    | ContinueTerm {}
    | FatalTerm {}
    | IfElseTerm {}
    | LoadTerm {}
    | NoOpTerm {}
    | NotifyTerm {}
    | ReleaseTerm {}
    | ResetTerm {}
    | ReturnTerm {}
    | SignalTerm {}
    | SleepTerm {}
    | StallTerm {}
    | SwitchTerm {}
    | UnloadTerm {}
    | WhileTerm {}
    ;

Type2Opcode
    : AcquireTerm {}
    | AddTerm {}
    | AndTerm {}
    | BuffTerm {}
    | ConcatTerm {}
    | ConcatResTerm {}
    | CondRefOfTerm {}
    | CopyTerm {}
    | DecTerm {}
    | DecStrTerm {}
    | DerefOfTerm {}
    | DivideTerm {}
    | FindSetLeftBitTerm {}
    | FindSetRightBitTerm {}
    | FromBCDTerm {}
    | HexStrTerm {}
    | IncTerm {}
    | IndexTerm {}
    | IntTerm {}
    | LAndTerm {}
    | LEqualTerm {}
    | LGreaterTerm {}
    | LGreaterEqualTerm {}
    | LLessTerm {}
    | LLessEqualTerm {}
    | LNotTerm {}
    | LNotEqualTerm {}
    | LoadTableTerm {}
    | LOrTerm {}
    | MatchTerm {}
    | MidTerm {}
    | ModTerm {}
    | MultiplyTerm {}
    | NAndTerm {}
    | NOrTerm {}
    | NotTerm {}
    | ObjectTypeTerm {}
    | OrTerm {}
    | RefOfTerm {}
    | ShiftLeftTerm {}
    | ShiftRightTerm {}
    | SizeOfTerm {}
    | StoreTerm {}
    | StringTerm {}
    | SubtractTerm {}
    | ToBCDTerm {}
    | WaitTerm {}
    | XOrTerm {}
    | UserTerm {}
    ;


/*
 * A type 3 opcode evaluates to an Integer and cannot have a destination operand
 */

Type3Opcode
    : AddTerm {}
    | AndTerm {}
    | DecTerm {}
    | DivideTerm {}
    | EISAIDTerm {}
    | FindSetLeftBitTerm {}
    | FindSetRightBitTerm {}
    | FromBCDTerm{}
    | IncTerm {}
    | IndexTerm {}
    | IntTerm {}
    | LAndTerm {}
    | LEqualTerm {}
    | LGreaterTerm {}
    | LGreaterEqualTerm {}
    | LLessTerm {}
    | LLessEqualTerm {}
    | LNotTerm {}
    | LNotEqualTerm {}
    | LOrTerm {}
    | MatchTerm {}
    | ModTerm {}
    | MultiplyTerm {}
    | NAndTerm {}
    | NOrTerm {}
    | NotTerm {}
    | OrTerm {}
    | ShiftLeftTerm {}
    | ShiftRightTerm {} 
    | SubtractTerm {}
    | ToBCDTerm {}
    | XOrTerm {}
    ;

Type4Opcode
    : ConcatTerm {}
    | DecStrTerm {}
    | HexStrTerm {}
    | MidTerm {}
    | StringTerm {}
    ;

/* TBD: add Unicode term */

Type5Opcode
    : BuffTerm {}
    | ConcatTerm {}
    | ConcatResTerm {}
    | MidTerm {}
    | ResourceTemplateTerm {}
    ;

Type6Opcode
    : RefOfTerm {}
    | DerefOfTerm {}
    | IndexTerm {}
    | UserTerm {}
    ;

IncludeTerm
    : INCLUDE '(' 
        String ')' {}
    ;

ExternalTerm
    : EXTERNAL '('
        String ','
        ObjectTypeKeyword
        ')' {}
    ;

FieldUnitList
    : {$$ = NULL}
    | FieldUnit FieldUnitListTail {$$ = TgLinkPeerNode ($1,$2);}
    ;

FieldUnitListTail
    : {$$ = NULL}
    | ',' {$$ = NULL}  /* Allows a trailing comma at list end */

    | ',' FieldUnit FieldUnitListTail {$$ = TgLinkPeerNode ($2,$3);}
    ;

FieldUnit
    : FieldUnitEntry {}
    | OffsetTerm {}
    | AccessAsTerm {}
    ;

FieldUnitEntry
    : ',' AmlPackageLengthTerm {$$ = TgCreateNode (RESERVED_BYTES,1,$2);}
    | NameSeg ',' 
        AmlPackageLengthTerm {$$ = TgLinkChildNode ($1,$3);}
    ;

OffsetTerm
    : OFFSET '('
        AmlPackageLengthTerm
        ')' {$$ = TgCreateNode (OFFSET,1,$3);}
    ;

AccessAsTerm
    : ACCESSAS '('
        AccessTypeKeyword
        OptionalAccessAttribTerm
        ')' {$$ = TgCreateNode (ACCESSAS,2,$3,$4);}
    ;

AmlPackageLengthTerm
    : Integer {$$ = TgUpdateNode (PACKAGE_LENGTH,(ASL_PARSE_NODE *) $1);}
    ;

OptionalAccessAttribTerm
    : {$$ = NULL}
    | ',' ByteConstExpr {$$ = $2}
    | ',' AccessAttribKeyword {$$ = $2}
    | ',' {$$ = NULL}
    ;

/******* Named Objects *******************************************************/


BankFieldTerm
    : BANKFIELD '('
        NameString ','
        NameString ','
        TermArg ','
        AccessTypeKeyword ','
        LockRuleKeyword ','
        UpdateRuleKeyword
        ')' '{' FieldUnitList '}'
            {$$ = TgCreateNode (BANKFIELD,7,$3,$5,$7,$9,$11,$13,$16);}
    ;

CreateBitFieldTerm
    : CREATEBITFIELD '('
        TermArg ','
        TermArg ','
        NameString 
        ')' {$$ = TgCreateNode (CREATEBITFIELD,3,$3,$5,$7);}
    ;

CreateByteFieldTerm
    : CREATEBYTEFIELD '('
        TermArg ','
        TermArg ','
        NameString 
        ')' {$$ = TgCreateNode (CREATEBYTEFIELD,3,$3,$5,$7);}
    ;

CreateDWordFieldTerm
    : CREATEDWORDFIELD '('
        TermArg ','
        TermArg ','
        NameString 
        ')' {$$ = TgCreateNode (CREATEDWORDFIELD,3,$3,$5,$7);}
    ;

CreateFieldTerm
    : CREATEFIELD '('
        TermArg ','
        TermArg ','
        TermArg ','
        NameString 
        ')' {$$ = TgCreateNode (CREATEFIELD,4,$3,$5,$7,$9);}
    ;

CreateQWordFieldTerm
    : CREATEQWORDFIELD '('
        TermArg ','
        TermArg ','
        NameString 
        ')' {$$ = TgCreateNode (CREATEQWORDFIELD,3,$3,$5,$7);}
    ;

CreateWordFieldTerm
    : CREATEWORDFIELD '('
        TermArg ','
        TermArg ','
        NameString 
        ')' {$$ = TgCreateNode (CREATEWORDFIELD,3,$3,$5,$7);}
    ;

DataRegionTerm
    : DATATABLEREGION '('
        NameString ','
        TermArg ','
        TermArg ','
        TermArg 
        ')' {$$ = TgCreateNode (DATATABLEREGION,4,$3,$5,$7,$9);}
    ;

DeviceTerm
    : DEVICE '('
        NameString
        ')' '{' ObjectList '}' 
            {$$ = TgCreateNode (DEVICE,2,$3,$6);}
    ;

EventTerm
    : EVENT '('
        NameString
        ')' {$$ = TgCreateNode (EVENT,1,$3);}
    ;

FieldTerm
    : FIELD '('
        NameString ','
        AccessTypeKeyword ','
        LockRuleKeyword ','
        UpdateRuleKeyword
        ')' '{' FieldUnitList '}' 
            {$$ = TgCreateNode (FIELD,5,$3,$5,$7,$9,$12);}
    ;

IndexFieldTerm
    : INDEXFIELD '('
        NameString ','
        NameString ','
        AccessTypeKeyword ','
        LockRuleKeyword ','
        UpdateRuleKeyword
        ')' '{' FieldUnitList '}' 
            {$$ = TgCreateNode (INDEXFIELD,6,$3,$5,$7,$9,$11,$14);}
    ;

MethodTerm
    : METHOD '('
        NameString
        OptionalByteConstExpr
        OptionalSerializeRuleKeyword
        OptionalByteConstExpr
        ')' '{' TermList '}' {$$ = TgCreateNode (METHOD,5,$3,$4,$5,$6,$9);}
    ;

MutexTerm
    : MUTEX '('
        NameString ','
        ByteConstExpr
        ')' {$$ = TgCreateNode (MUTEX,2,$3,$5);}
    ;

OpRegionTerm
    : OPERATIONREGION '(' 
        NameString ',' 
        OpRegionSpaceIdTerm ',' 
        TermArg ',' 
        TermArg 
        ')' {$$ = TgCreateNode (OPERATIONREGION,4,$3,$5,$7,$9);}
    ;

OpRegionSpaceIdTerm
    : RegionSpaceKeyword {}
    | ByteConst {}
    ;

PowerResTerm
    : POWERRESOURCE '('
        NameString ','
        ByteConstExpr ','
        WordConstExpr
        ')' '{' ObjectList '}' {$$ = TgCreateNode (POWERRESOURCE,4,$3,$5,$7,$10);}
    ;

ProcessorTerm
    : PROCESSOR '('
        NameString ','
        ByteConstExpr ','
        DWordConstExpr ','
        ByteConstExpr
        ')' '{' ObjectList '}' {$$ = TgCreateNode (PROCESSOR,5,$3,$5,$7,$9,$12);}
    ;

ThermalZoneTerm
    : THERMALZONE '('
        NameString
        ')' '{' ObjectList '}' {$$ = TgCreateNode (THERMALZONE,2,$3,$6);}
    ;



/******* Namespace modifiers *************************************************/


AliasTerm
    : ALIAS '('
        NameString ','
        NameString 
        ')' {$$ = TgCreateNode (ALIAS,2,$3,$5);}
    ;

NameTerm
    : NAME '('
        NameString ','
        DataRefObject 
        ')' {$$ = TgCreateNode (NAME,2,$3,$5);}
    ;

ScopeTerm
    : SCOPE '('
        NameString
        ')' '{' ObjectList '}' 
            {$$ = TgCreateNode (SCOPE,2,$3,$6);}
    ;



/******* Type 1 opcodes *******************************************************/


BreakTerm
    : BREAK 
        {$$ = TgCreateNode (BREAK, 0);}
    ;

BreakPointTerm
    : BREAKPOINT 
        {$$ = TgCreateNode (BREAKPOINT, 0);}
    ;

ContinueTerm
    : CONTINUE 
        {$$ = TgCreateNode (CONTINUE, 0);}
    ;

FatalTerm
    : FATAL '('
        ByteConstExpr ','
        DWordConstExpr ','
        TermArg
        ')' {$$ = TgCreateNode (FATAL,3,$3,$5,$7);}
    ;

IfElseTerm
    : IfTerm ElseTerm {$$ = TgLinkPeerNode ($1,$2);}
    ;

IfTerm 
    : IF '('
        TermArg
        ')' '{' TermList '}' 
            {$$ = TgCreateNode (IF,2,$3,$6);}
    ;

ElseTerm
    : {$$ = NULL}
    | ELSE '{' TermList '}' 
        {$$ = TgCreateNode (ELSE,1,$3);}
    | ELSEIF '{' TermList '}' ElseTerm 
        {$$ = TgCreateNode (ELSEIF,1,$3);}
    ;

LoadTerm
    : LOAD '('
        NameString ','
        SuperName 
        ')' {$$ = TgCreateNode (LOAD,2,$3,$5);}
    ;

NoOpTerm
    : NOOP 
        {$$ = TgCreateNode (NOOP, 0);}
    ;

NotifyTerm 
    : NOTIFY '('
        SuperName ','
        TermArg
        ')' {$$ = TgCreateNode (NOTIFY,2,$3,$5);}
    ;

ReleaseTerm
    : RELEASE '('
        SuperName
        ')' {$$ = TgCreateNode (RELEASE,1,$3);}
    ;

ResetTerm
    : RESET '('
        SuperName
        ')' {$$ = TgCreateNode (RESET,1,$3);}
    ;

ReturnTerm
    : RETURN '('
        TermArg
        ')' {$$ = TgCreateNode (RETURN,1,$3);}
    ;

SignalTerm
    : SIGNAL '('
        SuperName
        ')' {$$ = TgCreateNode (SIGNAL,1,$3);}
    ;

SleepTerm
    : SLEEP '('
        TermArg
        ')' {$$ = TgCreateNode (SLEEP,1,$3);}
    ;
StallTerm
    : STALL '('
        TermArg
        ')' {$$ = TgCreateNode (STALL,1,$3);}
    ;

SwitchTerm
    : SWITCH '('
        TermArg
        ')' '{' CaseTermList '}' 
            {$$ = TgCreateNode (SWITCH,2,$3,$6);}
    ;

CaseTermList
    : {}
    | CaseTerm {}
    | DefaultTerm DefaultTermList {}
    | CaseTerm {}
    | CaseTermList {}
    ;

DefaultTermList
    : {}
    | CaseTerm {}
    | CaseTerm DefaultTermList {}
    ;

CaseTerm
    : CASE '('
        DataObject
        ')' '{' TermList '}' 
            {$$ = TgCreateNode (CASE,2,$3,$6);}
    ;

DefaultTerm
    : DEFAULT 
        '{' TermList '}' 
            {$$ = TgCreateNode (DEFAULT,1,$3);}
    ;

UnloadTerm
    : UNLOAD '('
        SuperName
        ')' {$$ = TgCreateNode (UNLOAD,1,$3);}
    ;

WhileTerm
    : WHILE '('
        TermArg
        ')' '{' TermList '}' 
            {$$ = TgCreateNode (WHILE,2,$3,$6);}
    ;


/******* Type 2 opcodes *******************************************************/

AcquireTerm
    : ACQUIRE '('
        SuperName ','
        WordConstExpr
        ')' {$$ = TgCreateNode (ACQUIRE,2,$3,$5);}

AddTerm
    : ADD '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (ADD,3,$3,$5,$6);}
    ;

AndTerm
    : AND '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (AND,3,$3,$5,$6);}
    ;

BuffTerm
    : BUFF '(' 
        TermArg
        Target
        ')' {$$ = TgCreateNode (BUFF,2,$3,$4);}
    ;

ConcatTerm
    : CONCATENATE '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (CONCATENATE,3,$3,$5,$6);}
    ;

ConcatResTerm
    : CONCATENATERESTEMPLATE '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (CONCATENATERESTEMPLATE,3,$3,$5,$6);}
    ;

CondRefOfTerm
    : CONDREFOF '(' 
        SuperName
        Target
        ')' {$$ = TgCreateNode (CONDREFOF,2,$3,$4);}
    ;

CopyTerm
    : COPY '(' 
        TermArg ','
        CopyTarget
        ')' {$$ = TgCreateNode (COPY,2,$3,$5);}
    ;

CopyTarget
    : NameString {}
    | LocalTerm {}
    | ArgTerm {}
    ;

DecTerm
    : DECREMENT '(' 
        SuperName
        ')' {$$ = TgCreateNode (DECREMENT,1,$3);}
    ;

DecStrTerm
    : DECSTR '(' 
        TermArg
        Target
        ')' {$$ = TgCreateNode (DECSTR,2,$3,$4);}
    ;

DerefOfTerm
    : DEREFOF '(' 
        TermArg
        ')' {$$ = TgCreateNode (DEREFOF,1,$3);}
    ;

DivideTerm
    : DIVIDE '(' 
        TermArg ','
        TermArg
        Target
        Target
        ')' {$$ = TgCreateNode (DIVIDE,4,$3,$5,$6,$7);}
    ;

FindSetLeftBitTerm
    : FINDSETLEFTBIT '(' 
        TermArg
        Target
        ')' {$$ = TgCreateNode (FINDSETLEFTBIT,2,$3,$4);}
    ;

FindSetRightBitTerm
    : FINDSETRIGHTBIT '(' 
        TermArg
        Target
        ')' {$$ = TgCreateNode (FINDSETRIGHTBIT,2,$3,$4);}
    ;

FromBCDTerm
    : FROMBCD '(' 
        TermArg
        Target
        ')' {$$ = TgCreateNode (FROMBCD,2,$3,$4);}
    ;

HexStrTerm
    : HEXSTR '(' 
        TermArg
        Target
        ')' {$$ = TgCreateNode (HEXSTR,2,$3,$4);}
    ;

IncTerm
    : INCREMENT '(' 
        SuperName
        ')' {$$ = TgCreateNode (INCREMENT,1,$3);}
    ;

IndexTerm
    : INDEX '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (INDEX,3,$3,$5,$6);}
    ;

IntTerm
    : INT '(' 
        TermArg
        Target
        ')' {$$ = TgCreateNode (INT,2,$3,$4);}
    ;

LAndTerm
    : LAND '(' 
        TermArg ','
        TermArg
        ')' {$$ = TgCreateNode (LAND,2,$3,$5);}
    ;

LEqualTerm
    : LEQUAL '(' 
        TermArg ','
        TermArg
        ')' {$$ = TgCreateNode (LEQUAL,2,$3,$5);}
    ;

LGreaterTerm
    : LGREATER '(' 
        TermArg ','
        TermArg
        ')' {$$ = TgCreateNode (LGREATER,2,$3,$5);}
    ;

LGreaterEqualTerm
    : LGREATEREQUAL '(' 
        TermArg ','
        TermArg
        ')' {$$ = TgCreateNode (LGREATEREQUAL,2,$3,$5);}
    ;

LLessTerm
    : LLESS '(' 
        TermArg ','
        TermArg
        ')' {$$ = TgCreateNode (LLESS,2,$3,$5);}
    ;

LLessEqualTerm
    : LLESSEQUAL '(' 
        TermArg ','
        TermArg
        ')' {$$ = TgCreateNode (LLESSEQUAL,2,$3,$5);}
    ;

LNotTerm
    : LNOT '(' 
        TermArg
        ')' {$$ = TgCreateNode (LNOT ,1,$3);}
    ;

LNotEqualTerm
    : LNOTEQUAL '(' 
        TermArg ','
        TermArg
        ')' {$$ = TgCreateNode (LNOTEQUAL,2,$3,$5);}
    ;

LoadTableTerm
    : LOADTABLE '('
        TermArg ','
        TermArg ','
        TermArg
        OptionalListTermArg
        OptionalListTermArg
        OptionalListTermArg
        ')' {$$ = TgCreateNode (LOADTABLE,6,$3,$5,$7,$8,$9,$10);}
    ;

OptionalListTermArg
    : {$$ = NULL}
    | ',' TermArg {$$ = $2}
    ;

OptionalTermArg
    : {$$ = NULL}
    | TermArg {$$ = $1}
    ;

LOrTerm
    : LOR '(' 
        TermArg ','
        TermArg
        ')' {$$ = TgCreateNode (LOR,2,$3,$5);}
    ;

MatchTerm
    : MATCH '('
        TermArg ','
        MatchOpKeyword ','
        TermArg ','
        MatchOpKeyword ','
        TermArg ','
        TermArg
        ')' {$$ = TgCreateNode (MATCH,6,$3,$5,$7,$9,$11,$13);}
    ;

MidTerm
    : MID '(' 
        TermArg ','
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (MID,4,$3,$5,$7,$8);}
    ;

ModTerm
    : MOD '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (MOD,3,$3,$5,$6);}
    ;

MultiplyTerm
    : MULTIPLY '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (MULTIPLY,3,$3,$5,$6);}
    ;

NAndTerm
    : NAND '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (NAND,3,$3,$5,$6);}
    ;

NOrTerm
    : NOR '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (NOR,3,$3,$5,$6);}
    ;

NotTerm
    : NOT '(' 
        TermArg
        Target
        ')' {$$ = TgCreateNode (NOT,2,$3,$4);}
    ;

ObjectTypeTerm
    : OBJECTTYPE '(' 
        SuperName
        ')' {$$ = TgCreateNode (OBJECTTYPE,1,$3);}
    ;

OrTerm
    : OR '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (OR,3,$3,$5,$6);}
    ;

RefOfTerm
    : REFOF '(' 
        SuperName
        ')' {$$ = TgCreateNode (REFOF,1,$3);}
    ;

ShiftLeftTerm
    : SHIFTLEFT '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (SHIFTLEFT,3,$3,$5,$6);}
    ;

ShiftRightTerm
    : SHIFTRIGHT '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (SHIFTRIGHT,3,$3,$5,$6);}
    ;

SizeOfTerm
    : SIZEOF '(' 
        SuperName
        ')' {$$ = TgCreateNode (SIZEOF,1,$3);}
    ;

StoreTerm
    : STORE '(' 
        TermArg ','
        SuperName
        ')' {$$ = TgCreateNode (STORE,2,$3,$5);}
    ;

StringTerm
    : STRING '(' 
        TermArg
        OptionalListTermArg
        Target
        ')' {$$ = TgCreateNode (STRING,3,$3,$4,$5);}
    ;

SubtractTerm
    : SUBTRACT '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (SUBTRACT,3,$3,$5,$6);}
    ;

ToBCDTerm
    : TOBCD '(' 
        TermArg
        Target
        ')' {$$ = TgCreateNode (TOBCD,2,$3,$4);}
    ;

WaitTerm
    : WAIT '(' 
        SuperName ','
        TermArg
        ')' {$$ = TgCreateNode (WAIT,2,$3,$5);}
    ;

XOrTerm
    : XOR '(' 
        TermArg ','
        TermArg
        Target
        ')' {$$ = TgCreateNode (XOR,3,$3,$5,$6);}
    ;



/******* Keywords *************************************************************/


ObjectTypeKeyword
    : OBJECTTYPE_UNK {$$ = TgCreateLeafNode (OBJECTTYPE_UNK, NULL);}
    | OBJECTTYPE_INT {$$ = TgCreateLeafNode (OBJECTTYPE_INT, NULL);}
    | OBJECTTYPE_STR {$$ = TgCreateLeafNode (OBJECTTYPE_STR, NULL);}
    | OBJECTTYPE_BUF {$$ = TgCreateLeafNode (OBJECTTYPE_BUF, NULL);}
    | OBJECTTYPE_PKG {$$ = TgCreateLeafNode (OBJECTTYPE_PKG, NULL);}
    | OBJECTTYPE_FLD {$$ = TgCreateLeafNode (OBJECTTYPE_FLD, NULL);}
    | OBJECTTYPE_DEV {$$ = TgCreateLeafNode (OBJECTTYPE_DEV, NULL);}
    | OBJECTTYPE_EVT {$$ = TgCreateLeafNode (OBJECTTYPE_EVT, NULL);}
    | OBJECTTYPE_MTH {$$ = TgCreateLeafNode (OBJECTTYPE_MTH, NULL);}
    | OBJECTTYPE_MTX {$$ = TgCreateLeafNode (OBJECTTYPE_MTX, NULL);}
    | OBJECTTYPE_OPR {$$ = TgCreateLeafNode (OBJECTTYPE_OPR, NULL);}
    | OBJECTTYPE_POW {$$ = TgCreateLeafNode (OBJECTTYPE_POW, NULL);}
    | OBJECTTYPE_THZ {$$ = TgCreateLeafNode (OBJECTTYPE_THZ, NULL);}
    | OBJECTTYPE_BFF {$$ = TgCreateLeafNode (OBJECTTYPE_BFF, NULL);}
    | OBJECTTYPE_DDB {$$ = TgCreateLeafNode (OBJECTTYPE_DDB, NULL);}
    ;

AccessTypeKeyword
    : ACCESSTYPE_ANY {$$ = TgCreateLeafNode (ACCESSTYPE_ANY, NULL);}
    | ACCESSTYPE_BYTE {$$ = TgCreateLeafNode (ACCESSTYPE_BYTE, NULL);}
    | ACCESSTYPE_WORD {$$ = TgCreateLeafNode (ACCESSTYPE_WORD, NULL);}
    | ACCESSTYPE_DWORD {$$ = TgCreateLeafNode (ACCESSTYPE_DWORD, NULL);}
    | ACCESSTYPE_QWORD {$$ = TgCreateLeafNode (ACCESSTYPE_QWORD, NULL);}
    | ACCESSTYPE_BUF {$$ = TgCreateLeafNode (ACCESSTYPE_BUF, NULL);}
    ;

AccessAttribKeyword
    : ACCESSATTRIB_QUICK {$$ = TgCreateLeafNode (ACCESSATTRIB_QUICK , NULL);}
    | ACCESSATTRIB_SND_RCV {$$ = TgCreateLeafNode (ACCESSATTRIB_SND_RCV, NULL);}
    | ACCESSATTRIB_BYTE {$$ = TgCreateLeafNode (ACCESSATTRIB_BYTE, NULL);}
    | ACCESSATTRIB_WORD {$$ = TgCreateLeafNode (ACCESSATTRIB_WORD, NULL);}
    | ACCESSATTRIB_BLOCK {$$ = TgCreateLeafNode ( ACCESSATTRIB_BLOCK, NULL);}
    | ACCESSATTRIB_CALL {$$ = TgCreateLeafNode (ACCESSATTRIB_CALL, NULL);}
    ;

OptionalAccessAttribKeyword
    : {$$ = NULL}
    | ',' {$$ = NULL}
    | ',' AccessAttribKeyword {$$ = $2}
    ;

LockRuleKeyword
    : LOCKRULE_LOCK {$$ = TgCreateLeafNode (LOCKRULE_LOCK, NULL);}
    | LOCKRULE_NOLOCK {$$ = TgCreateLeafNode (LOCKRULE_NOLOCK, NULL);}
    ;

UpdateRuleKeyword
    : UPDATERULE_PRESERVE {$$ = TgCreateLeafNode (UPDATERULE_PRESERVE, NULL);}
    | UPDATERULE_ONES {$$ = TgCreateLeafNode (UPDATERULE_ONES, NULL);}
    | UPDATERULE_ZEROS {$$ = TgCreateLeafNode (UPDATERULE_ZEROS, NULL);}
    ;

RegionSpaceKeyword
    : REGIONSPACE_IO {$$ = TgCreateLeafNode (REGIONSPACE_IO, NULL);}
    | REGIONSPACE_MEM {$$ = TgCreateLeafNode (REGIONSPACE_MEM, NULL);}
    | REGIONSPACE_PCI {$$ = TgCreateLeafNode (REGIONSPACE_PCI, NULL);}
    | REGIONSPACE_EC {$$ = TgCreateLeafNode (REGIONSPACE_EC, NULL);}
    | REGIONSPACE_SMBUS {$$ = TgCreateLeafNode (REGIONSPACE_SMBUS, NULL);}
    | REGIONSPACE_CMOS {$$ = TgCreateLeafNode (REGIONSPACE_CMOS, NULL);}
    | REGIONSPACE_PCIBAR {$$ = TgCreateLeafNode (REGIONSPACE_PCIBAR, NULL);}
    ;

MatchOpKeyword
    : MATCHTYPE_MTR {$$ = TgCreateLeafNode (MATCHTYPE_MTR, NULL);}
    | MATCHTYPE_MEQ {$$ = TgCreateLeafNode (MATCHTYPE_MEQ, NULL);}
    | MATCHTYPE_MLE {$$ = TgCreateLeafNode (MATCHTYPE_MLE, NULL);}
    | MATCHTYPE_MLT {$$ = TgCreateLeafNode (MATCHTYPE_MLT, NULL);}
    | MATCHTYPE_MGE {$$ = TgCreateLeafNode (MATCHTYPE_MGE, NULL);}
    | MATCHTYPE_MGT {$$ = TgCreateLeafNode (MATCHTYPE_MGT, NULL);}
    ;

SerializeRuleKeyword
    : SERIALIZERULE_SERIAL {$$ = TgCreateLeafNode (SERIALIZERULE_SERIAL, NULL);}
    | SERIALIZERULE_NOTSERIAL {$$ = TgCreateLeafNode (SERIALIZERULE_NOTSERIAL, NULL);}
    ;

OptionalSerializeRuleKeyword
    : {$$ = NULL}
    | ',' {$$ = NULL}
    | ',' SerializeRuleKeyword {$$ = $2}
    ;


/******* Miscellaneous Types **************************************************/


SuperName
    : NameString {}
    | ArgTerm {}
    | LocalTerm {}
    | DebugTerm {}
    | Type6Opcode {}
    | UserTerm {}
    | error {$$= NULL}
    ;

ArgTerm
    : ARG0 {$$ = TgCreateLeafNode (ARG0, NULL);}
    | ARG1 {$$ = TgCreateLeafNode (ARG1, NULL);}
    | ARG2 {$$ = TgCreateLeafNode (ARG2, NULL);}
    | ARG3 {$$ = TgCreateLeafNode (ARG3, NULL);}
    | ARG4 {$$ = TgCreateLeafNode (ARG3, NULL);}
    | ARG5 {$$ = TgCreateLeafNode (ARG4, NULL);}
    | ARG5 {$$ = TgCreateLeafNode (ARG5, NULL);}
    | ARG6 {$$ = TgCreateLeafNode (ARG6, NULL);}
    ;


LocalTerm
    : LOCAL0 {$$ = TgCreateLeafNode (LOCAL0, NULL);}
    | LOCAL1 {$$ = TgCreateLeafNode (LOCAL1, NULL);}
    | LOCAL2 {$$ = TgCreateLeafNode (LOCAL2, NULL);}
    | LOCAL3 {$$ = TgCreateLeafNode (LOCAL3, NULL);}
    | LOCAL4 {$$ = TgCreateLeafNode (LOCAL4, NULL);}
    | LOCAL5 {$$ = TgCreateLeafNode (LOCAL5, NULL);}
    | LOCAL6 {$$ = TgCreateLeafNode (LOCAL6, NULL);}
    | LOCAL7 {$$ = TgCreateLeafNode (LOCAL7, NULL);}
    ;


DebugTerm
    : DEBUG {$$ = TgCreateLeafNode (DEBUG, NULL);}
    ;

Integer
    : INTEGER {$$ = TgCreateLeafNode (INTEGER, (void *) AslCompilerlval.i);}
    ;

ByteConst
    : Integer {$$ = TgUpdateNode (BYTECONST, $1);}
    ;

WordConst
    : Integer {$$ = TgUpdateNode (WORDCONST, $1);}
    ;

DwordConst
    : Integer {$$ = TgUpdateNode (DWORDCONST, $1);}
    ;

/* TBD: should be QWORDCONST */

QwordConst
    : Integer {$$ = TgUpdateNode (DWORDCONST, $1);}
    ;

String
    : STRING_LITERAL {$$ = TgCreateLeafNode (STRING_LITERAL, AslCompilerlval.s);}
    ;

/* TBD: Needs     | REVISION
 */

ConstTerm
    : ZERO {$$ = TgCreateLeafNode (ZERO, NULL);}
    | ONE {$$ = TgCreateLeafNode (ONE, NULL);}
    | ONES {$$ = TgCreateLeafNode (ONES, NULL);}
    ;

ByteConstExpr
    : Type3Opcode {$$ = TgUpdateNode (BYTECONST, $1);}
    | ConstExprTerm {$$ = TgUpdateNode (BYTECONST, $1);}
    | Integer {$$ = TgUpdateNode (BYTECONST, $1);}
    ;

OptionalByteConstExpr
    : {$$ = NULL}
    | ',' {$$ = NULL}
    | ',' ByteConstExpr {$$ = $2}
    ;

WordConstExpr
    : Type3Opcode {$$ = TgUpdateNode (WORDCONST, $1);}
    | ConstExprTerm {$$ = TgUpdateNode (WORDCONST, $1);}
    | Integer {$$ = TgUpdateNode (WORDCONST, $1);}
    ;

DWordConstExpr
    : Type3Opcode {$$ = TgUpdateNode (DWORDCONST, $1);}
    | ConstExprTerm {$$ = TgUpdateNode (DWORDCONST, $1);}
    | Integer {$$ = TgUpdateNode (DWORDCONST, $1);}
    ;

ConstExprTerm
    : ZERO {$$ = TgCreateLeafNode (ZERO, NULL);}
    | ONE {$$ = TgCreateLeafNode (ONE, NULL);}
    | ONES {$$ = TgCreateLeafNode (ONES, NULL);}
    ;


/* TBD: Need to add "StringData" to init */

BufferTerm
    : BUFFER '(' 
        OptionalTermArg
        ')' '{' BufferData '}' {$$ = TgCreateNode (BUFFER,2,$3,$6);}
    ;

BufferData
    : ByteList {}
    | StringData {}
    ;

ByteList
    : {$$ = NULL}
    | ByteConstExpr ByteListTail {$$ = TgLinkPeerNode ($1,$2);}
    ;

ByteListTail
    : {$$ = NULL}
    | ',' {$$ = NULL}   /* Allows a trailing comma at list end */

    | ',' ByteConstExpr ByteListTail {$$ = TgLinkPeerNode ($2,$3);}
    ;

PackageTerm
    : PACKAGE '(' 
        PackageLengthTerm
        ')' '{' PackageList '}' {$$ = TgCreateNode (PACKAGE,2,$3,$6);}
    ;

PackageLengthTerm
    : {$$ = NULL}
    | ByteConstExpr {}
    | TermArg {}
    ;

PackageList
    : {$$ = NULL}
    | PackageElement PackageListTail {$$ = TgLinkPeerNode ($1,$2);}
    ;

PackageListTail
    : {$$ = NULL}
    | ',' {$$ = NULL}   /* Allows a trailing comma at list end */

    | ',' PackageElement PackageListTail {$$ = TgLinkPeerNode ($2,$3);}
    ;

PackageElement
    : DataObject {}
    | NameString {}
    ;

EISAIDTerm
    : EISAID '(' 
        StringData ')' {$$ = TgUpdateNode (EISAID, $3);}
    ;


/******* Resources and Memory ***********************************************/


ResourceTemplateTerm
    : RESOURCETEMPLATE '(' ')'
        '{' ResourceMacroList '}'
        {$$ = TgCreateNode (RESOURCETEMPLATE,1,$5);}
    ;

ResourceMacroList
    : {$$ = NULL}
    | ResourceMacroTerm ResourceMacroList {$$ = TgLinkPeerNode ($1,$2);}
    ;

/* TBD: finish list */

ResourceMacroTerm
    : WordBusNumberTerm  {$$ = $1}
    ;

/* TBD: finish list */

WordBusNumberTerm
    : WordConstExpr
    ;



/* TBD: Could not find in spec */

ObjectReference
    : NameString {}
    ;

DDBHandle
    : String {}
    ;


/******* Object References ***********************************************/


NameString
    : NameSeg {}
    | NAMESTRING {$$ = TgCreateLeafNode (NAMESTRING, AslCompilerlval.s);}
    ;

NameSeg 
    : NAMESEG {$$ = TgCreateLeafNode (NAMESEG, AslCompilerlval.s);}
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




