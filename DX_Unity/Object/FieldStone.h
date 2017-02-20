//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FieldStone.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FIELDSTONE_H_____
#define _____FIELDSTONE_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"

class FieldStone : public GameObject {

private:

public:
	// ObjectType
	CObject3DModel m_Object3D;

	FieldStone() {
		m_Name = "FieldStone";
		m_Object3D.SetFileName(_T("Stone.x"));
		m_bCollision = false;
		m_Scale = D3DXVECTOR3( 0.78f,0.78f,0.78f );
	}

	void FastDraw() {
		m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	}
	
	FieldStone* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		FieldStone* Child = static_cast<FieldStone*>(Obj); 
		return Child;
	}
};

#endif