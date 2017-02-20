//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Model.h]
// author : 大洞祥太
// 
// モデルを読み込みそのデータを保持する
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MODEL_H_____
#define _____MODEL_H_____

#include <map>
#include "d3dx9.h"
#include <string>
#include <tchar.h>
#include "D3DXAllocateHierarchy.h"
#include "FrameMatrixTransformer.h"
#include "AnimationMeshDrawer.h"

// 1モデルに必要な情報
class CModel {

public:
	CModel();
	~CModel();

	// 3Dモデル関係
	bool LoadModel( const std::wstring& filename );
	void RenderModel( const D3DXMATRIXA16* pMtx, const bool bShadow );
	void Uninit();
	void SetMaterialColor( const D3DXCOLOR Color );
	LPD3DXANIMATIONCONTROLLER GetMainAnimationController();

private:

	// アニメーションなし
	LPD3DXMESH			m_Mesh;
	D3DMATERIAL9*		m_Materials;
	LPDIRECT3DTEXTURE9* m_Textures;
	DWORD				m_NumMaterials;
	LPDIRECT3DDEVICE9   m_pD3DDevice;
	D3DXATTRIBUTERANGE*	m_pAttr;	// 属性テーブル
	DWORD				m_dwAttr;	// 属性数
	
	// アニメーションあり
	SkinMesh::TMyD3DXFRAME*	m_pRootFrame;
	SkinMesh::CD3DXAllocateHierarchy m_Allocater;
	SkinMesh::CAnimationMeshDrawer m_AMDrawer;
	SkinMesh::CFrameMatrixTransformer m_FMTransformer;
	LPD3DXANIMATIONCONTROLLER m_pMainAnimationController;
	
	void SetModel();
	void DrawShadow();
};

#endif