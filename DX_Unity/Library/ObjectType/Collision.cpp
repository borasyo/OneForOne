//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Collision.cpp]
// author : 大洞祥太
//
// ※GetCollisionCubePlusSizeは左手座標系における軸のプラスの向きの大きさ
// ※GetCollisionCubeMinusSizeは左手座標系における軸のマイナスの向きの大きさ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Collision.h"

// -- 定数
const float fOutRange = 3.0f; // 判定外にする範囲
//const int nMaxBlood = 3;

// 点と点
bool Collision::CollisionPointandPoint( GameObject* pPoint, GameObject* pPoint2 ) {

	if( *(pPoint->GetPosition()) == *(pPoint2->GetPosition()) )
		return true;

	return false;
}

// 点と円
bool Collision::CollisionPointandCircle( GameObject* pPoint, GameObject* pCircle ){
	
	float fDistanceX = pCircle->GetPosition()->x - pPoint->GetPosition()->x;
	float fDistanceY = pCircle->GetPosition()->y - pPoint->GetPosition()->y;
	float fDistanceZ = pCircle->GetPosition()->z - pPoint->GetPosition()->z;
	
	// 2点間の距離が２つのオブジェクトの半径の合計より近いか
	if( sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ ) 
		<= pCircle->GetCollisionCircleSize() )
		return true;
	
	return false;
}

// 円と円
bool Collision::CollisionCircleandCircle( GameObject* pCircle, GameObject* pCircle2 ){
	
	float fDistanceX = pCircle2->GetPosition()->x - pCircle->GetPosition()->x;
	float fDistanceY = pCircle2->GetPosition()->y - pCircle->GetPosition()->y;
	float fDistanceZ = pCircle2->GetPosition()->z - pCircle->GetPosition()->z;

	// 2点間の距離が２つのオブジェクトの半径の合計より近いか
	if( sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ ) 
		<= pCircle->GetCollisionCircleSize()+pCircle2->GetCollisionCircleSize() )
		return true;
	
	return false;
}

// 箱と点
bool Collision::CollisionCubeandPoint( GameObject* pCube, GameObject* pPoint ) {
	
	// あまりに遠いオブジェクトは判定外に
	float fDistanceX = pCube->GetPosition()->x - pPoint->GetPosition()->x;
	float fDistanceY = pCube->GetPosition()->y - pPoint->GetPosition()->y;
	float fDistanceZ = pCube->GetPosition()->z - pPoint->GetPosition()->z;
	
	// 2点間の距離が２つのオブジェクトの半径の合計より近いか
	if( sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ ) 
		>= fOutRange )
		return false;

	// 箱内に点があるか
	if( pPoint->GetPosition()->x < pCube->GetPosition()->x+pCube->GetCollisionCubePlusSize().x  &&
		pPoint->GetPosition()->x > pCube->GetPosition()->x+pCube->GetCollisionCubeMinusSize().x && 
		pPoint->GetPosition()->y < pCube->GetPosition()->y+pCube->GetCollisionCubePlusSize().y  &&
		pPoint->GetPosition()->y > pCube->GetPosition()->y+pCube->GetCollisionCubeMinusSize().y && 
		pPoint->GetPosition()->z < pCube->GetPosition()->z+pCube->GetCollisionCubePlusSize().z  &&
		pPoint->GetPosition()->z > pCube->GetPosition()->z+pCube->GetCollisionCubeMinusSize().z ) 
	{
		return true;
	}

	return false;
}

// 箱と箱
bool Collision::CollisionCubeandCube( GameObject* pCube, GameObject* pCube2 ) {
	
	// あまりに遠いオブジェクトは判定外に
	float fDistance;
	float fDistanceX = pCube2->GetPosition()->x - pCube->GetPosition()->x;
	float fDistanceY = pCube2->GetPosition()->y - pCube->GetPosition()->y;
	float fDistanceZ = pCube2->GetPosition()->z - pCube->GetPosition()->z;
	
	// 2点間の距離が２つのオブジェクトの半径の合計より近いか(後でも使うので距離を保存)
	fDistance = sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ );
	if( fDistance >= fOutRange )//fDistanceX+fDistanceY+fDistanceZ )
		return false;
	
	if( ( pCube->GetCollisionCubePlusSize().x - pCube2->GetCollisionCubeMinusSize().x >= fDistance ||
		  pCube2->GetCollisionCubePlusSize().x - pCube->GetCollisionCubeMinusSize().x >= fDistance ) && 
		( pCube->GetCollisionCubePlusSize().y - pCube2->GetCollisionCubeMinusSize().y >= fDistance ||
		  pCube2->GetCollisionCubePlusSize().y - pCube->GetCollisionCubeMinusSize().y >= fDistance ) && 
		( pCube->GetCollisionCubePlusSize().z - pCube2->GetCollisionCubeMinusSize().z >= fDistance ||
		  pCube2->GetCollisionCubePlusSize().z - pCube->GetCollisionCubeMinusSize().z >= fDistance ) ) {
		return true;
	}
	return false;
}

