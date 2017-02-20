//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Meteo.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Meteo_H_____
#define _____Meteo_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"
#include "BulletFogParent.h"

class Meteo : public GameObject {

private:
	Hierarchy* m_pHierarchy;
	BulletFogParent* m_pBulletFogParent;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	bool m_bFall;
	int m_nTime;
	
public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	Meteo();
	~Meteo();

	bool Start();
	void Update();
	void Draw();

	void FreeFunction();
	
	Meteo* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		Meteo* Child = static_cast<Meteo*>(Obj); 
		return Child;
	}
};

#endif