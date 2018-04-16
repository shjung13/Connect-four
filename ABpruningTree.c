#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"ABpruningTree.h"
#define EMPTY 0
#define BLACK 11
#define WHITE 100
#define DEPTH 11
/*------------------------------------------------------------------------------------------------------------------------
-- Tree 생성(돌 위치 노드 별 저장) >> 탐색하며 Heuristic 계산(minmax 특성상 말단 노드의 경우만 Heuristic계산) >> 위치 반환
-- turn == 0 --> BLACK
-- turn == 1 --> WHITE
-- GenerateTree 로 먼저 Tree 생성 후 Search함
-- Tree 생성 후에 free 해줌
-------------------------------------------------------------------------------------------------------------------------*/

/**************************************************************************
** map의 위치에서 WinningLine 계산
** 돌 1개 --> 0 // 돌 2개 --> 1 // 돌 3개 --> 2 // 돌 4개 --> 3 에 저장
**************************************************************************/
void Detection(int turn, int *heuristic, int map[][7]) {			//x,y 현재 조사하는 노드 위치
	int count = 0;
	int num = 0;
	int i, j;
	int mystone = 0;
	int oppstone = 0;
	int x, y;
	for (i = 0; i < 4; i++)
		heuristic[i] = 0;
	if (turn == 0) {									// turn == 0 시 까만돌(==11)
		mystone = BLACK;
		oppstone = WHITE;
	}
	else {												// turn == 1 시 하얀돌(==100)
		mystone = WHITE;
		oppstone = BLACK;
	}
	for (x = 0; x < 6; x++) {
		y = 3;
		for (j = 0; j < 7; j++) {					// 가로 검사 --> 중간에 겹칠경우(O_OO__X) 이런 경우 winning line 두개임
			if (count > 3) {
				count = 0;
			}

			if (map[x][j] == EMPTY) {
				if (count == 3) {
					if (((j - 3) <= y) && (j >= y) && (num > 0)) {
						heuristic[num - 1] += 1;
						j -= 2;
						num = 0;
					}
					else {
						j -= 2;
						num = 0;
					}
					count++;
				}
				else
					count++;
			}
			else if (map[x][j] == mystone) {
				num++;
				if (count == 3) {
					if (((j - 3) <= y) && (j >= y)) {
						heuristic[num - 1] += 1;
						j -= 2;
						num = 0;
					}
					else {
						num = 0;
						j -= 2;
					}
					count++;
				}
				else
					count++;
			}
			else if (map[x][j] == oppstone) {
				num = 0; count = 0;
			}
		}
	}
	num = 0;
	count = 0;

	for (y = 0; y < 7; y++) {
		x = 3;
		for (i = 0; i < 6; i++) {						// 세로 검사 --> 중간에 겹칠경우(O_OO__X) 이런 경우 winning line 두개임
			if (count > 3) {
				count = 0;
			}
			if (map[i][y] == EMPTY) {
				if (count == 3) {
					if ((i - 3 <= x) && (i >= x) && (num > 0)) {
						heuristic[num - 1] += 1;
						i -= 2;
						num = 0;
					}
					else {
						num = 0; i -= 2;
					}
					count++;
				}
				else
					count++;
			}
			else if (map[i][y] == mystone) {
				num++;
				if (count == 3) {
					if ((i - 3 <= x) && (i >= x)) {
						heuristic[num - 1] += 1;
						i -= 2;
						num = 0;
					}
					else {
						num = 0; i -= 2;
					}count++;
				}
				else
					count++;
			}
			else if (map[i][y] == oppstone) {
				num = 0; count = 0;
			}
		}
	}
	num = 0, count = 0;
	for (y = 0; y < 7; y++) {
		x = 3;
		if ((x >= y) && (x - y < 3)) {						// 대각검사(왼아래-> 오른위) --- 1번(왼쪽 위의 경우)
			for (i = (x - y), j = 0; i < 6; i++, j++) {
				if (count > 3) {
					count = 0;
				}

				if (map[i][j] == EMPTY) {
					if (count == 3) {
						if (((j - 3) <= y) && (j >= y) && (num > 0)) {
							heuristic[num - 1] += 1;
							j -= 2;
							i -= 2;
							num = 0;
						}
						else {
							j -= 2;
							i -= 2;
							num = 0;
						}
						count++;
					}
					else
						count++;
				}
				else if (map[i][j] == mystone) {
					num++;
					if (count == 3) {
						if (((j - 3) <= y) && (j >= y)) {
							heuristic[num - 1] += 1;
							j -= 2;
							i -= 2;
							num = 0;
						}
						else {
							num = 0;
							j -= 2;
							i -= 2;
						}
						count++;
					}
					else
						count++;
				}
				else if (map[i][j] == oppstone) {
					num = 0; count = 0;
				}
			}
		}
		else if ((x < y) && (x - y < 4)) {							// 대각검사(왼아래-> 오른위) --- 2번(오른 아래의 경우)
			for (i = 0, j = (y - x); j < 7; i++, j++) {
				if (count > 3) {
					count = 0;
				}

				if (map[i][j] == EMPTY) {
					if (count == 3) {
						if (((j - 3) <= y) && (j >= y) && (num > 0)) {
							heuristic[num - 1] += 1;
							j -= 2;
							i -= 2;
							num = 0;
						}
						else {
							j -= 2;
							i -= 2;
							num = 0;
						}
						count++;
					}
					else
						count++;
				}
				else if (map[i][j] == mystone) {
					num++;
					if (count == 3) {
						if (((j - 3) <= y) && (j >= y)) {
							heuristic[num - 1] += 1;
							j -= 2;
							i -= 2;
							num = 0;
						}
						else {
							num = 0;
							j -= 2;
							i -= 2;
						}
						count++;
					}
					else
						count++;
				}
				else if (map[i][j] == oppstone) {
					num = 0; count = 0;
				}
			}
		}
		num = 0; count = 0;
		if ((x + y > 5) && (x + y <= 8)) {								// 대각검사(왼위-->오른아래) --- 1번(오른 위의 경우)	
			for (i = 5, j = (x + y - 5); j < 7; i--, j++) {
				if (count > 3) {
					count = 0;
				}

				if (map[i][j] == EMPTY) {
					if (count == 3) {
						if (((j - 3) <= y) && (j >= y) && (num > 0)) {
							heuristic[num - 1] += 1;
							j -= 2;
							i += 2;
							num = 0;
						}
						else {
							j -= 2;
							i += 2;
							num = 0;
						}
						count++;
					}
					else
						count++;
				}
				else if (map[i][j] == mystone) {
					num++;
					if (count == 3) {
						if (((j - 3) <= y) && (j >= y)) {
							heuristic[num - 1] += 1;
							j -= 2;
							i += 2;
							num = 0;
						}
						else {
							num = 0;
							j -= 2;
							i += 2;
						}
						count++;
					}
					else
						count++;
				}
				else if (map[i][j] == oppstone) {
					num = 0; count = 0;
				}
			}
		}
		else if ((x + y <= 5) && (x + y >= 3)) {									// 대각검사(왼위-->오른아래) --- 2번(왼아래의 경우)
			for (i = x + y, j = 0; i >= 0; i--, j++) {
				if (count > 3) {
					count = 0;
				}

				if (map[i][j] == EMPTY) {
					if (count == 3) {
						if (((j - 3) <= y) && (j >= y) && (num > 0)) {
							heuristic[num - 1] += 1;
							j -= 2;
							i += 2;
							num = 0;
						}
						else {
							j -= 2;
							i += 2;
							num = 0;
						}
						count++;
					}
					else
						count++;
				}
				else if (map[i][j] == mystone) {
					num++;
					if (count == 3) {
						if (((j - 3) <= y) && (j >= y)) {
							heuristic[num - 1] += 1;
							j -= 2;
							i += 2;
							num = 0;
						}
						else {
							num = 0;
							j -= 2;
							i += 2;
						}
						count++;
					}
					else
						count++;
				}
				else if (map[i][j] == oppstone) {
					num = 0; count = 0;
				}

			}
		}
	}
	num = 0; count = 0;
}


