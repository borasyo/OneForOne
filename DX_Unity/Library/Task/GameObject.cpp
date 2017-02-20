//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameObject.cpp]
// author : �哴�ˑ�
// 
// �S�ẴQ�[���I�u�W�F�N�g�̐e�N���X
// ObjectType��3D,2D,Camera,Light������B
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

// ---- �ď�����
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

// ---- �Q�b�^�[�֐�
// ���W���擾
inline D3DXVECTOR3* GameObject::GetPosition(){ 
	return &m_Position;
}

// �p�x���擾
inline D3DXVECTOR3* GameObject::GetRotation(){ 
	return &m_Rotation;
}		

// �T�C�Y���擾
inline D3DXVECTOR3* GameObject::GetScale(){
	return &m_Scale;
}

// ���΍��W���擾
inline D3DXVECTOR3* GameObject::GetLocalPosition(){ 
	return &m_LocalPosition;
}

// ���Ίp�x���擾
inline D3DXVECTOR3* GameObject::GetLocalRotation(){ 
	return &m_LocalRotation;
}		

// ���΃T�C�Y���擾
inline D3DXVECTOR3* GameObject::GetLocalScale(){
	return &m_LocalScale;
}

// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗂�
void GameObject::SendForMessage(std::string msg){ 
	m_Message = msg;
}	

// Object��Life���擾
int GameObject::GetLife(){
	return m_nLife;
}

// ���O�擾
const std::string GameObject::GetName(){ 
	return m_Name;
}				

// �^�O�擾
const std::string GameObject::GetTag(){ 
	return m_Tag;
}				

// ���C���[�擾
const std::string GameObject::GetLayer(){ 
	return m_Layer;
}			

// �e�̃I�u�W�F�N�g�擾
GameObject* GameObject::GetParent(){ 

	if( m_Parent )
		return m_Parent;

	return nullptr;
}				

// �q�̃I�u�W�F�N�g�擾
inline std::list<GameObject*>* GameObject::GetChild(){ 
	return &m_Child;
}	

// ���̃I�u�W�F�N�g�̓A�N�e�B�u���ǂ���
bool GameObject::GetActive(){ 
	return m_bActive;
}				

// ���̃I�u�W�F�N�g�͍X�V���邩�ǂ���
bool GameObject::GetUpdateFlg(){ 
	return m_bUpdate;
}				

// ���̃I�u�W�F�N�g�͔j��\���ǂ���
const bool GameObject::GetDestory(){ 
	return m_bDestroy;
}

// ����̎q�I�u�W�F�N�g���擾
GameObject* GameObject::FindChild(const std::string Name){
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		if( Name == (*Ite)->GetName() )
			return *Ite;
	return nullptr;
}

// ����̎q�I�u�W�F�N�g�S�Ă��擾
std::list<GameObject*> GameObject::FindChildAll(const std::string Name){	
	std::list<GameObject*> findchild;
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		if( Name == (*Ite)->GetName() ) findchild.push_back(*Ite);
	return findchild; 
}

//	�����蔻��֌W�Q�b�^�[
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

// ---- �Z�b�^�[�֐�
// �I�u�W�F�N�g���ړ�
void GameObject::Move(D3DXVECTOR3 move, bool bFlg){
	m_Position += move;
	m_MoveAmount = move;
	
	// �q�ɂ����f 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->Move(move,false);

	// �����e������΃��[�J�����ɂ����f
	if( m_Parent && bFlg )
		m_LocalPosition += move;
}

// �I�u�W�F�N�g����]
void GameObject::Rotation(D3DXVECTOR3 rot, bool bFlg){
	m_Rotation += rot;
	m_RotAmount = rot;

	// �q�ɂ����f 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->Rotation(rot,false);

	// �����e������΃��[�J�����ɂ����f
	if( m_Parent && bFlg )
		m_LocalRotation += rot;
}

// �I�u�W�F�N�g�̑傫����ύX
void GameObject::ScaleChange(D3DXVECTOR3 scale, bool bFlg){
	m_Scale += scale;
	m_ScaleAmount = scale;

	// Collision�͈͕ύX
	m_CollisionCubeMinus -= D3DXVECTOR3( m_BaseMinus.x*scale.x, m_BaseMinus.y*scale.y, m_BaseMinus.z*scale.z );
	m_CollisionCubePlus += D3DXVECTOR3( m_BasePlus.x*scale.x, m_BasePlus.y*scale.y, m_BasePlus.z*scale.z );
	m_fCollisionCircle += scale.x*m_fBaseCircle; // ���̔��a�Ȃ̂ŁAScale�͑S�ē����Ȃ͂��Ȃ̂�

	// �q�ɂ����f 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ScaleChange(scale,false);

	// �����e������΃��[�J�����ɂ����f
	if( m_Parent && bFlg )
		m_LocalScale += scale;
}

// �ω��ʏ�����
void GameObject::InitAmount(){
	m_MoveAmount  = D3DXVECTOR3(0,0,0);
	m_RotAmount   = D3DXVECTOR3(0,0,0);
	m_ScaleAmount = D3DXVECTOR3(0,0,0);
}

