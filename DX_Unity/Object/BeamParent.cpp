//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [BeamParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "BeamParent.h"

BeamParent::BeamParent() {
	m_Name = "BeamParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

BeamParent::~BeamParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	BeamChild.erase(BeamChild.begin(),BeamChild.end());
}

// 
GameObject* BeamParent::CreateChild(D3DXCOLOR Color, D3DXVECTOR3 Scale, bool bAdd ){

	auto Ite = BeamChild.begin();
	for( ; Ite != BeamChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので再使用
		(*Ite)->Start(Color,Scale,bAdd);

		break;
	}
	// 枠の余りがないので仕方なくnewする
	if( Ite == BeamChild.end() ) {
		Beam* pObj = new Beam;
		pObj->SetParent(this);
		BeamChild.push_back(pObj);
		pObj->Start(Color,Scale,bAdd);
		
#if _DEBUG
		std::cout << "Beam" << BeamChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// 更新描画
void BeamParent::Update(){

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

void BeamParent::Draw(){
	
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
