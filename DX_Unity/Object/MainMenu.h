//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainMenu.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MainMenu_H_____
#define _____MainMenu_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"
#include "../Library/DirectX/MouthPosition.h"

class MainMenu : public GameObject {

private:
	D3DXCOLOR m_Color;
	int m_nPattern;
	int m_nChangeCnt;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	CMouthPosition* m_pMouth;

public:
	// ObjectType
	CObject2D m_Object2D;

	MainMenu();
	~MainMenu();

	void Update();
	void Draw();
	void LateDraw();
	D3DXCOLOR* GetColor();
	
	MainMenu* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // ¸”s!!!
			return nullptr;

		MainMenu* Child = static_cast<MainMenu*>(Obj); 
		return Child;
	}
};

#endif