#include"Server.h"

std::bitset<MAX_GAME_COUNT> game_alive;

int main() {
	Server* s = Server::get_instance();
	s->run();
	return 0;
}