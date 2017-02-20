//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FireParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FireParent_H_____
#define _____FireParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "Fire.h"

class FireParent : public GameObject {

private:
	std::list<Fire*> FireChild; 

public:
	// ObjectType

	FireParent();
	~FireParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	FireParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		FireParent* Child = static_cast<FireParent*>(Obj); 
		return Child;
	}
};

#endif