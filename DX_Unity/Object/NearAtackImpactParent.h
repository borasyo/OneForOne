//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [NearAtackImpactParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____NearAtackImpactParent_H_____
#define _____NearAtackImpactParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "NearAtackImpact.h"

class NearAtackImpactParent : public GameObject {

private:
	std::list<NearAtackImpact*> NearAtackImpactChild; 

public:
	// ObjectType

	NearAtackImpactParent();
	~NearAtackImpactParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	NearAtackImpactParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		NearAtackImpactParent* Child = static_cast<NearAtackImpactParent*>(Obj); 
		return Child;
	}
};

#endif