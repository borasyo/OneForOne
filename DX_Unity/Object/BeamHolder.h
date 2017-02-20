//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [BeamHolder.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____BeamHolder_H_____
#define _____BeamHolder_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Debug/FPSController.h"
#include "BeamParent.h"

class BeamHolder : public GameObject {

private:
	// “ü‚ê•¨
	BeamParent* m_pBeamParent;

	// •K—vî•ñ
	D3DXCOLOR m_Color;
	D3DXVECTOR3 m_BeamPos;
	D3DXVECTOR3 m_BeamScale;
	GameObject* m_pTarget;
	int m_nCreateCnt;
	int m_nLength;
	int m_nBeamLife;
	float m_fInterval;
	bool m_bAdd;
	bool m_bDraw;
	FPSController* m_pFPSController;

public:
	BeamHolder(D3DXCOLOR Color, int nLength, int nLife, D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, bool bAdd, bool bCollision );
	~BeamHolder();

	bool Start();
	void Update();
	
	BeamHolder* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		BeamHolder* Child = static_cast<BeamHolder*>(Obj); 
		return Child;
	}
};

#endif