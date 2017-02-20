//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ObjectSpotLight.cpp]
// author : 大洞祥太
// 
// スポットライトを作成。まだ使用しない
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "ObjectSpotLight.h"

CObjectSpotLight::CObjectSpotLight() {
	
	ZeroMemory( &m_Light, sizeof( D3DLIGHT9 ) ); //ライト情報のクリア
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_nLightIndex = CLightIndex::Create()->GetIndex();

	//ライトタイプの設定
	m_Light.Type = D3DLIGHT_SPOT;//スポットライト

	//方向
	D3DXVECTOR3 vecDir = D3DXVECTOR3(0.0f,-1.0f,0.0f); 
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_Light.Direction, &vecDir );

	m_Light.Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); // ディフューズ色
	m_Light.Specular = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); // スペキュラー色
	m_Light.Ambient = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); // アンビエント色
	m_Light.Position = D3DXVECTOR3(0.0f,10.0f,0.0f); // ライトの位置
	//m_Light.Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f); // ライトの方向ベクトル
	m_Light.Range = 1.0f; // ライトの有効範囲
	m_Light.Falloff = 1.0f; // フォールオフ
	m_Light.Attenuation0 = 1.0f; // 定常減衰係数
	m_Light.Attenuation1 = 1.0f; // 定常減衰係数
	m_Light.Attenuation2 = 1.0f; // 定常減衰係数
	m_Light.Theta = D3DXToRadian(10.0f); // 内側のコーンの角度
	m_Light.Phi = D3DXToRadian(30.0f); // 外側のコーンの角度

	//ライトの設定
	m_pD3DDevice->LightEnable( m_nLightIndex, TRUE );

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	m_pD3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );
}

CObjectSpotLight::~CObjectSpotLight(){

}

void CObjectSpotLight::SetVecDirection( D3DXVECTOR3 vecDir ){
	// ライトの向き変更
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_Light.Direction, &vecDir );
	//ライトをレンダリングパイプラインに設定
	m_pD3DDevice->SetLight( m_nLightIndex, &m_Light );
}

void CObjectSpotLight::SwitchLight( bool bSwitch ) {
	// ライトのON,OFF切り替え
	m_pD3DDevice->LightEnable( m_nLightIndex, bSwitch );
}