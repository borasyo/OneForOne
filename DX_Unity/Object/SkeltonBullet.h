//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SkeltonBullet.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SkeltonBullet_H_____
#define _____SkeltonBullet_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"
#include "BulletFogParent.h"

class SkeltonBullet : public GameObject {

private:
	D3DXVECTOR3 m_Move;
	Hierarchy* m_pHierarchy;
	BulletFogParent* m_pBulletFogParent;
	float Vector(D3DXVECTOR3,D3DXVECTOR3);
	D3DXVECTOR3 RandomPos();

public:
	// ObjectType
	CObject3DModel m_Object3D;

	SkeltonBullet();
	~SkeltonBullet();

	bool Start();
	void Update();
	void Draw();
	
	SkeltonBullet* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		SkeltonBullet* Child = static_cast<SkeltonBullet*>(Obj); 
		return Child;
	}
};

#endif