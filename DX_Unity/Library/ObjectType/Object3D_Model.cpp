
#include "Object3D_Model.h"
#include "../DirectX/Direct3D.h"

CObject3DModel::CObject3DModel(){
	// デバイス取得
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	// マネージャー取得
	m_pModelManager = CModelManager::Create();

	// 名前初期化
	m_FileName = nullptr;

	// 基準値を格納
	m_fAnimSpeed = 1.0f;

	// アニメーションするか
	m_bAnim = true;
}

CObject3DModel::~CObject3DModel(){

}									

// 描画関数
void CObject3DModel::Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const D3DXVECTOR3 Rot, const bool bShadow ){
 
	D3DXMATRIXA16 mtxTranslate, mtxRotation, mtxScale;

	// アニメーションするので時間更新
	//if( m_bAnim && m_AnimationManager.GetAnimationController() )
	//	UpdateAnim();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity( &mtxWorld );

	// スケールセット
	D3DXMatrixScaling( &mtxScale, Scale.x, Scale.y, Scale.z );
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxScale);

	// 回転セット
	D3DXMatrixRotationYawPitchRoll( &mtxRotation, Rot.y, Rot.x, Rot.z );
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxRotation);
	
	// ポジションセット
	D3DXMatrixTranslation( &mtxTranslate, Pos.x, Pos.y, Pos.z );
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld, &mtxTranslate);

	// 描画情報セット
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &mtxWorld );
	
	// モデル描画
	m_pModelManager->RenderModel( &mtxWorld, m_FileName, bShadow );
}

// ゲッター
const LPCWSTR CObject3DModel::GetFileName(){
	return m_FileName;
}

// セッター
void CObject3DModel::SetFileName( const LPCWSTR& filename ){
	m_FileName = filename;

	// ファイル名が指定された時、マップに追加させる
	m_pModelManager->RenderModel( &mtxWorld, filename, false );
}

void CObject3DModel::SetMaterialColor( const D3DXCOLOR Color ){
	
	CModel* pModel = m_pModelManager->GetModel( m_FileName );
	pModel->SetMaterialColor( Color );
}

// コピーしたアニメーションコントローラーを取得し、保存
void CObject3DModel::SetAnimationController(){

	// 名前が分からないのにモデルのアニメーションコントローラーを取得できるわけない
	if( !m_FileName )
		return;

	LPD3DXANIMATIONCONTROLLER pCopyAnimationController = m_pModelManager->GetModel( m_FileName )->GetMainAnimationController();

	// 取得失敗
	if( !pCopyAnimationController )
		return;

	// 取得成功
	m_AnimationManager.SetAnimationController( pCopyAnimationController );
}

bool CObject3DModel::UpdateAnim(){
	
	// アニメーションコントローラーがあって、アニメーションを再生してもよいなら
	if( m_AnimationManager.GetAnimationController() && m_bAnim )
		return m_AnimationManager.AdvanceTime( m_fAnimSpeed );

	return false;
}

void CObject3DModel::SetAnimSpeed( const float fAnimSpeed ) {

	if( !m_bAnim )
		return;

	// 指定したスピードに格納
	m_fAnimSpeed = fAnimSpeed;
}

// アニメーションするかどうかのフラグを反転する
void CObject3DModel::SetAnimFlg( const bool bFlg ){
	m_bAnim = bFlg;
}

// アニメーションコントローラーを取得
CAnimationController* CObject3DModel::GetAnimationManager() {
	return &m_AnimationManager;
}