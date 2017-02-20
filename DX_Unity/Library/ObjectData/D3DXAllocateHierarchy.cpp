//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CD3DXAllocateHierarchy.cpp]
// author : 大洞祥太
// 
// ID3DXAllocateHierarchyの派生クラス
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "D3DXAllocateHierarchy.h"
#include <iostream>

// --- 名前空間
namespace SkinMesh {

CD3DXAllocateHierarchy::CD3DXAllocateHierarchy () {}

CD3DXAllocateHierarchy::~CD3DXAllocateHierarchy () {}

// フレームオブジェクトの生成
HRESULT CD3DXAllocateHierarchy::CreateFrame( THIS_ LPCSTR Name, LPD3DXFRAME* ppNewFrame ) {

	// 名前ありますか
	if ( !Name ) {
		return E_FAIL;
	}
	// フレームオブジェクトの生成
	// これが戻り値になる
	// 拡張クラスを利用
	TMyD3DXFRAME*	pFrame = nullptr;
	pFrame = new TMyD3DXFRAME;
	if ( !pFrame ) return E_OUTOFMEMORY;

	// 名前のセット
	pFrame->Name = nullptr;
	pFrame->Name = new char[strlen(Name) + 1];
	if ( pFrame->Name == 0 ) return E_OUTOFMEMORY;
	strcpy( pFrame->Name, Name);

	// 所持行列の初期化
	D3DXMatrixIdentity( &pFrame->TransformationMatrix);
	D3DXMatrixIdentity( &pFrame->mtxWorld);

	// 所持ポインタの初期化
	pFrame->pMeshContainer		= nullptr; // メッシュコンテナ
	pFrame->pFrameSibling		= nullptr; // 兄弟フレーム
	pFrame->pFrameFirstChild	= nullptr; // 子フレーム

	// 戻り値に代入
	*ppNewFrame = pFrame;

	// 後片付け
	pFrame = nullptr;

	return S_OK;
}

// メッシュコンテナの生成
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
	// メッシュコンテナの生成
	// 拡張構造体を利用
	TMyD3DXMESHCONTAINER* pMeshContainer = nullptr;
	pMeshContainer = new TMyD3DXMESHCONTAINER;
	if ( !pMeshContainer ) 
		return E_OUTOFMEMORY;

	// 0クリア
	ZeroMemory( pMeshContainer, sizeof(TMyD3DXMESHCONTAINER));

	// Nameの格納
	pMeshContainer->Name = new char[strlen(Name)+1];
	if ( !pMeshContainer->Name ) return E_OUTOFMEMORY;
	strcpy( pMeshContainer->Name, Name );

	// pMeshDataの格納
	// タイプ格納
	pMeshContainer->MeshData.Type = pMeshData->Type;

