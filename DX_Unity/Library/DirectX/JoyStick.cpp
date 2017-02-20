//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [JoyStick.cpp]
// author : 大洞祥太
// 
// 概要 : ジョイスティック関連取得
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "JoyStick.h"
#include <math.h>
#include <d3dx9.h>

#define	SAFE_RELEASE(p)		if(p){p->Release(); p = NULL;}

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

// 静的メンバ変数
LPDIRECTINPUT8			JoyStick::m_pDI = NULL;						// DirectJoyStick8 オブジェクト
LPDIRECTINPUTDEVICE8	JoyStick::m_pDIDeviceKey = NULL;			// DirectJoyStickDevice8 オブジェクト
LPDIRECTINPUTDEVICE8	JoyStick::m_pDIDeviceJoy[MAX_JOY] = {0};	// DirectJoyStickDevice8 オブジェクト
DIJOYSTATE				JoyStick::m_diJoyState[MAX_JOY] = {0};		// ジョイスティック情報取得バッファ
DIJOYSTATE				JoyStick::m_diPrevJoyState[MAX_JOY] = {0};	// 直前のジョイスティック情報
int						JoyStick::m_nJoy = 0;						// ジョイスティック接続数
LONG					JoyStick::m_OldAxisX[MAX_JOY] = {0};		// 前フレームのX軸傾き
LONG					JoyStick::m_OldAxisY[MAX_JOY] = {0};		// 前フレームのY軸傾き
TCHAR					g_szTitle[] = _T("JoyStick");

//	ジョイスティック問い合わせ用コールバック関数
BOOL CALLBACK JoyStick::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef) {
	DIDEVCAPS diDevCaps;			// デバイス情報

	// ジョイスティック用デバイスオブジェクトを作成
	HRESULT hr = m_pDI->CreateDevice(lpddi->guidInstance, &m_pDIDeviceJoy[m_nJoy], NULL);
	if (FAILED(hr))
		return DIENUM_CONTINUE;		// 列挙を続ける
	// ジョイスティックの能力を調べる
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = m_pDIDeviceJoy[m_nJoy]->GetCapabilities(&diDevCaps);
	if (FAILED(hr)) {
		SAFE_RELEASE(m_pDIDeviceJoy[m_nJoy]);
		return DIENUM_CONTINUE;		// 列挙を続ける
	}
	if (++m_nJoy < MAX_JOY)
		return DIENUM_CONTINUE;		// 列挙を続ける
	return DIENUM_STOP;		// 必要数揃ったので列挙を終了する
}


JoyStick::JoyStick() {
}


JoyStick::~JoyStick() {
}


void JoyStick::Init(HWND hWnd) {
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	// DirectJoyStickオブジェクトの作成
	HRESULT hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInput オブジェクトの作成に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//******** ジョイスティック用
	// DirectJoyStickDeviceオブジェクトの作成
	m_nJoy = 0;
	hr = m_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInputDevice オブジェクトの作成に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	for (int i = 0; i < m_nJoy; i++) {
		// データフォーマットの設定
		hr = m_pDIDeviceJoy[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectInput でデータフォーマットの設定に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}

		// 協調レベルの設定
		hr = m_pDIDeviceJoy[i]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectInputで協調レベルの設定に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}

		// デバイスの設定
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = DIJOFS_X;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_X;
		diprg.lMax       = JOY_MAX_X;
		m_pDIDeviceJoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);	// Ｘ方向の範囲を指定
		diprg.diph.dwObj = DIJOFS_Y;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_Y;
		diprg.lMax       = JOY_MAX_Y;
		m_pDIDeviceJoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);	// Ｙ方向の範囲を指定

		// デバイスへの入力制御開始
		hr = m_pDIDeviceJoy[i]->Acquire();
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectJoyStick でデバイスへの入力制御開始に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}
	}
}


void JoyStick::Uninit() {
	for (int i = 0; i < m_nJoy; i++) {
		if (m_pDIDeviceJoy[i])
			m_pDIDeviceJoy[i]->Unacquire();	// 入力を終了
		SAFE_RELEASE(m_pDIDeviceJoy[i]);	// DirectJoyStickDevice8 オブジェクトの解放
	}
	if (m_pDIDeviceKey)
		m_pDIDeviceKey->Unacquire();		// 入力を終了
	SAFE_RELEASE(m_pDIDeviceKey);			// DirectJoyStickDevice8 オブジェクトの解放
}


void JoyStick::Update() {
	
	// 前情報保存
	for(int i = 0; i < m_nJoy; i++) {
		m_OldAxisX[i] = m_diJoyState[i].lX;
		m_OldAxisY[i] = m_diJoyState[i].lY;
	}

	HRESULT hr;
	for (int i = 0; i < m_nJoy; i++) {
		m_diPrevJoyState[i] = m_diJoyState[i];

		m_pDIDeviceJoy[i]->Acquire();		// 要求を出す
		m_pDIDeviceJoy[i]->Poll();			// デバイス上のポーリング対象オブジェクトからデータを取得
		// 現在のジョイスティックの状態を取得
		hr = m_pDIDeviceJoy[i]->GetDeviceState(sizeof(m_diJoyState[0]), &m_diJoyState[i]);
		if (hr == DIERR_INPUTLOST)
			m_pDIDeviceJoy[i]->Acquire();	// 再度、要求を出す
	}
}

