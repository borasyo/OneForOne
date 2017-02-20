//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Blood.cpp]
// author : 大洞祥太
//
// 血の出る位置は要調整。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Blood.h"

// -- 定数
const float fGravity = 0.0245f;

// -- マクロ
#define DEFLECTION ((rand()%30)*0.1f)
#define FLY (rand()%5*0.1f)

bool Blood::Start(D3DXVECTOR3 MyselfPos, D3DXVECTOR3 OpponentPos) {
	
	// 初期化
	ReInit();
	m_bGrounded = false;
	m_bCollision = false;

	m_Move = (MyselfPos - OpponentPos)/6.0f;
	m_Move.x *= DEFLECTION; // 若干のずれを入れる
	m_Move.y += FLY;
	m_Move.z *= DEFLECTION; // 若干のずれを入れる
	m_Position = OpponentPos; // 自分の出る位置を格納

	// ライフ設定
	SetLife(90);

	return true;
}

void Blood::Update(){

	if( !m_bGrounded ) {
		Move(m_Move); // 移動
		m_Move.y -= fGravity; // 重力補正
	} 

	// 地面に着いたら
	if( m_Position.y <= 0 ) {
		m_Position.y = 0;
		m_bGrounded = true;
	}
	
	// ライフ減らす
	SetLife(-1);
}

void Blood::Draw(){
	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
}