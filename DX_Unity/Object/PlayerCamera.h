//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [PlayerCamera.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____PLAYERCAMERA_H_____
#define _____PLAYERCAMERA_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/ObjectCamera.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "Player.h"

class PlayerCamera : public GameObject {

private:
	float m_fHeight;
	float m_fDistance;
	float m_fVartical;
	float m_fRegulation;
	float m_fSin,m_fCos;
	CDirectInputManager* m_pDirectInputManager;

	Player* m_pPlayer;
	D3DXVECTOR3 m_TempPos;
	D3DXVECTOR3 m_TempRot;

	// --- ��u���p�ϐ�
	bool m_bSway;
	int m_nNowTime;
	int m_nMaxTime;
	float m_fSwayRange;
	float m_fTotalSway;
	bool m_bBeside;
	bool m_bUp;
	D3DXVECTOR3 m_SwayData;
	float m_fSwayAmount;

public:
	// ObjectType
	CObjectCamera m_ObjectCamera;

	PlayerCamera(Player* pPlayer){
		m_Name = "PlayerCamera";
		m_pPlayer = pPlayer;
	}
	~PlayerCamera(){}

	bool Start();
	void Update();
	void FastDraw();

	void FreeFunction();
	float* GetFloat();
	bool* GetBool();
	void Set(D3DXVECTOR3 TempPos, D3DXVECTOR3 TempRot) {
		m_TempPos = TempPos;
		m_TempRot = TempRot;
	}
	D3DXVECTOR3* GetVec() { return &m_SwayData; }

	// ���ԁA�h���͈́A�h���X�s�[�h�A�c�������A�v���X��������h��邩
	void Sway( int nTime, float fSwayRange, bool bBeside, bool bUp = true );
	
	//	�؂�ւ��p
	void SetTempData(D3DXVECTOR3 TempPos, D3DXVECTOR3 TempRot) {
		m_TempPos = TempPos;
		m_TempRot = TempRot;
	}
	D3DXVECTOR3 GetTempPos() { return m_TempPos; }
	D3DXVECTOR3 GetTempRot() { return m_TempRot; }
	
	PlayerCamera* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // ���s!!!
			return nullptr;

		PlayerCamera* Child = static_cast<PlayerCamera*>(Obj); 
		return Child;
	}
};

#endif