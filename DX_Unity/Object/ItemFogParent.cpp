//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [ItemFogParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "ItemFogParent.h"

ItemFogParent::ItemFogParent() {
	m_Name = "ItemFogParent";
	m_Tag = "Parent";
}

ItemFogParent::~ItemFogParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	ItemFogChild.erase(ItemFogChild.begin(),ItemFogChild.end());
}

// 
GameObject* ItemFogParent::CreateChild(){

	if( !m_bFlg )
		m_bFlg = true;

	auto Ite = ItemFogChild.begin();
	for( ; Ite != ItemFogChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので再使用
		//(*Ite)->Start();

		break;
	}
	// 枠の余りがないので仕方なくnewする
	if( Ite == ItemFogChild.end() ) {
		ItemFog* pObj = new ItemFog;
		pObj->SetParent(this);
		ItemFogChild.push_back(pObj);
		//pObj->Start();
		
#if _DEBUG
	//	std::cout << "ItemFog" << ItemFogChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

bool ItemFogParent::Start(){
	
	m_bFlg = false;
	m_nCnt = 0;
	return true;
}

// 更新描画
void ItemFogParent::Update(){

	if( m_bFlg ) {

		m_nCnt ++;

		if( m_nCnt >= 60 ) {

			GameObject* pPlayer = Hierarchy::Create()->FindWithName("Player");

			if( pPlayer->GetLife() > 0 ) {
				pPlayer->SetLife(5);
				if( pPlayer->GetLife() > 21 ) { // 例外処理
					pPlayer->SetLife( 21 - pPlayer->GetLife() );
				}
				*(pPlayer->GetFloat()) += 50.0f;
				if( *(pPlayer->GetFloat()) > 100.0f )
					*(pPlayer->GetFloat()) = 100.0f;
			}

			m_nCnt = 0;
			m_bFlg = false;
		}
	}
	
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

void ItemFogParent::Draw(){
	
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