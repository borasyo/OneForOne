//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [PlayerCamera.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "PlayerCamera.h"
#include "../Library/DirectX/Window.h"

// --- �萔
//const float fDistance = 10.0f;
const float fMaxDistance = 20.0f; // 30.0f
const float fMinDistance = 15.0f;
const float fRegulationSpeed = 0.5f;
const float fMaxOver = 4.0f;
const float fMaxVartical = 4.0f/fMinDistance;
const float fMinVartical = -2.0f/fMinDistance;

// -- �}�N��
#define RotSpeed (30.0f/(float)(CWindow::Create()->GetClientHeight()))

bool PlayerCamera::Start(){

	//
	ReInit();
	
	// �J�����̍���
	m_fHeight = 1.0f;

	// �v���C���[�ƃJ�����̋���
	m_fDistance = 15.0f; // 20.0f

	// �J�����̌��鍂��
	m_fVartical = 11.0f;

	// �t�B�[���h�O�ɍs���̂�h�~
	m_fRegulation = 0.0f;

	// Input�擾
	m_pDirectInputManager = CDirectInputManager::Instance();
	
	// �����蔻��͍s��Ȃ�
	m_bCollision = false;
	
	// ��u���p�ϐ�������
	m_bSway = false;
	m_nNowTime = 0;
	m_nMaxTime = 0;
	m_fSwayRange = 0.0f;
	m_fTotalSway = 0.0f;
	m_bBeside = false;
	m_SwayData = D3DXVECTOR3(0,0,0);
	m_fSwayAmount = 0.0f;
	
	m_TempPos = *(m_pPlayer->GetPosition());
	m_TempRot = *(m_pPlayer->GetRotation());
	// 
	//SetCollisionCubeSize( D3DXVECTOR3(0.1f,10.0f,0.1f), D3DXVECTOR3(0.1f,10.0f,0.1f) );

	return true;
}

