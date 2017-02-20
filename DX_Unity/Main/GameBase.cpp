//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameBase.cpp]
// author : 大洞祥太
// 
// ここでゲームループを回す。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "GameBase.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/DirectX/DirectSound.h"

// ---- 定数

// コンストラクタ
CGameBase::CGameBase()
	:m_pWindow(nullptr)
	,m_pDirect3D(nullptr)
	,m_pTextureManager(nullptr)
	,m_pInputManager(nullptr) 
	,m_pModelManager(nullptr)
	,m_pSceneManager(nullptr)
	,m_pFPSController(nullptr) {
}

// デストラクタ
CGameBase::~CGameBase(){
	Clear();
}

// ---- ゲームを走らせる
int CGameBase::Run()
{
	// システム初期化
	if( !Awake() ){
		return 0; //エラー
	}
	
	// ゲーム初期化
	if( !Start() ){
		Clear();
		return 0; //エラー
	}

	HRESULT hr;
	// ---- メインループ ----
	while( m_pWindow->HandleMessage() )
	{
		if( !m_pFPSController->CheckExec() )
			continue;

		// ---- 更新
		Update();

		// ---- 描画
		m_pDirect3D->Clear();
		hr = m_pDirect3D->BeginScene();
		Draw();
		m_pDirect3D->EndScene();
		m_pDirect3D->Present();
	}

	return m_pWindow->GetExitValue();
}

// システム初期化
bool CGameBase::Awake(){
	// ウインドウ作成
	m_pWindow = CWindow::Create();

	// HINSTANCE取得
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	// ウインドウ作成
	m_pWindow->MakeWindow( _T("One For One"), hInstance, 1050, 560 );
	
	// ウインドウの表示
	//m_pWindow->Show();

	// DirectX9生成初期化
	m_pDirect3D = CDirect3D::Create(m_pWindow);

	// DirectX9の初期化
	if( m_pDirect3D->InitDirect3D() ){
		return false;
	}
	
	// InputManager生成初期化
	m_pInputManager = CDirectInputManager::Instance();
	if( FAILED( m_pInputManager->Init(GetWindowHandle()) ) )
		return false;

	// TextureManager生成初期化
	m_pTextureManager = CTextureManager::Create();
	if( FAILED( m_pTextureManager->Init() ) )
		return false;

	// ModelManager生成初期化
	m_pModelManager = CModelManager::Create();
	if( FAILED( m_pModelManager->Init() ) )
		return false;

	// LightIndex生成
	m_pLightIndex = CLightIndex::Create();

	// MouthPos
	m_pMouthPosition = CMouthPosition::Create();
	m_pMouthPosition->Init();

	// シーンマネージャー生成
	m_pSceneManager = SceneManager::Create();

	// Sound初期化
	InitSound(m_pWindow->GetWindowHandle());

	// FPSコントローラ初期化
	m_pFPSController = FPSController::Create();
	m_pFPSController->Init();

	return true;
}

// 初期化処理
bool CGameBase::Start(){
	
	// Hierarchy生成初期化
	m_pHierarchy = Hierarchy::Create();
	m_pSceneManager->SetObject();
	
	// 全てのオブジェクトを初期化
	if( !m_pHierarchy->Start() )
		return false;
	
	// ウインドウの表示
	m_pWindow->Show();

	// Menu表示
	m_pSceneManager->Menu();

	return true;
}

// 更新処理
void CGameBase::Update(){

	// MouthPos更新
	m_pMouthPosition->Update();

	// DirectInput更新
	m_pInputManager->Update();

	// オブジェクト更新
	m_pHierarchy->Update();

	// マウスの移動制限を再設定
	if( m_pInputManager->GetKeyboardTrigger(DIK_RCONTROL) ) {

		// マウス移動制限
		RECT rc;
		GetClientRect(m_pWindow->GetWindowHandle(), &rc);

		//クライアント領域を画面座標に変換する
		POINT pt = { rc.left, rc.top };
		POINT pt2 = { rc.right, rc.bottom };
		ClientToScreen(m_pWindow->GetWindowHandle(), &pt);
		ClientToScreen(m_pWindow->GetWindowHandle(), &pt2);
		SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);

		//カーソルの動作範囲を制限する
		ClipCursor(&rc);
	}
}

// 描画処理
void CGameBase::Draw(){

	// オブジェクト描画
	m_pHierarchy->Draw();
	
	// FPS表示
	m_pFPSController->DrawFPS();
}

// 後処理
void CGameBase::Clear(){

	m_pModelManager->AllRelease();
	m_pMouthPosition->UnInit();
	UninitSound();

	// SingletonClassをdelete
	delete m_pModelManager;
	delete m_pInputManager;
	delete m_pTextureManager;
	delete m_pHierarchy;
	delete m_pDirect3D;
	delete m_pWindow;
	delete m_pLightIndex;
	delete m_pMouthPosition;
	delete m_pSceneManager;
	delete m_pFPSController;
}

// Direct3D取得
CDirect3D* CGameBase::GetDirect3D(){
	return m_pDirect3D;
}

// DirectX9device取得
LPDIRECT3DDEVICE9 CGameBase::GetDirectXDevice(){
	return m_pDirect3D->GetDirect3DDevice();
}

// Window取得
CWindow* CGameBase::GetWindow(){
	return m_pWindow;
}

// Handle取得
HWND CGameBase::GetWindowHandle(){
	return m_pWindow->GetWindowHandle();
}
