//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [main.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include <stdio.h>
#include <time.h>
#include "d3dx9.h"
#include "../Library/Debug/DebugWindow.h"
#include "../Library/Debug/MemoryLeakDebug.h"
#include "GameBase.h"

// ---- ƒƒCƒ“
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR CmdLine, int ShowCmd )
{
	srand((unsigned int)time(NULL));

	Debug::DebugWindow DebugWindow;
	DebugWindow.Init();

	SetMemoryLeakDebug();

	CGameBase GameBase;

	// ƒQ[ƒ€‚ğ‘–‚ç‚¹‚é
	return GameBase.Run();
}