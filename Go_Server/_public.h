#pragma once

#include<boost\asio.hpp>
#include<boost\enable_shared_from_this.hpp>
#include<boost\bind.hpp>
#include<boost\shared_ptr.hpp>

#include<iostream>
#include<string>
#include<utility>
#include<queue>
#include<mutex>

#ifndef MSG_LENTH
#define MSG_LENTH (16)
#endif // !MSG_LENTH 传输消息的长度

#ifndef SERVER_PORT
#define SERVER_PORT (20013)
#endif // !SERVER_PORT 服务端口

#ifndef CHESS_FLAG
#define CHESS_FLAG_CONTINUE (0)
#define CHESS_FLAG_A_WIN (1)
#define CHESS_FLAG_B_WIN (2)
#define CHESS_FLAG_CHESS_OCCUPY (3)
#define CHESS_FLAG_CHESS_OVERFLOW (4)
#endif // !CHESS_FLAG put_chess的返回值

#ifndef CHESS
#define CHESS_NULL (0)
#define CHESS_A (1)
#define CHESS_B (2)
#endif // !CHESS chess属于谁

#ifndef GODATA
#define GODATA_HEAD (0)
#define GODATA_DATA (1)
#define GODATA_HEAD_NULL (0)
#define GODATA_HEAD_FINDPLAYER (1)
#define GODATA_HEAD_JANKEN (2)
#define GODATA_HEAD_JANKEN_RESULT (3)
#define GODATA_HEAD_SET (4)
#define GODATA_HEAD_OTHER_SET (5)
#define GODATA_HEAD_SURRENDER (6)
#define GODATA_HEAD_OTHER_SURRENDER (7)
#define GODATA_HEAD_WIN (8)
#define GODATA_HEAD_DISCONNECT (9)
#define GODATA_HEAD_OTHER_DISCONNECT (10)
#define GODATA_HEAD_RESTART (11)
#define GODATA_HEAD_OTHER_RESTART (12)
#define GODATA_HEAD_PLAYERNAME (13)
#define GODATA_HEAD_OTHER_PLAYERNAME (14)
#define GODATA_HEAD_INVALID (15)
#define GODATA_HEAD_ACK (16)

#define GODATA_DATA_JANKEN_LOSE (0)
#define GODATA_DATA_JANKEN_WIN (1)
#define GODATA_DATA_JANKEN_DRAW (2)
#define GODATA_DATA_JANKEN_ROCK (3)
#define GODATA_DATA_JANKEN_PAPER (4)
#define GODATA_DATA_JANKEN_SCISSORS (5)

#define GODATA_DATA_LOSE (0)
#define GODATA_DATA_WIN (1)
#endif // !GODATA 传输协议
