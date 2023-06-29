#pragma once
#include "../Engine/GameObject.h"

class GameManager: public GameObject
{
	XMINT3 randPos_;
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

	void PopStar();

	void RandStar();
};