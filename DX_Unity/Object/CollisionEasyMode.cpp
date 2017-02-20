//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CollisionEasyMode.cpp]
// author : �哴�ˑ�
//
// ��GetCollisionCubePlusSize�͍�����W�n�ɂ����鎲�̃v���X�̌����̑傫��
// ��GetCollisionCubeMinusSize�͍�����W�n�ɂ����鎲�̃}�C�i�X�̌����̑傫��
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CollisionEasyMode.h"
#include "../Library/Task/SceneManager.h"
#include "../Library/DirectX/DirectSound.h"
#include "FireExplosion.h"
#include "FireExplosionParent.h"
#include "FadeIn.h"

// -- �萔
const float fOutRange = 3.0f; // ����O�ɂ���͈�
//const int nMaxBlood = 3;

// --- �}�N��
#define RANDOM (rand()%10000*0.0001f)

CollisionEasyMode::CollisionEasyMode(){
	m_Name = "CollisionEasyMode";
	m_pHierarchy = Hierarchy::Create();
	m_nMaxBlood = 5;

	BloodParent Obj;
	m_pBloodParent = Obj.GetDownCastClass(m_pHierarchy->CreateObject(new BloodParent));
	for( int i = 0; i < 350; i++ )
		m_pBloodParent->CreateChild( D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0) );
	for( auto Ite = m_pBloodParent->GetChild()->begin(); Ite != m_pBloodParent->GetChild()->end(); Ite++ )
		(*Ite)->SetActive(false);
}

CollisionEasyMode::~CollisionEasyMode(){

}

bool CollisionEasyMode::Start(){
	
	// �{�X�Ƃ��̍U�����擾
	pBoss = m_pHierarchy->FindWithTag("Boss");
	m_pWizardCollision = m_pHierarchy->FindWithName("WizardCollision");

	// �e���擾
	m_pFireExplosionParent = m_pHierarchy->FindWithName("FireExplosionParent");
	m_pNear = m_pHierarchy->FindWithName("NearAtackImpactParent");
	m_pBeamParent = m_pHierarchy->FindWithName("BeamParent");
	m_pFireParent = m_pHierarchy->FindWithName("FireParent");
	pFade = m_pHierarchy->FindWithName("Fade");
	
	return true;
}

