//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ObjectCamera.h]
// author : �哴�ˑ�
//
// GameObject��Camera�I�u�W�F�N�g�̏ꍇ�A�������������B
// 
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____OBJECT_CAMERA_H_____
#define _____OBJECT_CAMERA_H_____

#include"d3dx9.h"

class CObjectCamera {

private:
	D3DXVECTOR3 m_LookatPt;	// �����_���W
	D3DXVECTOR3 m_UpVec;	// ������x�N�g��
	D3DVIEWPORT9 m_ViewPort;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	CObjectCamera();
	~CObjectCamera();

	void Set(D3DXVECTOR3 pos); // �J�����̃Z�b�g
	void SetViewPort( D3DVIEWPORT9 ViewPort );

	// ---- �Q�b�^�[�֐�
	D3DXVECTOR3* GetLookatPt();	// �����_���擾
	D3DXVECTOR3* GetUpVec();	// �@�����擾
};

#endif