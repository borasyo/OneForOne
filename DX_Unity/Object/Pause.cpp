//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Pause.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Pause.h"
#include "../Library/DirectX/Direct3D.h"
#include "../Library/DirectX/Window.h"
#include "../Library/DirectX/DirectSound.h"

#include "FadeIn.h"
#include "FadeOut.h"
#include "../Library/Task/SceneManager.h"

// ---- ’è”
const int nArriveTime = 20;
const D3DXVECTOR3 ChangeSpeed = D3DXVECTOR3(1.8f,0.6f,0);

Pause::Pause() {
	m_Name = "Pause";
	
	m_Pause.SetFileName( _T("Pause.png") );
	m_Fade.SetFileName( _T("Shadow.jpg") );
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_pDirectInputManager = CDirectInputManager::Instance();
	
	m_ObjectList = Hierarchy::Create()->FindWithActive();
	for( auto Ite = m_ObjectList.begin(); Ite != m_ObjectList.end(); Ite++ )
		(*Ite)->SetUpdateFlg(false);

	m_bUpdate = true;
	
	CWindow* pWindow = CWindow::Create();
	m_Position.x = pWindow->GetClientWidth()/2;
	m_Position.y = pWindow->GetClientHeight()/2;

	m_Scale.x = 510;
	m_Scale.y = 166;
	m_FadeScale.x = 0.0f;
	m_FadeScale.y = 0.0f;

	m_fAlpha = 0.0f;
	m_bChange = false;
	m_bEnd = false;

	m_nFadeCnt = 0;
	m_bFadeFlg = false;
}

Pause::~Pause() {
	
}

void Pause::Update() {
	
	if( !m_bEnd ) {
		if( m_fAlpha < 1.0f ) {
			m_FadeScale.x += m_Position.x*4.0f/nArriveTime;
			m_FadeScale.y += m_Position.y*4.0f/nArriveTime;
			m_fAlpha += 1.0f/nArriveTime;
		} else {

			// Šg‘åk¬‚ðŒJ‚è•Ô‚·
			if( m_bChange ) {
				m_Scale += ChangeSpeed;

				if( m_Scale.x > 510 + ChangeSpeed.x*nArriveTime )
					m_bChange = false;
			} else {
				m_Scale -= ChangeSpeed;

				if( m_Scale.x < 510 - ChangeSpeed.x*nArriveTime )
					m_bChange = true;
			}
		}
	} else {
		
		if( m_fAlpha > 0.0f ) {
			m_FadeScale.x -= m_Position.x*4.0f/nArriveTime;
			m_FadeScale.y -= m_Position.y*4.0f/nArriveTime;
			m_fAlpha -= 1.0f/nArriveTime;
		}
	}
	
	m_Fade.SetVertexColor( D3DXCOLOR(0.5f,0.5f,0.5f,m_fAlpha) );
	m_Pause.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,m_fAlpha) );

	// ƒQ[ƒ€‚É–ß‚é
	if( m_fAlpha >= 1.0f && 
		(m_pDirectInputManager->GetKeyboardTrigger( DIK_LCONTROL ) ||
		 m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_10)) ) {
		PlaySound(CLICK);
		m_bEnd = true;
	}

	if( m_bEnd && m_fAlpha <= 0.0f ) {
		for( auto Ite = m_ObjectList.begin(); Ite != m_ObjectList.end(); Ite++ )
			(*Ite)->SetUpdateFlg(true);
		m_nLife = 0;
	}

	if( m_pDirectInputManager->GetKeyboardTrigger( DIK_RCONTROL ) || 
		m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_09) ) {
		Hierarchy::Create()->CreateObject(new FadeIn( 45, D3DXCOLOR( 1.0f,1.0f,1.0f,0.0f ) ));
		m_bFadeFlg = true;
		PlaySound(CLICK);

	} else if( m_bFadeFlg ) {

		m_nFadeCnt ++;
		if( m_nFadeCnt > 45 ) {
			
			for( auto Ite = m_ObjectList.begin(); Ite != m_ObjectList.end(); Ite++ )
				(*Ite)->SetUpdateFlg(true);

			m_nLife = 0;
			BanDestroy();
			SceneManager::Create()->ReInit();
			Hierarchy::Create()->CreateObject(new FadeOut( 45, D3DXCOLOR( 1.0f,1.0f,1.0f,1.0f ) ));

			return;
		}
	}
}

void Pause::Draw(){
	
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
	
	// •`‰æ
	m_Pause.Draw( m_Position, m_Scale );
}