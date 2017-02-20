//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Dragon.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Dragon.h"
#include "../Library/Task/Empty.h"
#include "Shadow.h"
#include "CleaveImpactParent.h"
#include "Fire.h"
#include "BeamHolder.h"
#include "DragonMeteoParent.h"
#include "../Library/DirectX/DirectSound.h"

// ---- �萔
const int nLife = 2400;

// Assault
const int nAssaultInterval = 398; // �Ԋu
const int nAssaultTime = 180;

// Fire
const int nFireInterval = 249;
const int nFireTime = 90;
const float fMovePos = 5.5f;
const float fReturnTime = 180.0f;
const float fReturnHeight = 130.0f; 

// --- �}�N��
#define RANDOM (rand()%3000*0.001f)
#define RANDOM_POS ( rand()%80000*0.001f + 20.0f ) 
#define RANDOM_HEIGHT ( rand()%4000*0.001 + 70.0f ) 

Dragon::Dragon() 
{
	m_Name = "Dragon";
	m_Object3D.SetFileName(_T("Dragon.x"));
	m_pBoss = nullptr;
	
	// Task�擾
	m_pHierarchy = Hierarchy::Create();
	
	// FireParent����
	m_pFireParent = Hierarchy::Create()->FindWithName("DragonFireParent");
	m_pFireParent->BanDestroy();
	
	// BulletFog�擾
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
	
	// AnimCotroller�擾
	m_Object3D.SetAnimationController();
}

Dragon::~Dragon() {
	
}

bool Dragon::Start( float fAtackLevel ){

	ReInit();
	m_bStart = false;
	m_bAtack = false;
	m_nAssaultCnt = rand()%nAssaultInterval; // Near�ł�Far�ł����s�H
	m_nFireCnt = rand()%nFireInterval;
	m_nAtackCnt = 1;
	m_nAtackValue = 999;
	m_fInitPos = RANDOM_HEIGHT;
	m_fReturnPos = D3DXVECTOR3(0,0,0);
	m_fAtackLevel = fAtackLevel;
	
	// Boss�擾
	if( !m_pBoss )
		m_pBoss = m_pHierarchy->FindWithTag("Boss");
	
	// �����ʒu
	float fPosX,fPosZ;
	switch(rand()%4){
		
	case 0:
		fPosX = RANDOM_POS;
		fPosZ = RANDOM_POS;
		break;
	case 1:
		fPosX = -RANDOM_POS;
		fPosZ = RANDOM_POS;
		break;
	case 2:
		fPosX = RANDOM_POS;
		fPosZ = -RANDOM_POS;
		break;
	case 3:
		fPosX = -RANDOM_POS;
		fPosZ = -RANDOM_POS;
		break;
	}
	Move( D3DXVECTOR3(fPosX,m_fInitPos,fPosZ) );
	Rotation( D3DXVECTOR3(0,Pai,0) );

	// �R���W�����ݒ�
	SetCollisionCubeSize( D3DXVECTOR3(5.0f,5.0f,5.0f), D3DXVECTOR3(5.0f,5.0f,5.0f) );

	// �傫������
	m_Scale = D3DXVECTOR3(2.0f,2.0f,2.0f);

	// ���C�t�ݒ�
	m_nLife = nLife; // 10000
	
	// Player�擾
	m_pPlayer = m_pHierarchy->FindWithName("Player");	
	
	// �A�j���[�V�����ݒ�
	int nShift = 0;
	m_Object3D.GetAnimationManager()->SetLoopTime( "Wait", 120 );
	m_Object3D.GetAnimationManager()->SetShiftTime( "Wait", nShift );
	m_Object3D.GetAnimationManager()->SetLoopTime( "Assault", nAssaultTime );
	m_Object3D.GetAnimationManager()->SetShiftTime( "Assault", nShift );
	m_Object3D.GetAnimationManager()->SetLoopTime( "Fire", 90 );
	m_Object3D.GetAnimationManager()->SetShiftTime( "Fire", nShift );
	
	m_Object3D.GetAnimationManager()->ChangeAnimation( "Wait", true );
	m_Object3D.SetAnimFlg( true );
	
	// �A��ꏊ��ݒ�
	switch(rand()%4){
		
	case 0:
		fPosX = RANDOM_POS;
		fPosZ = RANDOM_POS;
		break;
	case 1:
		fPosX = -RANDOM_POS;
		fPosZ = RANDOM_POS;
		break;
	case 2:
		fPosX = RANDOM_POS;
		fPosZ = -RANDOM_POS;
		break;
	case 3:
		fPosX = -RANDOM_POS;
		fPosZ = -RANDOM_POS;
		break;
	}
	m_fReturnPos = m_Position + D3DXVECTOR3( fPosX, 0, fPosZ );
	m_fReturnPos.y = fReturnHeight;

	return true;
}

