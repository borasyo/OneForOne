//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DragonMeteo.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DragonMeteo_H_____
#define _____DragonMeteo_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"
#include "BulletFogParent.h"

class DragonMeteo : public GameObject {

private:
	Hierarchy* m_pHierarchy;
	BulletFogParent* m_pBulletFogParent;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	DragonMeteo();
	~DragonMeteo();

	bool Start();
	void Update();
	void Draw();
	
	DragonMeteo* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		DragonMeteo* Child = static_cast<DragonMeteo*>(Obj); 
		return Child;
	}
};

#endif