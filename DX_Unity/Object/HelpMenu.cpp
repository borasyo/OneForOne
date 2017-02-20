//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [HelpMenu.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "HelpMenu.h"
#include "../Library/DirectX/Direct3D.h"
#include "../Library/DirectX/DirectSound.h"

// -- ’è”
const int nArriveTime = 20;
const D3DXVECTOR3 ChangeSpeed = D3DXVECTOR3(1.8f,0.6f,0);

HelpMenu::HelpMenu() {
	m_Name = "HelpMenu";
	m_Object2D.SetFileName( _T("HelpMenu.png") );
	m_Fade.SetFileName( _T("Shadow.jpg") );

	m_pWindow = CWindow::Create();
	m_pDirectInputManager = CDirectInputManager::Instance();
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	
	m_FadeScale.x = 0.0f;
	m_FadeScale.y = 0.0f;

	m_fAlpha = 0.0f;
	m_bEnd = false;
}

HelpMenu::~HelpMenu() {
	
}

bool HelpMenu::Start(){

	m_Scale = D3DXVECTOR3(0,0,1);
	m_Position = D3DXVECTOR3( m_pWindow->GetClientWidth()/2, m_pWindow->GetClientHeight()/2, 1 );

	return true;
}

void HelpMenu::Update(){
	
	if( !m_bEnd ) {
		if( m_fAlpha < 1.0f ) {
			m_FadeScale.x += m_Position.x*4.0f/nArriveTime;
			m_FadeScale.y += m_Position.y*4.0f/nArriveTime;
			m_Scale.x += m_pWindow->GetClientWidth()/nArriveTime;
			m_Scale.y += m_pWindow->GetClientHeight()/nArriveTime;
			m_fAlpha += 1.0f/nArriveTime;
		} 
	}
	
	else {
		if( m_fAlpha > 0.0f ) {
			m_FadeScale.x -= m_Position.x*4.0f/nArriveTime;
			m_FadeScale.y -= m_Position.y*4.0f/nArriveTime;
			m_Scale.x -= m_pWindow->GetClientWidth()/nArriveTime;
			m_Scale.y -= m_pWindow->GetClientHeight()/nArriveTime;
			m_fAlpha -= 1.0f/nArriveTime;
		}
	}
	
	m_Fade.SetVertexColor( D3DXCOLOR(0.75f,0.75f,0.75f,m_fAlpha) );
	m_Object2D.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,m_fAlpha) );
	
	// ƒQ[ƒ€‚É–ß‚é
	if( m_fAlpha >= 1.0f && (m_pDirectInputManager->GetMouseTrigger(0) || m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_01)) ) {
		PlaySound(CLICK);
		m_bEnd = true;
	}

	if( m_bEnd && m_fAlpha <= 0.0f ) {
		m_bEnd = false;
		m_bActive = false; // Ž©g‚ð”ñƒAƒNƒeƒBƒu‚É
		Hierarchy::Create()->FindWithName("MainMenuCollision")->SetActive(true); // MainMenuCollision‚ðtrue‚É
	}

}

void HelpMenu::Draw(){
	
	// Œ¸ŽZ‡¬
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	
	// ‰ÁŽZ‡¬
	//m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	//m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	//m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 

	// •`‰æ
	m_Fade.Draw( m_Position, m_FadeScale );
	
	// ’ÊíƒuƒŒƒ“ƒh
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// •`‰æ
	m_Object2D.Draw( m_Position, m_Scale );
}