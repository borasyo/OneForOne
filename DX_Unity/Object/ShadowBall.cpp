//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ShadowBall.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "ShadowBall.h"
#include "Shadow.h"
#include "BulletFog.h"
#include "../Library/DirectX/Direct3D.h"

// -- 定数
const float fUpSpeed = 1.035f;

bool ShadowBall::Start(){

	m_Scale = D3DXVECTOR3(1.2f,1.2f,1.2f);
	SetLife(1000);
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	// 影作成
	GameObject* pObj = m_pHierarchy->CreateObject(new Shadow);
	pObj->SetParent(this);
	*(pObj->GetPosition()) = m_Position;
	pObj->Start();
	pObj->ScaleChange(D3DXVECTOR3(0.6f,0.6f,0.6f));
	
	// ベジエ曲線の座標を準備
	GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
	D3DXVECTOR3 TargetPos;
	if( pPlayer )
		TargetPos = *(pPlayer->GetPosition());
	else {
		TargetPos = m_Position + D3DXVECTOR3(10,0,10);
		TargetPos.y = 0.0f;
	}

	float fDistanceX = TargetPos.x - m_Position.x;
	float fDistanceY = TargetPos.y - m_Position.y;
	float fDistanceZ = TargetPos.z - m_Position.z;

	m_Bez0 = m_Position;
	m_Bez2 = TargetPos;
    m_Bez1 = D3DXVECTOR3( m_Bez0.x, m_Bez0.y, m_Bez0.z + sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ ) );
    m_fArriveTime = sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ )/2.0f;
    m_fTime = 0;

	m_Bez1 = D3DXVECTOR3(cosf(m_Rotation.y) * (m_Bez1.x - m_Bez0.x) + sinf(m_Rotation.y) * (m_Bez1.z - m_Bez0.z) + m_Bez0.x,
						 m_Bez1.y,
						 sinf(m_Rotation.y) * (m_Bez1.x - m_Bez0.x) + cosf(m_Rotation.y) * (m_Bez1.z - m_Bez0.z) + m_Bez0.z);

	// コリジョン設定
	SetCollisionCircleSize(0.3f);

	return true;
}

void ShadowBall::Update(){
	
	// 敵の位置を更新
	if( m_fTime <= 0.65f ) {
		GameObject* pPlayer = m_pHierarchy->FindWithName("Player");

		if( pPlayer ) {
			m_Bez2 = *(pPlayer->GetPosition());
			//m_Bez2.y = 0;
		}
		else
			m_Bez2 = D3DXVECTOR3(0,0,0);
	}
	else { //if( m_fTime <= 0.6f + 1.0f/m_fArriveTime/8.0f && m_fTime >= 0.6f - 1.0f/m_fArriveTime/8.0f ) {
		m_fArriveTime /= fUpSpeed;
	}
	
    // ベジエ更新し、移動
	Move( D3DXVECTOR3( (1-m_fTime)*(1-m_fTime)*m_Bez0.x + 2*(1-m_fTime)*m_fTime*m_Bez1.x + m_fTime*m_fTime*m_Bez2.x - m_Position.x,
					   (1-m_fTime)*(1-m_fTime)*m_Bez0.y + 2*(1-m_fTime)*m_fTime*m_Bez1.y + m_fTime*m_fTime*m_Bez2.y - m_Position.y,
					   (1-m_fTime)*(1-m_fTime)*m_Bez0.z + 2*(1-m_fTime)*m_fTime*m_Bez1.z + m_fTime*m_fTime*m_Bez2.z - m_Position.z ) );
	m_fTime += 1.0f/m_fArriveTime/4.0f; // 毎フレーム増加させる 
	
	// エフェクト作成
	if( m_nFogCnt%2 == 0 ) {
		*(m_pBulletFogParent->CreateChild(D3DXCOLOR(0.3f,0.3f,1.0f,0.75f))->GetPosition()) = m_Position;
	}
	m_nFogCnt++;

	// 命削る
	SetLife(-1);

	// 範囲外判定
	if( m_Position.y <= 0.1f || m_fTime >= 1.0f ) {
		SetLife(-999);
	}
}

void ShadowBall::FastDraw(){

	// ZバッファOFF
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// ZバッファON
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}