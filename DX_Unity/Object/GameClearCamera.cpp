//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameClearCamera.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "GameClearCamera.h"
#include "GameClear.h"
#include "../Library/DirectX/DirectSound.h"

// --- �萔
const float fRotSpeed = Pai*2/(nGameClearTime*2);

GameClearCamera::GameClearCamera() {
	m_Name = "GameClearCamera";
	
	// �����蔻��͍s��Ȃ�
	m_bCollision = false;

	m_fAngle = 0.0f;
	m_nCnt = 0;

	// �����_��Boss�ɐݒ�
	m_pBoss = Hierarchy::Create()->FindWithTag("Boss");
	*(m_ObjectCamera.GetLookatPt()) = *(m_pBoss->GetPosition());
	m_Pos = *(m_pBoss->GetPosition());
	
	// ��������ʒu
	m_Position.y = m_pBoss->GetCollisionCubePlusSize().y*5.0f;
	if( m_Position.y < 15.0f )
		m_Position.y = 15.0f;
	m_fDistance = m_pBoss->GetCollisionCubePlusSize().x*8.0f + m_pBoss->GetCollisionCubePlusSize().z*8.0f;
	if( m_fDistance < 20.0f )
		m_fDistance = 20.0f;

	if( m_pBoss->GetName() == "Dragon" )
		m_fDistance = 20.0f;

	// �_�E���L���X�g���ĕێ�
	BulletFogParent Fog;
	m_pFog = Fog.GetDownCastClass( Hierarchy::Create()->FindWithName("BulletFogParent") );

	// ��
	PlaySound(GAMECLEAREFFECT);
}

GameClearCamera::~GameClearCamera() {
	
}

void GameClearCamera::Update() {

	// Fog����
	/*if( m_nCnt <= 300 ) {
		for( int i = 0; i < m_nCnt/10; i++ ) {
			GameObject* pObj;	
			pObj = m_pFog->CreateChild( D3DXCOLOR( 0.1f,0.015f,0.1f,0.5f ), rand()%300*0.01f );
			*(pObj->GetPosition()) = *(m_pBoss->GetPosition());
			*(pObj->GetScale()) = D3DXVECTOR3( m_nCnt/10,m_nCnt/10,m_nCnt/10 );
		}
	}*/

	// �J�E���g����
	m_nCnt++;

	if( m_nCnt == 420 ) {
		
		Hierarchy* pHierarchy = Hierarchy::Create();

		std::list<GameObject*>* pAllObj = pHierarchy->FindAllObject();
		for( auto Ite = pAllObj->begin(); Ite != pAllObj->end(); Ite++ ) {

			// Boss������
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

			// Fog����
			//if( (*Ite)->GetName() == "GameClearFogParent" )
			//	(*Ite)->SetActive(false);

			// Player�Ďn��
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