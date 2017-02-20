//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ObjectPointLight.cpp]
// author : �哴�ˑ�
// 
// �|�C���g���C�g���쐬�B�܂��g�p���Ȃ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "ObjectPointLight.h"

CObjectPointLight::CObjectPointLight() {
	
	ZeroMemory( &m_Light, sizeof( D3DLIGHT9 ) ); //���C�g���̃N���A
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_nLightIndex = CLightIndex::Create()->GetIndex();

	//���C�g�̐ݒ�
	m_Light.Type = D3DLIGHT_POINT; // �|�C���g���C�g
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // �f�B�t���[�Y�F
	m_Light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // �X�y�L�����[�F
	m_Light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // �A���r�G���g�F
	m_Light.Position = D3DXVECTOR3(0.0f, 15.0f, 0.0f); // ���C�g�̈ʒu(������xyz)
	m_Light.Range = 20.0f; // ���C�g�̗L���͈�
	m_Light.Attenuation0 = 1.0f; // �����萔
	m_Light.Attenuation1 = 1.0f; // �����萔
	m_Light.Attenuation2 = 1.0f; // �����萔

	HRESULT hr;

	//���C�g�̔��f
	hr = m_pD3DDevice->LightEnable( m_nLightIndex, TRUE );

	//�����_�[�X�e�[�g�̐ݒ�
	hr = m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	hr = m_pD3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );
}

CObjectPointLight::~CObjectPointLight(){

}

void CObjectPointLight::SetVecDirection( D3DXVECTOR3 vecDir ){
	// ���C�g�̌����ύX
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_Light.Direction, &vecDir );
	//���C�g�������_�����O�p�C�v���C���ɐݒ�
	m_pD3DDevice->SetLight( m_nLightIndex, &m_Light );
}

void CObjectPointLight::SwitchLight( bool bSwitch ) {
	// ���C�g��ON,OFF�؂�ւ�
	m_pD3DDevice->LightEnable( m_nLightIndex, bSwitch );
}