#pragma once
#include"_public.h"
#include"Session.h"
#include"Chess.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class Game {
private:
			//pAΪA��ҵ�session��pBΪB��ҵ�session
			session_ptr pA, pB;

			//name_AΪA����ǳƣ�name_BΪB����ǳ�
			char name_A[MSG_LENTH - 1], name_B[MSG_LENTH - 1];

			//����ָ�룬����ʱʹ�ø�ָ�����
			chess_ptr gameplay;

			//׼������������Ϊ2ʱ��ʾ˫�������Ͳ�ȭ��Ϣ
			int ready_count;

			int playername_count;

			//�ؿ���־����ʾ��һ������ؿ�������ֹͬʱ����ؿ�ʱ���������ؿ�
			int restart_flag;

			//GameΨһid
			int game_id;
public:
			//ʹ������{session_ptr}��Ψһid���죬������������ҵ�session
			Game(session_ptr A, session_ptr B, int id);
			
			//Game������������
			void start();
private:
			//��ֹ������������
			Game(const Game&) {};

			//��ֹ������ֵ����
			Game& operator=(const Game&) {};

			//��Ϸ����
			void run();

			//��Ϸ�ؿ�
			void re_run();

			//��Ϣ����ص���������session���յ���Ϣʱ����
			void msg_handler(session_ptr& cur_se);

			//�ؿ�����ص������������Ƿ��ؿ�
			void restart_handler(session_ptr& cur_se);

			//�յ���ϢΪ{GODATA_HEAD_PLAYERNAME}ʱ��{msg_handler}�е��ã������յ��������
			void ghandler_playername(session_ptr& cs, session_ptr& os);

			//�յ���ϢΪ{GODATA_HEAD_JANKEN}ʱ��{msg_handler}�е��ã������յ��˲�ȭ�ź�
			void ghandler_janken(session_ptr& cs, session_ptr& os);

			//�յ���ϢΪ{GODATA_HEAD_SET}ʱ��{msg_handler}�е��ã������յ��������ź�
			void ghandler_set(session_ptr& cs, session_ptr& os);

			//�յ���ϢΪ{GODATA_HEAD_SURRENDER}ʱ��{msg_handler}�е��ã������յ���Ͷ���ź�
			void ghandler_surrender(session_ptr& cs, session_ptr& os);

			//�յ���ϢΪ{GODATA_HEAD_DISCONNECT}ʱ��{msg_handler}�е��ã������յ����˳���Ϸ���Ͽ��ź�
			void ghandler_disconnect(session_ptr& cs, session_ptr& os);

			//�յ���ϢΪ{GODATA_HEAD_RESTART}ʱ��{msg_handler}�е��ã������յ���������ؿ���Ϸ�ź�
			void ghandler_restart(session_ptr& cs, session_ptr& os);

			void send(session_ptr&);
			void receive(session_ptr&);

			void send_handler(session_ptr&, const boost::system::error_code& ec);
			void receive_handler(session_ptr&, const boost::system::error_code& ec);
};

typedef Game* game_ptr;