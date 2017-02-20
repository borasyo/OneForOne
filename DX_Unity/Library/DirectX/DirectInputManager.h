//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DirectInputManager.cpp]
// author : �哴�ˑ�
// 
// �T�v : ���͊֌W���Ǘ�����B
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

// �}�N����`
#define	NUM_KEY_MAX	(256)

//-------- �W���C�X�e�B�b�N�֌W
#define JOY_X			0			// �w��
#define JOY_Y			1			// �x��

//-------- �Q�[���p�b�h�֌W
#define MAX_JOY			4			// �ő�F���ڑ���
#define JOY_MIN_X		-32768		// �w���ŏ��l
#define JOY_MAX_X		32767		// �w���ő�l
#define JOY_MIN_Y		-32768		// �x���ŏ��l
#define JOY_MAX_Y		32767		// �x���ő�l

struct DirectKeyboard {
	
	LPDIRECTINPUTDEVICE8 pDirectInputKeyboard;	// �L�[�{�[�h�f�o�C�X
	BYTE aKeyboardData[NUM_KEY_MAX];			// �L�[�{�[�h�̏��(����)
	BYTE aKeyboardLastData[NUM_KEY_MAX];		// �L�[�{�[�h�̏��(�P�t���[���O)
};

struct DirectMouse {
	
	LPDIRECTINPUTDEVICE8 pDirectInputMouse;	// �}�E�X�f�o�C�X
	DIMOUSESTATE MouseData;					// �}�E�X�̏��(����)
	DIMOUSESTATE MouseLastData;				// �}�E�X�̏��(����)
};

// �N���X��`
class CDirectInputManager{

public:
	~CDirectInputManager();

	static CDirectInputManager* Instance() { return m_pDirectInputManager; }

	HRESULT Init( HWND WindowHandle );	// �������֐�
	HRESULT Update();					// �X�V�֐�
	HRESULT Uninit();					// �I������
	
	bool GetKeyboardHold(int KeyState);		// ������Ă��邩
	bool GetKeyboardTrigger(int KeyState);	// �����ꂽ�u�Ԃ�
	bool GetKeyboardRelease(int KeyState);	// �����ꂽ�u�Ԃ�

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

	bool GetMouseHold(int MouseState);		// ������Ă��邩
	bool GetMouseTrigger(int MouseState);	// �����ꂽ�u�Ԃ�
	bool GetMouseRelease(int MouseState);	// �����ꂽ�u�Ԃ�
	D3DXVECTOR3 GetMouseMove();				// �ړ���
	LONG GetMouseMoveX();					// �ړ���X
	LONG GetMouseMoveY();					// �ړ���Y
	LONG GetMouseMoveZ();					// �ړ���Z
	
	// W or ���X�e�B�b�N��O�ɂ����Ƃ���True
	bool GetForwardTrigger() { return (GetKeyboardTrigger(DIK_W) || GetJoyAxisTrigger(0, JOY_Y) < 0); }
	bool GetForwardHold() { return (GetKeyboardHold(DIK_W) || GetJoyAxisPress(0, JOY_Y) < 0); }
	
	// S or ���X�e�B�b�N��O�ɂ����Ƃ���True
	bool GetBackTrigger() { return (GetKeyboardTrigger(DIK_S) || GetJoyAxisTrigger(0, JOY_Y) > 0); }
	bool GetBackHold() { return (GetKeyboardHold(DIK_S) || GetJoyAxisPress(0, JOY_Y) > 0); }
	
	// A or ���X�e�B�b�N��O�ɂ����Ƃ���True
	bool GetLeftTrigger() { return (GetKeyboardTrigger(DIK_A) || GetJoyAxisTrigger(0, JOY_X) < 0); }
	bool GetLeftHold() { return (GetKeyboardHold(DIK_A) || GetJoyAxisPress(0, JOY_X) < 0); }
	
	// D or ���X�e�B�b�N��O�ɂ����Ƃ���True
	bool GetRightTrigger() { return (GetKeyboardTrigger(DIK_D) || GetJoyAxisTrigger(0, JOY_X) > 0); }
	bool GetRightHold() { return (GetKeyboardHold(DIK_D) || GetJoyAxisPress(0, JOY_X) > 0); }

private:
	CDirectInputManager();
	
	HRESULT UpdataKeyboard();	// �L�[�{�[�h�X�V�֐�
	HRESULT UpdataMouse();		// �}�E�X�X�V�֐�
	HRESULT UpdataJoy();		// �W���C�p�b�h�X�V�֐�

private:
	static CDirectInputManager* m_pDirectInputManager;
	
	static LPDIRECTINPUT8	m_pDirectInput;		//	DirectInput�I�u�W�F�N�g
	DirectKeyboard			m_DirectKeyboard;	//	�L�[�{�[�h
	DirectMouse				m_DirectMouse;		//	�}�E�X
};

#endif