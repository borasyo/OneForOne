//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [SkeltonCorpsParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "SkeltonCorpsParent.h"

SkeltonCorpsParent::SkeltonCorpsParent() {
	m_Name = "SkeltonCorpsParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

SkeltonCorpsParent::~SkeltonCorpsParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	SkeltonCorpsChild.erase(SkeltonCorpsChild.begin(),SkeltonCorpsChild.end());
}

// 
GameObject* SkeltonCorpsParent::CreateChild(){

	auto Ite = SkeltonCorpsChild.begin();
	for( ; Ite != SkeltonCorpsChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂ōĎg�p
		(*Ite)->Start();

		break;
	}
	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == SkeltonCorpsChild.end() ) {
		SkeltonCorps* pObj = new SkeltonCorps;
		pObj->SetParent(this);
		SkeltonCorpsChild.push_back(pObj);
		pObj->Start(); 

#if _DEBUG
		std::cout << "SkeltonBullet" << SkeltonCorpsChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// �X�V�`��
void SkeltonCorpsParent::Update(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			continue;
		}

		(*Ite)->Update();
	}
}

void SkeltonCorpsParent::FastDraw(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			continue;
		}

		(*Ite)->FastDraw();
	}
}