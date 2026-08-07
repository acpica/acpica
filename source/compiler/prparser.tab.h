/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PRPARSER_TAB_H_INCLUDED
# define YY_YY_PRPARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    EXPOP_EOF = 258,               /* EXPOP_EOF  */
    EXPOP_NEW_LINE = 259,          /* EXPOP_NEW_LINE  */
    EXPOP_NUMBER = 260,            /* EXPOP_NUMBER  */
    EXPOP_HEX_NUMBER = 261,        /* EXPOP_HEX_NUMBER  */
    EXPOP_RESERVED1 = 262,         /* EXPOP_RESERVED1  */
    EXPOP_RESERVED2 = 263,         /* EXPOP_RESERVED2  */
    EXPOP_PAREN_OPEN = 264,        /* EXPOP_PAREN_OPEN  */
    EXPOP_PAREN_CLOSE = 265,       /* EXPOP_PAREN_CLOSE  */
    EXPOP_QUESTION = 266,          /* EXPOP_QUESTION  */
    EXPOP_COLON = 267,             /* EXPOP_COLON  */
    EXPOP_LOGICAL_OR = 268,        /* EXPOP_LOGICAL_OR  */
    EXPOP_LOGICAL_AND = 269,       /* EXPOP_LOGICAL_AND  */
    EXPOP_OR = 270,                /* EXPOP_OR  */
    EXPOP_XOR = 271,               /* EXPOP_XOR  */
    EXPOP_AND = 272,               /* EXPOP_AND  */
    EXPOP_EQUAL = 273,             /* EXPOP_EQUAL  */
    EXPOP_NOT_EQUAL = 274,         /* EXPOP_NOT_EQUAL  */
    EXPOP_GREATER = 275,           /* EXPOP_GREATER  */
    EXPOP_LESS = 276,              /* EXPOP_LESS  */
    EXPOP_GREATER_EQUAL = 277,     /* EXPOP_GREATER_EQUAL  */
    EXPOP_LESS_EQUAL = 278,        /* EXPOP_LESS_EQUAL  */
    EXPOP_SHIFT_RIGHT = 279,       /* EXPOP_SHIFT_RIGHT  */
    EXPOP_SHIFT_LEFT = 280,        /* EXPOP_SHIFT_LEFT  */
    EXPOP_ADD = 281,               /* EXPOP_ADD  */
    EXPOP_SUBTRACT = 282,          /* EXPOP_SUBTRACT  */
    EXPOP_MULTIPLY = 283,          /* EXPOP_MULTIPLY  */
    EXPOP_DIVIDE = 284,            /* EXPOP_DIVIDE  */
    EXPOP_MODULO = 285,            /* EXPOP_MODULO  */
    EXPOP_ONES_COMPLIMENT = 286,   /* EXPOP_ONES_COMPLIMENT  */
    EXPOP_LOGICAL_NOT = 287,       /* EXPOP_LOGICAL_NOT  */
    EXPOP_DEFINE = 288,            /* EXPOP_DEFINE  */
    EXPOP_IDENTIFIER = 289         /* EXPOP_IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 193 "prparser.y"

     UINT64                 value;
     UINT32                 op;
     char                   *str;

#line 104 "prparser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PRPARSER_TAB_H_INCLUDED  */
