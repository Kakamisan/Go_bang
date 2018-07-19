#pragma once
#include"_public.h"
#include"Game.h"

using namespace boost::asio;
using namespace ip;

class Server {
private:
			io_service m_io_service;

			tcp::acceptor m_acceptor;

			//session���У�ÿһ����Чsession����һ��Game����
			std::queue<session_ptr> m_q_sp;
private:
			//ServerΨһ���
			static Server *instance;
public:
			//Ϊ�ⲿ�ṩServerΨһ���
			static Server* & get_instance();

			~Server() {}
private:
			//ʹ��endpoint����
			Server(tcp::endpoint);
public:
			//����Server
			void run();
private:
			//���յ�session����ʱ����
			void accept_handler(session_ptr sp, const boost::system::error_code& ec);

			//׼�������µ�session����
			void accept_new_session();
};