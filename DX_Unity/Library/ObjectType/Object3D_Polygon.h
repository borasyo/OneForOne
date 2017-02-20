//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object3D_Polygon.h]
// author : �哴�ˑ�
// 
// GameObject��3DPolygon�I�u�W�F�N�g�̏ꍇ�A�������������B
//
// �E�e�N�X�`���A�j���[�V��������ꍇ�́ASetDivide�ŕ��������w�肵
//   �p�^�[�����ω������Ƃ��ɁASetTexture���ĂԁB
//
// �E�r���{�[�h�ɂ��邩�ǂ�����m_bBillboard�őΉ����Ă���B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____OBJECT_3D_POLYGON_H_____
#define _____OBJECT_3D_POLYGON_H_____

#include "d3dx9.h"
#include "../DirectX/Direct3D.h"
#include "../ObjectData/TextureManager.h"

// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3	vtx;	// ���_���W
	D3DXVECTOR3 normal;	// �@���x�N�g��
	D3DCOLOR	diffuse;// ���ˌ�
	D3DXVECTOR2	tex;	// �e�N�X�`�����W
}VERTEX_3D;

class CObject3DPolygon {

private:
	LPCWSTR m_FileName;
	VERTEX_3D m_Vertex[NUM_VERTEX]; // ���_���
	D3DXMATRIX mtxWorld;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	CTextureManager* m_pTextureManager;
	bool m_bBillboard;
	float m_fDivide;

public:
	CObject3DPolygon();
	virtual ~CObject3DPolygon();

	void Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const D3DXVECTOR3 Rot );
	const LPCWSTR GetFileName();
	void SetFileName( const LPCWSTR& filename );
	void SetBillFlg( const bool bFlg = false );
	void SetDivide( const float fDivide );
	
	HRESULT MakeVertexPolygon();
	void SetVertexBillBoard( const D3DXVECTOR3 Scale );
	void SetVertexPolygon( const D3DXVECTOR3 Scale );
	void SetVertexColor( const D3DCOLOR Color );
	void SetVertexNormal( const D3DXVECTOR3 Normal );
	void SetVertexTexture( const int nPattern ); // �������A���p�^�[���ڂ�
};

#endif