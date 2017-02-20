//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FieldFlower.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FieldFlower_H_____
#define _____FieldFlower_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"

// --- ’è”
const int nSize = 150;

class FieldFlower : public GameObject {

private:
	D3DXVECTOR3 m_FlowerPos[nSize];
	D3DXVECTOR3 m_FlowerScale[nSize];

public:
	// ObjectType
	CObject3DModel m_Object3D[nSize];

	FieldFlower();
	~FieldFlower();

	bool Start();
	void Update();
	void Draw();
	
	FieldFlower* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		FieldFlower* Child = static_cast<FieldFlower*>(Obj); 
		return Child;
	}
};

#endif