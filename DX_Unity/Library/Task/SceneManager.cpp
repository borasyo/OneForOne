//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneManager.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SceneManager.h"
#include "../DirectX/DirectSound.h"

// ---- object�ɂ���class���C���N���[�h
// -- MainMenu
#include "../../Object/MainMenu.h"
#include "../../Object/MainMenuTitle.h"
#include "../../Object/EasyBotton.h"
#include "../../Object/NormalBotton.h"
#include "../../Object/HardBotton.h"
#include "../../Object/ExitBotton.h"
#include "../../Object/HelpBotton.h"
#include "../../Object/HelpMenu.h"

// --- GameClear&&Over
#include "../../Object/GameOver.h"
#include "../../Object/GameClearCamera.h"
#include "../../Object/GameClearFogParent.h"

// -- Empty
#include "Empty.h"

// -- UI
#include "../../Object/Rader.h"
#include "../../Object/PlayerUI.h"

// -- Player
#include "../../Object/Player.h"
#include "../../Object/NearAtack.h"
#include "../../Object/FarAtack.h"
#include "../../Object/Deathblow.h"
#include "../../Object/PlayerCamera.h"
#include "../../Object/Danger.h"

// -- Camera
#include "../../Object/CameraSelect.h"
#include "../../Object/BeamCamera.h"
#include "../../Object/InvincibleCamera.h"
#include "../../Object/DeathblowCamera.h"

// -- Enemy
#include "../../Object/Wizard.h"
#include "../../Object/WizardWeapon.h"
#include "../../Object/Devil.h"
#include "../../Object/Dragon.h"

// -- Collision
#include "../../Object/MainMenuCollision.h"
#include "../../Object/CollisionEasyMode.h"
#include "../../Object/CollisionNormalMode.h"
#include "../../Object/CollisionHardMode.h"
#include "../../Object/ItemCollision.h"
#include "../../Object/FieldCollision.h"

//-- Field
#include "../../Object/SkyDome.h"
#include "../../Object/Field.h"

// --- Shadow
#include "../../Object/Shadow.h"

// --- Time
#include "../../Object/Time.h"

// --- Light
#include "../../Object/MainLight.h"

// --- Parent
#include "../../Object/BulletFogParent.h"
#include "../../Object/BeamParent.h"
#include "../../Object/WizardFogParent.h"

// -- Debug
#include "../../Object/Test2D.h"
#include "../../Object/Test3D.h"
#include "../../Object/TestCamera.h"
#include "../../Object/TestLight.h"
#include "../../Object/TestBuff.h"
#include "../../Object/TestLight.h"


// --- �R���X�g���N�^
SceneManager::SceneManager() {
	m_pCreator = Hierarchy::Create();
	m_pAllObj = m_pCreator->FindAllObject();
}

SceneManager::~SceneManager() {
	
}

// �N���G�C�g�֐�
SceneManager* SceneManager::Create() {
	static SceneManager* pSceneManager = new SceneManager;
	return pSceneManager;
}

