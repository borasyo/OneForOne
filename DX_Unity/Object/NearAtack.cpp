//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [NearAtack.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "NearAtack.h"
#include "NearAtackImpact.h"
#include "../Library/DirectX/DirectSound.h"

const float fAtackTime = 30.0f;

NearAtack::NearAtack() : m_bAtack(false) {
	m_Name = "NearAtack";
	m_Object3D.SetFileName(_T("NearAtack.x"));
	// NearAtack���܂Ƃ߂���ꕨ���쐬
	Hierarchy* pHierarchy = Hierarchy::Create();
	if( !(m_pNearAtackImpactParent = pHierarchy->FindWithName("NearAtackImpactParent")) )
		m_pNearAtackImpactParent =  Hierarchy::Create()->CreateObject(new NearAtackImpactParent);
}

void NearAtack::Awake(){

	ReInit();
	
	if( m_Parent )
		m_Position = *(m_Parent->GetPosition());
	m_Scale = D3DXVECTOR3(0,0,0);
	m_bCollision = false;
	m_bAtack = false;
}

void NearAtack::Update(){

	// --- �U������
	if( m_bAtack ){
		// --- ��]����
		Rotation( D3DXVECTOR3(0,-Pai*2.0f/fAtackTime,0) );

		// --- �Ռ��g�쐬
		D3DXVECTOR3 fRot = D3DXVECTOR3(0,0,0);
		for( int i = 0; i < 5; i++, fRot.y += Pai*2.0f/8.0f ) {
			GameObject* pObj = m_pNearAtackImpactParent->CreateChild();
			pObj->ReInit();
			*(pObj->GetRotation()) = m_Rotation+fRot;
			*(pObj->GetPosition()) = m_Position;
			//*(pObj->GetScale()) = D3DXVECTOR3(0.8f,0.8f,0.8f);
			pObj->Start();
		}

		// --- �U���J�E���g����
		m_nCnt ++;
		if( m_nCnt >= fAtackTime )
			m_bAtack = false;
	}
}

void NearAtack::Draw(){
	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}

void NearAtack::Atack(){\
	
	// ���ɍU�����Ȃ�Ԃ�
	if( m_bAtack ) 
		return;

	m_bAtack = true;
	m_nCnt = 0;
	PlaySound(PLAYERNEAR);
}