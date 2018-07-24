#pragma once
#include"_public.h"
#include"Godata.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class Game;
typedef void (Game::*game_func)(Session*);

class Session:public boost::enable_shared_from_this<Session>{

private:
			//ÿ��sessionӵ��һ��Ψһ{socket}
			tcp::socket m_socket;

			//ÿ��sessionӵ��һ����Ϣ{Godata}
			Godata m_msg;

			//ÿ��sessionӵ��һ��{error_code}
			int m_ec;

			//ÿ��sessionӵ��һ��Ψһ{session_id}
			int session_id;

			//ÿ��sessionӵ��һ��ͬ���ź�
			mutex signal;
public:
			//ʹ��{io_service}��{id}����
			Session(io_service& io,int id);

			virtual ~Session(){}

			tcp::socket& get_socket();

			//�ж�����session��{session_id}�Ƿ���ȣ���ȴ���Ϊͬһsession����
			bool operator==(const Session& other);

			int get_session_id();

			//�鿴�Ƿ����socket���󣬲���ʱ����TRUE
			int test_error();

			int test_disconnect();

			//socket����ʱ���ã�����session��{error_code}
			void update_error(const boost::system::error_code& ec);

			//socketʹ�õ�ǰ{Godata}����һ����Ϣ
			void send();

			//socket�첽�ȴ���ȡһ����Ϣ��{Godata}�����ص�{func}
			void receive();
public:
			void set_msg_findplayer();
			void set_msg_janken_result(char);
			void set_msg_other_set(char*);
			void set_msg_other_surrender();
			void set_msg_win(char,char*);
			void set_msg_other_disconnect();
			void set_msg_other_restart();
			void set_msg_other_playname(char*);
			void set_msg_invalid();

			//ʹ����һ��{Godata}���Ƶ���ǰ�����{Godata}
			void set_msg(const Godata& other);

			//����{Godata}������
			Godata& get_msg();

			//����{Godata}��ͷ�ֽ�
			char get_msg_head();

			//����{Godata}�����ݱ�
			char* get_msg_data();

			//������
			void signal_lock();

			//�����
			void sighnal_unlock();
private:
			Session(const Session&);

			Session& operator=(const Session&);

			void send_handler(const boost::system::error_code& ec);
			
			void receive_handler(const boost::system::error_code& ec);
};

//typedef boost::shared_ptr<Session> session_ptr;
typedef Session* session_ptr;