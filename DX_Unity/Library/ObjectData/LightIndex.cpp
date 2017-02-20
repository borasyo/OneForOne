//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [LightIndex.cpp]
// author : 大洞祥太
// 
// ライトのインデックス値を保持する
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "LightIndex.h"

CLightIndex::CLightIndex()
	:m_nIndex(0) {
}


CLightIndex::~CLightIndex(){

}

CLightIndex* CLightIndex::Create(){
	static CLightIndex* pLightIndex = new CLightIndex;

	return pLightIndex;
}

// インデックスを返す
DWORD CLightIndex::GetIndex(){
	int nTemporary = m_nIndex;
	m_nIndex ++;
	return nTemporary;
}

// インデックスリセット
void CLightIndex::ResetIndex(){
	m_nIndex = 0;
}