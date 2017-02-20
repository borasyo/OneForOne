//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DeathblowEffect.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "DeathblowEffect.h"
#include "../Library/DirectX/Window.h"
#include "../Library/DirectX/Direct3D.h"

// --- �萔
const float fArriveTime = 45.0f/nMaxCenter;
const float fMaxColor = 0.33f;

DeathblowEffect::DeathblowEffect() {
	m_Name = "DeathblowEffect";
	
	m_Center.SetFileName( _T("Shadow.jpg") );
	// ���F
	m_Center.SetVertexColor( D3DXCOLOR(fMaxColor/nMaxCenter,fMaxColor/nMaxCenter,0,fMaxColor/nMaxCenter) );
	
	CWindow* pWindow = CWindow::Create();
	m_pHierarchy = Hierarchy::Create();
	
	m_Position.x = pWindow->GetClientWidth()/2.0f;
	m_Position.y = pWindow->GetClientHeight()/2.0f;
	
	m_Scale.x = pWindow->GetClientWidth();
	m_Scale.y = pWindow->GetClientHeight();
	
	for( int i = 0; i < nMaxCenter; i++ ) {
		m_ScaleCenter[i].x = 0;//pWindow->GetClientWidth();
		m_ScaleCenter[i].y = 0;//pWindow->GetClientHeight();
	}
	
	m_MoveCenter.x = pWindow->GetClientWidth()*4/fArriveTime;
	m_MoveCenter.y = pWindow->GetClientHeight()*4/fArriveTime;
	m_MoveCenter.z = 0;
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_nCnt = 0;
	m_bFinish = false;
}

DeathblowEffect::~DeathblowEffect() {
	
}

void DeathblowEffect::Update(){
	
	// �X�V
	for( int i = 0; i < nMaxCenter; i++ ) {
		if( m_nCnt >= fArriveTime*i && m_nCnt < fArriveTime*(i+1) ) {
			m_ScaleCenter[i] += m_MoveCenter;
		}
	}

	m_nCnt++;

	if( !m_pHierarchy->FindWithName("Deathblow") ) {
		m_bFinish = true;
	}

	if( m_bFinish ) {

		for( int i = nMaxCenter-1; i >= 0; i-- ) {
			if( m_ScaleCenter[i].x > 0 ) {
				m_ScaleCenter[i] -= m_MoveCenter;
				break;
			}
		}

		if( m_ScaleCenter[0].x < 0 )
			m_nLife = 0;
	}
}

void DeathblowEffect::Draw(){
	
	// ���Z����
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	
	// �`��
	for( int i = 0; i < nMaxCenter; i++ ) {
		m_Center.Draw( m_Position, m_ScaleCenter[i] );
	}
	
	// �ʏ�u�����h
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}