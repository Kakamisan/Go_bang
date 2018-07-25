#include"Game.h"

Game::Game(session_ptr A, session_ptr B, int id)
	:pA(A), pB(B), game_id(id), gameplay(new Chess()), ready_count(0), restart_flag(0), playername_count(0)
{
	game_alive[id] = 1;
}

void Game::start() {
	pA->set_msg_findplayer();
	pB->set_msg_findplayer();
	send(pA);
	send(pB);
	run();
}

void Game::run() {
	receive(pA);
	receive(pB);
}

void Game::re_run() {
	gameplay->reset();
	ready_count = 0;
	playername_count = 0;
	restart_flag = 0;
	start();
}

void Game::msg_handler(session_ptr& cur_se) {
	std::cout << "id: " << game_id << " -> receive msg" << std::endl;
	session_ptr cs;
	session_ptr os;
	if ((*cur_se) == (*pA)) {
		cs = session_ptr(&(*pA));
		os = session_ptr(&(*pB));
	}
	else if ((*cur_se) == (*pB)) {
		cs = session_ptr(&(*pB));
		os = session_ptr(&(*pA));
	}
	else {
		std::cout << "Get error session_ptr !" << std::endl;
		return;
	}
	if (cs->test_error()) {
		std::cout << "session_id : " << cs->get_session_id() << " : test_error true" << std::endl;
		ghandler_disconnect(cs, os);
		return;
	}
	int chead = cs->get_msg_head();
	switch (chead)
	{
	case GODATA_HEAD_PLAYERNAME:
		ghandler_playername(cs, os);
		break;
	case GODATA_HEAD_JANKEN:
		ghandler_janken(cs, os);
		break;
	case GODATA_HEAD_SET:
		ghandler_set(cs, os);
		break;
	case GODATA_HEAD_SURRENDER:
		ghandler_surrender(cs, os);
		break;
	case GODATA_HEAD_DISCONNECT:
		ghandler_disconnect(cs, os);
		break;
	case GODATA_HEAD_RESTART:
		ghandler_restart(cs, os);
		break;
	case GODATA_HEAD_ACK:
		re_run();
		break;
	default:
		std::cout << "unknown head" << endl;
		os->set_msg_other_disconnect();
		send(os);
		cs->set_msg_other_disconnect();
		send(cs);
		game_alive[game_id] = 0;
		delete this;
		break;
	}
}

void Game::restart_handler(session_ptr& cur_se){
	if (cur_se->get_msg_head() == GODATA_HEAD_ACK) {
		re_run();
	}
	else {
		if ((*cur_se) == (*pA)) {
			ghandler_disconnect(pA, pB);
		}
		else {
			ghandler_disconnect(pB, pA);
		}
	}
}

void Game::ghandler_playername(session_ptr& cs, session_ptr& os) {
	const char* temp = cs->get_msg_data();
	std::cout << "playername : " << temp << endl;
	if ((*cs) == (*pA)) {
		strcpy_s(name_A, sizeof(name_A), temp);
	}
	else {
		strcpy_s(name_B, sizeof(name_B), temp);
	}
	playername_count++;
	std::cout << "playname_count : " << playername_count << endl;
	if (playername_count < 2)return;
	std::cout << name_A << " " << name_B << endl;
	pA->set_msg_other_playname(name_B);
	pB->set_msg_other_playname(name_A);
	send(pA);
	send(pB);
	receive(pA);
	receive(pB);
	playername_count = 0;
}

void Game::ghandler_janken(session_ptr& cs, session_ptr& os) {
	std::cout << "janken" << endl;
	ready_count++;
	if (ready_count > 1) {
		char cc = cs->get_msg_data()[0];
		char oc = os->get_msg_data()[0];
		//²ÂÈ­Æ½¾Ö
		if (cc == oc) {
			cs->set_msg_janken_result(GODATA_DATA_JANKEN_DRAW);
			os->set_msg_janken_result(GODATA_DATA_JANKEN_DRAW);
		}
		else {
			switch (cc)
			{
			case GODATA_DATA_JANKEN_ROCK:
				if (oc == GODATA_DATA_JANKEN_SCISSORS) {
					cs->set_msg_janken_result(GODATA_DATA_JANKEN_WIN);
					os->set_msg_janken_result(GODATA_DATA_JANKEN_LOSE);
				}
				else {
					cs->set_msg_janken_result(GODATA_DATA_JANKEN_LOSE);
					os->set_msg_janken_result(GODATA_DATA_JANKEN_WIN);
				}
				break;
			case GODATA_DATA_JANKEN_SCISSORS:
				if (oc == GODATA_DATA_JANKEN_PAPER) {
					cs->set_msg_janken_result(GODATA_DATA_JANKEN_WIN);
					os->set_msg_janken_result(GODATA_DATA_JANKEN_LOSE);
				}
				else {
					cs->set_msg_janken_result(GODATA_DATA_JANKEN_LOSE);
					os->set_msg_janken_result(GODATA_DATA_JANKEN_WIN);
				}
				break;
			case GODATA_DATA_JANKEN_PAPER:
				if (oc == GODATA_DATA_JANKEN_ROCK) {
					cs->set_msg_janken_result(GODATA_DATA_JANKEN_WIN);
					os->set_msg_janken_result(GODATA_DATA_JANKEN_LOSE);
				}
				else {
					cs->set_msg_janken_result(GODATA_DATA_JANKEN_LOSE);
					os->set_msg_janken_result(GODATA_DATA_JANKEN_WIN);
				}
				break;
			default:
				break;
			}
		}
		send(cs);
		send(os);
		ready_count = 0;
		receive(cs);
		receive(os);
	}
}