/**************************************************************************
** 승패를 찾는 함수
** return == 1 : 내가 이김 // return == 2 : 내가 짐
**************************************************************************/
int checkwin(int board[][7])
{

	int i, j;
	//checks horizontal win
	for (i = 0; i < 6; i++)
		for (j = 0; j < 4; j++) {
			if (board[i][j] + board[i][j + 1] + board[i][j + 2] + board[i][j + 3] == 400)
				return 1;
			else if (board[i][j] + board[i][j + 1] + board[i][j + 2] + board[i][j + 3] == 44)
				return 2;
		}

	//checks vertical win
	for (i = 0; i<7; i++)
		for (j = 0; j < 3; j++) {
			if (board[j][i] + board[j + 1][i] + board[j + 2][i] + board[j + 3][i] == 400)
				return 1;
			else if (board[j][i] + board[j + 1][i] + board[j + 2][i] + board[j + 3][i] == 44)
				return 2;
		}
	//return 2;

	//checks right diagonal win
	for (i = 0; i<3; i++)
		for (j = 0; j < 4; j++) {
			if (board[i][j] + board[i + 1][j + 1] + board[i + 2][j + 2] + board[i + 3][j + 3] == 400)
				return 1;
			else if (board[i][j] + board[i + 1][j + 1] + board[i + 2][j + 2] + board[i + 3][j + 3] == 44)
				return 2;
		}
	//checks left diagonal win
	for (i = 5; i>2; i--)
		for (j = 0; j < 4; j++) {
			if (board[i][j] + board[i - 1][j + 1] + board[i - 2][j + 2] + board[i - 3][j + 3] == 400)
				return 1;
			else if (board[i][j] + board[i - 1][j + 1] + board[i - 2][j + 2] + board[i - 3][j + 3] == 44)
				return 2;
		}
	return 0;
}

