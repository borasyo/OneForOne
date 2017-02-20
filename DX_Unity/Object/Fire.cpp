//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Fire.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Fire.h"
#include "BulletFog.h"
#include "Shadow.h"

// --- 定数
const float fMoveSpeed = 2.0f;
const int nArriveTime = 90;

// --- マクロ 
#define RANDOM (rand()%300*0.01f)

Fire::Fire() {
	m_Name = "Fire";
	m_Object3D.SetFileName( _T("DragonFire.png") );

	m_pHierarchy = Hierarchy::Create();

	// BulletFog取得
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
}

Fire::~Fire() {
	
}

bool Fire::Start(){
	
	// m_Move = D3DXVECTOR3( sinf(m_Rotation.y) * fMoveSpeed, 0, cosf(m_Rotation.y) * fMoveSpeed );

	GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
	D3DXVECTOR3 Distance = *(pPlayer->GetPosition()) - m_Position;
	m_Move = Distance/nArriveTime;
	
	// コリジョン設定
	SetCollisionCubeSize(D3DXVECTOR3(0.15f,0.15f,0.15f), D3DXVECTOR3(0.15f,0.15f,0.15f));

	// スケール調整
	m_Scale = D3DXVECTOR3(1.5f,1.5f,1.5f);

	// ライフ設定
	m_nLife = nArriveTime*2;

	return true;
}

void Fire::Update(){
	
	if( m_Child.empty() ) {
		// 影作成
		GameObject* pObj = m_pHierarchy->CreateObject(new Shadow( D3DXCOLOR(0.8f,0.1f,0.1f,1.0f), true ) );
		pObj->SetParent(this);
		*(pObj->GetPosition()) = m_Position;
		pObj->Start();
		*(pObj->GetScale()) = D3DXVECTOR3(2,2,2);
	}
	
	// 移動
	Move(m_Move);
	
	// エフェクト作成
	*(m_pBulletFogParent->CreateChild(D3DXCOLOR(0.8f,0.1f,0.1f,0.75f))->GetPosition()) = m_Position;

	// ライフ減らす
	SetLife(-1);

	// 範囲外判定
	if( m_Position.y <= 0 ) 
		m_nLife = 0;
}

void Fire::Draw(){
	// Z比較なし
	//m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Zバッファ更新を無効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z比較あり
	//m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファ更新を有効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
}