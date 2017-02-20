//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Item.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Item.h"

const float fInitPos = 30.0f;
const int nTime = 1200;
const float fCollision = 0.85f;

#define RANDOM_POS (rand()%800000*0.001f)

Item::Item() {
	m_Name = "Item";
	m_Object3D.SetFileName( _T("Item.x") );
}

Item::~Item() {
	
}

bool Item::Start(){

	Hierarchy* pHierarchy = Hierarchy::Create();
	GameObject* pPlayer = pHierarchy->FindWithName("Player");
	SetParent( pHierarchy->FindWithName("ItemParent") );

	while(1) {
		switch( rand()%4 ) {
		case 0:
			m_Position.x = pPlayer->GetPosition()->x + RANDOM_POS;
			m_Position.z = pPlayer->GetPosition()->z + RANDOM_POS;
			break;
		case 1:
			m_Position.x = pPlayer->GetPosition()->x - RANDOM_POS;
			m_Position.z = pPlayer->GetPosition()->z + RANDOM_POS;
			break;
		case 2:
			m_Position.x = pPlayer->GetPosition()->x + RANDOM_POS;
			m_Position.z = pPlayer->GetPosition()->z - RANDOM_POS;
			break;
		case 3:
			m_Position.x = pPlayer->GetPosition()->x - RANDOM_POS;
			m_Position.z = pPlayer->GetPosition()->z - RANDOM_POS;
			break;
		}

		// Bossの足元過ぎないかをチェック
		float fLimit = 15.0f;
		if( (m_Position.x > fLimit || m_Position.x < -fLimit) && (m_Position.z > fLimit || m_Position.z < -fLimit) )
			break;
	}
	m_Position.y = fInitPos;
	m_Rotation.y = rand()%628 * 0.01f;
		
	// 範囲外処理
	if( LimitPos.x < m_Position.x )
		m_Position.x = LimitPos.x;
	else if( -LimitPos.x > m_Position.x )
		m_Position.x = -LimitPos.x;
	if( LimitPos.z < m_Position.z )
		m_Position.z = LimitPos.z;
	else if( -LimitPos.z > m_Position.z )
		m_Position.z = -LimitPos.z;

	// コリジョン
	SetCollisionCubeSize( D3DXVECTOR3(fCollision,1.5f,fCollision), D3DXVECTOR3(fCollision,1.5f,fCollision) );

	// 大きさ
	ScaleChange( D3DXVECTOR3(0.75f,0.75f,0.75f) );

	return true;
}

void Item::Update(){
	
	// 落ちてくる
	if( m_Position.y > fInitPos-30.0f ) {
		Move( D3DXVECTOR3( 0, -0.25f, 0 ) );
		Rotation( D3DXVECTOR3( Pai*4.0f/120.0f, 0, 0 ) );
	} else {
		// 徐々に小さく
		ScaleChange( D3DXVECTOR3( -1.0f/nTime, -1.0f/nTime, -1.0f/nTime ) );

		if( m_Scale.x <= 0.75f ) {
			m_nLife = 0; // 消滅
		}
	}
}

void Item::Draw(){
	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}