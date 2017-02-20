//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Deathblow.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Deathblow.h"
#include "../Library/Task/Empty.h"
#include "Player.h"
#include "Shadow.h"
#include "../Library/DirectX/DirectSound.h"

// -- �萔
const int nShotTime = 300;
const float fMaxScale = 15.0f;
const float fMaxMove = 20.0f;

// --- �}�N��
#define RANDOM (rand()%25*0.01f)

Deathblow::Deathblow(){
	m_Name = "Deathblow";
	m_Object3D.SetFileName( _T("Shadow.jpg") );

	// BulletFog�擾
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
}

Deathblow::~Deathblow(){
}

bool Deathblow::Start(){

	m_Scale = D3DXVECTOR3(0,0,0);
	m_nShotCnt = 0;
	m_bShot = false;
	SetCollisionCircleSize(0.75f);
	m_bCollision = false;
	m_pHierarchy = Hierarchy::Create();
	m_pDirectInputManager = CDirectInputManager::Instance();
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_Object3D.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) );
	m_pTarget = nullptr;
	
	// �e�쐬
	GameObject* pObj = m_pHierarchy->CreateObject(new Shadow);
	pObj->SetParent(this);
	*(pObj->GetPosition()) = m_Position;
	pObj->Start();

	PlaySound(DEATHBLOWCHARGE);

	return true;
}

void Deathblow::Update(){

	if( !m_bShot ) {
		
		m_pPlayer = m_pHierarchy->FindWithName("Player"); // Player�T��
		
		// �X�V
		Count();

		// ����
		/*if( m_pDirectInputManager->GetMouseTrigger(0) ){
			for( int i = 0; i < 3; i++ ) { 
				Count();
			}
		}*/

		// ���ߏI�������
		if( m_nShotCnt >= nShotTime ) {
			m_bShot = true; // �����܂�
			m_bCollision = true;
			StopSound(DEATHBLOWCHARGE);
			PlaySound(DEATHBLOWSHOT);
	
			// �G��T��
			m_pTarget = m_pHierarchy->FindWithTag("Boss");
			D3DXVECTOR3 TargetPos;

			// �Ώۂ�����΂�����^�[�Q�b�g�Ɏw��
			if( m_pTarget )
				TargetPos = *(m_pTarget->GetPosition());
			else
				TargetPos = D3DXVECTOR3(0,0,0);

			float fDistanceX = TargetPos.x - m_Position.x;
			float fDistanceY = TargetPos.y - m_Position.y;
			float fDistanceZ = TargetPos.z - m_Position.z;

			m_Bez0 = m_Position;
			m_Bez2 = TargetPos;
			m_Bez1 = D3DXVECTOR3( m_Bez0.x, m_Bez0.y, m_Bez0.z + sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ ) );
			m_fTempArriveTime = m_fArriveTime = sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ );
			m_fTempArriveTime *= 1.0f;
			m_fArriveTime *= 10.0f;
			m_fTime = 0.0f;

			m_Bez1 = D3DXVECTOR3(cosf(m_pPlayer->GetRotation()->y) * (m_Bez1.x - m_Bez0.x) + sinf(m_pPlayer->GetRotation()->y) * (m_Bez1.z - m_Bez0.z) + m_Bez0.x,
								 m_Bez1.y,
								 sinf(m_pPlayer->GetRotation()->y) * (m_Bez1.x - m_Bez0.x) + cosf(m_pPlayer->GetRotation()->y) * (m_Bez1.z - m_Bez0.z) + m_Bez0.z);
		}
	}

	// �����Ă�̂ŁA�����{�X�ɒǏ]
	else {
		// �G�̈ʒu���X�V
		m_pTarget = m_pHierarchy->FindWithTag("Boss");
		if( m_pTarget )
			m_Bez2 = *(m_pTarget->GetPosition());
		else
			m_Bez2.y = 0.0f;
	
		// �x�W�G�X�V���A�ړ�
		Move( D3DXVECTOR3( (1-m_fTime)*(1-m_fTime)*m_Bez0.x + 2*(1-m_fTime)*m_fTime*m_Bez1.x + m_fTime*m_fTime*m_Bez2.x - m_Position.x,
						   (1-m_fTime)*(1-m_fTime)*m_Bez0.y + 2*(1-m_fTime)*m_fTime*m_Bez1.y + m_fTime*m_fTime*m_Bez2.y - m_Position.y,
						   (1-m_fTime)*(1-m_fTime)*m_Bez0.z + 2*(1-m_fTime)*m_fTime*m_Bez1.z + m_fTime*m_fTime*m_Bez2.z - m_Position.z ) );

		m_fTime += 1.0f/m_fArriveTime; // ���t���[������������

		if(m_fArriveTime > m_fTempArriveTime) {
			m_fArriveTime *= 0.95f;
		}
	}
	
	// �G�t�F�N�g����
	for( int i = 0; i < fMaxScale+5-m_Scale.x; i++ ) {
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
		Random *= 1.5f;
		Random.y += RANDOM;

		GameObject* pObj = m_pBulletFogParent->CreateChild(D3DXCOLOR(1.0f,1.0f,0.01f,1.0f),1.5f,m_Scale.x/10.0f);
		*(pObj->GetPosition()) = m_Position+Random*m_Scale.x;
		*(pObj->GetScale()) = m_Scale/2.5f;
		// ������������
		//if( m_pBulletFogParent->GetChild()->size() > 400 ) i++;
	}
	
	// �͈͊O����
	if( m_Position.y <= 0 || ( m_pTarget && m_Position.y >= m_pTarget->GetPosition()->y + 10.0f ) ) {
		SetLife(-999);
		FreeFunction();
	}
}

