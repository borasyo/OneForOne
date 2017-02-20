//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SlashRight.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SlashRight_H_____
#define _____SlashRight_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"
#include "../Library/DirectX/Direct3D.h"
#include "../Library/Task/SceneManager.h"

class SlashRight : public GameObject {

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	D3DXVECTOR3 m_Move;
	int m_nCnt;

public:
	// ObjectType
	CObject2D m_Object2D;

	SlashRight();
	~SlashRight();

	void Update();
	void Draw();
	
	SlashRight* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		SlashRight* Child = static_cast<SlashRight*>(Obj); 
		return Child;
	}
};

#endif