//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Wizard.cpp]
// author : 大洞祥太d
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Wizard.h"
#include "Shadow.h"
#include "ShadowBall.h"
#include "WizardImpactParent.h"
#include "../Library/Task/Empty.h"
#include "BeamHolder.h"
#include "../Library/DirectX/DirectSound.h"

// --- 定数
const int nFarInterval = 41;
const int nNearInterval = 52;
const int nAssaultInterval = 48;
const float fCollision = 0.5f; 
const int nNearAtackTime = 60;
const int nTeleportationTime = 1200;
const float fChaseSpeed = 45.0f;
const float fInitPos = 31.8f;
const float fAssaultRot = 0.6f;

const float fBorder = 25.0f; // NearとFarの境界

const int nBeamLife = 180;
const int nBeamLength = 30;
const int nBeamInterval = 60;
const D3DXVECTOR3 BeamPos = D3DXVECTOR3(0,0,0);
const D3DXVECTOR3 BeamScale = D3DXVECTOR3(1,1,1);

// --- マクロ
#define TELEPORT_X (rand()%(450+50)*0.1f)
#define TELEPORT_Z (rand()%(450+50)*0.1f)
#define RANDOM (rand()%1000*0.001f)

Wizard::Wizard()//:m_nAtackCnt(1)
				//,m_nTeleportationCnt(0)
				//,m_fAtackRot(0)
				//,m_bStart(false) {
{
	m_Name = "Wizard";
	m_Object3D.SetFileName(_T("Wizard.x"));
	m_Tag = "Boss";
	
	// Task取得
	m_pHierarchy = Hierarchy::Create();
	
	m_pImpactParent = m_pHierarchy->CreateObject(new WizardImpactParent);
	m_pImpactParent->BanDestroy();
	for( int i = 0; i < 50; i++ )
		m_pImpactParent->CreateChild();
	for( auto Ite = m_pImpactParent->GetChild()->begin(); Ite != m_pImpactParent->GetChild()->end(); Ite++ )
		(*Ite)->SetActive(false);
		
	m_pWizardCollision = m_pHierarchy->CreateObject(new Empty("WizardCollision"));
	m_pWizardCollision->BanDestroy();
	
	// 影作成
	GameObject* pObj = m_pHierarchy->CreateObject(new Shadow);
	pObj->SetParent(this);
	pObj->Start();
	*(pObj->GetScale()) *= 2.0f;
	
	WizardFogParent FogParent;
	m_pFogParent = FogParent.GetDownCastClass(m_pHierarchy->FindWithName("WizardFogParent"));
	
	// BulletFog取得
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
}

Wizard::~Wizard(){

}

void Wizard::Awake() {

	ReInit();
	m_nAtackCnt = 1;
	m_nTeleportationCnt = 0;
	m_fAtackRot = 0;
	m_bStart = false;

	if( FindChild("WizardWeapon") )
		*(FindChild("WizardWeapon")->GetPosition()) = m_Position;

	// 初期位置
	Move( D3DXVECTOR3(0,fInitPos,0) );
	Rotation( D3DXVECTOR3(0,Pai,0) );

	// 必要情報を取得、生成
	m_pPlayer = m_pHierarchy->FindWithName("Player");

	// ライフ設定
	m_nLife = 5000; // 5000	

	// コリジョン設定
	SetCollisionCubeSize(D3DXVECTOR3(fCollision,1.5f,fCollision), D3DXVECTOR3(fCollision,1.5f,fCollision));
	
	// スケール変更
	ScaleChange(D3DXVECTOR3(0.5f,0.5f,0.5f));

	// フラグOFF
	m_bBeam = false;
	m_bAssault = false;
}

void Wizard::Update(){

	if( !m_bStart && m_Position.y <= fInitPos-30.0f )
		m_bStart = true;
	
	// まだ戦闘開始じゃない
	if( !m_bStart ) {

		Move( D3DXVECTOR3(0,-0.5f,0) );

		return;
	}

	// 一定のライフが減ると瞬間移動
	if( m_nLife % 88 == 0 && m_fAtackRot == 0 && !m_bAssault ) {
		m_nTeleportationCnt = nTeleportationTime-1;
		m_nLife -= 4;
	}

	float fDistanceX = m_pPlayer->GetPosition()->x - m_Position.x;
	float fDistanceY = m_pPlayer->GetPosition()->y - m_Position.y;
	float fDistanceZ = m_pPlayer->GetPosition()->z - m_Position.z;
	
	// プレイヤーとの距離は近距離
	if( sqrt( fDistanceX*fDistanceX + fDistanceZ*fDistanceZ ) <= fBorder ) {

		m_bNear = true;
		
		// 攻撃していない時は少しづつ近づく
		if( m_fAtackRot == 0 && !m_bAssault && m_pPlayer->GetCollisionFlg() )
			Move( D3DXVECTOR3( fDistanceX/fChaseSpeed, 0, fDistanceZ/fChaseSpeed ) );
	}
	// 遠距離
	else 
		m_bNear = false;

	// 攻撃を行うかチェック
	CheckAtack();

	// カウント増加
	m_nAtackCnt++;
	if( !m_bBeam )
		m_nTeleportationCnt++;

	// プレイヤーのほうを向かせる
	if( !m_bAssault )
		Rotation(D3DXVECTOR3(0,(atan2f(fDistanceX,fDistanceZ)-m_Rotation.y),0));

	// Knife攻撃実行中
	if( m_fAtackRot != 0 ) 
		KnifeAtack();

	// Assault攻撃実行中
	if( m_bAssault )
		AssaultAtack();

	// ビーム移動(打った時の向きに直進)
	if( m_bBeam ) {
		m_pBeamHolder->Move(m_Move);

		// 移動スピードアップ
		/*if( m_nAtackCnt%nBeamLength == 0 )
			m_Move *= 3.0f;*/

		// ビーム終了
		if( m_nAtackCnt%(nBeamLife+nBeamLength+1) == 0 ) {
			m_bBeam = false;
			m_nAtackCnt = 1;
		}
	}

	// 瞬間移動するか
	Teleportation();

	// 例外チェック
	ExceptionCheck();

#if _DEBUG
	std::cout << "HP : " << m_nLife << std::endl;
#endif

}

