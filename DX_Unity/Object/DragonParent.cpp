//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [DragonParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "DragonParent.h"

DragonParent::DragonParent() {
	m_Name = "DragonParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

DragonParent::~DragonParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	DragonChild.erase(DragonChild.begin(),DragonChild.end());
}

// 
GameObject* DragonParent::CreateChild( float fAtackLevel ){

	auto Ite = DragonChild.begin();
	for( ; Ite != DragonChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので再使用
		(*Ite)->Start(fAtackLevel);

		break;
	}
	// 枠の余りがないので仕方なくnewする
	if( Ite == DragonChild.end() ) {
		Dragon* pObj = new Dragon;
		pObj->SetParent(this);
		DragonChild.push_back(pObj);
		pObj->Start(fAtackLevel);
		
#if _DEBUG
		std::cout << DragonChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// 更新描画
void DragonParent::Update(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		/*if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			continue;
		}*/

		(*Ite)->Update();
	}
}


void DragonParent::FastDraw(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		/*if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			continue;
		}*/

		(*Ite)->FastDraw();
	}
}