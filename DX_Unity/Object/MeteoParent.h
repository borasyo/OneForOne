//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MeteoParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MeteoParent_H_____
#define _____MeteoParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "Meteo.h"

class MeteoParent : public GameObject {

private:
	std::list<Meteo*> MeteoChild; 

public:
	// ObjectType

	MeteoParent();
	~MeteoParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	MeteoParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		MeteoParent* Child = static_cast<MeteoParent*>(Obj); 
		return Child;
	}
};

#endif