//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Danger.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Danger.h"
#include "../Library/DirectX/Window.h"

Danger::Danger() {
	m_Name = "Danger";
	m_Obj2D.SetFileName(_T("danger.png"));
}

Danger::~Danger() {
	
}

bool Danger::Start(){

	m_pPlayer = Hierarchy::Create()->FindWithName("Player");
	m_nInitHp = m_pPlayer->GetLife();

	CWindow* pWindow = CWindow::Create();
	m_Position.x = pWindow->GetClientWidth()/2.0f;
	m_Position.y = pWindow->GetClientHeight()/2.0f;
	m_Scale.x = pWindow->GetClientWidth();
	m_Scale.y = pWindow->GetClientHeight();

	m_bAdd = true;
	m_fNowAlpha = 0.0f;
	m_fNowMaxAlpha = 0.0f;

	return true;
}

void Danger::Update(){
	
	float fAs = (float)m_pPlayer->GetLife() / (float)m_nInitHp;

	//	まだ余裕
	if(fAs > 0.5f) {
		//m_Obj2D.SetVertexColor(D3DXCOLOR(0,0,0,0));
		m_fNowAlpha = 0.0f;
		m_fNowMaxAlpha = 0.0f;
	}

	//	死にかけ
	else if(fAs <= 0.25f) {
		//m_Obj2D.SetVertexColor(D3DXCOLOR(0.25f,0.25f,0.25f,0.25f));
		m_fNowMaxAlpha = 0.5f;
	}

	//	ちょい死にかけ
	else {
		//m_Obj2D.SetVertexColor(D3DXCOLOR(0.5f,0.5f,0.5f,0.5f));
		m_fNowMaxAlpha = 0.25f;
	}

	// 点滅処理
	if(m_bAdd) {
		m_fNowAlpha += (m_fNowMaxAlpha * m_fNowMaxAlpha) * 0.05f;

		if(m_fNowAlpha >= m_fNowMaxAlpha) {
			m_fNowAlpha = m_fNowMaxAlpha;
			m_bAdd = false;
		}

	} else {
		m_fNowAlpha -= (m_fNowMaxAlpha * m_fNowMaxAlpha) * 0.05f;

		if(m_fNowAlpha <= 0.0f) {
			m_fNowAlpha = 0.0f;
			m_bAdd = true;
		}
	}

	// 色更新
	m_Obj2D.SetVertexColor(D3DXCOLOR(1, 1, 1, m_fNowAlpha));
}

void Danger::LateDraw(){
	m_Obj2D.Draw( m_Position, m_Scale );
}