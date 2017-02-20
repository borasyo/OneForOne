//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainMenu.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "MainMenu.h"
#include "../Library/DirectX/Window.h"
#include "../Library/DirectX/Direct3D.h"

// --- 定数
const D3DXCOLOR DefColor[6] = {
	D3DXCOLOR( 1.0f,1.0f,0.0f,1.0f ),
	D3DXCOLOR( 1.0f,0.0f,0.0f,1.0f ),
	D3DXCOLOR( 1.0f,0.0f,1.0f,1.0f ),
	D3DXCOLOR( 0.0f,0.0f,1.0f,1.0f ),
	D3DXCOLOR( 0.0f,1.0f,1.0f,1.0f ),
	D3DXCOLOR( 0.0f,1.0f,0.0f,1.0f )
};
const int nChangeTime = 120;

MainMenu::MainMenu() {
	m_Name = "MainMenu";

	CWindow* pWindow = CWindow::Create();

	// サイズ指定
	m_Scale.x = pWindow->GetClientWidth();
	m_Scale.y = pWindow->GetClientHeight();
	
	// Pos指定
	m_Position.x = m_Scale.x/2.0f;
	m_Position.y = m_Scale.y/2.0f;
	
	m_nPattern = 0;
	m_Color = DefColor[m_nPattern];
	m_nPattern++;
	m_nChangeCnt = 0;
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_pMouth = CMouthPosition::Create();
}

MainMenu::~MainMenu() {
	
}

void MainMenu::Update(){

	int nAfterPattern = m_nPattern-1;
	if( nAfterPattern < 0 ) {
		nAfterPattern = 5;
	}
	m_Color += (DefColor[m_nPattern]-DefColor[nAfterPattern])/(float)nChangeTime;
	
	m_nChangeCnt++;
	if( m_nChangeCnt % nChangeTime == 0 ) {
		m_nChangeCnt = 0;
		m_nPattern ++;
		if( m_nPattern > 5 ) 
			m_nPattern = 0;
	}
}

void MainMenu::Draw(){
	// 加算合成
	//m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	//m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	//m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	
	// 描画
	m_Object2D.SetVertexColor(m_Color);
	m_Object2D.SetFileName( _T("MainMenu.png") );
	m_Object2D.Draw( m_Position, m_Scale );

	// 描画
	m_Object2D.SetVertexColor(D3DXCOLOR(1,1,1,1));
	m_Object2D.SetFileName( _T("MainMenuEffect.png") );
	m_Object2D.Draw( m_Position, m_Scale );
	
	// 通常ブレンド
	//m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	//m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	//m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}

void MainMenu::LateDraw(){
	m_pMouth->Draw();
}

D3DXCOLOR* MainMenu::GetColor(){
	return &m_Color;
}