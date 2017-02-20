//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [DragonMeteoParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "DragonMeteoParent.h"

DragonMeteoParent::DragonMeteoParent() {
	m_Name = "DragonMeteoParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

DragonMeteoParent::~DragonMeteoParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	DragonMeteoChild.erase(DragonMeteoChild.begin(),DragonMeteoChild.end());
}

// 
GameObject* DragonMeteoParent::CreateChild(){

	auto Ite = DragonMeteoChild.begin();
	for( ; Ite != DragonMeteoChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので使用
		(*Ite)->SetActive(true);
		(*Ite)->Start();

		break;
	}
	// 枠の余りがないので仕方なくnewする
	if( Ite == DragonMeteoChild.end() ) {
		DragonMeteo* pObj = new DragonMeteo;
		pObj->SetParent(this);
		DragonMeteoChild.push_back(pObj);
		pObj->Start();

#if _DEBUG
		std::cout << "DragonMeteo" << DragonMeteoChild.size() << std::endl;
#endif

		return pObj;
	}

	return *Ite;
}

// 更新描画
void DragonMeteoParent::Update(){
	
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

void DragonMeteoParent::Draw(){
	
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