/**************************************************************************
** 노드 생성
** Place --> 본인 노드에서 두어야 하는 위치(Board 에 적용 후 인자로 전송)
** 최대 7개의 자식 노드 생성 가능
**************************************************************************/
node *MakeNode(void) {
	node *nd = (node*)malloc(sizeof(node));
	nd->child[0] = NULL;
	return nd;
}
/**************************************************************************
** 트리를 만들면서 ABpruning 서치 수행
** 탐색이 된 노드에 대해서 바로 free 시켜줌
**************************************************************************/
int ABpruningTree(node *nd, short depth, int alpha, int beta, int turn, int minmaxmove, int map[][7]) {
	int board[6][7] = { 0, };
	int count = 0;
	int childnum = 0;
	int point[7] = { 0, };
	int i, j;
	int bestvalue;
	int childreturn;
	int mydoll, oppdoll;
	int heurivalue = 0;
	int heuri[4] = { 0, };
	int oppheuri[4] = { 0, };
	node *childnode[7];
	nd->depth = depth;

	for (i = 0; i < 7; i++) {
		for (j = 0; j < 6; j++) {
			board[j][i] = map[j][i];
			if (board[j][i] == EMPTY) {
				point[i] = j; break;
			}
			else if (j == 5)
				point[i] = 100;
		}
	}

	if (i = checkwin(board)) {
		if (i == 2)
			heurivalue = -INFINITY/2 - (nd->depth);
		else if (i == 1)
			heurivalue = INFINITY/2 + (nd->depth);
		nd->heuristicvalue = heurivalue;
		return heurivalue;
	}

	if (depth == 0) {
		Detection(1, heuri, board);
		Detection(0, oppheuri, board);
		heurivalue = heuri[0] + heuri[1] * 5 + heuri[2] * 10 + heuri[3] * 100 - (oppheuri[0] + oppheuri[1] * 3 + oppheuri[2] * 7 + oppheuri[3] * 100);
		return heurivalue;
	}

	if (turn == 0) {
		mydoll = BLACK;
		oppdoll = WHITE;
	}
	else {
		mydoll = WHITE;
		oppdoll = BLACK;
	}
	for (i = 0; i < 7; i++) {
		if (point[i] != 100) 
			childnum++;
	}
	for (i = 0; i < childnum; i++)
		childnode[i] = MakeNode();

	for (i = 0; i < 7; i++) {
		if (point[i] != 100) {
			nd->child[count] = childnode[count];
			childnode[count]->place[0] = point[i];
			childnode[count]->place[1] = i;
			if (count != 6)
				nd->child[count + 1] = NULL;
			count++;
		}
	}

	if (minmaxmove) {
		bestvalue = alpha;
		for (i = 0; i < 7; i++) {
			if (nd->child[i] == NULL)
				break;
			board[nd->child[i]->place[0]][nd->child[i]->place[1]] = mydoll;
			childreturn = ABpruningTree(nd->child[i], depth - 1, bestvalue, beta, !turn, !minmaxmove, board);
			board[nd->child[i]->place[0]][nd->child[i]->place[1]] = EMPTY;
			bestvalue = max(bestvalue, childreturn);
			if (beta <= bestvalue)
				break;
		}
		nd->heuristicvalue = bestvalue;
		if (depth!=DEPTH) {
			for (i = 0; i < 7; i++) {			//자식노드를 free 시켜줌
				if (nd->child[i] == NULL)
					break;
				free(nd->child[i]);
				nd->child[i] = NULL;
			}
		}
		return bestvalue;
	}
	else {
		bestvalue = beta;
		for (i = 0; i < 7; i++) {
			if (nd->child[i] == NULL)
				break;
			board[nd->child[i]->place[0]][nd->child[i]->place[1]] = mydoll;
			childreturn = ABpruningTree(nd->child[i], depth - 1, alpha, bestvalue, !turn, !minmaxmove, board);
			board[nd->child[i]->place[0]][nd->child[i]->place[1]] = EMPTY;
			bestvalue = min(bestvalue, childreturn);
			if (bestvalue<=alpha)
				break;
		}
		nd->heuristicvalue = bestvalue;
		if (depth != DEPTH) {				// 자식노드를 free 시켜줌
			for (i = 0; i < 7; i++) {
				if (nd->child[i] == NULL)
					break;
				free(nd->child[i]);
				nd->child[i] = NULL;
			}
		}
		return bestvalue;
	}

}

