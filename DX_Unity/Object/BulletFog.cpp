//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [BulletFog.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "BulletFog.h"
#include "../Library/DirectX/Direct3D.h"

#define MOVE_X (rand()%200*0.0002f)
#define MOVE_Y (rand()%200*0.0002f)
#define MOVE_Z (rand()%200*0.0002f)

bool BulletFog::Start(D3DXCOLOR FogCol, float fMove, float fDeathSize ){

	// 再初期化
	ReInit();
	m_Move = D3DXVECTOR3(0,0,0);
	m_Object3D.SetVertexColor(FogCol);

	switch(rand()%8){
	case 0:
		m_Move.x += MOVE_X;
		m_Move.y += MOVE_Y;
		m_Move.z += MOVE_Z;
		break;
	case 1:
		m_Move.x -= MOVE_X;
		m_Move.y += MOVE_Y;
		m_Move.z += MOVE_Z;
		break;
	case 2:
		m_Move.x += MOVE_X;
		m_Move.y -= MOVE_Y;
		m_Move.z += MOVE_Z;
		break;
	case 3:
		m_Move.x += MOVE_X;
		m_Move.y += MOVE_Y;
		m_Move.z -= MOVE_Z;
		break;
	case 4:
		m_Move.x -= MOVE_X;
		m_Move.y -= MOVE_Y;
		m_Move.z += MOVE_Z;
		break;
	case 5:
		m_Move.x -= MOVE_X;
		m_Move.y += MOVE_Y;
		m_Move.z -= MOVE_Z;
		break;
	case 6:
		m_Move.x += MOVE_X;
		m_Move.y -= MOVE_Y;
		m_Move.z -= MOVE_Z;
		break;
	case 7:
		m_Move.x -= MOVE_X;
		m_Move.y -= MOVE_Y;
		m_Move.z -= MOVE_Z;
		break;
	default:
		break;
	}
	//m_Move.z -= MOVE_Z;

	// 移動量調整
	m_Move *= fMove;
	
	ScaleChange(D3DXVECTOR3(-0.4f,-0.4f,-0.4f));
	m_fDeathSize = fDeathSize;

	return true;
}

void BulletFog::Update(){
	Move(m_Move);
	ScaleChange(D3DXVECTOR3(-0.02f,-0.02f,-0.02f));

	if( m_Scale.x < m_fDeathSize )
		m_nLife = 0;
}

void BulletFog::Draw(){
	
	// 加算合成
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	
	// Z比較なし
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Zバッファ更新を無効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

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