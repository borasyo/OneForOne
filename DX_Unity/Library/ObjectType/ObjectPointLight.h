//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ObjectPointLight.cpp]
// author : �哴�ˑ�
// 
// �|�C���g���C�g���쐬�B�܂��g�p���Ȃ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____OBJECT_POINT_LIGHT_H_____
#define _____OBJECT_POINT_LIGHT_H_____

#include "d3dx9.h"
#include "../DirectX/Direct3D.h"
#include "../ObjectData/LightIndex.h"

class CObjectPointLight{

private:
	D3DLIGHT9 m_Light;
	DWORD m_nLightIndex;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	CObjectPointLight();
	~CObjectPointLight();

	void SetVecDirection( D3DXVECTOR3 vec );
	void SwitchLight( bool bSwitch );
};

#endif