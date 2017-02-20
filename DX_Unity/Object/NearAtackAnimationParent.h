//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [NearAtackAnimationParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____NearAtackAnimationParent_H_____
#define _____NearAtackAnimationParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "NearAtackAnimation.h"

class NearAtackAnimationParent : public GameObject {

private:
	std::list<NearAtackAnimation*> NearAtackAnimationChild; 

public:
	// ObjectType

	NearAtackAnimationParent();
	~NearAtackAnimationParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	NearAtackAnimationParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		NearAtackAnimationParent* Child = static_cast<NearAtackAnimationParent*>(Obj); 
		return Child;
	}
};

#endif