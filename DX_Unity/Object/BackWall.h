//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [BackWall.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____BACKWALL_H_____
#define _____BACKWALL_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectData/TextureManager.h"
#include "../Library/DirectX/Direct3D.h"

class BackWall : public GameObject {

private:
	std::wstring m_TexName;
	CTextureManager* m_pTextureManager;

	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffField;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pD3DIndxBuffField;	//	�C���f�b�N�X�o�b�t�@
	
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	D3DXMATRIX	m_mtxWorld;	// ���[���h�}�g���N�X

	int m_nNumVertex;		// �����_��
	int m_nNumPolygon;		// ���|���S����
	int m_nNumVertexIndex;		//���C���f�b�N�X��

	// -- private�֐�
	HRESULT MakeVertex(int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY);

public:
	// ObjectType

	BackWall(){
		m_Name = "Wall";
		m_pTextureManager = CTextureManager::Create();
		m_TexName = _T("Floor.jpg");
	}
	~BackWall(){}

	bool Start();
	void Update();
	void FastDraw();
	
	BackWall* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // ���s!!!
			return nullptr;

		BackWall* Child = static_cast<BackWall*>(Obj); 
		return Child;
	}
};

#endif