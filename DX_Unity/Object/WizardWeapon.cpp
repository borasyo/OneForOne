//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [WizardWeapon.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "WizardWeapon.h"

void WizardWeapon::Awake(){

	ReInit();
	
	if( m_Parent )
		m_Position = *(m_Parent->GetPosition());
}

void WizardWeapon::Update(){
	// ���ɂȂ�
}

void WizardWeapon::Draw(){
	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}