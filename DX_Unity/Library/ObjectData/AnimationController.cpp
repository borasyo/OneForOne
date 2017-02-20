//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AnimationController.cpp]
// author : 大洞祥太
// 
// テクスチャを管理する
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include <iostream>
#include "AnimationController.h"

CAnimationController::CAnimationController(){
	m_pMyAnimationController = nullptr;
}

CAnimationController::~CAnimationController(){
	m_AnimSet.erase(m_AnimSet.begin(),m_AnimSet.end());

	if( m_pMyAnimationController ) {
		m_pMyAnimationController->Release();
		m_pMyAnimationController = nullptr;
	}
}

// アニメーションコントローラを設定
bool CAnimationController::SetAnimationController( const LPD3DXANIMATIONCONTROLLER pAnimCont ) {
	
	// セット
	m_pMyAnimationController = pAnimCont;

	// アニメーションの数だけHLANIMATION_DESC構造体を作成
	for( int nAnimID = 0; nAnimID < m_pMyAnimationController->GetMaxNumAnimationSets(); nAnimID++ ) {
		HLANIMATION_DESC AnimDesc;

		// アニメーションをセット
		m_pMyAnimationController->GetAnimationSet( nAnimID, &AnimDesc.pAnimSet );

		// IDを保存
		AnimDesc.nAnimID = nAnimID;

		// 初期化
		AnimDesc.fCurWeightTime = 0.0f;
		AnimDesc.bLoop = true;
		
		// Vectorに格納
		m_AnimSet.push_back( AnimDesc );

		// 格納後に初期化が必要
		SetLoopTime( nAnimID, 60.0f );
		SetShiftTime( nAnimID, 10.0f );
	}
	//m_nCurAnimID = 1;
	//m_nPreAnimID = 0;

	return true;
}

// 現在ウェイト取得
float CAnimationController::GetWeight(){

	return m_AnimSet[m_nCurAnimID].fCurWeightTime;
}

// ループ時間を取得
float CAnimationController::GetLoopTime( const int nAnimID ) {
	
   // 指定のアニメーションIDの存在をチェック
   if( m_AnimSet.size() <= nAnimID )
      return 0.0f;

	return m_AnimSet[nAnimID].fLoopTime;
}
   
// ループ時間を名前から取得
float CAnimationController::GetLoopTime( const LPCSTR AnimName ) {
	
   // 指定のアニメーションの存在をチェック
	for( int nAnimID = 0; nAnimID < m_AnimSet.size(); nAnimID++ ) {
		
		if( strcmp(m_AnimSet[nAnimID].pAnimSet->GetName(), AnimName) == 0 ) {
			// ヒットしたのでそのLoopTimeを返す
			return m_AnimSet[nAnimID].fLoopTime;
		}
	}
	// その名前はないよ
	return 0.0f;
}
   
// ループ時間を取得
int CAnimationController::GetNowAnimID() {
	return m_nCurAnimID;
}
   
// ループ時間を名前から取得
LPCSTR CAnimationController::GetNowAnimName() {
	return m_AnimSet[m_nCurAnimID].pAnimSet->GetName();
}

// ループ時間を設定
bool CAnimationController::SetLoopTime( const int nAnimID, const float fTime ) {
	
   // 指定のアニメーションIDの存在をチェック
   if( m_AnimSet.size() <= nAnimID )
      return false;

   // トラックスピード調節値を算出
   float fDefTime = m_AnimSet[nAnimID].pAnimSet->GetPeriod();
   m_AnimSet[nAnimID].fLoopTime = fTime;
   m_AnimSet[nAnimID].fTrackSpeed = fDefTime / fTime;

   return true;
}

// ループ時間を設定
bool CAnimationController::SetLoopTime( const LPCSTR AnimName, const float fTime ) {
	
   // 指定のアニメーションの存在をチェック
	for( int nAnimID = 0; nAnimID < m_AnimSet.size(); nAnimID++ ) {

		if( strcmp(m_AnimSet[nAnimID].pAnimSet->GetName(), AnimName) == 0 ) {
			
			// トラックスピード調節値を算出
			float fDefTime = m_AnimSet[nAnimID].pAnimSet->GetPeriod();
			m_AnimSet[nAnimID].fLoopTime = fTime;
			m_AnimSet[nAnimID].fTrackSpeed = fDefTime / fTime;

			return true;
		}
	}
	return false;
}

