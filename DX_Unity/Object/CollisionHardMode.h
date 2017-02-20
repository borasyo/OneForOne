//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CollisionHardMode.h]
// author : �哴�ˑ�
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
	
	// �R���W�����`�F�b�N����I�u�W�F�N�g�̐e
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

	// �����Ԃ��쐬
	void CreateBlood( D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos, bool bMore = false );
	D3DXVECTOR3 RandomPos( D3DXVECTOR3 pos );

public:
	// ObjectType

	CollisionHardMode();
	~CollisionHardMode();

	bool Start();
	void LateUpdate();
	
	CollisionHardMode* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // ���s!!!
			return nullptr;

		CollisionHardMode* Child = static_cast<CollisionHardMode*>(Obj); 
		return Child;
	}
};

#endif