//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [LightIndex.h]
// author : 大洞祥太
// 
// ライトのインデックス値を保持する
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____LIGHTINDEX_H_____
#define _____LIGHTINDEX_H_____

#include "d3dx9.h"

class CLightIndex {

public:
	~CLightIndex();

	static CLightIndex* Create(); 
	DWORD GetIndex();
	void ResetIndex();

private:
	CLightIndex();
	DWORD m_nIndex;
};

#endif

