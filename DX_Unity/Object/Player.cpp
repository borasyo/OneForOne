//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Player.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Player.h"
#include "NearAtack.h"
#include "FarAtack.h"
#include "PlayerFog.h"
#include "Shadow.h"
#include "Deathblow.h"
#include "FadeIn.h"
#include "DeathblowEffect.h"
#include "Pause.h"
#include "Item.h"
#include "../Library/Task/SceneManager.h"
#include "../Library/DirectX/DirectSound.h"

#include "CameraSelect.h"

// -- �萔
//const float fRotSpeed = 0.0075f; // �J�����̉�]��
const float fMoveSpeed = 0.2f; // �ʏ�ړ���
const float fRun = 1.5f;		// �����Ă���Ƃ��̑���
const float fMoveRot = 0.03f;	// �ړ����̉�]��
const int nChangeTime = 45;		// ����ύX�ɂ����鎞��
const float fCollision = 0.85f; 
const int nMaxReverberation = 210;
const int nItemInterval = 1800; // nItemInterval/60�b��1��4����3�̊m���ŃA�C�e��������
const float fAvoidSpeed = 4.5f;

const int nMaxAvoidTime = 10;

// -- �}�N��
#define RotSpeed (11.25f/(float)(CWindow::Create()->GetClientWidth()))
#define RANDOM_X (rand()%50*0.01f)
#define RANDOM_Y (rand()%100*0.01f)
#define RANDOM_Z (rand()%50*0.01f)

Player::Player()//:m_bNearAtack(false)
				//,m_bChange(false)   
				//,m_bAtack(false)  
				//,m_bDeathblow(false) 
				//,m_fMaxRot(fInitRot*fMagnification) {
{
	m_Name = "Player";
	m_Object3D.SetFileName(_T("Player.x"));
	m_pDirectInputManager = CDirectInputManager::Instance();
	
	m_pHierarchy = Hierarchy::Create();
	
	// BulletFog�擾
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
}

Player::~Player(){

}

void Player::Awake(){

	ReInit();
	m_bNearAtack = false;
	m_bChange = false;  
	m_bAtack = false;
	m_bDeathblow = false;
	m_bGaugeMax = false;
	m_bPause = false;
	m_fMaxRot = fInitRot*fMagnification;
	m_nItemCnt = 1;
	m_nAccumulationDamage = 0;
	m_nAvoidTime = 0;
	m_bAvoid = false;
	m_AvoidAmount = D3DXVECTOR3(0,0,0);
	m_pCamera = Hierarchy::Create()->FindWithName("PlayerCamera");
	m_pCameraSelect = Hierarchy::Create()->FindWithName("CameraSelect");
	
	// �e����
	GameObject* pObj = m_pHierarchy->CreateObject(new Shadow);
	pObj->SetParent(this);
	pObj->Start();
	*(pObj->GetScale()) *= 2.0f;

	Move( D3DXVECTOR3(0,1.2f,-40.0f) );
	
	m_pPlayerFogParent = m_pHierarchy->FindWithName("PlayerFogParent");

	SetLife(20); // 1�Ŏ��S
	m_nOldLife = m_nLife;
	m_fDeathblowGauge = 0.0f; // 0.0f
	m_nReverberation = 0;

	// �R���W�����ݒ�
	SetCollisionCubeSize(D3DXVECTOR3(fCollision,2.0f,fCollision), D3DXVECTOR3(fCollision,2.0f,fCollision));

	// Debug
	//m_fDeathblowGauge =	100.0f; // 0.0f
}