/**************************************************************************
** rule기반 함수
** 크리티컬한 경우를 제외하면 가운데부터 우선순위를 두고 구현
**************************************************************************/
int ruleby(int board[6][7])
{
	int doll = 0;
	int i = 0;
	int pointarr[7] = { 0, };
	if (firstturn(board) != -1)
		return firstturn(board);

	if (check_my_three(board) != -1)
		return check_my_three(board);

	if (check_your_three(board) != -1)
		return check_your_three(board);

	int check_nottodo[7] = { 0, };
	CheckSpecialTwo(board, pointarr);
	int special = 0;

	for (i = 0; i < 7; i++) {
		check_nottodo[i] = 1;
		special = check_special_hazard(board, i);
		if ((pointarr[i] == 1) && (special == 0)) {
			return i;
		}

		if (special == 1)            //check 그 내가두고 위에두면 지는거
			check_nottodo[i] = 0;
	}
	int sum = 0;
	for (i = 0; i < 7; i++) {
		sum += check_nottodo[i];
	}

	if (check_nottodo[3] == 1 && board[5][3] == 0)
		return 3;
	if (check_nottodo[4] == 1 && board[5][4] == 0)
		return 4;
	if (check_nottodo[2] == 1 && board[5][2] == 0)
		return 2;
	if (check_nottodo[1] == 1 && board[5][1] == 0)
		return 1;
	if (check_nottodo[5] == 1 && board[5][5] == 0)
		return 5;
	if (check_nottodo[0] == 1 && board[5][0] == 0)
		return 0;
	if (check_nottodo[6] == 1 && board[5][6] == 0)
		return 6;

	return doll;
}

int firstturn(int board[6][7])      //첫번째 턴에서 어케 둘건지
{
	int count = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (board[i][j] != 0)
			{
				count++;
			}
		}
	}

	if ((count == 0)&&(count==1)){      //상대가 안뒀을때 -> 우리무조건 가운데
		return 3;
	}
	else               // 첫번째턴 아닐때 이건 쓸모없음!
		return -1;

}

int check_my_three(int board[6][7])   //내꺼가 3개
{
	if (check_my_three_vertical(board) != -1)
		return check_my_three_vertical(board);
	if (check_my_three_horizontal(board) != -1)
		return check_my_three_horizontal(board);
	if (check_my_three_diagonal(board) != -1)
		return check_my_three_diagonal(board);

	return -1;
}


