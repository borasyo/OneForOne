//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CD3DXAllocateHierarchy.cpp]
// author : �哴�ˑ�
// 
// ID3DXAllocateHierarchy�̔h���N���X
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "D3DXAllocateHierarchy.h"
#include <iostream>

// --- ���O���
namespace SkinMesh {

CD3DXAllocateHierarchy::CD3DXAllocateHierarchy () {}

CD3DXAllocateHierarchy::~CD3DXAllocateHierarchy () {}

// �t���[���I�u�W�F�N�g�̐���
HRESULT CD3DXAllocateHierarchy::CreateFrame( THIS_ LPCSTR Name, LPD3DXFRAME* ppNewFrame ) {

	// ���O����܂���
	if ( !Name ) {
		return E_FAIL;
	}
	// �t���[���I�u�W�F�N�g�̐���
	// ���ꂪ�߂�l�ɂȂ�
	// �g���N���X�𗘗p
	TMyD3DXFRAME*	pFrame = nullptr;
	pFrame = new TMyD3DXFRAME;
	if ( !pFrame ) return E_OUTOFMEMORY;

	// ���O�̃Z�b�g
	pFrame->Name = nullptr;
	pFrame->Name = new char[strlen(Name) + 1];
	if ( pFrame->Name == 0 ) return E_OUTOFMEMORY;
	strcpy( pFrame->Name, Name);

	// �����s��̏�����
	D3DXMatrixIdentity( &pFrame->TransformationMatrix);
	D3DXMatrixIdentity( &pFrame->mtxWorld);

	// �����|�C���^�̏�����
	pFrame->pMeshContainer		= nullptr; // ���b�V���R���e�i
	pFrame->pFrameSibling		= nullptr; // �Z��t���[��
	pFrame->pFrameFirstChild	= nullptr; // �q�t���[��

	// �߂�l�ɑ��
	*ppNewFrame = pFrame;

	// ��Еt��
	pFrame = nullptr;

	return S_OK;
}

// ���b�V���R���e�i�̐���
HRESULT CD3DXAllocateHierarchy::CreateMeshContainer(THIS_ 
        LPCSTR Name, 
        CONST D3DXMESHDATA *pMeshData, 
        CONST D3DXMATERIAL *pMaterials, 
        CONST D3DXEFFECTINSTANCE *pEffectInstances, 
        DWORD NumMaterials, 
        CONST DWORD *pAdjacency, 
        LPD3DXSKININFO pSkinInfo, 
        LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	// ���b�V���R���e�i�̐���
	// �g���\���̂𗘗p
	TMyD3DXMESHCONTAINER* pMeshContainer = nullptr;
	pMeshContainer = new TMyD3DXMESHCONTAINER;
	if ( !pMeshContainer ) 
		return E_OUTOFMEMORY;

	// 0�N���A
	ZeroMemory( pMeshContainer, sizeof(TMyD3DXMESHCONTAINER));

	// Name�̊i�[
	pMeshContainer->Name = new char[strlen(Name)+1];
	if ( !pMeshContainer->Name ) return E_OUTOFMEMORY;
	strcpy( pMeshContainer->Name, Name );

	// pMeshData�̊i�[
	// �^�C�v�i�[
	pMeshContainer->MeshData.Type = pMeshData->Type;

	// ���b�V���f�[�^�ɖ@���ǉ�
	LPDIRECT3DDEVICE9 pDevice;
	pMeshData->pMesh->GetDevice( &pDevice );
	if ( !(pMeshData->pMesh->GetFVF() & D3DFVF_NORMAL) ) {
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

		HRESULT hr = pMeshData->pMesh->CloneMeshFVF(
			pMeshData->pMesh->GetOptions(),
			pMeshData->pMesh->GetFVF() | D3DFVF_NORMAL,
			pDevice,
			&pMeshContainer->MeshData.pMesh );

		if ( FAILED(hr) ) {
			//CDebug::ErrorPrintf("�@�������������̂Œǉ����悤�Ƃ��܂��������s\n");
			return E_FAIL;
		}

		// �e���_�̖@���ݒ�
		D3DXComputeNormals( pMeshContainer->MeshData.pMesh, nullptr);
	}

	// �^�C�v�ʊi�[
	// �ʏ탁�b�V��
	else if ( pMeshData->Type == D3DXMESHTYPE_MESH ) {
		// ���b�V���̊i�[
		pMeshContainer->MeshData.pMesh = pMeshData->pMesh;
		// �Q�ƃJ�E���^�̃C���N�������g
		pMeshContainer->MeshData.pMesh->AddRef();
		#if _DEBUG
		std::cout << "���b�V���^�C�v:�ʏ탁�b�V��" << std::endl;
		#endif
	}
	
	// �v���O���b�V�u���b�V��
	else if ( pMeshData->Type == D3DXMESHTYPE_PMESH ) {
		// ���b�V���̊i�[
		pMeshContainer->MeshData.pPMesh = pMeshData->pPMesh;
		// �Q�ƃJ�E���^�̃C���N�������g
		pMeshContainer->MeshData.pPMesh->AddRef();
		#if _DEBUG
		std::cout << "���b�V���^�C�v:�v���O���b�V�u���b�V��" << std::endl;
		#endif
	}

	// pMaterials�̊i�[
	// �}�e���A���z��̔z�񐔂��i�[
	pMeshContainer->NumMaterials = max( 1, NumMaterials );
	
	// �}�e���A���z��̓��I�m��
	pMeshContainer->pMaterials = nullptr;
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	if ( !pMeshContainer->pMaterials ) return E_OUTOFMEMORY;

	// �e�N�X�`���I�u�W�F�N�g�̓��I�m��
	pMeshContainer->ppTexture = nullptr;
	pMeshContainer->ppTexture =	new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	if ( !pMeshContainer->ppTexture ) return E_OUTOFMEMORY;
    memset( pMeshContainer->ppTexture, 0, sizeof(LPDIRECT3DTEXTURE9)*pMeshContainer->NumMaterials );

	// �}�e���A����񂪗L��Ίi�[������ΓK���ɍ��
	if ( NumMaterials > 0 ) {
		// �}�e���A�����L��
		for ( DWORD i = 0; i < NumMaterials; i ++) {
			// �}�e���A�����̃R�s�[
			pMeshContainer->pMaterials[i].MatD3D = pMaterials[i].MatD3D;
			// �e�N�X�`���t�@�C����
			pMeshContainer->pMaterials[i].pTextureFilename = nullptr;
			// �e�N�X�`�������݂��Ȃ����b�V��������̂Ŋm�F
			if ( pMaterials[i].pTextureFilename != NULL ) {
				pMeshContainer->pMaterials[i].pTextureFilename = new char[strlen(pMaterials[i].pTextureFilename)+1];
				if ( !pMeshContainer->pMaterials[i].pTextureFilename ) return E_OUTOFMEMORY;
				strcpy( pMeshContainer->pMaterials[i].pTextureFilename, pMaterials[i].pTextureFilename);
				// �e�N�X�`���ǂݍ���
				HRESULT hr = D3DXCreateTextureFromFileA( pDevice,
					pMeshContainer->pMaterials[i].pTextureFilename, &pMeshContainer->ppTexture[i] );
				if ( FAILED(hr) )
				{
					// �ǂݍ��߂Ȃ������ꍇ
					pMeshContainer->ppTexture[i] = nullptr;
				}
			}
		}
	} else {
		// �}�e���A����񖳂�
		pMeshContainer->pMaterials[0].pTextureFilename = nullptr;
		memset( &pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r   = 0.5F;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g   = 0.5F;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b   = 0.5F;
		pMeshContainer->pMaterials[0].MatD3D.Specular.r  = 0.5F;
		pMeshContainer->pMaterials[0].MatD3D.Specular.g  = 0.5F;
		pMeshContainer->pMaterials[0].MatD3D.Specular.b  = 0.5F;
	}

	// pEffectInstances
	// �i�[��z��̓��I�m��
	pMeshContainer->pEffects = nullptr;
	pMeshContainer->pEffects = new D3DXEFFECTINSTANCE;
	if ( !pMeshContainer->pEffects ) return E_OUTOFMEMORY;

	// �G�t�F�N�g�t�@�C��������΃t�@�C�����̃R�s�[
	pMeshContainer->pEffects->pEffectFilename = nullptr;
	if ( pEffectInstances->pEffectFilename ) {
		pMeshContainer->pEffects->pEffectFilename = new char[strlen(pEffectInstances->pEffectFilename) + 1];
		if ( !pMeshContainer->pEffects->pEffectFilename ) return E_OUTOFMEMORY;
		strcpy(  pMeshContainer->pEffects->pEffectFilename, pEffectInstances->pEffectFilename );
	} 

	// pDefaults�̔z��̗v�f�����i�[
	pMeshContainer->pEffects->NumDefaults = pEffectInstances->NumDefaults;

	// D3DXEFFECTDEFAULT�̓��I�m��
	pMeshContainer->pEffects->pDefaults = nullptr;
	pMeshContainer->pEffects->pDefaults = new D3DXEFFECTDEFAULT[pEffectInstances->NumDefaults];
	if ( !pMeshContainer->pEffects->pDefaults ) return E_OUTOFMEMORY;

	// �ꎞ�I�ɕϐ��ύX
	D3DXEFFECTDEFAULT *pSrc = pEffectInstances->pDefaults;
	D3DXEFFECTDEFAULT *pDst = pMeshContainer->pEffects->pDefaults;

	for ( DWORD i = 0; i < pEffectInstances->NumDefaults; i++) {
		pDst[i].pParamName = nullptr;

		if ( pSrc[i].pParamName ) {
			pDst[i].pParamName = new char[strlen(pSrc[i].pParamName)+1];
			if ( !pDst->pParamName ) return E_OUTOFMEMORY;
			strcpy( pDst->pParamName, pSrc->pParamName);
		}

		DWORD NumBytes = pDst[i].NumBytes = pSrc[i].NumBytes;
		pDst[i].Type = pSrc[i].Type;
		if ( pSrc[i].Type <= D3DXEDT_DWORD ) {
			pDst[i].pValue = nullptr;
			pDst[i].pValue = new DWORD[NumBytes];
			if ( !pDst[i].pValue ) return E_OUTOFMEMORY;
			memcpy( pDst[i].pValue, pSrc[i].pValue, NumBytes);
		}
	}

	// �z��̊m��
	const DWORD face_num = pMeshData->pMesh->GetNumFaces();
	pMeshContainer->pAdjacency = new DWORD[face_num*3];
	// �R�s�[
	memcpy( pMeshContainer->pAdjacency, pAdjacency, face_num*3*sizeof(DWORD));

	if ( pSkinInfo ) {
		// �X�L�����b�V���L��
		DWORD dwBoneNum;
		pMeshContainer->pSkinInfo = pSkinInfo;
		// �Q�ƃJ�E���^�̃C���N�������g
		pMeshContainer->pSkinInfo->AddRef();
		// �{�[�����擾
		dwBoneNum = pSkinInfo->GetNumBones();
		pMeshContainer->pMtxOffset = new D3DXMATRIX[dwBoneNum];

		// �{�[���s��̃R�s�[
		for ( DWORD i = 0; i < dwBoneNum; i ++) {
			memcpy(
				&pMeshContainer->pMtxOffset[i],
				pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i),
				sizeof(D3DMATRIX));
		}
		
		// �{�[������K�p�������b�V���ւ̕ϊ�
		if ( FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(
			pMeshData->pMesh,
			NULL,
			pMeshContainer->pAdjacency,
			nullptr, nullptr, nullptr,
			&pMeshContainer->dwBoneWeight,			
			&pMeshContainer->dwBoneNum,
			&pMeshContainer->pBoneComb,
			&pMeshContainer->MeshData.pMesh) ) )
		{
			//ErrorPrintf("�{�[�����̕ϊ��Ɏ��s\n");
			return E_FAIL;
		}
			

	} else {
		// �X�L�����b�V������
		pMeshContainer->pSkinInfo = nullptr;
	}

