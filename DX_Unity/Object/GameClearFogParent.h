//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameClearFogParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____GameClearFogParent_H_____
#define _____GameClearFogParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "GameClearFog.h"

class GameClearFogParent : public GameObject {

private:
	std::list<GameClearFog*> GameClearFogChild; 
	int m_nCnt;

public:
	// ObjectType

	GameClearFogParent();
	~GameClearFogParent();
	
	bool Start();
	void Update();
	void Draw();

	GameObject* CreateChild();
	
	GameClearFogParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		GameClearFogParent* Child = static_cast<GameClearFogParent*>(Obj); 
		return Child;
	}
};

#endif