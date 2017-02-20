//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameClear.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____GameClear_H_____
#define _____GameClear_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/Task/SceneManager.h"

class GameClear : public GameObject {

private:
	CObject2D m_Fade;
	CObject2D m_Fast;
	CObject2D m_Skill;
	CObject2D m_Stoic;
	CObject2D m_FastRank;
	CObject2D m_SkillRank;
	CObject2D m_StoicRank;
	float fAlpha;
	bool m_bFadeFlg;
	int m_nFadeCnt;
	SceneManager* m_pSceneManager;

	D3DXVECTOR3 m_FadeScale;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	CDirectInputManager* m_pDirectInputManager;
	
	D3DXVECTOR3 m_Pos[6];
	D3DXVECTOR3 m_Size[6];

public:
	GameClear();
	~GameClear();

	bool Start();
	void Update();
	void LateDraw();
	bool* GetBool();
	
	GameClear* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		GameClear* Child = static_cast<GameClear*>(Obj); 
		return Child;
	}
};

#endif