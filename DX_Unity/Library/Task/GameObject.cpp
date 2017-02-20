//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameObject.cpp]
// author : 大洞祥太
// 
// 全てのゲームオブジェクトの親クラス
// ObjectTypeに3D,2D,Camera,Lightがある。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "GameObject.h"
#include <math.h>

#include "../DirectX/DirectInputManager.h"

GameObject::GameObject()
	:m_Position(0,0,0)
	,m_Rotation(0,0,0)
	,m_Scale(1,1,1)
	,m_LocalPosition(0,0,0)
	,m_LocalRotation(0,0,0)
	,m_LocalScale(1,1,1)
	,m_MoveAmount(0,0,0)
	,m_RotAmount(0,0,0)
	,m_ScaleAmount(0,0,0)
	,m_CollisionCubeMinus(0,0,0)
	,m_CollisionCubePlus(0,0,0)
	,m_fCollisionCircle(0)
	,m_nLife(1)
	,m_bCollision(true)
	,m_bActive(true)
	,m_bUpdate(true)
	,m_bDestroy(true)
	,m_Parent(nullptr) {
		int i = 0;
}

GameObject::~GameObject(){

}

// ---- 再初期化
void GameObject::ReInit(){
	
	m_Position = D3DXVECTOR3(0,0,0);
	m_Rotation = D3DXVECTOR3(0,0,0);
	m_Scale = D3DXVECTOR3(1,1,1);
	m_LocalPosition = D3DXVECTOR3(0,0,0);
	m_LocalRotation = D3DXVECTOR3(0,0,0);
	m_LocalScale = D3DXVECTOR3(0,0,0);
	m_MoveAmount = D3DXVECTOR3(0,0,0);
	m_RotAmount = D3DXVECTOR3(0,0,0);
	m_ScaleAmount = D3DXVECTOR3(0,0,0);
	m_CollisionCubeMinus = D3DXVECTOR3(0,0,0);
	m_CollisionCubePlus = D3DXVECTOR3(0,0,0);
	m_fCollisionCircle = 0.0f;
	m_nLife = 1;
	m_bCollision = true;
	m_bActive = true;
	m_bUpdate = true;
}

// ---- ゲッター関数
// 座標を取得
inline D3DXVECTOR3* GameObject::GetPosition(){ 
	return &m_Position;
}

// 角度を取得
inline D3DXVECTOR3* GameObject::GetRotation(){ 
	return &m_Rotation;
}		

// サイズを取得
inline D3DXVECTOR3* GameObject::GetScale(){
	return &m_Scale;
}

// 相対座標を取得
inline D3DXVECTOR3* GameObject::GetLocalPosition(){ 
	return &m_LocalPosition;
}

// 相対角度を取得
inline D3DXVECTOR3* GameObject::GetLocalRotation(){ 
	return &m_LocalRotation;
}		

// 相対サイズを取得
inline D3DXVECTOR3* GameObject::GetLocalScale(){
	return &m_LocalScale;
}

// オブジェクトにメッセージを送る
void GameObject::SendForMessage(std::string msg){ 
	m_Message = msg;
}	

// ObjectのLifeを取得
int GameObject::GetLife(){
	return m_nLife;
}

// 名前取得
const std::string GameObject::GetName(){ 
	return m_Name;
}				

// タグ取得
const std::string GameObject::GetTag(){ 
	return m_Tag;
}				

// レイヤー取得
const std::string GameObject::GetLayer(){ 
	return m_Layer;
}			

// 親のオブジェクト取得
GameObject* GameObject::GetParent(){ 

	if( m_Parent )
		return m_Parent;

	return nullptr;
}				

// 子のオブジェクト取得
inline std::list<GameObject*>* GameObject::GetChild(){ 
	return &m_Child;
}	

// このオブジェクトはアクティブかどうか
bool GameObject::GetActive(){ 
	return m_bActive;
}				

// このオブジェクトは更新するかどうか
bool GameObject::GetUpdateFlg(){ 
	return m_bUpdate;
}				

// このオブジェクトは破壊可能かどうか
const bool GameObject::GetDestory(){ 
	return m_bDestroy;
}

// 特定の子オブジェクトを取得
GameObject* GameObject::FindChild(const std::string Name){
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		if( Name == (*Ite)->GetName() )
			return *Ite;
	return nullptr;
}

// 特定の子オブジェクト全てを取得
std::list<GameObject*> GameObject::FindChildAll(const std::string Name){	
	std::list<GameObject*> findchild;
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		if( Name == (*Ite)->GetName() ) findchild.push_back(*Ite);
	return findchild; 
}

