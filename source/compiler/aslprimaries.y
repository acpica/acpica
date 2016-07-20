NoEcho('
/******************************************************************************
 *
 * Module Name: aslprimaries.y - Rules for primary ASL operators
 *                             - Keep this file synched with the 
 *                               AslParseOpBlockType function in aslutils.c
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2016, Intel Corp.
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

')


/*******************************************************************************
 *
 * ASL Primary Terms
 *
 ******************************************************************************/

AccessAsTerm
    : PARSEOP_ACCESSAS '('
        AccessTypeKeyword
        OptionalAccessAttribTerm
        ')'                         {$$ = TrCreateNode (PARSEOP_ACCESSAS,2,$3,$4);}
    | PARSEOP_ACCESSAS '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

AcquireTerm
    : PARSEOP_ACQUIRE '('           {$<n>$ = TrCreateLeafNode (PARSEOP_ACQUIRE);}
        SuperName
        ',' WordConstExpr
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$6);}
    | PARSEOP_ACQUIRE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

AddTerm
    : PARSEOP_ADD '('               {$<n>$ = TrCreateLeafNode (PARSEOP_ADD);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_ADD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

AliasTerm
    : PARSEOP_ALIAS '('             {$<n>$ = TrCreateLeafNode (PARSEOP_ALIAS);}
        NameString
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,
                                        TrSetNodeFlags ($5, NODE_IS_NAME_DECLARATION));}
    | PARSEOP_ALIAS '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

AndTerm
    : PARSEOP_AND '('               {$<n>$ = TrCreateLeafNode (PARSEOP_AND);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_AND '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ArgTerm
    : PARSEOP_ARG0                  {$$ = TrCreateLeafNode (PARSEOP_ARG0);}
    | PARSEOP_ARG1                  {$$ = TrCreateLeafNode (PARSEOP_ARG1);}
    | PARSEOP_ARG2                  {$$ = TrCreateLeafNode (PARSEOP_ARG2);}
    | PARSEOP_ARG3                  {$$ = TrCreateLeafNode (PARSEOP_ARG3);}
    | PARSEOP_ARG4                  {$$ = TrCreateLeafNode (PARSEOP_ARG4);}
    | PARSEOP_ARG5                  {$$ = TrCreateLeafNode (PARSEOP_ARG5);}
    | PARSEOP_ARG6                  {$$ = TrCreateLeafNode (PARSEOP_ARG6);}
    ;

BankFieldTerm
    : PARSEOP_BANKFIELD '('         {$<n>$ = TrCreateLeafNode (PARSEOP_BANKFIELD);}
        NameString
        NameStringItem
        TermArgItem
        ',' AccessTypeKeyword
        ',' LockRuleKeyword
        ',' UpdateRuleKeyword
        ')' '{'
            FieldUnitList '}'       {$$ = TrLinkChildren ($<n>3,7,$4,$5,$6,$8,$10,$12,$15);}
    | PARSEOP_BANKFIELD '('
        error ')' '{' error '}'     {$$ = AslDoError(); yyclearin;}
    ;

BreakTerm
    : PARSEOP_BREAK                 {$$ = TrCreateNode (PARSEOP_BREAK, 0);}
    ;

BreakPointTerm
    : PARSEOP_BREAKPOINT            {$$ = TrCreateNode (PARSEOP_BREAKPOINT, 0);}
    ;

BufferTerm
    : PARSEOP_BUFFER                {$<n>$ = TrCreateLeafNode (PARSEOP_BUFFER);}
        OptionalDataCount
        '{' BufferTermData '}'      {$$ = TrLinkChildren ($<n>2,2,$3,$5);}
    ;

BufferTermData
    : ByteList                      {}
    | StringData                    {}
    ;

CaseTerm
    : PARSEOP_CASE '('              {$<n>$ = TrCreateLeafNode (PARSEOP_CASE);}
        DataObject
        ')' '{'
            TermList '}'            {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | PARSEOP_CASE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ConcatTerm
    : PARSEOP_CONCATENATE '('       {$<n>$ = TrCreateLeafNode (PARSEOP_CONCATENATE);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_CONCATENATE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ConcatResTerm
    : PARSEOP_CONCATENATERESTEMPLATE '('    {$<n>$ = TrCreateLeafNode (PARSEOP_CONCATENATERESTEMPLATE);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_CONCATENATERESTEMPLATE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ConnectionTerm
    : PARSEOP_CONNECTION '('
        NameString
        ')'                         {$$ = TrCreateNode (PARSEOP_CONNECTION,1,$3);}
    | PARSEOP_CONNECTION '('        {$<n>$ = TrCreateLeafNode (PARSEOP_CONNECTION);}
        ResourceMacroTerm
        ')'                         {$$ = TrLinkChildren ($<n>3, 1,
                                            TrLinkChildren (TrCreateLeafNode (PARSEOP_RESOURCETEMPLATE), 3,
                                                TrCreateLeafNode (PARSEOP_DEFAULT_ARG),
                                                TrCreateLeafNode (PARSEOP_DEFAULT_ARG),
                                                $4));}
    | PARSEOP_CONNECTION '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

CondRefOfTerm
    : PARSEOP_CONDREFOF '('         {$<n>$ = TrCreateLeafNode (PARSEOP_CONDREFOF);}
        SuperName
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_CONDREFOF '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ContinueTerm
    : PARSEOP_CONTINUE              {$$ = TrCreateNode (PARSEOP_CONTINUE, 0);}
    ;

CopyObjectTerm
    : PARSEOP_COPYOBJECT '('        {$<n>$ = TrCreateLeafNode (PARSEOP_COPYOBJECT);}
        TermArg
        ',' SimpleTarget
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,TrSetNodeFlags ($6, NODE_IS_TARGET));}
    | PARSEOP_COPYOBJECT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

CreateBitFieldTerm
    : PARSEOP_CREATEBITFIELD '('    {$<n>$ = TrCreateLeafNode (PARSEOP_CREATEBITFIELD);}
        TermArg
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,TrSetNodeFlags ($6, NODE_IS_NAME_DECLARATION));}
    | PARSEOP_CREATEBITFIELD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

