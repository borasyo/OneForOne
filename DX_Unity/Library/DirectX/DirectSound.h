//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//***************************************************************************************
//	�C���N���[�h�錾
//***************************************************************************************
#include <windows.h>
#include <time.h>
#include "d3dx9.h"
#include "dinput.h"
#include <crtdbg.h>

//*****************************************************************************
// �T�E���h�t�@�C��
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
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
