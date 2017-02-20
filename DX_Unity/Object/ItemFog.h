//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ItemFog.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____ItemFog_H_____
#define _____ItemFog_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"
#include "../Library/DirectX/Direct3D.h"

class ItemFog : public GameObject {

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

	ItemFog() : m_Move(D3DXVECTOR3(0,0,0)){
		m_Name = "ItemFog";
		m_Object3D.SetFileName(_T("Shadow.jpg"));
		m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	}
	~ItemFog(){}

	bool Start();
	void Update();
	void Draw();
	void FreeFunction();
	
	ItemFog* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		ItemFog* Child = static_cast<ItemFog*>(Obj); 
		return Child;
	}
};

#endif