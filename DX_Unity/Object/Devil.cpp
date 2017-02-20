//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Devil.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Devil.h"
#include "MeteoParent.h"
#include "SkeltonCorpsParent.h"
#include "SkeletonBulletParent.h"
#include "BeamHolder.h"
#include "ActionStopParent.h"
#include "FireParent.h"
#include "Shadow.h"
#include "../Library/DirectX/DirectSound.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/Debug/FPSController.h"

#include "CameraSelect.h"

// --- 定数
const int nDevilLife = 10000;
const float fInitPos = 46.5f;
const D3DXVECTOR3 Collision = D3DXVECTOR3(0.5f,1.75f,0.5f);

// 攻撃関係
const int nCorpsInterval = 1076;
const int nBulletInterval = 153;
const int nActionStopInterval = 777;
const int nMeteoInterval = 73;
const int nBeamLife = 300;
const int nBeamInterval = 522+nBeamLife;
const int nDragonInterval = 1000;
const int nInvincibleInterval = 2016; 

// Invincible
const int nInvincibleSpeed = 3;

// Meteo関連
#define METEO_POS ( rand()%20000*0.001f )

// Corps制限
const int nMaxCorps = 50; // 骸骨生成上限	
const int nCreateMaxCorps = 25; // 1回の生成での最大生成数

// Beamサイズ
const D3DXVECTOR3 BeamPos = D3DXVECTOR3(5,4.75f,5);
const D3DXVECTOR3 BeamScale = D3DXVECTOR3(50,50,4);

const float fSaveAmount = 30.0f;
const float fEraseAmountRange = 3.0f;
const float fBulletRange = 15.0f;
const float fInvincibleMove = 0.3f;

// 
const int nBeamAnimTime = 60;
const int nAngryLife = 4000;
const int nKnockBackAmount = 1500;

// --- マクロ
#define RANDOM_X (rand()%3000*0.001f)
#define RANDOM_Y (rand()%15000*0.001f)
#define RANDOM_Z (rand()%3000*0.001f)

Devil::Devil()
{
	m_Name = "Devil";
	m_Tag = "Boss";
	m_Object3D.SetFileName(_T("Devil.x"));

	// Task取得
	m_pHierarchy = Hierarchy::Create();
	
	// MeteoParent作成
	m_pMeteoParent = m_pHierarchy->CreateObject(new MeteoParent);
	for( int i = 0; i < 20; i++ )
		m_pMeteoParent->CreateChild();
	for( auto Ite = m_pMeteoParent->GetChild()->begin(); Ite != m_pMeteoParent->GetChild()->end(); Ite++ ) {
		(*Ite)->SetLife(-999);
		//(*Ite)->SetActive(false);
		//(*Ite)->FindChild("Shadow")->SetActive(false);
	}
	
	// SkeltonCorpsParent作成
	m_pSkeltonCorpsParent = m_pHierarchy->CreateObject(new SkeltonCorpsParent);
	for( int i = 0; i < nMaxCorps; i++ )
		m_pSkeltonCorpsParent->CreateChild();
	for( auto Ite = m_pSkeltonCorpsParent->GetChild()->begin(); Ite != m_pSkeltonCorpsParent->GetChild()->end(); Ite++ )
		(*Ite)->SetActive(false);

	// SkeltonBulletParent作成
	m_pSkeltonBulletParent = m_pHierarchy->CreateObject(new SkeltonBulletParent);

	// ActionStopParent作成
	m_pActionStopParent = m_pHierarchy->CreateObject(new ActionStopParent);
	*(m_pActionStopParent->GetPosition()) = m_Position;
	m_pActionStopParent->SetActive(false);
	for( int i = 0; i < 250; i++ ) {
		m_pActionStopParent->CreateChild();
	}
	for( auto Ite = m_pActionStopParent->GetChild()->begin(); Ite != m_pActionStopParent->GetChild()->end(); Ite++ ) {
		(*Ite)->SetActive(false);
	}

	// BulletFog取得
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
	
	// FireParent生成
	GameObject* pFireParent = m_pHierarchy->CreateObject(new FireParent);
	for( int i = 0; i < 10; i++ )
		pFireParent->CreateChild();
	for( auto Ite = pFireParent->GetChild()->begin(); Ite != pFireParent->GetChild()->end(); Ite++ )
		(*Ite)->SetActive(false);

	// DragonParent生成
	DragonParent DraPare;
	m_pDragonParent = DraPare.GetDownCastClass( m_pHierarchy->CreateObject(new DragonParent) );
	for( int i = 0; i < 10; i++ )
		m_pDragonParent->CreateChild(1.0f);
	for( auto Ite = m_pDragonParent->GetChild()->begin(); Ite != m_pDragonParent->GetChild()->end(); Ite++ )
		(*Ite)->SetActive(false);

	
	// AnimCotroller取得
	m_Object3D.SetAnimationController();
	//m_Object3D.SetMaterialColor( D3DXCOLOR(1,0,0,0) );

	// FPS
	m_pFPSController = FPSController::Create();

	m_nLevel = 0;
}

