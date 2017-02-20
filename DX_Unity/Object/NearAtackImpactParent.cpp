//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [NearAtackImpactParent.cpp]
// author : 大洞祥太
//
// ・Start関数で引数が必要な場合は、これをダウンキャストして、保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "NearAtackImpactParent.h"

NearAtackImpactParent::NearAtackImpactParent() {
	m_Name = "NearAtackImpactParent";
	m_Tag = "Parent";
	
	if( m_Child.empty() ) {
		for( int i = 0; i < 100; i++ ){
			CreateChild();
		}
	
		for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
		}
	}
}

NearAtackImpactParent::~NearAtackImpactParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	NearAtackImpactChild.erase(NearAtackImpactChild.begin(),NearAtackImpactChild.end());
}

// 
GameObject* NearAtackImpactParent::CreateChild(){

	auto Ite = NearAtackImpactChild.begin();
	for( ; Ite != NearAtackImpactChild.end(); Ite++ ) {

		// 今使っていないか
		if( (*Ite)->GetActive() )
			continue;

		// 使ってない物があったので再使用
		//(*Ite)->Start();

		break;
	}
	// 枠の余りがないので仕方なくnewする
	if( Ite == NearAtackImpactChild.end() ) {
		NearAtackImpact* pObj = new NearAtackImpact;
		pObj->SetParent(this);
		NearAtackImpactChild.push_back(pObj);
		//pObj->Start();
		
#if _DEBUG
		std::cout << "NearAtackImpact" << NearAtackImpactChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

// 更新描画
void NearAtackImpactParent::Update(){
	
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

void NearAtackImpactParent::Draw(){
	
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