//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [PlayerUI.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____PlayerUI_H_____
#define _____PlayerUI_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class PlayerUI : public GameObject {

private:
	Hierarchy* m_pHierarchy;
	GameObject* m_pPlayer;
	int m_nMaxLife;

public:
	// ObjectType
	CObject2D m_GaugeDecoration;
	CObject2D m_HPGauge;
	CObject2D m_DeathblowGauge;
	
	D3DXVECTOR3 m_HPGaugePos;
	D3DXVECTOR3 m_HPGaugeScale;
	D3DXVECTOR3 m_DeathblowGaugePos;
	D3DXVECTOR3 m_DeathblowGaugeScale;

	PlayerUI();
	~PlayerUI();

	bool Start();
	void Update();
	void LateDraw();
	
	PlayerUI* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		PlayerUI* Child = static_cast<PlayerUI*>(Obj); 
		return Child;
	}
};

#endif