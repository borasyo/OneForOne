//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FadeOut.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FadeOut.h"
#include "../Library/DirectX/Window.h"

FadeOut::FadeOut( float fTime, D3DXCOLOR col ) {
	m_Name = "FadeOut";
	m_Object2D.SetFileName(_T("Fade.png"));
	m_fTime = fTime;
	m_fAlpha = 1.0f;
	FadeColor = col;
	m_bCollision = false;

	// ƒXƒNƒŠ[ƒ“‚Ì‘å‚«‚³‚É‡‚í‚¹‚é
	CWindow* pWindow = CWindow::Create();
	m_Position = D3DXVECTOR3(pWindow->GetWindowWidth()/2.0f,pWindow->GetWindowHeight()/2.0f,1.0f);
	m_Scale    = D3DXVECTOR3(pWindow->GetWindowWidth(),pWindow->GetWindowHeight(),1.0f);
}

FadeOut::~FadeOut() {
	
}

void FadeOut::Update(){
	
	m_fAlpha -= 1.0f/m_fTime;
	FadeColor.a = m_fAlpha;
	m_Object2D.SetVertexColor( FadeColor );

	if( m_fAlpha <= 0.0f ) {
		SetLife(-1);
	}
}

void FadeOut::LateDraw(){

	// •`‰æ
	m_Object2D.Draw( m_Position, m_Scale );
}