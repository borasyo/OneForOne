//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Test2D.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TEST_2D_H_____
#define _____TEST_2D_H_____

#include <iostream>
#include <tchar.h>
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class Test2D : public GameObject {

private:
	float m_fAlpha;

public:
	// ObjectType
	CObject2D m_Object2D;

	Test2D(){
		m_Name = "Test2D";
		m_Object2D.SetFileName(_T("player.png"));
	}
	~Test2D(){}

	bool Start(){
		m_Position = D3DXVECTOR3(100.f,100.f,100.f);
		m_Scale    = D3DXVECTOR3(100.f,100.f,100.f);
		m_fAlpha = 1.0f;
		return true;
	}
	
	void Update(){
		m_Object2D.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,m_fAlpha) );
		m_fAlpha -= 0.001f;
	}

	void Draw(){

		m_Object2D.Draw( m_Position, m_Scale );
	}

	Test2D* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		Test2D* Child = static_cast<Test2D*>(Obj); 
		return Child;
	}
};

#endif