	// メッシュデータに法線追加
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
			//CDebug::ErrorPrintf("法線が無かったので追加しようとしましたが失敗\n");
			return E_FAIL;
		}

		// 各頂点の法線設定
		D3DXComputeNormals( pMeshContainer->MeshData.pMesh, nullptr);
	}

	// タイプ別格納
	// 通常メッシュ
	else if ( pMeshData->Type == D3DXMESHTYPE_MESH ) {
		// メッシュの格納
		pMeshContainer->MeshData.pMesh = pMeshData->pMesh;
		// 参照カウンタのインクリメント
		pMeshContainer->MeshData.pMesh->AddRef();
		#if _DEBUG
		std::cout << "メッシュタイプ:通常メッシュ" << std::endl;
		#endif
	}
	
	// プログレッシブメッシュ
	else if ( pMeshData->Type == D3DXMESHTYPE_PMESH ) {
		// メッシュの格納
		pMeshContainer->MeshData.pPMesh = pMeshData->pPMesh;
		// 参照カウンタのインクリメント
		pMeshContainer->MeshData.pPMesh->AddRef();
		#if _DEBUG
		std::cout << "メッシュタイプ:プログレッシブメッシュ" << std::endl;
		#endif
	}

	// pMaterialsの格納
	// マテリアル配列の配列数を格納
	pMeshContainer->NumMaterials = max( 1, NumMaterials );
	
	// マテリアル配列の動的確保
	pMeshContainer->pMaterials = nullptr;
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	if ( !pMeshContainer->pMaterials ) return E_OUTOFMEMORY;

	// テクスチャオブジェクトの動的確保
	pMeshContainer->ppTexture = nullptr;
	pMeshContainer->ppTexture =	new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	if ( !pMeshContainer->ppTexture ) return E_OUTOFMEMORY;
    memset( pMeshContainer->ppTexture, 0, sizeof(LPDIRECT3DTEXTURE9)*pMeshContainer->NumMaterials );

	// マテリアル情報が有れば格納無ければ適当に作る
	if ( NumMaterials > 0 ) {
		// マテリアル情報有り
		for ( DWORD i = 0; i < NumMaterials; i ++) {
			// マテリアル情報のコピー
			pMeshContainer->pMaterials[i].MatD3D = pMaterials[i].MatD3D;
			// テクスチャファイル名
			pMeshContainer->pMaterials[i].pTextureFilename = nullptr;
			// テクスチャが存在しないメッシュもあるので確認
			if ( pMaterials[i].pTextureFilename != NULL ) {
				pMeshContainer->pMaterials[i].pTextureFilename = new char[strlen(pMaterials[i].pTextureFilename)+1];
				if ( !pMeshContainer->pMaterials[i].pTextureFilename ) return E_OUTOFMEMORY;
				strcpy( pMeshContainer->pMaterials[i].pTextureFilename, pMaterials[i].pTextureFilename);
				// テクスチャ読み込み
				HRESULT hr = D3DXCreateTextureFromFileA( pDevice,
					pMeshContainer->pMaterials[i].pTextureFilename, &pMeshContainer->ppTexture[i] );
				if ( FAILED(hr) )
				{
					// 読み込めなかった場合
					pMeshContainer->ppTexture[i] = nullptr;
				}
			}
		}
	} else {
		// マテリアル情報無し
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
	// 格納先配列の動的確保
	pMeshContainer->pEffects = nullptr;
	pMeshContainer->pEffects = new D3DXEFFECTINSTANCE;
	if ( !pMeshContainer->pEffects ) return E_OUTOFMEMORY;

	// エフェクトファイルがあればファイル名のコピー
	pMeshContainer->pEffects->pEffectFilename = nullptr;
	if ( pEffectInstances->pEffectFilename ) {
		pMeshContainer->pEffects->pEffectFilename = new char[strlen(pEffectInstances->pEffectFilename) + 1];
		if ( !pMeshContainer->pEffects->pEffectFilename ) return E_OUTOFMEMORY;
		strcpy(  pMeshContainer->pEffects->pEffectFilename, pEffectInstances->pEffectFilename );
	} 

	// pDefaultsの配列の要素数を格納
	pMeshContainer->pEffects->NumDefaults = pEffectInstances->NumDefaults;

	// D3DXEFFECTDEFAULTの動的確保
	pMeshContainer->pEffects->pDefaults = nullptr;
	pMeshContainer->pEffects->pDefaults = new D3DXEFFECTDEFAULT[pEffectInstances->NumDefaults];
	if ( !pMeshContainer->pEffects->pDefaults ) return E_OUTOFMEMORY;

	// 一時的に変数変更
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

	// 配列の確保
	const DWORD face_num = pMeshData->pMesh->GetNumFaces();
	pMeshContainer->pAdjacency = new DWORD[face_num*3];
	// コピー
	memcpy( pMeshContainer->pAdjacency, pAdjacency, face_num*3*sizeof(DWORD));

	if ( pSkinInfo ) {
		// スキンメッシュ有り
		DWORD dwBoneNum;
		pMeshContainer->pSkinInfo = pSkinInfo;
		// 参照カウンタのインクリメント
		pMeshContainer->pSkinInfo->AddRef();
		// ボーン数取得
		dwBoneNum = pSkinInfo->GetNumBones();
		pMeshContainer->pMtxOffset = new D3DXMATRIX[dwBoneNum];

		// ボーン行列のコピー
		for ( DWORD i = 0; i < dwBoneNum; i ++) {
			memcpy(
				&pMeshContainer->pMtxOffset[i],
				pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i),
				sizeof(D3DMATRIX));
		}
		
		// ボーン情報を適用したメッシュへの変換
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
			//ErrorPrintf("ボーン情報の変換に失敗\n");
			return E_FAIL;
		}
			

	} else {
		// スキンメッシュ無し
		pMeshContainer->pSkinInfo = nullptr;
	}

	// 戻り値に格納
	*ppNewMeshContainer = pMeshContainer;

	return D3D_OK;
}

