//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Time.cpp]
// author : 大洞祥太
//
// 時間経過を保存する。
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

	// 1F経過
	m_nTime ++;
}

int* Time::GetInt(){
	return &m_nTime;
}