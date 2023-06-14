#pragma once
#include "Engine/GameObject.h"
#include "Scene/PlayScene.h"

//�V�[�����Ǘ�����N���X
class Instructions : public GameObject
{
public:
	int hPict_;    //�摜�ԍ�
	bool IsInstructions;

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Instructions(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};