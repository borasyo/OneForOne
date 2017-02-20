//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object2D.cpp]
// author : �哴�ˑ�
//
// 2D�`��������󂯂�N���X
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Object2D.h"
#include "../DirectX/Direct3D.h"

// �A�t�B���ϊ�
#define AFFINE_X(x,y,w,h,r,t1,t2) ( x+(w/2) + ( (t1*w)/2*cosf(r) - (t2*h)/2*sinf(r) ) )
#define AFFINE_Y(x,y,w,h,r,t1,t2) ( y+(h/2) + ( (t1*w)/2*sinf(r) + (t2*h)/2*cosf(r) ) )

CObject2D::CObject2D(){
	MakeVertexPolygon();
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_pTextureManager = CTextureManager::Create();
}
CObject2D::~CObject2D(){}

// �`��֐�
void CObject2D::Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const float fRot ){ 

	SetVertexPolygon( Pos, Scale, fRot );	// VERTEX_2D�X�V
	m_pD3DDevice->SetFVF( FVF_VERTEX_2D ); // ���_�t�H�[�}�b�g�̐ݒ�
	m_pD3DDevice->SetTexture( 0, m_pTextureManager->LoadTexture(m_FileName) ); // �e�N�X�`���̃Z�b�g
	m_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, NUM_POLYGON, m_Vertex, sizeof( VERTEX_2D ) ); // �|���S���̕`��
	
	m_pD3DDevice->SetTexture( 0, nullptr ); // �e�N�X�`����񏉊���
}

// ���W�X�V
void CObject2D::SetVertexPolygon( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const float fRot ){
	
	if( fRot == 0.0f ) {
		m_Vertex[0].pos = D3DXVECTOR3( Pos.x - Scale.x/2 , Pos.y - Scale.y/2 , 0.0f );
		m_Vertex[1].pos = D3DXVECTOR3( Pos.x + Scale.x/2 , Pos.y - Scale.y/2 , 0.0f );
		m_Vertex[2].pos = D3DXVECTOR3( Pos.x - Scale.x/2 , Pos.y + Scale.y/2 , 0.0f );
		m_Vertex[3].pos = D3DXVECTOR3( Pos.x + Scale.x/2 , Pos.y + Scale.y/2 , 0.0f );
	}

	else {
		m_Vertex[0].pos = D3DXVECTOR3( AFFINE_X(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot,-1,-1), AFFINE_Y(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot,-1,-1), 0.0f );
		m_Vertex[1].pos = D3DXVECTOR3( AFFINE_X(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot, 1,-1), AFFINE_Y(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot, 1,-1), 0.0f );
		m_Vertex[2].pos = D3DXVECTOR3( AFFINE_X(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot,-1, 1), AFFINE_Y(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot,-1, 1), 0.0f );
		m_Vertex[3].pos = D3DXVECTOR3( AFFINE_X(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot, 1, 1), AFFINE_Y(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot, 1, 1), 0.0f );
	}
}


void CObject2D::SetVertexColor( const D3DCOLOR Color ){
	
	// ���_�J���[�̐ݒ�( 0 �` 255 )
	m_Vertex[0].col = Color;
	m_Vertex[1].col = Color;
	m_Vertex[2].col = Color;
	m_Vertex[3].col = Color;
}

// �e�N�X�`���A�j���[�V��������Ȃ�
void CObject2D::SetVertexTexture( const int nPattern ){

	// Texture�̐ݒ�
	m_Vertex[0].tex = D3DXVECTOR2(nPattern * 1.0f/m_fDivide, 0.0f);
	m_Vertex[1].tex = D3DXVECTOR2((nPattern + 1) * 1.0f/m_fDivide, 0.0f);
	m_Vertex[2].tex = D3DXVECTOR2(nPattern * 1.0f/m_fDivide, 1.0f);
	m_Vertex[3].tex = D3DXVECTOR2((nPattern + 1) * 1.0f/m_fDivide, 1.0f);
}

void CObject2D::MakeVertexPolygon(){
	// rhw�̐ݒ�( 1.0�Œ� )
	m_Vertex[0].rhw =  
	m_Vertex[1].rhw =   
	m_Vertex[2].rhw =  
	m_Vertex[3].rhw =  1.0f;

	// ���_�J���[�̐ݒ�( 0 �` 255 )
	m_Vertex[0].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	m_Vertex[1].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	m_Vertex[2].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	m_Vertex[3].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	// �e�N�X�`�����W
	m_Vertex[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	m_Vertex[1].tex = D3DXVECTOR2( 1.0f, 0.0f );
	m_Vertex[2].tex = D3DXVECTOR2( 0.0f, 1.0f );
	m_Vertex[3].tex = D3DXVECTOR2( 1.0f, 1.0f );
}

// �Q�b�^�[
const std::wstring CObject2D::GetFileName(){
	return m_FileName;
}

// �Z�b�^�[
void CObject2D::SetFileName( const std::wstring& filename ){
	m_FileName = filename;
}