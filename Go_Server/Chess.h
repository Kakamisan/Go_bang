#pragma once
#include"_public.h"

#ifndef BOARD_SIZE
#define BOARD_SIZE (19)
#endif // !BOARD_SIZE

/*
z轴分布如下

↖	↑	↗		0	1	2
←		→		3		4
↙	↓	↘		5	6	7
*/
class Chess {
private:
			//记录棋盘棋子状况，分别为{CHESS_A}，{CHESS_B}，{CHESS_NULL}
			char chess_board[BOARD_SIZE][BOARD_SIZE];

			//记录棋盘各格各方向相连棋子数，其中有达到5时游戏结束
			char chess_count[BOARD_SIZE][BOARD_SIZE][8];
public:
			//默认空棋盘
			Chess();
public:
			//下子，返回{CHESS_FLAG_00}，参数为{x}，{y}，{CHESS_00}
			int put_chess(int x, int y, int chess);

			//重置为空棋盘
			void reset();
};

typedef boost::shared_ptr<Chess> chess_ptr;