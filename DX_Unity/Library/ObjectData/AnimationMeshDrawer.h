//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CAnimationMeshDrawer.h]
// author : 大洞祥太
// 
// 読み込んだアニメーションメッシュを描画する
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

// ---- 名前空間
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
	// フレームの描画(再帰)
	void DrawFrame ( LPDIRECT3DDEVICE9 pDevice, TMyD3DXFRAME* pFrame);

	// 描画
	void DrawMeshContainer ( LPDIRECT3DDEVICE9 pDevice, TMyD3DXFRAME* pFrame, TMyD3DXMESHCONTAINER* pMeshContainer);
};

}
#endif