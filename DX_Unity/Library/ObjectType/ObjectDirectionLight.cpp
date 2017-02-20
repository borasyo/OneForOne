//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ObjectDirectionLight.cpp]
// author : �哴�ˑ�
// 
// �f�B���N�V���i�����C�g���쐬�B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "ObjectDirectionLight.h"

CObjectDirectionLight::CObjectDirectionLight() {
	
	ZeroMemory( &m_Light, sizeof( D3DLIGHT9 ) ); //���C�g���̃N���A
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_nLightIndex = CLightIndex::Create()->GetIndex();

	//���C�g�^�C�v�̐ݒ�
	m_Light.Type = D3DLIGHT_DIRECTIONAL;//���s����

	//����
	D3DXVECTOR3 vecDir = D3DXVECTOR3(1.0f,1.0f,1.0f); 
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_Light.Direction, &vecDir );

	//�f�B�t���[�Y�i�g�U���ˌ��j
	m_Light.Diffuse = D3DXCOLOR(0.5f,0.5f,0.5f,0.5f);
	
	//�A���r�G���g�i�����j
	m_Light.Ambient = D3DXCOLOR(0.05f,0.05f,0.05f,0.05f);

	//�X�y�L�����[�i�����j
	m_Light.Specular = D3DXCOLOR(0.1f,0.1f,0.1f,0.1f);

	//���C�g�������_�����O�p�C�v���C���ɐݒ�
	m_pD3DDevice->SetLight( m_nLightIndex, &m_Light );

	//���C�g�̐ݒ�
	m_pD3DDevice->LightEnable( m_nLightIndex, TRUE );

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	m_pD3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );

	m_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL );
}

CObjectDirectionLight::~CObjectDirectionLight(){

}

void CObjectDirectionLight::SetVecDirection( D3DXVECTOR3 vecDir ){
	// ���C�g�̌����ύX
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_Light.Direction, &vecDir );
	//���C�g�������_�����O�p�C�v���C���ɐݒ�
	m_pD3DDevice->SetLight( m_nLightIndex, &m_Light );
}


void SetDiffuse( D3DXCOLOR Diffuse );

void SetAmbient( D3DXCOLOR Ambient );

void SetSpecular( D3DXCOLOR Specular );

void CObjectDirectionLight::SwitchLight( bool bSwitch ) {
	// ���C�g��ON,OFF�؂�ւ�
	m_pD3DDevice->LightEnable( m_nLightIndex, bSwitch );
}