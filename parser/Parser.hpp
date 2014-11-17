/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* "%code requires" blocks.  */

/* Line 1685 of yacc.c  */
#line 1 "grammar.yy"

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T

#include "math.h"
#include <iostream>
#include "stdio.h"
#include "DEF.hpp"
#include "ast.hpp"
#include "spline.hpp"

extern "C" int yylex(void);

#endif // YY_TYPEDEF_YY_SCANNER_T



/* Line 1685 of yacc.c  */
#line 57 "Parser.hpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VARS = 258,
     NUMBER = 259,
     INTEGER = 260,
     EOL = 261,
     END = 262,
     OP = 263,
     CP = 264,
     EQU = 265,
     Error_exit = 266,
     SPLITTER = 267,
     Error = 268,
     SEMICOLON = 269,
     PLUS = 270,
     MINUS = 271,
     MULT = 272,
     DIVI = 273,
     COMMA = 274,
     SIN = 275,
     COS = 276,
     TAN = 277,
     ASIN = 278,
     ACOS = 279,
     ATAN = 280,
     SINH = 281,
     COSH = 282,
     TANH = 283,
     ASINH = 284,
     ACOSH = 285,
     ATANH = 286,
     EXP = 287,
     LOG = 288,
     LOG10 = 289,
     SQRT = 290,
     FABS = 291,
     POW = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 25 "grammar.yy"

  variable* var;
  std::string* key;

  AST* ast;
  ast_variable_t* ast_variable;
  ast_line_t* ast_line;
  ast_lines_t* ast_lines;

  double number;
  Spline * spline;
  int integer;
  line_t* line;
  lines_t* lines;



/* Line 1685 of yacc.c  */
#line 129 "Parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


