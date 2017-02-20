//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainMenuTitle.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MainMenuTitle_H_____
#define _____MainMenuTitle_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class MainMenuTitle : public GameObject {

private:

public:
	// ObjectType
	CObject2D m_Object2D;

	MainMenuTitle();
	~MainMenuTitle();

	bool Start();
	void Update();
	void Draw();
	
	MainMenuTitle* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		MainMenuTitle* Child = static_cast<MainMenuTitle*>(Obj); 
		return Child;
	}
};

#endif