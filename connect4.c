#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"ABpruningTree.h"

#define EMPTY 0
#define BLACK 11
#define WHITE 100
#define DEPTH 11

int map[6][7] = { 0, };
int whosturn = 100;
int rulebytoggle = 0;
void manu();
void drowmap();					// ¸Ê ±×·ÁÁÜ
void game();

void drowmap()
{
	int i, j;
	system("cls");
	for (i = 0; i < 13; i++) {
		if (i == 0) {
			printf("¦®¦¬");
			for (j = 0; j < 6; j++) {
				printf("¦³¦¬");
			}
			printf("¦¯\n");
		}
		else if (i == 12) {
			printf("¦±¦¬");
			for (j = 0; j < 6; j++) {
				printf("¦µ¦¬");
			}
			printf("¦°\n");
		}
		else if (i % 2 == 1) {
			for (j = 0; j < 7; j++) {
				switch (map[5 - (i / 2)][j]) {
				case EMPTY:
					printf("¦­  ");
					break;
				case BLACK:
					printf("¦­¡Ü");
					break;
				case WHITE:
					printf("¦­¡Û");
					break;
				default:
					printf("²ô¾Ó");
				}

			}
			printf("¦­\n");
		}
		else {
			printf("¦²¦¬");
			for (j = 0; j < 6; j++) {
				printf("¦¶¦¬");
			}
			printf("¦´\n");
		}

	}
}

void manu() {
	printf("------------------------------------\n\n");
	printf("--------                   ---------\n");
	printf("--------press 0 to player 1---------\n");
	printf("--------press 1 to player 2---------\n");
	printf("--------                   ---------\n");
	printf("------------------------------------\n");
	scanf_s("%d", &whosturn);
}

void game() {
	int cord[2];						//¾îµð´Ù µÎ°ÔµÉ ÁÂÇ¥
	int backup[2];
	int heurivalue = 0;
	int c1, c2;
	cord[0] = cord[1] = 0;
	backup[0] = backup[1] = 0;
	while (1) {
		if (whosturn == 0) {
			drowmap();
			printf("¾îµðµÑ±î?\n");
			scanf_s("%d, %d", &c1, &c2);
			if (c1 == 100) {
				map[cord[0]][cord[1]] = EMPTY;
				map[backup[0]][backup[1]] = EMPTY;
			}
			else {
				map[c1 - 1][c2 - 1] = BLACK;
				backup[0] = c1 - 1;
				backup[1] = c2 - 1;
				whosturn = !whosturn;
			}

		}
		else {
			drowmap();
			printf("ruleby??\n");
			scanf_s("%d", &rulebytoggle);
			if (rulebytoggle) {
				cord[1] = ruleby(map);
				for (int j = 0; j < 6; j++)
					if (map[j][cord[1]] == 0) {
						cord[0] = j; break;
					}
			}
			else {
				node *root = MakeNode();
				heurivalue = ABpruningTree(root, DEPTH, -INFINITY, INFINITY, whosturn, 1, map);
				for (int i = 0; i < 7; i++) {
					if (root->child[i] == NULL)
						break;
					printf("child[%d] heuristic : %d\n", i, root->child[i]->heuristicvalue);
					if (heurivalue == (root->child[i]->heuristicvalue)) {
						printf("myheuri : %d\n", heurivalue);
						cord[0] = root->child[i]->place[0];
						cord[1] = root->child[i]->place[1];
						break;
					}
				}
				for (int i = 0; i < 7; i++) {
					if (root->child[i] == NULL)
						break;
					free(root->child[i]);
				}
				free(root);
			}

			map[cord[0]][cord[1]] = WHITE;
			whosturn = !whosturn;
		}

	}
}

int main()
{
	
	manu();
	if (whosturn != 100) {
		game();
	}
	system("pause");
	return 0;
}