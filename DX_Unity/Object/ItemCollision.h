//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ItemCollision.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____ItemCollision_H_____
#define _____ItemCollision_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Collision.h"

class ItemCollision : public GameObject {

private:
	Hierarchy* m_pHierarchy;
	GameObject* pParent;
	int m_nGetItemCnt;

public:
	// ObjectType
	Collision m_Collision;

	ItemCollision();
	~ItemCollision();

	bool Start();
	void LateUpdate();
	int * GetInt();
	
	ItemCollision* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		ItemCollision* Child = static_cast<ItemCollision*>(Obj); 
		return Child;
	}
};

#endif