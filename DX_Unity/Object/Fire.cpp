//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Fire.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Fire.h"
#include "BulletFog.h"
#include "Shadow.h"

// --- �萔
const float fMoveSpeed = 2.0f;
const int nArriveTime = 90;

// --- �}�N�� 
#define RANDOM (rand()%300*0.01f)

Fire::Fire() {
	m_Name = "Fire";
	m_Object3D.SetFileName( _T("DragonFire.png") );

	m_pHierarchy = Hierarchy::Create();

	// BulletFog�擾
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
}

Fire::~Fire() {
	
}

bool Fire::Start(){
	
	// m_Move = D3DXVECTOR3( sinf(m_Rotation.y) * fMoveSpeed, 0, cosf(m_Rotation.y) * fMoveSpeed );

	GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
	D3DXVECTOR3 Distance = *(pPlayer->GetPosition()) - m_Position;
	m_Move = Distance/nArriveTime;
	
	// �R���W�����ݒ�
	SetCollisionCubeSize(D3DXVECTOR3(0.15f,0.15f,0.15f), D3DXVECTOR3(0.15f,0.15f,0.15f));

	// �X�P�[������
	m_Scale = D3DXVECTOR3(1.5f,1.5f,1.5f);

	// ���C�t�ݒ�
	m_nLife = nArriveTime*2;

	return true;
}

void Fire::Update(){
	
	if( m_Child.empty() ) {
		// �e�쐬
		GameObject* pObj = m_pHierarchy->CreateObject(new Shadow( D3DXCOLOR(0.8f,0.1f,0.1f,1.0f), true ) );
		pObj->SetParent(this);
		*(pObj->GetPosition()) = m_Position;
		pObj->Start();
		*(pObj->GetScale()) = D3DXVECTOR3(2,2,2);
	}
	
	// �ړ�
	Move(m_Move);
	
	// �G�t�F�N�g�쐬
	*(m_pBulletFogParent->CreateChild(D3DXCOLOR(0.8f,0.1f,0.1f,0.75f))->GetPosition()) = m_Position;

	// ���C�t���炷
	SetLife(-1);

	// �͈͊O����
	if( m_Position.y <= 0 ) 
		m_nLife = 0;
}

void Fire::Draw(){
	// Z��r�Ȃ�
	//m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Z�o�b�t�@�X�V�𖳌���
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z��r����
	//m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z�o�b�t�@�X�V��L����
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
}