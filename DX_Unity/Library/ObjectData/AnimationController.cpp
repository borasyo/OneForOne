//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AnimationController.cpp]
// author : �哴�ˑ�
// 
// �e�N�X�`�����Ǘ�����
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include <iostream>
#include "AnimationController.h"

CAnimationController::CAnimationController(){
	m_pMyAnimationController = nullptr;
}

CAnimationController::~CAnimationController(){
	m_AnimSet.erase(m_AnimSet.begin(),m_AnimSet.end());

	if( m_pMyAnimationController ) {
		m_pMyAnimationController->Release();
		m_pMyAnimationController = nullptr;
	}
}

// �A�j���[�V�����R���g���[����ݒ�
bool CAnimationController::SetAnimationController( const LPD3DXANIMATIONCONTROLLER pAnimCont ) {
	
	// �Z�b�g
	m_pMyAnimationController = pAnimCont;

	// �A�j���[�V�����̐�����HLANIMATION_DESC�\���̂��쐬
	for( int nAnimID = 0; nAnimID < m_pMyAnimationController->GetMaxNumAnimationSets(); nAnimID++ ) {
		HLANIMATION_DESC AnimDesc;

		// �A�j���[�V�������Z�b�g
		m_pMyAnimationController->GetAnimationSet( nAnimID, &AnimDesc.pAnimSet );

		// ID��ۑ�
		AnimDesc.nAnimID = nAnimID;

		// ������
		AnimDesc.fCurWeightTime = 0.0f;
		AnimDesc.bLoop = true;
		
		// Vector�Ɋi�[
		m_AnimSet.push_back( AnimDesc );

		// �i�[��ɏ��������K�v
		SetLoopTime( nAnimID, 60.0f );
		SetShiftTime( nAnimID, 10.0f );
	}
	//m_nCurAnimID = 1;
	//m_nPreAnimID = 0;

	return true;
}

// ���݃E�F�C�g�擾
float CAnimationController::GetWeight(){

	return m_AnimSet[m_nCurAnimID].fCurWeightTime;
}

// ���[�v���Ԃ��擾
float CAnimationController::GetLoopTime( const int nAnimID ) {
	
   // �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
   if( m_AnimSet.size() <= nAnimID )
      return 0.0f;

	return m_AnimSet[nAnimID].fLoopTime;
}
   
// ���[�v���Ԃ𖼑O����擾
float CAnimationController::GetLoopTime( const LPCSTR AnimName ) {
	
   // �w��̃A�j���[�V�����̑��݂��`�F�b�N
	for( int nAnimID = 0; nAnimID < m_AnimSet.size(); nAnimID++ ) {
		
		if( strcmp(m_AnimSet[nAnimID].pAnimSet->GetName(), AnimName) == 0 ) {
			// �q�b�g�����̂ł���LoopTime��Ԃ�
			return m_AnimSet[nAnimID].fLoopTime;
		}
	}
	// ���̖��O�͂Ȃ���
	return 0.0f;
}
   
// ���[�v���Ԃ��擾
int CAnimationController::GetNowAnimID() {
	return m_nCurAnimID;
}
   
// ���[�v���Ԃ𖼑O����擾
LPCSTR CAnimationController::GetNowAnimName() {
	return m_AnimSet[m_nCurAnimID].pAnimSet->GetName();
}

// ���[�v���Ԃ�ݒ�
bool CAnimationController::SetLoopTime( const int nAnimID, const float fTime ) {
	
   // �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
   if( m_AnimSet.size() <= nAnimID )
      return false;

   // �g���b�N�X�s�[�h���ߒl���Z�o
   float fDefTime = m_AnimSet[nAnimID].pAnimSet->GetPeriod();
   m_AnimSet[nAnimID].fLoopTime = fTime;
   m_AnimSet[nAnimID].fTrackSpeed = fDefTime / fTime;

   return true;
}

// ���[�v���Ԃ�ݒ�
bool CAnimationController::SetLoopTime( const LPCSTR AnimName, const float fTime ) {
	
   // �w��̃A�j���[�V�����̑��݂��`�F�b�N
	for( int nAnimID = 0; nAnimID < m_AnimSet.size(); nAnimID++ ) {

		if( strcmp(m_AnimSet[nAnimID].pAnimSet->GetName(), AnimName) == 0 ) {
			
			// �g���b�N�X�s�[�h���ߒl���Z�o
			float fDefTime = m_AnimSet[nAnimID].pAnimSet->GetPeriod();
			m_AnimSet[nAnimID].fLoopTime = fTime;
			m_AnimSet[nAnimID].fTrackSpeed = fDefTime / fTime;

			return true;
		}
	}
	return false;
}

