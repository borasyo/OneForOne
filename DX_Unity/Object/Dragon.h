//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Dragon.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Dragon_H_____
#define _____Dragon_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object3D_Model.h"
#include "../Object/BulletFogParent.h"

class Dragon : public GameObject {

private:
	Hierarchy* m_pHierarchy;
	bool m_bStart;
	bool m_bAtack;
	bool m_bContact;
	D3DXVECTOR3 m_Move;
	int m_nAtackValue;
	float m_fInitPos;
	float m_fAtackLevel;
	D3DXVECTOR3 m_fReturnPos;
	
	// -- 攻撃カウント
	int m_nAssaultCnt;
	int m_nFireCnt;
	int m_nAtackCnt;

	float m_fBezTime;
	float m_fBezSpeed;
	D3DXVECTOR3 m_Bez0,m_Bez1,m_Bez2;

	// 必要オブジェクト
	GameObject* m_pPlayer;
	GameObject* m_pBoss;
	GameObject* m_pFireParent;
	BulletFogParent* m_pBulletFogParent;
	
	void CheckAtack();
	float Vector(D3DXVECTOR3,D3DXVECTOR3);
	D3DXVECTOR3 Random();

	// -- 各攻撃処理
	void AssaultAtack();
	void FireAtack();

	void DownCount();

public:
	// ObjectType
	CObject3DModel m_Object3D;

	Dragon();
	~Dragon();

	bool Start( float fAtackLevel );
	void Update();
	void FastDraw();
	
	bool* GetBool();

	Dragon* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // 失敗!!!
			return nullptr;

		Dragon* Child = static_cast<Dragon*>(Obj); 
		return Child;
	}
};

#endif