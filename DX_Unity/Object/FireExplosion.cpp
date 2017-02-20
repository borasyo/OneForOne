//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FireExplosion.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FireExplosion.h"
#include "../Library/DirectX/DirectSound.h"
#include "../Library/DirectX/Direct3D.h"

// -- �萔
const int nChangeTime = 3;

bool FireExplosion::Start(){

	ReInit();

	m_nChangeCnt = 0;
	m_nPattern = 0;

	// �傫���ύX
	ScaleChange(D3DXVECTOR3(2.5f,2.5f,2.5f));

	// �������ݒ�
	m_Object3D.SetDivide(10);

	// �������W�ݒ�
	m_Object3D.SetVertexTexture( m_nPattern );

	PlaySound(PLAYERFIREEXPLOSION);

	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	return true;
}

void FireExplosion::Update(){

	// �A�j���[�V�����X�V
	m_nChangeCnt ++;
	if( m_nChangeCnt % nChangeTime == 0 ){
		m_nPattern ++;
		m_Object3D.SetVertexTexture( m_nPattern );
	}

	// �A�j���[�V�������I������j��
	if( m_nChangeCnt >= nChangeTime*10 )
		m_nLife = 0;
}

void FireExplosion::Draw(){
	// Z��r�Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Z�o�b�t�@�X�V�𖳌���
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z��r����
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z�o�b�t�@�X�V��L����
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
}