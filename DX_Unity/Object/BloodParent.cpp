//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [BloodParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "BloodParent.h"

BloodParent::BloodParent() {
	m_Name = "BloodParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

BloodParent::~BloodParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	BloodChild.erase(BloodChild.begin(),BloodChild.end());
}

// 
GameObject* BloodParent::CreateChild(D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos){

	auto Ite = BloodChild.begin();
	for( ; Ite != BloodChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂ōĎg�p
		(*Ite)->Start(MyselfPos, OpponentPos);

		break;
	}
	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == BloodChild.end() ) {
		Blood* pObj = new Blood;
		pObj->SetParent(this);
		BloodChild.push_back(pObj);
		pObj->Start(MyselfPos, OpponentPos);
		
#if _DEBUG
		std::cout << "Blood" << BloodChild.size() << std::endl;
#endif
		return pObj;
	}

	return *Ite;
}

// �X�V�`��
void BloodParent::Update(){
	
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

void BloodParent::Draw(){
	
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