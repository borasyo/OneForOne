//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DeathblowCamera.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "DeathblowCamera.h"
#include "CameraSelect.h"

#include "Deathblow.h"

const float fInitDistance = 30.0f;

DeathblowCamera::DeathblowCamera() {
	m_Name = "DeathblowCamera";
}

DeathblowCamera::~DeathblowCamera() {
	
}

bool DeathblowCamera::Start(){
	
	m_pPlayer = Hierarchy::Create()->FindWithName("Player");
	m_pBoss = Hierarchy::Create()->FindWithTag("Boss");

	return true;
}

void DeathblowCamera::Update(){
	
	if(m_pDeathblow && m_pDeathblow->GetLife() > 0) {
		*(m_CameraData.GetLookatPt()) = *(m_pDeathblow->GetPosition());

		m_nCount++;

		if (m_nCount < 300) {
			m_Rotation.y += (Pai*2.0f) / 300.0f;
	
			m_fSin = sinf(m_Rotation.y);
			m_fCos = cosf(m_Rotation.y);
			float fSinDis = m_fSin * m_fDistance;
			float fCosDis = m_fCos * m_fDistance;
	
			// ˆÚ“®Œã‚ÌˆÊ’u‚ðŒvŽZ
			m_Position.x = m_pDeathblow->GetPosition()->x - fSinDis;
			m_Position.z = m_pDeathblow->GetPosition()->z - fCosDis;
		} else if (300 == m_nCount) {
			SetParent(m_pDeathblow);
		} else {
			m_fDistance += (100.0f - m_fDistance) / 60.0f;
			
			float fSinDis = m_fSin * m_fDistance;
			float fCosDis = m_fCos * m_fDistance;
			
			// ˆÚ“®Œã‚ÌˆÊ’u‚ðŒvŽZ
			m_Position.x = m_pDeathblow->GetPosition()->x - fSinDis;
			m_Position.z = m_pDeathblow->GetPosition()->z - fCosDis;
			
			if(m_pDeathblow->GetName() != "Deathblow") {
				m_pDeathblow = nullptr;
			}
		}

	} else {

		m_nWaitCount++;

		if(m_nWaitCount < 60) {
			m_fDistance -= (m_fDistance - fInitDistance) / 30.0f;

			float fSinDis = m_fSin * m_fDistance;
			float fCosDis = m_fCos * m_fDistance;
	
			// ˆÚ“®Œã‚ÌˆÊ’u‚ðŒvŽZ
			m_Position.x = m_CameraData.GetLookatPt()->x - fSinDis;
			m_Position.z = m_CameraData.GetLookatPt()->z - fCosDis;

		} else if(m_nWaitCount > 90) {
			CameraSelect::SetState(CAMERA_NORMAL);

			float fRad = atan2f(m_pBoss->GetPosition()->x - m_pPlayer->GetPosition()->x, m_pBoss->GetPosition()->z - m_pPlayer->GetPosition()->z) - m_pPlayer->GetRotation()->y;
			m_pPlayer->Rotation(D3DXVECTOR3(0, fRad, 0));
			return;
		}
	}
}

void DeathblowCamera::FastDraw(){
	
	m_CameraData.Set(m_Position);
}

void DeathblowCamera::OnEnable() {

	m_pDeathblow = Hierarchy::Create()->FindWithName("Deathblow");
	
//	m_Position = *(Hierarchy::Create()->FindWithName("Player")->GetPosition());
	m_Position.y = 20.0f;

	m_nCount = 0;
	m_nWaitCount = 0;
	m_fDistance = fInitDistance;
}

void DeathblowCamera::OnDisable() {
	
}