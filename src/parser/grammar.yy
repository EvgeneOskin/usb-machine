%code requires {
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T

#include "math.h"
#include <iostream>
#include "stdio.h"
#include "parser/parsertypes.hpp"
#include "parser/ast.hpp"
#include "parser/parserspline.hpp"

    void flexrestart(FILE*);
    int grammarparse(Parser*);

#endif // YY_TYPEDEF_YY_SCANNER_T
}

%output  "y.tab.c"
%defines "y.tab.h"

%error-verbose
%define api.pure
%locations

%parse-param { Parser *parser }

%union
{
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
}

%code {

extern "C" int grammarlex(YYSTYPE* yylval, YYLTYPE* yylloc);
extern int grammarparse (Parser *parsxer);
extern "C" int grammarerror (YYLTYPE *llocp, Parser *parser, const char *msg);

int grammarerror (YYLTYPE  *llocp, Parser *parser, const char *msg) {
    // Add error handling routine as needed
    return parser->handleError
        (msg,
         llocp->first_line, llocp->first_column,
         llocp->last_line, llocp->last_column);
}
}

%token <key> VARS
%token <number> NUMBER
%token <integer> INTEGER

%token EOL
%token END
%token OP CP
%token EQU
%token Error_exit
%token SPLITTER
%token Error
%token SEMICOLON

%token PLUS
%token MINUS
%token MULT
%token DIVI
%token COMMA

%token SIN
%token COS
%token TAN
%token ASIN
%token ACOS
%token ATAN

%token SINH
%token COSH
%token TANH
%token ASINH
%token ACOSH
%token ATANH

%token EXP
%token LOG
%token LOG10
%token SQRT
%token FABS
%token POW

%type <lines> code_exp
%type <line> line
%type <var> exp new_spline
%type <ast> term factor IB_exp
%type <spline> spline spline_nodes

%type <ast_variable> ast_exp
%type <ast_line> ast_line
%type <ast_lines> ast_lines
%type <lines> loop


%%
input:
| code_exp END {
  return 0;
 }
;

code_exp: code_exp EOL new_spline {
    parser->newSpline($3);
}
| code_exp EOL line {
  $$ = parser->add2Lines($3);
}
| code_exp EOL loop
| code_exp EOL
| new_spline {
    parser->newSpline($1);
}
| line {
  $$ = parser->add2Lines($1);
}
| loop
;

loop: MULT INTEGER EOL ast_lines MULT {

  char error;
  for (int i = 0; i < $2; ++i) {
    for (ast_lines_t::iterator lines_i = $4->begin();
         lines_i != $4->end();
         ++lines_i) {
      line_t * line = new line_t();
      for (ast_line_t::iterator line_i = (*lines_i)->begin();
           line_i != (*lines_i)->end();
           ++line_i) {
          variable var(line_i->first, eval(line_i->second, parser, &error));
          if (error) { YYERROR;}

          line->insert(var);
      }
      parser->add2Lines(line);
      // for (line_t::iterator i = parser->current_vars->begin();
      //      i != parser->current_vars->end(); ++i) {
      //   std::cout << "current var =" << i->first <<  ' ' << i->second << '\n';
      // }
    }
  }
  $$ = NULL;
};

ast_lines: ast_lines ast_line EOL {
    $$ = add_to_ast_lines($2, $1);
}
| ast_line EOL {
    $$ = new_ast_lines($1);
};

ast_line: ast_line SPLITTER ast_exp {
    $$ = add_to_ast_line($1, $3);
}
| ast_exp {
    $$ = new_ast_line($1);
};

ast_exp: VARS EQU IB_exp {
  $$ = new ast_variable_t(*$1, $3);
};

line: line SPLITTER exp {
    $$ = parser->add2Line($1, $3);
}
| exp {
    $$ = parser->newLine($1);
};

new_spline: VARS EQU spline {
    $$ = new variable(*$1, $3);
};

spline: OP spline_nodes CP { $$ = $2; std::cout << "NEW ";};

spline_nodes: IB_exp SPLITTER IB_exp {
    char error = 0;
    $$ = new Spline();
    $$->add_node(eval($1, parser, &error), eval($3, parser, &error));
    if (error) { YYERROR;}
}
| spline_nodes COMMA IB_exp SPLITTER IB_exp {
    char error = 0;
    $1->add_node(eval($3, parser, &error), eval($5, parser, &error));
    if (error) { YYERROR;}

    $$ = $1;
};

exp: VARS EQU IB_exp {
    char error = 0;
    $$ = new variable(*$1, eval($3, parser, &error));
    if (error) { YYERROR;}
}
| VARS EQU VARS OP CP {
    char error = 0;
    $$ = new variable(*$1, parser->getSpline(*$3, &error));
    if (error) { YYERROR;}
};

IB_exp: IB_exp PLUS factor { $$ = new AST($1, $3, PLUS); }
| IB_exp MINUS factor { $$ = new AST($1, $3, MINUS); }
| factor
;

factor: factor MULT term {  $$ = new AST($1, $3, MULT); }
| factor DIVI term {  $$ = new AST($1, $3, DIVI); }
| term
;

term: VARS {$$ = new AST(*($1)); }
| NUMBER { $$ = new AST($1); }
| INTEGER { $$ = new AST((double) $1); }
| MINUS term { $$ = new AST(new AST(0.0), $2, MINUS); }
| OP IB_exp CP { $$ = $2; }
| SIN OP IB_exp CP { $$ = new AST($3, SIN); }
| COS OP IB_exp CP { $$ = new AST($3, COS); }
| TAN OP IB_exp CP { $$ = new AST($3, TAN); }
| ASIN OP IB_exp CP { $$ = new AST($3, ASIN); }
| ACOS OP IB_exp CP { $$ = new AST($3, ACOS); }
| ATAN OP IB_exp CP { $$ = new AST($3, ATAN); }
| SINH OP IB_exp CP { $$ = new AST($3, SINH); }
| COSH OP IB_exp CP { $$ = new AST($3, COSH); }
| TANH OP IB_exp CP { $$ = new AST($3, TANH); }
| ASINH OP IB_exp CP { $$ = new AST($3, ASINH); }
| ACOSH OP IB_exp CP { $$ = new AST($3, ACOSH); }
| ATANH OP IB_exp CP { $$ = new AST($3, ATANH); }
| EXP OP IB_exp CP { $$ = new AST($3, EXP); }
| LOG OP IB_exp CP { $$ = new AST($3, LOG); }
| LOG10 OP IB_exp CP { $$ = new AST($3, LOG10); }
| SQRT OP IB_exp CP { $$ = new AST($3, SQRT); }
| FABS OP IB_exp CP { $$ = new AST($3, FABS); }
| POW OP IB_exp COMMA IB_exp CP { $$ = new AST($3, $5, POW); }
;

%%
