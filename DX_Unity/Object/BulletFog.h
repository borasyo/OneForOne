//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [BulletFog.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____BULLETFOG_H_____
#define _____BULLETFOG_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"

class BulletFog : public GameObject {

private:
	D3DXVECTOR3 m_Move;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	float m_fDeathSize;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	BulletFog():m_Move(D3DXVECTOR3(0,0,0)){
		m_Name = "BulletFog";
		m_Object3D.SetFileName(_T("Shadow.jpg"));
		m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	}
	~BulletFog(){}

	bool Start(D3DXCOLOR FogCol, float fMove, float fDeathSize);
	void Update();
	void Draw();
	
	BulletFog* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		BulletFog* Child = static_cast<BulletFog*>(Obj); 
		return Child;
	}
};

#endif