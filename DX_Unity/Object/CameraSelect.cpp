//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CameraSelect.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CameraSelect.h"

eCameraState CameraSelect::m_CameraState = CAMERA_NORMAL;

CameraSelect::CameraSelect() {
	m_Name = "CameraSelect";
}

CameraSelect::~CameraSelect() {
	
}

bool CameraSelect::Start(){

	m_SwayData = D3DXVECTOR3(0,0,0);

	return true;
}

void CameraSelect::FastUpdate(){

	if(m_SwayData != D3DXVECTOR3(0,0,0)) {
		switch(m_OldState) {
		
		case CAMERA_NORMAL:
			*(m_pNormalCamera->GetVec()) = m_SwayData;
			break;
	
		case CAMERA_BEAM:
			*(m_pBeamCamera->GetVec()) = m_SwayData;
			break;

		case CAMERA_INVINCIBLE:
			*(m_pDeathblowCamera->GetVec()) = m_SwayData;
			break;

		case CAMERA_DEATHBLOW:
			*(m_pDeathblowCamera->GetVec()) = m_SwayData;
			break;

		default:
			break;
		}
		m_SwayData = D3DXVECTOR3(0,0,0);
	}
	
	/*if(CDirectInputManager::Instance()->GetKeyboardTrigger(DIK_J)) {
		SetState(CAMERA_NORMAL);
	}
	if(CDirectInputManager::Instance()->GetKeyboardTrigger(DIK_K)) {
		SetState(CAMERA_BEAM);
	}
	if(CDirectInputManager::Instance()->GetKeyboardTrigger(DIK_L)) {
		SetState(CAMERA_INVINCIBLE);
	}*/

	// カメラの変更をチェック
	if(m_OldState != m_CameraState) {
		
		switch(m_OldState) {
		
		case CAMERA_NORMAL:
			m_pNormalCamera->SetActive(false);
			break;
	
		case CAMERA_BEAM:
			m_pBeamCamera->SetActive(false);
			break;

		case CAMERA_INVINCIBLE:
			m_pInvincibleCamera->SetActive(false);
			break;

		case CAMERA_DEATHBLOW:
			m_pDeathblowCamera->SetActive(false);
			break;

		default:
			break;
		}
		
		switch(m_CameraState) {
		
		case CAMERA_NORMAL:
			m_pNormalCamera->SetActive(true);
			switch(m_OldState) {
			case CAMERA_BEAM:
				m_pNormalCamera->SetTempData(m_pBeamCamera->GetTempPos(), m_pBeamCamera->GetTempRot());
				break;

			case CAMERA_INVINCIBLE:
				m_pNormalCamera->SetTempData(m_pInvincibleCamera->GetTempPos(), m_pInvincibleCamera->GetTempRot());
				break;
			}
			break;
	
		case CAMERA_BEAM:
			m_pBeamCamera->SetActive(true);
			switch(m_OldState) {
			case CAMERA_NORMAL:
				m_pBeamCamera->SetTempData(m_pNormalCamera->GetTempPos(), m_pNormalCamera->GetTempRot());
				break;
				
			case CAMERA_INVINCIBLE:
				m_pBeamCamera->SetTempData(m_pInvincibleCamera->GetTempPos(), m_pInvincibleCamera->GetTempRot());
				break;
			}
			break;

		case CAMERA_INVINCIBLE:
			m_pInvincibleCamera->SetActive(true);
			switch(m_OldState) {
			case CAMERA_NORMAL:
				m_pInvincibleCamera->SetTempData(m_pNormalCamera->GetTempPos(), m_pNormalCamera->GetTempRot());
				break;
				
			case CAMERA_BEAM:
				m_pInvincibleCamera->SetTempData(m_pBeamCamera->GetTempPos(), m_pBeamCamera->GetTempRot());
				break;
			}
			break;

		case CAMERA_DEATHBLOW:
			m_pDeathblowCamera->SetActive(true);
			break;

		default:
			break;
		}
	}

	m_OldState = m_CameraState;
}

void CameraSelect::SetState(eCameraState nextState) {
	
	if(nextState != CAMERA_NORMAL) {
		switch(m_CameraState) {
		
		case CAMERA_NORMAL:
			break;

		case CAMERA_DEATHBLOW:
			return;

		case CAMERA_BEAM:
		case CAMERA_INVINCIBLE:
			if(nextState == CAMERA_DEATHBLOW) 
				break;
			return;
		}
	}

	m_CameraState = nextState;
}

void CameraSelect::OnEnable() {
	
	m_CameraState = CAMERA_NORMAL;
	m_OldState    = CAMERA_NORMAL;
	m_SwayData = D3DXVECTOR3(0,0,0);

	Hierarchy* pTask = Hierarchy::Create();
	m_pNormalCamera = (PlayerCamera*)pTask->FindWithName("PlayerCamera");
	m_pBeamCamera = (BeamCamera*)pTask->FindWithName("BeamCamera");
	m_pInvincibleCamera = (InvincibleCamera*)pTask->FindWithName("InvincibleCamera");
	m_pDeathblowCamera = (DeathblowCamera*)pTask->FindWithName("DeathblowCamera");
	
	m_pBeamCamera->SetActive(false);
	m_pInvincibleCamera->SetActive(false);
	m_pDeathblowCamera->SetActive(false);
}