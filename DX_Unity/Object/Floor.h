//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Floor.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FLOOR_H_____
#define _____FLOOR_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectData/TextureManager.h"
#include "../Library/DirectX/Direct3D.h"

class Floor : public GameObject {

private:
	std::wstring m_TexName;
	CTextureManager* m_pTextureManager;

	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffField;	// 頂点バッファインターフェースへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pD3DIndxBuffField;	//	インデックスバッファ
	
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	D3DXMATRIX	m_mtxWorld;	// ワールドマトリクス

	int m_nNumVertex;		// 総頂点数
	int m_nNumPolygon;		// 総ポリゴン数
	int m_nNumVertexIndex;		//総インデックス数

	// -- private関数
	HRESULT MakeVertex(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);

public:
	// ObjectType

	Floor(){
		m_Name = "Floor";
		m_pTextureManager = CTextureManager::Create();
		m_TexName = _T("Field.jpg");
		//m_TexName = _T("Floor.jpg");
	}
	~Floor(){}

	bool Start();
	void Update();
	void FastDraw();
	
	Floor* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // 失敗!!!
			return nullptr;

		Floor* Child = static_cast<Floor*>(Obj); 
		return Child;
	}
};

#endif