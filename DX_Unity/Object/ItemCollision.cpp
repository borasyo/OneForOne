//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ItemCollision.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "ItemCollision.h"
#include "../Library/DirectX/DirectSound.h"
#include "ItemFogParent.h"

ItemCollision::ItemCollision() {
	m_Name = "ItemCollision";
	m_pHierarchy = Hierarchy::Create();
	pParent = m_pHierarchy->CreateObject(new ItemFogParent);
	
	for( int i = 0; i < 60; i++ ) {
		pParent->CreateChild();
	}
	for( auto Ite = pParent->GetChild()->begin(); Ite != pParent->GetChild()->end(); Ite++ )
		(*Ite)->SetActive(false);
}

ItemCollision::~ItemCollision() {
	
}

bool ItemCollision::Start() {
	m_nGetItemCnt = 0;
	return true;
}

// アイテムを何個とったか
int* ItemCollision::GetInt(){
	return &m_nGetItemCnt;
}

void ItemCollision::LateUpdate(){
	
	GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
	GameObject* pItem = m_pHierarchy->FindWithName("ItemParent");

	if( pPlayer && pItem ) {

		for( auto Ite = pItem->GetChild()->begin(); Ite != pItem->GetChild()->end(); Ite++ ) {
			if( m_Collision.CollisionOBBandOBB( pPlayer, (*Ite) ) ) {

				(*Ite)->SetLife( -999 );
				PlaySound(ITEMGET);
				
				// エフェクト
				for( int i = 0; i < 20; i++ ) {
 					GameObject* pFog = pParent->CreateChild();
					pFog->ReInit();
					*(pFog->GetPosition()) = *((*Ite)->GetPosition());
					*(pFog->GetRotation()) = *((*Ite)->GetPosition());
					pFog->Start();
					pFog->FreeFunction();
				}

				// カウント増加
				m_nGetItemCnt ++;
#if _DEBUG
				std::cout << "ItemCnt" << m_nGetItemCnt << std::endl;
#endif
			}
		}
	}
}
