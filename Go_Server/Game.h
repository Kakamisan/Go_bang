#pragma once
#include"_public.h"
#include"Session.h"
#include"Chess.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class Game {
private:
			//pA为A玩家的session，pB为B玩家的session
			session_ptr pA, pB;

			//name_A为A玩家昵称，name_B为B玩家昵称
			char name_A[MSG_LENTH - 1], name_B[MSG_LENTH - 1];

			//棋盘指针，下子时使用该指针调用
			chess_ptr gameplay;

			//准备计数，计数为2时表示双方均发送猜拳消息
			int ready_count;

			int playername_count;

			//重开标志，表示有一方提出重开，并防止同时提出重开时调用两次重开
			int restart_flag;

			//Game唯一id
			int game_id;
public:
			//使用两个{session_ptr}和唯一id构造，代表与两个玩家的session
			Game(session_ptr A, session_ptr B, int id);
			
			//Game对象启动方法
			void start();
private:
			//禁止创建拷贝构造
			Game(const Game&) {};

			//禁止创建赋值构造
			Game& operator=(const Game&) {};

			//游戏运行
			void run();

			//游戏重开
			void re_run();

			//消息处理回调函数，从session接收到消息时调用
			void msg_handler(session_ptr& cur_se);

			//重开处理回调函数，处理是否重开
			void restart_handler(session_ptr& cur_se);

			//收到消息为{GODATA_HEAD_PLAYERNAME}时在{msg_handler}中调用，代表收到了玩家名
			void ghandler_playername(session_ptr& cs, session_ptr& os);

			//收到消息为{GODATA_HEAD_JANKEN}时在{msg_handler}中调用，代表收到了猜拳信号
			void ghandler_janken(session_ptr& cs, session_ptr& os);

			//收到消息为{GODATA_HEAD_SET}时在{msg_handler}中调用，代表收到了下子信号
			void ghandler_set(session_ptr& cs, session_ptr& os);

			//收到消息为{GODATA_HEAD_SURRENDER}时在{msg_handler}中调用，代表收到了投降信号
			void ghandler_surrender(session_ptr& cs, session_ptr& os);

			//收到消息为{GODATA_HEAD_DISCONNECT}时在{msg_handler}中调用，代表收到了退出游戏并断开信号
			void ghandler_disconnect(session_ptr& cs, session_ptr& os);

			//收到消息为{GODATA_HEAD_RESTART}时在{msg_handler}中调用，代表收到了玩家想重开游戏信号
			void ghandler_restart(session_ptr& cs, session_ptr& os);

			void send(session_ptr&);
			void receive(session_ptr&);

			void send_handler(session_ptr&, const boost::system::error_code& ec);
			void receive_handler(session_ptr&, const boost::system::error_code& ec);
};

typedef Game* game_ptr;