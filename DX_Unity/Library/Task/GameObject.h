//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameObject.h]
// author : �哴�ˑ�
// 
// �S�ẴQ�[���I�u�W�F�N�g�̐e�N���X
// ObjectType��3D,2D,Camera,Light������B
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

// -- �萔
const float Pai = 3.141592653589793f;
const D3DXVECTOR3 LimitPos = D3DXVECTOR3( 140.0f, 0.0f, 140.0f ); // �ړ��͈͐���

// -- �\���̒�`

// -- �N���X��`
class GameObject {

protected:
	// ---- ��{�ϐ�
	D3DXVECTOR3 m_Position; // ���W
	D3DXVECTOR3 m_Rotation; // �p�x
	D3DXVECTOR3 m_Scale;	// �T�C�Y
	D3DXVECTOR3 m_MoveAmount;	 // �ǂꂾ���ړ�������
	D3DXVECTOR3 m_RotAmount;	 // �ǂꂾ����]������
	D3DXVECTOR3 m_ScaleAmount;	 // �ǂꂾ���g��k��������
	bool m_bActive;			// �A�N�e�B�u���ǂ���
	bool m_bUpdate;			// �X�V�����邩
	bool m_bDestroy;		// ���̃I�u�W�F�N�g�͎��R�ɔj��ł��邩
	std::string m_Message;  // ���b�Z�[�W�ɉ����ē���̏��������s
	int m_nLife; 

	// ---- �O������͕ύX�s��
	std::string m_Name;	 // ���O
	std::string m_Tag;	 // �^�O
	std::string m_Layer; // ���C���[
	
	// ---- �e�q�֌W
	D3DXVECTOR3 m_LocalPosition;	  // �e���猩�����΍��W
	D3DXVECTOR3 m_LocalRotation;	  // �e���猩�����Ίp�x
	D3DXVECTOR3 m_LocalScale;		  // �e���猩�����΃T�C�Y
	GameObject* m_Parent;			  // �e�N���X
	std::list<GameObject*> m_Child;	  // �q�N���X

	// ---- �����蔻��
	bool m_bCollision;					// �����蔻����s���Ă��悢��
	D3DXVECTOR3 m_CollisionCubePlus;	// ���W�ł�+�̕�
	D3DXVECTOR3 m_CollisionCubeMinus;	// ���W�ł�-�̕�
	float m_fCollisionCircle;			// ���̂̑傫��
	D3DXVECTOR3 m_BasePlus;				// �I�u�W�F�N�g���g�傷��ۂ̕ύX��ɂȂ�l
	D3DXVECTOR3 m_BaseMinus;			// �I�u�W�F�N�g���g�傷��ۂ̕ύX��ɂȂ�l
	float m_fBaseCircle;				// �I�u�W�F�N�g���g�傷��ۂ̕ύX��ɂȂ�l
	
protected:
	// ---- �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�ύX�����ۂ̃C�x���g�֐�(�O������͌Ăяo���s��)
	virtual void OnEnable() {}
	virtual void OnDisable() {}

public:
	GameObject();
	virtual ~GameObject();

	// ---- ��{�֐�
	virtual void Awake(){}			   // �R���X�g���N�^�Ŏ��s
	virtual bool Start(){return true;} // �Q�[�����[�v1�t���[���ڂ�1�x�������s

	virtual void FastUpdate(){} // �D�悵��Update
	virtual void Update(){}	    // ���ʂ�Update
	virtual void LateUpdate(){} // �Ō��Update

	virtual void FastDraw(){}	// �D�悵��Draw
	virtual void Draw(){}		// ���ʂ�Draw
	virtual void LateDraw(){}	// �Ō��Draw

	virtual void Clear(){}		// �㏈��

	virtual GameObject* CreateChild(){return nullptr;} // Particle�Ȃ�new�̐����c��ɂȂ�I�u�W�F�g�����������悭�쐬����
	
	// ---- �_�E���L���X�g
	virtual GameObject* GetDownCastClass(GameObject* Obj) = 0; // �_�E���L���X�g�̂��߂ɂ͕K�{�f�X

	// ---- ��O�`�F�b�N
	void ExceptionCheck();
	
