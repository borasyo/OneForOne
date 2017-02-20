//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Wizard.cpp]
// author : �哴�ˑ�d
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Wizard.h"
#include "Shadow.h"
#include "ShadowBall.h"
#include "WizardImpactParent.h"
#include "../Library/Task/Empty.h"
#include "BeamHolder.h"
#include "../Library/DirectX/DirectSound.h"

// --- �萔
const int nFarInterval = 41;
const int nNearInterval = 52;
const int nAssaultInterval = 48;
const float fCollision = 0.5f; 
const int nNearAtackTime = 60;
const int nTeleportationTime = 1200;
const float fChaseSpeed = 45.0f;
const float fInitPos = 31.8f;
const float fAssaultRot = 0.6f;

const float fBorder = 25.0f; // Near��Far�̋��E

const int nBeamLife = 180;
const int nBeamLength = 30;
const int nBeamInterval = 60;
const D3DXVECTOR3 BeamPos = D3DXVECTOR3(0,0,0);
const D3DXVECTOR3 BeamScale = D3DXVECTOR3(1,1,1);

// --- �}�N��
#define TELEPORT_X (rand()%(450+50)*0.1f)
#define TELEPORT_Z (rand()%(450+50)*0.1f)
#define RANDOM (rand()%1000*0.001f)

Wizard::Wizard()//:m_nAtackCnt(1)
				//,m_nTeleportationCnt(0)
				//,m_fAtackRot(0)
				//,m_bStart(false) {
{
	m_Name = "Wizard";
	m_Object3D.SetFileName(_T("Wizard.x"));
	m_Tag = "Boss";
	
	// Task�擾
	m_pHierarchy = Hierarchy::Create();
	
	m_pImpactParent = m_pHierarchy->CreateObject(new WizardImpactParent);
	m_pImpactParent->BanDestroy();
	for( int i = 0; i < 50; i++ )
		m_pImpactParent->CreateChild();
	for( auto Ite = m_pImpactParent->GetChild()->begin(); Ite != m_pImpactParent->GetChild()->end(); Ite++ )
		(*Ite)->SetActive(false);
		
	m_pWizardCollision = m_pHierarchy->CreateObject(new Empty("WizardCollision"));
	m_pWizardCollision->BanDestroy();
	
	// �e�쐬
	GameObject* pObj = m_pHierarchy->CreateObject(new Shadow);
	pObj->SetParent(this);
	pObj->Start();
	*(pObj->GetScale()) *= 2.0f;
	
	WizardFogParent FogParent;
	m_pFogParent = FogParent.GetDownCastClass(m_pHierarchy->FindWithName("WizardFogParent"));
	
	// BulletFog�擾
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
}

Wizard::~Wizard(){

}

void Wizard::Awake() {

	ReInit();
	m_nAtackCnt = 1;
	m_nTeleportationCnt = 0;
	m_fAtackRot = 0;
	m_bStart = false;

	if( FindChild("WizardWeapon") )
		*(FindChild("WizardWeapon")->GetPosition()) = m_Position;

	// �����ʒu
	Move( D3DXVECTOR3(0,fInitPos,0) );
	Rotation( D3DXVECTOR3(0,Pai,0) );

	// �K�v�����擾�A����
	m_pPlayer = m_pHierarchy->FindWithName("Player");

	// ���C�t�ݒ�
	m_nLife = 5000; // 5000	

	// �R���W�����ݒ�
	SetCollisionCubeSize(D3DXVECTOR3(fCollision,1.5f,fCollision), D3DXVECTOR3(fCollision,1.5f,fCollision));
	
	// �X�P�[���ύX
	ScaleChange(D3DXVECTOR3(0.5f,0.5f,0.5f));

	// �t���OOFF
	m_bBeam = false;
	m_bAssault = false;
}