//	当たり判定関係ゲッター
D3DXVECTOR3 GameObject::GetCollisionCubePlusSize(){
	return m_CollisionCubePlus;
}

D3DXVECTOR3 GameObject::GetCollisionCubeMinusSize(){
	return m_CollisionCubeMinus;
}

float GameObject::GetCollisionCircleSize(){
	return m_fCollisionCircle;
}

bool GameObject::GetCollisionFlg(){
	return m_bCollision;
}

// ---- セッター関数
// オブジェクトを移動
void GameObject::Move(D3DXVECTOR3 move, bool bFlg){
	m_Position += move;
	m_MoveAmount = move;
	
	// 子にも反映 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->Move(move,false);

	// もし親がいればローカル情報にも反映
	if( m_Parent && bFlg )
		m_LocalPosition += move;
}

// オブジェクトを回転
void GameObject::Rotation(D3DXVECTOR3 rot, bool bFlg){
	m_Rotation += rot;
	m_RotAmount = rot;

	// 子にも反映 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->Rotation(rot,false);

	// もし親がいればローカル情報にも反映
	if( m_Parent && bFlg )
		m_LocalRotation += rot;
}

// オブジェクトの大きさを変更
void GameObject::ScaleChange(D3DXVECTOR3 scale, bool bFlg){
	m_Scale += scale;
	m_ScaleAmount = scale;

	// Collision範囲変更
	m_CollisionCubeMinus -= D3DXVECTOR3( m_BaseMinus.x*scale.x, m_BaseMinus.y*scale.y, m_BaseMinus.z*scale.z );
	m_CollisionCubePlus += D3DXVECTOR3( m_BasePlus.x*scale.x, m_BasePlus.y*scale.y, m_BasePlus.z*scale.z );
	m_fCollisionCircle += scale.x*m_fBaseCircle; // 球の半径なので、Scaleは全て同じなはずなので

	// 子にも反映 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ScaleChange(scale,false);

	// もし親がいればローカル情報にも反映
	if( m_Parent && bFlg )
		m_LocalScale += scale;
}

// 変化量初期化
void GameObject::InitAmount(){
	m_MoveAmount  = D3DXVECTOR3(0,0,0);
	m_RotAmount   = D3DXVECTOR3(0,0,0);
	m_ScaleAmount = D3DXVECTOR3(0,0,0);
}

// -- 変化量ゲッター
D3DXVECTOR3* GameObject::GetMoveAmount(){
	return &m_MoveAmount;
}

D3DXVECTOR3* GameObject::GetRotAmount(){
	return &m_RotAmount;
}

D3DXVECTOR3* GameObject::GetScaleAmount(){
	return &m_ScaleAmount;
}

// 移動したのを戻す
void GameObject::ReturnMove( bool bFlg ) {
	m_Position -= m_MoveAmount;

	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMove( false );

	// もし親がいればローカル情報にも反映
	if( m_Parent && bFlg )
		m_LocalPosition -= m_MoveAmount;
}

// 移動したのを戻す
void GameObject::ReturnMoveX( bool bFlg ) {
	m_Position.x -= m_MoveAmount.x;

	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveX( false );

	// もし親がいればローカル情報にも反映
	if( m_Parent && bFlg )
		m_LocalPosition.x -= m_MoveAmount.x;
}

// 移動したのを戻す
void GameObject::ReturnMoveY( bool bFlg ) {
	m_Position.y -= m_MoveAmount.y;

	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveY( false );

	// もし親がいればローカル情報にも反映
	if( m_Parent && bFlg )
		m_LocalPosition.y -= m_MoveAmount.y;
}

// 移動したのを戻す
void GameObject::ReturnMoveZ( bool bFlg ) {
	m_Position.z -= m_MoveAmount.z;

	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveZ( false );

	// もし親がいればローカル情報にも反映
	if( m_Parent && bFlg )
		m_LocalPosition.z -= m_MoveAmount.z;
}

// 回転したのを戻す 
void GameObject::ReturnRot( bool bFlg ) {
	m_Rotation -= m_RotAmount;

	// 子にも反映 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnRot( false );

	// もし親がいればローカル情報にも反映
	if( m_Parent && bFlg )
		m_LocalRotation -= m_RotAmount;
}