void Dragon::Update(){
	
	if( m_nLife > 0 ) {
		if( m_Child.empty() ) {
			// �e�쐬
			GameObject* pObj = m_pHierarchy->CreateObject(new Shadow);
			pObj->SetParent(this);
			pObj->Start();
			*(pObj->GetScale()) *= 10.0f;
			PlaySound(DRAGONASSAULT);
		}

		if( !m_bStart && m_Position.y <= m_fInitPos-30.0f ) {
			m_bStart = true;
		}
		
		// Player�̕�������
		if( m_nAtackValue != 0 ) {
			float fRot = Vector(m_Position,*(m_pPlayer->GetPosition()))-m_Rotation.y;
			Rotation(D3DXVECTOR3(0,fRot,0));
		}
	
		// �܂��퓬�J�n����Ȃ�
		if( !m_bStart ) {

			Move( D3DXVECTOR3(0,-0.5f,0) );

			return;
		}

		// �U�����ĂȂ�
		if( !m_bAtack && !*(m_pBoss->GetBool()) && !*(m_pPlayer->GetBool()) ) {

			// �U���`�F�b�N
			CheckAtack();
		}
	
		// �U�����Ȃ̂Ŏ��s
		else {

			switch( m_nAtackValue ){

			case 0: // Assault
				AssaultAtack();
				break;

			case 1: // Fire
				FireAtack();
				break;

			default:
				break;
			}
		}
		
		// ���C�t���
		m_nLife --;
		if( m_bAtack && m_nLife <= 0 ) {
			m_nLife = 1;
		}
	}

	// ���C�t��0�ȉ��ɂȂ�����A���Ȃ��Ȃ�
	else if ( !m_bAtack ) {
		Move( m_fReturnPos/fReturnTime );

		// �߂���������
		if( fReturnHeight <= m_Position.y ) {
			m_bActive = false;
			m_bCollision = false;
			FindChild("Shadow")->SetLife(-1);
		}
	}
}

void Dragon::FastDraw(){
	// �`��
	// �A�j���[�V�����X�V
	if(m_Parent->GetUpdateFlg()) {
		m_Object3D.UpdateAnim();
	}
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}

// �U��������Ԃ�
bool* Dragon::GetBool(){
	return &m_bContact;
}

// �U�����s�����`�F�b�N
void Dragon::CheckAtack(){
		
	// Assault
	if( m_nAssaultCnt % (int)(nAssaultInterval*m_fAtackLevel) == 0 ) {
		m_bAtack = true;
		m_nAtackValue = 0;
		m_nAssaultCnt = 1;
		float fDistanceX = m_pPlayer->GetPosition()->x - m_Position.x;
		float fDistanceZ = m_pPlayer->GetPosition()->z - m_Position.z;
		//m_fBezSpeed = 1.0f/(sqrt( fDistanceX*fDistanceX + fDistanceZ*fDistanceZ )*60);
		m_fBezSpeed = 1.0f/nAssaultTime;
		m_Bez0 = m_Position;
		m_Bez1 = *(m_pPlayer->GetPosition());
		m_Bez1.y = m_pPlayer->GetPosition()->y*4;
		m_Bez2 = m_Position;
		m_Object3D.GetAnimationManager()->ChangeAnimation( "Assault", false );
		m_bCollision = true;
		return;
	}
	else {
		m_nAssaultCnt ++;
	}

	// Fire
	if( m_nFireCnt % (int)(nFireInterval*m_fAtackLevel) == 0 ) {
		// �U���I�u�W�F�N�g���쐬
		m_bAtack = true;
		m_nAtackValue = 1;
		m_nFireCnt =1;
		m_Object3D.GetAnimationManager()->ChangeAnimation( "Fire", false );
	}	
	else {
		m_nFireCnt ++; 
	}
}

