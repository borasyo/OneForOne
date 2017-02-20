//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [BeamParent.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____BeamParent_H_____
#define _____BeamParent_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "Beam.h"

class BeamParent : public GameObject {

private:
	std::list<Beam*> BeamChild; 

public:
	// ObjectType

	BeamParent();
	~BeamParent();
	
	void Update();
	void Draw();

	GameObject* CreateChild(D3DXCOLOR Color, D3DXVECTOR3 Scale, bool bAdd );
	
	BeamParent* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		BeamParent* Child = static_cast<BeamParent*>(Obj); 
		return Child;
	}
};

#endif