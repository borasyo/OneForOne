//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FieldCollision.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FieldCollision_H_____
#define _____FieldCollision_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Collision.h"

class FieldCollision : public GameObject {

private:
	Collision m_Collision;
	Hierarchy* m_pHierarchy;

public:
	// ObjectType
	
	FieldCollision();
	~FieldCollision();

	bool Start();
	void LateUpdate();
	
	FieldCollision* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		FieldCollision* Child = static_cast<FieldCollision*>(Obj); 
		return Child;
	}
};

#endif