//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainLight.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MAINLIGHTRL_H_____
#define _____MAINLIGHTRL_H_____

#include <iostream>
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/ObjectDirectionLight.h"

class MainLightRL : public GameObject {

private:

public:
	// ObjectType
	CObjectDirectionLight m_ObjectLight;

	MainLightRL(){
		m_Name = "MainLight";
	}
	~MainLightRL(){}

	bool Start(){
		m_ObjectLight.SetVecDirection( D3DXVECTOR3(1,-1,-1) );
		m_bCollision = false;
		//m_ObjectLight.SwitchLight(false);
		return true;
	}

	void Update(){

		//if( rand()%10 == 0 )
		//	m_ObjectLight.SwitchLight(rand()%2);
	}

	MainLightRL* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // ���s!!!
			return nullptr;

		MainLightRL* Child = static_cast<MainLightRL*>(Obj); 
		return Child;
	}
};

#endif