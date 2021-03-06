#include"Server.h"

Server *Server::instance = nullptr;

Server* & Server::get_instance() {
	if (instance != nullptr)return instance;
	tcp::endpoint ep(tcp::v4(), SERVER_PORT);
	instance = new Server(ep);
	return instance;
}

Server::Server(tcp::endpoint ep):m_acceptor(m_io_service,ep) {}

void Server::run() {
	accept_new_session();
	m_io_service.run();
}

void Server::accept_new_session() {
	static int shared_id = 10000;
	session_ptr new_session(new Session(m_io_service, ++shared_id));
	m_q_sp.push(new_session);
	m_acceptor.async_accept(new_session->get_socket(),
		boost::bind(&Server::accept_handler, this, new_session, boost::asio::placeholders::error)
	);
}

void Server::accept_handler(session_ptr sp, const boost::system::error_code& ec) {
	if (!ec&&sp) {
		while (m_q_sp.size() > 1) {
			if (m_q_sp.front()->test_disconnect()) {
				delete m_q_sp.front();
				m_q_sp.pop();
				//std::cout << "A is error!" << endl;
			}
			else {
				session_ptr A = m_q_sp.front();
				m_q_sp.pop();
				if (m_q_sp.front()->test_disconnect()) {
					delete m_q_sp.front();
					m_q_sp.pop();
					//std::cout << "B is error!" << endl;
					m_q_sp.push(A);
				}
				else {
					session_ptr B = m_q_sp.front();
					m_q_sp.pop();
					//std::cout << "A & B is normal!" << endl;

					static int id = 0;
					game_ptr new_game = new Game(A, B, id);
					std::cout << "game no." << id << " is starting" << std::endl;
					id++;

					new_game->start();
				}
			}
		}
		accept_new_session();
	}
	else {
		std::cout << ec.message() << std::endl;
		accept_new_session();
	}
}