Devil::~Devil() {

}

void Devil::Awake(){

	ReInit();
	m_bStart = false;
	m_bBeam = false;
	m_bAtack = false;
	m_bPreparation = false;
	m_bKnockBack = false;
	m_bInvincible = false;
	m_bAngry = false;
	m_nBulletCnt = 1;
	m_nActionStopCnt = rand()%(nActionStopInterval/3)+1;
	m_nBeamCnt = m_nActionStopCnt;//+30;
	m_nCorpsCnt = rand()%222+333;
	m_nMeteoCnt = 1;
	m_nDragonCnt = rand()%(nDragonInterval/3);
	m_nInvincibleCnt = 1;
	m_nDamage = 0;
	m_nAngryCnt = 0;
	m_fAtackLevel = 0.0f;
	m_fLifeLevel = 0.0f;
	
	// 難易度調整
	switch( m_nLevel ) {
		
	case 0:
		m_fLifeLevel = 1.0f;
		m_fAtackLevel = 1.0f;
		break;
	case 1:
		m_fLifeLevel = 0.75f;
		m_fAtackLevel = 1.5f;
		break;
	case 2:
		m_fLifeLevel = 0.5f;
		m_fAtackLevel = 1.6f;
		break;
	}

	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	// 初期設定
	//SetCollisionCircleSize( Collision.x*2 );
	SetCollisionCubeSize(D3DXVECTOR3(Collision.x,Collision.y,Collision.z), D3DXVECTOR3(Collision.x,Collision.y,Collision.z));
	Move( D3DXVECTOR3(0,fInitPos,0) );
	Rotation( D3DXVECTOR3(0,Pai,0) );
	ScaleChange( D3DXVECTOR3(7,7,7) );

	// ライフ設定
	m_nLife = nDevilLife*m_fLifeLevel; // 10000
	m_nOldLife = m_nLife;
	
	// Loop時間を設定
	m_Object3D.GetAnimationManager()->SetLoopTime( "Wait", 150 );
	m_Object3D.GetAnimationManager()->SetShiftTime( "Wait", 0 );
	m_Object3D.GetAnimationManager()->SetLoopTime( "SkeletonBullet", 80 );
	m_Object3D.GetAnimationManager()->SetLoopTime( "CorpsSkeleton", 100 );
	m_Object3D.GetAnimationManager()->SetLoopTime( "ActionStop", 270 );
	m_Object3D.GetAnimationManager()->SetLoopTime( "CancelActionStop", 60 );
	m_Object3D.GetAnimationManager()->SetShiftTime( "CancelActionStop", 0 );
	m_Object3D.GetAnimationManager()->SetLoopTime( "AtackActionStop", 60 );
	m_Object3D.GetAnimationManager()->SetShiftTime( "AtackActionStop", 0 );
	m_Object3D.GetAnimationManager()->SetLoopTime( "KnockBack", 120 );
	m_Object3D.GetAnimationManager()->SetShiftTime( "KnockBack", 0 );
	m_Object3D.GetAnimationManager()->SetLoopTime( "Death", 420 );
	m_Object3D.GetAnimationManager()->SetShiftTime( "Death", 0 );
	m_Object3D.GetAnimationManager()->SetLoopTime( "Invincible", 316 );
	
	// 走らせる
	m_Object3D.SetAnimFlg(true); // アニメーション再開
	m_Object3D.GetAnimationManager()->ChangeAnimation( "Wait", true );
	
	// 影作成
	GameObject* pObj = Hierarchy::Create()->CreateObject(new Shadow);
//	GameObject* pObj = Hierarchy::Create()->CreateObject(new Shadow(D3DXCOLOR( 0.6f,0.1f,0.6f,1.0f ), true));
	pObj->SetParent(this);
	pObj->Start();
	*(pObj->GetScale()) *= 12.0f;
	
	// Meteo消す
	for( auto Ite = m_pMeteoParent->GetChild()->begin(); Ite != m_pMeteoParent->GetChild()->end(); Ite++ ) {
		(*Ite)->SetActive(true);
		(*Ite)->SetLife(-999);
		//(*Ite)->SetActive(false);
		//(*Ite)->FindChild("Shadow")->SetActive(false);
	}

	// Debug
	///m_nInvincibleCnt = nInvincibleInterval*m_fAtackLevel - 240;
	//m_nLife = 10;//nAngryLife*m_fLifeLevel+1; // 10000
	//m_nBeamCnt = nBeamInterval - 30;
}

