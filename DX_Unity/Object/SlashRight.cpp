//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SlashRight.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SlashRight.h"
#include "../Library/DirectX/Window.h"
#include "../Library/DirectX/DirectSound.h"

// --- ’è”
const float fArriveTime = 10.0f;

SlashRight::SlashRight() {
	m_Name = "SlashRight";

	m_Object2D.SetFileName( _T("SlashRightDragon.png") );

	CWindow* pWindow = CWindow::Create();
	
	m_Position.x = pWindow->GetClientWidth() + pWindow->GetClientWidth()/2.0f;
	m_Position.y = -pWindow->GetClientHeight()/2.0f;
	
	m_Scale.x = pWindow->GetClientWidth();
	m_Scale.y = pWindow->GetClientHeight();
	
	m_Move.x = -pWindow->GetClientWidth()/fArriveTime;
	m_Move.y = pWindow->GetClientHeight()/fArriveTime;
	m_Move.z = 0;
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_nCnt = 0;
}

SlashRight::~SlashRight() {
	
}

void SlashRight::Update(){

	// ˆÚ“®
	if( m_nCnt < fArriveTime )
		Move( m_Move );

	if( m_nCnt == fArriveTime/2 )
		PlaySound(MAINMENUEFFECT);

	m_nCnt++;

	if( m_nCnt > fArriveTime + 120.0f ) {
		m_nLife = 0;
	}
}

void SlashRight::Draw(){
	
	// ‰ÁŽZ‡¬
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	
	// •`‰æ
	m_Object2D.Draw( m_Position, m_Scale );
	
	// ’ÊíƒuƒŒƒ“ƒh
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}