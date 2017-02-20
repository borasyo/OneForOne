//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Rader.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Rader_H_____
#define _____Rader_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class Rader : public GameObject {

private:
	Hierarchy* m_pHierarchy;
	D3DXVECTOR3 m_PlayerPointPos;
	D3DXVECTOR3 m_PlayerPointScale;
	float m_fPlayerRot;
	D3DXVECTOR3 m_EnemyPointPos;
	D3DXVECTOR3 m_EnemyPointScale;
	LPDIRECT3DDEVICE9 m_pD3DDevice; // DirectXDevice
	
	GameObject* m_pPlayer;
	GameObject* m_pBoss;
	GameObject* m_pItem;
	GameObject* m_pDragon;

public:
	// ObjectType
	CObject2D m_Object2D;
	CObject2D m_ObjectEnemyPoint;
	CObject2D m_ObjectPlayerPoint;
	CObject2D m_ObjectItemPoint;
	CObject2D m_ObjectDragonPoint;

	Rader();
	~Rader();

	bool Start();
	void Update();
	void LateDraw();
	
	Rader* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		Rader* Child = static_cast<Rader*>(Obj); 
		return Child;
	}
};

#endif