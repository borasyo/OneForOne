//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [InvincibleCamera.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "InvincibleCamera.h"
#include "CameraSelect.h"

// --- 定数
//const float fDistance = 10.0f;
const float fMaxDistance = 1000.0f; // 30.0f
const float fMinDistance = 15.0f;
const float fRegulationSpeed = 0.5f;
const float fMaxOver = 4.0f;
const float fMaxVartical = 4.0f/fMinDistance;
const float fMinVartical = -2.0f/fMinDistance;

// -- マクロ
#define RotSpeed (30.0f/(float)(CWindow::Create()->GetClientHeight()))

const int nMoveTime = 120;
const int nWaitTime = 1020;
const float fMoveDistance = 15.0f;
const float fMoveHeight = 0.0f;
const float fMoveVertical = 10.0f;

const float fInitHeight = 1.0f;
const float fInitDistance = 15.0f;
const float fInitVertical = 11.0f;

bool InvincibleCamera::Start(){

	//
	ReInit();
	
	// カメラの高さ
	m_fHeight = fInitHeight;

	// プレイヤーとカメラの距離
	m_fDistance = fInitDistance; // 20.0f

	// カメラの見る高さ
	m_fVartical = fInitVertical;

	// フィールド外に行くのを防止
	m_fRegulation = 0.0f;

	// Input取得
	m_pDirectInputManager = CDirectInputManager::Instance();
	
	// 当たり判定は行わない
	m_bCollision = false;
	
	// 画ブレ用変数初期化
	m_bSway = false;
	m_nNowTime = 0;
	m_nMaxTime = 0;
	m_fSwayRange = 0.0f;
	m_fTotalSway = 0.0f;
	m_bBeside = false;
	m_SwayData = D3DXVECTOR3(0,0,0);
	m_fSwayAmount = 0.0f;
	
	m_TempPos = *(m_pPlayer->GetPosition());
	m_TempRot = *(m_pPlayer->GetRotation());
	// 
	//SetCollisionCubeSize( D3DXVECTOR3(0.1f,10.0f,0.1f), D3DXVECTOR3(0.1f,10.0f,0.1f) );

	return true;
}

