//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [JoyStick.h]
// author : �哴�ˑ�
// 
// �T�v : �W���C�X�e�B�b�N�֘A�擾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once

#include <windows.h>
#include <tchar.h>
#include <dinput.h>					// DirectJoyStick �֘A�̃w�b�_

//-------- �W���C�X�e�B�b�N�֌W
#define JOY_X			0			// �w��
#define JOY_Y			1			// �x��

//-------- �Q�[���p�b�h�֌W
#define MAX_JOY			4			// �ő�F���ڑ���
#define JOY_MIN_X		-32768		// �w���ŏ��l
#define JOY_MAX_X		32767		// �w���ő�l
#define JOY_MIN_Y		-32768		// �x���ŏ��l
#define JOY_MAX_Y		32767		// �x���ő�l

#define	JOY_MOVE_NON	0.3			// ���̗V�ђl(0.0f �` 1.0f

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
	static LPDIRECTINPUT8		m_pDI;						// DirectJoyStick8 �I�u�W�F�N�g
	static LPDIRECTINPUTDEVICE8	m_pDIDeviceKey;				// DirectJoyStickDevice8 �I�u�W�F�N�g
	static LPDIRECTINPUTDEVICE8	m_pDIDeviceJoy[MAX_JOY];	// DirectJoyStickDevice8 �I�u�W�F�N�g
	static DIJOYSTATE			m_diJoyState[MAX_JOY];		// �W���C�X�e�B�b�N���擾�o�b�t�@
	static DIJOYSTATE			m_diPrevJoyState[MAX_JOY];	// ���O�̃W���C�X�e�B�b�N���
	static int					m_nJoy;						// �W���C�X�e�B�b�N�ڑ���
	
	static LONG					m_OldAxisX[MAX_JOY];		//	�O�t���[����X���X��
	static LONG					m_OldAxisY[MAX_JOY];		//	�O�t���[����Y���X��

public:
	JoyStick(void);
	virtual ~JoyStick();

	static void Init(HWND hWnd);
	static void Update();
	static void Uninit();

	//----- �p�b�h
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

	// ����������������iPS4�R���g���[�����Ɏg�����
	static bool CheckMoveAxis( int nJoy );
	static long Vec2Distance( long X, long Y );
};