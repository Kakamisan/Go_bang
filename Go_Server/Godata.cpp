#include"Godata.h"

Godata::Godata(char head, const char* data) {
	m_msg[GODATA_HEAD] = head;
	strcpy_s(&m_msg[1], min(sizeof(m_msg) - 1, strlen(data)), data);
}

Godata& Godata::operator=(const Godata& other) {
	strcpy_s(m_msg, MSG_LENTH, other.m_msg);
	return *this;
}

int Godata::transform_to_other() {
	if (!have_other()) {
		return FALSE;
	}
	int head = m_msg[GODATA_HEAD];
	switch (head)
	{
	case GODATA_HEAD_DISCONNECT:
		m_msg[GODATA_HEAD] = GODATA_HEAD_OTHER_DISCONNECT;
		break;
	case GODATA_HEAD_PLAYERNAME:
		m_msg[GODATA_HEAD] = GODATA_HEAD_OTHER_PLAYERNAME;
		break;
	case GODATA_HEAD_RESTART:
		m_msg[GODATA_HEAD] = GODATA_HEAD_OTHER_RESTART;
		break;
	case GODATA_HEAD_SET:
		m_msg[GODATA_HEAD] = GODATA_HEAD_OTHER_SET;
		break;
	case GODATA_HEAD_SURRENDER:
		m_msg[GODATA_HEAD] = GODATA_HEAD_OTHER_SURRENDER;
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}

int Godata::have_other() {
	int head = m_msg[GODATA_HEAD];
	if (head == GODATA_HEAD_FINDPLAYER)return FALSE;
	if (head == GODATA_HEAD_JANKEN)return FALSE;
	if (head == GODATA_HEAD_JANKEN_RESULT)return FALSE;
	if (head == GODATA_HEAD_NULL)return FALSE;
	if (head == GODATA_HEAD_WIN)return FALSE;
	if (head == GODATA_HEAD_OTHER_DISCONNECT)return FALSE;
	if (head == GODATA_HEAD_OTHER_PLAYERNAME)return FALSE;
	if (head == GODATA_HEAD_OTHER_RESTART)return FALSE;
	if (head == GODATA_HEAD_OTHER_SET)return FALSE;
	if (head == GODATA_HEAD_OTHER_SURRENDER)return FALSE;
	if (head == GODATA_HEAD_INVALID)return FALSE;
	if (head == GODATA_HEAD_ACK)return FALSE;
	return TRUE;
}

int Godata::change_head(int h) {
	m_msg[GODATA_HEAD] = h;
	return TRUE;
}
int Godata::change_data(const char* d) {
	strcpy_s(&m_msg[GODATA_DATA], min(sizeof(m_msg) - 1, strlen(d)), d);
	return TRUE;
}

int Godata::change_data(const string& str) {
	return change_data(str.c_str());
}

int Godata::change_data(char data)
{
	m_msg[GODATA_DATA] = data;
	return TRUE;
}

char Godata::get_head() {
	return m_msg[GODATA_HEAD];
}

char* Godata::msg_ptr() {
	return m_msg;
}

const char * Godata::get_data()
{
	return &m_msg[GODATA_DATA];
}
