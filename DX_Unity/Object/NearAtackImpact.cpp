//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [NearAtackImpact.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "NearAtackImpact.h"

bool NearAtackImpact::Start(){

	m_Move = D3DXVECTOR3(0,0,0);

	// 角度に合わせて位置も移動
	Move( D3DXVECTOR3( 2.5f*sinf(m_Rotation.y), 0.25f, 2.5f*cosf(m_Rotation.y) ) );
	m_Move = D3DXVECTOR3( 0.15f*cosf(m_Rotation.y), 0, -(0.15f*sinf(m_Rotation.y)) );

	// サイズ変更
	ScaleChange(D3DXVECTOR3(-0.2f,-0.2f,-0.2f));

	// 色変更
	m_Object3D.SetVertexColor( D3DXCOLOR(0.1f,0.3f,1.0f,1.0f) );
	
	// 
	SetCollisionCircleSize(2.0f);

	return true;
}

void NearAtackImpact::Update(){
	
	// 1Fだけ当たり判定を持たせた
	SetCollisionFlg(false);

	Move(m_Move);
	ScaleChange(D3DXVECTOR3(-0.02f,-0.02f,-0.02f));

	if( m_Scale.x < 0.5f )
		m_nLife = 0;
}

void NearAtackImpact::Draw(){

	// 加算合成
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	
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