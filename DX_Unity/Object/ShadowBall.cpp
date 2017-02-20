//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ShadowBall.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "ShadowBall.h"
#include "Shadow.h"
#include "BulletFog.h"
#include "../Library/DirectX/Direct3D.h"

// -- �萔
const float fUpSpeed = 1.035f;

bool ShadowBall::Start(){

	m_Scale = D3DXVECTOR3(1.2f,1.2f,1.2f);
	SetLife(1000);
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	// �e�쐬
	GameObject* pObj = m_pHierarchy->CreateObject(new Shadow);
	pObj->SetParent(this);
	*(pObj->GetPosition()) = m_Position;
	pObj->Start();
	pObj->ScaleChange(D3DXVECTOR3(0.6f,0.6f,0.6f));
	
	// �x�W�G�Ȑ��̍��W������
	GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
	D3DXVECTOR3 TargetPos;
	if( pPlayer )
		TargetPos = *(pPlayer->GetPosition());
	else {
		TargetPos = m_Position + D3DXVECTOR3(10,0,10);
		TargetPos.y = 0.0f;
	}

	float fDistanceX = TargetPos.x - m_Position.x;
	float fDistanceY = TargetPos.y - m_Position.y;
	float fDistanceZ = TargetPos.z - m_Position.z;

	m_Bez0 = m_Position;
	m_Bez2 = TargetPos;
    m_Bez1 = D3DXVECTOR3( m_Bez0.x, m_Bez0.y, m_Bez0.z + sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ ) );
    m_fArriveTime = sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ )/2.0f;
    m_fTime = 0;

	m_Bez1 = D3DXVECTOR3(cosf(m_Rotation.y) * (m_Bez1.x - m_Bez0.x) + sinf(m_Rotation.y) * (m_Bez1.z - m_Bez0.z) + m_Bez0.x,
						 m_Bez1.y,
						 sinf(m_Rotation.y) * (m_Bez1.x - m_Bez0.x) + cosf(m_Rotation.y) * (m_Bez1.z - m_Bez0.z) + m_Bez0.z);

	// �R���W�����ݒ�
	SetCollisionCircleSize(0.3f);

	return true;
}

void ShadowBall::Update(){
	
	// �G�̈ʒu���X�V
	if( m_fTime <= 0.65f ) {
		GameObject* pPlayer = m_pHierarchy->FindWithName("Player");

		if( pPlayer ) {
			m_Bez2 = *(pPlayer->GetPosition());
			//m_Bez2.y = 0;
		}
		else
			m_Bez2 = D3DXVECTOR3(0,0,0);
	}
	else { //if( m_fTime <= 0.6f + 1.0f/m_fArriveTime/8.0f && m_fTime >= 0.6f - 1.0f/m_fArriveTime/8.0f ) {
		m_fArriveTime /= fUpSpeed;
	}
	
    // �x�W�G�X�V���A�ړ�
	Move( D3DXVECTOR3( (1-m_fTime)*(1-m_fTime)*m_Bez0.x + 2*(1-m_fTime)*m_fTime*m_Bez1.x + m_fTime*m_fTime*m_Bez2.x - m_Position.x,
					   (1-m_fTime)*(1-m_fTime)*m_Bez0.y + 2*(1-m_fTime)*m_fTime*m_Bez1.y + m_fTime*m_fTime*m_Bez2.y - m_Position.y,
					   (1-m_fTime)*(1-m_fTime)*m_Bez0.z + 2*(1-m_fTime)*m_fTime*m_Bez1.z + m_fTime*m_fTime*m_Bez2.z - m_Position.z ) );
	m_fTime += 1.0f/m_fArriveTime/4.0f; // ���t���[������������ 
	
	// �G�t�F�N�g�쐬
	if( m_nFogCnt%2 == 0 ) {
		*(m_pBulletFogParent->CreateChild(D3DXCOLOR(0.3f,0.3f,1.0f,0.75f))->GetPosition()) = m_Position;
	}
	m_nFogCnt++;

	// �����
	SetLife(-1);

	// �͈͊O����
	if( m_Position.y <= 0.1f || m_fTime >= 1.0f ) {
		SetLife(-999);
	}
}

void ShadowBall::FastDraw(){

	// Z�o�b�t�@OFF
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z�o�b�t�@ON
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}