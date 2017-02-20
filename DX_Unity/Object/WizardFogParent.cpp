//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [WizardFogParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "WizardFogParent.h"

WizardFogParent::WizardFogParent() {
	m_Name = "WizardFogParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

WizardFogParent::~WizardFogParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	WizardFogChild.erase(WizardFogChild.begin(),WizardFogChild.end());
}

// 
GameObject* WizardFogParent::CreateChild(){

	auto Ite = WizardFogChild.begin();
	for( ; Ite != WizardFogChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂ōĎg�p
		//(*Ite)->Start();

		break;
	}
	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == WizardFogChild.end() ) {
		WizardFog* pObj = new WizardFog;
		pObj->SetParent(this);
		WizardFogChild.push_back(pObj);
		//->Start();
		
#if _DEBUG
		std::cout << "WizardFog" << WizardFogChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// �X�V�`��
void WizardFogParent::Update(){
	
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

void WizardFogParent::Draw(){
	
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