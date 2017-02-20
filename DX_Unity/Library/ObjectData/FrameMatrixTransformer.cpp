//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CFrameMatrixTransformer.cpp]
// author : 大洞祥太
// 
// 個々のフレームが持っているワールド行列の変換
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FrameMatrixTransformer.h"

// --- 名前空間
namespace SkinMesh {

CFrameMatrixTransformer::CFrameMatrixTransformer () {

}

CFrameMatrixTransformer::~CFrameMatrixTransformer () {

}

// 変換作業
void CFrameMatrixTransformer::Run ( TMyD3DXFRAME* pRootFrame, const D3DXMATRIX* pMtxWorld) {
	// スタックの初期化
	while ( !m_mtxStack.empty() ) {
		m_mtxStack.pop();
	}
	
	// ワールド行列をスタックに積む
	D3DXMATRIX mtxWorld;
	mtxWorld = *pMtxWorld;
	m_mtxStack.push( &mtxWorld );

	// 計算開始
	CreateWorldMatrix( pRootFrame );
}

// 全フレームを再帰計算処理
void CFrameMatrixTransformer::CreateWorldMatrix ( TMyD3DXFRAME* pFrame ) {

	if( !pFrame )
		return;

	// 親のワールド行列を取得
	D3DXMATRIX* pMatrix = m_mtxStack.top();

	// フレームローカル→ワールド計算
	D3DXMatrixMultiply( &pFrame->mtxWorld, &pFrame->TransformationMatrix, pMatrix );

	// 子フレームの計算
	if ( pFrame->pFrameFirstChild ) {
		// 子フレームのために自分のワールド行列をセット
		m_mtxStack.push( &pFrame->mtxWorld);
		// 子フレームへ移る
		CreateWorldMatrix( (TMyD3DXFRAME*)pFrame->pFrameFirstChild);
		// 兄弟フレームのために自分のワールド行列を取り出す
		m_mtxStack.pop();
	}

	// 兄弟フレームの計算
	if ( pFrame->pFrameSibling ) {
		// 兄弟フレームへ移る
		CreateWorldMatrix( (TMyD3DXFRAME*)pFrame->pFrameSibling );
	}
}

}