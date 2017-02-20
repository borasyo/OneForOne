//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Direct3D.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DIRECT3D_H_____
#define _____DIRECT3D_H_____

#pragma	comment(lib, "d3dx9.lib")
#pragma	comment(lib, "d3d9.lib")
#include "d3d9.h"
#include "d3dx9.h"
#include "Window.h"

class CDirect3D {
public:
	~CDirect3D();

	// クリエイト関数
	static	CDirect3D* Create( CWindow* pcWindow );
	static	CDirect3D* Create();

	// 初期化関数
	HRESULT InitDirect3D();

	void Clear();
	HRESULT BeginScene();
	void EndScene();
	void Present();

	// ゲッター
	const LPDIRECT3DDEVICE9 GetDirect3DDevice(){ return m_pD3DDevice; }

private:
	CDirect3D( CWindow* pcWindow );

	void InitRender();

public:
private:
	CWindow* m_pWindow;
	static CDirect3D* m_pCDirect3D;
	LPDIRECT3D9	m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	bool m_bWindowMode;
};

#endif