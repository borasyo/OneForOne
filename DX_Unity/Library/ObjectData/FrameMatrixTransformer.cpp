//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CFrameMatrixTransformer.cpp]
// author : �哴�ˑ�
// 
// �X�̃t���[���������Ă��郏�[���h�s��̕ϊ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FrameMatrixTransformer.h"

// --- ���O���
namespace SkinMesh {

CFrameMatrixTransformer::CFrameMatrixTransformer () {

}

CFrameMatrixTransformer::~CFrameMatrixTransformer () {

}

// �ϊ����
void CFrameMatrixTransformer::Run ( TMyD3DXFRAME* pRootFrame, const D3DXMATRIX* pMtxWorld) {
	// �X�^�b�N�̏�����
	while ( !m_mtxStack.empty() ) {
		m_mtxStack.pop();
	}
	
	// ���[���h�s����X�^�b�N�ɐς�
	D3DXMATRIX mtxWorld;
	mtxWorld = *pMtxWorld;
	m_mtxStack.push( &mtxWorld );

	// �v�Z�J�n
	CreateWorldMatrix( pRootFrame );
}

// �S�t���[�����ċA�v�Z����
void CFrameMatrixTransformer::CreateWorldMatrix ( TMyD3DXFRAME* pFrame ) {

	if( !pFrame )
		return;

	// �e�̃��[���h�s����擾
	D3DXMATRIX* pMatrix = m_mtxStack.top();

	// �t���[�����[�J�������[���h�v�Z
	D3DXMatrixMultiply( &pFrame->mtxWorld, &pFrame->TransformationMatrix, pMatrix );

	// �q�t���[���̌v�Z
	if ( pFrame->pFrameFirstChild ) {
		// �q�t���[���̂��߂Ɏ����̃��[���h�s����Z�b�g
		m_mtxStack.push( &pFrame->mtxWorld);
		// �q�t���[���ֈڂ�
		CreateWorldMatrix( (TMyD3DXFRAME*)pFrame->pFrameFirstChild);
		// �Z��t���[���̂��߂Ɏ����̃��[���h�s������o��
		m_mtxStack.pop();
	}

	// �Z��t���[���̌v�Z
	if ( pFrame->pFrameSibling ) {
		// �Z��t���[���ֈڂ�
		CreateWorldMatrix( (TMyD3DXFRAME*)pFrame->pFrameSibling );
	}
}

}