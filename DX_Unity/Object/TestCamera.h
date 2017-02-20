//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [testcamera.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TEST_CAMERA_H_____
#define _____TEST_CAMERA_H_____

#include <iostream>
#include <typeinfo.h>
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/ObjectCamera.h"
#include "../Library/DirectX/Direct3D.h"
#include "../Library/DirectX/DirectInputManager.h"

class TestCamera : public GameObject {

private:
	// ObjectType
	CObjectCamera m_ObjectCamera;

	CDirectInputManager* m_pDirectInputManager;

public:

	TestCamera(){
		m_Name = "TestCamera";
	}
	~TestCamera(){
	}
	
	bool Start(){
	#if _DEBUG
		std::cout << m_Name + "!" << std::endl;
	#endif
		m_pDirectInputManager = CDirectInputManager::Instance();
		m_Position = D3DXVECTOR3(5.f,5.f,5.f); 
		SetLocal();
		return true;
	}
	
	void Update(){
		if( !m_bActive ) return;

		if( m_Parent )
			*(m_ObjectCamera.GetLookatPt()) = *(m_Parent->GetPosition());
		
		if( m_pDirectInputManager->GetKeyboardHold(DIK_Z))
			Move(D3DXVECTOR3(0,0,0.2f) );
		else if( m_pDirectInputManager->GetKeyboardHold(DIK_X))
			Move(D3DXVECTOR3(-0.2f,0,0) );
		else if( m_pDirectInputManager->GetKeyboardHold(DIK_C))
			Move(D3DXVECTOR3(0,0,-0.2f) );
		else if( m_pDirectInputManager->GetKeyboardHold(DIK_V))
			Move(D3DXVECTOR3(0.2f,0,0) );
		else if( m_pDirectInputManager->GetKeyboardHold(DIK_B))
			Move(D3DXVECTOR3(0,-0.2f,0) );
		else if( m_pDirectInputManager->GetKeyboardHold(DIK_N))
			Move(D3DXVECTOR3(0,0.2f,0) );

	#if _DEBUG
		std::cout << m_Name + "." << std::endl;
	#endif
	}
	
	void FastDraw(){
		if( !m_bActive ) return;
		
		//m_ObjectCamera.Set(GetLocal());
		m_ObjectCamera.Set(m_Position);

	#if _DEBUG
		std::cout << m_Name + "-" << std::endl;
	#endif
	}

	void Test(){
	#if _DEBUG
		std::cout << typeid(*this).name() << std::endl;
	#endif
	}
	
	TestCamera* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		TestCamera* Child = static_cast<TestCamera*>(Obj); 
		return Child;
	}
};

#endif