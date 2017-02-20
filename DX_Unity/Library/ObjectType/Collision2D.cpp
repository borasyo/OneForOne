//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Collision2D.cpp]
// author : �哴�ˑ�
//
// ��GetCollisionCubePlusSize�͍�����W�n�ɂ����鎲�̃v���X�̌����̑傫��
// ��GetCollisionCubeMinusSize�͍�����W�n�ɂ����鎲�̃}�C�i�X�̌����̑傫��
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Collision2D.h"

// �_�Ɠ_
bool Collision2D::CollisionPointandPoint( GameObject* pPoint, GameObject* pPoint2 ) {

	if( *(pPoint->GetPosition()) == *(pPoint2->GetPosition()) )
		return true;

	return false;
}

// �_�Ɖ~
bool Collision2D::CollisionPointandCircle( GameObject* pPoint, GameObject* pCircle ){
	
	float fDistanceX = pCircle->GetPosition()->x - pPoint->GetPosition()->x;
	float fDistanceY = pCircle->GetPosition()->y - pPoint->GetPosition()->y;
	
	// 2�_�Ԃ̋������Q�̃I�u�W�F�N�g�̔��a�̍��v���߂���
	if( sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY ) 
		<= pCircle->GetCollisionCircleSize() )
		return true;
	
	return false;
}

// �~�Ɖ~
bool Collision2D::CollisionCircleandCircle( GameObject* pCircle, GameObject* pCircle2 ){
	
	float fDistanceX = pCircle2->GetPosition()->x - pCircle->GetPosition()->x;
	float fDistanceY = pCircle2->GetPosition()->y - pCircle->GetPosition()->y;

	// 2�_�Ԃ̋������Q�̃I�u�W�F�N�g�̔��a�̍��v���߂���
	if( sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY ) 
		<= pCircle->GetCollisionCircleSize()+pCircle2->GetCollisionCircleSize() )
		return true;
	
	return false;
}

// ���Ɠ_
bool Collision2D::CollisionCubeandPoint( GameObject* pCube, GameObject* pPoint ) {

	// �����ɓ_�����邩
	if( pPoint->GetPosition()->x < pCube->GetPosition()->x+pCube->GetCollisionCubePlusSize().x  &&
		pPoint->GetPosition()->x > pCube->GetPosition()->x+pCube->GetCollisionCubeMinusSize().x && 
		pPoint->GetPosition()->y < pCube->GetPosition()->y+pCube->GetCollisionCubePlusSize().y  &&
		pPoint->GetPosition()->y > pCube->GetPosition()->y+pCube->GetCollisionCubeMinusSize().y ) 
	{
		return true;
	}

	return false;
}

// ���Ɣ�
bool Collision2D::CollisionCubeandCube( GameObject* pCube, GameObject* pCube2 ) {
	
	// ���܂�ɉ����I�u�W�F�N�g�͔���O��
	float fDistance;
	float fDistanceX = pCube2->GetPosition()->x - pCube->GetPosition()->x;
	float fDistanceY = pCube2->GetPosition()->y - pCube->GetPosition()->y;
	
	// 2�_�Ԃ̋������Q�̃I�u�W�F�N�g�̔��a�̍��v���߂���(��ł��g���̂ŋ�����ۑ�)
	fDistance = sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY );
	
	if( ( pCube->GetCollisionCubePlusSize().x - pCube2->GetCollisionCubeMinusSize().x >= fDistance ||
		  pCube2->GetCollisionCubePlusSize().x - pCube->GetCollisionCubeMinusSize().x >= fDistance ) && 
		( pCube->GetCollisionCubePlusSize().y - pCube2->GetCollisionCubeMinusSize().y >= fDistance ||
		  pCube2->GetCollisionCubePlusSize().y - pCube->GetCollisionCubeMinusSize().y >= fDistance ) ) {
		return true;
	}
	return false;
}

// ���Ɖ~
bool Collision2D::CollisionCubeandCircle( GameObject* pCube, GameObject* pCircle ) {
	
	// ���܂�ɉ����I�u�W�F�N�g�͔���O��
	float fDistance, fCircleSize = sinf(Pai/4.0f);
	float fDistanceX = pCube->GetPosition()->x - pCircle->GetPosition()->x;
	float fDistanceY = pCube->GetPosition()->y - pCircle->GetPosition()->y;
	
	// 2�_�Ԃ̋������Q�̃I�u�W�F�N�g�̔��a�̍��v���߂���
	fDistance = sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY );
	
	if( ( pCube->GetCollisionCubePlusSize().x - pCircle->GetCollisionCircleSize()*fCircleSize >= fDistance ||
		  pCircle->GetCollisionCircleSize()*fCircleSize - pCube->GetCollisionCubeMinusSize().x >= fDistance ) && 
		( pCube->GetCollisionCubePlusSize().y - pCircle->GetCollisionCircleSize()*fCircleSize >= fDistance ||
		  pCircle->GetCollisionCircleSize()*fCircleSize - pCube->GetCollisionCubeMinusSize().y >= fDistance ) ) {
		return true;
	}

	return false;
}

