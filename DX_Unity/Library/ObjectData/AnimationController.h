//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AnimationController.h]
// author : 大洞祥太
// 
// テクスチャを管理する
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AnimationController_H_____
#define _____AnimationController_H_____

// ---- インクルード宣言
#include "d3dx9.h"
#include <vector>

// ---- 構造体
struct HLANIMATION_DESC
{
	int nAnimID;					// アニメーションID
    LPD3DXANIMATIONSET pAnimSet;	// アニメーションセット
    float fLoopTime;				// 1ループの時間
    float fTrackSpeed;				// トラックスピード調節値
    float fShiftTime;				// シフトするのにかかる時間
    float fCurWeightTime;			// 現在のウェイト時間
	bool bLoop;						// ループするかどうか
};

// --- クラス宣言
class CAnimationController{

private:
	LPD3DXANIMATIONCONTROLLER m_pMyAnimationController;
	std::vector<HLANIMATION_DESC> m_AnimSet; 
	int m_nCurAnimID, m_nPreAnimID;

public:
	CAnimationController();
	~CAnimationController();
	
   // アニメーションコントローラを設定
   bool SetAnimationController( const LPD3DXANIMATIONCONTROLLER pAnimCont );
   
   // 現在ウェイト取得
   float GetWeight();
   
   // ループ時間を取得
   float GetLoopTime( const int nAnimID );
   
   // ループ時間を名前から取得
   float GetLoopTime( const LPCSTR AnimName );
   
   // 現在再生中のアニメーションの番号を取得
   int GetNowAnimID();
   
   // 現在再生中のアニメーションの名前を取得
   LPCSTR GetNowAnimName();
   
   // ループ時間を設定
   bool SetLoopTime( const int nAnimID, const float fTime );

   // ループ時間を名前から設定
   bool SetLoopTime( const LPCSTR AnimName, const float fTime );
   
   // 動作開始にかかる時間を設定
   bool SetShiftTime( const int nAnimID, const float fInterval );

   // 動作開始にかかる時間を名前からを設定
   bool SetShiftTime( const LPCSTR AnimName, const float fInterval );
   
   // アニメーションを切り替え
   bool ChangeAnimation( const int nAnimID, const bool bLoop );
   
   // アニメーションを名前から切り替え
   bool ChangeAnimation( const LPCSTR AnimName, const bool bLoop );
   
   // アニメーションを更新
   bool AdvanceTime( const float fTime );
   
   // アニメーションコントローラを取得
   LPD3DXANIMATIONCONTROLLER* GetAnimationController() {

	   if( m_pMyAnimationController )
		   return &m_pMyAnimationController;

	   return nullptr;
   }
};

#endif
