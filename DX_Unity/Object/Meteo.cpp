//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Meteo.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Meteo.h"
#include "Shadow.h"
#include "BulletFog.h"
#include "FireExplosion.h"
#include "../Library/DirectX/Direct3D.h"
#include "../Library/DirectX/DirectSound.h"

// --- マクロ
#define RANGE (rand()%1500*0.01f);
#define RANDOM (rand()%45*0.01f)

// --- 定数
const float fHeight = 30.0f;
const float fFall = fHeight/60.0f;
const int nStopTime = 30;
const float fCollisionSize = 0.35f;

Meteo::Meteo() {
	m_Name = "Meteo";
	m_Object3D.SetFileName(_T("ShadowBall.png"));
	
	// 取得
	m_pHierarchy = Hierarchy::Create();
	
	// BulletFog取得
	BulletFogParent Obj;
	m_pBulletFogParent = Obj.GetDownCastClass(Hierarchy::Create()->FindWithName("BulletFogParent"));
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	
	// 影作成
	GameObject* pObj = m_pHierarchy->CreateObject(new Shadow(D3DXCOLOR(1.0f,0.0f,1.0f,0.8f),true));
	pObj->SetParent(this);
	//*(pObj->GetPosition()) = m_Position;
	//*(pObj->GetScale()) = m_Scale*1.25f;
	pObj->Start();
	pObj->SetActive(false);
}

Meteo::~Meteo() {
	
}

bool Meteo::Start() {
	
	// 再初期化
	ReInit();

	// スケール調整
	ScaleChange( D3DXVECTOR3(10.0f,10.0f,10.0f) - m_Scale );
	
	// コリジョン設定
	SetCollisionCubeSize( D3DXVECTOR3(fCollisionSize*m_Scale.x,fCollisionSize*m_Scale.y,fCollisionSize*m_Scale.z), 
						  D3DXVECTOR3(fCollisionSize*m_Scale.x,fCollisionSize*m_Scale.y,fCollisionSize*m_Scale.z) );

	// 場所を指定
	m_Position.y = fHeight;

	// 後はランダムに散らす
	switch(rand()%5){
	case 0:
		m_Position.x += RANGE;
		m_Position.z += RANGE;
		break;
	case 1:
		m_Position.x += RANGE;
		m_Position.z -= RANGE;
		break;
	case 2:
		m_Position.x -= RANGE;
		m_Position.z += RANGE;
		break;
	case 3:
		m_Position.x -= RANGE;
		m_Position.z -= RANGE;
		break;
	case 4:
		// プレイヤーの真上に生成
		break;
	default:
		break;
	}

	m_bFall = false;
	m_nTime = 0;
	m_Object3D.SetVertexColor( D3DXCOLOR(1,1,1,1) );

	GameObject* pShadow = FindChild("Shadow");
	*(pShadow->GetPosition()) = m_Position;
	*(pShadow->GetScale()) = m_Scale*1.25f;
	pShadow->SetActive(true);

	return true;
}

void Meteo::Update(){

	//if( m_Child.empty() ) {
	//}

	if( !m_bFall ) {
		// 落下
		Move( D3DXVECTOR3(0,-fFall,0) );

		// エフェクト作成
		D3DXVECTOR3 Random = D3DXVECTOR3(0,0,0);
		switch( rand()%4 ) {
		case 0:
			Random.x += RANDOM; 
			Random.z += RANDOM; 
			break;
		case 1:
			Random.x -= RANDOM; 
			Random.z += RANDOM; 
			break;
		case 2:
			Random.x += RANDOM; 
			Random.z -= RANDOM; 
			break;
		case 3:
			Random.x -= RANDOM; 
			Random.z -= RANDOM; 
			break;
		default:
			break;
		}

		// エフェクト作成
		for( int i = 0; i < 6; i++ ) {
			GameObject* pObj = m_pBulletFogParent->CreateChild(D3DXCOLOR(0.5f,0.0f,0.5f,0.5f), 1.5f, 1.25f);
			*(pObj)->GetPosition() = m_Position+Random*(m_Scale.x/2);
			*(pObj)->GetScale() = D3DXVECTOR3(2.5f,2.5f,2.5f);
		}
		
		// 範囲外判定
		if( m_Position.y <= fFall ) {
			m_bFall = true;
			PlaySound(METEO);
			*(m_pHierarchy->FindWithName("CameraSelect")->GetVec()) = D3DXVECTOR3(30,1.2f,0);
		}
	}

	else {

		m_nTime ++;
		m_Object3D.SetVertexColor( D3DXCOLOR(1,1,1, 1.0f - ((float)m_nTime/(float)nStopTime) ) );

		if( m_nTime >= nStopTime ) {
			m_nLife = 0;
		}
	}
}

void Meteo::Draw(){
	// Z比較なし
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);// Zバッファ更新を無効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	// 描画
	m_Object3D.Draw( m_Position, m_Scale, m_Rotation );
	
	// Z比較あり
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファ更新を有効に
	//m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
}

void Meteo::FreeFunction() {

	m_Scale *= 1.5f;
	m_CollisionCubePlus *= 1.5f;
	m_CollisionCubeMinus *= 1.5f;
	*(FindChild("Shadow")->GetScale()) *= 1.5f;
}