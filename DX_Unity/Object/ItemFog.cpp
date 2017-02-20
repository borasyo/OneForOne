//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ItemFog.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "ItemFog.h"

#define MOVE_X (rand()%300*0.0001f)
#define MOVE_Y (rand()%600*0.0001f)
#define MOVE_Z (rand()%300*0.0001f)
#define POS_X  ((rand()%7+1)*0.1f)
//#define POS_Y  ((rand()%15+5)*0.1f)
#define POS_Z  ((rand()%7+1)*0.1f)

// -- 定数
const float fAbsorptionTime = 20.0f; 
const float fMinSpeed = 0.5f;

bool ItemFog::Start(){

	m_Move = D3DXVECTOR3(0,0,0);
	
	if( rand()%2 ){
		m_Position.x += POS_X;
		m_Move.x += MOVE_X;
	}
	else {
		m_Position.x -= POS_X;
		m_Move.x -= MOVE_X;
	}
	m_Position.y -= 1.0f;
	m_Move.y = +MOVE_Y;
	if( rand()%2 ) {
		m_Position.z += POS_Z;
		m_Move.z += MOVE_Z;
	}
	else {
		m_Position.z -= POS_Z;
		m_Move.z -= MOVE_Z;
	}
	m_Move *= 2.0f;
	
	ScaleChange(D3DXVECTOR3(-0.2f,-0.2f,-0.2f));
	m_Object3D.SetVertexColor( D3DXCOLOR(0.1f,1.0f,0.1f,1.0f) );
	m_bAbsorption = false;
	m_pDeathblow = nullptr;

	m_pHierarchy = Hierarchy::Create();

	return true;
}

void ItemFog::Update(){

	if( m_Scale.x <= fInitScale/2.0f && m_bAbsorption && m_pDeathblow ) {
		m_Move.x = (m_pDeathblow->GetPosition()->x - m_Position.x) / fAbsorptionTime * 6;
		m_Move.y = (m_pDeathblow->GetPosition()->y - m_Position.y) / fAbsorptionTime * 6;
		m_Move.z = (m_pDeathblow->GetPosition()->z - m_Position.z) / fAbsorptionTime * 6;

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

void ItemFog::FreeFunction(){

	m_pDeathblow = m_pHierarchy->FindWithName("Player");

	m_Scale = D3DXVECTOR3(3,3,3);
	fInitScale = m_Scale.x;

	m_bAbsorption = true;
}

void ItemFog::Draw(){
	
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