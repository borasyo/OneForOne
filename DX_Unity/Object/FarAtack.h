//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FarAtack.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FARATACK_H_____
#define _____FARATACK_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"

class FarAtack : public GameObject {

private:
	bool m_bAtack;
	int m_nCnt;
	GameObject* m_pFireParent; 

public:
	// ObjectType
	CObject3DModel m_Object3D;

	FarAtack();
	~FarAtack();

	void Awake();
	void Update();
	void Draw();

	void Atack();
	
	FarAtack* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		FarAtack* Child = static_cast<FarAtack*>(Obj); 
		return Child;
	}
};

#endif