CreateByteFieldTerm
    : PARSEOP_CREATEBYTEFIELD '('   {$<n>$ = TrCreateLeafNode (PARSEOP_CREATEBYTEFIELD);}
        TermArg
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,TrSetNodeFlags ($6, NODE_IS_NAME_DECLARATION));}
    | PARSEOP_CREATEBYTEFIELD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

CreateDWordFieldTerm
    : PARSEOP_CREATEDWORDFIELD '('  {$<n>$ = TrCreateLeafNode (PARSEOP_CREATEDWORDFIELD);}
        TermArg
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,TrSetNodeFlags ($6, NODE_IS_NAME_DECLARATION));}
    | PARSEOP_CREATEDWORDFIELD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

CreateFieldTerm
    : PARSEOP_CREATEFIELD '('       {$<n>$ = TrCreateLeafNode (PARSEOP_CREATEFIELD);}
        TermArg
        TermArgItem
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,4,$4,$5,$6,TrSetNodeFlags ($7, NODE_IS_NAME_DECLARATION));}
    | PARSEOP_CREATEFIELD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

CreateQWordFieldTerm
    : PARSEOP_CREATEQWORDFIELD '('  {$<n>$ = TrCreateLeafNode (PARSEOP_CREATEQWORDFIELD);}
        TermArg
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,TrSetNodeFlags ($6, NODE_IS_NAME_DECLARATION));}
    | PARSEOP_CREATEQWORDFIELD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

CreateWordFieldTerm
    : PARSEOP_CREATEWORDFIELD '('   {$<n>$ = TrCreateLeafNode (PARSEOP_CREATEWORDFIELD);}
        TermArg
        TermArgItem
        NameStringItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,TrSetNodeFlags ($6, NODE_IS_NAME_DECLARATION));}
    | PARSEOP_CREATEWORDFIELD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

DataRegionTerm
    : PARSEOP_DATATABLEREGION '('   {$<n>$ = TrCreateLeafNode (PARSEOP_DATATABLEREGION);}
        NameString
        TermArgItem
        TermArgItem
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,4,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION),$5,$6,$7);}
    | PARSEOP_DATATABLEREGION '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

DebugTerm
    : PARSEOP_DEBUG                 {$$ = TrCreateLeafNode (PARSEOP_DEBUG);}
    ;