int JoyStick::GetNumJoystick(void) {
	return m_nJoy;
}

bool JoyStick::GetJoyPress(int nJoy, int nButton) {
	
	if (nJoy < 0 || nJoy >= m_nJoy) 
		return false;
	
	if (nButton < 0 || nButton >= 32) 
		return false;
	
	return (m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0;
}

bool JoyStick::GetJoyTrigger(int nJoy, int nButton) {
	
	if (nJoy < 0 || nJoy >= m_nJoy) 
		return false;
	
	if (nButton < 0 || nButton >= 32) 
		return false;
	
	return (m_diPrevJoyState[nJoy].rgbButtons[nButton] & 0x80) == 0 &&
		(m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0;
}

bool JoyStick::GetJoyRelease(int nJoy, int nButton) {
	
	if (nJoy < 0 || nJoy >= m_nJoy) 
		return false;
	
	if (nButton < 0 || nButton >= 32) 
		return false;
	
	return (m_diPrevJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0 &&
		(m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) == 0;
}

int JoyStick::GetJoyPressButton(int nJoy) {

	if( nJoy < 0 || nJoy >= m_nJoy )	
		return -1;

	for( int i = 0; i < 32; i ++ ) {
		if( ( m_diJoyState[nJoy].rgbButtons[i] & 0x80 ) != 0 ) {
			return i;
		}
	}
	return -1;
}

int JoyStick::GetJoyTriggerButton(int nJoy) {
	if( nJoy < 0 || nJoy >= m_nJoy )	
		return -1;

	for( int i = 0; i < 32; i ++ ) {
		if( ( m_diPrevJoyState[nJoy].rgbButtons[i] & 0x80 ) == 0 &&
			( m_diJoyState[nJoy].rgbButtons[i] & 0x80 ) != 0 )
		{
			return i;
		}
	}
	return -1;
}

float JoyStick::GetJoyAxisPress(int nJoy, int nAxis) {
	// 存在確認
	if (nJoy < 0 || nJoy >= m_nJoy) 
		return 0.0f;

	switch (nAxis) {
	case JOY_X:
		// 現フレームチェック
		if( abs(m_diJoyState[nJoy].lX) < JOY_MAX_X * JOY_MOVE_NON )
			return 0.0f;
		
		//	結果を返す
		return m_diJoyState[nJoy].lX;

	case JOY_Y:
		// 現フレームチェック
		if( abs(m_diJoyState[nJoy].lY) < JOY_MAX_Y * JOY_MOVE_NON )
			return 0.0f;
		
		//	結果を返す
		return m_diJoyState[nJoy].lY;

	default:
		break;
	}
	return 0.0f;
}

bool JoyStick::GetJoyAxisRelease(int nJoy, int nAxis) {
	// 存在確認
	if (nJoy < 0 || nJoy >= m_nJoy) 
		return 0.0f;

	switch (nAxis) {
	case JOY_X:
		//	結果を返す
		return (m_OldAxisX[nJoy] != m_diJoyState[nJoy].lX && 0 != m_OldAxisX[nJoy]);

	case JOY_Y:
		return (m_OldAxisY[nJoy] != m_diJoyState[nJoy].lY && 0 != m_OldAxisY[nJoy]);

	default:
		break;
	}
	return 0.0f;
}

//	右から時計回りに+,逆は-	
float JoyStick::GetJoyAxisDegree( int nJoy ) {
	// 例外確認
	if (nJoy < 0 || nJoy >= m_nJoy) 
		return -1000.0f;

	float X = (float)m_diJoyState[nJoy].lX;
	float Y = (float)m_diJoyState[nJoy].lY;

	// 動作確認
	if( !CheckMoveAxis(nJoy) )	
		return -1000.0f;

	// 角度抽出
	float rad = atan2f( Y, X );
	return D3DXToDegree( rad );
}

//	上から時計回りに+
int JoyStick::GetJoyCross( int nJoy, int nPov ) {
	return m_diJoyState[nJoy].rgdwPOV[nPov] == -1 ? -1 : m_diJoyState[nJoy].rgdwPOV[nPov] / 100;
}

bool JoyStick::CheckMoveAxis( int nJoy ) {
	// 軸の移動距離を求める
	long distance = Vec2Distance( m_diJoyState[nJoy].lX, m_diJoyState[nJoy].lY );

	// 判定距離
	long move = Vec2Distance( JOY_MAX_X, JOY_MAX_Y );
	move = (long)(move * JOY_MOVE_NON);

	return move <= distance;
}

long JoyStick::Vec2Distance( long X, long Y ) {
	return (long)sqrtl(X * X + Y * Y);
}