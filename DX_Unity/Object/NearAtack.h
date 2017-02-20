//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [NearAtack.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____NEARATACK_H_____
#define _____NEARATACK_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"
#include "NearAtackImpactParent.h"

class NearAtack : public GameObject {

private:
	bool m_bAtack;
	int m_nCnt;

	GameObject* m_pNearAtackImpactParent;

public:
	// ObjectType
	CObject3DModel m_Object3D;

	NearAtack();
	~NearAtack(){}

	void Awake();
	void Update();
	void Draw();

	void Atack();
	
	NearAtack* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		NearAtack* Child = static_cast<NearAtack*>(Obj); 
		return Child;
	}
};

#endif