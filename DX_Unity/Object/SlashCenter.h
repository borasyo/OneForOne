//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SlashCenter.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SlashCenter_H_____
#define _____SlashCenter_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"
#include "../Library/DirectX/Direct3D.h"
#include "../Library/Task/SceneManager.h"

class SlashCenter : public GameObject {

private:
	SceneManager* m_pSceneManager;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	D3DXVECTOR3 m_Move;
	int m_nMode;
	int m_nCnt;

public:
	// ObjectType
	CObject2D m_Object2D;

	SlashCenter(int nMode);
	~SlashCenter();

	void Update();
	void Draw();
	
	SlashCenter* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		SlashCenter* Child = static_cast<SlashCenter*>(Obj); 
		return Child;
	}
};

#endif