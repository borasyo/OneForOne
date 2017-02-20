//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Shadow.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SHADOW_H_____
#define _____SHADOW_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"
#include "../Library/DirectX/Direct3D.h"

class Shadow : public GameObject {

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	bool m_bAdd;
	bool m_bInit;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	Shadow( D3DXCOLOR Color = D3DXCOLOR(0.6f,0.6f,0.6f,0.6f), bool bAdd = false ){
		m_Name = "Shadow";
		m_Object3D.SetFileName(_T("Shadow.jpg"));
		m_Object3D.MakeVertexPolygon();
		m_Object3D.SetVertexColor(Color);
		m_bAdd = bAdd;
		m_bInit = false;
	}
	~Shadow(){}

	bool Start();
	void LateUpdate();
	void FastDraw();
	
	Shadow* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		Shadow* Child = static_cast<Shadow*>(Obj); 
		return Child;
	}
};

#endif