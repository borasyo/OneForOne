//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SkeltonCorps.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SkeltonCorps.h"
#include "WizardFogParent.h"

// -- ’è”
const float fGravity = 0.0245f;
const D3DXVECTOR3 MoveScale = D3DXVECTOR3(0.0008f,0.0008f,0.0008f);
const int nSkeletonDeathEffect = 10;
const D3DXVECTOR3 InitScale = D3DXVECTOR3(2,2,2);

// -- ƒ}ƒNƒ
#define MOVE_X ((rand()%3500 + 500)*0.01f)
//#define MOVE_Y ((rand()%4000+2000)*0.0001f)
#define MOVE_Z ((rand()%3500 + 500)*0.01f)
#define ROT (rand()%628*0.01f)
#define RANDOM (rand()%100*0.01f)

SkeltonCorps::SkeltonCorps():m_bGrounded(false)
							,m_Move(D3DXVECTOR3(0,0,0)) { 
	m_Name = "SkeltonCorps";
	m_Object3D.SetFileName(_T("Skeleton.x"));
	//m_bGrounded = false;
}

SkeltonCorps::~SkeltonCorps() {
	
}

bool SkeltonCorps::Start(){

	// Ä‰Šú‰»
	ReInit();
	m_Move = D3DXVECTOR3(0,0,0);
	
	switch(rand()%4){
	case 0:
		m_Move.x += MOVE_X;
		m_Move.z += MOVE_Z;
		break;
	case 1:
		m_Move.x -= MOVE_X;
		m_Move.z += MOVE_Z;
		break;
	case 2:
		m_Move.x += MOVE_X;
		m_Move.z -= MOVE_Z;
		break;
	case 3:
		m_Move.x -= MOVE_X;
		m_Move.z -= MOVE_Z;
		break;
	default:
		break;
	}
	m_Position += m_Move;
	m_Position.y = 0.5f*InitScale.x;
	
	SetCollisionCubeSize(D3DXVECTOR3(0.15f,0.25f,0.15f), D3DXVECTOR3(0.15f,0.25f,0.15f));
	ScaleChange( InitScale );
	Rotation(D3DXVECTOR3(0,ROT,0));
	
	// Š[œŒRŽ€–SƒGƒtƒFƒNƒgì¬
	if( m_bGrounded ) {
		WizardFogParent FogParent;
		WizardFogParent* m_FogParent = FogParent.GetDownCastClass(Hierarchy::Create()->FindWithName("WizardFogParent"));
		for( int i = 0; i < nSkeletonDeathEffect*m_Scale.x; i++) {
			GameObject* pFog = m_FogParent->CreateChild();
			pFog->ReInit();
			pFog->Start();
			*(pFog->GetPosition()) = m_Position+RandomPos();
			*(pFog->GetScale()) = D3DXVECTOR3(1,1,1);
		}
	} else {
		SetCollisionFlg(false);
	}
	m_bGrounded = true;

	return true;
}

void SkeltonCorps::Update(){

	/*if( m_Scale.x < 6.0f ) {
		ScaleChange( MoveScale );
		Move( D3DXVECTOR3(0,MoveScale.y/2.5f,0) );
	}*/
}

void SkeltonCorps::FastDraw(){
	// •`‰æ
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}


D3DXVECTOR3 SkeltonCorps::RandomPos(){

	D3DXVECTOR3 pos = D3DXVECTOR3(0,0,0);
	
	if( rand()%2 ) {
		pos.x = -RANDOM;
	} else {
		pos.x = RANDOM;
	}

	if( rand()%2 ) {
		pos.y = -RANDOM;
	} else {
		pos.y = RANDOM;
	}

	if( rand()%2 ) {
		pos.z = -RANDOM;
	} else {
		pos.z = RANDOM;
	}

	return pos;
}