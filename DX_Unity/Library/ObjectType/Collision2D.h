//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Collision2D.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Collision2D_H_____
#define _____Collision2D_H_____

#include "../Task/GameObject.h"

// --- 構造体
struct OBB{
    D3DXVECTOR3 Pos;	//中心点の座標
    D3DXVECTOR3 Vec[3];	//XYZ の各座標軸の傾きを表す方向ベクトル
    D3DXVECTOR3 Length;	//OBB の各座標軸に沿った長さの半分（中心点から面までの長さ）
};

class Collision2D {

public:
	// ---- 当たり判定関数(箱、円、点の3種類)
	bool CollisionCubeandCube( GameObject* pCube, GameObject* pCube2 );			// CubeとCubeで当たり判定
	bool CollisionCubeandPoint( GameObject* pCube, GameObject* pPoint );		// CubeとPointで当たり判定
	bool CollisionCubeandCircle( GameObject* pCube, GameObject* pCircle );		// CubeとCircleで当たり判定
	bool CollisionPointandPoint( GameObject* pPoint, GameObject* pPoint2 );		// PointとPointで当たり判定
	bool CollisionPointandCircle( GameObject* pPoint, GameObject* pCircle );	// PointとCircleで当たり判定
	bool CollisionCircleandCircle( GameObject* pCircle, GameObject* pCircle2 );	// CircleとCircleで当たり判定
	bool CollisionOBBandOBB( GameObject* pObb, GameObject* pObb2 );				// OBBとOBBで当たり判定

	// OBBに必要な関数
	OBB SetOBB( GameObject* pObb );
	FLOAT LenSegOnSeparateAxis( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0 );

};

#endif