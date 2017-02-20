//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CAnimationMeshDrawer.cpp]
// author : �哴�ˑ�
// 
// �ǂݍ��񂾃A�j���[�V�������b�V����`�悷��
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "AnimationMeshDrawer.h"

// --- ���O��� 
namespace SkinMesh {

CAnimationMeshDrawer::CAnimationMeshDrawer () {

}

CAnimationMeshDrawer::~CAnimationMeshDrawer () {

}

void CAnimationMeshDrawer::Draw ( TMyD3DXFRAME* pRootFrame, LPDIRECT3DDEVICE9 pDevice ) {
	DrawFrame( pDevice, pRootFrame);
}

// �t���[���̕`��
void CAnimationMeshDrawer::DrawFrame ( LPDIRECT3DDEVICE9 pDevice, TMyD3DXFRAME* pFrame ) {

	TMyD3DXMESHCONTAINER*	pMeshContainer = (TMyD3DXMESHCONTAINER*)pFrame->pMeshContainer;

	// ���b�V���R���e�i������ꍇ�`��
	while ( pMeshContainer ) {
		// ���b�V���R���e�i�̕`��
		DrawMeshContainer( pDevice, pFrame, pMeshContainer );

		// ����
		pMeshContainer = (TMyD3DXMESHCONTAINER*)pMeshContainer->pNextMeshContainer;
	}

	// �Z��t���[���̕`��
	if ( pFrame->pFrameSibling ) {
		DrawFrame( pDevice, (TMyD3DXFRAME*)pFrame->pFrameSibling );
	}

	// �q�t���[���̕`��
	if ( pFrame->pFrameFirstChild ) {
		DrawFrame( pDevice, (TMyD3DXFRAME*)pFrame->pFrameFirstChild );
	}
}

// ���b�V���R���e�i�̕`��
void CAnimationMeshDrawer::DrawMeshContainer( LPDIRECT3DDEVICE9 pDevice, TMyD3DXFRAME* pFrame, TMyD3DXMESHCONTAINER* pMeshContainer ) {

	// �X�L�����b�V���L��
	DWORD dwBoneID = 0 - 1;
	LPD3DXBONECOMBINATION pBoneComb = (LPD3DXBONECOMBINATION)pMeshContainer->pBoneComb->GetBufferPointer();
	for ( DWORD i = 0; i < pMeshContainer->dwBoneNum; i++ ) {
		DWORD dwMatrixNum = 0;
		for ( DWORD j = 0; j < pMeshContainer->dwBoneWeight; j++ ) {
			if ( pBoneComb[i].BoneId[j] != UINT_MAX ) {
					dwMatrixNum = j;
			}
		}

		pDevice->SetRenderState( D3DRS_VERTEXBLEND, dwMatrixNum);
		for ( DWORD j = 0; j < pMeshContainer->dwBoneWeight; j++ ) {
			DWORD mtxIndex = pBoneComb[i].BoneId[j];
			if ( mtxIndex != UINT_MAX ) {
				D3DXMATRIX mtx;
				D3DXMatrixMultiply( &mtx, &pMeshContainer->pMtxOffset[mtxIndex],
					pMeshContainer->ppMtxBone[mtxIndex]);
				pDevice->SetTransform( D3DTS_WORLDMATRIX(j), &mtx );
			}
		}
		pDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[i].AttribId].MatD3D );
		pDevice->SetTexture( 0, pMeshContainer->ppTexture[pBoneComb[i].AttribId] );
		dwBoneID = pBoneComb[i].AttribId;
		pMeshContainer->MeshData.pMesh->DrawSubset(i);
	}
}

}