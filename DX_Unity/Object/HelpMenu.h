//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [HelpMenu.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____HelpMenu_H_____
#define _____HelpMenu_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/DirectX/Window.h"

class HelpMenu : public GameObject {

private:
	// ObjectType
	CObject2D m_Object2D;
	CObject2D m_Fade;

	CDirectInputManager* m_pDirectInputManager;
	CWindow* m_pWindow;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	float m_fAlpha;
	D3DXVECTOR3 m_FadeScale;
	bool m_bEnd;

public:

	HelpMenu();
	~HelpMenu();

	bool Start();
	void Update();
	void Draw();
	
	HelpMenu* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		HelpMenu* Child = static_cast<HelpMenu*>(Obj); 
		return Child;
	}
};

#endif