// 動作開始にかかる時間を設定
bool CAnimationController::SetShiftTime( const int nAnimID, const float fInterval ) {
	
   // 指定のアニメーションIDの存在をチェック
   if( m_AnimSet.size() <= nAnimID )
      return false;

   // シフト時間を登録
   m_AnimSet[nAnimID].fShiftTime = fInterval;

   return true;
}

// 動作開始にかかる時間を設定
bool CAnimationController::SetShiftTime( const LPCSTR AnimName, const float fInterval ) {
	
   // 指定のアニメーションの存在をチェック
	for( int nAnimID = 0; nAnimID < m_AnimSet.size(); nAnimID++ ) {
		
		if( strcmp(m_AnimSet[nAnimID].pAnimSet->GetName(), AnimName) == 0 ) {
			
			// シフト時間を登録
			m_AnimSet[nAnimID].fShiftTime = fInterval;
			return true;
		}
	}
	return false;
}

// アニメーションを切り替え
bool CAnimationController::ChangeAnimation( const int nAnimID, const bool bLoop ) {
	
  // 指定のアニメーションIDの存在をチェック
   if( m_AnimSet.size() <= nAnimID )
      return false;

   // 異なるアニメーションであるかをチェック
   if( m_nCurAnimID == nAnimID )
      return false;

   if( !bLoop && m_nCurAnimID <= m_AnimSet.size() && !m_AnimSet[m_nCurAnimID].bLoop )
	   return false;

   // 現在のアニメーションセットの設定値を取得
   D3DXTRACK_DESC TD;  // トラックの能力
   m_pMyAnimationController->GetTrackDesc( 0, &TD );

   // 今のアニメーションをトラック1に移行し
   // トラックの設定値も移行
   if( m_AnimSet.size() > m_nCurAnimID ) {
	   m_pMyAnimationController->SetTrackAnimationSet( 1, m_AnimSet[m_nCurAnimID].pAnimSet );
	   m_pMyAnimationController->SetTrackDesc( 1, &TD );
   }

   // 新しいアニメーションセットをトラック0に設定
   m_pMyAnimationController->SetTrackAnimationSet( 0, m_AnimSet[nAnimID].pAnimSet );

   // トラック0のスピードの設定
   m_pMyAnimationController->SetTrackSpeed( 0, m_AnimSet[nAnimID].fTrackSpeed );

   // トラックの合成を許可
   m_pMyAnimationController->SetTrackEnable( 0, true );
   m_pMyAnimationController->SetTrackEnable( 1, true );

   // 再初期化
   m_AnimSet[nAnimID].fCurWeightTime = 0.0f;
   m_AnimSet[nAnimID].bLoop = bLoop;

   // ローカル時間を初期化
   m_pMyAnimationController->SetTrackPosition( 0, 0.0f );
   m_pMyAnimationController->AdvanceTime( 0, nullptr );

   // 現在のアニメーション番号を切り替え
   m_nPreAnimID = m_nCurAnimID; // 1つ前のアニメーションとして格納
   m_nCurAnimID = nAnimID;		// 現在のアニメーションとして格納

#if _DEBUG
   std::cout << m_AnimSet[nAnimID].pAnimSet->GetName() << "のアニメーションを実行" << std::endl;
#endif

   return true;
}