void Devil::LateUpdate(){
	
	// アニメーション更新
	m_bAtack = m_Object3D.UpdateAnim();
	
	// まだ戦闘開始じゃない
	if( !m_bStart ) {

		if(m_Position.y <= fInitPos - 30.0f) {
			m_bStart = true;
			return;
		}

		Move( D3DXVECTOR3(0,-1.0f,0) );

		return;
	}

	if( !m_bAngry && m_nOldLife > nAngryLife*m_fLifeLevel && m_nLife <= nAngryLife*m_fLifeLevel ) {
		m_bAngry = true;
		m_nDamage = nKnockBackAmount*m_fLifeLevel; // 強制ノックバック
		StopSound( HARD_BGM );
		PlaySound( EASY_BGM );
	}

	if( m_bAngry ) {
		m_nAngryCnt ++; // 怒り状態（攻撃スピード1.5倍）

		// エフェクト作成
		if( !m_bInvincible ) {
			for( int i = 0; i < 2; i++ ) {
				GameObject* pObj = m_pBulletFogParent->CreateChild(D3DXCOLOR(0.1f,0.0f,0.0f,0.5f));
				*(pObj)->GetPosition() = m_Position+Random();
				*(pObj)->GetScale() = D3DXVECTOR3(m_Scale.x,m_Scale.x,m_Scale.x);
			}
		}
	}

	// ダメージを負っている
	if( m_nOldLife - m_nLife > 0 ) {
		m_nDamage += m_nOldLife - m_nLife;
		if( m_nDamage >= nKnockBackAmount*m_fLifeLevel && strcmp( m_Object3D.GetAnimationManager()->GetNowAnimName(), "Wait" ) == 0 ) { //&& !m_bPreparation ) {
			m_bKnockBack = true;
			m_Object3D.GetAnimationManager()->ChangeAnimation( "KnockBack", false );
			m_nDamage = 0;
		}
	}

	if( strcmp( m_Object3D.GetAnimationManager()->GetNowAnimName(), "KnockBack" ) == 0 &&
		m_Object3D.GetAnimationManager()->GetWeight() >= m_Object3D.GetAnimationManager()->GetLoopTime( "KnockBack" ) - 3.0f ) {
		m_bKnockBack = false;
		DownCount(30);
		//m_Object3D.GetAnimationManager()->ChangeAnimation( "Wait", true );
	}
	
	GameObject* pPlayer = Hierarchy::Create()->FindWithName("Player");
	
	// 攻撃をチェック
	if( !m_bKnockBack )
		CheckAtack(pPlayer);
	
	// Dragonを生成するかチェック
	m_nDragonCnt ++;
	if( rand()%2 == 0 )
		m_nDragonCnt ++;

	if( m_nDragonCnt%(int)(nDragonInterval*m_fAtackLevel) == 0 ) {
		m_pDragonParent->CreateChild( m_fAtackLevel );
		m_nDragonCnt = 0;
	}

	// 例外チェック
	ExceptionCheck();
	
	// ライフ
	m_nOldLife = m_nLife; // 現在を過去へ格納

	// 影が消されてないか
	/*GameObject* pShadow = FindChild("Shadow");
	if( !pShadow->GetActive() ){
		pShadow->SetActive( true );
	}*/

#if _DEBUG
	//std::cout << "HP : " << m_nLife << std::endl;
#endif
}