// ������object�𐶐�
void SceneManager::SetObject() {
	
	// UI�쐬
	m_pCreator->CreateObject(new Rader);
	m_pCreator->CreateObject(new PlayerUI);

	// Field�쐬
	m_pCreator->CreateObject(new SkyDome);
	m_pCreator->CreateObject(new Field);
	m_pCreator->CreateObject(new FieldCollision);
			
	// BulletFog���܂Ƃ߂���ꕨ���쐬
	BulletFogParent* pBulletFog = new BulletFogParent;
	m_pCreator->CreateObject(pBulletFog)->BanDestroy();
	// ���炩���߂�����x�쐬
	for( int i = 0; i < 10000; i++ )
		pBulletFog->CreateChild(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	for( auto Ite = pBulletFog->GetChild()->begin(); Ite != pBulletFog->GetChild()->end(); Ite++ )
		(*Ite)->SetActive(false);
	
	// Fade�̓��ꕨ����
	m_pCreator->CreateObject(new Empty("Fade"));
	
	// Beam���܂Ƃ߂���ꕨ���쐬
	BeamParent* pBeamParent = new BeamParent;
	m_pCreator->CreateObject(pBeamParent)->BanDestroy();

	// ���炩���߂�����x�쐬
	for( int i = 0; i < 600; i++ )
		pBeamParent->CreateChild(D3DXCOLOR(0,0,0,0),D3DXVECTOR3(0,0,0),true);
	for( auto Ite = pBeamParent->GetChild()->begin(); Ite != pBeamParent->GetChild()->end(); Ite++ ) {
		(*Ite)->SetActive(false);
		(*Ite)->SetCollisionFlg(false);
	}

	// WizardFog���܂Ƃ߂���ꕨ���쐬
	WizardFogParent* pWizardFog = new WizardFogParent;
	m_pCreator->CreateObject(pWizardFog)->BanDestroy();
	
	// ���炩���߂�����x�쐬
	for( int i = 0; i < 1200; i++ )
		pWizardFog->CreateChild();
	for( auto Ite = pWizardFog->GetChild()->begin(); Ite != pWizardFog->GetChild()->end(); Ite++ )
		(*Ite)->SetActive(false);
	
	// Boss����
	GameObject* pDevil =  m_pCreator->CreateObject(new Devil);
	//m_pCreator->CreateObject(new Dragon);
	//GameObject* pWizardWeapon = m_pCreator->CreateObject(new WizardWeapon);
	//pWizardWeapon->SetParent( m_pCreator->CreateObject(new Wizard) );

	// �����A�j���[�V����
	m_pCreator->CreateObject(new FireExplosionParent);

	// Player�쐬
	GameObject* pPlayer = m_pCreator->CreateObject(new Player);
	m_pCreator->CreateObject(new NearAtack)->SetParent(pPlayer);
	m_pCreator->CreateObject(new FarAtack)->SetParent(pPlayer);
	m_pCreator->CreateObject(new PlayerCamera((Player*)pPlayer));//->SetParent();
	
	m_pCreator->CreateObject(new BeamCamera((Player*)pPlayer));
	m_pCreator->CreateObject(new InvincibleCamera((Player*)pPlayer));
	m_pCreator->CreateObject(new DeathblowCamera);
	m_pCreator->CreateObject(new CameraSelect);
	
	// -- Item
	m_pCreator->CreateObject(new ItemCollision);
	m_pCreator->CreateObject(new Empty("ItemParent"));

	// --- Time
	m_pCreator->CreateObject(new Time);

	// PlayerFogParent����
	GameObject* pPlayerFogParent = m_pCreator->CreateObject(new PlayerFogParent);
	pPlayerFogParent->SetParent(pPlayer);
	for( int i = 0; i < 150; i++ ) {
		pPlayerFogParent->CreateChild();
	}
	for( auto Ite = pPlayerFogParent->GetChild()->begin(); Ite != pPlayerFogParent->GetChild()->end(); Ite++ ) {
		(*Ite)->SetActive(false);
		(*Ite)->SetCollisionFlg(false);
	}

	// �R���W����
	//m_pCreator->CreateObject(new CollisionEasyMode);
	//m_pCreator->CreateObject(new CollisionNormalMode);
	m_pCreator->CreateObject(new CollisionHardMode);
	
	// Light����
	m_pCreator->CreateObject(new MainLight);

	// MainMenu�Ŏg���I�u�W�F�N�g
	m_pCreator->CreateObject(new MainMenu)->BanDestroy();
	m_pCreator->CreateObject(new MainMenuTitle)->BanDestroy();
	m_pCreator->CreateObject(new EasyBotton)->BanDestroy();
	m_pCreator->CreateObject(new NormalBotton)->BanDestroy();
	m_pCreator->CreateObject(new HardBotton)->BanDestroy();
	m_pCreator->CreateObject(new ExitBotton)->BanDestroy();
	m_pCreator->CreateObject(new HelpBotton)->BanDestroy();
	m_pCreator->CreateObject(new MainMenuCollision)->BanDestroy();
	m_pCreator->CreateObject(new HelpMenu)->BanDestroy();

	// GameClearFog����
	GameObject* pClearFog = m_pCreator->CreateObject(new GameClearFogParent);
	for( int i = 0; i < 400; i++ ) {
		pClearFog->CreateChild();
	}
	for( auto Ite = pClearFog->GetChild()->begin(); Ite != pClearFog->GetChild()->end(); Ite++ ) {
		(*Ite)->SetActive(false);
		(*Ite)->SetCollisionFlg(false);
	}

	// �_�ō쐬
	m_pCreator->CreateObject(new Danger);

	// �����܂łŐ��������I�u�W�F�N�g�͏I�����܂Ŕj�󂳂��Ȃ�
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		(*Ite)->BanDestroy();
	}
	
#if _DEBUG
	std::cout << "SetObject" << m_pAllObj->size() << std::endl;
#endif
}

