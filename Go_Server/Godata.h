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
			//���ݱ��壬����ͷ�ֽںͺ����ֽ�
			char m_msg[MSG_LENTH];
public:
			Godata() {};

			Godata(char, const char*);

			Godata& operator=(const Godata&);

			//ת����OTHERͷ������{GODATA_HEAD_SET} -> {GODATA_HEAD_OTHER_SET}������BOOL
			int transform_to_other();

			//�ı�ͷ�ֽڣ�����{GODATA_HEAD_00}
			int change_head(int);

			//�ı����ݱ�������Ϊ�ַ���
			int change_data(char*);

			//�ı����ݱ�������Ϊ�ַ���
			//int change_data(string&);

			//�ı����ݱ�������Ϊ���ַ�
			int change_data(char);

			//����ͷ�ֽ�
			char get_head();

			//�������ݱ�ָ��
			char* get_data();

			//�������������ָ��
			char* msg_ptr();
private:
			//����BOOL��Ϊ��ʱ��ʾͷ�ֽ�ӵ�ж�ӦOTHERͷ
			int have_other();

};