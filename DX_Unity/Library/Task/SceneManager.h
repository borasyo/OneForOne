//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneManager.h]
// author : 大洞祥太
//
// シーンで必要なオブジェクトをアクティブに、
// その他を非アクティブにすることでシーンを管理。
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

	// ここでobjectを生成
	void SetObject();

	// ---- シーン管理関数

	// タイトルで必要なオブジェクトをアクティブ状態にする
	void Menu();
	
	// ゲームメインで必要なオブジェクトをアクティブ状態にする
	void EasyMode();
	void NormalMode();
	void HardMode();
	
	// ゲームエンド、クリアで必要なオブジェクトをアクティブ状態にする
	void SetGameOver();
	void SetGameClear();

	// もう一度Play
	void ReInit();
};

#endif