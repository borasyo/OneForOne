//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SlashCenter.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SlashCenter.h"
#include "../Library/DirectX/Window.h"
#include "SlashLeft.h"
#include "SlashRight.h"
#include "FadeIn.h"

// --- 定数
const float fArriveTime = 45.0f;

SlashCenter::SlashCenter(int nMode) {
	m_Name = "SlashCenter";
	m_Object2D.SetFileName( _T("Shadow.jpg") );

	CWindow* pWindow = CWindow::Create();
	
	m_Position.x = pWindow->GetClientWidth()/2.0f;
	m_Position.y = pWindow->GetClientHeight()/2.0f;
	
	m_Scale.x = 0;//pWindow->GetClientWidth();
	m_Scale.y = 0;//pWindow->GetClientHeight();
	
	m_Move.x = pWindow->GetClientWidth()*4/fArriveTime;
	m_Move.y = pWindow->GetClientHeight()*4/fArriveTime;
	m_Move.z = 0;
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_pSceneManager = SceneManager::Create();

	m_nMode = nMode;
	m_Object2D.SetVertexColor( D3DXCOLOR(0.3f,0.3f,0.3f,0.3f) );
	m_nCnt = 0;

	// MainMenuの更新を停止する
	Hierarchy* pHierarchy = Hierarchy::Create();

	std::list<GameObject*>* pAllObj = pHierarchy->FindAllObject(); // リスト取得
	for( auto Ite = pAllObj->begin(); Ite != pAllObj->end(); Ite++ ) {
		// 対象オブジェクトを更新停止に
		if( (*Ite)->GetName() == "EasyBotton" )
			(*Ite)->SetUpdateFlg(false);
		if( (*Ite)->GetName() == "NormalBotton" )
			(*Ite)->SetUpdateFlg(false);
		if( (*Ite)->GetName() == "HardBotton" )
			(*Ite)->SetUpdateFlg(false);
		if( (*Ite)->GetName() == "ExitBotton" )
			(*Ite)->SetUpdateFlg(false);
		if( (*Ite)->GetName() == "MainMenuCollision" )
			(*Ite)->SetUpdateFlg(false);
	}
}

SlashCenter::~SlashCenter() {
	
}

void SlashCenter::Update(){

	// 移動
	ScaleChange( m_Move );

	m_nCnt++;

	if( m_nCnt == fArriveTime - 10.0f ) {
		Hierarchy* pHierarchy = Hierarchy::Create();
		
		pHierarchy->CreateObject(new SlashLeft());
		pHierarchy->CreateObject(new SlashRight());
	}

	if( m_nCnt >= fArriveTime + 120.0f ) {
		m_nLife = 0;
		
		Hierarchy* pHierarchy = Hierarchy::Create();
		std::list<GameObject*>* pAllObj = pHierarchy->FindAllObject(); // リスト取得
		for( auto Ite = pAllObj->begin(); Ite != pAllObj->end(); Ite++ ) {
			// 対象オブジェクトを更新停止に
			if( (*Ite)->GetName() == "EasyBotton" )
				(*Ite)->SetUpdateFlg(true);
			if( (*Ite)->GetName() == "NormalBotton" )
				(*Ite)->SetUpdateFlg(true);
			if( (*Ite)->GetName() == "HardBotton" )
				(*Ite)->SetUpdateFlg(true);
			if( (*Ite)->GetName() == "ExitBotton" )
				(*Ite)->SetUpdateFlg(true);
			if( (*Ite)->GetName() == "MainMenuCollision" )
				(*Ite)->SetUpdateFlg(true);
		}
		
		switch(m_nMode){
		case 0:
			m_pSceneManager->EasyMode();
			break;
		case 1:
			m_pSceneManager->NormalMode();
			break;
		case 2:
			m_pSceneManager->HardMode();
			break;
		}
	}
}

void SlashCenter::Draw(){
	
	// 加算合成
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	
	// 描画
	m_Object2D.Draw( m_Position, m_Scale );
	
	// 通常ブレンド
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}