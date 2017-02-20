//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Empty.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Empty.h"

Empty::Empty( std::string Name ){
	m_Name = Name;
}

// 全ての子オブジェクトを削除
Empty::~Empty(){
	
	/*for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) 
		delete *Ite;
	m_Child.erase(m_Child.begin(),m_Child.end());*/
}

/*void Empty::Update(){
	
	// 更新
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		(*Ite)->Update();
	}
}

void Empty::Draw(){
	
	// 更新
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		(*Ite)->Draw();
	}
}*/