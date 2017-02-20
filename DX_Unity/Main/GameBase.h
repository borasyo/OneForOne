//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameBase.h]
// author : 大洞祥太
// 
// ここでゲームループをを回す。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____GAMEBASE_H_____
#define _____GAMEBASE_H_____

#include "../Library/DirectX/Window.h"
#include "../Library/DirectX/Direct3D.h"
#include "../Library/Debug/FPSController.h"
#include "../Library/Task/Hierarchy.h"
#include "../Library/ObjectData/TextureManager.h"
#include "../Library/ObjectData/ModelManager.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/ObjectData/LightIndex.h"
#include "../Library/DirectX/MouthPosition.h"
#include "../Library/Task/SceneManager.h"

class CGameBase {

public:
	CGameBase();
	~CGameBase();

	// 実行
	int Run();
		
	// ---- ゲッター
	CDirect3D* GetDirect3D();			  // DirectX9取得
	LPDIRECT3DDEVICE9 GetDirectXDevice(); // Device取得
	CWindow* GetWindow();				  // Window取得
	HWND GetWindowHandle();				  // WindowHandle取得

private:
	
	bool Awake();	// システム初期化
	bool Start();	// ゲーム初期化
	void Update();	// 更新
	void Draw();	// 描画
	void Clear();	// 終了

private:
	Hierarchy* m_pHierarchy;
	CWindow* m_pWindow;
	FPSController* m_pFPSController;
	CTextureManager* m_pTextureManager;
	CDirectInputManager* m_pInputManager;
	CModelManager* m_pModelManager;
	CLightIndex* m_pLightIndex;
	CMouthPosition* m_pMouthPosition;
	SceneManager* m_pSceneManager;
public:
	CDirect3D* m_pDirect3D;
};

#endif