void Deathblow::Draw(){
	
	// ���Z����
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
	
	// Z��r�Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Z�o�b�t�@�X�V�𖳌���
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z��r����
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z�o�b�t�@�X�V��L����
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	
	// �ʏ�u�����h
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}

bool* Deathblow::GetBool() {

	return &m_bShot;
}

void Deathblow::Count(){
	
	// �J�E���g����
	m_nShotCnt ++;

	// �傫������
	ScaleChange( D3DXVECTOR3( fMaxScale/nShotTime, fMaxScale/nShotTime, fMaxScale/nShotTime ) );

	// �ړ�
	Move( D3DXVECTOR3( 0, fMaxMove/nShotTime, 0 ) );

	*(m_pPlayer->GetFloat()) -= fMaxDeathblowGauge/nShotTime;
}

void Deathblow::FreeFunction() {
	
	// �K�E�Z�I��
	if( m_pPlayer )
		*(m_pPlayer->GetBool()) = false;
	CreateEffect();
}

void Deathblow::CreateEffect(){

	// �G�t�F�N�g����
	for( int i = 0; i < 200; i++ ) {
		
		D3DXVECTOR3 Random = D3DXVECTOR3(0,0,0);
		switch( rand()%8 ) {
		case 0:
			Random.x += RANDOM; 
			Random.y += RANDOM; 
			Random.z += RANDOM; 
			break;
		case 1:
			Random.x -= RANDOM; 
			Random.y += RANDOM; 
			Random.z -= RANDOM; 
			break;
		case 2:
			Random.x -= RANDOM; 
			Random.y -= RANDOM; 
			Random.z += RANDOM; 
			break;
		case 3:
			Random.x += RANDOM; 
			Random.y -= RANDOM; 
			Random.z -= RANDOM; 
			break;
		case 4:
			Random.x -= RANDOM; 
			Random.y += RANDOM; 
			Random.z += RANDOM; 
			break;
		case 5:
			Random.x += RANDOM; 
			Random.y -= RANDOM; 
			Random.z += RANDOM; 
			break;
		case 6:
			Random.x += RANDOM; 
			Random.y += RANDOM; 
			Random.z -= RANDOM; 
			break;
		case 7:
			Random.x -= RANDOM; 
			Random.y -= RANDOM; 
			Random.z -= RANDOM; 
			break;
		default:
			break;
		}
		Random.y *= 3.0f;
		GameObject* pObj = m_pBulletFogParent->CreateChild(D3DXCOLOR(1.0f,1.0f,0.01f,1.0f),4.0f,1.0f);
		*(pObj->GetPosition()) = m_Position+Random*10.0f;
		*(pObj->GetScale()) = D3DXVECTOR3(5,5,5);
	}
}