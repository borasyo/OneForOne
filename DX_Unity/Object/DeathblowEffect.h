//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DeathblowEffect.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DeathblowEffect_H_____
#define _____DeathblowEffect_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

/// -- ’è”
const int nMaxCenter = 3;

class DeathblowEffect : public GameObject {

private:
	D3DXVECTOR3 m_MoveCenter;
	D3DXVECTOR3 m_ScaleCenter[nMaxCenter];

	int m_nCnt;
	bool m_bFinish;
	Hierarchy* m_pHierarchy;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	// ObjectType
	CObject2D m_Right;
	CObject2D m_Left;
	CObject2D m_Center;

	DeathblowEffect();
	~DeathblowEffect();

	void Update();
	void Draw();
	
	DeathblowEffect* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		DeathblowEffect* Child = static_cast<DeathblowEffect*>(Obj); 
		return Child;
	}
};

#endif