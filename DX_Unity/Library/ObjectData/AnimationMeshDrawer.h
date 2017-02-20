//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CAnimationMeshDrawer.h]
// author : �哴�ˑ�
// 
// �ǂݍ��񂾃A�j���[�V�������b�V����`�悷��
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef __CANIMATIONMESHDRAWER_IG__
#define __CANIMATIONMESHDRAWER_IG__

#include "d3dx9.h"
#include "D3DXAllocateHierarchy.h"
#include <string>
#include <tchar.h>

// ---- ���O���
namespace SkinMesh {

class IAnimationMeshDrawer {
public:
	virtual ~IAnimationMeshDrawer () {}
	virtual void Draw ( TMyD3DXFRAME* pFrame, LPDIRECT3DDEVICE9 pDevice) = 0;
};

class CAnimationMeshDrawer 
	: public IAnimationMeshDrawer {
public:
	CAnimationMeshDrawer();
	~CAnimationMeshDrawer();

	void Draw ( TMyD3DXFRAME* pFrame, LPDIRECT3DDEVICE9 pDevice) override;

private:
	// �t���[���̕`��(�ċA)
	void DrawFrame ( LPDIRECT3DDEVICE9 pDevice, TMyD3DXFRAME* pFrame);

	// �`��
	void DrawMeshContainer ( LPDIRECT3DDEVICE9 pDevice, TMyD3DXFRAME* pFrame, TMyD3DXMESHCONTAINER* pMeshContainer);
};

}
#endif