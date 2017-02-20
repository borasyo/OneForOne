//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [PlayerFogParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "PlayerFogParent.h"

PlayerFogParent::PlayerFogParent() {
	m_Name = "PlayerFogParent";
	m_Tag = "Parent";
}

PlayerFogParent::~PlayerFogParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	PlayerFogChild.erase(PlayerFogChild.begin(),PlayerFogChild.end());
}

// 
GameObject* PlayerFogParent::CreateChild(){

	auto Ite = PlayerFogChild.begin();
	for( ; Ite != PlayerFogChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので再使用
		//(*Ite)->Start();

		break;
	}
	// 枠の余りがないので仕方なくnewする
	if( Ite == PlayerFogChild.end() ) {
		PlayerFog* pObj = new PlayerFog;
		pObj->SetParent(this);
		PlayerFogChild.push_back(pObj);
		//pObj->Start();
		
#if _DEBUG
		std::cout << "PlayerFog" << PlayerFogChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// 更新描画
void PlayerFogParent::Update(){
	
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

void PlayerFogParent::Draw(){
	
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