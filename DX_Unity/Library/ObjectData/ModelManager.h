//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ModelManager.h]
// author : 大洞祥太
// 
// 読み込んだモデルを管理するマネージャークラス
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MODELMANAGER_H_____
#define _____MODELMANAGER_H_____

#include "Model.h"

class CModelManager {

public:
	~CModelManager();

	static CModelManager* Create(); 
	HRESULT Init( const std::wstring& FilePath = _T("data/MODEL/") );
	void RenderModel( const D3DXMATRIXA16* pMtx, const std::wstring& FileName, const bool bShadow );
	void Release( const std::wstring& FileName );
	void AllRelease();
	CModel* GetModel( const std::wstring& FileName );

private:
	CModelManager();
	std::wstring m_FilePath;
	std::map<std::wstring, CModel*> m_ModelList;
};

#endif

