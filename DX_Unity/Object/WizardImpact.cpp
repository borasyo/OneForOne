//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [WizardImpact.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "WizardImpact.h"

bool WizardImpact::Start(){

	// ������
	//ReInit();
	m_Move = D3DXVECTOR3(0,0,0);

	// �p�x�ɍ��킹�Ĉʒu���ړ�
	Move( D3DXVECTOR3( 2.0f*sinf(m_Rotation.y), 1.0f, 2.0f*cosf(m_Rotation.y) ) );
	m_Move = D3DXVECTOR3( 0.2f*cosf(m_Rotation.y), 0, -(0.2f*sinf(m_Rotation.y)) );
	
	ScaleChange(D3DXVECTOR3(-0.2f,-0.2f,-0.2f));

	// �F�ύX
	m_Object3D.SetVertexColor( D3DXCOLOR(1.0f,0.0f,0.5f,0.7f) );

	return true;
}

void WizardImpact::Update(){
	
	Move(m_Move);
	ScaleChange(D3DXVECTOR3(-0.02f,-0.02f,-0.02f));

	if( m_Scale.x < 0.5f )
		m_nLife = 0;
}

void WizardImpact::Draw(){
	
	// ���Z
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

	// Z��r�Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Z�o�b�t�@�X�V�𖳌���
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z��r����
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z�o�b�t�@�X�V��L����
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	
	// �ʏ�u�����h
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

}