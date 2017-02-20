//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [HelpBotton.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____HelpBotton_H_____
#define _____HelpBotton_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class HelpBotton : public GameObject {

private:
	bool m_bOnMouth;

public:
	// ObjectType
	CObject2D m_Object2D;

	HelpBotton();
	~HelpBotton();

	bool Start();
	void Update();
	void Draw();
	bool* GetBool();
	
	HelpBotton* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		HelpBotton* Child = static_cast<HelpBotton*>(Obj); 
		return Child;
	}
};

#endif