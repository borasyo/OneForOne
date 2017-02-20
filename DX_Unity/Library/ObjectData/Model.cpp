//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Model.cpp]
// author : �哴�ˑ�
// 
// ���f����ǂݍ��݂��̃f�[�^��ێ�����
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Model.h"
#include "../DirectX/Direct3D.h"
#include <iostream>

CModel::CModel():m_Mesh(nullptr),
				 m_pAttr(nullptr),
			     m_Materials(nullptr),
			     m_Textures(nullptr),
				 m_pRootFrame(nullptr),
				 m_NumMaterials(0){
	// �f�o�C�X�擾
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
}

CModel::~CModel(){}

void CModel::Uninit(){
	
	if( m_Materials ){
		delete[] m_Materials;
		m_Materials = nullptr;
	}
	
	if( m_Textures ){
		for( DWORD i = 0; i < m_NumMaterials; i++ ){
			if( !m_Textures[i] ) continue;
			m_Textures[i]->Release();
		}
		delete[] m_Textures;
		m_Textures = nullptr;
	}

	if( m_Mesh ){
		m_Mesh->Release();
		m_Mesh = nullptr;
	}
	
	// �J������
	if ( m_pMainAnimationController ) {
		m_pMainAnimationController->Release();
		m_pMainAnimationController = nullptr;
	}
	m_Allocater.DestroyFrame( m_pRootFrame );
}

// ���f���ǂݍ���
bool CModel::LoadModel( const std::wstring& filename ){
	
	// �ǂݍ���
	if ( FAILED( D3DXLoadMeshHierarchyFromX( filename.c_str(), D3DXMESH_MANAGED, m_pD3DDevice,
					&m_Allocater, NULL, (D3DXFRAME**)&m_pRootFrame, &m_pMainAnimationController) ))
	{	
		LPD3DXBUFFER pD3DXMtrlBuffer;
		// X�t�@�C���ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( filename.c_str(), D3DXMESH_SYSTEMMEM, m_pD3DDevice, NULL,
					&pD3DXMtrlBuffer, NULL, &m_NumMaterials, &m_Mesh ) ) ){
			MessageBox( NULL, _T("There is no X-file that the filename"), _T("3D Lib"), MB_OK );
			return false;
		}

		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		m_Materials = new D3DMATERIAL9[m_NumMaterials];
		if( m_Materials == NULL ) return false;
		m_Textures = new LPDIRECT3DTEXTURE9[m_NumMaterials];
		if( m_Textures == NULL ) return false;

		for( int i = 0; i < m_NumMaterials; i++ ){
			// �}�e���A���̃R�s�[
			m_Materials[i] = d3dxMaterials[i].MatD3D;
			// �A���r�G���g�F�̐ݒ�
			m_Materials[i].Ambient = m_Materials[i].Diffuse;
			// �e�N�X�`���ǂݍ���
			//m_Textures[i] = nullptr;
			if( d3dxMaterials[i].pTextureFilename != NULL &&
				lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 ){
				if( FAILED( D3DXCreateTextureFromFileA( m_pD3DDevice, 
					d3dxMaterials[i].pTextureFilename, &m_Textures[i] ) ) ){
					MessageBox( NULL, _T("There is no TextureFile that the pTextureFilename"), _T("3D Lib"), MB_OK );
					return false;
				}
			}
			else { // �e�N�X�`���͐ݒ肳��Ă��Ȃ��̂�m_Texture�͉�����Ă���
				m_Textures[i] = nullptr;
			}
		}
		pD3DXMtrlBuffer->Release();
		
#if _DEBUG
		std::cout << "�X�L�����b�V���Ȃ��̃��f�����Ɠǂݍ��݂܂���" << std::endl;
#endif

	}
	else{
		// �{�[���̉��H
		m_Allocater.CreateBone( m_pRootFrame, (LPD3DXFRAME)m_pRootFrame );

		// �A�j���[�V������60FPS�ɒ���
		if( m_pMainAnimationController )
			m_pMainAnimationController->SetTrackSpeed( 0, 60.0F/4800.0F);
		
#if _DEBUG
		std::cout << "�X�L�����b�V������̃��f����ǂݍ��݂܂���" << std::endl;
#endif
	}

	return true;
}

// ���f��������
void CModel::RenderModel( const D3DXMATRIXA16* pMtx, const bool bShadow ){

	D3DMATERIAL9 matDef;

	// ���݂̃}�e���A�����擾
	m_pD3DDevice->GetMaterial( &matDef );
	
	if( m_pMainAnimationController ) {
		//m_pAnimationController->AdvanceTime( m_fAnimSpeed, NULL );
		m_FMTransformer.Run( m_pRootFrame, pMtx );
		m_AMDrawer.Draw( m_pRootFrame, m_pD3DDevice );
	}
	
	else {
		if( bShadow )
			DrawShadow();
		else
			SetModel();
	}

	// ���ɖ߂�
	m_pD3DDevice->SetMaterial( &matDef );
	m_pD3DDevice->SetTexture(0,NULL);
}

void CModel::SetModel() {
	
	if( !m_Materials ) return;
	if( !m_Mesh ) return;

	for( DWORD i = 0; i < m_NumMaterials; i++ ) {
		m_pD3DDevice->SetMaterial( &m_Materials[i] );
		
		if( m_Textures[i] )
			m_pD3DDevice->SetTexture( 0, m_Textures[i] );
		
		m_Mesh->DrawSubset(i);
	}
}

void CModel::DrawShadow(){
	if( !m_Mesh ) return;

	for( DWORD i = 0; i < m_NumMaterials; i++ )
		m_Mesh->DrawSubset(i);
}

// �F�Z�b�g
void CModel::SetMaterialColor( const D3DXCOLOR Color ){
	
	for( DWORD i = 0; i < m_NumMaterials; i++ )
		m_Materials[i].Diffuse = Color;
}

LPD3DXANIMATIONCONTROLLER CModel::GetMainAnimationController() {

	if( !m_pMainAnimationController )
		return nullptr;

	LPD3DXANIMATIONCONTROLLER pCopyAnimationController;

	m_pMainAnimationController->CloneAnimationController(
	m_pMainAnimationController->GetMaxNumAnimationOutputs(),
	m_pMainAnimationController->GetMaxNumAnimationSets(),
	m_pMainAnimationController->GetMaxNumTracks(),
	m_pMainAnimationController->GetMaxNumEvents(),
	&pCopyAnimationController);

	return pCopyAnimationController;
}