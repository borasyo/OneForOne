//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SkeltonBulletParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SkeltonBulletParent_H_____
#define _____SkeltonBulletParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "SkeltonBullet.h"

class SkeltonBulletParent : public GameObject {

private:
	std::list<SkeltonBullet*> SkeltonBulletChild; 
	
public:
	// ObjectType

	SkeltonBulletParent();
	~SkeltonBulletParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	SkeltonBulletParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		SkeltonBulletParent* Child = static_cast<SkeltonBulletParent*>(Obj); 
		return Child;
	}
};

#endif