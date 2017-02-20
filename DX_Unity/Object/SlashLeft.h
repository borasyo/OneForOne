//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SlashLeft.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SlashLeft_H_____
#define _____SlashLeft_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"
#include "../Library/DirectX/Direct3D.h"

class SlashLeft : public GameObject {

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	D3DXVECTOR3 m_Move;
	int m_nCnt;

public:
	// ObjectType
	CObject2D m_Object2D;

	SlashLeft();
	~SlashLeft();

	void Update();
	void Draw();
	
	SlashLeft* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		SlashLeft* Child = static_cast<SlashLeft*>(Obj); 
		return Child;
	}
};

#endif