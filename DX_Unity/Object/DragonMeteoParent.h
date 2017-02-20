//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DragonMeteoParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DragonMeteoParent_H_____
#define _____DragonMeteoParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "DragonMeteo.h"

class DragonMeteoParent : public GameObject {

private:
	std::list<DragonMeteo*> DragonMeteoChild; 

public:
	// ObjectType

	DragonMeteoParent();
	~DragonMeteoParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	DragonMeteoParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		DragonMeteoParent* Child = static_cast<DragonMeteoParent*>(Obj); 
		return Child;
	}
};

#endif