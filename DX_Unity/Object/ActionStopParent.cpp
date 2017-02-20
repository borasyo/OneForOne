//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [ActionStopParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "ActionStopParent.h"

// -- �萔
const float fAtackTime = 5.0f;
const int nMaxLife = 185;

// --- �}�N�� 
#define RANDOM (rand()%300*0.01f)

ActionStopParent::ActionStopParent() {
	m_Name = "ActionStopParent";
	m_Tag = "Parent";
	SetCollisionCubeSize(D3DXVECTOR3(25.0f,10.0f,25.0f),D3DXVECTOR3(25.0f,10.0f,25.0f));
	m_bActive = false;
	m_bCollision = false;
	m_bDestroy = false;
	
	// BulletFog�擾
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
	
#if _DEBUG
	std::cout << "CreateActionStopParent" << std::endl;
#endif
}

ActionStopParent::~ActionStopParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	ActionStopChild.erase(ActionStopChild.begin(),ActionStopChild.end());
}

// 
GameObject* ActionStopParent::CreateChild(){

	// �p�x���炷
	m_Rotation.y += Pai/32.0f;
	ExceptionCheck();

	auto Ite = ActionStopChild.begin();
	for( ; Ite != ActionStopChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂ōĎg�p
		//(*Ite)->Start();

		break;
	}
	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == ActionStopChild.end() ) {
		ActionStop* pObj = new ActionStop;
		pObj->SetParent(this);
		ActionStopChild.push_back(pObj);
		//pObj->Start();
		
#if _DEBUG
		std::cout << "ActionStop" << ActionStopChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

bool ActionStopParent::Start(){
	
	// ������
	ReInit();

	// ���C�t
	SetLife(nMaxLife);
	
	// Player���擾
	m_pPlayer = Hierarchy::Create()->FindWithName("Player");

	m_bAtack = false;
	m_fMoveSpeed = 0.0f;
	m_fHeight = 0.0f;

	return true;
}

// �X�V�`��
void ActionStopParent::Update(){
	
	// Player�����Ȃ���Δj��
	if( !m_pPlayer ) {
		m_nLife = 0;
		return;
	}
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			continue;
		}

		(*Ite)->Update();
	}

	if( m_fHeight == 0.0f ) {
		m_fHeight = m_Position.y;
	}
	
	// �G�t�F�N�g����
	for( int i = 0; i < 8; i++ ) {
		GameObject* pObj = CreateChild();
		pObj->ReInit();
		*(pObj->GetRotation()) = m_Rotation;
		*(pObj->GetPosition()) = m_Position;
		pObj->Start();
	}
	
	// ���
	m_nLife --;
	
	// �I��
	if( m_nLife <= 0 ) {	
		m_bActive = false;
		m_bCollision = false;
		m_nLife = 1; // �j�󂳂��Ȃ�
		for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
			(*Ite)->SetActive(false);
		}

		// �e�������
		if( !m_Parent )
			return;

		m_Parent->SetUpdateFlg(true); // �X�V�ĊJ
		m_Parent->Rotation( D3DXVECTOR3( -(m_Parent->GetRotation()->x), 0, -(m_Parent->GetRotation()->z) ) );
		m_Parent->SetActive(true);
		for( auto Ite = m_Parent->GetChild()->begin(); Ite != m_Parent->GetChild()->end(); Ite++ ) {
			if( *Ite == this ) {
				m_Parent->GetChild()->erase(Ite);
				break;
			}
		}
		// �e������
		m_Parent = nullptr;
	}

	if( m_Parent ) {
		// �G�t�F�N�g�쐬
		for( int i = 0; i < 2; i++ ) {
			GameObject* pObj = m_pBulletFogParent->CreateChild(D3DXCOLOR(1.0f,0.1f,0.1f,0.5f));
			*(pObj)->GetPosition() = m_Position + RandomPos();
			*(pObj)->GetScale() = D3DXVECTOR3(3,3,3);
		}
	}

	// Player��߂܂��Ă���Ƃ��͒ǂ������鏈����~
	if( m_Parent || !m_bAtack ) 
		return;

	// Player�Ƃ̋����𑪂�
	float fDistanceX = m_pPlayer->GetPosition()->x - m_Position.x;
	float fDistanceZ = m_pPlayer->GetPosition()->z - m_Position.z;

	// ��ɒǂ�������
	float fRot = atan2f( fDistanceX, fDistanceZ );
	m_Position.x += m_fMoveSpeed * sinf( fRot ); // �����x�Ɋp�x�����Ĉړ�
	m_Position.z += m_fMoveSpeed * cosf( fRot ); // �����x�Ɋp�x�����Ĉړ�
	m_Position.y -= (m_fHeight-1.2f)/fAtackTime;
	if( m_Position.y < 1.2f )
		m_Position.y = 1.2f;

	m_nLife ++;
}


void ActionStopParent::Draw(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			continue;
		}

		(*Ite)->Draw();
	}
}

void ActionStopParent::FreeFunction(){
	
	float fDistanceX = m_pPlayer->GetPosition()->x - m_Position.x;
	float fDistanceZ = m_pPlayer->GetPosition()->z - m_Position.z;
	m_fMoveSpeed = sqrt( fDistanceX*fDistanceX + fDistanceZ*fDistanceZ ) / fAtackTime;

	m_bAtack = true;
}

D3DXVECTOR3 ActionStopParent::RandomPos(){

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

	return pos/2;
}