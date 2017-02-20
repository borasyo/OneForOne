//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [TextureManager.h]
// author : 大洞祥太
// 
// テクスチャを管理する
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TEXTUREMANAGER_H_____
#define _____TEXTUREMANAGER_H_____

#include "d3dx9.h"
#include <map>
#include <string>
#include <tchar.h>

class CTextureManager{
public:
	static CTextureManager* Create();
	HRESULT Init( const std::wstring& FilePath = _T("data/TEXTURE/") );
	~CTextureManager();
	LPDIRECT3DTEXTURE9 LoadTexture( const std::wstring& FileName );
private:
	CTextureManager();

private:
	std::wstring m_FilePath;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	std::map<std::wstring, LPDIRECT3DTEXTURE9> m_TextureList;
};

#endif