// OBB��OBB�̓����蔻��
bool Collision2D::CollisionOBBandOBB( GameObject* pObb, GameObject* pObb2 ) {

	// OBB������
	OBB Obb  = SetOBB( pObb  );
	OBB Obb2 = SetOBB( pObb2 );

	// �e�����x�N�g���̊m��
	D3DXVECTOR3 NAe1 = Obb.Vec[0], Ae1 = NAe1 * Obb.Length[0];
	D3DXVECTOR3 NAe2 = Obb.Vec[1], Ae2 = NAe2 * Obb.Length[1];
	D3DXVECTOR3 NAe3 = Obb.Vec[2], Ae3 = NAe3 * Obb.Length[2];
	D3DXVECTOR3 NBe1 = Obb2.Vec[0], Be1 = NBe1 * Obb2.Length[0];
	D3DXVECTOR3 NBe2 = Obb2.Vec[1], Be2 = NBe2 * Obb2.Length[1];
	D3DXVECTOR3 NBe3 = Obb2.Vec[2], Be3 = NBe3 * Obb2.Length[2];
	D3DXVECTOR3 Interval = Obb.Pos - Obb2.Pos;

	// ������ : Ae1
	FLOAT rA = D3DXVec3Length( &Ae1 );
	FLOAT rB = LenSegOnSeparateAxis( &NAe1, &Be1, &Be2, &Be3 );
	FLOAT L = fabs(D3DXVec3Dot( &Interval, &NAe1 ));
	if( L > rA + rB ) 
	   return false; // �Փ˂��Ă��Ȃ�

	// ������ : Ae2
	rA = D3DXVec3Length( &Ae2 );
	rB = LenSegOnSeparateAxis( &NAe2, &Be1, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &NAe2 ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : Ae3
	rA = D3DXVec3Length( &Ae3 );
	rB = LenSegOnSeparateAxis( &NAe3, &Be1, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &NAe3 ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : Be1
	rA = LenSegOnSeparateAxis( &NBe1, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be1 );
	L = fabs(D3DXVec3Dot( &Interval, &NBe1 ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : Be2
	rA = LenSegOnSeparateAxis( &NBe2, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &NBe2 ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : Be3
	rA = LenSegOnSeparateAxis( &NBe3, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &NBe3 ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross( &Cross, &NAe1, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : C12
	D3DXVec3Cross( &Cross, &NAe1, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : C13
	D3DXVec3Cross( &Cross, &NAe1, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : C21
	D3DXVec3Cross( &Cross, &NAe2, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : C22
	D3DXVec3Cross( &Cross, &NAe2, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : C23
	D3DXVec3Cross( &Cross, &NAe2, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : C31
	D3DXVec3Cross( &Cross, &NAe3, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : C32
	D3DXVec3Cross( &Cross, &NAe3, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// ������ : C33
	D3DXVec3Cross( &Cross, &NAe3, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB )
	   return false; // �Փ˂��Ă��Ȃ�
	
	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}


// �������ɓ��e���ꂽ���������瓊�e���������Z�o
FLOAT Collision2D::LenSegOnSeparateAxis( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 )
{
   // 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
   // ������Sep�͕W��������Ă��邱��
   FLOAT r1 = fabs(D3DXVec3Dot( Sep, e1 ));
   FLOAT r2 = fabs(D3DXVec3Dot( Sep, e2 ));
   FLOAT r3 = e3 ? (fabs(D3DXVec3Dot( Sep, e3 ))) : 0;
   return r1 + r2 + r3;
}	

// OBB�ɕK�v�ȏ����Z�b�g
OBB Collision2D::SetOBB( GameObject* pObb ) {
	
	// �ϐ��錾
    D3DXMATRIX matRot;
	OBB SetOBB;

    // ���S�_�擾
	SetOBB.Pos = *(pObb->GetPosition());

    // �����x�N�g���擾
	D3DXMatrixRotationYawPitchRoll(&matRot, pObb->GetRotation()->y, pObb->GetRotation()->x, pObb->GetRotation()->z);
	SetOBB.Vec[0] = D3DXVECTOR3(matRot._11,matRot._12,matRot._13);
    SetOBB.Vec[1] = D3DXVECTOR3(matRot._21,matRot._22,matRot._23);
    SetOBB.Vec[2] = D3DXVECTOR3(matRot._31,matRot._32,matRot._33);

    // �����擾
	D3DXVECTOR3 pPlusSize = pObb->GetCollisionCubePlusSize();
	D3DXVECTOR3 pMinusSize = pObb->GetCollisionCubeMinusSize();
	SetOBB.Length.x = (pPlusSize.x - pMinusSize.x) / 2.0f;
	SetOBB.Length.y = (pPlusSize.y - pMinusSize.y) / 2.0f;
	SetOBB.Length.z = (pPlusSize.z - pMinusSize.z) / 2.0f;

	return SetOBB;
}