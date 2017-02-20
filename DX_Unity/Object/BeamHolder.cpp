//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [BeamHolder.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "BeamHolder.h"

const int nInterval = 5;

// ------ �F�A�r�[����łI�u�W�F�N�g�A�����A���A�I�u�W�F�N�g����ǂꂾ���������A1�̑傫���A���@�w�`�悷�邩�A���Z���������Z������
BeamHolder::BeamHolder(D3DXCOLOR Color, int nLength, int nLife, D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, bool bAdd, bool bCollision ) {
	m_Name = "BeamHolder";

	// BeamParent�擾
	BeamParent pObj;
	m_pBeamParent = pObj.GetDownCastClass(Hierarchy::Create()->FindWithName("BeamParent"));

	// �w�肵������ۑ�
	m_Color = Color;
	//m_pTarget = pTarget;
	m_nLength = nLength;
	m_nBeamLife = nLife;
	m_BeamScale = Scale;
	m_fInterval = Scale.z/2.0f;
	m_BeamPos = Pos; // �r�[�����o���Ώۂ��猩�Ăǂꂾ���ʒu��␳���邩
	m_bAdd = bAdd;
	m_bCollision = bCollision;
	//m_bDraw = bDraw;

	// ���C�t�ݒ�
	SetLife(nLife+nLength);

	// FPS
	m_pFPSController = FPSController::Create();
}

BeamHolder::~BeamHolder() {
	
}

bool BeamHolder::Start(){

	// �J�E���g������
	m_nCreateCnt = 0;
	m_bCollision = false;

	// Pos,Rot�ݒ�
	if( m_Parent ) {
		m_Position = *(m_Parent->GetPosition());
		m_Rotation = *(m_Parent->GetRotation());
	}

	return true;
}

void BeamHolder::Update(){

	if( m_nCreateCnt < m_nLength ) {
		
		GameObject* pObj = m_pBeamParent->CreateChild(m_Color,m_Scale,m_bAdd);
		pObj->SetLife(m_nBeamLife);
		// �R���W�������S��false���A5���1��R���W������false��
		if( !m_bCollision || m_nCreateCnt%nInterval != 0 ) {
			pObj->SetCollisionFlg( false );
		}
		m_nCreateCnt++;

		if( m_pFPSController->GetFPS() <= 50 ) {
			m_fInterval += (m_BeamScale.z/2.0f) / m_nLength;
			m_nLength --;
			m_nCreateCnt ++;
		}
	}

	// �ꏊ�X�V
	float fLength = m_fInterval;
	float fSin = sinf( m_Rotation.y );
	float fCos = cosf( m_Rotation.y );
	for( auto Ite = m_pBeamParent->GetChild()->begin(); Ite != m_pBeamParent->GetChild()->end(); Ite++ ) { //, fLength += m_fInterval ) {
		if( !(*Ite)->GetActive() ) 
			continue;
		
		// �Ⴄ�r�[���Ȃ�R���e�B�j���[
		if( *((*Ite)->GetColor()) != m_Color )
			continue;

		(*Ite)->GetPosition()->x = m_Position.x+fSin*fLength;
		(*Ite)->GetPosition()->y = m_Position.y+m_BeamPos.y;
		(*Ite)->GetPosition()->z = m_Position.z+fCos*fLength;
		(*Ite)->ScaleChange( m_Scale - *((*Ite)->GetScale()) );
		fLength += m_fInterval;
	}
	

	// ���������y��
	/*if( m_pFPSController->GetFPS() <= 50 ) {
		
		int nCnt = 0;
		int nInterval = 2;
		for( auto Ite = m_pBeamParent->GetChild()->begin(); Ite != m_pBeamParent->GetChild()->end(); Ite++ ) { //, fLength += m_fInterval ) {
			if( !(*Ite)->GetActive() ) 
				continue;
		
			// �Ⴄ�r�[���Ȃ�R���e�B�j���[
			if( *((*Ite)->GetColor()) != m_Color )
				continue;

			if( nCnt % nInterval == 0 ) {
				(*Ite)->SetLife(-9999);
				m_nLength --;
			}
			else {
				(*Ite)->GetScale()->z *= 2.0f; //1.0f + .0/nInterval;
				m_fInterval *= 2.0f;
			}
			nCnt ++;
		}
	}*/

	// �r�[���𒷂������I���Ă��āA���r�[�����I�����n�߂Ă�����A�Ǐ]���I��
	int nBeamLength = 0;
	for( auto Ite = m_pBeamParent->GetChild()->begin(); Ite != m_pBeamParent->GetChild()->end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;
		
		// �Ⴄ�r�[���Ȃ�R���e�B�j���[
		if( *((*Ite)->GetColor()) != m_Color )
			continue;

		nBeamLength ++;
	}

	if( m_Parent && m_nCreateCnt >= m_nLength && m_nLength-1 == nBeamLength ) {
		
		for( auto Ite = m_Parent->GetChild()->begin(); Ite != m_Parent->GetChild()->end(); Ite++ ) {
			if( *Ite == this ) {
				m_Parent->GetChild()->erase(Ite);
				break;
			}
		}
		// �e������
		m_Parent = nullptr;
	}

	if( m_nCreateCnt >= m_nLength && m_nLength > nBeamLength ) {

		if( m_Scale.x > 0.0f ) {
			m_Scale -= D3DXVECTOR3( m_Scale.x/300.0f, m_Scale.y/300.0f, 0 );
			m_Position += D3DXVECTOR3( 1.5f*fSin, 0.0f, 1.5f*fCos ); 
		}
	}

	// �����
	SetLife(-1);
}