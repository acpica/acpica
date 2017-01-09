NoEcho('
/******************************************************************************
 *
 * Module Name: aslcstyle.y - Production rules for symbolic operators
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

')

/*******************************************************************************
 *
 * Production rules for the symbolic (c-style) operators
 *
 ******************************************************************************/

/*
 * ASL Extensions: C-style math/logical operators and expressions.
 * The implementation transforms these operators into the standard
 * AML opcodes and syntax.
 *
 * Supported operators and precedence rules (high-to-low)
 *
 * NOTE: The operator precedence and associativity rules are
 * implemented by the tokens in asltokens.y
 *
 * (left-to-right):
 *  1)      ( ) expr++ expr--
 *
 * (right-to-left):
 *  2)      ! ~
 *
 * (left-to-right):
 *  3)      *   /   %
 *  4)      +   -
 *  5)      >>  <<
 *  6)      <   >   <=  >=
 *  7)      ==  !=
 *  8)      &
 *  9)      ^
 *  10)     |
 *  11)     &&
 *  12)     ||
 *
 * (right-to-left):
 *  13)     = += -= *= /= %= <<= >>= &= ^= |=
 */


/*******************************************************************************
 *
 * Basic operations for math and logical expressions.
 *
 ******************************************************************************/

Expression

    /* Unary operators */

    : PARSEOP_EXP_LOGICAL_NOT           {$<n>$ = TrCreateLeafNode (PARSEOP_LNOT);}
        TermArg                         {$$ = TrLinkChildren ($<n>2,1,$3);}
    | PARSEOP_EXP_NOT                   {$<n>$ = TrCreateLeafNode (PARSEOP_NOT);}
        TermArg                         {$$ = TrLinkChildren ($<n>2,2,$3,TrCreateNullTarget ());}

    | SuperName PARSEOP_EXP_INCREMENT   {$<n>$ = TrCreateLeafNode (PARSEOP_INCREMENT);}
                                        {$$ = TrLinkChildren ($<n>3,1,$1);}
    | SuperName PARSEOP_EXP_DECREMENT   {$<n>$ = TrCreateLeafNode (PARSEOP_DECREMENT);}
                                        {$$ = TrLinkChildren ($<n>3,1,$1);}

    /* Binary operators: math and logical */

    | TermArg PARSEOP_EXP_ADD           {$<n>$ = TrCreateLeafNode (PARSEOP_ADD);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,TrCreateNullTarget ());}
    | TermArg PARSEOP_EXP_DIVIDE        {$<n>$ = TrCreateLeafNode (PARSEOP_DIVIDE);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,4,$1,$4,TrCreateNullTarget (),
                                            TrCreateNullTarget ());}
    | TermArg PARSEOP_EXP_MODULO        {$<n>$ = TrCreateLeafNode (PARSEOP_MOD);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,TrCreateNullTarget ());}
    | TermArg PARSEOP_EXP_MULTIPLY      {$<n>$ = TrCreateLeafNode (PARSEOP_MULTIPLY);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,TrCreateNullTarget ());}
    | TermArg PARSEOP_EXP_SHIFT_LEFT    {$<n>$ = TrCreateLeafNode (PARSEOP_SHIFTLEFT);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,TrCreateNullTarget ());}
    | TermArg PARSEOP_EXP_SHIFT_RIGHT   {$<n>$ = TrCreateLeafNode (PARSEOP_SHIFTRIGHT);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,TrCreateNullTarget ());}
    | TermArg PARSEOP_EXP_SUBTRACT      {$<n>$ = TrCreateLeafNode (PARSEOP_SUBTRACT);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,TrCreateNullTarget ());}

    | TermArg PARSEOP_EXP_AND           {$<n>$ = TrCreateLeafNode (PARSEOP_AND);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,TrCreateNullTarget ());}
    | TermArg PARSEOP_EXP_OR            {$<n>$ = TrCreateLeafNode (PARSEOP_OR);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,TrCreateNullTarget ());}
    | TermArg PARSEOP_EXP_XOR           {$<n>$ = TrCreateLeafNode (PARSEOP_XOR);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,TrCreateNullTarget ());}

    | TermArg PARSEOP_EXP_GREATER       {$<n>$ = TrCreateLeafNode (PARSEOP_LGREATER);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,2,$1,$4);}
    | TermArg PARSEOP_EXP_GREATER_EQUAL {$<n>$ = TrCreateLeafNode (PARSEOP_LGREATEREQUAL);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,2,$1,$4);}
    | TermArg PARSEOP_EXP_LESS          {$<n>$ = TrCreateLeafNode (PARSEOP_LLESS);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,2,$1,$4);}
    | TermArg PARSEOP_EXP_LESS_EQUAL    {$<n>$ = TrCreateLeafNode (PARSEOP_LLESSEQUAL);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,2,$1,$4);}

    | TermArg PARSEOP_EXP_EQUAL         {$<n>$ = TrCreateLeafNode (PARSEOP_LEQUAL);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,2,$1,$4);}
    | TermArg PARSEOP_EXP_NOT_EQUAL     {$<n>$ = TrCreateLeafNode (PARSEOP_LNOTEQUAL);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,2,$1,$4);}

    | TermArg PARSEOP_EXP_LOGICAL_AND   {$<n>$ = TrCreateLeafNode (PARSEOP_LAND);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,2,$1,$4);}
    | TermArg PARSEOP_EXP_LOGICAL_OR    {$<n>$ = TrCreateLeafNode (PARSEOP_LOR);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,2,$1,$4);}

    /* Parentheses */

    | PARSEOP_OPEN_PAREN
        Expression
        PARSEOP_CLOSE_PAREN             {$$ = $2;}

    /* Index term -- "= BUF1[5]" on right-hand side of an equals (source) */

    | IndexExpTerm
    ;

    /*
     * Index term -- "BUF1[5] = " or " = BUF1[5] on either the left side
     * of an equals (target) or the right side (source)
     * Currently used in these terms:
     *      Expression
     *      ObjectTypeSource
     *      DerefOfSource
     *      Type6Opcode
     */
