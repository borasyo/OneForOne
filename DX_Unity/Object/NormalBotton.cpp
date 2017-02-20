//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [NormalBotton.cpp]
// author : ëÂì¥èÀëæ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "NormalBotton.h"

NormalBotton::NormalBotton() {
	m_Name = "NormalBotton";
	m_Object2D.SetFileName( _T("Normal.png") );
}

NormalBotton::~NormalBotton() {
	
}

bool NormalBotton::Start(){

	m_Scale = D3DXVECTOR3(345,102,1) * 0.7f; // 345 102
	m_Position = D3DXVECTOR3(750,500,1) * 0.7f; // 
	SetCollisionCubeSize( m_Scale/2.0f, m_Scale/2.0f );
	
	m_bOnMouth = false; 

	return true;
}

void NormalBotton::Update(){
	
	if( m_bOnMouth ) 
		m_Object2D.SetFileName( _T("OnNormal.png") );
	else
		m_Object2D.SetFileName( _T("Normal.png") );

}

void NormalBotton::Draw(){
	// ï`âÊ
	m_Object2D.Draw( m_Position, m_Scale );

}

bool* NormalBotton::GetBool(){
	return &m_bOnMouth;
}