#include "main.h"
#include<stdio.h>
#include "ass.tab.h"
#include<stdlib.h>

struct Board board;

void initialize();

void add1();

void printBoard();

void move(int insertRandom, int direction, int operation);

void moveLeft(int insertRandom, int operation);

void rotate90();

int main() {
	yyin = stdin;
	initialize();

	do {
		yyparse();
	} while(!feof(yyin));

	return 0;
}


void initialize(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			board.board[i][j] = 0;
		}
	}
}

// void add1(){
// 	for(int i=0; i<4; i++){
// 		for(int j=0; j<4; j++){
// 			board.board[i][j] += 1;
// 		}
// 	}
// }


void printBoard(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			printf("%d ", board.board[i][j]);
		}
		printf("\n");
	}
}

void value_in(int row, int col)
{
	printf("Value in %d, %d is: %d\n", row, col, board.board[row-1][col-1]);
}

void assign_value(int val, int row, int col)
{
	if(row>4 || col>4 || row<1 || col <1)
	{
		printf("There is no tile like that. The tile co-ordinates must be in the range 1,2,3,4.\n");
		return;
	}
	board.board[row-1][col-1]=val;
}

void move(int insertRandom, int direction, int operation){
	/*
		If direction = 
			LEFT 5
			RIGHT 6
			UP 7
			DOWN 8

		Whenever, a random tile is added, it searches for all zero tiles.
		Hence, if its a subtract operation, after getting a zero, the tile might get a new value.
		
	*/
	if(direction == 5){
		moveLeft(insertRandom, operation);
	}
	else if(direction == 6){
		rotate90();
		rotate90();
		moveLeft(insertRandom, operation);
		rotate90();
		rotate90();
	}
	else if(direction == 7){
		rotate90();
		rotate90();
		rotate90();
		moveLeft(insertRandom, operation);
		rotate90();
	}
	else if(direction == 8){
		rotate90();
		moveLeft(insertRandom, operation);
		rotate90();
		rotate90();
		rotate90();
	}
}


void moveLeft(int insertRandom, int operation){
	/*
		If operation = 
			ADD 1
			SUBTRACT 2
			MULTIPLY 3
			DIVIDE 4
	*/

	int i,j;
	for(i=0; i<4; i++){
		int temp[4];
		int tempIdx=0;
		for(j=0; j<4; j++){
			if((board.board)[i][j] != 0){
				temp[tempIdx] = (board.board)[i][j];
				tempIdx++;
			}
		}
		int temp2[4];
		int temp2Idx = 0;
		int k = 0;
		while(k < tempIdx){
			if(k < tempIdx - 1){
				if(temp[k] == temp[k+1]){
					// temp2[temp2Idx] = temp[k]*2;
					if(operation == 1){	temp2[temp2Idx] = temp[k]*2; }
					else if(operation == 2){ temp2[temp2Idx] = 0; }
					else if(operation == 3){ temp2[temp2Idx]  *= temp2[temp2Idx];}
					else{temp2[temp2Idx] = 1;}
					k++;	temp2Idx++;
				}
				else{
					temp2[temp2Idx] = temp[k];
					temp2Idx++;
				}
			}
			else{
				temp2[temp2Idx] = temp[k];
				temp2Idx++;
			}
			k++;
		}

		for(k=0; k<4; k++){
			if(k < temp2Idx){
				(board.board)[i][k] = temp2[k];
			}
			else{
				(board.board)[i][k] = 0;
			}
		}

	}

	int emptyIndexes[4][16][2];
	int tk[4];
	int tkIdx = 0;
	int rowIdx = 0;
	int eIdx = 0;

	for(i=0; i<4; i++){
		int temp[4][2];
		int tempIdx = 0;
		eIdx = 0;
		for(j=0; j<4; j++){
			if((board.board)[i][j] == 0){
				temp[tempIdx][0] = i;
				temp[tempIdx][1] = j;
				tempIdx++;
			}
			else{
				tempIdx = 0;
			}
		}
		if(tempIdx){
			for(int k=0; k<tempIdx; k++){
				emptyIndexes[rowIdx][eIdx][0] = temp[k][0];
				emptyIndexes[rowIdx][eIdx][1] = temp[k][1];
				eIdx++;
				tk[tkIdx] = eIdx;
			}
			rowIdx++;
			tkIdx++;
		}
	}

	int a = rand()%rowIdx;
	int b = rand()%tk[a];
	int k = rand()%2;
	// printf("New in %d, %d\n", emptyIndexes[a][0], emptyIndexes[a][1]);
	if(insertRandom){
		(board.board)[emptyIndexes[a][b][0]][emptyIndexes[a][b][0]] = k==0?2:4;
	}
	return;
}

void rotate90(){
	int i,j;
	for (i = 0; i < 2; i++) {
        for (j = i; j < 3 - i; j++) {
 
            // Swap elements of each cycle
            // in clockwise direction
            int temp = (board.board)[i][j];
            (board.board)[i][j] = (board.board)[4 - 1 - j][i];
            (board.board)[4 - 1 - j][i] = (board.board)[4 - 1 - i][4 - 1 - j];
            (board.board)[4 - 1 - i][4 - 1 - j] = (board.board)[j][4 - 1 - i];
            (board.board)[j][4 - 1 - i] = temp;
        }
    }
}