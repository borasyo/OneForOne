//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CollisionEasyMode.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CollisionEasyMode_H_____
#define _____CollisionEasyMode_H_____

#include <iostream>
#include "../Library/Task/Empty.h"
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Collision.h"
#include "BloodParent.h"
#include "Player.h"

class CollisionEasyMode : public GameObject {

private:
	Collision m_Collision;
	Hierarchy* m_pHierarchy;
	int m_nMaxBlood;
	GameObject* pBoss;

	// コリジョンチェックするオブジェクトの親
	GameObject* m_pWizardCollision;
	GameObject* m_pFireExplosionParent;
	GameObject* m_pBeamParent;
	BloodParent* m_pBloodParent;
	GameObject* m_pNear;
	GameObject* pFade;
	GameObject* m_pFireParent;

	// 血しぶき作成
	void CreateBlood( D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos, bool bMore = false );
	D3DXVECTOR3 RandomPos(D3DXVECTOR3 BossPos);

public:
	// ObjectType

	CollisionEasyMode();
	~CollisionEasyMode();

	bool Start();
	void LateUpdate();
	
	CollisionEasyMode* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // 失敗!!!
			return nullptr;

		CollisionEasyMode* Child = static_cast<CollisionEasyMode*>(Obj); 
		return Child;
	}
};

#endif