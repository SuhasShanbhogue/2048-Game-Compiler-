%option noyywrap

%{
#include <stdio.h>

#define YY_DECL int yylex()

#include "ass.tab.h"

%}

%%

[ \t]+	; // ignore all whitespace
\n		{return NEWLINE;}
\.	{return FULLSTOP;}
"ADD"	{yylval.iint = 1; return ADD;}
"SUBTRACT"	{yylval.iint = 2 ;return SUB;}
"MULTIPLY"	{yylval.iint = 3 ; return MUL;}
"DIVIDE"	{yylval.iint = 4; return DIV;}
"LEFT"	{yylval.iint = 5; return LEFT;}
"RIGHT" {yylval.iint = 6; return RIGHT;}
"UP"	{yylval.iint = 7; return UP;}
"DOWN" {yylval.iint = 8; return DOWN;}
"ASSIGN" {return ASSIGN;}
[0-9][0-9]* {yylval.iint = atoi(yytext); return INTVALUE;}
"TO" {return TO;}
"VALUE" {return VALUE;}
"IN" {return IN;}
"IS" {return IS;}
"VAR" {return VAR;}
, {return COMMA;}
"exit"		{return QUIT;}
"quit"		{return QUIT;}
[a-zA-Z][a-zA-Z0-9]* {strcpy(yylval.str,yytext); return VARNAME;}
[a-zA-Z0-9][ a-zA-Z0-9]* {return GARBAGE;}


%%



