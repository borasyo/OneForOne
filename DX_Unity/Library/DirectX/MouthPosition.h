//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MouthPosition.h]
// author : �哴�ˑ�
//
// �}�E�X�̍��W���擾����B
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

	Position_2D* GetMouthScreenPosition(); // Position_2D�\���̂�Ԃ�(�X�N���[�����W)
	Position_2D* GetMouthScreenPosition( float *PositionX ); // �|�C���^�ɏ����Z�b�g(�X�N���[�����W)
	Position_2D* GetMouthScreenPosition( float *PositionX , float *PositionY );

	Position_2D* GetMouthClientPosition(); // Position_2D�\���̂�Ԃ�(�N���C�A���g���W)
	Position_2D* GetMouthClientPosition( float *PositionX ); // �|�C���^�ɏ����Z�b�g(�N���C�A���g���W)
	Position_2D* GetMouthClientPosition( float *PositionX , float *PositionY );

	void SetMouthClientPosition( float PositionX , float PositionY ); // �w��N���C�A���g���W�ɃJ�[�\�����ړ�������

	D3DXVECTOR3 GetScale();

protected:
private:
	CMouthPosition();

private:
	Position_2D* m_tScreenPosition; // �X�N���[�����W
	Position_2D* m_tClientPosition; // �N���C�A���g���W

	bool m_bInitialized;
	bool m_ShowMouthFlag;
};

#endif