void Player::Update(){

	// �U����H����Ă����ꍇ�A�ݐσ_���[�W�𑝂₷
	if( m_nOldLife != m_nLife ) {
		int i = m_nOldLife - m_nLife;
		if( i > 0 ) { // �񕜂��Ă���ꍇ�͓���Ȃ� 
			m_nAccumulationDamage += i;
			// ��u��
			*(m_pCameraSelect->GetVec()) = D3DXVECTOR3( 10.0f, 1.0f, 0 );
		}
	}

	if( m_nItemCnt%nItemInterval == 0 ) { //&& rand()%6 != 0 ) {
		m_pHierarchy->CreateObject(new Item)->Start();
		m_nItemCnt = 1;
	}
	else
		m_nItemCnt ++;

	// Player���S����
	if( m_nLife <= 1 ){
		SceneManager::Create()->SetGameOver();
		return;
	}

	// Update���Ă���̂�Pause���ł͂Ȃ�
	m_bPause = false;

	// �ړ�
	if( !m_bAvoid ) {
		if( !m_bDeathblow ) {
			CharaMove();
		}
	}
	else {
		AvoidMove();
	}

	// �U�����ĂȂ��Ȃ�
	if( !m_bDeathblow && !m_bChange  )
		Atack();

	// Fog�쐬
	if( m_fDeathblowGauge >= fMaxDeathblowGauge || m_bDeathblow ) {
		CreateFog();
	}

	// ����ύX����
	if( (m_pDirectInputManager->GetMouseTrigger(1) || m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_08)) && !m_bChange && !m_bDeathblow ) {
		m_bChange = true;
		m_nChangeCnt = 0;
	}

	// �K�E�Z�����I�I
	if( m_fDeathblowGauge >= fMaxDeathblowGauge && 
		(m_pDirectInputManager->GetMouseTrigger(2) || m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_07)) && !m_bChange && !m_bDeathblow ) {
		CreateDeathblow();
	}

	// �`�F���W
	if( m_bChange )
		Change();

	// �K�E�Z�̂��Ǝb���͖��G�p��
	if( !m_bCollision && !m_bDeathblow ) {
		m_nReverberation ++;
		if( m_nReverberation >= nMaxReverberation ) {
			m_bCollision = true;
			m_nReverberation = 0;
		}
	}

	// �K�E�Q�[�W����
	if( m_fDeathblowGauge < fMaxDeathblowGauge && !m_bDeathblow ) {
		m_fDeathblowGauge += fMaxDeathblowGauge/fDeathblowTime; // ���u�ł�30�b�ŗ��܂�
		//m_fDeathblowGauge += 0.3f;
	}
	
	// Pause
	// ������Ƃ�N���X��ʂŗp�ӂ�����
	// Player��Update�Ŕ�����Ƃ��Player�̍X�V���~�܂�ꍇ�A�|�[�Y�o���Ȃ��Ȃ��Ă��܂�����
	if( m_pDirectInputManager->GetKeyboardTrigger( DIK_LCONTROL ) || 
		m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_10) ) {
		m_pHierarchy->CreateObject(new Pause);
		PlaySound(CLICK);
		Rotation( D3DXVECTOR3(-m_Rotation.x,0,-m_Rotation.z) );
		m_bPause = true;
	}

	// ��O�`�F�b�N���{
	ExceptionCheck();

	// �R���W�����O�̃��C�t��ۑ�
	m_nOldLife = m_nLife;
}

// ---- �`��
void Player::Draw(){
	
	// --- Debug
	if((m_pDirectInputManager->GetKeyboardHold(DIK_G) || m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_12)) && m_nLife <= 20) {
		m_nLife++;
	}
	if((m_pDirectInputManager->GetKeyboardHold(DIK_F) || m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_11))) {
		m_fDeathblowGauge += 1.0f;
	}
	// ---
	
	// ��]
	if( !m_bPause ) {

		const float fJoyRiv = 3.0f;
		if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_04)) {
			Rotation( D3DXVECTOR3(0, -RotSpeed * fJoyRiv, 0));
		} else if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_02)) {
			Rotation( D3DXVECTOR3(0, RotSpeed * fJoyRiv, 0) );
		} else {
			Rotation( D3DXVECTOR3(0, m_pDirectInputManager->GetMouseMoveX()*RotSpeed,0) );
		}
	}

	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}

