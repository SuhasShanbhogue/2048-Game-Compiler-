%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
#define RED "\e[0;31m"
#define NC "\e[0m"
%}

%union {

	char str[100];
	int iint;
}
%token<iint> ADD LEFT RIGHT UP DOWN  SUB MUL DIV 
%token<iint> COMMA NEWLINE QUIT ASSIGN TO VALUE IN IS VAR FULLSTOP
%token<iint> INTVALUE
%token<str> VARNAME 
%type<iint> MOVES ARITHMETIC DIRECTION SMALLCAPS1 SMALLCAPS2 SMALLCAPS3 MOVESPROBLEM1
%start operation

%%

operation :operation MOVES NEWLINE
	|operation MOVESPROBLEM1 NEWLINE
	|operation ASSIGNMENT NEWLINE
	|operation NAMING NEWLINE
	|operation QUERY NEWLINE
	|operation SMALLCAPS1 NEWLINE
	|operation SMALLCAPS2 NEWLINE
	|operation SMALLCAPS3 NEWLINE
	|operation error NEWLINE {yyerrok;}
	|operation error FULLSTOP NEWLINE
	|NEWLINE
	|



	;


SMALLCAPS1 : VARNAME DIRECTION FULLSTOP{
	fprintf(stderr, RED "Please make sure that the arithmetic operation is written in capitals and is one of : \nADD\nSUBTRACT\nMULTIPLY\nDIVIDE\n" NC);
	printf("2048-shell> ");
};

SMALLCAPS2 : ARITHMETIC VARNAME FULLSTOP{
	fprintf(stderr, RED "Please make sure that the direction is written in capitals and is one of : \nLEFT\nRIGHT\nUP\nDOWN\n" NC);
	printf("2048-shell> ");
};

SMALLCAPS3 : VARNAME VARNAME FULLSTOP{
	fprintf(stderr, RED "Please make sure that the arithmetic operation is written in capitals and is one of : \nADD\nSUBTRACT\nMULTIPLY\nDIVIDE\n" NC);
	fprintf(stderr, RED "Please make sure that the direction is written in capitals and is one of : \nLEFT\nRIGHT\nUP\nDOWN\n" NC);
	printf("2048-shell> ");
}


MOVESPROBLEM1 : ARITHMETIC DIRECTION{
	fprintf(stderr, RED "Please end all the commands with a fullstop.\n" NC);
	printf("2048-shell> ");
}

MOVES : ARITHMETIC DIRECTION FULLSTOP{
								int a = checkStateChangeForMove($2, $1);
								if(a == 1){
									move(1, $2, $1);
									printBoard();
									printf("2048-shell> ");
									fprintCurrentState();
								}
								else{
									printf("This move doesn't do anything!\n");
									printf("2048-shell> ");	
								}
							}

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


ASSIGNMENT : ASSIGN INTVALUE TO INTVALUE COMMA INTVALUE FULLSTOP{
														assign_value($2, $4, $6);
														printBoard();
														printf("2048-shell> ");
														}
	;


NAMING : VAR VARNAME IS INTVALUE COMMA INTVALUE FULLSTOP {
												name_variable($2, $4, $6);
												printBoard();
												printf("2048-shell> ");
												}
	;

QUERY : VALUE IN INTVALUE COMMA INTVALUE FULLSTOP {
											value_in($3, $5);
											printBoard();
											printf("2048-shell> ");
											}
	;
%%




void yyerror(const char* s) {
	fprintf(stderr, "-1\n");
	printf("Syntax Error!\n");
	printf("2048-shell> ");
}