// Fire�U��
void Dragon::FireAtack() {

	int nEndTime = 15 * (nFireTime/60);
	if( m_Object3D.GetAnimationManager()->GetWeight() == nFireTime - nEndTime ) {
		
		GameObject* pObj = m_pFireParent->CreateChild();
		pObj->ReInit(); // �ď�����
		*(pObj->GetRotation()) = m_Rotation; 
		*(pObj->GetPosition()) = m_Position + D3DXVECTOR3(fMovePos*sinf(m_Rotation.y), -1.5f, fMovePos*cosf(m_Rotation.y)); 
		pObj->Start(); 
		PlaySound(DRAGONFIRE);
		m_nAtackValue = 999;
		m_bAtack = false;
		DownCount();
	}
}

// Assault�U��
void Dragon::AssaultAtack(){
	
	// �J�E���g����
	m_nAtackCnt++;

	if( m_fBezTime < 1.0f ) {

		float fRate = 1;

		if( m_fBezTime > 0.4f && m_fBezTime < 0.5f ) {
			fRate = 3.0f;
		}
		else if( m_fBezTime > 0.3f && m_fBezTime < 0.5f ) {
			fRate = 2.0f;
		}
		
		if( m_fBezTime < 0.1f ) {
			fRate = 0.33f;
		}
		else if( m_fBezTime < 0.2f ) {
			fRate = 0.5f;
		}

		if( m_fBezTime >= 0.35f && m_fBezTime <= 0.4f )
			PlaySound(DRAGONASSAULT);

		if( m_fBezTime >= 6.5f && m_bCollision )
			m_bCollision = false;

		if( m_fBezTime < 0.5f ) {
			Move( (m_Bez1 - m_Bez0) / ((float)(nAssaultTime/2)*fRate) );
		}
		else if( m_fBezTime > 0.5f ) {
			Move( (m_Bez2 - m_Bez1) / ((float)(nAssaultTime/2)*fRate) );
		}
		m_fBezTime += m_fBezSpeed/fRate;
		
		if( m_fBezTime >= m_fBezSpeed*(nAssaultTime-(nAssaultTime/60.0f*10.0f)) ) {
			m_Object3D.SetAnimFlg(true);
		}
		else if( m_Object3D.GetAnimationManager()->GetLoopTime("Assault") - nAssaultTime/60.0f*10.0f <= m_Object3D.GetAnimationManager()->GetWeight() ) {
			m_Object3D.SetAnimFlg(false);
		}
	}
	else {
		m_fBezTime = 0.0f;
		m_nAtackValue = 999;
		m_bAtack = false;
		DownCount();
		m_Object3D.SetAnimFlg(true);
	}
}

void Dragon::DownCount(){
	
	m_nFireCnt -= 30;
	if( m_nFireCnt < 1 )
		m_nFireCnt = 1;

	m_nAssaultCnt -= 30;
	if( m_nAssaultCnt < 1 )
		m_nAssaultCnt = 1;
}

float Dragon::Vector(D3DXVECTOR3 MyPos, D3DXVECTOR3 OpoPos){
	
	float fDistanceX = OpoPos.x - MyPos.x;
	//float fDistanceY = OpoPos.y - MyPos.y;
	float fDistanceZ = OpoPos.z - MyPos.z;
	float fRot = atan2f(fDistanceX,fDistanceZ);

	return fRot;
}

D3DXVECTOR3 Dragon::Random() {
	
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

	// Debug
	Random.y = 0.0f;

	return Random;
}