IndexExpTerm

    : SuperName
        PARSEOP_EXP_INDEX_LEFT
        TermArg
        PARSEOP_EXP_INDEX_RIGHT         {$$ = TrCreateLeafNode (PARSEOP_INDEX);
                                        TrLinkChildren ($$,3,$1,$3,TrCreateNullTarget ());}
    ;


/*******************************************************************************
 *
 * All assignment-type operations -- math and logical. Includes simple
 * assignment and compound assignments.
 *
 ******************************************************************************/

EqualsTerm

    /* Allow parens anywhere */

    : PARSEOP_OPEN_PAREN
        EqualsTerm
        PARSEOP_CLOSE_PAREN             {$$ = $2;}

    /* Simple Store() operation */

    | SuperName
        PARSEOP_EXP_EQUALS
        TermArg                         {$$ = TrCreateAssignmentNode ($1, $3);}

    /* Chained equals: (a=RefOf)=b, a=b=c=d etc. */

    | PARSEOP_OPEN_PAREN
        EqualsTerm
        PARSEOP_CLOSE_PAREN
        PARSEOP_EXP_EQUALS
        TermArg                         {$$ = TrCreateAssignmentNode ($2, $5);}

    /* Compound assignments -- Add (operand, operand, target) */

    | TermArg PARSEOP_EXP_ADD_EQ        {$<n>$ = TrCreateLeafNode (PARSEOP_ADD);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,
                                            TrSetNodeFlags (TrCreateTargetOperand ($1, NULL), NODE_IS_TARGET));}

    | TermArg PARSEOP_EXP_DIV_EQ        {$<n>$ = TrCreateLeafNode (PARSEOP_DIVIDE);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,4,$1,$4,TrCreateNullTarget (),
                                            TrSetNodeFlags (TrCreateTargetOperand ($1, NULL), NODE_IS_TARGET));}

    | TermArg PARSEOP_EXP_MOD_EQ        {$<n>$ = TrCreateLeafNode (PARSEOP_MOD);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,
                                            TrSetNodeFlags (TrCreateTargetOperand ($1, NULL), NODE_IS_TARGET));}

    | TermArg PARSEOP_EXP_MUL_EQ        {$<n>$ = TrCreateLeafNode (PARSEOP_MULTIPLY);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,
                                            TrSetNodeFlags (TrCreateTargetOperand ($1, NULL), NODE_IS_TARGET));}

    | TermArg PARSEOP_EXP_SHL_EQ        {$<n>$ = TrCreateLeafNode (PARSEOP_SHIFTLEFT);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,
                                            TrSetNodeFlags (TrCreateTargetOperand ($1, NULL), NODE_IS_TARGET));}

    | TermArg PARSEOP_EXP_SHR_EQ        {$<n>$ = TrCreateLeafNode (PARSEOP_SHIFTRIGHT);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,
                                            TrSetNodeFlags (TrCreateTargetOperand ($1, NULL), NODE_IS_TARGET));}

    | TermArg PARSEOP_EXP_SUB_EQ        {$<n>$ = TrCreateLeafNode (PARSEOP_SUBTRACT);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,
                                            TrSetNodeFlags (TrCreateTargetOperand ($1, NULL), NODE_IS_TARGET));}

    | TermArg PARSEOP_EXP_AND_EQ        {$<n>$ = TrCreateLeafNode (PARSEOP_AND);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,
                                            TrSetNodeFlags (TrCreateTargetOperand ($1, NULL), NODE_IS_TARGET));}

    | TermArg PARSEOP_EXP_OR_EQ         {$<n>$ = TrCreateLeafNode (PARSEOP_OR);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,
                                            TrSetNodeFlags (TrCreateTargetOperand ($1, NULL), NODE_IS_TARGET));}

    | TermArg PARSEOP_EXP_XOR_EQ        {$<n>$ = TrCreateLeafNode (PARSEOP_XOR);}
        TermArg                         {$$ = TrLinkChildren ($<n>3,3,$1,$4,
                                            TrSetNodeFlags (TrCreateTargetOperand ($1, NULL), NODE_IS_TARGET));}
    ;
