//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Tree.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Tree.h"
#include "../Library/DirectX/Direct3D.h"

// --- �}�N��
#define TREE_POS ( rand()%25000 * 0.01f )

// --- �萔
const float fMaxPos = 125.0f;
const float fHeight = 2.5f;
const float fWidth = 0.5f;

Tree::Tree() {
	m_Name = "Tree";
	m_Object3D.SetFileName( _T("Tree.x") );
}

Tree::~Tree() {
	
}

bool Tree::Start(){
	
	m_Position.x = TREE_POS - fMaxPos;
	m_Position.y = fHeight;
	m_Position.z = TREE_POS - fMaxPos;

	SetCollisionCubeSize( D3DXVECTOR3(fWidth,fHeight,fWidth), D3DXVECTOR3(fWidth,fHeight,fWidth) );
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	return true;
}

void Tree::Update(){
	// ���ɂȂ�
}

void Tree::Draw(){
	
	// Z��r�Ȃ�
	//m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Z�o�b�t�@�X�V�𖳌���
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// �`��
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z��r����
	//m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z�o�b�t�@�X�V��L����
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
}