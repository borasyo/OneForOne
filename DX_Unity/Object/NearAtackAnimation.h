//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [NearAtackAnimation.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____NearAtackAnimation_H_____
#define _____NearAtackAnimation_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"

class NearAtackAnimation : public GameObject {

private:
	CObject3DPolygon m_Object3D;

	int m_nPattern;
	int m_nChangeTime;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	NearAtackAnimation();
	~NearAtackAnimation();

	bool Start();
	void Update();
	void Draw();
	
	NearAtackAnimation* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		NearAtackAnimation* Child = static_cast<NearAtackAnimation*>(Obj); 
		return Child;
	}
};

#endif