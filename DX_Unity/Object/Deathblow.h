//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Deathblow.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DEATHBLOW_H_____
#define _____DEATHBLOW_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"
#include "BulletFogParent.h"
#include "../Library/DirectX/DirectInputManager.h"

class Deathblow : public GameObject {

private:
	GameObject* m_pTarget;
	GameObject* m_pPlayer;
	D3DXVECTOR3 m_Bez0,m_Bez1,m_Bez2;
	float m_fArriveTime,m_fTime;
	float m_fTempArriveTime;
	int m_nShotCnt;
	bool m_bShot;
	Hierarchy* m_pHierarchy;
	BulletFogParent* m_pBulletFogParent;
	CDirectInputManager* m_pDirectInputManager;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	void Count();
	void CreateEffect();

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	Deathblow();
	~Deathblow();

	bool Start();
	void Update();
	void Draw();
	void FreeFunction();
	bool* GetBool();
	
	Deathblow* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		Deathblow* Child = static_cast<Deathblow*>(Obj); 
		return Child;
	}
};

#endif