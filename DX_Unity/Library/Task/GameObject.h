//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameObject.h]
// author : 大洞祥太
// 
// 全てのゲームオブジェクトの親クラス
// ObjectTypeに3D,2D,Camera,Lightがある。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____GAMEOBJECT_H_____
#define _____GAMEOBJECT_H_____

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "d3dx9.h"

// -- 定数
const float Pai = 3.141592653589793f;
const D3DXVECTOR3 LimitPos = D3DXVECTOR3( 140.0f, 0.0f, 140.0f ); // 移動範囲制限

// -- 構造体定義

// -- クラス定義
class GameObject {

protected:
	// ---- 基本変数
	D3DXVECTOR3 m_Position; // 座標
	D3DXVECTOR3 m_Rotation; // 角度
	D3DXVECTOR3 m_Scale;	// サイズ
	D3DXVECTOR3 m_MoveAmount;	 // どれだけ移動したか
	D3DXVECTOR3 m_RotAmount;	 // どれだけ回転したか
	D3DXVECTOR3 m_ScaleAmount;	 // どれだけ拡大縮小したか
	bool m_bActive;			// アクティブかどうか
	bool m_bUpdate;			// 更新させるか
	bool m_bDestroy;		// このオブジェクトは自由に破壊できるか
	std::string m_Message;  // メッセージに応じて特定の処理を実行
	int m_nLife; 

	// ---- 外部からは変更不可
	std::string m_Name;	 // 名前
	std::string m_Tag;	 // タグ
	std::string m_Layer; // レイヤー
	
	// ---- 親子関係
	D3DXVECTOR3 m_LocalPosition;	  // 親から見た相対座標
	D3DXVECTOR3 m_LocalRotation;	  // 親から見た相対角度
	D3DXVECTOR3 m_LocalScale;		  // 親から見た相対サイズ
	GameObject* m_Parent;			  // 親クラス
	std::list<GameObject*> m_Child;	  // 子クラス

	// ---- 当たり判定
	bool m_bCollision;					// 当たり判定を行ってもよいか
	D3DXVECTOR3 m_CollisionCubePlus;	// 座標での+の幅
	D3DXVECTOR3 m_CollisionCubeMinus;	// 座標での-の幅
	float m_fCollisionCircle;			// 球体の大きさ
	D3DXVECTOR3 m_BasePlus;				// オブジェクトを拡大する際の変更基準になる値
	D3DXVECTOR3 m_BaseMinus;			// オブジェクトを拡大する際の変更基準になる値
	float m_fBaseCircle;				// オブジェクトを拡大する際の変更基準になる値
	
protected:
	// ---- オブジェクトのアクティブ状態を変更した際のイベント関数(外部からは呼び出し不可)
	virtual void OnEnable() {}
	virtual void OnDisable() {}

public:
	GameObject();
	virtual ~GameObject();

	// ---- 基本関数
	virtual void Awake(){}			   // コンストラクタで実行
	virtual bool Start(){return true;} // ゲームループ1フレーム目で1度だけ実行

	virtual void FastUpdate(){} // 優先してUpdate
	virtual void Update(){}	    // 普通にUpdate
	virtual void LateUpdate(){} // 最後にUpdate

	virtual void FastDraw(){}	// 優先してDraw
	virtual void Draw(){}		// 普通にDraw
	virtual void LateDraw(){}	// 最後にDraw

	virtual void Clear(){}		// 後処理

	virtual GameObject* CreateChild(){return nullptr;} // Particleなどnewの数が膨大になるオブジェトを処理効率よく作成する
	
	// ---- ダウンキャスト
	virtual GameObject* GetDownCastClass(GameObject* Obj) = 0; // ダウンキャストのためには必須デス

	// ---- 例外チェック
	void ExceptionCheck();
	
	// ---- Amount初期化
	void InitAmount();

	// ---- 再初期化
	void ReInit();
	
	// ---- ゲッター関数
	D3DXVECTOR3* GetPosition();				// 座標を取得
	D3DXVECTOR3* GetRotation();				// 角度を取得
	D3DXVECTOR3* GetScale();				// サイズを取得
	D3DXVECTOR3* GetLocalPosition();		// 相対座標を取得
	D3DXVECTOR3* GetLocalRotation();		// 相対角度を取得
	D3DXVECTOR3* GetLocalScale();			// 相対サイズを取得
	
	D3DXVECTOR3* GetMoveAmount();			// 移動量を取得
	D3DXVECTOR3* GetRotAmount();			// 回転量を取得
	D3DXVECTOR3* GetScaleAmount();			// 拡大縮小率量を取得

	const std::string GetName();			// 名前取得
	const std::string GetTag();				// タグ取得
	const std::string GetLayer();			// レイヤー取得

	bool GetActive();						// このオブジェクトはアクティブかどうか
	bool GetUpdateFlg();					// このオブジェクトは更新するか
	const bool GetDestory();				// このオブジェクトは破壊可能か
	int GetLife(); 

	// --- Free関数
	virtual void FreeFunction(){}
	virtual int* GetInt() {return nullptr;}
	virtual float* GetFloat() {return nullptr;}
	virtual bool* GetBool() {return nullptr;}
	virtual D3DXVECTOR3* GetVec() {return nullptr;}
	virtual D3DXCOLOR* GetColor(){ return nullptr; }

	// 親子
	GameObject* GetParent();				// 親のオブジェクト取得
	std::list<GameObject*>* GetChild();	// 子のオブジェクト取得
	GameObject* FindChild(const std::string Name); // 特定の子オブジェクトを取得
	std::list<GameObject*> FindChildAll(const std::string Name); // 特定の子オブジェクトを取得

	// 当たり判定
	D3DXVECTOR3 GetCollisionCubePlusSize();
	D3DXVECTOR3 GetCollisionCubeMinusSize();
	float GetCollisionCircleSize();
	bool GetCollisionFlg();

	// ---- セッター関数
	void Move(D3DXVECTOR3 move, bool bFlg = true);			// オブジェクトを移動(子がいれば子も)
	void Rotation(D3DXVECTOR3 rot, bool bFlg = true);		// オブジェクトを回転(子がいれば子も)
	void ScaleChange(D3DXVECTOR3 scale, bool bFlg = true);  // オブジェクトスケール変更(子がいれば子も)
	void ReturnMove( bool bFlg = true );	// 移動したのを戻す
	void ReturnMoveX( bool bFlg = true );	// 移動したXを戻す
	void ReturnMoveY( bool bFlg = true );	// 移動したYを戻す
	void ReturnMoveZ( bool bFlg = true );	// 移動したZを戻す
	void ReturnRot( bool bFlg = true );		// 回転したのを戻す
	void ReturnScale( bool bFlg = true );	// 拡大したのを戻す
	
	void SetCollisionCubeSize(D3DXVECTOR3 PlusSize, D3DXVECTOR3 MinusSize);
	void SetCollisionCircleSize(float size);

	GameObject* SetParent(GameObject* Parent);  // 親子関係を設定
	void SetLocal();	// ローカル情報を格納
	
	void SetActive(bool bFlg);
	void SetUpdateFlg(bool bFlg);
	void BanDestroy();  // このオブジェクトを破壊できなくする
	void SendForMessage(std::string msg);	// オブジェクトにメッセージを送る
	void SetLife(int nLife); // ライフを変動する
	void SetCollisionFlg(bool bFlg); 
};

#endif