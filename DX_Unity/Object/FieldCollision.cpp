//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FieldCollision.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FieldCollision.h"

const float fRivision = 0.5f;

FieldCollision::FieldCollision() {
	m_Name = "FieldCollision";
	m_pHierarchy = Hierarchy::Create();
}

FieldCollision::~FieldCollision() {
	
}

bool FieldCollision::Start() {

	return true;
}

void FieldCollision::LateUpdate(){
	
	// �v���C���[�擾
	GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
	GameObject* pField = m_pHierarchy->FindWithTag("Field");
	GameObject* pPlayerCamera = m_pHierarchy->FindWithName("PlayerCamera");
	
	// ---- �v���C���[�ƃt�B�[���h�̓����蔻��
	// ---- �������Ă��Ȃ���΃t�B�[���h�O�Ɣ���
	if( pPlayer && pField && !m_Collision.CollisionPointandCircle( pPlayer, pField ) ) {
		
		// �Ƃ肠����X���߂��Ă݂�
		pPlayer->ReturnMoveX();
		if( m_Collision.CollisionPointandCircle( pPlayer, pField ) )
			return; // �͈͓��ɖ߂����̂�Z���̓I�[�o�[���Ă��Ȃ�

		// �܂��͈͊O�Ȃ̂�Z���͊m���ɃI�[�o�[���Ă���̂Ŗ߂�
		else {

			// Z���߂�
			pPlayer->ReturnMoveZ();

			// ������������Z�����I�[�o�[���Ă���������X���̓I�[�o�[���Ă��Ȃ������m��Ȃ�
			pPlayer->Move( D3DXVECTOR3( pPlayer->GetMoveAmount()->x, 0, 0 ) );

			// ����́H
			if( !m_Collision.CollisionPointandCircle( pPlayer, pField ) )
				pPlayer->ReturnMoveX(); // ����ς�X�����I�[�o�[���Ă���
		}
		pPlayer->Move( D3DXVECTOR3(0,0,0) );
	}

	// ---- �t�B�[���h�ƃJ�����Ƃ̓����蔻��
	if( pPlayerCamera && pField ) {

		if( !m_Collision.CollisionPointandCircle( pPlayerCamera, pField ) ) {
			*(pPlayerCamera->GetFloat()) -= 0.4f;
		}
		/*else if( *(pPlayerCamera->GetFloat()) > 0.0f ) {
			*(pPlayerCamera->GetFloat()) -= 0.5f;
		}*/
	}
}