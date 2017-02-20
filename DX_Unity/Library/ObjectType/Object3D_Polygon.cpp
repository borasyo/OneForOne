//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object3D_Polygon.h]
// author : 大洞祥太
// 
// GameObjectが3DPolygonオブジェクトの場合、これを合成する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Object3D_Polygon.h"

CObject3DPolygon::CObject3DPolygon():m_bBillboard(true)
									,m_fDivide(0) {
	// デバイス取得
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	// マネージャー取得
	m_pTextureManager = CTextureManager::Create();
	
	// 頂点情報の作成
	MakeVertexPolygon();
	
	// 色はデフォルトに初期化
	SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) );
}

CObject3DPolygon::~CObject3DPolygon(){

}

void CObject3DPolygon::Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const D3DXVECTOR3 Rot ) {
	
	D3DXMATRIX mtxTranslate, mtxRotation, mtxScale;
	
	// ライティングを無効にする
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	// スケールセット
	D3DXMatrixScaling( &mtxScale, Scale.x, Scale.y, Scale.z );
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxScale);

	// 回転セットします
	// ビルボードなら
	if( m_bBillboard ) { 

		// 座標更新
		SetVertexBillBoard(Scale);

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &mtxWorld );

		D3DXMATRIX mtxView;
		m_pD3DDevice->GetTransform( D3DTS_VIEW, &mtxView );
		
		//mtxWorld._11 = mtxView.

		// 逆行列を求める
		D3DXMatrixInverse( &mtxWorld,NULL,&mtxView );

		mtxWorld._41 = 0.0f;
		mtxWorld._42 = 0.0f;
		mtxWorld._43 = 0.0f;
	}
	// 通常なら
	else {
		// 座標更新
		SetVertexPolygon(Scale);

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &mtxWorld );
		
		// 回転セット
		D3DXMatrixRotationYawPitchRoll( &mtxRotation, Rot.y, Rot.x, Rot.z );
		D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxRotation);
	}

	// ポジションセット
	D3DXMatrixTranslation( &mtxTranslate, Pos.x, Pos.y, Pos.z );
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxTranslate);
	
	// 描画
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &mtxWorld );
	
	m_pD3DDevice->SetFVF( FVF_VERTEX_3D ); // 頂点フォーマットの設定
	m_pD3DDevice->SetTexture( 0, m_pTextureManager->LoadTexture(m_FileName) ); // テクスチャのセット
	m_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, NUM_POLYGON, m_Vertex, sizeof( VERTEX_3D ) ); // ポリゴンの描画

	m_pD3DDevice->SetTexture( 0, nullptr ); // テクスチャ情報初期化
	
	// ライティングを有効にする
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

HRESULT CObject3DPolygon::MakeVertexPolygon(){

	if( m_bBillboard ) {

		// テクスチャ座標
		m_Vertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		m_Vertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	
		// 法線の設定
		m_Vertex[0].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[1].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[2].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[3].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	} 
	else {

		// テクスチャ座標
		m_Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		m_Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		// 法線の設定
		m_Vertex[0].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[1].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[2].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[3].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	}

	return S_OK;
}

void CObject3DPolygon::SetVertexPolygon( const D3DXVECTOR3 Scale ){
	
	// 頂点座標の設定
	m_Vertex[0].vtx = D3DXVECTOR3( -Scale.x/2, 0.0f,  Scale.z/2 );
	m_Vertex[1].vtx = D3DXVECTOR3(  Scale.x/2, 0.0f,  Scale.z/2 );
	m_Vertex[2].vtx = D3DXVECTOR3( -Scale.x/2, 0.0f, -Scale.z/2 );
	m_Vertex[3].vtx = D3DXVECTOR3(  Scale.x/2, 0.0f, -Scale.z/2 );
}

void CObject3DPolygon::SetVertexBillBoard( const D3DXVECTOR3 Scale ){
	
	// 頂点座標の設定
	m_Vertex[0].vtx = D3DXVECTOR3( -Scale.x/2 , -Scale.y/2 , 0.0f );
	m_Vertex[1].vtx = D3DXVECTOR3( -Scale.x/2 , +Scale.y/2 , 0.0f );
	m_Vertex[2].vtx = D3DXVECTOR3( +Scale.x/2 , -Scale.y/2 , 0.0f );
	m_Vertex[3].vtx = D3DXVECTOR3( +Scale.x/2 , +Scale.y/2 , 0.0f );
}

void CObject3DPolygon::SetVertexColor( const D3DCOLOR Color ){
	
	// 頂点カラーの設定( 0 ～ 255 )
	m_Vertex[0].diffuse = Color;
	m_Vertex[1].diffuse = Color;
	m_Vertex[2].diffuse = Color;
	m_Vertex[3].diffuse = Color;
}

// 法線変えたいなら
void CObject3DPolygon::SetVertexNormal( const D3DXVECTOR3 Normal ){
	
	// 法線の設定
	m_Vertex[0].normal = Normal;
	m_Vertex[1].normal = Normal;
	m_Vertex[2].normal = Normal;
	m_Vertex[3].normal = Normal;
}

// テクスチャアニメーションするなら
void CObject3DPolygon::SetVertexTexture( const int nPattern ){

	if( m_bBillboard ) {
		// Textureの設定
		m_Vertex[0].tex = D3DXVECTOR2(nPattern * 1.0f/m_fDivide, 1.0f);
		m_Vertex[1].tex = D3DXVECTOR2(nPattern * 1.0f/m_fDivide, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2((nPattern + 1) * 1.0f/m_fDivide, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2((nPattern + 1) * 1.0f/m_fDivide, 0.0f);
	}
	else {
		// Textureの設定
		m_Vertex[0].tex = D3DXVECTOR2(nPattern * 1.0f/m_fDivide, 0.0f);
		m_Vertex[1].tex = D3DXVECTOR2((nPattern + 1) * 1.0f/m_fDivide, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2(nPattern * 1.0f/m_fDivide, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2((nPattern + 1) * 1.0f/m_fDivide, 1.0f);
	}
}

// ゲッター
const LPCWSTR CObject3DPolygon::GetFileName(){
	return m_FileName;
}

// セッター
void CObject3DPolygon::SetFileName( const LPCWSTR& filename ){
	m_FileName = filename;
}

void CObject3DPolygon::SetBillFlg( const bool bFlg ){
	m_bBillboard = bFlg;
	MakeVertexPolygon();
}

void CObject3DPolygon::SetDivide( const float fDivide ){
	m_fDivide = fDivide;
}