void InvincibleCamera::Update(){

	if(m_bOn) {

		m_nTime ++;
	
		if(m_nTime < nWaitTime) {
			m_fHeight += ((fInitHeight + fMoveHeight) - m_fHeight) / (float)nMoveTime;
			m_fDistance += ((fInitDistance + fMoveDistance) - m_fDistance) / (float)nMoveTime;
			m_fVartical += ((fInitVertical + fMoveVertical) - m_fVartical) / (float)nMoveTime;

		} else if(m_nTime >= nWaitTime) {
			m_fHeight -= (m_fHeight - fInitHeight) / (float)nMoveTime;
			m_fDistance -= (m_fDistance - fInitDistance) / (float)nMoveTime;
			m_fVartical -= (m_fVartical - fInitVertical) / (float)nMoveTime;

			if(m_fDistance <= fInitDistance + 0.01f) {
				CameraSelect::SetState(CAMERA_NORMAL);
			}
		}
	}

	// ----- Debug
#if _DEBUG
	if(m_pDirectInputManager->GetKeyboardTrigger(DIK_RETURN)) {
		int i = 0;
		i++;
		printf("%d\n", i);
	}

	if(m_pDirectInputManager->GetKeyboardHold(DIK_Z)) {
		m_fHeight += 0.05f;
	} else if(m_pDirectInputManager->GetKeyboardHold(DIK_X)) {
		m_fHeight -= 0.05f;
	}
#endif

	/*if(m_pDirectInputManager->GetKeyboardTrigger(DIK_C)) {
		m_fDistance += 0.01f;
	} else if(m_pDirectInputManager->GetKeyboardTrigger(DIK_V)) {
		m_fDistance -= 0.01f;
	}
	
	if(m_pDirectInputManager->GetKeyboardTrigger(DIK_B)) {
		m_fVartical += 0.01f;
	} else if(m_pDirectInputManager->GetKeyboardTrigger(DIK_N)) {
		m_fVartical -= 0.01f;
	}*/

	// ------------

	// 見る高さを変更
	/*const float fJoyRiv = 4.0f;
	if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_01)) {
		m_fVartical += RotSpeed * fJoyRiv;
	} else if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_03)) {
		m_fVartical -= RotSpeed * fJoyRiv;
	} else {
		m_fVartical -= m_pDirectInputManager->GetMouseMoveY() * RotSpeed;
	}

	if( m_fVartical >= fMaxVartical*m_fDistance ) {
		m_fVartical = fMaxVartical*m_fDistance;
	} else if( m_fVartical <= fMinVartical*m_fDistance ) {
		m_fVartical = fMinVartical*m_fDistance;
	}*/
	
	m_TempPos += (*(m_pPlayer->GetPosition()) - m_TempPos) * 0.1f;

	/*D3DXVECTOR3 RotAmount = (*(m_pPlayer->GetRotation()) - m_TempRot);
	if(RotAmount.y > Pai) {
		RotAmount.y -= Pai * 2.0f;
	}
	m_TempRot += RotAmount * 0.3f;*/
	m_TempRot = *(m_pPlayer->GetRotation());

	// 角度によるSinCosを取得
	m_fSin = sinf(m_TempRot.y);
	m_fCos = cosf(m_TempRot.y);
	
	float fSinDis = m_fSin*m_fDistance;
	float fCosDis = m_fCos*m_fDistance;
	
	// 移動後の位置を計算
	m_Position.x = m_TempPos.x - fSinDis;
	m_Position.y = m_fHeight;
	m_Position.z = m_TempPos.z - fCosDis;
	
	// プレイヤーの向きに合わせて向き変更
	m_ObjectCamera.GetLookatPt()->x = m_TempPos.x + fSinDis;
	m_ObjectCamera.GetLookatPt()->y = m_fVartical;
	m_ObjectCamera.GetLookatPt()->z = m_TempPos.z + fCosDis;
	
	// X軸,Z軸で範囲オーバーしていないかをチェック
	/*if( m_fRegulation <= 0.0f ) {
		if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_11)) {
			m_fDistance -= 0.2f;
		} else if(m_pDirectInputManager->GetJoyPress(0, JOYBUTTON_12)) {
			m_fDistance += 0.2f;
		} else {
			m_fDistance -= m_pDirectInputManager->GetMouseMoveZ()*0.01f;
		}
	}

	// Distanceの制限
	if( m_fDistance > fMaxDistance )
		m_fDistance = fMaxDistance;
	else if( m_fDistance < fMinDistance )
		m_fDistance = fMinDistance;*/

	if( m_fDistance <= m_fRegulation ) {
		m_fRegulation = m_fDistance - 2.0f;
	}

	if(m_fDistance < fMinDistance) {
		m_fDistance += 0.2f;
	}
	
	if( m_SwayData != D3DXVECTOR3(0,0,0) ) {
			
		if( m_bSway && m_fSwayRange >= m_SwayData.y ) {
			m_SwayData = D3DXVECTOR3(0,0,0);
		}
		else {
			m_nNowTime = 0;
			m_nMaxTime = (int)m_SwayData.x;
			m_fSwayRange = m_SwayData.y; 
			m_bBeside = (bool)m_SwayData.z;
			m_fTotalSway = 0.0f;
			m_bUp = true;
			m_bSway = true;
			m_fSwayAmount = 0.0f;
			m_SwayData = D3DXVECTOR3(0,0,0);
		}
	}
	else {
		m_SwayData = D3DXVECTOR3(0,0,0);
	}

	if( m_bSway ) {

		if( m_nNowTime % 2 == 0 )
			m_fSwayAmount = rand()%((int)(m_fSwayRange*100))/100.0f + 0.1f;

		// プラス方向か
		if( m_bUp ) {
			m_fTotalSway += m_fSwayAmount;
		}
		// マイナス方向か
		else {
			m_fTotalSway -= m_fSwayAmount;
		}
		
		// 横揺れなら
		if( m_bBeside ) {
			
			float fDistanceX = m_ObjectCamera.GetLookatPt()->x - m_Position.x;
			float fDistanceZ = m_ObjectCamera.GetLookatPt()->z - m_Position.z;
			float fAngle = atan2f(fDistanceX,fDistanceZ)+Pai/2;
			float fSin = sinf(fAngle);
			float fCos = cosf(fAngle);

			m_Position.x += fSin*m_fTotalSway;
			m_Position.z += fCos*m_fTotalSway;
			m_ObjectCamera.GetLookatPt()->x += fSin*m_fTotalSway;
			m_ObjectCamera.GetLookatPt()->z += fCos*m_fTotalSway;
		}

		// 縦揺れなら
		else {
			m_Position.y += m_fTotalSway;
			m_ObjectCamera.GetLookatPt()->y += m_fTotalSway;
		}
		
		// 反転
		m_bUp = !m_bUp;

		// カウントアップ
		m_nNowTime ++;
		if( m_nNowTime >= m_nMaxTime ) {
			m_bSway = false;
		}
	}
}

void InvincibleCamera::FastDraw(){

	// コリジョン判定による補正を反映
	float fSinDis = m_fSin*m_fRegulation;
	float fCosDis = m_fCos*m_fRegulation;

	// 移動後の位置を計算
	m_Position.x += fSinDis;
	m_Position.z += fCosDis;
	
	// プレイヤーの向きに合わせて向き変更
	m_ObjectCamera.GetLookatPt()->x -= fSinDis;
	m_ObjectCamera.GetLookatPt()->z -= fCosDis;
	
	// カメラをセット
	m_ObjectCamera.Set(m_Position);
}

void InvincibleCamera::FreeFunction() {
	
	m_bSway = false;
	m_nNowTime = 0;
	m_nMaxTime = 0;
	m_fSwayRange = 0.0f;
	m_fTotalSway = 0.0f;
	m_bBeside = false;
	m_SwayData = D3DXVECTOR3(0,0,0);
	m_fSwayAmount = 0.0f;
}

// 時間、揺れる範囲、揺れるスピード、縦か横か (ダウンキャストあり)
void InvincibleCamera::Sway( int nTime, float fSwayRange, bool bBeside, bool bUp ) {
	
	// 重複禁止
	if( m_bSway )
		return;

	// 各値を設定
	m_bSway = true;
	m_nNowTime = 0;
	m_nMaxTime = nTime;
	m_fSwayRange = fSwayRange;
	m_fTotalSway = 0.0f;
	m_bBeside = bBeside;	// trueなら横揺れ
	m_bUp = bUp;
	m_fSwayAmount = 0.0f;
}

void InvincibleCamera::OnEnable() {
	m_bOn = true;

	m_fHeight = fInitHeight;
	m_fDistance = fInitDistance;
	m_fVartical = fInitVertical;
}

void InvincibleCamera::OnDisable() {
	m_bOn = false;
	m_nTime = 0;
}