//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DirectInputManager.cpp]
// author : �哴�ˑ�
// 
//  �T�v : ���͊֌W���Ǘ�����B
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

// �������֐�
HRESULT CDirectInputManager::Init( HWND WindowHandle ){

	// �G���[���o�Ȃ����`�F�b�N
	if( FAILED(DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL )) ){
		return E_FAIL;
	}
	//------------------------ �L�[�{�[�h�̏����� ----------------------------//
	
	// �L�[�{�[�h�f�o�C�X�̍쐬
	if (FAILED(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_DirectKeyboard.pDirectInputKeyboard, NULL)))
		return E_FAIL;

	// �f�[�^�t�H�[�}�b�g���L�[�{�[�h�p�ɃZ�b�g
	m_DirectKeyboard.pDirectInputKeyboard->SetDataFormat(&c_dfDIKeyboard);

	// �������x���̐ݒ�
	m_DirectKeyboard.pDirectInputKeyboard->SetCooperativeLevel(WindowHandle, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// �f�[�^�擾�J�n
	m_DirectKeyboard.pDirectInputKeyboard->Acquire();

	//------------------------ �}�E�X�̏����� ----------------------------//

	// �}�E�X�f�o�C�X�̐���
	if (FAILED(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_DirectMouse.pDirectInputMouse, NULL)))
		return E_FAIL;

	// �f�[�^�t�H�[�}�b�g���}�E�X�p�ɃZ�b�g
	m_DirectMouse.pDirectInputMouse->SetDataFormat(&c_dfDIMouse2);

	// �������x���̐ݒ�
	m_DirectMouse.pDirectInputMouse->SetCooperativeLevel(WindowHandle, DISCL_EXCLUSIVE | DISCL_BACKGROUND);

	// �f�[�^�擾�J�n
	m_DirectMouse.pDirectInputMouse->Acquire();

	//------------------------ �W���C�X�e�B�b�N�̏����� ----------------------------//
	JoyStick::Init(WindowHandle);

	return S_OK;
}

// �X�V�֐�s
HRESULT CDirectInputManager::Update(){
	
	if(FAILED(UpdataKeyboard()))
		return E_FAIL;

	if(FAILED(UpdataMouse()))
		return E_FAIL;

	if(FAILED(UpdataJoy()))
		return E_FAIL;

	return S_OK;
}

// �I������
HRESULT CDirectInputManager::Uninit(){
	m_pDirectInput->Release();
	m_DirectKeyboard.pDirectInputKeyboard->Release();
	m_DirectMouse.pDirectInputMouse->Release();
	
	JoyStick::Uninit();

	return S_OK;
}

// �L�[�̉�����ԏK��
bool CDirectInputManager::GetKeyboardHold(int nKeyState){
	return (m_DirectKeyboard.aKeyboardData[nKeyState] & 0x80) ? true : false;
}

// �L�[�̉�����ԏK��(�����ꂽ�u��)
bool CDirectInputManager::GetKeyboardTrigger(int nKeyState){
	return (m_DirectKeyboard.aKeyboardData[nKeyState] & 0x80) && !(m_DirectKeyboard.aKeyboardLastData[nKeyState] & 0x80) ? true : false;
}

// �L�[�̉�����ԏK��(�������u��)
bool CDirectInputManager::GetKeyboardRelease(int nKeyState){
	return !(m_DirectKeyboard.aKeyboardData[nKeyState] & 0x80) && (m_DirectKeyboard.aKeyboardLastData[nKeyState] & 0x80) ? true : false;
}

// �X�V����
HRESULT CDirectInputManager::UpdataKeyboard(){
	
	// �K�����X�V
	m_DirectKeyboard.pDirectInputKeyboard->Acquire();
	memcpy( m_DirectKeyboard.aKeyboardLastData, m_DirectKeyboard.aKeyboardData, NUM_KEY_MAX );
	m_DirectKeyboard.pDirectInputKeyboard->GetDeviceState( NUM_KEY_MAX, m_DirectKeyboard.aKeyboardData );

	return S_OK;
}

HRESULT CDirectInputManager::UpdataMouse(){

	// �K�����X�V
	m_DirectMouse.pDirectInputMouse->Acquire();
	m_DirectMouse.MouseLastData = m_DirectMouse.MouseData;
	m_DirectMouse.pDirectInputMouse->GetDeviceState( sizeof(DIMOUSESTATE2), &m_DirectMouse.MouseData );
	
	return S_OK;
}

HRESULT CDirectInputManager::UpdataJoy() {
	
	// �X�V
	JoyStick::Update();

	return S_OK;
}

// �}�E�X�̉�����ԏK��
bool CDirectInputManager::GetMouseHold(int nMouseState){
	return (m_DirectMouse.MouseData.rgbButtons[nMouseState] & 0x80) ? true : false;
}

// �}�E�X�̉�����ԏK��(�����ꂽ�u��)
bool CDirectInputManager::GetMouseTrigger(int nMouseState){
	return (m_DirectMouse.MouseData.rgbButtons[nMouseState] & 0x80) && !(m_DirectMouse.MouseLastData.rgbButtons[nMouseState] & 0x80) ? true : false;
}

// �}�E�X�̉�����ԏK��(�������u��)
bool CDirectInputManager::GetMouseRelease(int nMouseState){
	return !(m_DirectMouse.MouseData.rgbButtons[nMouseState] & 0x80) && (m_DirectMouse.MouseLastData.rgbButtons[nMouseState] & 0x80) ? true : false;
}

// �}�E�X�̈ړ��ʂ��擾
D3DXVECTOR3 CDirectInputManager::GetMouseMove(){
	return D3DXVECTOR3( (float)GetMouseMoveX(), (float)GetMouseMoveY(), (float)GetMouseMoveZ() );
}

// ----- �}�E�X�̈ړ����`�F�b�N
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