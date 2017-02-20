//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [HardBotton.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____HardBotton_H_____
#define _____HardBotton_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class HardBotton : public GameObject {

private:
	bool m_bOnMouth;

public:
	// ObjectType
	CObject2D m_Object2D;

	HardBotton();
	~HardBotton();

	bool Start();
	void Update();
	void Draw();
	bool* GetBool();
	
	HardBotton* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		HardBotton* Child = static_cast<HardBotton*>(Obj); 
		return Child;
	}
};

#endif