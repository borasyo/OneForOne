//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DirectInputManager.cpp]
// author : 大洞祥太
// 
// 概要 : 入力関係を管理する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DIRECT_INPUT_MANAGER_H_____
#define _____DIRECT_INPUT_MANAGER_H_____

#pragma	comment(lib, "dinput8.lib")
#pragma	comment(lib, "dxguid.lib")
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "JoyStick.h"

// マクロ定義
#define	NUM_KEY_MAX	(256)

//-------- ジョイスティック関係
#define JOY_X			0			// Ｘ軸
#define JOY_Y			1			// Ｙ軸

//-------- ゲームパッド関係
#define MAX_JOY			4			// 最大認識接続数
#define JOY_MIN_X		-32768		// Ｘ軸最小値
#define JOY_MAX_X		32767		// Ｘ軸最大値
#define JOY_MIN_Y		-32768		// Ｙ軸最小値
#define JOY_MAX_Y		32767		// Ｙ軸最大値

struct DirectKeyboard {
	
	LPDIRECTINPUTDEVICE8 pDirectInputKeyboard;	// キーボードデバイス
	BYTE aKeyboardData[NUM_KEY_MAX];			// キーボードの状態(現在)
	BYTE aKeyboardLastData[NUM_KEY_MAX];		// キーボードの状態(１フレーム前)
};

struct DirectMouse {
	
	LPDIRECTINPUTDEVICE8 pDirectInputMouse;	// マウスデバイス
	DIMOUSESTATE MouseData;					// マウスの状態(現在)
	DIMOUSESTATE MouseLastData;				// マウスの状態(現在)
};

// クラス定義
class CDirectInputManager{

public:
	~CDirectInputManager();

	static CDirectInputManager* Instance() { return m_pDirectInputManager; }

	HRESULT Init( HWND WindowHandle );	// 初期化関数
	HRESULT Update();					// 更新関数
	HRESULT Uninit();					// 終了処理
	
	bool GetKeyboardHold(int KeyState);		// 押されているか
	bool GetKeyboardTrigger(int KeyState);	// 押された瞬間か
	bool GetKeyboardRelease(int KeyState);	// 放された瞬間か

	int	GetNumJoystick() { return JoyStick::GetNumJoystick(); }
	bool GetJoyPress(int nJoy , int nButton) { return JoyStick::GetJoyPress(nJoy, nButton); }
	int	GetJoyPressButton(int nJoy) { return JoyStick::GetJoyPressButton(nJoy); }
	bool GetJoyTrigger(int nJoy, int nButton) { return JoyStick::GetJoyTrigger(nJoy, nButton); }
	int	GetJoyTriggerButton(int nJoy) { return JoyStick::GetJoyTriggerButton(nJoy); }
	bool GetJoyRelease(int nJoy, int nButton) { return JoyStick::GetJoyRelease(nJoy, nButton); }
	float GetJoyAxisPress(int nJoy, int nAxis) { return JoyStick::GetJoyAxisPress(nJoy, nAxis); }
	float GetJoyAxisTrigger(int nJoy, int nAxis) { return JoyStick::GetJoyAxisTrigger(nJoy, nAxis); }
	bool GetJoyAxisRelease(int nJoy, int nAxis) { return JoyStick::GetJoyAxisRelease(nJoy, nAxis); }
	float GetJoyAxisDegree(int nJoy) { return JoyStick::GetJoyAxisDegree(nJoy); }
	int	GetJoyCross(int nJoy, int nPov = 0) { return JoyStick::GetJoyCross(nJoy, nPov); }

	bool GetMouseHold(int MouseState);		// 押されているか
	bool GetMouseTrigger(int MouseState);	// 押された瞬間か
	bool GetMouseRelease(int MouseState);	// 放された瞬間か
	D3DXVECTOR3 GetMouseMove();				// 移動量
	LONG GetMouseMoveX();					// 移動量X
	LONG GetMouseMoveY();					// 移動量Y
	LONG GetMouseMoveZ();					// 移動量Z
	
	// W or 左スティックを前にしたときにTrue
	bool GetForwardTrigger() { return (GetKeyboardTrigger(DIK_W) || GetJoyAxisTrigger(0, JOY_Y) < 0); }
	bool GetForwardHold() { return (GetKeyboardHold(DIK_W) || GetJoyAxisPress(0, JOY_Y) < 0); }
	
	// S or 左スティックを前にしたときにTrue
	bool GetBackTrigger() { return (GetKeyboardTrigger(DIK_S) || GetJoyAxisTrigger(0, JOY_Y) > 0); }
	bool GetBackHold() { return (GetKeyboardHold(DIK_S) || GetJoyAxisPress(0, JOY_Y) > 0); }
	
	// A or 左スティックを前にしたときにTrue
	bool GetLeftTrigger() { return (GetKeyboardTrigger(DIK_A) || GetJoyAxisTrigger(0, JOY_X) < 0); }
	bool GetLeftHold() { return (GetKeyboardHold(DIK_A) || GetJoyAxisPress(0, JOY_X) < 0); }
	
	// D or 左スティックを前にしたときにTrue
	bool GetRightTrigger() { return (GetKeyboardTrigger(DIK_D) || GetJoyAxisTrigger(0, JOY_X) > 0); }
	bool GetRightHold() { return (GetKeyboardHold(DIK_D) || GetJoyAxisPress(0, JOY_X) > 0); }

private:
	CDirectInputManager();
	
	HRESULT UpdataKeyboard();	// キーボード更新関数
	HRESULT UpdataMouse();		// マウス更新関数
	HRESULT UpdataJoy();		// ジョイパッド更新関数

private:
	static CDirectInputManager* m_pDirectInputManager;
	
	static LPDIRECTINPUT8	m_pDirectInput;		//	DirectInputオブジェクト
	DirectKeyboard			m_DirectKeyboard;	//	キーボード
	DirectMouse				m_DirectMouse;		//	マウス
};

#endif