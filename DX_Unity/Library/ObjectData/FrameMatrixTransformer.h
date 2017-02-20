//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CFrameMatrixTransformer.h]
// author : 大洞祥太
// 
// 個々のフレームが持っているワールド行列の変換
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef __CFRAMEMATRIXTRANSFORMER_IG__
#define __CFRAMEMATRIXTRANSFORMER_IG__

#include <stack>
#include <list>
#include "d3dx9.h"
#include "D3DXAllocateHierarchy.h"
#include <string>
#include <tchar.h>

// -- 名前空間
namespace SkinMesh {

class IFrameMatrixTransformer {
public:
	virtual ~IFrameMatrixTransformer(void){}
	virtual void Run ( TMyD3DXFRAME* frame, const D3DXMATRIX* pMtxWorld) = 0;
};

class CFrameMatrixTransformer 
	: public IFrameMatrixTransformer {
protected:
	std::stack<D3DXMATRIX*>		m_mtxStack;			// 変換用行列スタック

public:
	CFrameMatrixTransformer ();

	~CFrameMatrixTransformer ();

	virtual void Run ( TMyD3DXFRAME* pRootFrame, const D3DXMATRIX* pMtxWorld) override;

protected:
	// ワールド行列の計算
	 void CreateWorldMatrix ( TMyD3DXFRAME* pFrame);

};

}

#endif