// ����J�n�ɂ����鎞�Ԃ�ݒ�
bool CAnimationController::SetShiftTime( const int nAnimID, const float fInterval ) {
	
   // �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
   if( m_AnimSet.size() <= nAnimID )
      return false;

   // �V�t�g���Ԃ�o�^
   m_AnimSet[nAnimID].fShiftTime = fInterval;

   return true;
}

// ����J�n�ɂ����鎞�Ԃ�ݒ�
bool CAnimationController::SetShiftTime( const LPCSTR AnimName, const float fInterval ) {
	
   // �w��̃A�j���[�V�����̑��݂��`�F�b�N
	for( int nAnimID = 0; nAnimID < m_AnimSet.size(); nAnimID++ ) {
		
		if( strcmp(m_AnimSet[nAnimID].pAnimSet->GetName(), AnimName) == 0 ) {
			
			// �V�t�g���Ԃ�o�^
			m_AnimSet[nAnimID].fShiftTime = fInterval;
			return true;
		}
	}
	return false;
}

// �A�j���[�V������؂�ւ�
bool CAnimationController::ChangeAnimation( const int nAnimID, const bool bLoop ) {
	
  // �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
   if( m_AnimSet.size() <= nAnimID )
      return false;

   // �قȂ�A�j���[�V�����ł��邩���`�F�b�N
   if( m_nCurAnimID == nAnimID )
      return false;

   if( !bLoop && m_nCurAnimID <= m_AnimSet.size() && !m_AnimSet[m_nCurAnimID].bLoop )
	   return false;

   // ���݂̃A�j���[�V�����Z�b�g�̐ݒ�l���擾
   D3DXTRACK_DESC TD;  // �g���b�N�̔\��
   m_pMyAnimationController->GetTrackDesc( 0, &TD );

   // ���̃A�j���[�V�������g���b�N1�Ɉڍs��
   // �g���b�N�̐ݒ�l���ڍs
   if( m_AnimSet.size() > m_nCurAnimID ) {
	   m_pMyAnimationController->SetTrackAnimationSet( 1, m_AnimSet[m_nCurAnimID].pAnimSet );
	   m_pMyAnimationController->SetTrackDesc( 1, &TD );
   }

   // �V�����A�j���[�V�����Z�b�g���g���b�N0�ɐݒ�
   m_pMyAnimationController->SetTrackAnimationSet( 0, m_AnimSet[nAnimID].pAnimSet );

   // �g���b�N0�̃X�s�[�h�̐ݒ�
   m_pMyAnimationController->SetTrackSpeed( 0, m_AnimSet[nAnimID].fTrackSpeed );

   // �g���b�N�̍���������
   m_pMyAnimationController->SetTrackEnable( 0, true );
   m_pMyAnimationController->SetTrackEnable( 1, true );

   // �ď�����
   m_AnimSet[nAnimID].fCurWeightTime = 0.0f;
   m_AnimSet[nAnimID].bLoop = bLoop;

   // ���[�J�����Ԃ�������
   m_pMyAnimationController->SetTrackPosition( 0, 0.0f );
   m_pMyAnimationController->AdvanceTime( 0, nullptr );

   // ���݂̃A�j���[�V�����ԍ���؂�ւ�
   m_nPreAnimID = m_nCurAnimID; // 1�O�̃A�j���[�V�����Ƃ��Ċi�[
   m_nCurAnimID = nAnimID;		// ���݂̃A�j���[�V�����Ƃ��Ċi�[

#if _DEBUG
   std::cout << m_AnimSet[nAnimID].pAnimSet->GetName() << "�̃A�j���[�V���������s" << std::endl;
#endif

   return true;
}