int check_belowFilled(int board[6][7], int garo, int sero)
{
	if (sero == 0)
		return 1;
	else
	{
		if (board[sero - 1][garo] != EMPTY)
			return 1;
		else
			return 0;
	}
}

int check_my_three_vertical(int board[6][7])
{
	for (int garo = 0; garo < 7; garo++)
	{
		for (int sero = 0; sero < 3; sero++)
		{
			if (board[sero + 3][garo] == 0 && board[sero][garo] == board[sero + 1][garo] && board[sero][garo] == board[sero + 2][garo] && board[sero][garo] == WHITE)
				return garo;
		}
	}
	return -1;
}

int check_my_three_horizontal(int board[6][7])
{
	for (int garo = 0; garo < 4; garo++)
	{
		for (int sero = 0; sero < 6; sero++)
		{
			if (board[sero][garo + 3] == 0 && check_belowFilled(board, garo + 3, sero) == 1 && board[sero][garo] == board[sero][garo + 1] && board[sero][garo] == board[sero][garo + 2] && board[sero][garo] == WHITE)
				return garo + 3;   //// ㅇㅇㅇ-
			if (board[sero][garo] == 0 && check_belowFilled(board, garo, sero) == 1 && board[sero][garo + 1] == board[sero][garo + 2] && board[sero][garo + 1] == board[sero][garo + 3] && board[sero][garo + 1] == WHITE)
				return garo;   //// -ㅇㅇㅇ
			if (board[sero][garo + 2] == 0 && check_belowFilled(board, garo + 2, sero) == 1 && board[sero][garo] == board[sero][garo + 1] && board[sero][garo] == board[sero][garo + 3] && board[sero][garo] == WHITE)
				return garo + 2;   //// ㅇㅇ-ㅇ
			if (board[sero][garo + 1] == 0 && check_belowFilled(board, garo + 1, sero) == 1 && board[sero][garo] == board[sero][garo + 2] && board[sero][garo] == board[sero][garo + 3] && board[sero][garo] == WHITE)
				return garo + 1;   //// ㅇ-ㅇㅇ
		}
	}
	return -1;

}

int check_my_three_diagonal(int board[6][7])
{
	for (int garo = 0; garo < 4; garo++)
	{
		for (int sero = 0; sero < 3; sero++)
		{
			if (board[sero][garo] == 0 && check_belowFilled(board, garo, sero) == 1 && board[sero + 1][garo + 1] == board[sero + 2][garo + 2] && board[sero + 1][garo + 1] == board[sero + 3][garo + 3] && board[sero + 1][garo + 1] == WHITE)
				return garo;   //// - ㅇ ㅇ ㅇ
			if (board[sero + 1][garo + 1] == 0 && check_belowFilled(board, garo + 1, sero + 1) == 1 && board[sero][garo] == board[sero + 2][garo + 2] && board[sero][garo] == board[sero + 3][garo + 3] && board[sero][garo] == WHITE)
				return garo + 1;   //// ㅇ - ㅇ ㅇ
			if (board[sero + 2][garo + 2] == 0 && check_belowFilled(board, garo + 2, sero + 2) == 1 && board[sero][garo] == board[sero + 1][garo + 1] && board[sero][garo] == board[sero + 3][garo + 3] && board[sero][garo] == WHITE)
				return garo + 2;   //// ㅇ ㅇ - ㅇ
			if (board[sero + 3][garo + 3] == 0 && check_belowFilled(board, garo + 3, sero + 3) == 1 && board[sero][garo] == board[sero + 1][garo + 1] && board[sero][garo] == board[sero + 2][garo + 2] && board[sero][garo] == WHITE)
				return garo + 3;   //// ㅇ ㅇ ㅇ -
		}
	}      ////오른쪽 위로솟는 대각선

	for (int garo = 3; garo < 7; garo++)		// 가로 3부터
	{
		for (int sero = 0; sero < 3; sero++)
		{
			if (board[sero][garo] == 0 && check_belowFilled(board, garo, sero) == 1 && board[sero + 1][garo - 1] == board[sero + 2][garo - 2] && board[sero + 1][garo - 1] == board[sero + 3][garo - 3] && board[sero + 1][garo - 1] == WHITE)
				return garo;   //// - ㅇ ㅇ ㅇ
			if (board[sero + 1][garo - 1] == 0 && check_belowFilled(board, garo - 1, sero + 1) == 1 && board[sero][garo] == board[sero + 2][garo - 2] && board[sero][garo] == board[sero + 3][garo - 3] && board[sero][garo] == WHITE)
				return garo - 1;   //// ㅇ - ㅇ ㅇ
			if (board[sero + 2][garo - 2] == 0 && check_belowFilled(board, garo - 2, sero + 2) == 1 && board[sero][garo] == board[sero + 1][garo - 1] && board[sero][garo] == board[sero + 3][garo - 3] && board[sero][garo] == WHITE)
				return garo - 2;   //// ㅇ ㅇ - ㅇ
			if (board[sero + 3][garo - 3] == 0 && check_belowFilled(board, garo - 3, sero + 3) == 1 && board[sero][garo] == board[sero + 1][garo - 1] && board[sero][garo] == board[sero + 2][garo - 2] && board[sero][garo] == WHITE)
				return garo - 3;   //// ㅇ ㅇ ㅇ - 
		}
	}      ////왼쪽 위로솟는 대각선
	return -1;
}

