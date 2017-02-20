//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ExitBotton.cpp]
// author : ëÂì¥èÀëæ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "ExitBotton.h"

ExitBotton::ExitBotton() {
	m_Name = "ExitBotton";
	m_Object2D.SetFileName( _T("Exit.png") );
}

ExitBotton::~ExitBotton() {
	
}

bool ExitBotton::Start(){
	
	m_Scale = D3DXVECTOR3(192,102,5) * 0.7f; // 192 102
	m_Position = D3DXVECTOR3(500,700,0) * 0.7f; // 
	SetCollisionCubeSize( m_Scale/2.0f, m_Scale/2.0f );

	m_bOnMouth = false; 

	return true;
}

void ExitBotton::Update(){

	if( m_bOnMouth ) 
		m_Object2D.SetFileName( _T("OnExit.png") );
	else
		m_Object2D.SetFileName( _T("Exit.png") );
}

void ExitBotton::Draw(){
	// ï`âÊ
	m_Object2D.Draw( m_Position, m_Scale );

}

bool* ExitBotton::GetBool(){
	return &m_bOnMouth;
}