DecTerm
    : PARSEOP_DECREMENT '('         {$<n>$ = TrCreateLeafNode (PARSEOP_DECREMENT);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_DECREMENT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

DefaultTerm
    : PARSEOP_DEFAULT '{'           {$<n>$ = TrCreateLeafNode (PARSEOP_DEFAULT);}
        TermList '}'                {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_DEFAULT '{'
        error '}'                   {$$ = AslDoError(); yyclearin;}
    ;

DerefOfTerm
    : PARSEOP_DEREFOF '('           {$<n>$ = TrCreateLeafNode (PARSEOP_DEREFOF);}
        TermArg
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_DEREFOF '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

DeviceTerm
    : PARSEOP_DEVICE '('            {$<n>$ = TrCreateLeafNode (PARSEOP_DEVICE);}
        NameString
        ')' '{'
            TermList '}'            {$$ = TrLinkChildren ($<n>3,2,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION),$7);}
    | PARSEOP_DEVICE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

DivideTerm
    : PARSEOP_DIVIDE '('            {$<n>$ = TrCreateLeafNode (PARSEOP_DIVIDE);}
        TermArg
        TermArgItem
        Target
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,4,$4,$5,$6,$7);}
    | PARSEOP_DIVIDE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

EISAIDTerm
    : PARSEOP_EISAID '('
        StringData ')'              {$$ = TrUpdateNode (PARSEOP_EISAID, $3);}
    | PARSEOP_EISAID '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ElseIfTerm
    : IfTerm ElseTerm               {$$ = TrLinkPeerNode ($1,$2);}
    ;

ElseTerm
    :                               {$$ = NULL;}
    | PARSEOP_ELSE '{'              {$<n>$ = TrCreateLeafNode (PARSEOP_ELSE);}
        TermList '}'                {$$ = TrLinkChildren ($<n>3,1,$4);}

    | PARSEOP_ELSE '{'
        error '}'                   {$$ = AslDoError(); yyclearin;}

    | PARSEOP_ELSE
        error                       {$$ = AslDoError(); yyclearin;}

    | PARSEOP_ELSEIF '('            {$<n>$ = TrCreateLeafNode (PARSEOP_ELSE);}
        TermArg                     {$<n>$ = TrCreateLeafNode (PARSEOP_IF);}
        ')' '{'
            TermList '}'            {TrLinkChildren ($<n>5,2,$4,$8);}
        ElseTerm                    {TrLinkPeerNode ($<n>5,$11);}
                                    {$$ = TrLinkChildren ($<n>3,1,$<n>5);}

    | PARSEOP_ELSEIF '('
        error ')'                   {$$ = AslDoError(); yyclearin;}

    | PARSEOP_ELSEIF
        error                       {$$ = AslDoError(); yyclearin;}
    ;

EventTerm
    : PARSEOP_EVENT '('             {$<n>$ = TrCreateLeafNode (PARSEOP_EVENT);}
        NameString
        ')'                         {$$ = TrLinkChildren ($<n>3,1,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION));}
    | PARSEOP_EVENT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ExternalTerm
    : PARSEOP_EXTERNAL '('
        NameString
        OptionalObjectTypeKeyword
        OptionalParameterTypePackage
        OptionalParameterTypesPackage
        ')'                         {$$ = TrCreateNode (PARSEOP_EXTERNAL,4,$3,$4,$5,$6);}
    | PARSEOP_EXTERNAL '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

FatalTerm
    : PARSEOP_FATAL '('             {$<n>$ = TrCreateLeafNode (PARSEOP_FATAL);}
        ByteConstExpr
        ',' DWordConstExpr
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7);}
    | PARSEOP_FATAL '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

FieldTerm
    : PARSEOP_FIELD '('             {$<n>$ = TrCreateLeafNode (PARSEOP_FIELD);}
        NameString
        ',' AccessTypeKeyword
        ',' LockRuleKeyword
        ',' UpdateRuleKeyword
        ')' '{'
            FieldUnitList '}'       {$$ = TrLinkChildren ($<n>3,5,$4,$6,$8,$10,$13);}
    | PARSEOP_FIELD '('
        error ')' '{' error '}'     {$$ = AslDoError(); yyclearin;}
    ;

