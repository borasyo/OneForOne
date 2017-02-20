//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CollisionHardMode.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CollisionHardMode_H_____
#define _____CollisionHardMode_H_____

#include <iostream>
#include "../Library/Task/Empty.h"
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Collision.h"
#include "BloodParent.h"
#include "FireExplosionParent.h"
#include "WizardFogParent.h"
#include "Player.h"

class CollisionHardMode : public GameObject {

private:
	Collision m_Collision;
	Hierarchy* m_pHierarchy;	
	int m_nMaxBlood;
	GameObject* pBoss;
	
	// コリジョンチェックするオブジェクトの親
	GameObject* m_pMeteoParent;
	GameObject* m_pSkeltonCorpsParent;
	GameObject* m_pSkeltonBulletParent;
	GameObject* m_pFireExplosionParent;
	GameObject* m_pBeamParent;
	GameObject* m_pNear;
	GameObject* m_pActionStopParent;
	GameObject* pFade;
	GameObject* m_pFireParent;
	GameObject* m_pDragonFireParent;
	GameObject* m_pNearAtackParent;
	BloodParent* m_pBloodParent;
	WizardFogParent* m_pFogParent;

	// 血しぶき作成
	void CreateBlood( D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos, bool bMore = false );
	D3DXVECTOR3 RandomPos( D3DXVECTOR3 pos );

public:
	// ObjectType

	CollisionHardMode();
	~CollisionHardMode();

	bool Start();
	void LateUpdate();
	
	CollisionHardMode* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // 失敗!!!
			return nullptr;

		CollisionHardMode* Child = static_cast<CollisionHardMode*>(Obj); 
		return Child;
	}
};

#endif