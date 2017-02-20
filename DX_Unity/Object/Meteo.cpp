//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Meteo.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Meteo.h"
#include "Shadow.h"
#include "BulletFog.h"
#include "FireExplosion.h"
#include "../Library/DirectX/Direct3D.h"
#include "../Library/DirectX/DirectSound.h"

// --- �}�N��
#define RANGE (rand()%1500*0.01f);
#define RANDOM (rand()%45*0.01f)

// --- �萔
const float fHeight = 30.0f;
const float fFall = fHeight/60.0f;
const int nStopTime = 30;
const float fCollisionSize = 0.35f;

Meteo::Meteo() {
	m_Name = "Meteo";
	m_Object3D.SetFileName(_T("ShadowBall.png"));
	
	// �擾
	m_pHierarchy = Hierarchy::Create();
	
	// BulletFog�擾
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	
	// �e�쐬
	GameObject* pObj = m_pHierarchy->CreateObject(new Shadow(D3DXCOLOR(1.0f,0.0f,1.0f,0.8f),true));
	pObj->SetParent(this);
	//*(pObj->GetPosition()) = m_Position;
	//*(pObj->GetScale()) = m_Scale*1.25f;
	pObj->Start();
	pObj->SetActive(false);
}

Meteo::~Meteo() {
	
}

bool Meteo::Start() {
	
	// �ď�����
	ReInit();

	// �X�P�[������
	ScaleChange( D3DXVECTOR3(10.0f,10.0f,10.0f) - m_Scale );
	
	// �R���W�����ݒ�
	SetCollisionCubeSize( D3DXVECTOR3(fCollisionSize*m_Scale.x,fCollisionSize*m_Scale.y,fCollisionSize*m_Scale.z), 
						  D3DXVECTOR3(fCollisionSize*m_Scale.x,fCollisionSize*m_Scale.y,fCollisionSize*m_Scale.z) );

	// �ꏊ���w��
	m_Position.y = fHeight;

	// ��̓����_���ɎU�炷
	switch(rand()%5){
	case 0:
		m_Position.x += RANGE;
		m_Position.z += RANGE;
		break;
	case 1:
		m_Position.x += RANGE;
		m_Position.z -= RANGE;
		break;
	case 2:
		m_Position.x -= RANGE;
		m_Position.z += RANGE;
		break;
	case 3:
		m_Position.x -= RANGE;
		m_Position.z -= RANGE;
		break;
	case 4:
		// �v���C���[�̐^��ɐ���
		break;
	default:
		break;
	}

	m_bFall = false;
	m_nTime = 0;
	m_Object3D.SetVertexColor( D3DXCOLOR(1,1,1,1) );

	GameObject* pShadow = FindChild("Shadow");
	*(pShadow->GetPosition()) = m_Position;
	*(pShadow->GetScale()) = m_Scale*1.25f;
	pShadow->SetActive(true);

	return true;
}

void Meteo::Update(){

	//if( m_Child.empty() ) {
	//}

	if( !m_bFall ) {
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
		for( int i = 0; i < 6; i++ ) {
			GameObject* pObj = m_pBulletFogParent->CreateChild(D3DXCOLOR(0.5f,0.0f,0.5f,0.5f), 1.5f, 1.25f);
			*(pObj)->GetPosition() = m_Position+Random*(m_Scale.x/2);
			*(pObj)->GetScale() = D3DXVECTOR3(2.5f,2.5f,2.5f);
		}
		
		// �͈͊O����
		if( m_Position.y <= fFall ) {
			m_bFall = true;
			PlaySound(METEO);
			*(m_pHierarchy->FindWithName("CameraSelect")->GetVec()) = D3DXVECTOR3(30,1.2f,0);
		}
	}

	else {

		m_nTime ++;
		m_Object3D.SetVertexColor( D3DXCOLOR(1,1,1, 1.0f - ((float)m_nTime/(float)nStopTime) ) );

		if( m_nTime >= nStopTime ) {
			m_nLife = 0;
		}
	}
}

void Meteo::Draw(){
	// Z��r�Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Z�o�b�t�@�X�V�𖳌���
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z��r����
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z�o�b�t�@�X�V��L����
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
}

void Meteo::FreeFunction() {

	m_Scale *= 1.5f;
	m_CollisionCubePlus *= 1.5f;
	m_CollisionCubeMinus *= 1.5f;
	*(FindChild("Shadow")->GetScale()) *= 1.5f;
}