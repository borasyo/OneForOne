//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [WizardFogParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____WizardFogParent_H_____
#define _____WizardFogParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "WizardFog.h"

class WizardFogParent : public GameObject {

private:
	std::list<WizardFog*> WizardFogChild; 

public:
	// ObjectType

	WizardFogParent();
	~WizardFogParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	WizardFogParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		WizardFogParent* Child = static_cast<WizardFogParent*>(Obj); 
		return Child;
	}
};

#endif