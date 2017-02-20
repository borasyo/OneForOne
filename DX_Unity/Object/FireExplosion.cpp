//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FireExplosion.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FireExplosion.h"
#include "../Library/DirectX/DirectSound.h"
#include "../Library/DirectX/Direct3D.h"

// -- 定数
const int nChangeTime = 3;

bool FireExplosion::Start(){

	ReInit();

	m_nChangeCnt = 0;
	m_nPattern = 0;

	// 大きさ変更
	ScaleChange(D3DXVECTOR3(2.5f,2.5f,2.5f));

	// 分割数設定
	m_Object3D.SetDivide(10);

	// 初期座標設定
	m_Object3D.SetVertexTexture( m_nPattern );

	PlaySound(PLAYERFIREEXPLOSION);

	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	return true;
}

void FireExplosion::Update(){

	// アニメーション更新
	m_nChangeCnt ++;
	if( m_nChangeCnt % nChangeTime == 0 ){
		m_nPattern ++;
		m_Object3D.SetVertexTexture( m_nPattern );
	}

	// アニメーションを終えたら破壊
	if( m_nChangeCnt >= nChangeTime*10 )
		m_nLife = 0;
}

void FireExplosion::Draw(){
	// Z比較なし
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Zバッファ更新を無効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z比較あり
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファ更新を有効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
}