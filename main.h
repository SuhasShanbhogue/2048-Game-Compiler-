#ifndef _MAIN_H
#define _MAIN_H
#include<stdio.h>


typedef struct Node {
    char var_name[50];
    struct Node* next;
}Node ;

extern void printer();
extern void initialize();
extern void add1();
extern void printBoard();
extern void value_in(int row, int col);
extern void assign_value(int val, int row, int col);
extern void move(int insertRandom, int direction, int operation);
extern void moveLeft(int insertRandom, int operation);
extern void rotateNodes90();
extern void initialize_board_names();
extern void insert_name(Node *head, char new_name[50]);
extern void move_list(Node *head, Node *new_list_head);
extern void make_list_zero(Node *head);
extern void printList(Node* head);
extern void name_variable(char varname[50], int row, int col);

struct Board{
	int board[4][4];
};

struct BoardNames{
    Node* board_names[4][4];
};

extern FILE* yyin;

#endif