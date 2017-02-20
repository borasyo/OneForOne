//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [WizardImpactParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____WizardImpactParent_H_____
#define _____WizardImpactParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "WizardImpact.h"

class WizardImpactParent : public GameObject {

private:
	std::list<WizardImpact*> WizardImpactChild; 

public:
	// ObjectType

	WizardImpactParent();
	~WizardImpactParent();
	
	void FastUpdate();
	void Update();
	void LateUpdate();
	void FastDraw();
	void Draw();
	void LateDraw();

	GameObject* CreateChild();
	
	WizardImpactParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		WizardImpactParent* Child = static_cast<WizardImpactParent*>(Obj); 
		return Child;
	}
};

#endif