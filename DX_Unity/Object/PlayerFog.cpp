//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [PlayerFog.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "PlayerFog.h"

#define MOVE_X (rand()%150*0.0001f)
#define MOVE_Y (rand()%300*0.0001f)
#define MOVE_Z (rand()%150*0.0001f)
#define POS_X  ((rand()%7+1)*0.1f)
//#define POS_Y  ((rand()%15+5)*0.1f)
#define POS_Z  ((rand()%7+1)*0.1f)

// -- 定数
const float fAbsorptionTime = 60.0f; 

bool PlayerFog::Start(){

	m_Move = D3DXVECTOR3(0,0,0);
	
	if( rand()%2 ){
		m_Position.x += POS_X*sinf(m_Rotation.y);
		m_Move.x += MOVE_X;
	}
	else {
		m_Position.x -= POS_X*sinf(m_Rotation.y);
		m_Move.x -= MOVE_X;
	}
	m_Position.y -= 1.0f;
	m_Move.y = +MOVE_Y;
	if( rand()%2 ) {
		m_Position.z += POS_Z*cosf(m_Rotation.y);
		m_Move.z += MOVE_Z;
	}
	else {
		m_Position.z -= POS_Z*cosf(m_Rotation.y);
		m_Move.z -= MOVE_Z;
	}
	m_Move *= 2.0f;
	
	ScaleChange(D3DXVECTOR3(-0.2f,-0.2f,-0.2f));
	m_Object3D.SetVertexColor( D3DXCOLOR(1.0f,1.0f,0.01f,1.0f) );
	m_bAbsorption = false;
	m_pDeathblow = nullptr;

	m_pHierarchy = Hierarchy::Create();

	return true;
}

void PlayerFog::Update(){


	if( !m_bAbsorption ) {
		Move(m_Move);
		ScaleChange(D3DXVECTOR3(-0.01f,-0.01f,-0.01f));

		if( m_Scale.x < 0.2f )
			m_nLife = 0;
	}

	else {

		if( m_Scale.x < fInitScale/2.0f && m_bAbsorption && m_pDeathblow ) {
			m_Move.x = (m_pDeathblow->GetPosition()->x - m_Position.x) / fAbsorptionTime;
			m_Move.y = (m_pDeathblow->GetPosition()->y - m_Position.y) / fAbsorptionTime;
			m_Move.z = (m_pDeathblow->GetPosition()->z - m_Position.z) / fAbsorptionTime;
			float fScale = -fInitScale/fAbsorptionTime/4.0f;
			ScaleChange(D3DXVECTOR3(fScale,fScale,fScale));
			Move(m_Move);
		}
		else {
			// 移動
			Move(m_Move);
			ScaleChange(D3DXVECTOR3(-0.05f,-0.05f,-0.05f));
		}
			
		if( m_Scale.x < 0.0f )
			m_nLife = 0;
	}
}

void PlayerFog::FreeFunction(){

	m_pDeathblow = m_pHierarchy->FindWithName("Deathblow");

	if( m_pDeathblow && !*(m_pDeathblow->GetBool()) ) {
		m_Scale = *(m_pDeathblow->GetScale())/6.0f;
		if( m_Scale.x < 1.0f ) 
			m_Scale = D3DXVECTOR3(1,1,1);
		fInitScale = m_Scale.x;

		m_bAbsorption = true;
	}
}

void PlayerFog::Draw(){
	
	// 加算合成
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	
	// Z比較なし
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Zバッファ更新を無効に
	//if( m_bAbsorption )
	//	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z比較あり
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファ更新を有効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	
	// 通常ブレンド
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}