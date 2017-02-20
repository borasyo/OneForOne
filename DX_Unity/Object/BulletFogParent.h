//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [BulletFogParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____BulletFogParent_H_____
#define _____BulletFogParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "BulletFog.h"

class BulletFogParent : public GameObject {

private:
	std::list<BulletFog*> BulletFogChild; 

public:
	// ObjectType

	BulletFogParent();
	~BulletFogParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild(D3DXCOLOR FogCol, float fMove = 1.0f, float fDeathSize = 0.2f );
	
	BulletFogParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		BulletFogParent* Child = static_cast<BulletFogParent*>(Obj); 
		return Child;
	}
};

#endif