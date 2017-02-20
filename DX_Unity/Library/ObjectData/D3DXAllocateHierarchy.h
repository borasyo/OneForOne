//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CD3DXAllocateHierarchy.h]
// author : 大洞祥太
// 
// ID3DXAllocateHierarchyの派生クラス
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef __CD3DXALLOCATEHIERARCHY_IG__
#define __CD3DXALLOCATEHIERARCHY_IG__

#include "d3dx9.h"
#include <string>
#include <tchar.h>

// --- 名前空間
namespace SkinMesh {

// D3DXFRAMEの拡張構造体
struct TMyD3DXFRAME
	: public D3DXFRAME
{
	D3DXMATRIX	mtxWorld;
};

// D3DXMESHCONTAINERの拡張構造体
struct TMyD3DXMESHCONTAINER
	: public D3DXMESHCONTAINER 
{
	
	D3DXMATERIAL* pMaterials;
	// ボーン情報を持てるように拡張
	DWORD					dwBoneWeight;	// ボーンの重み
	DWORD					dwBoneNum;		// ボーンの数
	LPD3DXBUFFER			pBoneComb;		// ボーンコンビネーション配列
	D3DXMATRIX**			ppMtxBone;		// ボーン行列配列
	LPDIRECT3DTEXTURE9*		ppTexture;		// テクスチャ
	D3DXMATRIX*				pMtxOffset;		// ボーン行列
};

class CD3DXAllocateHierarchy
	: public ID3DXAllocateHierarchy 
{
public:
	CD3DXAllocateHierarchy ();

	virtual ~CD3DXAllocateHierarchy ();

    STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);

    STDMETHOD(CreateMeshContainer)(THIS_ 
        LPCSTR Name, 
        CONST D3DXMESHDATA *pMeshData, 
        CONST D3DXMATERIAL *pMaterials, 
        CONST D3DXEFFECTINSTANCE *pEffectInstances, 
        DWORD NumMaterials, 
        CONST DWORD *pAdjacency, 
        LPD3DXSKININFO pSkinInfo, 
        LPD3DXMESHCONTAINER *ppNewMeshContainer);

	// ボーン生成
	void CreateBone ( TMyD3DXFRAME* pFrame, const D3DXFRAME* pRootFrame);

	// フレームオブジェクトの削除
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);

	// メッシュコンテナの削除
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

private:
	void CopyMeshData ( LPD3DXMESHDATA pDst, const LPD3DXMESHDATA pSrc);

	void CreateBoneMatrix( TMyD3DXMESHCONTAINER* pMeshContainer, const D3DXFRAME* pRootFrame);
};

}

#endif