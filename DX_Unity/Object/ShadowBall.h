//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ShadowBall.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SHADOWBALL_H_____
#define _____SHADOWBALL_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"
#include "BulletFogParent.h"

class ShadowBall : public GameObject {

private:
	Hierarchy* m_pHierarchy;
	D3DXVECTOR3 m_Bez0,m_Bez1,m_Bez2;
	float m_fArriveTime,m_fTime;
	int m_nFogCnt;
	BulletFogParent* m_pBulletFogParent;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	ShadowBall(){
		m_Name = "ShadowBall";
			m_Object3D.SetFileName(_T("BlueBall.png"));
		m_pHierarchy = Hierarchy::Create();

		// BulletFogŽæ“¾
		BulletFogParent Obj;
		m_pBulletFogParent = Obj.GetDownCastClass(m_pHierarchy->FindWithName("BulletFogParent"));
	}
	~ShadowBall(){}

	bool Start();
	void Update();
	void FastDraw();
	
	ShadowBall* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		ShadowBall* Child = static_cast<ShadowBall*>(Obj); 
		return Child;
	}
};

#endif