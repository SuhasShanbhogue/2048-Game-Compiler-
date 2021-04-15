#include "main.h"
#include<stdio.h>
#include<string.h>
#include "ass.tab.h"
#include<stdlib.h>

struct Board board;

// Node *(board_names[4][4]);

struct BoardNames board_names;

void initialize();

void add1();

void printBoard();

void move(int insertRandom, int direction, int operation);

void moveLeft(int insertRandom, int operation);

void insertRandomCell();
	
void rotate90();

// New additions

int checkStateChangeForMove(int direction, int operation);	

struct Board moveState(int insertRandom, int direction, int operation, struct Board temp);

struct Board moveLeftState(int insertRandom, int operation, struct Board temp);

struct Board rotate90State(struct Board temp);

int main() {
	yyin = stdin;
	initialize();
	initialize_board_names();
	moveLeft(1, 1);
	
	printBoard();
	fprintCurrentState();
	do {
		printf("2048-shell> ");
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

void add1(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			board.board[i][j] += 1;
		}
	}
}


void printBoard(){
	for(int i=0; i<4; i++){
		printf("|");
		for(int j=0; j<4; j++){
			printf("%d|", board.board[i][j]);
		}
		printf("\n");
	}
}

void value_in(int row, int col)
{
	printf("Number in %d, %d is: %d\n", row, col, board.board[row-1][col-1]);
	// printf("names of %d, %d are:\n", row, col);
	// printList((board_names.board_names)[row-1][col-1]);
}

void assign_value(int val, int row, int col)
{
	if(row>4 || col>4 || row<1 || col <1)
	{
		printf("There is no tile like that. The tile co-ordinates must be in the range 1,2,3,4.\n");
		fprintf(stderr,"-1\n");
		return;
	}
	if(val==(board.board)[row-1][col-1])
	{
		return;
	}
	(board.board)[row-1][col-1]=val;
	if(val==0)
	{
		make_list_zero((board_names.board_names)[row-1][col-1]);
	}
	fprintCurrentState();

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
		Node* temp_nodes[4]; //for varnames
		int tempIdx=0;
		for(j=0; j<4; j++){
			if((board.board)[i][j] != 0){
				temp[tempIdx] = (board.board)[i][j];
				temp_nodes[tempIdx]=(board_names.board_names)[i][j]; //for varnames
				tempIdx++;
			}
		}
		int temp2[4];
		Node* temp2_nodes[4]; //for varnames
		int temp2Idx = 0;
		int k = 0;
		while(k < tempIdx){
			if(k < tempIdx - 1){
				if(temp[k] == temp[k+1]){
					// temp2[temp2Idx] = temp[k]*2;
					if(operation == 1){	temp2[temp2Idx] = temp[k]*2; 
										temp2_nodes[temp2Idx]=temp_nodes[k]; //for varnames
										move_list(temp2_nodes[temp2Idx], temp_nodes[k+1]); //for varnames
										}
					else if(operation == 2){ temp2[temp2Idx] = -7; 
										temp2_nodes[temp2Idx]=temp_nodes[k]; //for varnames
										make_list_zero(temp2_nodes[temp2Idx]); //for varnames
										}
					else if(operation == 3){ temp2[temp2Idx]  = temp[k]*temp[k];
										temp2_nodes[temp2Idx]=temp_nodes[k]; //for varnames
										move_list(temp2_nodes[temp2Idx], temp_nodes[k+1]); //for varnames
										}
					else				{temp2[temp2Idx] = 1;
										temp2_nodes[temp2Idx]=temp_nodes[k]; //for varnames
										move_list(temp2_nodes[temp2Idx], temp_nodes[k+1]); //for varnames

										}
					k++;	temp2Idx++;
				}
				else{
					temp2[temp2Idx] = temp[k];
					temp2_nodes[temp2Idx]=temp_nodes[k]; //for varnames
					temp2Idx++;
				}
			}
			else{
				temp2[temp2Idx] = temp[k];
				temp2_nodes[temp2Idx]=temp_nodes[k]; //for varnames
				temp2Idx++;
			}
			k++;
		}

		for(k=0; k<4; k++){
			if(k < temp2Idx){
				(board.board)[i][k] = temp2[k];
				(board_names.board_names)[i][k]=temp2_nodes[k];//for varnames
			}
			else{
				(board.board)[i][k] = 0;
				(board_names.board_names)[i][k] = (Node *)malloc(sizeof(Node)); //for varnames
				(board_names.board_names)[i][k]->next=NULL; //for varnames
				char dummy[50]="dummy_head";  //for varnames
				strcpy((board_names.board_names)[i][k]->var_name, dummy);  //for varnames
			}
		}

	}

	if(insertRandom){
		insertRandomCell();
		if(operation == 2){
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					if((board.board)[i][j]==-7){
						(board.board)[i][j]=0;
					}
				}
			}
		}
	}
	return;
}

