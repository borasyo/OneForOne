//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Empty.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Empty.h"

Empty::Empty( std::string Name ){
	m_Name = Name;
}

// �S�Ă̎q�I�u�W�F�N�g���폜
Empty::~Empty(){
	
	/*for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) 
		delete *Ite;
	m_Child.erase(m_Child.begin(),m_Child.end());*/
}

/*void Empty::Update(){
	
	// �X�V
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		(*Ite)->Update();
	}
}

void Empty::Draw(){
	
	// �X�V
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		(*Ite)->Draw();
	}
}*/