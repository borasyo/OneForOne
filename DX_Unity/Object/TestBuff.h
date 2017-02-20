//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [TestBuff.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TEST_BUFF_H_____
#define _____TEST_BUFF_H_____

#include <iostream>
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Polygon.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/DirectX/Direct3D.h"

#include <time.h>
#include "../Library/Task/Hierarchy.h"

class TestBuff : public GameObject {

private:
	CDirectInputManager* m_pDirectInputManager;
	int m_nPattern;

public:
	// ObjectType
	CObject3DPolygon m_Object3D;

	TestBuff(){
		m_Name = "TestBuff";
		m_Object3D.SetFileName(_T("TestAnim.png"));
		m_Object3D.SetDivide(8);
		m_Object3D.SetBillFlg();
	}
	~TestBuff(){}
	
	bool Start(){
	#if _DEBUG
		std::cout << m_Name + "!" << std::endl;
	#endif
		m_pDirectInputManager = CDirectInputManager::Instance();
		m_Position = D3DXVECTOR3(0,0.1f,0);
		m_Scale = D3DXVECTOR3(3,3,3);
		m_nPattern = 0;
		m_Object3D.SetVertexTexture(m_nPattern);

		return true;
	}
	
	void Update(){
	#if _DEBUG
		std::cout << m_Name + "." << std::endl;
	#endif
		/*
		if( m_pDirectInputManager->GetKeyboardHold(DIK_Q))
			Rotation(D3DXVECTOR3(0.1f,0,0) );
		if( m_pDirectInputManager->GetKeyboardHold(DIK_W))
			Move(D3DXVECTOR3(0,0,0.1f) );
		else if( m_pDirectInputManager->GetKeyboardHold(DIK_A))
			Move(D3DXVECTOR3(-0.1f,0,0) );
		else if( m_pDirectInputManager->GetKeyboardHold(DIK_S))
			Move(D3DXVECTOR3(0,0,-0.1f) );
		else if( m_pDirectInputManager->GetKeyboardHold(DIK_D))
			Move(D3DXVECTOR3(0.1f,0,0) );
		*/
		if(rand()%5 == 0){	
			m_nPattern ++;
			m_Object3D.SetVertexTexture(m_nPattern);
		}

		// 例外チェック実施
		ExceptionCheck();
	}
	
	void Draw(){

		m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
			
	#if _DEBUG
		std::cout << m_Name + "-" << std::endl;
	#endif
	}
	
	TestBuff* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // 失敗!!!
			return nullptr;

		TestBuff* Child = static_cast<TestBuff*>(Obj); 
		return Child;
	}
};

#endif