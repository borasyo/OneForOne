//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Test3D.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TEST_3D_H_____
#define _____TEST_3D_H_____

#include <iostream>
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"
#include "../Library/DirectX/DirectInputManager.h"

#include <time.h>
#include "../Library/Task/Hierarchy.h"

class Test3D : public GameObject {

private:
	CDirectInputManager* m_pDirectInputManager;

public:
	// ObjectType
	CObject3DModel m_Object3D;

	Test3D(){
		m_Name = "Test3D";
		m_Object3D.SetFileName(_T("catsenkan.x"));
	}
	~Test3D(){}
	
	bool Start(){
	#if _DEBUG
		std::cout << m_Name + "!" << std::endl;
	#endif
		m_pDirectInputManager = CDirectInputManager::Instance();
		if( m_Parent ) {
			m_Position = *(m_Parent->GetPosition()) + D3DXVECTOR3(2,0,2);
			SetLocal();
		}
		return true;
	}
	
	void Update(){
		if( !m_bActive ) return;
	#if _DEBUG
		std::cout << m_Name + "." << std::endl;
	#endif

		// 例外チェック実施
		ExceptionCheck();
	}
	
	void Draw(){
		if( !m_bActive ) return;

		if( !m_Parent )
			m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
		else
			m_Object3D.Draw( m_Position, m_Scale, m_Rotation );

	#if _DEBUG
		std::cout << m_Name + "-" << std::endl;
	#endif
	}
	
	Test3D* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // 失敗!!!
			return nullptr;

		Test3D* Child = static_cast<Test3D*>(Obj); 
		return Child;
	}
};

#endif