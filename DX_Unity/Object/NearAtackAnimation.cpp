//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [NearAtackAnimation.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "NearAtackAnimation.h"
#include "../Library/DirectX/Direct3D.h"

const int nMaxPattern = 15;
const int nChangeInterval = 2;

#define RANDOM_X (rand()%100000 * 0.00001f)
#define RANDOM_Z (rand()%100000 * 0.00001f)

NearAtackAnimation::NearAtackAnimation() {
	m_Name = "NearAtackAnimation";
	m_Object3D.SetFileName( _T("NearAtack.png") );
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	
	// 分割数設定
	m_Object3D.SetDivide(nMaxPattern);
}

NearAtackAnimation::~NearAtackAnimation() {
	
}

bool NearAtackAnimation::Start(){

	m_nChangeTime = 0;
	m_nPattern = 0;

	// 初期座標設定
	m_Object3D.SetVertexTexture( m_nPattern );
	m_Scale = D3DXVECTOR3(5,5,5);
	//m_nLife = 1;

	m_Position.y += 1.0f;
	
	if( rand()%2 ) {
		m_Position.x += RANDOM_X;
	}
	else {
		m_Position.x -= RANDOM_X;
	}

	if( rand()%2 ) {
		m_Position.z += RANDOM_Z;
	}
	else {
		m_Position.z -= RANDOM_Z;
	}

	return true;
}

void NearAtackAnimation::Update(){

	m_nChangeTime ++;

	if( m_nChangeTime % nChangeInterval == 0 ) {
		m_nPattern ++;

		m_Object3D.SetVertexTexture( m_nPattern );

		if( m_nPattern >= nMaxPattern ) {
			m_nLife = 0;
		}
	}
}

void NearAtackAnimation::Draw(){

	// 加算合成
	//m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	//m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	//m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	
	// Z比較なし
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Zバッファ更新を無効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z比較あり
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファ更新を有効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	
	// 通常ブレンド
	//m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	//m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	//m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}