//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Fire.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Fire_H_____
#define _____Fire_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"
#include "BulletFogParent.h"

class Fire : public GameObject {

private:
	D3DXVECTOR3 m_Move;
	Hierarchy* m_pHierarchy;
	BulletFogParent* m_pBulletFogParent;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	Fire();
	~Fire();

	bool Start();
	void Update();
	void Draw();
	
	Fire* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // ���s!!!
			return nullptr;

		Fire* Child = static_cast<Fire*>(Obj); 
		return Child;
	}
};

#endif