//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Time.cpp]
// author : �哴�ˑ�
//
// ���Ԍo�߂�ۑ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Time.h"

Time::Time() {
	m_Name = "Time";
}

Time::~Time() {
	
}

bool Time::Start(){

	m_nTime = 0;

	return true;
}

void Time::Update(){

	// 1F�o��
	m_nTime ++;
}

int* Time::GetInt(){
	return &m_nTime;
}