//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MouthPosition.h]
// author : 大洞祥太
//
// マウスの座標を取得する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Window.h"
#include "MouthPosition.h"
#include <iostream>
#include "DirectInputManager.h"

CMouthPosition::CMouthPosition() : m_bInitialized(0)
								 , m_tScreenPosition(0)
								 , m_tClientPosition(0){
}

CMouthPosition* CMouthPosition::Create(){
	static CMouthPosition* pMouthPos = new CMouthPosition;

	return pMouthPos;
}

bool CMouthPosition::Init(){
	// 多重初期化禁止(UnInit必須)
	if(m_bInitialized){
		return !m_bInitialized;
	}

	// 確保
	m_tScreenPosition = new Position_2D;
	m_tClientPosition = new Position_2D;
	
	// 0リセット
	m_tScreenPosition->x = 0;
	m_tScreenPosition->y = 0;
	m_tClientPosition->x = 0;
	m_tClientPosition->y = 0;

	// 最初はマウスが表示されている
	m_ShowMouthFlag = true;

	// ウィンドウ外でもマウスの挙動を監視する
	//SetCapture( CWindow::Create()->GetWindowHandle() );

	// 初期化したよフラグ
	m_bInitialized = true;

	//
	m_Object2D.SetFileName(_T("MouthPoint.png"));
	m_Scale = D3DXVECTOR3(35,50,1) * 0.7f;

	return m_bInitialized;
}

void CMouthPosition::Draw(){

	D3DXVECTOR3 Pos = D3DXVECTOR3(m_tClientPosition->x,m_tClientPosition->y,1);
	m_Object2D.Draw( Pos, m_Scale );
}

bool CMouthPosition::UnInit(){
	
	if( !m_bInitialized ){
		// 初期化されていない
		return m_bInitialized;
	}

	if( m_tScreenPosition != NULL ){
		delete m_tScreenPosition;
	}
	if( m_tClientPosition != NULL ){
		delete m_tClientPosition;
	}

	m_tScreenPosition	= NULL;
	m_tClientPosition   = NULL;
//	m_tClientPosition->x = CWindow::Create()->GetClientWidth()/2.0f;
//	m_tClientPosition->y = CWindow::Create()->GetClientHeight()/2.0f;
	m_bInitialized		= false;

	ShowCursor( 1 );

	return true;
}

void CMouthPosition::Update(){

	if( !m_bInitialized ){
		return ;
	}

	// 座標取得
	POINT  Pos;
	Pos.x = 0;
	Pos.y = 0;
	GetCursorPos( &Pos );
	
	// スクリーン座標
	m_tScreenPosition->x = (FLOAT)Pos.x;
	m_tScreenPosition->y = (FLOAT)Pos.y;

	// クライアント座標
	ScreenToClient( CWindow::Create()->GetWindowHandle() , &Pos );	//スクリーン座標をクライアント座標に変換
	
	if(CDirectInputManager::Instance()->GetNumJoystick() > 0) {
		
		float fJoyX = CDirectInputManager::Instance()->GetJoyAxisPress(0, JOY_X);
		float fJoyY = CDirectInputManager::Instance()->GetJoyAxisPress(0, JOY_Y);
		
		const float fJoyRiv  = 0.0005f;
		m_tClientPosition->x += fJoyX * fJoyRiv;
		m_tClientPosition->y += fJoyY * fJoyRiv;
	} else {
		m_tClientPosition->x = (FLOAT)Pos.x;
		m_tClientPosition->y = (FLOAT)Pos.y;
	}

	float	fWidth;
	float	fHeight;
	bool	bMouthShowFlag;
	
	fWidth	= (float)CWindow::Create()->GetClientWidth();
	fHeight	= (float)CWindow::Create()->GetClientHeight();

	// ウィンドウ外にいるか
	bMouthShowFlag = (  m_tClientPosition->x <   0.0f || m_tClientPosition->y <    0.0f ||
						m_tClientPosition->x > fWidth || m_tClientPosition->y > fHeight );

	if(CDirectInputManager::Instance()->GetNumJoystick() > 0) {
		
		if( m_tClientPosition->x < 0.0f) {
			m_tClientPosition->x = 0.0f;
		} else if(m_tClientPosition->x > fWidth) {
			m_tClientPosition->x = fWidth;
		}

		if( m_tClientPosition->y < 0.0f) {
			m_tClientPosition->y = 0.0f;
		} else if(m_tClientPosition->y > fHeight) {
			m_tClientPosition->y = fHeight;
		}
	}

	// 表示切り替え
	if( bMouthShowFlag != m_ShowMouthFlag ){
		ShowCursor( bMouthShowFlag );
		m_ShowMouthFlag = bMouthShowFlag;
	}

	//std::cout << "X座標" << m_tClientPosition->x << "Y座標" << m_tClientPosition->y << std::endl;
}


// Position_2D構造体を返す(スクリーン座標)
CMouthPosition::Position_2D* CMouthPosition::GetMouthScreenPosition(){
	return m_tScreenPosition;
}

// ポインタに情報をセット(スクリーン座標)
// Xのみ(スクリーン座標)
CMouthPosition::Position_2D* CMouthPosition::GetMouthScreenPosition( float *PositionX ){
	*PositionX = m_tScreenPosition->x;
	return m_tScreenPosition;
}
// XY(スクリーン座標)
CMouthPosition::Position_2D* CMouthPosition::GetMouthScreenPosition( float *PositionX , float *PositionY ){
	*PositionX = m_tScreenPosition->x;
	*PositionY = m_tScreenPosition->y;
	return m_tScreenPosition;
}

// Position_2D構造体を返す(クライアント座標)
CMouthPosition::Position_2D* CMouthPosition::GetMouthClientPosition(){
	return m_tClientPosition;
}

// ポインタに情報をセット(クライアント座標)
// Xのみ(クライアント座標)
CMouthPosition::Position_2D* CMouthPosition::GetMouthClientPosition( float *PositionX ){
	*PositionX = m_tClientPosition->x;
	return m_tClientPosition;
}
// XY(クライアント座標)
CMouthPosition::Position_2D* CMouthPosition::GetMouthClientPosition( float *PositionX , float *PositionY ){
	*PositionX = m_tClientPosition->x;
	*PositionY = m_tClientPosition->y;
	return m_tClientPosition;
}


// マウスを移動させる(クライアント座標)
void CMouthPosition::SetMouthClientPosition( float PositionX , float PositionY ){
	POINT  Pos;
	Pos.x = 0;
	Pos.y = 0;
	GetCursorPos( &Pos );
	
	Pos.x = Pos.x + (LONG)(PositionX - m_tClientPosition->x);
	Pos.y = Pos.y + (LONG)(PositionY - m_tClientPosition->y);

	SetCursorPos( (int)Pos.x , (int)Pos.y );

	//--	クライアント座標
	ScreenToClient( CWindow::Create()->GetWindowHandle() , &Pos );	//スクリーン座標をクライアント座標に変換
	
	m_tClientPosition->x = (float)Pos.x;
	m_tClientPosition->y = (float)Pos.y;
}

// 表示しているマウスポインタの大きさを取得
D3DXVECTOR3 CMouthPosition::GetScale(){
	return m_Scale;
}