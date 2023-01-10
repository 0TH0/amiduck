#pragma once
#include "GameObject.h"
#include "Fbx.h"

//-----------------------------------------------------------
//�J����
//-----------------------------------------------------------
namespace Camera
{
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize();

	//�X�V�i�r���[�s��쐬�j
	void Update();

	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMFLOAT3 position);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMFLOAT3 target);

	//�ʒu���擾
	XMFLOAT3 GetPosition();

	//�œ_���擾
	XMFLOAT3 GetTarget();

	//�r���[�s����擾
	XMMATRIX GetViewMatrix();

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix();

	//�r���{�[�h�p��]�s����擾
	XMMATRIX GetBillboardMatrix();

	void SetDefault();

	void SetDual();

	int GetDual();

	//�r���[�|�[�g�s����擾
	XMMATRIX GetViewPortMatrix();

	//�X�N���[�����W���烏�[���h���W�Ɍv�Z����
	void CalcScreenToWorld(RayCastData& rayData);
	
	//�X�^�[�g�ʒu�̃x�N�g���擾
	XMVECTOR GetvStart();

	//�^�[�Q�b�g�ʒu�̃x�N�g���擾
	XMVECTOR GetvTarget();

	//�e�t�s������߂�
	XMMATRIX CalcinvTransform();

	//�X�^�[�g�ʒu�̃x�N�g���擾
	XMFLOAT3 &GetMousePosBack();

	//�^�[�Q�b�g�ʒu�̃x�N�g���擾
	XMFLOAT3 &GetMousePosFront();

	float GetScrWDiv2();

	float GetScrHDiv2();
};