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

			//����ָ�룬����ʱʹ�ø�ָ�����
			chess_ptr gameplay;

			//׼������������Ϊ2ʱ��ʾ˫�������Ͳ�ȭ��Ϣ
			int ready_count;
public:
			//ʹ������{session_ptr}���죬������������ҵ�session
			Game(session_ptr A, session_ptr B);

			virtual ~Game() { }

			//Game������������
			void start();
private:
			//��ֹ������������
			Game(const Game&) {};

			//��ֹ������ֵ����
			Game& operator=(const Game&) {};

			//��Ϸ����
			void run();

			//��Ϣ����ص���������session���յ���Ϣʱ����
			void msg_handler(Session* const cur_se);

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
};

typedef boost::shared_ptr<Game> game_ptr;