// 拡大したのを戻す
void GameObject::ReturnScale( bool bFlg ) {
	m_Scale -= m_ScaleAmount;

	// 子にも反映 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnScale( false );

	// もし親がいればローカル情報にも反映
	if( m_Parent && bFlg )
		m_LocalScale -= m_ScaleAmount;
}

// オブジェクトを自由に破壊できなくする
void GameObject::BanDestroy(){ 
	m_bDestroy = false;
}

// ライフを変動
void GameObject::SetLife( int nLife ) {
	m_nLife += nLife;
	if( m_nLife < 0 )
		m_nLife = 0;
}

// アクティブ状態を変更
void GameObject::SetActive(bool bFlg) {
	
	if(m_bActive != bFlg) {

		// Enable
		if(bFlg) {
			OnEnable();
		} 
		// Disable
		else {
			OnDisable();
		}
	}

	// 変更可なので変更
	m_bActive = m_bUpdate = bFlg;
}

// 更新フラグ変更
void GameObject::SetUpdateFlg(bool bFlg) {
	m_bUpdate = bFlg;
}

//
void GameObject::SetCollisionFlg(bool bFlg){
	m_bCollision = bFlg;
}

// 親子関係を設定
GameObject* GameObject::SetParent(GameObject* Parent){ 
	m_Parent = Parent; // 親に設定
	Parent->GetChild()->push_back(this); // このオブジェクトをParentの子に設定
	SetLocal();
	return Parent;
}

// ローカル情報を更新
void GameObject::SetLocal(){

	if(!m_Parent) 
		return;

	// 親との距離を計算
	m_LocalPosition = m_Position - *(m_Parent->GetPosition());
	m_LocalRotation = m_Rotation - *(m_Parent->GetRotation());
	m_LocalScale    = m_Scale    - *(m_Parent->GetScale());
}

// 当たり判定関係セッター
void GameObject::SetCollisionCubeSize( D3DXVECTOR3 PlusSize, D3DXVECTOR3 MinusSize ) {
	
	// プラス軸を格納
	m_CollisionCubePlus = PlusSize;
	m_BasePlus = PlusSize;
	
	// マイナス軸を格納
	m_CollisionCubeMinus = -MinusSize;
	m_BaseMinus = MinusSize;
}

void GameObject::SetCollisionCircleSize( float size ) {
	// 半径を格納
	m_fCollisionCircle = size;
	m_fBaseCircle = size;

	// OBBとの当たり判定で必要
	float fCubeSize = size*0.85f;
	m_CollisionCubePlus  = +D3DXVECTOR3(fCubeSize,fCubeSize,fCubeSize);
	m_BasePlus = m_CollisionCubePlus;
	m_CollisionCubeMinus = -D3DXVECTOR3(fCubeSize,fCubeSize,fCubeSize);
	m_BaseMinus = m_CollisionCubeMinus;
}

// 例外チェック
void GameObject::ExceptionCheck(){
	
	// 角度の例外チェック
	if( m_Rotation.x < 0.0f )
		Rotation( D3DXVECTOR3( Pai*2.0f,0,0 ) );
	else if( m_Rotation.x > Pai*2.0f )
		Rotation( D3DXVECTOR3( -Pai*2.0f,0,0 ) );
	if( m_Rotation.y < 0.0f )
		Rotation( D3DXVECTOR3( 0,Pai*2.0f,0 ) );
	else if( m_Rotation.y > Pai*2.0f )
		Rotation( D3DXVECTOR3( 0,-Pai*2.0f,0 ) );
	if( m_Rotation.z < 0.0f )
		Rotation( D3DXVECTOR3( 0,0,Pai*2.0f ) );
	else if( m_Rotation.z > Pai*2.0f )
		Rotation( D3DXVECTOR3( 0,0,-Pai*2.0f ) );
	
	// 相対角度の例外チェック
	if( m_LocalRotation.x < 0.0f )
		m_LocalRotation.x += Pai*2.0f;
	else if( m_LocalRotation.x > Pai*2.0f )
		m_LocalRotation.x -= Pai*2.0f;
	if( m_LocalRotation.y < 0.0f )
		m_LocalRotation.y += Pai*2.0f;
	else if( m_LocalRotation.y > Pai*2.0f )
		m_LocalRotation.y -= Pai*2.0f;
	if( m_LocalRotation.z < 0.0f )
		m_LocalRotation.z += Pai*2.0f;
	else if( m_LocalRotation.z > Pai*2.0f )
		m_LocalRotation.z -= Pai*2.0f;

	// 子がいれば子にも実施
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ExceptionCheck();
}