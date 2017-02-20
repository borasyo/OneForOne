//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [WizardFog.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "WizardFog.h"

#define MOVE_X (rand()%150*0.0001f)
#define MOVE_Y (rand()%600*0.0001f)
#define MOVE_Z (rand()%150*0.0001f)
#define POS_X  ((rand()%10+1)*0.1f)
//#define POS_Y  ((rand()%15+5)*0.1f)
#define POS_Z  ((rand()%10+1)*0.1f)

bool WizardFog::Start(){
	
	m_Move = D3DXVECTOR3(0,0,0);
	if( rand()%2 ){
		m_Position.x += POS_X*sinf(m_Rotation.y);
		m_Move.x += MOVE_X;
	}
	else {
		m_Position.x -= POS_X*sinf(m_Rotation.y);
		m_Move.x -= MOVE_X;
	}
	m_Position.y -= 0.5f;
	m_Move.y = MOVE_Y;
	if( rand()%2 ) {
		m_Position.z += POS_Z*cosf(m_Rotation.y);
		m_Move.z += MOVE_Z;
	}
	else {
		m_Position.z -= POS_Z*cosf(m_Rotation.y);
		m_Move.z -= MOVE_Z;
	}
	
	m_Move *= m_Scale.y;
	ScaleChange(D3DXVECTOR3(-0.2f,-0.2f,-0.2f));
	m_Object3D.SetVertexColor( D3DXCOLOR(1.0f,0.5f,1.0f,1.0f) );

	m_scale.x = -MOVE_X-0.01f;
	m_scale.y = m_scale.z = m_scale.x;

	return true;
}

void WizardFog::Update(){

	Move(m_Move);
	ScaleChange(m_scale);

	if( m_Scale.x < 0.2f )
		m_nLife = 0;
}

void WizardFog::Draw(){
	
	// 減算合成
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

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