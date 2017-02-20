//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [EasyBotton.cpp]
// author : ëÂì¥èÀëæ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "EasyBotton.h"

EasyBotton::EasyBotton() {
	m_Name = "EasyBotton";
	m_Object2D.SetFileName( _T("Easy.png") );
}

EasyBotton::~EasyBotton() {
	
}

bool EasyBotton::Start(){

	m_Scale = D3DXVECTOR3(224,126,1) * 0.7f; // 192 102
	m_Position = D3DXVECTOR3(300,500,1) * 0.7f; // 
	SetCollisionCubeSize( m_Scale/2.0f, m_Scale/2.0f );
	
	m_bOnMouth = false; 

	return true;
}

void EasyBotton::Update(){
	
	if( m_bOnMouth ) 
		m_Object2D.SetFileName( _T("OnEasy.png") );
	else
		m_Object2D.SetFileName( _T("Easy.png") );

}

void EasyBotton::Draw(){
	// ï`âÊ
	m_Object2D.Draw( m_Position, m_Scale );

}

bool* EasyBotton::GetBool(){
	return &m_bOnMouth;
}