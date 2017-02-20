//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CD3DXAllocateHierarchy.h]
// author : �哴�ˑ�
// 
// ID3DXAllocateHierarchy�̔h���N���X
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

// --- ���O���
namespace SkinMesh {

// D3DXFRAME�̊g���\����
struct TMyD3DXFRAME
	: public D3DXFRAME
{
	D3DXMATRIX	mtxWorld;
};

// D3DXMESHCONTAINER�̊g���\����
struct TMyD3DXMESHCONTAINER
	: public D3DXMESHCONTAINER 
{
	
	D3DXMATERIAL* pMaterials;
	// �{�[���������Ă�悤�Ɋg��
	DWORD					dwBoneWeight;	// �{�[���̏d��
	DWORD					dwBoneNum;		// �{�[���̐�
	LPD3DXBUFFER			pBoneComb;		// �{�[���R���r�l�[�V�����z��
	D3DXMATRIX**			ppMtxBone;		// �{�[���s��z��
	LPDIRECT3DTEXTURE9*		ppTexture;		// �e�N�X�`��
	D3DXMATRIX*				pMtxOffset;		// �{�[���s��
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

	// �{�[������
	void CreateBone ( TMyD3DXFRAME* pFrame, const D3DXFRAME* pRootFrame);

	// �t���[���I�u�W�F�N�g�̍폜
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);

	// ���b�V���R���e�i�̍폜
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

private:
	void CopyMeshData ( LPD3DXMESHDATA pDst, const LPD3DXMESHDATA pSrc);

	void CreateBoneMatrix( TMyD3DXMESHCONTAINER* pMeshContainer, const D3DXFRAME* pRootFrame);
};

}

#endif