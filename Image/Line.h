#pragma once
#include "../Engine/GameObject.h"

//�e�X�g�V�[�����Ǘ�����N���X
class Line : public GameObject
{
public:
	int hPict_;    //�摜�ԍ�
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Line(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};