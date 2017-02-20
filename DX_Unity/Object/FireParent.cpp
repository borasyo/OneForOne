//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [FireParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "FireParent.h"

FireParent::FireParent() {
	m_Name = "DragonFireParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

FireParent::~FireParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	FireChild.erase(FireChild.begin(),FireChild.end());
}

// 
GameObject* FireParent::CreateChild(){

	auto Ite = FireChild.begin();
	for( ; Ite != FireChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂ōĎg�p
		//(*Ite)->Start();

		break;
	}

	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == FireChild.end() ) {
		Fire* pObj = new Fire;
		pObj->SetParent(this);
		FireChild.push_back(pObj);
		//pObj->Start();
		
#if _DEBUG
		std::cout << FireChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// �X�V�`��
void FireParent::Update(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			(*Ite)->FindChild("Shadow")->SetLife(-1);
			continue;
		}

		(*Ite)->Update();
	}
}

void FireParent::Draw(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			(*Ite)->FindChild("Shadow")->SetLife(-1);
			continue;
		}

		(*Ite)->Draw();
	}
}