//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CleaveImpact.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CleaveImpact.h"

CleaveImpact::CleaveImpact() {
	m_Name = "CleaveImpact";
	m_Object3D.SetFileName(_T("Shadow.jpg"));
	// デバイス取得
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
}

CleaveImpact::~CleaveImpact() {
	
}

bool CleaveImpact::Start(){
	
	m_Move = D3DXVECTOR3(0,0,0);

	// 角度に合わせて位置も移動
	Move( D3DXVECTOR3( -6.5f*sinf(m_Rotation.y), 0.0f, -6.5f*cosf(m_Rotation.y) ) );
	m_Move = D3DXVECTOR3( 0.2f*cosf(m_Rotation.y), 0, -(0.2f*sinf(m_Rotation.y)) );

	// サイズ変更
	ScaleChange(D3DXVECTOR3(0.5f,0.5f,0.5f));

	// 色変更
	m_Object3D.SetVertexColor( D3DXCOLOR( 0.2f,0.4f,0.4f,1.0f) );

	m_bCollision = false;

	return true;
}

void CleaveImpact::Update(){
	
	Move(m_Move);
	ScaleChange(D3DXVECTOR3(-0.02f,-0.02f,-0.02f));

	if( m_Scale.x < 0.5f )
		m_nLife = 0;
}

void CleaveImpact::Draw(){
	
	// 減算
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

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
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

}