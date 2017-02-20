//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameBase.cpp]
// author : �哴�ˑ�
// 
// �����ŃQ�[�����[�v���񂷁B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "GameBase.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/DirectX/DirectSound.h"

// ---- �萔

// �R���X�g���N�^
CGameBase::CGameBase()
	:m_pWindow(nullptr)
	,m_pDirect3D(nullptr)
	,m_pTextureManager(nullptr)
	,m_pInputManager(nullptr) 
	,m_pModelManager(nullptr)
	,m_pSceneManager(nullptr)
	,m_pFPSController(nullptr) {
}

// �f�X�g���N�^
CGameBase::~CGameBase(){
	Clear();
}

// ---- �Q�[���𑖂点��
int CGameBase::Run()
{
	// �V�X�e��������
	if( !Awake() ){
		return 0; //�G���[
	}
	
	// �Q�[��������
	if( !Start() ){
		Clear();
		return 0; //�G���[
	}

	HRESULT hr;
	// ---- ���C�����[�v ----
	while( m_pWindow->HandleMessage() )
	{
		if( !m_pFPSController->CheckExec() )
			continue;

		// ---- �X�V
		Update();

		// ---- �`��
		m_pDirect3D->Clear();
		hr = m_pDirect3D->BeginScene();
		Draw();
		m_pDirect3D->EndScene();
		m_pDirect3D->Present();
	}

	return m_pWindow->GetExitValue();
}

// �V�X�e��������
bool CGameBase::Awake(){
	// �E�C���h�E�쐬
	m_pWindow = CWindow::Create();

	// HINSTANCE�擾
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	// �E�C���h�E�쐬
	m_pWindow->MakeWindow( _T("One For One"), hInstance, 1050, 560 );
	
	// �E�C���h�E�̕\��
	//m_pWindow->Show();

	// DirectX9����������
	m_pDirect3D = CDirect3D::Create(m_pWindow);

	// DirectX9�̏�����
	if( m_pDirect3D->InitDirect3D() ){
		return false;
	}
	
	// InputManager����������
	m_pInputManager = CDirectInputManager::Instance();
	if( FAILED( m_pInputManager->Init(GetWindowHandle()) ) )
		return false;

	// TextureManager����������
	m_pTextureManager = CTextureManager::Create();
	if( FAILED( m_pTextureManager->Init() ) )
		return false;

	// ModelManager����������
	m_pModelManager = CModelManager::Create();
	if( FAILED( m_pModelManager->Init() ) )
		return false;

	// LightIndex����
	m_pLightIndex = CLightIndex::Create();

	// MouthPos
	m_pMouthPosition = CMouthPosition::Create();
	m_pMouthPosition->Init();

	// �V�[���}�l�[�W���[����
	m_pSceneManager = SceneManager::Create();

	// Sound������
	InitSound(m_pWindow->GetWindowHandle());

	// FPS�R���g���[��������
	m_pFPSController = FPSController::Create();
	m_pFPSController->Init();

	return true;
}

// ����������
bool CGameBase::Start(){
	
	// Hierarchy����������
	m_pHierarchy = Hierarchy::Create();
	m_pSceneManager->SetObject();
	
	// �S�ẴI�u�W�F�N�g��������
	if( !m_pHierarchy->Start() )
		return false;
	
	// �E�C���h�E�̕\��
	m_pWindow->Show();

	// Menu�\��
	m_pSceneManager->Menu();

	return true;
}

// �X�V����
void CGameBase::Update(){

	// MouthPos�X�V
	m_pMouthPosition->Update();

	// DirectInput�X�V
	m_pInputManager->Update();

	// �I�u�W�F�N�g�X�V
	m_pHierarchy->Update();

	// �}�E�X�̈ړ��������Đݒ�
	if( m_pInputManager->GetKeyboardTrigger(DIK_RCONTROL) ) {

		// �}�E�X�ړ�����
		RECT rc;
		GetClientRect(m_pWindow->GetWindowHandle(), &rc);

		//�N���C�A���g�̈����ʍ��W�ɕϊ�����
		POINT pt = { rc.left, rc.top };
		POINT pt2 = { rc.right, rc.bottom };
		ClientToScreen(m_pWindow->GetWindowHandle(), &pt);
		ClientToScreen(m_pWindow->GetWindowHandle(), &pt2);
		SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);

		//�J�[�\���̓���͈͂𐧌�����
		ClipCursor(&rc);
	}
}

// �`�揈��
void CGameBase::Draw(){

	// �I�u�W�F�N�g�`��
	m_pHierarchy->Draw();
	
	// FPS�\��
	m_pFPSController->DrawFPS();
}

// �㏈��
void CGameBase::Clear(){

	m_pModelManager->AllRelease();
	m_pMouthPosition->UnInit();
	UninitSound();

	// SingletonClass��delete
	delete m_pModelManager;
	delete m_pInputManager;
	delete m_pTextureManager;
	delete m_pHierarchy;
	delete m_pDirect3D;
	delete m_pWindow;
	delete m_pLightIndex;
	delete m_pMouthPosition;
	delete m_pSceneManager;
	delete m_pFPSController;
}

// Direct3D�擾
CDirect3D* CGameBase::GetDirect3D(){
	return m_pDirect3D;
}

// DirectX9device�擾
LPDIRECT3DDEVICE9 CGameBase::GetDirectXDevice(){
	return m_pDirect3D->GetDirect3DDevice();
}

// Window�擾
CWindow* CGameBase::GetWindow(){
	return m_pWindow;
}

// Handle�擾
HWND CGameBase::GetWindowHandle(){
	return m_pWindow->GetWindowHandle();
}
