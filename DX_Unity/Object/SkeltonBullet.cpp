//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SkeltonBullet.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SkeltonBullet.h"
#include "BulletFog.h"
#include "Shadow.h"

// --- 定数
const float fMoveTime = 60.0f;
const float fNear = 1.0f;
const float fMoreNear = 0.5f;

// --- マクロ 
#define RANDOM (rand()%300*0.01f)

SkeltonBullet::SkeltonBullet() {
	m_Name = "SkeltonBullet";
	m_Object3D.SetFileName(_T("Skeleton.x"));

	m_pHierarchy = Hierarchy::Create();

	// BulletFog取得
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
}

SkeltonBullet::~SkeltonBullet() {
	
}

bool SkeltonBullet::Start(){

	float fMove = 0.0f;
	if( rand()%2 ) 
		fMove += RANDOM;
	else
		fMove -= RANDOM;

	Move( D3DXVECTOR3(fMove,4.25f,0) );
	GameObject* pPlayer = Hierarchy::Create()->FindWithName("Player");
	if( pPlayer ) {
		m_Move = D3DXVECTOR3((pPlayer->GetPosition()->x - m_Position.x) / fMoveTime,
							 (pPlayer->GetPosition()->y - m_Position.y) / fMoveTime, 
							 (pPlayer->GetPosition()->z - m_Position.z) / fMoveTime );
	}
	else {
		switch( rand()%4 ) {
		case 0:
			m_Move = D3DXVECTOR3(  RANDOM, -RANDOM,  RANDOM );
			break;
		case 1:
			m_Move = D3DXVECTOR3( -RANDOM, -RANDOM,  RANDOM );
			break;
		case 2:
			m_Move = D3DXVECTOR3(  RANDOM, -RANDOM, -RANDOM );
			break;
		case 3:
			m_Move = D3DXVECTOR3( -RANDOM, -RANDOM, -RANDOM );
			break;
		}
	}

	// 距離が近いと遅すぎるため、補正
	if( m_Move.x < fNear && m_Move.x > -fNear && m_Move.z < fNear && m_Move.z > -fNear )
		m_Move *= 1.7f;

	if( m_Move.x < fMoreNear && m_Move.x > -fMoreNear && m_Move.z < fMoreNear && m_Move.z > -fMoreNear ) {
		m_Move *= 1.1f;
		m_Rotation.x += Vector( m_Position, *(pPlayer->GetPosition()) );
	}
	
	// コリジョン設定
	SetCollisionCubeSize(D3DXVECTOR3(0.15f,0.15f,0.15f), D3DXVECTOR3(0.15f,0.15f,0.15f));

	// スケール調整
	ScaleChange(D3DXVECTOR3(4,4,4));

	return true;
}

void SkeltonBullet::Update(){

	if( m_Child.empty() ) {
		// 影作成
		GameObject* pObj = m_pHierarchy->CreateObject(new Shadow);
		pObj->SetParent(this);
		*(pObj->GetPosition()) = m_Position;
		pObj->Start();
	}

	// 移動
	Move(m_Move);
	
	// エフェクト作成
	for( int i = 0; i < 5; i++ ) {
		GameObject* pObj = m_pBulletFogParent->CreateChild(D3DXCOLOR(0.5f,0.1f,0.1f,0.75f));
		*(pObj)->GetPosition() = m_Position + RandomPos();
		*(pObj)->GetScale() = D3DXVECTOR3(1,1,1);
	}

	// 範囲外判定
	if( m_Position.y <= 0 ) {
		m_nLife = 0;
	}
}

void SkeltonBullet::Draw(){
	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}

float SkeltonBullet::Vector(D3DXVECTOR3 MyPos, D3DXVECTOR3 OpoPos){
	
	///float fDistanceX = OpoPos.x - MyPos.x;
	float fDistanceY = OpoPos.y - MyPos.y;
	float fDistanceZ = OpoPos.z - MyPos.z;
	float fRot = atan2f(fDistanceY,fDistanceZ);

	if( fDistanceZ < 0.0f )
		fRot -= Pai;
	else 
		fRot -= (Pai + Pai/2);

	return fRot;
}

D3DXVECTOR3 SkeltonBullet::RandomPos(){

	D3DXVECTOR3 pos = D3DXVECTOR3(0,0,0);
	
	if( rand()%2 ) {
		pos.x = -RANDOM;
	} else {
		pos.x = RANDOM;
	}

	if( rand()%2 ) {
		pos.y = -RANDOM;
	} else {
		pos.y = RANDOM;
	}

	if( rand()%2 ) {
		pos.z = -RANDOM;
	} else {
		pos.z = RANDOM;
	}

	return pos/2;
}