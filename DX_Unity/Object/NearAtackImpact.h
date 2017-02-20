//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [NearAtackImpact.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____NEARATACKIMPACT_H_____
#define _____NEARATACKIMPACT_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"

class NearAtackImpact : public GameObject {

private:
	D3DXVECTOR3 m_Move;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	NearAtackImpact(){
		m_Name = "NearAtackImpact";
		m_Object3D.SetFileName(_T("Shadow.jpg"));
		// �f�o�C�X�擾
		m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	}
	~NearAtackImpact(){}

	bool Start();
	void Update();
	void Draw();
	
	NearAtackImpact* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // ���s!!!
			return nullptr;

		NearAtackImpact* Child = static_cast<NearAtackImpact*>(Obj); 
		return Child;
	}
};

#endif