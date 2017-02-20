//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
//[TextureManager.cpp]
// author : 大洞祥太
// 
// テクスチャを管理する
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include <iostream>
#include "TextureManager.h"
#include "../DirectX/Direct3D.h"

CTextureManager::CTextureManager()
	:m_pD3DDevice(nullptr)
	,m_TextureList(){
}

CTextureManager::~CTextureManager(){
	// テクスチャを開放
	for( std::map<std::wstring, LPDIRECT3DTEXTURE9>::iterator Ite = m_TextureList.begin(); Ite != m_TextureList.end(); Ite ++ )
		if(Ite->second)
			Ite->second->Release();
}

CTextureManager* CTextureManager::Create(){
	// シングルトン
	static CTextureManager*	pTextureManager = new CTextureManager;
	return pTextureManager;
}


HRESULT CTextureManager::Init( const std::wstring& FilePath ){
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	if( !m_pD3DDevice )
		return E_FAIL;

	m_FilePath = FilePath;

	return S_OK;
}


LPDIRECT3DTEXTURE9 CTextureManager::LoadTexture( const std::wstring& FileName ){
	std::map<std::wstring, LPDIRECT3DTEXTURE9>::iterator Ite = m_TextureList.find( FileName );

	if (Ite != m_TextureList.end()){
		return Ite->second;
	} else {
		LPDIRECT3DTEXTURE9 spTexture;
		std::wstring TextureName = m_FilePath + FileName;

		if(FAILED(D3DXCreateTextureFromFile( m_pD3DDevice, TextureName.c_str(), &spTexture ))){
			MessageBox( NULL, _T("There is no TextureFile that the TextureFilename"), _T("3D Lib"), MB_OK );
			return nullptr;
		}
		m_TextureList.insert(std::make_pair( FileName, spTexture ));
		return spTexture;
	}
}