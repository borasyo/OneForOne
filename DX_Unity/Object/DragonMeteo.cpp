//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DragonMeteo.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "DragonMeteo.h"
#include "Shadow.h"
#include "BulletFog.h"
#include "FireExplosion.h"
#include "../Library/DirectX/DirectSound.h"

// --- �}�N��
#define RANGE (rand()%1500*0.01f);
#define RANDOM (rand()%10*0.01f)

// --- �萔
const float fHeight = 30.0f;
const float fFall = fHeight/90.0f;

DragonMeteo::DragonMeteo() {
	m_Name = "DragonMeteo";
	m_Object3D.SetFileName(_T("DragonMeteo.png"));
	
	// �擾
	m_pHierarchy = Hierarchy::Create();
	
	// BulletFog�擾
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
}

DragonMeteo::~DragonMeteo() {
	
}

bool DragonMeteo::Start() {
	
	// �ď�����
	ReInit();

	// �R���W�����ݒ�
	SetCollisionCircleSize(1.5f);

	// �X�P�[������
	ScaleChange( D3DXVECTOR3(1.5f,1.5f,1.5f) );

	// �ꏊ���w��
	m_Position.y = fHeight;

	return true;
}

void DragonMeteo::Update(){

	if( m_Child.empty() ) {
		// �e�쐬
		GameObject* pObj = m_pHierarchy->CreateObject(new Shadow(D3DXCOLOR(0.9f,0.0f,0.1f,0.8f),true));
		pObj->SetParent(this);
		*(pObj->GetPosition()) = m_Position;
		pObj->ScaleChange(D3DXVECTOR3(2.5f,2.5f,2.5f));
		pObj->Start();
	}

	// ����
	Move( D3DXVECTOR3(0,-fFall,0) );

	// �G�t�F�N�g�쐬
	D3DXVECTOR3 Random = D3DXVECTOR3(0,0,0);
	switch( rand()%4 ) {
	case 0:
		Random.x += RANDOM; 
		Random.z += RANDOM; 
		break;
	case 1:
		Random.x -= RANDOM; 
		Random.z += RANDOM; 
		break;
	case 2:
		Random.x += RANDOM; 
		Random.z -= RANDOM; 
		break;
	case 3:
		Random.x -= RANDOM; 
		Random.z -= RANDOM; 
		break;
	default:
		break;
	}

	// �G�t�F�N�g�쐬
	for( int i = 0; i < 2; i++ ) {
		*(m_pBulletFogParent->CreateChild(D3DXCOLOR(0.9f,0.0f,0.1f,0.5f))->GetPosition()) = m_Position+Random*m_Scale.x;
	}
	
	// �͈͊O����
	if( m_Position.y <= fFall ) {
		m_nLife = 0;
		PlaySound(METEO);
	}
}

void DragonMeteo::Draw(){
	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}