void Devil::FastDraw(){

	if( strcmp(m_Object3D.GetAnimationManager()->GetNowAnimName(), "Death" ) == 0 )
		m_Object3D.UpdateAnim();
	
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );	// 裏面カリングOFF

	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );	// 裏面カリングON
}

// 攻撃を行うかチェック
void Devil::CheckAtack(GameObject* pPlayer){
	
	// Meteos
	if( m_nMeteoCnt%(int)(nMeteoInterval*m_fAtackLevel) == 0 ) {

		D3DXVECTOR3 Pos;
		if( pPlayer ) {
			Pos = *(pPlayer->GetPosition());
			Pos.y = 0;
			
			// もし無敵中なら範囲拡大
			if( m_bInvincible ) {
				if( rand()%2 ) {
					Pos.x += METEO_POS;
				} else {
					Pos.x -= METEO_POS;
				}

				if( rand()%2 ) {
					Pos.z += METEO_POS;
				} else {
					Pos.z -= METEO_POS;
				}
			}
		}
		else {
			Pos = D3DXVECTOR3(-100,0,-100);
			Pos += D3DXVECTOR3(rand()%2000*0.1f,0,rand()%2000*0.1f);
		}
		m_pHierarchy->FindWithName("SkyDome")->FreeFunction();

		GameObject* pMeteo = m_pMeteoParent->CreateChild();
		pMeteo->Move(Pos);

		if( m_bInvincible ) 
			pMeteo->FreeFunction();
		
		m_nMeteoCnt = 1; // カウント初期化
		
		// 発射音は無敵じゃない時だけ出す
		if( !m_bInvincible ) 
			PlaySound(METEOSHOT);
	}
	else if( !m_bBeam ) {
		m_nMeteoCnt++;
		if( m_nLife <= nAngryLife*m_fLifeLevel && m_nAngryCnt%2 == 0 && m_nMeteoCnt%(int)(nMeteoInterval*m_fAtackLevel) != 0 )
			m_nMeteoCnt ++;
	}

	// End Meteo
	

	// Invincible
	if( m_nInvincibleCnt%(int)(nInvincibleInterval*m_fAtackLevel) == 0 ) {

		if( !m_bPreparation && m_Object3D.GetAnimationManager()->ChangeAnimation( "Invincible", false ) ) {
			m_bPreparation = true;
			m_bCollision = false; // 無敵にする
			m_bInvincible = false;
			CameraSelect::SetState(CAMERA_INVINCIBLE);
		}

		// 準備中...
		if( !m_bInvincible ) {

			// 準備終了
			if( m_Object3D.GetAnimationManager()->GetWeight() >= 136.0f ) {
				m_bInvincible = true;
				m_Object3D.SetAnimSpeed( 1.0f/15.0f );
				PlaySound( WIZARDBEAM );
			}

			Move( D3DXVECTOR3( 0, fInvincibleMove, 0 ) );
		}
		else {
			// Meteoの速さをnInvincibleSpeed倍に
			for( int i = 0; i < nInvincibleSpeed; i++ ) {
				
				// FPS維持を優先
				if( m_pFPSController->GetFPS() < 50 )
					i = nInvincibleSpeed;

				if( m_nMeteoCnt%(int)(nMeteoInterval*m_fAtackLevel) == 0 )
					continue;
				
				m_nMeteoCnt++;
			}
		
			// エフェクト作成
			for( int i = 0; i < 3; i++ ) {
				GameObject* pObj = m_pBulletFogParent->CreateChild(D3DXCOLOR(0.0f,0.1f,0.0f,0.5f), 3.0f, 0.6f);
				*(pObj)->GetPosition() = m_Position+Random();
				*(pObj)->GetScale() = D3DXVECTOR3(m_Scale.x,m_Scale.x,m_Scale.x) * 1.5f;
			}

			// 終了
			if( m_Object3D.GetAnimationManager()->GetWeight() >= m_Object3D.GetAnimationManager()->GetLoopTime("Invincible") - 120.0f ) {				
				m_bPreparation = false;
				//m_bCollision = true; // 無敵解除
				m_bInvincible = false;
				DownCount(120);
				m_nInvincibleCnt = 1;
				m_Object3D.SetAnimSpeed( 1.0f );
				StopSound( WIZARDBEAM );	
			}

			// 自己回復
			//m_nLife ++;
		}

		return; // Invincible実行中はこれより下の処理は停止
	}
	else if( !m_bBeam && !m_bPreparation ) {

		if( !*(pPlayer->GetBool()) ) { 
			m_nInvincibleCnt++;
			if( m_nLife <= nAngryLife*m_fLifeLevel && m_nAngryCnt%2 == 0 && m_nInvincibleCnt%(int)(nInvincibleInterval*m_fAtackLevel) != 0 )
				m_nInvincibleCnt ++;
		}

		if( m_Position.y > fInitPos - 30.0f ) {

			Move( D3DXVECTOR3( 0, -fInvincibleMove, 0 ) );

			if( m_Position.y == fInitPos - 30.0f ) {
				m_bCollision = true;
			}
		}
	}

	// End Invincible


	// Beam
	if( m_nBeamCnt%(int)(nBeamInterval*m_fAtackLevel) == 0 ) {

		if( !m_bBeam && !m_bPreparation && m_Object3D.GetAnimationManager()->ChangeAnimation( "Beam", false ) ){
			m_bPreparation = true;

			GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
			float fDistanceX = pPlayer->GetPosition()->x - m_Position.x;
			float fDistanceZ = pPlayer->GetPosition()->z - m_Position.z;
			m_fRot = (atan2f(fDistanceX,fDistanceZ) - m_Rotation.y) / 59.0f;

			if( m_fRot < -Pai/59.0f )
				m_fRot += Pai*2/59.0f;
			
			GameObject* pSkyDome = m_pHierarchy->FindWithName("SkyDome");
			*(pSkyDome->GetBool()) = true;
			GameObject* pField = m_pHierarchy->FindWithName("Field");
			*(pField->GetBool()) = true;
			m_bBeam = true;
			m_nBeamCnt ++;
			CameraSelect::SetState(CAMERA_BEAM);
		}
		return;
	}
	
	if( m_bBeam && m_bPreparation &&
		m_nBeamCnt % ((int)(nBeamInterval*m_fAtackLevel)+59) == 0 ) {
		// 攻撃処理実行
		m_pBeam = m_pHierarchy->CreateObject(new BeamHolder( D3DXCOLOR(0.15f,0.0f,0.0625f,1.0f), nBeamLife-50, nBeamLife, D3DXVECTOR3(0,0,0), BeamScale, true, true ));
		m_pBeam->SetParent(this);
		m_pBeam->Start();

		// 芯となるビーム
		GameObject* pObj = m_pHierarchy->CreateObject(new BeamHolder( D3DXCOLOR(0.1f,0.1f,0.1f,0.25f), nBeamLife-50, nBeamLife, D3DXVECTOR3(0,0,0), BeamScale, true, false ));
		pObj->SetParent(this);
		pObj->Start();

		// 全カウント初期化
		m_fRot /= 3.0f;
		m_nActionStopCnt = 1; // カウント初期化
		m_nMeteoCnt = 1; // カウント初期化
		m_nBulletCnt = 1; // カウント初期化
		PlaySound(DEVILBEAM);
	} 
	
	// アニメーション終了3F前に実行
	if( m_bBeam && m_Object3D.GetAnimationManager()->GetLoopTime("Beam") - 1.0f <= m_Object3D.GetAnimationManager()->GetWeight() ) {
		m_Object3D.SetAnimFlg(false); // アニメーション停止
	}

	if( m_bBeam && m_nBeamCnt % ((int)(nBeamInterval*m_fAtackLevel)+nBeamAnimTime-1 + nBeamLife) == 0 ) {
		DownCount();
		//m_pBeam = nullptr;
		m_bBeam = false;
		m_bPreparation = false;
		m_fRot = 0;
		m_nBeamCnt = 1; // カウント初期化
		m_Object3D.SetAnimFlg(true); // アニメーション再開
		//m_nBeamCnt = nBeamLife*3+rand()%300; // nBeamLife+1
		//StopSound(DEVILBEAM);
		
		// 空を元に戻す
		GameObject* pSkyDome = m_pHierarchy->FindWithName("SkyDome");
		*(pSkyDome->GetBool()) = false;
		GameObject* pField = m_pHierarchy->FindWithName("Field");
		*(pField->GetBool()) = false;
	}

	if ( m_bBeam ) {
		Rotation( D3DXVECTOR3(0,m_fRot,0) );
		if( m_nBeamCnt >= ((int)(nBeamInterval*m_fAtackLevel)+nBeamAnimTime-1) && m_pBeam ) {

			for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
				if( m_pBeam == *Ite && (*Ite)->GetScale()->x < BeamScale.x ) {
					m_pBeam->ScaleChange( D3DXVECTOR3(BeamScale.x/120,BeamScale.y/120,0));
					*(m_pBeam->GetPosition()) = m_Position + D3DXVECTOR3( sinf(m_Rotation.y) * BeamPos.x, BeamPos.y, cosf(m_Rotation.y) * BeamPos.z );
				}
				else if( (*Ite)->GetName() != "Shadow" && (*Ite)->GetScale()->x < BeamScale.x ) {
					(*Ite)->ScaleChange( D3DXVECTOR3((BeamScale.x)/120,(BeamScale.y)/120,0));
					*((*Ite)->GetPosition()) = m_Position + D3DXVECTOR3( sinf(m_Rotation.y) * BeamPos.x, BeamPos.y, cosf(m_Rotation.y) * BeamPos.z );
				}
			}
			// 画ブレ生成
			*(m_pHierarchy->FindWithName("CameraSelect")->GetVec()) = D3DXVECTOR3( nBeamLife+150,1.75f,0 );
		}
	}
	
	if( !m_bPreparation || m_bBeam ) {
		m_nBeamCnt++;

		if( m_nBeamCnt%(int)(nBeamInterval*m_fAtackLevel) == 0 && *(pPlayer->GetBool()) ) {
			m_nBeamCnt --;
		}

		//if( m_bBeam )
		//	return;
	}

	// End Beam
	
	// Corps
	if( m_nCorpsCnt%(int)(nCorpsInterval*m_fAtackLevel) == 0 ) {

		if( m_bPreparation && m_bAtack ) {
			int nCorps = 0; 
			for( auto Ite = m_pSkeltonCorpsParent->GetChild()->begin(); Ite != m_pSkeltonCorpsParent->GetChild()->end(); Ite++ ){
				if( (*Ite)->GetActive() ) {
					nCorps ++;
				}
			}

			// 上限チェック
			if( nCorps < nMaxCorps ) {

				// 上限は超えないように数を調整
				nCorps = nMaxCorps - nCorps;

				// 10以上は生成しない
				if( nCorps > nCreateMaxCorps )
					nCorps = nCreateMaxCorps;

				// 決まった数生成
				for( int i = 0; i < nCorps; i++ ) {
					m_pSkeltonCorpsParent->CreateChild();
				}
			}
			m_nCorpsCnt = 1; // カウント初期化
			PlaySound(DEVILCORPS);
			m_bPreparation = false;
			DownCount();
		}
		else if( !m_bPreparation && m_Object3D.GetAnimationManager()->ChangeAnimation( "CorpsSkeleton", false ) ) {
			m_bPreparation = true;
		}
		return;
	}
	else if( !m_bBeam && !m_bPreparation && m_nLevel != 2 ) {
		m_nCorpsCnt++;
		if( m_nLife <= nAngryLife*m_fLifeLevel && m_nAngryCnt%2 == 0 && m_nCorpsCnt%(int)(nCorpsInterval*m_fAtackLevel) != 0 )
			m_nCorpsCnt ++;
	}

	// End Corps 

	// Bullet
	if( pPlayer && m_nBulletCnt%(int)(nBulletInterval*m_fAtackLevel) == 0 ) {
		
		if( m_Object3D.GetAnimationManager()->GetWeight() == 50.0f ) {
			// Bullet生成
			GameObject* pObj = m_pSkeltonBulletParent->CreateChild();
			pObj->ReInit();
			*(pObj->GetPosition()) = m_Position + D3DXVECTOR3( sinf(m_Rotation.y) * BeamPos.x, 0.0f, cosf(m_Rotation.y) * BeamPos.z );
			*(pObj->GetRotation()) = m_Rotation;
			pObj->Start();
			m_nBulletCnt = 1; // カウント初期化
			PlaySound(DEVILBULLET);
			m_bPreparation = false;
			DownCount();
		}
		else {
			if( !m_bPreparation && m_Object3D.GetAnimationManager()->ChangeAnimation( "SkeletonBullet", false ) ) {
				GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
				float fDistanceX = pPlayer->GetPosition()->x - m_Position.x;
				float fDistanceZ = pPlayer->GetPosition()->z - m_Position.z;
				m_fRot = (atan2f(fDistanceX,fDistanceZ) - m_Rotation.y) / 50.0f;

				if( m_fRot < -Pai/50.0f )
					m_fRot += Pai*2/50.0f;
			}
			Rotation( D3DXVECTOR3(0,m_fRot,0) );
			m_bPreparation = true;
		}
		return;
	}
	else if( !m_bBeam && rand()%2 && !m_bPreparation ) {
		m_nBulletCnt++;
		if( m_nLife <= nAngryLife*m_fLifeLevel && m_nAngryCnt%2 == 0 && m_nBulletCnt%(int)(nBulletInterval*m_fAtackLevel) != 0 )
			m_nBulletCnt ++;
	}

	// End Bullet

	// ActionStop
	if( m_nActionStopCnt%(int)(nActionStopInterval*m_fAtackLevel) == 0 ) {

		if( !m_bPreparation && m_Object3D.GetAnimationManager()->ChangeAnimation( "ActionStop", false ) ) {
			m_Object3D.GetAnimationManager()->SetShiftTime( "Wait", 0 );
			m_bPreparation = true;
		}

		// 準備アニメーションが終了したor攻撃アニメーションが終了した
		if( strcmp(m_Object3D.GetAnimationManager()->GetNowAnimName(), "ActionStop") == 0 &&
			m_Object3D.GetAnimationManager()->GetLoopTime("ActionStop") - 1.0f <= m_Object3D.GetAnimationManager()->GetWeight() ) {
			m_nActionStopCnt = 1; // カウント初期化
			m_bPreparation = false;
			//DownCount();
			m_Object3D.GetAnimationManager()->ChangeAnimation( "Wait", true );
			m_Object3D.GetAnimationManager()->ChangeAnimation( "CancelActionStop", false );
			DownCount( m_Object3D.GetAnimationManager()->GetLoopTime("CancelActionStop") );
			StopSound(DEVILACTIONSTOP);
			//m_Object3D.GetAnimationManager()->SetShiftTime( "Wait", 30 );
		}

		// 移動がなければ
		if( strcmp(m_Object3D.GetAnimationManager()->GetNowAnimName(), "ActionStop") == 0 && 
			m_Object3D.GetAnimationManager()->GetWeight() > 90 &&
			( m_nOldLife != m_nLife || *pPlayer->GetMoveAmount() == D3DXVECTOR3(0,0,0) ) ) {
			m_Object3D.GetAnimationManager()->ChangeAnimation( "Wait", true );
			m_Object3D.GetAnimationManager()->ChangeAnimation( "AtackActionStop", false );
			m_pActionStopParent->FreeFunction(); // 攻撃移動

			GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
			float fDistanceX = pPlayer->GetPosition()->x - m_Position.x;
			float fDistanceZ = pPlayer->GetPosition()->z - m_Position.z;
			m_fRot = (atan2f(fDistanceX,fDistanceZ) - m_Rotation.y) / 15.0f;

			if( m_fRot < -Pai/15.0f )
				m_fRot += Pai*2/15.0f;

			DownCount( 90, false );
			m_nBeamCnt = nBeamInterval - 60*m_fAtackLevel;
		}

		if( m_Object3D.GetAnimationManager()->GetWeight() == 90 ) {	
			m_pActionStopParent->Start();
			*(m_pActionStopParent->GetPosition()) = m_Position + D3DXVECTOR3( 8.5f * sinf(m_Rotation.y + 1.0f), 9.0f, 8.5f * cosf(m_Rotation.y + 1.0f) );
			PlaySound(DEVILACTIONSTOP);
		}

		if( strcmp(m_Object3D.GetAnimationManager()->GetNowAnimName(), "AtackActionStop") == 0 ) {
			Rotation( D3DXVECTOR3(0,m_fRot,0) );

			if( m_Object3D.GetAnimationManager()->GetWeight() >= 15.0f )
				m_fRot = 0.0f;
		}
		
		if( strcmp(m_Object3D.GetAnimationManager()->GetNowAnimName(), "AtackActionStop") == 0 &&
			m_Object3D.GetAnimationManager()->GetLoopTime("AtackActionStop") - 1.0f <= m_Object3D.GetAnimationManager()->GetWeight() ) {
			m_nActionStopCnt = 1; // カウント初期化
			m_bPreparation = false;
			StopSound(DEVILACTIONSTOP);
			DownCount();
		}
	}
	else if( !m_bBeam && !m_bPreparation && m_nLevel != 2 ) {
		m_nActionStopCnt++;
		if( m_nLife <= nAngryLife*m_fLifeLevel && m_nAngryCnt%2 == 0 && m_nActionStopCnt%(int)(nActionStopInterval*m_fAtackLevel) != 0 )
			m_nActionStopCnt ++;
	}

	// End ActionStop
}

