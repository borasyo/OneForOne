//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Collision.cpp]
// author : 大洞祥太
//
// ※GetCollisionCubePlusSizeは左手座標系における軸のプラスの向きの大きさ
// ※GetCollisionCubeMinusSizeは左手座標系における軸のマイナスの向きの大きさ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CollisionHardMode.h"
#include "FireExplosion.h"
#include "Blood.h"
#include "Player.h"
#include "FadeIn.h"
#include "SkeltonCorps.h"
#include "../Library/Task/SceneManager.h"
#include "../Library/DirectX/DirectSound.h"
#include "NearAtackAnimationParent.h"

// -- 定数
const float fOutRange = 3.0f; // 判定外にする範囲
const int nSkeletonDeathEffect = 10;
//const int nMaxBlood = 3;
//const float fUpNearGauge = 0.0f;
//const float fUpFarGauge = 0.0f;

// --- マクロ
#define RANDOM (rand()%40000*0.0001f)

CollisionHardMode::CollisionHardMode() {
	m_Name = "CollisionHardMode";
	m_pHierarchy = Hierarchy::Create();
	m_nMaxBlood = 5;
		
	WizardFogParent FogParent;
	m_pFogParent = FogParent.GetDownCastClass(m_pHierarchy->FindWithName("WizardFogParent"));
		
	BloodParent Obj;
	m_pBloodParent = Obj.GetDownCastClass(m_pHierarchy->CreateObject(new BloodParent));
	for( int i = 0; i < 350; i++ )
		m_pBloodParent->CreateChild( D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0) );
	for( auto Ite = m_pBloodParent->GetChild()->begin(); Ite != m_pBloodParent->GetChild()->end(); Ite++ )
		(*Ite)->SetActive(false);

	m_pNearAtackParent = m_pHierarchy->CreateObject(new NearAtackAnimationParent);
	for( int i = 0; i < 10; i++ ) {
		m_pNearAtackParent->CreateChild();
	}
	for( auto Ite = m_pNearAtackParent->GetChild()->begin(); Ite != m_pNearAtackParent->GetChild()->end(); Ite++ )
		(*Ite)->SetActive(false);
}
	
CollisionHardMode::~CollisionHardMode() {

}

bool CollisionHardMode::Start(){
	
	// ボス取得
	pBoss = m_pHierarchy->FindWithTag("Boss");

	// 親を取得
	m_pFireExplosionParent = m_pHierarchy->FindWithName("FireExplosionParent");
	m_pNear = m_pHierarchy->FindWithName("NearAtackImpactParent");
	m_pMeteoParent = m_pHierarchy->FindWithName("MeteoParent");
	m_pSkeltonCorpsParent = m_pHierarchy->FindWithName("SkeltonCorpsParent");
	m_pSkeltonBulletParent = m_pHierarchy->FindWithName("SkeltonBulletParent");
	m_pBeamParent = m_pHierarchy->FindWithName("BeamParent");
	m_pFireParent = m_pHierarchy->FindWithName("FireParent");
	pFade = m_pHierarchy->FindWithName("Fade");
	m_pActionStopParent = m_pHierarchy->FindWithName("ActionStopParent");
	m_pDragonFireParent = m_pHierarchy->FindWithName("DragonFireParent");
	
	return true;
}

