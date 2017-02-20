//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Field.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Field.h"

// --- ’è”
const float fFieldSize = 16.0f;
const float fChangeSpeed = 1.0f/120.0f;

Field::Field() {
	m_Name = "Field";
	m_Tag = "Field";
	m_Object3D.SetFileName( _T("Field.x") );

	SetCollisionCircleSize( LimitPos.x );
}

Field::~Field() {
	
}

bool Field::Start(){

	m_Scale = D3DXVECTOR3( fFieldSize,fFieldSize,fFieldSize );
	m_Object3D.SetMaterialColor( D3DXCOLOR(1,1,1,1) );
	m_bDark = false;
	m_fColor = 1.0f;

	return true;
}

void Field::Update(){

	if( m_bDark ) {
		if( m_fColor > 0.0f )
			m_fColor -= fChangeSpeed;
	}
	else {
		if( m_fColor < 1.0f )
			m_fColor += fChangeSpeed;
	}
	
	m_Object3D.SetMaterialColor( D3DXCOLOR(m_fColor,m_fColor,m_fColor,1) );
}

void Field::FastDraw(){

	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}

bool* Field::GetBool(){
	return &m_bDark;
}