//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainMenuTitle.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "MainMenuTitle.h"
#include "../Library/DirectX/Window.h"

MainMenuTitle::MainMenuTitle() {
	m_Name = "MainMenuTitle";
	m_Object2D.SetFileName( _T("GameTitle.png") );
}

MainMenuTitle::~MainMenuTitle() {
	
}

bool MainMenuTitle::Start(){

	CWindow* m_pWindow = CWindow::Create();
	m_Position.x = m_pWindow->GetClientWidth()/2.0f;
	m_Position.y = m_pWindow->GetClientHeight()/4.0f; //4.0f
	m_Scale.x = 1092 * 0.7f;	// 1092;
	m_Scale.y = 212 * 0.7f;	// 212;

	return true;
}

void MainMenuTitle::Update(){
	// ‚È‚µ
}

void MainMenuTitle::Draw(){
	// •`‰æ
	m_Object2D.Draw( m_Position, m_Scale );
}