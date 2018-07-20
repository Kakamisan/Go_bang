#include"Session.h"

Session::Session(io_service& io, int id) :m_socket(io), session_id(id) {}

bool Session::operator==(const Session& other) {
	if (session_id == other.session_id)return true;
	return false;
}

int Session::test_error() {
	int ec = 0;
	if (m_ec)ec = 1;
	return ec;
}

void Session::update_error(const boost::system::error_code& ec) {
	m_ec = ec;
}

void Session::send() {
	m_socket.async_write_some(
		buffer(m_msg.msg_ptr(), MSG_LENTH),
		boost::bind(
			[](Session* const cur_se, const boost::system::error_code& ec)
	{
		cur_se->update_error(ec);
	},
			this, boost::asio::placeholders::error)
	);
}

void Session::receive(const void* const func) {
	m_socket.async_read_some(buffer(m_msg.msg_ptr(), MSG_LENTH),
		boost::bind(
			[func](Session* const cur_se, const boost::system::error_code& ec)
	{
		cur_se->update_error(ec);
		boost::bind(func, cur_se)();
	},
			this, boost::asio::placeholders::error
		)
	);
}

void Session::set_msg_findplayer() {
	m_msg.change_head(GODATA_HEAD_FINDPLAYER);
}

void Session::set_msg_janken_result(char data) {
	m_msg.change_head(GODATA_HEAD_JANKEN_RESULT);
	m_msg.change_data(data);
}

void Session::set_msg_other_set(const char* data){
	m_msg.change_head(GODATA_HEAD_OTHER_SET);
	m_msg.change_data(data);
}

void Session::set_msg_other_surrender()
{
	m_msg.change_head(GODATA_HEAD_OTHER_SURRENDER);
}

void Session::set_msg_win(char data)
{
	m_msg.change_head(GODATA_HEAD_WIN);
	m_msg.change_data(data);
}

void Session::set_msg_other_disconnect()
{
	m_msg.change_head(GODATA_HEAD_OTHER_DISCONNECT);
}

void Session::set_msg_other_restart()
{
	m_msg.change_head(GODATA_HEAD_OTHER_RESTART);
}

void Session::set_msg_other_playname(const char* name)
{
	m_msg.change_head(GODATA_HEAD_OTHER_PLAYERNAME);
	m_msg.change_data(name);
}

void Session::set_msg_invalid()
{
	m_msg.change_head(GODATA_HEAD_INVALID);
}

void Session::set_msg(const Godata& other) {
	m_msg = other;
}

const Godata& Session::get_msg() {
	return m_msg;
}

char Session::get_msg_head() {
	return m_msg.get_head();
}

const char* Session::get_msg_data() {
	return m_msg.get_data();
}

void Session::signal_lock()
{
	signal.lock();
}

void Session::sighnal_unlock()
{
	signal.unlock();
}
