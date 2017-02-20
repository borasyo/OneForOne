//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [MeteoParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "MeteoParent.h"

MeteoParent::MeteoParent() {
	m_Name = "MeteoParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

MeteoParent::~MeteoParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	MeteoChild.erase(MeteoChild.begin(),MeteoChild.end());
}

// 
GameObject* MeteoParent::CreateChild(){

	auto Ite = MeteoChild.begin();
	for( ; Ite != MeteoChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂Ŏg�p
		(*Ite)->SetActive(true);
		(*Ite)->Start();

		break;
	}
	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == MeteoChild.end() ) {
		Meteo* pObj = new Meteo;
		pObj->SetParent(this);
		MeteoChild.push_back(pObj);
		pObj->Start();

#if _DEBUG
		std::cout << "Meteo" << MeteoChild.size() << std::endl;
#endif

		return pObj;
	}

	return *Ite;
}

// �X�V�`��
void MeteoParent::Update(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			(*Ite)->FindChild("Shadow")->SetActive(false);
			//(*Ite)->FindChild("Shadow")->SetLife(-1);
			continue;
		}

		(*Ite)->Update();
	}
}

void MeteoParent::Draw(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			(*Ite)->FindChild("Shadow")->SetActive(false);
			//(*Ite)->FindChild("Shadow")->SetLife(-1);
			continue;
		}

		(*Ite)->Draw();
	}
}