// アニメーションを切り替え
bool CAnimationController::ChangeAnimation( const LPCSTR AnimName, const bool bLoop ) {
	
   // 指定のアニメーションの存在をチェック
	for( int nAnimID = 0; nAnimID < m_AnimSet.size(); nAnimID++ ) {
		
		if( strcmp(m_AnimSet[nAnimID].pAnimSet->GetName(), AnimName) == 0 ) {

		   // 異なるアニメーションであるかをチェック
		   if( m_nCurAnimID == nAnimID )
			  return false;

		   if( !bLoop && m_nCurAnimID <= m_AnimSet.size() && !m_AnimSet[m_nCurAnimID].bLoop )
			   return false;

		   // 現在のアニメーションセットの設定値を取得
		   D3DXTRACK_DESC TD;  // トラックの能力
		   m_pMyAnimationController->GetTrackDesc( 0, &TD );

		   // 今のアニメーションをトラック1に移行し
		   // トラックの設定値も移行
		   if( m_AnimSet.size() > m_nCurAnimID ) {
			   m_pMyAnimationController->SetTrackAnimationSet( 1, m_AnimSet[m_nCurAnimID].pAnimSet );
			   m_pMyAnimationController->SetTrackDesc( 1, &TD );
		   }

		   // 新しいアニメーションセットをトラック0に設定
		   m_pMyAnimationController->SetTrackAnimationSet( 0, m_AnimSet[nAnimID].pAnimSet );

		   // トラック0のスピードの設定
		   m_pMyAnimationController->SetTrackSpeed( 0, m_AnimSet[nAnimID].fTrackSpeed );

		   // トラックの合成を許可
		   m_pMyAnimationController->SetTrackEnable( 0, true );
		   m_pMyAnimationController->SetTrackEnable( 1, true );

		   // 再初期化
		   m_AnimSet[nAnimID].fCurWeightTime = 0.0f;
		   m_AnimSet[nAnimID].bLoop = bLoop;

		   // ローカル時間を初期化
		   m_pMyAnimationController->SetTrackPosition( 0, 0.0f );
		   m_pMyAnimationController->AdvanceTime( 0, nullptr );

		   // 現在のアニメーション番号を切り替え
		   m_nPreAnimID = m_nCurAnimID; // 1つ前のアニメーションとして格納
		   m_nCurAnimID = nAnimID;		// 現在のアニメーションとして格納
#if _DEBUG
			std::cout << AnimName << "のアニメーションを実行" << std::endl;
#endif

		   return true;
		}
	}
	return false;
}

// アニメーションを更新
bool CAnimationController::AdvanceTime( const float fTime ) {

   // 合成中か否かを判定
   m_AnimSet[m_nCurAnimID].fCurWeightTime += fTime;
   if( m_AnimSet[m_nCurAnimID].fCurWeightTime <= m_AnimSet[m_nCurAnimID].fShiftTime )
   {
		// 合成中。ウェイトを算出
		float fWeight = m_AnimSet[m_nCurAnimID].fCurWeightTime / m_AnimSet[m_nCurAnimID].fShiftTime;
		// ウェイトを登録
		m_pMyAnimationController->SetTrackWeight( 0, fWeight );		// 現在のアニメーション
		m_pMyAnimationController->SetTrackWeight( 1, 1 - fWeight );	// 前のアニメーション
   }
   else
   {
	    // 合成終了中。通常アニメーションをするTrack0のウェイトを最大値に
		m_pMyAnimationController->SetTrackWeight( 0, 1.0f );	// 現在のアニメーション
		m_pMyAnimationController->SetTrackEnable( 1, false );	// 前のアニメーションを無効にする
   }

   // 時間を更新
   m_pMyAnimationController->AdvanceTime( fTime, nullptr );
   
   // ループチェック
   if( !m_AnimSet[m_nCurAnimID].bLoop && // ループしなくて
	   m_AnimSet[m_nCurAnimID].fLoopTime <= m_AnimSet[m_nCurAnimID].fCurWeightTime && // ループ時間分、フレームが進んでいて、
	   m_AnimSet[m_nCurAnimID].fCurWeightTime * m_AnimSet[m_nCurAnimID].fTrackSpeed >= m_AnimSet[m_nCurAnimID].pAnimSet->GetPeriod() ) { // 指定ピリオド分も進んでいれば
		ChangeAnimation( m_nPreAnimID, m_AnimSet[m_nPreAnimID].bLoop );
		return true; // アニメーション終わりを告げる
   }

   return false; // アニメーション継続中
}