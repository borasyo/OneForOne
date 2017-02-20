//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneManager.h]
// author : �哴�ˑ�
//
// �V�[���ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u�ɁA
// ���̑����A�N�e�B�u�ɂ��邱�ƂŃV�[�����Ǘ��B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SCENE_H_____
#define _____SCENE_H_____

#include <iostream>
#include "GameObject.h"
#include "Hierarchy.h"

class SceneManager {

private:
	SceneManager();
	Hierarchy* m_pCreator;
	std::list<GameObject*>* m_pAllObj;

public:
	~SceneManager();

	static SceneManager* Create();

	// ������object�𐶐�
	void SetObject();

	// ---- �V�[���Ǘ��֐�

	// �^�C�g���ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u��Ԃɂ���
	void Menu();
	
	// �Q�[�����C���ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u��Ԃɂ���
	void EasyMode();
	void NormalMode();
	void HardMode();
	
	// �Q�[���G���h�A�N���A�ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u��Ԃɂ���
	void SetGameOver();
	void SetGameClear();

	// ������xPlay
	void ReInit();
};

#endif