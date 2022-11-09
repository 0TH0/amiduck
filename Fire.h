#pragma once
#include "Engine/GameObject.h"

//�V�[�����Ǘ�����N���X
class Fire : public GameObject
{
public:
	int hModel_; 
	float PlayerPosX_;
	float PlayerPosY_;
	float PlayerPosZ_;

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Fire(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};