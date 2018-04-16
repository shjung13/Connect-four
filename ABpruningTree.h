#pragma once
#ifndef __ABPRUNING_TREE_H__
#define __ABPRUNING_TREE_H__
#include<stdio.h>
#include<stdlib.h>
#define INFINITY 10000000

typedef struct _node {
	int heuristicvalue;
	short depth;
	short place[2];
	struct _node *child[7];
} node;

node *MakeNode(void);

int checkwin(int board[][7]);

void Detection(int turn, int *heuristic, int map[][7]);

int ABpruningTree(node *nd, short depth, int alpha, int beta, int turn, int minmaxmove, int map[][7]);

int ruleby(int board[6][7]);

int firstturn(int board[6][7]);
int check_my_three(int board[6][7]);
int CheckSpecialTwo(int board[6][7], int *pointarr);
int check_your_three(int board[6][7]);

int check_my_three_vertical(int board[6][7]);
int check_my_three_horizontal(int board[6][7]);
int check_my_three_diagonal(int board[6][7]);
int check_your_three_vertical(int board[6][7]);
int check_your_three_horizontal(int board[6][7]);
int check_your_three_diagonal(int board[6][7]);

int check_special_hazard(int board[6][7], int index);
#endif