// �A�j���[�V������؂�ւ�
bool CAnimationController::ChangeAnimation( const LPCSTR AnimName, const bool bLoop ) {
	
   // �w��̃A�j���[�V�����̑��݂��`�F�b�N
	for( int nAnimID = 0; nAnimID < m_AnimSet.size(); nAnimID++ ) {
		
		if( strcmp(m_AnimSet[nAnimID].pAnimSet->GetName(), AnimName) == 0 ) {

		   // �قȂ�A�j���[�V�����ł��邩���`�F�b�N
		   if( m_nCurAnimID == nAnimID )
			  return false;

		   if( !bLoop && m_nCurAnimID <= m_AnimSet.size() && !m_AnimSet[m_nCurAnimID].bLoop )
			   return false;

		   // ���݂̃A�j���[�V�����Z�b�g�̐ݒ�l���擾
		   D3DXTRACK_DESC TD;  // �g���b�N�̔\��
		   m_pMyAnimationController->GetTrackDesc( 0, &TD );

		   // ���̃A�j���[�V�������g���b�N1�Ɉڍs��
		   // �g���b�N�̐ݒ�l���ڍs
		   if( m_AnimSet.size() > m_nCurAnimID ) {
			   m_pMyAnimationController->SetTrackAnimationSet( 1, m_AnimSet[m_nCurAnimID].pAnimSet );
			   m_pMyAnimationController->SetTrackDesc( 1, &TD );
		   }

		   // �V�����A�j���[�V�����Z�b�g���g���b�N0�ɐݒ�
		   m_pMyAnimationController->SetTrackAnimationSet( 0, m_AnimSet[nAnimID].pAnimSet );

		   // �g���b�N0�̃X�s�[�h�̐ݒ�
		   m_pMyAnimationController->SetTrackSpeed( 0, m_AnimSet[nAnimID].fTrackSpeed );

		   // �g���b�N�̍���������
		   m_pMyAnimationController->SetTrackEnable( 0, true );
		   m_pMyAnimationController->SetTrackEnable( 1, true );

		   // �ď�����
		   m_AnimSet[nAnimID].fCurWeightTime = 0.0f;
		   m_AnimSet[nAnimID].bLoop = bLoop;

		   // ���[�J�����Ԃ�������
		   m_pMyAnimationController->SetTrackPosition( 0, 0.0f );
		   m_pMyAnimationController->AdvanceTime( 0, nullptr );

		   // ���݂̃A�j���[�V�����ԍ���؂�ւ�
		   m_nPreAnimID = m_nCurAnimID; // 1�O�̃A�j���[�V�����Ƃ��Ċi�[
		   m_nCurAnimID = nAnimID;		// ���݂̃A�j���[�V�����Ƃ��Ċi�[
#if _DEBUG
			std::cout << AnimName << "�̃A�j���[�V���������s" << std::endl;
#endif

		   return true;
		}
	}
	return false;
}

// �A�j���[�V�������X�V
bool CAnimationController::AdvanceTime( const float fTime ) {

   // ���������ۂ��𔻒�
   m_AnimSet[m_nCurAnimID].fCurWeightTime += fTime;
   if( m_AnimSet[m_nCurAnimID].fCurWeightTime <= m_AnimSet[m_nCurAnimID].fShiftTime )
   {
		// �������B�E�F�C�g���Z�o
		float fWeight = m_AnimSet[m_nCurAnimID].fCurWeightTime / m_AnimSet[m_nCurAnimID].fShiftTime;
		// �E�F�C�g��o�^
		m_pMyAnimationController->SetTrackWeight( 0, fWeight );		// ���݂̃A�j���[�V����
		m_pMyAnimationController->SetTrackWeight( 1, 1 - fWeight );	// �O�̃A�j���[�V����
   }
   else
   {
	    // �����I�����B�ʏ�A�j���[�V����������Track0�̃E�F�C�g���ő�l��
		m_pMyAnimationController->SetTrackWeight( 0, 1.0f );	// ���݂̃A�j���[�V����
		m_pMyAnimationController->SetTrackEnable( 1, false );	// �O�̃A�j���[�V�����𖳌��ɂ���
   }

   // ���Ԃ��X�V
   m_pMyAnimationController->AdvanceTime( fTime, nullptr );
   
   // ���[�v�`�F�b�N
   if( !m_AnimSet[m_nCurAnimID].bLoop && // ���[�v���Ȃ���
	   m_AnimSet[m_nCurAnimID].fLoopTime <= m_AnimSet[m_nCurAnimID].fCurWeightTime && // ���[�v���ԕ��A�t���[�����i��ł��āA
	   m_AnimSet[m_nCurAnimID].fCurWeightTime * m_AnimSet[m_nCurAnimID].fTrackSpeed >= m_AnimSet[m_nCurAnimID].pAnimSet->GetPeriod() ) { // �w��s���I�h�����i��ł����
		ChangeAnimation( m_nPreAnimID, m_AnimSet[m_nPreAnimID].bLoop );
		return true; // �A�j���[�V�����I����������
   }

   return false; // �A�j���[�V�����p����
}