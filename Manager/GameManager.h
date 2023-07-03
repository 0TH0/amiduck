#pragma once
#include "../Engine/GameObject.h"

class GameManager: public GameObject
{
	enum
	{
		RED,
		BLUE,
		GREEN,
		ENEMY_MAX
	};
	XMINT3 randPos_;
	int EnemyTime_[ENEMY_MAX];
	int MAX_TIME;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GameManager(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�����o��
	void PopStar();

	//�����_��
	void RandObject();

	//�G����
	void EnemyReturn();
};