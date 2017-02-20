//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//***************************************************************************************
//	インクルード宣言
//***************************************************************************************
#include <windows.h>
#include <time.h>
#include "d3dx9.h"
#include "dinput.h"
#include <crtdbg.h>

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	MAINMENU_BGM,
	EASY_BGM,
	NORMAL_BGM,
	HARD_BGM,
	CLICK,		
	MAINMENUEFFECT,	
	DEATHBLOWCHARGE,	
	DEATHBLOWEXPLOSION,	
	DEATHBLOWSHOT,		
	DEATHBLOWGAUGEMAX,		
	DEVILACTIONSTOP,	
	DEVILBEAM,		
	DEVILBULLET,		
	DEVILCORPS,			
	DRAGONASSAULT,				
	DRAGONCLEAVE,				
	DRAGONFIRE,				
	DRAGONFLAME,				
	GAMECLEAR,						
	GAMECLEAREFFECT,						
	GAMEOVER,
	METEO,
	METEOSHOT,
	PLAYERDAMEGE,	
	PLAYERFAR,	
	PLAYERFIREEXPLOSION,	
	PLAYERNEAR,	
	PLAYERNEARDAMAGE,	
	WIZARDASSAULT,		
	WIZARDBEAM,		
	WIZARDBULLET,		
	WIZARDNEAR,		
	WIZARDTELEPORT,	
	ITEMGET,		
	AVOID,
	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
