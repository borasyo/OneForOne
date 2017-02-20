//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DragonParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DragonParent_H_____
#define _____DragonParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "Dragon.h"

class DragonParent : public GameObject {

private:
	std::list<Dragon*> DragonChild; 

public:

	DragonParent();
	~DragonParent();
	
	void Update();
	void FastDraw();

	GameObject* CreateChild( float fAtackLevel );
	
	DragonParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		DragonParent* Child = static_cast<DragonParent*>(Obj); 
		return Child;
	}
};

#endif