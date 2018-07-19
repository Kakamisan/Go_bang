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
			//每个session拥有一个唯一{socket}
			tcp::socket m_socket;

			//每个session拥有一个消息{Godata}
			Godata m_msg;

			//每个session拥有一个{error_code}
			boost::system::error_code m_ec;

			//每个session拥有一个唯一{session_id}
			int session_id;
public:
			//使用{io_service}和{id}构造
			Session(io_service& io,int id);

			virtual ~Session(){}

			//判断两个session的{session_id}是否相等，相等代表为同一session对象
			bool operator==(const Session& other);

			//查看是否产生socket错误，产生时返回TRUE
			int test_error();

			//socket连接时调用，更新session的{error_code}
			void update_error(const boost::system::error_code& ec);

			//socket使用当前{Godata}发送一条消息
			void send();

			//socket异步等待读取一条消息到{Godata}，并回调{func}
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

			//使用另一个{Godata}复制到当前对象的{Godata}
			void set_msg(const Godata& other);

			//返回{Godata}的引用
			const Godata& get_msg();

			//返回{Godata}的头字节
			char get_msg_head();

			//返回{Godata}的数据报
			const char* get_msg_data();
private:
			Session(const Session&);

			Session& operator=(const Session&);
};

typedef boost::shared_ptr<Session> session_ptr;