// ボーンの生成
void CD3DXAllocateHierarchy::CreateBone ( TMyD3DXFRAME* pFrame, const D3DXFRAME* pRootFrame ) {
	// メッシュコンテナがあれば行列生成を試みる
	if ( pFrame->pMeshContainer ) {
		CreateBoneMatrix((TMyD3DXMESHCONTAINER*)pFrame->pMeshContainer, pRootFrame);
	}

	// 兄弟フレームのボーン生成
	if ( pFrame->pFrameSibling ) {
		CreateBone( (TMyD3DXFRAME*)pFrame->pFrameSibling, pRootFrame);
	}

	// 子フレームのボーン生成
	if ( pFrame->pFrameFirstChild ) {
		CreateBone( (TMyD3DXFRAME*)pFrame->pFrameFirstChild, pRootFrame);
	}
}

// ボーン行列の生
void CD3DXAllocateHierarchy::CreateBoneMatrix ( TMyD3DXMESHCONTAINER* pMeshContainer, const D3DXFRAME* pRootFrame ) {
	// スキン情報がなければ
	if ( !pMeshContainer->pSkinInfo ) {
		return;
	}

	// 変数宣言
	DWORD dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();

	// ボーン行列を生成
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

// フレームオブジェクトの削除
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

// メッシュコンテナの削除
HRESULT CD3DXAllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree){
#if _DEBUG
#ifdef CD3DXALLOCATEHIERARCHY_DEBUG
	CDebug::DPrintf("DestroyMeshContainer function call.\n");
#endif
#endif
	TMyD3DXMESHCONTAINER* pMeshContainer = (TMyD3DXMESHCONTAINER*)pMeshContainerToFree;

	// ボーン行列
	if ( pMeshContainer->ppMtxBone ) {
		delete[] pMeshContainer->ppMtxBone;
	}

	// スキン情報
	if (pMeshContainerToFree->pSkinInfo) {
		pMeshContainerToFree->pSkinInfo->Release();
		pMeshContainerToFree->pSkinInfo = nullptr;
	}

	// オフセット行列
	if ( pMeshContainer->pMtxOffset ) {
		delete[] pMeshContainer->pMtxOffset;
	}
	
	// ポリゴン隣接性
	delete[] pMeshContainer->pAdjacency;

	for( unsigned long i = 0; i < pMeshContainer->pEffects->NumDefaults; i++){
		delete[] pMeshContainer->pEffects->pDefaults[i].pParamName;
		delete[] pMeshContainer->pEffects->pDefaults[i].pValue;
	}

	if ( pMeshContainer->pEffects->pDefaults ) {
		delete[] pMeshContainer->pEffects->pDefaults;
	}

	// メッシュ(3種類)
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

	// エフェクトのファイル名
	if ( pMeshContainer->pEffects->pEffectFilename ) {
		delete[] pMeshContainer->pEffects->pEffectFilename;
	}

	// エフェクト
	delete pMeshContainer->pEffects;

	// テクスチャのファイル名
	for( int i = 0; i< pMeshContainer->NumMaterials; i++ ){
		delete[] pMeshContainer->pMaterials[i].pTextureFilename;
	}

	// テクスチャ
	for ( int i = 0; i < pMeshContainer->NumMaterials; i++ ) {
		if ( pMeshContainer->ppTexture[i] ) {
			pMeshContainer->ppTexture[i]->Release();
		}
	}

	// テクスチャ
	delete[] pMeshContainer->ppTexture;

	// マテリアル
	if ( pMeshContainer->pMaterials ) {
		delete[] pMeshContainerToFree->pMaterials;
	}

	// 名前
	if ( pMeshContainer->Name ) {
		delete[] pMeshContainer->Name;
	}

	// メッシュコンテナの開放:1
	delete pMeshContainer;

	return S_OK;
}

}