void Player::FastDraw(){
	if( m_fDeathblowGauge >= fMaxDeathblowGauge ) {
		m_fDeathblowGauge = fMaxDeathblowGauge;
		if( !m_bGaugeMax ) {
			PlaySound(DEATHBLOWGAUGEMAX);
			m_bGaugeMax = true;
		}
	}
}

void Player::AvoidMove() {

	// ������s
	Move( m_AvoidAmount );
	
	// �G�t�F�N�g
	for( int i = 0; i < 10; i++ ) {
		
		// �G�t�F�N�g�쐬
		D3DXVECTOR3 Random = D3DXVECTOR3(0,0,0);
		if( rand()%2 ) {
			Random.y += RANDOM_Y;
		}
		else {
			Random.y -= RANDOM_Y;
		}
		switch( rand()%4 ) {
		case 0:
			Random.x += RANDOM_X; 
			Random.z += RANDOM_Z; 
			break;
		case 1:
			Random.x -= RANDOM_X; 
			Random.z += RANDOM_Z; 
			break;
		case 2:
			Random.x += RANDOM_X; 
			Random.z -= RANDOM_Z; 
			break;
		case 3:
			Random.x -= RANDOM_X; 
			Random.z -= RANDOM_Z; 
			break;
		default:
			break;
		}

		GameObject* pObj = m_pBulletFogParent->CreateChild( D3DXCOLOR(0.1f,0.3f,1.0f,0.5f), 1.0f, 0.5f );
		*(pObj->GetPosition()) = m_Position+Random;
		*(pObj->GetScale()) = D3DXVECTOR3(1.5f,1.5f,1.5f);
	}

	m_nAvoidTime ++;

	if( m_nAvoidTime >= nMaxAvoidTime ) {
		m_nAvoidTime = 0;
		m_bAvoid = false;
		m_AvoidAmount = D3DXVECTOR3(0,0,0);
		m_fMaxRot = fInitRot*fMagnification;
		m_fDeathblowGauge -= 10.0f;
		if( (!m_pDirectInputManager->GetKeyboardHold(DIK_A)   && !m_pDirectInputManager->GetKeyboardHold(DIK_D)) ||
			(m_pDirectInputManager->GetKeyboardHold(DIK_A) && m_pDirectInputManager->GetKeyboardHold(DIK_D)) )
			Rotation( D3DXVECTOR3(0,0,-m_Rotation.z) );
		if( (!m_pDirectInputManager->GetKeyboardHold(DIK_W) && !m_pDirectInputManager->GetKeyboardHold(DIK_S)) ||
			(m_pDirectInputManager->GetKeyboardHold(DIK_W) && m_pDirectInputManager->GetKeyboardHold(DIK_S)) )
			Rotation( D3DXVECTOR3(-m_Rotation.x,0,0) );
		//Rotation( D3DXVECTOR3(-m_Rotation.x,0,-m_Rotation.z) );
	}
}

// DeathblowGauge��Ԃ�
float* Player::GetFloat(){

	return &m_fDeathblowGauge;
}

// �K�E�t���O��Ԃ�
bool* Player::GetBool(){
	return &m_bDeathblow;
}

// �ݐσ_���[�W��Ԃ�(Clear���ȊO�g��Ȃ�)
int* Player::GetInt(){
	return &m_nAccumulationDamage;
}

