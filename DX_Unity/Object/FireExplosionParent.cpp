//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [FireExplosionParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "FireExplosionParent.h"

FireExplosionParent::FireExplosionParent() {
	m_Name = "FireExplosionParent";
	m_Tag = "Parent";
}

FireExplosionParent::~FireExplosionParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	FireExplosionChild.erase(FireExplosionChild.begin(),FireExplosionChild.end());
}

// 
GameObject* FireExplosionParent::CreateChild(){

	auto Ite = FireExplosionChild.begin();
	for( ; Ite != FireExplosionChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので再使用
		(*Ite)->Start();

		break;
	}
	// 枠の余りがないので仕方なくnewする
	if( Ite == FireExplosionChild.end() ) {
		FireExplosion* pObj = new FireExplosion;
		pObj->SetParent(this);
		FireExplosionChild.push_back(pObj);
		pObj->Start();
		
#if _DEBUG
		std::cout << "FireExplosion" << FireExplosionChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// 更新描画
void FireExplosionParent::Update(){
	
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

void FireExplosionParent::Draw(){
	
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
