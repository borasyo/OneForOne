//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Empty.h]
// author : 大洞祥太
//
// 空のオブジェクト。
// 複数のオブジェクトをまとめる親が欲しい時に生成する。
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
		return nullptr; // 空のオブジェクトなのでダウンキャストさせない
	}
};

#endif