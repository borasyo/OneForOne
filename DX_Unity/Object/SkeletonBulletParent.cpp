//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [SkeltonBulletParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "SkeletonBulletParent.h"

SkeltonBulletParent::SkeltonBulletParent() {
	m_Name = "SkeltonBulletParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

SkeltonBulletParent::~SkeltonBulletParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	SkeltonBulletChild.erase(SkeltonBulletChild.begin(),SkeltonBulletChild.end());
}

// 
GameObject* SkeltonBulletParent::CreateChild(){

	auto Ite = SkeltonBulletChild.begin();
	for( ; Ite != SkeltonBulletChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂ōĎg�p
		//(*Ite)->Start();

		break;
	}
	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == SkeltonBulletChild.end() ) {
		SkeltonBullet* pObj = new SkeltonBullet;
		pObj->SetParent(this);
		SkeltonBulletChild.push_back(pObj);
		//pObj->Start();
		
#if _DEBUG
		std::cout << "SkeltonBullet" << SkeltonBulletChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// �X�V�`��
void SkeltonBulletParent::Update(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			(*Ite)->FindChild("Shadow")->SetLife(-999);
			continue;
		}

		(*Ite)->Update();
	}
}

void SkeltonBulletParent::Draw(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			(*Ite)->FindChild("Shadow")->SetLife(-999);
			continue;
		}

		(*Ite)->Draw();
	}
}