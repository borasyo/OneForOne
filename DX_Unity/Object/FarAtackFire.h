//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FarAtackFire.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FARATACKFIRE_H_____
#define _____FARATACKFIRE_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"
#include "BulletFogParent.h"

class FarAtackFire : public GameObject {

private:
	Hierarchy* m_pHierarchy;
	D3DXVECTOR3 m_Bez0,m_Bez1,m_Bez2;
	float m_fArriveTime,m_fTime;
	GameObject* m_pEnemyParent;
	GameObject* m_pBoss;
	GameObject* m_pEnemy;
	BulletFogParent* m_pBulletFogParent;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	FarAtackFire() {
		m_Name = "FarAtackFire";
		m_Object3D.SetFileName(_T("Fire.png"));
		
		// BulletFogŽæ“¾
		BulletFogParent Obj;
		m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
	}
	~FarAtackFire(){}

	bool Start();
	void Update();
	void Draw();
	
	FarAtackFire* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		FarAtackFire* Child = static_cast<FarAtackFire*>(Obj); 
		return Child;
	}
};

#endif