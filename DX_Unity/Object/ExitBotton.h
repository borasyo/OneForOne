//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ExitBotton.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____ExitBotton_H_____
#define _____ExitBotton_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class ExitBotton : public GameObject {

private:
	bool m_bOnMouth;

public:
	// ObjectType
	CObject2D m_Object2D;

	ExitBotton();
	~ExitBotton();

	bool Start();
	void Update();
	void Draw();
	bool* GetBool();
	
	ExitBotton* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		ExitBotton* Child = static_cast<ExitBotton*>(Obj); 
		return Child;
	}
};

#endif