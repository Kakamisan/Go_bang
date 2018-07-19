#pragma once
#include"_public.h"

#ifndef BOARD_SIZE
#define BOARD_SIZE (19)
#endif // !BOARD_SIZE

/*
z��ֲ�����

�I	��	�J		0	1	2
��		��		3		4
�L	��	�K		5	6	7
*/
class Chess {
private:
			//��¼��������״�����ֱ�Ϊ{CHESS_A}��{CHESS_B}��{CHESS_NULL}
			char chess_board[BOARD_SIZE][BOARD_SIZE];

			//��¼���̸�������������������������дﵽ5ʱ��Ϸ����
			char chess_count[BOARD_SIZE][BOARD_SIZE][8];
public:
			//Ĭ�Ͽ�����
			Chess();
public:
			//���ӣ�����{CHESS_FLAG_00}������Ϊ{x}��{y}��{CHESS_00}
			int put_chess(int x, int y, int chess);

			//����Ϊ������
			void reset();
};

typedef boost::shared_ptr<Chess> chess_ptr;