int CheckSpecialTwo(int board[6][7], int *pointarr) {

	int i, j;
	int check = 0;
	for (i = 0; i < 7; i++) {
		pointarr[i] = 0;
	}
	//checks horizontal win
	for (i = 0; i < 6; i++)
		for (j = 0; j < 4; j++) {
			if ((i == 0) || ((board[i - 1][j] != EMPTY) && (board[i - 1][j + 1] != EMPTY) && (board[i - 1][j + 2] != EMPTY) && (board[i - 1][j + 3] != EMPTY))) {
				//_OO_
				if ((board[i][j] == EMPTY) && (board[i][j + 1] == BLACK) && (board[i][j + 2] == BLACK) && (board[i][j + 3] == EMPTY)) {
					check = 1;
					pointarr[j] = 1;
					pointarr[j + 3] = 1;
				}
				//O_O_
				else if ((board[i][j] == BLACK) && (board[i][j + 1] == EMPTY) && (board[i][j + 2] == BLACK) && (board[i][j + 3] == EMPTY)) {
					check = 1;
					pointarr[j + 1] = 1;
					pointarr[j + 3] = 1;
				}
				//_O_O
				else if ((board[i][j] == EMPTY) && (board[i][j + 1] == BLACK) && (board[i][j + 2] == EMPTY) && (board[i][j + 3] == BLACK)) {
					check = 1;
					pointarr[j] = 1;
					pointarr[j + 2] = 1;
				}
				//O__O
				else if ((board[i][j] == BLACK) && (board[i][j + 1] == EMPTY) && (board[i][j + 2] == EMPTY) && (board[i][j + 3] == BLACK)) {
					check = 1;
					pointarr[j + 1] = 1;
					pointarr[j + 2] = 1;
				}
			}
		}
			//checks right diagonal win
			for (i = 0; i < 3; i++)
				for (j = 0; j < 4; j++)
					if (((i == 0) && (board[i][j + 1] != EMPTY) && (board[i + 1][j + 2] != EMPTY) && (board[i + 2][j + 3] != EMPTY)) || ((i != 0) && (board[i - 1][j] != EMPTY) && (board[i][j + 1] != EMPTY) && (board[i + 1][j + 2] != EMPTY) && (board[i + 2][j + 3] != EMPTY))) {
						//_OO_
						if ((board[i][j] == EMPTY) && (board[i + 1][j + 1] == BLACK) && (board[i + 2][j + 2] == BLACK) && (board[i + 3][j + 3] == EMPTY)) {
							check = 1;
							pointarr[j] = 1;
							pointarr[j + 3] = 1;
						}
						//O_O_
						else if ((board[i][j] == BLACK) && (board[i + 1][j + 1] == EMPTY) && (board[i + 2][j + 2] == BLACK) && (board[i + 3][j + 3] == EMPTY)) {
							check = 1;
							pointarr[j + 1] = 1;
							pointarr[j + 3] = 1;
						}
						//_O_O
						else if ((board[i][j] == EMPTY) && (board[i + 1][j + 1] == BLACK) && (board[i + 2][j + 2] == EMPTY) && (board[i + 3][j + 3] == BLACK)) {
							check = 1;
							pointarr[j] = 1;
							pointarr[j + 2] = 1;
						}
						//O__O
						else if ((board[i][j] == BLACK) && (board[i + 1][j + 1] == EMPTY) && (board[i + 2][j + 2] == EMPTY) && (board[i + 3][j + 3] == BLACK)) {
							check = 1;
							pointarr[j + 1] = 1;
							pointarr[j + 2] = 1;
						}
					}

			//checks left diagonal win
			for (i = 5; i > 2; i--)
				for (j = 0; j < 4; j++)
					if (((i == 3) && (board[i - 1][j] != EMPTY) && (board[i - 2][j + 1] != EMPTY) && (board[i - 3][j + 2] != EMPTY)) || ((i != 3) && (board[i - 1][j] != EMPTY) && (board[i - 2][j + 1] != EMPTY) && (board[i - 3][j + 2] != EMPTY) && (board[i - 4][j + 3] != EMPTY))) {
						//_OO_
						if ((board[i][j] == EMPTY) && (board[i - 1][j + 1] == BLACK) && (board[i - 2][j + 2] == BLACK) && (board[i - 3][j + 3] == EMPTY)) {
							check = 1;
							pointarr[j] = 1;
							pointarr[j + 3] = 1;
						}
						//O_O_
						else if ((board[i][j] == BLACK) && (board[i - 1][j + 1] == EMPTY) && (board[i - 2][j + 2] == BLACK) && (board[i - 3][j + 3] == EMPTY)) {
							check = 1;
							pointarr[j + 1] = 1;
							pointarr[j + 3] = 1;
						}
						//_O_O
						else if ((board[i][j] == EMPTY) && (board[i - 1][j + 1] == BLACK) && (board[i - 2][j + 2] == EMPTY) && (board[i - 3][j + 3] == BLACK)) {
							check = 1;
							pointarr[j] = 1;
							pointarr[j + 2] = 1;
						}
						//O__O
						else if ((board[i][j] == BLACK) && (board[i - 1][j + 1] == EMPTY) && (board[i - 2][j + 2] == EMPTY) && (board[i - 3][j + 3] == BLACK)) {
							check = 1;
							pointarr[j + 1] = 1;
							pointarr[j + 2] = 1;
						}
					}
	if (check == 0)
		return -1;
	else
		return 1;
}