// ---- �V�[���Ǘ��֐�

// �^�C�g���ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u��Ԃɂ���
void SceneManager::Menu() {

	// ��U�S�ẴI�u�W�F�N�g��false��
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		(*Ite)->SetActive(false);
	}
	
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		
		if( (*Ite)->GetName() == "MainMenu" )
			(*Ite)->SetActive(true);
		if( (*Ite)->GetName() == "MainMenuTitle" )
			(*Ite)->SetActive(true);
		if( (*Ite)->GetName() == "EasyBotton" )
			(*Ite)->SetActive(true);
		if( (*Ite)->GetName() == "NormalBotton" )
			(*Ite)->SetActive(true);
		if( (*Ite)->GetName() == "HardBotton" )
			(*Ite)->SetActive(true);
		if( (*Ite)->GetName() == "ExitBotton" )
			(*Ite)->SetActive(true);
		if( (*Ite)->GetName() == "HelpBotton" )
			(*Ite)->SetActive(true);
		if( (*Ite)->GetName() == "MainMenuCollision" )
			(*Ite)->SetActive(true);
	}

	StopSound();
	PlaySound(MAINMENU_BGM);
	
#if _DEBUG
	std::cout << "MainMenu" << std::endl;
#endif
}

// �Q�[�����C���ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u��Ԃɂ���
void SceneManager::EasyMode() {
	// ��U�S�ẴI�u�W�F�N�g��true��
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		(*Ite)->SetActive(true);
	}

	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		
		if( (*Ite)->GetName() == "MainMenu" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "MainMenuTitle" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "EasyBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "NormalBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "HardBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "ExitBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "HelpBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "MainMenuCollision" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "ActionStopParent" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "GameClearFogParent" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "HelpMenu" )
			(*Ite)->SetActive(false);

		if( (*Ite)->GetName() == "Devil" ) {
			*((*Ite)->GetInt()) = 2;
			(*Ite)->Awake();
		}
	}
	
	StopSound();
	PlaySound(HARD_BGM);

#if _DEBUG
	std::cout << "EasyMode" << std::endl;
#endif
}

void SceneManager::NormalMode() {
	// ��U�S�ẴI�u�W�F�N�g��true��
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		(*Ite)->SetActive(true);
	}
	
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		
		if( (*Ite)->GetName() == "MainMenu" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "MainMenuTitle" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "EasyBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "NormalBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "HardBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "ExitBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "HelpBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "MainMenuCollision" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "ActionStopParent" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "GameClearFogParent" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "HelpMenu" )
			(*Ite)->SetActive(false);
		
		if( (*Ite)->GetName() == "Devil" ) {
			*((*Ite)->GetInt()) = 1;
			(*Ite)->Awake();
		}
	}
	
	StopSound();
	PlaySound(HARD_BGM);

#if _DEBUG
	std::cout << "NormalMode" << std::endl;
#endif
}

void SceneManager::HardMode() {
	// ��U�S�ẴI�u�W�F�N�g��true��
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		(*Ite)->SetActive(true);
	}
	
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		
		if( (*Ite)->GetName() == "MainMenu" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "MainMenuTitle" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "EasyBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "NormalBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "HardBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "ExitBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "HelpBotton" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "MainMenuCollision" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "ActionStopParent" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "GameClearFogParent" )
			(*Ite)->SetActive(false);
		if( (*Ite)->GetName() == "HelpMenu" )
			(*Ite)->SetActive(false);
		
		if( (*Ite)->GetName() == "Devil" ) {
			*((*Ite)->GetInt()) = 0;
			(*Ite)->Awake();
		}
	}
	
	StopSound();
	PlaySound(HARD_BGM);

#if _DEBUG
	std::cout << "HardMode" << std::endl;
#endif
}

// �Q�[���G���h�ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u��Ԃɂ���
void SceneManager::SetGameOver(){
	
	StopSound();
	m_pCreator->CreateObject(new GameOver)->Start();
	
	GameObject* pPlayer = m_pCreator->FindWithName("Player");
	pPlayer->SetActive(false);
	pPlayer->SetCollisionFlg(false);

	for( auto Ite = pPlayer->GetChild()->begin(); Ite != pPlayer->GetChild()->end(); Ite++ ) {
		(*Ite)->SetActive(false);
		(*Ite)->SetCollisionFlg(false);
	}

#if _DEBUG
	std::cout << "GameOver" << std::endl;
#endif
}

