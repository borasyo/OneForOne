//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Blood.cpp]
// author : �哴�ˑ�
//
// ���̏o��ʒu�͗v�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Blood.h"

// -- �萔
const float fGravity = 0.0245f;

// -- �}�N��
#define DEFLECTION ((rand()%30)*0.1f)
#define FLY (rand()%5*0.1f)

bool Blood::Start(D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos) {
	
	// ������
	ReInit();
	m_bGrounded = false;
	m_bCollision = false;

	m_Move = (MyselfPos - OpponentPos)/6.0f;
	m_Move.x *= DEFLECTION; // �኱�̂��������
	m_Move.y += FLY;
	m_Move.z *= DEFLECTION; // �኱�̂��������
	m_Position = OpponentPos; // �����̏o��ʒu���i�[

	// ���C�t�ݒ�
	SetLife(90);

	return true;
}

void Blood::Update(){

	if( !m_bGrounded ) {
		Move(m_Move); // �ړ�
		m_Move.y -= fGravity; // �d�͕␳
	} 

	// �n�ʂɒ�������
	if( m_Position.y <= 0 ) {
		m_Position.y = 0;
		m_bGrounded = true;
	}
	
	// ���C�t���炷
	SetLife(-1);
}

void Blood::Draw(){
	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}