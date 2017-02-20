//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CFrameMatrixTransformer.h]
// author : �哴�ˑ�
// 
// �X�̃t���[���������Ă��郏�[���h�s��̕ϊ�
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

// -- ���O���
namespace SkinMesh {

class IFrameMatrixTransformer {
public:
	virtual ~IFrameMatrixTransformer(void){}
	virtual void Run ( TMyD3DXFRAME* frame, const D3DXMATRIX* pMtxWorld) = 0;
};

class CFrameMatrixTransformer 
	: public IFrameMatrixTransformer {
protected:
	std::stack<D3DXMATRIX*>		m_mtxStack;			// �ϊ��p�s��X�^�b�N

public:
	CFrameMatrixTransformer ();

	~CFrameMatrixTransformer ();

	virtual void Run ( TMyD3DXFRAME* pRootFrame, const D3DXMATRIX* pMtxWorld) override;

protected:
	// ���[���h�s��̌v�Z
	 void CreateWorldMatrix ( TMyD3DXFRAME* pFrame);

};

}

#endif