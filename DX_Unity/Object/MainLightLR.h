//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainLight.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MAINLIGHTLR_H_____
#define _____MAINLIGHTLR_H_____

#include <iostream>
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/ObjectDirectionLight.h"

class MainLightLR : public GameObject {

private:

public:
	// ObjectType
	CObjectDirectionLight m_ObjectLight;

	MainLightLR(){
		m_Name = "MainLight";
	}
	~MainLightLR(){}

	bool Start(){
		m_ObjectLight.SetVecDirection( D3DXVECTOR3(-1,-1,1) );
		m_bCollision = false;
		//m_ObjectLight.SwitchLight(false);
		return true;
	}

	void Update(){

		//if( rand()%10 == 0 )
		//	m_ObjectLight.SwitchLight(rand()%2);
	}

	MainLightLR* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		MainLightLR* Child = static_cast<MainLightLR*>(Obj); 
		return Child;
	}
};

#endif