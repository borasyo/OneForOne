//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Beam.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Beam_H_____
#define _____Beam_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"

class Beam : public GameObject {

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	int m_nCollisionCnt;
	bool m_bAdd;
	D3DXCOLOR m_Color;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	Beam();
	~Beam();

	bool Start(D3DXCOLOR Color, D3DXVECTOR3 Scale, bool bAdd);
	void Update();
	void Draw();

	D3DXCOLOR* GetColor();
	
	Beam* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		Beam* Child = static_cast<Beam*>(Obj); 
		return Child;
	}
};

#endif