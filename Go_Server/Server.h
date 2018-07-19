#pragma once
#include"_public.h"
#include"Game.h"

using namespace boost::asio;
using namespace ip;

class Server {
private:
			io_service m_io_service;

			tcp::acceptor m_acceptor;

			//session队列，每一对有效session生成一个Game对象
			std::queue<session_ptr> m_q_sp;
private:
			//Server唯一句柄
			static Server *instance;
public:
			//为外部提供Server唯一句柄
			static Server* & get_instance();

			~Server() {}
private:
			//使用endpoint构造
			Server(tcp::endpoint);
public:
			//启动Server
			void run();
private:
			//接收到session连接时调用
			void accept_handler(session_ptr sp, const boost::system::error_code& ec);

			//准备接收新的session连接
			void accept_new_session();
};