void PlayerCamera::Update(){


	// ----- Debug
#if _DEBUG
	if(m_pDirectInputManager->GetKeyboardTrigger(DIK_RETURN)) {
		int i = 0;
		i++;
		printf("%d\n", i);
	}

	if(m_pDirectInputManager->GetKeyboardHold(DIK_Z)) {
		m_fHeight += 0.05f;
	} else if(m_pDirectInputManager->GetKeyboardHold(DIK_X)) {
		m_fHeight -= 0.05f;
	}
#endif

	/*if(m_pDirectInputManager->GetKeyboardTrigger(DIK_C)) {
		m_fDistance += 0.01f;
	} else if(m_pDirectInputManager->GetKeyboardTrigger(DIK_V)) {
		m_fDistance -= 0.01f;
	}
	
	if(m_pDirectInputManager->GetKeyboardTrigger(DIK_B)) {
		m_fVartical += 0.01f;
	} else if(m_pDirectInputManager->GetKeyboardTrigger(DIK_N)) {
		m_fVartical -= 0.01f;
	}*/

	// ------------

	// ���鍂����ύX
	/*const float fJoyRiv = 4.0f;
	if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_01)) {
		m_fVartical += RotSpeed * fJoyRiv;
	} else if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_03)) {
		m_fVartical -= RotSpeed * fJoyRiv;
	} else {
		m_fVartical -= m_pDirectInputManager->GetMouseMoveY() * RotSpeed;
	}

	if( m_fVartical >= fMaxVartical*m_fDistance ) {
		m_fVartical = fMaxVartical*m_fDistance;
	} else if( m_fVartical <= fMinVartical*m_fDistance ) {
		m_fVartical = fMinVartical*m_fDistance;
	}*/
	
	m_TempPos += (*(m_pPlayer->GetPosition()) - m_TempPos) * 0.1f;

	/*D3DXVECTOR3 RotAmount = (*(m_pPlayer->GetRotation()) - m_TempRot);
	if(RotAmount.y > Pai) {
		RotAmount.y -= Pai * 2.0f;
	}
	m_TempRot += RotAmount * 0.3f;*/
	m_TempRot = *(m_pPlayer->GetRotation());

	// �p�x�ɂ��SinCos���擾
	m_fSin = sinf(m_TempRot.y);
	m_fCos = cosf(m_TempRot.y);
	
	float fSinDis = m_fSin*m_fDistance;
	float fCosDis = m_fCos*m_fDistance;
	
	// �ړ���̈ʒu���v�Z
	m_Position.x = m_TempPos.x - fSinDis;
	m_Position.y = m_fHeight;
	m_Position.z = m_TempPos.z - fCosDis;
	
	// �v���C���[�̌����ɍ��킹�Č����ύX
	m_ObjectCamera.GetLookatPt()->x = m_TempPos.x + fSinDis;
	m_ObjectCamera.GetLookatPt()->y = m_fVartical;
	m_ObjectCamera.GetLookatPt()->z = m_TempPos.z + fCosDis;
	
	// X��,Z���Ŕ͈̓I�[�o�[���Ă��Ȃ������`�F�b�N
	/*if( m_fRegulation <= 0.0f ) {
		if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_11)) {
			m_fDistance -= 0.2f;
		} else if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_12)) {
			m_fDistance += 0.2f;
		} else {
			m_fDistance -= m_pDirectInputManager->GetMouseMoveZ()*0.01f;
		}
	}

	// Distance�̐���
	if( m_fDistance > fMaxDistance )
		m_fDistance = fMaxDistance;
	else if( m_fDistance < fMinDistance )
		m_fDistance = fMinDistance;*/

	if( m_fDistance <= m_fRegulation ) {
		m_fRegulation = m_fDistance - 2.0f;
	}

	if(m_fDistance < fMinDistance) {
		m_fDistance += 0.2f;
	}
	
	if( m_SwayData != D3DXVECTOR3(0,0,0) ) {
			
		if( m_bSway && m_fSwayRange >= m_SwayData.y ) {
			m_SwayData = D3DXVECTOR3(0,0,0);
		}
		else {
			m_nNowTime = 0;
			m_nMaxTime = (int)m_SwayData.x;
			m_fSwayRange = m_SwayData.y; 
			m_bBeside = (bool)m_SwayData.z;
			m_fTotalSway = 0.0f;
			m_bUp = true;
			m_bSway = true;
			m_fSwayAmount = 0.0f;
			m_SwayData = D3DXVECTOR3(0,0,0);
		}
	}
	else {
		m_SwayData = D3DXVECTOR3(0,0,0);
	}

	if( m_bSway ) {

		if( m_nNowTime % 2 == 0 )
			m_fSwayAmount = rand()%((int)(m_fSwayRange*100))/100.0f + 0.1f;

		// �v���X������
		if( m_bUp ) {
			m_fTotalSway += m_fSwayAmount;
		}
		// �}�C�i�X������
		else {
			m_fTotalSway -= m_fSwayAmount;
		}
		
		// ���h��Ȃ�
		if( m_bBeside ) {
			
			float fDistanceX = m_ObjectCamera.GetLookatPt()->x - m_Position.x;
			float fDistanceZ = m_ObjectCamera.GetLookatPt()->z - m_Position.z;
			float fAngle = atan2f(fDistanceX,fDistanceZ)+Pai/2;
			float fSin = sinf(fAngle);
			float fCos = cosf(fAngle);

			m_Position.x += fSin*m_fTotalSway;
			m_Position.z += fCos*m_fTotalSway;
			m_ObjectCamera.GetLookatPt()->x += fSin*m_fTotalSway;
			m_ObjectCamera.GetLookatPt()->z += fCos*m_fTotalSway;
		}

		// �c�h��Ȃ�
		else {
			m_Position.y += m_fTotalSway;
			m_ObjectCamera.GetLookatPt()->y += m_fTotalSway;
		}
		
		// ���]
		m_bUp = !m_bUp;

		// �J�E���g�A�b�v
		m_nNowTime ++;
		if( m_nNowTime >= m_nMaxTime ) {
			m_bSway = false;
		}
	}
}

void PlayerCamera::FastDraw(){

	// �R���W��������ɂ��␳�𔽉f
	float fSinDis = m_fSin*m_fRegulation;
	float fCosDis = m_fCos*m_fRegulation;

	// �ړ���̈ʒu���v�Z
	m_Position.x += fSinDis;
	m_Position.z += fCosDis;
	
	// �v���C���[�̌����ɍ��킹�Č����ύX
	m_ObjectCamera.GetLookatPt()->x -= fSinDis;
	m_ObjectCamera.GetLookatPt()->z -= fCosDis;
	
	// �J�������Z�b�g
	m_ObjectCamera.Set(m_Position);
}

void PlayerCamera::FreeFunction() {
	
	m_bSway = false;
	m_nNowTime = 0;
	m_nMaxTime = 0;
	m_fSwayRange = 0.0f;
	m_fTotalSway = 0.0f;
	m_bBeside = false;
	m_SwayData = D3DXVECTOR3(0,0,0);
	m_fSwayAmount = 0.0f;
}

float* PlayerCamera::GetFloat() {
	return &m_fDistance;
}

bool* PlayerCamera::GetBool() {
	return &m_bSway;
}

// ���ԁA�h���͈́A�h���X�s�[�h�A�c������ (�_�E���L���X�g����)
void PlayerCamera::Sway( int nTime, float fSwayRange, bool bBeside, bool bUp  ) {
	
	// �d���֎~
	if( m_bSway )
		return;

	// �e�l��ݒ�
	m_bSway = true;
	m_nNowTime = 0;
	m_nMaxTime = nTime;
	m_fSwayRange = fSwayRange;
	m_fTotalSway = 0.0f;
	m_bBeside = bBeside;	// true�Ȃ牡�h��
	m_bUp = bUp;
	m_fSwayAmount = 0.0f;
}