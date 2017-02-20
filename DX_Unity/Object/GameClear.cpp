//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameClear.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "GameClear.h"
#include "../Library/DirectX/Window.h"
#include "../Library/DirectX/Direct3D.h"
#include "FadeIn.h"
#include "FadeOut.h"
#include "../Library/DirectX/DirectSound.h"

// ---- 定数
const int nArriveTime = 240;
const int nFadeTime = 45;
const float fRogoSpace = 250.0f * 0.7f;
const float fRankSpace = 200.0f * 0.7f;

const D3DXVECTOR3 ScaleS = D3DXVECTOR3(111,148,0) * 0.7f;
const D3DXVECTOR3 ScaleA = D3DXVECTOR3(152,152,0) * 0.7f;
const D3DXVECTOR3 ScaleB = D3DXVECTOR3(137,146,0) * 0.7f;
const D3DXVECTOR3 ScaleC = D3DXVECTOR3(132,146,0) * 0.7f;

GameClear::GameClear() {
	m_Name = "GameClear";
	m_Fade.SetFileName( _T("Shadow.jpg") );
	m_Fast.SetFileName( _T("Fast.png") );
	m_Skill.SetFileName( _T("Skill.png") );
	m_Stoic.SetFileName( _T("Stoic.png") );
	PlaySound(GAMECLEAR);
}

GameClear::~GameClear() {
}

bool GameClear::Start(){
	
	CWindow* pWindow = CWindow::Create();
	m_Position.x = pWindow->GetClientWidth()/2;
	m_Position.y = pWindow->GetClientHeight()/2;
	
	m_FadeScale.x = 0.0f;
	m_FadeScale.y = 0.0f;
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_pDirectInputManager = CDirectInputManager::Instance();
	m_pSceneManager = SceneManager::Create();

	fAlpha = 0.0f;
	m_bFadeFlg = false;
	m_nFadeCnt = 0;
	
	// Fast
	m_Pos[0] = D3DXVECTOR3( m_Position.x - fRogoSpace, 190 * 0.7f, 0 );
	m_Size[0] = D3DXVECTOR3( 425,170,0 ) * 0.7f;
	
	// Skill
	m_Pos[1] = D3DXVECTOR3( m_Position.x - fRogoSpace, 390 * 0.7f, 0 );
	m_Size[1] = D3DXVECTOR3( 327,172,0 ) * 0.7f;
	
	// Stoic
	m_Pos[2] = D3DXVECTOR3( m_Position.x - fRogoSpace, 590 * 0.7f, 0 );
	m_Size[2] = D3DXVECTOR3( 374,168,0 ) * 0.7f;

	// 各Rank設定
	Hierarchy* pHierarchy = Hierarchy::Create();
	
	// FastRank
	int nTime = *(pHierarchy->FindWithName("Time")->GetInt());

	if( nTime <= 12600 ) {
		m_FastRank.SetFileName( _T("RankS.png") );
		m_Size[3] = ScaleS;

	} else if( nTime <= 19800 ) {
		m_FastRank.SetFileName( _T("RankA.png") );
		m_Size[3] = ScaleA;

	} else if( nTime < 36000 ) {
		m_FastRank.SetFileName( _T("RankB.png") );
		m_Size[3] = ScaleB;

	} else {
		m_FastRank.SetFileName( _T("RankC.png") );
		m_Size[3] = ScaleC;
	}
	m_Pos[3] = D3DXVECTOR3( m_Position.x + fRankSpace, 190 * 0.7f, 0 );

	// SkillRank
	int nDamage = *(pHierarchy->FindWithName("Player")->GetInt());

	if( nDamage < 4 ) {
		m_SkillRank.SetFileName( _T("RankS.png") );
		m_Size[4] = ScaleS;
	} else if( nDamage < 10 ) {
		m_SkillRank.SetFileName( _T("RankA.png") );
		m_Size[4] = ScaleA;
	} else if( nDamage < 20 ) {
		m_SkillRank.SetFileName( _T("RankB.png") );
		m_Size[4] = ScaleB;
	} else {
		m_SkillRank.SetFileName( _T("RankC.png") );
		m_Size[4] = ScaleC;

	}
	m_Pos[4] = D3DXVECTOR3( m_Position.x + fRankSpace, 390 * 0.7f, 0 );

	// StoicRank
	int nStoic = *(pHierarchy->FindWithName("ItemCollision")->GetInt());

	if( nStoic == 0 ) {
		m_StoicRank.SetFileName( _T("RankS.png") );
		m_Size[5] = ScaleS;
	} else if( nStoic < 4 ) {
		m_StoicRank.SetFileName( _T("RankA.png") );
		m_Size[5] = ScaleA;
	} else if( nStoic < 8 ) {
		m_StoicRank.SetFileName( _T("RankB.png") );
		m_Size[5] = ScaleB;
	} else {
		m_StoicRank.SetFileName( _T("RankC.png") );
		m_Size[5] = ScaleC;

	}
	m_Pos[5] = D3DXVECTOR3( m_Position.x + fRankSpace, 590 * 0.7f, 0 );
	
	m_Size[3] *= 1.25f;
	m_Size[4] *= 1.25f;
	m_Size[5] *= 1.25f;

	// 画ブレを残さない
	*(pHierarchy->FindWithName("PlayerCamera")->GetBool()) = false;

	// 壁を再表示
	/*std::list<GameObject*>* pAllObj = pHierarchy->FindAllObject();
	for( auto Ite = pAllObj->begin(); Ite != pAllObj->end(); Ite++ ) {
		if( (*Ite)->GetName() == "Wall" )
			(*Ite)->SetActive(true);
	}*/

	return true;
}

void GameClear::Update(){
	
	if( m_FadeScale.x < m_Position.x * 4 && m_FadeScale.y < m_Position.y * 4 ) {
		m_FadeScale.x += m_Position.x*4.0f/nArriveTime;
		m_FadeScale.y += m_Position.y*4.0f/nArriveTime;
		fAlpha += 1.0f/nArriveTime;
	}
	
	m_Fade.SetVertexColor( D3DXCOLOR(0.75f,0.75f,0.0f,fAlpha) );
	m_Fast.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,fAlpha) );
	m_Skill.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,fAlpha) );
	m_Stoic.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,fAlpha) );
	m_FastRank.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,fAlpha) );
	m_SkillRank.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,fAlpha) );
	m_StoicRank.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,fAlpha) );

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

void GameClear::LateDraw(){
	
	if( !m_bFadeFlg ) {
		// 加算合成
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 

		// 描画
		m_Fade.Draw( m_Position, m_FadeScale );
	
		// 通常ブレンド
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}
	
	// 描画
	m_Fast.Draw( m_Pos[0], m_Size[0] );
	m_Skill.Draw( m_Pos[1], m_Size[1] );
	m_Stoic.Draw( m_Pos[2], m_Size[2] );
	m_FastRank.Draw( m_Pos[3], m_Size[3] );
	m_SkillRank.Draw( m_Pos[4], m_Size[4] );
	m_StoicRank.Draw( m_Pos[5], m_Size[5] );
}

bool* GameClear::GetBool(){
	return &m_bDestroy;
}