//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FarAtack.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FarAtack.h"
#include "FarAtackFire.h"
#include "../Library/Task/Empty.h"
#include "../Library/DirectX/DirectSound.h"

// -- �萔
const int nLimit = 60/4; // 1�t���[���ɉ������Ă邩�𐧌�����
const float fRotSpeed = 0.02f; 

FarAtack::FarAtack() : m_bAtack(false){
	m_Name = "FarAtack";
	m_Object3D.SetFileName(_T("FarAtack.x"));

	if( !Hierarchy::Create()->FindWithName("FireParent") )
		m_pFireParent = Hierarchy::Create()->CreateObject(new Empty("FireParent"));
}

FarAtack::~FarAtack(){
}

void FarAtack::Awake(){
	
	ReInit();

	if( m_Parent )
		m_Position = *(m_Parent->GetPosition());
	m_bCollision = false;
}

void FarAtack::Update(){

	// �U���Ԋu
	if( m_bAtack ){
		Rotation( D3DXVECTOR3(0,-fRotSpeed,0) );
		m_nCnt ++;
		if( m_nCnt >= nLimit ){
			Rotation( D3DXVECTOR3(0,fRotSpeed*m_nCnt,0) );
			m_bAtack = false;
		}
	}
}

void FarAtack::Draw(){
	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}

void FarAtack::Atack(){

	if( m_bAtack )
		return;

	m_bAtack = true;
	m_nCnt = 0;

	// �U���I�u�W�F�N�g���쐬
	Hierarchy* pHierarchy =  Hierarchy::Create();
	GameObject* pObj = pHierarchy->CreateObject(new FarAtackFire);
	pObj->SetParent(m_pFireParent);
	*(pObj->GetRotation()) = *(m_Parent->GetRotation()); 
	*(pObj->GetPosition()) = *(m_Parent->GetPosition()) + D3DXVECTOR3(1*sinf(pObj->GetRotation()->y-0.5f), 1.0f, 1*cosf(pObj->GetRotation()->y-0.5f)); 
	pObj->Start(); 
	PlaySound(PLAYERFAR);
}