//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [WizardFog.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____WIZARDFOG_H_____
#define _____WIZARDFOG_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"
#include "../Library/DirectX/Direct3D.h"

class WizardFog : public GameObject {

private:
	D3DXVECTOR3 m_Move;
	D3DXVECTOR3 m_scale;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	WizardFog() : m_Move(D3DXVECTOR3(0,0,0)){
		m_Name = "WizardFog";
		m_Object3D.SetFileName(_T("Shadow.jpg"));
		m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	}
	~WizardFog(){}

	bool Start();
	void Update();
	void Draw();
	
	WizardFog* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		WizardFog* Child = static_cast<WizardFog*>(Obj); 
		return Child;
	}
};

#endif