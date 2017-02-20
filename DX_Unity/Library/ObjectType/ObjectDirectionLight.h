//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ObjectDirectionLight.cpp]
// author : 大洞祥太
// 
// ディレクショナルライトを作成。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____OBJECT_DIRECTION_LIGHT_H_____
#define _____OBJECT_DIRECTION_LIGHT_H_____

#include "d3dx9.h"
#include "../DirectX/Direct3D.h"
#include "../ObjectData/LightIndex.h"

class CObjectDirectionLight{

private:
	D3DLIGHT9 m_Light;
	DWORD m_nLightIndex;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	CObjectDirectionLight();
	~CObjectDirectionLight();

	void SetVecDirection( D3DXVECTOR3 vec );
	void SetDiffuse( D3DXCOLOR Diffuse );
	void SetAmbient( D3DXCOLOR Ambient );
	void SetSpecular( D3DXCOLOR Specular );
	void SwitchLight( bool bSwitch );
};

#endif