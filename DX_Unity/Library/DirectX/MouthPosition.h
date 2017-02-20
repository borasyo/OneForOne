//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MouthPosition.h]
// author : 大洞祥太
//
// マウスの座標を取得する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MousePosition_H_____
#define _____MousePosition_H_____

#include "../ObjectType/Object2D.h"

class CMouthPosition{

public:
	typedef struct{
		float x;
		float y;
	} Position_2D;

	CObject2D m_Object2D;
	D3DXVECTOR3 m_Scale;

public:
	~CMouthPosition(void){};
	static CMouthPosition* Create(); 
	bool Init();
	void Update();
	void Draw();
	bool UnInit();

	Position_2D* GetMouthScreenPosition(); // Position_2D構造体を返す(スクリーン座標)
	Position_2D* GetMouthScreenPosition( float *PositionX ); // ポインタに情報をセット(スクリーン座標)
	Position_2D* GetMouthScreenPosition( float *PositionX , float *PositionY );

	Position_2D* GetMouthClientPosition(); // Position_2D構造体を返す(クライアント座標)
	Position_2D* GetMouthClientPosition( float *PositionX ); // ポインタに情報をセット(クライアント座標)
	Position_2D* GetMouthClientPosition( float *PositionX , float *PositionY );

	void SetMouthClientPosition( float PositionX , float PositionY ); // 指定クライアント座標にカーソルを移動させる

	D3DXVECTOR3 GetScale();

protected:
private:
	CMouthPosition();

private:
	Position_2D* m_tScreenPosition; // スクリーン座標
	Position_2D* m_tClientPosition; // クライアント座標

	bool m_bInitialized;
	bool m_ShowMouthFlag;
};

#endif