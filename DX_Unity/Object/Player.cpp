//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Player.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Player.h"
#include "NearAtack.h"
#include "FarAtack.h"
#include "PlayerFog.h"
#include "Shadow.h"
#include "Deathblow.h"
#include "FadeIn.h"
#include "DeathblowEffect.h"
#include "Pause.h"
#include "Item.h"
#include "../Library/Task/SceneManager.h"
#include "../Library/DirectX/DirectSound.h"

#include "CameraSelect.h"

// -- 定数
//const float fRotSpeed = 0.0075f; // カメラの回転量
const float fMoveSpeed = 0.2f; // 通常移動量
const float fRun = 1.5f;		// 走っているときの速さ
const float fMoveRot = 0.03f;	// 移動時の回転量
const int nChangeTime = 45;		// 武器変更にかかる時間
const float fCollision = 0.85f; 
const int nMaxReverberation = 210;
const int nItemInterval = 1800; // nItemInterval/60秒に1回4分の3の確率でアイテム落ちる
const float fAvoidSpeed = 4.5f;

const int nMaxAvoidTime = 10;

// -- マクロ
#define RotSpeed (11.25f/(float)(CWindow::Create()->GetClientWidth()))
#define RANDOM_X (rand()%50*0.01f)
#define RANDOM_Y (rand()%100*0.01f)
#define RANDOM_Z (rand()%50*0.01f)

Player::Player()//:m_bNearAtack(false)
				//,m_bChange(false)   
				//,m_bAtack(false)  
				//,m_bDeathblow(false) 
				//,m_fMaxRot(fInitRot*fMagnification) {
{
	m_Name = "Player";
	m_Object3D.SetFileName(_T("Player.x"));
	m_pDirectInputManager = CDirectInputManager::Instance();
	
	m_pHierarchy = Hierarchy::Create();
	
	// BulletFog取得
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
}

Player::~Player(){

}

void Player::Awake(){

	ReInit();
	m_bNearAtack = false;
	m_bChange = false;  
	m_bAtack = false;
	m_bDeathblow = false;
	m_bGaugeMax = false;
	m_bPause = false;
	m_fMaxRot = fInitRot*fMagnification;
	m_nItemCnt = 1;
	m_nAccumulationDamage = 0;
	m_nAvoidTime = 0;
	m_bAvoid = false;
	m_AvoidAmount = D3DXVECTOR3(0,0,0);
	m_pCamera = Hierarchy::Create()->FindWithName("PlayerCamera");
	m_pCameraSelect = Hierarchy::Create()->FindWithName("CameraSelect");
	
	// 影生成
	GameObject* pObj = m_pHierarchy->CreateObject(new Shadow);
	pObj->SetParent(this);
	pObj->Start();
	*(pObj->GetScale()) *= 2.0f;

	Move( D3DXVECTOR3(0,1.2f,-40.0f) );
	
	m_pPlayerFogParent = m_pHierarchy->FindWithName("PlayerFogParent");

	SetLife(20); // 1で死亡
	m_nOldLife = m_nLife;
	m_fDeathblowGauge = 0.0f; // 0.0f
	m_nReverberation = 0;

	// コリジョン設定
	SetCollisionCubeSize(D3DXVECTOR3(fCollision,2.0f,fCollision), D3DXVECTOR3(fCollision,2.0f,fCollision));

	// Debug
	//m_fDeathblowGauge =	100.0f; // 0.0f
}

