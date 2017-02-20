//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AnimationController.h]
// author : �哴�ˑ�
// 
// �e�N�X�`�����Ǘ�����
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AnimationController_H_____
#define _____AnimationController_H_____

// ---- �C���N���[�h�錾
#include "d3dx9.h"
#include <vector>

// ---- �\����
struct HLANIMATION_DESC
{
	int nAnimID;					// �A�j���[�V����ID
    LPD3DXANIMATIONSET pAnimSet;	// �A�j���[�V�����Z�b�g
    float fLoopTime;				// 1���[�v�̎���
    float fTrackSpeed;				// �g���b�N�X�s�[�h���ߒl
    float fShiftTime;				// �V�t�g����̂ɂ����鎞��
    float fCurWeightTime;			// ���݂̃E�F�C�g����
	bool bLoop;						// ���[�v���邩�ǂ���
};

// --- �N���X�錾
class CAnimationController{

private:
	LPD3DXANIMATIONCONTROLLER m_pMyAnimationController;
	std::vector<HLANIMATION_DESC> m_AnimSet; 
	int m_nCurAnimID, m_nPreAnimID;

public:
	CAnimationController();
	~CAnimationController();
	
   // �A�j���[�V�����R���g���[����ݒ�
   bool SetAnimationController( const LPD3DXANIMATIONCONTROLLER pAnimCont );
   
   // ���݃E�F�C�g�擾
   float GetWeight();
   
   // ���[�v���Ԃ��擾
   float GetLoopTime( const int nAnimID );
   
   // ���[�v���Ԃ𖼑O����擾
   float GetLoopTime( const LPCSTR AnimName );
   
   // ���ݍĐ����̃A�j���[�V�����̔ԍ����擾
   int GetNowAnimID();
   
   // ���ݍĐ����̃A�j���[�V�����̖��O���擾
   LPCSTR GetNowAnimName();
   
   // ���[�v���Ԃ�ݒ�
   bool SetLoopTime( const int nAnimID, const float fTime );

   // ���[�v���Ԃ𖼑O����ݒ�
   bool SetLoopTime( const LPCSTR AnimName, const float fTime );
   
   // ����J�n�ɂ����鎞�Ԃ�ݒ�
   bool SetShiftTime( const int nAnimID, const float fInterval );

   // ����J�n�ɂ����鎞�Ԃ𖼑O�����ݒ�
   bool SetShiftTime( const LPCSTR AnimName, const float fInterval );
   
   // �A�j���[�V������؂�ւ�
   bool ChangeAnimation( const int nAnimID, const bool bLoop );
   
   // �A�j���[�V�����𖼑O����؂�ւ�
   bool ChangeAnimation( const LPCSTR AnimName, const bool bLoop );
   
   // �A�j���[�V�������X�V
   bool AdvanceTime( const float fTime );
   
   // �A�j���[�V�����R���g���[�����擾
   LPD3DXANIMATIONCONTROLLER* GetAnimationController() {

	   if( m_pMyAnimationController )
		   return &m_pMyAnimationController;

	   return nullptr;
   }
};

#endif
