//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FieldCollision.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FieldCollision.h"

const float fRivision = 0.5f;

FieldCollision::FieldCollision() {
	m_Name = "FieldCollision";
	m_pHierarchy = Hierarchy::Create();
}

FieldCollision::~FieldCollision() {
	
}

bool FieldCollision::Start() {

	return true;
}

void FieldCollision::LateUpdate(){
	
	// プレイヤー取得
	GameObject* pPlayer = m_pHierarchy->FindWithName("Player");
	GameObject* pField = m_pHierarchy->FindWithTag("Field");
	GameObject* pPlayerCamera = m_pHierarchy->FindWithName("PlayerCamera");
	
	// ---- プレイヤーとフィールドの当たり判定
	// ---- 当たっていなければフィールド外と判定
	if( pPlayer && pField && !m_Collision.CollisionPointandCircle( pPlayer, pField ) ) {
		
		// とりあえずX軸戻してみる
		pPlayer->ReturnMoveX();
		if( m_Collision.CollisionPointandCircle( pPlayer, pField ) )
			return; // 範囲内に戻せたのでZ軸はオーバーしていない

		// まだ範囲外なのでZ軸は確実にオーバーしているので戻す
		else {

			// Z軸戻す
			pPlayer->ReturnMoveZ();

			// もしかしたらZ軸がオーバーしていただけでX軸はオーバーしていないかも知れない
			pPlayer->Move( D3DXVECTOR3( pPlayer->GetMoveAmount()->x, 0, 0 ) );

			// 判定は？
			if( !m_Collision.CollisionPointandCircle( pPlayer, pField ) )
				pPlayer->ReturnMoveX(); // やっぱりX軸もオーバーしていた
		}
		pPlayer->Move( D3DXVECTOR3(0,0,0) );
	}

	// ---- フィールドとカメラとの当たり判定
	if( pPlayerCamera && pField ) {

		if( !m_Collision.CollisionPointandCircle( pPlayerCamera, pField ) ) {
			*(pPlayerCamera->GetFloat()) -= 0.4f;
		}
		/*else if( *(pPlayerCamera->GetFloat()) > 0.0f ) {
			*(pPlayerCamera->GetFloat()) -= 0.5f;
		}*/
	}
}