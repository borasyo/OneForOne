//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Hierarchy.cpp]
// author : 大洞祥太
// 
// Scene上の全てのオブジェクトを管理する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Hierarchy.h"
#include <iostream>

Hierarchy::Hierarchy(){}

// 全てのゲームオブジェクトを削除
Hierarchy::~Hierarchy(){
	Clear();
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) delete *Ite;
	AllGameObject.erase(AllGameObject.begin(),AllGameObject.end());
}
	
// インスタンス取得
Hierarchy* Hierarchy::Create(){
	static Hierarchy* hierarchy = new Hierarchy;
	return hierarchy;
}

// ゲームオブジェクト新規作成
GameObject* Hierarchy::CreateObject(GameObject* Obj){
	AllGameObject.push_back(Obj);
	return Obj;
}

// ゲームオブジェクトを削除	
bool Hierarchy::DestroyObject(GameObject* pObj, bool bParentErase){

	// そのオブジェクトは存在するかをチェック
	if( !pObj )
		return false; // 失敗!!

	// 探索の前に破壊可能かチェック
	if( !pObj->GetDestory() )
		return false; // 失敗!!

	// 子を削除
	std::list<GameObject*>* Child = pObj->GetChild(); // 子リストを取得
	for( auto ChildIte = Child->begin(); ChildIte != Child->end(); ChildIte++ ) {
		DestroyObject(*ChildIte,false); // 子リスト全てにDestroyを実行
		(*ChildIte)->SetLife(-999);
	}

	if( pObj->GetName() == "Shadow" ) {
		int i = 0;
	}

	// 親が居れば、親への登録を解除(bParentEraseがfalseの場合、重複するので解除しない)
	if( pObj->GetParent() && bParentErase ){
		std::list<GameObject*>* Parent = pObj->GetParent()->GetChild(); // 親の子リストを取得
		if( Parent ) {
		for( auto ParentIte = Parent->begin(); ParentIte != Parent->end(); ParentIte++ ){
			if( pObj == *ParentIte ){ // 親の子リストから自分を見つけ出す
				Parent->erase(ParentIte); // 削除
				break;
			}
		}
		}
	}

	// 自身を削除
	pObj->Clear();
	pObj->SetLife(-999);

	return true; // 成功!!
}

// 開始処理
bool Hierarchy::Start(){
	// 優先的に初期化
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		// Awake実行
		(*Ite)->Awake();	
	}

	// 通常の初期化
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		// Start実行
		if(!(*Ite)->Start())
			return false;
 	}
	return true;
}

// 更新処理
void Hierarchy::Update(){
	// LifeCheck
	std::vector<GameObject*> Destroy;
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite ++)
		if( (*Ite)->GetLife() == 0 )
			Destroy.push_back(*Ite);
	for( auto Ite = Destroy.begin(); Ite != Destroy.end(); Ite++ )
		DestroyObject(*Ite);
	
	// Nullになったオブジェクトをリストから消去
	NullObjectErase();
	
	// InitAmount
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		(*Ite)->InitAmount();
	}
	
	// Fast
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		if( !(*Ite)->GetActive() || !(*Ite)->GetUpdateFlg() ) continue;
		(*Ite)->FastUpdate();
	}
	// Normal
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		if( !(*Ite)->GetActive() || !(*Ite)->GetUpdateFlg() ) continue;
		(*Ite)->Update();
	}
	// Late
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		if( !(*Ite)->GetActive() || !(*Ite)->GetUpdateFlg() ) continue;
		(*Ite)->LateUpdate();
	}
}

// 描画処理
void Hierarchy::Draw(){
	// LifeCheck
	std::vector<GameObject*> Destroy;
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite ++)
		if( (*Ite)->GetLife() == 0 )
			Destroy.push_back(*Ite);
	for( auto Ite = Destroy.begin(); Ite != Destroy.end(); Ite++ )
		DestroyObject(*Ite);

	// Nullになったオブジェクトをリストから消去
	NullObjectErase();

	// Fast
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		if( !(*Ite)->GetActive() ) continue;
		(*Ite)->FastDraw();
	}
	// Normal
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		if( !(*Ite)->GetActive() ) continue;
		(*Ite)->Draw();
	}
	// Late
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		if( !(*Ite)->GetActive() ) continue;
		(*Ite)->LateDraw();
	}
}

// 削除処理
void Hierarchy::Clear(){	
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ )
		(*Ite)->Clear();
}

// 死んだオブジェクトをリストから消去
void Hierarchy::NullObjectErase() {
	
	auto Ite = AllGameObject.begin();
	while( Ite != AllGameObject.end() ) {
		
		if( (*Ite)->GetLife() != 0 ) {
			Ite++;
		}
		else if( (*Ite)->GetDestory() ) {
			GameObject* pObj = *Ite;
			Ite = AllGameObject.erase(Ite);
			delete pObj;
			pObj = nullptr;
		}
		else
			Ite++;
	}
}

// 全てのオブジェクトを取得
std::list<GameObject*>* Hierarchy::FindAllObject(){
	return &AllGameObject;
}

// 全てのアクティブオブジェクトを取得
std::list<GameObject*> Hierarchy::FindWithActive(){
	std::list<GameObject*> GetObj;

	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;
		
		// Activeなので格納
		GetObj.push_back(*Ite);
	}

	return GetObj;
}

// 全てのオブジェクトの中から名前の一致するオブジェクトを全て返す
std::vector<GameObject*> Hierarchy::FindWithNameAll(const std::string name){
	std::vector<GameObject*> GetObj;

	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		//if( !(*Ite)->GetActive() ) 
		//	continue;
		if( (*Ite)->GetName() == name ) 
			GetObj.push_back(*Ite);
	}

	return GetObj;
}

// 全てのオブジェクトの中から名前の一致するオブジェクトを1つ返す(nameがuniqueではない場合使用しない)
GameObject* Hierarchy::FindWithName(const std::string name){
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		//if( !(*Ite)->GetActive() ) 
		//	continue;
		if( (*Ite)->GetName() == name ) 
			return *Ite;
	}
	
	return nullptr;
}

// 全てのオブジェクトの中からタグの一致するオブジェクトを全て返す
std::vector<GameObject*> Hierarchy::FindWithTagAll(const std::string tag){
	std::vector<GameObject*> GetObj;

	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		//if( !(*Ite)->GetActive() ) 
		//	continue;
		if( (*Ite)->GetTag() == tag ) 
			GetObj.push_back(*Ite);
	}

	return GetObj;
}

// 全てのオブジェクトの中からタグの一致するオブジェクトを1つ返す(tagがuniqueではない場合使用しない)
GameObject* Hierarchy::FindWithTag(const std::string tag){
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;
		if( (*Ite)->GetTag() == tag ) 
			return *Ite;
	}

	return nullptr;
}

// 全てのオブジェクトの中からレイヤーの一致するオブジェクトを全て返す
std::vector<GameObject*> Hierarchy::FindWithLayerAll(const std::string layer){
	std::vector<GameObject*> GetObj;
	
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		//if( !(*Ite)->GetActive() ) 
		//	continue;
		if( (*Ite)->GetLayer() == layer ) 
			GetObj.push_back(*Ite);
	}

	return GetObj;
}

// 全てのオブジェクトの中からレイヤーの一致するオブジェクトを1つ返す(layerがuniqueではない場合使用しない)
GameObject* Hierarchy::FindWithLayer(const std::string layer){
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		//if( !(*Ite)->GetActive() ) 
		//	continue;
		if( (*Ite)->GetLayer() == layer ) 
			return *Ite;
	}

	return nullptr;
}