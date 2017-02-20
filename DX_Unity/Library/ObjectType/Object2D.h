//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object2D.h]
// author : 大洞祥太
//
// GameObjectが2Dオブジェクトの場合、これを合成する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TEXTURE_DRAW_H_____
#define _____TEXTURE_DRAW_H_____

#include "d3dx9.h"
#include "../Task/GameObject.h"
#include "../ObjectData/TextureManager.h"

// ---- マクロ
#define NUM_VERTEX  (4) // 頂点数(固定)
#define NUM_POLYGON (2) // ポリゴン数(固定)
#define	FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 ) // 頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ )

// ---- 2DTexture構造体
typedef struct _VERTEX_2D	// 頂点フォーマットに合わせた構造体
{
	D3DXVECTOR3	pos;			// 頂点座標
	float		rhw;			// テクスチャのパースペクティブコレクト用
	D3DCOLOR	col;			// 頂点カラー
	D3DXVECTOR2 tex;			// テクスチャ座標
} VERTEX_2D;

// ---- Class
class CObject2D {

private:
	std::wstring m_FileName;
	VERTEX_2D m_Vertex[NUM_VERTEX]; // 頂点情報
	LPDIRECT3DDEVICE9 m_pD3DDevice; // DirectXDevice
	CTextureManager* m_pTextureManager; // 
	float m_fDivide;

public:	
	CObject2D();
	~CObject2D();

	// 描画関数
	void Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const float fRot = 0.0f );
	// 座標更新
	void SetVertexPolygon( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const float fRot );
	void SetVertexColor( const D3DCOLOR Color );
	void SetVertexTexture( const int nPattern ); // 分割数、何パターン目か

	// 頂点情報初期化
	void MakeVertexPolygon();

	// ゲッターセッター
	const std::wstring GetFileName();
	void SetFileName( const std::wstring& filename );
};

#endif;