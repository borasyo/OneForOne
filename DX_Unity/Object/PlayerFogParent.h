//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [PlayerFogParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____PlayerFogParent_H_____
#define _____PlayerFogParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "PlayerFog.h"

class PlayerFogParent : public GameObject {

private:
	std::list<PlayerFog*> PlayerFogChild; 

public:
	// ObjectType

	PlayerFogParent();
	~PlayerFogParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	PlayerFogParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		PlayerFogParent* Child = static_cast<PlayerFogParent*>(Obj); 
		return Child;
	}
};

#endif