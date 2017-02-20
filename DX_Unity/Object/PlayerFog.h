//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [PlayerFog.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____PLAYERFOG_H_____
#define _____PLAYERFOG_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"
#include "../Library/DirectX/Direct3D.h"

class PlayerFog : public GameObject {

private:
	Hierarchy* m_pHierarchy;
	D3DXVECTOR3 m_Move;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	bool m_bAbsorption;
	GameObject* m_pDeathblow;
	float fInitScale;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	PlayerFog() : m_Move(D3DXVECTOR3(0,0,0)){
		m_Name = "PlayerFog";
		m_Object3D.SetFileName(_T("Shadow.jpg"));
		m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	}
	~PlayerFog(){}

	bool Start();
	void Update();
	void Draw();
	void FreeFunction();
	
	PlayerFog* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		PlayerFog* Child = static_cast<PlayerFog*>(Obj); 
		return Child;
	}
};

#endif