void insertRandomCell(){
	int X[16], Y[16], ectr=0;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if((board.board)[i][j]==0){
				X[ectr] = i;
				Y[ectr] = j;
				ectr++;
			}
		}
	}

	int a = rand()%(ectr);
	int b = rand()%2;
	if(b == 0){
		(board.board)[X[a]][Y[a]] = 2;
	}
	else{
		(board.board)[X[a]][Y[a]] = 4;	
	}
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
	rotateNodes90();
}


void rotateNodes90(){
	int i,j;
	for (i = 0; i < 2; i++) {
        for (j = i; j < 3 - i; j++) {
 
            // Swap elements of each cycle
            // in clockwise direction
			Node* temp=(board_names.board_names)[i][j];			
            (board_names.board_names)[i][j] = (board_names.board_names)[4 - 1 - j][i];
            (board_names.board_names)[4 - 1 - j][i] = (board_names.board_names)[4 - 1 - i][4 - 1 - j];
            (board_names.board_names)[4 - 1 - i][4 - 1 - j] = (board_names.board_names)[j][4 - 1 - i];
            (board_names.board_names)[j][4 - 1 - i] = temp;
        }
    }
}


void initialize_board_names()
{
	//INITIALIZE 4*4 Array of pointers to Node, with dummy head
	for (int i = 0; i < 4; i++) {
		for(int j=0; j<4; j++)
		{
			(board_names.board_names)[i][j] = (Node *)malloc(sizeof(Node));
			(board_names.board_names)[i][j]->next=NULL;
			char dummy[50]="dummy_head";
			strcpy((board_names.board_names)[i][j]->var_name, dummy);
		}
	} 
}

void insert_name(Node *head, char new_name[50])
{
	//insert variable name given by user at the end of linked list
	Node *newNode;
	newNode = malloc(sizeof(Node));
	strcpy(newNode->var_name, new_name);
	newNode->next = NULL;

	Node *temp = head;
	while(temp->next != NULL){
	temp = temp->next;
	}

	temp->next = newNode;	
}

void move_list(Node *head, Node *new_list_head)
{
	//REMOVE NAMES ATTACHED TO NEW_LIST AND ADD THEM TO ORIGINAL LIST (HEAD)
	Node *temp = head;
	while(temp->next != NULL){
	temp = temp->next;
	}

	temp->next = new_list_head->next;
	new_list_head->next=NULL;
}

void make_list_zero(Node *head)
{
	//DELETE ALL NAMES OF LIST OF A TILE WHEN TILE BECOMES ZERO
	head->next=NULL;
}

void printList(Node* head)
{
	//PRINT LINKED LIST
	Node* node=head->next;
	if(node==NULL)
	{
		return;
	}
	while (node != NULL) {
		fprintf(stderr,"%s", node->var_name);
		node = node->next;
		if(node!=NULL)
		{
			fprintf(stderr, ",");
		}
	}
	fprintf(stderr," ");
}

void name_variable(char varname[50], int row, int col) //modified this for variable issue
{
	//FOR VAR <<varname>> IS <<x>>,<<y>>.
	if((board.board)[row-1][col-1]==0)
	{
		printf("Sorry, cannot assign a variable name to a zero tile!\n");
		fprintf(stderr,"-1\n");
		return;
	}
	for(int i=0; i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(findInList(varname , (board_names.board_names)[i][j])==1)
			{
				if((i==row-1)&&(j==col-1))
				{
					return;
				}
				printf("Sorry, variable name %s already exists. Please try another name.\n", varname);
				fprintf(stderr,"-1\n");
				return;

			}
		}
	}
	insert_name((board_names.board_names)[row-1][col-1], varname);
	fprintCurrentState();

}