	// ---- Amount������
	void InitAmount();

	// ---- �ď�����
	void ReInit();
	
	// ---- �Q�b�^�[�֐�
	D3DXVECTOR3* GetPosition();				// ���W���擾
	D3DXVECTOR3* GetRotation();				// �p�x���擾
	D3DXVECTOR3* GetScale();				// �T�C�Y���擾
	D3DXVECTOR3* GetLocalPosition();		// ���΍��W���擾
	D3DXVECTOR3* GetLocalRotation();		// ���Ίp�x���擾
	D3DXVECTOR3* GetLocalScale();			// ���΃T�C�Y���擾
	
	D3DXVECTOR3* GetMoveAmount();			// �ړ��ʂ��擾
	D3DXVECTOR3* GetRotAmount();			// ��]�ʂ��擾
	D3DXVECTOR3* GetScaleAmount();			// �g��k�����ʂ��擾

	const std::string GetName();			// ���O�擾
	const std::string GetTag();				// �^�O�擾
	const std::string GetLayer();			// ���C���[�擾

	bool GetActive();						// ���̃I�u�W�F�N�g�̓A�N�e�B�u���ǂ���
	bool GetUpdateFlg();					// ���̃I�u�W�F�N�g�͍X�V���邩
	const bool GetDestory();				// ���̃I�u�W�F�N�g�͔j��\��
	int GetLife(); 

	// --- Free�֐�
	virtual void FreeFunction(){}
	virtual int* GetInt() {return nullptr;}
	virtual float* GetFloat() {return nullptr;}
	virtual bool* GetBool() {return nullptr;}
	virtual D3DXVECTOR3* GetVec() {return nullptr;}
	virtual D3DXCOLOR* GetColor(){ return nullptr; }

	// �e�q
	GameObject* GetParent();				// �e�̃I�u�W�F�N�g�擾
	std::list<GameObject*>* GetChild();	// �q�̃I�u�W�F�N�g�擾
	GameObject* FindChild(const std::string Name); // ����̎q�I�u�W�F�N�g���擾
	std::list<GameObject*> FindChildAll(const std::string Name); // ����̎q�I�u�W�F�N�g���擾

	// �����蔻��
	D3DXVECTOR3 GetCollisionCubePlusSize();
	D3DXVECTOR3 GetCollisionCubeMinusSize();
	float GetCollisionCircleSize();
	bool GetCollisionFlg();

	// ---- �Z�b�^�[�֐�
	void Move(D3DXVECTOR3 move, bool bFlg = true);			// �I�u�W�F�N�g���ړ�(�q������Ύq��)
	void Rotation(D3DXVECTOR3 rot, bool bFlg = true);		// �I�u�W�F�N�g����](�q������Ύq��)
	void ScaleChange(D3DXVECTOR3 scale, bool bFlg = true);  // �I�u�W�F�N�g�X�P�[���ύX(�q������Ύq��)
	void ReturnMove( bool bFlg = true );	// �ړ������̂�߂�
	void ReturnMoveX( bool bFlg = true );	// �ړ�����X��߂�
	void ReturnMoveY( bool bFlg = true );	// �ړ�����Y��߂�
	void ReturnMoveZ( bool bFlg = true );	// �ړ�����Z��߂�
	void ReturnRot( bool bFlg = true );		// ��]�����̂�߂�
	void ReturnScale( bool bFlg = true );	// �g�債���̂�߂�
	
	void SetCollisionCubeSize(D3DXVECTOR3 PlusSize, D3DXVECTOR3 MinusSize);
	void SetCollisionCircleSize(float size);

	GameObject* SetParent(GameObject* Parent);  // �e�q�֌W��ݒ�
	void SetLocal();	// ���[�J�������i�[
	
	void SetActive(bool bFlg);
	void SetUpdateFlg(bool bFlg);
	void BanDestroy();  // ���̃I�u�W�F�N�g��j��ł��Ȃ�����
	void SendForMessage(std::string msg);	// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗂�
	void SetLife(int nLife); // ���C�t��ϓ�����
	void SetCollisionFlg(bool bFlg); 
};

#endif