
#include "ObjectCamera.h"
#include "../DirectX/Direct3D.h"
#include "../DirectX/Window.h"

CObjectCamera::CObjectCamera()
	:m_LookatPt( 0.f, 0.f, 0.f )
	,m_UpVec( 0.f, 1.f, 0.f ) {
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	CWindow* pWindow = CWindow::Create();
	m_ViewPort.X = 0.0f;
	m_ViewPort.Y = 0.0f;
	m_ViewPort.Height = pWindow->GetClientHeight();
	m_ViewPort.Width = pWindow->GetClientWidth();
	m_ViewPort.MinZ = 0.0f;
	m_ViewPort.MaxZ = 1.0f;
}

CObjectCamera::~CObjectCamera(){

}

// カメラをセットする
void CObjectCamera::Set(D3DXVECTOR3 pos){

	m_pD3DDevice->SetViewport( &m_ViewPort );
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &pos, &m_LookatPt , &m_UpVec );
	m_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );
}

// ViewPortを設定
void CObjectCamera::SetViewPort( D3DVIEWPORT9 ViewPort ){
	m_ViewPort = ViewPort;
}

// ゲッター
D3DXVECTOR3* CObjectCamera::GetLookatPt(){
	return &m_LookatPt;
}

D3DXVECTOR3* CObjectCamera::GetUpVec(){
	return &m_UpVec;
}