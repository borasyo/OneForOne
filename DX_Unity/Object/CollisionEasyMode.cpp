//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CollisionEasyMode.cpp]
// author : 大洞祥太
//
// ※GetCollisionCubePlusSizeは左手座標系における軸のプラスの向きの大きさ
// ※GetCollisionCubeMinusSizeは左手座標系における軸のマイナスの向きの大きさ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CollisionEasyMode.h"
#include "../Library/Task/SceneManager.h"
#include "../Library/DirectX/DirectSound.h"
#include "FireExplosion.h"
#include "FireExplosionParent.h"
#include "FadeIn.h"

// -- 定数
const float fOutRange = 3.0f; // 判定外にする範囲
//const int nMaxBlood = 3;

// --- マクロ
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
	
	// ボスとその攻撃を取得
	pBoss = m_pHierarchy->FindWithTag("Boss");
	m_pWizardCollision = m_pHierarchy->FindWithName("WizardCollision");

	// 親を取得
	m_pFireExplosionParent = m_pHierarchy->FindWithName("FireExplosionParent");
	m_pNear = m_pHierarchy->FindWithName("NearAtackImpactParent");
	m_pBeamParent = m_pHierarchy->FindWithName("BeamParent");
	m_pFireParent = m_pHierarchy->FindWithName("FireParent");
	pFade = m_pHierarchy->FindWithName("Fade");
	
	return true;
}

void CollisionEasyMode::LateUpdate(){

	// ボス取得
	pBoss = m_pHierarchy->FindWithTag("Boss");
	
	// プレイヤー取得
	GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
	
	// ---- 敵と必殺弾の当たり判定 ----
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

	// ---- 敵と遠距離攻撃の当たり判定 -----
	for( auto FireIte = m_pFireParent->GetChild()->begin(); FireIte != m_pFireParent->GetChild()->end(); FireIte++ ) {
		if( !(*FireIte)->GetCollisionFlg() ) continue;
		// ボスとの判定
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
	
	// ---- 敵と近接の当たり判定
	for( auto NearIte = m_pNear->GetChild()->begin(); NearIte != m_pNear->GetChild()->end(); NearIte++ ) {
		if( !(*NearIte)->GetCollisionFlg() ) continue;
		
		// ボスとの判定
		if( pBoss && pBoss->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pBoss, *NearIte ) ) {
			pBoss->SetLife(-1);
			CreateBlood( *(pBoss->GetPosition()), *((*NearIte)->GetPosition()) );
			*(pPlayer->GetFloat()) += fUpGauge;
			//PlaySound(PLAYERNEARDAMAGE);
		}
	}

	// Boss死亡か
	if( pBoss && pBoss->GetLife() <= 0 ) {
		SceneManager::Create()->SetGameClear();
		return;
	}

	// ---- プレイヤーとボスの当たり判定
	if( pPlayer && pBoss ){
		if( m_Collision.CollisionOBBandOBB( pPlayer, pBoss ) ) {
			pPlayer->ReturnMove(); // 戻す
			pPlayer->ReturnMove(); // 戻す
			pBoss->ReturnMove(); // 戻す
			pBoss->ReturnMove(); // 戻す
		}
	}
	
	// プレイヤーと敵の攻撃の当たり判定
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
	
	// ---- プレイヤーとビームとの当たり判定
	if( pPlayer && pPlayer->GetCollisionFlg() && m_pBeamParent ) {
		for( auto Ite = m_pBeamParent->GetChild()->begin(); Ite != m_pBeamParent->GetChild()->end(); Ite++ ) {
			if( (*Ite)->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pPlayer, *Ite ) ) {
				// ダメージ処理
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
	// 出る量多くする
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