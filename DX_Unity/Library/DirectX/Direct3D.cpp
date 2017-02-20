//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Direct3D.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Direct3D.h"

// --- �萔
const bool bWindowMode = true;

// ���̐���
CDirect3D* CDirect3D::m_pCDirect3D = nullptr;

CDirect3D::CDirect3D( CWindow* pWindow )
	:m_pWindow(pWindow)
	,m_pD3D(nullptr)
	,m_pD3DDevice(nullptr)
	,m_bWindowMode(bWindowMode){
}

CDirect3D::~CDirect3D(){
	if( m_pD3D )
		m_pD3D->Release();
	if( m_pD3DDevice )
		m_pD3DDevice->Release();
}

// �N���G�C�g�֐�
CDirect3D* CDirect3D::Create( CWindow* pWindow ){
	static CDirect3D* pCDirect3D = new CDirect3D( pWindow );
	m_pCDirect3D = pCDirect3D;
	return pCDirect3D;
}

CDirect3D* CDirect3D::Create(){
	if( !m_pCDirect3D )
		return nullptr;
	return m_pCDirect3D;
}

// �������֐�
HRESULT CDirect3D::InitDirect3D(){
	D3DPRESENT_PARAMETERS	d3dpp;
	D3DDISPLAYMODE			d3ddm;

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if( m_pD3D == NULL )
		return E_FAIL;

	// ���݂̃f�B�X�v���C���[�h���K��
	if( FAILED( m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm) ) )
		return E_FAIL;

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	if( m_bWindowMode ){
		// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.BackBufferHeight = m_pWindow->GetClientHeight();
		d3dpp.BackBufferWidth  = m_pWindow->GetClientWidth();
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.BackBufferCount  = 1;
		d3dpp.MultiSampleType  = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow		= NULL;
		d3dpp.Windowed			= TRUE;												
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.Flags				= 0;
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}
	else
	{
		//�t���X�N����
		int ScreenCnt = m_pD3D->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8);
		int maxNo=0;
		D3DDISPLAYMODE    dspMax={0,0,0,D3DFMT_UNKNOWN};
		
		//�ő�T�C�Y�擾
		for(int i=0;i<ScreenCnt;i++)
		{
			D3DDISPLAYMODE    d3dspMode;
			m_pD3D->EnumAdapterModes(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, i, &d3dspMode);
			if(i && dspMax.Width*dspMax.Height < d3dspMode.Width*d3dspMode.Height)
			{
				dspMax = d3dspMode;
				maxNo = i;
			}
			//DOM("x:%d y:%d Hz:%d\n",d3dspMode.Width,d3dspMode.Height,d3dspMode.RefreshRate);
		}

		m_pD3D->EnumAdapterModes(D3DADAPTER_DEFAULT ,D3DFMT_X8R8G8B8, maxNo ,&d3ddm);

		//�t���X�N�ݒ�
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		d3dpp.BackBufferWidth    = d3ddm.Width;    // ��
		d3dpp.BackBufferHeight    = d3ddm.Height;    // ����
		d3dpp.BackBufferFormat    = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferCount    = 0;        // �o�b�N�o�b�t�@�̐�
		d3dpp.MultiSampleType  = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect        = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow    = NULL;        // �\���ڕW�E�B���h�E(�\��t���Ώۂ̃E�B���h�E�n���h�������Ă�������)
		d3dpp.Windowed        = FALSE;    // �t���X�N���[�����w��
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags				= 0;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval    = D3DPRESENT_INTERVAL_DEFAULT;
		
		m_pWindow->SetHeight(d3ddm.Height);
		m_pWindow->SetWidth(d3ddm.Width);
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs��
	if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,					// �f�B�X�v���C�A�_�v�^
									 D3DDEVTYPE_HAL,						// �f�o�C�X�^�C�v
									 m_pWindow->GetWindowHandle(),			// �t�H�[�J�X����E�B���h�E�ւ̃n���h��
									 D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
									 &d3dpp,								// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
									 &m_pD3DDevice)) )	{					// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^

		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>�ƃn�[�h�E�F�A�ōs���A<���_����>��CPU�ōs��
		if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,					// �f�B�X�v���C�A�_�v�^
										 D3DDEVTYPE_HAL,						// �f�o�C�X�^�C�v
										 m_pWindow->GetWindowHandle(),			// �t�H�[�J�X����E�B���h�E�ւ̃n���h��
										 D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
										 &d3dpp,								// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
										 &m_pD3DDevice)) ){						// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
											 
			// �L�̐ݒ肪���s������
			// �f�o�C�X�쐬����]<�`��>�ƃn<���_����>��CPU�ōs��
			if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,					// �f�B�X�v���C�A�_�v�^
											 D3DDEVTYPE_REF,						// �f�o�C�X�^�C�v
											 m_pWindow->GetWindowHandle(),			// �t�H�[�J�X����E�B���h�E�ւ̃n���h��
											 D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
											 &d3dpp,								// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
											 &m_pD3DDevice)) ){						// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^

				// �L�̐ݒ肪���s������
				// �f�o�C�X�쐬����]<�`��>�ƃn<���_����>��CPU�ōs��
				if( FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,					// �f�B�X�v���C�A�_�v�^
												 D3DDEVTYPE_REF,						// �f�o�C�X�^�C�v
												 m_pWindow->GetWindowHandle(),			// �t�H�[�J�X����E�B���h�E�ւ̃n���h��
												 D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
												 &d3dpp,								// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
												 &m_pD3DDevice)) ){						// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
					// ���������s
					return E_FAIL;
				}
			}
		}
	}
	this->InitRender();
	return S_OK;
}

typedef struct{
	D3DXVECTOR3		pos; // ���_���W
	float			rhw; // �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR		col; // ���_�J���[
	D3DXVECTOR2		tex; // �e�N�X�`�����W
}VERTEX_2D;

// �����_�[������
void CDirect3D::InitRender( void ){
	
	// �e�N�X�`���̐ݒ�
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// �����_�[�X�e�[�g�̃p�����[�^�̐ݒ�
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );			// ���ʂ��J�����O
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );			// �A���t�@�u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );		// �\�[�X�̐ݒ�
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );	// �ł��Ƃ̐ݒ�

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );	// �e�N�X�`��U�l�̌J��Ԃ��ݒ�
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );	// �e�N�X�`��V�l�̌J��Ԃ��ݒ�
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );	// �e�N�X�`���g�厞�̕�Ԑݒ�
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );	// �e�N�X�`���g�����̕�Ԑݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
		
	// ���C�g�ݒ�
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	// ������ݒ肷��B
	m_pD3DDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_ARGB(64,64,64,64) );
	// ���C�gON
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	// �ˉe�ϊ�
	CWindow *window = CWindow::Create();
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, (float)window->GetWindowWidth()/(float)window->GetWindowHeight(), 1.f, 10000.f );
	m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

void CDirect3D::Clear( void ){
	m_pD3DDevice->Clear( 0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0,0,0,0), 1.0f, 0 );
}

HRESULT CDirect3D::BeginScene( void ){
	return m_pD3DDevice->BeginScene();
}

void CDirect3D::EndScene( void ){
	m_pD3DDevice->EndScene();
}

void CDirect3D::Present( void ){
	m_pD3DDevice->Present( NULL, NULL, NULL, NULL );
}