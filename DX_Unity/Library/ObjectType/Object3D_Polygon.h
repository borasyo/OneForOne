//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object3D_Polygon.h]
// author : 大洞祥太
// 
// GameObjectが3DPolygonオブジェクトの場合、これを合成する。
//
// ・テクスチャアニメーションする場合は、SetDivideで分割数を指定し
//   パターンが変化したときに、SetTextureを呼ぶ。
//
// ・ビルボードにするかどうかはm_bBillboardで対応している。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____OBJECT_3D_POLYGON_H_____
#define _____OBJECT_3D_POLYGON_H_____

#include "d3dx9.h"
#include "../DirectX/Direct3D.h"
#include "../ObjectData/TextureManager.h"

// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3	vtx;	// 頂点座標
	D3DXVECTOR3 normal;	// 法線ベクトル
	D3DCOLOR	diffuse;// 反射光
	D3DXVECTOR2	tex;	// テクスチャ座標
}VERTEX_3D;

class CObject3DPolygon {

private:
	LPCWSTR m_FileName;
	VERTEX_3D m_Vertex[NUM_VERTEX]; // 頂点情報
	D3DXMATRIX mtxWorld;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	CTextureManager* m_pTextureManager;
	bool m_bBillboard;
	float m_fDivide;

public:
	CObject3DPolygon();
	virtual ~CObject3DPolygon();

	void Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const D3DXVECTOR3 Rot );
	const LPCWSTR GetFileName();
	void SetFileName( const LPCWSTR& filename );
	void SetBillFlg( const bool bFlg = false );
	void SetDivide( const float fDivide );
	
	HRESULT MakeVertexPolygon();
	void SetVertexBillBoard( const D3DXVECTOR3 Scale );
	void SetVertexPolygon( const D3DXVECTOR3 Scale );
	void SetVertexColor( const D3DCOLOR Color );
	void SetVertexNormal( const D3DXVECTOR3 Normal );
	void SetVertexTexture( const int nPattern ); // 分割数、何パターン目か
};

#endif