void Player::Update(){

	// 攻撃を食らっていた場合、累積ダメージを増やす
	if( m_nOldLife != m_nLife ) {
		int i = m_nOldLife - m_nLife;
		if( i > 0 ) { // 回復している場合は入らない 
			m_nAccumulationDamage += i;
			// 画ブレ
			*(m_pCameraSelect->GetVec()) = D3DXVECTOR3( 10.0f, 1.0f, 0 );
		}
	}

	if( m_nItemCnt%nItemInterval == 0 ) { //&& rand()%6 != 0 ) {
		m_pHierarchy->CreateObject(new Item)->Start();
		m_nItemCnt = 1;
	}
	else
		m_nItemCnt ++;

	// Player死亡判定
	if( m_nLife <= 1 ){
		SceneManager::Create()->SetGameOver();
		return;
	}

	// UpdateしているのでPause中ではない
	m_bPause = false;

	// 移動
	if( !m_bAvoid ) {
		if( !m_bDeathblow ) {
			CharaMove();
		}
	}
	else {
		AvoidMove();
	}

	// 攻撃してないなら
	if( !m_bDeathblow && !m_bChange  )
		Atack();

	// Fog作成
	if( m_fDeathblowGauge >= fMaxDeathblowGauge || m_bDeathblow ) {
		CreateFog();
	}

	// 武器変更命令
	if( (m_pDirectInputManager->GetMouseTrigger(1) || m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_08)) && !m_bChange && !m_bDeathblow ) {
		m_bChange = true;
		m_nChangeCnt = 0;
	}

	// 必殺技発動！！
	if( m_fDeathblowGauge >= fMaxDeathblowGauge && 
		(m_pDirectInputManager->GetMouseTrigger(2) || m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_07)) && !m_bChange && !m_bDeathblow ) {
		CreateDeathblow();
	}

	// チェンジ
	if( m_bChange )
		Change();

	// 必殺技のあと暫くは無敵継続
	if( !m_bCollision && !m_bDeathblow ) {
		m_nReverberation ++;
		if( m_nReverberation >= nMaxReverberation ) {
			m_bCollision = true;
			m_nReverberation = 0;
		}
	}

	// 必殺ゲージ増加
	if( m_fDeathblowGauge < fMaxDeathblowGauge && !m_bDeathblow ) {
		m_fDeathblowGauge += fMaxDeathblowGauge/fDeathblowTime; // 放置でも30秒で溜まる
		//m_fDeathblowGauge += 0.3f;
	}
	
	// Pause
	// 判定をとるクラスを別で用意したい
	// PlayerのUpdateで判定をとるとPlayerの更新が止まる場合、ポーズ出来なくなってしまうため
	if( m_pDirectInputManager->GetKeyboardTrigger( DIK_LCONTROL ) || 
		m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_10) ) {
		m_pHierarchy->CreateObject(new Pause);
		PlaySound(CLICK);
		Rotation( D3DXVECTOR3(-m_Rotation.x,0,-m_Rotation.z) );
		m_bPause = true;
	}

	// 例外チェック実施
	ExceptionCheck();

	// コリジョン前のライフを保存
	m_nOldLife = m_nLife;
}

// ---- 描画
void Player::Draw(){
	
	// --- Debug
	if((m_pDirectInputManager->GetKeyboardHold(DIK_G) || m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_12)) && m_nLife <= 20) {
		m_nLife++;
	}
	if((m_pDirectInputManager->GetKeyboardHold(DIK_F) || m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_11))) {
		m_fDeathblowGauge += 1.0f;
	}
	// ---
	
	// 回転
	if( !m_bPause ) {

		const float fJoyRiv = 3.0f;
		if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_04)) {
			Rotation( D3DXVECTOR3(0, -RotSpeed * fJoyRiv, 0));
		} else if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_02)) {
			Rotation( D3DXVECTOR3(0, RotSpeed * fJoyRiv, 0) );
		} else {
			Rotation( D3DXVECTOR3(0, m_pDirectInputManager->GetMouseMoveX()*RotSpeed,0) );
		}
	}

	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}

void Player::FastDraw(){
	if( m_fDeathblowGauge >= fMaxDeathblowGauge ) {
		m_fDeathblowGauge = fMaxDeathblowGauge;
		if( !m_bGaugeMax ) {
			PlaySound(DEATHBLOWGAUGEMAX);
			m_bGaugeMax = true;
		}
	}
}

void Player::AvoidMove() {

	// 回避実行
	Move( m_AvoidAmount );
	
	// エフェクト
	for( int i = 0; i < 10; i++ ) {
		
		// エフェクト作成
		D3DXVECTOR3 Random = D3DXVECTOR3(0,0,0);
		if( rand()%2 ) {
			Random.y += RANDOM_Y;
		}
		else {
			Random.y -= RANDOM_Y;
		}
		switch( rand()%4 ) {
		case 0:
			Random.x += RANDOM_X; 
			Random.z += RANDOM_Z; 
			break;
		case 1:
			Random.x -= RANDOM_X; 
			Random.z += RANDOM_Z; 
			break;
		case 2:
			Random.x += RANDOM_X; 
			Random.z -= RANDOM_Z; 
			break;
		case 3:
			Random.x -= RANDOM_X; 
			Random.z -= RANDOM_Z; 
			break;
		default:
			break;
		}

		GameObject* pObj = m_pBulletFogParent->CreateChild( D3DXCOLOR(0.1f,0.3f,1.0f,0.5f), 1.0f, 0.5f );
		*(pObj->GetPosition()) = m_Position+Random;
		*(pObj->GetScale()) = D3DXVECTOR3(1.5f,1.5f,1.5f);
	}

	m_nAvoidTime ++;

	if( m_nAvoidTime >= nMaxAvoidTime ) {
		m_nAvoidTime = 0;
		m_bAvoid = false;
		m_AvoidAmount = D3DXVECTOR3(0,0,0);
		m_fMaxRot = fInitRot*fMagnification;
		m_fDeathblowGauge -= 10.0f;
		if( (!m_pDirectInputManager->GetKeyboardHold(DIK_A)   && !m_pDirectInputManager->GetKeyboardHold(DIK_D)) ||
			(m_pDirectInputManager->GetKeyboardHold(DIK_A) && m_pDirectInputManager->GetKeyboardHold(DIK_D)) )
			Rotation( D3DXVECTOR3(0,0,-m_Rotation.z) );
		if( (!m_pDirectInputManager->GetKeyboardHold(DIK_W) && !m_pDirectInputManager->GetKeyboardHold(DIK_S)) ||
			(m_pDirectInputManager->GetKeyboardHold(DIK_W) && m_pDirectInputManager->GetKeyboardHold(DIK_S)) )
			Rotation( D3DXVECTOR3(-m_Rotation.x,0,0) );
		//Rotation( D3DXVECTOR3(-m_Rotation.x,0,-m_Rotation.z) );
	}
}

