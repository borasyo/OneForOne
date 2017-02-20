//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [NearAtackImpactParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "NearAtackImpactParent.h"

NearAtackImpactParent::NearAtackImpactParent() {
	m_Name = "NearAtackImpactParent";
	m_Tag = "Parent";
	
	if( m_Child.empty() ) {
		for( int i = 0; i < 100; i++ ){
			CreateChild();
		}
	
		for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
		}
	}
}

NearAtackImpactParent::~NearAtackImpactParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	NearAtackImpactChild.erase(NearAtackImpactChild.begin(),NearAtackImpactChild.end());
}

// 
GameObject* NearAtackImpactParent::CreateChild(){

	auto Ite = NearAtackImpactChild.begin();
	for( ; Ite != NearAtackImpactChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂ōĎg�p
		//(*Ite)->Start();

		break;
	}
	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == NearAtackImpactChild.end() ) {
		NearAtackImpact* pObj = new NearAtackImpact;
		pObj->SetParent(this);
		NearAtackImpactChild.push_back(pObj);
		//pObj->Start();
		
#if _DEBUG
		std::cout << "NearAtackImpact" << NearAtackImpactChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// �X�V�`��
void NearAtackImpactParent::Update(){
	
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

void NearAtackImpactParent::Draw(){
	
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