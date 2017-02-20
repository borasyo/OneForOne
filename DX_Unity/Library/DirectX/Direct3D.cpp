//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Direct3D.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Direct3D.h"

// --- 定数
const bool bWindowMode = true;

// 実体生成
CDirect3D* CDirect3D::m_pCDirect3D = nullptr;

CDirect3D::CDirect3D( CWindow* pWindow )
	:m_pWindow(pWindow)
	,m_pD3D(nullptr)
	,m_pD3DDevice(nullptr)
	,m_bWindowMode(bWindowMode){
}

CDirect3D::~CDirect3D(){
	if( m_pD3D )
		m_pD3D->Release();
	if( m_pD3DDevice )
		m_pD3DDevice->Release();
}

// クリエイト関数
CDirect3D* CDirect3D::Create( CWindow* pWindow ){
	static CDirect3D* pCDirect3D = new CDirect3D( pWindow );
	m_pCDirect3D = pCDirect3D;
	return pCDirect3D;
}

CDirect3D* CDirect3D::Create(){
	if( !m_pCDirect3D )
		return nullptr;
	return m_pCDirect3D;
}

// 初期化関数
HRESULT CDirect3D::InitDirect3D(){
	D3DPRESENT_PARAMETERS	d3dpp;
	D3DDISPLAYMODE			d3ddm;

	// Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if( m_pD3D == NULL )
		return E_FAIL;

	// 現在のディスプレイモードを習得
	if( FAILED( m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm) ) )
		return E_FAIL;

	// デバイスのプレゼンテーションパラメータの設定
	if( m_bWindowMode ){
		// ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.BackBufferHeight = m_pWindow->GetClientHeight();
		d3dpp.BackBufferWidth  = m_pWindow->GetClientWidth();
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.BackBufferCount  = 1;
		d3dpp.MultiSampleType  = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow		= NULL;
		d3dpp.Windowed			= TRUE;												
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.Flags				= 0;
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}
	else
	{
		//フルスク処理
		int ScreenCnt = m_pD3D->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8);
		int maxNo=0;
		D3DDISPLAYMODE    dspMax={0,0,0,D3DFMT_UNKNOWN};
		
		//最大サイズ取得
		for(int i=0;i<ScreenCnt;i++)
		{
			D3DDISPLAYMODE    d3dspMode;
			m_pD3D->EnumAdapterModes(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, i, &d3dspMode);
			if(i && dspMax.Width*dspMax.Height < d3dspMode.Width*d3dspMode.Height)
			{
				dspMax = d3dspMode;
				maxNo = i;
			}
			//DOM("x:%d y:%d Hz:%d\n",d3dspMode.Width,d3dspMode.Height,d3dspMode.RefreshRate);
		}

		m_pD3D->EnumAdapterModes(D3DADAPTER_DEFAULT ,D3DFMT_X8R8G8B8, maxNo ,&d3ddm);

		//フルスク設定
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		d3dpp.BackBufferWidth    = d3ddm.Width;    // 幅
		d3dpp.BackBufferHeight    = d3ddm.Height;    // 高さ
		d3dpp.BackBufferFormat    = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferCount    = 0;        // バックバッファの数
		d3dpp.MultiSampleType  = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect        = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow    = NULL;        // 表示目標ウィンドウ(貼り付け対象のウィンドウハンドルを入れてください)
		d3dpp.Windowed        = FALSE;    // フルスクリーンを指定
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags				= 0;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval    = D3DPRESENT_INTERVAL_DEFAULT;
		
		m_pWindow->SetHeight(d3ddm.Height);
		m_pWindow->SetWidth(d3ddm.Width);
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行う
	if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,					// ディスプレイアダプタ
									 D3DDEVTYPE_HAL,						// デバイスタイプ
									 m_pWindow->GetWindowHandle(),			// フォーカスするウィンドウへのハンドル
									 D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
									 &d3dpp,								// デバイスのプレゼンテーションパラメータ
									 &m_pD3DDevice)) )	{					// デバイスインターフェースへのポインタ

		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>とハードウェアで行い、<頂点処理>はCPUで行う
		if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,					// ディスプレイアダプタ
										 D3DDEVTYPE_HAL,						// デバイスタイプ
										 m_pWindow->GetWindowHandle(),			// フォーカスするウィンドウへのハンドル
										 D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
										 &d3dpp,								// デバイスのプレゼンテーションパラメータ
										 &m_pD3DDevice)) ){						// デバイスインターフェースへのポインタ
											 
			// 記の設定が失敗したら
			// デバイス作成制御]<描画>とハ<頂点処理>はCPUで行う
			if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,					// ディスプレイアダプタ
											 D3DDEVTYPE_REF,						// デバイスタイプ
											 m_pWindow->GetWindowHandle(),			// フォーカスするウィンドウへのハンドル
											 D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
											 &d3dpp,								// デバイスのプレゼンテーションパラメータ
											 &m_pD3DDevice)) ){						// デバイスインターフェースへのポインタ

				// 記の設定が失敗したら
				// デバイス作成制御]<描画>とハ<頂点処理>はCPUで行う
				if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,					// ディスプレイアダプタ
												 D3DDEVTYPE_REF,						// デバイスタイプ
												 m_pWindow->GetWindowHandle(),			// フォーカスするウィンドウへのハンドル
												 D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
												 &d3dpp,								// デバイスのプレゼンテーションパラメータ
												 &m_pD3DDevice)) ){						// デバイスインターフェースへのポインタ
					// 初期化失敗
					return E_FAIL;
				}
			}
		}
	}
	this->InitRender();
	return S_OK;
}

typedef struct{
	D3DXVECTOR3		pos; // 頂点座標
	float			rhw; // テクスチャのパースペクティブコレクト用
	D3DCOLOR		col; // 頂点カラー
	D3DXVECTOR2		tex; // テクスチャ座標
}VERTEX_2D;

// レンダー初期化
void CDirect3D::InitRender( void ){
	
	// テクスチャの設定
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// レンダーステートのパラメータの設定
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );			// 裏面をカリング
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );			// アルファブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );		// ソースの設定
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );	// ですとの設定

	// サンプラーステートパラメータの設定
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );	// テクスチャU値の繰り返し設定
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );	// テクスチャV値の繰り返し設定
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );	// テクスチャ拡大時の補間設定
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );	// テクスチャ拡小時の補間設定

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
		
	// ライト設定
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	// 環境光を設定する。
	m_pD3DDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_ARGB(64,64,64,64) );
	// ライトON
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	// 射影変換
	CWindow *window = CWindow::Create();
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, (float)window->GetWindowWidth()/(float)window->GetWindowHeight(), 1.f, 10000.f );
	m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

void CDirect3D::Clear( void ){
	m_pD3DDevice->Clear( 0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0,0,0,0), 1.0f, 0 );
}

HRESULT CDirect3D::BeginScene( void ){
	return m_pD3DDevice->BeginScene();
}

void CDirect3D::EndScene( void ){
	m_pD3DDevice->EndScene();
}

void CDirect3D::Present( void ){
	m_pD3DDevice->Present( NULL, NULL, NULL, NULL );
}