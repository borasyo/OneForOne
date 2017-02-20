//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Rader.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Rader.h"
#include "../Library/DirectX/Direct3D.h"

Rader::Rader() {
	m_Name = "Rader";
	m_Object2D.SetFileName( _T("Rader.png") );
	m_ObjectEnemyPoint.SetFileName( _T("Shadow.jpg") );
	m_ObjectItemPoint.SetFileName( _T("Shadow.jpg") );
	m_ObjectPlayerPoint.SetFileName( _T("PlayerPoint.png") );
	m_ObjectDragonPoint.SetFileName( _T("Shadow.jpg") );
}

Rader::~Rader() {
	
}

bool Rader::Start(){
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	m_Position = D3DXVECTOR3(1320,140,1) * 0.7f;
	m_Scale = D3DXVECTOR3(200,200,1) * 0.7f;
	
	m_ObjectItemPoint.SetVertexColor( D3DXCOLOR( 0.1f,1.0f,0.1f,1.0f ) );
	m_ObjectDragonPoint.SetVertexColor( D3DXCOLOR( 0.1f,0.1f,1.0f,1.0f ) );
	
	m_ObjectEnemyPoint.SetVertexColor( D3DXCOLOR( 1.0f,0.1f,0.1f,1.0f ) );
	m_EnemyPointPos = D3DXVECTOR3(-100,-100,0) * 0.7f;
	m_EnemyPointScale = D3DXVECTOR3(20.0f,20.0f,0) * 0.7f;

	m_PlayerPointPos = D3DXVECTOR3(-100,-100,0) * 0.7f;
	m_PlayerPointScale = D3DXVECTOR3(10.5f,15.0f,0) * 0.7f;
	 
	m_pHierarchy = Hierarchy::Create();
	m_pPlayer = m_pHierarchy->FindWithName("Player");
	m_pBoss = m_pHierarchy->FindWithTag("Boss");
	m_pDragon = m_pHierarchy->FindWithName("DragonParent");

	return true;
}

void Rader::Update(){

	m_pPlayer = m_pHierarchy->FindWithName("Player");
	m_pBoss = m_pHierarchy->FindWithTag("Boss");

	if( m_pPlayer ) {
		m_PlayerPointPos.x = m_Position.x + ( (m_pPlayer->GetPosition()->x/300.0f) * (m_Scale.x*0.5f) );
		m_PlayerPointPos.y = m_Position.y - ( (m_pPlayer->GetPosition()->z/300.0f) * (m_Scale.y*0.5f) );
		m_fPlayerRot = m_pPlayer->GetRotation()->y;
	}

	if( m_pBoss ) {
		m_EnemyPointPos.x = m_Position.x + ( (m_pBoss->GetPosition()->x/300.0f) * (m_Scale.x*0.5f) );
		m_EnemyPointPos.y = m_Position.y - ( (m_pBoss->GetPosition()->z/300.0f) * (m_Scale.y*0.5f) );
	}
}

void Rader::LateDraw(){
	
	// Z”äŠr‚È‚µ
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Zƒoƒbƒtƒ@XV‚ð–³Œø‚É
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );
	
	// •`‰æ
	m_Object2D.Draw( m_Position, m_Scale );
	
	// ‰ÁŽZ‡¬
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 

	// -------- •`‰æ ---------

	// Boss•`‰æ
	m_ObjectEnemyPoint.Draw( m_EnemyPointPos, m_EnemyPointScale );

	// Item•`‰æ
	m_pItem = m_pHierarchy->FindWithName("ItemParent");
	for( auto Ite = m_pItem->GetChild()->begin(); Ite != m_pItem->GetChild()->end(); Ite++ ) {
		D3DXVECTOR3 ItemPointPos;
		ItemPointPos.x = m_Position.x + ( ((*Ite)->GetPosition()->x/300.0f) * (m_Scale.x*0.5f) );
		ItemPointPos.y = m_Position.y - ( ((*Ite)->GetPosition()->z/300.0f) * (m_Scale.y*0.5f) );
		m_ObjectItemPoint.Draw( ItemPointPos, D3DXVECTOR3(10*(*Ite)->GetScale()->x,10*(*Ite)->GetScale()->y,0) );
	}

	// Dragon•`‰æ
	for( auto Ite = m_pDragon->GetChild()->begin(); Ite != m_pDragon->GetChild()->end(); Ite++ ) {

		if( !(*Ite)->GetActive() )
			continue;

		D3DXVECTOR3 DragonPointPos;
		DragonPointPos.x = m_Position.x + ( ((*Ite)->GetPosition()->x/300.0f) * (m_Scale.x*0.5f) );
		DragonPointPos.y = m_Position.y - ( ((*Ite)->GetPosition()->z/300.0f) * (m_Scale.y*0.5f) );
		m_ObjectDragonPoint.Draw( DragonPointPos, D3DXVECTOR3(10*(*Ite)->GetScale()->x,10*(*Ite)->GetScale()->y,0) );
	}
	
	// ’ÊíƒuƒŒƒ“ƒh
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// •`‰æ
	m_ObjectPlayerPoint.Draw( m_PlayerPointPos, m_PlayerPointScale, m_fPlayerRot );
	
	// Z”äŠr‚ ‚è
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zƒoƒbƒtƒ@XV‚ð—LŒø‚É
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
}