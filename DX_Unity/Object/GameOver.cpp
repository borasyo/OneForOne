//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameOver.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "GameOver.h"
#include "../Library/DirectX/Window.h"
#include "../Library/DirectX/Direct3D.h"
#include "FadeIn.h"
#include "FadeOut.h"
#include "../Library/DirectX/DirectSound.h"

// ---- ’è”
const int nArriveTime = 240;
const int nFadeTime = 45;

GameOver::GameOver() {
	m_Name = "GameOver";
	m_Fade.SetFileName( _T("Shadow.jpg") );
	m_Rogo.SetFileName( _T("GameOver.png") );
	PlaySound(GAMEOVER);
}

GameOver::~GameOver() {
}

bool GameOver::Start(){
	
	CWindow* pWindow = CWindow::Create();
	m_Position.x = pWindow->GetClientWidth()/2;
	m_Position.y = pWindow->GetClientHeight()/2;

	m_Scale.x = 629 * 0.7f;
	m_Scale.y = 256 * 0.7f;
	
	m_FadeScale.x = 0.0f;
	m_FadeScale.y = 0.0f;
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_pDirectInputManager = CDirectInputManager::Instance();
	m_pSceneManager = SceneManager::Create();

	fAlpha = 0.0f;
	m_bFadeFlg = false;
	m_nFadeCnt = 0;

	return true;
}

void GameOver::Update(){
	
	if( m_FadeScale.x < m_Position.x * 4 && m_FadeScale.y < m_Position.y * 4 ) {
		m_FadeScale.x += m_Position.x*4.0f/nArriveTime;
		m_FadeScale.y += m_Position.y*4.0f/nArriveTime;
		fAlpha += 1.0f/nArriveTime;
	}
	
	m_Fade.SetVertexColor( D3DXCOLOR(1.0f,0.0f,0.0f,fAlpha) );
	m_Rogo.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,fAlpha) );

	if( !m_bFadeFlg && m_FadeScale.x >= m_Position.x * 4 && 
		(m_pDirectInputManager->GetMouseTrigger(0) || m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_01)) ) {
		Hierarchy::Create()->CreateObject(new FadeIn( nFadeTime, D3DXCOLOR( 1.0f,1.0f,1.0f,0.0f ) ));
		m_bFadeFlg = true;
		PlaySound(CLICK);
	}
	else if( m_bFadeFlg ) {

		m_nFadeCnt ++;
		fAlpha -= 1.0f/nFadeTime;
		if( m_nFadeCnt > nFadeTime ) {
			m_nLife = 0;
			BanDestroy();
			m_pSceneManager->ReInit();
			Hierarchy::Create()->CreateObject(new FadeOut( nFadeTime, D3DXCOLOR( 1.0f,1.0f,1.0f,1.0f ) ));
			return;
		}
	}
}

void GameOver::LateDraw(){
	
	if( !m_bFadeFlg ) {
		// ‰ÁŽZ‡¬
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 

		// •`‰æ
		m_Fade.Draw( m_Position, m_FadeScale );
	
		// ’ÊíƒuƒŒƒ“ƒh
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}
	
	// •`‰æ
	m_Rogo.Draw( m_Position, m_Scale );
}

bool* GameOver::GetBool(){
	return &m_bDestroy;
}