//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [FireParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "FireParent.h"

FireParent::FireParent() {
	m_Name = "DragonFireParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

FireParent::~FireParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	FireChild.erase(FireChild.begin(),FireChild.end());
}

// 
GameObject* FireParent::CreateChild(){

	auto Ite = FireChild.begin();
	for( ; Ite != FireChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので再使用
		//(*Ite)->Start();

		break;
	}

	// 枠の余りがないので仕方なくnewする
	if( Ite == FireChild.end() ) {
		Fire* pObj = new Fire;
		pObj->SetParent(this);
		FireChild.push_back(pObj);
		//pObj->Start();
		
#if _DEBUG
		std::cout << FireChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// 更新描画
void FireParent::Update(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			(*Ite)->FindChild("Shadow")->SetLife(-1);
			continue;
		}

		(*Ite)->Update();
	}
}

void FireParent::Draw(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			(*Ite)->FindChild("Shadow")->SetLife(-1);
			continue;
		}

		(*Ite)->Draw();
	}
}