	// �߂�l�Ɋi�[
	*ppNewMeshContainer = pMeshContainer;

	return D3D_OK;
}

// �{�[���̐���
void CD3DXAllocateHierarchy::CreateBone ( TMyD3DXFRAME* pFrame, const D3DXFRAME* pRootFrame ) {
	// ���b�V���R���e�i������΍s�񐶐������݂�
	if ( pFrame->pMeshContainer ) {
		CreateBoneMatrix((TMyD3DXMESHCONTAINER*)pFrame->pMeshContainer, pRootFrame);
	}

	// �Z��t���[���̃{�[������
	if ( pFrame->pFrameSibling ) {
		CreateBone( (TMyD3DXFRAME*)pFrame->pFrameSibling, pRootFrame);
	}

	// �q�t���[���̃{�[������
	if ( pFrame->pFrameFirstChild ) {
		CreateBone( (TMyD3DXFRAME*)pFrame->pFrameFirstChild, pRootFrame);
	}
}

// �{�[���s��̐�
void CD3DXAllocateHierarchy::CreateBoneMatrix ( TMyD3DXMESHCONTAINER* pMeshContainer, const D3DXFRAME* pRootFrame ) {
	// �X�L����񂪂Ȃ����
	if ( !pMeshContainer->pSkinInfo ) {
		return;
	}

	// �ϐ��錾
	DWORD dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();

	// �{�[���s��𐶐�
	pMeshContainer->ppMtxBone = new D3DXMATRIX*[dwBoneNum];

	for ( DWORD i = 0; i < dwBoneNum; i ++) {
		TMyD3DXFRAME* pFrame = (TMyD3DXFRAME*)D3DXFrameFind(
			pRootFrame,
			pMeshContainer->pSkinInfo->GetBoneName(i));

		if ( !pFrame ) {
			return;
		}
		pMeshContainer->ppMtxBone[i] = &pFrame->mtxWorld;
	}
}

