%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {

	char str[100];
	int iint;
}
%token<iint> ADD LEFT RIGHT UP DOWN  SUB MUL DIV 
%token<iint> COMMA NEWLINE QUIT ASSIGN TO VALUE IN IS VAR FULLSTOP
%token<iint> INTVALUE 
%token<str> VARNAME 
%type<iint> MOVES ARITHMETIC DIRECTION
%start operation

%%

operation :operation MOVES NEWLINE
	|operation ASSIGNMENT FULLSTOP NEWLINE
	|operation NAMING FULLSTOP NEWLINE
	|operation QUERY FULLSTOP NEWLINE
	|NEWLINE
	|



	;

MOVES : ARITHMETIC DIRECTION FULLSTOP{printf("%d,%d\n",$1,$2);
								move(1, $2, $1);
								printBoard();}

	;

ARITHMETIC : ADD {$$ = $1;}
	| SUB {$$ = $1;}
	| MUL {$$ = $1;}
	| DIV {$$ = $1;}
	;

DIRECTION : UP {$$ = $1;}
	| DOWN {$$ = $1;}
	| LEFT {$$ = $1;}
	| RIGHT {$$ = $1;}

	;


ASSIGNMENT : ASSIGN INTVALUE TO INTVALUE COMMA INTVALUE {printf("%d,%d,%d",$2,$4,$6);}
	;


NAMING : VAR VARNAME IS INTVALUE COMMA INTVALUE {printf("%s,%d,%d",$2,$4,$6);}
	;

QUERY : VALUE IN INTVALUE COMMA INTVALUE {printf("%d,%d\n",$3,$5);
											value_in($3, $5);}
	;
%%




void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", "");
}