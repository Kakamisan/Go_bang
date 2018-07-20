#include"Game.h"

Game::Game(session_ptr A, session_ptr B, int id)
	:pA(A), pB(B), game_id(id), gameplay(new Chess()), ready_count(0), restart_flag(0) 
{
	game_alive[id] = 1;
}

void Game::start() {
	pA->set_msg_findplayer();
	pB->set_msg_findplayer();
	pA->send();
	pB->send();
	run();
}

void Game::run() {
	pA->receive(this, &Game::msg_handler, game_id);
	pB->receive(this, &Game::msg_handler, game_id);
}

void Game::re_run() {
	gameplay->reset();
	ready_count = 0;
	restart_flag = 0;
	start();
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
		ghandler_disconnect(cs, os);
		return;
	}
	char chead = cs->get_msg_head();
	switch (chead)
	{
	case GODATA_HEAD_PLAYERNAME:
		cs->signal_lock();
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
		os->set_msg_other_disconnect();
		os->send();
		cs->set_msg_other_disconnect();
		cs->send();
		game_alive[game_id] = 0;
		delete this;
		break;
	}
}

void Game::restart_handler(Session* const cur_se){
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
	if ((*cs) == (*pA)) {
		strcpy_s(name_A, sizeof(name_A), temp);
	}
	else {
		strcpy_s(name_B, sizeof(name_B), temp);
	}
	cs->sighnal_unlock();
	os->signal_lock();
	os->set_msg_other_playname(temp);
	os->send();
	os->sighnal_unlock();
	os->receive(this, &Game::msg_handler, game_id);
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
		cs->receive(this, &Game::msg_handler, game_id);
		os->receive(this, &Game::msg_handler, game_id);
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
		os->set_msg_other_set(cs->get_msg_data());
		os->send();
		os->receive(this, &Game::msg_handler, game_id);
		break;
	case CHESS_FLAG_A_WIN:
		pA->set_msg_win(GODATA_DATA_WIN);
		pB->set_msg_win(GODATA_DATA_LOSE);
		pA->send();
		pB->send();
		pA->receive(this, &Game::msg_handler, game_id);
		pB->receive(this, &Game::msg_handler, game_id);
		break;
	case CHESS_FLAG_B_WIN:
		pA->set_msg_win(GODATA_DATA_LOSE);
		pB->set_msg_win(GODATA_DATA_WIN);
		pA->send();
		pB->send();
		pA->receive(this, &Game::msg_handler, game_id);
		pB->receive(this, &Game::msg_handler, game_id);
		break;
	case CHESS_FLAG_CHESS_OCCUPY:
	case CHESS_FLAG_CHESS_OVERFLOW:
		cs->set_msg_invalid();
		cs->send();
		cs->receive(this, &Game::msg_handler, game_id);
		break;
	default:
		break;
	}
}

void Game::ghandler_surrender(session_ptr& cs, session_ptr& os) {
	os->set_msg_other_surrender();
	os->send();
	os->receive(this, &Game::msg_handler, game_id);
	cs->receive(this, &Game::msg_handler, game_id);
}

void Game::ghandler_disconnect(session_ptr& cs, session_ptr& os) {
	os->set_msg_other_disconnect();
	os->send();
	game_alive[game_id] = 0;
	delete this;
}

void Game::ghandler_restart(session_ptr& cs, session_ptr& os) {
	if (restart_flag)return;
	restart_flag = 1;
	os->set_msg_other_restart();
	os->send();
	os->receive(this, &Game::restart_handler, game_id);
}