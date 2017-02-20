//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [BulletFogParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "BulletFogParent.h"

BulletFogParent::BulletFogParent() {
	m_Name = "BulletFogParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

BulletFogParent::~BulletFogParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	BulletFogChild.erase(BulletFogChild.begin(),BulletFogChild.end());
}

// 
GameObject* BulletFogParent::CreateChild(D3DXCOLOR FogCol, float fMove, float fDeathSize){

	auto Ite = BulletFogChild.begin();
	for( ; Ite != BulletFogChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので再使用
		(*Ite)->Start(FogCol,fMove,fDeathSize);

		break;
	}
	// 枠の余りがないので仕方なくnewする
	if( Ite == BulletFogChild.end() ) {
		BulletFog* pObj = new BulletFog;
		pObj->SetParent(this);
		BulletFogChild.push_back(pObj);
		pObj->Start(FogCol,fMove,fDeathSize);
		
#if _DEBUG
	//	std::cout << "BulletFog" << BulletFogChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// 更新描画
void BulletFogParent::Update(){
	
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

void BulletFogParent::Draw(){
	
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