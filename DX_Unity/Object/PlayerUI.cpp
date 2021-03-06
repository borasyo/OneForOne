//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [PlayerUI.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "PlayerUI.h"
#include "Player.h"

// --- 定数
const float fGaugeScale = 1320 * 0.7f;

PlayerUI::PlayerUI() {
	m_Name = "PlayerUI";
	m_GaugeDecoration.SetFileName( _T("GaugeDecoration.png") );
	m_HPGauge.SetFileName( _T("HPGauge.png") );
	m_DeathblowGauge.SetFileName( _T("DeathblowGauge.png") );
}

PlayerUI::~PlayerUI() {
	
}

bool PlayerUI::Start(){
	
	m_Position = D3DXVECTOR3(500,85,1) * 0.7f;
	m_Scale = D3DXVECTOR3(900,150,1) * 0.7f;

	m_HPGaugePos = D3DXVECTOR3(m_Position.x - (295 * 0.7f),m_Position.y - (4 * 0.7f),1);
	m_HPGaugeScale = D3DXVECTOR3(fGaugeScale,10 * 0.7f,1);// * 0.7f;

	m_DeathblowGaugePos = m_HPGaugePos;
	m_DeathblowGaugePos.y += m_HPGaugeScale.y;
	m_DeathblowGaugeScale = m_HPGaugeScale;

	m_pHierarchy = Hierarchy::Create();
	m_pPlayer = m_pHierarchy->FindWithName("Player");
	m_nMaxLife = m_pPlayer->GetLife() - 1; // 最大ライフ取得

	return true;
}

void PlayerUI::Update(){
	
	m_pPlayer = m_pHierarchy->FindWithName("Player");
	if( m_pPlayer ) {
		// PlayerのHPに応じて減らす
		m_HPGaugeScale.x = fGaugeScale*((float)(m_pPlayer->GetLife() - 1)/(float)m_nMaxLife);

		float fPer = m_pPlayer->GetLife() / (float)m_nMaxLife;
		
		if(fPer > 0.5f) {
			m_HPGauge.SetVertexColor(D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f));
		} else if(fPer <= 0.25f) {
			m_HPGauge.SetVertexColor(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
		} else {
			m_HPGauge.SetVertexColor(D3DXCOLOR(1.0f , 1.0f, 0.5f, 1.0f));
		}

		// PlayerのGaugeに応じて減らす
		m_DeathblowGaugeScale.x = fGaugeScale*(*(m_pPlayer->GetFloat())/fMaxDeathblowGauge);
		
		// テクスチャを切り替える
		if( !*(m_pPlayer->GetBool()) ) {
			if( *(m_pPlayer->GetFloat()) < 10.0f ) 
				m_DeathblowGauge.SetFileName( _T("DeathblowGaugeAvoid.png") );
			else if( *(m_pPlayer->GetFloat()) < fMaxDeathblowGauge )
				m_DeathblowGauge.SetFileName( _T("DeathblowGauge.png") );
			else
				m_DeathblowGauge.SetFileName( _T("DeathblowGaugeMax.png") );
		}
	}
}

void PlayerUI::LateDraw(){

	// 描画
	m_GaugeDecoration.Draw( m_Position, m_Scale );
	
	// 描画
	m_HPGauge.Draw( m_HPGaugePos, m_HPGaugeScale );
	
	// 描画
	m_DeathblowGauge.Draw( m_DeathblowGaugePos, m_DeathblowGaugeScale );

}