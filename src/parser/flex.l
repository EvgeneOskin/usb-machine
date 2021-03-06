%{
#include "grammar_yacc.h"
#include <QObject>
#include <string>

#undef YY_DECL
#define YY_DECL extern "C" int grammarlex(YYSTYPE* yylval, YYLTYPE* yylloc)
%}


%option warn nodefault

%option noyywrap never-interactive
/* nounistd */
/* yylineno -- it store line number */
%option yylineno

%%
[ \t]*"="[ \t]* {
  return EQU;
}

[ \t]*";"[ \t]* {
  return SEMICOLON;
}

[0-9]+ {
  yylval->integer = atoi(yytext);
  return INTEGER;
}

[0-9]+"."([0-9]*)?([Ee][+-]?[0-9]+)? |
"."[0-9]*([Ee][+-]?[0-9]+)? {
  yylval->number = atof(yytext);
  //printf("catch num = \"%e\"\n", yylval.value);
  return NUMBER;
}

(pi) {
  yylval->number = 3.1415926535897932384626433832795;
  return NUMBER;
}

(e) {
  yylval->number = 2.718282;
  return NUMBER;
}

([ \t]*(";".*)?(\r)?\n)+ {
  return EOL;
}


[ \t]*"+"[ \t]*  {
  return PLUS;
}

[ \t]*"-"[ \t]*  {
  return MINUS;
}

[ \t]*"*"[ \t]*  {
  return MULT;
}

[ \t]*"/"[ \t]*  {
  return DIVI;
}

[ \t]*","[ \t]*  {
  return COMMA;
}

"("[ \t]*  {
  return OP;
}

[ \t]*")"  {
  return CP;
}

(sin) {
  return SIN;
}

(cos) {
  return COS;
}

(tan) {
  return TAN;
}

(asin) {
  return ASIN;
}

(acos) {
  return ACOS;
}

(atan) {
  return ATAN;
}

(sinh) {
  return SINH;
}

(cosh) {
  return COSH;
}

(tanh) {
  return TANH;
}

(asinh) {
  return ASINH;
}

(acosh) {
  return ACOSH;
}

(atanh) {
  return ATANH;
}

(exp) {
  return EXP;
}

(log) {
  return LOG;
}

(log10) {
  return LOG10;
}

(sqrt) {
  return SQRT;
}

(fabs) {
  return FABS;
}

(pow) {
  return POW;
}

([a-zA-Z][a-zA-Z0-9]*) {
  yylval->key = new std::string(yytext);
  return VARS;
}

[ \t]+ {
  return SPLITTER;
}

<<EOF>> {
  return END;
}

. {
  printf("unhandled: %s\n", yytext);
  return Error_exit;
}
