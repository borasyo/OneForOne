//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Collision2D.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Collision2D_H_____
#define _____Collision2D_H_____

#include "../Task/GameObject.h"

// --- �\����
struct OBB{
    D3DXVECTOR3 Pos;	//���S�_�̍��W
    D3DXVECTOR3 Vec[3];	//XYZ �̊e���W���̌X����\�������x�N�g��
    D3DXVECTOR3 Length;	//OBB �̊e���W���ɉ����������̔����i���S�_����ʂ܂ł̒����j
};

class Collision2D {

public:
	// ---- �����蔻��֐�(���A�~�A�_��3���)
	bool CollisionCubeandCube( GameObject* pCube, GameObject* pCube2 );			// Cube��Cube�œ����蔻��
	bool CollisionCubeandPoint( GameObject* pCube, GameObject* pPoint );		// Cube��Point�œ����蔻��
	bool CollisionCubeandCircle( GameObject* pCube, GameObject* pCircle );		// Cube��Circle�œ����蔻��
	bool CollisionPointandPoint( GameObject* pPoint, GameObject* pPoint2 );		// Point��Point�œ����蔻��
	bool CollisionPointandCircle( GameObject* pPoint, GameObject* pCircle );	// Point��Circle�œ����蔻��
	bool CollisionCircleandCircle( GameObject* pCircle, GameObject* pCircle2 );	// Circle��Circle�œ����蔻��
	bool CollisionOBBandOBB( GameObject* pObb, GameObject* pObb2 );				// OBB��OBB�œ����蔻��

	// OBB�ɕK�v�Ȋ֐�
	OBB SetOBB( GameObject* pObb );
	FLOAT LenSegOnSeparateAxis( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0 );

};

#endif