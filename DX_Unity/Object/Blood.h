//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Blood.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Blood_H_____
#define _____Blood_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"

class Blood : public GameObject {

private:
	GameObject* m_pMyself;	 // 血を出すオブジェクト
	GameObject* m_pOpponent; //	血を出させるオブジェクト
	D3DXVECTOR3 m_Move;		 // 移動量 
	bool m_bGrounded;

public:
	// ObjectType
	CObject3DModel m_Object3D;

	Blood() 
			:m_pMyself(nullptr)
			,m_pOpponent(nullptr)
			,m_bGrounded(false)
			,m_Move(D3DXVECTOR3(0,0,0)) 
	{
		m_Name = "Blood";
		m_Object3D.SetFileName(_T("Blood.x"));
	}
	~Blood(){}

	bool Start(D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos);
	void Update();
	void Draw();
	
	Blood* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // 失敗!!!
			return nullptr;

		Blood* Child = static_cast<Blood*>(Obj); 
		return Child;
	}
};

#endif