void Wizard::FastDraw(){
	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}

// 攻撃を行うかチェック
void Wizard::CheckAtack(){
	
	// Knife
	if( m_bNear && m_fAtackRot == 0 && !m_bAssault && m_nAtackCnt%nNearInterval == 0 && !m_bBeam && rand()%2 ) {
		m_fAtackRot = Pai*2.0f/(nNearAtackTime-1)*4.0f;
		m_nAtackCnt = 1; // カウント初期化
	}

	// Assault
	else if( m_bNear && m_fAtackRot == 0 && !m_bAssault && m_nAtackCnt%nAssaultInterval == 0 && !m_bBeam && rand()%2 ) {
		m_bAssault = true;
		m_nAtackCnt = 1;
	}

	// ShadowBall
	if( !m_bNear && m_fAtackRot == 0 && m_nAtackCnt%nFarInterval == 0 && !m_bBeam && rand()%2 ) {
			
		// 攻撃オブジェクトを作成
		GameObject* pObj = m_pHierarchy->CreateObject(new ShadowBall);
		pObj->SetParent(m_pWizardCollision);
		*(pObj->GetRotation()) = m_Rotation; 
		*(pObj->GetPosition()) = m_Position + D3DXVECTOR3(1*sinf(m_Rotation.y), 1.0f, 1*cosf(m_Rotation.y)); 
		pObj->Start(); 
		m_nAtackCnt = 1; // カウント初期化
		PlaySound(WIZARDBULLET);
	}
	
	// Beam
	else if( !m_bNear && m_nAtackCnt%nBeamInterval == 0 && !m_bBeam && rand()%2 ) {
		m_pBeamHolder = m_pHierarchy->CreateObject(new BeamHolder( D3DXCOLOR(1.0f,0.5f,0.2f,1.0f), nBeamLength, nBeamLife, BeamPos, BeamScale, true, true ));
		m_pBeamHolder->Start();
		*(m_pBeamHolder->GetPosition()) = m_Position;
		*(m_pBeamHolder->GetRotation()) = m_Rotation;
		m_bBeam = true;
		m_Move = D3DXVECTOR3(0.8f*sinf(m_Rotation.y), 0, 0.8f*cosf(m_Rotation.y)); 
		m_nAtackCnt = 1; // カウント初期化
		PlaySound(WIZARDBEAM);
	}
}

// 瞬間移動
void Wizard::Teleportation() {

	// テレポート可能時間
	if( m_nTeleportationCnt%nTeleportationTime == 0 && m_fAtackRot == 0 && !m_bAssault ) {
		// 瞬間移動します
		D3DXVECTOR3 move = D3DXVECTOR3(0,0,0);
		
		for( int i = 0; i < 180; i++) {
			// Fog作成
			GameObject* pFog = m_pFogParent->CreateChild();
			pFog->ReInit();
			*(pFog->GetPosition()) = m_Position+Random();
			*(pFog->GetRotation()) = m_Rotation;
			pFog->Start();
		}

		// 移動座標決定
		if( rand()%2 )
			move.x = TELEPORT_X;
		else
			move.x = -TELEPORT_X;

		if( rand()%2 )
			move.z = TELEPORT_Z;
		else
			move.z = -TELEPORT_Z;

		// 移動実行、攻撃カウント初期化(移動していきなりの攻撃を防ぐため)
		Move( D3DXVECTOR3( -m_Position.x, 0, -m_Position.z ) ); // 0に戻して
		Move( D3DXVECTOR3( move.x, 0, move.z ) );
		m_nAtackCnt = 1;
		
		PlaySound(WIZARDTELEPORT);
	}

	// 攻撃が終わり次第、回転するようにする
	if( m_nTeleportationCnt%nTeleportationTime == 0 && m_fAtackRot != 0 ) 
		m_nTeleportationCnt --;
}

