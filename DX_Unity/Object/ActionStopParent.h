//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ActionStopParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____ActionStopParent_H_____
#define _____ActionStopParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "ActionStop.h"
#include "BulletFogParent.h"

class ActionStopParent : public GameObject {

private:
	std::list<ActionStop*> ActionStopChild; 
	GameObject* m_pPlayer;
	float m_fMoveSpeed;
	bool m_bAtack;
	float m_fHeight;
	BulletFogParent* m_pBulletFogParent;
	
	D3DXVECTOR3 RandomPos();

public:
	ActionStopParent();
	~ActionStopParent();

	bool Start();
	void Update();
	void Draw();

	void FreeFunction();

	GameObject* CreateChild();
	
	ActionStopParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		ActionStopParent* Child = static_cast<ActionStopParent*>(Obj); 
		return Child;
	}
};

#endif