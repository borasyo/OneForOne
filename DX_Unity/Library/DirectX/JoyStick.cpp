//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [JoyStick.cpp]
// author : �哴�ˑ�
// 
// �T�v : �W���C�X�e�B�b�N�֘A�擾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "JoyStick.h"
#include <math.h>
#include <d3dx9.h>

#define	SAFE_RELEASE(p)		if(p){p->Release(); p = NULL;}

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

// �ÓI�����o�ϐ�
LPDIRECTINPUT8			JoyStick::m_pDI = NULL;						// DirectJoyStick8 �I�u�W�F�N�g
LPDIRECTINPUTDEVICE8	JoyStick::m_pDIDeviceKey = NULL;			// DirectJoyStickDevice8 �I�u�W�F�N�g
LPDIRECTINPUTDEVICE8	JoyStick::m_pDIDeviceJoy[MAX_JOY] = {0};	// DirectJoyStickDevice8 �I�u�W�F�N�g
DIJOYSTATE				JoyStick::m_diJoyState[MAX_JOY] = {0};		// �W���C�X�e�B�b�N���擾�o�b�t�@
DIJOYSTATE				JoyStick::m_diPrevJoyState[MAX_JOY] = {0};	// ���O�̃W���C�X�e�B�b�N���
int						JoyStick::m_nJoy = 0;						// �W���C�X�e�B�b�N�ڑ���
LONG					JoyStick::m_OldAxisX[MAX_JOY] = {0};		// �O�t���[����X���X��
LONG					JoyStick::m_OldAxisY[MAX_JOY] = {0};		// �O�t���[����Y���X��
TCHAR					g_szTitle[] = _T("JoyStick");

//	�W���C�X�e�B�b�N�₢���킹�p�R�[���o�b�N�֐�
BOOL CALLBACK JoyStick::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef) {
	DIDEVCAPS diDevCaps;			// �f�o�C�X���

	// �W���C�X�e�B�b�N�p�f�o�C�X�I�u�W�F�N�g���쐬
	HRESULT hr = m_pDI->CreateDevice(lpddi->guidInstance, &m_pDIDeviceJoy[m_nJoy], NULL);
	if (FAILED(hr))
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = m_pDIDeviceJoy[m_nJoy]->GetCapabilities(&diDevCaps);
	if (FAILED(hr)) {
		SAFE_RELEASE(m_pDIDeviceJoy[m_nJoy]);
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	}
	if (++m_nJoy < MAX_JOY)
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	return DIENUM_STOP;		// �K�v���������̂ŗ񋓂��I������
}


JoyStick::JoyStick() {
}


JoyStick::~JoyStick() {
}


void JoyStick::Init(HWND hWnd) {
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	// DirectJoyStick�I�u�W�F�N�g�̍쐬
	HRESULT hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInput �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//******** �W���C�X�e�B�b�N�p
	// DirectJoyStickDevice�I�u�W�F�N�g�̍쐬
	m_nJoy = 0;
	hr = m_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInputDevice �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	for (int i = 0; i < m_nJoy; i++) {
		// �f�[�^�t�H�[�}�b�g�̐ݒ�
		hr = m_pDIDeviceJoy[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectInput �Ńf�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}

		// �������x���̐ݒ�
		hr = m_pDIDeviceJoy[i]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectInput�ŋ������x���̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}

		// �f�o�C�X�̐ݒ�
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = DIJOFS_X;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_X;
		diprg.lMax       = JOY_MAX_X;
		m_pDIDeviceJoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);	// �w�����͈̔͂��w��
		diprg.diph.dwObj = DIJOFS_Y;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_Y;
		diprg.lMax       = JOY_MAX_Y;
		m_pDIDeviceJoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);	// �x�����͈̔͂��w��

		// �f�o�C�X�ւ̓��͐���J�n
		hr = m_pDIDeviceJoy[i]->Acquire();
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectJoyStick �Ńf�o�C�X�ւ̓��͐���J�n�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}
	}
}


