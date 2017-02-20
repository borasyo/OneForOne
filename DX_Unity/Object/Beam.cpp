//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Beam.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Beam.h"

Beam::Beam() {
	m_Name = "Beam";
	m_Object3D.SetFileName(_T("Shadow.jpg"));

	// デバイス取得
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
}

Beam::~Beam() {
	
}

bool Beam::Start(D3DXCOLOR Color, D3DXVECTOR3 Scale, bool bAdd){
	
	// 初期化
	ReInit();

	// 色設定
	m_Color = Color;
	m_Object3D.SetVertexColor(m_Color);

	// コリジョン
	SetCollisionCubeSize(D3DXVECTOR3(0.2f,0.5f,0.2f),D3DXVECTOR3(0.2f,0.5f,0.2f));
	
	// カウント初期化
	m_nCollisionCnt = 0;
	
	// スケール変更
	ScaleChange(Scale);

	// 加算合成か減算合成か
	m_bAdd = bAdd;

	return true;
}

void Beam::Update(){

	// FlgがOFFになっていたら復帰までカウント
	if( !GetCollisionFlg() ) {
		m_nCollisionCnt ++;
		if( m_nCollisionCnt >= 20 ) {
			SetCollisionFlg(true);
			m_nCollisionCnt = 0;
		}
	}

	// 命削る
	SetLife(-1);
}

void Beam::Draw(){
	
	//減算合成
	if( !m_bAdd ) {
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	}
	// 加算合成
	else {
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	}
	
	// Z比較なし
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Zバッファ更新を無効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z比較あり
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファ更新を有効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	
	// 通常ブレンド
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

}

D3DXCOLOR* Beam::GetColor() {
	return &m_Color;
}