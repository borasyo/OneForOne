//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CollisionNormalMode.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CollisionNormalMode_H_____
#define _____CollisionNormalMode_H_____

#include <iostream>
#include "../Library/Task/Empty.h"
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Collision.h"
#include "BloodParent.h"
#include "Player.h"

class CollisionNormalMode : public GameObject {

private:
	Collision m_Collision;
	Hierarchy* m_pHierarchy;
	int m_nMaxBlood;
	GameObject* pBoss;

	// コリジョンチェックするオブジェクトの親
	GameObject* m_pDragonCollision;
	GameObject* m_pFireExplosionParent;
	GameObject* m_pBeamParent;
	BloodParent* m_pBloodParent;
	GameObject* m_pNear;
	GameObject* pFade;
	GameObject* m_pFireParent;
	GameObject* m_pDragonFireParent;
	GameObject* m_pMeteoParent;

	// 血しぶき作成
	void CreateBlood( D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos, bool bMore = false );
	D3DXVECTOR3 RandomPos(D3DXVECTOR3 BossPos);

public:
	// ObjectType

	CollisionNormalMode();
	~CollisionNormalMode();

	bool Start();
	void LateUpdate();
	
	CollisionNormalMode* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // 失敗!!!
			return nullptr;

		CollisionNormalMode* Child = static_cast<CollisionNormalMode*>(Obj); 
		return Child;
	}
};

#endif