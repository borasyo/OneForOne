//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainMenuCollision.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "MainMenuCollision.h"
#include "../Library/Task/Empty.h"
#include "../Library/Task/SceneManager.h"
#include "../Library/DirectX/Window.h"
#include "../Object/SlashRight.h"
#include "../Object/SlashLeft.h"
#include "../Object/SlashCenter.h"
#include "../Library/DirectX/DirectSound.h"

MainMenuCollision::MainMenuCollision() {
	m_Name = "MainMenuCollision";

	// マウスのは当たり判定用オブジェクトを生成
	Hierarchy* pHierarchy = Hierarchy::Create();
	pMouse = pHierarchy->CreateObject(new Empty("MousePos"));
	pMouse->SetCollisionCircleSize(1.0f);
}

MainMenuCollision::~MainMenuCollision() {
	
}

bool MainMenuCollision::Start(){
	
	// 取得
	m_pDirectInputManager = CDirectInputManager::Instance();
	m_pMouthPosition = CMouthPosition::Create();
	Hierarchy* pHierarchy = Hierarchy::Create();

	// 各ボタンを取得
	pEasy = pHierarchy->FindWithName("EasyBotton");
	pNormal = pHierarchy->FindWithName("NormalBotton");
	pHard = pHierarchy->FindWithName("HardBotton");
	pExit = pHierarchy->FindWithName("ExitBotton");
	pHelp = pHierarchy->FindWithName("HelpBotton");

	return true;
}

void MainMenuCollision::LateUpdate(){

	// Task取得
	Hierarchy* pHierarchy = Hierarchy::Create();

	// シーン移動するか
	if( m_pDirectInputManager->GetMouseTrigger(0) || m_pDirectInputManager->GetJoyTrigger(0, JOYBUTTON_01)) {

		SceneManager* pSceneManager = SceneManager::Create();

		if( *(pEasy->GetBool()) ) {
			PlaySound(CLICK);
			pHierarchy->CreateObject(new SlashCenter(0));
			return;
		}

		else if( *(pNormal->GetBool()) ) {
			PlaySound(CLICK);
			pHierarchy->CreateObject(new SlashCenter(1));
			return;
		}

		else if( *(pHard->GetBool()) ) {
			PlaySound(CLICK);
			pHierarchy->CreateObject(new SlashCenter(2));
			return;
		}
		
		else if( *(pExit->GetBool()) ) {
			DestroyWindow(CWindow::Create()->GetWindowHandle());
			return;
		}

		else if( *(pHelp->GetBool()) ) {
			PlaySound(CLICK);
			Hierarchy* pHierarchy = Hierarchy::Create();
			pHierarchy->FindWithName("HelpMenu")->SetActive(true);
			m_bActive = false;
			return;
		}
	}

	// 移動しないなら更新
	D3DXVECTOR2 NowPos = D3DXVECTOR2( m_pMouthPosition->GetMouthClientPosition()->x, m_pMouthPosition->GetMouthClientPosition()->y );
	D3DXVECTOR2 NowScale = D3DXVECTOR2( m_pMouthPosition->GetScale().x, m_pMouthPosition->GetScale().y );
	*(pMouse->GetPosition()) = D3DXVECTOR3( NowPos.x - NowScale.x/2, NowPos.y - NowScale.y/2, 0 );

	// EasyBottonとの当たり判定
	if( pEasy && Collision2DCube( pMouse, pEasy ) ) {
		*(pEasy->GetBool()) = true;
		return;
	}
	else
		*(pEasy->GetBool()) = false;

	// NormalBottonとの当たり判定
	if( pNormal && Collision2DCube( pMouse, pNormal ) ) {
		*(pNormal->GetBool()) = true;
		return;
	}
	else
		*(pNormal->GetBool()) = false;

	// HardBottonとの当たり判定
	if( pHard && Collision2DCube( pMouse, pHard ) ) {
		*(pHard->GetBool()) = true;
		return;
	}
	else
		*(pHard->GetBool()) = false;

	// ExitBottonとの当たり判定
	if( pExit && Collision2DCube( pMouse, pExit ) ) {
		*(pExit->GetBool()) = true;
		return;
	}
	else
		*(pExit->GetBool()) = false;

	// Help
	if( pHelp && Collision2DCube( pMouse, pHelp ) ) {
		*(pHelp->GetBool()) = true;
		return;
	}
	else
		*(pHelp->GetBool()) = false;
}

bool MainMenuCollision::Collision2DCube( GameObject* pPoint, GameObject* pCube ){
	
	D3DXVECTOR3 PointPos = *(pPoint->GetPosition());
	D3DXVECTOR3 CubePos = *(pCube->GetPosition());
	D3DXVECTOR3 CubeScale = *(pCube->GetScale());

	// 矩形と点の当たり判定
	if( CubePos.x - CubeScale.x/2 <= PointPos.x && CubePos.x + CubeScale.x/2 >= PointPos.x &&
		CubePos.y - CubeScale.y/2 <= PointPos.y && CubePos.y + CubeScale.y/2 >= PointPos.y ) 
		return true;

	return false;
}