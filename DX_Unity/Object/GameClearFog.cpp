//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameClearFog.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "GameClearFog.h"

#define MOVE_X (rand()%300*0.0001f + 0.01f)
#define MOVE_Y (rand()%600*0.0001f + 0.02f)
#define MOVE_Z (rand()%300*0.0001f + 0.01f)
//#define POS_X  ((rand()%10+1)*0.1f)
//#define POS_Y  ((rand()%15+5)*0.1f)
//#define POS_Z  ((rand()%10+1)*0.1f)

GameClearFog::GameClearFog() {
	m_Name = "GameClearFog";
	m_Object3D.SetFileName(_T("Shadow.jpg"));
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
}

GameClearFog::~GameClearFog() {
	
}

bool GameClearFog::Start(){

	m_Move = D3DXVECTOR3(0,0,0);

	if( rand()%2 ){
		//m_Position.x += POS_X*sinf(m_Rotation.y);
		m_Move.x += MOVE_X;
	}
	else {
		//m_Position.x -= POS_X*sinf(m_Rotation.y);
		m_Move.x -= MOVE_X;
	}
	m_Position.y -= 0.5f;
	m_Move.y = MOVE_Y;
	if( rand()%2 ) {
		//m_Position.z += POS_Z*cosf(m_Rotation.y);
		m_Move.z += MOVE_Z;
	}
	else {
		//m_Position.z -= POS_Z*cosf(m_Rotation.y);
		m_Move.z -= MOVE_Z;
	}

	GameObject* pBoss = Hierarchy::Create()->FindWithTag("Boss");
	
	if( pBoss->GetName() == "Devil" ) {
		m_Object3D.SetVertexColor( D3DXCOLOR(0.5f,0.15f,0.5f,1.0f) );
		//m_Scale = D3DXVECTOR3(18.0f,18.0f,18.0f);
		m_Move *= 6.0f;
	}

	m_scale.x = (-MOVE_X-0.01f)*2.0f;
	m_scale.y = m_scale.z = m_scale.x;

	return true;
}

void GameClearFog::Update(){
	
	Move(m_Move);
	ScaleChange(m_scale);

	if( m_Scale.x < 5.0f )
		m_nLife = 0;
}

void GameClearFog::Draw(){
	
	// 加算合成
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 

	// 減算合成
	//m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
	//m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	//m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

	// Z比較なし
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Zバッファ更新を無効に
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z比較あり
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファ更新を有効に
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	
	// 通常ブレンド
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}