// DeathblowGaugeを返す
float* Player::GetFloat(){

	return &m_fDeathblowGauge;
}

// 必殺フラグを返す
bool* Player::GetBool(){
	return &m_bDeathblow;
}

// 累積ダメージを返す(Clear時以外使わない)
int* Player::GetInt(){
	return &m_nAccumulationDamage;
}

// ---- Playerの移動
bool Player::CharaMove(){

	 m_fMove = 0.0f;
	float fRot = 0.0f; 
	D3DXVECTOR3 MoveRot = D3DXVECTOR3(0,0,0);

	// 移動
	if( m_pDirectInputManager->GetLeftHold() ){
		m_fMove = fMoveSpeed; // 移動
		fRot = -(Pai/2.0f);

		// -- Player回転
		if( m_Rotation.z <= m_fMaxRot )
			MoveRot.z += fMoveRot;
	}
	else if( m_pDirectInputManager->GetRightHold() ){
		m_fMove = fMoveSpeed;	// 移動
		fRot = (Pai/2.0f);
		
		// -- Player回転
		if( m_Rotation.z - Pai*2.0f >= -m_fMaxRot || m_Rotation.z == 0.0f )
			MoveRot.z -= fMoveRot;
	}
	if( m_pDirectInputManager->GetForwardHold() ){
		m_fMove = fMoveSpeed;	// 移動

		// -- Player回転
		if( m_Rotation.x <= m_fMaxRot )
			MoveRot.x += fMoveRot;

		// -- 斜め移動チェック
		if( m_pDirectInputManager->GetLeftHold())
			fRot = -(Pai/4.0f);
		else if( m_pDirectInputManager->GetRightHold() )
			fRot = (Pai/4.0f);
	}
	else if( m_pDirectInputManager->GetBackHold() ){
		m_fMove = fMoveSpeed;	// 移動
		fRot = Pai;

		// -- Player回転
		if( m_Rotation.x - Pai*2.0f >= -m_fMaxRot || m_Rotation.x == 0.0f )
			MoveRot.x -= fMoveRot;

		// -- 斜め移動チェック
		if( m_pDirectInputManager->GetLeftHold() )
			fRot = -(Pai/4.0f)-(Pai/2.0f);
		else if( m_pDirectInputManager->GetRightHold() )
			fRot = (Pai/4.0f)+(Pai/2.0f);
	}

	// 速度UPするか
	//if( m_bDeathblow )
	//	m_fMove *= fRun*1.5f;
	//if( m_bNearAtack )
	
	// 姿勢を元に戻す
	if( m_pDirectInputManager->GetKeyboardRelease(DIK_A) || m_pDirectInputManager->GetKeyboardRelease(DIK_D) || 
		m_pDirectInputManager->GetJoyAxisRelease(0, JOY_X) || 
		(m_pDirectInputManager->GetKeyboardTrigger(DIK_A) && m_pDirectInputManager->GetKeyboardHold(DIK_D)) )
		Rotation( D3DXVECTOR3(0,0,-m_Rotation.z) );
	if( m_pDirectInputManager->GetKeyboardRelease(DIK_W) || m_pDirectInputManager->GetKeyboardRelease(DIK_S) ||
		m_pDirectInputManager->GetJoyAxisRelease(0, JOY_Y) ||
		(m_pDirectInputManager->GetKeyboardTrigger(DIK_W) && m_pDirectInputManager->GetKeyboardHold(DIK_S)) )
		Rotation( D3DXVECTOR3(-m_Rotation.x,0,0) );

	// 移動実行
	if( m_fMove != 0.0f ) {
		
		m_fMove *= fRun;
	

		// 移動するときにSHIFTが押されたら
		if( (m_pDirectInputManager->GetKeyboardTrigger(DIK_LSHIFT) || m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_05)) && m_fDeathblowGauge >= 10.0f ) {
			m_bAvoid = true;
			m_AvoidAmount = D3DXVECTOR3( m_fMove*sinf(m_Rotation.y+fRot), 0, m_fMove*cosf(m_Rotation.y+fRot) );
			m_AvoidAmount *= fAvoidSpeed;
			m_nAvoidTime = 0;
			
			m_fMaxRot = fInitRot*fMagnification*3.0f;
			
			// 回転実行
			Rotation(MoveRot*20.0f);

			// SE再生
			PlaySound(AVOID);

			return true;
		}
		
		// 回転実行
		Rotation(MoveRot);

		Move(D3DXVECTOR3( m_fMove*sinf(m_Rotation.y+fRot), 0, m_fMove*cosf(m_Rotation.y+fRot) ) );

		return true;
	} 
	
	Rotation( D3DXVECTOR3(-m_Rotation.x,0,-m_Rotation.z) );
	return false;
}

