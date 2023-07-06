#pragma once
#include "../Engine/GameObject.h"

static const int MAX_STAR = 5;
static const int MAX_STAR_AFTER_TIME = 120;

//�V�[�����Ǘ�����N���X
class Star : public GameObject
{
	int hModel_;
	int hPict_;    //�摜�ԍ�
	int MAX_TIME;
	int rimit_;
	float rimitY;
	float scale_;
	float gravity_;
	float rotateSpeed_;
	bool IsHit_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Star(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void OnCollision(GameObject* pTarget) override;
};