//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [CleaveImpactParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "CleaveImpactParent.h"

CleaveImpactParent::CleaveImpactParent() {
	m_Name = "CleaveImpactParent";
	m_Tag = "Parent";
}

CleaveImpactParent::~CleaveImpactParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	CleaveImpactChild.erase(CleaveImpactChild.begin(),CleaveImpactChild.end());
}

// 
GameObject* CleaveImpactParent::CreateChild(){

	auto Ite = CleaveImpactChild.begin();
	for( ; Ite != CleaveImpactChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂ōĎg�p
		//(*Ite)->Start();

		break;
	}
	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == CleaveImpactChild.end() ) {
		CleaveImpact* pObj = new CleaveImpact;
		pObj->SetParent(this);
		CleaveImpactChild.push_back(pObj);
		//pObj->Start();
		
#if _DEBUG
		std::cout << "CleaveImpact" << CleaveImpactChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// �X�V�`��
void CleaveImpactParent::Update(){
	
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

void CleaveImpactParent::Draw(){
	
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