//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CleaveImpactParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CleaveImpactParent_H_____
#define _____CleaveImpactParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "CleaveImpact.h"

class CleaveImpactParent : public GameObject {

private:
	std::list<CleaveImpact*> CleaveImpactChild; 

public:
	// ObjectType

	CleaveImpactParent();
	~CleaveImpactParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	CleaveImpactParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		CleaveImpactParent* Child = static_cast<CleaveImpactParent*>(Obj); 
		return Child;
	}
};

#endif