void Devil::DownCount( int nAmount, bool bFlg ) {

	m_nBeamCnt -= nAmount;
	if( m_nBeamCnt < 1 )
		m_nBeamCnt = 1;

	m_nBulletCnt -= nAmount;
	if( m_nBulletCnt < 1 )
		m_nBulletCnt = 1;
	
	m_nCorpsCnt -= nAmount;
	if( m_nCorpsCnt < 1 )
		m_nCorpsCnt = 1;

	if( !bFlg )
		return;
	
	m_nActionStopCnt -= nAmount;
	if( m_nActionStopCnt < 1 )
		m_nActionStopCnt = 1;

	m_nInvincibleCnt -= nAmount;
	if( m_nInvincibleCnt < 1 )
		m_nInvincibleCnt = 1;
}

void Devil::FreeFunction(){
	m_Object3D.SetAnimFlg(true);
	m_Object3D.GetAnimationManager()->ChangeAnimation( "Wait", true );
	m_Object3D.GetAnimationManager()->ChangeAnimation( "Death", true );
}

D3DXVECTOR3 Devil::Random() {
	
	D3DXVECTOR3 Random = D3DXVECTOR3(0,0,0);
	switch( rand()%9 ) {
	case 0:
		Random.x += RANDOM_X; 
		Random.y += RANDOM_Y; 
		Random.z += RANDOM_Z; 
		break;
	case 1:
		Random.x -= RANDOM_X; 
		Random.y += RANDOM_Y; 
		Random.z -= RANDOM_Z; 
		break;
	case 2:
		Random.x -= RANDOM_X; 
		Random.y -= RANDOM_Y; 
		Random.z += RANDOM_Z; 
		break;
	case 3:
		Random.x += RANDOM_X; 
		Random.y -= RANDOM_Y; 
		Random.z -= RANDOM_Z; 
		break;
	case 4:
		Random.x -= RANDOM_X; 
		Random.y += RANDOM_Y; 
		Random.z += RANDOM_Z; 
		break;
	case 5:
		Random.x += RANDOM_X; 
		Random.y -= RANDOM_Y; 
		Random.z += RANDOM_Z; 
		break;
	case 6:
		Random.x += RANDOM_X;
		Random.y += RANDOM_Y;
		Random.z -= RANDOM_Z;
		break;
	case 7:
		Random.x -= RANDOM_X; 
		Random.y -= RANDOM_Y; 
		Random.z -= RANDOM_Z; 
		break;
	default:
		break;
	}

	//Random.y = -15.0f;

	return Random;
}

int* Devil::GetInt(){
	return &m_nLevel;
}

bool* Devil::GetBool(){
	return &m_bBeam;
}