// �Q�[���N���A�ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u��Ԃɂ���
void SceneManager::SetGameClear(){
	
	StopSound();

	// ClearCamera����
	m_pCreator->CreateObject(new GameClearCamera);

	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		
		if( (*Ite)->GetName() == "GameClearFogParent" ) {
			(*Ite)->SetActive(true);
			(*Ite)->Start();
			*((*Ite)->GetPosition()) = *(m_pCreator->FindWithTag("Boss")->GetPosition());
			*((*Ite)->GetScale()) = m_pCreator->FindWithTag("Boss")->GetCollisionCubeMinusSize();
		}
		
		if( (*Ite)->GetName() == "BeamParent" )
			(*Ite)->SetActive(false);
		
		if( (*Ite)->GetName() == "PlayerCamera" ) {
			(*Ite)->FreeFunction();
			(*Ite)->SetActive(false);
		}

		if( (*Ite)->GetName() == "BeamCamera" ) {
			(*Ite)->FreeFunction();
			(*Ite)->SetActive(false);
		}

		if( (*Ite)->GetName() == "InvincibleCamera" ) {
			(*Ite)->FreeFunction();
			(*Ite)->SetActive(false);
		}
		
		if( (*Ite)->GetName() == "DeathblowCamera" ) {
			(*Ite)->FreeFunction();
			(*Ite)->SetActive(false);
		}

		if( (*Ite)->GetName() == "Dragon" ) {
			(*Ite)->SetUpdateFlg(false);
			for( auto Child = (*Ite)->GetChild()->begin(); Child != (*Ite)->GetChild()->end(); Child ++ )
				(*Child)->SetUpdateFlg(false);
		}
		if( (*Ite)->GetName() == "CollisionNormalMode" )
			(*Ite)->SetActive(false);

		if( (*Ite)->GetName() == "Devil" ) {
			(*Ite)->SetUpdateFlg(false);
			for( auto Child = (*Ite)->GetChild()->begin(); Child != (*Ite)->GetChild()->end(); Child ++ )
				(*Child)->SetUpdateFlg(false);
		}
		
		if( (*Ite)->GetName() == "CollisionHardMode" )
			(*Ite)->SetActive(false);

		if( (*Ite)->GetName() == "Wizard" ) {
			(*Ite)->SetUpdateFlg(false);
			for( auto Child = (*Ite)->GetChild()->begin(); Child != (*Ite)->GetChild()->end(); Child ++ )
				(*Child)->SetUpdateFlg(false);
		}
		if( (*Ite)->GetName() == "CollisionEasyMode" )
			(*Ite)->SetActive(false);
	}

#if _DEBUG
	std::cout << "GameClear" << std::endl;
#endif
}

// ������xPlay
void SceneManager::ReInit(){

	// �S�Ẳ���~
	StopSound();
	
	// �j��\�I�u�W�F�N�g��S�j��
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		m_pCreator->DestroyObject( *Ite );
	}

	// �j�󂳂ꂽ�I�u�W�F�N�g�����X�g�������
	m_pCreator->NullObjectErase();
	
	std::vector<GameObject*> ParentList = m_pCreator->FindWithTagAll("Parent");
	for( auto Parent = ParentList.begin(); Parent != ParentList.end(); Parent++ ) {
		for( auto Child = (*Parent)->GetChild()->begin(); Child != (*Parent)->GetChild()->end(); Child++ ) {
			(*Child)->SetActive(false);
			(*Child)->SetCollisionFlg(false);
		}
	}

	// ��U�S�ẴI�u�W�F�N�g��true��
	for( auto Ite = m_pAllObj->begin(); Ite != m_pAllObj->end(); Ite++ ) {
		(*Ite)->SetActive(true);
	}

	// �ď�����
	m_pCreator->Start();

	// ��O
	GameObject* pException = m_pCreator->FindWithName("GameOver");
	if( pException ) {
		*(pException->GetBool()) = true;
	}
	
	pException = m_pCreator->FindWithName("GameClear");
	if( pException ) {
		*(pException->GetBool()) = true;
	}

	pException = m_pCreator->FindWithName("Pause");
	if( pException ) {
		*(pException->GetBool()) = true;
	}

	// �Ă�Menu��
	Menu();
}