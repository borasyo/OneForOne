//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Danger.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Danger_H_____
#define _____Danger_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class Danger : public GameObject {

private:
	CObject2D m_Obj2D;
	GameObject* m_pPlayer;
	int m_nInitHp;

	bool m_bAdd;
	float m_fNowAlpha;
	float m_fNowMaxAlpha;

public:

	Danger();
	~Danger();

	bool Start();
	void Update();
	void LateDraw();
	
	Danger* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		Danger* Child = static_cast<Danger*>(Obj); 
		return Child;
	}
};

#endif