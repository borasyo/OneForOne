//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Pause.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Pause_H_____
#define _____Pause_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"
#include "../Library/DirectX/DirectInputManager.h"

class Pause : public GameObject {

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	float m_fAlpha;
	D3DXVECTOR3 m_FadeScale;
	CDirectInputManager* m_pDirectInputManager;
	std::list<GameObject*> m_ObjectList;
	bool m_bChange;
	bool m_bEnd;

	bool m_bFadeFlg;
	int  m_nFadeCnt;

public:
	// ObjectType
	CObject2D m_Pause;
	CObject2D m_Fade;

	Pause();
	~Pause();

	void Update();
	void Draw();
	
	bool* GetBool() { return &m_bDestroy; }
	
	Pause* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		Pause* Child = static_cast<Pause*>(Obj); 
		return Child;
	}
};

#endif