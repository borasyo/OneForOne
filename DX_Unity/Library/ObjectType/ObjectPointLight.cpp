//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ObjectPointLight.cpp]
// author : 大洞祥太
// 
// ポイントライトを作成。まだ使用しない
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "ObjectPointLight.h"

CObjectPointLight::CObjectPointLight() {
	
	ZeroMemory( &m_Light, sizeof( D3DLIGHT9 ) ); //ライト情報のクリア
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_nLightIndex = CLightIndex::Create()->GetIndex();

	//ライトの設定
	m_Light.Type = D3DLIGHT_POINT; // ポイントライト
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // ディフューズ色
	m_Light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // スペキュラー色
	m_Light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // アンビエント色
	m_Light.Position = D3DXVECTOR3(0.0f, 15.0f, 0.0f); // ライトの位置(左からxyz)
	m_Light.Range = 20.0f; // ライトの有効範囲
	m_Light.Attenuation0 = 1.0f; // 減衰定数
	m_Light.Attenuation1 = 1.0f; // 減衰定数
	m_Light.Attenuation2 = 1.0f; // 減衰定数

	HRESULT hr;

	//ライトの反映
	hr = m_pD3DDevice->LightEnable( m_nLightIndex, TRUE );

	//レンダーステートの設定
	hr = m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	hr = m_pD3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );
}

CObjectPointLight::~CObjectPointLight(){

}

void CObjectPointLight::SetVecDirection( D3DXVECTOR3 vecDir ){
	// ライトの向き変更
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_Light.Direction, &vecDir );
	//ライトをレンダリングパイプラインに設定
	m_pD3DDevice->SetLight( m_nLightIndex, &m_Light );
}

void CObjectPointLight::SwitchLight( bool bSwitch ) {
	// ライトのON,OFF切り替え
	m_pD3DDevice->LightEnable( m_nLightIndex, bSwitch );
}