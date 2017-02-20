//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [SkeltonCorpsParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "SkeltonCorpsParent.h"

SkeltonCorpsParent::SkeltonCorpsParent() {
	m_Name = "SkeltonCorpsParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

SkeltonCorpsParent::~SkeltonCorpsParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	SkeltonCorpsChild.erase(SkeltonCorpsChild.begin(),SkeltonCorpsChild.end());
}

// 
GameObject* SkeltonCorpsParent::CreateChild(){

	auto Ite = SkeltonCorpsChild.begin();
	for( ; Ite != SkeltonCorpsChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので再使用
		(*Ite)->Start();

		break;
	}
	// 枠の余りがないので仕方なくnewする
	if( Ite == SkeltonCorpsChild.end() ) {
		SkeltonCorps* pObj = new SkeltonCorps;
		pObj->SetParent(this);
		SkeltonCorpsChild.push_back(pObj);
		pObj->Start(); 

#if _DEBUG
		std::cout << "SkeltonBullet" << SkeltonCorpsChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// 更新描画
void SkeltonCorpsParent::Update(){
	
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

void SkeltonCorpsParent::FastDraw(){
	
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