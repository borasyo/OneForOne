//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Player.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____PLAYER_H_____
#define _____PLAYER_H_____

#include <iostream>
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"
#include "../Library/DirectX/DirectInputManager.h"

#include <time.h>
#include "../Library/Task/Hierarchy.h"
#include "PlayerFogParent.h"
#include "BulletFogParent.h"

// --- ’è”
const float fInitRot = 0.15f;
const float fMagnification = 1.5f;
const float fMaxDeathblowGauge = 100.0f;
const float fDeathblowTime = 3600.0f;
const float fUpGauge = (fMaxDeathblowGauge/fDeathblowTime)*2.0f; // “G‚Éƒ_ƒ[ƒW‚ð—^‚¦‚½‚Æ‚«‚ÌGauge‘‰Á—Ê

class Player : public GameObject {

private:
	CDirectInputManager* m_pDirectInputManager;
	int m_nChangeCnt;
	int m_nItemCnt;
	bool m_bNearAtack;
	bool m_bDeathblow;
	bool m_bChange;
	bool m_bAtack;
	bool m_bGaugeMax;
	bool m_bPause;
	float m_fMaxRot;
	float m_fMove;
	float m_fDeathblowGauge;
	Hierarchy* m_pHierarchy;
	GameObject* m_pPlayerFogParent;
	BulletFogParent* m_pBulletFogParent;

	// ‰ñ”ð
	bool m_bAvoid;
	int m_nAvoidTime;
	D3DXVECTOR3 m_AvoidAmount;

	int m_nReverberation;
	int m_nOldLife;
	int m_nAccumulationDamage;
	
	GameObject* m_pCamera;
	GameObject* m_pCameraSelect;

	bool CharaMove();
	void Atack();
	void Change();
	void CreateFog();
	void CreateDeathblow();
	void AvoidMove();

public:
	// ObjectType
	CObject3DModel m_Object3D;

	Player();
	~Player();

	void Awake();
	void Update();
	void FastDraw();
	void Draw();
	float* GetFloat();
	bool* GetBool();
	int * GetInt();
	
	bool GetNearAtackFlg();
	
	Player* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		Player* Child = static_cast<Player*>(Obj); 
		return Child;
	}
};

#endif