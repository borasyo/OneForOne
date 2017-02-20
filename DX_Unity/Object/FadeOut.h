//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FadeOut.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FADEOUT_H_____
#define _____FADEOUT_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class FadeOut : public GameObject {

private:
	float m_fAlpha;
	float m_fTime;
	D3DXCOLOR FadeColor;

public:
	// ObjectType
	CObject2D m_Object2D;
	
	FadeOut( float fTime, D3DXCOLOR col );
	~FadeOut();

	void Update();
	void LateDraw();
	
	FadeOut* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		FadeOut* Child = static_cast<FadeOut*>(Obj); 
		return Child;
	}
};

#endif