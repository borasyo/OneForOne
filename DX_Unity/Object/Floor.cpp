//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Floor.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Floor.h"

// --- マクロ
#define	FIELD_SIZE_X	(100.0f) // 地面のサイズ(X方向)
#define	FIELD_SIZE_Z	(100.0f) // 地面のサイズ(Z方向)

#define FIELD_POS (0.0f)

// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3	vtx;	// 頂点座標
	D3DXVECTOR3 normal;	// 法線ベクトル
	D3DCOLOR	diffuse;// 反射光
	D3DXVECTOR2	tex;	// テクスチャ座標
	D3DXVECTOR3 nor; // 法線
}VERTEX_3D;

// ---- 準備
bool Floor::Start(){
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_bCollision = false;
	
	// 頂点情報の作成
	MakeVertex(10, 10, FIELD_SIZE_X, FIELD_SIZE_Z);

	return true;
}


void Floor::Update(){
	
	/*
	// 毎フレームの更新処理を書く
	VERTEX_3D*	pVtx;

	// 頂点データの範囲をロックし
	// 頂点バッファへのポインタを取得
	m_pD3DVtxBuffField->Lock( 0, 0,(void**)&pVtx, 0 );

	// 頂点座標の変更

	// 頂点データをアンロックする
	m_pD3DVtxBuffField->Unlock();
	*/
}

void Floor::FastDraw(){
	
	D3DXMatrixIdentity( &m_mtxWorld );

	// ワールドマトリクスの設定
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld );

	// 頂点バッファをデバイスの
	// データストリームにバインド
	m_pD3DDevice->SetStreamSource( 0, m_pD3DVtxBuffField, 0, sizeof(VERTEX_3D) );
	
	//インデックスバッファをレンダリングパイプラインに設定
	m_pD3DDevice->SetIndices( m_pD3DIndxBuffField );

	// 頂点フォーマットの設定
	m_pD3DDevice->SetFVF( FVF_VERTEX_3D );

	// テクスチャの設定
	m_pD3DDevice->SetTexture(0, m_pTextureManager->LoadTexture(m_TexName) );
	
	//ポリゴンの描画
	m_pD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP,
										0,//頂点バッファのベース位置
										0,//頂点バッファの使用開始位置
										m_nNumVertex,
										0,//インデックスバッファの開始位置
										m_nNumPolygon );

}

HRESULT Floor::MakeVertex(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ){
	
	// 頂点数（縮退ポリゴン用を考慮する）
	m_nNumVertex = ( nNumBlockX + 1 ) * nNumBlockZ * 2 + ( nNumBlockZ - 1 ) * 2;
	
	// * インデックス数の設定（縮退ポリゴンを考慮する）*
	m_nNumVertexIndex = ( nNumBlockX + 1 ) * nNumBlockZ * 2 + ( nNumBlockZ - 1 ) * 2;

	// ポリゴン数（縮退ポリゴン用を考慮する）
	m_nNumPolygon = nNumBlockX * nNumBlockZ * 2 + ( nNumBlockZ - 1 ) * 4;

	// オブジェクトの頂点バッファを生成
	if( FAILED( m_pD3DDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nNumVertex,// 頂点データ用に確保するバッファサイズ		
		D3DUSAGE_WRITEONLY,	// 頂点バッファの使用法
		FVF_VERTEX_3D,	// 使用する頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pD3DVtxBuffField, // リソースのバッファを保持するメモリクラスを指定
		NULL ))) // 頂点バッファインタフェースへのポインタ
	{
		return E_FAIL;
	}
	
	// * インデックス確保 *
	if( FAILED( m_pD3DDevice->CreateIndexBuffer( sizeof(WORD) * m_nNumVertexIndex,
		//インデックスデータ用に確保する　バッファサイズ（バイト）
		D3DUSAGE_WRITEONLY,	//使用法
		D3DFMT_INDEX16,		//フォーマット
		D3DPOOL_MANAGED,	//リソースのバッファを保持する
		&m_pD3DIndxBuffField,//メモリクラスを指定
		NULL) ) )
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D*	pVtx;

#if 0	// 1枚の四角形ポリゴンに張り付けるテクスチャのサイズ
		const float fSizeTexX = 1.0f / nNumBlockX;
		const float fSizeTexZ = 1.0f / nNumBlockZ;
#else
		const float fSizeTexX = 1.0f;
		const float fSizeTexZ = 1.0f;
#endif

		// 頂点データの範囲をロックし
		// 頂点バッファへのポインタを取得
		m_pD3DVtxBuffField->Lock( 0, 0, (void**)&pVtx, 0 );
		
		for( int CntZ = 0; CntZ < nNumBlockZ + 1; CntZ ++ )
		{
			for( int CntX = 0; CntX < nNumBlockX + 1; CntX ++)
			{
				pVtx[CntZ * (nNumBlockX + 1) + CntX].vtx.x = -nNumBlockX / 2.0f * fSizeBlockX + CntX * fSizeBlockX;
				pVtx[CntZ * (nNumBlockX + 1) + CntX].vtx.y = FIELD_POS;
				pVtx[CntZ * (nNumBlockX + 1) + CntX].vtx.z = +nNumBlockZ / 2.0f * fSizeBlockZ - CntZ * fSizeBlockZ;

				//法線
				pVtx[CntZ*(nNumBlockX + 1) + CntX].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//反射光
				pVtx[CntZ*(nNumBlockX + 1) + CntX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//テクスチャ座標
				pVtx[CntZ*(nNumBlockX + 1) + CntX].tex.x = fSizeTexX * CntX;
				pVtx[CntZ*(nNumBlockX + 1) + CntX].tex.y = fSizeTexZ * CntZ;
			}
		}
	}
		
	{//インデックスバッファの中身を埋める
		WORD* pIdx;

		//インデックスデータの範囲をロックし頂点バッファへのポインタを取得
		m_pD3DIndxBuffField->Lock( 0, 0, (void**)&pIdx, 0 );

		int nCntIdx = 0;
		for( int nCntZ = 0; nCntZ < nNumBlockZ; nCntZ ++ )
		{
			if( nCntZ > 0 )
			{//縮退ポリゴンのためのダブりを設定
				pIdx[nCntIdx] = ( nCntZ + 1 ) * ( nNumBlockX + 1 );
				nCntIdx ++;
			}

			for( int nCntX = 0; nCntX < nNumBlockX + 1; nCntX ++ )
			{
				pIdx[nCntIdx] = ( nCntZ + 1 ) * ( nNumBlockX + 1 ) + nCntX;
				nCntIdx ++;
				pIdx[nCntIdx] = nCntZ * ( nNumBlockX + 1 ) + nCntX;
				nCntIdx ++;
			}

			if( nCntZ < nNumBlockZ - 1 )
			{//縮退ポリゴンのためのダブりを設定
				pIdx[nCntIdx] = nCntZ * ( nNumBlockX + 1 ) + nNumBlockX;
				nCntIdx ++;
			}
		}

		m_pD3DIndxBuffField->Unlock();
	}

	return S_OK;
}