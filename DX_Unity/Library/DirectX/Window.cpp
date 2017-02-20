//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Window.cpp]
// author : �哴�ˑ�
// 
//  Window�����v���O�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Window.h"

// �R���X�g���N�^
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

// �N���G�C�g�֐�
CWindow* CWindow::Create(){
	static CWindow* pWindow = new CWindow;
	return pWindow;
}

// �E�B���h�E�����֐�
HRESULT CWindow::MakeWindow( LPTSTR WindowName, HINSTANCE& hInstance,
							const int& ClientWidth, const int& ClientHeight ){
	// �E�B���h�E�̖��O���X�V����
	m_WindowName	= WindowName;
	// �E�B���h�E�̃T�C�Y���X�V����
	m_ClientWidth	= ClientWidth;
	m_ClientHeight	= ClientHeight;

	ZeroMemory(static_cast<LPVOID>(&m_Wcex), sizeof(WNDCLASSEX));

	// WNDCLASSEX�̒�`
	m_Wcex.cbSize			= sizeof(WNDCLASSEX);					// WNDCLASSEX�̃������T�C�Y���w��
	m_Wcex.style			= CS_CLASSDC;							// �\������E�B���h�E�̃X�^�C�����w��
	m_Wcex.lpfnWndProc		= CWindow::WindowProc;					// �E�B���h�E�v���V�[�W���̃A�h���X
	m_Wcex.cbClsExtra		= 0L;									// ���ʂ͎g�p���Ȃ��i"0"���w��j window-class structure.(�E�B���h�E�N���X�ɃA���P�[�g����ǉ��o�C�g�����w�肷��H)
	m_Wcex.cbWndExtra		= 0L;									// ���ʂ͎g�p���Ȃ��i"0"���w��j window instance�i�E�B���h�E�C���X�^���X�ɃA���P�[�g����ǉ��o�C�g�����w�肷��H�j
	m_Wcex.hInstance		= GetModuleHandle(nullptr);				// WinMain�̃C���X�^���X�n���h����ݒ�
	m_Wcex.hIcon			= nullptr;								// �A�C�R���w��(�f�t�H�Ȃ�NULL)
	m_Wcex.hCursor			= LoadCursor(nullptr, IDC_ARROW);		// �}�E�X�J�[�\�����w��
	m_Wcex.hbrBackground	= nullptr;								// �N���C�A���g�̈�w�i���f�t�H�F��
	m_Wcex.lpszMenuName		= nullptr;								// Window�ɂ��郁�j���[��ݒ�
	m_Wcex.lpszClassName	= _T("Window");							// �E�B���h�E�N���X�̖��O
	m_Wcex.hIconSm			= nullptr;								// ���A�C�R���ݒ�̏����L�q

	//Entry m_wcex
	RegisterClassEx(&m_Wcex);

	RECT rect = { 0, 0, ClientWidth, ClientHeight };
	AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);

	//�E�B���h�EHandle���쐬
	m_WindowHandle = CreateWindow(	_T("Window"),
									m_WindowName,
									WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,				// �E�B���h�E�^�C�v
									CW_USEDEFAULT,										// �E�B���h�Ex���W
									CW_USEDEFAULT,										// �E�B���h�Ey���W
									m_WindowWidth = (m_ClientWidth + GetSystemMetrics(SM_CXDLGFRAME) * 2),	// �E�B���h�E��
									m_WindowHeight = (m_ClientHeight + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),		// �E�B���h�E����
									GetDesktopWindow(),
									nullptr,
									m_Wcex.hInstance,
									nullptr);

	// �����ł����Ȃ�OK,���s�Ȃ�FAIL
	if (m_WindowHandle != nullptr)
		return S_OK;
	else
		return E_FAIL;
}

// �E�B���h�E�̕\���֐�
HRESULT CWindow::Show( void ){
	if (m_WindowHandle != nullptr){

		ShowWindow(m_WindowHandle, SW_SHOWDEFAULT);
		UpdateWindow(m_WindowHandle);
		
	#if 1
		// �}�E�X�ړ�����
		RECT rc;
		GetClientRect(m_WindowHandle, &rc);

		//�N���C�A���g�̈����ʍ��W�ɕϊ�����
		POINT pt = { rc.left, rc.top };
		POINT pt2 = { rc.right, rc.bottom };
		ClientToScreen(m_WindowHandle, &pt);
		ClientToScreen(m_WindowHandle, &pt2);
		SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);

		//�J�[�\���̓���͈͂𐧌�����
		ClipCursor(&rc);
	#endif

		return S_OK;
	}else
		return E_FAIL;
}

// ���b�Z�[�W�̏����֐�
bool CWindow::HandleMessage(){
	// �|�X�g�ς݃��b�Z�[�W�̏���
	while (PeekMessage(&m_MessageInfo, nullptr, 0, 0, PM_REMOVE)){
		// WM_QUIT���b�Z�[�W�̏���
		if (m_MessageInfo.message == WM_QUIT){
			return false;
		}
		// WM_QUIT�ȊO�̃��b�Z�[�W�̏���
		TranslateMessage(&m_MessageInfo);
		DispatchMessage(&m_MessageInfo);
	}
	return true;
}


// �E�B���h�E�v���V�[�W��
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