//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FieldFlower.cpp]
// author : ëÂì¥èÀëæ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FieldFlower.h"

// --- É}ÉNÉç
#define FLOWER_POS ( rand()%36000 * 0.01f )

// --- íËêî
const float fMaxPos = 180.0f;

FieldFlower::FieldFlower() {
	m_Name = "FieldFlower";

	for( int i = 0; i < nSize; i++ ) {

		if( rand()%2 ) {
			m_Object3D[i].SetFileName( _T("FlowerHyacinth.x") );
			m_FlowerScale[i] = D3DXVECTOR3(2,2,2);
			m_FlowerPos[i].y = -0.5f;
		}
		else {
			m_Object3D[i].SetFileName( _T("FlowerLotus.x") );
			m_FlowerScale[i] = D3DXVECTOR3(1,1,1);
			m_FlowerPos[i].y = 0.0f;
		}
	}
}

FieldFlower::~FieldFlower() {
	
}

bool FieldFlower::Start(){
	 
	for( int i = 0; i < nSize; i++ ) {
		m_FlowerPos[i].x = FLOWER_POS - fMaxPos;
		m_FlowerPos[i].z = FLOWER_POS - fMaxPos;
	}

	return true;
}

void FieldFlower::Update(){

	// Ç»Çµ
}

void FieldFlower::Draw(){
	// ï`âÊ
	for( int i = 0; i < nSize; i++ ) {
		m_Object3D[i].Draw( m_FlowerPos[i], m_FlowerScale[i], m_Rotation );
	}
}