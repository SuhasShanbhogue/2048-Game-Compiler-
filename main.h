#ifndef _MAIN_H
#define _MAIN_H
#include<stdio.h>

extern void printer();
extern void initialize();
extern void add1();
extern void printBoard();
extern void value_in(int row, int col);
extern void assign_value(int val, int row, int col);
extern void move(int insertRandom, int direction, int operation);
extern void moveLeft(int insertRandom, int operation);

struct Board{
	int board[4][4];
};
extern FILE* yyin;

#endif