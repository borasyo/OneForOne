//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [NormalBotton.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____NormalBotton_H_____
#define _____NormalBotton_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class NormalBotton : public GameObject {

private:
	bool m_bOnMouth;

public:
	// ObjectType
	CObject2D m_Object2D;

	NormalBotton();
	~NormalBotton();

	bool Start();
	void Update();
	void Draw();
	bool* GetBool();
	
	NormalBotton* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		NormalBotton* Child = static_cast<NormalBotton*>(Obj); 
		return Child;
	}
};

#endif