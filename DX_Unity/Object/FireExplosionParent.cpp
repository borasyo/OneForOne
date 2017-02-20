//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [FireExplosionParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "FireExplosionParent.h"

FireExplosionParent::FireExplosionParent() {
	m_Name = "FireExplosionParent";
	m_Tag = "Parent";
}

FireExplosionParent::~FireExplosionParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	FireExplosionChild.erase(FireExplosionChild.begin(),FireExplosionChild.end());
}

// 
GameObject* FireExplosionParent::CreateChild(){

	auto Ite = FireExplosionChild.begin();
	for( ; Ite != FireExplosionChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂ōĎg�p
		(*Ite)->Start();

		break;
	}
	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == FireExplosionChild.end() ) {
		FireExplosion* pObj = new FireExplosion;
		pObj->SetParent(this);
		FireExplosionChild.push_back(pObj);
		pObj->Start();
		
#if _DEBUG
		std::cout << "FireExplosion" << FireExplosionChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// �X�V�`��
void FireExplosionParent::Update(){
	
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

void FireExplosionParent::Draw(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			continue;
		}

		(*Ite)->Draw();
	}
}