// ---- Player�̈ړ�
bool Player::CharaMove(){

	 m_fMove = 0.0f;
	float fRot = 0.0f; 
	D3DXVECTOR3 MoveRot = D3DXVECTOR3(0,0,0);

	// �ړ�
	if( m_pDirectInputManager->GetLeftHold() ){
		m_fMove = fMoveSpeed; // �ړ�
		fRot = -(Pai/2.0f);

		// -- Player��]
		if( m_Rotation.z <= m_fMaxRot )
			MoveRot.z += fMoveRot;
	}
	else if( m_pDirectInputManager->GetRightHold() ){
		m_fMove = fMoveSpeed;	// �ړ�
		fRot = (Pai/2.0f);
		
		// -- Player��]
		if( m_Rotation.z - Pai*2.0f >= -m_fMaxRot || m_Rotation.z == 0.0f )
			MoveRot.z -= fMoveRot;
	}
	if( m_pDirectInputManager->GetForwardHold() ){
		m_fMove = fMoveSpeed;	// �ړ�

		// -- Player��]
		if( m_Rotation.x <= m_fMaxRot )
			MoveRot.x += fMoveRot;

		// -- �΂߈ړ��`�F�b�N
		if( m_pDirectInputManager->GetLeftHold())
			fRot = -(Pai/4.0f);
		else if( m_pDirectInputManager->GetRightHold() )
			fRot = (Pai/4.0f);
	}
	else if( m_pDirectInputManager->GetBackHold() ){
		m_fMove = fMoveSpeed;	// �ړ�
		fRot = Pai;

		// -- Player��]
		if( m_Rotation.x - Pai*2.0f >= -m_fMaxRot || m_Rotation.x == 0.0f )
			MoveRot.x -= fMoveRot;

		// -- �΂߈ړ��`�F�b�N
		if( m_pDirectInputManager->GetLeftHold() )
			fRot = -(Pai/4.0f)-(Pai/2.0f);
		else if( m_pDirectInputManager->GetRightHold() )
			fRot = (Pai/4.0f)+(Pai/2.0f);
	}

	// ���xUP���邩
	//if( m_bDeathblow )
	//	m_fMove *= fRun*1.5f;
	//if( m_bNearAtack )
	
	// �p�������ɖ߂�
	if( m_pDirectInputManager->GetKeyboardRelease(DIK_A) || m_pDirectInputManager->GetKeyboardRelease(DIK_D) || 
		m_pDirectInputManager->GetJoyAxisRelease(0, JOY_X) || 
		(m_pDirectInputManager->GetKeyboardTrigger(DIK_A) && m_pDirectInputManager->GetKeyboardHold(DIK_D)) )
		Rotation( D3DXVECTOR3(0,0,-m_Rotation.z) );
	if( m_pDirectInputManager->GetKeyboardRelease(DIK_W) || m_pDirectInputManager->GetKeyboardRelease(DIK_S) ||
		m_pDirectInputManager->GetJoyAxisRelease(0, JOY_Y) ||
		(m_pDirectInputManager->GetKeyboardTrigger(DIK_W) && m_pDirectInputManager->GetKeyboardHold(DIK_S)) )
		Rotation( D3DXVECTOR3(-m_Rotation.x,0,0) );

	// �ړ����s
	if( m_fMove != 0.0f ) {
		
		m_fMove *= fRun;
	

		// �ړ�����Ƃ���SHIFT�������ꂽ��
		if( (m_pDirectInputManager->GetKeyboardTrigger(DIK_LSHIFT) || m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_05)) && m_fDeathblowGauge >= 10.0f ) {
			m_bAvoid = true;
			m_AvoidAmount = D3DXVECTOR3( m_fMove*sinf(m_Rotation.y+fRot), 0, m_fMove*cosf(m_Rotation.y+fRot) );
			m_AvoidAmount *= fAvoidSpeed;
			m_nAvoidTime = 0;
			
			m_fMaxRot = fInitRot*fMagnification*3.0f;
			
			// ��]���s
			Rotation(MoveRot*20.0f);

			// SE�Đ�
			PlaySound(AVOID);

			return true;
		}
		
		// ��]���s
		Rotation(MoveRot);

		Move(D3DXVECTOR3( m_fMove*sinf(m_Rotation.y+fRot), 0, m_fMove*cosf(m_Rotation.y+fRot) ) );

		return true;
	} 
	
	Rotation( D3DXVECTOR3(-m_Rotation.x,0,-m_Rotation.z) );
	return false;
}

