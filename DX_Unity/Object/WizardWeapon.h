//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [WizardWeapon.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____WIZARDWEAPON_H_____
#define _____WIZARDWEAPON_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"

class WizardWeapon : public GameObject {

private:

public:
	// ObjectType
	CObject3DModel m_Object3D;

	WizardWeapon(){
		m_Name = "WizardWeapon";
		m_Object3D.SetFileName(_T("WizardWeapon.x"));
	}
	~WizardWeapon(){}

	void Awake();
	void Update();
	void Draw();
	
	WizardWeapon* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		WizardWeapon* Child = static_cast<WizardWeapon*>(Obj); 
		return Child;
	}
};

#endif