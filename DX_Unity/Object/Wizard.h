//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Wizard.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Wizard_H_____
#define _____Wizard_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"
#include "WizardFogParent.h"
#include "BulletFogParent.h"

class Wizard : public GameObject {

private:
	Hierarchy* m_pHierarchy;
	int m_nAtackCnt;
	int m_nTeleportationCnt;
	float m_fAtackRot;
	bool m_bNear;
	bool m_bBeam;
	bool m_bStart;
	bool m_bAssault;
	GameObject* m_pPlayer;
	GameObject* m_pWizardCollision;
	GameObject* m_pImpactParent;
	GameObject* m_pBeamHolder;
	WizardFogParent* m_pFogParent;
	BulletFogParent* m_pBulletFogParent;
	
	D3DXVECTOR3 m_Move;
	
	void KnifeAtack();
	void AssaultAtack();
	void CheckAtack();
	void Teleportation();
	D3DXVECTOR3 Random();

public:
	// ObjectType
	CObject3DModel m_Object3D;

	Wizard();
	~Wizard();

	void Awake();
	void Update();
	void FastDraw();
	
	Wizard* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		Wizard* Child = static_cast<Wizard*>(Obj); 
		return Child;
	}
};

#endif