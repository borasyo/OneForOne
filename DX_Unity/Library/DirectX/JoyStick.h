//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [JoyStick.h]
// author : 大洞祥太
// 
// 概要 : ジョイスティック関連取得
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once

#include <windows.h>
#include <tchar.h>
#include <dinput.h>					// DirectJoyStick 関連のヘッダ

//-------- ジョイスティック関係
#define JOY_X			0			// Ｘ軸
#define JOY_Y			1			// Ｙ軸

//-------- ゲームパッド関係
#define MAX_JOY			4			// 最大認識接続数
#define JOY_MIN_X		-32768		// Ｘ軸最小値
#define JOY_MAX_X		32767		// Ｘ軸最大値
#define JOY_MIN_Y		-32768		// Ｙ軸最小値
#define JOY_MAX_Y		32767		// Ｙ軸最大値

#define	JOY_MOVE_NON	0.3			// 軸の遊び値(0.0f ～ 1.0f

#define JOYBUTTON_01 0
#define JOYBUTTON_02 1
#define JOYBUTTON_03 2
#define JOYBUTTON_04 3
#define JOYBUTTON_05 4
#define JOYBUTTON_06 5
#define JOYBUTTON_07 6
#define JOYBUTTON_08 7
#define JOYBUTTON_09 8
#define JOYBUTTON_10 9
#define JOYBUTTON_11 10
#define JOYBUTTON_12 11
#define JOYBUTTON_13 12
#define JOYBUTTON_14 13

class JoyStick
{
private:
	static LPDIRECTINPUT8		m_pDI;						// DirectJoyStick8 オブジェクト
	static LPDIRECTINPUTDEVICE8	m_pDIDeviceKey;				// DirectJoyStickDevice8 オブジェクト
	static LPDIRECTINPUTDEVICE8	m_pDIDeviceJoy[MAX_JOY];	// DirectJoyStickDevice8 オブジェクト
	static DIJOYSTATE			m_diJoyState[MAX_JOY];		// ジョイスティック情報取得バッファ
	static DIJOYSTATE			m_diPrevJoyState[MAX_JOY];	// 直前のジョイスティック情報
	static int					m_nJoy;						// ジョイスティック接続数
	
	static LONG					m_OldAxisX[MAX_JOY];		//	前フレームのX軸傾き
	static LONG					m_OldAxisY[MAX_JOY];		//	前フレームのY軸傾き

public:
	JoyStick(void);
	virtual ~JoyStick();

	static void Init(HWND hWnd);
	static void Update();
	static void Uninit();

	//----- パッド
	static int		GetNumJoystick(void);
	static bool		GetJoyPress(int nJoy , int nButton);
	static int		GetJoyPressButton(int nJoy);
	static bool		GetJoyTrigger(int nJoy, int nButton);
	static int		GetJoyTriggerButton(int nJoy);
	static bool		GetJoyRelease(int nJoy, int nButton);
	static float	GetJoyAxisPress(int nJoy, int nAxis);
	static float	GetJoyAxisTrigger(int nJoy, int nAxis);
	static bool	GetJoyAxisRelease(int nJoy, int nAxis);
	static float	GetJoyAxisDegree( int nJoy );
	static int		GetJoyCross( int nJoy, int nPov = 0 );

private:
	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

	// 軸が動いたか判定（PS4コントローラ等に使えるよ
	static bool CheckMoveAxis( int nJoy );
	static long Vec2Distance( long X, long Y );
};