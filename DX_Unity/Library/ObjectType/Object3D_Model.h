//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object3D.h]
// author : �哴�ˑ�
// 
// GameObject��3DModel�I�u�W�F�N�g�̏ꍇ�A�������������B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____OBJECT_3D_MODEL_H_____
#define _____OBJECT_3D_MODEL_H_____

#include "d3dx9.h"
#include "../ObjectData/ModelManager.h"
#include "../Task/GameObject.h"
#include "../ObjectData/AnimationController.h"

class CObject3DModel {

private:
	LPCWSTR m_FileName;
	D3DXMATRIXA16 mtxWorld;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	CModelManager* m_pModelManager;
	CAnimationController m_AnimationManager;
	float m_fAnimSpeed;
	bool m_bAnim;

public:
	CObject3DModel();
	virtual ~CObject3DModel();
	
	void Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const D3DXVECTOR3 Rot, const bool bShadow = false );
	const LPCWSTR GetFileName();
	void SetFileName( const LPCWSTR& filename );
	void SetMaterialColor( const D3DXCOLOR Color );

	// �A�j���[�V��������̎��̂ݎg��
	bool UpdateAnim();
	void SetAnimationController();
	void SetAnimSpeed( const float fAnimSpeed );
	void SetAnimFlg( const bool bFlg );
	CAnimationController* GetAnimationManager();
};

#endif