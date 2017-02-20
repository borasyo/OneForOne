//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [NearAtackImpact.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "NearAtackImpact.h"

bool NearAtackImpact::Start(){

	m_Move = D3DXVECTOR3(0,0,0);

	// �p�x�ɍ��킹�Ĉʒu���ړ�
	Move( D3DXVECTOR3( 2.5f*sinf(m_Rotation.y), 0.25f, 2.5f*cosf(m_Rotation.y) ) );
	m_Move = D3DXVECTOR3( 0.15f*cosf(m_Rotation.y), 0, -(0.15f*sinf(m_Rotation.y)) );

	// �T�C�Y�ύX
	ScaleChange(D3DXVECTOR3(-0.2f,-0.2f,-0.2f));

	// �F�ύX
	m_Object3D.SetVertexColor( D3DXCOLOR(0.1f,0.3f,1.0f,1.0f) );
	
	// 
	SetCollisionCircleSize(2.0f);

	return true;
}

void NearAtackImpact::Update(){
	
	// 1F���������蔻�����������
	SetCollisionFlg(false);

	Move(m_Move);
	ScaleChange(D3DXVECTOR3(-0.02f,-0.02f,-0.02f));

	if( m_Scale.x < 0.5f )
		m_nLife = 0;
}

void NearAtackImpact::Draw(){

	// ���Z����
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	
	// Z��r�Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Z�o�b�t�@�X�V�𖳌���
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z��r����
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z�o�b�t�@�X�V��L����
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	
	// �ʏ�u�����h
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

}