void Wizard::Update(){

	if( !m_bStart && m_Position.y <= fInitPos-30.0f )
		m_bStart = true;
	
	// �܂��퓬�J�n����Ȃ�
	if( !m_bStart ) {

		Move( D3DXVECTOR3(0,-0.5f,0) );

		return;
	}

	// ���̃��C�t������Əu�Ԉړ�
	if( m_nLife % 88 == 0 && m_fAtackRot == 0 && !m_bAssault ) {
		m_nTeleportationCnt = nTeleportationTime-1;
		m_nLife -= 4;
	}

	float fDistanceX = m_pPlayer->GetPosition()->x - m_Position.x;
	float fDistanceY = m_pPlayer->GetPosition()->y - m_Position.y;
	float fDistanceZ = m_pPlayer->GetPosition()->z - m_Position.z;
	
	// �v���C���[�Ƃ̋����͋ߋ���
	if( sqrt( fDistanceX*fDistanceX + fDistanceZ*fDistanceZ ) <= fBorder ) {

		m_bNear = true;
		
		// �U�����Ă��Ȃ����͏����Â߂Â�
		if( m_fAtackRot == 0 && !m_bAssault && m_pPlayer->GetCollisionFlg() )
			Move( D3DXVECTOR3( fDistanceX/fChaseSpeed, 0, fDistanceZ/fChaseSpeed ) );
	}
	// ������
	else 
		m_bNear = false;

	// �U�����s�����`�F�b�N
	CheckAtack();

	// �J�E���g����
	m_nAtackCnt++;
	if( !m_bBeam )
		m_nTeleportationCnt++;

	// �v���C���[�̂ق�����������
	if( !m_bAssault )
		Rotation(D3DXVECTOR3(0,(atan2f(fDistanceX,fDistanceZ)-m_Rotation.y),0));

	// Knife�U�����s��
	if( m_fAtackRot != 0 ) 
		KnifeAtack();

	// Assault�U�����s��
	if( m_bAssault )
		AssaultAtack();

	// �r�[���ړ�(�ł������̌����ɒ��i)
	if( m_bBeam ) {
		m_pBeamHolder->Move(m_Move);

		// �ړ��X�s�[�h�A�b�v
		/*if( m_nAtackCnt%nBeamLength == 0 )
			m_Move *= 3.0f;*/

		// �r�[���I��
		if( m_nAtackCnt%(nBeamLife+nBeamLength+1) == 0 ) {
			m_bBeam = false;
			m_nAtackCnt = 1;
		}
	}

	// �u�Ԉړ����邩
	Teleportation();

	// ��O�`�F�b�N
	ExceptionCheck();

#if _DEBUG
	std::cout << "HP : " << m_nLife << std::endl;
#endif

}

void Wizard::FastDraw(){
	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}

// �U�����s�����`�F�b�N
void Wizard::CheckAtack(){
	
	// Knife
	if( m_bNear && m_fAtackRot == 0 && !m_bAssault && m_nAtackCnt%nNearInterval == 0 && !m_bBeam && rand()%2 ) {
		m_fAtackRot = Pai*2.0f/(nNearAtackTime-1)*4.0f;
		m_nAtackCnt = 1; // �J�E���g������
	}

	// Assault
	else if( m_bNear && m_fAtackRot == 0 && !m_bAssault && m_nAtackCnt%nAssaultInterval == 0 && !m_bBeam && rand()%2 ) {
		m_bAssault = true;
		m_nAtackCnt = 1;
	}

	// ShadowBall
	if( !m_bNear && m_fAtackRot == 0 && m_nAtackCnt%nFarInterval == 0 && !m_bBeam && rand()%2 ) {
			
		// �U���I�u�W�F�N�g���쐬
		GameObject* pObj = m_pHierarchy->CreateObject(new ShadowBall);
		pObj->SetParent(m_pWizardCollision);
		*(pObj->GetRotation()) = m_Rotation; 
		*(pObj->GetPosition()) = m_Position + D3DXVECTOR3(1*sinf(m_Rotation.y), 1.0f, 1*cosf(m_Rotation.y)); 
		pObj->Start(); 
		m_nAtackCnt = 1; // �J�E���g������
		PlaySound(WIZARDBULLET);
	}
	
	// Beam
	else if( !m_bNear && m_nAtackCnt%nBeamInterval == 0 && !m_bBeam && rand()%2 ) {
		m_pBeamHolder = m_pHierarchy->CreateObject(new BeamHolder( D3DXCOLOR(1.0f,0.5f,0.2f,1.0f), nBeamLength, nBeamLife, BeamPos, BeamScale, true, true ));
		m_pBeamHolder->Start();
		*(m_pBeamHolder->GetPosition()) = m_Position;
		*(m_pBeamHolder->GetRotation()) = m_Rotation;
		m_bBeam = true;
		m_Move = D3DXVECTOR3(0.8f*sinf(m_Rotation.y), 0, 0.8f*cosf(m_Rotation.y)); 
		m_nAtackCnt = 1; // �J�E���g������
		PlaySound(WIZARDBEAM);
	}
}

