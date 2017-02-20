//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Shadow.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Shadow.h"

bool Shadow::Start(){

	//if( !m_bInit ) {
		m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
		m_Position = *(m_Parent->GetPosition());
		m_Position.y = 0.0f;
		m_Object3D.SetBillFlg();
		m_bCollision = false;
		m_bInit = true;
	//}

	return true;
}

void Shadow::LateUpdate(){
	// Y座標は固定
	m_Position.y = 0.1f;

	m_Rotation = D3DXVECTOR3(0,0,0);
}

void Shadow::FastDraw(){
	
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