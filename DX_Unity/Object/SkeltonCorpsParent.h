//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SkeltonCorpsParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SkeltonCorpsParent_H_____
#define _____SkeltonCorpsParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "SkeltonCorps.h"

class SkeltonCorpsParent : public GameObject {

private:
	std::list<SkeltonCorps*> SkeltonCorpsChild; 

public:
	// ObjectType

	SkeltonCorpsParent();
	~SkeltonCorpsParent();
	
	void Update();
	void FastDraw();

	GameObject* CreateChild();
	
	SkeltonCorpsParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		SkeltonCorpsParent* Child = static_cast<SkeltonCorpsParent*>(Obj); 
		return Child;
	}
};

#endif