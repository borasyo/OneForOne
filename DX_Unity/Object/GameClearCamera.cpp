//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameClearCamera.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "GameClearCamera.h"
#include "GameClear.h"
#include "../Library/DirectX/DirectSound.h"

// --- 定数
const float fRotSpeed = Pai*2/(nGameClearTime*2);

GameClearCamera::GameClearCamera() {
	m_Name = "GameClearCamera";
	
	// 当たり判定は行わない
	m_bCollision = false;

	m_fAngle = 0.0f;
	m_nCnt = 0;

	// 注視点をBossに設定
	m_pBoss = Hierarchy::Create()->FindWithTag("Boss");
	*(m_ObjectCamera.GetLookatPt()) = *(m_pBoss->GetPosition());
	m_Pos = *(m_pBoss->GetPosition());
	
	// 見下げる位置
	m_Position.y = m_pBoss->GetCollisionCubePlusSize().y*5.0f;
	if( m_Position.y < 15.0f )
		m_Position.y = 15.0f;
	m_fDistance = m_pBoss->GetCollisionCubePlusSize().x*8.0f + m_pBoss->GetCollisionCubePlusSize().z*8.0f;
	if( m_fDistance < 20.0f )
		m_fDistance = 20.0f;

	if( m_pBoss->GetName() == "Dragon" )
		m_fDistance = 20.0f;

	// ダウンキャストして保持
	BulletFogParent Fog;
	m_pFog = Fog.GetDownCastClass( Hierarchy::Create()->FindWithName("BulletFogParent") );

	// 音
	PlaySound(GAMECLEAREFFECT);
}

GameClearCamera::~GameClearCamera() {
	
}

void GameClearCamera::Update() {

	// Fog生成
	/*if( m_nCnt <= 300 ) {
		for( int i = 0; i < m_nCnt/10; i++ ) {
			GameObject* pObj;	
			pObj = m_pFog->CreateChild( D3DXCOLOR( 0.1f,0.015f,0.1f,0.5f ), rand()%300*0.01f );
			*(pObj->GetPosition()) = *(m_pBoss->GetPosition());
			*(pObj->GetScale()) = D3DXVECTOR3( m_nCnt/10,m_nCnt/10,m_nCnt/10 );
		}
	}*/

	// カウント増加
	m_nCnt++;

	if( m_nCnt == 420 ) {
		
		Hierarchy* pHierarchy = Hierarchy::Create();

		std::list<GameObject*>* pAllObj = pHierarchy->FindAllObject();
		for( auto Ite = pAllObj->begin(); Ite != pAllObj->end(); Ite++ ) {

			// Bossを消す
			if( (*Ite)->GetName() == "Dragon" ) {
				(*Ite)->SetActive(false);
				for( auto Child = (*Ite)->GetChild()->begin(); Child != (*Ite)->GetChild()->end(); Child ++ )
					(*Child)->SetActive(false);
			}

			if( (*Ite)->GetName() == "Devil" ) {
				(*Ite)->SetActive(false);
				for( auto Child = (*Ite)->GetChild()->begin(); Child != (*Ite)->GetChild()->end(); Child ++ )
					(*Child)->SetActive(false);
			}

			if( (*Ite)->GetName() == "Wizard" ) {
				(*Ite)->SetActive(false);
				for( auto Child = (*Ite)->GetChild()->begin(); Child != (*Ite)->GetChild()->end(); Child ++ )
					(*Child)->SetActive(false);
			}
		}
	}

	if( m_nCnt > nGameClearTime*1.5f ) {
		Hierarchy* pHierarchy = Hierarchy::Create();

		std::list<GameObject*>* pAllObj = pHierarchy->FindAllObject();
		for( auto Ite = pAllObj->begin(); Ite != pAllObj->end(); Ite++ ) {

			// Fog消す
			//if( (*Ite)->GetName() == "GameClearFogParent" )
			//	(*Ite)->SetActive(false);

			// Player再始動
			if( (*Ite)->GetName() == "PlayerCamera" )
				(*Ite)->SetActive(true);
		}

		pHierarchy->CreateObject(new GameClear)->Start();
		m_nLife = 0;
		StopSound(GAMECLEAREFFECT);
		*(pHierarchy->FindWithName("PlayerCamera")->GetBool()) = false; 
	}
	
	m_Position.x = m_Pos.x + cosf(m_fAngle)*m_fDistance;
	m_Position.z = m_Pos.z + sinf(m_fAngle)*m_fDistance;
	
	m_fAngle += fRotSpeed;
	if( Pai*2 <= m_fAngle )
		m_fAngle -= Pai*2;
	else if( 0.f >= m_fAngle )
		m_fAngle += Pai*2;
}

void GameClearCamera::Draw(){
	m_ObjectCamera.Set(m_Position);
}