//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Hierarchy.cpp]
// author : �哴�ˑ�
// 
// Scene��̑S�ẴI�u�W�F�N�g���Ǘ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Hierarchy.h"
#include <iostream>

Hierarchy::Hierarchy(){}

// �S�ẴQ�[���I�u�W�F�N�g���폜
Hierarchy::~Hierarchy(){
	Clear();
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) delete *Ite;
	AllGameObject.erase(AllGameObject.begin(),AllGameObject.end());
}
	
// �C���X�^���X�擾
Hierarchy* Hierarchy::Create(){
	static Hierarchy* hierarchy = new Hierarchy;
	return hierarchy;
}

// �Q�[���I�u�W�F�N�g�V�K�쐬
GameObject* Hierarchy::CreateObject(GameObject* Obj){
	AllGameObject.push_back(Obj);
	return Obj;
}

// �Q�[���I�u�W�F�N�g���폜	
bool Hierarchy::DestroyObject(GameObject* pObj, bool bParentErase){

	// ���̃I�u�W�F�N�g�͑��݂��邩���`�F�b�N
	if( !pObj )
		return false; // ���s!!

	// �T���̑O�ɔj��\���`�F�b�N
	if( !pObj->GetDestory() )
		return false; // ���s!!

	// �q���폜
	std::list<GameObject*>* Child = pObj->GetChild(); // �q���X�g���擾
	for( auto ChildIte = Child->begin(); ChildIte != Child->end(); ChildIte++ ) {
		DestroyObject(*ChildIte,false); // �q���X�g�S�Ă�Destroy�����s
		(*ChildIte)->SetLife(-999);
	}

	if( pObj->GetName() == "Shadow" ) {
		int i = 0;
	}

	// �e������΁A�e�ւ̓o�^������(bParentErase��false�̏ꍇ�A�d������̂ŉ������Ȃ�)
	if( pObj->GetParent() && bParentErase ){
		std::list<GameObject*>* Parent = pObj->GetParent()->GetChild(); // �e�̎q���X�g���擾
		if( Parent ) {
		for( auto ParentIte = Parent->begin(); ParentIte != Parent->end(); ParentIte++ ){
			if( pObj == *ParentIte ){ // �e�̎q���X�g���玩���������o��
				Parent->erase(ParentIte); // �폜
				break;
			}
		}
		}
	}

	// ���g���폜
	pObj->Clear();
	pObj->SetLife(-999);

	return true; // ����!!
}

// �J�n����
bool Hierarchy::Start(){
	// �D��I�ɏ�����
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		// Awake���s
		(*Ite)->Awake();	
	}

	// �ʏ�̏�����
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		// Start���s
		if(!(*Ite)->Start())
			return false;
 	}
	return true;
}

// �X�V����
void Hierarchy::Update(){
	// LifeCheck
	std::vector<GameObject*> Destroy;
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite ++)
		if( (*Ite)->GetLife() == 0 )
			Destroy.push_back(*Ite);
	for( auto Ite = Destroy.begin(); Ite != Destroy.end(); Ite++ )
		DestroyObject(*Ite);
	
	// Null�ɂȂ����I�u�W�F�N�g�����X�g�������
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

// �`�揈��
void Hierarchy::Draw(){
	// LifeCheck
	std::vector<GameObject*> Destroy;
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite ++)
		if( (*Ite)->GetLife() == 0 )
			Destroy.push_back(*Ite);
	for( auto Ite = Destroy.begin(); Ite != Destroy.end(); Ite++ )
		DestroyObject(*Ite);

	// Null�ɂȂ����I�u�W�F�N�g�����X�g�������
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

// �폜����
void Hierarchy::Clear(){	
	for( auto Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ )
		(*Ite)->Clear();
}

// ���񂾃I�u�W�F�N�g�����X�g�������
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

// �S�ẴI�u�W�F�N�g���擾
std::list<GameObject*>* Hierarchy::FindAllObject(){
	return &AllGameObject;
}

// �S�ẴA�N�e�B�u�I�u�W�F�N�g���擾
std::list<GameObject*> Hierarchy::FindWithActive(){
	std::list<GameObject*> GetObj;

	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;
		
		// Active�Ȃ̂Ŋi�[
		GetObj.push_back(*Ite);
	}

	return GetObj;
}

// �S�ẴI�u�W�F�N�g�̒����疼�O�̈�v����I�u�W�F�N�g��S�ĕԂ�
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

// �S�ẴI�u�W�F�N�g�̒����疼�O�̈�v����I�u�W�F�N�g��1�Ԃ�(name��unique�ł͂Ȃ��ꍇ�g�p���Ȃ�)
GameObject* Hierarchy::FindWithName(const std::string name){
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		//if( !(*Ite)->GetActive() ) 
		//	continue;
		if( (*Ite)->GetName() == name ) 
			return *Ite;
	}
	
	return nullptr;
}

// �S�ẴI�u�W�F�N�g�̒�����^�O�̈�v����I�u�W�F�N�g��S�ĕԂ�
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

// �S�ẴI�u�W�F�N�g�̒�����^�O�̈�v����I�u�W�F�N�g��1�Ԃ�(tag��unique�ł͂Ȃ��ꍇ�g�p���Ȃ�)
GameObject* Hierarchy::FindWithTag(const std::string tag){
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ) {
		if( !(*Ite)->GetActive() ) 
			continue;
		if( (*Ite)->GetTag() == tag ) 
			return *Ite;
	}

	return nullptr;
}

// �S�ẴI�u�W�F�N�g�̒����烌�C���[�̈�v����I�u�W�F�N�g��S�ĕԂ�
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

// �S�ẴI�u�W�F�N�g�̒����烌�C���[�̈�v����I�u�W�F�N�g��1�Ԃ�(layer��unique�ł͂Ȃ��ꍇ�g�p���Ȃ�)
GameObject* Hierarchy::FindWithLayer(const std::string layer){
	for( std::list<GameObject*>::iterator Ite = AllGameObject.begin(); Ite != AllGameObject.end(); Ite++ ){
		//if( !(*Ite)->GetActive() ) 
		//	continue;
		if( (*Ite)->GetLayer() == layer ) 
			return *Ite;
	}

	return nullptr;
}