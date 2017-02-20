//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [LeftWall.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____LEFTWALL_H_____
#define _____LEFTWALL_H_____

#include <iostream>
#include "../Library/Task/Hierarchy.h"
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectData/TextureManager.h"
#include "../Library/DirectX/Direct3D.h"

class LeftWall : public GameObject {

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
	HRESULT MakeVertex(int nNumBlockY, int nNumBlockZ, float fSizeBlockY, float fSizeBlockZ);

public:
	// ObjectType

	LeftWall(){
		m_Name = "Wall";
		m_pTextureManager = CTextureManager::Create();
		m_TexName = _T("Floor.jpg");
	}
	~LeftWall(){}

	bool Start();
	void Update();
	void FastDraw();
	
	LeftWall* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // ���s!!!
			return nullptr;

		LeftWall* Child = static_cast<LeftWall*>(Obj); 
		return Child;
	}
};

#endif