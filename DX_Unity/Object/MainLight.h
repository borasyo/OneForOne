//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainLight.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MAINLIGHT_H_____
#define _____MAINLIGHT_H_____

#include <iostream>
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/ObjectDirectionLight.h"
#include "MainLightLL.h"
#include "MainLightLR.h"
#include "MainLightRL.h"
#include "MainLightRR.h"

class MainLight : public GameObject {

private:

public:
	// ObjectType
	CObjectDirectionLight m_ObjectLight;

	MainLight(){
		m_Name = "MainLight";

		Hierarchy* pHierarchy =  Hierarchy::Create();
		pHierarchy->CreateObject(new MainLightLL);
		pHierarchy->CreateObject(new MainLightRL);
		pHierarchy->CreateObject(new MainLightLR);
		pHierarchy->CreateObject(new MainLightRR);
	}
	~MainLight(){}

	bool Start(){
		m_ObjectLight.SetVecDirection( D3DXVECTOR3(0,-1,0) );
		m_bCollision = false;
		//m_ObjectLight.SwitchLight(false);
		return true;
	}

	void Update(){

		//if( rand()%10 == 0 )
		//	m_ObjectLight.SwitchLight(rand()%2);
	}

	MainLight* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		MainLight* Child = static_cast<MainLight*>(Obj); 
		return Child;
	}
};

#endif