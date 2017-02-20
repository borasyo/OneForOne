//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [HardBotton.cpp]
// author : ëÂì¥èÀëæ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "HardBotton.h"

HardBotton::HardBotton() {
	m_Name = "HardBotton";
	m_Object2D.SetFileName( _T("Hard.png") );
}

HardBotton::~HardBotton() {
	
}

bool HardBotton::Start(){

	m_Scale = D3DXVECTOR3(248,102,1) * 0.7f; // 248 102
	m_Position = D3DXVECTOR3(1200,500,1) * 0.7f; // 
	SetCollisionCubeSize( m_Scale/2.0f, m_Scale/2.0f );

	m_bOnMouth = false;

	return true;
}

void HardBotton::Update(){
	
	if( m_bOnMouth ) 
		m_Object2D.SetFileName( _T("OnHard.png") );
	else
		m_Object2D.SetFileName( _T("Hard.png") );
}

void HardBotton::Draw(){
	// ï`âÊ
	m_Object2D.Draw( m_Position, m_Scale );

}

bool* HardBotton::GetBool(){
	return &m_bOnMouth;
}