void CollisionHardMode::LateUpdate() {
	
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
			
			if( *(pBoss->GetInt()) != 2 ) {
				pBoss->SetLife(-2500);  // 2000?
			}else {
				pBoss->SetLife(-2000);  // 2000?
			}

			for( int i = 0; i < 25; i++ )
				CreateBlood( *(pBoss->GetPosition()), RandomPos(*(pBoss->GetPosition())), true );
			
			// 雑魚敵を全部殺す
			if( m_pSkeltonCorpsParent ) {
				for( auto EnemyIte = m_pSkeltonCorpsParent->GetChild()->begin(); EnemyIte != m_pSkeltonCorpsParent->GetChild()->end(); EnemyIte++ ) {

					// 例外
					if( !(*EnemyIte)->GetActive() || !(*EnemyIte)->GetCollisionFlg() )
						continue;

					// ダメージ処理
					(*EnemyIte)->SetLife(-3);
					//SetCollisionFlg(false);
				
					// 骸骨軍死亡エフェクト作成
					int nScale = (int)(*EnemyIte)->GetScale()->x;
					for( int i = 0; i < nSkeletonDeathEffect*nScale; i++) {
						GameObject* pFog = m_pFogParent->CreateChild();
						pFog->ReInit();
						pFog->Start();
						*(pFog->GetPosition()) = *((*EnemyIte)->GetPosition());
						*(pFog->GetScale()) = *((*EnemyIte)->GetScale())/2;
					}
				}
			}

			// Dragonを全て退避させる
			GameObject* pDragonParent = m_pHierarchy->FindWithName("DragonParent");
			for( auto Ite = pDragonParent->GetChild()->begin(); Ite != pDragonParent->GetChild()->end(); Ite++ ) {
				if( !(*Ite)->GetActive() )
					continue;

				(*Ite)->SetLife(-9999);
			}

			// 画ブレ
			if( pBoss->GetLife() > 0 )
				*(m_pHierarchy->FindWithName("CameraSelect")->GetVec()) = D3DXVECTOR3( 90.0f, 1.5f, 0 );
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
			
			CreateBlood( *(pBoss->GetPosition()) - D3DXVECTOR3( 0,pBoss->GetPosition()->y,0) + D3DXVECTOR3( 0,(*FireIte)->GetPosition()->y + 1.5f,0), *((*FireIte)->GetPosition()), true );
			*(pPlayer->GetFloat()) += fUpGauge;
			
			// 画ブレ
			//if( pBoss->GetLife() > 0 )
			//	*(m_pHierarchy->FindWithName("CameraSelect")->GetVec()) = D3DXVECTOR3( 4, 0.2f, 1 );
		}
		// 雑魚敵との判定
		if( !m_pSkeltonCorpsParent ) 
			continue;
		for( auto EnemyIte = m_pSkeltonCorpsParent->GetChild()->begin(); EnemyIte != m_pSkeltonCorpsParent->GetChild()->end(); EnemyIte++ ) {
			if( (*EnemyIte)->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( *EnemyIte, *FireIte ) ){
				// ダメージ処理
				(*FireIte)->SetLife(-999);
				(*EnemyIte)->SetLife(-8);
				GameObject* pExplosion = m_pFireExplosionParent->CreateChild();
				pExplosion->Start();
				*(pExplosion->GetPosition()) = *((*FireIte)->GetPosition());
				CreateBlood( *((*EnemyIte)->GetPosition()), *((*FireIte)->GetPosition()), true );
				*(pPlayer->GetFloat()) += fUpGauge;
				
				// 骸骨軍死亡エフェクト作成
				for( int i = 0; i < nSkeletonDeathEffect; i++) {
					GameObject* pFog = m_pFogParent->CreateChild();
					pFog->ReInit();
					pFog->Start();
					*(pFog->GetPosition()) = *((*EnemyIte)->GetPosition());
					*(pFog->GetScale()) = *((*EnemyIte)->GetScale())/2;
				}
				//*(m_pHierarchy->FindWithName("CameraSelect")->GetVec()) = D3DXVECTOR3( 4, 0.2f, 1 );
				break;
			}
		}
	}
	
	// ---- 敵と近接の当たり判定
	for( auto NearIte = m_pNear->GetChild()->begin(); NearIte != m_pNear->GetChild()->end(); NearIte++ ) {
		if( !(*NearIte)->GetCollisionFlg() ) continue;
		
		// ボスとの判定
		if( pBoss && pBoss->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pBoss, *NearIte ) ) {
			pBoss->SetLife(-1);
			CreateBlood( *(pBoss->GetPosition()) - D3DXVECTOR3( 0,pBoss->GetPosition()->y,0) + D3DXVECTOR3( 0,(*NearIte)->GetPosition()->y + 1.5f,0), *((*NearIte)->GetPosition()) );
			*(pPlayer->GetFloat()) += fUpGauge;

			// 画ブレ
			if( pBoss->GetLife() > 0 )
				*(m_pHierarchy->FindWithName("CameraSelect")->GetVec()) = D3DXVECTOR3( 2, 0.5f, 1 );

			if( rand()%5 == 0 ) {
				GameObject* pObj = m_pNearAtackParent->CreateChild();
				*(pObj->GetPosition()) = *((*NearIte)->GetPosition());
				pObj->Start();
			}

			break;
		}

		// 骸骨軍の判定
		if( !m_pSkeltonCorpsParent ) continue;
		for( auto EnemyIte = m_pSkeltonCorpsParent->GetChild()->begin(); EnemyIte != m_pSkeltonCorpsParent->GetChild()->end(); EnemyIte++ ) {
			if( (*EnemyIte)->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( *EnemyIte, *NearIte ) ){
				// ダメージ処理
				(*EnemyIte)->SetLife(-1);
				CreateBlood( *((*EnemyIte)->GetPosition()), *((*NearIte)->GetPosition()) );
				*(pPlayer->GetFloat()) += fUpGauge;
				//PlaySound(PLAYERNEARDAMAGE);
				
				// 骸骨軍死亡エフェクト作成
				for( int i = 0; i < nSkeletonDeathEffect; i++) {
					GameObject* pFog = m_pFogParent->CreateChild();
					pFog->ReInit();
					pFog->Start();
					*(pFog->GetPosition()) = *((*EnemyIte)->GetPosition());
					*(pFog->GetScale()) = *((*EnemyIte)->GetScale())/2;
				}

				// 画ブレ
 				*(m_pHierarchy->FindWithName("CameraSelect")->GetVec()) = D3DXVECTOR3( 10, 0.5f, 1 );

				GameObject* pObj = m_pNearAtackParent->CreateChild();
				*(pObj->GetPosition()) = *((*NearIte)->GetPosition());
				pObj->Start();
				
				break;
			}
		}
	}
	
	// Boss死亡か
	if( pBoss && pBoss->GetLife() <= 0 ) {
		
		// Dragonを全て退避させる
		GameObject* pDragonParent = m_pHierarchy->FindWithName("DragonParent");
		for( auto Ite = pDragonParent->GetChild()->begin(); Ite != pDragonParent->GetChild()->end(); Ite++ ) {
			if( !(*Ite)->GetActive() )
				continue;
			(*Ite)->SetLife(-9999);
		}

		pBoss->FreeFunction();
		SceneManager::Create()->SetGameClear();
		return;
	}

	// ---- プレイヤーとボスの当たり判定
	if( pPlayer && pBoss ){
		if( m_Collision.CollisionOBBandOBB( pPlayer, pBoss ) ) {
			pPlayer->ReturnMove(); // 戻す
			pPlayer->ReturnMove(); // 戻す
			pBoss->ReturnMove(); // 戻す
		}
	}
	
	// ---- プレイヤーとドラゴンの当たり判定
	GameObject* pDragon = m_pHierarchy->FindWithName("DragonParent");
	if( pPlayer && pPlayer->GetCollisionFlg() && pDragon ) { //&& *(pBoss->GetBool()) ){
		for( auto Ite = pDragon->GetChild()->begin(); Ite != pDragon->GetChild()->end(); Ite++ ) {
			if( (*Ite)->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pPlayer, *Ite ) ) {
				pPlayer->SetLife(-1);
				PlaySound(PLAYERDAMEGE);
				CreateBlood( *(pPlayer->GetPosition()), *(pDragon->GetPosition()), true );
				if( !pFade->FindChild("FadeIn") ) {
					m_pHierarchy->CreateObject(new FadeIn(10,D3DXCOLOR(0.5f,0,0,0)))->SetParent(pFade);
				}
				(*Ite)->SetCollisionFlg(false);
				return;
			}
		}
	}
	
	// ---- プレイヤーと火炎弾の当たり判定
	if( pPlayer && pPlayer->GetCollisionFlg() && m_pDragonFireParent ) {
		for( auto Ite = m_pDragonFireParent->GetChild()->begin(); Ite != m_pDragonFireParent->GetChild()->end(); Ite++ ) {
			if( (*Ite)->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pPlayer, *Ite ) ) {
				// ダメージ処理
				pPlayer->SetLife(-1);
				(*Ite)->SetLife(-999);
				PlaySound(PLAYERDAMEGE);
				CreateBlood( *(pPlayer->GetPosition()), *((*Ite)->GetPosition()), true );
				if( !pFade->FindChild("FadeIn") ) {
					m_pHierarchy->CreateObject(new FadeIn(10,D3DXCOLOR(0.5f,0,0,0)))->SetParent(pFade);
				}
				return;
			}
		}
	}

	// ---- プレイヤーと骸骨弾との当たり判定
	if( pPlayer && pPlayer->GetCollisionFlg() && m_pSkeltonBulletParent ) {
		for( auto Ite = m_pSkeltonBulletParent->GetChild()->begin(); Ite != m_pSkeltonBulletParent->GetChild()->end(); Ite++ ) {
			if( (*Ite)->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pPlayer, *Ite ) ) {
				// ダメージ処理
				pPlayer->SetLife(-1);
				PlaySound(PLAYERDAMEGE);
				(*Ite)->SetLife(-999);
				CreateBlood( *(pPlayer->GetPosition()), *((*Ite)->GetPosition()), true );
				if( !pFade->FindChild("FadeIn") ) {
					m_pHierarchy->CreateObject(new FadeIn(10,D3DXCOLOR(0.5f,0,0,0)))->SetParent(pFade);
				}
				return;
			}
		}
	}

	// ---- プレイヤーと骸骨との当たり判定
	if( pPlayer && pPlayer->GetCollisionFlg() && m_pSkeltonCorpsParent ) {
		for( auto Ite = m_pSkeltonCorpsParent->GetChild()->begin(); Ite != m_pSkeltonCorpsParent->GetChild()->end(); Ite++ ) {
			if( (*Ite)->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pPlayer, *Ite ) ) {
				// ダメージ処理
				pPlayer->SetLife(-1);
				PlaySound(PLAYERDAMEGE);
				(*Ite)->SetLife(-999);
				CreateBlood( *(pPlayer->GetPosition()), *((*Ite)->GetPosition()), true );
				if( !pFade->FindChild("FadeIn") ) {
					m_pHierarchy->CreateObject(new FadeIn(10,D3DXCOLOR(0.5f,0,0,0)))->SetParent(pFade);
				}
				return;
			}
		}
	}
	
	// ---- プレイヤーとメテオとの当たり判定
	if( pPlayer && pPlayer->GetCollisionFlg() && m_pMeteoParent ) {
		for( auto Ite = m_pMeteoParent->GetChild()->begin(); Ite != m_pMeteoParent->GetChild()->end(); Ite++ ) {
			if( (*Ite)->GetCollisionFlg() && m_Collision.CollisionOBBandOBB( pPlayer, *Ite ) ) {
				// ダメージ処理
				pPlayer->SetLife(-1);
				PlaySound(PLAYERDAMEGE);
				(*Ite)->SetLife(-999);
				CreateBlood( *(pPlayer->GetPosition()), *((*Ite)->GetPosition()), true );
				if( !pFade->FindChild("FadeIn") ) {
					m_pHierarchy->CreateObject(new FadeIn(10,D3DXCOLOR(0.5f,0,0,0)))->SetParent(pFade);
				}
				return;
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
				return;
			}
		}
	}

	// ---- プレイヤーと捕縛魔法陣との当たり判定
	m_pActionStopParent = m_pHierarchy->FindWithName("ActionStopParent");
	if( pPlayer && m_pActionStopParent && m_pActionStopParent->GetCollisionFlg() && 
		m_Collision.CollisionOBBandOBB( pPlayer, m_pActionStopParent ) ) {

		if( pPlayer->GetCollisionFlg() ) {
			// 一定時間動けなくする
			m_pActionStopParent->SetParent(pPlayer);
			m_pActionStopParent->SetLife(-999);
			m_pActionStopParent->SetLife(300);
			m_pActionStopParent->SetCollisionFlg(false);
			pPlayer->SetUpdateFlg(false); // 更新停止
			*(m_pActionStopParent->GetPosition()) = *(pPlayer->GetPosition());
			return;
		}
		else // 無敵中なのでくらわない
			m_pActionStopParent->SetLife(-999);
	}
}

void CollisionHardMode::CreateBlood( D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos, bool bMore ) {
	
	if( !bMore ) {
		// 処理落ち防止のため出る量を制限する
		m_nMaxBlood = 3;
	}
	// プレイヤーは出る量多くする
	else {
		m_nMaxBlood = 10;
	}

	for( int i = 0; i < m_nMaxBlood; i ++ ) {
		m_pBloodParent->CreateChild( MyselfPos,OpponentPos );
	}
}

D3DXVECTOR3 CollisionHardMode::RandomPos( D3DXVECTOR3 pos ){
	
	D3DXVECTOR3 Pos = D3DXVECTOR3(0,pos.y - 5.0f,0);

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