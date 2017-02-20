//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DeathblowCamera.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DeathblowCamera_H_____
#define _____DeathblowCamera_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/ObjectCamera.h"

class DeathblowCamera : public GameObject {

private:
	CObjectCamera m_CameraData;

	GameObject* m_pDeathblow;
	GameObject* m_pPlayer;
	GameObject* m_pBoss;
	
	int m_nCount;
	int m_nWaitCount;
	float m_fDistance;

	float m_fSin,m_fCos;
	
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

	DeathblowCamera();
	~DeathblowCamera();

	bool Start();
	void Update();
	void FastDraw();
	
	void OnEnable();
	void OnDisable();
	
	D3DXVECTOR3* GetVec() { return &m_SwayData; }

	// ���ԁA�h���͈́A�h���X�s�[�h�A�c�������A�v���X��������h��邩
	void Sway( int nTime, float fSwayRange, bool bBeside, bool bUp = true );
	
	DeathblowCamera* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // ���s!!!
			return nullptr;

		DeathblowCamera* Child = static_cast<DeathblowCamera*>(Obj); 
		return Child;
	}
};

#endif