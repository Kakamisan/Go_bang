#pragma once

#include"_define.h"

#include<boost\asio.hpp>
#include<boost\enable_shared_from_this.hpp>
#include<boost\bind.hpp>
#include<boost\shared_ptr.hpp>

#include<iostream>
#include<string>
#include<utility>
#include<queue>
#include<mutex>
#include<bitset>

extern std::bitset<MAX_GAME_COUNT> game_alive;