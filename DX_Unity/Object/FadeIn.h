//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FadeIn.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FADEIN_H_____
#define _____FADEIN_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class FadeIn : public GameObject {

private:
	float m_fAlpha;
	float m_fTime;
	D3DXCOLOR FadeColor;

public:
	// ObjectType
	CObject2D m_Object2D;

	FadeIn( float fTime, D3DXCOLOR col );
	~FadeIn();

	void Update();
	void LateDraw();
	
	FadeIn* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		FadeIn* Child = static_cast<FadeIn*>(Obj); 
		return Child;
	}
};

#endif