//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FarAtackFire.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FarAtackFire.h"
#include "BulletFog.h"
#include "Shadow.h"
#include "FireExplosion.h"

bool FarAtackFire::Start(){
	
	// ��{���
	m_Scale = D3DXVECTOR3(0.8f,0.8f,0.8f);
	m_nLife = 120;
	m_pHierarchy = Hierarchy::Create();

	// �e�쐬
	GameObject* pObj = m_pHierarchy->CreateObject(new Shadow);
	pObj->SetParent(this);
	*(pObj->GetPosition()) = m_Position;
	pObj->Start();
	
	// �x�W�G�Ȑ��̍��W������
	GameObject* pPlayer = m_pHierarchy->FindWithName("Player"); // Player�T��
	m_pBoss = nullptr;
	m_pEnemyParent = m_pHierarchy->FindWithName("SkeltonCorpsParent"); // �G���G����
	// �G���G�̓��ꕨ�������
	if( m_pEnemyParent ) { 
		auto Ite = m_pEnemyParent->GetChild()->begin();
		for( ; Ite != m_pEnemyParent->GetChild()->end(); Ite++ ) {
			if( (*Ite)->GetActive() )
				break;
		}
		if( Ite == m_pEnemyParent->GetChild()->end() ) {
			m_pBoss = m_pHierarchy->FindWithTag("Boss");
			m_pEnemy = m_pBoss;
		} else {
			m_pEnemy = (*Ite);
		}
	}
	// �{�X�T��
	else {
		m_pBoss = m_pHierarchy->FindWithTag("Boss");
		m_pEnemy = m_pBoss;
	}
	D3DXVECTOR3 TargetPos;

	// �Ώۂ�����΂�����^�[�Q�b�g�Ɏw��
	if( m_pEnemy ) {
		TargetPos = *(m_pEnemy->GetPosition());

		if( m_pEnemy->GetName() == "Devil" ){
			TargetPos.y += m_pEnemy->GetCollisionCubePlusSize().y; 
		}
	}
	else
		TargetPos = D3DXVECTOR3(0,0,0);

	float fDistanceX = TargetPos.x - m_Position.x;
	float fDistanceY = TargetPos.y - m_Position.y;
	float fDistanceZ = TargetPos.z - m_Position.z;

	m_Bez0 = m_Position;
	m_Bez2 = TargetPos;
    m_Bez1 = D3DXVECTOR3( m_Bez0.x, m_Bez0.y, m_Bez0.z + sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ ) );
    m_fArriveTime = sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ )/2.0f;
    m_fTime = 0.0f;

	m_Bez1 = D3DXVECTOR3(cosf(pPlayer->GetRotation()->y) * (m_Bez1.x - m_Bez0.x) + sinf(pPlayer->GetRotation()->y) * (m_Bez1.z - m_Bez0.z) + m_Bez0.x,
						 m_Bez1.y,
						 sinf(pPlayer->GetRotation()->y) * (m_Bez1.x - m_Bez0.x) + cosf(pPlayer->GetRotation()->y) * (m_Bez1.z - m_Bez0.z) + m_Bez0.z);

	// �R���W�����ݒ�
	SetCollisionCircleSize(0.5f);

	return true;
}

void FarAtackFire::Update() {
	
	// �G�̈ʒu���X�V
	if( m_pBoss ) {
		m_pEnemy = m_pHierarchy->FindWithTag("Boss");

		if( m_pEnemy ) {
			m_Bez2 = *(m_pEnemy->GetPosition());
			if( m_pEnemy->GetName() == "Devil" )
				m_Bez2.y += m_pEnemy->GetCollisionCubePlusSize().y;
		}
		else { 
			m_Bez2.y = 0.0f;
		}
	}
	
    // �x�W�G�X�V���A�ړ�
	Move( D3DXVECTOR3( (1-m_fTime)*(1-m_fTime)*m_Bez0.x + 2*(1-m_fTime)*m_fTime*m_Bez1.x + m_fTime*m_fTime*m_Bez2.x - m_Position.x,
                       (1-m_fTime)*(1-m_fTime)*m_Bez0.y + 2*(1-m_fTime)*m_fTime*m_Bez1.y + m_fTime*m_fTime*m_Bez2.y - m_Position.y,
                       (1-m_fTime)*(1-m_fTime)*m_Bez0.z + 2*(1-m_fTime)*m_fTime*m_Bez1.z + m_fTime*m_fTime*m_Bez2.z - m_Position.z ) );

    m_fTime += 1.0f/m_fArriveTime/2.0f; // ���t���[������������ 
	
	// �G�t�F�N�g�쐬
	*(m_pBulletFogParent->CreateChild(D3DXCOLOR(1.0f,0.1f,0.1f,0.5f))->GetPosition()) = m_Position;

	// �����
	SetLife(-1);

	// �͈͊O����
	if( m_Position.y <= 0 || m_fTime >= 1.0f )
		SetLife(-999);
}

void FarAtackFire::Draw() {
	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}