int check_your_three(int board[6][7])   //내꺼가 3개
{
	if (check_your_three_vertical(board) != -1)
		return check_your_three_vertical(board);
	if (check_your_three_horizontal(board) != -1)
		return check_your_three_horizontal(board);
	if (check_your_three_diagonal(board) != -1)
		return check_your_three_diagonal(board);

	return -1;
}

int check_your_three_vertical(int board[6][7])
{
	for (int garo = 0; garo < 7; garo++)
	{
		for (int sero = 0; sero < 3; sero++)
		{
			if (board[sero + 3][garo] == 0 && board[sero][garo] == board[sero + 1][garo] && board[sero][garo] == board[sero + 2][garo] && board[sero][garo] == BLACK)
				return garo;
		}
	}
	return -1;
}

int check_your_three_horizontal(int board[6][7])
{
	for (int garo = 0; garo < 4; garo++)
	{
		for (int sero = 0; sero < 6; sero++)
		{
			if (board[sero][garo + 3] == 0 && check_belowFilled(board, garo + 3, sero) == 1 && board[sero][garo] == board[sero][garo + 1] && board[sero][garo] == board[sero][garo + 2] && board[sero][garo] == BLACK)
				return garo + 3;   //// X X X -
			if (board[sero][garo] == 0 && check_belowFilled(board, garo, sero) == 1 && board[sero][garo + 1] == board[sero][garo + 2] && board[sero][garo + 1] == board[sero][garo + 3] && board[sero][garo + 1] == BLACK)
				return garo;   //// - X X X
			if (board[sero][garo + 2] == 0 && check_belowFilled(board, garo + 2, sero) == 1 && board[sero][garo] == board[sero][garo + 1] && board[sero][garo] == board[sero][garo + 3] && board[sero][garo] == BLACK)
				return garo + 2;   //// X X - X
			if (board[sero][garo + 1] == 0 && check_belowFilled(board, garo + 1, sero) == 1 && board[sero][garo] == board[sero][garo + 2] && board[sero][garo] == board[sero][garo + 3] && board[sero][garo] == BLACK)
				return garo + 1;   //// X - X X
		}
	}
	return -1;

}

