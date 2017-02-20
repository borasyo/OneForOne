//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Devil.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DEVIL_H_____
#define _____DEVIL_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"
#include "../Library/DirectX/Direct3D.h"
#include "../Library/Debug/FPSController.h"

#include "MeteoParent.h"
#include "BulletFogParent.h"
#include "DragonParent.h"

class Devil : public GameObject {

private:
	int m_nBulletCnt;
	int m_nCorpsCnt;
	int m_nMeteoCnt;
	int m_nBeamCnt;
	int m_nActionStopCnt;
	int m_nDragonCnt;
	int m_nInvincibleCnt;
	int m_nDamage;
	int m_nOldLife;
	int m_nAngryCnt;
	bool m_bStart;
	bool m_bBeam;
	bool m_bAtack;
	bool m_bPreparation;
	bool m_bKnockBack;
	bool m_bInvincible;
	bool m_bAngry;
	float m_fRot;
	GameObject* m_pMeteoParent;
	GameObject* m_pSkeltonCorpsParent;
	GameObject* m_pSkeltonBulletParent;
	GameObject* m_pActionStopParent;
	GameObject* m_pBeam;
	DragonParent* m_pDragonParent;
	Hierarchy* m_pHierarchy;
	std::list<GameObject*> pBeamList;
	std::list<D3DXVECTOR3> MoveList;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	BulletFogParent* m_pBulletFogParent;
	FPSController* m_pFPSController;

	// 難易度調整
	int m_nLevel;
	float m_fLifeLevel;
	float m_fAtackLevel;

	void CheckAtack(GameObject* pPlayer); // 攻撃を行うかチェック
	D3DXVECTOR3 Random();

public:
	// ObjectType
	CObject3DModel m_Object3D;

	Devil();
	~Devil();

	void Awake();
	void LateUpdate();
	void FastDraw();

	void FreeFunction();
	int* GetInt(); 
	bool* GetBool();

	void DownCount( int nAmount = 45, bool bFlg = true );
	
	Devil* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // 失敗!!!
			return nullptr;

		Devil* Child = static_cast<Devil*>(Obj); 
		return Child;
	}
};

#endif