//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [BloodParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "BloodParent.h"

BloodParent::BloodParent() {
	m_Name = "BloodParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

BloodParent::~BloodParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	BloodChild.erase(BloodChild.begin(),BloodChild.end());
}

// 
GameObject* BloodParent::CreateChild(D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos){

	auto Ite = BloodChild.begin();
	for( ; Ite != BloodChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので再使用
		(*Ite)->Start(MyselfPos, OpponentPos);

		break;
	}
	// 枠の余りがないので仕方なくnewする
	if( Ite == BloodChild.end() ) {
		Blood* pObj = new Blood;
		pObj->SetParent(this);
		BloodChild.push_back(pObj);
		pObj->Start(MyselfPos, OpponentPos);
		
#if _DEBUG
		std::cout << "Blood" << BloodChild.size() << std::endl;
#endif
		return pObj;
	}

	return *Ite;
}

// 更新描画
void BloodParent::Update(){
	
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

void BloodParent::Draw(){
	
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