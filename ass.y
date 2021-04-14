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
%token<iint> COMMA NEWLINE QUIT ASSIGN TO VALUE IN IS VAR FULLSTOP GARBAGE
%token<iint> INTVALUE 
%token<str> VARNAME 
%type<iint> MOVES ARITHMETIC DIRECTION
%start operation

%%

operation :operation MOVES NEWLINE
	|operation ASSIGNMENT 
	|operation NAMING 
	|operation QUERY 
	|operation NEWLINE
	|operation GARBAGE {printf("syntax error");}
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


ASSIGNMENT : ASSIGN INTVALUE TO INTVALUE COMMA INTVALUE FULLSTOP NEWLINE {printf("%d,%d,%d\n",$2,$4,$6);
														assign_value($2, $4, $6);
														printBoard();}
			|ASSIGN INTVALUE TO INTVALUE COMMA INTVALUE NEWLINE {printf("You need to end a command with a full-stop.");}
	;


NAMING : VAR VARNAME IS INTVALUE COMMA INTVALUE FULLSTOP NEWLINE {printf("%s,%d,%d\n",$2,$4,$6);
												name_variable($2, $4, $6);
												printBoard(); }
		| VAR VARNAME IS INTVALUE COMMA INTVALUE NEWLINE	{printf("You need to end a command with a full-stop.");}									

	;

QUERY : VALUE IN INTVALUE COMMA INTVALUE FULLSTOP NEWLINE {printf("%d,%d\n",$3,$5);
											value_in($3, $5);
											printBoard();
											}
		| VALUE IN INTVALUE COMMA INTVALUE  NEWLINE {printf("You need to end a command with a full-stop.");}									
	;
%%




void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", "");
}