int check_your_three_diagonal(int board[6][7])
{
	//오른쪽 위로솟는 대각선
	for (int garo = 0; garo < 4; garo++)
	{
		for (int sero = 0; sero < 3; sero++)
		{
			if (board[sero][garo] == 0 && check_belowFilled(board, garo, sero) == 1 && board[sero + 1][garo + 1] == board[sero + 2][garo + 2] && board[sero + 1][garo + 1] == board[sero + 3][garo + 3] && board[sero + 1][garo + 1] == BLACK)
				return garo;   //// - X X X
			if (board[sero + 1][garo + 1] == 0 && check_belowFilled(board, garo + 1, sero + 1) == 1 && board[sero][garo] == board[sero + 2][garo + 2] && board[sero][garo] == board[sero + 3][garo + 3] && board[sero][garo] == BLACK)
				return garo + 1;   //// X - X X
			if (board[sero + 2][garo + 2] == 0 && check_belowFilled(board, garo + 2, sero + 2) == 1 && board[sero][garo] == board[sero + 1][garo + 1] && board[sero][garo] == board[sero + 3][garo + 3] && board[sero][garo] == BLACK)
				return garo + 2;   //// X X - X
			if (board[sero + 3][garo + 3] == 0 && check_belowFilled(board, garo + 3, sero + 3) == 1 && board[sero][garo] == board[sero + 1][garo + 1] && board[sero][garo] == board[sero + 2][garo + 2] && board[sero][garo] == BLACK)
				return garo + 3;   //// X X X -
		}
	}

	//왼쪽 위로솟는 대각선
	for (int garo = 3; garo < 7; garo++)
	{
		for (int sero = 0; sero < 3; sero++)
		{
			if (board[sero][garo] == 0 && check_belowFilled(board, garo, sero) == 1 && board[sero + 1][garo - 1] == board[sero + 2][garo - 2] && board[sero + 1][garo - 1] == board[sero + 3][garo - 3] && board[sero + 1][garo - 1] == BLACK)
				return garo;   // - X X X
			if (board[sero + 1][garo - 1] == 0 && check_belowFilled(board, garo - 1, sero + 1) == 1 && board[sero][garo] == board[sero + 2][garo - 2] && board[sero][garo] == board[sero + 3][garo - 3] && board[sero][garo] == BLACK)
				return garo - 1;   // X - X X
			if (board[sero + 2][garo - 2] == 0 && check_belowFilled(board, garo - 2, sero + 2) == 1 && board[sero][garo] == board[sero + 1][garo - 1] && board[sero][garo] == board[sero + 3][garo - 3] && board[sero][garo] == BLACK)
				return garo - 2;   // X X - X
			if (board[sero + 3][garo - 3] == 0 && check_belowFilled(board, garo - 3, sero + 3) == 1 && board[sero][garo] == board[sero + 1][garo - 1] && board[sero][garo] == board[sero + 2][garo - 2] && board[sero][garo] == BLACK)
				return garo - 3;   // X X X - 
		}
	}

	return -1;
}

int check_special_hazard(int board[6][7], int index) {
	int y = 0;
	int map[6][7] = { 0, };
	for (int i = 0; i<6; i++)
	{
		for (int j = 0; j<7; j++)
		{
			map[i][j] = board[i][j];
		}
	}
	for (int sero = 0; sero<6; sero++)
	{
		if (map[sero][index] == 0)
		{
			y = sero;
			break;
		}
	}
	if (y != 5)
		map[y + 1][index] = BLACK;
	else
		return 0;
	if (checkwin(map) == 2)
		return 1;

	return 0;
}