void Game::ghandler_set(session_ptr& cs, session_ptr& os) {
	std::cout << "set" << endl;
	char tempdata[2];
	tempdata[0] = cs->get_msg_data()[0];
	tempdata[1] = cs->get_msg_data()[1];
	int flag;
	if ((*cs) == (*pA)) {
		flag = gameplay->put_chess(tempdata[0], tempdata[1], CHESS_A);
	}
	else {
		flag = gameplay->put_chess(tempdata[0], tempdata[1], CHESS_B);
	}
	switch (flag)
	{
	case CHESS_FLAG_CONTINUE:
		os->set_msg_other_set(cs->get_msg_data());
		send(os);
		receive(os);
		break;
	case CHESS_FLAG_A_WIN:
		pA->set_msg_win(GODATA_DATA_WIN, tempdata);
		pB->set_msg_win(GODATA_DATA_LOSE, tempdata);
		send(pA);
		send(pB);
		receive(pA);
		receive(pB);
		break;
	case CHESS_FLAG_B_WIN:
		pA->set_msg_win(GODATA_DATA_LOSE, tempdata);
		pB->set_msg_win(GODATA_DATA_WIN, tempdata);
		send(pA);
		send(pB);
		receive(pA);
		receive(pB);
		break;
	case CHESS_FLAG_CHESS_OCCUPY:
	case CHESS_FLAG_CHESS_OVERFLOW:
		cs->set_msg_invalid();
		send(cs);
		receive(cs);
		break;
	default:
		break;
	}
}

void Game::ghandler_surrender(session_ptr& cs, session_ptr& os) {
	std::cout << "surrender" << endl;
	os->set_msg_other_surrender();
	send(os);
	receive(os);
	receive(cs);
}

void Game::ghandler_disconnect(session_ptr& cs, session_ptr& os) {
	std::cout << "disconnect" << endl;
	os->set_msg_other_disconnect();
	send(os);
	game_alive[game_id] = 0;
	delete this;
}

void Game::ghandler_restart(session_ptr& cs, session_ptr& os) {
	std::cout << "restart" << endl;
	if (restart_flag)return;
	restart_flag = 1;
	os->set_msg_other_restart();
	send(os);
	receive(os);
}

void Game::send(session_ptr& ses) {
	(ses->get_socket()).async_write_some
	(
		buffer((ses->get_msg()).m_msg, MSG_LENTH),
		boost::bind(&Game::send_handler, this, ses, boost::asio::placeholders::error)
	);
}

void Game::send_handler(session_ptr& ses, const boost::system::error_code& ec) {
	std::cout << "session_id : " << ses->get_session_id() << " : send!" << "msg : " << (int)((ses->get_msg()).get_head()) << " " << (int)((ses->get_msg_data())[0]) << " " << (int)((ses->get_msg_data())[1]) << endl;
	ses->update_error(ec);
}

void Game::receive(session_ptr& ses) {
	(ses->get_socket()).async_read_some
	(
		buffer((ses->get_msg()).m_msg, MSG_LENTH),
		boost::bind(&Game::receive_handler, this, ses, boost::asio::placeholders::error)
	);
}

void Game::receive_handler(session_ptr& ses, const boost::system::error_code& ec) {
	std::cout << "session_id : " << ses->get_session_id() << " : read!" << endl;
	ses->update_error(ec);
	if (ec) {
		std::cout << "session_id : " << ses->get_session_id() << " error" << endl;
	}
	if (!game_alive[game_id])return;
	msg_handler(ses);
}