void JoyStick::Uninit() {
	for (int i = 0; i < m_nJoy; i++) {
		if (m_pDIDeviceJoy[i])
			m_pDIDeviceJoy[i]->Unacquire();	// ���͂��I��
		SAFE_RELEASE(m_pDIDeviceJoy[i]);	// DirectJoyStickDevice8 �I�u�W�F�N�g�̉��
	}
	if (m_pDIDeviceKey)
		m_pDIDeviceKey->Unacquire();		// ���͂��I��
	SAFE_RELEASE(m_pDIDeviceKey);			// DirectJoyStickDevice8 �I�u�W�F�N�g�̉��
}


void JoyStick::Update() {
	
	// �O���ۑ�
	for(int i = 0; i < m_nJoy; i++) {
		m_OldAxisX[i] = m_diJoyState[i].lX;
		m_OldAxisY[i] = m_diJoyState[i].lY;
	}

	HRESULT hr;
	for (int i = 0; i < m_nJoy; i++) {
		m_diPrevJoyState[i] = m_diJoyState[i];

		m_pDIDeviceJoy[i]->Acquire();		// �v�����o��
		m_pDIDeviceJoy[i]->Poll();			// �f�o�C�X��̃|�[�����O�ΏۃI�u�W�F�N�g����f�[�^���擾
		// ���݂̃W���C�X�e�B�b�N�̏�Ԃ��擾
		hr = m_pDIDeviceJoy[i]->GetDeviceState(sizeof(m_diJoyState[0]), &m_diJoyState[i]);
		if (hr == DIERR_INPUTLOST)
			m_pDIDeviceJoy[i]->Acquire();	// �ēx�A�v�����o��
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
	// ���݊m�F
	if (nJoy < 0 || nJoy >= m_nJoy) 
		return 0.0f;

	switch (nAxis) {
	case JOY_X:
		// ���t���[���`�F�b�N
		if( abs(m_diJoyState[nJoy].lX) < JOY_MAX_X * JOY_MOVE_NON )
			return 0.0f;
		
		//	���ʂ�Ԃ�
		return m_diJoyState[nJoy].lX;

	case JOY_Y:
		// ���t���[���`�F�b�N
		if( abs(m_diJoyState[nJoy].lY) < JOY_MAX_Y * JOY_MOVE_NON )
			return 0.0f;
		
		//	���ʂ�Ԃ�
		return m_diJoyState[nJoy].lY;

	default:
		break;
	}
	return 0.0f;
}

bool JoyStick::GetJoyAxisRelease(int nJoy, int nAxis) {
	// ���݊m�F
	if (nJoy < 0 || nJoy >= m_nJoy) 
		return 0.0f;

	switch (nAxis) {
	case JOY_X:
		//	���ʂ�Ԃ�
		return (m_OldAxisX[nJoy] != m_diJoyState[nJoy].lX && 0 != m_OldAxisX[nJoy]);

	case JOY_Y:
		return (m_OldAxisY[nJoy] != m_diJoyState[nJoy].lY && 0 != m_OldAxisY[nJoy]);

	default:
		break;
	}
	return 0.0f;
}

//	�E���玞�v����+,�t��-	
float JoyStick::GetJoyAxisDegree( int nJoy ) {
	// ��O�m�F
	if (nJoy < 0 || nJoy >= m_nJoy) 
		return -1000.0f;

	float X = (float)m_diJoyState[nJoy].lX;
	float Y = (float)m_diJoyState[nJoy].lY;

	// ����m�F
	if( !CheckMoveAxis(nJoy) )	
		return -1000.0f;

	// �p�x���o
	float rad = atan2f( Y, X );
	return D3DXToDegree( rad );
}

//	�ォ�玞�v����+
int JoyStick::GetJoyCross( int nJoy, int nPov ) {
	return m_diJoyState[nJoy].rgdwPOV[nPov] == -1 ? -1 : m_diJoyState[nJoy].rgdwPOV[nPov] / 100;
}

bool JoyStick::CheckMoveAxis( int nJoy ) {
	// ���̈ړ����������߂�
	long distance = Vec2Distance( m_diJoyState[nJoy].lX, m_diJoyState[nJoy].lY );

	// ���苗��
	long move = Vec2Distance( JOY_MAX_X, JOY_MAX_Y );
	move = (long)(move * JOY_MOVE_NON);

	return move <= distance;
}

long JoyStick::Vec2Distance( long X, long Y ) {
	return (long)sqrtl(X * X + Y * Y);
}