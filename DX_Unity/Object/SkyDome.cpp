//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SkyDome.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SkyDome.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/DirectX/Direct3D.h"

// --- 定数
const float fDomeSize = 200.0f;
const float fTime = 60.0f;
const float fChangeSpeed = 1.0f/120.0f;

SkyDome::SkyDome() {
	m_Name = "SkyDome";
	m_Object3D.SetFileName( _T("SkyDome.x") );
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
}

SkyDome::~SkyDome() {
	
}

bool SkyDome::Start(){

	m_Scale = D3DXVECTOR3( fDomeSize,fDomeSize,fDomeSize );
	m_nMeteoCnt = (int)fTime;
	m_bMeteo = false;
	m_Object3D.SetMaterialColor( D3DXCOLOR(1,1,1,1) );

	m_bDark = false;
	m_fColor = 1.0f; 

	return true;
}

void SkyDome::Update(){

	//if( CDirectInputManager::Create()->GetKeyboardTrigger(DIK_P) ){
	//	FreeFunction();
	//}

	if( m_bMeteo ) {
		m_nMeteoCnt ++;
		
		m_Object3D.SetMaterialColor( D3DXCOLOR(1,(float)m_nMeteoCnt/fTime,(float)m_nMeteoCnt/fTime,1) );

		if( m_nMeteoCnt >= (int)fTime ) {
			m_Object3D.SetMaterialColor( D3DXCOLOR(1,1,1,1) );
			m_bMeteo = false;
		}
	}
	
	else {
		if( m_bDark ) {
			if( m_fColor > 0.0f )
				m_fColor -= fChangeSpeed;
		}
		else {
			if( m_fColor < 1.0f )
				m_fColor += fChangeSpeed;
		}
	
		m_Object3D.SetMaterialColor( D3DXCOLOR(m_fColor,m_fColor,m_fColor,1) );
	}
}

void SkyDome::FastDraw(){
	
	if( (int)fTime > m_nMeteoCnt ) {
		// 加算合成
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	
		// Z比較なし
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Zバッファ更新を無効に
		//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );
	}

	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	if( (int)fTime > m_nMeteoCnt ) {
		// Z比較あり
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファ更新を有効に
		//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	
		// 通常ブレンド
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}
}

void SkyDome::FreeFunction(){
	m_bMeteo = true;
	m_nMeteoCnt = 0;
}

bool* SkyDome::GetBool(){
	return &m_bDark;
}