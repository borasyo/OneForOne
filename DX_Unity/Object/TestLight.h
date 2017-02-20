//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [TestLight.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TEST_LIGHT_H_____
#define _____TEST_LIGHT_H_____

#include <iostream>
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/ObjectDirectionLight.h"
#include "../Library/ObjectType/ObjectSpotLight.h"
#include "../Library/ObjectType/ObjectPointLight.h"

class TestLight : public GameObject {

private:

public:
	// ObjectType
	CObjectPointLight m_ObjectLight;

	TestLight(){
		m_Name = "TestLight";
	}
	~TestLight(){}

	bool Start(){
	#if _DEBUG
		std::cout << m_Name + "!" << std::endl;
	#endif
		///m_ObjectLight.SetVecDirection( D3DXVECTOR3(1,1,1) );
		return true;
	}
	
	void Update(){
		if( !m_bActive ) return;
	#if _DEBUG
		std::cout << m_Name + "." << std::endl;
	#endif
	}

	void Draw(){
		if( !m_bActive ) return;

	#if _DEBUG
		std::cout << m_Name + "-" << std::endl;
	#endif
	}

	TestLight* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		TestLight* Child = static_cast<TestLight*>(Obj); 
		return Child;
	}
};

#endif