//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Window.cpp]
// author : 大洞祥太
// 
//  Window生成プログラム。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Window.h"

// コンストラクタ
CWindow::CWindow()
	: m_WindowHandle(nullptr)
	, m_MessageInfo()
	, m_WindowName(_T("Window"))
	, m_ClientWidth(0)
	, m_ClientHeight(0)
	, m_WindowWidth(0)
	, m_WindowHeight(0){
	ZeroMemory(&m_MessageInfo, sizeof(m_MessageInfo));
}

// クリエイト関数
CWindow* CWindow::Create(){
	static CWindow* pWindow = new CWindow;
	return pWindow;
}

// ウィンドウ生成関数
HRESULT CWindow::MakeWindow( LPTSTR WindowName, HINSTANCE& hInstance,
							const int& ClientWidth, const int& ClientHeight ){
	// ウィンドウの名前を更新する
	m_WindowName	= WindowName;
	// ウィンドウのサイズを更新する
	m_ClientWidth	= ClientWidth;
	m_ClientHeight	= ClientHeight;

	ZeroMemory(static_cast<LPVOID>(&m_Wcex), sizeof(WNDCLASSEX));

	// WNDCLASSEXの定義
	m_Wcex.cbSize			= sizeof(WNDCLASSEX);					// WNDCLASSEXのメモリサイズを指定
	m_Wcex.style			= CS_CLASSDC;							// 表示するウィンドウのスタイルを指定
	m_Wcex.lpfnWndProc		= CWindow::WindowProc;					// ウィンドウプロシージャのアドレス
	m_Wcex.cbClsExtra		= 0L;									// 普通は使用しない（"0"を指定） window-class structure.(ウィンドウクラスにアロケートする追加バイト数を指定する？)
	m_Wcex.cbWndExtra		= 0L;									// 普通は使用しない（"0"を指定） window instance（ウィンドウインスタンスにアロケートする追加バイト数を指定する？）
	m_Wcex.hInstance		= GetModuleHandle(nullptr);				// WinMainのインスタンスハンドルを設定
	m_Wcex.hIcon			= nullptr;								// アイコン指定(デフォならNULL)
	m_Wcex.hCursor			= LoadCursor(nullptr, IDC_ARROW);		// マウスカーソルを指定
	m_Wcex.hbrBackground	= nullptr;								// クライアント領域背景をデフォ色に
	m_Wcex.lpszMenuName		= nullptr;								// Windowにつけるメニューを設定
	m_Wcex.lpszClassName	= _T("Window");							// ウィンドウクラスの名前
	m_Wcex.hIconSm			= nullptr;								// 小アイコン設定の情報を記述

	//Entry m_wcex
	RegisterClassEx(&m_Wcex);

	RECT rect = { 0, 0, ClientWidth, ClientHeight };
	AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);

	//ウィンドウHandleを作成
	m_WindowHandle = CreateWindow(	_T("Window"),
									m_WindowName,
									WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,				// ウィンドウタイプ
									CW_USEDEFAULT,										// ウィンドウx座標
									CW_USEDEFAULT,										// ウィンドウy座標
									m_WindowWidth = (m_ClientWidth + GetSystemMetrics(SM_CXDLGFRAME) * 2),	// ウィンドウ幅
									m_WindowHeight = (m_ClientHeight + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),		// ウィンドウ高さ
									GetDesktopWindow(),
									nullptr,
									m_Wcex.hInstance,
									nullptr);

	// 生成できたならOK,失敗ならFAIL
	if (m_WindowHandle != nullptr)
		return S_OK;
	else
		return E_FAIL;
}

// ウィンドウの表示関数
HRESULT CWindow::Show( void ){
	if (m_WindowHandle != nullptr){

		ShowWindow(m_WindowHandle, SW_SHOWDEFAULT);
		UpdateWindow(m_WindowHandle);
		
	#if 1
		// マウス移動制限
		RECT rc;
		GetClientRect(m_WindowHandle, &rc);

		//クライアント領域を画面座標に変換する
		POINT pt = { rc.left, rc.top };
		POINT pt2 = { rc.right, rc.bottom };
		ClientToScreen(m_WindowHandle, &pt);
		ClientToScreen(m_WindowHandle, &pt2);
		SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);

		//カーソルの動作範囲を制限する
		ClipCursor(&rc);
	#endif

		return S_OK;
	}else
		return E_FAIL;
}

// メッセージの処理関数
bool CWindow::HandleMessage(){
	// ポスト済みメッセージの処理
	while (PeekMessage(&m_MessageInfo, nullptr, 0, 0, PM_REMOVE)){
		// WM_QUITメッセージの処理
		if (m_MessageInfo.message == WM_QUIT){
			return false;
		}
		// WM_QUIT以外のメッセージの処理
		TranslateMessage(&m_MessageInfo);
		DispatchMessage(&m_MessageInfo);
	}
	return true;
}


// ウィンドウプロシージャ
LRESULT CALLBACK CWindow::WindowProc( HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam ){
	switch ( uMessage ){
		
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWindow);
			break;
		}
		break;

	case WM_CLOSE:
		PostMessage(hWindow, WM_DESTROY, 0, 0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return(DefWindowProc(hWindow, uMessage, wParam, lParam));
	}
	return 0;
}