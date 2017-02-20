//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [NearAtackAnimationParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "NearAtackAnimationParent.h"

NearAtackAnimationParent::NearAtackAnimationParent() {
	m_Name = "NearAtackAnimationParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

NearAtackAnimationParent::~NearAtackAnimationParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	NearAtackAnimationChild.erase(NearAtackAnimationChild.begin(),NearAtackAnimationChild.end());
}

// 
GameObject* NearAtackAnimationParent::CreateChild(){

	auto Ite = NearAtackAnimationChild.begin();
	for( ; Ite != NearAtackAnimationChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂ōĎg�p
		(*Ite)->ReInit();
		//(*Ite)->Start();

		break;
	}
	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == NearAtackAnimationChild.end() ) {
		NearAtackAnimation* pObj = new NearAtackAnimation;
		pObj->SetParent(this);
		NearAtackAnimationChild.push_back(pObj);
		//pObj->Start();
		
#if _DEBUG
		std::cout << NearAtackAnimationChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// �X�V�`��
void NearAtackAnimationParent::Update(){
	
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

void NearAtackAnimationParent::Draw(){
	
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