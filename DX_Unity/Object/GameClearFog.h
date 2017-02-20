//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameClearFog.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____GameClearFog_H_____
#define _____GameClearFog_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"

class GameClearFog : public GameObject {

private:
	D3DXVECTOR3 m_Move;
	D3DXVECTOR3 m_scale;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	GameClearFog();
	~GameClearFog();

	bool Start();
	void Update();
	void Draw();
	
	GameClearFog* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		GameClearFog* Child = static_cast<GameClearFog*>(Obj); 
		return Child;
	}
};

#endif