int findInList(char myvar[], Node* head) //newly added for variable issue
{
	Node* temp=head;
	while(temp!=NULL)
	{
		if(strcmp(temp->var_name , myvar)==0)
		{
			return 1;
		}
		temp=temp->next;
	}
	return 0;
}

void fprintCurrentState()
{
	//PRINTS BOARD
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			fprintf(stderr, "%d ",(board.board)[i][j]);
		}
	}

	//PRINTS VARIABLE NAMES
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(((board_names.board_names)[i][j])->next!=NULL)
			{
				fprintf(stderr, "%d,%d", i+1,j+1);
			}
			printList((board_names.board_names)[i][j]);
		}
	}
	fprintf(stderr, "\n");
	
}
// New additions

int checkStateChangeForMove(int direction, int operation){
	struct Board temp;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			(temp.board)[i][j] = (board.board)[i][j];
		}
	}
	struct Board temp1 = moveState(0, direction, operation, temp);

	int changed = 0;

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if((board.board)[i][j] != (temp1.board)[i][j]){
				changed = 1;
			}
		}
	}

	return changed;	// Returns 1 if the state was changed due to the move
}

struct Board moveState(int insertRandom, int direction, int operation, struct Board temp){
	if(direction == 5){
		temp = moveLeftState(insertRandom, operation, temp);
	}
	else if(direction == 6){
		temp = rotate90State(temp);
		temp = rotate90State(temp);
		temp = moveLeftState(insertRandom, operation, temp);
		temp = rotate90State(temp);
		temp = rotate90State(temp);
	}
	else if(direction == 7){
		temp = rotate90State(temp);
		temp = rotate90State(temp);
		temp = rotate90State(temp);
		temp = moveLeftState(insertRandom, operation, temp);
		temp = rotate90State(temp);
	}
	else if(direction == 8){
		temp = rotate90State(temp);
		temp = moveLeftState(insertRandom, operation, temp);
		temp = rotate90State(temp);
		temp = rotate90State(temp);
		temp = rotate90State(temp);
	}
	return temp;
}

struct Board moveLeftState(int insertRandom, int operation, struct Board tempboard){
	int i,j;
	for(i=0; i<4; i++){
		int temp[4];
		int tempIdx=0;
		for(j=0; j<4; j++){
			if((tempboard.board)[i][j] != 0){
				temp[tempIdx] = (tempboard.board)[i][j];
				tempIdx++;
			}
		}
		int temp2[4];
		int temp2Idx = 0;
		int k = 0;
		while(k < tempIdx){
			if(k < tempIdx - 1){
				if(temp[k] == temp[k+1]){
					if(operation == 1)		{	temp2[temp2Idx] = temp[k]*2; 
										}
					else if(operation == 2)	{ 	temp2[temp2Idx] = -7; 
										}
					else if(operation == 3)	{ 	temp2[temp2Idx]  = temp[k]*temp[k];
										}
					else					{	temp2[temp2Idx] = 1;
										}
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
				(tempboard.board)[i][k] = temp2[k];
			}
			else{
				(tempboard.board)[i][k] = 0;
			}
		}

	}
	return tempboard;
}

struct Board rotate90State(struct Board tempboard){
	int i,j;
	for (i = 0; i < 2; i++) {
        for (j = i; j < 3 - i; j++) {
 
            // Swap elements of each cycle
            // in clockwise direction
            int temp = (tempboard.board)[i][j];
            (tempboard.board)[i][j] = (tempboard.board)[4 - 1 - j][i];
            (tempboard.board)[4 - 1 - j][i] = (tempboard.board)[4 - 1 - i][4 - 1 - j];
            (tempboard.board)[4 - 1 - i][4 - 1 - j] = (tempboard.board)[j][4 - 1 - i];
            (tempboard.board)[j][4 - 1 - i] = temp;
        }
    }
    return tempboard;
}
