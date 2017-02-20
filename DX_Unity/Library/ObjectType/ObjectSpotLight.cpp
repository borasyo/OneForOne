//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ObjectSpotLight.cpp]
// author : �哴�ˑ�
// 
// �X�|�b�g���C�g���쐬�B�܂��g�p���Ȃ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "ObjectSpotLight.h"

CObjectSpotLight::CObjectSpotLight() {
	
	ZeroMemory( &m_Light, sizeof( D3DLIGHT9 ) ); //���C�g���̃N���A
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_nLightIndex = CLightIndex::Create()->GetIndex();

	//���C�g�^�C�v�̐ݒ�
	m_Light.Type = D3DLIGHT_SPOT;//�X�|�b�g���C�g

	//����
	D3DXVECTOR3 vecDir = D3DXVECTOR3(0.0f,-1.0f,0.0f); 
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_Light.Direction, &vecDir );

	m_Light.Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); // �f�B�t���[�Y�F
	m_Light.Specular = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); // �X�y�L�����[�F
	m_Light.Ambient = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); // �A���r�G���g�F
	m_Light.Position = D3DXVECTOR3(0.0f,10.0f,0.0f); // ���C�g�̈ʒu
	//m_Light.Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f); // ���C�g�̕����x�N�g��
	m_Light.Range = 1.0f; // ���C�g�̗L���͈�
	m_Light.Falloff = 1.0f; // �t�H�[���I�t
	m_Light.Attenuation0 = 1.0f; // ��팸���W��
	m_Light.Attenuation1 = 1.0f; // ��팸���W��
	m_Light.Attenuation2 = 1.0f; // ��팸���W��
	m_Light.Theta = D3DXToRadian(10.0f); // �����̃R�[���̊p�x
	m_Light.Phi = D3DXToRadian(30.0f); // �O���̃R�[���̊p�x

	//���C�g�̐ݒ�
	m_pD3DDevice->LightEnable( m_nLightIndex, TRUE );

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	m_pD3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );
}

CObjectSpotLight::~CObjectSpotLight(){

}

void CObjectSpotLight::SetVecDirection( D3DXVECTOR3 vecDir ){
	// ���C�g�̌����ύX
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_Light.Direction, &vecDir );
	//���C�g�������_�����O�p�C�v���C���ɐݒ�
	m_pD3DDevice->SetLight( m_nLightIndex, &m_Light );
}

void CObjectSpotLight::SwitchLight( bool bSwitch ) {
	// ���C�g��ON,OFF�؂�ւ�
	m_pD3DDevice->LightEnable( m_nLightIndex, bSwitch );
}