// ---- 攻撃
void Player::Atack(){
	
	if( m_pDirectInputManager->GetMouseHold(0) || m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_06) ){

		// 必殺技
		if( m_bDeathblow || CameraSelect::GetCameraState() == CAMERA_DEATHBLOW ) 
			return;

		// 近接
		if( m_bNearAtack ) {
			NearAtack Atk;
			for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
				if( (*Ite)->GetName() == "NearAtack" )
					Atk.GetDownCastClass(*Ite)->Atack();
		}
		// 遠距離
		else {
			FarAtack Atk;
			for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
				if( (*Ite)->GetName() == "FarAtack" )
					Atk.GetDownCastClass(*Ite)->Atack();
		}
	}
}

// ---- 武器切り替え
void Player::Change(){

	// 武器の大きさを変更
	D3DXVECTOR3 NearScale = D3DXVECTOR3(1.5f/(float)nChangeTime,1.5f/(float)nChangeTime,1.5f/(float)nChangeTime);
	D3DXVECTOR3 FarScale = D3DXVECTOR3(1.0f/(float)nChangeTime,1.0f/(float)nChangeTime,1.0f/(float)nChangeTime);
	
	// チェンジカウントを増やす
	m_nChangeCnt ++;

	// 名前を比較するため
	NearAtack Near;
	FarAtack Far;
	
	// 現在近接攻撃なら
	if( m_bNearAtack ){
		for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {

			// 近接をひっこめる
			if( (*Ite)->GetName() == Near.GetName() ) 
				(*Ite)->ScaleChange( -NearScale );

			// 遠距離をだす
			if( (*Ite)->GetName() == Far.GetName() ) { 
				(*Ite)->ScaleChange( FarScale );
			}
		}
	}
	// 現在遠距離攻撃なら
	else {
		for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
			
			// 近接をだす
			if( (*Ite)->GetName() == Near.GetName() ) 
				(*Ite)->ScaleChange( NearScale );
			
			// 遠距離をひっこめる
			if( (*Ite)->GetName() == Far.GetName() ) { 
				(*Ite)->ScaleChange( -FarScale );
			}
		}
	}

	if( m_nChangeCnt >= nChangeTime ){

		// 武器チェンジ終了
		m_bChange = false;
		
		// フラグ入れ替え
		m_bNearAtack = !m_bNearAtack;
		
		m_fMaxRot = fInitRot*fMagnification;
	}
}

// --- 必殺技発動！
void Player::CreateDeathblow() {
	
	PlaySound(CLICK);
	m_bGaugeMax = false;

	// 作成
	GameObject* pObj = m_pHierarchy->CreateObject(new Deathblow);
	*(pObj->GetPosition()) = m_Position;
	pObj->Start();

	// エフェクト作成
	m_pHierarchy->CreateObject(new DeathblowEffect);

	// フラグON
	m_bDeathblow = true;

	// 無敵状態
	m_bCollision = false;
	
	// 姿勢を元に戻す
	Rotation( D3DXVECTOR3(-m_Rotation.x,0,-m_Rotation.z) );

	// 
	CameraSelect::SetState(CAMERA_DEATHBLOW);
}

// ---- PlayerのParticle作成マシン
void Player::CreateFog(){

	if( m_bDeathblow ) {
		GameObject* pFog = m_pPlayerFogParent->CreateChild();
		pFog->ReInit();
		*(pFog->GetPosition()) = m_Position;
		*(pFog->GetRotation()) = m_Rotation;
		pFog->Start();
		pFog->FreeFunction();
	}

	else if( rand()%3 == 0 ) {
		GameObject* pFog = m_pPlayerFogParent->CreateChild();
		pFog->ReInit();
		*(pFog->GetPosition()) = m_Position;
		*(pFog->GetRotation()) = m_Rotation;
		pFog->Start();
	}
}

// ---- ゲッター
bool Player::GetNearAtackFlg(){
	return m_bNearAtack;
}


