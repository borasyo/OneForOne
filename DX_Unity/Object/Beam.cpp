//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Beam.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Beam.h"

Beam::Beam() {
	m_Name = "Beam";
	m_Object3D.SetFileName(_T("Shadow.jpg"));

	// �f�o�C�X�擾
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
}

Beam::~Beam() {
	
}

bool Beam::Start(D3DXCOLOR Color, D3DXVECTOR3 Scale, bool bAdd){
	
	// ������
	ReInit();

	// �F�ݒ�
	m_Color = Color;
	m_Object3D.SetVertexColor(m_Color);

	// �R���W����
	SetCollisionCubeSize(D3DXVECTOR3(0.2f,0.5f,0.2f),D3DXVECTOR3(0.2f,0.5f,0.2f));
	
	// �J�E���g������
	m_nCollisionCnt = 0;
	
	// �X�P�[���ύX
	ScaleChange(Scale);

	// ���Z���������Z������
	m_bAdd = bAdd;

	return true;
}

void Beam::Update(){

	// Flg��OFF�ɂȂ��Ă����畜�A�܂ŃJ�E���g
	if( !GetCollisionFlg() ) {
		m_nCollisionCnt ++;
		if( m_nCollisionCnt >= 20 ) {
			SetCollisionFlg(true);
			m_nCollisionCnt = 0;
		}
	}

	// �����
	SetLife(-1);
}

void Beam::Draw(){
	
	//���Z����
	if( !m_bAdd ) {
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	}
	// ���Z����
	else {
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	}
	
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

D3DXCOLOR* Beam::GetColor() {
	return &m_Color;
}