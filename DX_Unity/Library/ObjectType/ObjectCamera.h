//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ObjectCamera.h]
// author : 大洞祥太
//
// GameObjectがCameraオブジェクトの場合、これを合成する。
// 
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____OBJECT_CAMERA_H_____
#define _____OBJECT_CAMERA_H_____

#include"d3dx9.h"

class CObjectCamera {

private:
	D3DXVECTOR3 m_LookatPt;	// 注視点座標
	D3DXVECTOR3 m_UpVec;	// 上方向ベクトル
	D3DVIEWPORT9 m_ViewPort;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	CObjectCamera();
	~CObjectCamera();

	void Set(D3DXVECTOR3 pos); // カメラのセット
	void SetViewPort( D3DVIEWPORT9 ViewPort );

	// ---- ゲッター関数
	D3DXVECTOR3* GetLookatPt();	// 注視点を取得
	D3DXVECTOR3* GetUpVec();	// 法線を取得
};

#endif