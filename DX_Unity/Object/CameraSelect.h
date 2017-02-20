//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CameraSelect.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CameraSelect_H_____
#define _____CameraSelect_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"

#include "PlayerCamera.h"
#include "BeamCamera.h"
#include "DeathblowCamera.h"
#include "InvincibleCamera.h"

enum eCameraState {

	CAMERA_NORMAL = 0,
	CAMERA_BEAM,
	CAMERA_INVINCIBLE,
	CAMERA_DEATHBLOW,

	CAMERA_MAX,
};

class CameraSelect : public GameObject {

private:
	static eCameraState m_CameraState;
	eCameraState m_OldState;
	
	PlayerCamera* m_pNormalCamera;
	BeamCamera* m_pBeamCamera;
	InvincibleCamera* m_pInvincibleCamera;
	DeathblowCamera* m_pDeathblowCamera;
	
	D3DXVECTOR3 m_SwayData;

public:
	// ObjectType

	CameraSelect();
	~CameraSelect();

	bool Start();
	void FastUpdate();
//	void Update();

	void OnEnable();
	
	D3DXVECTOR3* GetVec() { return &m_SwayData; }

	static void SetState(eCameraState nextState);
	static eCameraState GetCameraState() { return m_CameraState; }
	
	CameraSelect* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		CameraSelect* Child = static_cast<CameraSelect*>(Obj); 
		return Child;
	}
};

#endif