FindSetLeftBitTerm
    : PARSEOP_FINDSETLEFTBIT '('    {$<n>$ = TrCreateLeafNode (PARSEOP_FINDSETLEFTBIT);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_FINDSETLEFTBIT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

FindSetRightBitTerm
    : PARSEOP_FINDSETRIGHTBIT '('   {$<n>$ = TrCreateLeafNode (PARSEOP_FINDSETRIGHTBIT);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_FINDSETRIGHTBIT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

    /* Convert a For() loop to a While() loop */
ForTerm
    : PARSEOP_FOR '('               {$<n>$ = TrCreateLeafNode (PARSEOP_WHILE);}
        OptionalTermArg ','         {}
        OptionalPredicate ','
        OptionalTermArg             {$<n>$ = TrLinkPeerNode ($4,$<n>3);
                                        TrSetParent ($9,$<n>3);}                /* New parent is WHILE */
        ')' '{' TermList '}'        {$<n>$ = TrLinkChildren ($<n>3,2,$7,$13);}
                                    {$<n>$ = TrLinkPeerNode ($13,$9);
                                        $$ = $<n>10;}
    ;

OptionalPredicate
    :                               {$$ = TrCreateValuedLeafNode (PARSEOP_INTEGER, 1);}
    | TermArg                       {$$ = $1;}
    ;

FprintfTerm
    : PARSEOP_FPRINTF '('            {$<n>$ = TrCreateLeafNode (PARSEOP_FPRINTF);}
        TermArg ','
        StringData
        PrintfArgList
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$6,$7);}
    | PARSEOP_FPRINTF '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

FromBCDTerm
    : PARSEOP_FROMBCD '('           {$<n>$ = TrCreateLeafNode (PARSEOP_FROMBCD);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_FROMBCD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

FunctionTerm
    : PARSEOP_FUNCTION '('          {$<n>$ = TrCreateLeafNode (PARSEOP_METHOD);}
        NameString
        OptionalParameterTypePackage
        OptionalParameterTypesPackage
        ')' '{'
            TermList '}'            {$$ = TrLinkChildren ($<n>3,7,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION),
                                        TrCreateValuedLeafNode (PARSEOP_BYTECONST, 0),
                                        TrCreateLeafNode (PARSEOP_SERIALIZERULE_NOTSERIAL),
                                        TrCreateValuedLeafNode (PARSEOP_BYTECONST, 0),$5,$6,$9);}
    | PARSEOP_FUNCTION '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

IfTerm
    : PARSEOP_IF '('                {$<n>$ = TrCreateLeafNode (PARSEOP_IF);}
        TermArg
        ')' '{'
            TermList '}'            {$$ = TrLinkChildren ($<n>3,2,$4,$7);}

    | PARSEOP_IF '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

IncludeTerm
    : PARSEOP_INCLUDE '('
        String  ')'                 {$$ = TrUpdateNode (PARSEOP_INCLUDE, $3);
                                        FlOpenIncludeFile ($3);}
    ;

IncludeEndTerm
    : PARSEOP_INCLUDE_END           {$<n>$ = TrCreateLeafNode (PARSEOP_INCLUDE_END); TrSetCurrentFilename ($$);}
    ;

