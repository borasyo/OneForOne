//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [WizardImpact.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____WIZARDIMPACT_H_____
#define _____WIZARDIMPACT_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"

class WizardImpact : public GameObject {

private:
	D3DXVECTOR3 m_Move;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	WizardImpact(){
		m_Name = "WizardImpact";
		m_Object3D.SetFileName(_T("Shadow.jpg"));
		m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	}
	~WizardImpact(){}

	bool Start();
	void Update();
	void Draw();
	
	WizardImpact* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		WizardImpact* Child = static_cast<WizardImpact*>(Obj); 
		return Child;
	}
};

#endif