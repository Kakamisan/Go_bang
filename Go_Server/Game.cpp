#include"Game.h"

Game::Game(session_ptr A, session_ptr B) :pA(A), pB(B), gameplay(new Chess()), ready_count(0) {}

void Game::start() {
	pA->set_msg_findplayer();
	pB->set_msg_findplayer();
	pA->send();
	pB->send();
	run();
}

void Game::run() {
	pA->receive(this->msg_handler);
	pB->receive(this->msg_handler);
}

void Game::msg_handler(Session* const cur_se) {
	session_ptr cs;
	session_ptr os;
	if ((*cur_se) == (*pA)) {
		cs = pA;
		os = pB;
	}
	else if ((*cur_se) == (*pB)) {
		cs = pB;
		os = pA;
	}
	else {
		std::cout << "Get error session_ptr !" << std::endl;
		return;
	}
	if (cs->test_error()) {
		os->set_msg_other_disconnect();
		os->send();
		return;
	}
	char chead = cs->get_msg_head();
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
	default:
		break;
	}
	//do
}

void Game::ghandler_playername(session_ptr& cs, session_ptr& os) {
	Godata temp = cs->get_msg();
	os->set_msg(temp);
	os->set_msg_other_playname();
	os->send();
	os->receive(this->msg_handler);
}

void Game::ghandler_janken(session_ptr& cs, session_ptr& os) {
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
		cs->send();
		os->send();
		ready_count = 0;
		cs->receive(this->msg_handler);
		os->receive(this->msg_handler);
	}
}

void Game::ghandler_set(session_ptr& cs, session_ptr& os) {
	int x, y;
	x = cs->get_msg_data()[0];
	y = cs->get_msg_data()[1];
	int flag;
	if ((*cs) == (*pA)) {
		flag = gameplay->put_chess(x, y, CHESS_A);
	}
	else {
		flag = gameplay->put_chess(x, y, CHESS_B);
	}
	
	switch (flag)
	{
	case CHESS_FLAG_CONTINUE:
		os->set_msg(cs->get_msg());
		os->set_msg_other_set();
		os->send();
		os->receive(this->msg_handler);
		break;
	case CHESS_FLAG_A_WIN:
		pA->set_msg_win(GODATA_DATA_WIN);
		pB->set_msg_win(GODATA_DATA_LOSE);
		pA->send();
		pB->send();
		pA->receive(this->msg_handler);
		pB->receive(this->msg_handler);
		break;
	case CHESS_FLAG_B_WIN:
		pA->set_msg_win(GODATA_DATA_LOSE);
		pB->set_msg_win(GODATA_DATA_WIN);
		pA->send();
		pB->send();
		pA->receive(this->msg_handler);
		pB->receive(this->msg_handler);
		break;
	case CHESS_FLAG_CHESS_OCCUPY:
	case CHESS_FLAG_CHESS_OVERFLOW:
		cs->set_msg_invalid();
		cs->send();
		cs->receive(this->msg_handler);
		break;
	default:
		break;
	}
}