//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameClearCamera.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____GameClearCamera_H_____
#define _____GameClearCamera_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/ObjectCamera.h"
#include "BulletFogParent.h"

// --- ’è”
const int nGameClearTime = 480;

class GameClearCamera : public GameObject {

private:
	// ObjectType
	CObjectCamera m_ObjectCamera;

	float m_fAngle;
	float m_fDistance;
	int m_nCnt;
	D3DXVECTOR3 m_Pos;
	GameObject* m_pBoss;
	BulletFogParent* m_pFog;

public:

	GameClearCamera();
	~GameClearCamera();

	void Update();
	void Draw();
	
	GameClearCamera* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		GameClearCamera* Child = static_cast<GameClearCamera*>(Obj); 
		return Child;
	}
};

#endif