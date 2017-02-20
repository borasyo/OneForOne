//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
//[Window.h]
// author : �哴�ˑ�
// 
// Window�����v���O�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____WINDOW_H_____
#define _____WINDOW_H_____

#include <Windows.h>	// �E�B���h�E�쐬�p
#include <tchar.h>		// Unicode

class CWindow {

public:
	static	CWindow* Create(); // WindowClass�̃N���G�C�g�֐�

	~CWindow(){};

	// Window�쐬(�f�t�H���g�T�C�Y��800�~600���w��)
	HRESULT MakeWindow(	LPTSTR WindowName, HINSTANCE& hInstance,
						const int& ClientWidth = 800, const int& ClientHeight = 600 );

	// Window�\��
	HRESULT Show();

	// �E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WindowProc( HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam );
	
	// ���b�Z�[�W�̏����֐�
	bool HandleMessage();

	// ----- �Q�b�^�[ -----
	int	GetExitValue( void )const{ return m_MessageInfo.wParam; }		// �I���R�[�h�̎擾�֐�
	HWND GetWindowHandle()const{ return m_WindowHandle; }				// �E�B���h�E�n���h���̎擾�֐�
	LPTSTR GetName()const{ return m_WindowName; }						// �E�B���h�E�̖��O�擾�֐�
	int GetClientWidth(){ return m_ClientWidth; }						// �N���C�A���g�̈�̕��擾�֐�
	int GetClientHeight(){ return m_ClientHeight; }						// �N���C�A���g�̈�̍����擾�֐�
	int GetWindowWidth()const{ return m_WindowWidth; }					// �E�B���h�E�̕��擾�֐�
	int	GetWindowHeight()const{ return m_WindowHeight; }				// �E�B���h�E�̍����擾�֐�
	float WindowAspect() const{ return (float)m_ClientWidth/(float)m_ClientHeight; }  // �A�X�y�N�g����擾

	// ---- �Z�b�^�[ ----
	void SetWidth(int nWidth){ m_ClientWidth = m_WindowWidth = nWidth; }
	void SetHeight(int nHeight){ m_ClientHeight = m_WindowHeight = nHeight; }

private:
	// �R���X�g���N�^
	CWindow();

	//===== �����o�ϐ� =====
private:
	HWND		m_WindowHandle;		// �E�B���h�E�n���h��
	MSG			m_MessageInfo;		// ���b�Z�[�W���
	WNDCLASSEX	m_Wcex;				// �E�B���h�E�N���X
	LPTSTR		m_WindowName;		// �E�B���h�E�̖��O
	int			m_ClientWidth;		// �N���C�A���g�̈�̕�
	int			m_ClientHeight;		// �N���C�A���g�̈�̍���
	int			m_WindowWidth;		// �E�B���h�E�̕�
	int			m_WindowHeight;		// �E�B���h�E�̍���
};

#endif