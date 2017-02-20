//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SkyDome.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SkyDome_H_____
#define _____SkyDome_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"

class SkyDome : public GameObject {

private:
	CObject3DModel m_Object3D;
	bool m_bMeteo;
	int m_nMeteoCnt;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	bool m_bDark;
	float m_fColor;

public:
	// ObjectType

	SkyDome();
	~SkyDome();

	bool Start();
	void Update();
	void FastDraw();
	void FreeFunction();

	bool* GetBool();
	
	SkyDome* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		SkyDome* Child = static_cast<SkyDome*>(Obj); 
		return Child;
	}
};

#endif