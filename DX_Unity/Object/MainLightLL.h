//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainLight.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MAINLIGHTLL_H_____
#define _____MAINLIGHTLL_H_____

#include <iostream>
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/ObjectDirectionLight.h"

class MainLightLL : public GameObject {

private:

public:
	// ObjectType
	CObjectDirectionLight m_ObjectLight;

	MainLightLL(){
		m_Name = "MainLight";
	}
	~MainLightLL(){}

	bool Start(){
		m_ObjectLight.SetVecDirection( D3DXVECTOR3(-1,-1,-1) );
		m_bCollision = false;
		//m_ObjectLight.SwitchLight(false);
		return true;
	}

	void Update(){

		//if( rand()%10 == 0 )
		//	m_ObjectLight.SwitchLight(rand()%2);
	}

	MainLightLL* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		MainLightLL* Child = static_cast<MainLightLL*>(Obj); 
		return Child;
	}
};

#endif