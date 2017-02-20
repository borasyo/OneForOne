//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [WizardImpactParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "WizardImpactParent.h"

WizardImpactParent::WizardImpactParent() {
	m_Name = "WizardImpactParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

WizardImpactParent::~WizardImpactParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	WizardImpactChild.erase(WizardImpactChild.begin(),WizardImpactChild.end());
}

// 
GameObject* WizardImpactParent::CreateChild(){

	auto Ite = WizardImpactChild.begin();
	for( ; Ite != WizardImpactChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので再使用
		//(*Ite)->Start();

		break;
	}
	// 枠の余りがないので仕方なくnewする
	if( Ite == WizardImpactChild.end() ) {
		WizardImpact* pObj = new WizardImpact;
		pObj->SetParent(this);
		WizardImpactChild.push_back(pObj);
		//pObj->Start();
		
#if _DEBUG
		std::cout << "WizardImpact" << WizardImpactChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// 更新描画
void WizardImpactParent::FastUpdate(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			continue;
		}

		(*Ite)->FastUpdate();
	}
}

void WizardImpactParent::Update(){
	
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

void WizardImpactParent::LateUpdate(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			continue;
		}

		(*Ite)->LateUpdate();
	}
}

void WizardImpactParent::FastDraw(){
	
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

void WizardImpactParent::Draw(){
	
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

void WizardImpactParent::LateDraw(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			continue;
		}

		(*Ite)->LateDraw();
	}
}