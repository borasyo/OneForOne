//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [BloodParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____BloodParent_H_____
#define _____BloodParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "Blood.h"

class BloodParent : public GameObject {

private:
	std::list<Blood*> BloodChild; 

public:
	// ObjectType

	BloodParent();
	~BloodParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild(D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos);
	
	BloodParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		BloodParent* Child = static_cast<BloodParent*>(Obj); 
		return Child;
	}
};

#endif