IncTerm
    : PARSEOP_INCREMENT '('         {$<n>$ = TrCreateLeafNode (PARSEOP_INCREMENT);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_INCREMENT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

IndexFieldTerm
    : PARSEOP_INDEXFIELD '('        {$<n>$ = TrCreateLeafNode (PARSEOP_INDEXFIELD);}
        NameString
        NameStringItem
        ',' AccessTypeKeyword
        ',' LockRuleKeyword
        ',' UpdateRuleKeyword
        ')' '{'
            FieldUnitList '}'       {$$ = TrLinkChildren ($<n>3,6,$4,$5,$7,$9,$11,$14);}
    | PARSEOP_INDEXFIELD '('
        error ')' '{' error '}'     {$$ = AslDoError(); yyclearin;}
    ;

IndexTerm
    : PARSEOP_INDEX '('             {$<n>$ = TrCreateLeafNode (PARSEOP_INDEX);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_INDEX '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

LAndTerm
    : PARSEOP_LAND '('              {$<n>$ = TrCreateLeafNode (PARSEOP_LAND);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_LAND '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

LEqualTerm
    : PARSEOP_LEQUAL '('            {$<n>$ = TrCreateLeafNode (PARSEOP_LEQUAL);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_LEQUAL '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

LGreaterEqualTerm
    : PARSEOP_LGREATEREQUAL '('     {$<n>$ = TrCreateLeafNode (PARSEOP_LLESS);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrCreateNode (PARSEOP_LNOT, 1, TrLinkChildren ($<n>3,2,$4,$5));}
    | PARSEOP_LGREATEREQUAL '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

LGreaterTerm
    : PARSEOP_LGREATER '('          {$<n>$ = TrCreateLeafNode (PARSEOP_LGREATER);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_LGREATER '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

LLessEqualTerm
    : PARSEOP_LLESSEQUAL '('        {$<n>$ = TrCreateLeafNode (PARSEOP_LGREATER);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrCreateNode (PARSEOP_LNOT, 1, TrLinkChildren ($<n>3,2,$4,$5));}
    | PARSEOP_LLESSEQUAL '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

LLessTerm
    : PARSEOP_LLESS '('             {$<n>$ = TrCreateLeafNode (PARSEOP_LLESS);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_LLESS '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

LNotEqualTerm
    : PARSEOP_LNOTEQUAL '('         {$<n>$ = TrCreateLeafNode (PARSEOP_LEQUAL);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrCreateNode (PARSEOP_LNOT, 1, TrLinkChildren ($<n>3,2,$4,$5));}
    | PARSEOP_LNOTEQUAL '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

LNotTerm
    : PARSEOP_LNOT '('              {$<n>$ = TrCreateLeafNode (PARSEOP_LNOT);}
        TermArg
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_LNOT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

LoadTableTerm
    : PARSEOP_LOADTABLE '('         {$<n>$ = TrCreateLeafNode (PARSEOP_LOADTABLE);}
        TermArg
        TermArgItem
        TermArgItem
        OptionalListString
        OptionalListString
        OptionalReference
        ')'                         {$$ = TrLinkChildren ($<n>3,6,$4,$5,$6,$7,$8,$9);}
    | PARSEOP_LOADTABLE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

LoadTerm
    : PARSEOP_LOAD '('              {$<n>$ = TrCreateLeafNode (PARSEOP_LOAD);}
        NameString
        RequiredTarget
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_LOAD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

LocalTerm
    : PARSEOP_LOCAL0                {$$ = TrCreateLeafNode (PARSEOP_LOCAL0);}
    | PARSEOP_LOCAL1                {$$ = TrCreateLeafNode (PARSEOP_LOCAL1);}
    | PARSEOP_LOCAL2                {$$ = TrCreateLeafNode (PARSEOP_LOCAL2);}
    | PARSEOP_LOCAL3                {$$ = TrCreateLeafNode (PARSEOP_LOCAL3);}
    | PARSEOP_LOCAL4                {$$ = TrCreateLeafNode (PARSEOP_LOCAL4);}
    | PARSEOP_LOCAL5                {$$ = TrCreateLeafNode (PARSEOP_LOCAL5);}
    | PARSEOP_LOCAL6                {$$ = TrCreateLeafNode (PARSEOP_LOCAL6);}
    | PARSEOP_LOCAL7                {$$ = TrCreateLeafNode (PARSEOP_LOCAL7);}
    ;

LOrTerm
    : PARSEOP_LOR '('               {$<n>$ = TrCreateLeafNode (PARSEOP_LOR);}
        TermArg
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_LOR '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

MatchTerm
    : PARSEOP_MATCH '('             {$<n>$ = TrCreateLeafNode (PARSEOP_MATCH);}
        TermArg
        ',' MatchOpKeyword
        TermArgItem
        ',' MatchOpKeyword
        TermArgItem
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,6,$4,$6,$7,$9,$10,$11);}
    | PARSEOP_MATCH '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

MethodTerm
    : PARSEOP_METHOD  '('           {$<n>$ = TrCreateLeafNode (PARSEOP_METHOD);}
        NameString
        OptionalByteConstExpr       {UtCheckIntegerRange ($5, 0, 7);}
        OptionalSerializeRuleKeyword
        OptionalByteConstExpr
        OptionalParameterTypePackage
        OptionalParameterTypesPackage
        ')' '{'
            TermList '}'            {$$ = TrLinkChildren ($<n>3,7,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION),$5,$7,$8,$9,$10,$13);}
    | PARSEOP_METHOD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

MidTerm
    : PARSEOP_MID '('               {$<n>$ = TrCreateLeafNode (PARSEOP_MID);}
        TermArg
        TermArgItem
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,4,$4,$5,$6,$7);}
    | PARSEOP_MID '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ModTerm
    : PARSEOP_MOD '('               {$<n>$ = TrCreateLeafNode (PARSEOP_MOD);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_MOD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

MultiplyTerm
    : PARSEOP_MULTIPLY '('          {$<n>$ = TrCreateLeafNode (PARSEOP_MULTIPLY);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_MULTIPLY '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

MutexTerm
    : PARSEOP_MUTEX '('             {$<n>$ = TrCreateLeafNode (PARSEOP_MUTEX);}
        NameString
        ',' ByteConstExpr
        ')'                         {$$ = TrLinkChildren ($<n>3,2,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION),$6);}
    | PARSEOP_MUTEX '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

NameTerm
    : PARSEOP_NAME '('              {$<n>$ = TrCreateLeafNode (PARSEOP_NAME);}
        NameString
        ',' DataObject
        ')'                         {$$ = TrLinkChildren ($<n>3,2,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION),$6);}
    | PARSEOP_NAME '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

NAndTerm
    : PARSEOP_NAND '('              {$<n>$ = TrCreateLeafNode (PARSEOP_NAND);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_NAND '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

NoOpTerm
    : PARSEOP_NOOP                  {$$ = TrCreateNode (PARSEOP_NOOP, 0);}
    ;

NOrTerm
    : PARSEOP_NOR '('               {$<n>$ = TrCreateLeafNode (PARSEOP_NOR);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_NOR '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

NotifyTerm
    : PARSEOP_NOTIFY '('            {$<n>$ = TrCreateLeafNode (PARSEOP_NOTIFY);}
        SuperName
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_NOTIFY '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

NotTerm
    : PARSEOP_NOT '('               {$<n>$ = TrCreateLeafNode (PARSEOP_NOT);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_NOT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ObjectTypeTerm
    : PARSEOP_OBJECTTYPE '('        {$<n>$ = TrCreateLeafNode (PARSEOP_OBJECTTYPE);}
        ObjectTypeName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_OBJECTTYPE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

OffsetTerm
    : PARSEOP_OFFSET '('
        AmlPackageLengthTerm
        ')'                         {$$ = TrCreateNode (PARSEOP_OFFSET,1,$3);}
    | PARSEOP_OFFSET '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

OpRegionTerm
    : PARSEOP_OPERATIONREGION '('   {$<n>$ = TrCreateLeafNode (PARSEOP_OPERATIONREGION);}
        NameString
        ',' OpRegionSpaceIdTerm
        TermArgItem
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,4,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION),$6,$7,$8);}
    | PARSEOP_OPERATIONREGION '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

OpRegionSpaceIdTerm
    : RegionSpaceKeyword            {}
    | ByteConst                     {$$ = UtCheckIntegerRange ($1, 0x80, 0xFF);}
    ;

OrTerm
    : PARSEOP_OR '('                {$<n>$ = TrCreateLeafNode (PARSEOP_OR);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_OR '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

PackageTerm
    : PARSEOP_PACKAGE               {$<n>$ = TrCreateLeafNode (PARSEOP_VAR_PACKAGE);}
        OptionalDataCount
        '{' PackageList '}'         {$$ = TrLinkChildren ($<n>2,2,$3,$5);}

PowerResTerm
    : PARSEOP_POWERRESOURCE '('     {$<n>$ = TrCreateLeafNode (PARSEOP_POWERRESOURCE);}
        NameString
        ',' ByteConstExpr
        ',' WordConstExpr
        ')' '{'
            TermList '}'            {$$ = TrLinkChildren ($<n>3,4,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION),$6,$8,$11);}
    | PARSEOP_POWERRESOURCE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

PrintfTerm
    : PARSEOP_PRINTF '('            {$<n>$ = TrCreateLeafNode (PARSEOP_PRINTF);}
        StringData
        PrintfArgList
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_PRINTF '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

PrintfArgList
    :                               {$$ = NULL;}
    | TermArg                       {$$ = $1;}
    | PrintfArgList ','
       TermArg                      {$$ = TrLinkPeerNode ($1, $3);}
    ;

ProcessorTerm
    : PARSEOP_PROCESSOR '('         {$<n>$ = TrCreateLeafNode (PARSEOP_PROCESSOR);}
        NameString
        ',' ByteConstExpr
        OptionalDWordConstExpr
        OptionalByteConstExpr
        ')' '{'
            TermList '}'            {$$ = TrLinkChildren ($<n>3,5,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION),$6,$7,$8,$11);}
    | PARSEOP_PROCESSOR '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

