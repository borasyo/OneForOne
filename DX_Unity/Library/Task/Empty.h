//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Empty.h]
// author : �哴�ˑ�
//
// ��̃I�u�W�F�N�g�B
// �����̃I�u�W�F�N�g���܂Ƃ߂�e���~�������ɐ�������B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____EMPTY_H_____
#define _____EMPTY_H_____

#include <iostream>
#include "GameObject.h"

class Empty : public GameObject {

private:

public:
	Empty(std::string Name);
	~Empty();

	//void Update();
	//void Draw();
	
	Empty* GetDownCastClass(GameObject* Obj){
		return nullptr; // ��̃I�u�W�F�N�g�Ȃ̂Ń_�E���L���X�g�����Ȃ�
	}
};

#endif