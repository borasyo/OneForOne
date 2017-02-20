//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DirectInputManager.cpp]
// author : 大洞祥太
// 
//  概要 : 入力関係を管理する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "DirectInputManager.h"
//#include "../Function/Define.h"
#include <functional>
#include <initializer_list>

CDirectInputManager* CDirectInputManager::m_pDirectInputManager = new CDirectInputManager;
LPDIRECTINPUT8 CDirectInputManager::m_pDirectInput;


CDirectInputManager::CDirectInputManager() {
	m_pDirectInput = nullptr;
	m_DirectKeyboard.pDirectInputKeyboard = nullptr;
	m_DirectMouse.pDirectInputMouse = nullptr;
}

CDirectInputManager::~CDirectInputManager(){
}

// 初期化関数
HRESULT CDirectInputManager::Init( HWND WindowHandle ){

	// エラーが出ないかチェック
	if( FAILED(DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL )) ){
		return E_FAIL;
	}
	//------------------------ キーボードの初期化 ----------------------------//
	
	// キーボードデバイスの作成
	if (FAILED(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_DirectKeyboard.pDirectInputKeyboard, NULL)))
		return E_FAIL;

	// データフォーマットをキーボード用にセット
	m_DirectKeyboard.pDirectInputKeyboard->SetDataFormat(&c_dfDIKeyboard);

	// 協調レベルの設定
	m_DirectKeyboard.pDirectInputKeyboard->SetCooperativeLevel(WindowHandle, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// データ取得開始
	m_DirectKeyboard.pDirectInputKeyboard->Acquire();

	//------------------------ マウスの初期化 ----------------------------//

	// マウスデバイスの生成
	if (FAILED(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_DirectMouse.pDirectInputMouse, NULL)))
		return E_FAIL;

	// データフォーマットをマウス用にセット
	m_DirectMouse.pDirectInputMouse->SetDataFormat(&c_dfDIMouse2);

	// 協調レベルの設定
	m_DirectMouse.pDirectInputMouse->SetCooperativeLevel(WindowHandle, DISCL_EXCLUSIVE | DISCL_BACKGROUND);

	// データ取得開始
	m_DirectMouse.pDirectInputMouse->Acquire();

	//------------------------ ジョイスティックの初期化 ----------------------------//
	JoyStick::Init(WindowHandle);

	return S_OK;
}

// 更新関数s
HRESULT CDirectInputManager::Update(){
	
	if(FAILED(UpdataKeyboard()))
		return E_FAIL;

	if(FAILED(UpdataMouse()))
		return E_FAIL;

	if(FAILED(UpdataJoy()))
		return E_FAIL;

	return S_OK;
}

// 終了処理
HRESULT CDirectInputManager::Uninit(){
	m_pDirectInput->Release();
	m_DirectKeyboard.pDirectInputKeyboard->Release();
	m_DirectMouse.pDirectInputMouse->Release();
	
	JoyStick::Uninit();

	return S_OK;
}

// キーの押下状態習得
bool CDirectInputManager::GetKeyboardHold(int nKeyState){
	return (m_DirectKeyboard.aKeyboardData[nKeyState] & 0x80) ? true : false;
}

// キーの押下状態習得(押された瞬間)
bool CDirectInputManager::GetKeyboardTrigger(int nKeyState){
	return (m_DirectKeyboard.aKeyboardData[nKeyState] & 0x80) && !(m_DirectKeyboard.aKeyboardLastData[nKeyState] & 0x80) ? true : false;
}

// キーの押下状態習得(離した瞬間)
bool CDirectInputManager::GetKeyboardRelease(int nKeyState){
	return !(m_DirectKeyboard.aKeyboardData[nKeyState] & 0x80) && (m_DirectKeyboard.aKeyboardLastData[nKeyState] & 0x80) ? true : false;
}

// 更新処理
HRESULT CDirectInputManager::UpdataKeyboard(){
	
	// 習得＆更新
	m_DirectKeyboard.pDirectInputKeyboard->Acquire();
	memcpy( m_DirectKeyboard.aKeyboardLastData, m_DirectKeyboard.aKeyboardData, NUM_KEY_MAX );
	m_DirectKeyboard.pDirectInputKeyboard->GetDeviceState( NUM_KEY_MAX, m_DirectKeyboard.aKeyboardData );

	return S_OK;
}

HRESULT CDirectInputManager::UpdataMouse(){

	// 習得＆更新
	m_DirectMouse.pDirectInputMouse->Acquire();
	m_DirectMouse.MouseLastData = m_DirectMouse.MouseData;
	m_DirectMouse.pDirectInputMouse->GetDeviceState( sizeof(DIMOUSESTATE2), &m_DirectMouse.MouseData );
	
	return S_OK;
}

HRESULT CDirectInputManager::UpdataJoy() {
	
	// 更新
	JoyStick::Update();

	return S_OK;
}

// マウスの押下状態習得
bool CDirectInputManager::GetMouseHold(int nMouseState){
	return (m_DirectMouse.MouseData.rgbButtons[nMouseState] & 0x80) ? true : false;
}

// マウスの押下状態習得(押された瞬間)
bool CDirectInputManager::GetMouseTrigger(int nMouseState){
	return (m_DirectMouse.MouseData.rgbButtons[nMouseState] & 0x80) && !(m_DirectMouse.MouseLastData.rgbButtons[nMouseState] & 0x80) ? true : false;
}

// マウスの押下状態習得(離した瞬間)
bool CDirectInputManager::GetMouseRelease(int nMouseState){
	return !(m_DirectMouse.MouseData.rgbButtons[nMouseState] & 0x80) && (m_DirectMouse.MouseLastData.rgbButtons[nMouseState] & 0x80) ? true : false;
}

// マウスの移動量を取得
D3DXVECTOR3 CDirectInputManager::GetMouseMove(){
	return D3DXVECTOR3( (float)GetMouseMoveX(), (float)GetMouseMoveY(), (float)GetMouseMoveZ() );
}

// ----- マウスの移動をチェック
LONG CDirectInputManager::GetMouseMoveX(){
	if( m_DirectMouse.MouseData.lX < -1 || m_DirectMouse.MouseData.lX > 1 ){
		return m_DirectMouse.MouseData.lX;
	}
	return NULL;
}

LONG CDirectInputManager::GetMouseMoveY() {
	if( m_DirectMouse.MouseData.lY < -1 || m_DirectMouse.MouseData.lY > 1 ){
		return m_DirectMouse.MouseData.lY;
	}
	return NULL;
}

LONG CDirectInputManager::GetMouseMoveZ() {
	if( m_DirectMouse.MouseData.lZ < -1 || m_DirectMouse.MouseData.lZ > 1 ){
		return m_DirectMouse.MouseData.lZ;
	}
	return NULL;
}