// �u�Ԉړ�
void Wizard::Teleportation() {

	// �e���|�[�g�\����
	if( m_nTeleportationCnt%nTeleportationTime == 0 && m_fAtackRot == 0 && !m_bAssault ) {
		// �u�Ԉړ����܂�
		D3DXVECTOR3 move = D3DXVECTOR3(0,0,0);
		
		for( int i = 0; i < 180; i++) {
			// Fog�쐬
			GameObject* pFog = m_pFogParent->CreateChild();
			pFog->ReInit();
			*(pFog->GetPosition()) = m_Position+Random();
			*(pFog->GetRotation()) = m_Rotation;
			pFog->Start();
		}

		// �ړ����W����
		if( rand()%2 )
			move.x = TELEPORT_X;
		else
			move.x = -TELEPORT_X;

		if( rand()%2 )
			move.z = TELEPORT_Z;
		else
			move.z = -TELEPORT_Z;

		// �ړ����s�A�U���J�E���g������(�ړ����Ă����Ȃ�̍U����h������)
		Move( D3DXVECTOR3( -m_Position.x, 0, -m_Position.z ) ); // 0�ɖ߂���
		Move( D3DXVECTOR3( move.x, 0, move.z ) );
		m_nAtackCnt = 1;
		
		PlaySound(WIZARDTELEPORT);
	}

	// �U�����I��莟��A��]����悤�ɂ���
	if( m_nTeleportationCnt%nTeleportationTime == 0 && m_fAtackRot != 0 ) 
		m_nTeleportationCnt --;
}

// Knife�U��
void Wizard::KnifeAtack(){
	
	GameObject* pWeapon = FindChild("WizardWeapon");
	pWeapon->Rotation(D3DXVECTOR3(0,m_fAtackRot,0));
	
	// �U���J�n����15F�ڂœ����蔻�������
	if( m_nAtackCnt == 30 ) {
		
		// �����蔻����쐬
		GameObject* pObj = m_pHierarchy->CreateObject(new Empty("WizardKnife"));
		pObj->SetParent(m_pWizardCollision);
		pObj->SetLife(nNearAtackTime-m_nAtackCnt-5);
		pObj->SetCollisionCubeSize( D3DXVECTOR3(3.0f,5.0f,3.0f), D3DXVECTOR3(3.0f,5.0f,3.0f) );
		*(pObj->GetPosition()) = m_Position;
		PlaySound(WIZARDNEAR);
	}
	
	GameObject* pCol = m_pWizardCollision->FindChild("WizardKnife");
	// �����蔻�肪��������Ă���Ȃ�
	if( pCol ) {
		
		m_Move = D3DXVECTOR3(0.8f*sinf(m_Rotation.y), 0, 0.8f*cosf(m_Rotation.y)); 

		// �������
		pCol->SetLife(-1);
		
		// --- �Ռ��g�쐬
		for( int i = 0; i < 2; i++ ) {
			GameObject* pObj = m_pImpactParent->CreateChild();
			pObj->ReInit();
			*(pObj->GetRotation()) = *(pWeapon->GetRotation());
			*(pObj->GetPosition()) = *(pWeapon->GetPosition())+D3DXVECTOR3(0.4f,0.3f,0.4f);
			pObj->Start();
		}
	}

	// �I��
	if( m_nAtackCnt%nNearAtackTime == 0 ) {
		m_fAtackRot = 0;
		m_nAtackCnt = 1;
	}
}

// Assault�U��
void Wizard::AssaultAtack(){
	
	GameObject* pWeapon = FindChild("WizardWeapon");

	// �U���J�n����40F�ڂœ����蔻�������
	if( m_nAtackCnt <= 40 ) {
		
		Rotation( D3DXVECTOR3(fAssaultRot/40,0,0) );

		// �����蔻����쐬
		if( m_nAtackCnt < 40 )
			return;

		GameObject* pObj = m_pHierarchy->CreateObject(new Empty("WizardAssault"));
		pObj->SetParent(m_pWizardCollision);
		pObj->SetLife(20);
		pObj->SetCollisionCubeSize( GetCollisionCubePlusSize()*1.5f, GetCollisionCubeMinusSize()*1.5f );
		*(pObj->GetPosition()) = m_Position;
		*(pObj->GetRotation()) = m_Rotation;
		
		m_Move = D3DXVECTOR3(0.8f*sinf(m_Rotation.y), 0, 0.8f*cosf(m_Rotation.y)); // �ړ��ʕۑ�
		PlaySound(DRAGONASSAULT);
	}
	
	GameObject* pCol = m_pWizardCollision->FindChild("WizardAssault");
	// �����蔻�肪��������Ă���Ȃ�
	if( pCol ) {

		// �ړ�
		Move(m_Move);

		// �R���W�����ړ�
		pCol->Move(m_Move);

		// �������
		pCol->SetLife(-1);

		// �G�t�F�N�g�쐬
		for( int i = 0; i < 4; i++ )
			*(m_pBulletFogParent->CreateChild(D3DXCOLOR(0.1f,1.0f,0.1f,0.5f))->GetPosition()) = m_Position+Random();
	}

	// �I��
	if( m_nAtackCnt%nNearAtackTime/2 == 0 ) {
		Rotation( D3DXVECTOR3(-m_Rotation.x,0,0) );
		m_bAssault = false;
		m_nAtackCnt = 1;
	}
}

D3DXVECTOR3 Wizard::Random() {
	
	D3DXVECTOR3 Random = D3DXVECTOR3(0,0,0);
	switch( rand()%9 ) {
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

	return Random;
}