// Knife攻撃
void Wizard::KnifeAtack(){
	
	GameObject* pWeapon = FindChild("WizardWeapon");
	pWeapon->Rotation(D3DXVECTOR3(0,m_fAtackRot,0));
	
	// 攻撃開始から15F目で当たり判定を実装
	if( m_nAtackCnt == 30 ) {
		
		// 当たり判定を作成
		GameObject* pObj = m_pHierarchy->CreateObject(new Empty("WizardKnife"));
		pObj->SetParent(m_pWizardCollision);
		pObj->SetLife(nNearAtackTime-m_nAtackCnt-5);
		pObj->SetCollisionCubeSize( D3DXVECTOR3(3.0f,5.0f,3.0f), D3DXVECTOR3(3.0f,5.0f,3.0f) );
		*(pObj->GetPosition()) = m_Position;
		PlaySound(WIZARDNEAR);
	}
	
	GameObject* pCol = m_pWizardCollision->FindChild("WizardKnife");
	// 当たり判定が生成されているなら
	if( pCol ) {
		
		m_Move = D3DXVECTOR3(0.8f*sinf(m_Rotation.y), 0, 0.8f*cosf(m_Rotation.y)); 

		// 命削って
		pCol->SetLife(-1);
		
		// --- 衝撃波作成
		for( int i = 0; i < 2; i++ ) {
			GameObject* pObj = m_pImpactParent->CreateChild();
			pObj->ReInit();
			*(pObj->GetRotation()) = *(pWeapon->GetRotation());
			*(pObj->GetPosition()) = *(pWeapon->GetPosition())+D3DXVECTOR3(0.4f,0.3f,0.4f);
			pObj->Start();
		}
	}

	// 終了
	if( m_nAtackCnt%nNearAtackTime == 0 ) {
		m_fAtackRot = 0;
		m_nAtackCnt = 1;
	}
}

// Assault攻撃
void Wizard::AssaultAtack(){
	
	GameObject* pWeapon = FindChild("WizardWeapon");

	// 攻撃開始から40F目で当たり判定を実装
	if( m_nAtackCnt <= 40 ) {
		
		Rotation( D3DXVECTOR3(fAssaultRot/40,0,0) );

		// 当たり判定を作成
		if( m_nAtackCnt < 40 )
			return;

		GameObject* pObj = m_pHierarchy->CreateObject(new Empty("WizardAssault"));
		pObj->SetParent(m_pWizardCollision);
		pObj->SetLife(20);
		pObj->SetCollisionCubeSize( GetCollisionCubePlusSize()*1.5f, GetCollisionCubeMinusSize()*1.5f );
		*(pObj->GetPosition()) = m_Position;
		*(pObj->GetRotation()) = m_Rotation;
		
		m_Move = D3DXVECTOR3(0.8f*sinf(m_Rotation.y), 0, 0.8f*cosf(m_Rotation.y)); // 移動量保存
		PlaySound(DRAGONASSAULT);
	}
	
	GameObject* pCol = m_pWizardCollision->FindChild("WizardAssault");
	// 当たり判定が生成されているなら
	if( pCol ) {

		// 移動
		Move(m_Move);

		// コリジョン移動
		pCol->Move(m_Move);

		// 命削って
		pCol->SetLife(-1);

		// エフェクト作成
		for( int i = 0; i < 4; i++ )
			*(m_pBulletFogParent->CreateChild(D3DXCOLOR(0.1f,1.0f,0.1f,0.5f))->GetPosition()) = m_Position+Random();
	}

	// 終了
	if( m_nAtackCnt%nNearAtackTime/2 == 0 ) {
		Rotation( D3DXVECTOR3(-m_Rotation.x,0,0) );
		m_bAssault = false;
		m_nAtackCnt = 1;
	}
}

D3DXVECTOR3 Wizard::Random() {
	
	D3DXVECTOR3 Random = D3DXVECTOR3(0,0,0);
	switch( rand()%9 ) {
	case 0:
		Random.x += RANDOM; 
		Random.y += RANDOM; 
		Random.z += RANDOM; 
		break;
	case 1:
		Random.x -= RANDOM; 
		Random.y += RANDOM; 
		Random.z -= RANDOM; 
		break;
	case 2:
		Random.x -= RANDOM; 
		Random.y -= RANDOM; 
		Random.z += RANDOM; 
		break;
	case 3:
		Random.x += RANDOM; 
		Random.y -= RANDOM; 
		Random.z -= RANDOM; 
		break;
	case 4:
		Random.x -= RANDOM; 
		Random.y += RANDOM; 
		Random.z += RANDOM; 
		break;
	case 5:
		Random.x += RANDOM; 
		Random.y -= RANDOM; 
		Random.z += RANDOM; 
		break;
	case 6:
		Random.x += RANDOM; 
		Random.y += RANDOM; 
		Random.z -= RANDOM; 
		break;
	case 7:
		Random.x -= RANDOM; 
		Random.y -= RANDOM; 
		Random.z -= RANDOM; 
		break;
	default:
		break;
	}

	return Random;
}