// �t���[���I�u�W�F�N�g�̍폜
HRESULT CD3DXAllocateHierarchy::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree) {
#if _DEBUG
#ifdef CD3DXALLOCATEHIERARCHY_DEBUG
	CDebug::DPrintf("DestroyFrame function call.(");
	CDebug::DPrintf(pFrameToFree->Name);
	CDebug::DPrintf(")\n");
#endif
#endif

	if( !pFrameToFree )
		return D3D_OK;
	
	if ( pFrameToFree->Name ) {
		delete[] pFrameToFree->Name;
	}

	if ( pFrameToFree->pMeshContainer ) {
		DestroyMeshContainer(pFrameToFree->pMeshContainer);
	}

	if ( pFrameToFree->pFrameSibling ) {
		DestroyFrame(pFrameToFree->pFrameSibling);
	}

	if ( pFrameToFree->pFrameFirstChild ) {
		DestroyFrame(pFrameToFree->pFrameFirstChild);
	}

	delete pFrameToFree;
	return D3D_OK;
}

// ���b�V���R���e�i�̍폜
HRESULT CD3DXAllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree){
#if _DEBUG
#ifdef CD3DXALLOCATEHIERARCHY_DEBUG
	CDebug::DPrintf("DestroyMeshContainer function call.\n");
#endif
#endif
	TMyD3DXMESHCONTAINER* pMeshContainer = (TMyD3DXMESHCONTAINER*)pMeshContainerToFree;

	// �{�[���s��
	if ( pMeshContainer->ppMtxBone ) {
		delete[] pMeshContainer->ppMtxBone;
	}

	// �X�L�����
	if (pMeshContainerToFree->pSkinInfo) {
		pMeshContainerToFree->pSkinInfo->Release();
		pMeshContainerToFree->pSkinInfo = nullptr;
	}

	// �I�t�Z�b�g�s��
	if ( pMeshContainer->pMtxOffset ) {
		delete[] pMeshContainer->pMtxOffset;
	}
	
	// �|���S���אڐ�
	delete[] pMeshContainer->pAdjacency;

	for( unsigned long i = 0; i < pMeshContainer->pEffects->NumDefaults; i++){
		delete[] pMeshContainer->pEffects->pDefaults[i].pParamName;
		delete[] pMeshContainer->pEffects->pDefaults[i].pValue;
	}

	if ( pMeshContainer->pEffects->pDefaults ) {
		delete[] pMeshContainer->pEffects->pDefaults;
	}

	// ���b�V��(3���)
	if ( pMeshContainerToFree->MeshData.pMesh ) {
		pMeshContainerToFree->MeshData.pMesh->Release();
		pMeshContainerToFree->MeshData.pMesh = nullptr;
	}
	if ( pMeshContainer->MeshData.pPMesh ) {
		pMeshContainer->MeshData.pPMesh->Release();
		pMeshContainer->MeshData.pPMesh = NULL;
	}
	if ( pMeshContainer->MeshData.pPatchMesh ) {
		pMeshContainer->MeshData.pPatchMesh->Release();
		pMeshContainer->MeshData.pPatchMesh = nullptr;
	}

	// �G�t�F�N�g�̃t�@�C����
	if ( pMeshContainer->pEffects->pEffectFilename ) {
		delete[] pMeshContainer->pEffects->pEffectFilename;
	}

	// �G�t�F�N�g
	delete pMeshContainer->pEffects;

	// �e�N�X�`���̃t�@�C����
	for( int i = 0; i< pMeshContainer->NumMaterials; i++ ){
		delete[] pMeshContainer->pMaterials[i].pTextureFilename;
	}

	// �e�N�X�`��
	for ( int i = 0; i < pMeshContainer->NumMaterials; i++ ) {
		if ( pMeshContainer->ppTexture[i] ) {
			pMeshContainer->ppTexture[i]->Release();
		}
	}

	// �e�N�X�`��
	delete[] pMeshContainer->ppTexture;

	// �}�e���A��
	if ( pMeshContainer->pMaterials ) {
		delete[] pMeshContainerToFree->pMaterials;
	}

	// ���O
	if ( pMeshContainer->Name ) {
		delete[] pMeshContainer->Name;
	}

	// ���b�V���R���e�i�̊J��:1
	delete pMeshContainer;

	return S_OK;
}

}