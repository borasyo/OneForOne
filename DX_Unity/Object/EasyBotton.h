//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [EasyBotton.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____EasyBotton_H_____
#define _____EasyBotton_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class EasyBotton : public GameObject {

private:
	bool m_bOnMouth;

public:
	// ObjectType
	CObject2D m_Object2D;

	EasyBotton();
	~EasyBotton();

	bool Start();
	void Update();
	void Draw();
	bool* GetBool();
	
	EasyBotton* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		EasyBotton* Child = static_cast<EasyBotton*>(Obj); 
		return Child;
	}
};

#endif