//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object3D_Polygon.h]
// author : �哴�ˑ�
// 
// GameObject��3DPolygon�I�u�W�F�N�g�̏ꍇ�A�������������B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Object3D_Polygon.h"

CObject3DPolygon::CObject3DPolygon():m_bBillboard(true)
									,m_fDivide(0) {
	// �f�o�C�X�擾
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	// �}�l�[�W���[�擾
	m_pTextureManager = CTextureManager::Create();
	
	// ���_���̍쐬
	MakeVertexPolygon();
	
	// �F�̓f�t�H���g�ɏ�����
	SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) );
}

CObject3DPolygon::~CObject3DPolygon(){

}

void CObject3DPolygon::Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const D3DXVECTOR3 Rot ) {
	
	D3DXMATRIX mtxTranslate, mtxRotation, mtxScale;
	
	// ���C�e�B���O�𖳌��ɂ���
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	// �X�P�[���Z�b�g
	D3DXMatrixScaling( &mtxScale, Scale.x, Scale.y, Scale.z );
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxScale);

	// ��]�Z�b�g���܂�
	// �r���{�[�h�Ȃ�
	if( m_bBillboard ) { 

		// ���W�X�V
		SetVertexBillBoard(Scale);

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &mtxWorld );

		D3DXMATRIX mtxView;
		m_pD3DDevice->GetTransform( D3DTS_VIEW, &mtxView );
		
		//mtxWorld._11 = mtxView.

		// �t�s������߂�
		D3DXMatrixInverse( &mtxWorld,NULL,&mtxView );

		mtxWorld._41 = 0.0f;
		mtxWorld._42 = 0.0f;
		mtxWorld._43 = 0.0f;
	}
	// �ʏ�Ȃ�
	else {
		// ���W�X�V
		SetVertexPolygon(Scale);

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &mtxWorld );
		
		// ��]�Z�b�g
		D3DXMatrixRotationYawPitchRoll( &mtxRotation, Rot.y, Rot.x, Rot.z );
		D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxRotation);
	}

	// �|�W�V�����Z�b�g
	D3DXMatrixTranslation( &mtxTranslate, Pos.x, Pos.y, Pos.z );
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxTranslate);
	
	// �`��
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &mtxWorld );
	
	m_pD3DDevice->SetFVF( FVF_VERTEX_3D ); // ���_�t�H�[�}�b�g�̐ݒ�
	m_pD3DDevice->SetTexture( 0, m_pTextureManager->LoadTexture(m_FileName) ); // �e�N�X�`���̃Z�b�g
	m_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, NUM_POLYGON, m_Vertex, sizeof( VERTEX_3D ) ); // �|���S���̕`��

	m_pD3DDevice->SetTexture( 0, nullptr ); // �e�N�X�`����񏉊���
	
	// ���C�e�B���O��L���ɂ���
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

HRESULT CObject3DPolygon::MakeVertexPolygon(){

	if( m_bBillboard ) {

		// �e�N�X�`�����W
		m_Vertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		m_Vertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	
		// �@���̐ݒ�
		m_Vertex[0].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[1].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[2].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[3].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	} 
	else {

		// �e�N�X�`�����W
		m_Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		m_Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		// �@���̐ݒ�
		m_Vertex[0].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[1].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[2].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[3].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	}

	return S_OK;
}

void CObject3DPolygon::SetVertexPolygon( const D3DXVECTOR3 Scale ){
	
	// ���_���W�̐ݒ�
	m_Vertex[0].vtx = D3DXVECTOR3( -Scale.x/2, 0.0f,  Scale.z/2 );
	m_Vertex[1].vtx = D3DXVECTOR3(  Scale.x/2, 0.0f,  Scale.z/2 );
	m_Vertex[2].vtx = D3DXVECTOR3( -Scale.x/2, 0.0f, -Scale.z/2 );
	m_Vertex[3].vtx = D3DXVECTOR3(  Scale.x/2, 0.0f, -Scale.z/2 );
}

void CObject3DPolygon::SetVertexBillBoard( const D3DXVECTOR3 Scale ){
	
	// ���_���W�̐ݒ�
	m_Vertex[0].vtx = D3DXVECTOR3( -Scale.x/2 , -Scale.y/2 , 0.0f );
	m_Vertex[1].vtx = D3DXVECTOR3( -Scale.x/2 , +Scale.y/2 , 0.0f );
	m_Vertex[2].vtx = D3DXVECTOR3( +Scale.x/2 , -Scale.y/2 , 0.0f );
	m_Vertex[3].vtx = D3DXVECTOR3( +Scale.x/2 , +Scale.y/2 , 0.0f );
}

void CObject3DPolygon::SetVertexColor( const D3DCOLOR Color ){
	
	// ���_�J���[�̐ݒ�( 0 �` 255 )
	m_Vertex[0].diffuse = Color;
	m_Vertex[1].diffuse = Color;
	m_Vertex[2].diffuse = Color;
	m_Vertex[3].diffuse = Color;
}

// �@���ς������Ȃ�
void CObject3DPolygon::SetVertexNormal( const D3DXVECTOR3 Normal ){
	
	// �@���̐ݒ�
	m_Vertex[0].normal = Normal;
	m_Vertex[1].normal = Normal;
	m_Vertex[2].normal = Normal;
	m_Vertex[3].normal = Normal;
}

// �e�N�X�`���A�j���[�V��������Ȃ�
void CObject3DPolygon::SetVertexTexture( const int nPattern ){

	if( m_bBillboard ) {
		// Texture�̐ݒ�
		m_Vertex[0].tex = D3DXVECTOR2(nPattern * 1.0f/m_fDivide, 1.0f);
		m_Vertex[1].tex = D3DXVECTOR2(nPattern * 1.0f/m_fDivide, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2((nPattern + 1) * 1.0f/m_fDivide, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2((nPattern + 1) * 1.0f/m_fDivide, 0.0f);
	}
	else {
		// Texture�̐ݒ�
		m_Vertex[0].tex = D3DXVECTOR2(nPattern * 1.0f/m_fDivide, 0.0f);
		m_Vertex[1].tex = D3DXVECTOR2((nPattern + 1) * 1.0f/m_fDivide, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2(nPattern * 1.0f/m_fDivide, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2((nPattern + 1) * 1.0f/m_fDivide, 1.0f);
	}
}

// �Q�b�^�[
const LPCWSTR CObject3DPolygon::GetFileName(){
	return m_FileName;
}

// �Z�b�^�[
void CObject3DPolygon::SetFileName( const LPCWSTR& filename ){
	m_FileName = filename;
}

void CObject3DPolygon::SetBillFlg( const bool bFlg ){
	m_bBillboard = bFlg;
	MakeVertexPolygon();
}

void CObject3DPolygon::SetDivide( const float fDivide ){
	m_fDivide = fDivide;
}