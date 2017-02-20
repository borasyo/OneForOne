//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameOver.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____GameOver_H_____
#define _____GameOver_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/Task/SceneManager.h"

class GameOver : public GameObject {

private:
	CObject2D m_Fade;
	CObject2D m_Rogo;
	float fAlpha;
	bool m_bFadeFlg;
	int m_nFadeCnt;
	SceneManager* m_pSceneManager;

	D3DXVECTOR3 m_FadeScale;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	CDirectInputManager* m_pDirectInputManager;

public:

	GameOver();
	~GameOver();

	bool Start();
	void Update();
	void LateDraw();
	bool* GetBool();
	
	GameOver* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		GameOver* Child = static_cast<GameOver*>(Obj); 
		return Child;
	}
};

#endif