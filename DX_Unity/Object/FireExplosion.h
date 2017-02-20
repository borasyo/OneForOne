//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FireExplosion.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FIREEXPLOSION_H_____
#define _____FIREEXPLOSION_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"

class FireExplosion : public GameObject {

private:
	CObject3DPolygon m_Object3D;
	int m_nChangeCnt;
	int m_nPattern;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	// ObjectType

	FireExplosion(){
		m_Name = "FireExplosion";
		m_Object3D.SetFileName(_T("FireExplosion.png"));
		Start();
	}
	~FireExplosion(){}

	bool Start();
	void Update();
	void Draw();
	
	FireExplosion* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		FireExplosion* Child = static_cast<FireExplosion*>(Obj); 
		return Child;
	}
};

#endif