// 箱と円
bool Collision::CollisionCubeandCircle( GameObject* pCube, GameObject* pCircle ) {
	
	// あまりに遠いオブジェクトは判定外に
	float fDistance, fCircleSize = sinf(Pai/4.0f);
	float fDistanceX = pCube->GetPosition()->x - pCircle->GetPosition()->x;
	float fDistanceY = pCube->GetPosition()->y - pCircle->GetPosition()->y;
	float fDistanceZ = pCube->GetPosition()->z - pCircle->GetPosition()->z;
	
	// 2点間の距離が２つのオブジェクトの半径の合計より近いか
	fDistance = sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY + fDistanceZ*fDistanceZ );
	if( fDistance >= fOutRange )
		return false;
	
	if( ( pCube->GetCollisionCubePlusSize().x - pCircle->GetCollisionCircleSize()*fCircleSize >= fDistance ||
		  pCircle->GetCollisionCircleSize()*fCircleSize - pCube->GetCollisionCubeMinusSize().x >= fDistance ) && 
		( pCube->GetCollisionCubePlusSize().y - pCircle->GetCollisionCircleSize()*fCircleSize >= fDistance ||
		  pCircle->GetCollisionCircleSize()*fCircleSize - pCube->GetCollisionCubeMinusSize().y >= fDistance ) && 
		( pCube->GetCollisionCubePlusSize().z - pCircle->GetCollisionCircleSize()*fCircleSize >= fDistance ||
		  pCircle->GetCollisionCircleSize()*fCircleSize - pCube->GetCollisionCubeMinusSize().z >= fDistance ) ) {
		return true;
	}

	return false;
}

// OBBとOBBの当たり判定
bool Collision::CollisionOBBandOBB( GameObject* pObb, GameObject* pObb2 ) {

	// OBBを準備
	OBB Obb  = SetOBB( pObb  );
	OBB Obb2 = SetOBB( pObb2 );

	// 各方向ベクトルの確保
	D3DXVECTOR3 NAe1 = Obb.Vec[0], Ae1 = NAe1 * Obb.Length[0];
	D3DXVECTOR3 NAe2 = Obb.Vec[1], Ae2 = NAe2 * Obb.Length[1];
	D3DXVECTOR3 NAe3 = Obb.Vec[2], Ae3 = NAe3 * Obb.Length[2];
	D3DXVECTOR3 NBe1 = Obb2.Vec[0], Be1 = NBe1 * Obb2.Length[0];
	D3DXVECTOR3 NBe2 = Obb2.Vec[1], Be2 = NBe2 * Obb2.Length[1];
	D3DXVECTOR3 NBe3 = Obb2.Vec[2], Be3 = NBe3 * Obb2.Length[2];
	D3DXVECTOR3 Interval = Obb.Pos - Obb2.Pos;

	// 分離軸 : Ae1
	FLOAT rA = D3DXVec3Length( &Ae1 );
	FLOAT rB = LenSegOnSeparateAxis( &NAe1, &Be1, &Be2, &Be3 );
	FLOAT L = fabs(D3DXVec3Dot( &Interval, &NAe1 ));
	if( L > rA + rB ) 
	   return false; // 衝突していない

	// 分離軸 : Ae2
	rA = D3DXVec3Length( &Ae2 );
	rB = LenSegOnSeparateAxis( &NAe2, &Be1, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &NAe2 ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : Ae3
	rA = D3DXVec3Length( &Ae3 );
	rB = LenSegOnSeparateAxis( &NAe3, &Be1, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &NAe3 ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis( &NBe1, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be1 );
	L = fabs(D3DXVec3Dot( &Interval, &NBe1 ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis( &NBe2, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &NBe2 ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis( &NBe3, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &NBe3 ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross( &Cross, &NAe1, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : C12
	D3DXVec3Cross( &Cross, &NAe1, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : C13
	D3DXVec3Cross( &Cross, &NAe1, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : C21
	D3DXVec3Cross( &Cross, &NAe2, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : C22
	D3DXVec3Cross( &Cross, &NAe2, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : C23
	D3DXVec3Cross( &Cross, &NAe2, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : C31
	D3DXVec3Cross( &Cross, &NAe3, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : C32
	D3DXVec3Cross( &Cross, &NAe3, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離軸 : C33
	D3DXVec3Cross( &Cross, &NAe3, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // 衝突していない
	
	// 分離平面が存在しないので「衝突している」
	return true;
}


// 分離軸に投影された軸成分から投影線分長を算出
FLOAT Collision::LenSegOnSeparateAxis( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 )
{
   // 3つの内積の絶対値の和で投影線分長を計算
   // 分離軸Sepは標準化されていること
   FLOAT r1 = fabs(D3DXVec3Dot( Sep, e1 ));
   FLOAT r2 = fabs(D3DXVec3Dot( Sep, e2 ));
   FLOAT r3 = e3 ? (fabs(D3DXVec3Dot( Sep, e3 ))) : 0;
   return r1 + r2 + r3;
}	

// OBBに必要な情報をセット
OBB Collision::SetOBB( GameObject* pObb ) {
	
	// 変数宣言
    D3DXMATRIX matRot;
	OBB SetOBB;

    // 中心点取得
	SetOBB.Pos = *(pObb->GetPosition());

    // 方向ベクトル取得
	D3DXMatrixRotationYawPitchRoll(&matRot, pObb->GetRotation()->y, pObb->GetRotation()->x, pObb->GetRotation()->z);
	SetOBB.Vec[0] = D3DXVECTOR3(matRot._11,matRot._12,matRot._13);
    SetOBB.Vec[1] = D3DXVECTOR3(matRot._21,matRot._22,matRot._23);
    SetOBB.Vec[2] = D3DXVECTOR3(matRot._31,matRot._32,matRot._33);

    // 長さ取得
	D3DXVECTOR3 pPlusSize = pObb->GetCollisionCubePlusSize();
	D3DXVECTOR3 pMinusSize = pObb->GetCollisionCubeMinusSize();
	SetOBB.Length.x = (pPlusSize.x - pMinusSize.x) / 2.0f;
	SetOBB.Length.y = (pPlusSize.y - pMinusSize.y) / 2.0f;
	SetOBB.Length.z = (pPlusSize.z - pMinusSize.z) / 2.0f;

	return SetOBB;
}