// -- �ω��ʃQ�b�^�[
D3DXVECTOR3* GameObject::GetMoveAmount(){
	return &m_MoveAmount;
}

D3DXVECTOR3* GameObject::GetRotAmount(){
	return &m_RotAmount;
}

D3DXVECTOR3* GameObject::GetScaleAmount(){
	return &m_ScaleAmount;
}

// �ړ������̂�߂�
void GameObject::ReturnMove( bool bFlg ) {
	m_Position -= m_MoveAmount;

	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMove( false );

	// �����e������΃��[�J�����ɂ����f
	if( m_Parent && bFlg )
		m_LocalPosition -= m_MoveAmount;
}

// �ړ������̂�߂�
void GameObject::ReturnMoveX( bool bFlg ) {
	m_Position.x -= m_MoveAmount.x;

	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveX( false );

	// �����e������΃��[�J�����ɂ����f
	if( m_Parent && bFlg )
		m_LocalPosition.x -= m_MoveAmount.x;
}

// �ړ������̂�߂�
void GameObject::ReturnMoveY( bool bFlg ) {
	m_Position.y -= m_MoveAmount.y;

	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveY( false );

	// �����e������΃��[�J�����ɂ����f
	if( m_Parent && bFlg )
		m_LocalPosition.y -= m_MoveAmount.y;
}

// �ړ������̂�߂�
void GameObject::ReturnMoveZ( bool bFlg ) {
	m_Position.z -= m_MoveAmount.z;

	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveZ( false );

	// �����e������΃��[�J�����ɂ����f
	if( m_Parent && bFlg )
		m_LocalPosition.z -= m_MoveAmount.z;
}

// ��]�����̂�߂� 
void GameObject::ReturnRot( bool bFlg ) {
	m_Rotation -= m_RotAmount;

	// �q�ɂ����f 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnRot( false );

	// �����e������΃��[�J�����ɂ����f
	if( m_Parent && bFlg )
		m_LocalRotation -= m_RotAmount;
}

// �g�債���̂�߂�
void GameObject::ReturnScale( bool bFlg ) {
	m_Scale -= m_ScaleAmount;

	// �q�ɂ����f 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnScale( false );

	// �����e������΃��[�J�����ɂ����f
	if( m_Parent && bFlg )
		m_LocalScale -= m_ScaleAmount;
}

// �I�u�W�F�N�g�����R�ɔj��ł��Ȃ�����
void GameObject::BanDestroy(){ 
	m_bDestroy = false;
}

// ���C�t��ϓ�
void GameObject::SetLife( int nLife ) {
	m_nLife += nLife;
	if( m_nLife < 0 )
		m_nLife = 0;
}

// �A�N�e�B�u��Ԃ�ύX
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

	// �ύX�Ȃ̂ŕύX
	m_bActive = m_bUpdate = bFlg;
}

// �X�V�t���O�ύX
void GameObject::SetUpdateFlg(bool bFlg) {
	m_bUpdate = bFlg;
}

//
void GameObject::SetCollisionFlg(bool bFlg){
	m_bCollision = bFlg;
}

// �e�q�֌W��ݒ�
GameObject* GameObject::SetParent(GameObject* Parent){ 
	m_Parent = Parent; // �e�ɐݒ�
	Parent->GetChild()->push_back(this); // ���̃I�u�W�F�N�g��Parent�̎q�ɐݒ�
	SetLocal();
	return Parent;
}

// ���[�J�������X�V
void GameObject::SetLocal(){

	if(!m_Parent) 
		return;

	// �e�Ƃ̋������v�Z
	m_LocalPosition = m_Position - *(m_Parent->GetPosition());
	m_LocalRotation = m_Rotation - *(m_Parent->GetRotation());
	m_LocalScale    = m_Scale    - *(m_Parent->GetScale());
}

// �����蔻��֌W�Z�b�^�[
void GameObject::SetCollisionCubeSize( D3DXVECTOR3 PlusSize, D3DXVECTOR3 MinusSize ) {
	
	// �v���X�����i�[
	m_CollisionCubePlus = PlusSize;
	m_BasePlus = PlusSize;
	
	// �}�C�i�X�����i�[
	m_CollisionCubeMinus = -MinusSize;
	m_BaseMinus = MinusSize;
}

void GameObject::SetCollisionCircleSize( float size ) {
	// ���a���i�[
	m_fCollisionCircle = size;
	m_fBaseCircle = size;

	// OBB�Ƃ̓����蔻��ŕK�v
	float fCubeSize = size*0.85f;
	m_CollisionCubePlus  = +D3DXVECTOR3(fCubeSize,fCubeSize,fCubeSize);
	m_BasePlus = m_CollisionCubePlus;
	m_CollisionCubeMinus = -D3DXVECTOR3(fCubeSize,fCubeSize,fCubeSize);
	m_BaseMinus = m_CollisionCubeMinus;
}

// ��O�`�F�b�N
void GameObject::ExceptionCheck(){
	
	// �p�x�̗�O�`�F�b�N
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
	
	// ���Ίp�x�̗�O�`�F�b�N
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

	// �q������Ύq�ɂ����{
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ExceptionCheck();
}