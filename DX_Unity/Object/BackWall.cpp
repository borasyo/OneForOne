//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [BackWall.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "BackWall.h"

// --- �}�N��
#define	FIELD_SIZE_X	(100.0f) // �n�ʂ̃T�C�Y(X����)
#define	FIELD_SIZE_Y	(100.0f) // �n�ʂ̃T�C�Y(Z����)

#define FIELD_POS (-150.0f);

// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3	vtx;	// ���_���W
	D3DXVECTOR3 normal;	// �@���x�N�g��
	D3DCOLOR	diffuse;// ���ˌ�
	D3DXVECTOR2	tex;	// �e�N�X�`�����W
	D3DXVECTOR3 nor; // �@��
}VERTEX_3D;

// ---- ����
bool BackWall::Start(){
	
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_bCollision = false;
	
	// ���_���̍쐬
	MakeVertex(4, 4, FIELD_SIZE_X, FIELD_SIZE_Y);

	return true;
}


void BackWall::Update(){
	
	/*
	// ���t���[���̍X�V����������
	VERTEX_3D*	pVtx;

	// ���_�f�[�^�͈̔͂����b�N��
	// ���_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DVtxBuffField->Lock( 0, 0,(void**)&pVtx, 0 );

	// ���_���W�̕ύX

	// ���_�f�[�^���A�����b�N����
	m_pD3DVtxBuffField->Unlock();
	*/
}

void BackWall::FastDraw(){
	
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // ���ʃJ�����OOFF

	D3DXMatrixIdentity( &m_mtxWorld );

	// ���[���h�}�g���N�X�̐ݒ�
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld );

	// ���_�o�b�t�@���f�o�C�X��
	// �f�[�^�X�g���[���Ƀo�C���h
	m_pD3DDevice->SetStreamSource( 0, m_pD3DVtxBuffField, 0, sizeof(VERTEX_3D) );
	
	//�C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	m_pD3DDevice->SetIndices( m_pD3DIndxBuffField );

	// ���_�t�H�[�}�b�g�̐ݒ�
	m_pD3DDevice->SetFVF( FVF_VERTEX_3D );

	// �e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0, m_pTextureManager->LoadTexture(m_TexName) );
	
	//�|���S���̕`��
	m_pD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP,
										0,//���_�o�b�t�@�̃x�[�X�ʒu
										0,//���_�o�b�t�@�̎g�p�J�n�ʒu
										m_nNumVertex,
										0,//�C���f�b�N�X�o�b�t�@�̊J�n�ʒu
										m_nNumPolygon );
	
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW ); // ���ʃJ�����OON
}

HRESULT BackWall::MakeVertex(int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY){
	
	// ���_���i�k�ރ|���S���p���l������j
	m_nNumVertex = ( nNumBlockY + 1 ) * nNumBlockX * 2 + ( nNumBlockX - 1 ) * 2;
	
	// * �C���f�b�N�X���̐ݒ�i�k�ރ|���S�����l������j*
	m_nNumVertexIndex = ( nNumBlockY + 1 ) * nNumBlockX * 2 + ( nNumBlockX - 1 ) * 2;

	// �|���S�����i�k�ރ|���S���p���l������j
	m_nNumPolygon = nNumBlockY * nNumBlockX * 2 + ( nNumBlockX - 1 ) * 4;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if( FAILED( m_pD3DDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nNumVertex,// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y		
		D3DUSAGE_WRITEONLY,	// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,	// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pD3DVtxBuffField, // ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		NULL ))) // ���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
	{
		return E_FAIL;
	}
	
	// * �C���f�b�N�X�m�� *
	if( FAILED( m_pD3DDevice->CreateIndexBuffer( sizeof(WORD) * m_nNumVertexIndex,
		//�C���f�b�N�X�f�[�^�p�Ɋm�ۂ���@�o�b�t�@�T�C�Y�i�o�C�g�j
		D3DUSAGE_WRITEONLY,	//�g�p�@
		D3DFMT_INDEX16,		//�t�H�[�}�b�g
		D3DPOOL_MANAGED,	//���\�[�X�̃o�b�t�@��ێ�����
		&m_pD3DIndxBuffField,//�������N���X���w��
		NULL) ) )
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D*	pVtx;

#if 0	// 1���̎l�p�`�|���S���ɒ���t����e�N�X�`���̃T�C�Y
		const float fSizeTexX = 1.0f / nNumBlockX;
		const float fSizeTexZ = 1.0f / nNumBlockX;
#else
		const float fSizeTexY = 1.0f;
		const float fSizeTexZ = 1.0f;
#endif

		// ���_�f�[�^�͈̔͂����b�N��
		// ���_�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DVtxBuffField->Lock( 0, 0, (void**)&pVtx, 0 );
		
		for( int CntZ = 0; CntZ < nNumBlockX + 1; CntZ ++ )
		{
			for( int CntY = 0; CntY < nNumBlockY + 1; CntY ++)
			{
				pVtx[CntZ * (nNumBlockY + 1) + CntY].vtx.x = +nNumBlockX / 2.0f * fSizeBlockX - CntZ * fSizeBlockX;
				pVtx[CntZ * (nNumBlockY + 1) + CntY].vtx.y = -nNumBlockY / 2.0f * fSizeBlockY + CntY * fSizeBlockY;
				pVtx[CntZ * (nNumBlockY + 1) + CntY].vtx.z = FIELD_POS;

				//�@��
				pVtx[CntZ*(nNumBlockY + 1) + CntY].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���ˌ�
				pVtx[CntZ*(nNumBlockY + 1) + CntY].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[CntZ*(nNumBlockY + 1) + CntY].tex.x = fSizeTexY * CntY;
				pVtx[CntZ*(nNumBlockY + 1) + CntY].tex.y = fSizeTexZ * CntZ;
			}
		}
	}
		
	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
		WORD* pIdx;

		//�C���f�b�N�X�f�[�^�͈̔͂����b�N�����_�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DIndxBuffField->Lock( 0, 0, (void**)&pIdx, 0 );

		int nCntIdx = 0;
		for( int nCntZ = 0; nCntZ < nNumBlockX; nCntZ ++ )
		{
			if( nCntZ > 0 )
			{//�k�ރ|���S���̂��߂̃_�u���ݒ�
				pIdx[nCntIdx] = ( nCntZ + 1 ) * ( nNumBlockY + 1 );
				nCntIdx ++;
			}

			for( int nCntX = 0; nCntX < nNumBlockY + 1; nCntX ++ )
			{
				pIdx[nCntIdx] = ( nCntZ + 1 ) * ( nNumBlockY + 1 ) + nCntX;
				nCntIdx ++;
				pIdx[nCntIdx] = nCntZ * ( nNumBlockY + 1 ) + nCntX;
				nCntIdx ++;
			}

			if( nCntZ < nNumBlockX - 1 )
			{//�k�ރ|���S���̂��߂̃_�u���ݒ�
				pIdx[nCntIdx] = nCntZ * ( nNumBlockY + 1 ) + nNumBlockY;
				nCntIdx ++;
			}
		}

		m_pD3DIndxBuffField->Unlock();
	}

	return S_OK;
}