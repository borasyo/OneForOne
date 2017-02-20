//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [HelpBotton.cpp]
// author : ëÂì¥èÀëæ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "HelpBotton.h"

HelpBotton::HelpBotton() {
	m_Name = "HelpBotton";
	m_Object2D.SetFileName( _T("Help.png") );
}

HelpBotton::~HelpBotton() {
	
}

bool HelpBotton::Start(){
	
	m_Scale = D3DXVECTOR3(231,127,5) * 0.7f; // 192 102
	m_Position = D3DXVECTOR3(1000,715,0) * 0.7f; // 
	SetCollisionCubeSize( m_Scale/2.0f, m_Scale/2.0f );

	m_bOnMouth = false; 

	return true;
}

void HelpBotton::Update(){

	if( m_bOnMouth ) 
		m_Object2D.SetFileName( _T("OnHelp.png") );
	else
		m_Object2D.SetFileName( _T("Help.png") );
}

void HelpBotton::Draw(){
	// ï`âÊ
	m_Object2D.Draw( m_Position, m_Scale );

}

bool* HelpBotton::GetBool(){
	return &m_bOnMouth;
}