RawDataBufferTerm
    : PARSEOP_DATABUFFER  '('       {$<n>$ = TrCreateLeafNode (PARSEOP_DATABUFFER);}
        OptionalWordConst
        ')' '{'
            ByteList '}'            {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | PARSEOP_DATABUFFER '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

/*
 * In RefOf, the node isn't really a target, but we can't keep track of it after
 * we've taken a pointer to it. (hard to tell if a local becomes initialized this way.)
 */
RefOfTerm
    : PARSEOP_REFOF '('             {$<n>$ = TrCreateLeafNode (PARSEOP_REFOF);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,TrSetNodeFlags ($4, NODE_IS_TARGET));}
    | PARSEOP_REFOF '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ReleaseTerm
    : PARSEOP_RELEASE '('           {$<n>$ = TrCreateLeafNode (PARSEOP_RELEASE);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_RELEASE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ResetTerm
    : PARSEOP_RESET '('             {$<n>$ = TrCreateLeafNode (PARSEOP_RESET);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_RESET '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ReturnTerm
    : PARSEOP_RETURN '('            {$<n>$ = TrCreateLeafNode (PARSEOP_RETURN);}
        OptionalReturnArg
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_RETURN                {$$ = TrLinkChildren (TrCreateLeafNode (PARSEOP_RETURN),1,TrSetNodeFlags (TrCreateLeafNode (PARSEOP_ZERO), NODE_IS_NULL_RETURN));}
    | PARSEOP_RETURN '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ScopeTerm
    : PARSEOP_SCOPE '('             {$<n>$ = TrCreateLeafNode (PARSEOP_SCOPE);}
        NameString
        ')' '{'
            TermList '}'            {$$ = TrLinkChildren ($<n>3,2,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION),$7);}
    | PARSEOP_SCOPE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ShiftLeftTerm
    : PARSEOP_SHIFTLEFT '('         {$<n>$ = TrCreateLeafNode (PARSEOP_SHIFTLEFT);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_SHIFTLEFT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ShiftRightTerm
    : PARSEOP_SHIFTRIGHT '('        {$<n>$ = TrCreateLeafNode (PARSEOP_SHIFTRIGHT);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_SHIFTRIGHT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

SignalTerm
    : PARSEOP_SIGNAL '('            {$<n>$ = TrCreateLeafNode (PARSEOP_SIGNAL);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_SIGNAL '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

SizeOfTerm
    : PARSEOP_SIZEOF '('            {$<n>$ = TrCreateLeafNode (PARSEOP_SIZEOF);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_SIZEOF '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

SleepTerm
    : PARSEOP_SLEEP '('             {$<n>$ = TrCreateLeafNode (PARSEOP_SLEEP);}
        TermArg
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_SLEEP '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

StallTerm
    : PARSEOP_STALL '('             {$<n>$ = TrCreateLeafNode (PARSEOP_STALL);}
        TermArg
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_STALL '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

StoreTerm
    : PARSEOP_STORE '('             {$<n>$ = TrCreateLeafNode (PARSEOP_STORE);}
        TermArg
        ',' SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,TrSetNodeFlags ($6, NODE_IS_TARGET));}
    | PARSEOP_STORE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

SubtractTerm
    : PARSEOP_SUBTRACT '('          {$<n>$ = TrCreateLeafNode (PARSEOP_SUBTRACT);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_SUBTRACT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

SwitchTerm
    : PARSEOP_SWITCH '('            {$<n>$ = TrCreateLeafNode (PARSEOP_SWITCH);}
        TermArg
        ')' '{'
            CaseDefaultTermList '}'
                                    {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | PARSEOP_SWITCH '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ThermalZoneTerm
    : PARSEOP_THERMALZONE '('       {$<n>$ = TrCreateLeafNode (PARSEOP_THERMALZONE);}
        NameString
        ')' '{'
            TermList '}'            {$$ = TrLinkChildren ($<n>3,2,TrSetNodeFlags ($4, NODE_IS_NAME_DECLARATION),$7);}
    | PARSEOP_THERMALZONE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

TimerTerm
    : PARSEOP_TIMER '('             {$<n>$ = TrCreateLeafNode (PARSEOP_TIMER);}
        ')'                         {$$ = TrLinkChildren ($<n>3,0);}
    | PARSEOP_TIMER                 {$$ = TrLinkChildren (TrCreateLeafNode (PARSEOP_TIMER),0);}
    | PARSEOP_TIMER '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ToBCDTerm
    : PARSEOP_TOBCD '('             {$<n>$ = TrCreateLeafNode (PARSEOP_TOBCD);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_TOBCD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ToBufferTerm
    : PARSEOP_TOBUFFER '('          {$<n>$ = TrCreateLeafNode (PARSEOP_TOBUFFER);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_TOBUFFER '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ToDecimalStringTerm
    : PARSEOP_TODECIMALSTRING '('   {$<n>$ = TrCreateLeafNode (PARSEOP_TODECIMALSTRING);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_TODECIMALSTRING '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ToHexStringTerm
    : PARSEOP_TOHEXSTRING '('       {$<n>$ = TrCreateLeafNode (PARSEOP_TOHEXSTRING);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_TOHEXSTRING '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ToIntegerTerm
    : PARSEOP_TOINTEGER '('         {$<n>$ = TrCreateLeafNode (PARSEOP_TOINTEGER);}
        TermArg
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_TOINTEGER '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ToPLDTerm
    : PARSEOP_TOPLD '('             {$<n>$ = TrCreateLeafNode (PARSEOP_TOPLD);}
        PldKeywordList
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_TOPLD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

PldKeywordList
    :                               {$$ = NULL;}
    | PldKeyword
        PARSEOP_EXP_EQUALS Integer  {$$ = TrLinkChildren ($1,1,$3);}
    | PldKeyword
        PARSEOP_EXP_EQUALS String   {$$ = TrLinkChildren ($1,1,$3);}
    | PldKeywordList ','            /* Allows a trailing comma at list end */
    | PldKeywordList ','
        PldKeyword
        PARSEOP_EXP_EQUALS Integer  {$$ = TrLinkPeerNode ($1,TrLinkChildren ($3,1,$5));}
    | PldKeywordList ','
        PldKeyword
        PARSEOP_EXP_EQUALS String   {$$ = TrLinkPeerNode ($1,TrLinkChildren ($3,1,$5));}
    ;


ToStringTerm
    : PARSEOP_TOSTRING '('          {$<n>$ = TrCreateLeafNode (PARSEOP_TOSTRING);}
        TermArg
        OptionalCount
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_TOSTRING '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

ToUUIDTerm
    : PARSEOP_TOUUID '('
        StringData ')'              {$$ = TrUpdateNode (PARSEOP_TOUUID, $3);}
    | PARSEOP_TOUUID '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

UnicodeTerm
    : PARSEOP_UNICODE '('           {$<n>$ = TrCreateLeafNode (PARSEOP_UNICODE);}
        StringData
        ')'                         {$$ = TrLinkChildren ($<n>3,2,0,$4);}
    | PARSEOP_UNICODE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

UnloadTerm
    : PARSEOP_UNLOAD '('            {$<n>$ = TrCreateLeafNode (PARSEOP_UNLOAD);}
        SuperName
        ')'                         {$$ = TrLinkChildren ($<n>3,1,$4);}
    | PARSEOP_UNLOAD '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

WaitTerm
    : PARSEOP_WAIT '('              {$<n>$ = TrCreateLeafNode (PARSEOP_WAIT);}
        SuperName
        TermArgItem
        ')'                         {$$ = TrLinkChildren ($<n>3,2,$4,$5);}
    | PARSEOP_WAIT '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

XOrTerm
    : PARSEOP_XOR '('               {$<n>$ = TrCreateLeafNode (PARSEOP_XOR);}
        TermArg
        TermArgItem
        Target
        ')'                         {$$ = TrLinkChildren ($<n>3,3,$4,$5,$6);}
    | PARSEOP_XOR '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;

WhileTerm
    : PARSEOP_WHILE '('             {$<n>$ = TrCreateLeafNode (PARSEOP_WHILE);}
        TermArg
        ')' '{' TermList '}'
                                    {$$ = TrLinkChildren ($<n>3,2,$4,$7);}
    | PARSEOP_WHILE '('
        error ')'                   {$$ = AslDoError(); yyclearin;}
    ;
