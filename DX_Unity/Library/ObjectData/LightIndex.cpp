//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [LightIndex.cpp]
// author : �哴�ˑ�
// 
// ���C�g�̃C���f�b�N�X�l��ێ�����
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

// �C���f�b�N�X��Ԃ�
DWORD CLightIndex::GetIndex(){
	int nTemporary = m_nIndex;
	m_nIndex ++;
	return nTemporary;
}

// �C���f�b�N�X���Z�b�g
void CLightIndex::ResetIndex(){
	m_nIndex = 0;
}