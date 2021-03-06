#pragma once
#include"_public.h"
/*
head : 
*/
using namespace std;
class Godata {
			friend class Session;
			friend class Game;
private:
			//数据本体，包括头字节和后续字节
			char m_msg[MSG_LENTH];
public:
			Godata() {};

			Godata(char, const char*);

			Godata& operator=(const Godata&);

			//转换到OTHER头，例如{GODATA_HEAD_SET} -> {GODATA_HEAD_OTHER_SET}，返回BOOL
			int transform_to_other();

			//改变头字节，参数{GODATA_HEAD_00}
			int change_head(int);

			//改变数据报，参数为字符串
			int change_data(char*);

			//改变数据报，参数为字符串
			//int change_data(string&);

			//改变数据报，参数为单字符
			int change_data(char);

			//返回头字节
			char get_head();

			//返回数据报指针
			char* get_data();

			//返回数据整体的指针
			char* msg_ptr();
private:
			//返回BOOL，为真时表示头字节拥有对应OTHER头
			int have_other();

};