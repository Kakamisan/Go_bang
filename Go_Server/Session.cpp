#include"Session.h"

Session::Session(io_service& io, int id) :m_socket(io), session_id(id) {}

tcp::socket & Session::get_socket()
{
	// TODO: 在此处插入 return 语句
	return m_socket;
}

bool Session::operator==(const Session& other) {
	if (session_id == other.session_id)return true;
	return false;
}

int Session::get_session_id()
{
	return session_id;
}

int Session::test_error() {
	return m_ec;
}

void Session::update_error(const boost::system::error_code& ec) {
	if (ec)m_ec = 1;
	else m_ec = 0;
}

void Session::send() {
	m_socket.async_write_some(
		buffer(m_msg.msg_ptr(), MSG_LENTH),
		/*boost::bind(
			[](const boost::system::error_code& ec, Session* const cur_se)
	{
		cur_se->update_error(ec);
	},
			boost::asio::placeholders::error, this)*/
		boost::bind(&Session::send_handler, this, boost::asio::placeholders::error)
	);
}

void Session::receive(void* p, game_func func, int id) {
	m_socket.async_read_some(buffer(m_msg.msg_ptr(), MSG_LENTH),
		/*boost::bind(
			[p, func](const boost::system::error_code& ec, Session* const cur_se)
	{
		cur_se->update_error(ec);
		(const_cast<Game*>(p)->*func)(cur_se);
	},
			boost::asio::placeholders::error, this)*/
		boost::bind(&Session::receive_handler, this, p, func, id, boost::asio::placeholders::error)
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

Godata& Session::get_msg() {
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

void Session::send_handler(const boost::system::error_code& ec)
{
	update_error(ec);
	if (ec)return;
}

void Session::receive_handler(void* p, game_func func, int id, const boost::system::error_code& ec)
{
	update_error(ec);
	if (ec)return;
	if (!game_alive[id])return;
	//(reinterpret_cast<Game*>(p)->*func)(this);
}
