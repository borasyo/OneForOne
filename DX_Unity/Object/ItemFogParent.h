//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ItemFogParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____ItemFogParent_H_____
#define _____ItemFogParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "ItemFog.h"

class ItemFogParent : public GameObject {

private:
	std::list<ItemFog*> ItemFogChild; 
	bool m_bFlg;
	int m_nCnt;

public:
	// ObjectType

	ItemFogParent();
	~ItemFogParent();
	
	bool Start();
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	ItemFogParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		ItemFogParent* Child = static_cast<ItemFogParent*>(Obj); 
		return Child;
	}
};

#endif