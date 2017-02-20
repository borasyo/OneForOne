//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainMenuCollision.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MainMenuCollision_H_____
#define _____MainMenuCollision_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/ObjectType/Collision.h"
#include "../Library/DirectX/MouthPosition.h"

class MainMenuCollision : public GameObject {
	
private:
	Collision m_Collision;
	GameObject* pMouse;
	GameObject* pEasy;
	GameObject* pNormal;
	GameObject* pHard;
	GameObject* pExit;
	GameObject* pHelp;

	CDirectInputManager* m_pDirectInputManager;
	CMouthPosition* m_pMouthPosition;

	bool Collision2DCube( GameObject*, GameObject* );

public:
	// ObjectType

	MainMenuCollision();
	~MainMenuCollision();

	bool Start();
	void LateUpdate();
	
	MainMenuCollision* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		MainMenuCollision* Child = static_cast<MainMenuCollision*>(Obj); 
		return Child;
	}
};

#endif