//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object2D.h]
// author : �哴�ˑ�
//
// GameObject��2D�I�u�W�F�N�g�̏ꍇ�A�������������B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TEXTURE_DRAW_H_____
#define _____TEXTURE_DRAW_H_____

#include "d3dx9.h"
#include "../Task/GameObject.h"
#include "../ObjectData/TextureManager.h"

// ---- �}�N��
#define NUM_VERTEX  (4) // ���_��(�Œ�)
#define NUM_POLYGON (2) // �|���S����(�Œ�)
#define	FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 ) // ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�� )

// ---- 2DTexture�\����
typedef struct _VERTEX_2D	// ���_�t�H�[�}�b�g�ɍ��킹���\����
{
	D3DXVECTOR3	pos;			// ���_���W
	float		rhw;			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR	col;			// ���_�J���[
	D3DXVECTOR2 tex;			// �e�N�X�`�����W
} VERTEX_2D;

// ---- Class
class CObject2D {

private:
	std::wstring m_FileName;
	VERTEX_2D m_Vertex[NUM_VERTEX]; // ���_���
	LPDIRECT3DDEVICE9 m_pD3DDevice; // DirectXDevice
	CTextureManager* m_pTextureManager; // 
	float m_fDivide;

public:	
	CObject2D();
	~CObject2D();

	// �`��֐�
	void Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const float fRot = 0.0f );
	// ���W�X�V
	void SetVertexPolygon( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const float fRot );
	void SetVertexColor( const D3DCOLOR Color );
	void SetVertexTexture( const int nPattern ); // �������A���p�^�[���ڂ�

	// ���_��񏉊���
	void MakeVertexPolygon();

	// �Q�b�^�[�Z�b�^�[
	const std::wstring GetFileName();
	void SetFileName( const std::wstring& filename );
};

#endif;