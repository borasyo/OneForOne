
#include "Object3D_Model.h"
#include "../DirectX/Direct3D.h"

CObject3DModel::CObject3DModel(){
	// �f�o�C�X�擾
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	// �}�l�[�W���[�擾
	m_pModelManager = CModelManager::Create();

	// ���O������
	m_FileName = nullptr;

	// ��l���i�[
	m_fAnimSpeed = 1.0f;

	// �A�j���[�V�������邩
	m_bAnim = true;
}

CObject3DModel::~CObject3DModel(){

}									

// �`��֐�
void CObject3DModel::Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const D3DXVECTOR3 Rot, const bool bShadow ){
 
	D3DXMATRIXA16 mtxTranslate, mtxRotation, mtxScale;

	// �A�j���[�V��������̂Ŏ��ԍX�V
	//if( m_bAnim && m_AnimationManager.GetAnimationController() )
	//	UpdateAnim();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &mtxWorld );

	// �X�P�[���Z�b�g
	D3DXMatrixScaling( &mtxScale, Scale.x, Scale.y, Scale.z );
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxScale);

	// ��]�Z�b�g
	D3DXMatrixRotationYawPitchRoll( &mtxRotation, Rot.y, Rot.x, Rot.z );
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxRotation);
	
	// �|�W�V�����Z�b�g
	D3DXMatrixTranslation( &mtxTranslate, Pos.x, Pos.y, Pos.z );
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxTranslate);

	// �`����Z�b�g
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &mtxWorld );
	
	// ���f���`��
	m_pModelManager->RenderModel( &mtxWorld, m_FileName, bShadow );
}

// �Q�b�^�[
const LPCWSTR CObject3DModel::GetFileName(){
	return m_FileName;
}

// �Z�b�^�[
void CObject3DModel::SetFileName( const LPCWSTR& filename ){
	m_FileName = filename;

	// �t�@�C�������w�肳�ꂽ���A�}�b�v�ɒǉ�������
	m_pModelManager->RenderModel( &mtxWorld, filename, false );
}

void CObject3DModel::SetMaterialColor( const D3DXCOLOR Color ){
	
	CModel* pModel = m_pModelManager->GetModel( m_FileName );
	pModel->SetMaterialColor( Color );
}

// �R�s�[�����A�j���[�V�����R���g���[���[���擾���A�ۑ�
void CObject3DModel::SetAnimationController(){

	// ���O��������Ȃ��̂Ƀ��f���̃A�j���[�V�����R���g���[���[���擾�ł���킯�Ȃ�
	if( !m_FileName )
		return;

	LPD3DXANIMATIONCONTROLLER pCopyAnimationController = m_pModelManager->GetModel( m_FileName )->GetMainAnimationController();

	// �擾���s
	if( !pCopyAnimationController )
		return;

	// �擾����
	m_AnimationManager.SetAnimationController( pCopyAnimationController );
}

bool CObject3DModel::UpdateAnim(){
	
	// �A�j���[�V�����R���g���[���[�������āA�A�j���[�V�������Đ����Ă��悢�Ȃ�
	if( m_AnimationManager.GetAnimationController() && m_bAnim )
		return m_AnimationManager.AdvanceTime( m_fAnimSpeed );

	return false;
}

void CObject3DModel::SetAnimSpeed( const float fAnimSpeed ) {

	if( !m_bAnim )
		return;

	// �w�肵���X�s�[�h�Ɋi�[
	m_fAnimSpeed = fAnimSpeed;
}

// �A�j���[�V�������邩�ǂ����̃t���O�𔽓]����
void CObject3DModel::SetAnimFlg( const bool bFlg ){
	m_bAnim = bFlg;
}

// �A�j���[�V�����R���g���[���[���擾
CAnimationController* CObject3DModel::GetAnimationManager() {
	return &m_AnimationManager;
}