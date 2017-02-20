//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [WizardWeapon.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "WizardWeapon.h"

void WizardWeapon::Awake(){

	ReInit();
	
	if( m_Parent )
		m_Position = *(m_Parent->GetPosition());
}

void WizardWeapon::Update(){
	// “Á‚É‚È‚µ
}

void WizardWeapon::Draw(){
	// •`‰æ
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}