// ---- �U��
void Player::Atack(){
	
	if( m_pDirectInputManager->GetMouseHold(0) || m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_06) ){

		// �K�E�Z
		if( m_bDeathblow || CameraSelect::GetCameraState() == CAMERA_DEATHBLOW ) 
			return;

		// �ߐ�
		if( m_bNearAtack ) {
			NearAtack Atk;
			for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
				if( (*Ite)->GetName() == "NearAtack" )
					Atk.GetDownCastClass(*Ite)->Atack();
		}
		// ������
		else {
			FarAtack Atk;
			for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
				if( (*Ite)->GetName() == "FarAtack" )
					Atk.GetDownCastClass(*Ite)->Atack();
		}
	}
}

// ---- ����؂�ւ�
void Player::Change(){

	// ����̑傫����ύX
	D3DXVECTOR3 NearScale = D3DXVECTOR3(1.5f/(float)nChangeTime,1.5f/(float)nChangeTime,1.5f/(float)nChangeTime);
	D3DXVECTOR3 FarScale = D3DXVECTOR3(1.0f/(float)nChangeTime,1.0f/(float)nChangeTime,1.0f/(float)nChangeTime);
	
	// �`�F���W�J�E���g�𑝂₷
	m_nChangeCnt ++;

	// ���O���r���邽��
	NearAtack Near;
	FarAtack Far;
	
	// ���݋ߐڍU���Ȃ�
	if( m_bNearAtack ){
		for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {

			// �ߐڂ��Ђ����߂�
			if( (*Ite)->GetName() == Near.GetName() ) 
				(*Ite)->ScaleChange( -NearScale );

			// ������������
			if( (*Ite)->GetName() == Far.GetName() ) { 
				(*Ite)->ScaleChange( FarScale );
			}
		}
	}
	// ���݉������U���Ȃ�
	else {
		for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
			
			// �ߐڂ�����
			if( (*Ite)->GetName() == Near.GetName() ) 
				(*Ite)->ScaleChange( NearScale );
			
			// ���������Ђ����߂�
			if( (*Ite)->GetName() == Far.GetName() ) { 
				(*Ite)->ScaleChange( -FarScale );
			}
		}
	}

	if( m_nChangeCnt >= nChangeTime ){

		// ����`�F���W�I��
		m_bChange = false;
		
		// �t���O����ւ�
		m_bNearAtack = !m_bNearAtack;
		
		m_fMaxRot = fInitRot*fMagnification;
	}
}

// --- �K�E�Z�����I
void Player::CreateDeathblow() {
	
	PlaySound(CLICK);
	m_bGaugeMax = false;

	// �쐬
	GameObject* pObj = m_pHierarchy->CreateObject(new Deathblow);
	*(pObj->GetPosition()) = m_Position;
	pObj->Start();

	// �G�t�F�N�g�쐬
	m_pHierarchy->CreateObject(new DeathblowEffect);

	// �t���OON
	m_bDeathblow = true;

	// ���G���
	m_bCollision = false;
	
	// �p�������ɖ߂�
	Rotation( D3DXVECTOR3(-m_Rotation.x,0,-m_Rotation.z) );

	// 
	CameraSelect::SetState(CAMERA_DEATHBLOW);
}

// ---- Player��Particle�쐬�}�V��
void Player::CreateFog(){

	if( m_bDeathblow ) {
		GameObject* pFog = m_pPlayerFogParent->CreateChild();
		pFog->ReInit();
		*(pFog->GetPosition()) = m_Position;
		*(pFog->GetRotation()) = m_Rotation;
		pFog->Start();
		pFog->FreeFunction();
	}

	else if( rand()%3 == 0 ) {
		GameObject* pFog = m_pPlayerFogParent->CreateChild();
		pFog->ReInit();
		*(pFog->GetPosition()) = m_Position;
		*(pFog->GetRotation()) = m_Rotation;
		pFog->Start();
	}
}

// ---- �Q�b�^�[
bool Player::GetNearAtackFlg(){
	return m_bNearAtack;
}


