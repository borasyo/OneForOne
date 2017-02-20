//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FadeIn.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FadeIn.h"
#include "FadeOut.h"
#include "../Library/DirectX/Window.h"

FadeIn::FadeIn( float fTime, D3DXCOLOR col ) {
	m_Name = "FadeIn";
	m_Object2D.SetFileName(_T("Fade.png"));
	m_fTime = fTime;
	m_fAlpha = 0.0f;
	FadeColor = col;
	m_bCollision = false;

	// ƒXƒNƒŠ[ƒ“‚Ì‘å‚«‚³‚É‡‚í‚¹‚é
	CWindow* pWindow = CWindow::Create();
	m_Position = D3DXVECTOR3(pWindow->GetClientWidth()/2.0f,pWindow->GetClientHeight()/2.0f,1.0f);
	m_Scale    = D3DXVECTOR3(pWindow->GetClientWidth(),pWindow->GetClientHeight(),1.0f);
}

FadeIn::~FadeIn() {

}

void FadeIn::Update(){

	m_fAlpha += 1.0f/m_fTime;
	FadeColor.a = m_fAlpha;
	m_Object2D.SetVertexColor( FadeColor );

	if( m_fAlpha >= 1.0f ) {
		SetLife(-1);
		Hierarchy::Create()->CreateObject(new FadeOut(m_fTime,FadeColor));
	}
}

void FadeIn::LateDraw(){
	
	// •`‰æ
	m_Object2D.Draw( m_Position, m_Scale );
}