void CollisionEasyMode::LateUpdate(){

	// �{�X�擾
	pBoss = m_pHierarchy->FindWithTag("Boss");
	
	// �v���C���[�擾
	GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
	
	// ---- �G�ƕK�E�e�̓����蔻�� ----
	GameObject* pDeathblow = m_pHierarchy->FindWithName("Deathblow");
	if( pDeathblow && pBoss ) {
		if( ( pDeathblow->GetCollisionFlg() && pBoss->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pDeathblow, pBoss ) ) ){
			PlaySound(DEATHBLOWEXPLOSION);
			StopSound(DEATHBLOWSHOT);
			pDeathblow->SetLife(-999);
			pDeathblow->FreeFunction();
			pBoss->SetLife(-2500);
			for( int i = 0; i < 30; i++ )
				CreateBlood( *(pBoss->GetPosition()), RandomPos(*(pBoss->GetPosition())), true );
		}
	}

	// ---- �G�Ɖ������U���̓����蔻�� -----
	for( auto FireIte = m_pFireParent->GetChild()->begin(); FireIte != m_pFireParent->GetChild()->end(); FireIte++ ) {
		if( !(*FireIte)->GetCollisionFlg() ) continue;
		// �{�X�Ƃ̔���
		if( pBoss && pBoss->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pBoss, *FireIte ) ) {
			(*FireIte)->SetLife(-999);
			pBoss->SetLife(-8);
			
			GameObject* pExplosion = m_pFireExplosionParent->CreateChild();
			pExplosion->Start();
			*(pExplosion->GetPosition()) = *((*FireIte)->GetPosition());

			CreateBlood( *(pBoss->GetPosition()), *((*FireIte)->GetPosition()), true );
			*(pPlayer->GetFloat()) += fUpGauge;
			break;
		}
	}
	
	// ---- �G�Ƌߐڂ̓����蔻��
	for( auto NearIte = m_pNear->GetChild()->begin(); NearIte != m_pNear->GetChild()->end(); NearIte++ ) {
		if( !(*NearIte)->GetCollisionFlg() ) continue;
		
		// �{�X�Ƃ̔���
		if( pBoss && pBoss->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pBoss, *NearIte ) ) {
			pBoss->SetLife(-1);
			CreateBlood( *(pBoss->GetPosition()), *((*NearIte)->GetPosition()) );
			*(pPlayer->GetFloat()) += fUpGauge;
			//PlaySound(PLAYERNEARDAMAGE);
		}
	}

	// Boss���S��
	if( pBoss && pBoss->GetLife() <= 0 ) {
		SceneManager::Create()->SetGameClear();
		return;
	}

	// ---- �v���C���[�ƃ{�X�̓����蔻��
	if( pPlayer && pBoss ){
		if( m_Collision.CollisionOBBandOBB( pPlayer, pBoss ) ) {
			pPlayer->ReturnMove(); // �߂�
			pPlayer->ReturnMove(); // �߂�
			pBoss->ReturnMove(); // �߂�
			pBoss->ReturnMove(); // �߂�
		}
	}
	
	// �v���C���[�ƓG�̍U���̓����蔻��
	if( pPlayer && pPlayer->GetCollisionFlg() ) {
		for( auto Ite = m_pWizardCollision->GetChild()->begin(); Ite != m_pWizardCollision->GetChild()->end(); Ite++ ) {
			if( (*Ite)->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pPlayer, *Ite ) ) {
				pPlayer->SetLife(-1);
				PlaySound(PLAYERDAMEGE);
				(*Ite)->SetLife(-999);
				CreateBlood( *(pPlayer->GetPosition()), *((*Ite)->GetPosition()), true );
				if( !pFade->FindChild("FadeIn") ) {
					m_pHierarchy->CreateObject(new FadeIn(10,D3DXCOLOR(0.5f,0,0,0)))->SetParent(pFade);
				}
			}
		}
	}
	
	// ---- �v���C���[�ƃr�[���Ƃ̓����蔻��
	if( pPlayer && pPlayer->GetCollisionFlg() && m_pBeamParent ) {
		for( auto Ite = m_pBeamParent->GetChild()->begin(); Ite != m_pBeamParent->GetChild()->end(); Ite++ ) {
			if( (*Ite)->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pPlayer, *Ite ) ) {
				// �_���[�W����
				pPlayer->SetLife(-1);
				PlaySound(PLAYERDAMEGE);
				CreateBlood( *(pPlayer->GetPosition()), *((*Ite)->GetPosition()), true );
				if( !pFade->FindChild("FadeIn") ) {
					m_pHierarchy->CreateObject(new FadeIn(10,D3DXCOLOR(0.5f,0,0,0)))->SetParent(pFade);
				}
				for( auto BeamIte = m_pBeamParent->GetChild()->begin(); BeamIte != m_pBeamParent->GetChild()->end(); BeamIte++ )
					(*BeamIte)->SetCollisionFlg(false);
				break;
			}
		}
	}
}

void CollisionEasyMode::CreateBlood( D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos, bool bMore ) {

	if( !bMore && rand()%2 == 0 ) {
		m_nMaxBlood = 1;
	}
	else {
		m_nMaxBlood = 0;
	}
	// �o��ʑ�������
	if( bMore )
		m_nMaxBlood = 7;
	
	for( int i = 0; i < m_nMaxBlood; i ++ ) {
		m_pBloodParent->CreateChild( MyselfPos,OpponentPos );
	}
}

D3DXVECTOR3 CollisionEasyMode::RandomPos(D3DXVECTOR3 BossPos){
	
	D3DXVECTOR3 Pos = BossPos;
	Pos.y -= 0.6f;

	switch( rand()%4 ) {
		
	case 0:
		Pos.x += RANDOM;
		Pos.z += RANDOM;
		break;
	case 1:
		Pos.x += RANDOM;
		Pos.z -= RANDOM;
		break;
	case 2:
		Pos.x -= RANDOM;
		Pos.z += RANDOM;
		break;
	case 3:
		Pos.x -= RANDOM;
		Pos.z -= RANDOM;
		break;
	}

	return Pos;
}