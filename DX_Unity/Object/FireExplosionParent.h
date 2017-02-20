//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FireExplosionParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FireExplosionParent_H_____
#define _____FireExplosionParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "FireExplosion.h"

class FireExplosionParent : public GameObject {

private:
	std::list<FireExplosion*> FireExplosionChild; 

public:
	// ObjectType

	FireExplosionParent();
	~FireExplosionParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	FireExplosionParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		FireExplosionParent* Child = static_cast<FireExplosionParent*>(Obj); 
		return Child;
	}
};

#endif