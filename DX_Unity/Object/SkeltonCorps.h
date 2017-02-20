//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SkeltonCorps.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SkeltonCorps_H_____
#define _____SkeltonCorps_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"

class SkeltonCorps : public GameObject {

private:
	D3DXVECTOR3 m_Move;	 // ˆÚ“®—Ê
	bool m_bGrounded;

	D3DXVECTOR3 RandomPos();

public:
	// ObjectType
	CObject3DModel m_Object3D;

	SkeltonCorps();
	~SkeltonCorps();

	bool Start();
	void Update();
	void FastDraw();
	
	SkeltonCorps* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		SkeltonCorps* Child = static_cast<SkeltonCorps*>(Obj); 
		return Child;
	}
};

#endif