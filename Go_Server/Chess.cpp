#include"Chess.h"

Chess::Chess() {
	memset(chess_board, 0, sizeof(chess_board));
	memset(chess_count, 0, sizeof(chess_count));
}
/*
¨I	¡ü	¨J		0	1	2
¡û		¡ú		3		4
¨L	¡ý	¨K		5	6	7
*/

int Chess::put_chess(int x, int y, int chess) {
	if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)return CHESS_FLAG_CHESS_OVERFLOW;
	if (chess_board[x][y])return CHESS_FLAG_CHESS_OCCUPY;

	chess_board[x][y] = chess;
	for (int i = 0; i < 8; ++i) {
		chess_count[x][y][i] += chess == CHESS_A ? 1 : -1;
		if (chess_count[x][y][i] == 5)return CHESS_FLAG_A_WIN;
		if (chess_count[x][y][i] == -5)return CHESS_FLAG_B_WIN;
	}
	//0
	for (int i = 1; i <= 4; ++i) {
		if (x - i < 0 || y - i < 0) break;
		chess_count[x - i][y - i][7] += chess == CHESS_A ? 1 : -1;
		if (chess_count[x - i][y - i][7] == 5)return CHESS_FLAG_A_WIN;
		if (chess_count[x - i][y - i][7] == -5)return CHESS_FLAG_B_WIN;
	}
	//1
	for (int i = 1; i <= 4; ++i) {
		if (y - i < 0) break;
		chess_count[x][y - i][6] += chess == CHESS_A ? 1 : -1;
		if (chess_count[x][y - i][6] == 5)return CHESS_FLAG_A_WIN;
		if (chess_count[x][y - i][6] == -5)return CHESS_FLAG_B_WIN;
	}
	//2
	for (int i = 1; i <= 4; ++i) {
		if (x + i >= BOARD_SIZE || y - i < 0) break;
		chess_count[x + i][y - i][5] += chess == CHESS_A ? 1 : -1;
		if (chess_count[x + i][y - i][5] == 5)return CHESS_FLAG_A_WIN;
		if (chess_count[x + i][y - i][5] == -5)return CHESS_FLAG_B_WIN;
	}
	//3
	for (int i = 1; i <= 4; ++i) {
		if (x - i < 0) break;
		chess_count[x - i][y][4] += chess == CHESS_A ? 1 : -1;
		if (chess_count[x - i][y][4] == 5)return CHESS_FLAG_A_WIN;
		if (chess_count[x - i][y][4] == -5)return CHESS_FLAG_B_WIN;
	}
	//4
	for (int i = 1; i <= 4; ++i) {
		if (x + i >= BOARD_SIZE) break;
		chess_count[x + i][y][3] += chess == CHESS_A ? 1 : -1;
		if (chess_count[x + i][y][3] == 5)return CHESS_FLAG_A_WIN;
		if (chess_count[x + i][y][3] == -5)return CHESS_FLAG_B_WIN;
	}
	//5
	for (int i = 1; i <= 4; ++i) {
		if (x - i < 0 || y + i >= BOARD_SIZE) break;
		chess_count[x - i][y + i][2] += chess == CHESS_A ? 1 : -1;
		if (chess_count[x - i][y + i][2] == 5)return CHESS_FLAG_A_WIN;
		if (chess_count[x - i][y + i][2] == -5)return CHESS_FLAG_B_WIN;
	}
	//6
	for (int i = 1; i <= 4; ++i) {
		if (y + i >= BOARD_SIZE) break;
		chess_count[x][y + i][1] += chess == CHESS_A ? 1 : -1;
		if (chess_count[x][y + i][1] == 5)return CHESS_FLAG_A_WIN;
		if (chess_count[x][y + i][1] == -5)return CHESS_FLAG_B_WIN;
	}
	//7
	for (int i = 1; i <= 4; ++i) {
		if (x + i >= BOARD_SIZE || y + i >= BOARD_SIZE) break;
		chess_count[x + i][y + i][0] += chess == CHESS_A ? 1 : -1;
		if (chess_count[x + i][y + i][0] == 5)return CHESS_FLAG_A_WIN;
		if (chess_count[x + i][y + i][0] == -5)return CHESS_FLAG_B_WIN;
	}
	return CHESS_FLAG_CONTINUE;
}

void Chess::reset() {
	memset(chess_board, 0, sizeof(chess_board));
	memset(chess_count, 0, sizeof(chess_count));
}