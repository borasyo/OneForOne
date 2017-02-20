//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MemoryLeakDebug.h]
// author : �哴�ˑ�
// 
// MemoryLeak���`�F�b�N����
// 
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MEMORYLEAKDEBUG_H_____
#define _____MEMORYLEAKDEBUG_H_____

#if _DEBUG
	#include <crtdbg.h>
#endif

// �Z�b�g�A�b�v
void SetMemoryLeakDebug(){
	#if _DEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif
}

#endif