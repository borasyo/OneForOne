//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FPSController.h]
// author : 大洞祥太
//
// FPS管理
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FPSCONTROLLER_H_____
#define _____FPSCONTROLLER_H_____

#pragma comment(lib,"winmm.lib")
#include <Windows.h>
#include <MMSystem.h>
#include <iostream>
#include "../DirectX/Direct3D.h"
#include "../DirectX/Window.h"
#include "d3dx9.h"

class FPSController{
public:

	// インスタンス取得
	static FPSController* FPSController::Create(){
		static FPSController* fpsController = new FPSController;
		return fpsController;
	}

	void Init(){

		// 取得
		m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
		m_pWindow = CWindow::Create();

		// 情報表示用フォントを設定
		D3DXCreateFontA(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pD3DXFont);
	}

	bool CheckExec(){
		
		m_dwCurrentTime = timeGetTime();
		if((m_dwCurrentTime - m_dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
		{
			m_nCountFPS = m_dwFrameCount * 1000 / (m_dwCurrentTime - m_dwFPSLastTime);
			m_dwFPSLastTime = m_dwCurrentTime;
			m_dwFrameCount = 0;
		}

		if((m_dwCurrentTime - m_dwExecLastTime) >= (1000 / 60))
		{
			m_dwExecLastTime = m_dwCurrentTime;
			m_dwFrameCount++;
			return true;
		}

		return false;
	}

	void DrawFPS(){
#if 0
		//if( m_nCountFPS >= 50 )
		//	return;
		
		RECT rect = {0, 10, m_pWindow->GetClientWidth(), m_pWindow->GetClientHeight()};
		char str[256];

		wsprintfA(str, "FPS : %d\n", m_nCountFPS);

		// テキスト描画
		m_pD3DXFont->DrawTextA(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
#endif
	}

	// FPS取得
	int GetFPS() { return m_nCountFPS; }

private:
	
	FPSController(){
		//フレームカウント初期化
		timeBeginPeriod(1);				// 分解能を設定
		m_dwExecLastTime = m_dwFPSLastTime = timeGetTime();
		m_dwCurrentTime = m_dwFrameCount = m_nCountFPS = 0;
		m_pFPSController = nullptr;
	}
	
	DWORD m_dwExecLastTime;
	DWORD m_dwFPSLastTime;
	DWORD m_dwCurrentTime;
	DWORD m_dwFrameCount;
	int m_nCountFPS;
	
	FPSController* m_pFPSController;
	LPD3DXFONT m_pD3DXFont;		// フォントへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice; // DirectXDevice
	CWindow* m_pWindow;
};

#endif