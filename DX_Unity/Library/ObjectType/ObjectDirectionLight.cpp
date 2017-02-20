//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ObjectDirectionLight.cpp]
// author : 大洞祥太
// 
// ディレクショナルライトを作成。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "ObjectDirectionLight.h"

CObjectDirectionLight::CObjectDirectionLight() {
	
	ZeroMemory( &m_Light, sizeof( D3DLIGHT9 ) ); //ライト情報のクリア
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_nLightIndex = CLightIndex::Create()->GetIndex();

	//ライトタイプの設定
	m_Light.Type = D3DLIGHT_DIRECTIONAL;//平行光源

	//方向
	D3DXVECTOR3 vecDir = D3DXVECTOR3(1.0f,1.0f,1.0f); 
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_Light.Direction, &vecDir );

	//ディフューズ（拡散反射光）
	m_Light.Diffuse = D3DXCOLOR(0.5f,0.5f,0.5f,0.5f);
	
	//アンビエント（環境光）
	m_Light.Ambient = D3DXCOLOR(0.05f,0.05f,0.05f,0.05f);

	//スペキュラー（環境光）
	m_Light.Specular = D3DXCOLOR(0.1f,0.1f,0.1f,0.1f);

	//ライトをレンダリングパイプラインに設定
	m_pD3DDevice->SetLight( m_nLightIndex, &m_Light );

	//ライトの設定
	m_pD3DDevice->LightEnable( m_nLightIndex, TRUE );

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	m_pD3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );

	m_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL );
}

CObjectDirectionLight::~CObjectDirectionLight(){

}

void CObjectDirectionLight::SetVecDirection( D3DXVECTOR3 vecDir ){
	// ライトの向き変更
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_Light.Direction, &vecDir );
	//ライトをレンダリングパイプラインに設定
	m_pD3DDevice->SetLight( m_nLightIndex, &m_Light );
}


void SetDiffuse( D3DXCOLOR Diffuse );

void SetAmbient( D3DXCOLOR Ambient );

void SetSpecular( D3DXCOLOR Specular );

void CObjectDirectionLight::SwitchLight( bool bSwitch ) {
	// ライトのON,OFF切り替え
	m_pD3DDevice->LightEnable( m_nLightIndex, bSwitch );
}