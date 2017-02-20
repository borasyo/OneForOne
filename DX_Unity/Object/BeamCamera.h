//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [BeamCamera.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____BeamCamera_H_____
#define _____BeamCamera_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/ObjectCamera.h"

#include "../Library/DirectX/DirectInputManager.h"
#include "Player.h"

class BeamCamera : public GameObject {

private:
	CObjectCamera m_ObjectCamera;

	float m_fHeight;
	float m_fDistance;
	float m_fVartical;
	float m_fRegulation;
	float m_fSin,m_fCos;
	CDirectInputManager* m_pDirectInputManager;

	Player* m_pPlayer;
	D3DXVECTOR3 m_TempPos;
	D3DXVECTOR3 m_TempRot;
	
	// --- 画ブレ用変数
	bool m_bSway;
	int m_nNowTime;
	int m_nMaxTime;
	float m_fSwayRange;
	float m_fTotalSway;
	bool m_bBeside;
	bool m_bUp;
	D3DXVECTOR3 m_SwayData;
	float m_fSwayAmount;

	bool m_bOn;
	int m_nTime;

public:
	// ObjectType
	
	BeamCamera(Player* pPlayer){
		m_Name = "BeamCamera";
		m_pPlayer = pPlayer;
	}
	~BeamCamera(){}

	bool Start();
	void Update();
	void FastDraw();
	
	//	切り替え用
	void SetTempData(D3DXVECTOR3 TempPos, D3DXVECTOR3 TempRot) {
		m_TempPos = TempPos;
		m_TempRot = TempRot;
	}
	D3DXVECTOR3 GetTempPos() { return m_TempPos; }
	D3DXVECTOR3 GetTempRot() { return m_TempRot; }
	
	void OnEnable();
	void OnDisable();
	
	void FreeFunction();
	D3DXVECTOR3* GetVec() { return &m_SwayData; }

	// 時間、揺れる範囲、揺れるスピード、縦か横か、プラス方向から揺れるか
	void Sway( int nTime, float fSwayRange, bool bBeside, bool bUp = true );
	
	BeamCamera* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // 失敗!!!
			return nullptr;

		BeamCamera* Child = static_cast<BeamCamera*>(Obj); 
		return Child;
	}
};

#endif