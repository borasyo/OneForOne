//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/
//
// [GameClearFogParent.cpp]
// author : �哴�ˑ�
//
// �EStart�֐��ň������K�v�ȏꍇ�́A������_�E���L���X�g���āA�ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/

#include "GameClearFogParent.h"
#include "GameClearCamera.h"

GameClearFogParent::GameClearFogParent() {
	m_Name = "GameClearFogParent";
	m_Tag = "Parent";
	m_bCollision = false;
}

GameClearFogParent::~GameClearFogParent() {
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		(*Ite)->Clear();	
		delete *Ite;
	}
	m_Child.erase(m_Child.begin(),m_Child.end());
	GameClearFogChild.erase(GameClearFogChild.begin(),GameClearFogChild.end());
}

// 
GameObject* GameClearFogParent::CreateChild(){

	auto Ite = GameClearFogChild.begin();
	for( ; Ite != GameClearFogChild.end(); Ite++ ) {

		// ���g���Ă��Ȃ���
		if( (*Ite)->GetActive() )
			continue;

		// �g���ĂȂ������������̂ōĎg�p
		(*Ite)->Start();

		break;
	}
	// �g�̗]�肪�Ȃ��̂Ŏd���Ȃ�new����
	if( Ite == GameClearFogChild.end() ) {
		GameClearFog* pObj = new GameClearFog;
		pObj->SetParent(this);
		GameClearFogChild.push_back(pObj);
		pObj->Start();
		
#if _DEBUG
		std::cout << "GameClearFog" << GameClearFogChild.size() << std::endl;
#endif
		
		return pObj;
	}

	return *Ite;
}

bool GameClearFogParent::Start(){
	m_nCnt = 0;
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;
		
		(*Ite)->SetActive(false);
		(*Ite)->SetCollisionFlg(false);
	}

	return true;
}

// �X�V�`��
void GameClearFogParent::Update(){
	
	// ���̃I�u�W�F�N�g��Active�̎�Fog�𐶐�����
	m_nCnt++;
	if( m_nCnt < 420 ) {
	
		for( int i = 0; i < 2; i++) {
			// Fog�쐬
			GameObject* pFog = CreateChild();
			pFog->ReInit();
			*(pFog->GetPosition()) = m_Position;
			pFog->GetPosition()->y = 0.0f;
			*(pFog->GetRotation()) = m_Rotation;

			float fSize = (float)m_nCnt/10.0f;
			if( fSize < 8.0f ) {
				fSize = 8.0f;
			}
			*(pFog->GetScale()) = D3DXVECTOR3( fSize, fSize, fSize );
			pFog->Start();
		}
	}
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			continue;
		}

		(*Ite)->Update();
	}
}

void GameClearFogParent::Draw(){
	
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ ) {
		if( !(*Ite)->GetActive() )
			continue;

		if( (*Ite)->GetLife() == 0 ) {
			(*Ite)->SetActive(false);
			(*Ite)->SetCollisionFlg(false);
			continue;
		}

		(*Ite)->Draw();
	}
}
