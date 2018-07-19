#pragma once
#include"_public.h"
#include"Godata.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class Session:public boost::enable_shared_from_this<Session>{
public:
			friend class Game;
			friend class Server;
private:
			//ÿ��sessionӵ��һ��Ψһ{socket}
			tcp::socket m_socket;

			//ÿ��sessionӵ��һ����Ϣ{Godata}
			Godata m_msg;

			//ÿ��sessionӵ��һ��{error_code}
			boost::system::error_code m_ec;

			//ÿ��sessionӵ��һ��Ψһ{session_id}
			int session_id;
public:
			//ʹ��{io_service}��{id}����
			Session(io_service& io,int id);

			virtual ~Session(){}

			//�ж�����session��{session_id}�Ƿ���ȣ���ȴ���Ϊͬһsession����
			bool operator==(const Session& other);

			//�鿴�Ƿ����socket���󣬲���ʱ����TRUE
			int test_error();

			//socket����ʱ���ã�����session��{error_code}
			void update_error(const boost::system::error_code& ec);

			//socketʹ�õ�ǰ{Godata}����һ����Ϣ
			void send();

			//socket�첽�ȴ���ȡһ����Ϣ��{Godata}�����ص�{func}
			void receive(const void* const func);
public:
			void set_msg_findplayer();
			void set_msg_janken_result(char);
			void set_msg_other_set();
			void set_msg_other_surrender();
			void set_msg_win(char);
			void set_msg_other_disconnect();
			void set_msg_other_restart();
			void set_msg_other_playname();
			void set_msg_invalid();

			//ʹ����һ��{Godata}���Ƶ���ǰ�����{Godata}
			void set_msg(const Godata& other);

			//����{Godata}������
			const Godata& get_msg();

			//����{Godata}��ͷ�ֽ�
			char get_msg_head();

			//����{Godata}�����ݱ�
			const char* get_msg_data();
private:
			Session(const Session&);

			Session& operator=(const Session&);
};

typedef boost::shared_ptr<Session> session_ptr;